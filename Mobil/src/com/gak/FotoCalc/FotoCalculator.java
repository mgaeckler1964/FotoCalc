package com.gak.FotoCalc;

/**
 * <p>Title: FOTOCALC</p>
 *
 * <p>Description: Mobiler Fotorechner</p>
 *
 * <p>Copyright: Copyright (c) 2012</p>
 *
 * <p>Company: CRESD GmbH</p>
 *
 * @author not attributable
 * @version 1.1
 */
public class FotoCalculator
{
	static private double atan( double tangens )
	{
		double	testVal;
		double	angle	 = 0;
		double 	minAngle = - Math.PI/2;
		double 	maxAngle = + Math.PI/2;

		while( minAngle < maxAngle )
		{
			angle = (minAngle + maxAngle) / 2;
			if( angle == maxAngle || angle== minAngle )
				break;

			testVal = Math.tan( angle );
			if( testVal < tangens )
				minAngle = angle;
			else if( testVal > tangens )
				maxAngle = angle;
			else
				break;
		}

		return angle;
	}

	static public String calcAngle( double bildGroesse, double brennweite )
	{
		String	resultString = "Falsche Daten";

		if( bildGroesse > 0 && brennweite > 0 )
		{
			resultString = "Bildwinkel: ";
			double bildwinkel = 360 * atan( bildGroesse / (2*brennweite) ) / Math.PI;
			resultString += String.valueOf( Math.ceil( bildwinkel * 10)/10 );
			resultString += " Grad";

			resultString += "\nKB Brennweite: ";
			double	kbSize = Math.sqrt(36 * 36 + 24 * 24);
			double cropFactor = kbSize / bildGroesse;
			double kbLength = cropFactor * brennweite;
			resultString += String.valueOf( Math.ceil( kbLength * 10)/10 ) + " mm";

			resultString += "\nCropfaktor: ";
			resultString += String.valueOf( Math.ceil( cropFactor * 10)/10 );
		}

		return resultString;
	}
	static public String calcDOF(double bildGroesse, double brennweite, double blende, double distanz)
	{
		String	resultString = "Falsche Daten";

		if( bildGroesse > 0 && brennweite > 0 && blende > 0 && distanz > 0 )
		{
			resultString = "Schärfentiefe von ";
			double zerstreuungskreis = bildGroesse/1500;
			double hyperfokaleEntfernung = brennweite*brennweite / (blende*zerstreuungskreis) + brennweite;

			double minDistanz = distanz*hyperfokaleEntfernung / (hyperfokaleEntfernung+distanz-brennweite);
			resultString += String.valueOf( Math.ceil( minDistanz )/1000 ) + " m";

			resultString += " bis ";
			double quotient = hyperfokaleEntfernung-distanz+brennweite;
			if( quotient > 0 )
			{
				double maxDistanz = distanz*hyperfokaleEntfernung / quotient;
				resultString += String.valueOf( Math.ceil( maxDistanz )/1000 ) + " m";
			}
			else
			{
				resultString += "unendlich";
			}
		}
		return resultString;
	}
	static public String calcHyperDistance(double bildGroesse, double brennweite, double blende)
	{
		String	resultString = "Falsche Daten";

		if( bildGroesse > 0 && brennweite > 0 && blende > 0 )
		{
			resultString = "Hyperfokale Entfernung von ";
			double zerstreuungskreis = bildGroesse/1500;
			double hyperfokaleEntfernung = brennweite*brennweite / (blende*zerstreuungskreis) + brennweite;
			resultString += String.valueOf( Math.ceil( hyperfokaleEntfernung )/1000 ) + " m";
		}

		return resultString;
	}
	static public String calcVergFaktor( double distanz, double brennweite, double bildBreite, double bildHoehe )
	{
		double	vergrFaktor = 0.0;
		String	resultString = "Falsche Daten";

		if( distanz>0 && brennweite>0 )
		{
			double tmp = distanz/brennweite-2;
			double det = tmp*tmp-4;
			if( det > 0 )
				vergrFaktor = ((distanz/brennweite-2) + Math.sqrt( det )) / 2;
			else if( det == 0 )
				vergrFaktor = (distanz/brennweite-2) / 2;
		}
		if( vergrFaktor > 0.005 )
		{
			resultString = "Vergrößerungsfaktor von ";
			resultString += String.valueOf( Math.ceil( vergrFaktor * 10 )/10 );
			if( bildBreite > 0 )
			{
				resultString += "\nBreite: ";
				resultString += String.valueOf( Math.ceil( bildBreite * vergrFaktor * 10 )/10 );
				resultString += "mm";
			}
			if( bildHoehe > 0 )
			{
				resultString += "\nHöhe: ";
				resultString += String.valueOf( Math.ceil( bildHoehe * vergrFaktor * 10 )/10 );
				resultString += "mm";
			}
		}
		else if( vergrFaktor < 0 )
			resultString = "Vergrößerungsfaktor kann nicht berechnet werden.";

		return resultString;
	}
}
