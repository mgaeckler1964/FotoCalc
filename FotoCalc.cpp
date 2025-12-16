/*
		Project:		FotoCalc
		Module:			FotoCalc.cpp
		Description:	The application and the main form with the calculations
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2025 Martin Gäckler

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


// --------------------------------------------------------------------- //
// ----- switches ------------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- includes ------------------------------------------------------ //
// --------------------------------------------------------------------- //

#include <gak/logfile.h>
#include <gak/fmtNumber.h>

#include <WINLIB/WINAPP.H>
#include <WINLIB/colors.h>

#include "FotoCalc_rc.h"
#include "foto.gui.h"

// --------------------------------------------------------------------- //
// ----- imported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module switches ----------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT-
#	pragma option -b
#	pragma option -a4
#	pragma option -pc
#endif

using namespace winlib;
using namespace winlibGUI;

// --------------------------------------------------------------------- //
// ----- constants ----------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- macros -------------------------------------------------------- //
// --------------------------------------------------------------------- //

double inline rechneVergroesserungAusBild( double objektGroesse, double pictureSize )
{
	double vergrFaktor = objektGroesse/pictureSize;

	return vergrFaktor;
}

double inline rechneVergroesserungAusObjektiv( double brennweite, double distanz )
{
	double vergrFaktor = -1;

	double det = pow(distanz/brennweite-2, 2)-4;
	if( det > 0 )
		vergrFaktor = ((distanz/brennweite-2) + sqrt( det )) / 2;
	else if( det == 0 )
		vergrFaktor = (distanz/brennweite-2) / 2;

	return vergrFaktor;
}

// --------------------------------------------------------------------- //
// ----- type definitions ---------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class definitions --------------------------------------------- //
// --------------------------------------------------------------------- //

class FotoMainWindow : public FotoFORM_form
{
	enum AUTO_RECHNE {
		AUTO_NIX, AUTO_FAKTOR, AUTO_DISTANZ
	} autoRechne;
	bool autoBildGroesse;

	void rechneVergFaktor( void );
	void rechneBildgroesse( void );
	void rechneDistanz( void );
	void rechneBildwinkel( void );
	void rechneSchaerfentiefe( void );

	void EditGroesseChange(EditControl *Sender);
	void EditDistanzChange(EditControl *Sender);
	void EditBrennweiteChange(EditControl *Sender);
	void EditVergrFaktorChange(EditControl *Sender);
	void EditBlendeChange(EditControl *Sender);

	virtual ProcessStatus handleCreate( void );
	virtual ProcessStatus handleCommand( int cmd );
	virtual ProcessStatus handleEditChange( int control );
	virtual ProcessStatus handleButtonClick( int control );

public:
	FotoMainWindow() : FotoFORM_form( NULL ) 
	{
	}
};

class FotoCalcApplication : public GuiApplication
{
	virtual bool 	startApplication( HINSTANCE /*hInstance*/, const char * /*cmdLine*/ )
	{
		setApplication("Foto");
		setComapny("gak");

		STRING	language = GetProfile( "", "language", "" );
		setCountry( language );
		return 0;
	}
	virtual CallbackWindow  *createMainWindow( const char * /*cmdLine*/, int /*nCmdShow*/ )
	{
		FotoMainWindow	*mainWindow = new FotoMainWindow;
		if( mainWindow->create( NULL ) == scERROR )
		{
			MessageBox( NULL, "Could not create window", "Error", MB_ICONERROR );
			delete mainWindow;
			mainWindow = NULL;
		}
		mainWindow->focus();
		mainWindow->EditObjektGroesse->focus();

		return mainWindow;
	}
	virtual void deleteMainWindow( BasicWindow  *mainWindow )
	{
		delete mainWindow;
	}

	public:
	FotoCalcApplication() : GuiApplication( IDI_FOTOCALC ) {}
};

// --------------------------------------------------------------------- //
// ----- exported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module static data -------------------------------------------- //
// --------------------------------------------------------------------- //

static FotoCalcApplication	fotoApplication;

// --------------------------------------------------------------------- //
// ----- class static data --------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- prototypes ---------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module functions ---------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class inlines ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class constructors/destructors -------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class static functions ---------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class privates ------------------------------------------------ //
// --------------------------------------------------------------------- //

