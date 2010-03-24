#include "mapconvtab.h"

_mapconvTab::_mapconvTab(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
    bLowpass = true;
    bInvert = true;
    bFeatureEnable = false;
    bTypemapEnable = false;
    bOtherEnable = false;
    bOtherFirstTime = true;

    bHeightmapLoaded = false;
    bTextureLoaded = false;
    bMetalLoaded = false;
    bFeatureLoaded = false;
    bTypemapLoaded = false;

    wxBoxSizer *hboxMain = new wxBoxSizer(wxHORIZONTAL);

//Vertical box for the files////////////////////////////////////////////////////////////////////////
    wxStaticBoxSizer *gboxFiles = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Files"));

    wxBoxSizer *hboxHeight = new wxBoxSizer(wxHORIZONTAL);              //Heightmap/////////////////
    btnHeight = new wxButton(this, IDBTN_HEIGHT, wxT("Height Map"));
    tcHeight = new wxTextCtrl(this, wxID_ANY, wxT("heightmap.bmp"));

    wxBoxSizer *hboxTexture = new wxBoxSizer(wxHORIZONTAL);             //Texture///////////////////
    btnTexture = new wxButton(this, IDBTN_TEXTURE, wxT("Texture"));
    tcTexture = new wxTextCtrl(this, wxID_ANY, wxT("texture.bmp"));

    wxBoxSizer *hboxMetal = new wxBoxSizer(wxHORIZONTAL);               //Metal/////////////////////
    btnMetal = new wxButton(this, IDBTN_METAL, wxT("Metal"));
    tcMetal = new wxTextCtrl(this, wxID_ANY, wxT("metal.bmp"));

    wxBoxSizer *hboxFeatureEnable = new wxBoxSizer(wxHORIZONTAL);       //Feature enable////////////
    cbFeatureEnable = new wxCheckBox(this, IDCB_FEATURE_ENABLE, wxT("Enable Feature Map"));
    wxBoxSizer *hboxFeature = new wxBoxSizer(wxHORIZONTAL);             //Feature///////////////////
    btnFeature = new wxButton(this, IDBTN_FEATURE, wxT("Feature"));
    tcFeature = new wxTextCtrl(this, wxID_ANY, wxT("featuremap.bmp"));
    btnFeature->Enable(bFeatureEnable);
    tcFeature->Enable(bFeatureEnable);

    wxBoxSizer *hboxFeatureList = new wxBoxSizer(wxHORIZONTAL);         //Feature list//////////////
    btnFeatureList = new wxButton(this, IDBTN_FEATURELIST, wxT("Feature List"));
    tcFeatureList = new wxTextCtrl(this, wxID_ANY, wxT("featurelist.txt"));
    btnFeatureList->Enable(bFeatureEnable);
    tcFeatureList->Enable(bFeatureEnable);

    wxBoxSizer *hboxTypeEnable = new wxBoxSizer(wxHORIZONTAL);       //Type enable////////////
    cbTypeEnable = new wxCheckBox(this, IDCB_TYPEMAP_ENABLE, wxT("Enable Type Map"));
    wxBoxSizer *hboxType = new wxBoxSizer(wxHORIZONTAL);             //Type///////////////////
    btnType = new wxButton(this, IDBTN_TYPE, wxT("Type"));
    tcType = new wxTextCtrl(this, wxID_ANY, wxT("typemap.bmp"));
    btnType->Enable(bTypemapEnable);
    tcType->Enable(bTypemapEnable);

    wxBoxSizer *hboxGeovent = new wxBoxSizer(wxHORIZONTAL);               //Geovent///////////////////
    btnGeovent = new wxButton(this, IDBTN_GEOVENT, wxT("Geovent"));
    tcGeovent = new wxTextCtrl(this, wxID_ANY, wxT("geovent.bmp"));

    wxBoxSizer *hboxOutput = new wxBoxSizer(wxHORIZONTAL);               //Output////////////////////
    btnOutput = new wxButton(this, IDBTN_OUTPUT, wxT("Output"));
    tcOutput = new wxTextCtrl(this, wxID_ANY, wxT("Output.smf"));

    wxBoxSizer *hboxOtherOptions = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vboxOtherOptions = new wxBoxSizer(wxVERTICAL);
    cbOtherOptionsEnable = new wxCheckBox(this, IDCB_OTHER_ENABLE, wxT("Enable Additional Options"));
    tcOtherOptions = new wxTextCtrl(this, IDST_OTHER, wxT("Additional Options"));
    tcOtherOptions->Enable(bOtherEnable);

//Vertical box for the heightmap options and quality controls/////////////////////////////////////////////////////////////////
    wxBoxSizer *vboxOptions = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer *gboxHeightOptions = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Heightmap Options"));
    wxStaticBoxSizer *gboxAdditionalOptions = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Other Options"));
    wxStaticBoxSizer *gboxPreview = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Preview"));

    wxFlexGridSizer *fgHeightOptions = new wxFlexGridSizer(4,2,5,5);
        stMax = new wxStaticText(this, IDTC_MIN_HEIGHT, wxT("Maximum"));
        tcMax = new wxTextCtrl(this, wxID_ANY, wxT("250"));
        stMin = new wxStaticText(this, IDTC_MIN_HEIGHT, wxT("Minimum"));
        tcMin = new wxTextCtrl(this, wxID_ANY, wxT("25"));
        cbLowpass = new wxCheckBox(this, IDCB_LOWPASS, wxT("Lowpass"));
        wxPanel *pnlLowpassPadding = new wxPanel(this, wxID_ANY);
        cbInvert = new wxCheckBox(this, IDCB_INVERT, wxT("Invert"));
        wxPanel *pnlInvertPadding = new wxPanel(this, wxID_ANY);
        cbLowpass->SetValue(bLowpass);
        cbInvert->SetValue(bInvert);

    wxFlexGridSizer *fgCompression = new wxFlexGridSizer(2,2,5,5);
        tcCompression = new wxTextCtrl(this, wxID_ANY, wxT("0.8"));
        stCompression = new wxStaticText(this, wxID_ANY, wxT("Compression"));
        tcFeatureRotate = new wxTextCtrl(this, wxID_ANY, wxT("0"));
        stFeatureRotate = new wxStaticText(this, wxID_ANY, wxT("Rotate # features"));

    wxArrayString *asQuality = new wxArrayString();
        asQuality->Add(wxT("Low"), 1);
        asQuality->Add(wxT("Medium"), 1);
        asQuality->Add(wxT("High"), 1);
        asQuality->Add(wxT("Best"), 1);
    rbxQuality = new wxRadioBox(this, IDRBX_QUALITY, wxT("nvdxt Options"), wxDefaultPosition, wxDefaultSize, *asQuality, 0, wxRA_SPECIFY_ROWS, wxDefaultValidator, wxT("radioBox"));
    rbxQuality->SetSelection(2);
    rbxQuality->SetItemToolTip(1, wxT("Requires an nvidia 8 gfx card or better."));

//Preview box////////////////////////////////////////////////////////////////////////////////////////
	sbmPreview = new wxStaticBitmap(this, wxID_ANY, charArr2wxBitmap( placeholder_png, sizeof( placeholder_png ) ), wxPoint(10, 10));

    gboxPreview->Add(sbmPreview, 1,  wxEXPAND | wxRIGHT | wxLEFT | wxBOTTOM | wxTOP, 5);
//Assemble files vbox////////////////////////////////////////////////////////////////////
    hboxHeight->Add(tcHeight, 1, wxLEFT | wxRIGHT, 8);
    hboxHeight->Add(btnHeight, 0, wxLEFT | wxRIGHT, 8);
    hboxTexture->Add(tcTexture, 1, wxLEFT | wxRIGHT, 8);
    hboxTexture->Add(btnTexture, 0, wxLEFT | wxRIGHT, 8);
    hboxMetal->Add(tcMetal, 1, wxLEFT | wxRIGHT, 8);
    hboxMetal->Add(btnMetal, 0, wxLEFT | wxRIGHT, 8);
    hboxFeatureEnable->Add(cbFeatureEnable, 0, wxLEFT | wxRIGHT, 8);
    hboxFeature->Add(tcFeature, 1, wxLEFT | wxRIGHT, 8);
    hboxFeature->Add(btnFeature, 0, wxLEFT | wxRIGHT, 8);
    hboxFeatureList->Add(tcFeatureList, 1, wxLEFT | wxRIGHT, 8);
    hboxFeatureList->Add(btnFeatureList, 0, wxLEFT | wxRIGHT, 8);
    hboxTypeEnable->Add(cbTypeEnable, 0, wxLEFT | wxRIGHT, 8);
    hboxType->Add(tcType, 1, wxLEFT | wxRIGHT, 8);
    hboxType->Add(btnType, 0, wxLEFT | wxRIGHT, 8);
    hboxGeovent->Add(tcGeovent, 1, wxLEFT | wxRIGHT, 8);
    hboxGeovent->Add(btnGeovent, 0, wxLEFT | wxRIGHT, 8);
    hboxOutput->Add(tcOutput, 1, wxLEFT | wxRIGHT, 8);
    hboxOutput->Add(btnOutput, 0, wxLEFT | wxRIGHT, 8);
        vboxOtherOptions->Add(cbOtherOptionsEnable, 0, wxLEFT | wxRIGHT, 8);
        vboxOtherOptions->Add(-1, 15);
        vboxOtherOptions->Add(tcOtherOptions, 1, wxLEFT | wxRIGHT, 8);
    hboxOtherOptions->Add(vboxOtherOptions, 1, wxLEFT | wxRIGHT, 8);

    gboxFiles->Add(hboxHeight, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxTexture, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxMetal, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxFeatureEnable, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxFeature, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(hboxFeatureList, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(hboxTypeEnable, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxType, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(hboxGeovent, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(hboxOutput, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gboxFiles->Add(hboxOtherOptions, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
//Assemble Heightmap options////////////////////////////////////////////////////////////////////////
        fgHeightOptions->Add(stMax, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(tcMax, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(stMin, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(tcMin, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(cbLowpass, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(pnlLowpassPadding, 1, wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(cbInvert, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(pnlInvertPadding, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
    gboxHeightOptions->Add(fgHeightOptions, 1, wxEXPAND ,0 ,0);
//Assemble Quality boxes////////////////////////////////////////////////////////////////////////////


    fgCompression->Add(stCompression, 1,  wxEXPAND | wxRIGHT | wxLEFT, 5);
    fgCompression->Add(tcCompression, 1,  wxEXPAND | wxRIGHT | wxLEFT, 5);
    fgCompression->Add(stFeatureRotate, 1,  wxEXPAND | wxRIGHT | wxLEFT, 5);
    fgCompression->Add(tcFeatureRotate, 1,  wxEXPAND | wxRIGHT | wxLEFT, 5);

    gboxAdditionalOptions->Add(fgCompression, 1, wxEXPAND | wxRIGHT | wxLEFT | wxTOP, 8);


    vboxOptions->Add(gboxHeightOptions, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    vboxOptions->Add(rbxQuality, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);/////////////////////////////////////////////////////
    vboxOptions->Add(gboxAdditionalOptions, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    vboxOptions->Add(gboxPreview, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
//Final assembly////////////////////////////////////////////////////////////////////////////////////
    hboxMain->Add(gboxFiles, 2, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5);
    hboxMain->Add(vboxOptions, 1, wxTOP | wxBOTTOM | wxALIGN_RIGHT, 5);

    this->SetSizer(hboxMain);


    calculateWaterHeight();


//Enabling checkboxes//
    Connect(IDCB_FEATURE_ENABLE, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(_mapconvTab::OnToggleFeatureEnable));
    Connect(IDCB_TYPEMAP_ENABLE, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(_mapconvTab::OnToggleTypemapEnable));
    Connect(IDCB_OTHER_ENABLE, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(_mapconvTab::OnToggleOtherEnable));

    Connect(IDCB_LOWPASS, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(_mapconvTab::OnToggleLowpass));
    Connect(IDCB_INVERT, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(_mapconvTab::OnToggleInvert));
//File inputs//
    Connect(IDBTN_HEIGHT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_mapconvTab::OnOpenHeight));
    Connect(IDBTN_TEXTURE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_mapconvTab::OnOpenTexture));
    Connect(IDBTN_METAL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_mapconvTab::OnOpenMetal));
    Connect(IDBTN_FEATURE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_mapconvTab::OnOpenFeature));
    Connect(IDBTN_FEATURELIST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_mapconvTab::OnOpenFeatureList));
    Connect(IDBTN_TYPE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_mapconvTab::OnOpenType));
    Connect(IDBTN_GEOVENT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_mapconvTab::OnOpenGeovent));
    Connect(IDBTN_OUTPUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_mapconvTab::OnOpenOutput));

    Connect(IDTC_MAX_HEIGHT, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(_mapconvTab::OnChangeMax));
    Connect(IDTC_MIN_HEIGHT, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(_mapconvTab::OnChangeMin));
}

void _mapconvTab::calculateWaterHeight(void){
    long max, min;

    max = wxAtoi(tcMax->GetValue());
    min = wxAtoi(tcMin->GetValue());

    if(min >= 0)
        iWaterHeight = -1;
    else
        iWaterHeight = (int)((-min)/(max-min)*255);

    tcHeight->SetValue(wxString::Format(wxT("%i"),iWaterHeight));
}

void _mapconvTab::OnChangeMax(wxCommandEvent& event){
    event.Skip();
}
void _mapconvTab::OnChangeMin(wxCommandEvent& event){
    event.Skip();
}


void _mapconvTab::OnOpenHeight(wxCommandEvent& event){
    event.Skip(true);
}

void _mapconvTab::OnOpenTexture(wxCommandEvent& event){
    event.Skip(true);
}

void _mapconvTab::OnOpenMetal(wxCommandEvent& event){
    event.Skip(true);
}

void _mapconvTab::OnOpenFeature(wxCommandEvent& event){
    event.Skip(true);
}

void _mapconvTab::OnOpenFeatureList(wxCommandEvent& event){
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcFeatureList->SetValue(path);
    }
}

void _mapconvTab::OnOpenType(wxCommandEvent& event){
    event.Skip(true);
}

void _mapconvTab::OnOpenGeovent(wxCommandEvent& event){
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcGeovent->SetValue(path);
    }
}

void _mapconvTab::OnOpenOutput(wxCommandEvent& event){
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcOutput->SetValue(path);
    }
}

void _mapconvTab::Compile(void){
    wxString command;
    command.append(wxT("MapConv"));

    if(bLowpass)
        command.append(wxT(" -l"));
    if(bInvert)
        command.append(wxT(" -i"));
    command.append(wxT(" -c ") + tcCompression->GetValue());//compression
    command.append(wxT(" -x ") + tcMax->GetValue());        //height maximum
    command.append(wxT(" -n ") + tcMin->GetValue());        //height minimum

    command.append(wxT(" -o \"") + tcOutput->GetValue() + wxT("\""));     //output
    command.append(wxT(" -t \"") + tcTexture->GetValue() + wxT("\""));    //texture
    command.append(wxT(" -a \"") + tcHeight->GetValue() + wxT("\""));     //heightmap
    command.append(wxT(" -m \"") + tcMetal->GetValue() + wxT("\""));      //metalmap
    command.append(wxT(" -g \"") + tcGeovent->GetValue() + wxT("\""));    //geoventmap

    if(bFeatureEnable)
    {
        command.append(wxT(" -f \"") + tcFeature->GetValue() + wxT("\""));
        command.append(wxT(" -j \"") + tcFeatureList->GetValue() + wxT("\""));
    }
    if(bTypemapEnable)
    {
        command.append(wxT(" -y \"") + tcType->GetValue() + wxT("\""));
    }
    if(bOtherEnable)
    {
        command.append(wxT(" ") + tcOtherOptions->GetValue());
    }
    int iQuality = rbxQuality->GetSelection();
    if(iQuality == 0)
    {
        command.append(wxT(" -z \"nvdxt.exe -dxt1a -nmips 4 -quick -file\""));
    }
    else if(iQuality == 1)
    {
        command.append(wxT(" -q "));
    }
    else if(iQuality == 2)
    {
    }
    else if(iQuality == 3)
    {
        command.append(wxT(" -z \"nvdxt.exe -dxt1a -nmips 4 -Sinc -quality_highest -file\""));
    }
	//better use wxExecute family of functions, lets you capture output and do async ops, etc.
	system(command.mb_str());
}

void _mapconvTab::OnToggleLowpass(wxCommandEvent& event){
    bLowpass=!bLowpass;
}

void _mapconvTab::OnToggleInvert(wxCommandEvent& event){
    bInvert=!bInvert;
}

void _mapconvTab::OnToggleFeatureEnable(wxCommandEvent& event){
    if(bFeatureEnable == false)
    {
        btnFeature->Enable(true);
        tcFeature->Enable(true);
        btnFeatureList->Enable(true);
        tcFeatureList->Enable(true);
    }
    else
    {
        btnFeature->Enable(false);
        tcFeature->Enable(false);
        btnFeatureList->Enable(false);
        tcFeatureList->Enable(false);
    }
    bFeatureEnable = !bFeatureEnable;
}

void _mapconvTab::OnToggleTypemapEnable(wxCommandEvent& event){
    if(bTypemapEnable == false)
    {
        btnType->Enable(true);
        tcType->Enable(true);
    }
    else
    {
        btnType->Enable(false);
        tcType->Enable(false);
    }
    bTypemapEnable = !bTypemapEnable;
}

void _mapconvTab::OnToggleOtherEnable(wxCommandEvent& event){
    if(bOtherFirstTime == true)
    {
		tcOtherOptions->SetValue(wxEmptyString);
        bOtherFirstTime = false;
    }
    if(bOtherEnable == false)
    {
		tcOtherOptions->SetValue(wxEmptyString);
        tcOtherOptions->Enable(true);
    }
    else
    {
		tcOtherOptions->SetValue(_("Additional Options"));
        tcOtherOptions->Enable(false);
    }
    bOtherEnable = !bOtherEnable;
}

void _mapconvTab::reset(void){
    bLowpass = true;
    bInvert = true;
//    bFeatureEnable = false;
//    bTypemapEnable = false;
//    bOtherEnable = false;
//    bOtherFirstTime = true;
//    bTextureLoaded = false;

    cbLowpass->SetValue(bLowpass);
    cbInvert->SetValue(bInvert);
    btnFeature->Enable(bFeatureEnable);
    tcFeature->Enable(bFeatureEnable);
    btnFeatureList->Enable(bFeatureEnable);
    tcFeatureList->Enable(bFeatureEnable);
    btnType->Enable(bTypemapEnable);
    tcType->Enable(bTypemapEnable);
    cbOtherOptionsEnable->SetValue(bOtherEnable);
    tcOtherOptions->Enable(bOtherEnable);

    tcHeight->SetValue(wxT("heightmap.bmp"));
    tcTexture->SetValue(wxT("texture.bmp"));
    tcMetal->SetValue(wxT("metal.bmp"));
    tcFeature->SetValue(wxT("feature.bmp"));
    tcFeatureList->SetValue(wxT("featurelist.txt"));
    tcType->SetValue(wxT("typemap.bmp"));
    tcGeovent->SetValue(wxT("geovent.bmp"));
    tcOutput->SetValue(wxT("output.smf"));
    tcOtherOptions->SetValue(wxT(""));

//	sbmPreviewBig->SetBitmap( charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) ) );
}
