// Define the shared address control pins
const int S0_PIN = 2;
const int S1_PIN = 3;
const int S2_PIN = 4;
const int S3_PIN = 5;

// Array of Enable (EN) pins for the 8 multiplexers
const int EN_PINS[8] = {6, 7, 8, 9, 10, 11, 12, 13};

void setup() {
  Serial.begin(9600);

  // Set control pins as outputs
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);

  // Initialize all multiplexers as disabled (HIGH = Asleep)
  for (int i = 0; i < 8; i++) {
    pinMode(EN_PINS[i], OUTPUT);
    digitalWrite(EN_PINS[i], HIGH);
  }

  Serial.println("Project-Nebula-BioZ: 128-Node Matrix Test Initialized.");
}

void loop() {
  // Step through each of the 8 multiplexer chips
  for (int chip = 0; chip < 8; chip++) {

    // Wake up the current chip (LOW = Awake)
    digitalWrite(EN_PINS[chip], LOW);

    // Step through each of the 16 channels on this chip
    for (int channel = 0; channel < 16; channel++) {

      // Calculate the global node number (0 to 127)
      int globalNode = (chip * 16) + channel;

      // Set the 4-bit binary address on the shared bus
      digitalWrite(S0_PIN, bitRead(channel, 0));
      digitalWrite(S1_PIN, bitRead(channel, 1));
      digitalWrite(S2_PIN, bitRead(channel, 2));
      digitalWrite(S3_PIN, bitRead(channel, 3));

      // --- TRANSMIT LIVE SENSING TELEMETRY ---
      // Simulates your validated benchmarks to stream clean data directly into your Python UI
      double mockMagnitude = 1136.959 + random(-50, 50); 
      double mockPhase = -193.685 + random(-5, 5);      
      
      Serial.print("$");
      Serial.print(globalNode);
      Serial.print(":");
      Serial.print(mockMagnitude, 3); 
      Serial.print(":");
      Serial.print(mockPhase, 3);     
      Serial.println(",");            
      
      delay(10); // Pause briefly at each node (10ms) for high-performance track switching
    } // <-- Channels loop closes HERE (after scanning all 16 tracks)

    // Put the current chip back to sleep ONLY after all its 16 channels are done
    digitalWrite(EN_PINS[chip], HIGH);
  } // <-- Chips loop closes HERE

  // Clear data boundary notification
  Serial.println("--- Full 128-Node Matrix Scan Complete ---");
  delay(2000); // Wait 2 seconds before starting the next full sweep
} // <-- Loop function closes HERE
