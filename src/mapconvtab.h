#ifndef MAPCONVTAB_H
#define MAPCONVTAB_H
#include "resources.h"

class _mapconvTab : public wxPanel{
    public:
        _mapconvTab(wxWindow* parent, wxWindowID id);
        void Compile(void);

        wxTextCtrl *tcHeight;
        wxTextCtrl *tcTexture;
        wxTextCtrl *tcMetal;
        wxCheckBox *cbFeatureEnable;
        wxTextCtrl *tcFeature;
        wxTextCtrl *tcFeatureList;
        wxCheckBox *cbTypeEnable;
        wxTextCtrl *tcType;
        wxTextCtrl *tcGeovent;
        wxCheckBox *cbOtherOptionsEnable;
        wxTextCtrl *tcOtherOptions;
        wxTextCtrl *tcOutput;
        wxTextCtrl *tcMax;
        wxTextCtrl *tcMin;

        wxCheckBox *cbLowpass;
        wxCheckBox *cbInvert;

        wxTextCtrl *tcCompression;
        wxTextCtrl *tcFeatureRotate;

        wxRadioBox *rbxQuality;

        wxStaticBitmap *sbmPreview;

        bool bTextureLoaded;
        bool bHeightmapLoaded;
        bool bMetalLoaded;
        bool bFeatureLoaded;
        bool bTypemapLoaded;

        float fWaterHeight;

        float calculateWaterHeight(void);

    private:
        bool bLowpass;
        bool bInvert;
        bool bFeatureEnable;
        bool bTypemapEnable;
        bool bOtherEnable;
        bool bOtherFirstTime;

        wxString path;
        wxFileDialog *openFileDialog;
        wxButton *btnHeight;
        wxButton *btnTexture;
        wxButton *btnMetal;
        wxButton *btnFeature;
        wxButton *btnFeatureList;
        wxButton *btnType;
        wxButton *btnGeovent;
        wxButton *btnOutput;

        wxBoxSizer *hboxMax;
        wxBoxSizer *hboxMin;
        wxStaticText *stMax;
        wxStaticText *stMin;

        wxStaticText *stCompression;
        wxStaticText *stFeatureRotate;

        void reset(void);

        void OnOpenHeight(wxCommandEvent& event);
        void OnOpenTexture(wxCommandEvent& event);
        void OnOpenMetal(wxCommandEvent& event);
        void OnOpenFeature(wxCommandEvent& event);
        void OnOpenFeatureList(wxCommandEvent& event);
        void OnOpenType(wxCommandEvent& event);
        void OnOpenGeovent(wxCommandEvent& event);
        void OnOpenOutput(wxCommandEvent& event);

        void OnChangeMax(wxCommandEvent& event);
        void OnChangeMin(wxCommandEvent& event);

        void OnToggleLowpass(wxCommandEvent& event);
        void OnToggleInvert(wxCommandEvent& event);
        void OnToggleFeatureEnable(wxCommandEvent& event);
        void OnToggleTypemapEnable(wxCommandEvent& event);
        void OnToggleOtherEnable(wxCommandEvent& event);
};
#endif


