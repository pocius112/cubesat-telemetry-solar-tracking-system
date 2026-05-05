#include <Wire.h>
#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

// ===================== MPU6050 =====================
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t t;

const int mpu_ad = 0x68;

// ===================== NRF24 =====================
RF24 radio(7, 8);   // CE, CSN
const byte address[6] = "00001";

// ===================== STATES =====================
enum State {
  BOOT,
  CALIBRATION,
  MEASURING,
  SAFE_MODE
};

State currentState = BOOT;

// ===================== LDR =====================
const int topSensor = A0;
const int frontSensor = A1;
const int bottomSensor = A2;

// ===================== SERVO =====================
Servo panelServo;
int servoPos = 90;

// ===================== THRESHOLDS =====================
const int lightThreshold = 200;
const int deadband = 50;

// ===================== DATA PACKET =====================
struct __attribute__((packed)) DataPacket {
  float roll;
  float pitch;
  float temp;
  int top;
  int front;
  int bottom;
  int servoPos;
  int state;
};

DataPacket data;

void setup() {
  Serial.begin(9600);

  // MPU6050 init
  Wire.begin();
  Wire.beginTransmission(mpu_ad);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Servo init
  panelServo.attach(9);
  panelServo.write(servoPos);

  // NRF24 init
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  currentState = MEASURING;
}

void loop() {

  // ===================== READ MPU6050 =====================
  Wire.beginTransmission(mpu_ad);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(mpu_ad, 14, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  t  = Wire.read() << 8 | Wire.read();
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();

  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  float roll  = atan2(ay_g, az_g) * 180.0 / PI;
  float pitch = atan2(-ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180.0 / PI;
  float tempC = t / 340.00 + 36.53;

  // ===================== READ LDR =====================
  int topValue = analogRead(topSensor);
  int frontValue = analogRead(frontSensor);
  int bottomValue = analogRead(bottomSensor);

  // ===================== STATE MACHINE =====================
  switch(currentState) {

    case MEASURING: {

      if(frontValue < lightThreshold) {
        currentState = SAFE_MODE;
        break;
      }

      int error = topValue - bottomValue;

      if(error > deadband) {
        servoPos += 5;
      }
      else if(error < -deadband) {
        servoPos -= 5;
      }

      servoPos = constrain(servoPos, 20, 160);
      panelServo.write(servoPos);

      break;
    }

    case SAFE_MODE: {

      servoPos = 90;
      panelServo.write(servoPos);

      if(frontValue > lightThreshold) {
        currentState = MEASURING;
      }

      break;
    }

    default:
      currentState = MEASURING;
      break;
  }

  // ===================== PREPARE DATA =====================
  data.roll = roll;
  data.pitch = pitch;
  data.temp = tempC;
  data.top = topValue;
  data.front = frontValue;
  data.bottom = bottomValue;
  data.servoPos = servoPos;
  data.state = currentState;

  // ===================== SEND DATA =====================
  bool ok = radio.write(&data, sizeof(data));

  // ===================== SERIAL DEBUG =====================
  Serial.print("Sending roll: ");
Serial.println(roll);
  Serial.print("Roll: ");
  Serial.print(data.roll);

  Serial.print(" Pitch: ");
  Serial.print(data.pitch);

  Serial.print(" Temp: ");
  Serial.print(data.temp);

  Serial.print(" Top: ");
  Serial.print(data.top);

  Serial.print(" Front: ");
  Serial.print(data.front);

  Serial.print(" Bottom: ");
  Serial.print(data.bottom);

  Serial.print(" Servo: ");
  Serial.print(data.servoPos);

  Serial.print(" State: ");
  Serial.print(data.state);

  Serial.print(" TX: ");
  Serial.println(ok ? "OK" : "FAIL");

  delay(200);
}