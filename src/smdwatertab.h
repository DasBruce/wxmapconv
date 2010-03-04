#ifndef SMDWATERTAB_H
#define SMDWATERTAB_H
#include "resources.h"

class _smdWaterTab : public wxPanel{
    public:
        _smdWaterTab(wxWindow* parent, wxWindowID id);
    private:
        wxColourDialog *cldColour;
        wxColourData *colourData;
        wxColour *tempColour;

        wxColour *colWaterBase;
        wxColour *colWaterMin;
        wxColour *colWaterAbsorb;

        wxButton *btnWaterBase;
        wxPanel *pnlWaterBaseColourDisplay;
        wxButton *btnWaterMin;
        wxPanel *pnlWaterMinColourDisplay;
        wxButton *btnWaterAbsorb;
        wxPanel *pnlWaterAbsorbColourDisplay;

        void OnClickWaterBaseColour(wxCommandEvent& event);
        void OnClickWaterMinColour(wxCommandEvent& event);
        void OnClickWaterAbsorbColour(wxCommandEvent& event);
};
#endif



