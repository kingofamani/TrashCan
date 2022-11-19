/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 19 Nov 2022 03:22:27 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <SimpleTimer.h>
#include <IRremote.h>
#include <Servo.h>
#include <Ultrasonic.h>

SimpleTimer timer;
IRrecv irrecv(4);
decode_results results;
Servo __myservo3;
int count = 0;

int secs = 10;

boolean isTimeOut = false;

Ultrasonic ultrasonic_5_6(5, 6);

void open() {
  __myservo3.write(80);
  delay(1000);
}

void close() {
  __myservo3.write(0);
  delay(1000);
}

void countDown(int secs) {
  timer.setTimer(1000, printSec, secs+1);
}

void printSec() {
  static int k = 0;
  k++;
  Serial.println((String(secs-k+1)+String("秒")));
  if ((k) == secs + 1) {
    k = 0;
    isTimeOut = true;
  }
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
  timer.run();
  if (ultrasonic_5_6.convert(ultrasonic_5_6.timing(), Ultrasonic::CM) <= 7) {
    count = count + 1;
    Serial.println(count);
    delay(35);
  }
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff9867") {
      //按2
      open();
      Serial.println("開始投籃");
      //開始計時
      countDown(secs);
    }

    irrecv.resume();
  }
  //結束計時
  if (isTimeOut) {
    Serial.println((String("遊戲結束，你總共進了")+String(count)+String("球")));
    isTimeOut = false;
    count = 0;
    close();
  }
}