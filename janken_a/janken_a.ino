#include <stdlib.h>

long enemy;
char i[255];
int result,player;
int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void loop(){
  player = Serial.read();
  if((char)player == 'a'){
  enemy = random(1,4);
  Serial.println(enemy);
  }
}

