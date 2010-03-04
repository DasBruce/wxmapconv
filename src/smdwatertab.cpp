#include "smdwatertab.h"

_smdWaterTab::_smdWaterTab(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
    colWaterBase = new wxColour(100, 150, 200);
    colWaterMin = new wxColour(10, 10, 30);
    colWaterAbsorb = new wxColour(4, 4, 2);
    wxFlexGridSizer *fgSMDWater = new wxFlexGridSizer(0,1,5,5);
//water base colour
    wxStaticBoxSizer *gboxSMDWater = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Water Simple"));
    wxGridSizer* gsSMDWater = new wxFlexGridSizer(0,3,5,5);

    wxStaticText *stWaterBaseColour = new wxStaticText(this, wxID_ANY, wxT("WaterBase Colour"));
    btnWaterBase = new wxButton(this, IDBTN_WATERBASE_COLOUR, wxT("Water Base"));
    pnlWaterBaseColourDisplay = new wxPanel(this, -1);
    wxStaticText *stWaterMinColour = new wxStaticText(this, wxID_ANY, wxT("WaterMin Colour"));
    btnWaterMin = new wxButton(this, IDBTN_WATERMIN_COLOUR, wxT("Water Min"));
    pnlWaterMinColourDisplay = new wxPanel(this, -1);
    wxStaticText *stWaterAbsorbColour = new wxStaticText(this, wxID_ANY, wxT("WaterAbsorb Colour"));
    btnWaterAbsorb = new wxButton(this, IDBTN_WATERABSORB_COLOUR, wxT("Water Absorb"));
    pnlWaterAbsorbColourDisplay = new wxPanel(this, -1);

//Assemble water settings page///////////////////////////////////////////////////////////////////

    gsSMDWater->Add(stWaterBaseColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(btnWaterBase, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(pnlWaterBaseColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlWaterBaseColourDisplay->SetBackgroundColour(*colWaterBase);

    gsSMDWater->Add(stWaterMinColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(btnWaterMin, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(pnlWaterMinColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlWaterMinColourDisplay->SetBackgroundColour(*colWaterMin);

    gsSMDWater->Add(stWaterAbsorbColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(btnWaterAbsorb, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(pnlWaterAbsorbColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlWaterAbsorbColourDisplay->SetBackgroundColour(*colWaterAbsorb);

    gboxSMDWater->Add(gsSMDWater, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP,5);
    fgSMDWater->Add(gboxSMDWater, 1, wxEXPAND, 0);
    this->SetSizer(fgSMDWater);

    Connect(IDBTN_WATERBASE_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdWaterTab::OnClickWaterBaseColour));
    Connect(IDBTN_WATERMIN_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdWaterTab::OnClickWaterMinColour));
    Connect(IDBTN_WATERABSORB_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_smdWaterTab::OnClickWaterAbsorbColour));
}
void _smdWaterTab::OnClickWaterBaseColour(wxCommandEvent& event){
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colWaterBase = colourData->GetColour();
        pnlWaterBaseColourDisplay->SetBackgroundColour(*colWaterBase);
        pnlWaterBaseColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}

void _smdWaterTab::OnClickWaterMinColour(wxCommandEvent& event){
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colWaterMin = colourData->GetColour();
        pnlWaterMinColourDisplay->SetBackgroundColour(*colWaterMin);
        pnlWaterMinColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}

void _smdWaterTab::OnClickWaterAbsorbColour(wxCommandEvent& event){
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colWaterAbsorb = colourData->GetColour();
        pnlWaterAbsorbColourDisplay->SetBackgroundColour(*colWaterAbsorb);
        pnlWaterAbsorbColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
