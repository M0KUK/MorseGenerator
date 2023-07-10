#include <Arduino.h>

#define ASCII_START 65  //Ascii code of first letter 'A' needed to offset
#define NUMBER_OF_LETTERS 26
#define WAIT_TIME 2000 //Time before starting again in miliseconds, e.g. 1000 is 1 second

const int buzzerPin = 8; //defines pin that buzzer is connected to
const int morseTone = 600;  //defines the tone for the morse sound
const int ditLength = 100;  //dot length in miliseconds
const int dahLength = 3 * ditLength;  //dash length in miliseconds (3x dot length)
const String morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
  "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." 
};


void ditPlay(){
  tone(buzzerPin, morseTone, ditLength);
  delay(ditLength);
}

void dahPlay(){
  tone(buzzerPin, morseTone, dahLength);
  delay(dahLength);
}

void play(char whatToPlay){
  if (whatToPlay == '-'){
    dahPlay();
  }
  else if (whatToPlay == '.'){
    ditPlay();
  }
}

//TODO add upperCase handling

void playCharacter(char letterToPlay){
  String toPlay = morseCode[letterToPlay- ASCII_START]; //selecting right character
  for (byte i = 0; i < toPlay.length(); i++) //looping through all dits and dahs
  {
    play(toPlay[i]);
    delay(ditLength);
  }
}


void setup() {
  // TODO Setting up Serial
  Serial.begin(9600);

  randomSeed(analogRead(0)); //Pin 0 should be left floating for more random results
  // Play CQ
  // playCharacter('C');
  // delay(dahLength); //end of character
  // playCharacter('Q');


}

void loop() {
  //Play random character
  char randomLetter = random(NUMBER_OF_LETTERS) + ASCII_START;
  playCharacter(randomLetter);
  delay(dahLength);

  delay(WAIT_TIME);
}