# MQTT Image Client for ESP32

[![C++](https://img.shields.io/badge/C++-ESP32-blue?logo=cplusplus&logoColor=white)](https://www.arduino.cc/)
[![Protocol](https://img.shields.io/badge/Protocol-MQTT-660066?logo=eclipse-mosquitto&logoColor=white)]()
[![Platform](https://img.shields.io/badge/Platform-ESP32-E7352C)]()
[![License](https://img.shields.io/badge/License-GPL--3.0-green)](LICENSE)

An embedded MQTT client running on an **ESP32** microcontroller that stores an image in the device filesystem (SPIFFS) and transmits it over MQTT publish/subscribe to a broker. Useful as a base template for IoT edge devices that need to push binary or image payloads over a lightweight protocol.

---

## What it does

The ESP32 connects to a Wi-Fi network, mounts its internal SPIFFS filesystem, reads a pre-loaded image file, and publishes it as a binary payload to a configured MQTT topic. 

```
ESP32 (SPIFFS image) ── MQTT pub ──► Broker ── MQTT sub ──► Any subscriber (dashboard, server, cloud)
```

---

## Hardware requirements

- ESP32 development board (any variant with Wi-Fi)
- Arduino IDE 1.8.18 (required for ESP32 Sketch Data Upload plugin)
- [ESP32FS plugin](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/) installed in the Arduino IDE

---

## Project structure

```
mqtt_client/
├── data/               ← Place your image here before uploading to SPIFFS
│   └── image.jpg
├── mqtt_Client.ino     ← Main sketch
└── README.md
```

---

## Configuration

Open `mqtt_Client.ino` and fill in your credentials before flashing:

```cpp
// Wi-Fi
const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// MQTT broker
const char* mqttServer = "192.168.x.x";     // IP of your broker
const uint16_t mqttPort = 1883;              // Default non-TLS port
const char* mqttTopic = "esp32/image";       // Topic to publish to

// Image filename (must match the file you uploaded to SPIFFS)
sendImage("image.jpg");
```

---

## SPIFFS image upload — step by step

1. Install the [ESP32FS plugin](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/) by placing the `.jar` inside `~/Arduino/tools/ESP32FS/tool/`
2. Create a `data/` folder inside your sketch directory
3. Place your image inside `data/`
4. In Arduino IDE: **Tools → ESP32 Sketch Data Upload**
5. Flash the sketch normally

The image must be uploaded to SPIFFS before the sketch runs — the device reads it from local storage at boot.

---

## Topics

`esp32` `mqtt` `iot` `embedded` `c-plus-plus` `raspberry-pi` `arduino` `spiffs` `edge-computing`
