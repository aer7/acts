#include "G4Types.hh"
#include <G4UserRunAction.hh>
#include <G4Run.hh>
#include <iostream>
#include "ActsExamples/DDG4/RootRunAction.hpp"
#include "TClass.h"
#include <G4VHitsCollection.hh> 

namespace ActsExamples::DDG4 {
  RootRunAction::RootRunAction() : G4UserRunAction() {
    std::cout << "construct run action\n";
    run = nullptr;
  }
  
  RootRunAction::~RootRunAction() {
    std::cout << "destruct run action\n";

    // TDirectory::TContext ctxt(m_file);
    // Sections::iterator i = m_sections.find(m_section);

    // std::cout << "Closing root file."

    // if ( i != m_sections.end() )
    //   m_sections.erase(i);
    
    // m_branches.clear();
    // m_tree->Write();
    // m_file->Close();
    // m_tree = 0;
    // detail::deletePtr (m_file);
  }

  G4Run* RootRunAction::GenerateRun() {
    std::cout << "generate run\n";
    return nullptr;
  }

  void RootRunAction::BeginOfRunAction(const G4Run* aRun) {
    std::cout << "begin run action\n";
    std::string fname = "fname";
    TDirectory::TContext ctxt(TDirectory::CurrentDirectory());
    m_file = TFile::Open(fname.c_str(), "RECREATE", "Simulation data");
    if (m_file->IsZombie()) {
      delete m_file;
      std::cout << "Failed to open m_file";
      throw;
    }
    m_tree = section(m_section);
  }
  
  void RootRunAction::EndOfRunAction(const G4Run* aRun) {
    std::cout << "End run\n";
  }

  TTree* RootRunAction::section(const std::string& nam) {
    // Sections::const_iterator i = m_sections.find(nam);
    // if (i == m_sections.end()) {
    //   TDirectory::TContext ctxt(m_file);
    //   TTree* t = new TTree(nam.c_str(), ("Geant4 " + nam + " information").c_str());
    //   m_sections.emplace(nam, t);
    //   return t;
    // }
    // return (*i).second;
    return nullptr;
  }

  int RootRunAction::fill(const std::string& nam, TClass* c, void* ptr) {
    // if (m_file) {
    //   TBranch* b = 0;
    //   Branches::const_iterator i = m_branches.find(nam);
    //   if (i == m_branches.end()) {
    // 	const std::type_info& typ = type.type();
    // 	TClass* cl = TBuffer::GetClass(typ);
    // 	if (cl) {
    // 	  b = m_tree->Branch(nam.c_str(), cl->GetName(), (void*) 0);
    // 	  b->SetAutoDelete(false);
    // 	  m_branches.emplace(nam, b);
    // 	}
    // 	else {
    // 	  throw runtime_error("No ROOT TClass object availible for object type:" + typeName(typ));
    // 	}
    //   }
    //   else {
    // 	b = (*i).second;
    //   }
    //   Long64_t evt = b->GetEntries(), nevt = b->GetTree()->GetEntries(), num = nevt - evt;
    //   if (nevt > evt) {
    // 	b->SetAddress(0);
    // 	while (num > 0) {
    // 	  b->Fill();
    // 	  --num;
    // 	}
    //   }
    //   b->SetAddress(&ptr);
    //   int nbytes = b->Fill();
    //   if (nbytes < 0) {
    // 	throw runtime_error("Failed to write ROOT collection:" + nam + "!");
    //   }
    //   return nbytes;
    // }
    return 0;
  }

  void RootRunAction::commit(G4Event* ctxt) {
    // TObjArray* a = m_tree->GetListOfBranches();
    // Long64_t evt = m_tree->GetEntries() + 1;
    // Int_t nb = a->GetEntriesFast();
    // /// Fill NULL pointers to all branches, which have less entries than the Event branch
    // for (Int_t i = 0; i < nb; ++i) {
    //   TBranch* br_ptr = (TBranch*) a->UncheckedAt(i);
    //   Long64_t br_evt = br_ptr->GetEntries();
    //   if (br_evt < evt) {
    //     Long64_t num = evt - br_evt;
    //     br_ptr->SetAddress(0);
    //     while (num > 0) {
    //       br_ptr->Fill();
    //       --num;
    //     }
    //   }
    // }
    // m_tree->SetEntries(evt);
  }

  void RootRunAction::closeOutput() {
    
  }
  
  void RootRunAction::saveCollection(G4VHitsCollection* collection) {
    
  }
  
}
