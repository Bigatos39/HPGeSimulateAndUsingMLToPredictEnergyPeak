#ifndef MYPHYSICLIST_HH
#define MYPHYSICLIST_HH

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
<<<<<<< HEAD
#include "G4PhysListFactory.hh"
=======
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4IonPhysics.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicsListHelper.hh"
>>>>>>> 89408436d91cb0e8370cefed9a0e2a0933a353ec
#include "G4RadioactiveDecayPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4VModularPhysicsList.hh"
#include "QGSP_BERT.hh"

class MyPhysicsList : public G4VModularPhysicsList {
public:
  MyPhysicsList();
  virtual ~MyPhysicsList();

<<<<<<< HEAD
  /*protected:
    // Construct particle and physics
    void ConstructParticle() override;
    void ConstructProcess() override; */
=======
protected:
  // Construct particle and physics
  void ConstructParticle() override;
  void ConstructProcess() override;
>>>>>>> 89408436d91cb0e8370cefed9a0e2a0933a353ec
};

#endif //! MYPHYSICLIST_HH
