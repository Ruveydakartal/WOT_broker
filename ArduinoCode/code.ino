
#include <WiFiNINA.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "WOT"; // Enter your WiFi name
const char *password = "enterthegame";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "192.168.50.234";
const int mqtt_port = 1883;

const char *mqttPuzzleCompleteTopic = "prop4/puzzleComplete";
const char *mqttPuzzleCompleteMessage = "completed";

const char *mqttStartChallenge = "prop4/index";
const char *mqttRestartChallenge = "restartArduino/now";

//PINS

const int s1Pin = 2; //Relay 1 input
const int l1Pin = 13; //Cijfer 1 led

const int s2Pin = 3; //Relay 2 input
const int l2Pin = 12; //Cijfer 2 led

const int s3Pin = 4; //Relay 3 input
const int l3Pin = 11; //Cijfer 3 led

const int switchPin = 5; //Relay 4 input
const int l4Pin = 10; //Schakelaar led

const int l5Pin = 9;

bool challengeStarted = false;

bool completed = false;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setupWifi() {

  // Connect to SSID
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  // Let them know
  Serial.println("Connected to the Wi-Fi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, mqttStartChallenge) == 0) {
    if(mqttClient.connected()) {
      challengeStarted = true;
    }
  } else if (strcmp(topic, mqttRestartChallenge) == 0) {
        if(mqttClient.connected()) {
    Serial.println("Restarting Arduino...");
    mqttClient.publish(mqttPuzzleCompleteTopic, "false");
    mqttClient.publish(mqttStartChallenge, "false");
    
    challengeStarted = false;
    digitalWrite(l1Pin, LOW);
    digitalWrite(l2Pin, LOW);
    digitalWrite(l3Pin, LOW);
    digitalWrite(l5Pin, HIGH);
    digitalWrite(l4Pin, LOW);

    delay(1000); // Delay to allow serial print to complete
    asm volatile ("  jmp 0"); // Jump to the beginning of the program to reset
  }}
}


void setupMQTT() {
  // Connecting to a MQTT broker
  mqttClient.setServer(mqtt_broker, mqtt_port);

  // Set the callback whenever we receive a topic
  mqttClient.setCallback(mqttCallback);

  // Start connecting
  while (!mqttClient.connected()) {
    if (mqttClient.connect("prop4")) {
      Serial.println("MQTT broker connected!");
    } else {
      Serial.print("MQTT connection failed with state ");
      Serial.print(mqttClient.state());
      delay(2000);
    }
  }

  // Subscribe
  mqttClient.subscribe(mqttStartChallenge);
  mqttClient.subscribe(mqttPuzzleCompleteTopic);
  mqttClient.subscribe(mqttRestartChallenge);

}

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(9600);

 pinMode(s1Pin, INPUT); // Use internal pull-up resistor
  pinMode(l1Pin, OUTPUT);

  pinMode(s2Pin, INPUT); // Use internal pull-up resistor
  pinMode(l2Pin, OUTPUT);

  pinMode(s3Pin, INPUT); // Use internal pull-up resistor
  pinMode(l3Pin, OUTPUT);

  pinMode(switchPin, INPUT); // Use internal pull-up resistor
  pinMode(l4Pin, OUTPUT);
  pinMode(l5Pin, OUTPUT);

  // Setup WiFi
  setupWifi();

  // Setup MQTT
  setupMQTT();
}

void loop() {

  mqttClient.loop();

  if (challengeStarted) {
    
    if (digitalRead(s1Pin) == HIGH) {
    digitalWrite(l1Pin, HIGH);
  } else {
    digitalWrite(l1Pin, LOW);
  }

  if (digitalRead(s2Pin) == HIGH) {
    digitalWrite(l2Pin, HIGH);
  } else {
    digitalWrite(l2Pin, LOW);
  }

  if (digitalRead(s3Pin) == HIGH) {
    digitalWrite(l3Pin, HIGH);
  } else {
    digitalWrite(l3Pin, LOW);
  }

  if (digitalRead(switchPin) == HIGH) {
    digitalWrite(l4Pin, HIGH);
    digitalWrite(l5Pin, LOW);
  } else {
    digitalWrite(l5Pin, HIGH);
    digitalWrite(l4Pin, LOW);
  }
  
  checkPropCompletion();
  }

  
}

void checkPropCompletion() {
  if (!completed && digitalRead(s1Pin) == HIGH && digitalRead(s2Pin) == HIGH && digitalRead(s3Pin) == HIGH && digitalRead(switchPin) == HIGH) {
    completed = true;
    Serial.println("PROP 4 COMPLETED!");

    // Publish a message to a specific topic when propCompleted is true
   
      mqttClient.publish(mqttPuzzleCompleteTopic, mqttPuzzleCompleteMessage);
      // mqttClient.publish(mqttPuzzleCompleteTopic5, "");

    
  }
}

