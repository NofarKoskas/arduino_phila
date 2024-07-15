#include <Encoder.h>

Encoder knobLeft(19, 38);

#define PWMA 12 // A motor speed
#define DIRA1 34 
#define DIRA2 35 // A motor direction

#define PWMB 8    // B motor speed
#define DIRB1 37 
#define DIRB2 36  // B motor direction

#define PWMC 6    // C motor speed
#define DIRC1 43 
#define DIRC2 42  // C motor direction

#define PWMD 5    // D motor speed
#define DIRD1 A4  // D motor direction pin 26  
#define DIRD2 A5  // D motor direction pin 27

#define MOTORB_FORWARD(pwm)    do { digitalWrite(DIRB1, LOW); digitalWrite(DIRB2, HIGH); analogWrite(PWMB, pwm); } while(0)
#define MOTORB_STOP(x)         do { digitalWrite(DIRB1, LOW); digitalWrite(DIRB2, LOW); analogWrite(PWMB, 0); } while(0)
#define MOTORB_BACKOFF(pwm)    do { digitalWrite(DIRB1, HIGH); digitalWrite(DIRB2, LOW); analogWrite(PWMB, pwm); } while(0)

#define MAX_PWM   200
#define MIN_PWM   130

float Motor_PWM = 30.0;
float RWheel = 39.7*1000;   // [mm]
float Phi = 3.141592654; // [rad]

void setup() {
  Serial.begin(9600);
  Serial.println("Encoder Test:");
}

void loop() {
  static float position = 0.0;  // Declare position variable and initialize it
  
  long newPOS = knobLeft.read();
  float newPOSinMM = (float)(newPOS * 2 * Phi * RWheel) / 1300.0;

  if (newPOSinMM != position) {
    Serial.print("Position = ");
    Serial.println(newPOSinMM);
    position = newPOSinMM;
  }

  if (newPOSinMM < 249.422*1000) {
    MOTORB_BACKOFF((int)Motor_PWM); // Convert Motor_PWM to int for analogWrite
    delay(10);
  }
  MOTORB_STOP((int)Motor_PWM); // Convert Motor_PWM to int for analogWrite

  // Reset encoder position to zero if a character is sent from the serial monitor
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset knob to zero");
    knobLeft.write(0);
  }
}
