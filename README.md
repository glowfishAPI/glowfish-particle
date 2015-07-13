# glowfi.sh for Particle.io Devices

This library facilitates integration between glowfish and particle.io devices.  Currently, the library consists of only a simple (yet powerful!) anomaly detection webhook example, but the folder structure adheres to [the valid library spec defined by Particle.io](https://github.com/spark/uber-library-example) so that as we do add more firmware functionality, we don't break links and make people sad.

## Real-time Multivariate Anomaly Detection by Webhook

For this example, the anomaly detection endpoint of glowfi.sh is used to do real-time detection of statistical signal anomalies in multi-sensor device event data of the Photon. Every 5 seconds, JSON data from three sensors (temperature, photoresistor, and wifi signal strength) is sent in one event via Spark.publish() from the Photon.  A webhook listens in for this event, and posts the data to the anomaly_detect endpoint of the glowfi.sh HTTP API.  The Photon listens to the response by using Spark.subscribe on the hook-response. The Photon handler parses the response data, and if the data was deemed anamalous the device will blink an LED. Yup that's right, this is real-time multivariate anomaly detection on device with just a simple publish and subscribe. A video will be posted shortly to show the particular set up that worked for this code.

anomaly-detect-webhook.ino contains the example code for app in the Particle IDE.  You will need to include three libraries: SparkJson, particle-dallas-temperature, and particle-dallas-onewire. SparkJson is available via the public library search in the IDE. I had issues with the SPARK-DALLAS-TEMPERATURE ane ONEWIRE public libraries in the IDE for my DS18b20, so I grabbed the particle-dallas-temperature and particle-dallas-onewire created by crodriguez, explained [here](https://community.particle.io/t/ds18b20-working-example/8068/20). Thanks crodriguez.

anomaly-detect-webhook.json contains the json to be used when [registering your Particle webhook](http://docs.particle.io/photon/webhooks/). You will need to replace "username1" and "password1" with your Auth Key and Auth Secret Key, respectively, for your glowfish application given in the [glowfish admin](https://api.glowfi.sh/admin/app/). If you do not have access yet to glowfi.sh, please sign up [here](https://glowfi.sh/beta/).

Please note this has only been tested using the Photon and the sensors included in the Particle Maker kit.





