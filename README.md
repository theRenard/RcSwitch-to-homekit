## Two way communication between your 🔌 remote control outlets and 🍎HomeKit ##

Use your remote as usual, control your outlets even without Siri around and get all the benefits of Homekit services.

![](/img/example.gif "An remote and a smartphone both working with HomeKit")

For this project you will need:

- A computer capable of running a Node-RED instance (Raspberry,  Orange π, Mac/PC/Linux).
- A set of Wireless Remote Control Outlets, supported by the RC-Switch library like these:

![](/img/outlets.example.jpg "Some Outlets and their remotes") (I have two models from etekcity and SCS both work fine)

- A wi-fi enabled microcontroller like the ESP8266 or ESP32
- A couple of 433 mhz transmitter and receiver
- PlatformIO or Arduino IDE to edit, compile and upload this project to your microcontroller.

### HARDWARE ###

The microcontroller schematic is really basic. Just connect the receiver and the transmitter to the microcontroller with both data and power. I've used GPIO D1 for the emitter and D3 for the transmitter.

![](/img/schematic.example.png "A schematics example")

This is how mine looks like once assembled, I've used a wemos D1 in an old can, powered by its own usb port. Take care to leave some space between the two antennas to avoid interferences. Custom antennas could give you some extra-range, outlets in a 6/7 meters range are perfectly reachable.

![](/img/microcontroller.example.jpeg "A schematics example")


### SOFTWARE ###

**Node-Red**

For this to work you just need to install Node-RED and  and start it on boot. You can find an example of an outlet flow [here](/node-red/flow.json), you can use it as a starting point . You will need one of this flow for every outlet you'll use.

![](/img/node_red.example.png "A schematics example")

**Microcontroller**

I've used Wi-Fi Manager library to have a better control over the the Wi-Fi module and RC-Switch to get and set the messages over the 433Mhz frequence, PubSubClient library and ArduinoJson parse and send messages over MQTT protocol to Node-RED.

**Remote Flow**

The workflow is quite straight, here what happens when you use your remote:

The microcontroller listens the 433Mhz frequence for a code that corresponds to one of your outlets and if it founds one it sends an MQTT message on the corresponding topic. Example:

"0FF00FFF0101" sends "On" to "lights/zap1/setState"

"0FF00FFF0110" sends "Off" to "lights/zap1/setState"


The MQTT broker then forwards the same message to the homebridge node that changes the value in your HomeKit app. Now Siri knows that the outlet is on.

**HomeKit Flow**

Same as above, but now is the Node-RED flow that sends the homebridge value (say 'On') to the right outlet topic like "lights/zap1/setState". The microcontroller gets the message and sends the corresponding code ("0FF00FFF0101" in this case) with its 433Mhz transmitter. The outlet turns on.

**PlatformIO**

Please modify the platformio.ini file according to your board and your serial port.