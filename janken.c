#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
int enemy;
int s,t,u,v,w,y,z;
char x[3],c[3],f[10000];
int d;
int hyouji = 100;
int e = 0;
int max = 50;
int no[10000];
/*
int rireki(int n,int l){
  if(n == 1){//引き分け
    switch(l){
    case 1 : return 1; break;
    case 2 : return 4; break;
    case 3 : return 7; break;
    }
  }
  if(n == 2){//勝ち
    switch(l){
    case 1 : return 2; break;
    case 2 : return 5; break;
    case 3 : return 8; break;
    }
  }
  if(n == 3){//負け
    switch(l){
    case 1 : return 3; break;
    case 2 : return 6; break;
    case 3 : return 9; break;
    }
  }
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
    case 2 : return 2;          break;
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
*/
int main(void){
  u = 0;
  do{
    printf("ジャンケンスタート！\n");
    do{
      printf("何戦行いますか？\n");
      fgets(f,sizeof(f),stdin);
      if (f[strlen(f)-1] != '\n')
	while (getchar() != '\n');
      s = atoi(f);
      if(s < 1 || 99999999999999999999 < s){
	printf("やり直して下さい\n");
      }
    }while(s < 1 || 99999999999999999999 < s);
    max = s;
    printf("%d戦行います\n",s);
    do{
      srand(time(NULL));
      enemy = rand() % 3;
      printf("グーは１、チョキは２、パーは３を入力してね！\n");
      printf("数字を入力してください\nあなたは"); 
      fgets(x,sizeof(x),stdin);
      if (x[strlen(x)-1] != '\n')
	while (getchar() != '\n');
      s = atoi(x);
      //結果表示
      if(s == 1){
	printf("\nグー\nVS\n");
      }
      if(s == 2){
	printf("\nチョキ\nVS\n");
      }
      if(s == 3){
	printf("\nパー\nVS\n");
      }
      if(s < 1 || s > 3){
	printf("\nやり直して下さい\n");
	w = 0;
	break;
      }
      z = janken(s,enemy);
      switch(enemy){
      case 0 : printf("グー\n");
	break;
      case 1 : printf("チョキ\n");
	break;                       
      case 2 : printf("パー\n"); 
	break;
      }
      switch(z){
      case 1 : printf("\nDRAW\n");
	break;
      case 2 : printf("\nWIN!!\n");
	break;
      case 3 :printf("\nLOSE...\n");  
	break;  
      }
      d = rireki(z,s);
      no[e] = d;
      printf("%d回目終了\n",e + 1);
      e++;
      if(e == max){
	printf("履歴が規定数に達しました。\nプログラムを終了します。\n");
	printf("履歴---------------------------------------------------------------------\n");
	for(u = 0;u < e;u++){
	  printf("結果%d(Player vs CPU)：",u + 1);
	  switch(no[u]){
	  case 1 : printf("DROW\nグー　vs　グー\n"); break;
	  case 2 : printf("WIN\nグー　vs　チョキ\n"); break;
	  case 3 : printf("LOSE\nグー　vs　パー\n"); break;
	  case 4 : printf("DROW\nチョキ　vs　チョキ\n"); break;
	  case 5 : printf("WIN\nチョキ　vs　パー\n"); break;
	  case 6 : printf("LOSE\nチョキ　vs　グー\n"); break;
	  case 7 : printf("DROW\nパー　vs　パー\n"); break;
	  case 8 : printf("WIN\nパー　vs　グー\n"); break;
	  case 9 : printf("LOSE\nパー　vs　チョキ\n"); break;
	  }
	}
	printf("------------------------------------------------------------------------------\n");
	w = 1;
	t = 1;
	break;
      }
      printf("\n続けますか？\nYES！・・・0　or NO・・・9\n履歴を表示して終了・・・１\n数字を入力してください\n");
      do{
	fgets(c,sizeof(c),stdin);
	if (c[strlen(c)-1] != '\n')
	  while (getchar() != '\n');
	t = atoi(c);
	if(t != 1 && t != 9 && t != 0){
	  printf("やり直して下さい");
	}
      }while(t != 1 && t != 9 && t != 0);
      if(t == 1){
	if(e < hyouji){
	  printf("履歴-------------------------------------------------------------------\n");
	  for(u = 0;u < e;u++){
	    printf("\n結果%d(Player vs CPU)：",u + 1);
	    switch(no[u]){
	    case 1 : printf("DROW\nグー　vs　グー\n"); break;
	    case 2 : printf("WIN\nグー　vs　チョキ\n"); break;
	    case 3 : printf("LOSE\nグー　vs　パー\n"); break;
	    case 4 : printf("DROW\nチョキ　vs　チョキ\n"); break;
	    case 5 : printf("WIN\nチョキ　vs　パー\n"); break;
	    case 6 : printf("LOSE\nチョキ　vs　グー\n"); break;
	    case 7 : printf("DROW\nパー　vs　パー\n"); break;
	    case 8 : printf("WIN\nパー　vs　グー\n"); break;
	    case 9 : printf("LOSE\nパー　vs　チョキ\n"); break;
	    }
	  }
	  printf("----------------------------------------------------------------------------\n");
	}	
	if(e >= hyouji){
	  printf("履歴-------------------------------------------------------------------\n");
	  for(u = e - hyouji;u < e;u++){
	    printf("\n結果%d(Player vs CPU)：",u + 1);
	    switch(no[u]){
	    case 1 : printf("DROW\nグー　vs　グー\n"); break;
	    case 2 : printf("WIN\nグー　vs　チョキ\n"); break;
	    case 3 : printf("LOSE\nグー　vs　パー\n"); break;
	    case 4 : printf("DROW\nチョキ　vs　チョキ\n"); break;
	    case 5 : printf("WIN\nチョキ　vs　パー\n"); break;
	    case 6 : printf("LOSE\nチョキ　vs　グー\n"); break;
	    case 7 : printf("DROW\nパー　vs　パー\n"); break;
	    case 8 : printf("WIN\nパー　vs　グー\n"); break;
	    case 9 : printf("LOSE\nパー　vs　チョキ\n"); break;
	    }
	  }
	  printf("----------------------------------------------------------------------------\n");
	}
      }
      if(t != 0){
	w = 1;
      }
    }while(t == 0);
  }while(w == 0);
  return 0;
}



