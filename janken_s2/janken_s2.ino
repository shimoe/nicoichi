int led = 13;


void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(led, OUTPUT);
}

void loop(){
  int i= random(3);
  Serial.write(i);
  digitalWrite(led, HIGH);   // LEDをオン
  delay(1000);                  // 1秒待つ
  digitalWrite(led, LOW);    // LEDをオフ
  delay(1000);
}
