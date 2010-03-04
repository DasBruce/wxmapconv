#ifndef SMDGENERALTAB_H
#define SMDGENERALTAB_H
#include "resources.h"

class _smdGeneralTab : public wxPanel{
    public:
        _smdGeneralTab(wxWindow* parent, wxWindowID id);
    private:
        int iOldTeamCount;

        wxTextCtrl *tcDescription;
        wxTextCtrl *tcGravity;
        wxTextCtrl *tcMapHardness;
        wxTextCtrl *tcMaxMetal;
        wxTextCtrl *tcExtractorRadius;
        wxTextCtrl *tcTidalStrength;
        wxTextCtrl *tcMaxWind;
        wxTextCtrl *tcMinWind;
        wxTextCtrl *tcMaxHeight;
        wxTextCtrl *tcMinHeight;

        wxTextCtrl *tcTeamCount;
        wxTextCtrl *tcTeam1X;
        wxTextCtrl *tcTeam1Y;
        wxTextCtrl *tcTeam2X;
        wxTextCtrl *tcTeam2Y;
        wxTextCtrl *tcTeam3X;
        wxTextCtrl *tcTeam3Y;
        wxTextCtrl *tcTeam4X;
        wxTextCtrl *tcTeam4Y;
        wxTextCtrl *tcTeam5X;
        wxTextCtrl *tcTeam5Y;
        wxTextCtrl *tcTeam6X;
        wxTextCtrl *tcTeam6Y;
        wxTextCtrl *tcTeam7X;
        wxTextCtrl *tcTeam7Y;
        wxTextCtrl *tcTeam8X;
        wxTextCtrl *tcTeam8Y;

		void OnChangeTeamCount(wxCommandEvent& event);
};
#endif

