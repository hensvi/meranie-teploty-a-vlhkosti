#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Definovanie pinov
#define DHTPIN 14       // Pin, na ktorom je pripojený DHT11
#define DHTTYPE DHT11   // Typ senzora
#define SCREEN_WIDTH 128 // Šírka OLED displeja
#define SCREEN_HEIGHT 64 // Výška OLED displeja

// Inicializácia objektov
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
    Serial.begin(115200);
    dht.begin();
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
}

void loop() {
    float teplota = dht.readTemperature();
    float vlhkost = dht.readHumidity();
    
    if (isnan(teplota) || isnan(vlhkost)) {
        Serial.println(F("Chyba pri čítaní dát zo senzora DHT!"));
        return;
    }
    
    Serial.print(F("Teplota: "));
    Serial.print(teplota);
    Serial.print(F(" °C, Vlhkosť: "));
    Serial.print(vlhkost);
    Serial.println(F(" %"));
    
    // Aktualizácia OLED displeja
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.print("Teplota: ");
    display.print(teplota);
    display.print(" C");
    display.setCursor(0, 30);
    display.print("Vlhkost: ");
    display.print(vlhkost);
    display.print(" %");
    display.display();
    
    delay(2000); // Aktualizácia každé 2 sekundy
}
