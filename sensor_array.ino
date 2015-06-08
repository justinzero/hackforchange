
#include <dht.h>
const int userID = 1;    // User ID (Static)

//Pin Assignments
const int tempPin =  A0;  // Temperature Sensor
const int gasPin =   A1;  // Gas Sensor
const int humidPin = 2;  // Humidity Sensor
const int flamePin = A3;  // Flame Sensor
const int tiltPin =  3;  // Tilt Switch
int flameRed = 8;
int flameGreen   = 9;
int humidRed = 10;
int humidGreen = 11;
int gasRed   = 12;
int gasGreen = 13;
int tiltState = 0;
boolean headUp = 1;
dht DHT;

#define DHT11_PIN 2
#define beta 4090  //500 mV offset to allow for negative temperatures

void setup()
  {
  Serial.begin(9600);  //Start the serial connection with the computer
  pinMode(DHT11_PIN, INPUT);
  pinMode(humidPin, INPUT);
  pinMode(flameRed, OUTPUT);
  pinMode(flameGreen, OUTPUT);
  pinMode(humidRed, OUTPUT);
  pinMode(humidGreen, OUTPUT);
  pinMode(gasRed, OUTPUT);
  pinMode(gasGreen, OUTPUT);
  }

void loop()
{
//
//  Temperature sensor
//
 int reading = analogRead(tempPin);  
 
 long a = 1023 - analogRead(tempPin);
 
// converting that reading to voltage, for 3.3v arduino use 3.3
 float tempVoltage = reading * 5.0;
 tempVoltage /= 1024.0; 
  
// now print out the temperature
 float temperatureC = beta / (log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;  //converting from 10 mv per degree wit 500 mV offset
// Serial.print(temperatureC); Serial.println(" degrees C");

// now convert to Fahrenheit
 float temperatureF = temperatureC * 1.8 + 32.0;
// Serial.print(temperatureF); Serial.println(" degrees F");  
  

//
//  Smoke Sensor
//
int gasReading;
gasReading = analogRead(gasPin);
if (gasReading >= 110) {
  digitalWrite(gasRed, HIGH);
  digitalWrite(gasGreen, LOW);
}
else {
  digitalWrite(gasRed, LOW);
  digitalWrite(gasGreen, HIGH);
}


//
//   Tilt Switch
//
tiltState = digitalRead(tiltPin);
if (tiltState == HIGH) {
  headUp = 1;
}
else
{
  headUp = 0;
}

//
//  Flame Sensor
//
int flameState = analogRead(flamePin);
if (flameState >= 255) {
  digitalWrite(flameRed, HIGH);
  digitalWrite(flameGreen, LOW);
}
else 
{
  digitalWrite(flameRed, LOW);
  digitalWrite(flameGreen, HIGH);
}

//
//  Humidity Sensor
//
 int chk = DHT.read11(DHT11_PIN);

if (DHT.humidity >= 50) {
  digitalWrite(humidRed, HIGH);
  digitalWrite(humidGreen, LOW);
}
else 
{
  digitalWrite(humidRed, LOW);
  digitalWrite(humidGreen, HIGH);
}


//
//   JSON Serial Output
//
 Serial.println("{");
 Serial.print(" \"User ID\" : \""); Serial.print(userID);Serial.println("\",");
 Serial.print(" \"Temperature\" : \""); Serial.print(temperatureF);Serial.println("\",");
 Serial.print(" \"Smoke Level\" : \""); Serial.print(gasReading);Serial.println("\",");
 Serial.print(" \"Humidity Level\" : \""); Serial.print(DHT.humidity,1);Serial.println("\",");
 Serial.print(" \"Open Flame\" : \""); Serial.print(flameState);Serial.println("\",");
 Serial.print(" \"Head is upright\" : \""); Serial.print(headUp);Serial.println("\",");
 Serial.println("}");
 Serial.println();

 
// Delay between loops
 delay(5000);
}
