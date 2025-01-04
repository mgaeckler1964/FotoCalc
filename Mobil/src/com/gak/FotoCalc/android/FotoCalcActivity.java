/*
		Project:		FotoCalc
		Module:			FotoCalcActivity.java
		Description:	the android main activitiy for the calculator
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

import android.app.Activity;
import android.os.Build;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.EditText;
import android.app.AlertDialog;
import android.content.*;

import com.gak.FotoCalc.android.R;
import com.gak.FotoCalc.FotoCalculator;

public class FotoCalcActivity extends Activity
{
	// these variables are borrowed from FotoCalcForm for JavaME
	double	m_width;
	double	m_height;
	double	m_picSize;
	double	m_focalLength;
	double	m_aperture;
	double	m_distance;
	double	m_time;
	double	m_greyFilter;
	static final int NEED_SIZE			= 1;
	static final int NEED_FOCAL_LENGTH	= 2;
	static final int NEED_APERTURE		= 4;
	static final int NEED_DISTANCE		= 8;
	static final int NEED_TIME			= 16;
	static final int NEED_FILTER		= 32;
	static final String CONFIGURATION = "fotoCalc.cfg";
	
	EditText	greyFilter, time, distance, aperture, focalLength, imageHeight, imageWidth;

	/** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        greyFilter = (EditText)findViewById( R.id.greyFilter );
        time = (EditText)findViewById( R.id.time );
        distance = (EditText)findViewById( R.id.distance );
        aperture = (EditText)findViewById( R.id.aperture );
        focalLength = (EditText)findViewById( R.id.focalLength );
        imageHeight = (EditText)findViewById( R.id.imageHeight );
        imageWidth = (EditText)findViewById( R.id.imageWidth );

        SharedPreferences settings = getSharedPreferences(CONFIGURATION, 0);
        greyFilter.setText( settings.getString("greyFilter", "") );
        time.setText( settings.getString("time", "") );
        distance.setText( settings.getString("distance", "") );
        aperture.setText( settings.getString("aperture", "") );
        focalLength.setText( settings.getString("focalLength", "") );
        imageHeight.setText( settings.getString("imageHeight", "") );
        imageWidth.setText( settings.getString("imageWidth", "") );
    }
    @Override
    public boolean onCreateOptionsMenu( android.view.Menu menu )
    {
    	MenuInflater inflater = getMenuInflater();
    	inflater.inflate(R.menu.fc_menu, menu);
    	
    	return super.onCreateOptionsMenu(menu);
    }
    
    @Override
    public boolean onOptionsItemSelected( MenuItem item )
    {
    	int	itemId = item.getItemId();
    	//System.out.println( itemId );
    	switch( itemId )
    	{
    	case R.id.exit:
    		finish();
    		break;
    	case R.id.calcDOF:
    		calcDOF();
    		break;
    	case R.id.calcAngle:
    		calcAngle();
    		break;
    	case R.id.calcHyperDistance:
    		calcHyperDistance();
    		break;
    	case R.id.calcSizeFactor:
    		calcSizeFactor();
    		break;
    	case R.id.calcTime:
    		calcTime();
    		break;
    	case R.id.SmallPicture:
    		imageWidth.setText("36");
    		imageHeight.setText("24");
    		break;
    	case R.id.apsNikon:
    		imageWidth.setText("23.6");
    		imageHeight.setText("15.8");
    		break;
    	case R.id.fourThirds:
    		imageWidth.setText("17.31");
    		imageHeight.setText("12.98");
    		break;   
    	case R.id.nikon1:
    		imageWidth.setText("13.2");
    		imageHeight.setText("8.8");
    		break;
    	case R.id.SamsungA55:
    		imageWidth.setText("8.16");
    		imageHeight.setText("6.12");
    		break;
    	case R.id.compact17:
    		imageWidth.setText("7.6");
    		imageHeight.setText("5.7");
    		break;   
    	case R.id.compact18:
    		imageWidth.setText("7.18");
    		imageHeight.setText("5.32");
    		break;   
    	case R.id.compact23:
    		imageWidth.setText("6.16");
    		imageHeight.setText("4.62");
    		break;   
    	case R.id.about:
    		String name = getString(R.string.app_name);
    		String version = getString(R.string.app_version);
    		String copyinfo = getString(R.string.app_copyinfo);
    		String url = getString(R.string.app_url);
    		showResult( 
    			name, 
    			name + " " + version + "\n" +
    			copyinfo + "\n" +
    			url
    		);
    		break;
    	case R.id.restart:
            greyFilter.setText( "" );
            time.setText( "" );
            distance.setText( "" );
            aperture.setText( "" );
            focalLength.setText( "" );
            imageHeight.setText( "" );
            imageWidth.setText( "" );
            break;
    	}

    	return super.onOptionsItemSelected(item);
    }

    @Override
    public void onOptionsMenuClosed(Menu menu) {
        super.onOptionsMenuClosed(menu);
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.CUR_DEVELOPMENT) {
            // Workaround for https://issuetracker.google.com/issues/315761686
            invalidateOptionsMenu();
        }
    }
    
    @Override
    public void onPause()
    {
    	super.onPause();
    	saveData();
    }
    
    private void saveData()
    {
    	SharedPreferences settings = getSharedPreferences(CONFIGURATION, 0);
        SharedPreferences.Editor editor = settings.edit();
        editor.putString("greyFilter", greyFilter.getText().toString());
        editor.putString("time", time.getText().toString());
        editor.putString("distance", distance.getText().toString());
        editor.putString("aperture", aperture.getText().toString());
        editor.putString("focalLength", focalLength.getText().toString());
        editor.putString("imageHeight", imageHeight.getText().toString());
        editor.putString("imageWidth", imageWidth.getText().toString());

        // Commit the edits!
        editor.commit();
    }
    private void showResult( String title, String resultString )
    {
    	AlertDialog.Builder builder = new AlertDialog.Builder(this);
    	builder.setMessage(resultString)
    		   .setTitle(title)
    	       .setCancelable(false)
    	       .setNegativeButton("Fertig", new DialogInterface.OnClickListener() {
    	           public void onClick(DialogInterface dialog, int id) {
    	                dialog.cancel();
    	           }
    	       })
    	       .setIcon(R.drawable.foto);
    	AlertDialog alert = builder.create();
    	alert.show();
    }
    private void showTimeResult( double neueZeit, double blende )
    {
    	Intent intent = new Intent( this, ResultScreen.class );
    	intent.putExtra( "neueZeit", neueZeit );
    	intent.putExtra( "blende", blende );
    	startActivity( intent );
    }
	private String getData( int flags, int optional )
	{
		String	error = "";

		m_width = -1;
		m_height = -1;
		m_focalLength = -1;
		m_aperture = -1;
		m_distance = -1;
		m_picSize = -1;
		m_time = -1;
		m_greyFilter = -1;

		if( (flags & NEED_FILTER) != 0 )
		{
			try
			{
				m_greyFilter = Double.parseDouble(greyFilter.getText().toString());
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_FILTER) == 0 )
					error = "Graufilter fehlt oder hat falsches Format";
			}
		}

		if( (flags & NEED_TIME) != 0 )
		{
			try
			{
				String timeStr = time.getText().toString();
				m_time = Double.parseDouble(timeStr);
				if (timeStr.indexOf('.') < 0)
					m_time = 1.0 / m_time;
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_TIME) == 0 )
					error = "Belichtungszeit fehlt oder hat falsches Format";
			}
		}

		if( (flags & NEED_DISTANCE) != 0 )
		{
		try
			{
				m_distance = Double.parseDouble(distance.getText().toString());
				m_distance *= 1000;
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_DISTANCE) == 0 )
					error = "Entfernung fehlt oder hat falsches Format";
			}
		}

		if( (flags & NEED_APERTURE) != 0 )
		{
			try
			{
				m_aperture = Double.parseDouble(aperture.getText().toString());
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_APERTURE) == 0 )
					error = "Blende fehlt oder hat falsches Format";
			}
		}

		if( (flags & NEED_FOCAL_LENGTH) != 0 )
		{
			try
			{
				m_focalLength = Double.parseDouble(focalLength.getText().toString());
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_FOCAL_LENGTH) == 0 )
					error = "Brennweite fehlt oder hat falsches Format";
			}
		}

		if( (flags & NEED_SIZE) != 0 )
		{
			try
			{
				m_height = Double.parseDouble(imageHeight.getText().toString());
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_SIZE) == 0 )
					error = "Höhe fehlt oder hat falsches Format";
			}
			try
			{
				m_width = Double.parseDouble(imageWidth.getText().toString());
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_SIZE) == 0 )
					error = "Breite fehlt oder hat falsches Format";
			}
			if( m_width > 0 && m_height > 0 )
				m_picSize = Math.sqrt(m_width * m_width + m_height * m_height);
		}

		return error;
	}

	private String getData( int flags )
	{
		return getData( flags, 0 );
	}
	private void calcAngle()
	{
		String	resultString = getData( NEED_SIZE|NEED_FOCAL_LENGTH );

		if( m_picSize > 0 && m_focalLength > 0 )
		{
			resultString = FotoCalculator.calcAngle( m_picSize, m_focalLength );
		}

		showResult( "Bildwinkel", resultString );
	}
	private void calcDOF()
	{
		String	resultString = getData(NEED_SIZE|NEED_FOCAL_LENGTH|NEED_APERTURE|NEED_DISTANCE);

		if( m_picSize > 0 && m_focalLength > 0 && m_aperture > 0 && m_distance > 0 )
		{
			resultString = FotoCalculator.calcDOF(m_picSize, m_focalLength, m_aperture, m_distance);
		}
		showResult( "Schärfentiefe", resultString );
	}
	private void calcHyperDistance()
	{
		String	resultString = getData(NEED_SIZE|NEED_FOCAL_LENGTH|NEED_APERTURE);

		if( m_picSize > 0 && m_focalLength > 0 && m_aperture > 0 )
		{
			resultString = FotoCalculator.calcHyperDistance(m_picSize, m_focalLength, m_aperture);
		}

		showResult( "Hyperfokale Entfernung", resultString );
	}

	private void calcSizeFactor()
	{
		String	resultString = getData(NEED_DISTANCE|NEED_FOCAL_LENGTH|NEED_SIZE, NEED_SIZE);

		if( m_distance>0 && m_focalLength>0 )
		{
			resultString = FotoCalculator.calcSizeFactor( m_distance, m_focalLength, m_width, m_height );
		}

		showResult( "Vergrößerungsfaktor", resultString );
	}
	private void calcTime()
	{
		double	neueZeit;
		String	resultString = getData(NEED_TIME|NEED_FILTER);

		if( m_time > 0 && m_greyFilter > 0 )
		{
			neueZeit = m_time * m_greyFilter;
			getData(NEED_APERTURE);
    		showTimeResult( neueZeit, m_aperture );
		}
		else
		{
			showResult( "Neue Zeit", resultString );
		}
	}
}