# Simple MQTT Client for ESP32 using SPIFFS

## A simple program for use a SPIFFS on your ESP32 for upload and transmit an image using MQTT (pub/sub)

An important aspect did u know for using this features:

If you use an IDE from Arduino, you need use the latest version allow the feature of **ESP32 Sketch Data Upload**, that its a 1.8.18.
The url you can find it actually is: [PREVIOUS ARDUINO IDE's](https://www.arduino.cc/en/software/OldSoftwareReleases/) 

In other hand, for use the utility, you need to download the *.jar* and include in your IDE. The follow steps explains how to do it:

1. Download the file from [ESP32fs](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/)
2. Find your sketchbook location and create a directory naming *tools*
3. Copy the unzip folder previously download in step one into this folder (create in step 2)
4. Verificate, the finally path from the file is similar to ~/tools/ESP32FS/tool

**Note:** It's mandatory follow the structure of path for include the tool into the IDE describe in the previous steps.

Finally, if you make all the previous steps, if you reload the IDE, in section **Tools**, you should see the feature.

## Using SPIFFS for upload an image to ESP32

For use correctly the tool, you should keep in mind a structure of folders for include the picture you want upload to the microcontroler, so lets see a diagram thats explain how to build your project properly.

![Hierarchy of memory in ESP32](https://github.com/user-attachments/assets/48b3fde9-179d-4db1-be1a-62f875f3a4f5)

![Structure of Arduino Project](https://github.com/user-attachments/assets/09a1581c-70e7-4fd6-8b66-e5fd89a1cd15)


