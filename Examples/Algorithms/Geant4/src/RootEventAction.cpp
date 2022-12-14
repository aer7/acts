// This file is part of the Acts project.
//
// Copyright (C) 2020 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "ActsExamples/DDG4/RootEventAction.hpp"
#include <DDG4/Geant4Output2ROOT.h>
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4ParticleTable.hh>
#include <G4Run.hh>
#include <G4RunManager.hh>
#include <TBranch.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <stdexcept>

namespace ActsExamples::DDG4 {
  // G4UserEventAction
  RootEventAction::RootEventAction() : G4UserEventAction()  {
    if (s_instance != nullptr) {
      throw std::logic_error("Attempted to duplicate a singleton");
    } else {
      s_instance = this;
    }
    std::cout << "construct \n";
  }

  // G4UserEventAction
  RootEventAction::~RootEventAction() {
    s_instance = nullptr;
    std::cout << "destruct \n";
  }

  // G4UserEventAction
  void RootEventAction::BeginOfEventAction(const G4Event* event) {
    std::cout << "start event\n";
  }

  // G4UserEventAction
  void RootEventAction::EndOfEventAction(const G4Event* event) {
    std::cout << "end event\n";
    // OutputContext<G4Event> ctxt(evt);
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (hce)  {
      int nCol = hce->GetNumberOfCollections();
      std::cout << "Found HitCollection";
      std::cout << std::to_string(nCol);
      // try  {
      // 	m_truth = event().extension<Geant4ParticleMap>(false);
      // 	if ( m_truth && !m_truth->isValid() )  {
      // 	  m_truth = 0;
      // 	  printout(WARNING,name(),"+++ [Event:%d] No valid MC truth info present. "
      // 		   "Is a Particle handler installed ?",evt->GetEventID());
      // 	}
      // 	try  {
      // 	  saveEvent(ctxt);
      // 	  for (int i = 0; i < nCol; ++i) {
      // 	    G4VHitsCollection* hc = hce->GetHC(i);
      // 	    saveCollection(ctxt, hc);
      // 	  }
      // 	}
      // 	catch(const exception& e)   {
      // 	  std::cout << "Exception while saving event\n";
      // 	  std::cout << e.what();
      // 	  throw;
      // 	}
      // 	catch(...)   {
      // 	  std::cout << "Catch ...";
      // 	  throw;
      // 	}
      // 	commit(ctxt);
      // }
      // catch(const exception& e)   {
      // 	std::cout << "Catch exception\n";
      // 	std::cout << e.what();
      // 	throw;
      //   }
      //   catch(...)   {
      // 	std::cout << "Unknown exception\n";
      // 	throw;
      //   }
      //   m_truth = 0;
      //   return;
    } else {
      std::cout << "No HitCollection.";
    }
  }

  void RootEventAction::saveCollection(const G4Event* event) {
    // Geant4HitCollection* coll = dynamic_cast<Geant4HitCollection*>(collection);
    // string hc_nam = collection->GetName();
    // for(const auto& n : m_disabledCollections)  {
    //   if ( n == hc_nam )   {
    // 	return;
    //   }
    // }
    // if (coll) {
    //   vector<void*> hits;
    //   coll->getHitsUnchecked(hits);
    //   size_t nhits = coll->GetSize();
    //   if ( m_handleMCTruth && m_truth && nhits > 0 )   {
    // 	hits.reserve(nhits);
    // 	try  {
    // 	  for(size_t i=0; i<nhits; ++i)   {
    // 	    Geant4HitData* h = coll->hit(i);
    // 	    Geant4Tracker::Hit* trk_hit = dynamic_cast<Geant4Tracker::Hit*>(h);
    // 	    if ( 0 != trk_hit )   {
    // 	      Geant4HitData::Contribution& t = trk_hit->truth;
    // 	      int trackID = t.trackID;
    // 	      t.trackID = m_truth->particleID(trackID);
    // 	    }
    // 	    Geant4Calorimeter::Hit* cal_hit = dynamic_cast<Geant4Calorimeter::Hit*>(h);
    // 	    if ( 0 != cal_hit )   {
    // 	      Geant4HitData::Contributions& c = cal_hit->truth;
    // 	      for(Geant4HitData::Contributions::iterator j=c.begin(); j!=c.end(); ++j)  {
    // 		Geant4HitData::Contribution& t = *j;
    // 		int trackID = t.trackID;
    // 		t.trackID = m_truth->particleID(trackID);
    // 	      }
    // 	    }
    // 	  }
    // 	}
    // 	catch(...)   {
    // 	  printout(ERROR,name(),"+++ Exception while saving collection %s.",hc_nam.c_str());
    // 	}
    //   }
    //   fill(hc_nam, coll->vector_type(), &hits);
    // }    
  }

  void RootEventAction::commit(const G4Event* event) {
    // std::cout << "commit called\n";
    // if (m_file) {
    //   TObjArray* a = m_tree->GetListOfBranches();
    //   Long64_t evt = m_tree->GetEntries() + 1;
    //   Int_t nb = a->GetEntriesFast();
    //   /// Fill NULL pointers to all branches, which have less entries than the Event branch
    //   for (Int_t i = 0; i < nb; ++i) {
    // 	TBranch* br_ptr = (TBranch*) a->UncheckedAt(i);
    // 	Long64_t br_evt = br_ptr->GetEntries();
    // 	if (br_evt < evt) {
    // 	  Long64_t num = evt - br_evt;
    // 	  br_ptr->SetAddress(0);
    // 	  while (num > 0) {
    // 	    br_ptr->Fill();
    // 	    --num;
    // 	  }
    // 	}
    //   }
    //   m_tree->SetEntries(evt);
    // }
  }

  RootEventAction* RootEventAction::s_instance = nullptr;
}
