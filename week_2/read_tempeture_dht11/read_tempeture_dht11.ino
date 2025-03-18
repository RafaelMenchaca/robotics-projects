#include <DHT.h>

#define DHTPIN 2       // DHT11 connected to Pin 2
#define DHTTYPE DHT11  // Define sensor type as DHT11

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    float temperature = dht.readTemperature();  // Read temperature in Celsius
    float humidity = dht.readHumidity();        // Read humidity

    // Check if readings are valid
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C  |  Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    delay(2000);  // Wait 2 seconds before next reading
}
