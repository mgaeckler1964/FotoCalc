/*
		Project:		FotoCalc
		Module:			FotoCalculator.java
		Description:	the calculations
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 2013-2026 Martin Gäckler

		This program is free software: you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Linz, Austria ``AS IS''
		AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
		PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
		LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
		USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		SUCH DAMAGE.
*/

package at.gaeckler.FotoCalc;

import android.content.Context;

import java.util.Locale;

import at.gaeckler.FotoCalc.android.R;

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

	static public String calcAngle( Context context, double bildGroesse, double brennweite )
	{
		String	resultString = context.getString(R.string.wrongData);

		if( bildGroesse > 0 && brennweite > 0 )
		{
			resultString = context.getString(R.string.angleOfView) +": ";
			double bildwinkel = 360 * atan( bildGroesse / (2*brennweite) ) / Math.PI;
			resultString += String.format(Locale.getDefault(), "%.2f", Math.ceil( bildwinkel * 10)/10 );
			resultString += " °";

			resultString += "\n"+ context.getString(R.string.focalLength135) +": ";
			double	kbSize = Math.sqrt(36 * 36 + 24 * 24);
			double cropFactor = kbSize / bildGroesse;
			double kbLength = cropFactor * brennweite;
			resultString += String.format(Locale.getDefault(), "%.2f mm", Math.ceil( kbLength * 10)/10);

			resultString += "\n"+context.getString(R.string.cropFactor)+": ";
			resultString += String.format(Locale.getDefault(), "%.2f", Math.ceil( cropFactor * 10)/10 );
		}

		return resultString;
	}
	static public String calcDOF(Context context, double bildGroesse, double brennweite, double blende, double distanz)
	{
		String	resultString = context.getString(R.string.wrongData);

		if( bildGroesse > 0 && brennweite > 0 && blende > 0 && distanz > 0 )
		{
			resultString = context.getString(R.string.dofResult1);
			double zerstreuungskreis = bildGroesse/1500;
			double hyperfokaleEntfernung = brennweite*brennweite / (blende*zerstreuungskreis) + brennweite;

			double minDistanz = distanz*hyperfokaleEntfernung / (hyperfokaleEntfernung+distanz-brennweite);
			resultString += String.format(Locale.getDefault(), "%.2f", Math.ceil( minDistanz )/1000 ) + " m";

			resultString += context.getString(R.string.dofResult2);
			double quotient = hyperfokaleEntfernung-distanz+brennweite;
			if( quotient > 0 )
			{
				double maxDistanz = distanz*hyperfokaleEntfernung / quotient;
				resultString += String.format(Locale.getDefault(), "%.2f", Math.ceil( maxDistanz )/1000 ) + " m";
			}
			else
			{
				resultString += context.getString(R.string.infinity);
			}
		}
		return resultString;
	}
	static public String calcHyperDistance(Context context, double bildGroesse, double brennweite, double blende)
	{
		String	resultString = context.getString(R.string.wrongData);

		if( bildGroesse > 0 && brennweite > 0 && blende > 0 )
		{
			resultString = context.getString(R.string.HyperDistanceFrom);
			double zerstreuungskreis = bildGroesse/1500;
			double hyperfokaleEntfernung = brennweite*brennweite / (blende*zerstreuungskreis) + brennweite;
			resultString += String.format(Locale.getDefault(), "%.2f", Math.ceil( hyperfokaleEntfernung )/1000 ) + " m";
		}

		return resultString;
	}
	static public String calcSizeFactor( Context context, double distanz, double brennweite, double bildBreite, double bildHoehe )
	{
		double	vergrFaktor = 0.0;
		String	resultString = context.getString(R.string.wrongData);

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
			resultString = context.getString(R.string.sizeFactorFrom);
			resultString += String.format(Locale.getDefault(), "%.2f", Math.ceil( vergrFaktor * 10 )/10 );
			if( bildBreite > 0 )
			{
				resultString += "\n" + context.getString(R.string.width) +" : ";
				resultString += String.format(Locale.getDefault(), "%.2f", Math.ceil( bildBreite * vergrFaktor * 10 )/10 );
				resultString += "mm";
			}
			if( bildHoehe > 0 )
			{
				resultString += "\n" + context.getString(R.string.height) +" : ";
				resultString += String.format(Locale.getDefault(), "%.2f", Math.ceil( bildHoehe * vergrFaktor * 10 )/10 );
				resultString += "mm";
			}
		}
		else if( vergrFaktor < 0 )
			resultString = context.getString(R.string.sizeFactorError);

		return resultString;
	}
}
