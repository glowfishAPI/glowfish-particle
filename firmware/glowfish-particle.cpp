#include "glowfish-particle.h"
#include "HttpClient/HttpClient.h"

HttpClient http;
// Headers currently need to be set at init, useful for API keys etc.
http_request_t request;
http_response_t response;

GlowfishParticle::GlowfishParticle() {
}

// TODO? Implement reset_model?

int GlowfishParticle::glowfishPOST(int glowfishEndpointType, const char * jsonBuf, http_header_t * headers) {
  if (glowfishEndpointType == GF_ANOMALY_DETECT)
    request.path = "/v1/anomaly_detect/";
  else if (glowfishEndpointType == GF_SIGNAL_EXTRACT)
    request.path = "/v1/signal_extract/";
  else
    return GLOWFISH_ERROR;
  request.body = jsonBuf;
  http.post(request, response, headers);

  #ifdef LOGGING
  Serial.print("Application>\tResponse status: ");
  Serial.println(response.status);

  Serial.print("Application>\tHTTP Response Body: ");
  Serial.println(response.body);
  #endif

  return response.status;
}

int GlowfishParticle::glowfishAnomalyDetected () {
  // Make a copy as response.body is const and it's not compatible with parseObject
  int len = strlen(response.body);
  char dataCopy[len+1];
  strcpy(dataCopy, response.body);

  // Blink an led 2 times if anomaly was found otherwise continue
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(dataCopy);

  if (root.success() && root.containsKey("result")) {
    JsonObject& result = root["result"];
    if (result.containsKey("anomaly_predictions"))
      return (int) result["anomaly_predictions"][0];
    else return 0;
  }
}


int GlowfishParticle::setupGlowFish() {
  request.hostname = GLOWFISH_IP_STR;
  request.ip = IPAddress(GLOWFISH_IP_INT_TUPLE);
  request.port = 80;
  return 1;
}
