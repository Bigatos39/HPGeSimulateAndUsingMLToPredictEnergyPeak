#ifndef MYPRIMARYGENERATOR_HH
#define MYPRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource;

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  MyPrimaryGeneratorAction();
  virtual ~MyPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event *);

private:
  G4GeneralParticleSource *particleSource;
};

#endif // !MYPRIMARYGENERATOR_HH
