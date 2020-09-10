#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <cctype>
#include "observer.h"
#include "info.h"
#include "subject.h"

class TextDisplay : public Observer {
  std::vector<std::vector<char>> theDisplay;

 public:
  TextDisplay();

  bool valid();
  void notify(Subject &);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
