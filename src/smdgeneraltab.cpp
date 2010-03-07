#include "smdgeneraltab.h"

#define GRAVITY "130"
#define MAPHARDNESS "100"
#define MAXMETAL "3.0"
#define EXTRACTORRADIUS "50"
#define TIDALSTRENGTH "20"
#define MAXWIND "30"
#define MINWIND "10"
#define MAXHEIGHT "250"
#define MINHEIGHT "25"
#define STARTPOSX "64"
#define STARTPOSY "64"

_smdGeneralTab::_smdGeneralTab(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
    wxBoxSizer *vboxSMDGeneralMain = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer *gboxSMDGeneral = new wxStaticBoxSizer(wxVERTICAL, this, wxT("General Map Options"));
    wxFlexGridSizer* gsSMDBasic = new wxFlexGridSizer(0,4,5,5);

    wxStaticText *stDescription = new wxStaticText(this, wxID_ANY, wxT("Description"));
    tcDescription = new wxTextCtrl(this, wxID_ANY, wxT("Description of your map"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    wxStaticText *stGravity = new wxStaticText(this, wxID_ANY, wxT("Gravity"));
    tcGravity = new wxTextCtrl(this, wxID_ANY, wxT(GRAVITY));
    wxStaticText *stMapHardness = new wxStaticText(this, wxID_ANY, wxT("Map Hardness"));
    tcMapHardness = new wxTextCtrl(this, wxID_ANY, wxT(MAPHARDNESS));
    wxStaticText *stMaxMetal = new wxStaticText(this, wxID_ANY, wxT("Max Metal"));
    tcMaxMetal = new wxTextCtrl(this, wxID_ANY, wxT(MAXMETAL));
    wxStaticText *stExtractorRadius = new wxStaticText(this, wxID_ANY, wxT("Extractor Radius"));
    tcExtractorRadius = new wxTextCtrl(this, wxID_ANY, wxT(EXTRACTORRADIUS));
    wxStaticText *stTidalStrength = new wxStaticText(this, wxID_ANY, wxT("TidalStrength"));
    tcTidalStrength = new wxTextCtrl(this, wxID_ANY, wxT(TIDALSTRENGTH));
    wxStaticText *stMaxWind = new wxStaticText(this, wxID_ANY, wxT("MaxWind"));
    tcMaxWind = new wxTextCtrl(this, IDTC_MAX_HEIGHT, wxT(MAXWIND));
    wxStaticText *stMinWind = new wxStaticText(this, wxID_ANY, wxT("MinWind"));
    tcMinWind = new wxTextCtrl(this, IDTC_MIN_HEIGHT, wxT(MINWIND));
    wxStaticText *stMaxHeight = new wxStaticText(this, wxID_ANY, wxT("Max Height"));
    tcMaxHeight = new wxTextCtrl(this, IDTC_MAX_HEIGHT, wxT(MAXHEIGHT));
    wxStaticText *stMinHeight = new wxStaticText(this, wxID_ANY, wxT("Min Height"));
    tcMinHeight = new wxTextCtrl(this, IDTC_MIN_HEIGHT, wxT(MINHEIGHT));

    wxStaticBoxSizer *gboxSMDStartPos = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Player Start Options"));

    wxGridSizer *gsStartPos = new wxFlexGridSizer(0,5,5,5);
        wxStaticText *stTeamCount = new wxStaticText(this, wxID_ANY, wxT("Number of Players"));
        tcTeamCount = new wxTextCtrl(this, IDTC_TEAM_COUNT, wxT("4"), wxDefaultPosition, wxSize(50,20), 0, wxDefaultValidator, wxT("TeamCount"));
        wxPanel *pnlTeamCountPlaceHolder1 = new wxPanel(this, -1);
        wxPanel *pnlTeamCountPlaceHolder2 = new wxPanel(this, -1);
        wxPanel *pnlTeamCountPlaceHolder3 = new wxPanel(this, -1);

        wxStaticText *stTeam1 = new wxStaticText(this, wxID_ANY, wxT("Team1"));
            wxStaticText *stTeam1X = new wxStaticText(this, -1, wxT(" X "));
            tcTeam1X = new wxTextCtrl(this, -1, wxT("64"));
            wxStaticText *stTeam1Y = new wxStaticText(this, -1, wxT(" Y "));
            tcTeam1Y = new wxTextCtrl(this, -1, wxT("64"));
        wxStaticText *stTeam2 = new wxStaticText(this, wxID_ANY, wxT("Team2"));
            wxStaticText *stTeam2X = new wxStaticText(this, -1, wxT(" X "));
            tcTeam2X = new wxTextCtrl(this, -1, wxT("64"));
            wxStaticText *stTeam2Y = new wxStaticText(this, -1, wxT(" Y "));
            tcTeam2Y = new wxTextCtrl(this, -1, wxT("64"));
        wxStaticText *stTeam3 = new wxStaticText(this, wxID_ANY, wxT("Team3"));
            wxStaticText *stTeam3X = new wxStaticText(this, -1, wxT(" X "));
            tcTeam3X = new wxTextCtrl(this, -1, wxT("64"));
            wxStaticText *stTeam3Y = new wxStaticText(this, -1, wxT(" Y "));
            tcTeam3Y = new wxTextCtrl(this, -1, wxT("64"));
        wxStaticText *stTeam4 = new wxStaticText(this, wxID_ANY, wxT("Team4"));
            wxStaticText *stTeam4X = new wxStaticText(this, -1, wxT(" X "));
            tcTeam4X = new wxTextCtrl(this, -1, wxT("64"));
            wxStaticText *stTeam4Y = new wxStaticText(this, -1, wxT(" Y "));
            tcTeam4Y = new wxTextCtrl(this, -1, wxT("64"));
        wxStaticText *stTeam5 = new wxStaticText(this, wxID_ANY, wxT("Team5"));
            wxStaticText *stTeam5X = new wxStaticText(this, -1, wxT(" X "));
            tcTeam5X = new wxTextCtrl(this, -1, wxT("64"));
            wxStaticText *stTeam5Y = new wxStaticText(this, -1, wxT(" Y "));
            tcTeam5Y = new wxTextCtrl(this, -1, wxT("64"));
        wxStaticText *stTeam6 = new wxStaticText(this, wxID_ANY, wxT("Team6"));
            wxStaticText *stTeam6X = new wxStaticText(this, -1, wxT(" X "));
            tcTeam6X = new wxTextCtrl(this, -1, wxT("64"));
            wxStaticText *stTeam6Y = new wxStaticText(this, -1, wxT(" Y "));
            tcTeam6Y = new wxTextCtrl(this, -1, wxT("64"));
        wxStaticText *stTeam7 = new wxStaticText(this, wxID_ANY, wxT("Team7"));
            wxStaticText *stTeam7X = new wxStaticText(this, -1, wxT(" X "));
            tcTeam7X = new wxTextCtrl(this, -1, wxT("64"));
            wxStaticText *stTeam7Y = new wxStaticText(this, -1, wxT(" Y "));
            tcTeam7Y = new wxTextCtrl(this, -1, wxT("64"));
        wxStaticText *stTeam8 = new wxStaticText(this, wxID_ANY, wxT("Team8"));
            wxStaticText *stTeam8X = new wxStaticText(this, -1, wxT(" X "));
            tcTeam8X = new wxTextCtrl(this, -1, wxT("64"));
            wxStaticText *stTeam8Y = new wxStaticText(this, -1, wxT(" Y "));
            tcTeam8Y = new wxTextCtrl(this, -1, wxT("64"));
        tcTeam5X->Enable(false);
        tcTeam5Y->Enable(false);
        tcTeam6X->Enable(false);
        tcTeam6Y->Enable(false);
        tcTeam7X->Enable(false);
        tcTeam7Y->Enable(false);
        tcTeam8X->Enable(false);
        tcTeam8Y->Enable(false);

    gsSMDBasic->SetFlexibleDirection(wxVERTICAL);
    gsSMDBasic->Add(stDescription, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcDescription, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stGravity, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcGravity, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMapHardness, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMapHardness, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMaxMetal, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMaxMetal, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stExtractorRadius, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcExtractorRadius, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stTidalStrength, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcTidalStrength, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMaxWind, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMaxWind, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMinWind, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMinWind, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMaxHeight, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMaxHeight, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMinHeight, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMinHeight, 3, wxEXPAND, 0);

    gsStartPos->Add(stTeamCount, 1, wxEXPAND, 0);
    gsStartPos->Add(tcTeamCount, 1, wxEXPAND, 0);
    gsStartPos->Add(pnlTeamCountPlaceHolder1, 1, wxEXPAND, 0);
    gsStartPos->Add(pnlTeamCountPlaceHolder2, 1, wxEXPAND, 0);
    gsStartPos->Add(pnlTeamCountPlaceHolder3, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam1, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam1X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam1X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam1Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam1Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam2, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam2X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam2X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam2Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam2Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam3, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam3X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam3X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam3Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam3Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam4, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam4X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam4X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam4Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam4Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam5, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam5X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam5X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam5Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam5Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam6, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam6X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam6X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam6Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam6Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam7, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam7X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam7X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam7Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam7Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam8, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam8X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam8X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam8Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam8Y, 1, wxEXPAND, 0);

    gboxSMDGeneral->Add(gsSMDBasic, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxSMDStartPos->Add(gsStartPos, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

    vboxSMDGeneralMain->Add(gboxSMDGeneral, 3, wxEXPAND, 0);
    vboxSMDGeneralMain->Add(gboxSMDStartPos, 4, wxEXPAND, 0);
    this->SetSizer(vboxSMDGeneralMain);


    Connect(IDTC_TEAM_COUNT, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(_smdGeneralTab::OnChangeTeamCount));

}

void _smdGeneralTab::OnChangeTeamCount(wxCommandEvent& event){
    int i = wxAtoi(tcTeamCount->GetValue());

    if(i>8)       i=8;
    else if(i<2)    i=2;

    tcTeamCount->ChangeValue(wxString::Format(wxT("%i"), i));

    if(i!=iOldTeamCount)
    {
        if(i==2){
            tcTeam3X->Enable(false);
            tcTeam3Y->Enable(false);
            tcTeam4X->Enable(false);
            tcTeam4Y->Enable(false);
            tcTeam5X->Enable(false);
            tcTeam5Y->Enable(false);
            tcTeam6X->Enable(false);
            tcTeam6Y->Enable(false);
            tcTeam7X->Enable(false);
            tcTeam7Y->Enable(false);
            tcTeam8X->Enable(false);
            tcTeam8Y->Enable(false);
        }
        if(i==3){
            tcTeam3X->Enable(true);
            tcTeam3Y->Enable(true);
            tcTeam4X->Enable(false);
            tcTeam4Y->Enable(false);
            tcTeam5X->Enable(false);
            tcTeam5Y->Enable(false);
            tcTeam6X->Enable(false);
            tcTeam6Y->Enable(false);
            tcTeam7X->Enable(false);
            tcTeam7Y->Enable(false);
            tcTeam8X->Enable(false);
            tcTeam8Y->Enable(false);
        }
        if(i==4){
            tcTeam3X->Enable(true);
            tcTeam3Y->Enable(true);
            tcTeam4X->Enable(true);
            tcTeam4Y->Enable(true);
            tcTeam5X->Enable(false);
            tcTeam5Y->Enable(false);
            tcTeam6X->Enable(false);
            tcTeam6Y->Enable(false);
            tcTeam7X->Enable(false);
            tcTeam7Y->Enable(false);
            tcTeam8X->Enable(false);
            tcTeam8Y->Enable(false);
        }
        if(i==5){
            tcTeam3X->Enable(true);
            tcTeam3Y->Enable(true);
            tcTeam4X->Enable(true);
            tcTeam4Y->Enable(true);
            tcTeam5X->Enable(true);
            tcTeam5Y->Enable(true);
            tcTeam6X->Enable(false);
            tcTeam6Y->Enable(false);
            tcTeam7X->Enable(false);
            tcTeam7Y->Enable(false);
            tcTeam8X->Enable(false);
            tcTeam8Y->Enable(false);
        }
        if(i==6){
            tcTeam3X->Enable(true);
            tcTeam3Y->Enable(true);
            tcTeam4X->Enable(true);
            tcTeam4Y->Enable(true);
            tcTeam5X->Enable(true);
            tcTeam5Y->Enable(true);
            tcTeam6X->Enable(true);
            tcTeam6Y->Enable(true);
            tcTeam7X->Enable(false);
            tcTeam7Y->Enable(false);
            tcTeam8X->Enable(false);
            tcTeam8Y->Enable(false);
        }
        if(i==7){
            tcTeam3X->Enable(true);
            tcTeam3Y->Enable(true);
            tcTeam4X->Enable(true);
            tcTeam4Y->Enable(true);
            tcTeam5X->Enable(true);
            tcTeam5Y->Enable(true);
            tcTeam6X->Enable(true);
            tcTeam6Y->Enable(true);
            tcTeam7X->Enable(true);
            tcTeam7Y->Enable(true);
            tcTeam8X->Enable(false);
            tcTeam8Y->Enable(false);
        }
        if(i==8){
            tcTeam3X->Enable(true);
            tcTeam3Y->Enable(true);
            tcTeam4X->Enable(true);
            tcTeam4Y->Enable(true);
            tcTeam5X->Enable(true);
            tcTeam5Y->Enable(true);
            tcTeam6X->Enable(true);
            tcTeam6Y->Enable(true);
            tcTeam7X->Enable(true);
            tcTeam7Y->Enable(true);
            tcTeam8X->Enable(true);
            tcTeam8Y->Enable(true);
        }
    }
}

void _smdGeneralTab::reset(void)
{
    tcGravity->SetValue(wxT(GRAVITY));
    tcMapHardness->SetValue(wxT(MAPHARDNESS));
    tcMaxMetal->SetValue(wxT(MAXMETAL));
    tcExtractorRadius->SetValue(wxT(EXTRACTORRADIUS));
    tcTidalStrength->SetValue(wxT(TIDALSTRENGTH));
    tcMaxWind->SetValue(wxT(MAXWIND));
    tcMinWind->SetValue(wxT(MINWIND));
    tcMaxHeight->SetValue(wxT(MAXHEIGHT));
    tcMinHeight->SetValue(wxT(MINHEIGHT));
}

