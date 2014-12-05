// 角速度だけを出すように不必要な変数、画面表示の命令などを削ったもの
// 確認用の変数、画面表示が見たい場合は tomato5.c を参照してネ



/* -------------------------------------
   グローバル変数
------------------------------------- */
// Arduinoピン設定
const int EncPhaseA = 2; // 割り込みピンを指定すること！
const int EncPhaseB = 4;

// 計算結果格納用の変数
volatile long DegIni = 0;

// エンコーダー用
volatile int NowEncPhaseB; // 条件分岐の都度読み込みを実行しないように
volatile int LastEncPhaseB;

// 角速度関係
int AngVel = 0;
unsigned long LastTime = 0; // 前回角速度を計測した時の絶対時刻
unsigned long ElapsedTime = 0; // 経過時間



/* -------------------------------------
   関数プロトタイプ宣言
------------------------------------- */
void EncCounter ( void );



/* -------------------------------------
   メイン関数
------------------------------------- */
void setup () {
	pinMode ( EncPhaseA, INPUT );
	pinMode ( EncPhaseB, INPUT );

	Serial.begin ( 9600 );

	LastEncPhaseB = digitalRead ( EncPhaseB ); // 初期化

	attachInterrupt ( 2, EncCounter, CHANGE ); // 割り込み処理
}



void loop () {
	ElapsedTime = millis() -LastTime; // 経過時間の算出

	AngVel = DegIni *0.18 *4 /127.78 *1000 /ElapsedTime;

        SPDR = AngVel;

	LastTime = millis();			   
	DegIni = 0;
}



/* -------------------------------------
   エンコーダー
------------------------------------- */
void EncCounter ( void ) {
	if ( digitalRead(EncPhaseA) == HIGH ) {
		NowEncPhaseB = digitalRead ( EncPhaseB ); // 条件分岐の都度に digitalRead を実行しないように、ここで最初に一回だけ読み込んで NewEncPhaseB として置いておく
		switch ( LastEncPhaseB ) {
		case 0: // 順回転だった場合
			switch ( NowEncPhaseB ) {
			case 0: // 予想より回転が早かった場合
				DegIni +=2;
				break;
			case 1: // 通常の場合
				DegIni ++;
				break;
			}
			break;
		case 1: // 逆回転だった場合
			switch ( NowEncPhaseB ) {
			case 0:
				DegIni --;
				break;
			case 1:
				DegIni -=2;
u				break;
			}
			break;
		}
	} else;

	LastEncPhaseB = digitalRead(EncPhaseB);
}
