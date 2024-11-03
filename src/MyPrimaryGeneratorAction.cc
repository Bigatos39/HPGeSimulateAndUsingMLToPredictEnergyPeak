#include "MyPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() {
  particleSource = new G4GeneralParticleSource();
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() { delete particleSource; }

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
  // Get Primary Vertex
  particleSource->GeneratePrimaryVertex(anEvent);
}
