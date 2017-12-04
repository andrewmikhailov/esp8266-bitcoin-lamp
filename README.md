# ESP8266 Bitcoin Lamp
This project written on C++/Arduino demonstrates basic ESP8266 microcontroller capabilities:
  - Digital I/O;
  - HTTP/HTTPS requests;
  - PWM;
  - JSON parsing;
  - REST API client;
  - WiFi client;
  - Minor stand-by.

The idea was to create something very basic but still useful. This device goes to the Bitcoin exchange's REST API, downloads the rate change history for the most recent week and displays a lamp depending on the rate change.
When Bitcoin was growing much during the last week - the green lamp is shining brightly, when Bitcoin was falling much - the red lamp is shining brightly. The lamp is not bright for minor fluctuations. It is fun and it is magic. Everyone needs such a lamp in his room.
