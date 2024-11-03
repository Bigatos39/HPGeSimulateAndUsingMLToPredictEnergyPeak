#include "MyActionInitialization.hh"

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::BuildForMaster() const {
  MyRunAction *runAction = new MyRunAction();
  SetUserAction(runAction);
}

void MyActionInitialization::Build() const {
  MyPrimaryGeneratorAction *generator = new MyPrimaryGeneratorAction();
  SetUserAction(generator);

  MyRunAction *runAction = new MyRunAction();
  SetUserAction(runAction);

  MyEventAction *eventAction = new MyEventAction(runAction);
  SetUserAction(eventAction);

  MySteppingAction *steppingAction = new MySteppingAction(eventAction);
  SetUserAction(steppingAction);
}
