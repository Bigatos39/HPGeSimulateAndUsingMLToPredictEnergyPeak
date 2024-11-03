#include "MyRunAction.hh"
#include "G4SystemOfUnits.hh"

MyRunAction::MyRunAction() {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->CreateH1("H1", "Edep in absorber, Energy[MeV]", 2000, 0.,
                            2.8 * MeV);

  // Create ntuple
  analysisManager->CreateNtuple("HPGe", "Edep");
  analysisManager->CreateNtupleDColumn("fEdep");
  analysisManager->FinishNtuple();
}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run *run) {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile(fFileName);
}

void MyRunAction::EndOfRunAction(const G4Run *) {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

void MyRunAction::SetFilename(G4String fileName) {
  fFileName = G4String(fileName);
}
