#include <DHT.h>
#include <LiquidCrystal.h>

// Pin Definitions
#define DHTPIN 2           // DHT11 Data pin connected to pin 2
#define DHTTYPE DHT11      // DHT11 sensor type
#define TRIG_PIN 3         // Ultrasonic sensor Trig pin
#define ECHO_PIN 4         // Ultrasonic sensor Echo pin
#define GAS_SENSOR A0      // Gas sensor connected to A0
#define OVERFLOW_SENSOR A1 // Overflow sensor connected to A1
#define BUZZER_PIN 5       // Buzzer connected to pin 5
#define rs 6               // LCD RS pin
#define en 7               // LCD Enable pin
#define d4 8               // LCD D4 pin
#define d5 9               // LCD D5 pin
#define d6 10              // LCD D6 pin
#define d7 11              // LCD D7 pin

// Initialize DHT sensor and LCD
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);        // Initialize 16x2 LCD
  dht.begin();             // Initialize DHT sensor
   Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);  // Ultrasonic sensor Trig pin as output
  pinMode(ECHO_PIN, INPUT);   // Ultrasonic sensor Echo pin as input
  pinMode(GAS_SENSOR, INPUT); // Gas sensor input
  pinMode(OVERFLOW_SENSOR, INPUT); // Overflow sensor input
  pinMode(BUZZER_PIN, OUTPUT); // Buzzer output
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read gas and overflow sensor values
  int gasValue = analogRead(GAS_SENSOR);
  int overflowValue = analogRead(OVERFLOW_SENSOR);

  // Measure distance with ultrasonic sensor
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Distance in cm

  // Display temperature, humidity, and distance
  lcd.setCursor(0, 0);
  if (isnan(humidity) || isnan(temperature)) {
    lcd.print("Sensor Error");
  } else {
    lcd.print("T:");
    lcd.print(temperature);
    lcd.print((char)223); // Degree symbol
    lcd.print("C ");
    lcd.print("H:");
    lcd.print(humidity);
    lcd.print("%");
  }

  // Check gas and overflow conditions
  lcd.setCursor(0, 1);
  bool alert = false;

  if (gasValue > 800) {
    lcd.print("Gas Detected   ");
    alert = true;
    GasMessage();
  } else if (overflowValue > 512) {
    lcd.print("Overflow       ");
    alert = true;
    sendAlertMessage();
  } else if (distance < 10) {
    lcd.print("Dist < 10 cm    ");
    alert = true;
    BlockMessage();
  } else {
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm   ");
  }

  // Activate buzzer if any alert condition is met
  if (alert) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000); // Update every 2 seconds
}

void sendAlertMessage() { 
 
  
  Serial.print("AT+CMGF=1\r\n"); // Set SMS text mode
  delay(2000);
  Serial.print("AT+CMGS=\"");
  Serial.print("+919637121841");
  Serial.print("\"\r\n"); // Set recipient number
  delay(2000);
  Serial.print("Alert!Drainage Overflow detected.\r\n"); // Message content
  delay(2000);
  Serial.print((char)26); // End AT command with Ctrl+Z
  delay(2000);
  Serial.print("\r\n");
  
  
}


void GasMessage() { 
 
  
  Serial.print("AT+CMGF=1\r\n"); // Set SMS text mode
  delay(2000);
  Serial.print("AT+CMGS=\"");
  Serial.print("+919637121841");
  Serial.print("\"\r\n"); // Set recipient number
  delay(2000);
  Serial.print("Alert!Toxic Gas detected.\r\n"); // Message content
  delay(2000);
  Serial.print((char)26); // End AT command with Ctrl+Z
  delay(2000);
  Serial.print("\r\n");
  
  
}

void BlockMessage() { 
 
  
  Serial.print("AT+CMGF=1\r\n"); // Set SMS text mode
  delay(2000);
  Serial.print("AT+CMGS=\"");
  Serial.print("+919637121841");
  Serial.print("\"\r\n"); // Set recipient number
  delay(2000);
  Serial.print("Alert!Drainage Blockage detected.\r\n"); // Message content
  delay(2000);
  Serial.print((char)26); // End AT command with Ctrl+Z
  delay(2000);
  Serial.print("\r\n");
  
  
}



