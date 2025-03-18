# Gas-Uhr
Datenerfassung mit Sensor und Ausgabe über WLAN. Server-Client(Ajax).

### WLAN einrichten:
#### Im Terminal ausführen:
```
cd include
cp env.bsp env.h
nano env.h

```
#### Zugangsdaten anpassen:
```
* STATION-MODE
    * SSID = sta_ssid, Passwort = sta_password
* ACCESS-MODE
    * SSID = ap_ssid, Passwort = ap_password

```

#### env.h speichern.
### Globale Einstellungen(main.cpp//Globals):
```
* INPUT_PIN: GPIO, LOW-aktiv
* WIFI_STATE: STATION oder ACCESS
* BOUNCE: Entprellen in ms(0..)
```
