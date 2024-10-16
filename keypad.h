#include <Arduino.h>
#ifndef Keypad_h
#define Keypad_h

class Keypad{
  int _rPins[4];
  int _cPins[4];
  char _keymap[4][4] = {
    {'1', '2', '3', '|'},
    {'4', '5', '6', '&'},
    {'7', '8', '9', '^'},
    {'*', '0', '=', '>'}
  };

  public: 
  Keypad(int rPins[4], int cPins[4]){
    for(int i = 0; i<4;i++){
      _rPins[i] = rPins[i];
      pinMode(_rPins[i], 1);
      digitalWrite(_rPins[i], 1);
      _cPins[i] = cPins[i];
      pinMode(_cPins[i], INPUT_PULLUP);
      }
  };
  char getKey(){
  for (int row = 0; row < 4; row++) {
        digitalWrite(_rPins[row], LOW);
        for (int col = 0; col < 4; col++) {
            if (digitalRead(_cPins[col]) == LOW) { 
                while (digitalRead(_cPins[col]) == LOW);
                digitalWrite(_rPins[row], HIGH); 
                //Serial.println(_keymap[row][col]);
                return _keymap[row][col];
            }
        }

        digitalWrite(_rPins[row], HIGH);
    }

    return '\0'; // Нет нажатой кнопки
  };
};

#endif