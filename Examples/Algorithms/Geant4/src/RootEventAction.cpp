// This file is part of the Acts project.
//
// Copyright (C) 2020 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "ActsExamples/DDG4/RootEventAction.hpp"
#include <stdexcept>
#include <G4Run.hh>
#include <DDG4/Geant4Output2ROOT.h>
#include <G4Event.hh>
#include <G4RunManager.hh>
#include <iostream>

namespace ActsExamples::DDG4 {

  // G4UserEventAction
  RootEventAction::RootEventAction() : G4UserEventAction()  {
    if (s_instance != nullptr) {
      throw std::logic_error("Attempted to duplicate a singleton");
    } else {
      s_instance = this;
    }
  }

  // G4UserEventAction
  RootEventAction::~RootEventAction() {
    s_instance = nullptr;
  }

  // G4UserEventAction
  void RootEventAction::BeginOfEventAction(const G4Event* event) {
    std::cout << "Hello my good sir\n";
  }

  // G4UserEventAction
  void RootEventAction::EndOfEventAction(const G4Event* event) {
    
  }

  RootEventAction* RootEventAction::s_instance = nullptr;
}
