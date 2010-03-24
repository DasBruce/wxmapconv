#ifndef PREVIEWTAB_H
#define PREVIEWTAB_H
#include "resources.h"

class _previewTab : public wxPanel{
    public:
        _previewTab(wxWindow* parent, wxWindowID id);
        bool LoadPreviewImage(int type, wxImage *image);

    private:
        wxStaticBitmap *sbmPreviewBig;
        wxRadioBox *rbxPreview;

        wxCheckBox *cbOverlayWater;

		wxBitmap bmHeightmap;
		wxBitmap bmTexture;
		wxBitmap bmMetal;
		wxBitmap bmFeature;
		wxBitmap bmTypemap;

        void OnChangePreview(wxCommandEvent& event);
};
#endif
