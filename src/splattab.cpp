#include "splattab.h"

_splatTab::_splatTab(wxWindow* parent, wxWindowID id) : wxPanel(parent, id){

    wxBoxSizer *vboxSplatMain = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *hboxRedChannel = new wxBoxSizer(wxHORIZONTAL);
            tcRedChannel = new wxTextCtrl(this, IDTC_REDCHANNEL, wxT("Red channel source"));
            wxButton *btnRedChannel = new wxButton(this, IDBTN_REDCHANNEL, wxT("Red"));
        wxBoxSizer *hboxGreenChannel = new wxBoxSizer(wxHORIZONTAL);
            tcGreenChannel = new wxTextCtrl(this, IDTC_GREENCHANNEL, wxT("Green channel source"));
            wxButton *btnGreenChannel = new wxButton(this, IDBTN_GREENCHANNEL, wxT("Green"));
        wxBoxSizer *hboxBlueChannel = new wxBoxSizer(wxHORIZONTAL);
            tcBlueChannel = new wxTextCtrl(this, IDTC_BLUECHANNEL, wxT("Blue channel source"));
            wxButton *btnBlueChannel = new wxButton(this, IDBTN_BLUECHANNEL, wxT("Blue"));
//        wxBoxSizer *hboxOutputSplat = new wxBoxSizer(wxHORIZONTAL);
//            tcOutputSplat = new wxTextCtrl(this, IDTC_OUTPUTSPLAT, wxT("Output splat file"));
//            wxButton *btnOutputSplat = new wxButton(this, IDBTN_OUTPUTSPLAT, wxT("Output"));

        hboxRedChannel->Add(tcRedChannel, 1, wxALL | wxEXPAND, 3);
        hboxRedChannel->Add(btnRedChannel, 0, wxALL | wxEXPAND, 3);
    vboxSplatMain->Add(hboxRedChannel, 0, wxALL | wxEXPAND, 3);
        hboxGreenChannel->Add(tcGreenChannel, 1, wxALL | wxEXPAND, 3);
        hboxGreenChannel->Add(btnGreenChannel, 0, wxALL | wxEXPAND, 3);
    vboxSplatMain->Add(hboxGreenChannel, 0, wxALL | wxEXPAND, 3);
        hboxBlueChannel->Add(tcBlueChannel, 1, wxALL | wxEXPAND, 3);
        hboxBlueChannel->Add(btnBlueChannel, 0, wxALL | wxEXPAND, 3);
    vboxSplatMain->Add(hboxBlueChannel, 0, wxALL | wxEXPAND, 3);
//        hboxOutputSplat->Add(tcOutputSplat, 1, wxALL | wxEXPAND, 3);
//        hboxOutputSplat->Add(btnOutputSplat, 0, wxALL | wxEXPAND, 3);
//    vboxSplatMain->Add(hboxOutputSplat, 0, wxALL | wxEXPAND, 3);

    this->SetSizer(vboxSplatMain);

    Connect(IDBTN_REDCHANNEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_splatTab::OnClickRed));
    Connect(IDBTN_GREENCHANNEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_splatTab::OnClickGreen));
    Connect(IDBTN_BLUECHANNEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_splatTab::OnClickBlue));
//    Connect(IDBTN_OUTPUTSPLAT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_splatTab::OnClickOutput));
}

void _splatTab::OnClickRed(wxCommandEvent& event){
    wxFileDialog *openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcRedChannel->SetValue(openFileDialog->GetPath());
    }
}

void _splatTab::OnClickGreen(wxCommandEvent& event){
    wxFileDialog *openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcGreenChannel->SetValue(openFileDialog->GetPath());
    }
}

void _splatTab::OnClickBlue(wxCommandEvent& event){
    wxFileDialog *openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcBlueChannel->SetValue(openFileDialog->GetPath());
    }
}

void _splatTab::OnClickOutput(wxCommandEvent& event){
    wxFileDialog *openFileDialog = new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("*.*"), wxFD_SAVE);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcOutputSplat->SetValue(openFileDialog->GetPath());
    }
}
