# Environment Monitoring & Watering Control System using ESP32 and MQTT 

<p align="justify">
An MQTT-powered system with real-time sensor data monitoring, state evaluation, actuator control, and continuous data logging. This project aims to explore the MQTT protocol, using it to enable communication between devices and services for actuator control and real-time monitoring.
</p>

<p align="justify">
The system is inspired by the automated control of a greenhouse used for growing plants and vegetables. Different sensors and actuators are employed to create two independent control sections that together make up the complete system:
</p>


## Features

<p align="justify">
The control mode is selected in Node-RED as either <b>Automatic</b> or <b>Manual</b>, with the ESP32 controlling the fan and pump accordingly. In Manual Mode, the user directly operates the actuators, while in Automatic Mode, their operation is determined by the evaluation of the system variables. Simultaneously, system data is published via MQTT and distributed by the broker to the ESP32 and Node-RED. Node-RED stores the received data in InfluxDB, which is used by Grafana to generate the monitoring dashboard. If the pump is set to operate while the tank water level is too low, an alarm banner is displayed on the Node-RED dashboard.

</p>

<!---insert project overview diagram--->


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

## MQTT TOPICS

## Node-RED LOGIC

### Data Preparation 

### Node-RED --> InfluxDB

### Alarms

## GRAFANA

<p align="justify">
JUST EXPLAIN THE FLUX INSTRUCTIONS USED TO GATHER THE DATA
</p>

## MEDIA

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