#ifndef MYPHYSICLIST_HH
#define MYPHYSICLIST_HH

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4PhysListFactory.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4VModularPhysicsList.hh"
#include "QGSP_BERT.hh"

class MyPhysicsList : public G4VModularPhysicsList {
public:
  MyPhysicsList();
  virtual ~MyPhysicsList();

  /*protected:
    // Construct particle and physics
    void ConstructParticle() override;
    void ConstructProcess() override; */
};

#endif //! MYPHYSICLIST_HH
