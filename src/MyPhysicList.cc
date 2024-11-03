#include "MyPhysicList.hh"
#include "G4IonTable.hh"

MyPhysicsList::MyPhysicsList() {
<<<<<<< HEAD
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

MyPhysicsList::~MyPhysicsList() {}
=======
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
>>>>>>> 89408436d91cb0e8370cefed9a0e2a0933a353ec
