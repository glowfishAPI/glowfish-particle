#include "glowfish-particle/glowfish-particle.h"
#include "SparkJson/SparkJson.h"
#include "HttpClient/HttpClient.h"

#define GF_AUTHORIZATION "Basic <Base 64 encoding of your glowfi.sh username and password>"
// If you don't know how to do that, go here: http://www.tuxgraphics.org/toolbox/base64-javascript.html

#define N_POINTS 100

http_header_t headers [] = {
  { "Content-Type", "application/json" },
  { "Accept" , "*/*"},
  { "Authorization", GF_AUTHORIZATION},
  { NULL, NULL } // NOTE: Always terminate headers will NULL
};

// A 100 point Sine Wave
float g_sine [N_POINTS] = {0.0, 0.063, 0.125, 0.187, 0.249, 0.309, 0.368, 0.426, 0.482, 0.536, 0.588, 0.637, 0.685, 0.729, 0.771, 0.809, 0.844, 0.876, 0.905, 0.93, 0.951, 0.969, 0.982, 0.992, 0.998, 1.0, 0.998, 0.992, 0.982, 0.969, 0.951, 0.93, 0.905, 0.876, 0.844, 0.809, 0.771, 0.729, 0.685, 0.637, 0.588, 0.536, 0.482, 0.426, 0.368, 0.309, 0.249, 0.187, 0.125, 0.063, 0.0, -0.063, -0.125, -0.187, -0.249, -0.309, -0.368, -0.426, -0.482, -0.536, -0.588, -0.637, -0.685, -0.729, -0.771, -0.809, -0.844, -0.876, -0.905, -0.93, -0.951, -0.969, -0.982, -0.992, -0.998, -1.0, -0.998, -0.992, -0.982, -0.969, -0.951, -0.93, -0.905, -0.876, -0.844, -0.809, -0.771, -0.729, -0.685, -0.637, -0.588, -0.536, -0.482, -0.426, -0.368, -0.309, -0.249, -0.187, -0.125, -0.063};
unsigned int g_sine_i = 0, g_cos_i = N_POINTS/4;

GlowfishParticle gf;

int anomalyLed = D7;
int heartbeatLed = D7;
unsigned int nextTime = 0;    // Next time to contact the server

void setup() {
  pinMode(anomalyLed, OUTPUT);
  gf.setupGlowFish();
}

void loop() {
  if (nextTime > millis()) return;
  StaticJsonBuffer<GF_JSON_SIZE> glowfishJson;
  JsonObject& top = glowfishJson.createObject();
  JsonObject& data_set = top.createNestedObject("data_set");
  // TODO: I don't quite understand how much memory needs to get allocated
  //JsonObject& time = top.createNestedArray("time");
  JsonArray& temp = data_set.createNestedArray("temp");
  temp.add(g_sine[g_sine_i]);
  JsonArray& humid = data_set.createNestedArray("humidity");
  humid.add(g_sine[g_cos_i]);
  JsonArray& signal = data_set.createNestedArray("wifi");
  signal.add(2*g_sine[g_sine_i]*g_sine[g_cos_i]);
  g_sine_i = (g_sine_i + 1) % N_POINTS;
  g_cos_i = (g_cos_i + 1) % N_POINTS;

  int status;

  //time.add();

  char jsonBuf[GF_JSON_SIZE];
  top.printTo(jsonBuf, sizeof(jsonBuf));

    #ifdef LOGGING
  Serial.println(jsonBuf);
    #endif

  status = gf.glowfishPOST(GF_SIGNAL_EXTRACT, jsonBuf, headers);
  if (status == 200) {
    digitalWrite(heartbeatLed, HIGH);
    delay(250);
    digitalWrite(heartbeatLed, LOW);
  }

  status = gf.glowfishPOST(GF_ANOMALY_DETECT, jsonBuf, headers);
  if (status == 200) {
    digitalWrite(heartbeatLed, HIGH);
    delay(250);
    digitalWrite(heartbeatLed, LOW);
  }

  int anomaly_detected = gf.glowfishAnomalyDetected();
  if (anomaly_detected > 0) {
    digitalWrite(anomalyLed, HIGH);
    delay(500);
    digitalWrite(anomalyLed, LOW);
    delay(500);
    digitalWrite(anomalyLed, HIGH);
    delay(500);
    digitalWrite(anomalyLed, LOW);
  }
  // Set the next real execution to 1 minute after (approx)
  nextTime = millis() + 5000;
}
