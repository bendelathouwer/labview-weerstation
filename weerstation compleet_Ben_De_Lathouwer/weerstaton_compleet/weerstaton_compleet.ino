#include "DHT.h"// the sensor libary 
#include <Wire.h>
#include <Adafruit_MotorShield.h>

int IndicatorPin = 3;
// sensor instance
DHT dht;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

void setup()
{
  Serial.begin(115200);

  dht.setup(2);// the data from the sensor is read on pin number 2

  pinMode(IndicatorPin, OUTPUT);

  AFMS.begin(2500);
  myMotor -> setSpeed(0);
  myMotor ->run(FORWARD);
  myMotor ->run(RELEASE);

}

void loop() {
  if (Serial.available())
  {
    byte ch = Serial.read();
    //Serial.print("0x");
    // Serial.println(ch, HEX);

    // controls fan
    MotorControl(ch);
  }

  // read sensors
  getDhtData();
}


void getDhtData()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(humidity, 1);
  Serial.print(" ");
  Serial.print(temperature, 1);
  Serial.println();
}

void MotorControl(byte ch)
{
  switch (ch)
  {
    case '0':
      digitalWrite(IndicatorPin, LOW);
      myMotor ->run(FORWARD);
      myMotor ->setSpeed(0);

      break;
    case '1':
      digitalWrite(IndicatorPin, HIGH); 
      myMotor ->run(FORWARD);
      myMotor ->setSpeed(255);
    
      break;
    default:
      // who cares! (eg CR, LF, ...)
      break;
  }
}


