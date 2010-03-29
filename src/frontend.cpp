#include "wxwfrontend.h"

Frontend::Frontend(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 580)){
    bSaved = false;

    image = new wxImage(300,300);

    menubar = new wxMenuBar;
    mnFile = new wxMenu;
    mnSMD = new wxMenu;
    mnMapconv = new wxMenu;
    mnAbout = new wxMenu;

    mnFile->Append(IDMENU_NEW, wxT("&New"));
    mnFile->Append(IDMENU_OPEN, wxT("&Open"));
    mnFile->Append(IDMENU_SAVE, wxT("&Save"));
    mnFile->Append(IDMENU_SAVEAS, wxT("Save &As"));
    mnFile->AppendSeparator();
    mnFile->Append(wxID_EXIT, wxT("&Quit"));

    mnMapconv->Append(IDMENU_COMPILE, wxT("&Compile"));

    mnSMD->Append(IDMENU_SMDOPEN, wxT("&Open"));
    mnSMD->Append(IDMENU_SMDSAVE, wxT("&Save"));
    mnSMD->Append(IDMENU_SMDRESET, wxT("&Reset"));

    menubar->Append(mnFile, wxT("&File"));
    menubar->Append(mnMapconv, wxT("&Mapconv"));
    menubar->Append(mnSMD, wxT("&SMD"));

    SetMenuBar(menubar);

    notebook = new wxNotebook(this, IDNB_MAIN);
    mapconvTab = new _mapconvTab(notebook, -1);
    previewTab = new _previewTab(notebook, -1);
	smdTab = new _smdTab(notebook, -1);

	notebook->AddPage(mapconvTab, _T("MapConv"), true);
	notebook->AddPage(previewTab, _("Preview"), true);
    notebook->AddPage(smdTab, wxT("SMD"), true);
    notebook->SetSelection(0);

//Menu Options//
    Connect(IDMENU_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickNew));
    Connect(IDMENU_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickSaveProject));
    Connect(IDMENU_SAVEAS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickSaveProjectAs));
    Connect(IDMENU_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickLoadProject));

    Connect(IDMENU_COMPILE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickCompile));

    Connect(IDMENU_SMDOPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickOpenSMD));
    Connect(IDMENU_SMDSAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickSaveSMD));
    Connect(IDMENU_SMDRESET, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickResetSMD));

    Connect(IDBTN_SMD_SAVE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickSaveSMD));

//Propagated messages//
    Connect(IDBTN_HEIGHT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenHeight));
    Connect(IDBTN_TEXTURE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenTexture));
    Connect(IDBTN_METAL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenMetal));
    Connect(IDBTN_FEATURE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenFeature));
    Connect(IDBTN_TYPE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenType));

    Connect(IDTC_MAX_HEIGHT, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frontend::OnChangeMax));
    Connect(IDTC_MIN_HEIGHT, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frontend::OnChangeMin));

    Centre();
}

void Frontend::OnChangeMax(wxCommandEvent& event){
    previewTab->fWaterHeight = mapconvTab->calculateWaterHeight();
    //mapconvTab->tcTexture->SetValue( wxString::Format(wxT("%f"), previewTab->fWaterHeight));
}
void Frontend::OnChangeMin(wxCommandEvent& event){
    previewTab->fWaterHeight =  mapconvTab->calculateWaterHeight();
    //mapconvTab->tcTexture->SetValue( wxString::Format(wxT("%f"), previewTab->fWaterHeight));
}

