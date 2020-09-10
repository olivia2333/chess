#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "info.h"

class Observer;

class Subject {
  std::vector<Observer*> observers;
  InfoType info;
 protected:
  void setState(InfoType newI);
 public:
  void attach(Observer *o);  
  void notifyObservers();
  InfoType getState() const;
};
#endif
