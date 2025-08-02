# 🚗 ESPDrive – Wi-Fi Controlled Motor Car (ESP32)

**ESPDrive** is a real-time motor control system built using an ESP32. It hosts a mobile-friendly web interface that lets you control a car's motion over Wi-Fi — no external app or server required!

---

## 🚀 Features

- 🌐 Control via browser (desktop/mobile)
- 🔌 ESP32-hosted web UI (no internet needed)
- ⬆️ Real-time actions (press-and-hold based)
- 🧭 Directional controls:
  - Forward / Reverse
  - Left / Right
  - Stop
- 🧠 Built-in mDNS support (use `http://car.local`)

---

## 📦 Library Dependencies

You need the following libraries in Arduino IDE (automatically included with ESP32 board support):

| Library      | Install Instructions |
|--------------|----------------------|
| **WiFi.h**   | Built-in with ESP32 board package |
| **WebServer.h** | Built-in with ESP32 board package |
| **ESPmDNS.h**   | Built-in with ESP32 board package |

### 📥 Install ESP32 Board Support (if not already):

1. Open **Arduino IDE** → Preferences  
2. Add this to **Additional Board URLs**:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools** → **Board** → **Boards Manager**  
4. Search for **ESP32** and install  
5. Select your ESP32 board under **Tools → Board**

---

## 🛠 Requirements

- ESP32 Dev Board
- L298N Motor Driver Module
- 2 DC Motors (Drive + Steering)
- Jumper wires, battery, chassis
- Arduino IDE with ESP32 board installed

---

## 📂 Project Structure

```
ESPDrive/
├── ESP32_Car_Control.ino    # Main program
└── README.md                # Project documentation
```

---

## ⚙️ Wiring & Pins

| Function        | ESP32 Pin |
|----------------|-----------|
| Motor1 IN1     | 27        |
| Motor1 IN2     | 26        |
| Motor2 IN1     | 25        |
| Motor2 IN2     | 33        |

Make sure all motor driver EN pins are powered (e.g., connected to 5V or PWM).

---

## 🔧 Configuration

Update your Wi-Fi credentials in the code:

```cpp
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
```

Flash the code to your ESP32 using Arduino IDE.

---

## 🖥️ Web Interface

Access the interface by visiting:

```
http://<ESP_IP>
```

Or use:

```
http://car.local
```

Controls available:

- ⬆️ Forward
- ⬇️ Reverse
- ⬅️ Left
- ➡️ Right
- ⏹️ Stop

Each button uses `onmousedown` and `ontouchstart` for smooth control.

---

## 🧠 How It Works

1. ESP32 connects to Wi-Fi and hosts a simple web server
2. A mobile-friendly HTML page is served to control movement
3. Pressing buttons triggers ESP32 endpoints (`/forward`, `/stop`, etc.)
4. These toggle motor pins in real time to control the car

---

## 🧾 Disclaimer

- For educational/personal use only
- Requires basic safety precautions while using motors and power supplies
- Not intended for commercial automotive control

---

## 🔮 Future Enhancements

- 📶 SoftAP fallback mode
- 🕹️ Speed control using PWM
- 📸 ESP32-CAM livestream integration
- 📦 3D printed chassis design
- 📱 Android app alternative

---

## 👨‍💻 Author

**Divyam Sethi**  
🔗 [LinkedIn](https://www.linkedin.com/in/divyam-sethi-3a5141232)  
📧 [Email](mailto:divyamsethi1804@gmail.com)

---

## ⭐️ Support

If you found this project helpful, please give it a ⭐ on GitHub and share it with fellow IoT enthusiasts!
