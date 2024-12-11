/*
		Project:		FotoCalc
		Module:			ResultScreen.java
		Description:	the android result activitiy for the calculator
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2024 Martin Gäckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Austria, Linz ``AS IS''
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

package com.gak.FotoCalc.android;

import com.gak.FotoCalc.android.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.view.*;

public class ResultScreen extends Activity {

	double neueZeit;
	double blende;
	Button	buttonPrev, buttonOK, buttonNext;
	TextView resultString;

	public static final int	zeiten[] =
	{
		1, 2, 3, 4, 5, 6, 8, 10, 13, 15, 20, 25, 30, 40, 45, 50, 60, 80,
		90, 100, 125, 160, 180, 200, 250, 320, 350, 400, 500, 640, 750,
		800, 1000, 1250, 1500, 1600, 2000, 2500, 3000, 3200, 4000, 8000, -1
	};

	public static final double blendenReihe[] =
	{
		1, 1.4, 1.8, 2, 2.2, 2.4, 2.5, 2.8, 3.2, 3.3, 3.5, 4, 4.5, 4.8, 5, 5.6,
		6.3, 6.7, 7.1, 8, 9, 9.5, 10, 11, 13, 14, 16, 18, 19, 20, 22, 32, -1
	};

	private void makeResultString()
	{
		int i;

		String resultString = "";
		if( neueZeit < 1 )
		{
			for( i=0; zeiten[i]>0; i++ )
			{
				if( neueZeit >= 1.0/zeiten[i] )
					break;
			}

			if( neueZeit > 1.0/zeiten[i] )
			{
				if (i > 0)
					resultString += "1/" + String.valueOf(zeiten[i - 1]) +
						" > ";
				resultString += "1/" + String.valueOf(Math.ceil(10/neueZeit)/10);

				if( zeiten[i] > 0 )
					resultString += " > ";
			}
			if( zeiten[i] > 0 )
				resultString += "1/" + String.valueOf( zeiten[i] );
		}
		else
			resultString += String.valueOf( Math.ceil( neueZeit * 10 ) / 10 ) + '"';
		
		if( blende > 0 )
			resultString += "\n" + String.valueOf(Math.ceil( blende * 10 ) / 10 );
		this.resultString.setText(resultString);
	}

	protected void changeAperture( int keyCode )
	{
		if( blende > 0 )
		{
			int		i;
			double	neueBlende = blende;

			for( i=0; blendenReihe[i] > 0; i++ )
				if( blendenReihe[i] > blende )
					break;

			if( keyCode == 1 && blendenReihe[i]>0 )
				neueBlende = blendenReihe[i];
			else if( keyCode == -1 && i>0 )
			{
				neueBlende = blendenReihe[i - 1];
				if (neueBlende == blende && i > 1)
					neueBlende = blendenReihe[i-2];
			}
			if( neueBlende != blende )
			{
				double faktor = (neueBlende*neueBlende) / (blende*blende);
				neueZeit = neueZeit * faktor;
				blende = neueBlende;
				makeResultString();
			}
		}
	}

	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.result_screen);
        
        Intent intent = getIntent();
        neueZeit = intent.getDoubleExtra("neueZeit", 0);
        blende = intent.getDoubleExtra("blende", -1);

        buttonPrev = (Button)findViewById( R.id.buttonPrev );
        buttonOK = (Button)findViewById( R.id.buttonOK );
        buttonNext = (Button)findViewById( R.id.buttonNext );
        resultString = (TextView)findViewById( R.id.resultString );
        
        buttonOK.setOnClickListener( new View.OnClickListener() {
			
			public void onClick(View bttn) {
				finish();
			}
		} );
        if( blende > 0 )
        {
	        buttonPrev.setOnClickListener( new View.OnClickListener() {
				
				public void onClick(View bttn) {
					changeAperture( -1 );
				}
			} );
	        buttonNext.setOnClickListener( new View.OnClickListener() {
				
				public void onClick(View bttn) {
					changeAperture( 1 );
				}
			} );
        }
        else
        {
        	buttonPrev.setVisibility(View.GONE);
        	buttonNext.setVisibility(View.GONE);
        }
        makeResultString();
    }
    @Override
    public void onBackPressed()
    {
    	finish();
    	super.onBackPressed();
    }
 }
