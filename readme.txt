Fotorechner 1.1.1 für Windows - (c) 2010-2021 by Martin Gäckler
===============================================================

Dieses Programm berechnet verschiedene Werte der Fotografie. Dabei ist 
aber zu beachten, daß es sich um näherungswerte handelt, da die verwendeten
Formeln nur für "dünne" Linsen gelten d.h. Gegenstandsweite und Bildweite 
ergeben zusammen den Abstand des Objektes zum Film bzw. Sensor.

Folgende Werte können Sie eingeben:

Objektgröße, Bildgröße, Entfernung, Brennweite, Vergrößerungsmasstab und 
Blende.

Diese Werte werden automatisch berechnet:

Bildwinkel            : Aus Brennweite und Bildgröße
Bildgröße             : Aus Objektgröße und Vergrößerungsmasstab.
Entfernung            : Aus Vergrößerungsmasstab und Brennweite.
Vergrößerungsmasstab  : Wenn vorhanden aus Entfernung und Brennweite 
                        ansonsten aus Objektgröße und Bildgröße.
Hyperfokale Entfernung: Aus Blende, Brennweite und Bildgröße (die Bild-
                        größe wird als Bilddiagonale interpretiert)
Minimum Entfernung    : Aus Blende, Brennweite, Bildgröße und Entfernung.
Maximum Entfernung    : Aus Blende, Brennweite, Bildgröße und Entfernung.
                        
Wenn die Brennweite verändert wird, so wird automatisch die Entfernung 
oder der Vergrößerungsmasstab neu berechnet. Je nachdem, was zuletzt 
berechnet wurde. Eine fett gezeichnete Beschrifftung zeigt den Wert an, 
der bei Eingabe der Brennweite neu berechnet wird.

So lange die Bildgröße nicht verändert wurde, wird diese automatisch 
berechnet. Ein Rechtsklick auf die Bildgröße zeigt ein Popupmenü mit
einigen gängigen Größen.

Berechnete Werte erscheinen mit grünem Hintergrund. Wenn der 
Vergrößerungsfaktor nicht berechnet werden konnte, so wird dieser mit
rotem Hintergrund angezeigt.


==========================================================================

This program calculates some values for a fotographer. Please note: the 
calculations are not exact due to the fact that the used formulas a valid 
for thin lenses, only.

You can enter the following values:

Object size, picture size, distance, focal length, factor and aperture.

The following values will be calculated:

Picture angle      : based on focal length and picture size
Picture size       : based on object size and factor.
Distance           : based on factor and focal length.
Factor             : based on distance and focal length if available
                     otherwise based on object and picture size.
Hyperfocal distance: based on aperture, focal length and picture size 
                     (interpreted as picture diagonal)
Minimum distance   : based on aperture, focal length, picture size and 
                     distance.
Maximum distance   : based on aperture, focal length, picture size and 
                     distance.
                        
If you change the focal length, the program automatically updated the 
distance or the factor. A bold label show which value will be calculated.

As far as you did not enter a picture size it will be updated 
automatically. A right click on the picture size shows a popup menu with
common values.

Calculated values apear with a green background. If the program cannot
calculated a new factor a red background apears. 
