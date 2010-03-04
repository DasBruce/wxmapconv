#ifndef WXWFRONTEND_H
#define WXWFRONTEND_H
#include "resources.h"

class Frontend : public wxFrame{
    public:
        Frontend(const wxString& title);

    private:
        bool bSaved;

        wxFileDialog *openFileDialog;
        wxString sProjectName;
        wxString path;
        wxString projectPath;

        wxMenuBar *menubar;
        wxMenu *mnFile;
        wxMenu *mnAbout;

        wxNotebook *notebook;

        _previewTab *previewTab;
        _mapconvTab *mapconvTab;
        _smdTab *smdTab;
        //preveiew panel//////////////////////////////////////////////////////////////

        wxImage *image;

        void setDefaultsMapconv(void);
        void setDefaultsSMD(void);

        void SaveProject(void);
        void OpenSMD(void);

        void LoadImage(int type);

        void OnClickNew(wxCommandEvent& event);
        void OnClickLoadProject(wxCommandEvent& event);
        void OnClickSaveProject(wxCommandEvent& event);
        void OnClickSaveProjectAs(wxCommandEvent& event);
		void OnTabSwitch(wxCommandEvent& event);
        void OnClickSMDSave(wxCommandEvent& event);
        void OnMouseEvent(wxCommandEvent& event);
};

#endif //#ifndef FRONENT_HH_INCLUDED
