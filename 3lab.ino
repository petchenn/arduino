#include <Wire.h>
#include <Arduino.h>
#include "Keypad.h"
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

//переполнение, сохранение во внутреннюю, вывод операции

int rowPins[4] = {2, 3, 4, 5}; // строки
int colPins[4] = {6, 7, 8, 9}; // столбцы

long Num1, Num2, Number, res, save = 0;
char operation;
bool result, first = true;
int n = 0;

Keypad keypad(rowPins, colPins);
LiquidCrystal_I2C lcd(0x27, 11, 12);
//EEPROM.write(0,0);

void setup();
long calculate(long first, long second, char op);
void loop();
void inputKey(char key);

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print(Number);
    //EEPROM.put(0, 0);
    //lcd.print("Hello, world!");
    EEPROM.get(0, save);
    Serial.begin(9600);
}

long calculate(long first, long second, char op){
  long res;
  switch(op){
    case '|':
    res = first | second;

    break;
    case '&':
    res = first & second;

    break;
    case '^':
    res = first ^ second;
    break;
    case '>':
    res = (~first) | second;
    break;
    default:
    Serial.println("wrong input");
    break;
  }
  return res;
}

void inputKey(char);

void loop() {
    //Serial.println(1);
    char key = keypad.getKey();
    if (key != '\0') {
        inputKey(key);
        if(first) lcd.home();
        if (result) {
          lcd.clear();
          lcd.print(res, OCT);
          }
        else {
          lcd.print(Number, OCT);
          if (!first) lcd.setCursor(0,1);
    }
}}

void inputKey(char key){
    //lcd.clear(); //Then clean it
    if (key == '*') //If cancel Button is pressed
    { Serial.println("Button Cancel");
        Number = Num1 = Num2 = n = 0;
        lcd.clear();
        lcd.home();
        result = false;
        first = true; }

    if (key == '1' && n<9) //If Button 1 is pressed
    {
        Serial.println("Button 1");
        if (Number == 0){
            Number = 1;
            n++;}
        else
            {Number = (Number * 8) + 1; //Pressed twice
            n++;}
    }

    if (key == '4' && n<9) //If Button 4 is pressed
    {
        Serial.println("Button 4");
        if (Number == 0){
            Number = 4;
            n++;}
        else
            {Number = (Number * 8) + 4; //Pressed twice
            n++;}
}

    if (key == '7' && n<9) //If Button 7 is pressed
    {
        Serial.println("Button 7");
        if (Number == 0){
            Number = 7;
            n++;}
        else
            {Number = (Number * 8) + 7; //Pressed twice
            n++;}
    }


    if (key == '0' && n<9) {
        Serial.println("Button 0"); //Button 0 is Pressed
        if (Number == 0){
            Number = 0;
            n++;}
        else
            {Number = (Number * 8) + 0; //Pressed twice
            n++;}
    }

    if (key == '2' && n<9) //Button 2 is Pressed
    {
        Serial.println("Button 2");
        if (Number == 0){
            Number = 2;
            n++;}
        else
            {Number = (Number * 8) + 2; //Pressed twice
            n++;}
    }

    if (key == '5' && n<9) {
        Serial.println("Button 5");
        if (Number == 0){
            Number = 5;
            n++;}
        else
            {Number = (Number * 8) + 5; //Pressed twice
            n++;}
    }

    if (key == '6' && n<9) {
        Serial.println("Button 6");
        if (Number == 0){
            Number = 6;
            n++;}
        else
            {Number = (Number * 8) + 6; //Pressed twice
            n++;}
    }


    if (key == '=') {
        Serial.println("Button Equal");
        Num2 = Number;
        lcd.clear();
        res = calculate(Num1, Num2, operation);
        lcd.print(res, OCT);
        Serial.println(res);
        //save = res;
        result = true;
    }

    if (key == '3' && n<9) {
        Serial.println("Button 3");
        if (Number == 0){
            Number = 3;
            n++;}
        else
            {Number = (Number * 8) + 3; //Pressed twice
            n++;}
    }

    if (key == '|' || key == '^' || key == '&' || key == '>') //Detecting Buttons on Column 4
    {
        Num1 = Number;
        operation = key;
        first = false;
        Number = n = 0;
        lcd.setCursor(0,15);
        lcd.print(operation);
        lcd.setCursor(0,1);

        delay(100);
    }
    if(key == '8'){
      if(result){
        save = res;
        Serial.println(res);
        EEPROM.put(0, save);
      }
    }
    if(key == '9'){
      //long s;
      //EEPROM.get(0, s);
      Number = save;
      Serial.println(Number);
    }
    }

