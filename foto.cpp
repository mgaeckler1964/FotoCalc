//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("foto.res");
USEFORM("fotoFrm.cpp", FotorechnerForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "Fotorechner";
		Application->CreateForm(__classid(TFotorechnerForm), &FotorechnerForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------

