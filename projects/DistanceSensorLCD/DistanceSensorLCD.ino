#include <LiquidCrystal.h>
int triggerPort = 7;
int echoPort = 8;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
long r;
long duration;
void setup() {
  r = 0;
  lcd.begin(16, 2);
  pinMode( triggerPort, OUTPUT );
  pinMode( echoPort, INPUT );
}

void readSensor() {
  digitalWrite( triggerPort, LOW );
  //invia un impulso di 10microsec su trigger
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );

  duration = pulseIn( echoPort, HIGH );

  r = duration / 58.2;
}
long lastdist = 0;
void loop() {
  readSensor();
  delay(50);
  if (lastdist != r) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(r);
  }
}