void Frontend::OnClickNew(wxCommandEvent& event){
    wxFileDialog* newfiledialog = new wxFileDialog(this, wxT("Save Project"), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
    if(newfiledialog->ShowModal() == wxID_OK)
    {
        projectPath = newfiledialog->GetPath();
        sProjectName = newfiledialog->GetFilename();
        this->SetTitle(wxT("Mapconv Frontend - ") + sProjectName);
//        setDefaultsMapconv();
        smdTab->reset();

        SaveProject();
    }
    delete newfiledialog;
}

void Frontend::OnClickSaveProject(wxCommandEvent& event){
    if(!bSaved){
        wxFileDialog* SaveFileDialog = new wxFileDialog(this, wxT("Save Project As..."), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
        if (SaveFileDialog->ShowModal() == wxID_OK)
        {
            projectPath = SaveFileDialog->GetPath();
            SaveProject();
        }
        delete SaveFileDialog;
    }
    else
        SaveProject();
}

void Frontend::OnClickSaveProjectAs(wxCommandEvent& event){
    wxFileDialog* SaveFileDialog = new wxFileDialog(this, wxT("Save Project As..."), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
    if (SaveFileDialog->ShowModal() == wxID_OK)
    {
        projectPath = SaveFileDialog->GetPath();
        SaveProject();
    }
    delete SaveFileDialog;
}

void Frontend::SaveProject(void){
    wxFile file;

    file.Open(projectPath, wxFile::write);

    file.Write(wxT("heightmap=") + mapconvTab->tcHeight->GetValue() + wxT(";\n"));
    file.Write(wxT("texture=") + mapconvTab->tcTexture->GetValue() + wxT(";\n"));
    file.Write(wxT("metal=") + mapconvTab->tcMetal->GetValue() + wxT(";\n"));
    file.Write(wxT("enablefeaturemap="));
        if(mapconvTab->cbFeatureEnable->GetValue()) file.Write(wxT("true;\n"));
        else                            file.Write(wxT("false;\n"));
    file.Write(wxT("featuremap=") + mapconvTab->tcFeature->GetValue() + wxT(";\n"));
    file.Write(wxT("featurelist=") + mapconvTab->tcFeatureList->GetValue() + wxT(";\n"));
    file.Write(wxT("enabletypemap="));
        if(mapconvTab->cbTypeEnable->GetValue()) file.Write(wxT("true;\n"));
        else                         file.Write(wxT("false;\n"));
    file.Write(wxT("typemap=") + mapconvTab->tcType->GetValue() + wxT(";\n"));
    file.Write(wxT("geovent=") + mapconvTab->tcGeovent->GetValue() + wxT(";\n"));
    file.Write(wxT("additionaloptions=") + mapconvTab->tcOtherOptions->GetValue() + wxT(";\n"));
    file.Write(wxT("output=") + mapconvTab->tcOutput->GetValue() + wxT(";\n"));
    file.Write(wxT("maxheight=") + mapconvTab->tcMax->GetValue() + wxT(";\n"));
    file.Write(wxT("minheight=") + mapconvTab->tcMin->GetValue() + wxT(";\n"));
    file.Write(wxT("lowpass="));
        if(mapconvTab->cbLowpass->GetValue()) file.Write(wxT("true;\n"));
        else                      file.Write(wxT("false;\n"));
    file.Write(wxT("invert="));
        if(mapconvTab->cbInvert->GetValue()) file.Write(wxT("true;\n"));
        else                     file.Write(wxT("false;\n"));
    file.Write(wxT("quality=") + wxString::Format(wxT("%i"),mapconvTab->rbxQuality->GetSelection()) + wxT(";\n"));
    file.Write(wxT("compression=") + mapconvTab->tcCompression->GetValue() + wxT(";\n"));
    file.Write(wxT("rotatefeatures=") + mapconvTab->tcFeatureRotate->GetValue() + wxT(";\n"));
    file.Write(wxT("heightmaploaded="));
        if(mapconvTab->bHeightmapLoaded)    file.Write(wxT("true;\n"));
        else                    file.Write(wxT("false;\n"));
    file.Write(wxT("textureloaded="));
        if(mapconvTab->bTextureLoaded) file.Write(wxT("true;\n"));
        else               file.Write(wxT("false;\n"));
    file.Write(wxT("metalloaded="));
        if(mapconvTab->bMetalLoaded)   file.Write(wxT("true;\n"));
        else               file.Write(wxT("false;\n"));
    file.Write(wxT("featureloaded="));
        if(mapconvTab->bFeatureLoaded) file.Write(wxT("true;\n"));
        else               file.Write(wxT("false;\n"));
    file.Write(wxT("typemaploaded="));
        if(mapconvTab->bTypemapLoaded) file.Write(wxT("true;\n"));
        else               file.Write(wxT("false;\n"));

    file.Close();
    bSaved = true;
}

void Frontend::OnClickLoadProject(wxCommandEvent& event){
    wxTextFile *file;

    wxString str;
    wxString name;
    wxString value;

    int start, length;

    wxFileDialog *LoadFileDialog = new wxFileDialog(this);
    if (LoadFileDialog->ShowModal() == wxID_OK)
    {
        file = new wxTextFile(LoadFileDialog->GetPath());
        if(file->Open())
        {
            for ( str = file->GetFirstLine(); !file->Eof(); str = file->GetNextLine() )
            {
                start = 0;
                length = str.Find(wxT("="));
                name = str.Mid(start, length);

                start = str.Find(wxT("=")) + 1;
                length = str.Find(wxT(";")) - start;
                value = str.Mid(start, length);

                if(name == wxT("heightmap"))
                    mapconvTab->tcHeight->SetValue(value);
                else if(name == wxT("texture"))
                    mapconvTab->tcTexture->SetValue(value);
                else if(name == wxT("metal"))
                    mapconvTab->tcMetal->SetValue(value);
                else if(name == wxT("enablefeaturemap")){
                    if(value == wxT("true"))
                        mapconvTab->cbFeatureEnable->SetValue(true);
                    else
                        mapconvTab->cbFeatureEnable->SetValue(false);
                }
                else if(name == wxT("featuremap"))
                    mapconvTab->tcFeature->SetValue(value);
                else if(name == wxT("featurelist"))
                    mapconvTab->tcFeatureList->SetValue(value);
                else if(name == wxT("enabletypemap")){
                    if(value == wxT("true"))
                        mapconvTab->cbTypeEnable->SetValue(true);
                    else
                        mapconvTab->cbTypeEnable->SetValue(false);
                }
                else if(name == wxT("typemap"))
                    mapconvTab->tcType->SetValue(value);
                else if(name == wxT("geovent"))
                    mapconvTab->tcGeovent->SetValue(value);
                else if(name == wxT("additionaloptions"))
                    mapconvTab->tcOtherOptions->SetValue(value);
                else if(name == wxT("output"))
                    mapconvTab->tcOutput->SetValue(value);
                else if(name == wxT("maxheight"))
                    mapconvTab->tcMax->SetValue(value);
                else if(name == wxT("minheight"))
                    mapconvTab->tcMin->SetValue(value);
                else if(name == wxT("lowpass")){
                    if(value == wxT("true"))
                        mapconvTab->cbLowpass->SetValue(true);
                    else
                        mapconvTab->cbLowpass->SetValue(false);
                }
                else if(name == wxT("invert")){
                    if(value == wxT("true"))
                        mapconvTab->cbInvert->SetValue(true);
                    else
                        mapconvTab->cbInvert->SetValue(false);
                }
                else if(name == wxT("quality"))
                    mapconvTab->rbxQuality->SetSelection(wxAtoi(value));
                else if(name == wxT("compression"))
                    mapconvTab->tcCompression->SetValue(value);
                else if(name == wxT("rotatefeatures"))
                    mapconvTab->tcFeatureRotate->SetValue(value);
                else if(name == wxT("heightmaploaded")){
                    if(value == wxT("true")){
                        mapconvTab->bHeightmapLoaded=true;
                        path = mapconvTab->tcHeight->GetValue();
                        LoadImage(ID_HEIGHT);
                    }
                    else    mapconvTab->bHeightmapLoaded=false;
                }
                else if(name == wxT("textureloaded")){
                    if(value == wxT("true")){
                        mapconvTab->bTextureLoaded=true;
                        path = mapconvTab->tcTexture->GetValue();
                        LoadImage(ID_TEXTURE);
                    }
                    else    mapconvTab->bTextureLoaded=false;
                }
                else if(name == wxT("metalloaded")){
                    if(value == wxT("true")){
                        mapconvTab->bMetalLoaded=true;
                        path = mapconvTab->tcMetal->GetValue();
                        LoadImage(ID_METAL);
                    }
                    else    mapconvTab->bMetalLoaded=false;
                }
                else if(name == wxT("featureloaded")){
                    if(value == wxT("true")){
                        mapconvTab->bFeatureLoaded=true;
                        path = mapconvTab->tcFeature->GetValue();
                        LoadImage(ID_FEATURE);
                    }
                    else    mapconvTab->bFeatureLoaded=false;
                }

                else if(name == wxT("typemaploaded")){
                    if(value == wxT("true")){
                        mapconvTab->bTypemapLoaded=true;
                        path = mapconvTab->tcType->GetValue();
                        LoadImage(ID_TYPE);
                    }
                    else    mapconvTab->bTypemapLoaded=false;
                }
                else{}//error value not found
            }

            file->Close();
        }
    }
    delete LoadFileDialog;
    //bSaved = true;
}

void Frontend::OnClickCompile(wxCommandEvent& event){
    mapconvTab->Compile();
}

void Frontend::OnClickOpenSMD(wxCommandEvent& event){
    wxString str;
    wxString name;
    wxString value;
    int start, length;

    wxTextFile *file;
    wxFileDialog *loadSMDDialog = new wxFileDialog(this);

    if (loadSMDDialog->ShowModal() == wxID_OK)
    {
        file = new wxTextFile(loadSMDDialog->GetPath());
        if(file->Open())
        {
            for ( str = file->GetFirstLine(); !file->Eof(); str = file->GetNextLine() )
            {
                int startPosID = -1;
                str.MakeLower();

                if(str.Contains(wxT("[")) && str.Contains(wxT("]")))//team is the only important name between [], others seem to be for ease of reading
                {
                    str = str.After('[');
                    str = str.Before(']');
                    if(str == wxT("team0"))
                        startPosID = 0;
                    else if(str == wxT("team1"))
                        startPosID = 1;
                    else if(str == wxT("team2"))
                        startPosID = 2;
                    else if(str == wxT("team3"))
                        startPosID = 3;
                    else if(str == wxT("team4"))
                        startPosID = 4;
                    else if(str == wxT("team5"))
                        startPosID = 5;
                    else if(str == wxT("team6"))
                        startPosID = 6;
                    else if(str == wxT("team7"))
                        startPosID = 7;

                }
                if(str.Contains(wxT("=")))
                {
                    //!TODO
                    str.Trim(false);
                    str.Trim(true);

                    start = 0;
                    length = str.Find(wxT("="));
                    name = str.Mid(start, length);
                    name.Trim(true);

                    start = str.Find(wxT("=")) + 1;
                    length = str.Find(wxT(";")) - start;
                    value = str.Mid(start, length);
                    value.Trim(false);

                    if(name == wxT("description"))
                        smdTab->smdGeneralTab->tcDescription->SetValue(value);
                    else if(name == wxT("tidalstrength"))
                        smdTab->smdGeneralTab->tcTidalStrength->SetValue(value);
                    else if(name == wxT("gravity"))
                        smdTab->smdGeneralTab->tcGravity->SetValue(value);
                    else if(name == wxT("maxmetal"))
                        smdTab->smdGeneralTab->tcMaxMetal->SetValue(value);
                    else if(name == wxT("extractorradius"))
                        smdTab->smdGeneralTab->tcExtractorRadius->SetValue(value);
                    else if(name == wxT("maphardness"))
                        smdTab->smdGeneralTab->tcMapHardness->SetValue(value);
                    else if(name == wxT("maxheight"))
                        smdTab->smdGeneralTab->tcMaxHeight->SetValue(value);
                    else if(name == wxT("minheight"))
                        smdTab->smdGeneralTab->tcMinHeight->SetValue(value);
                    else if(name == wxT("minwind"))
                        smdTab->smdGeneralTab->tcMinWind->SetValue(value);
                    else if(name == wxT("maxwind"))
                        smdTab->smdGeneralTab->tcMaxWind->SetValue(value);
                    else if(name == wxT("fogcolor") || name == wxT("fogcolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdAtmosphereTab->colFog->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdAtmosphereTab->pnlFogColourDisplay->SetBackgroundColour(*smdTab->smdAtmosphereTab->colFog);
                        smdTab->smdAtmosphereTab->pnlFogColourDisplay->Refresh();
                    }
                    else if(name == wxT("fogstart"))
                        smdTab->smdAtmosphereTab->tcFogStart->SetValue(value);
                    else if(name == wxT("suncolor") || name == wxT("suncolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdAtmosphereTab->colSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdAtmosphereTab->pnlSunColourDisplay->SetBackgroundColour(*smdTab->smdAtmosphereTab->colSun);
                        smdTab->smdAtmosphereTab->pnlSunColourDisplay->Refresh();
                    }
                    else if(name == wxT("skycolor") || name == wxT("skycolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdAtmosphereTab->colSky->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdAtmosphereTab->pnlSkyColourDisplay->SetBackgroundColour(*smdTab->smdAtmosphereTab->colSky);
                        smdTab->smdAtmosphereTab->pnlSkyColourDisplay->Refresh();
                    }
                    else if(name == wxT("cloudcolor") || name == wxT("cloudcolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdAtmosphereTab->colCloud->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdAtmosphereTab->pnlCloudColourDisplay->SetBackgroundColour(*smdTab->smdAtmosphereTab->colCloud);
                        smdTab->smdAtmosphereTab->pnlCloudColourDisplay->Refresh();
                    }
                    else if(name == wxT("clouddensity"))
                        smdTab->smdAtmosphereTab->tcCloudDensity->SetValue(value);
                    else if(name == wxT("groundambientcolor") || name == wxT("groundambientcolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdAtmosphereTab->colGroundAmbient->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdAtmosphereTab->pnlGroundAmbientColourDisplay->SetBackgroundColour(*smdTab->smdAtmosphereTab->colGroundAmbient);
                        smdTab->smdAtmosphereTab->pnlGroundAmbientColourDisplay->Refresh();
                    }
                    else if(name == wxT("groundsuncolor") || name == wxT("groundsuncolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdAtmosphereTab->colGroundSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdAtmosphereTab->pnlGroundSunColourDisplay->SetBackgroundColour(*smdTab->smdAtmosphereTab->colGroundSun);
                        smdTab->smdAtmosphereTab->pnlGroundSunColourDisplay->Refresh();
                    }
                    else if(name == wxT("groundshadowdensity"))
                        smdTab->smdAtmosphereTab->tcUnitShadowDensity->SetValue(value);
                    else if(name == wxT("unitambientcolor") || name == wxT("unitambientcolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdAtmosphereTab->colUnitAmbient->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdAtmosphereTab->pnlUnitAmbientColourDisplay->SetBackgroundColour(*smdTab->smdAtmosphereTab->colUnitAmbient);
                        smdTab->smdAtmosphereTab->pnlUnitAmbientColourDisplay->Refresh();
                    }
                    else if(name == wxT("unitsuncolor") || name == wxT("unitsuncolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdAtmosphereTab->colUnitSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdAtmosphereTab->pnlUnitSunColourDisplay->SetBackgroundColour(*smdTab->smdAtmosphereTab->colUnitSun);
                        smdTab->smdAtmosphereTab->pnlUnitSunColourDisplay->Refresh();
                    }
                    else if(name == wxT("unitshadowdensity"))
                        smdTab->smdAtmosphereTab->tcUnitShadowDensity->SetValue(value);
                    else if(name == wxT("waterbasecolor") || name == wxT("waterbasecolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdWaterTab->colWaterBase->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdWaterTab->pnlWaterBaseColourDisplay->SetBackgroundColour(*smdTab->smdWaterTab->colWaterBase);
                        smdTab->smdWaterTab->pnlWaterBaseColourDisplay->Refresh();
                    }
                    else if(name == wxT("watermincolor") || name == wxT("watermincolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdWaterTab->colWaterMin->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdWaterTab->pnlWaterMinColourDisplay->SetBackgroundColour(*smdTab->smdWaterTab->colWaterMin);
                        smdTab->smdWaterTab->pnlWaterMinColourDisplay->Refresh();
                    }
                    else if(name == wxT("waterabsorbcolor") || name == wxT("waterabsorbcolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdWaterTab->colWaterAbsorb->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdWaterTab->pnlWaterAbsorbColourDisplay->SetBackgroundColour(*smdTab->smdWaterTab->colWaterAbsorb);
                        smdTab->smdWaterTab->pnlWaterAbsorbColourDisplay->Refresh();
                    }
                    else if(name == wxT("watersurfacecolor") || name == wxT("watersurfacecolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdWaterTab->colWaterSurface->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdWaterTab->pnlWaterSurfaceColourDisplay->SetBackgroundColour(*smdTab->smdWaterTab->colWaterSurface);
                        smdTab->smdWaterTab->pnlWaterSurfaceColourDisplay->Refresh();
                    }
                    else if(name == wxT("waterplanecolor") || name == wxT("waterplanecolour"))
                    {
                        int subLength;
                        float red, green, blue;

                        subLength = value.Find(wxT(" "));
                        red = wxAtof( value.Mid( 0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        subLength = value.Find(wxT(" "));
                        green = wxAtof( value.Mid(0, subLength));
                        value = value.Mid( subLength+1, value.Length());

                        blue = wxAtof( value );
                        smdTab->smdWaterTab->colWaterPlane->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                        smdTab->smdWaterTab->pnlWaterPlaneColourDisplay->SetBackgroundColour(*smdTab->smdWaterTab->colWaterPlane);
                        smdTab->smdWaterTab->pnlWaterPlaneColourDisplay->Refresh();
                    }
                    else if(name == wxT("sundir"))
                    {
    //                    int subLength;
    //
    //                    subLength = value.Find(wxT(" "));
    //                    smdTab->smdAtmosphereTab->tcSunDirX->SetValue( value.Mid( 0, subLength));
    //                    value = value.Mid( subLength+1, value.Length());
    //
    //                    subLength = value.Find(wxT(" "));
    //                    smdTab->smdAtmosphereTab->tcSunDirY->SetValue( value.Mid(0, subLength));
    //                    value = value.Mid( subLength+1, value.Length());
    //
    //                    smdTab->smdAtmosphereTab->tcSunDirZ->SetValue( value );
                    }
                    else if(name == wxT("startposx"))
                    {
                        switch(startPosID)
                        {
                            case 0:
                                smdTab->smdGeneralTab->tcTeam1X->SetValue(value);
                                break;
                            case 1:
                                smdTab->smdGeneralTab->tcTeam2X->SetValue(value);
                                break;
                            case 2:
                                smdTab->smdGeneralTab->tcTeam3X->SetValue(value);
                                break;
                            case 3:
                                smdTab->smdGeneralTab->tcTeam4X->SetValue(value);
                                break;
                            case 4:
                                smdTab->smdGeneralTab->tcTeam5X->SetValue(value);
                                break;
                            case 5:
                                smdTab->smdGeneralTab->tcTeam6X->SetValue(value);
                                break;
                            case 6:
                                smdTab->smdGeneralTab->tcTeam7X->SetValue(value);
                                break;
                            case 7:
                                smdTab->smdGeneralTab->tcTeam8X->SetValue(value);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(name == wxT("startposz"))
                    {
                        switch(startPosID)
                        {
                            case 0:
                                smdTab->smdGeneralTab->tcTeam1Y->SetValue(value);
                                break;
                            case 1:
                                smdTab->smdGeneralTab->tcTeam2Y->SetValue(value);
                                break;
                            case 2:
                                smdTab->smdGeneralTab->tcTeam3Y->SetValue(value);
                                break;
                            case 3:
                                smdTab->smdGeneralTab->tcTeam4Y->SetValue(value);
                                break;
                            case 4:
                                smdTab->smdGeneralTab->tcTeam5Y->SetValue(value);
                                break;
                            case 5:
                                smdTab->smdGeneralTab->tcTeam6Y->SetValue(value);
                                break;
                            case 6:
                                smdTab->smdGeneralTab->tcTeam7Y->SetValue(value);
                                break;
                            case 7:
                                smdTab->smdGeneralTab->tcTeam8Y->SetValue(value);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
        file->Close();
    }
    delete loadSMDDialog;
    //bSaved = true;
}

void Frontend::OnClickResetSMD(wxCommandEvent& event){
    smdTab->reset();
}

void Frontend::OnClickSaveSMD(wxCommandEvent& event){
    wxString sBuffer;
    wxFile file;
    int iTeamCount;
//A large number of variables are read as char's but need to be stored as floats between 1 and 0

    wxString sSunRed = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colSun->Red()/255);
    wxString sSunGreen = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colSun->Green()/255);
    wxString sSunBlue = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colSun->Blue()/255);
    wxString sSkyRed = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colSky->Red()/255);
    wxString sSkyGreen = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colSky->Green()/255);
    wxString sSkyBlue = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colSky->Blue()/255);
    wxString sCloudRed = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colCloud->Red()/255);
    wxString sCloudGreen = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colCloud->Green()/255);
    wxString sCloudBlue = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colCloud->Blue()/255);
    wxString sFogRed = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colFog->Red()/255);
    wxString sFogGreen = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colFog->Green()/255);
    wxString sFogBlue = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colFog->Blue()/255);

    wxString sGroundAmbientRed = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colGroundAmbient->Red()/255);
    wxString sGroundAmbientGreen = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colGroundAmbient->Green()/255);
    wxString sGroundAmbientBlue = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colGroundAmbient->Blue()/255);
    wxString sGroundSunRed = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colGroundSun->Red()/255);
    wxString sGroundSunGreen = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colGroundSun->Green()/255);
    wxString sGroundSunBlue = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colGroundSun->Blue()/255);
    wxString sUnitSunRed = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colUnitSun->Red()/255);
    wxString sUnitSunGreen = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colUnitSun->Green()/255);
    wxString sUnitSunBlue = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colUnitSun->Blue()/255);
    wxString sUnitAmbientRed = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colUnitAmbient->Red()/255);
    wxString sUnitAmbientGreen = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colUnitAmbient->Green()/255);
    wxString sUnitAmbientBlue = wxString::Format(wxT("%f"), (float)smdTab->smdAtmosphereTab->colUnitAmbient->Blue()/255);

    wxString sWaterBaseRed = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterBase->Red()/255);
    wxString sWaterBaseGreen = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterBase->Green()/255);
    wxString sWaterBaseBlue = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterBase->Blue()/255);
    wxString sWaterMinRed = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterMin->Red()/255);
    wxString sWaterMinGreen = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterMin->Green()/255);
    wxString sWaterMinBlue = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterMin->Blue()/255);
    wxString sWaterAbsorbRed = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterAbsorb->Red()/255);
    wxString sWaterAbsorbGreen = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterAbsorb->Green()/255);
    wxString sWaterAbsorbBlue = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterAbsorb->Blue()/255);
    wxString sWaterPlaneRed = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterPlane->Red()/255);
    wxString sWaterPlaneGreen = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterPlane->Green()/255);
    wxString sWaterPlaneBlue = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterPlane->Blue()/255);
    wxString sWaterSurfaceRed = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterSurface->Red()/255);
    wxString sWaterSurfaceGreen = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterSurface->Green()/255);
    wxString sWaterSurfaceBlue = wxString::Format(wxT("%f"), (float)smdTab->smdWaterTab->colWaterSurface->Blue()/255);

    sFogRed.Truncate(5);
    sFogGreen.Truncate(5);
    sFogBlue.Truncate(5);
    sSunRed.Truncate(5);
    sSunGreen.Truncate(5);
    sSunBlue.Truncate(5);
    sSkyRed.Truncate(5);
    sSkyGreen.Truncate(5);
    sSkyBlue.Truncate(5);
    sCloudRed.Truncate(5);
    sCloudGreen.Truncate(5);
    sCloudBlue.Truncate(5);

    sGroundAmbientRed.Truncate(5);
    sGroundAmbientGreen.Truncate(5);
    sGroundAmbientBlue.Truncate(5);
    sGroundSunRed.Truncate(5);
    sGroundSunGreen.Truncate(5);
    sGroundSunBlue.Truncate(5);
    sUnitAmbientRed.Truncate(5);
    sUnitAmbientGreen.Truncate(5);
    sUnitAmbientBlue.Truncate(5);
    sUnitSunRed.Truncate(5);
    sUnitSunGreen.Truncate(5);
    sUnitSunBlue.Truncate(5);

    sWaterBaseRed.Truncate(5);
    sWaterBaseGreen.Truncate(5);
    sWaterBaseBlue.Truncate(5);
    sWaterMinRed.Truncate(5);
    sWaterMinGreen.Truncate(5);
    sWaterMinBlue.Truncate(5);
    sWaterAbsorbRed.Truncate(6);
    sWaterAbsorbGreen.Truncate(6);
    sWaterAbsorbBlue.Truncate(6);
    sWaterPlaneRed.Truncate(6);
    sWaterPlaneGreen.Truncate(6);
    sWaterPlaneBlue.Truncate(6);
    sWaterSurfaceRed.Truncate(6);
    sWaterSurfaceGreen.Truncate(6);
    sWaterSurfaceBlue.Truncate(6);

    file.Open(wxT("map.smd"), wxFile::write);
    file.Write(wxT("[MAP]\n{\n"));
        file.Write(wxT("\tDescription=") + smdTab->smdGeneralTab->tcDescription->GetValue() + wxT(";\n"));
        file.Write(wxT("\tTidalStrength=") + smdTab->smdGeneralTab->tcTidalStrength->GetValue() + wxT(";\n"));
        file.Write(wxT("\tGravity=") + smdTab->smdGeneralTab->tcGravity->GetValue() + wxT(";\n"));
        file.Write(wxT("\tMaxMetal=") + smdTab->smdGeneralTab->tcMaxMetal->GetValue() + wxT(";\n"));
        file.Write(wxT("\tExtractorRadius=") + smdTab->smdGeneralTab->tcExtractorRadius->GetValue() + wxT(";\n"));
        file.Write(wxT("\tMapHardness=") + smdTab->smdGeneralTab->tcMapHardness->GetValue() + wxT(";\n"));
        file.Write(wxT("\t[SMF]\n\t{\n"));
            file.Write(wxT("\t\tminheight = ") + smdTab->smdGeneralTab->tcMinHeight->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tmaxheight = ") + smdTab->smdGeneralTab->tcMaxHeight->GetValue() + wxT(";\n"));
        file.Write(wxT("\t}\n\t[ATMOSPHERE]\n\t{\n"));
            file.Write(wxT("\t\tFogColour=") + sFogRed + wxT(" ") + sFogGreen + wxT(" ") + sFogBlue + wxT(";\n"));
            file.Write(wxT("\t\tFogStart=") + smdTab->smdAtmosphereTab->tcFogStart->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tSunColour=") + sSunRed + wxT(" ") + sSunGreen + wxT(" ") + sSunBlue + wxT(";\n"));
            file.Write(wxT("\t\tSkyColour=") + sSkyRed + wxT(" ") + sSkyGreen + wxT(" ") + sSkyBlue + wxT(";\n"));
            file.Write(wxT("\t\tCloudColour=") + sCloudRed + wxT(" ") + sCloudGreen + wxT(" ") + sCloudBlue + wxT(";\n"));
            file.Write(wxT("\t\tCloudDensity=") + smdTab->smdAtmosphereTab->tcCloudDensity->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tMinWind=") + smdTab->smdGeneralTab->tcMinWind->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tMaxWind=") + smdTab->smdGeneralTab->tcMaxWind->GetValue() + wxT(";\n"));
        file.Write(wxT("\t}\n\t[LIGHT]\n\t{\n"));
            file.Write(wxT("\t\tSunDir=1 2 0;\n"));
//            file.Write(wxT("\t\tSunDir=") + tcSunDirX->GetValue() + wxT(" ") + tcSunDirY->GetValue() + wxT(" ") + tcSunDirZ->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tGroundAmbientColour=") + sGroundAmbientRed + wxT(" ") + sGroundAmbientGreen + wxT(" ") + sGroundAmbientBlue + wxT(";\n"));
            file.Write(wxT("\t\tGroundSunColour=") + sGroundSunRed + wxT(" ") + sGroundSunGreen + wxT(" ") + sGroundSunBlue + wxT(";\n"));
            file.Write(wxT("\t\tGroundShadowDensity=") + smdTab->smdAtmosphereTab->tcGroundShadowDensity->GetValue() +wxT(";\n"));
            file.Write(wxT("\t\tUnitAmbientColour=") + sUnitAmbientRed + wxT(" ") + sUnitAmbientGreen + wxT(" ") + sUnitAmbientBlue + wxT(";\n"));
            file.Write(wxT("\t\tUnitSunColour=") + sUnitSunRed + wxT(" ") + sUnitSunGreen + wxT(" ") + sUnitSunBlue + wxT(";\n"));
            file.Write(wxT("\t\tUnitShadowDensity=") + smdTab->smdAtmosphereTab->tcUnitShadowDensity->GetValue() +wxT(";\n"));
        file.Write(wxT("\t}\n\t[WATER]\n\t{\n"));
            file.Write(wxT("\t\tWaterBaseColour=") + sWaterBaseRed + wxT(" ") + sWaterBaseGreen + wxT(" ") + sWaterBaseBlue + wxT(";\n"));
            file.Write(wxT("\t\tWaterMinColour=") + sWaterMinRed + wxT(" ") + sWaterMinGreen + wxT(" ") + sWaterMinBlue + wxT(";\n"));
            file.Write(wxT("\t\tWaterAbsorbColour=") + sWaterAbsorbRed + wxT(" ") + sWaterAbsorbGreen + wxT(" ") + sWaterAbsorbBlue + wxT(";\n"));
            file.Write(wxT("\t\tWaterPlaneColour=") + sWaterPlaneRed + wxT(" ") + sWaterPlaneGreen + wxT(" ") + sWaterPlaneBlue + wxT(";\n"));
            file.Write(wxT("\t\tWaterSurfaceColour=") + sWaterSurfaceRed + wxT(" ") + sWaterSurfaceGreen + wxT(" ") + sWaterSurfaceBlue + wxT(";\n"));
        file.Write(wxT("\t}\n"));
        iTeamCount = wxAtoi(smdTab->smdGeneralTab->tcTeamCount->GetValue());
        switch(iTeamCount){
            case 8:
                file.Write(wxT("\t[TEAM7]\n\t{\n\t\tStartPosX=") + smdTab->smdGeneralTab->tcTeam8X->GetValue() + wxT(";\n\t\tStartPosZ=") + smdTab->smdGeneralTab->tcTeam8Y->GetValue() + wxT(";\n\t}\n"));
            case 7:
                file.Write(wxT("\t[TEAM6]\n\t{\n\t\tStartPosX=") + smdTab->smdGeneralTab->tcTeam7X->GetValue() + wxT(";\n\t\tStartPosZ=") + smdTab->smdGeneralTab->tcTeam7Y->GetValue() + wxT(";\n\t}\n"));
            case 6:
                file.Write(wxT("\t[TEAM5]\n\t{\n\t\tStartPosX=") + smdTab->smdGeneralTab->tcTeam6X->GetValue() + wxT(";\n\t\tStartPosZ=") + smdTab->smdGeneralTab->tcTeam6Y->GetValue() + wxT(";\n\t}\n"));
            case 5:
                file.Write(wxT("\t[TEAM4]\n\t{\n\t\tStartPosX=") + smdTab->smdGeneralTab->tcTeam5X->GetValue() + wxT(";\n\t\tStartPosZ=") + smdTab->smdGeneralTab->tcTeam5Y->GetValue() + wxT(";\n\t}\n"));
            case 4:
                file.Write(wxT("\t[TEAM3]\n\t{\n\t\tStartPosX=") + smdTab->smdGeneralTab->tcTeam4X->GetValue() + wxT(";\n\t\tStartPosZ=") + smdTab->smdGeneralTab->tcTeam4Y->GetValue() + wxT(";\n\t}\n"));
            case 3:
                file.Write(wxT("\t[TEAM2]\n\t{\n\t\tStartPosX=") + smdTab->smdGeneralTab->tcTeam3X->GetValue() + wxT(";\n\t\tStartPosZ=") + smdTab->smdGeneralTab->tcTeam3Y->GetValue() + wxT(";\n\t}\n"));
            case 2:
                file.Write(wxT("\t[TEAM1]\n\t{\n\t\tStartPosX=") + smdTab->smdGeneralTab->tcTeam2X->GetValue() + wxT(";\n\t\tStartPosZ=") + smdTab->smdGeneralTab->tcTeam2Y->GetValue() + wxT(";\n\t}\n"));
                file.Write(wxT("\t[TEAM0]\n\t{\n\t\tStartPosX=") + smdTab->smdGeneralTab->tcTeam1X->GetValue() + wxT(";\n\t\tStartPosZ=") + smdTab->smdGeneralTab->tcTeam1Y->GetValue() + wxT(";\n\t}\n"));
        }
        file.Write(wxT("\n}"));

    file.Close();
}