//---------------------------------------------------------------------------
void FotoMainWindow::rechneVergFaktor( void )
{
	bool	rechneBildgroesse = true;
	char	buffer[128];

	double	vergrFaktor = 0.0;
	double	distanz = atof( EditDistanz->getText() ) * 1000.0;
	double	brennweite = atof( EditBrennweite->getText() );
	double	objektGroesse = atof( EditObjektGroesse->getText() );
	double	bildGroesse = atof( EditBildGroesse->getText() );

	if( distanz>0 && brennweite>0 )
		vergrFaktor = rechneVergroesserungAusObjektiv( brennweite, distanz );
	else if( objektGroesse > 0 && bildGroesse > 0 )
	{
		vergrFaktor = rechneVergroesserungAusBild( objektGroesse, bildGroesse );
		rechneBildgroesse = false;
	}

	if( vergrFaktor > 0.005 )
	{
		sprintf( buffer, "%.2f", vergrFaktor );
		EditVergrFaktor->setBackgroundColorByRef( colors::PALE_GREEN );
		EditVergrFaktor->setTag(1);
		EditVergrFaktor->setText( buffer );
		EditVergrFaktor->setTag(0);
		if( rechneBildgroesse )
			this->rechneBildgroesse();
	}
	else if( vergrFaktor < 0 )
		EditVergrFaktor->setBackgroundColorByRef( colors::SALMON );

}

void FotoMainWindow::rechneBildgroesse( void )
{
	char	buffer[128];
	double	pictureSize = 0;
	double	vergrFaktor = atof( EditVergrFaktor->getText() );
	double	objektGroesse = atof( EditObjektGroesse->getText() );

	*buffer = 0;
	if( vergrFaktor > 0 && objektGroesse > 0 )
		pictureSize = objektGroesse / vergrFaktor;

	if( pictureSize > 0.005 )
		sprintf( buffer, "%.2f", pictureSize );

	if( *buffer )
	{
		EditBildGroesse->setTag(1);
		EditBildGroesse->setBackgroundColorByRef( colors::PALE_GREEN );
		EditBildGroesse->setText( buffer );
		EditBildGroesse->setTag(0);
		autoBildGroesse = true;
	}
}

void FotoMainWindow::rechneDistanz( void )
{
	char	buffer[128];

	double brennweite=atof( EditBrennweite->getText() );
	double vergrFaktor=atof( EditVergrFaktor->getText() );
	*buffer = 0;

	if( brennweite > 0 && vergrFaktor > 0 )
	{
		double distanz=(vergrFaktor+1)*brennweite + (vergrFaktor+1)/vergrFaktor*brennweite;
		sprintf( buffer, "%.3f", distanz/1000 );
	}

	if( *buffer )
	{
		EditDistanz->setTag(1);
		EditDistanz->setBackgroundColorByRef( colors::PALE_GREEN );
		EditDistanz->setText( buffer );
		EditDistanz->setTag(0);
	}
}

void FotoMainWindow::rechneBildwinkel( void )
{
	char	buffer[128];
	double	bildGroesse = atof( EditBildGroesse->getText() );
	double	brennweite = atof( EditBrennweite->getText() );
	double	bildwinkel;

	if( bildGroesse > 0 && brennweite > 0 )
	{
		bildwinkel = 360 * atan( bildGroesse / (2*brennweite) ) / M_PI;
		sprintf( buffer, "%.2f", bildwinkel );
		EditBildwinkel->setBackgroundColorByRef( colors::PALE_GREEN );
		EditBildwinkel->setText( buffer );
	}
}

void FotoMainWindow::rechneSchaerfentiefe( void )
{
	char	buffer[128];
	double	bildGroesse = atof( EditBildGroesse->getText() );
	double	brennweite = atof( EditBrennweite->getText() );
	double	blende = atof( EditBlende->getText() );
	double	distanz = atof( EditDistanz->getText() ) * 1000.0;

	if( bildGroesse > 0 && brennweite > 0 && blende > 0 )
	{
		double zerstreuungskreis = bildGroesse/1500;
		double hyperfokaleEntfernung = brennweite*brennweite / (blende*zerstreuungskreis) + brennweite;

		sprintf( buffer, "%.3f", hyperfokaleEntfernung/1000 );
		EditHyperfokaleDistanz->setBackgroundColorByRef( colors::PALE_GREEN );
		EditHyperfokaleDistanz->setText( buffer );

		if( distanz > 0 )
		{
			double minDistanz = distanz*hyperfokaleEntfernung / (hyperfokaleEntfernung+distanz-brennweite);
			sprintf( buffer, "%.3f", minDistanz/1000 );
			EditMinDistanz->setBackgroundColorByRef( colors::PALE_GREEN );
			EditMinDistanz->setText( buffer );

			double quotient = hyperfokaleEntfernung-distanz+brennweite;
			if( quotient > 0 )
			{
				double maxDistanz = distanz*hyperfokaleEntfernung / quotient;
				sprintf( buffer, "%.3f", maxDistanz/1000.0 );
//				EditMaxDistanz->Font->Name = "MS Sans Serif";
				EditMaxDistanz->setText( buffer );
			}
			else
			{
//				EditMaxDistanz->Font->Name = "Symbol";
				EditMaxDistanz->setText( "\xA5" );
			}

			EditMaxDistanz->setBackgroundColorByRef( colors::PALE_GREEN );
		}
	}
}

