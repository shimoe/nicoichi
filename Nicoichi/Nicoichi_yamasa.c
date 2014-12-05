/* -------------------------------------
   グローバル変数
------------------------------------- */
// Arduinoピン設定
const int EncPhaseA = 2; // 割り込みピンを指定すること！
const int EncPhaseB = 4;

// 計算結果格納用の変数
volatile long DegIni = 0;

// エンコーダー用
volatile int NowEncPhaseB;
volatile int LastEncPhaseB;

// 角速度関係
int AngVel = 0;
unsigned long StartTime;
unsigned long EndTime = 0;

// モーター
const int MtrR1 = 10;
const int MtrR2 = 11;


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

	Serial.begin ( 115200 );

	LastEncPhaseB = digitalRead ( EncPhaseB ); // 初期化
	StartTime = millis();
	
	attachInterrupt ( 2, EncCounter, CHANGE ); // 割り込み処理

	digitalWrite ( MtrR1, HIGH  );
	analogWrite ( MtrR2, 0 );
}



void loop () {
}



/* -------------------------------------
   エンコーダー
------------------------------------- */
void EncCounter ( void ) {
	if ( digitalRead(EncPhaseA) == HIGH ) {
		NowEncPhaseB = digitalRead ( EncPhaseB );
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
				break;
			}
			break;
		}
	} else;

	LastEncPhaseB = NowEncPhaseB;

	StartTime = millis();

	//DeltaTime = StartTime -EndTime;
	AngVel = DegIni *0.18 *4 /127.78// *1000 /(StartTime -EndTime);
	Serial.println ( AngVel, DEC );

	EndTime = StartTime;
}
