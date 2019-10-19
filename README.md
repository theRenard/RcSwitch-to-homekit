![example](/img/example.gif "example")

```
[
    {
        "id": "385de9b.c4c7a96",
        "type": "homekit-service",
        "z": "abf1ab95.46d11",
        "isParent": true,
        "bridge": "870ebb80.5cee28",
        "parentService": "",
        "name": "Scale",
        "serviceName": "Lightbulb",
        "topic": "",
        "filter": false,
        "manufacturer": "leRenard",
        "model": "Zap",
        "serialNo": "12345737B",
        "characteristicProperties": "",
        "x": 670,
        "y": 240,
        "wires": [
            [
                "a00e4a92.69b9f",
                "151522e4.646405"
            ]
        ]
    },
    {
        "id": "ed4e951a.091f98",
        "type": "mqtt out",
        "z": "abf1ab95.46d11",
        "name": "zap Set State",
        "topic": "lights/zap1/setState",
        "qos": "0",
        "retain": "",
        "broker": "4cfc6208.43ea64",
        "x": 1120,
        "y": 240,
        "wires": []
    },
    {
        "id": "909cdcf0.90f0f",
        "type": "inject",
        "z": "abf1ab95.46d11",
        "name": "Zap On",
        "topic": "",
        "payload": "{\"On\":true}",
        "payloadType": "json",
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "x": 430,
        "y": 180,
        "wires": [
            [
                "385de9b.c4c7a96"
            ]
        ]
    },
    {
        "id": "151522e4.646405",
        "type": "debug",
        "z": "abf1ab95.46d11",
        "name": "",
        "active": false,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "x": 870,
        "y": 180,
        "wires": []
    },
    {
        "id": "babac8c.868f838",
        "type": "mqtt in",
        "z": "abf1ab95.46d11",
        "name": "Zap Get State",
        "topic": "lights/zap1/getState",
        "qos": "0",
        "datatype": "auto",
        "broker": "4cfc6208.43ea64",
        "x": 170,
        "y": 240,
        "wires": [
            [
                "66925df8.888f94"
            ]
        ]
    },
    {
        "id": "64f56124.a3fd8",
        "type": "debug",
        "z": "abf1ab95.46d11",
        "name": "",
        "active": false,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "x": 690,
        "y": 300,
        "wires": []
    },
    {
        "id": "66925df8.888f94",
        "type": "json",
        "z": "abf1ab95.46d11",
        "name": "String to Json",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 440,
        "y": 240,
        "wires": [
            [
                "64f56124.a3fd8",
                "385de9b.c4c7a96"
            ]
        ]
    },
    {
        "id": "a00e4a92.69b9f",
        "type": "switch",
        "z": "abf1ab95.46d11",
        "name": "check hap.context",
        "property": "hap.context",
        "propertyType": "msg",
        "rules": [
            {
                "t": "nnull"
            }
        ],
        "checkall": "true",
        "repair": false,
        "outputs": 1,
        "x": 890,
        "y": 240,
        "wires": [
            [
                "ed4e951a.091f98"
            ]
        ]
    },
    {
        "id": "3c594aff.68731e",
        "type": "inject",
        "z": "abf1ab95.46d11",
        "name": "Zap Off",
        "topic": "",
        "payload": "{\"On\":false}",
        "payloadType": "json",
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "x": 430,
        "y": 300,
        "wires": [
            [
                "385de9b.c4c7a96"
            ]
        ]
    },
    {
        "id": "870ebb80.5cee28",
        "type": "homekit-bridge",
        "z": "",
        "bridgeName": "Homebridge",
        "pinCode": "111-11-111",
        "port": "",
        "allowInsecureRequest": false,
        "manufacturer": "Default Manufacturer",
        "model": "Default Model",
        "serialNo": "Default Serial Number",
        "customMdnsConfig": false,
        "mdnsMulticast": true,
        "mdnsInterface": "",
        "mdnsPort": "",
        "mdnsIp": "",
        "mdnsTtl": "",
        "mdnsLoopback": true,
        "mdnsReuseAddr": true
    },
    {
        "id": "4cfc6208.43ea64",
        "type": "mqtt-broker",
        "z": "",
        "name": "Mosca",
        "broker": "localhost",
        "port": "1883",
        "clientid": "",
        "usetls": false,
        "compatmode": true,
        "keepalive": "60",
        "cleansession": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthRetain": "false",
        "birthPayload": "",
        "closeTopic": "",
        "closeQos": "0",
        "closeRetain": "false",
        "closePayload": "",
        "willTopic": "/light/nuvola/getState",
        "willQos": "0",
        "willRetain": "false",
        "willPayload": "{\"On\":false}"
    }
]
```
