// Encoder is a 600P/R each rotation gives 600 Pulses on each diode
// If we chose Rising/Falling we get 1200 readings per rotation
// if we set it to Change (Rising and Falling) we get 2400 p er rotation

// Set variables to hold Encoder counters, these will increase or decrease depending on the rotation of encoder.
volatile int C1 = 0;  
volatile int C2 = 0;

const float W = 145;                                  // Distance between encoders
const float MM_REV = 60;                              // Encoder pulley circle perimeter
const float PP_REV = 2400;                            // Pulses per revolution
const float DRV = MM_REV/PP_REV;                      // Distance moved per pulse

float D1;                                             // Left wire distance
float D2;                                             // Right wire distance

float x = 0;                                          // X cartesian coordinate
float y = 0;                                          // Y cartesian coordinate

// Define Pins (must be interrupt capable)
#define E1_A 2
#define E1_B 3
#define E2_A 21
#define E2_B 20

void setup() {
  
  // Set pins to input
  pinMode(E1_A, INPUT);
  pinMode(E1_B, INPUT);
  pinMode(E2_A, INPUT);
  pinMode(E2_B, INPUT);
  
  // Turn on pullup resistors
  digitalWrite(E1_A, HIGH);
  digitalWrite(E1_B, HIGH);
  digitalWrite(E2_A, HIGH);
  digitalWrite(E2_B, HIGH);

  // Enable interrupt for pins on change (HIGH or LOW) and define the function to run on interrupt
  attachInterrupt(0, e1a, CHANGE); // pin 2   MEGA2560
  attachInterrupt(1, e1b, CHANGE); // pin 3   MEGA2560
  attachInterrupt(2, e2a, CHANGE); // pin 21  MEGA2560
  attachInterrupt(3, e2b, CHANGE); // pin 20  MEGA2560

  // Start Serial
  Serial.begin (115200);
  
}

void loop() {

  D1 = C1 * DRV + W/2;
  D2 = C2 * DRV + W/2;
  
  x = ( sq(W) - sq(D2) + sq(D1) ) / (2*W);
  y = sqrt(sq(D1)-sq(x));
  
  // Send the value of counter
  Serial.println ("C1: "+ String(C1) + "; C2: " + String(C2));
  Serial.println ("D1: "+ String(D1) + "; D2: " + String(D2));
  Serial.println ("X: "+ String(x) + "; Y: " + String(y));
  delay(500);
}


// ENCODER 1 //////////////////////////////////////////////////////////////////////////

void e1a(){
  if (digitalRead(E1_A) == HIGH) {     // look for a low-to-high on channel A
    if (digitalRead(E1_B) == LOW) {    // check channel B to see which way encoder is turning
      C1++;                       // CW
    } 
    else {
      C1--;                       // CCW
    }
  }
  else {                                // must be a high-to-low edge on channel A    
    if (digitalRead(E1_B) == HIGH) {   // check channel B to see which way encoder is turning  
      C1++;                       // CW
    } 
    else {
      C1--;                       // CCW
    }
  }
}

void e1b(){
  if (digitalRead(E1_B) == HIGH) {     // look for a low-to-high on channel B
    if (digitalRead(E1_A) == HIGH) {   // check channel A to see which way encoder is turning 
      C1++;                       // CW
    } 
    else {
      C1--;    // CCW
    }
  }
  else {                                // Look for a high-to-low on channel B 
    if (digitalRead(E1_A) == LOW) {    // check channel B to see which way encoder is turning  
      C1++;                       // CW
    } 
    else {
      C1--;                       // CCW
    }
  }
}


// ENCODER 2 //////////////////////////////////////////////////////////////////////////

void e2a(){
  if (digitalRead(E2_A) == HIGH) {     // look for a low-to-high on channel A
    if (digitalRead(E2_B) == LOW) {    // check channel B to see which way encoder is turning
      C2--;                       // CW
    } 
    else {
      C2++;                       // CCW
    }
  }
  else {                                // must be a high-to-low edge on channel A    
    if (digitalRead(E2_B) == HIGH) {   // check channel B to see which way encoder is turning  
      C2--;                       // CW
    } 
    else {
      C2++;                       // CCW
    }
  }
}

void e2b(){
  if (digitalRead(E2_B) == HIGH) {     // look for a low-to-high on channel B
    if (digitalRead(E2_A) == HIGH) {   // check channel A to see which way encoder is turning 
      C2--;                       // CW
    } 
    else {
      C2++;    // CCW
    }
  }
  else {                                // Look for a high-to-low on channel B 
    if (digitalRead(E2_A) == LOW) {    // check channel B to see which way encoder is turning  
      C2--;                       // CW
    } 
    else {
      C2++;                       // CCW
    }
  }
}
