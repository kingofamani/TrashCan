/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 18 Nov 2022 00:31:51 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Servo.h>
#include <IRremote.h>
#include <Ultrasonic.h>

Servo __myservo3;
void openAndClose() {
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  __myservo3.write(80);
  delay(3000);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  __myservo3.write(0);
  delay(1000);
}

IRrecv irrecv(4);
decode_results results;
int count = 0;

int s = 0;

Ultrasonic ultrasonic_5_6(5, 6);

void open() {
  __myservo3.write(80);
  delay(1000);
}

void close() {
  __myservo3.write(0);
  delay(1000);
}

int timer(int countDownSec) {
  static unsigned long startTime = "millis()";
  static unsigned long beforeFlagSec = "millis()";
  int inteval = 1000;
  if (millis() > beforeFlagSec + inteval) {
    beforeFlagSec = millis();
    int rest = countDownSec - ((millis() + startTime) / 1000);
    if (rest >= 0) {
      Serial.println(rest);
      return (rest);
    }
  }
}

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  __myservo3.attach(3);
  Serial.begin(9600);

  irrecv.enableIRIn();
  __myservo3.write(0);
  delay(1000);
}


void loop()
{
  if (ultrasonic_5_6.convert(ultrasonic_5_6.timing(), Ultrasonic::CM) <= 7) {
    count = count + 1;
  }
  delay(35);
  Serial.println(count);
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff6897") {
      //按1
      openAndClose();
    } else if (String(results.value, HEX) == "ff9867") {
      //按2
      s = timer(10);
      if (s == 0) {
        Serial.println("結束");
        s = timer(0);
      }
      open();
    } else if (String(results.value, HEX) == "ffb04f") {
      //按3
      count = 0;
      close();
    }

    irrecv.resume();
  }
}