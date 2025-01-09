/*
	this file was created from C:\CRESD\Source\FotoCalc\foto.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/
#ifndef C__CRESD_SOURCE_FOTOCALC_FOTO_GUI_H
#define C__CRESD_SOURCE_FOTOCALC_FOTO_GUI_H
#include <winlib/popup.h>
#include <winlib/frame.h>
#include <winlib/scrollFrame.h>
#include <winlib/ControlW.h>
#include <winlib/xmlEditorChild.h>
#include <winlib/gridView.h>

#include <winlib/winApp.h>

namespace winlibGUI {

	const int ApsDiagonal284mm_id=134;
	const int ApsHeight158mm_id=133;
	const int ApsWidth236mm_id=132;
	const int ButtonLanguage_id=168;
	const int ButtonNeustart_id=169;
	const int ButtonRechneDistanz_id=157;
	const int ButtonRechneVergr_id=163;
	const int Diagonal77mm_id=152;
	const int Diagonal893mm_id=149;
	const int Diagonal95mm_id=146;
	const int EditBildGroesse_id=158;
	const int EditBildwinkel_id=160;
	const int EditBlende_id=165;
	const int EditBrennweite_id=159;
	const int EditDistanz_id=156;
	const int EditHyperfokaleDistanz_id=164;
	const int EditMaxDistanz_id=167;
	const int EditMinDistanz_id=166;
	const int EditObjektGroesse_id=154;
	const int EditVergrFaktor_id=162;
	const int FotoFORM_id=128;
	const int Height462mm_id=151;
	const int Height532mm_id=148;
	const int Height57mm_id=145;
	const int LabelDistanz_id=155;
	const int LabelFaktor_id=161;
	const int MicroFourThirdsDiagonal2163mm_id=137;
	const int MicroFourThirdsHeight1998mm_id=136;
	const int MicroFourThirdsWidth1731mm_id=135;
	const int Nikon1Diagonal1586mm_id=140;
	const int Nikon1Height88mm_id=139;
	const int Nikon1width132mm_id=138;
	const int SamsungDiagonal1012mm_id=143;
	const int SamsungHeight612mm_id=142;
	const int SamsungWidth816mm_id=141;
	const int SizeMenu_id=153;
	const int SpDiagonal4327mm_id=131;
	const int SpHeight24mm_id=130;
	const int SPWidth36mm_id=129;
	const int Width616mm_id=150;
	const int Width718mm_id=147;
	const int Width76mm_id=144;

	class GuiApplication : public winlib::Application {
		public:
		virtual gak::xml::Document *getGuiDoc( void );
		GuiApplication(int iconID=-1) : winlib::Application(iconID) {}
	};

	class FotoFORM_form : public winlib::PopupWindow {
		public:
		FotoFORM_form(winlib::BasicWindow *owner) : PopupWindow(owner) {}
		winlib::SuccessCode create(winlib::BasicWindow*parent) {
			return PopupWindow::create(parent,"FotoFORM");
		}

		winlib::EditControl *EditObjektGroesse;
		winlib::Label *LabelDistanz;
		winlib::EditControl *EditDistanz;
		winlib::PushButton *ButtonRechneDistanz;
		winlib::EditControl *EditBildGroesse;
		winlib::EditControl *EditBrennweite;
		winlib::EditControl *EditBildwinkel;
		winlib::Label *LabelFaktor;
		winlib::EditControl *EditVergrFaktor;
		winlib::PushButton *ButtonRechneVergr;
		winlib::EditControl *EditHyperfokaleDistanz;
		winlib::EditControl *EditBlende;
		winlib::EditControl *EditMinDistanz;
		winlib::EditControl *EditMaxDistanz;
		winlib::PushButton *ButtonLanguage;
		winlib::PushButton *ButtonNeustart;
		private:
		virtual void getControls();
	};	// end of FotoFORM
}	// namespace winlibGUI

#endif // C__CRESD_SOURCE_FOTOCALC_FOTO_GUI_H
