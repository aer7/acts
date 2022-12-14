#!/usr/bin/env python3
import pathlib, acts, acts.examples
from acts.examples.simulation import (
    addParticleGun,
    MomentumConfig,
    EtaConfig,
    ParticleConfig,
    addPythia8,
    addFatras,
    ParticleSelectorConfig,
    addDigitization,
)
from acts.examples.reconstruction import (
    addSeeding,
    TruthSeedRanges,
    addCKFTracks,
    CKFPerformanceConfig,
    addVertexFitting,
    VertexFinder,
    TrackSelectorRanges,
)
from common import getOpenDataDetectorDirectory
from acts.examples.odd import getOpenDataDetector
import datetime
import os

logger = acts.logging.getLogger("full_chain_odd")
logger.info("Starting full_chain_odd")

ttbar_pu200 = True
u = acts.UnitConstants
geoDir = getOpenDataDetectorDirectory()
outputDir = pathlib.Path.cwd() / datetime.datetime.now().strftime('%Y-%m-%d-%H-%M-%S')
os.mkdir(outputDir)
os.mkdir(outputDir / 'pythia')
os.mkdir(outputDir / 'fatras')
os.mkdir(outputDir / 'digitization')
os.mkdir(outputDir / 'seeding')
os.mkdir(outputDir / 'ckf')
os.mkdir(outputDir / 'vertexfitting')

# acts.examples.dump_args_calls(locals())  # show python binding calls

oddMaterialMap = geoDir / "data/odd-material-maps.root"
oddDigiConfig = geoDir / "config/odd-digi-smearing-config.json"
oddSeedingSel = geoDir / "config/odd-seeding-config.json"
oddMaterialDeco = acts.IMaterialDecorator.fromFile(oddMaterialMap)

detector, trackingGeometry, decorators = getOpenDataDetector(
    geoDir, mdecorator=oddMaterialDeco
)
field = acts.ConstantBField(acts.Vector3(0.0, 0.0, 2.0 * u.T))
rnd = acts.examples.RandomNumbers(seed=42)

s = acts.examples.Sequencer(events=1, numThreads=-1, outputDir=str(outputDir))

if not ttbar_pu200:
    logger.info('Using particle gun, not pythia.')
    addParticleGun(
        s,
        MomentumConfig(1.0 * u.GeV, 10.0 * u.GeV, transverse=True),
        EtaConfig(-3.0, 3.0, uniform=True),
        ParticleConfig(2, acts.PdgParticle.eMuon, randomizeCharge=True),
        rnd=rnd,
    )
else:
    logger.info('Using pythia, not particle gun.')
    addPythia8(
        s,
        hardProcess=["Top:qqbar2ttbar=on"],
        npileup=10,
        vtxGen=acts.examples.GaussianVertexGenerator(
            stddev=acts.Vector4(0.0125 * u.mm, 0.0125 * u.mm, 55.5 * u.mm, 5.0 * u.ns),
            mean=acts.Vector4(0, 0, 0, 0),
        ),
        rnd=rnd,
        outputDirRoot=outputDir / 'pythia',
    )

addFatras(
    s,
    trackingGeometry,
    field,
    ParticleSelectorConfig(eta=(-3.0, 3.0), pt=(150 * u.MeV, None), removeNeutral=True)
    if ttbar_pu200
    else ParticleSelectorConfig(),
    outputDirRoot=outputDir / 'fatras',
    rnd=rnd,
)

addDigitization(
    s,
    trackingGeometry,
    field,
    digiConfigFile=oddDigiConfig,
    outputDirRoot=outputDir / 'digitization',
    rnd=rnd,
)

addSeeding(
    s,
    trackingGeometry,
    field,
    TruthSeedRanges(pt=(1.0 * u.GeV, None), eta=(-3.0, 3.0), nHits=(9, None))
    if ttbar_pu200
    else TruthSeedRanges(),
    geoSelectionConfigFile=oddSeedingSel,
    outputDirRoot=outputDir / 'seeding',
)

addCKFTracks(
    s,
    trackingGeometry,
    field,
    CKFPerformanceConfig(ptMin=1.0 * u.GeV if ttbar_pu200 else 0.0, nMeasurementsMin=6),
    outputDirRoot=outputDir / 'ckf',
)

addVertexFitting(
    s,
    field,
    TrackSelectorRanges(pt=(1.0 * u.GeV, None), absEta=(None, 3.0), removeNeutral=True),
    vertexFinder=VertexFinder.Iterative,
    trajectories="trajectories",
    outputDirRoot=outputDir / 'vertexfitting'
)

s.run()
