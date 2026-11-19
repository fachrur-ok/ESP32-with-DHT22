#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

// Konfigurasi pin DHT22
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Konfigurasi WiFi
const char* ssid = "DnZO_wrt";
const char* password = "internet1";

// Konfigurasi ThingSpeak
unsigned long channelID = 3569501;
const char* writeAPIKey = "XUWGOCZFRPKKTG9N";

// Interval pengambilan data: 60 detik
const unsigned long interval = 60000;
unsigned long previousMillis = 0;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Memulai sensor DHT22
  dht.begin();

  // Menghubungkan WiFi
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi berhasil terhubung!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Memulai ThingSpeak
  ThingSpeak.begin(client);

  // Agar pembacaan pertama dilakukan segera
  previousMillis = millis() - interval;
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Membaca sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Memeriksa hasil pembacaan
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Gagal membaca sensor DHT22!");
      return;
    }

    // Menampilkan data di Serial Monitor
    Serial.println("========================");
    Serial.print("Suhu       : ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Kelembapan : ");
    Serial.print(humidity);
    Serial.println(" %RH");

    // Mengirim data ke ThingSpeak
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);

    int response = ThingSpeak.writeFields(
      channelID,
      writeAPIKey
    );

    if (response == 200) {
      Serial.println("Data berhasil dikirim ke ThingSpeak!");
    } else {
      Serial.print("Gagal mengirim data. Kode: ");
      Serial.println(response);
    }

    Serial.println("========================");
  }
}