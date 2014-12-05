#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//グローバル関数

int player,enemy,m,d;
char x[3];


//乱数関数

int randam(int r){
  int s,t,u,v;
  srand(time(NULL));
  s = 1 + rand()%3;
  u = r;
  for(t = 1;t < player ;t++){    
    u = player * u;
  }
  v = (u^s) % 15;
  return v;
}

//メイン関数

int main(void){
  printf("明日の天気予報\n");
  wait(3000);
  printf("今日は○月△日です。\n○と△に数字を入力して下さい\n");
  fgets(x,sizeof(x),stdin);
  if (x[strlen(x)-1] != '\n')
    while (getchar() != '\n');
  m = atoi(x);
  printf("○＝%d\n",m); 
  fgets(x,sizeof(x),stdin);
  if (x[strlen(x)-1] != '\n')
    while (getchar() != '\n');
  d = atoi(x);
  printf("△＝%d\n",d);
  player = m + d;
  enemy = randam(player);
  printf("loading…\n");
  wait(1000);
  printf("今日は%d月%d日\n",m,d);
  printf("明日は\n");
  switch(enemy){
  case 0 : printf("？？？\n"); break;
  case 1 : printf("晴れ\n"); break;
  case 2 : printf("雨\n"); break;
  case 3 : printf("曇り\n"); break;
  case 4 : printf("晴れのち雨\n"); break;
  case 5 : printf("曇り時々雨\n"); break;
  case 6 : printf("雨時々晴れ\n"); break;
  case 7 : printf("あられ\n"); break;
  case 8 : printf("雨時々飴\n"); break;
  case 9 : printf("雹のち豹\n"); break;
  case 10 : printf("晴れのち曇り\n"); break;
  case 11 : printf("濃霧\n"); break;
  case 12 : printf("親方ァ！空から女の子が！\n"); break;
  case 13 : printf("快晴\n"); break;
  case 14 : printf("みぞれ混じりの雨\n"); break;
  case 15 : printf("晴れ時々雷雨\n"); break;
  }
  printf("の模様です。\n");
}
