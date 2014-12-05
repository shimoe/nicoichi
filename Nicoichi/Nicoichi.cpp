/* -------------------------------------
   pin番号指定
------------------------------------- */
#define EncRPhaseA 2
#define EncRPhaseB 3
#define MtrR1 8
#define MtrR2 9
#define EncLPhaseA 4
#define EncLPhaseB 5
#define MtrL1 10
#define MtrL2 11


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
float omega = 0;
float Vel = 0.035;


/* -------------------------------------
   グローバル変数R
------------------------------------- */
// 計算結果格納用の変数(計算位置)
volatile long DegIniR = 0;

// エンコーダー用変数
volatile int NowEncRPhaseB; // 条件分岐の都度読み込みを実行しないように
volatile int LastEncRPhaseB; // 上り降りで代入

// 速度関係
volatile float VelR = 0; // right速度
volatile unsigned long LastTimeR = 0; // 前回角速度を計測した時の絶対時刻
volatile unsigned long ElapsedTimeR = 0; // 経過時間
float ComVelR = 0; //define right speed
unsigned int inputR = 0;
float max_VelR = 0;

/* -------------------------------------
   グローバル変数L
------------------------------------- */
// 計算結果格納用の変数(計算位置)
volatile long DegIniL = 0;

// エンコーダー用変数
volatile int NowEncLPhaseB; // 条件分岐の都度読み込みを実行しないように
volatile int LastEncLPhaseB; // 上り降りで代入

// 速度関係
volatile float VelL = 0; // left速度
volatile unsigned long LastTimeL = 0; // 前回角速度を計測した時の絶対時刻
volatile unsigned long ElapsedTimeL = 0; // 経過時間
float ComVelL = 0; 
unsigned int inputL = 0;
float max_VelL = 0;

/* -------------------------------------
   関数プロトタイプ宣言
------------------------------------- */
void EncCounterR ( void );
void EncCounterL ( void );


/* -------------------------------------
   メイン関数
------------------------------------- */
void setup () {
  pinMode ( EncRPhaseA, INPUT );
  pinMode ( EncRPhaseB, INPUT );
  pinMode(MtrR1, OUTPUT);
  pinMode(MtrR2, OUTPUT);
  pinMode ( EncLPhaseA, INPUT );
  pinMode ( EncLPhaseB, INPUT );
  pinMode(MtrL1, OUTPUT);
  pinMode(MtrL2, OUTPUT);
  
  Serial.begin ( 115200 );

  LastEncRPhaseB = digitalRead ( EncRPhaseB ); // 初期化
  LastEncLPhaseB = digitalRead ( EncLPhaseB ); // 初期化
  
  attachInterrupt ( 2, EncRCounter, CHANGE ); // 割り込み処理登録
  attachInterrupt ( 4, EncLCounter, CHANGE ); // 割り込み処理登録
  
  ComVelR = TREAD * omega + Vel;
  ComVelL = Vel - TREAD * omega;
  max_VelR = ((5200.0/127.78/60.0) * PI * R_WHEEL)*MAX_MTR_R2/255.0;
  max_VelL = ((5200.0/127.78/60.0) * PI * L_WHEEL)*MAX_MTR_L2/255.0;
 
  
  analogWriteResolution(8);
  digitalWrite(MtrR1, LOW);
  analogWrite(MtrR2, 0);
  digitalWrite(MtrL1, HIGH);
  analogWrite(MtrL2, 255);

}



void loop () {
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
   analogWrite(MtrR2, inputR);
   analogWrite(MtrL2, 255 - inputL);
   
  Serial.print(inputR ,DEC);
  Serial.print("\t");
  Serial.println(inputL ,DEC);
}



/* -------------------------------------
   エンコーダー感知タスク
------------------------------------- */
void EncRCounter ( void ) {
  ElapsedTimeR = millis() -LastTimeR; // 経過時間の算出
  NowEncRPhaseB = digitalRead ( EncRPhaseB );
  if ( digitalRead(EncRPhaseA) == HIGH ) {
    // この下の代入は現在のBを読んでいるだけ
     // 条件分岐の都度に digitalRead を実行しないように、ここで最初に一回だけ読み込んで NewEncPhaseB として置いておく
    switch(LastEncRPhaseB){ // 前回チェンジ時のBで分岐
    case 0: switch(NowEncRPhaseB){
            case 0: DegIniR -1; break;
            case 1: DegIniR += 4;     break;
            }  break; 
    case 1: switch(NowEncRPhaseB){
            case 0: DegIniR -= 4;  break;
            case 1: DegIniR ++;  break;
            }  break;
    }
  }
  VelR = (DegIniR *0.18 *4.0 /127.78 *1000.0 /ElapsedTimeR) / 360.0 * PI * R_WHEEL;
 
  DegIniR = 0;
  
  LastTimeR = ElapsedTimeR;			   
  LastEncRPhaseB = digitalRead ( EncRPhaseB ); // 現在のBを改めて残す
//  Serial.print(NowEncRPhaseB ,DEC);
//  Serial.print("\t");
//  Serial.println(NowEncLPhaseB ,DEC);
}

void EncLCounter ( void ) {
  ElapsedTimeL = millis() -LastTimeL; // 経過時間の算出
  NowEncLPhaseB = digitalRead ( EncLPhaseB );
  if ( digitalRead(EncLPhaseA) == HIGH ) {
    // この下の代入は現在のBを読んでいるだけ
     // 条件分岐の都度に digitalRead を実行しないように、ここで最初に一回だけ読み込んで NewEncPhaseB として置いておく
    switch(LastEncLPhaseB){ // 前回チェンジ時のBで分岐
    case 0: switch(NowEncLPhaseB){
            case 0: DegIniL -1; break;
            case 1: DegIniL += 4;     break;
            }  break; 
    case 1: switch(NowEncLPhaseB){
            case 0: DegIniL -= 4;  break;
            case 1: DegIniL ++;  break;
            }  break;
    }
  }
  VelL = (DegIniL *0.18 *4.0 /127.78 *1000.0 /ElapsedTimeL) / 360.0 * PI * L_WHEEL;
 
  DegIniL = 0;
  
  LastTimeL = ElapsedTimeL;			   
  LastEncLPhaseB = digitalRead ( EncLPhaseB ); // 現在のBを改めて残す
//  Serial.print(NowEncRPhaseB ,DEC);
//  Serial.print("\t");
//  Serial.println(NowEncLPhaseB ,DEC);
}
