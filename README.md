# Simple MQTT Client for ESP32 using SPIFFS

## Prerequisites

If you use an IDE from Arduino, you need use the latest version allow the feature of **ESP32 Sketch Data Upload**, that its a 1.8.18.

The url you can find it actually is: [PREVIOUS ARDUINO IDE's](https://www.arduino.cc/en/software/OldSoftwareReleases/) 

In other hand, for use the utility, you need to download the *.jar* and include in your IDE. The follow steps explains how to do it:

1. Download the file from [ESP32fs](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/)
2. Find your sketchbook location and create a directory naming *tools*
3. Copy the unzip folder previously download in step one into this folder (create in step 2)
4. Verificate, the finally path from the file is similar to ~/tools/ESP32FS/tool

**It's mandatory follow the structure of path for include the tool into the IDE describe in the previous steps.**

Finally, if you make all the previous steps, if you reload the IDE, in section **Tools**, you should see the feature.

## Using SPIFFS for upload an image to ESP32

For use correctly the tool, you should keep in mind a structure of folders for include the picture you want upload to the microcontroler, so lets see a diagram thats explain how to build your project properly.

![Hirarchy of Memory](https://github.com/user-attachments/assets/2e5b4e27-3671-4640-889c-9f8e0a889fd2)

A short brief of hirarchy in the memory using SPIFFS.

![Structure of Arduino Project](https://github.com/user-attachments/assets/09a1581c-70e7-4fd6-8b66-e5fd89a1cd15)

You need to create a folder with picture named *data* from upload the image using the tools previously you should keep available or installed, like the picture of Structure of Arduino Project.

## A simple program for use a SPIFFS on your ESP32 for upload and transmit an image using MQTT (pub/sub)

The last step, remember to fill in the code your SSID, password, IP of broker MQTT, port of service (without TLS is 1883 for default), the topic or topics and name of image with extension (you should put in the folder and upload previously).

**Wi-Fi**

const char* ssid = "";

const char* password = "";

**MQTT**

const char* mqttServer = "";

const uint16_t mqttPort = 1883; //No TLS

const char* mqttTopic = "esp32/ag1";

**Image**

sendImage("");
