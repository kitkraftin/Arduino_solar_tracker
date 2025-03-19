#include <Servo.h>

#define LDR_LEFT 2   // Digital pin for left LDR module (D0)
#define LDR_RIGHT 3  // Digital pin for right LDR module (D0)
#define SERVO_PIN 9  // Servo motor pin

Servo solarServo;
int servoPos = 120; // Initial servo position (facing straight up)
int threshold = 50; // Hysteresis to prevent oscillations

void setup() {
  pinMode(LDR_LEFT, INPUT);
  pinMode(LDR_RIGHT, INPUT);
  solarServo.attach(SERVO_PIN);
  solarServo.write(servoPos);
  Serial.begin(9600);
}

void loop() {
  int leftLDR = digitalRead(LDR_LEFT) ? 1000 : 20;  // Simulating digital output behavior
  int rightLDR = digitalRead(LDR_RIGHT) ? 1000 : 20;

  Serial.print("Left LDR: ");
  Serial.print(leftLDR);
  Serial.print(" | Right LDR: ");
  Serial.println(rightLDR);

  if (abs(leftLDR - rightLDR) < threshold) {
    // Sun is overhead, reset to 90 degrees
    servoPos = 120;
  } else if (leftLDR > rightLDR) {
    // Move servo to the right
    servoPos = constrain(servoPos + 5, 0, 180);
  } else {
    // Move servo to the left
    servoPos = constrain(servoPos - 5, 0, 180);
  }

  solarServo.write(servoPos);
  delay(500);  // Adjust delay to control servo movement speed
}