void Frontend::LoadImage(int type){
    int scale;
    image = new wxImage;

    path.MakeLower();
    if(path.find(wxT(".bmp"), 0)!=wxNOT_FOUND){
        image->LoadFile(path, wxBITMAP_TYPE_BMP, -1);
    }
    else if(path.find(wxT(".jpg"), 0)!=wxNOT_FOUND || path.find(wxT(".jpeg"), 0)!=wxNOT_FOUND){
        image->LoadFile(path, wxBITMAP_TYPE_JPEG, -1);
    }
    else if(path.find(wxT(".png"), 0)!=wxNOT_FOUND){
        image->LoadFile(path, wxBITMAP_TYPE_PNG, -1);
    }
    else if(path.find(wxT(".tga"), 0)!=wxNOT_FOUND){
        image->LoadFile(path, wxBITMAP_TYPE_TGA, -1);
    }
    else{
        //error not a supported file type
    }

    int width = image->GetWidth();
    int height = image->GetHeight();

    if(width > height){
        scale=width/height;
        image->Rescale(440, 440/scale, wxIMAGE_QUALITY_HIGH);
    }
    else if(height > width){
        scale=height/width;
        image->Rescale(440/scale, 440, wxIMAGE_QUALITY_HIGH);
    }
    else{
        image->Rescale(440, 440, wxIMAGE_QUALITY_HIGH);
        scale=1;
    }

    previewTab->LoadPreviewImage(type, image);
    if(type == ID_TEXTURE){
        image->Rescale(128, 128, wxIMAGE_QUALITY_HIGH);
        mapconvTab->sbmPreview->SetBitmap(wxBitmap(*image, -1));
    }

    delete image;
}

void Frontend::OnOpenHeight(wxCommandEvent& event){
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        mapconvTab->tcHeight->SetValue(path);
        LoadImage(ID_HEIGHT);
        mapconvTab->bHeightmapLoaded = true;
    }
}

void Frontend::OnOpenTexture(wxCommandEvent& event){
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        mapconvTab->tcTexture->SetValue(path);
        LoadImage(ID_TEXTURE);
        mapconvTab->bTextureLoaded = true;
    }

}

void Frontend::OnOpenMetal(wxCommandEvent& event){
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        mapconvTab->tcMetal->SetValue(path);
        LoadImage(ID_METAL);
        mapconvTab->bMetalLoaded = true;
    }
}

void Frontend::OnOpenFeature(wxCommandEvent& event){
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        mapconvTab->tcFeature->SetValue(path);
        LoadImage(ID_FEATURE);
        mapconvTab->bFeatureLoaded = true;
    }
}

void Frontend::OnOpenType(wxCommandEvent& event){
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        mapconvTab->tcType->SetValue(path);
        LoadImage(ID_TYPE);
        mapconvTab->bTypemapLoaded = true;
    }
}
