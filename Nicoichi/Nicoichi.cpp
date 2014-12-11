/* -------------------------------------
   pin番号指定
------------------------------------- */
#define R_ENC_PHASE_A 2
#define R_ENC_PHASE_B 3
#define MTR_R1 8
#define MTR_R2 9
#define L_ENC_PHASE_A 4
#define L_ENC_PHASE_B 5
#define MTR_L1 10
#define MTR_L2 11


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
void setup () {
  pinMode ( R_ENC_PHASE_A, INPUT );
  pinMode ( R_ENC_PHASE_B, INPUT );
  pinMode(MTR_R1, OUTPUT);
  pinMode(MTR_R2, OUTPUT);
  pinMode ( L_ENC_PHASE_A, INPUT );
  pinMode ( L_ENC_PHASE_B, INPUT );
  pinMode(MTR_L1, OUTPUT);
  pinMode(MTR_L2, OUTPUT);
  
  Serial.begin ( 115200 );

  LastR_ENC_PHASE_B = digitalRead ( R_ENC_PHASE_B ); // 初期化
  LastL_ENC_PHASE_B = digitalRead ( L_ENC_PHASE_B ); // 初期化
  
  attachInterrupt ( 2, EncRCounter, CHANGE ); // 割り込み処理登録
  attachInterrupt ( 4, EncLCounter, CHANGE ); // 割り込み処理登録
  
  ComVelR = TREAD * omega + Vel;
  ComVelL = Vel - TREAD * omega;
  max_VelR = ((5200.0/127.78/60.0) * PI * R_WHEEL)*MAX_MTR_R2/255.0;   //((毎分回転数/ギア比/秒)*pi*右輪直径)/最大速度時のパルス
  max_VelL = ((5200.0/127.78/60.0) * PI * L_WHEEL)*MAX_MTR_L2/255.0;
 
  
  analogWriteResolution(8);
  digitalWrite(MTR_R1, LOW);
  analogWrite(MTR_R2, 0);  //右の入力値はそのままの値(255で100%)
  digitalWrite(MTR_L1, HIGH);
  analogWrite(MTR_L2, 255);  //左の入力値は255-操作量(0で100%)

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
   analogWrite(MTR_R2, inputR);
   analogWrite(MTR_L2, 255 - inputL);
   
  Serial.print(inputR ,DEC);
  Serial.print("\t");
  Serial.println(inputL ,DEC);
}



/* -------------------------------------
   エンコーダー感知タスク
------------------------------------- */
void EncRCounter ( void ) {
  ElapsedTimeR = millis() -LastTimeR; // 経過時間の算出
  NowR_ENC_PHASE_B = digitalRead ( R_ENC_PHASE_B );
  if ( digitalRead(R_ENC_PHASE_A) == HIGH ) {
    // この下の代入は現在のBを読んでいるだけ
     // 条件分岐の都度に digitalRead を実行しないように、ここで最初に一回だけ読み込んで NewEncPhaseB として置いておく
    switch(LastR_ENC_PHASE_B){ // 前回チェンジ時のBで分岐
    case 0: switch(NowR_ENC_PHASE_B){
            case 0: DegIniR -1; break;
            case 1: DegIniR += 4;     break;
            }  break; 
    case 1: switch(NowR_ENC_PHASE_B){
            case 0: DegIniR -= 4;  break;
            case 1: DegIniR ++;  break;
            }  break;
    }
  }
  VelR = (DegIniR *0.18 *4.0 /127.78 *1000.0 /ElapsedTimeR) / 360.0 * PI * R_WHEEL;
 
  DegIniR = 0;
  
  LastTimeR = ElapsedTimeR;			   
  LastR_ENC_PHASE_B = digitalRead ( R_ENC_PHASE_B ); // 現在のBを改めて残す
}

void EncLCounter ( void ) {
  ElapsedTimeL = millis() -LastTimeL; // 経過時間の算出
  NowL_ENC_PHASE_B = digitalRead ( L_ENC_PHASE_B );
  if ( digitalRead(L_ENC_PHASE_A) == HIGH ) {
    // この下の代入は現在のBを読んでいるだけ
     // 条件分岐の都度に digitalRead を実行しないように、ここで最初に一回だけ読み込んで NewEncPhaseB として置いておく
    switch(LastL_ENC_PHASE_B){ // 前回チェンジ時のBで分岐
    case 0: switch(NowL_ENC_PHASE_B){
            case 0: DegIniL -1; break;
            case 1: DegIniL += 4;     break;
            }  break; 
    case 1: switch(NowL_ENC_PHASE_B){
            case 0: DegIniL -= 4;  break;
            case 1: DegIniL ++;  break;
            }  break;
    }
  }
  VelL = (DegIniL *0.18 *4.0 /127.78 *1000.0 /ElapsedTimeL) / 360.0 * PI * L_WHEEL;
 
  DegIniL = 0;
  
  LastTimeL = ElapsedTimeL;			   
  LastL_ENC_PHASE_B = digitalRead ( L_ENC_PHASE_B ); // 現在のBを改めて残す
}
