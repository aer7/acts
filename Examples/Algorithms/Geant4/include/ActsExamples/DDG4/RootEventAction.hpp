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

namespace ActsExamples::DDG4 {

class RootEventAction final : public G4UserEventAction {
 public:
  // G4UserEventAction
  RootEventAction();

  // G4UserEventAction
  ~RootEventAction() final override;

  // G4UserEventAction
  // @param event is the G4Event to be processed
  // @note resets the event and step action
  void BeginOfEventAction(const G4Event* event) final override;
  
  // G4UserEventAction
  // @param event is the G4Event to be processed
  void EndOfEventAction(const G4Event* event) final override;
  
 private:
  // G4UserEventAction
  static RootEventAction* s_instance;  
  
  void saveCollection(const G4Event* event);
  void commit(const G4Event* event);
};

}