void FotoMainWindow::EditGroesseChange(EditControl *Sender)
{
	if( !Sender->getTag() )
	{
		if( Sender == EditBildGroesse )
		{
			autoBildGroesse = false;
			EditBildGroesse->setBackgroundColorByRef( colors::WHITE );
		}

		if( autoBildGroesse )
			rechneBildgroesse();
		else
		{
			char	buffer[128];

			double	vergrFaktor = 0.0;
			double	objektGroesse = atof( EditObjektGroesse->getText() );
			double	bildGroesse = atof( EditBildGroesse->getText() );

			*buffer = 0;
			if( objektGroesse > 0 && bildGroesse > 0 )
				vergrFaktor = rechneVergroesserungAusBild( objektGroesse, bildGroesse );

			if( vergrFaktor > 0.005 )
				sprintf( buffer, "%.2f", vergrFaktor );

			if( *buffer )
			{
				EditVergrFaktor->setTag(1);
				EditVergrFaktor->setBackgroundColorByRef( colors::PALE_GREEN );
				EditVergrFaktor->setText( buffer );
				EditVergrFaktor->setTag(0);
				rechneDistanz();
			}
		}
	}

	if( Sender == EditBildGroesse )
	{
		rechneBildwinkel();
		rechneSchaerfentiefe();
	}
}

void FotoMainWindow::EditDistanzChange(EditControl *Sender)
{
	if( !Sender->getTag() )
	{
		rechneVergFaktor();
		autoRechne = AUTO_FAKTOR;

		LabelDistanz->getFont().setNormal();
		LabelFaktor->getFont().setBold();
		EditDistanz->setBackgroundColorByRef( colors::WHITE );
		invalidateWindow();
	}
	rechneSchaerfentiefe();
}

void FotoMainWindow::EditBrennweiteChange(EditControl *)
{
	rechneBildwinkel();
	rechneSchaerfentiefe();

	if( autoRechne == AUTO_FAKTOR || EditVergrFaktor->getText().isEmpty() )
	{
		rechneVergFaktor();
		if( EditVergrFaktor->getText() > "" )
		{
			autoRechne = AUTO_FAKTOR;
			LabelDistanz->getFont().setNormal();
			LabelFaktor->getFont().setBold();
			invalidateWindow();
		}
	}
	if( autoRechne == AUTO_DISTANZ || EditDistanz->getText().isEmpty() )
	{
		rechneDistanz();
		if( EditDistanz->getText() > "" )
		{
			autoRechne = AUTO_DISTANZ;
			LabelDistanz->getFont().setBold();
			LabelFaktor->getFont().setNormal();
			invalidateWindow();
		}
	}
}

void FotoMainWindow::EditVergrFaktorChange(EditControl *Sender)
{
	if( !Sender->getTag() )
	{
		EditVergrFaktor->setBackgroundColorByRef( colors::WHITE );
		rechneBildgroesse();
		rechneDistanz();
		autoRechne = AUTO_DISTANZ;
		LabelDistanz->getFont().setBold();
		LabelFaktor->getFont().setNormal();
		invalidateWindow();
	}
}

void FotoMainWindow::EditBlendeChange(EditControl *)
{
	rechneSchaerfentiefe();
}

// --------------------------------------------------------------------- //
// ----- class protected ----------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class virtuals ------------------------------------------------ //
// --------------------------------------------------------------------- //
   
ProcessStatus FotoMainWindow::handleCreate( void )
{
	PopupMenu *popup = appObject->loadMenuNew<PopupMenu>(SizeMenu_id);
	EditBildGroesse->setPopupMenu(popup);
	return psDO_DEFAULT;
}

