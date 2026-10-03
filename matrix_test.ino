cpp
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

// Log the active node to the Serial Monitor
Serial.print("Scanning Matrix Node: ");
Serial.println(globalNode);

delay(50); // Pause briefly (50ms) at each node to simulate a reading
}

// Put the current chip back to sleep before moving to the next
digitalWrite(EN_PINS[chip], HIGH);
}

Serial.println("--- Full 128-Node Matrix Scan Complete ---");
delay(2000); // Wait 2 seconds before starting the next full sweep
}
