// make sure to include with Particle IDE the SparkJson, onewire, and dallas-temperature libraries 
// as described in main README.md

DallasTemperature dallas(new OneWire(D2));

int photoResistor = A0;
int photoPower = A5;
int heartbeatLed = D7;
int anomalyLed = D0;

void setup()
{
  dallas.begin();
  pinMode(photoResistor,INPUT);
  pinMode(heartbeatLed, OUTPUT);
  pinMode(anomalyLed, OUTPUT);
  pinMode(photoPower, OUTPUT);
  digitalWrite(photoPower, HIGH);
  Spark.subscribe("hook-response/glowfish_example", myHandler, MY_DEVICES);
}

void loop()
{
  dallas.requestTemperatures();
  float fahr = dallas.getTempFByIndex( 0 );
  String s_fahr(fahr, 1);
  int wifi = WiFi.RSSI();
  String s_wifi = String(wifi);
  int photo = analogRead(photoResistor);
  String s_photo = String(photo);
  Spark.publish("glowfish_example","{\"temp\":"+ s_fahr + ",\"photo\":"+s_photo+",\"wifi\":" + s_wifi + "}" ,60, PUBLIC);
  delay(5000);
}

void myHandler(const char *event, const char *data)
{
  //show heartbeat for hook-response on blue led
  digitalWrite(heartbeatLed, HIGH);
  delay(250);
  digitalWrite(heartbeatLed, LOW);

  //non const required by AduinoJson specs
  int len = strlen(data);
  char dataCopy[len+1];
  strcpy(dataCopy,data);

  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(dataCopy);
  if (root.success() && root.containsKey("result"))
  {
    JsonObject& result = root["result"];
    if (result.containsKey("anomaly_predictions")) 
    {
      boolean anomaly_detected = result["anomaly_predictions"][0];
      if (anomaly_detected) {
        digitalWrite(anomalyLed, HIGH);
        delay(1500);
        digitalWrite(anomalyLed, LOW);
      }
    }    
  }
}
