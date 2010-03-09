#include "smdatmospheretab.h"

//public
_smdAtmosphereTab::_smdAtmosphereTab(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{

//Atmospheric Options//
    colSun = new wxColour(255, 200, 20);
    colSky = new wxColour(20, 20, 240);
    colCloud = new wxColour(150, 150, 150);
    colFog = new wxColour(100, 100, 100);
//Light Options//
    colGroundAmbient = new wxColour(127, 127, 127);
    colGroundSun = new wxColour(127, 127, 127);
    colUnitAmbient = new wxColour(127, 127, 127);
    colUnitSun = new wxColour(127, 127, 127);


    wxBoxSizer *vboxSMDAtmosphereAndLight = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hboxSMDAtmosphere = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hboxSunDirection = new wxBoxSizer(wxHORIZONTAL);


    wxStaticBoxSizer *gsSMDAtmosphere = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Atmospheric Settings"));
    wxFlexGridSizer *fgSMDAtmosphere = new wxFlexGridSizer(6,3,5,5);

        wxStaticText *stSunColour = new wxStaticText(this, wxID_ANY, wxT("Sun Colour"));
        btnSunColour = new wxButton(this, IDBTN_SUN_COLOUR, wxT("Sun Colour"));
        pnlSunColourDisplay = new wxPanel(this, -1);

        wxStaticText *stSkyColour = new wxStaticText(this, wxID_ANY, wxT("Sky Colour"));
        btnSkyColour = new wxButton(this, IDBTN_SKY_COLOUR, wxT("Sky Colour"));
        pnlSkyColourDisplay = new wxPanel(this, -1);

        wxStaticText *stCloudColour = new wxStaticText(this, wxID_ANY, wxT("Cloud Colour      "));
        btnCloudColour = new wxButton(this, IDBTN_CLOUD_COLOUR, wxT("Cloud Colour"));
        pnlCloudColourDisplay = new wxPanel(this, -1);

        wxStaticText *stCloudDensity = new wxStaticText(this, wxID_ANY, wxT("Cloud Density"));
        tcCloudDensity = new wxTextCtrl(this, IDTC_CLOUD_DENSITY, wxT("0.55"));
        wxPanel *pnlCloudDensityPlacehold = new wxPanel(this, -1);

        wxStaticText *stFogColour = new wxStaticText(this, wxID_ANY, wxT("Fog Colour"));
        btnFogColour = new wxButton(this, IDBTN_FOG_COLOUR, wxT("Fog Colour"));
        pnlFogColourDisplay = new wxPanel(this, -1);

        wxStaticText *stFogStart = new wxStaticText(this, wxID_ANY, wxT("Fog Density"));
        tcFogStart = new wxTextCtrl(this, IDTC_FOG_DENSITY, wxT("0.55"));
        wxPanel *pnlFogStartPlacehold = new wxPanel(this, -1);

//Assemble atmospheric settings page///////////////////////////////////////////////////////////////

    fgSMDAtmosphere->Add(stSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(btnSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlSunColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
        pnlSunColourDisplay->SetBackgroundColour(*colSun);
    fgSMDAtmosphere->Add(stSkyColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(btnSkyColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlSkyColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
        pnlSkyColourDisplay->SetBackgroundColour(*colSky);

    fgSMDAtmosphere->Add(stCloudColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(btnCloudColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlCloudColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
        pnlCloudColourDisplay->SetBackgroundColour(*colCloud);
    fgSMDAtmosphere->Add(stCloudDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(tcCloudDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlCloudDensityPlacehold, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

    fgSMDAtmosphere->Add(stFogColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(btnFogColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlFogColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
        pnlFogColourDisplay->SetBackgroundColour(*colFog);
    fgSMDAtmosphere->Add(stFogStart, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(tcFogStart, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlFogStartPlacehold, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);


////////////////////////////////////////////////////////////////////////////////////////////////////
//Lighting page, containing lighting and shadow info////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    wxStaticBoxSizer *gsSMDLight = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Lighting Settings"));
    wxFlexGridSizer *fgSMDLight = new wxFlexGridSizer(6,3,5,5);

        wxStaticText *stGroundAmbientColour = new wxStaticText(this, wxID_ANY, wxT("Ground Ambient"));
        btnGroundAmbientColour = new wxButton(this, IDBTN_GROUNDAMBIENT_COLOUR, wxT("G A Colour"));
        pnlGroundAmbientColourDisplay = new wxPanel(this, -1);

        wxStaticText *stGroundSunColour = new wxStaticText(this, wxID_ANY, wxT("Ground Sun"));
        btnGroundSunColour = new wxButton(this, IDBTN_GROUNDSUN_COLOUR, wxT("G S Colour"));
        pnlGroundSunColourDisplay = new wxPanel(this, -1);

        wxStaticText *stGroundShadowDensity = new wxStaticText(this, wxID_ANY, wxT("Ground Shadow Density"));
        tcGroundShadowDensity = new wxTextCtrl(this, IDTC_GROUND_SHADOW_DENSITY, wxT("0.55"));
        wxPanel *pnlGroundShadowDensityPlacehold = new wxPanel(this, -1);

        wxStaticText *stUnitAmbientColour = new wxStaticText(this, wxID_ANY, wxT("Unit Ambient"));
        btnUnitAmbientColour = new wxButton(this, IDBTN_UNITAMBIENT_COLOUR, wxT("U A Colour"));
        pnlUnitAmbientColourDisplay = new wxPanel(this, -1);

        wxStaticText *stUnitSunColour = new wxStaticText(this, wxID_ANY, wxT("Unit Sun"));
        btnUnitSunColour = new wxButton(this, IDBTN_UNITSUN_COLOUR, wxT("U S Colour"));
        pnlUnitSunColourDisplay = new wxPanel(this, -1);

        wxStaticText *stUnitShadowDensity = new wxStaticText(this, wxID_ANY, wxT("Unit Shadow Density"));
        tcUnitShadowDensity = new wxTextCtrl(this, IDTC_UNIT_SHADOW_DENSITY, wxT("0.55"));
        wxPanel *pnlUnitShadowDensityPlacehold = new wxPanel(this, -1);

    fgSMDLight->Add(stGroundAmbientColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(btnGroundAmbientColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlGroundAmbientColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlGroundAmbientColourDisplay->SetBackgroundColour(*colGroundAmbient);

    fgSMDLight->Add(stGroundSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(btnGroundSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlGroundSunColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlGroundSunColourDisplay->SetBackgroundColour(*colGroundSun);
    fgSMDLight->Add(stGroundShadowDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(tcGroundShadowDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlGroundShadowDensityPlacehold, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

    fgSMDLight->Add(stUnitAmbientColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(btnUnitAmbientColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlUnitAmbientColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlUnitAmbientColourDisplay->SetBackgroundColour(*colUnitAmbient);

    fgSMDLight->Add(stUnitSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(btnUnitSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlUnitSunColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlUnitSunColourDisplay->SetBackgroundColour(*colUnitSun);
    fgSMDLight->Add(stUnitShadowDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(tcUnitShadowDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlUnitShadowDensityPlacehold, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

    gsSMDAtmosphere->Add(fgSMDAtmosphere, 1, wxEXPAND, 0);
    gsSMDLight->Add(fgSMDLight, 1, wxEXPAND, 0);

    hboxSMDAtmosphere->Add(gsSMDAtmosphere, 1, wxEXPAND, 0);
    hboxSMDAtmosphere->Add(gsSMDLight, 1, wxEXPAND, 0);

////////////////////////////////////////////////////////////////////////////////////////////////////
//Sun Direction graphical interface/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    wxStaticBoxSizer *gsSunDirection = new wxStaticBoxSizer(wxVERTICAL, this, wxT("SunDirection"));
    wxFlexGridSizer *fgSunDirection = new wxFlexGridSizer(1,1,5,5);

    pnlSunDirection = new wxPanel(this, -1);
    pnlSunDirection->SetBackgroundColour(wxColour(255,0,0));

    fgSunDirection->Add(pnlSunDirection, 1, wxEXPAND, 0);
    gsSunDirection->Add(fgSunDirection, 1, wxEXPAND, 0);
    hboxSunDirection->Add(gsSunDirection, 1, wxEXPAND, 0);

    vboxSMDAtmosphereAndLight->Add(hboxSMDAtmosphere, 1, wxEXPAND, 0);
    vboxSMDAtmosphereAndLight->Add(hboxSunDirection, 1, wxEXPAND, 0);
    this->SetSizer(vboxSMDAtmosphereAndLight);

    Connect(IDBTN_SUN_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdAtmosphereTab::OnClickSunColour));
    Connect(IDBTN_SKY_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdAtmosphereTab::OnClickSkyColour));
    Connect(IDBTN_CLOUD_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdAtmosphereTab::OnClickCloudColour));
    Connect(IDBTN_FOG_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdAtmosphereTab::OnClickFogColour));
    Connect(IDBTN_GROUNDAMBIENT_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdAtmosphereTab::OnClickGroundAmbientColour));
    Connect(IDBTN_GROUNDSUN_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdAtmosphereTab::OnClickGroundSunColour));
    Connect(IDBTN_UNITAMBIENT_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdAtmosphereTab::OnClickUnitAmbientColour));
    Connect(IDBTN_UNITSUN_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdAtmosphereTab::OnClickUnitSunColour));

    Connect(IDTC_CLOUD_DENSITY, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(_smdAtmosphereTab::OnChangeCloudDensityText));
    Connect(IDTC_FOG_DENSITY, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(_smdAtmosphereTab::OnChangeFogStartText));
    Connect(IDTC_GROUND_SHADOW_DENSITY, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(_smdAtmosphereTab::OnChangeGroundShadowDensityText));
    Connect(IDTC_GROUND_SHADOW_DENSITY, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(_smdAtmosphereTab::OnChangeUnitShadowDensityText));
}

void _smdAtmosphereTab::reset(void)
{
    colSun->Set(255, 190, 20);
    colSky->Set(20, 20, 240);
    colCloud->Set(150, 150, 150);
    colFog->Set(100, 100, 100);
    colGroundAmbient->Set(127, 127, 127);
    colGroundSun->Set(127, 127, 127);
    colUnitAmbient->Set(127, 127, 127);
    colUnitSun->Set(127, 127, 127);

    pnlSunColourDisplay->SetBackgroundColour(*colSun);
    pnlSkyColourDisplay->SetBackgroundColour(*colSky);
    pnlCloudColourDisplay->SetBackgroundColour(*colCloud);
    pnlFogColourDisplay->SetBackgroundColour(*colFog);
    pnlGroundAmbientColourDisplay->SetBackgroundColour(*colGroundAmbient);
    pnlGroundSunColourDisplay->SetBackgroundColour(*colGroundSun);
    pnlUnitAmbientColourDisplay->SetBackgroundColour(*colUnitAmbient);
    pnlUnitSunColourDisplay->SetBackgroundColour(*colUnitSun);

    pnlSunColourDisplay->Refresh();
    pnlSkyColourDisplay->Refresh();
    pnlCloudColourDisplay->Refresh();
    pnlFogColourDisplay->Refresh();
    pnlGroundAmbientColourDisplay->Refresh();
    pnlGroundSunColourDisplay->Refresh();
    pnlUnitAmbientColourDisplay->Refresh();
    pnlUnitSunColourDisplay->Refresh();

}
//private
void _smdAtmosphereTab::OnClickSunColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colSun = colourData->GetColour();
        pnlSunColourDisplay->SetBackgroundColour(*colSun);
        pnlSunColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void _smdAtmosphereTab::OnClickSkyColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colSky = colourData->GetColour();
        pnlSkyColourDisplay->SetBackgroundColour(*colSky);
        pnlSkyColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void _smdAtmosphereTab::OnClickCloudColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colCloud = colourData->GetColour();
        pnlCloudColourDisplay->SetBackgroundColour(*colCloud);
        pnlCloudColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void _smdAtmosphereTab::OnClickFogColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colFog = colourData->GetColour();
        pnlFogColourDisplay->SetBackgroundColour(*colFog);
        pnlFogColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void _smdAtmosphereTab::OnChangeCloudDensityText(wxCommandEvent& event){
}
void _smdAtmosphereTab::OnChangeFogStartText(wxCommandEvent& event){
}

void _smdAtmosphereTab::OnClickGroundAmbientColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colGroundAmbient = colourData->GetColour();
        pnlGroundAmbientColourDisplay->SetBackgroundColour(*colGroundAmbient);
        pnlGroundAmbientColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void _smdAtmosphereTab::OnClickGroundSunColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colGroundSun = colourData->GetColour();
        pnlGroundSunColourDisplay->SetBackgroundColour(*colGroundSun);
        pnlGroundSunColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void _smdAtmosphereTab::OnClickUnitAmbientColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colUnitAmbient = colourData->GetColour();
        pnlUnitAmbientColourDisplay->SetBackgroundColour(*colUnitAmbient);
        pnlUnitAmbientColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void _smdAtmosphereTab::OnClickUnitSunColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colUnitSun = colourData->GetColour();
        pnlUnitSunColourDisplay->SetBackgroundColour(*colUnitSun);
        pnlUnitSunColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void _smdAtmosphereTab::OnChangeUnitShadowDensityText(wxCommandEvent& event){
}
void _smdAtmosphereTab::OnChangeGroundShadowDensityText(wxCommandEvent& event){
}
