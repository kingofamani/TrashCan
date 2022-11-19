/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 19 Nov 2022 07:57:55 GMT
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
}


void loop()
{
  if (ultrasonic_5_6.convert(ultrasonic_5_6.timing(), Ultrasonic::CM) <= 7) {
    count = count + 1;
    Serial.println(count);
    delay(35);
  }
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff9867") {
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