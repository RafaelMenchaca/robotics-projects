#include <DHT.h>

#define DHTPIN 2       // Change if using a different pin
#define DHTTYPE DHT11  // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    Serial.println("Testing DHT11 Sensor...");
    dht.begin();
}

void loop() {
    delay(2000);  // Must wait at least 2 seconds between readings

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("⚠️ Failed to read from DHT sensor! Retrying...");
    } else {
        Serial.print("✅ Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C  |  Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
}
