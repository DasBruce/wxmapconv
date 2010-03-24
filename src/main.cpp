#include "main.h"
#include "wxwfrontend.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    Frontend *frontend = new Frontend(wxT("Mapconv GUI"));
    frontend->Show(true);

    return true;
}

