#ifndef SPLATTAB_H
#define SPLATTAB_H
#include "resources.h"

class _splatTab : public wxPanel{
    public:
        _splatTab(wxWindow* parent, wxWindowID id);

        wxTextCtrl *tcRedChannel;
        wxTextCtrl *tcGreenChannel;
        wxTextCtrl *tcBlueChannel;
        wxTextCtrl *tcOutputSplat;

    private:
        void OnClickRed(wxCommandEvent& event);
        void OnClickGreen(wxCommandEvent& event);
        void OnClickBlue(wxCommandEvent& event);
        void OnClickOutput(wxCommandEvent& event);
};
#endif

