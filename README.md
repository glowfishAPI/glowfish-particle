# glowfi.sh for Particle.io Devices

This library facilitates integration between glowfish and particle.io devices.  Currently, the library consists of only a simple (yet powerful!) anomaly detection webhook example, but the folder structure adheres to [the valid library spec defined by Particle.io](https://github.com/spark/uber-library-example). So, as we add more functionality we don't need to move folders, break links, and make people sad.

## Real-time Multivariate Anomaly Detection by Webhook

For this example, the anomaly detection endpoint of glowfi.sh is used to do real-time detection of statistical signal anomalies in multi-sensor device event data of the Photon. Every 5 seconds, JSON data from three sensors (temperature, photoresistor, and wifi signal strength) is sent in one event via Spark.publish() from the Photon.  A webhook listens in for this event, and posts the data to the anomaly_detect endpoint of the glowfi.sh HTTP API.  The Photon listens to the response by using Spark.subscribe on the hook-response. The Photon handler parses the response data, and if the data was deemed anamalous the device will blink an LED. Yup that's right, this is real-time multivariate anomaly detection on device with just a simple publish and subscribe. Check out [this quick explainer video](https://www.youtube.com/watch?v=zG9-_eCTfFk&feature=youtu.be) to see the example in action.

anomaly-detect-webhook.ino contains the example code for the app in the Particle IDE.  You will need to include three libraries: SparkJson, particle-dallas-temperature, and particle-dallas-onewire. SparkJson is available via the public library search in the IDE. I had issues with the SPARK-DALLAS-TEMPERATURE and ONEWIRE public libraries in the IDE for my DS18b20, so I grabbed the particle-dallas-temperature and particle-dallas-onewire created by crodriguez, explained [here](https://community.particle.io/t/ds18b20-working-example/8068/20).

anomaly-detect-webhook.json contains the json to be used when [registering your Particle webhook](http://docs.particle.io/photon/webhooks/). You will need to replace "username1" and "password1" with your Auth Key and Auth Secret Key, respectively, for your glowfish application given in the [glowfish admin](https://api.glowfi.sh/admin/app/). If you do not have access yet to glowfi.sh, please sign up [here](https://glowfi.sh/beta/).

Please note this has only been tested using the Photon and the sensors included in the Particle Maker kit.

Also note that until a total minimum of 100 events are recieved by the glowfi.sh API, no anomaly detections will be produced. Once the minimum has been reached, anomaly detections will begin. So in this example, it will send data for about 500 seconds before anomaly detections are live. See [the anomaly_detect API doc](http://glowfish.readme.io/docs/anomaly_detect) for more details.

The next step for this example is to subscribe a data visualizer such as librato or ubidots to the hook-response with the anomaly detection data.





