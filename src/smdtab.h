#ifndef SMDTAB_H
#define SMDTAB_H
#include "resources.h"
#include <wx/panel.h>

class _smdGeneralTab;
class _smdAtmosphereTab;
class _smdWaterTab;
class  wxButton;

class _smdTab : public wxPanel{
    public:
        _smdGeneralTab *smdGeneralTab;
        _smdAtmosphereTab *smdAtmosphereTab;
        _smdWaterTab *smdWaterTab;

        _smdTab(wxWindow* parent, wxWindowID id);
        void reset(void);
    private:
        wxNotebook *nbSMD;
        wxButton *btnSMDSave;
};

#endif
