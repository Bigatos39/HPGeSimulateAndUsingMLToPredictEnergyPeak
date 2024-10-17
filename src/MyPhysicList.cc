#include "MyPhysicList.hh"
#include "G4IonTable.hh"

MyPhysicsList::MyPhysicsList() {
  SetVerboseLevel(1);
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  RegisterPhysics(new G4StepLimiterPhysics());
}

MyPhysicsList::~MyPhysicsList() {}

void MyPhysicsList::ConstructParticle() {
  G4VModularPhysicsList::ConstructParticle();
}

void MyPhysicsList::ConstructProcess() {
  G4VModularPhysicsList::ConstructProcess();
}
