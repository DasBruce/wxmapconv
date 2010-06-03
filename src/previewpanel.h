#ifndef PREVIEWPANEL_H
#define PREVIEWPANEL_H
#include "resources.h"

class _previewPanel : public wxPanel{
    public:
        _previewPanel(wxWindow* parent, wxWindowID id);
        void OnClickPreview(wxMouseEvent& event);
};

#endif
