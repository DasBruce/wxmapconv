#ifndef PREVIEWTAB_H
#define PREVIEWTAB_H
#include "resources.h"

class _previewTab : public wxPanel{
    public:
        _previewTab(wxWindow* parent, wxWindowID id);
        bool LoadPreviewImage(int type, wxImage *image);
        float fWaterHeight;
        wxTextCtrl *tcHeightMax;
        wxTextCtrl *tcHeightMin;

    private:
        wxStaticBitmap *sbmPreviewBig;
        wxRadioBox *rbxPreview;

        wxCheckBox *cbOverlayWater;
        wxButton *btnRecalculateWater;

        wxBitmap *bmBitmap;

		wxImage imHeightmap;
		wxImage imTexture;
		wxImage imMetal;
		wxImage imFeature;
		wxImage imTypemap;

		wxImage imHeightmapWater;
		wxImage imTextureWater;
		wxImage imMetalWater;
		wxImage imFeatureWater;
		wxImage imTypemapWater;

		//wxBitmap bmWater;
		bool bShowWater;
		bool bHeightmapLoaded;
		bool bTextureLoaded;
		bool bMetalLoaded;
		bool bFeatureLoaded;
		bool bTypemapLoaded;

        void UpdatePreview(void);
        void GenerateWaterImage(wxImage *imHeight, wxImage *imUnderlay, int type);

        void OnChangePreview(wxCommandEvent& event);
        void OnClickRecalculateWater(wxCommandEvent& event);
        void OnClickShowWater(wxCommandEvent& event);
        void OnChangeMaxPreview(wxCommandEvent& event);
        void OnChangeMinPreview(wxCommandEvent& event);
        void OnClickPreview(wxMouseEvent& event);
};
#endif
