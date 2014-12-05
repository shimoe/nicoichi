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

int janken(int a,int b){
  if(a == 1){
    switch(b){
    case 0 : return 1;//引き分け
      break;
    case 1 : return 2;//勝ち
      break;
    case 2 : return 3;//負け
      break;
    } 
  }
  else if(a == 2){
    switch(b){
    case 0 : return 3;
      break;
    case 1 : return 1;
      break;
    case 2 : return 2;    
      break;
    }
  }
  else if(a == 3){
    switch(b){
    case 0 : return 2;
      break;
    case 1 : return 3;
      break;
    case 2 : return 1;    
      break; 
    }
  }
}

void loop(){
  player = Serial.read();
  if((char)player == 'a'){
  enemy = random(1,4);
  Serial.println(enemy);
  }
}

