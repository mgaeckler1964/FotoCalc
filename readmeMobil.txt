Fotorechner 1.1.1 f�r JavaME und Android - (c) 2011-2012 by CRESD GmbH
======================================================================

Dieses Programm berechnet verschiedene Werte der Fotografie. Dabei ist 
aber zu beachten, da� es sich um N�herungswerte handelt, da die verwendeten
Formeln nur f�r "d�nne" Linsen gelten d.h. Gegenstandsweite und Bildweite 
ergeben zusammen den Abstand des Objektes zum Film bzw. Sensor.

Zur Installation der Programme installieren Sie bitte die Dateien foto.jar 
f�r JavaME bzw. FotoCalc.apk f�r Android gem�� der Bedienungsanleitung Ihres
Smartphones.

Folgende Werte k�nnen Sie eingeben:

Filmgr��e, Brennweite, Blende, Entfernung, Zeit und Verl�ngerungsfaktor des 
Graufilters.

Diese Werte werden berechnet:

Sch�rfentiefe         : Aus Filmgr��e, Brennweite, Blende, und Entfernung.
Bildwinkel,
KB Brennweite,
Cropfaktor            : Aus Bildgr��e und Brennweite.
Hyperfokale Entfernung: Aus Bildgr��e, Brennweite  und Blende
Vergr��erungsfaktor   : Aus Brennweite und Entfernung. Optional die Objektgr��e
                        aus der Filmgr��e und dem Vergr��erungsfaktor.
Belichtungszeit:      : Aus Zeit und Verl�ngerungsfaktor, wenn auch eine 
                        Blende angegeben wurde, k�nnen Sie mit Links und Rechts
                        eine andere Blende w�hlen, und es wird eine neue Zeit
                        berechnet.

Bei der Eingabe der Zeit ist folgendes zu beachten:
Geben Sie eine ganze Zahl ohne Dezimalpunkt ein, so wird die Angabe als 
Bruchteil einer Sekunde interpretiert.

Beispiel: 250 entspricht 1/250s

Geben Sie eine Zahl mit Dezimalpunkt ein, so wird dies als ein Vielfaches 
einer Sekunde interpretiert.
Beispiel: 250. entspricht 250s

