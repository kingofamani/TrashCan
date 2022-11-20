/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 20 Nov 2022 23:43:39 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <SimpleTimer.h>
#include <IRremote.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_i2c(0x27);

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
  __myservo3.write(130);
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
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print((String(secs-k+1)+String(" secs ")));
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
  lcd_i2c.begin(16, 2);
  __myservo3.write(0);
  delay(1000);
  lcd_i2c.backlight();
}


void loop()
{
  timer.run();
  if (ultrasonic_5_6.convert(ultrasonic_5_6.timing(), Ultrasonic::CM) <= 7) {
    count = count + 1;
    lcd_i2c.setCursor(0,1);
    lcd_i2c.print(count);
    delay(35);
  }
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff9867") {
      //按2
      open();
      lcd_i2c.clear();
      lcd_i2c.setCursor(0,0);
      lcd_i2c.print("START");
      //開始計時
      countDown(secs);
    }

    irrecv.resume();
  }
  //結束計時
  if (isTimeOut) {
    lcd_i2c.clear();
    lcd_i2c.setCursor(0,0);
    lcd_i2c.print("Game Over");
    lcd_i2c.setCursor(0,1);
    lcd_i2c.print((String("Your score:")+String(count)));
    isTimeOut = false;
    count = 0;
    close();
  }
}