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
