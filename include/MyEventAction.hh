#ifndef EVENT_HH
#define EVENT_HH

#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4UserEventAction.hh"

#include "MyRunAction.hh"

class MyEventAction : public G4UserEventAction {
public:
  MyEventAction(MyRunAction *);
  ~MyEventAction();

  virtual void BeginOfEventAction(const G4Event *);
  virtual void EndOfEventAction(const G4Event *);

  void AddEdep(G4double edep);

private:
  G4double fEdep;
};

#endif
