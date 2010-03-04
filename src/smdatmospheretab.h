#ifndef SMDATMOSPHERETAB_H
#define SMDATMOSPHERETAB_H
#include "resources.h"

class _smdAtmosphereTab : public wxPanel{
    public:
        _smdAtmosphereTab(wxWindow* parent, wxWindowID id);
    private:
        wxColourDialog *cldColour;
        wxColourData *colourData;
        wxColour *tempColour;

        wxButton *btnSunColour;
        wxButton *btnSkyColour;
        wxButton *btnCloudColour;
        wxButton *btnFogColour;
        wxPanel *pnlSunColourDisplay;
        wxPanel *pnlSkyColourDisplay;
        wxPanel *pnlCloudColourDisplay;
        wxTextCtrl *tcCloudDensity;
        wxPanel *pnlFogColourDisplay;
        wxTextCtrl *tcFogStart;

        wxButton *btnGroundAmbientColour;
        wxButton *btnGroundSunColour;
        wxButton *btnUnitAmbientColour;
        wxButton *btnUnitSunColour;
        wxPanel *pnlGroundAmbientColourDisplay;
        wxTextCtrl *tcGroundShadowDensity;
        wxPanel *pnlGroundSunColourDisplay;
        wxPanel *pnlUnitAmbientColourDisplay;
        wxPanel *pnlUnitSunColourDisplay;
        wxTextCtrl *tcUnitShadowDensity;

        wxColour *colSun;
        wxColour *colSky;
        wxColour *colCloud;
        wxColour *colFog;

        wxColour *colGroundAmbient;
        wxColour *colGroundSun;
        wxColour *colUnitAmbient;
        wxColour *colUnitSun;
        wxPanel *pnlSunDirection;

        void OnClickSunColour(wxCommandEvent& event);
        void OnClickSkyColour(wxCommandEvent& event);
        void OnClickCloudColour(wxCommandEvent& event);
        void OnClickFogColour(wxCommandEvent& event);
        void OnChangeCloudDensityText(wxCommandEvent& event);
        void OnChangeFogStartText(wxCommandEvent& event);

        void OnClickGroundAmbientColour(wxCommandEvent& event);
        void OnClickGroundSunColour(wxCommandEvent& event);
        void OnClickUnitAmbientColour(wxCommandEvent& event);
        void OnClickUnitSunColour(wxCommandEvent& event);
        void OnChangeGroundShadowDensityText(wxCommandEvent& event);
        void OnChangeUnitShadowDensityText(wxCommandEvent& event);
};
#endif


