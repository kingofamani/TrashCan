/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 19 Nov 2022 04:04:20 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <IRremote.h>
#include <Servo.h>
#include <Ultrasonic.h>

IRrecv irrecv(4);
decode_results results;
Servo __myservo3;
int count = 0;

Ultrasonic ultrasonic_5_6(5, 6);

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

void open() {
  __myservo3.write(80);
  delay(1000);
}

void close() {
  __myservo3.write(0);
  delay(1000);
}

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn();
  __myservo3.attach(3);
  __myservo3.write(0);
  delay(1000);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}


void loop()
{
  if (ultrasonic_5_6.convert(ultrasonic_5_6.timing(), Ultrasonic::CM) <= 7) {
    count = count + 1;
    Serial.println(count);
    delay(35);
  }
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff6897") {
      //按1
      openAndClose();
    } else if (String(results.value, HEX) == "ff9867") {
      //按2
      open();
    } else if (String(results.value, HEX) == "ffb04f") {
      //按3
      count = 0;
      close();
    }

    irrecv.resume();
  }
}