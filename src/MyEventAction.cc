#include "MyEventAction.hh"
#include "G4SystemOfUnits.hh"

MyEventAction::MyEventAction(MyRunAction *) { fEdep = 0.; }

MyEventAction::~MyEventAction() {}

void MyEventAction::BeginOfEventAction(const G4Event *) { fEdep = 0.; }

void MyEventAction::AddEdep(G4double edep) { fEdep += edep; }

void MyEventAction::EndOfEventAction(const G4Event *) {
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  if (fEdep > 0) {
    fEdep = fEdep / MeV;

    // fill histograms
    man->FillH1(0, fEdep);

    // fill ntuple
    man->FillNtupleDColumn(0, fEdep);
    man->AddNtupleRow();
  }
}
