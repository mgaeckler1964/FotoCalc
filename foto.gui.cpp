/*
	this file was created from C:\CRESD\Source\FotoCalc\foto.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/

#include "C:\CRESD\Source\FotoCalc\foto.gui.h"

namespace winlibGUI {

	gak::xml::Document *GuiApplication::getGuiDoc() {
		gak::xml::Document *doc = winlib::Application::getGuiDoc();
		if(!doc) {
			gak::STRING xmlSrc = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n"
"<gui>\n"
"<forms>\n"
"<form name=\"FotoFORM\" style=\"281673728\" width=\"590\" height=\"254\" caption=\"Foto Calculator\" id=\"128\" baseClass=\"PopupWindow\">\n"
"<layoutManager type=\"TableManager\" marginLeft=\"5\" marginRight=\"5\" marginTop=\"5\" marginBottom=\"5\" />\n"
"<child type=\"Label\" name=\"\" caption=\"Object Size [mm]:\" x=\"27\" y=\"37\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"0\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditObjektGroesse\" caption=\"\" x=\"165\" y=\"15\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"154\">\n"
"<layout x=\"1\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"10\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"LabelDistanz\" caption=\"Distance [m]\" x=\"265\" y=\"39\" width=\"80\" height=\"25\" style=\"1342242827\" id=\"155\">\n"
"<layout x=\"2\" y=\"0\" width=\"1\" height=\"1\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditDistanz\" caption=\"\" x=\"304\" y=\"16\" width=\"80\" height=\"24\" style=\"1350631808\" id=\"156\">\n"
"<layout x=\"3\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"10\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"PushButton\" name=\"ButtonRechneDistanz\" caption=\"Calculate\" x=\"412\" y=\"11\" width=\"80\" height=\"25\" style=\"1342242816\" id=\"157\">\n"
"<layout x=\"4\" y=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"Picture Size [mm]\" x=\"23\" y=\"40\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"0\" y=\"1\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditBildGroesse\" caption=\"\" x=\"116\" y=\"29\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"158\">\n"
"<layout x=\"1\" y=\"1\" growWidth=\"10\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"FocalLength [mm]\" x=\"310\" y=\"34\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"2\" y=\"1\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditBrennweite\" caption=\"\" x=\"388\" y=\"30\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"159\">\n"
"<layout x=\"3\" y=\"1\" growWidth=\"10\" width=\"1\" height=\"1\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"Picture Angel\" x=\"22\" y=\"80\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"0\" y=\"2\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditBildwinkel\" caption=\"\" x=\"128\" y=\"64\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"160\">\n"
"<layout x=\"1\" y=\"2\" growWidth=\"10\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"LabelFaktor\" caption=\"Factor\" x=\"297\" y=\"62\" width=\"80\" height=\"25\" style=\"1342242827\" id=\"161\">\n"
"<layout x=\"2\" y=\"2\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditVergrFaktor\" caption=\"\" x=\"384\" y=\"64\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"162\">\n"
"<layout x=\"3\" y=\"2\" width=\"1\" height=\"1\" growWidth=\"10\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"PushButton\" name=\"ButtonRechneVergr\" caption=\"Calculate\" x=\"547\" y=\"58\" width=\"80\" height=\"25\" style=\"1342242816\" id=\"163\">\n"
"<layout x=\"4\" y=\"2\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"Hyp. dist. [m]\" x=\"19\" y=\"136\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"0\" y=\"3\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditHyperfokaleDistanz\" caption=\"\" x=\"152\" y=\"96\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"164\">\n"
"<layout x=\"1\" y=\"3\" growWidth=\"10\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"Aperture\" x=\"304\" y=\"96\" width=\"80\" height=\"25\" style=\"1342242827\">\n"
"<layout x=\"2\" y=\"3\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditBlende\" caption=\"\" x=\"384\" y=\"96\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"165\">\n"
"<layout x=\"3\" y=\"3\" growWidth=\"10\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"Min. Dist. [m]\" x=\"35\" y=\"211\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"0\" y=\"4\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditMinDistanz\" caption=\"\" x=\"160\" y=\"152\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"166\">\n"
"<layout x=\"1\" y=\"4\" growWidth=\"10\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"Max. Dist [m]\" x=\"296\" y=\"128\" width=\"80\" height=\"25\" style=\"1342242827\">\n"
"<layout x=\"2\" y=\"4\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditMaxDistanz\" caption=\"\" x=\"408\" y=\"136\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"167\">\n"
"<layout x=\"3\" y=\"4\" growWidth=\"10\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"135: 24mm * 36mm,   APS: 15,8mm * 23,6mm,   1/1,7\': 5,7mm * 7,6mm,   1/1,8\': 5,32mm * 7,18mm\" x=\"26\" y=\"140\" width=\"0\" height=\"25\" style=\"1342242827\">\n"
"<layout x=\"0\" y=\"5\" width=\"5\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"PushButton\" name=\"ButtonLanguage\" caption=\"Deutsch\" x=\"35\" y=\"190\" width=\"80\" height=\"25\" style=\"1342242816\" id=\"168\">\n"
"<layout x=\"0\" y=\"6\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"PushButton\" name=\"ButtonNeustart\" caption=\"Restart\" x=\"552\" y=\"200\" width=\"80\" height=\"25\" style=\"1342242816\" id=\"169\">\n"
"<layout x=\"4\" y=\"6\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"</form>\n"
"</forms>\n"
"<menus>\n"
"<menu name=\"SizeMenu\" caption=\"Size\" id=\"153\">\n"
"<menu caption=\"135 Film\">\n"
"<menu caption=\"Width (36mm)\" name=\"SPWidth36mm\" id=\"129\" />\n"
"<menu caption=\"Height (24mm)\" name=\"SpHeight24mm\" id=\"130\" />\n"
"<menu caption=\"Diagonal (43.27mm)\" name=\"SpDiagonal4327mm\" id=\"131\" />\n"
"</menu>\n"
"<menu caption=\"APS (Nikon)\">\n"
"<menu caption=\"Width (23.6mm)\" name=\"ApsWidth236mm\" id=\"132\" />\n"
"<menu caption=\"Height (15.8mm)\" name=\"ApsHeight158mm\" id=\"133\" />\n"
"<menu caption=\"Diagonal (28.4mm)\" name=\"ApsDiagonal284mm\" id=\"134\" />\n"
"</menu>\n"
"<menu caption=\"(Micro) Four Thirds\">\n"
"<menu caption=\"Width (17.31mm)\" name=\"MicroFourThirdsWidth1731mm\" id=\"135\" />\n"
"<menu caption=\"Height (19.98mm)\" name=\"MicroFourThirdsHeight1998mm\" id=\"136\" />\n"
"<menu caption=\"Diagonal (21.63mm)\" name=\"MicroFourThirdsDiagonal2163mm\" id=\"137\" />\n"
"</menu>\n"
"<menu caption=\"Nikon-1\">\n"
"<menu caption=\"Width (13.2mm)\" name=\"Nikon1width132mm\" id=\"138\" />\n"
"<menu caption=\"Height (8.8mm)\" name=\"Nikon1Height88mm\" id=\"139\" />\n"
"<menu caption=\"Diagonal (15.86mm)\" name=\"Nikon1Diagonal1586mm\" id=\"140\" />\n"
"</menu>\n"
"<menu caption=\"Samsung A55\">\n"
"<menu caption=\"Width (8.16mm)\" name=\"SamsungWidth816mm\" id=\"141\" />\n"
"<menu caption=\"Height (6.12mm)\" name=\"SamsungHeight612mm\" id=\"142\" />\n"
"<menu caption=\"Diagonal (10.12mm)\" name=\"SamsungDiagonal1012mm\" id=\"143\" />\n"
"</menu>\n"
"<menu caption=\"1/1,7\'\">\n"
"<menu caption=\"Width (7.6mm)\" name=\"Width76mm\" id=\"144\" />\n"
"<menu caption=\"Height (5.7mm)\" name=\"Height57mm\" id=\"145\" />\n"
"<menu caption=\"Diagonal (9.5mm)\" name=\"Diagonal95mm\" id=\"146\" />\n"
"</menu>\n"
"<menu caption=\"1/1.8\'\" name=\"\">\n"
"<menu caption=\"Width (7.18mm)\" name=\"Width718mm\" id=\"147\" />\n"
"<menu caption=\"Height (5.32mm)\" name=\"Height532mm\" id=\"148\" />\n"
"<menu caption=\"Diagonal (8.93mm)\" name=\"Diagonal893mm\" id=\"149\" />\n"
"</menu>\n"
"<menu caption=\"1/2.3\'\">\n"
"<menu caption=\"Width (6.16mm)\" name=\"Width (6.16mm)\" id=\"150\" />\n"
"<menu caption=\"Height (4.62mm)\" name=\"Height (4.62mm)\" id=\"151\" />\n"
"<menu caption=\"Diagonal (7.7mm)\" name=\"Diagonal (7.7mm)\" id=\"152\" />\n"
"</menu>\n"
"</menu>\n"
"</menus>\n"
"</gui>";
			return Application::getGuiDoc( xmlSrc );
		}
		return NULL;
	}


	void FotoFORM_form::getControls() {
		EditObjektGroesse=static_cast<winlib::EditControl*>(findChild(EditObjektGroesse_id));
		LabelDistanz=static_cast<winlib::Label*>(findChild(LabelDistanz_id));
		EditDistanz=static_cast<winlib::EditControl*>(findChild(EditDistanz_id));
		ButtonRechneDistanz=static_cast<winlib::PushButton*>(findChild(ButtonRechneDistanz_id));
		EditBildGroesse=static_cast<winlib::EditControl*>(findChild(EditBildGroesse_id));
		EditBrennweite=static_cast<winlib::EditControl*>(findChild(EditBrennweite_id));
		EditBildwinkel=static_cast<winlib::EditControl*>(findChild(EditBildwinkel_id));
		LabelFaktor=static_cast<winlib::Label*>(findChild(LabelFaktor_id));
		EditVergrFaktor=static_cast<winlib::EditControl*>(findChild(EditVergrFaktor_id));
		ButtonRechneVergr=static_cast<winlib::PushButton*>(findChild(ButtonRechneVergr_id));
		EditHyperfokaleDistanz=static_cast<winlib::EditControl*>(findChild(EditHyperfokaleDistanz_id));
		EditBlende=static_cast<winlib::EditControl*>(findChild(EditBlende_id));
		EditMinDistanz=static_cast<winlib::EditControl*>(findChild(EditMinDistanz_id));
		EditMaxDistanz=static_cast<winlib::EditControl*>(findChild(EditMaxDistanz_id));
		ButtonLanguage=static_cast<winlib::PushButton*>(findChild(ButtonLanguage_id));
		ButtonNeustart=static_cast<winlib::PushButton*>(findChild(ButtonNeustart_id));
	}	// FotoFORM
}	// namespace winlibGUI
