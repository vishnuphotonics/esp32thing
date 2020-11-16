uint64_t chipid;  
#include "WiFi.h"
void setup() {
pinMode (LED_BUILTIN, OUTPUT);
Serial.begin(115200);
// Set WiFi to station mode and disconnect from an AP if it was previously connected
WiFi.mode(WIFI_STA);
WiFi.disconnect();
delay(100);

Serial.println("Setup done");
}
void loop() {
digitalWrite(LED_BUILTIN, HIGH);
delay(2000);
digitalWrite(LED_BUILTIN, LOW);
delay(2000);
chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
Serial.printf("ESP32 Chip ID = %04X",(uint16_t)(chipid>>32));//print High 2 bytes
Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.

Serial.println("scan start");

// WiFi.scanNetworks will return the number of networks found
int n = WiFi.scanNetworks();
Serial.println("scan done");
if (n == 0) {
    Serial.println("no networks found");
} else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
        delay(10);
    }
}
Serial.println("");

// Wait a bit before scanning again
delay(5000);

}

//Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.
