# MQTT Demo Used in the Web Of Things lessons

## Introduction
In this project you'll find three subprojects:
- `MQTT-Arduino-ESP`: This is an Arduino/ESP project that will connect to an MQTT broker.
- `server`: An express server that will handle HTTP methods and has an implementation of Socket.IO
- `client`: The frontend client to control the Arduino/ESP


## MQTT-Arduino-ESP
For this project, you're Arduino/ESP needs to have access to the LAN via WiFi or Ethernet. If not, you cannot run the Wifi.h library.

## Server
The server has some endpoints:
- `startTimer`: starts an internal server timer
- `stopTimer`: stops the internal server timer
- `startProp`: starts the puzzle
- `restartProp`: restarts the puzzle 

## Client
This is a React application to start the timer (will be fed via sockets) on Arduino/ESP.

## Author
- Rüveyda Kartal <ruveyda.kartal@outlook.be>
- Victor Tanaka 
- Tim De Paepe <tim.depaepe@arteveldehs.be># WOT_broker
