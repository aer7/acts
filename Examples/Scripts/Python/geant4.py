#!/usr/bin/env python3
from pathlib import Path

import acts
import os
import datetime
import acts.examples
from acts.examples.simulation import addParticleGun, addGeant4, EtaConfig
from acts.examples.odd import getOpenDataDetector
from common import getOpenDataDetectorDirectory

u = acts.UnitConstants


def runGeant4(
    geometryService,
    trackingGeometry,
    field,
    outputDir,
    s: acts.examples.Sequencer = None,
):
    s = s or acts.examples.Sequencer(events=100, numThreads=1)
    s.config.logLevel = acts.logging.INFO
    rnd = acts.examples.RandomNumbers()
    
    addParticleGun(
        s,
        EtaConfig(-2.0, 2.0),
        rnd=rnd,
    )

    os.mkdir(outputDir)
    os.mkdir(outputDir / 'geant')
    addGeant4(
        s,
        geometryService,
        trackingGeometry,
        field,
        outputDirRoot = outputDir / 'geant',
        rnd=rnd,
    )
    return s


if "__main__" == __name__:
    
    detector, trackingGeometry, decorators = getOpenDataDetector(
        getOpenDataDetectorDirectory()
    )
    field = acts.ConstantBField(acts.Vector3(0, 0, 2 * u.T))
    
    outputDir = Path.cwd() / datetime.datetime.now().strftime('%Y-%m-%d-%H-%M-%S')
    runGeant4(detector.geometryService, trackingGeometry, field, outputDir).run()
