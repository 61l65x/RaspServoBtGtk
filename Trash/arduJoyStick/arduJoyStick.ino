
// Define sensor pins.
#define SENSOR_1_PIN A0 //X
#define SENSOR_2_PIN A1 //Y
#define SWITCH_PIN A2

#define SENSOR_1_OUTPUT 3
#define SENSOR_2_OUTPUT 4
#define SWITCH_OUTPUT 5


void setup() {
  // Start the serial monitor.
  Serial.begin(9600);

  // Initiate digital pins as outputs.
  pinMode(SENSOR_1_OUTPUT, OUTPUT);
  pinMode(SENSOR_2_OUTPUT, OUTPUT);
  pinMode(SWITCH_OUTPUT, OUTPUT);
  
}

void loop() {
  // Collate data from the analog sensors.
  int SENSOR_1_VALUE = analogRead(SENSOR_1_PIN); //X
  int SENSOR_2_VALUE = analogRead(SENSOR_2_PIN); //Y
  int SWITCH_VALUE =   analogRead(SWITCH_PIN);


  // Print values.
  //Serial.println("SENSOR_1: " + String(SENSOR_1_VALUE) + "\nSENSOR_2: " + String(SENSOR_2_VALUE) + "\nSWITCH: " + String(SWITCH_VALUE));
  Serial.println("\nSWITCH_VALUE: " + String(SWITCH_VALUE));
  // Send signal to Raspberry Pi if the condition is met.
  if(SENSOR_1_VALUE){ digitalWrite(SENSOR_1_OUTPUT, HIGH); }else{ digitalWrite(SENSOR_1_OUTPUT, LOW); }
  
  if(SENSOR_2_VALUE){ digitalWrite(SENSOR_2_OUTPUT, HIGH); }else{ digitalWrite(SENSOR_2_OUTPUT, LOW); }

  if(SWITCH_VALUE){ digitalWrite(SWITCH_OUTPUT, HIGH); }else{ digitalWrite(SWITCH_OUTPUT, LOW); }

}
