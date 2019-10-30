![](/img/example.gif "An remote and a smartphone both working with HomeKit")

**For this project you will need the following:**

- A computer capable of running a Node-RED instance (Raspberry,  Orange π, Mac/PC/Linux) with these nodes:
    - Mosca MQTT Broker
    - node-red-contrib-homekit-bridged
- A set of Wireless Remote Control Outlets, supported by the RC-Switch library like these:

![](/img/outlets.example.png "Some Outlets and their remotes") (I have two models from etekcity and SCS both work fine)

- A wi-fi microcontroller like the ESP8266 or ESP32
- A couple of 433 mhz transmitter and receiver

**HARDWARE**

The microcontroller schematic is basically four cables. Take care to leave some space between the two antennas to avoid interferences. Custom antennas could give you some extra-range, outlets in a 6/7 meters range are perfectly reachable.

![](/img/schematic.example.png "A schematics example")


**SOFTWARE**

For this to work you just need to install Node-RED and start it on boot. You can find an example of an outlet flow [here](/node-red/flow.json). You will need one of there for every outlet you'll use.

![](/img/node_red.example.png "A schematics example")


**Remote Flow**

The workflow is quite straight, here what happens when you use your remote:

The microcontroller listens the 433Mhz frequence for a code that corresponds to one of your outlets and if it founds one it sends an MQTT message on the corresponding topic. Example:

"0FF00FFF0101" sends "On" to "lights/zap1/setState"

"0FF00FFF0110" sends "Off" to "lights/zap1/setState"


The MQTT broker then forwards the same message to the homebridge node that changes the value in your HomeKit app. Now Siri knows that the outlet is on.

**HomeKit Flow**

Same as above, but now is the Node-RED flow that sends the homebridge value (say 'On') to the right outlet topic like "lights/zap1/setState". The microcontroller gets the message and sends the corresponding code ("0FF00FFF0101" in this case) with its 433Mhz transmitter. The outlet turns on.