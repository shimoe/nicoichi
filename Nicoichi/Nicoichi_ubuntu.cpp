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


/* -------------------------------------
   modelparams
------------------------------------- */
#define R_WHEEL 0.10  //[m]
#define L_WHEEL 0.15  //[m]
#define TREAD 0.3  //[m]
#define MAX_MTR_R2 56
#define MAX_MTR_L2 56

/* -------------------------------------
   グローバル変数
------------------------------------- */
float omega = 0;  //角速度の目標値
float Vel = 0.035;  //並進速度の目標値


/* -------------------------------------
   グローバル変数R
------------------------------------- */
// 計算結果格納用の変数(計算位置)
volatile long DegIniR = 0;

// エンコーダー用変数
volatile int NowR_ENC_PHASE_B; // 条件分岐の都度読み込みを実行しないように
volatile int LastR_ENC_PHASE_B; // 上り降りで代入

// 速度関係
volatile float VelR = 0; // 現在の右輪の速度[m/s]
volatile unsigned long LastTimeR = 0; // 前回角速度を計測した時の絶対時刻
volatile unsigned long ElapsedTimeR = 0; // 経過時間
float ComVelR = 0; //右輪速度の目標値[m/s]
unsigned int inputR = 0; //速度の操作量[m/s]
float max_VelR = 0;  //速度の最大値[m/s]

/* -------------------------------------
   グローバル変数L
------------------------------------- */
// 計算結果格納用の変数(計算位置)
volatile long DegIniL = 0;

// エンコーダー用変数
volatile int NowL_ENC_PHASE_B; // 条件分岐の都度読み込みを実行しないように
volatile int LastL_ENC_PHASE_B; // 上り降りで代入

// 速度関係
volatile float VelL = 0; // left速度
volatile unsigned long LastTimeL = 0; // 前回角速度を計測した時の絶対時刻
volatile unsigned long ElapsedTimeL = 0; // 経過時間
float ComVelL = 0;  //左輪速度の目標値[m/s]
unsigned int inputL = 0;  //速度の操作量[m/s]
float max_VelL = 0;  //速度の最大値[m/s]

/* -------------------------------------
   関数プロトタイプ宣言
------------------------------------- */
void EncCounterR ( void );
void EncCounterL ( void );


/* -------------------------------------
   メイン関数
------------------------------------- */
int main() {
  
  /* ファイルディスクリプタ */
  struct termios oldtio, newtio;    /* シリアル通信設定 */
    
  fd = open(SERIAL_PORT, O_RDWR);   /* デバイスをオープンする */
    
  ioctl(fd, TCGETS, &oldtio);       /* 現在のシリアルポートの設定を待避させる */
  newtio = oldtio;                  /* ポート設定をコピー */
  // newtio.c_cflag = ;             /* ポートの設定をおこなう 詳細はtermios(3)参照 */
  ioctl(fd, TCSETS, &newtio);       /* ポートの設定を有効にする */

  write(fd, &player, sizeof(&player));      /* デバイスへ255バイト書き込み */

  ioctl(fd, TCSETS, &oldtio);       /* ポートの設定を元に戻す */
  close(fd);                        /* デバイスのクローズ */

  ComVelR = TREAD * omega + Vel;
  ComVelL = Vel - TREAD * omega;
  max_VelR = ((5200.0/127.78/60.0) * PI * R_WHEEL)*MAX_MTR_R2/255.0;   //((毎分回転数/ギア比/秒)*pi*右輪直径)/最大速度時のパルス
  max_VelL = ((5200.0/127.78/60.0) * PI * L_WHEEL)*MAX_MTR_L2/255.0;
 

  inputR += 0.6 * (ComVelR + VelR)/max_VelR * MAX_MTR_R2;
  if(inputR > MAX_MTR_R2){
   inputR = MAX_MTR_R2;
   }
   else if(inputR < 0){
    inputR = 0; 
   }
  inputL += 0.6 * (ComVelL - VelL)/max_VelL * MAX_MTR_L2;
    if(inputL > MAX_MTR_L2){
   inputL = MAX_MTR_L2;
   }
   else if(inputL < 0){
    inputL = 0; 
   }
	VelR = (DegIniR *0.18 *4.0 /127.78 *1000.0 /ElapsedTimeR) / 360.0 * PI * R_WHEEL;
	VelL = (DegIniL *0.18 *4.0 /127.78 *1000.0 /ElapsedTimeL) / 360.0 * PI * L_WHEEL;

}
