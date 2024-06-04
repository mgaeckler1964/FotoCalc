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
	double	width;
	double	height;
	double	bildGroesse;
	double	brennweite;
	double	blende;
	double	distanz;
	double	zeit;
	double	graufilter;
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
    	case R.id.calcVergFaktor:
    		calcVergFaktor();
    		break;
    	case R.id.rechneZeit:
    		calcTime();
    		break;
    	case R.id.KleinBild:
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
    		showResult( "Fotorechner", "Fotorechner 2.6.4\n(c) 2011-2024 by Martin Gäckler\nhttps://www.gaeckler.at/");
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

		width = -1;
		height = -1;
		brennweite = -1;
		blende = -1;
		distanz = -1;
		bildGroesse = -1;
		zeit = -1;
		graufilter = -1;

		if( (flags & NEED_FILTER) != 0 )
		{
			try
			{
				graufilter = Double.parseDouble(greyFilter.getText().toString());
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
				zeit = Double.parseDouble(timeStr);
				if (timeStr.indexOf('.') < 0)
					zeit = 1.0 / zeit;
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
				distanz = Double.parseDouble(distance.getText().toString());
				distanz *= 1000;
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
				blende = Double.parseDouble(aperture.getText().toString());
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
				brennweite = Double.parseDouble(focalLength.getText().toString());
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
				height = Double.parseDouble(imageHeight.getText().toString());
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_SIZE) == 0 )
					error = "Höhe fehlt oder hat falsches Format";
			}
			try
			{
				width = Double.parseDouble(imageWidth.getText().toString());
			}
			catch (NumberFormatException e)
			{
				if( (optional & NEED_SIZE) == 0 )
					error = "Breite fehlt oder hat falsches Format";
			}
			if( width > 0 && height > 0 )
				bildGroesse = Math.sqrt(width * width + height * height);
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

		if( bildGroesse > 0 && brennweite > 0 )
		{
			resultString = FotoCalculator.calcAngle( bildGroesse, brennweite );
		}

		showResult( "Bildwinkel", resultString );
	}
	private void calcDOF()
	{
		String	resultString = getData(NEED_SIZE|NEED_FOCAL_LENGTH|NEED_APERTURE|NEED_DISTANCE);

		if( bildGroesse > 0 && brennweite > 0 && blende > 0 && distanz > 0 )
		{
			resultString = FotoCalculator.calcDOF(bildGroesse, brennweite, blende, distanz);
		}
		showResult( "Schärfentiefe", resultString );
	}
	private void calcHyperDistance()
	{
		String	resultString = getData(NEED_SIZE|NEED_FOCAL_LENGTH|NEED_APERTURE);

		if( bildGroesse > 0 && brennweite > 0 && blende > 0 )
		{
			resultString = FotoCalculator.calcHyperDistance(bildGroesse, brennweite, blende);
		}

		showResult( "Hyperfokale Entfernung", resultString );
	}

	private void calcVergFaktor()
	{
		String	resultString = getData(NEED_DISTANCE|NEED_FOCAL_LENGTH|NEED_SIZE, NEED_SIZE);

		if( distanz>0 && brennweite>0 )
		{
			resultString = FotoCalculator.calcVergFaktor( distanz, brennweite, width, height );
		}

		showResult( "Vergrößerungsfaktor", resultString );
	}
	private void calcTime()
	{
		double	neueZeit;
		String	resultString = getData(NEED_TIME|NEED_FILTER);

		if( zeit > 0 && graufilter > 0 )
		{
			neueZeit = zeit * graufilter;
			getData(NEED_APERTURE);
    		showTimeResult( neueZeit, blende );
		}
		else
		{
			showResult( "Neue Zeit", resultString );
		}
	}
}