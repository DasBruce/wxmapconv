#ifndef SMDTAB_H
#define SMDTAB_H
#include "resources.h"

class _smdTab : public wxPanel{
    public:
        _smdTab(wxWindow* parent, wxWindowID id);
    private:
        wxButton *btnSMDSave;
        _smdGeneralTab *smdGeneralTab;
        _smdAtmosphereTab *smdAtmosphereTab;
        _smdWaterTab *smdWaterTab;
};

#endif
