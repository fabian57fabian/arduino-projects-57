/*
 * //Other way to calculate sound force using digital in and out
  const int OUT_PIN = 8;
  const int SAMPLE_TIME = 10;
  unsigned long millisCurrent;
  unsigned long millisLast = 0;
  unsigned long millisElapsed = 0;
  int sampleBufferValue = 0;

  void setup()
  {
  Serial.begin(9600);
  }

  void loop() {

  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

  if (digitalRead(OUT_PIN) == LOW) {
    sampleBufferValue++;
  }
  if (millisElapsed > SAMPLE_TIME) {
    Serial.println(sampleBufferValue);
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }

  }

*/

int Sen = A2;//A0; // A0
int val = 0;
int LED1 = 12;//16; // D0, 16
int LED2 = 10;
int LED3 = 8;

int TH1 = 6;
int TH2 = 8;
int TH3 = 10;

int NORMAL_SENSOR = 519;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(Sen, INPUT);
  Serial.begin(9600);
}
void loop() {
  val = analogRead(Sen);
  val -= NORMAL_SENSOR;
  if (val < 0){
    val = -val;
  }
  Serial.println(val, DEC);

  digitalWrite(LED1, val > TH1 ? HIGH : LOW);
  digitalWrite(LED2, val > TH2 ? HIGH : LOW);
  digitalWrite(LED3, val > TH3 ? HIGH : LOW);
  delay(50);
}
