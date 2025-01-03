/*
		Project:		FotoCalc
		Module:			fotoFrm.h
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

#ifndef fotoFrmH
#define fotoFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFotorechnerForm : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TEdit *EditDistanz;
	TEdit *EditBrennweite;
	TEdit *EditVergrFaktor;
	TButton *ButtonRechneVergr;
	TLabel *LabelDistanz;
	TLabel *Label2;
	TLabel *LabelFaktor;
	TButton *ButtonRechneDistanz;
	TLabel *Label4;
	TEdit *EditObjektGroesse;
	TLabel *Label5;
	TEdit *EditBildGroesse;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *EditBildwinkel;
	TButton *ButtonNeustart;
	TButton *ButtonLanguage;
	TLabel *Label1;
	TEdit *EditHyperfokaleDistanz;
	TEdit *EditBlende;
	TLabel *Label3;
	TEdit *EditMinDistanz;
	TEdit *EditMaxDistanz;
	TLabel *Label8;
	TLabel *Label9;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1171;
	TMenuItem *APSNikon1;
	TMenuItem *Kleinbild1;
	TMenuItem *Breite718mm;
	TMenuItem *Hhe532mm;
	TMenuItem *Diagonale893mm;
	TMenuItem *Breite236mm;
	TMenuItem *Hhe158mm;
	TMenuItem *Diagonale284mm;
	TMenuItem *Breite36mm;
	TMenuItem *Hhe24mm;
	TMenuItem *Diagonale4327mm;
	TMenuItem *N1172;
	TMenuItem *Breite76mm;
	TMenuItem *Hhe57mm;
	TMenuItem *Diagonale95mm;
	TMenuItem *MicroFourThirds1;
	TMenuItem *Nikon11;
	TMenuItem *N1231;
	TMenuItem *Diagonale2163mm;
	TMenuItem *SamsungA551;
	TMenuItem *Breite816mm1;
	TMenuItem *Hhe612mm1;
	TMenuItem *Diagonale1012mm1;
	void __fastcall ButtonRechneVergrClick(TObject *Sender);
	void __fastcall ButtonRechneDistanzClick(TObject *Sender);
	void __fastcall ButtonNeustartClick(TObject *Sender);
	void __fastcall EditBrennweiteChange(TObject *Sender);
	void __fastcall EditDistanzChange(TObject *Sender);
	void __fastcall EditVergrFaktorChange(TObject *Sender);
	void __fastcall EditGroesseChange(TObject *Sender);
	void __fastcall ButtonLanguageClick(TObject *Sender);
	void __fastcall EditBlendeChange(TObject *Sender);
	void __fastcall Breite718mmClick(TObject *Sender);
	void __fastcall Hhe532mmClick(TObject *Sender);
	void __fastcall Diagonale893mmClick(TObject *Sender);
	void __fastcall Breite236mmClick(TObject *Sender);
	void __fastcall Hhe158mmClick(TObject *Sender);
	void __fastcall Diagonale284mmClick(TObject *Sender);
	void __fastcall Breite36mmClick(TObject *Sender);
	void __fastcall Hhe24mmClick(TObject *Sender);
	void __fastcall Diagonale4327mmClick(TObject *Sender);
	void __fastcall Breite76mmClick(TObject *Sender);
	void __fastcall Hhe57mmClick(TObject *Sender);
	void __fastcall Diagonale95mmClick(TObject *Sender);
	void __fastcall Breite1731mmClick(TObject *Sender);
	void __fastcall Hhe1298mmClick(TObject *Sender);
	void __fastcall Diagonale2163mmClick(TObject *Sender);
	void __fastcall Breite132mmClick(TObject *Sender);
	void __fastcall Hhe88mmClick(TObject *Sender);
	void __fastcall Diagonale1586mmClick(TObject *Sender);
	void __fastcall Breite616mmClick(TObject *Sender);
	void __fastcall Hhe462mmClick(TObject *Sender);
	void __fastcall Diagonale77mmClick(TObject *Sender);
	void __fastcall Breite816mm1Click(TObject *Sender);
	void __fastcall Hhe612mm1Click(TObject *Sender);
	void __fastcall Diagonale1012mm1Click(TObject *Sender);
private:	// Anwender-Deklarationen
	enum AUTO_RECHNE {
		AUTO_NIX, AUTO_FAKTOR, AUTO_DISTANZ
	} autoRechne;
	bool autoBildGroesse;

	void rechneBildgroesse( void );
	void rechneBildwinkel( void );
	void rechneVergFaktor( void );
	void rechneDistanz( void );
	void rechneSchaerfentiefe( void );

public:		// Anwender-Deklarationen
	__fastcall TFotorechnerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFotorechnerForm *FotorechnerForm;
//---------------------------------------------------------------------------
#endif
