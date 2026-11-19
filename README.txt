# Monitoring Lingkungan Berbasis IoT

Proyek ini menggunakan ESP32-S3 dan sensor DHT22 untuk mengukur suhu dan kelembapan lingkungan. Data hasil pengukuran dikirim melalui jaringan WiFi ke ThingSpeak agar dapat disimpan dan dipantau secara online.

## 1. Perangkat yang Digunakan

Hardware:

* ESP32-S3
* Sensor DHT22
* Kabel jumper
* Kabel USB

Software:

* Arduino IDE
* ThingSpeak

## 2. Rangkaian Sensor

Hubungkan sensor DHT22 ke ESP32-S3 dengan konfigurasi berikut:

* VCC DHT22 ke 3V3 ESP32-S3
* DATA DHT22 ke GPIO 4 ESP32-S3
* GND DHT22 ke GND ESP32-S3

Pastikan seluruh kabel terpasang dengan benar sebelum perangkat dinyalakan.

## 3. Persiapan Arduino IDE

Sebelum menjalankan program, pastikan Arduino IDE sudah terinstal di komputer.

### Instalasi Board ESP32

Jika board ESP32 belum tersedia, lakukan langkah berikut:

1. Buka Arduino IDE.

2. Pilih File → Preferences.

3. Masukkan URL berikut pada bagian Additional Boards Manager URLs:

   https://espressif.github.io/arduino-esp32/package_esp32_index.json

4. Klik OK.

5. Buka Tools → Board → Boards Manager.

6. Cari ESP32, kemudian instal paket ESP32 dari Espressif Systems.

### Instalasi Library

Buka Sketch → Include Library → Manage Libraries, kemudian cari dan instal:

* DHT sensor library by Adafruit
* Adafruit Unified Sensor
* ThingSpeak by MathWorks

Library WiFi sudah tersedia dalam paket ESP32.

## 4. Konfigurasi Program

Buka file monitoring_dht22.ino menggunakan Arduino IDE.

Sebelum program dijalankan, sesuaikan konfigurasi berikut.

### Konfigurasi WiFi

Masukkan nama dan password WiFi yang akan digunakan.

```cpp
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";
```

### Konfigurasi ThingSpeak

Buat channel baru melalui https://thingspeak.mathworks.com/.

Aktifkan dua field pada channel:

* Field 1: Temperature
* Field 2: Humidity

Setelah channel dibuat, buka bagian API Keys. Salin Channel ID dan Write API Key, kemudian masukkan ke dalam program.

```cpp
unsigned long channelID = CHANNEL_ID;
const char* writeAPIKey = "WRITE_API_KEY";
```

### Interval Pengiriman Data

Program menggunakan interval pengiriman data selama 60 detik.

```cpp
const unsigned long interval = 60000;
```

Dengan pengaturan tersebut, ESP32-S3 akan mengirimkan data suhu dan kelembapan setiap satu menit.

## 5. Cara Menjalankan Program

1. Hubungkan ESP32-S3 ke komputer menggunakan kabel USB.
2. Buka file program melalui Arduino IDE.
3. Pilih board ESP32S3 Dev Module atau tipe board yang sesuai.
4. Pilih port COM yang digunakan ESP32-S3.
5. Atur Upload Speed menjadi 115200 jika diperlukan.
6. Klik Verify untuk memeriksa program.
7. Klik Upload untuk mengunggah program ke ESP32-S3.
8. Setelah upload selesai, buka Serial Monitor dengan baud rate 115200.

Jika program berjalan dengan baik, ESP32-S3 akan terhubung ke WiFi, membaca data dari sensor DHT22, kemudian mengirimkan hasil pengukuran ke ThingSpeak setiap 60 detik.

## 6. Monitoring Data pada ThingSpeak

Data yang berhasil dikirim akan muncul pada channel ThingSpeak dalam bentuk grafik.

Terdapat dua parameter yang dikirimkan:

* Temperature: hasil pengukuran suhu lingkungan dalam satuan derajat Celsius (°C).
* Humidity: hasil pengukuran kelembapan udara dalam satuan persen (%RH).

Data yang tersimpan dapat diunduh dalam format CSV untuk digunakan dalam proses pengolahan dan analisis lebih lanjut.

## 7. Troubleshooting

Beberapa kendala yang mungkin terjadi selama penggunaan perangkat:

* ESP32 tidak terdeteksi: periksa kabel USB dan port COM yang digunakan.
* Upload program gagal: coba turunkan Upload Speed menjadi 115200 atau gunakan tombol BOOT saat proses upload.
* WiFi tidak terhubung: periksa kembali nama dan password WiFi.
* Sensor gagal membaca data: periksa sambungan pin DHT22 dan pastikan sensor mendapatkan suplai daya.
* Data tidak masuk ThingSpeak: periksa Channel ID, Write API Key, dan koneksi internet.

## 8. Catatan Penggunaan

* Pastikan ESP32-S3 mendapatkan suplai daya selama proses pengambilan data.
* Koneksi WiFi harus tersedia agar data dapat dikirim ke ThingSpeak.
* Untuk pengambilan data selama tujuh hari, perangkat perlu dijaga tetap aktif dan diperiksa secara berkala.
* Jangan mengunggah password WiFi atau Write API Key asli ke repository publik GitHub.

## Informasi Proyek

Mikrokontroler: ESP32-S3

Sensor: DHT22

Bahasa Pemrograman: C++

Platform Pemrograman: Arduino IDE

Komunikasi: WiFi

Platform IoT: ThingSpeak

Interval Pengiriman: 60 detik
