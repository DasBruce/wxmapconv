#ifndef MAPCONVTAB_H
#define MAPCONVTAB_H
#include "resources.h"

class _mapconvTab : public wxPanel{
    public:
        _mapconvTab(wxWindow* parent, wxWindowID id);
    private:
        bool bLowpass;
        bool bInvert;
        bool bFeatureEnable;
        bool bTypemapEnable;
        bool bOtherEnable;
        bool bOtherFirstTime;

        bool bTextureLoaded;
        bool bHeightmapLoaded;
        bool bMetalLoaded;
        bool bFeatureLoaded;
        bool bTypemapLoaded;

        wxString path;
        wxFileDialog *openFileDialog;
        wxButton *btnHeight;
        wxTextCtrl *tcHeight;
        wxButton *btnTexture;
        wxTextCtrl *tcTexture;
        wxButton *btnMetal;
        wxTextCtrl *tcMetal;
        wxCheckBox *cbFeatureEnable;
        wxButton *btnFeature;
        wxTextCtrl *tcFeature;
        wxButton *btnFeatureList;
        wxTextCtrl *tcFeatureList;
        wxCheckBox *cbTypeEnable;
        wxButton *btnType;
        wxTextCtrl *tcType;
        wxButton *btnGeovent;
        wxTextCtrl *tcGeovent;
        wxCheckBox *cbOtherOptionsEnable;
        wxTextCtrl *tcOtherOptions;
        wxButton *btnOutput;
        wxTextCtrl *tcOutput;

        wxBoxSizer *hboxMax;
        wxBoxSizer *hboxMin;
        wxTextCtrl *tcMax;
        wxTextCtrl *tcMin;
        wxStaticText *stMax;
        wxStaticText *stMin;
        wxCheckBox *cbLowpass;
        wxCheckBox *cbInvert;

        wxTextCtrl *tcCompression;
        wxStaticText *stCompression;
        wxTextCtrl *tcFeatureRotate;
        wxStaticText *stFeatureRotate;

        wxRadioBox *rbxQuality;

        wxStaticBitmap *sbmPreview;

        wxButton *btnCompile;

        void OnOpenHeight(wxCommandEvent& event);
        void OnOpenTexture(wxCommandEvent& event);
        void OnOpenMetal(wxCommandEvent& event);
        void OnOpenFeature(wxCommandEvent& event);
        void OnOpenFeatureList(wxCommandEvent& event);
        void OnOpenType(wxCommandEvent& event);
        void OnOpenGeovent(wxCommandEvent& event);
        void OnOpenOutput(wxCommandEvent& event);

        void OnToggleLowpass(wxCommandEvent& event);
        void OnToggleInvert(wxCommandEvent& event);
        void OnToggleFeatureEnable(wxCommandEvent& event);
        void OnToggleTypemapEnable(wxCommandEvent& event);
        void OnToggleOtherEnable(wxCommandEvent& event);

        void OnClickCompile(wxCommandEvent& event);
};
#endif


