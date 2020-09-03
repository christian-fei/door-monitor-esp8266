#include <Arduino.h>
#include "Logic.h"

Logic::Logic(int inputPin, int outputPin)
{
  pinMode(outputPin, OUTPUT);
  pinMode(inputPin, INPUT);

  _inputPin = inputPin;
  _outputPin = outputPin;
  _doorIsOpen = false;
}

bool Logic::doorIsOpen()
{
  return _doorIsOpen;
}

void Logic::run(bool soundOn)
{
  bool doorIsOpen = (digitalRead(_inputPin) == HIGH);
  if (doorIsOpen == _doorIsOpen) { return; }
  _doorIsOpen = doorIsOpen;

  if (!soundOn) { return; }

  if (doorIsOpen) {
    digitalWrite(_outputPin, HIGH);
    delay(500);
    digitalWrite(_outputPin, LOW);
    delay(500);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(500);
    digitalWrite(_outputPin, LOW);
    delay(500);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(250);
    digitalWrite(_outputPin, LOW);
    delay(250);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }

    digitalWrite(_outputPin, HIGH);
    delay(250);
    digitalWrite(_outputPin, LOW);
    delay(250);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(250);
    digitalWrite(_outputPin, LOW);
    delay(250);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(250);
    digitalWrite(_outputPin, LOW);
    delay(250);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }

    digitalWrite(_outputPin, HIGH);
    delay(125);
    digitalWrite(_outputPin, LOW);
    delay(125);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }

    digitalWrite(_outputPin, HIGH);
    delay(125);
    digitalWrite(_outputPin, LOW);
    delay(125);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(125);
    digitalWrite(_outputPin, LOW);
    delay(125);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(125);
    digitalWrite(_outputPin, LOW);
    delay(125);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(125);
    digitalWrite(_outputPin, LOW);
    delay(125);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(125);
    digitalWrite(_outputPin, LOW);
    delay(125);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(125);
    digitalWrite(_outputPin, LOW);
    delay(125);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(125);
    digitalWrite(_outputPin, LOW);
    delay(125);
    doorIsOpen = (digitalRead(_inputPin) == HIGH);
    if (!doorIsOpen) { return; }
    
    digitalWrite(_outputPin, HIGH);
    delay(2000);
    digitalWrite(_outputPin, LOW);
  }
  else
  {
    digitalWrite(_outputPin, LOW);
  }
}
