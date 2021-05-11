Fotorechner 1.1.1 für JavaME und Android - (c) 2011-2012 by CRESD GmbH
======================================================================

Dieses Programm berechnet verschiedene Werte der Fotografie. Dabei ist 
aber zu beachten, daß es sich um Näherungswerte handelt, da die verwendeten
Formeln nur für "dünne" Linsen gelten d.h. Gegenstandsweite und Bildweite 
ergeben zusammen den Abstand des Objektes zum Film bzw. Sensor.

Zur Installation der Programme installieren Sie bitte die Dateien foto.jar 
für JavaME bzw. FotoCalc.apk für Android gemäß der Bedienungsanleitung Ihres
Smartphones.

Folgende Werte können Sie eingeben:

Filmgröße, Brennweite, Blende, Entfernung, Zeit und Verlängerungsfaktor des 
Graufilters.

Diese Werte werden berechnet:

Schärfentiefe         : Aus Filmgröße, Brennweite, Blende, und Entfernung.
Bildwinkel,
KB Brennweite,
Cropfaktor            : Aus Bildgröße und Brennweite.
Hyperfokale Entfernung: Aus Bildgröße, Brennweite  und Blende
Vergrößerungsfaktor   : Aus Brennweite und Entfernung. Optional die Objektgröße
                        aus der Filmgröße und dem Vergrößerungsfaktor.
Belichtungszeit:      : Aus Zeit und Verlängerungsfaktor, wenn auch eine 
                        Blende angegeben wurde, können Sie mit Links und Rechts
                        eine andere Blende wählen, und es wird eine neue Zeit
                        berechnet.

Bei der Eingabe der Zeit ist folgendes zu beachten:
Geben Sie eine ganze Zahl ohne Dezimalpunkt ein, so wird die Angabe als 
Bruchteil einer Sekunde interpretiert.

Beispiel: 250 entspricht 1/250s

Geben Sie eine Zahl mit Dezimalpunkt ein, so wird dies als ein Vielfaches 
einer Sekunde interpretiert.
Beispiel: 250. entspricht 250s

