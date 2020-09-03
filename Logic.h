#ifndef Logic_h
#define Logic_h

#include "Arduino.h"

class Logic
{
public:
  Logic(int inputPin, int outputPin);
  void run(bool soundOn);
  bool doorIsOpen();

private:
  int _inputPin;
  int _outputPin;
  bool _doorIsOpen;
};

#endif