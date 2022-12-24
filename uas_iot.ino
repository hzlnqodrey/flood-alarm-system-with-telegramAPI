#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "Lab Basis Data";
const char* password = "ifbasdat";

#define BOTtoken "5822073426:AAGW8iw7j0OeE-hOFczG87VfWBpNCzCC54Y"
#define CHAT_ID "-863691061"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

#define pinSensor A0
#define RED_LED 4
#define buzzer 15
int sensorValue = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setInsecure();
  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);
// Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "Sistem deteksi banjir menyala!", "");

  pinMode (RED_LED, OUTPUT);   //Deklarasi LED merah sebagai Output7Output
     // Buzzer
    pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  sensorValue = analogRead(pinSensor);

  Serial.print("Sensor value: ");
  Serial.println(sensorValue);

  if (sensorValue >= 200) {
    digitalWrite (RED_LED, HIGH);            //LED merah aktif

    bot.sendMessage(CHAT_ID, "Banjir terdeteksi! Hindari daerah yang terkena banjir!", "");
    Serial.println("Banjir terdeteksi!");
            tone(buzzer, 1000);
            delay(50);
            noTone(buzzer);
            delay(50);
  } 
  delay(1000);
}
