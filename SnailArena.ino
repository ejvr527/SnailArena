
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN1 2
#define DHTPIN2 3 
#define DHTPIN3 4 
#define DHTPIN4 5 

// Uncomment the type of sensor in use:
#define DHTTYPE1    DHT11     // DHT 11
#define DHTTYPE2    DHT22     // DHT 22 (AM2302)
#define DHTTYPE3    DHT21     // DHT 21 (AM2301)

DHT dht[] = {
  {DHTPIN1, DHTTYPE2},
  {DHTPIN2, DHTTYPE2},
  {DHTPIN3, DHTTYPE2},
  {DHTPIN4, DHTTYPE2}
};

float humidity[4];
float temperature[4];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (auto& sensor : dht) {
    sensor.begin();
  }
}

void loopTable(float humidity[4],float temperature[4]){
  Serial.print(F("Temperature "));
  for (int i = 0; i < 4; i++) {
    Serial.print("\t");
    Serial.print(temperature[i]);
  }
  Serial.println("");
  Serial.print(F("Humidity "));
  for (int i = 0; i < 4; i++) {
    Serial.print("\t");
    Serial.print(humidity[i]);
  }
  Serial.println("");
  Serial.println("");
}

void thruSerial(float humidity[4],float temperature[4]){
  Serial.print(F("T:"));
  for (int i = 0; i < 4; i++) {
    Serial.print(temperature[i]);
    if(i!=3){
      Serial.print(",");
    }
  }
  Serial.println("");
  Serial.print(F("H:"));
  for (int i = 0; i < 4; i++) {
    Serial.print(humidity[i]);
    if(i!=3){
      Serial.print(",");
    }
    
  }
  Serial.println("");
}

void averaged(float humidity[4],float temperature[4]){
  float tsum=0.0;
  float hsum=0.0;
  float tave=0.0;
  float have=0.0;
  
  for (int i = 0; i < 4; i++) {
    tsum=tsum+temperature[i];
  }
  tave=tsum/4;
  for (int i = 0; i < 4; i++) {
    hsum=hsum+humidity[i];
  }
  have=hsum/4;
  
  Serial.print(tave);
  Serial.print(",");
  Serial.print(have);
  Serial.println("");
}
void loop() {
//  readFromDHT
  for (int i = 0; i < 4; i++) {
    temperature[i] = dht[i].readTemperature();
    humidity[i] = dht[i].readHumidity();
  }
  
//  loopTable(humidity, temperature);
//  thruSerial(humidity, temperature);
  averaged(humidity, temperature);
  
  int ldr = analogRead(A0);
  float ldr_volt = ldr * (5.0 / 1023.0);
  Serial.println(ldr_volt);

  int temp1 = analogRead(A1);
  float temp1_volt = temp1 * (5.0 / 1023.0);
  Serial.println(temp1_volt);

  int temp2 = analogRead(A2);
  float temp2_volt = temp2 * (5.0 / 1023.0);
  Serial.println(temp2_volt);
  
  delay(1000);
}
