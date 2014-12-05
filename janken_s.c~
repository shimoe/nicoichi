#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include <string.h>

#define SERIAL_PORT "/dev/ttyUSB0"  /* シリアルインターフェースに対応するデバイスファイル */


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


  int main(int argc, char *argv[])
{
  int buf[255];                    /* バッファ */
  int fd;
  char x[3];
  /* ファイルディスクリプタ */
  struct termios oldtio, newtio;    /* シリアル通信設定 */
    
  fd = open(SERIAL_PORT, O_RDWR);   /* デバイスをオープンする */
    
  ioctl(fd, TCGETS, &oldtio);       /* 現在のシリアルポートの設定を待避させる */
  newtio = oldtio;                  /* ポート設定をコピー */
  // newtio.c_cflag = ;             /* ポートの設定をおこなう 詳細はtermios(3)参照 */
  ioctl(fd, TCSETS, &newtio);       /* ポートの設定を有効にする */
  int s;
  char player;
  do{
  fgets(x,sizeof(x),stdin);
  if (x[strlen(x)-1] != '\n')
    while (getchar() != '\n');
  s = atoi(x);
  if(s == 1){
    printf("\nグー\nVS\n");
  }
  if(s == 2){
    printf("\nチョキ\nVS\n");
  }
  if(s == 3){
    printf("\nパー\nVS\n");
  }
  }while(s < 1 || s > 3);
  player = 'a';
  write(fd, &player, sizeof(&player));      /* デバイスへ255バイト書き込み */

  int enemy,result;
  enemy =  read(fd, &s, sizeof(&s)); 
 
  result = janken(s,enemy);
  switch(enemy){
  case 0 : printf("グー\n");
    break;
  case 1 : printf("チョキ\n");
    break;                       
  case 2 : printf("パー\n"); 
    break;
  }
  switch(result){
  case 1 : printf("\nDRAW\n");
    break;
  case 2 : printf("\nWIN!!\n");
    break;
  case 3 :printf("\nLOSE...\n");  
    break;  
  }
  ioctl(fd, TCSETS, &oldtio);       /* ポートの設定を元に戻す */
  close(fd);                        /* デバイスのクローズ */

  return 0;
 }
