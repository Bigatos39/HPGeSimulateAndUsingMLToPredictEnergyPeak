#include "MyRunAction.hh"
#include "G4SystemOfUnits.hh"

MyRunAction::MyRunAction() {
  auto analysisManager = G4AnalysisManager::Instance();
<<<<<<< HEAD
  analysisManager->CreateH1("Edep", "Edep in absorber, Energy[MeV]", 2000, 0.,
=======
  analysisManager->CreateH1("H1", "Edep in absorber, Energy[MeV]", 2000, 0.,
>>>>>>> 89408436d91cb0e8370cefed9a0e2a0933a353ec
                            2.8 * MeV);

  // Create ntuple
  analysisManager->CreateNtuple("HPGe", "Edep");
  analysisManager->CreateNtupleDColumn("fEdep");
  analysisManager->FinishNtuple();
}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run *run) {
  auto analysisManager = G4AnalysisManager::Instance();
<<<<<<< HEAD
  analysisManager->OpenFile(fFileName, true);
=======
  analysisManager->OpenFile("output.root");
>>>>>>> 89408436d91cb0e8370cefed9a0e2a0933a353ec
}

void MyRunAction::EndOfRunAction(const G4Run *) {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

void MyRunAction::SetFilename(G4String fileName) {
  fFileName = G4String(fileName);
}
