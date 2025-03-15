## WLAN
# Diesen Code ausführen:
```
		cd include
		cp env.bsp env.h
		nano env.h

```
# Zugangsdaten anpassen:

// Zugangsdaten STATION MODE
const char* sta_ssid = "";
const char* sta_password = "";

// Zugangsdaten ACCESS MODE
const char* ap_ssid = "";
const char* ap_password = "";

# und env.h speichern.


# In main.cpp bei Bedarf DEFAULTS ändern:
```
		const uint8_t INPUT_PIN     = 2;                     // Input-Pin - LOW aktiv
		const uint8_t TEST_ON       = 0;				             // Testlauf: 0 -> AUS, 1 -> EIN
		const uint16_t LEERTAKTE    = 500;		               // Entprellen (in loop-Schleife leere Takte herunterzählen.)
		const enumState WIFI_STATE  = STATION;               // WLAN MODUS: STATION oder ACCESS
```
