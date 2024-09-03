#include <WiFiServer.h>
#include <DHT.h>

#define BLYNK_PRINT Serial



#define BLYNK_TEMPLATE_ID "TMPL4xc13YJ8"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "Ws9O84JdueJTXX4cARv2WQEgwLBMsCMo"
char auth[] = "Ws9O84JdueJTXX4cARv2WQEgwLBMsCMo";
char ssid[] = "POCOX3"; //Enter your WIFI name
char pass[] = "ninad@123"; //Enter your WIFI passowrd

#define buzzer D5
#define rled D0
#define gled D1
BlynkTimer timer;
int smokeA0 = A0;


DHT dht(D4, DHT11);




void setup() {

  Serial.begin(115200);



  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);



  dht.begin();



  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);


}




void loop() {
  Blynk.run();
  timer.run();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(t);
  Blynk.virtualWrite(V0, t);
  Serial.print("Humidity: ");
  Blynk.virtualWrite(V1, h);
  Serial.println(h);



  int sensorReading = analogRead(A0);
  Serial.println("test");
  Serial.println(sensorReading);

  if (sensorReading > 400) {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    Blynk.virtualWrite(V2, "Fruit is spoiled ");
    Blynk.notify("Fruit is spoiled ") ;
    Serial.println("Smoke detected");
    digitalWrite(rled, HIGH);
    digitalWrite(gled, LOW);



  } else {
    Blynk.virtualWrite(V2, "Fruit is fresh ");
    digitalWrite(rled, LOW);
    digitalWrite(gled, HIGH);
  }
}
