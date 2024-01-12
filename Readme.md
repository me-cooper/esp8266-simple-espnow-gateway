### RECEIVER_ONLY_ESPNOW

Nur der ESPNOW-Empfänger, der Befehle von Clients empfängt und diese an den **RECEIVER_SERIAL_SLAVE** weiterleitet.



### RECEIVER_ONLY_ESPNOW

Gleiches wie **RECEIVER_ONLY_ESPNOW** nur das zusätzlich noch ein DHT22 auf D4 angebracht ist, der direkt die ersten Befehle Richtung Client sendet.



### RECEIVER_SERIAL_SLAVE

Dieser nimmt Commands vom ESPNow Server entgegen und macht daraus 1:1 eine HTTP-Request.



Aktuell werden nur GET-Request unterstützt da der Link vom Befehl einfach 1:1 für die Request an sich verwendet wird.



### SENDER_ONLY_ESPNOW

Beispiel Sender mit Deep-Sleep. Sendet Befehle nach dem Boot und geht dann direkt wieder in den Deep-Sleep.