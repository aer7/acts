// This file is part of the Acts project.
//
// Copyright (C) 2020 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <map>
#include <memory>
#include <string>
#include <G4UserEventAction.hh>
#include <globals.hh>

// This implements Geant's G4UserRunAction for the purpose of calling
// DD4HEP's Geant4Output2ROOT function. This function writes a Root
// file of particle data which can be visualized by DD4HEP's DDEve.
// The structure this Root file is unique to DD4HEP and DDEve, and
// instead of reimplementing it in ACTS, or trying to hack one of the
// other Root files to conform to the structure, just call
// Geant4Output2ROOT. DDEve specifically can only visualize Root files
// made by Geant4Output2ROOT. This is very similar to the code in
// DDG4.py, which is called by the 'ddeve' script. "RootEventAction"
// is a relatively generic name, feel free to change it.

namespace ActsExamples {

class RootEventAction final : public G4UserEventAction {
 public:
  /// Static access method
  static EventAction* instance();

  /// Construct the action and ensure singleton usage.
  EventAction(std::vector<std::string> processFilter);
  ~EventAction() final override;

  /// Interface method for begin of the event
  /// @param event is the G4Event to be processed
  /// @note resets the event and step action
  void BeginOfEventAction(const G4Event* event) final override;

  /// Interface method for end of event
  /// @param event is the G4Event to be processed
  void EndOfEventAction(const G4Event* event) final override;

  /// Clear the recorded data.
  void clear();
};
}
