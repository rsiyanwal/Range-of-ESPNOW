# Range-of-ESPNOW
To evaluate the reliability of the ESP-NOW protocol, we conducted an experiment involving two wireless NodeMCUs communicating with each other. We define the following variables for this experiment:

- NodeMCU A: the controller that transmits data packets
- NodeMCU B: the slave that receives the packets
- Packet size: 250 bytes
- Transmission rate: 100 packets per second
- NodeMCU B is responsible for counting the number of packets received and printing the count every second.

Our experiment tested the reliability of the ESP-NOW protocol in various forest-like areas. We evaluated its performance and limitations in different conditions, from open ground with some trees to a thick forest. The results, shown below, demonstrate the protocol's robustness and usability in our architecture. In open ground with some trees, the protocol's range was up to 115 meters, while in a thick forest, it was around 63 meters.
