#ifndef WXWFRONTEND_H
#define WXWFRONTEND_H
#include "resources.h"

class Frontend : public wxFrame{
    public:
        Frontend(const wxString& title);

    private:
        bool bSaved;

        wxString sProjectName;
        wxString path;
        wxString projectPath;

        wxMenuBar *menubar;
        wxMenu *mnFile;
        wxMenu *mnSMD;
        wxMenu *mnMapconv;
        wxMenu *mnAbout;

        wxNotebook *notebook;

        _previewTab *previewTab;
        _mapconvTab *mapconvTab;
        _smdTab *smdTab;

        wxFileDialog *openFileDialog;

        wxImage *image;

        void setDefaultsMapconv(void);
        void SaveProject(void);
        void LoadImage(int type);
        void calculateWaterHeight(void);

        void OnClickNew(wxCommandEvent& event);
        void OnClickLoadProject(wxCommandEvent& event);
        void OnClickSaveProject(wxCommandEvent& event);
        void OnClickSaveProjectAs(wxCommandEvent& event);
        void OnClickCompile(wxCommandEvent& event);
        void OnClickResetSMD(wxCommandEvent& event);
		void OnTabSwitch(wxCommandEvent& event);
        void OnClickSaveSMD(wxCommandEvent& event);
        void OnClickOpenSMD(wxCommandEvent& event);

        void OnChangeMax(wxCommandEvent& event);
        void OnChangeMin(wxCommandEvent& event);
        void OnChangeMaxPreview(wxCommandEvent& event);
        void OnChangeMinPreview(wxCommandEvent& event);

        void OnOpenHeight(wxCommandEvent& event);
        void OnOpenTexture(wxCommandEvent& event);
        void OnOpenMetal(wxCommandEvent& event);
        void OnOpenFeature(wxCommandEvent& event);
        void OnOpenType(wxCommandEvent& event);
        void OnOpenGeovent(wxCommandEvent& event);

        void OnClickPreview(wxMouseEvent& event);
};

#endif //#ifndef FRONENT_HH_INCLUDED
