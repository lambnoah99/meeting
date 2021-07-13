# Meeting-Display
## Anforderungen
Funktional:
        Anzeige über Lichtsignal
        Einbindung ins Netzwerk
        Über Webinterface steuerbar
        IP-Adresse an Gerät selbst ablesbar

Nicht-Funktional:
        System sollte funktionieren
        Konfiguration/Einbindung sollte ohne programmieren durchführbar sein
        Der gesetzte Status sollte sich innerhalb von wenigen Sekunden aktualisieren (<2s)
        Das Gerät sollte nicht zu groß sein (~Portmonaie)
        Das Gerät sollte optisch ansprechend sein / nicht negativ auffallen

## API-Endpunkte

- /
    Status-Seite
- /on
    Schalte LED Ein
- /off
    Schalte LED aus
- /reset
    Starte gerät neu

## Serielles Interface

Über das Serielle Interface kann der aktuelle WIFI-Status und die IP-Adresse herausgefunden werden.
Dazu muss das Gerät per USB verbunden werden und eine Serielle-Kommunikation mit einer Baudrate von 9600 ausgebaut werden.