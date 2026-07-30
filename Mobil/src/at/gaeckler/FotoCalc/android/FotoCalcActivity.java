/*
		Project:		FotoCalc
		Module:			FotoCalcActivity.java
		Description:	the android main activitiy for the calculator
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

import android.os.Build;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.EditText;
import android.content.*;

import androidx.appcompat.app.AppCompatDelegate;

import at.gaeckler.FotoCalc.FotoCalculator;
import at.gaeckler.MyActivity;

public class FotoCalcActivity extends MyActivity
{
	// these variables are borrowed from FotoCalcForm for JavaME
	private double	m_width;
	private double	m_height;
	private double	m_picSize;
	private double	m_focalLength;
	private double	m_aperture;
	private double	m_distance;
	private double	m_time;
	private double	m_greyFilter;
	private static final int NEED_SIZE			= 1;
	private static final int NEED_FOCAL_LENGTH	= 2;
	private static final int NEED_APERTURE		= 4;
	private static final int NEED_DISTANCE		= 8;
	private static final int NEED_TIME			= 16;
	private static final int NEED_FILTER		= 32;
	private static final String CONFIGURATION = "fotoCalc.cfg";
	private static final String			DARK_MODE_KEY = "darkMode";
	private static final String			GREY_KEY = "greyFilter";
	public static final String			TIME_KEY = "time";
	private static final String			DIST_KEY = "distance";
	public static final String			APERTURE_KEY = "aperture";
	private static final String			FOCAL_KEY = "focalLength";
	private static final String			HEIGHT_KEY = "imageHeight";
	private static final String			WIDTH_KEY = "imageWidth";

	EditText	greyFilter, time, distance, aperture, focalLength, imageHeight, imageWidth;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		greyFilter = findViewById( R.id.greyFilter );
		time = findViewById( R.id.time );
		distance = findViewById( R.id.distance );
		aperture = findViewById( R.id.aperture );
		focalLength = findViewById( R.id.focalLength );
		imageHeight = findViewById( R.id.imageHeight );
		imageWidth = findViewById( R.id.imageWidth );

		loadData();

		switchColorMode();
	}
	@Override
	public boolean onCreateOptionsMenu( android.view.Menu menu )
	{
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.fc_menu, menu);

		return super.onCreateOptionsMenu(menu);
	}

	@Override
	public boolean onPrepareOptionsMenu(Menu menu)
	{
		menu.findItem(R.id.darkMode).setChecked(m_darkMode);

		return super.onPrepareOptionsMenu(menu);
	}

	@Override
	public boolean onOptionsItemSelected( MenuItem item )
	{
		int	itemId = item.getItemId();
		//System.out.println( itemId );
		if( itemId == R.id.exit ) {
			finish();
		}
		else if( itemId == R.id.calcDOF ) {
			calcDOF();
		}
		else if( itemId == R.id.calcAngle ) {
			calcAngle();
		}
		else if( itemId == R.id.calcHyperDistance ) {
			calcHyperDistance();
		}
		else if( itemId == R.id.calcSizeFactor ) {
			calcSizeFactor();
		}
		else if( itemId == R.id.calcTime ) {
			calcTime();
		}
		else if( itemId == R.id.SmallPicture ) {
			imageWidth.setText("36");
			imageHeight.setText("24");
		}
		else if( itemId == R.id.apsNikon ) {
			imageWidth.setText("23.6");
			imageHeight.setText("15.8");
		}
		else if( itemId == R.id.fourThirds ) {
			imageWidth.setText("17.31");
			imageHeight.setText("12.98");
		}
		else if( itemId == R.id.nikon1 ) {
			imageWidth.setText("13.2");
			imageHeight.setText("8.8");
		}
		else if( itemId == R.id.SamsungA55 ) {
			imageWidth.setText("8.16");
			imageHeight.setText("6.12");
		}
		else if( itemId == R.id.compact17 ) {
			imageWidth.setText("7.6");
			imageHeight.setText("5.7");
		}
		else if( itemId == R.id.compact18 ) {
			imageWidth.setText("7.18");
			imageHeight.setText("5.32");
		}
		else if( itemId == R.id.compact23 ) {
			imageWidth.setText("6.16");
			imageHeight.setText("4.62");
		}
		else if( itemId == R.id.about ) {
			String name = getString(R.string.app_name);
			String version = getString(R.string.app_version);
			String app_copyright = getString(R.string.app_copyright);
			String url = getString(R.string.app_url);
			showResult(
				name,
				name + " " + version + "\n" + app_copyright + "\n" + url
			);
		}
		else if( itemId == R.id.restart ) {
			greyFilter.setText( "" );
			time.setText( "" );
			distance.setText( "" );
			aperture.setText( "" );
			focalLength.setText( "" );
			imageHeight.setText( "" );
			imageWidth.setText( "" );
		}
		else if( itemId == R.id.darkMode )
		{
			m_darkMode = !m_darkMode;
			switchColorMode();
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
		getSharedPreferences(CONFIGURATION, Context.MODE_PRIVATE).edit()
			.putString(GREY_KEY, greyFilter.getText().toString())
			.putString(TIME_KEY, time.getText().toString())
			.putString(DIST_KEY, distance.getText().toString())
			.putString(APERTURE_KEY, aperture.getText().toString())
			.putString(FOCAL_KEY, focalLength.getText().toString())
			.putString(HEIGHT_KEY, imageHeight.getText().toString())
			.putString(WIDTH_KEY, imageWidth.getText().toString())
			.putBoolean(DARK_MODE_KEY, m_darkMode)
			.apply()
		;
	}

	private void loadData()
	{
		SharedPreferences settings = getSharedPreferences(CONFIGURATION, 0);

		greyFilter.setText(settings.getString(GREY_KEY, ""));
		time.setText(settings.getString(TIME_KEY, ""));
		distance.setText(settings.getString(DIST_KEY, ""));
		aperture.setText(settings.getString(APERTURE_KEY, ""));
		focalLength.setText(settings.getString(FOCAL_KEY, ""));
		imageHeight.setText(settings.getString(HEIGHT_KEY, ""));
		imageWidth.setText(settings.getString(WIDTH_KEY, ""));
		m_darkMode = settings.getBoolean(DARK_MODE_KEY, true);
	}

	private void showResult( String title, String resultString )
	{
		showMessage( R.drawable.foto, title, resultString, false, null );
	}
	private void showTimeResult( double neueZeit, double blende )
	{
		Intent intent = new Intent( this, ResultScreen.class );
		intent.putExtra( TIME_KEY, neueZeit );
		intent.putExtra( APERTURE_KEY, blende );
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
		double	newTime;
		String	resultString = getData(NEED_TIME|NEED_FILTER);

		if( m_time > 0 && m_greyFilter > 0 )
		{
			newTime = m_time * m_greyFilter;
			getData(NEED_APERTURE);
			showTimeResult( newTime, m_aperture );
		}
		else
		{
			showResult( "Neue Zeit", resultString );
		}
	}

	private boolean m_darkMode=true;
	private void switchColorMode()
	{
		if( m_darkMode )
		{
			AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
		}
		else
		{
			AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO);
		}
	}
}