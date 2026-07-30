/*
		Project:		FotoCalc
		Module:			ResultScreen.java
		Description:	the android result activitiy for the calculator
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

package at.gaeckler.FotoCalc.android;

import static at.gaeckler.FotoCalc.android.FotoCalcActivity.APERTURE_KEY;
import static at.gaeckler.FotoCalc.android.FotoCalcActivity.TIME_KEY;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import at.gaeckler.MyActivity;

public class ResultScreen extends MyActivity
{
	double m_newTime;
	double m_aperture;
	Button	buttonPrev, buttonOK, buttonNext;
	TextView resultView;

	public static final int[] s_times =
	{
		1, 2, 3, 4, 5, 6, 8, 10, 13, 15, 20, 25, 30, 40, 45, 50, 60, 80,
		90, 100, 125, 160, 180, 200, 250, 320, 350, 400, 500, 640, 750,
		800, 1000, 1250, 1500, 1600, 2000, 2500, 3000, 3200, 4000, 8000, -1
	};

	public static final double[] s_apertures =
	{
		1, 1.4, 1.8, 2, 2.2, 2.4, 2.5, 2.8, 3.2, 3.3, 3.5, 4, 4.5, 4.8, 5, 5.6,
		6.3, 6.7, 7.1, 8, 9, 9.5, 10, 11, 13, 14, 16, 18, 19, 20, 22, 32, -1
	};

	private void makeResultString()
	{
		int i;

		String resultString = "";
		if( m_newTime < 1 )
		{
			for(i=0; s_times[i]>0; i++ )
			{
				if( m_newTime >= 1.0/ s_times[i] )
					break;
			}

			if( m_newTime > 1.0/ s_times[i] )
			{
				if (i > 0)
					resultString += "1/" + s_times[i - 1] +
						" > ";
				resultString += "1/" + Math.ceil(10/ m_newTime)/10;

				if( s_times[i] > 0 )
					resultString += " > ";
			}
			if( s_times[i] > 0 )
				resultString += "1/" + s_times[i];
		}
		else
			resultString += Math.ceil( m_newTime * 10 ) / 10 + '"';
		
		if( m_aperture > 0 )
			resultString += "\n" + Math.ceil( m_aperture * 10 ) / 10;
		resultView.setText(resultString);
	}

	private void changeAperture( int keyCode )
	{
		if( m_aperture > 0 )
		{
			int		i;
			double	newAperture = m_aperture;

			for(i=0; s_apertures[i] > 0; i++ )
				if( s_apertures[i] > m_aperture)
					break;

			if( keyCode == 1 && s_apertures[i]>0 )
				newAperture = s_apertures[i];
			else if( keyCode == -1 && i>0 )
			{
				newAperture = s_apertures[i - 1];
				if (newAperture == m_aperture && i > 1)
					newAperture = s_apertures[i-2];
			}
			if( newAperture != m_aperture)
			{
				double factor = (newAperture*newAperture) / (m_aperture * m_aperture);
				m_newTime = m_newTime * factor;
				m_aperture = newAperture;
				makeResultString();
			}
		}
	}

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.result_screen);

		Intent intent = getIntent();
		m_newTime = intent.getDoubleExtra(TIME_KEY, 0);
		m_aperture = intent.getDoubleExtra(APERTURE_KEY, -1);

		buttonPrev = findViewById( R.id.buttonPrev );
		buttonOK = findViewById( R.id.buttonOK );
		buttonNext = findViewById( R.id.buttonNext );
		resultView = findViewById( R.id.resultString );

		buttonOK.setOnClickListener( (bttn) -> finish());
		if( m_aperture > 0 )
		{
			buttonPrev.setOnClickListener( (bttn) -> changeAperture( -1 ) );
			buttonNext.setOnClickListener( (bttn) -> changeAperture( 1 ) );
		}
		else
		{
			buttonPrev.setVisibility(View.GONE);
			buttonNext.setVisibility(View.GONE);
		}
		makeResultString();
	}
}
