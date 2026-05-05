#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

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

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    digitalWrite(LED_BUILTIN, HIGH);
} else {
    digitalWrite(LED_BUILTIN, LOW);
}
  if (radio.available()) {
    radio.read(&data, sizeof(data));

    Serial.print("Roll: ");
    Serial.print(data.roll);

    Serial.print(" Pitch: ");
    Serial.print(data.pitch);

    Serial.print(" Temp: ");
    Serial.print(data.temp);

    Serial.print(" Servo: ");
    Serial.print(data.servoPos);

    Serial.print(" State: ");
    Serial.println(data.state);
  }
}