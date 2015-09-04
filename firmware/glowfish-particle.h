#define GF_ANOMALY_DETECT 1
#define GF_SIGNAL_EXTRACT 2

#include "SparkJson/SparkJson.h"
#include "HttpClient/HttpClient.h"

#define GLOWFISH_IP_STR "api.glowfi.sh"
#define GLOWFISH_IP_INT_TUPLE 130,211,173,55

#define GF_JSON_SIZE (300)
#define GLOWFISH_ERROR (-2)

class GlowfishParticle {
 public:
  GlowfishParticle(void);
  int setupGlowFish();
  int glowfishAnomalyDetected();
  int glowfishPOST(int glowfishEndpointType, const char * jsonBuf, http_header_t * headers);
};
