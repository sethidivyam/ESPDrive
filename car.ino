#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

//======================= WIFI CONFIG =======================//
const char* ssid = "wifi_name";
const char* password = "wifi_password";

//======================= WEB SERVER =======================//
WebServer server(80);

//======================= MOTOR PINS =======================//
// Motor 1 (Drive Motor)
const int motor1Pin1 = 27;
const int motor1Pin2 = 26;

// Motor 2 (Steering Motor)
const int motor2Pin1 = 25;
const int motor2Pin2 = 33;

//======================= WEB PAGE HANDLER =======================//
void handleRoot() {
  const char html[] PROGMEM = R"rawliteral(
    <!DOCTYPE HTML><html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        html { font-family: Helvetica; text-align: center; }
        .button { background-color: #4CAF50; border: none; color: white; padding: 10px 25px; font-size: 22px; margin: 1px; cursor: pointer; }
        .button2 { background-color: #555555; }
      </style>
      <script>
        function sendCommand(cmd) { fetch('/' + cmd); }
        function startCommand(cmd) { sendCommand(cmd); }
        function stopCommand() { sendCommand('stop'); }
      </script>
    </head>
    <body>
      <h1>ESP32 DOIT Motor Control</h1>
      <p>
        <button class="button"
          onmousedown="startCommand('forward')"
          onmouseup="stopCommand()"
          ontouchstart="startCommand('forward')"
          ontouchend="stopCommand()">FORWARD</button>
      </p>
      <div>
        <p>
          <button class="button"
            onmousedown="startCommand('left')"
            onmouseup="stopCommand()"
            ontouchstart="startCommand('left')"
            ontouchend="stopCommand()">LEFT</button>

          <button class="button button2"
            onclick="stopCommand()">STOP</button>

          <button class="button"
            onmousedown="startCommand('right')"
            onmouseup="stopCommand()"
            ontouchstart="startCommand('right')"
            ontouchend="stopCommand()">RIGHT</button>
        </p>
      </div>
      <p>
        <button class="button"
          onmousedown="startCommand('reverse')"
          onmouseup="stopCommand()"
          ontouchstart="startCommand('reverse')"
          ontouchend="stopCommand()">REVERSE</button>
      </p>
    </body>
    </html>)rawliteral";
  server.send(200, "text/html", html);
}

//======================= MOVEMENT HANDLERS =======================//
void handleForward() {
  Serial.println("FORWARD");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  server.send(200);
}

void handleReverse() {
  Serial.println("REVERSE");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  server.send(200);
}

void handleLeft() {
  Serial.println("LEFT");
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  server.send(200);
}

void handleRight() {
  Serial.println("RIGHT");
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  server.send(200);
}

void handleStop() {
  Serial.println("STOP");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  server.send(200);
}

//======================= SETUP =======================//
void setup() {
  Serial.begin(115200);

  // Set pin modes
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP address: " + WiFi.localIP().toString());

  // Start mDNS
  if (!MDNS.begin("car")) {
    Serial.println("Error starting mDNS");
    return;
  }
  Serial.println("mDNS responder started. Access via http://car.local/");

  // Register routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/reverse", handleReverse);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);

  server.begin();
}

//======================= LOOP =======================//
void loop() {
  server.handleClient();
}