ProcessStatus FotoMainWindow::handleCommand( int menuId )
{
	switch(menuId)
	{
	case SPWidth36mm_id:
		EditBildGroesse->setText("36");
		break;
	case SpHeight24mm_id:
		EditBildGroesse->setText("24");
		break;
	case SpDiagonal4327mm_id:
		EditBildGroesse->setText("43.27");
		break;

	case ApsWidth236mm_id:
		EditBildGroesse->setText("23.6");
		break;
	case ApsHeight158mm_id:
		EditBildGroesse->setText("15.8");
		break;
	case ApsDiagonal284mm_id:
		EditBildGroesse->setText("28.4");
		break;

	case MicroFourThirdsWidth1731mm_id:
		EditBildGroesse->setText("17,31");
		break;
	case MicroFourThirdsHeight1998mm_id:
		EditBildGroesse->setText("19.98");
		break;
	case MicroFourThirdsDiagonal2163mm_id:
		EditBildGroesse->setText("21.63");
		break;

	case Nikon1width132mm_id:
		EditBildGroesse->setText("13.2");
		break;
	case Nikon1Height88mm_id:
		EditBildGroesse->setText("8.8");
		break;
	case  Nikon1Diagonal1586mm_id:
		EditBildGroesse->setText("15.86");
		break;

	case SamsungWidth816mm_id:
		EditBildGroesse->setText("8.16");
		break;
	case SamsungHeight612mm_id:
		EditBildGroesse->setText("6.12");
		break;
	case SamsungDiagonal1012mm_id:
		EditBildGroesse->setText("10.12");
		break;

	case Width616mm_id:
		EditBildGroesse->setText("6.16");
		break;
	case Width718mm_id:
		EditBildGroesse->setText("7.18");
		break;
	case Width76mm_id:
		EditBildGroesse->setText("7.6");
		break;

	case Height462mm_id:
		EditBildGroesse->setText("4.62");
		break;
	case Height532mm_id:
		EditBildGroesse->setText("5.32");
		break;
	case Height57mm_id:
		EditBildGroesse->setText("5.7");
		break;

	case Diagonal77mm_id:
		EditBildGroesse->setText("7.7");
		break;
	case Diagonal893mm_id:
		EditBildGroesse->setText("8.93");
		break;
	case Diagonal95mm_id:
		EditBildGroesse->setText("9.5");
		break;


	default:
		return psDO_DEFAULT;
	}
	return psPROCESSED;
}

ProcessStatus FotoMainWindow::handleEditChange( int control )
{
	switch( control )
	{
	case EditObjektGroesse_id:
		EditGroesseChange(EditObjektGroesse);
		break;
	case EditBildGroesse_id:
		EditGroesseChange(EditBildGroesse);
		break;
	case EditDistanz_id:
		EditDistanzChange(EditDistanz);
		break;
	case EditBrennweite_id:
		EditBrennweiteChange(EditBrennweite);
		break;
	case EditVergrFaktor_id:
		EditVergrFaktorChange(EditVergrFaktor);
		break;
	case EditBlende_id:
		EditBlendeChange(EditVergrFaktor);
		break;
	}

	return psDO_DEFAULT;
}

ProcessStatus FotoMainWindow::handleButtonClick( int buttonID )
{
	switch( buttonID )
	{
		case ButtonRechneDistanz_id:
		{
			rechneDistanz();
			autoRechne = AUTO_DISTANZ;
			LabelDistanz->getFont().setBold();
			LabelFaktor->getFont().setNormal();
			invalidateWindow();
			break;
		}
		case ButtonRechneVergr_id:
		{
			rechneVergFaktor();
			autoRechne = AUTO_FAKTOR;
			LabelDistanz->getFont().setNormal();
			LabelFaktor->getFont().setBold();
			invalidateWindow();
			break;
		}
		case ButtonNeustart_id:
		{
			autoBildGroesse = true;
			EditDistanz->setBackgroundColorByRef(colors::WHITE);
			EditDistanz->setText( "" );
			EditBrennweite->setText( "" );
			EditVergrFaktor->setText( "" );
			EditVergrFaktor->setBackgroundColorByRef(colors::WHITE);
			EditObjektGroesse->setText( "" );
			EditBildGroesse->setBackgroundColorByRef(colors::WHITE);
			EditBildGroesse->setText( "" );
			EditBildwinkel->setBackgroundColorByRef(colors::WHITE);
			EditBildwinkel->setText( "" );
			EditHyperfokaleDistanz->setBackgroundColorByRef(colors::WHITE);
			EditHyperfokaleDistanz->setText( "" );
			EditMinDistanz->setBackgroundColorByRef(colors::WHITE);
			EditMinDistanz->setText( "" );
			EditMaxDistanz->setBackgroundColorByRef(colors::WHITE);
			EditMaxDistanz->setText( "" );
			EditBlende->setText( "" );

			autoRechne = AUTO_NIX;
			LabelDistanz->getFont().setNormal();
			LabelFaktor->getFont().setNormal();
			invalidateWindow();
			break;
		}
		case ButtonLanguage_id:
		{
			char buffer[1024];
			GetModuleFileName( NULL, buffer, sizeof( buffer ) );
			STRING oldLanguage = appObject->getCountry();
			doLogValue(oldLanguage);

			if( oldLanguage != "de" )
			{
				appObject->WriteProfile( false, "", "language", "de" );
			}
			else
			{
				appObject->WriteProfile( false, "", "language", "en" );
			}

			WinExec( buffer, SW_SHOW );

			exit( 0 );

			break;
		}

		default:
			return FotoFORM_form::handleButtonClick( buttonID );
	}
	return psPROCESSED;
}

// --------------------------------------------------------------------- //
// ----- class publics ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- entry points -------------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT.
#	pragma option -b.
#	pragma option -a.
#	pragma option -p.
#endif

