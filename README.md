# Environment Monitoring & Watering Control System using ESP32 and MQTT 

<p align="justify">
An MQTT-powered system with real-time sensor data monitoring, state evaluation, actuator control, and continuous data logging. This project aims to explore the MQTT protocol, using it to enable communication between devices and services for actuator control and real-time monitoring.
</p>

<p align="justify">
The system is inspired by the automated control of a greenhouse used for growing plants and vegetables. Different sensors and actuators are employed to create two independent control sections that together make up the complete system:
</p>

<p align="center">
<img src= "media\Station-division.png" alt="station_divisions" style="height::300px; width:400px;"/>
</p>



## Features

<p align="justify">
The control mode is selected in Node-RED as either <b>Automatic</b> or <b>Manual</b>, with the ESP32 controlling the fan and pump accordingly. In Manual Mode, the user directly operates the actuators, while in Automatic Mode, their operation is determined by the evaluation of the system variables. Simultaneously, system data is published via MQTT and distributed by the broker to the ESP32 and Node-RED. Node-RED stores the received data in InfluxDB, which is used by Grafana to generate the monitoring dashboard. If the pump is set to operate while the tank water level is too low, an alarm banner is displayed on the Node-RED dashboard.

</p>

<p align="center">
<img src= "media\project_2_overview.svg" alt="project_overview" style="height::400px; width:600px;"/>
</p>

## Setup
### Hardware

<div style="text-align: justify">

- B10K Potentiometer

- LM35 Temperature Sensor

- CDS Photoresistor

- IRLZ44N Mosfet

- 2N2222A Transistor

- 1N4001 Diode (x3)

- DHT22 Sensor Module

- SEN0205 Level Sensor

- 3V-6V DC Type 130 Micro DC Motor

- Relay Module JQC-3FF-S-Z

- MH Soil Moisture Level Sensor Module

- ESP32 WROOM-32

- RASPBERRY PI ZERO WH 

- Power Source 

</div>

### Software

<div style="text-align: justify">

- DOCKER: Node-Red, InfluxDB, Grafana
- Eclipse Mosquitto Broker 
- IDE (PlatformIO)

## Project Electrical Schematics
<p align="center">
<img src= "media\MQTT_PROJ.svg" alt="schematics" style="height::400px; width:500px;"/>
</p>

<p align="justify">
The following paragraphs explain the rationale behind the design choices and mounting considerations for some of the key components shown in the electrical schematics.
</p>

<p align="justify">
To measure temperature, while the DHT22 could also have been used,  to diversify the components used, a dedicated sensor , the LM35 , was chosen for it.
The LM35 is capable of measuring both positive and negative temperatures, producing an output voltage proportional to temperature according to the datasheet (Texas Instruments):

<b>

```
VOUT = 10 mV/°C × T
```

</b>

</p>

<p align="justify">
Since the ESP32's ADC cannot measure negative voltages, to overcome this limitation the LM35's GND pin was raised using two diodes in series, shifting the entire output range upward. A resistor was added to the Vout pin to provide a current path that keeps the diodes forward biased, ensuring a stable offset voltage.
</p>

<p align="justify">
As a result, the LM35 outputs approximately 0.87 V at 0 °C  (the measured voltage drop across the two diodes) instead of 0 V. This leaves room for temperatures below 0 °C to be represented as positive voltages that can be safely measured by the ESP32, effectively enabling the LM35's full temperature measurement range.
</p>


<p align="justify">
The DC motor is controlled using a MOSFET because an ESP32 GPIO pin cannot supply enough current to drive the motor directly. Although this project uses a small DC motor, driving an inductive load directly from a microcontroller pin is considered poor design practice. Instead, the MOSFET acts as an electronic switch, allowing the motor to be powered safely from an external supply while being controlled by the ESP32.
</p>


<p align="justify">
A flyback diode was connected across the motor to protect the MOSFET from the high voltage spike (back electromotive force, or back EMF) generated when the motor stops running. This also helps protect the ESP32 and improves the reliability of the circuit.
</p>



## MQTT TOPICS

<p align="justify">
Regarding the data published by the ESP32, instead of using a separate MQTT topic for each variable, all measurements (and the exact same process for the status of the actuators) were grouped into a single JSON payload using the <b>"ArduinoJson"</b> library. The MQTT topic serves only as the message address, while the JSON payload contains all the data in a single transmission, resulting in a cleaner and more efficient communication structure.
</p>



<p align="justify">
In this project, Node-RED subscribes to that topic and receives the complete JSON message. The payload is then automatically parsed into a JavaScript object, allowing individual values to be accessed easily through their corresponding properties <b> (e.g., msg.payload.temperature or msg.payload.humidity).
</b></p>


<p align="center">
<img src= "media\mqtt_topics.svg" alt="mqtt_topics" style="height::300px; width:600px;"/>
</p>

## ESP32 MQTT CONFIGURATION

<p align="justify">
To connect as a client the following parameters were set in the client connect function in the <b>“PubSubClient”</B> library:
</p>


<p align="justify">

boolean <b>connect</b> (clientID, [username, password], [willTopic, willQoS, willRetain, willMessage], [cleanSession])</p>
<p align="justify">
<b> Parameters </b>
</p>



<p align="justify"> <b>• clientID, </b> <i>const char[]</i> : esp32_1, the client ID to use when connecting to the server
</p>


<p align="justify">
<b>• Credentials </b>
</p>

