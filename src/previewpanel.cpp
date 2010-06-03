#include "previewpanel.h"

_previewPanel::_previewPanel::_previewPanel(wxWindow* parent, wxWindowID id) : wxPanel(parent, id){
    //Connect(IDPNL_PREVIEW, wxEVT_LEFT_DOWN, 0, wxMouseEventHandler(_previewPanel::OnClickPreview));
    Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler(_previewPanel::OnClickPreview),0, this);
}

void _previewPanel::OnClickPreview(wxMouseEvent& event){
    event.Skip(true);
}
