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
        //preveiew panel//////////////////////////////////////////////////////////////

        wxImage *image;

        void setDefaultsMapconv(void);

        void SaveProject(void);

        void LoadImage(int type);

        void OnClickNew(wxCommandEvent& event);
        void OnClickLoadProject(wxCommandEvent& event);
        void OnClickSaveProject(wxCommandEvent& event);
        void OnClickSaveProjectAs(wxCommandEvent& event);
        void OnClickCompile(wxCommandEvent& event);
        void OnClickResetSMD(wxCommandEvent& event);
		void OnTabSwitch(wxCommandEvent& event);
        void OnClickSaveSMD(wxCommandEvent& event);
        void OnClickOpenSMD(wxCommandEvent& event);
};

#endif //#ifndef FRONENT_HH_INCLUDED
