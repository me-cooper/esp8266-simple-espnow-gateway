# Changelog



- **11.01.2024**

`String receivedString = Serial.readString();` wurde durch `String receivedString = Serial.readStringUntil('\n');` ersetzt. Das konnte die Geschwindigkeit Aktion -> Ergebnis von 2.55 Sekunden auf 0.46 Sekunden reduzieren LOL