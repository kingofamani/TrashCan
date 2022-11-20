/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 20 Nov 2022 23:42:00 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <EEPROM.h>
#include <IRremote.h>
#include <Servo.h>
#include <Ultrasonic.h>

IRrecv irrecv(4);
decode_results results;
Servo __myservo3;
int count = 0;

Ultrasonic ultrasonic_5_6(5, 6);

void open() {
  __myservo3.write(130);
  delay(1000);
}

void close() {
  __myservo3.write(0);
  delay(1000);
}

void writeToMemory(int addr, int val) {
  EEPROM.write(addr, val);
}

int ReadFromMemory(int addr) {
  return (EEPROM.read(addr));
}

void clearOneMemory(int addr) {
  EEPROM.write(addr, 0);
  Serial.println("清除完成");
}

void writeScore() {
  if (count > (ReadFromMemory(1))) {
    Serial.println((String("恭喜你破紀錄：")+String(count)+String("分")));
    writeToMemory(1, count);
  } else {
    Serial.println("再接再厲。");
  }
  delay(2000);
}

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn();
  __myservo3.attach(3);
  __myservo3.write(0);
  delay(1000);
  Serial.print("最高紀錄：");
  Serial.println((ReadFromMemory(1)));
  delay(2000);
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
    } else if (String(results.value, HEX) == "ff9867") {
      //按2打開
      Serial.println("投籃開始");
      open();
    } else if (String(results.value, HEX) == "ffb04f") {
      //按3關閉結束投籃
      writeScore();
      count = 0;
      close();
    } else if (String(results.value, HEX) == "ff30cf") {
      //按4清除最高紀錄
      clearOneMemory(1);
    }

    irrecv.resume();
  }
}