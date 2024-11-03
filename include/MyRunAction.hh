#ifndef MYRUNACTION_HH
#define MYRUNACTION_HH

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4UserRunAction.hh"

class G4Run;

class MyRunAction : public G4UserRunAction {
public:
  MyRunAction();
  ~MyRunAction();

  void AddEdep(G4double edep);
  void SetFilename(G4String fileName);

  void BeginOfRunAction(const G4Run *) override;
  void EndOfRunAction(const G4Run *) override;

private:
  G4String fFileName;
};

#endif // !MYRUNACTION_HH