<div style="text-align: justify">

- <b>username,</b> <i>const char[]</i> : the username used.
</div>


<div style="text-align: justify">

- <b>password,</b> <i>const char[]</i> : the username used.
</div>


<p align="justify">
<b>• Will</b>
</p>
<div style="text-align: justify">

<div style="text-align: justify">

- <b>willTopic,</b> <i>const char[]</i> : status/connection,  the topic to be used by the will message.
</div>

<div style="text-align: justify">

- <b>willQoS, </b> <i>int: 0,1 or 2 </i> : 1
</div>

<div style="text-align: justify">

- <b>willRetain, </b> <i>boolean</i> : true,  the will message should be published with the retain flag.
</div>

<div style="text-align: justify">

- <b>willMessage,</b> <i>const char[]</i> : “esp32 offline” , the payload of the will message.
</div>

<p align="justify">
<b>• cleanSession,</b> <i>boolean</i>: false, making sure every message of the client  is delivered, isn’t forgotten by the broker when disconnected.</p>


## Node-RED LOGIC

<p align="justify">
The <b>“ArduinoJson”</b> library serializes the data into a JSON string, which is then transmitted via MQTT. In Node-RED, the MQTT In node (configured to Auto-Detect) recognizes the JSON payload and automatically parses it into a JavaScript object. As a result, individual values can be accessed using dot notation <b>(e.g., msg.payload.pump and msg.payload.motor).</b>
</p>


<p align="justify">
The alarm logic begins with a dashboard button whose state is stored in the global flow variable <b>´ackValue´</b>. A Function node is employed to then evaluate this variable together with the values of the <b>´pump_alarm_manual´ and  ´pump_alarm_auto´</b> payloads. Based on these inputs, it determines the appropriate output for the Template node, either displaying an alarm message, displaying no alarm message, or hiding the alarm after it has been acknowledged by the user.
</p>


### Node-RED → InfluxDB

<p align="justify">
InfluxDB provides a native <b>HTTP Write API</b>. Since the available Node-RED nodes do not support the  version of  InfluxDB used in this project (version 3), data was written from Node-RED to InfluxDB by sending HTTP POST requests to the <b><i>/api/v2/write endpoint.</i></b> 
</p>

<p align="center">
<img src= "media\node_influx_flowchart.svg" alt="node_red_influx_flow" style="height::300px; width:400px;"/>
</p>

## GRAFANA

<p align="justify">
There are two buckets setup in InfluxDB:   "Env_Data_Monitor" and  "Watering_Monitor" . Each bucket is used to record the following data:
</p>

<p align="justify">
<b>Env_Data_Monitor</b> → temperature, air humidity, ambient light, fan status, control mode
</p>

<p align="justify">
<b>Watering_Monitor</b> → write soil humidity, tank level, pump status, control mode
</p>


<p align="justify">
To retrieve data from the buckets, when a field contains a string, the Flux query follows the logic shown below:
</p>

```
from(bucket: "Watering_Monitor")
  |> range(start: v.timeRangeStart, stop: v.timeRangeStop)
  |> filter(fn: (r) => r["_field"] == "soil_humidity")

```

<p align="justify">
In contrast, to retrieve data from the buckets, when a field contains numerical data, the Flux query follows the logic shown below:
</p>

```
from(bucket: "Env_Data_Monitor")
  |> range(start: v.timeRangeStart, stop: v.timeRangeStop)
  |> filter(fn: (r) => r["_field"] == "temperature")
  |> aggregateWindow(every: 5s, fn: last, createEmpty: false)
  |> yield(name: "last")

```


## MEDIA

![](/media/fan_auto_mode.gif)


![](/media/pump_operation.gif)



## IMPROVEMENTS 


<p align="justify">

<b>TLS Encryption:</b> Username and password authentication stops unauthorized clients from connecting, but it doesn't protect the data itself. Anyone on the same Wi-Fi could intercept and read that traffic. To prevent this, TLS encryption must be enabled. This involves generating certificates (or using a free service) and pointing to them in the configuration file. This closes the gap between "authenticated" and "actually secure."

</p>

<p align="justify">

<b>Two-Way Alarm Acknowledgement:</b>
Right now, acknowledging an alarm only updates the dashboard, there is no message being sent to the other components of the system. A proper fix sends an acknowledgement message back to ESP32, so the alarm state clears at the source instead of persisting indefinitely after it's been handled.</p>


<p align="justify">

<b>Logging Alarm Events to a Database:</b> By storing each alarm trigger as a database entry, isolated events become a dataset that can later be analyzed to identify recurring patterns and alarm frequency, particularly in more complex systems.</p>


<p align="justify">

<b>Analog Over Digital Sensing:</b> A digital water level sensor only indicates whether water is present or absent. Using an analog water level sensor instead would provide continuous measurements, enabling more nuanced conditions, smarter evaluations, and more meaningful monitoring.</p>



<p align="justify">

<b>Error Handling:</b> The system currently relies on the ESP32's reconnect loop, feedback check when Node-RED writes to InfluxDB and Node-Red debug nodes to observe received messages, which, although minimal, provides a functional level of error detection. As more sensors and actuators are added, identifying faulty behaviour becomes increasingly difficult without a clear baseline. Defining expected value ranges for each sensor during isolated testing and flagging out-of-range readings through the serial monitor or Node-RED's Debug panel would make troubleshooting faster and less reliant on guesswork.</p>