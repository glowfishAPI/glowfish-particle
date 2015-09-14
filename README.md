# glowfi.sh for Particle.io Devices

The code here facilitates integration between glowfish and Particle.io devices.  Currently this repo consists of two parts. The first and main piece is a library that provides direct HTTP connectivity to glowfi.sh API endpoints. This library adheres to the Particle library spec, and thus easily importable in the web IDE. The second part of the repo is a webhook example for anomaly detection.

Please note this code has only been tested using the Photon.
 
## glowfish-particle Library

The library provides the ability to connect directly to the glowfi.sh API via HTTP calls instead of using Particle Cloud's pub/sub messaging system.  While Particle Cloud provides a powerful ecosystem for interaction among various agents, this library can prove a conventient way of POSTing the data directly when some constraints such as rate limits, payload size limits, etc. need to be avoided. 

The sample application in *firmware/examples/test-glowfish-post/anomaly-detect-post.cpp* shows how to use the library, using our *anomaly_detect* endpoint as the example. Please see the comments at the top of *anomaly-detect-post.cpp* for more implementation details.Currently, the other supported endpoints in this library are *signal_extract*, *train*, and *predict*.  

Please note that *anomaly-detect-post.cpp* relies on three libraries: SparkJson, HttpClient, and glowfish-particle.  If using the web IDE - you can import SparkJson and HttpClient via the Community Library listing's "Include in App" button.  glowfish-particle is not listed yet in Community Libraries, so you will need to use the "Contribute Library" and this repo's github url: *glowfishAPI/glowfish-particle*. For more info on how to do this, please see the [Contribute Library](https://docs.particle.io/guide/getting-started/build/photon/#contribute-a-library) section of Particle's user guide.

## Webhook Example

In the folder *firmware/examples/anomaly-detect-webhook* we provide example webhook json and an application to accomplish a simple glowfish integration via the Particle Cloud.  Note that the two files contained in this folder are self contained, and do not rely on the rest of the glowfish-particle library to be imported. For more info, please see [the README file located in that folder](https://github.com/glowfishAPI/glowfish-particle/tree/master/firmware/examples/anomaly-detect-webhook). 

 




