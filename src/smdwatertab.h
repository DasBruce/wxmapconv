#ifndef SMDWATERTAB_H
#define SMDWATERTAB_H
#include "resources.h"

class _smdWaterTab : public wxPanel{
    public:
        wxColour *colWaterBase;
        wxColour *colWaterMin;
        wxColour *colWaterAbsorb;

        _smdWaterTab(wxWindow* parent, wxWindowID id);
        void reset(void);
    private:
        wxColourDialog *cldColour;
        wxColourData *colourData;
        wxColour *tempColour;


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



