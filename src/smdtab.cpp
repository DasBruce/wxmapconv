#include "smdtab.h"

_smdTab::_smdTab(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
    nbSMD = new wxNotebook(this, wxID_ANY);

    smdGeneralTab = new _smdGeneralTab(nbSMD, -1);
    smdAtmosphereTab = new _smdAtmosphereTab(nbSMD, -1);
    smdWaterTab = new _smdWaterTab(nbSMD, -1);

    nbSMD->AddPage(smdGeneralTab, wxT("General"), true);
    nbSMD->AddPage(smdAtmosphereTab, wxT("Atmosphere"), true);
    nbSMD->AddPage(smdWaterTab, wxT("Water"), true);

    btnSMDSave = new wxButton( this, IDBTN_SMD_SAVE, wxT("Save SMD"));
    wxBoxSizer *hboxSMDSave = new wxBoxSizer(wxHORIZONTAL);
    hboxSMDSave->Add(btnSMDSave, 0,0,0);

    wxFlexGridSizer* box = new wxFlexGridSizer(2,1,0,0);       //create a sizer to expand the subnotebooks
    box->Add( nbSMD, 1, wxEXPAND, 0 );
    box->Add( hboxSMDSave, 0, wxEXPAND, 0);

    this->SetSizer( box );
    this->Layout();
}
