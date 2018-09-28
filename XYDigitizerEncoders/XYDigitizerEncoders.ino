
// Encoder is a 600P/R each rotation gives 600 Pulses on each diode
// If we chose Rising/Falling we get 1200 readings per rotation
// if we set it to Change (Rising and Falling) we get 2400 p er rotation

const float mm_encoder_dist = 159;
const float mm_per_step = 60/2400;
float x;
float y;

// Set variables to hold Encoder counters, these will increase or decrease depending on the rotation of encoder.
volatile int counter1 = 0;  
volatile int counter2 = 0;

// Define Pins (must be interrupt capable)
#define RE1_A 2
#define RE1_B 3
#define RE2_A 21
#define RE2_B 20

void setup() {
  
  // Set pins to input
  pinMode(RE1_A, INPUT);
  pinMode(RE1_B, INPUT);
  pinMode(RE2_A, INPUT);
  pinMode(RE2_B, INPUT);
  
  // Turn on pullup resistors
  digitalWrite(RE1_A, HIGH);
  digitalWrite(RE1_B, HIGH);
  digitalWrite(RE2_A, HIGH);
  digitalWrite(RE2_B, HIGH);

  // Enable interrupt for pins on change (HIGH or LOW) and define the function to run on interrupt
  attachInterrupt(0, e1a, CHANGE); // pin 2   MEGA2560
  attachInterrupt(1, e1b, CHANGE); // pin 3   MEGA2560
  attachInterrupt(2, e2a, CHANGE); // pin 21  MEGA2560
  attachInterrupt(3, e2b, CHANGE); // pin 20  MEGA2560

  // Start Serial
  Serial.begin (115200);
  
}

void loop() {
  // Send the value of counter
  Serial.println ("C1: "+ String(counter1) + "; C2: " + String(counter2));
}


// ENCODER 1 //////////////////////////////////////////////////////////////////////////

void e1a(){
  if (digitalRead(RE1_A) == HIGH) {     // look for a low-to-high on channel A
    if (digitalRead(RE1_B) == LOW) {    // check channel B to see which way encoder is turning
      counter1++;                       // CW
    } 
    else {
      counter1--;                       // CCW
    }
  }
  else {                                // must be a high-to-low edge on channel A    
    if (digitalRead(RE1_B) == HIGH) {   // check channel B to see which way encoder is turning  
      counter1++;                       // CW
    } 
    else {
      counter1--;                       // CCW
    }
  }
}

void e1b(){
  if (digitalRead(RE1_B) == HIGH) {     // look for a low-to-high on channel B
    if (digitalRead(RE1_A) == HIGH) {   // check channel A to see which way encoder is turning 
      counter1++;                       // CW
    } 
    else {
      counter1--;    // CCW
    }
  }
  else {                                // Look for a high-to-low on channel B 
    if (digitalRead(RE1_A) == LOW) {    // check channel B to see which way encoder is turning  
      counter1++;                       // CW
    } 
    else {
      counter1--;                       // CCW
    }
  }
}


// ENCODER 2 //////////////////////////////////////////////////////////////////////////

void e2a(){
  if (digitalRead(RE2_A) == HIGH) {     // look for a low-to-high on channel A
    if (digitalRead(RE2_B) == LOW) {    // check channel B to see which way encoder is turning
      counter2--;                       // CW
    } 
    else {
      counter2++;                       // CCW
    }
  }
  else {                                // must be a high-to-low edge on channel A    
    if (digitalRead(RE2_B) == HIGH) {   // check channel B to see which way encoder is turning  
      counter2--;                       // CW
    } 
    else {
      counter2++;                       // CCW
    }
  }
}

void e2b(){
  if (digitalRead(RE2_B) == HIGH) {     // look for a low-to-high on channel B
    if (digitalRead(RE2_A) == HIGH) {   // check channel A to see which way encoder is turning 
      counter2--;                       // CW
    } 
    else {
      counter2++;    // CCW
    }
  }
  else {                                // Look for a high-to-low on channel B 
    if (digitalRead(RE2_A) == LOW) {    // check channel B to see which way encoder is turning  
      counter2--;                       // CW
    } 
    else {
      counter2++;                       // CCW
    }
  }
}

