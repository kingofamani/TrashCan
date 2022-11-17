/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 16 Nov 2022 07:05:05 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_i2c(0x27);

#include <IRremote.h>
#include <Servo.h>
#include <Ultrasonic.h>

IRrecv irrecv(4);
decode_results results;
Servo __myservo3;
int count = 0;

Ultrasonic ultrasonic_8_9(8, 9);

void open() {
  __myservo3.write(80);
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

void writeScore(int addr, int count) {
  lcd_i2c.clear();
  if (count > (ReadFromMemory(1))) {
    lcd_i2c.print((String("New Rec:")+String(count)));
    writeToMemory(1, count);
  } else {
    lcd_i2c.print("Fail");
  }
  delay(2000);
}

void setup()
{
  Serial.begin(9600);

  lcd_i2c.begin(16, 2);
  irrecv.enableIRIn();
  __myservo3.attach(3);
  lcd_i2c.backlight();
  __myservo3.write(0);
  delay(1000);
  Serial.print("最高紀錄：");
  Serial.println((ReadFromMemory(1)));
  delay(2000);
}


void loop()
{
  if (ultrasonic_8_9.convert(ultrasonic_8_9.timing(), Ultrasonic::CM) <= 7) {
    count = count + 1;
  }
  delay(35);
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print(count);
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff6897") {
      //按1
    } else if (String(results.value, HEX) == "ff9867") {
      //按2打開
      open();
    } else if (String(results.value, HEX) == "ffb04f") {
      //按3關閉結束投籃
      writeScore(1, count);
      count = 0;
      lcd_i2c.clear();
      close();
    } else if (String(results.value, HEX) == "ff30cf") {
      //按4清除最高紀錄
      clearOneMemory(1);
    }

    irrecv.resume();
  }
}