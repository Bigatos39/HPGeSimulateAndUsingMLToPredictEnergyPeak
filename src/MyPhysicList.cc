#include "MyPhysicList.hh"
#include "G4IonTable.hh"

MyPhysicsList::MyPhysicsList() {
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

MyPhysicsList::~MyPhysicsList() {}
