#ifndef SMDWATERTAB_H
#define SMDWATERTAB_H
#include "resources.h"

class _smdWaterTab : public wxPanel{
    public:
        wxColour *colWaterBase;
        wxColour *colWaterMin;
        wxColour *colWaterAbsorb;
        wxColour *colWaterPlane;
        wxColour *colWaterSurface;

        wxPanel *pnlWaterBaseColourDisplay;
        wxPanel *pnlWaterMinColourDisplay;
        wxPanel *pnlWaterAbsorbColourDisplay;
        wxPanel *pnlWaterPlaneColourDisplay;
        wxPanel *pnlWaterSurfaceColourDisplay;

        _smdWaterTab(wxWindow* parent, wxWindowID id);
        void reset(void);
    private:
        wxColourDialog *cldColour;
        wxColourData *colourData;
        wxColour *tempColour;

        wxButton *btnWaterBase;
        wxButton *btnWaterMin;
        wxButton *btnWaterAbsorb;
        wxButton *btnWaterPlane;
        wxButton *btnWaterSurface;

        void OnClickWaterBaseColour(wxCommandEvent& event);
        void OnClickWaterMinColour(wxCommandEvent& event);
        void OnClickWaterAbsorbColour(wxCommandEvent& event);
        void OnClickWaterPlaneColour(wxCommandEvent& event);
        void OnClickWaterSurfaceColour(wxCommandEvent& event);
};
#endif



