# ESP32_AWS_IoT_skeleton
A end to end skeleton on IoT with ESP32 and AWS IoT core. Two way communication via MQTT. ESP32 firmware and AWS lambda for device connectivity logging in DynamoDB. This project enables connectivity to ESP32 to enable and disable a GPIO pin which is connected to a in-build LED on the board via MQTT. This physical pin can be further attached to a relay to controll home/industrial appliances.

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

A IoT based simple controller system using ESP32 via MQTT. 

- ESP32
- MQTT
- ✨Magic ✨

## ESP32
[ESP32](https://www.espressif.com/en/products/socs/esp32) series are Powerful Wi-Fi+Bluetooth/Bluetooth LE modules that target a wide variety of AIoT applications, ranging from low-power sensor networks to the most demanding tasks. In this, esp32 devkit v1 is used as the IoT device since it is a qualified IoT hardware by [AWS IoT Platform](https://devices.amazonaws.com/detail/a3G0h0000077nRtEAI/ESP32-WROOM-32SE)

| Hadwared | Specs |
| ------ | ------ |
| Number of cores | 2 (dual core) |
| Wi-Fi | 2.4 GHz up to 150 Mbits/s |
| Bluetooth | BLE (Bluetooth Low Energy) and legacy Bluetooth |
| Architecture | 32 bits |
| Clock frequency | Up to 240 MHz |
| RAM | 512 KB |
| Peripherals | Capacitive touch, ADC (analog to digital converter), DAC (digital to analog converter), I2C (Inter-Integrated Circuit), UART (universal asynchronous receiver/transmitter), CAN 2.0 (Controller Area Netwokr), SPI (Serial Peripheral Interface), I2S (Integrated Inter-IC Sound), RMII (Reduced Media-Independent Interface), PWM (pulse width modulation) |

## MQTT
[MQTT](https://mqtt.org/) is an OASIS standard messaging protocol for the Internet of Things (IoT). It is designed as an extremely lightweight publish/subscribe messaging transport that is ideal for connecting remote devices with a small code footprint and minimal network bandwidth.

Here [AWS IoT Core](https://aws.amazon.com/iot-core/) is used as the MQTT broker since it secures device connections and data with mutual authentication and end-to-end encryption

## ✨Magic ✨
### Device and Firmware setup
- Download and install [Arduino IDE](https://www.arduino.cc/en/software)
- clone the repo.
- [Install ESP32 board](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) in Arduino.
- Install MQTTClient,ArduinoJson [from library manager](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)
- Create a AWS account and navigate to [AWS IoT core](https://us-east-1.console.aws.amazon.com/iot/home)
- [Create a thing](https://docs.aws.amazon.com/iot/latest/developerguide/iot-moisture-create-thing.html) and download the device certificates.
- Connect the device, Open the folder ESP32_Firmware in Arduino
- Open secrets.h and:
    - Enter SSID and password of your wifi network
    - Give your thing a name
    - Replace the certificates with downloaded certificates
- Connect the device and flash the firmware
- Open terminal to see the connectivity status of the device

### AWS lambda for capturing events(optional)
AWS IoT core has [lifecycle events](https://docs.aws.amazon.com/iot/latest/developerguide/life-cycle-events.html) which can be usefull to know the connectivity of the device (connected/disconnected). Further this can be sent to [AWS lambda](https://aws.amazon.com/lambda/) service where these events can be processed or logged into database. Here the trigger is set si that it logs each devices connectivity status to [DynamoDB](https://aws.amazon.com/dynamodb/).

- To set this up, Create a new lambda function with python3.9.
- Go to [Device rules](https://us-east-1.console.aws.amazon.com/iot/home?region=us-east-1#/rulehub).
- create a rule and set trigger to your lambda service.
- Go to dynamoDB and create a db.
- Open the folder AWS_lambda_events and paste the code to your lambda service.
