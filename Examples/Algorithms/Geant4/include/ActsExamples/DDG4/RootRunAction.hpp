#include "G4Types.hh"
#include <G4UserRunAction.hh>
#include <G4RunManager.hh>
#include <TBranch.h>
#include <TFile.h>
#include <TTree.h>
#include "TClass.h"
#include <G4VHitsCollection.hh> 

namespace ActsExamples::DDG4 {

  class RootRunAction final : public G4UserRunAction {
  public:
    // Interface
    RootRunAction();
    ~RootRunAction();
    G4Run* GenerateRun();
    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction(const G4Run* aRun);
    inline virtual void SetMaster(G4bool val = true) { isMaster = val; }
    inline G4bool IsMaster() const { return isMaster; }
    
  protected:
    // Interface
    G4bool isMaster = false;

    // No interface
    std::string m_output;
    bool        m_errorFatal;
    // Geant4ParticleMap* m_truth;
    typedef std::map<std::string, TBranch*> Branches;
    typedef std::map<std::string, TTree*> Sections;
    /// Known file sections
    Sections m_sections;
    /// Branches in the event tree
    Branches m_branches;
    /// Reference to the ROOT file to open
    TFile* m_file;
    /// Reference to the event data tree
    TTree* m_tree;
    /// File sequence number
    int    m_fseqNunmber  { 0 };
    /// Property: name of the event tree
    std::string m_section = "EVENT";
    /// Property: vector with disabled collections
    std::vector<std::string> m_disabledCollections;
    /// Property: vector with disabled collections
    bool  m_disableParticles = false;
    /// Property: Flag if Monte-Carlo truth should be followed and checked
    bool m_handleMCTruth = true;
    /// Property: Flag if Monte-Carlo truth should be followed and checked
    bool m_filesByRun = false;
    TTree* section(const std::string& nam);
    class ComponentCast;
    int fill(const std::string& nam, TClass* c, void* ptr);
    virtual void closeOutput();
    virtual void saveCollection(G4VHitsCollection* collection);
    virtual void commit(G4Event* ctxt);
    G4Run* run;
  };
}
