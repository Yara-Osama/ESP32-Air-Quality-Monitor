# ESP32 Air Quality Monitor (Humidity, Dust, CO) with MQTT + Node-RED Dashboard

An end‑to‑end STEM capstone project: an ESP32 reads humidity (DHT11), dust density, and carbon monoxide (CO), computes an **Air Quality Index (AQI)**, shows values on a 16x2 LCD, publishes live data over MQTT, and visualizes/alerts in a Node‑RED dashboard.

## Features
- ESP32 firmware reads **Humidity**, **Dust density**, **CO (ppm)** and computes **AQI**.
- 16x2 **LCD** status (Wi‑Fi, IP, live readings) and **buzzer/LED** alerts on unsafe values.
- **MQTT** topics (public broker by default) for streaming to **Node‑RED** gauges/charts.
- Node‑RED flow to display metrics and push notifications + optional file logging.

## Hardware (typical)
- ESP32 DevKit
- DHT11 humidity/temperature sensor
- Analog CO gas sensor module (e.g., MQ‑series)
- Optical dust sensor module with LED (typical LED/photodiode dust sensor)
- 16×2 LCD (HD44780 compatible)
- Buzzer + LED, wires, breadboard

> If you used different modules, adjust the pin mapping below accordingly.

## Pin mapping (from firmware)
- **DHT11**: `DHTPIN = 4`
- **CO analog sensor**: `COPIN = 27`
- **Dust sensor output**: `DUSTPIN = 25`
- **Dust sensor LED control**: `DUSTLED = 33`
- **Buzzer**: `BUZZERPIN = 32`
- **Warning LED / flasher**: `FLASHER = 26`
- **LCD (LiquidCrystal RS, E, D4, D5, D6, D7)**: `19, 23, 18, 17, 16, 15`

## MQTT
- **Broker**: `broker.hivemq.com` (port `1883`)
- **Topics**:
  - `ESP32/humidity`
  - `ESP32/dust`
  - `ESP32/carbonmonoxide`
  - `ESP32/AQI`

> Change broker/credentials as needed in `WiFi_MQTT.cpp` and `WiFi_MQTT.h`.

## Node‑RED Dashboard
Import the flow from `dashboard/flows.json`. It includes:
- Gauges for Humidity, Dust, CO, and AQI
- Line charts for time‑series history
- Mobile/remote notifications when **CO > 9 ppm** or **Dust > 35** (project units)
- Optional JSON‑line file logging (edit the output file path after import)

## Arduino/PlatformIO Libraries
- `WiFi.h` (ESP32 core)
- `PubSubClient` (MQTT)
- `LiquidCrystal`
- `DHT`

## Build & Upload (Arduino IDE)
1. Install **ESP32 board support** in Arduino IDE.
2. Install libraries above via **Library Manager**.
3. Open `firmware/Pollution_Tracker.ino`.
4. Select your ESP32 board + port, then **Upload**.
5. Update the SSID/password (currently `ESP32` / `12345678`) in `connectToWiFi()`.

## How AQI is computed
`AQI.cpp` maps **CO** and **PM2.5** ranges to the standard 0–500 AQI scale. The firmware publishes `ESP32/AQI` which the Node‑RED dashboard plots.

## Repository layout
```
.
├── firmware/
│   ├── Pollution_Tracker.ino
│   ├── AQI.h
│   ├── AQI.cpp
│   ├── WiFi_MQTT.h
│   └── WiFi_MQTT.cpp
└── dashboard/
    └── flows.json
```

## Quick start (Node‑RED)
1. Open Node‑RED → Menu → **Import** → **Clipboard** → paste the JSON from `dashboard/flows.json` → **Import**.
2. Double‑click the **MQTT in** nodes and confirm the broker (`broker.hivemq.com:1883`).
3. Adjust the **file** node path for logging (optional).
4. Deploy and open **/ui** to view the dashboard.

## Security note
The default broker is **public** and unauthenticated. For production, use a private MQTT broker with TLS and credentials.

## License
See [LICENSE](LICENSE).
