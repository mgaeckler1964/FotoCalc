/*
		Project:		FotoCalc
		Module:			fotoFrm.cpp
		Description:	the main form with the calculations
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

//---------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>

#include <vcl.h>
#pragma hdrstop

#include "fotoFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFotorechnerForm *FotorechnerForm;

//---------------------------------------------------------------------------
double inline rechneVergroesserungAusBild( double objektGroesse, double pictureSize )
{
	double vergrFaktor = objektGroesse/pictureSize;

	return vergrFaktor;
}

//---------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
void TFotorechnerForm::rechneVergFaktor( void )
{
	bool	rechneBildgroesse = true;
	char	buffer[128];

	double	vergrFaktor = 0.0;
	double	distanz = atof( EditDistanz->Text.c_str() ) * 1000.0;
	double	brennweite = atof( EditBrennweite->Text.c_str() );
	double	objektGroesse = atof( EditObjektGroesse->Text.c_str() );
	double	bildGroesse = atof( EditBildGroesse->Text.c_str() );

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
		EditVergrFaktor->Color = (TColor)0xAAFFAA;
		EditVergrFaktor->Tag = 1;
		EditVergrFaktor->Text = buffer;
		EditVergrFaktor->Tag = 0;
		if( rechneBildgroesse )
			this->rechneBildgroesse();
	}
	else if( vergrFaktor < 0 )
		EditVergrFaktor->Color = (TColor)0xAAAAFF;

}

//---------------------------------------------------------------------------
void TFotorechnerForm::rechneBildgroesse( void )
{
	char	buffer[128];
	double	pictureSize = 0;
	double	vergrFaktor = atof( EditVergrFaktor->Text.c_str() );
	double	objektGroesse = atof( EditObjektGroesse->Text.c_str() );

	*buffer = 0;
	if( vergrFaktor > 0 && objektGroesse > 0 )
		pictureSize = objektGroesse / vergrFaktor;

	if( pictureSize > 0.005 )
		sprintf( buffer, "%.2f", pictureSize );

	if( *buffer )
	{
		EditBildGroesse->Tag = 1;
		EditBildGroesse->Color = (TColor)0xAAFFAA;
		EditBildGroesse->Text = buffer;
		EditBildGroesse->Tag = 0;
		autoBildGroesse = true;
	}
}

//---------------------------------------------------------------------------
void TFotorechnerForm::rechneDistanz( void )
{
	char	buffer[128];

	double brennweite=atof( EditBrennweite->Text.c_str() );
	double vergrFaktor=atof( EditVergrFaktor->Text.c_str() );
	*buffer = 0;

	if( brennweite > 0 && vergrFaktor > 0 )
	{
		double distanz=(vergrFaktor+1)*brennweite + (vergrFaktor+1)/vergrFaktor*brennweite;
		sprintf( buffer, "%.3f", distanz/1000 );
	}

	if( *buffer )
	{
		EditDistanz->Color = (TColor)0xAAFFAA;
		EditDistanz->Tag = 1;
		EditDistanz->Text = buffer;
		EditDistanz->Tag = 0;
	}
}
//---------------------------------------------------------------------------
void TFotorechnerForm::rechneBildwinkel( void )
{
	char	buffer[128];
	double	bildGroesse = atof( EditBildGroesse->Text.c_str() );
	double	brennweite = atof( EditBrennweite->Text.c_str() );
	double	bildwinkel;

	if( bildGroesse > 0 && brennweite > 0 )
	{
		bildwinkel = 360 * atan( bildGroesse / (2*brennweite) ) / M_PI;
		sprintf( buffer, "%.2f", bildwinkel );
		EditBildwinkel->Color = (TColor)0xAAFFAA;
		EditBildwinkel->Text = buffer;
	}
}

//---------------------------------------------------------------------------
void TFotorechnerForm::rechneSchaerfentiefe( void )
{
	char	buffer[128];
	double	bildGroesse = atof( EditBildGroesse->Text.c_str() );
	double	brennweite = atof( EditBrennweite->Text.c_str() );
	double	blende = atof( EditBlende->Text.c_str() );
	double	distanz = atof( EditDistanz->Text.c_str() ) * 1000.0;

	if( bildGroesse > 0 && brennweite > 0 && blende > 0 )
	{
		double zerstreuungskreis = bildGroesse/1500;
		double hyperfokaleEntfernung = brennweite*brennweite / (blende*zerstreuungskreis) + brennweite;

		sprintf( buffer, "%.3f", hyperfokaleEntfernung/1000 );
		EditHyperfokaleDistanz->Color = (TColor)0xAAFFAA;
		EditHyperfokaleDistanz->Text = buffer;

		if( distanz > 0 )
		{
			double minDistanz = distanz*hyperfokaleEntfernung / (hyperfokaleEntfernung+distanz-brennweite);
			sprintf( buffer, "%.3f", minDistanz/1000 );
			EditMinDistanz->Color = (TColor)0xAAFFAA;
			EditMinDistanz->Text = buffer;

			double quotient = hyperfokaleEntfernung-distanz+brennweite;
			if( quotient > 0 )
			{
				double maxDistanz = distanz*hyperfokaleEntfernung / quotient;
				sprintf( buffer, "%.3f", maxDistanz/1000.0 );
				EditMaxDistanz->Font->Name = "MS Sans Serif";
				EditMaxDistanz->Text = buffer;
			}
			else
			{
				EditMaxDistanz->Font->Name = "Symbol";
				EditMaxDistanz->Text = "\xA5";
			}

			EditMaxDistanz->Color = (TColor)0xAAFFAA;
		}
	}
}
//---------------------------------------------------------------------------
__fastcall TFotorechnerForm::TFotorechnerForm(TComponent* Owner)
	: TForm(Owner)
{
	autoRechne = AUTO_NIX;
	autoBildGroesse = true;
}
//---------------------------------------------------------------------------
void __fastcall TFotorechnerForm::ButtonRechneVergrClick(TObject *)
{
	rechneVergFaktor();
	autoRechne = AUTO_FAKTOR;
	LabelDistanz->Font->Style = TFontStyles();
	LabelFaktor->Font->Style = TFontStyles() << fsBold;
}
//---------------------------------------------------------------------------
void __fastcall TFotorechnerForm::ButtonRechneDistanzClick(TObject *)
{
	rechneDistanz();
	autoRechne = AUTO_DISTANZ;
	LabelDistanz->Font->Style = TFontStyles() << fsBold;
	LabelFaktor->Font->Style = TFontStyles();
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::ButtonNeustartClick(TObject *)
{
	autoBildGroesse = true;
	EditDistanz->Color = (TColor)0xFFFFFF;
	EditDistanz->Text = "";
	EditBrennweite->Text = "";
	EditVergrFaktor->Color = (TColor)0xFFFFFF;
	EditVergrFaktor->Text = "";
	EditObjektGroesse->Text = "";
	EditBildGroesse->Color = (TColor)0xFFFFFF;
	EditBildGroesse->Text = "";
	EditBildwinkel->Color = (TColor)0xFFFFFF;
	EditBildwinkel->Text = "";
	EditHyperfokaleDistanz->Color = (TColor)0xFFFFFF;
	EditHyperfokaleDistanz->Text = "";
	EditMinDistanz->Color = (TColor)0xFFFFFF;
	EditMinDistanz->Text = "";
	EditMaxDistanz->Color = (TColor)0xFFFFFF;
	EditMaxDistanz->Text = "";
	EditBlende->Text = "";

	autoRechne = AUTO_NIX;
	LabelDistanz->Font->Style = TFontStyles();
	LabelFaktor->Font->Style = TFontStyles();
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::EditBrennweiteChange(TObject *)
{
	rechneBildwinkel();
	rechneSchaerfentiefe();

	if( autoRechne == AUTO_FAKTOR || EditVergrFaktor->Text == "" )
	{
		rechneVergFaktor();
		if( EditVergrFaktor->Text > "" )
		{
			autoRechne = AUTO_FAKTOR;
			LabelDistanz->Font->Style = TFontStyles();
			LabelFaktor->Font->Style = TFontStyles() << fsBold;
		}
	}
	if( autoRechne == AUTO_DISTANZ || EditDistanz->Text == "" )
	{
		rechneDistanz();
		if( EditDistanz->Text > "" )
		{
			autoRechne = AUTO_DISTANZ;
			LabelDistanz->Font->Style = TFontStyles() << fsBold;
			LabelFaktor->Font->Style = TFontStyles();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::EditDistanzChange(TObject *Sender)
{
	if( !((TComponent*)Sender)->Tag )
	{
		rechneVergFaktor();
		autoRechne = AUTO_FAKTOR;
		LabelDistanz->Font->Style = TFontStyles();
		LabelFaktor->Font->Style = TFontStyles() << fsBold;
		EditDistanz->Color = (TColor)0xFFFFFF;
	}
	rechneSchaerfentiefe();
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::EditVergrFaktorChange(TObject *Sender)
{
	if( !((TComponent*)Sender)->Tag )
	{
		EditVergrFaktor->Color = (TColor)0xFFFFFF;
		rechneBildgroesse();
		rechneDistanz();
		autoRechne = AUTO_DISTANZ;
		LabelDistanz->Font->Style = TFontStyles() << fsBold;
		LabelFaktor->Font->Style = TFontStyles();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::EditGroesseChange(TObject *Sender)
{
	if( !((TComponent*)Sender)->Tag )
	{
		if( Sender == EditBildGroesse )
		{
			autoBildGroesse = false;
			EditBildGroesse->Color = (TColor)0xFFFFFF;
		}

		if( autoBildGroesse )
			rechneBildgroesse();
		else
		{
			char	buffer[128];

			double	vergrFaktor = 0.0;
			double	objektGroesse = atof( EditObjektGroesse->Text.c_str() );
			double	bildGroesse = atof( EditBildGroesse->Text.c_str() );

			*buffer = 0;
			if( objektGroesse > 0 && bildGroesse > 0 )
				vergrFaktor = rechneVergroesserungAusBild( objektGroesse, bildGroesse );

			if( vergrFaktor > 0.005 )
				sprintf( buffer, "%.2f", vergrFaktor );

			if( *buffer )
			{
				EditVergrFaktor->Tag = 1;
				EditVergrFaktor->Color = (TColor)0xAAFFAA;
				EditVergrFaktor->Text = buffer;
				EditVergrFaktor->Tag = 0;
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
//---------------------------------------------------------------------------
static void SetLocalOverrides(char* FileName, char* LocaleOverride)

{
	HKEY Key;
	const char* LocaleOverrideKey = "Software\\Borland\\Locales";

	if(
		RegOpenKeyEx(
			HKEY_CURRENT_USER, LocaleOverrideKey, 0, KEY_ALL_ACCESS, &Key
		) == ERROR_SUCCESS
	)
	{
		if (lstrlen(LocaleOverride) == 3)
			RegSetValueEx(
				Key, FileName, 0, REG_SZ, (const BYTE*)LocaleOverride, 4
			);
		else
			RegDeleteValue( Key, FileName );

		RegCloseKey(Key);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::ButtonLanguageClick(TObject *)
{
	char buffer[1024];
	GetModuleFileName( NULL, buffer, sizeof( buffer ) );

	if( ButtonLanguage->Caption == "English" )
		SetLocalOverrides( buffer, "ENU" );
	else
		SetLocalOverrides( buffer, "" );

	WinExec( buffer, SW_SHOW );

	exit( 0 );
}
//---------------------------------------------------------------------------


void __fastcall TFotorechnerForm::EditBlendeChange(TObject *)
{
	rechneSchaerfentiefe();
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Breite718mmClick(TObject *)
{
	EditBildGroesse->Text = "7.18";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Hhe532mmClick(TObject *)
{
	EditBildGroesse->Text = "5.32";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Diagonale893mmClick(TObject *)
{
	EditBildGroesse->Text = "8.93";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Breite236mmClick(TObject *)
{
	EditBildGroesse->Text = "23.6";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Hhe158mmClick(TObject *)
{
	EditBildGroesse->Text = "15.8";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Diagonale284mmClick(TObject *)
{
	EditBildGroesse->Text = "28.4";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Breite36mmClick(TObject *)
{
	EditBildGroesse->Text = "36";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Hhe24mmClick(TObject *)
{
	EditBildGroesse->Text = "24";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Diagonale4327mmClick(TObject *)
{
	EditBildGroesse->Text = "43.27";
}
//---------------------------------------------------------------------------


void __fastcall TFotorechnerForm::Breite76mmClick(TObject *)
{
	EditBildGroesse->Text = "7.6";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Hhe57mmClick(TObject *)
{
	EditBildGroesse->Text = "5.7";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Diagonale95mmClick(TObject *)
{
	EditBildGroesse->Text = "9.5";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Breite1731mmClick(TObject *)
{
	EditBildGroesse->Text = "17.31";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Hhe1298mmClick(TObject *)
{
	EditBildGroesse->Text = "12.98";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Diagonale2163mmClick(TObject *)
{
	EditBildGroesse->Text = "21.63";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Breite132mmClick(TObject *)
{
	EditBildGroesse->Text = "13.2";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Hhe88mmClick(TObject *)
{
	EditBildGroesse->Text = "8.8";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Diagonale1586mmClick(TObject *)
{
	EditBildGroesse->Text = "15.86";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Breite616mmClick(TObject *)
{
	EditBildGroesse->Text = "6.16";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Hhe462mmClick(TObject *)
{
	EditBildGroesse->Text = "4.62";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Diagonale77mmClick(TObject *)
{
	EditBildGroesse->Text = "7.7";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Breite816mm1Click(TObject *)
{
	EditBildGroesse->Text = "8.16";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Hhe612mm1Click(TObject *)
{
	EditBildGroesse->Text = "6.12";
}
//---------------------------------------------------------------------------

void __fastcall TFotorechnerForm::Diagonale1012mm1Click(TObject *)
{
	EditBildGroesse->Text = "10.12";
}
//---------------------------------------------------------------------------

