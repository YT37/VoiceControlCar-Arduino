#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

String voice;
SoftwareSerial BT(0, 1);

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

Servo myServo;

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);

  myServo.attach(10);
  myServo.write(90);
}
void loop()
{
  while (BT.available())
  {
    delay(10);
    char c = BT.read();
    voice += c;
  }

  if (voice.length() > 0)
  {
    BT.println(voice);

    if (voice == "*forward#")
    {
      forward();
    }

    else if (voice == "*backward#")
    {
      backward();
    }

    else if (voice == "*right#")
    {
      right();
    }

    else if (voice == "*left#")
    {
      left();
    }

    else if (voice == "*stop#")
    {
      stop();
    }

    voice = "";
  }
}
void forward()
{
  motor1.run(BACKWARD);
  motor1.setSpeed(255);

  motor2.run(BACKWARD);
  motor2.setSpeed(255);

  delay(2000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void backward()
{
  motor1.run(FORWARD);
  motor1.setSpeed(255);

  motor2.run(FORWARD);
  motor2.setSpeed(255);

  delay(2000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void left()
{
  myServo.write(180);
  delay(500);

  myServo.write(90);
  delay(500);

  motor1.run(FORWARD);
  motor1.setSpeed(255);

  motor2.run(BACKWARD);
  motor2.setSpeed(255);

  delay(2000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void right()
{
  myServo.write(0);
  delay(1000);

  myServo.write(90);
  delay(1000);

  motor1.run(BACKWARD);
  motor1.setSpeed(255);

  motor2.run(FORWARD);
  motor2.setSpeed(255);

  delay(2000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}