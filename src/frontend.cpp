#include "wxwfrontend.h"

Frontend::Frontend(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 600))
{

    bSaved = false;

    image = new wxImage(300,300);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Menu bar//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    menubar = new wxMenuBar;
    mnFile = new wxMenu;
    mnAbout = new wxMenu;

    mnFile->Append(IDMENU_NEW, wxT("&New"));
    mnFile->Append(IDMENU_OPEN, wxT("&Open"));
    mnFile->Append(IDMENU_SAVE, wxT("&Save"));
    mnFile->Append(IDMENU_SAVEAS, wxT("Save &As"));
    mnFile->AppendSeparator();
    mnFile->Append(wxID_EXIT, wxT("&Quit"));

    menubar->Append(mnFile, wxT("&File"));
    SetMenuBar(menubar);


    notebook = new wxNotebook(this, IDNB_MAIN);
    mapconvTab = new _mapconvTab(notebook, -1);
    previewTab = new _previewTab(notebook, -1);
	smdTab = new _smdTab(notebook, -1);
    nbSMD = new wxNotebook(smdTab, wxID_ANY);


	notebook->AddPage(mapconvTab, _T("MapConv"), true);
	notebook->AddPage(previewTab, _("Preview"), true);
    notebook->AddPage(smdTab, wxT("SMD"), true);


//Mouse//
    Connect(wxID_ANY, wxEVT_LEFT_DOWN, wxCommandEventHandler(Frontend::OnMouseEvent));
//Menu Options//
    Connect(IDMENU_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickNew));
    Connect(IDMENU_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickSaveProject));
    Connect(IDMENU_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickLoadProject));

    Connect(IDBTN_SMD_SAVE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickSMDSave));

    Centre();
}

void Frontend::OnClickNew(wxCommandEvent& event){
    wxFileDialog* newfiledialog = new wxFileDialog(this, wxT("Save Project"), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
    if(newfiledialog->ShowModal() == wxID_OK)
    {
        projectPath = newfiledialog->GetPath();
        sProjectName = newfiledialog->GetFilename();
        this->SetTitle(wxT("Mapconv Frontend - ") + sProjectName);
//        setDefaultsMapconv();
        setDefaultsSMD();

        SaveProject();
    }
    delete newfiledialog;
}




void Frontend::setDefaultsSMD(void){
////Atmospheric Options//
//    colSun->Set(255, 190, 20);
//    colSky->Set(20, 20, 240);
//    colCloud->Set(150, 150, 150);
//    colFog->Set(100, 100, 100);
////Light Options//
//    colGroundAmbient->Set(127, 127, 127);
//    colGroundSun->Set(127, 127, 127);
//    colUnitAmbient->Set(127, 127, 127);
//    colUnitSun->Set(127, 127, 127);
////Water Options//
//    colWaterBase->Set(100, 150, 200);
//    colWaterMin->Set(10, 10, 30);
//    colWaterAbsorb->Set(4, 4, 2);
}


void Frontend::OnClickSaveProject(wxCommandEvent& event)
{
    if(!bSaved)
    {
        wxFileDialog* saveAsFileDialog = new wxFileDialog(this, wxT("Save Project As..."), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
        if (openFileDialog->ShowModal() == wxID_OK)
        {
            projectPath = openFileDialog->GetPath();
            SaveProject();
        }
        delete saveAsFileDialog;
    }
    else
        SaveProject();
}

void Frontend::OnClickSaveProjectAs(wxCommandEvent& event)
{
    wxFileDialog* saveAsFileDialog = new wxFileDialog(this, wxT("Save Project As..."), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        projectPath = openFileDialog->GetPath();
        SaveProject();
    }
    delete saveAsFileDialog;
}

void Frontend::SaveProject(void)
{
//    wxFile file;
//
//    file.Open(projectPath, wxFile::write);
//
//    file.Write(wxT("heightmap=") + tcHeight->GetValue() + wxT(";\n"));
//    file.Write(wxT("texture=") + tcTexture->GetValue() + wxT(";\n"));
//    file.Write(wxT("metal=") + tcMetal->GetValue() + wxT(";\n"));
//    file.Write(wxT("enablefeaturemap="));
//        if(cbFeatureEnable->GetValue()) file.Write(wxT("true;\n"));
//        else                            file.Write(wxT("false;\n"));
//    file.Write(wxT("featuremap=") + tcFeature->GetValue() + wxT(";\n"));
//    file.Write(wxT("featurelist=") + tcFeatureList->GetValue() + wxT(";\n"));
//    file.Write(wxT("enabletypemap="));
//        if(cbTypeEnable->GetValue()) file.Write(wxT("true;\n"));
//        else                         file.Write(wxT("false;\n"));
//    file.Write(wxT("typemap=") + tcType->GetValue() + wxT(";\n"));
//    file.Write(wxT("geovent=") + tcGeovent->GetValue() + wxT(";\n"));
//    file.Write(wxT("additionaloptions=") + tcOtherOptions->GetValue() + wxT(";\n"));
//    file.Write(wxT("output=") + tcOutput->GetValue() + wxT(";\n"));
//    file.Write(wxT("maxheight=") + tcMax->GetValue() + wxT(";\n"));
//    file.Write(wxT("minheight=") + tcMin->GetValue() + wxT(";\n"));
//    file.Write(wxT("lowpass="));
//        if(cbLowpass->GetValue()) file.Write(wxT("true;\n"));
//        else                      file.Write(wxT("false;\n"));
//    file.Write(wxT("invert="));
//        if(cbInvert->GetValue()) file.Write(wxT("true;\n"));
//        else                     file.Write(wxT("false;\n"));
//    file.Write(wxT("quality=") + wxString::Format(wxT("%i"),rbxQuality->GetSelection()) + wxT(";\n"));
//    file.Write(wxT("compression=") + tcCompression->GetValue() + wxT(";\n"));
//    file.Write(wxT("rotatefeatures=") + tcFeatureRotate->GetValue() + wxT(";\n"));
//    file.Write(wxT("heightmaploaded="));
//        if(bHeightmapLoaded)    file.Write(wxT("true;\n"));
//        else                    file.Write(wxT("false;\n"));
//    file.Write(wxT("textureloaded="));
//        if(bTextureLoaded) file.Write(wxT("true;\n"));
//        else               file.Write(wxT("false;\n"));
//    file.Write(wxT("metalloaded="));
//        if(bMetalLoaded)   file.Write(wxT("true;\n"));
//        else               file.Write(wxT("false;\n"));
//    file.Write(wxT("featureloaded="));
//        if(bFeatureLoaded) file.Write(wxT("true;\n"));
//        else               file.Write(wxT("false;\n"));
//    file.Write(wxT("typemaploaded="));
//        if(bTypemapLoaded) file.Write(wxT("true;\n"));
//        else               file.Write(wxT("false;\n"));
//
//    file.Close();
//    bSaved = true;
}

void Frontend::OnClickLoadProject(wxCommandEvent& event)
{
//    wxTextFile *file;
//
//    wxString str;
//    wxString name;
//    wxString value;
//
//    int start, length;
//
//    wxFileDialog *loadFileDialog = new wxFileDialog(this);
//    if (openFileDialog->ShowModal() == wxID_OK)
//    {
//        file = new wxTextFile(openFileDialog->GetPath());
//        if(file->Open())
//        {
//            for ( str = file->GetFirstLine(); !file->Eof(); str = file->GetNextLine() )
//            {
//                start = 0;
//                length = str.Find(wxT("="));
//                name = str.Mid(start, length);
//
//                start = str.Find(wxT("=")) + 1;
//                length = str.Find(wxT(";")) - start;
//                value = str.Mid(start, length);
//
//                if(name == wxT("heightmap"))
//                    tcHeight->SetValue(value);
//                else if(name == wxT("texture"))
//                    tcTexture->SetValue(value);
//                else if(name == wxT("metal"))
//                    tcMetal->SetValue(value);
//                else if(name == wxT("enablefeaturemap")){
//                    if(value == wxT("true"))
//                        cbFeatureEnable->SetValue(true);
//                    else
//                        cbFeatureEnable->SetValue(false);
//                }
//                else if(name == wxT("featuremap"))
//                    tcFeature->SetValue(value);
//                else if(name == wxT("featurelist"))
//                    tcFeatureList->SetValue(value);
//                else if(name == wxT("enabletypemap")){
//                    if(value == wxT("true"))
//                        cbTypeEnable->SetValue(true);
//                    else
//                        cbTypeEnable->SetValue(false);
//                }
//                else if(name == wxT("typemap"))
//                    tcType->SetValue(value);
//                else if(name == wxT("geovent"))
//                    tcGeovent->SetValue(value);
//                else if(name == wxT("additionaloptions"))
//                    tcOtherOptions->SetValue(value);
//                else if(name == wxT("output"))
//                    tcOutput->SetValue(value);
//                else if(name == wxT("maxheight"))
//                    tcMax->SetValue(value);
//                else if(name == wxT("minheight"))
//                    tcMin->SetValue(value);
//                else if(name == wxT("lowpass")){
//                    if(value == wxT("true"))
//                        cbLowpass->SetValue(true);
//                    else
//                        cbLowpass->SetValue(false);
//                }
//                else if(name == wxT("invert")){
//                    if(value == wxT("true"))
//                        cbInvert->SetValue(true);
//                    else
//                        cbInvert->SetValue(false);
//                }
//                else if(name == wxT("quality"))
//                    rbxQuality->SetSelection(wxAtoi(value));
//                else if(name == wxT("compression"))
//                    tcCompression->SetValue(value);
//                else if(name == wxT("rotatefeatures"))
//                    tcFeatureRotate->SetValue(value);
//                else if(name == wxT("heightmaploaded")){
//                    if(value == wxT("true")){
////                        bHeightmapLoaded=true;
//                        path = tcHeight->GetValue();
//                        LoadImage(ID_HEIGHT);
//                    }
////                    else    bHeightmapLoaded=false;
//                }
//                else if(name == wxT("textureloaded")){
//                    if(value == wxT("true")){
////                        bTextureLoaded=true;
//                        path = tcTexture->GetValue();
//                        LoadImage(ID_TEXTURE);
//                    }
////                    else    bTextureLoaded=false;
//                }
//                else if(name == wxT("metalloaded")){
//                    if(value == wxT("true")){
////                        bMetalLoaded=true;
//                        path = tcMetal->GetValue();
//                        LoadImage(ID_METAL);
//                    }
////                    else    bMetalLoaded=false;
//                }
//                else if(name == wxT("featureloaded")){
//                    if(value == wxT("true")){
////                        bFeatureLoaded=true;
//                        path = tcFeature->GetValue();
//                        LoadImage(ID_FEATURE);
//                    }
////                    else    bFeatureLoaded=false;
//                }
//
//                else if(name == wxT("typemaploaded")){
//                    if(value == wxT("true")){
////                        bTypemapLoaded=true;
//                        path = tcType->GetValue();
//                        LoadImage(ID_TYPE);
//                    }
////                    else    bTypemapLoaded=false;
//                }
//                else{}//error value not found
//            }
//
//            file->Close();
//        }
//    }
//    delete loadFileDialog;
//    bSaved = true;
}


void Frontend::LoadImage(int type)
{
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
//    if(type == ID_TEXTURE){
//        image->Rescale(128, 128, wxIMAGE_QUALITY_HIGH);
//        sbmPreview->SetBitmap(wxBitmap(*image, -1));
//    }

    delete image;
}

void Frontend::OnMouseEvent(wxCommandEvent& event)
{
//    wxRect rectSunDir = pnlSunDirection->GetRect();
//    if(rectSunDir.Contains(event.m_x, event.m_y))
//        tcHeight->SetValue(wxT("contained"));
}

void Frontend::OpenSMD(void)
{
//    wxString str;
//    wxString name;
//    wxString value;
//    int start, length;
//
//    wxTextFile *file;
//    wxFileDialog *loadSMDDialog = new wxFileDialog(this);
//
//    if (loadSMDDialog->ShowModal() == wxID_OK)
//    {
//        file = new wxTextFile(loadSMDDialog->GetPath());
//
//        for (str = file->GetFirstLine(); !file->Eof(); str = file->GetNextLine())
//        {
//            int startPosID = -1;
//            str.MakeLower();
//
//            if(str.Contains(wxT("[")) && str.Contains(wxT("]")))
//            {
//                str = str.After('[');
//                str = str.Before(']');
//                if(str == wxT("team0"))
//                    startPosID = 0;
//                else if(str == wxT("team1"))
//                    startPosID = 1;
//                else if(str == wxT("team2"))
//                    startPosID = 2;
//                else if(str == wxT("team3"))
//                    startPosID = 3;
//                else if(str == wxT("team4"))
//                    startPosID = 4;
//                else if(str == wxT("team5"))
//                    startPosID = 5;
//                else if(str == wxT("team6"))
//                    startPosID = 6;
//                else if(str == wxT("team7"))
//                    startPosID = 7;
//
//            }
//            if(str.Contains(wxT("=")))
//            {
//				//!TODO
////                str = str.After(RXwhite);
////                str = str.Before(RXwhite);
//                start = 0;
//                length = str.Find(wxT("="));
//                name = str.Mid(start, length);
//
//                start = str.Find(wxT("=")) + 1;
//                length = str.Find(wxT(";")) - start;
//                value = str.Mid(start, length);
////
////                if(name == wxT("description"))
////                    tcDescription->SetValue(value);
////                else if(name == wxT("tidalstrenght"))
////                    tcTidalStrength->SetValue(value);
////                else if(name == wxT("gravity"))
////                    tcGravity->SetValue(value);
////                else if(name == wxT("maxmetal"))
////                    tcMaxMetal->SetValue(value);
////                else if(name == wxT("extractorradius"))
////                    tcExtractorRadius->SetValue(value);
////                else if(name == wxT("maphardness"))
////                    tcMapHardness->SetValue(value);
////                else if(name == wxT("maxheight"))
////                    tcMaxHeight->SetValue(value);
////                else if(name == wxT("minheight"))
////                    tcMinHeight->SetValue(value);
////                else
//                if(name == wxT("fogcolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colFog->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlFogColourDisplay->SetBackgroundColour(*colFog);
//                }
//                else if(name == wxT("fogstart"))
//                    tcFogStart->SetValue(value);
//                else if(name == wxT("suncolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlSunColourDisplay->SetBackgroundColour(*colSun);
//                }
//                else if(name == wxT("skycolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colSky->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlSkyColourDisplay->SetBackgroundColour(*colSky);
//                }
//                else if(name == wxT("cloudcolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colCloud->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlCloudColourDisplay->SetBackgroundColour(*colCloud);
//                }
//                else if(name == wxT("clouddensity"))
//                    tcCloudDensity->SetValue(value);
//                else if(name == wxT("minwind"))
//                    tcMinWind->SetValue(value);
//                else if(name == wxT("maxwind"))
//                    tcMaxWind->SetValue(value);
//                else if(name == wxT("sundir"))
//                {
//                    int subLength;
//
//                    subLength = value.Find(wxT(" "));
//                    tcSunDirX->SetValue( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    tcSunDirY->SetValue( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    tcSunDirZ->SetValue( value );
//                }
//                else if(name == wxT("groundambientcolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colGroundAmbient->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlGroundAmbientColourDisplay->SetBackgroundColour(*colGroundAmbient);
//                }
//                else if(name == wxT("groundsuncolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colGroundSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlGroundSunColourDisplay->SetBackgroundColour(*colGroundSun);
//                }
//                else if(name == wxT("groundshadowdensity"))
//                    tcUnitShadowDensity->SetValue(value);
//                else if(name == wxT("unitambientcolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colUnitAmbient->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlUnitAmbientColourDisplay->SetBackgroundColour(*colUnitAmbient);
//                }
//                else if(name == wxT("unitsuncolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colUnitSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlUnitSunColourDisplay->SetBackgroundColour(*colUnitSun);
//                }
//                else if(name == wxT("unitshadowdensity"))
//                    tcUnitShadowDensity->SetValue(value);
//                else if(name == wxT("waterbasecolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colWaterBase->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlWaterBaseColourDisplay->SetBackgroundColour(*colWaterBase);
//                }
//                else if(name == wxT("watermincolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colWaterMin->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlWaterMinColourDisplay->SetBackgroundColour(*colWaterMin);
//                }
//                else if(name == wxT("waterabsorbcolor"))
//                {
//                    int subLength;
//                    float red, green, blue;
//
//                    subLength = value.Find(wxT(" "));
//                    red = wxAtof( value.Mid( 0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    subLength = value.Find(wxT(" "));
//                    green = wxAtof( value.Mid(0, subLength));
//                    value = value.Mid( subLength+1, value.Length());
//
//                    blue = wxAtof( value );
//                    colWaterAbsorb->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
//                    pnlWaterAbsorbColourDisplay->SetBackgroundColour(*colWaterAbsorb);
//                }
////                else if(name == wxT("startposx"))
////                {
////                    switch(startPosID)
////                    {
////                        case 0:
////                            tcTeam1X->SetValue(value);
////                            break;
////                        case 1:
////                            tcTeam2X->SetValue(value);
////                            break;
////                        case 2:
////                            tcTeam3X->SetValue(value);
////                            break;
////                        case 3:
////                            tcTeam4X->SetValue(value);
////                            break;
////                        case 4:
////                            tcTeam5X->SetValue(value);
////                            break;
////                        case 5:
////                            tcTeam6X->SetValue(value);
////                            break;
////                        case 6:
////                            tcTeam7X->SetValue(value);
////                            break;
////                        case 7:
////                            tcTeam8X->SetValue(value);
////                            break;
////                        default:
////                            break;
////                    }
////                }
//                else if(name == wxT("startposz"))
//                {
//                    switch(startPosID)
//                    {
//                        case 0:
//                            tcTeam1Y->SetValue(value);
//                            break;
//                        case 1:
//                            tcTeam2Y->SetValue(value);
//                            break;
//                        case 2:
//                            tcTeam3Y->SetValue(value);
//                            break;
//                        case 3:
//                            tcTeam4Y->SetValue(value);
//                            break;
//                        case 4:
//                            tcTeam5Y->SetValue(value);
//                            break;
//                        case 5:
//                            tcTeam6Y->SetValue(value);
//                            break;
//                        case 6:
//                            tcTeam7Y->SetValue(value);
//                            break;
//                        case 7:
//                            tcTeam8Y->SetValue(value);
//                            break;
//                        default:
//                            break;
//                    }
//                }
//            }
//        }
//        file->Close();
//    }
//    delete loadSMDDialog;
//    //bSaved = true;
}

void Frontend::OnClickSMDSave(wxCommandEvent& event)
{
    wxString sBuffer;
    wxFile file;
//    int iTeamCount;
////A large number of variables are read as char's but need to be stored as floats between 1 and 0
//    wxString sSunRed = wxString::Format(wxT("%f"), (float)colSun->Red()/255);
//    wxString sSunGreen = wxString::Format(wxT("%f"), (float)colSun->Green()/255);
//    wxString sSunBlue = wxString::Format(wxT("%f"), (float)colSun->Blue()/255);
//
//    wxString sSkyRed = wxString::Format(wxT("%f"), (float)colSky->Red()/255);
//    wxString sSkyGreen = wxString::Format(wxT("%f"), (float)colSky->Green()/255);
//    wxString sSkyBlue = wxString::Format(wxT("%f"), (float)colSky->Blue()/255);
//    wxString sCloudRed = wxString::Format(wxT("%f"), (float)colCloud->Red()/255);
//    wxString sCloudGreen = wxString::Format(wxT("%f"), (float)colCloud->Green()/255);
//    wxString sCloudBlue = wxString::Format(wxT("%f"), (float)colCloud->Blue()/255);
//    wxString sFogRed = wxString::Format(wxT("%f"), (float)colFog->Red()/255);
//    wxString sFogGreen = wxString::Format(wxT("%f"), (float)colFog->Green()/255);
//    wxString sFogBlue = wxString::Format(wxT("%f"), (float)colFog->Blue()/255);
//
//    wxString sGroundAmbientRed = wxString::Format(wxT("%f"), (float)colGroundAmbient->Red()/255);
//    wxString sGroundAmbientGreen = wxString::Format(wxT("%f"), (float)colGroundAmbient->Green()/255);
//    wxString sGroundAmbientBlue = wxString::Format(wxT("%f"), (float)colGroundAmbient->Blue()/255);
//    wxString sGroundSunRed = wxString::Format(wxT("%f"), (float)colGroundSun->Red()/255);
//    wxString sGroundSunGreen = wxString::Format(wxT("%f"), (float)colGroundSun->Green()/255);
//    wxString sGroundSunBlue = wxString::Format(wxT("%f"), (float)colGroundSun->Blue()/255);
//    wxString sUnitSunRed = wxString::Format(wxT("%f"), (float)colUnitSun->Red()/255);
//    wxString sUnitSunGreen = wxString::Format(wxT("%f"), (float)colUnitSun->Green()/255);
//    wxString sUnitSunBlue = wxString::Format(wxT("%f"), (float)colUnitSun->Blue()/255);
//    wxString sUnitAmbientRed = wxString::Format(wxT("%f"), (float)colUnitAmbient->Red()/255);
//    wxString sUnitAmbientGreen = wxString::Format(wxT("%f"), (float)colUnitAmbient->Green()/255);
//    wxString sUnitAmbientBlue = wxString::Format(wxT("%f"), (float)colUnitAmbient->Blue()/255);
//
//    wxString sWaterBaseRed = wxString::Format(wxT("%f"), (float)colWaterBase->Red()/255);
//    wxString sWaterBaseGreen = wxString::Format(wxT("%f"), (float)colWaterBase->Green()/255);
//    wxString sWaterBaseBlue = wxString::Format(wxT("%f"), (float)colWaterBase->Blue()/255);
//    wxString sWaterMinRed = wxString::Format(wxT("%f"), (float)colWaterMin->Red()/255);
//    wxString sWaterMinGreen = wxString::Format(wxT("%f"), (float)colWaterMin->Green()/255);
//    wxString sWaterMinBlue = wxString::Format(wxT("%f"), (float)colWaterMin->Blue()/255);
//    wxString sWaterAbsorbRed = wxString::Format(wxT("%f"), (float)colWaterAbsorb->Red()/255);
//    wxString sWaterAbsorbGreen = wxString::Format(wxT("%f"), (float)colWaterAbsorb->Green()/255);
//    wxString sWaterAbsorbBlue = wxString::Format(wxT("%f"), (float)colWaterAbsorb->Blue()/255);
//
//    sFogRed.Truncate(5);
//    sFogGreen.Truncate(5);
//    sFogBlue.Truncate(5);
//    sSunRed.Truncate(5);
//    sSunGreen.Truncate(5);
//    sSunBlue.Truncate(5);
//    sSkyRed.Truncate(5);
//    sSkyGreen.Truncate(5);
//    sSkyBlue.Truncate(5);
//    sCloudRed.Truncate(5);
//    sCloudGreen.Truncate(5);
//    sCloudBlue.Truncate(5);
//
//    sGroundAmbientRed.Truncate(5);
//    sGroundAmbientGreen.Truncate(5);
//    sGroundAmbientBlue.Truncate(5);
//    sGroundSunRed.Truncate(5);
//    sGroundSunGreen.Truncate(5);
//    sGroundSunBlue.Truncate(5);
//    sUnitAmbientRed.Truncate(5);
//    sUnitAmbientGreen.Truncate(5);
//    sUnitAmbientBlue.Truncate(5);
//    sUnitSunRed.Truncate(5);
//    sUnitSunGreen.Truncate(5);
//    sUnitSunBlue.Truncate(5);
//
//    sWaterBaseRed.Truncate(5);
//    sWaterBaseGreen.Truncate(5);
//    sWaterBaseBlue.Truncate(5);
//    sWaterMinRed.Truncate(5);
//    sWaterMinGreen.Truncate(5);
//    sWaterMinBlue.Truncate(5);
//    sWaterAbsorbRed.Truncate(6);
//    sWaterAbsorbGreen.Truncate(6);
//    sWaterAbsorbBlue.Truncate(6);

    file.Open(wxT("map.smd"), wxFile::write);
    file.Write(wxT("[MAP]\n{\n"));
//        file.Write(wxT("\tDescription=") + tcDescription->GetValue() + wxT(";\n"));
//        file.Write(wxT("\tTidalStrength=") + tcTidalStrength->GetValue() + wxT(";\n"));
//        file.Write(wxT("\tGravity=") + tcGravity->GetValue() + wxT(";\n"));
//        file.Write(wxT("\tMaxMetal=") + tcMaxMetal->GetValue() + wxT(";\n"));
//        file.Write(wxT("\tExtractorRadius=") + tcExtractorRadius->GetValue() + wxT(";\n"));
//        file.Write(wxT("\tMapHardness=") + tcMapHardness->GetValue() + wxT(";\n"));
//        file.Write(wxT("\t[SMF]\n\t{\n"));
//            file.Write(wxT("\t\tminheight = ") + tcMinHeight->GetValue() + wxT(";\n"));
//            file.Write(wxT("\t\tmaxheight = ") + tcMaxHeight->GetValue() + wxT(";\n"));
//        file.Write(wxT("\t}\n\t[ATMOSPHERE]\n\t{\n"));
//            file.Write(wxT("\t\tFogColour=") + sFogRed + wxT(" ") + sFogGreen + wxT(" ") + sFogBlue + wxT(";\n"));
//            file.Write(wxT("\t\tFogStart=") + tcFogStart->GetValue() + wxT(";\n"));
//            file.Write(wxT("\t\tSunColour=") + sSunRed + wxT(" ") + sSunGreen + wxT(" ") + sSunBlue + wxT(";\n"));
//            file.Write(wxT("\t\tSkyColour=") + sSkyRed + wxT(" ") + sSkyGreen + wxT(" ") + sSkyBlue + wxT(";\n"));
//            file.Write(wxT("\t\tCloudColour=") + sCloudRed + wxT(" ") + sCloudGreen + wxT(" ") + sCloudBlue + wxT(";\n"));
//            file.Write(wxT("\t\tCloudDensity=") + tcCloudDensity->GetValue() + wxT(";\n"));
//            file.Write(wxT("\t\tMinWind=") + tcMinWind->GetValue() + wxT(";\n"));
//            file.Write(wxT("\t\tMaxWind=") + tcMaxWind->GetValue() + wxT(";\n"));
//        file.Write(wxT("\t}\n\t[LIGHT]\n\t{\n"));
//            file.Write(wxT("\t\tSunDir=1 2 0;\n"));//            file.Write(wxT("\t\tSunDir=") + tcSunDirX->GetValue() + wxT(" ") + tcSunDirY->GetValue() + wxT(" ") + tcSunDirZ->GetValue() + wxT(";\n"));
//            file.Write(wxT("\t\tGroundAmbientColour=") + sGroundAmbientRed + wxT(" ") + sGroundAmbientGreen + wxT(" ") + sGroundAmbientBlue + wxT(";\n"));
//            file.Write(wxT("\t\tGroundSunColour=") + sGroundSunRed + wxT(" ") + sGroundSunGreen + wxT(" ") + sGroundSunBlue + wxT(";\n"));
//            file.Write(wxT("\t\tGroundShadowDensity=") + tcGroundShadowDensity->GetValue() +wxT(";\n"));
//            file.Write(wxT("\t\tUnitAmbientColour=") + sUnitAmbientRed + wxT(" ") + sUnitAmbientGreen + wxT(" ") + sUnitAmbientBlue + wxT(";\n"));
//            file.Write(wxT("\t\tUnitSunColour=") + sUnitSunRed + wxT(" ") + sUnitSunGreen + wxT(" ") + sUnitSunBlue + wxT(";\n"));
//            file.Write(wxT("\t\tUnitShadowDensity=") + tcUnitShadowDensity->GetValue() +wxT(";\n"));
//        file.Write(wxT("\t}\n\t[WATER]\n\t{\n"));
//            file.Write(wxT("\t\tWaterBaseColour=") + sWaterBaseRed + wxT(" ") + sWaterBaseGreen + wxT(" ") + sWaterBaseBlue + wxT(";\n"));
//            file.Write(wxT("\t\tWaterMinColour=") + sWaterMinRed + wxT(" ") + sWaterMinGreen + wxT(" ") + sWaterMinBlue + wxT(";\n"));
//            file.Write(wxT("\t\tWaterAbsorbColour=") + sWaterAbsorbRed + wxT(" ") + sWaterAbsorbGreen + wxT(" ") + sWaterAbsorbBlue + wxT(";\n"));
//        file.Write(wxT("\t}\n"));
//        iTeamCount = wxAtoi(tcTeamCount->GetValue());
//        switch(iTeamCount){
//            case 8:
//                file.Write(wxT("\t[TEAM7]\n\t{\n\t\tStartPosX=") + tcTeam8X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam8Y->GetValue() + wxT(";\n\t}\n"));
//            case 7:
//                file.Write(wxT("\t[TEAM6]\n\t{\n\t\tStartPosX=") + tcTeam7X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam7Y->GetValue() + wxT(";\n\t}\n"));
//            case 6:
//                file.Write(wxT("\t[TEAM5]\n\t{\n\t\tStartPosX="));
//            case 5:
//                file.Write(wxT("\t[TEAM4]\n\t{\n\t\tStartPosX=") + tcTeam5X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam5Y->GetValue() + wxT(";\n\t}\n"));
//            case 4:
//                file.Write(wxT("\t[TEAM3]\n\t{\n\t\tStartPosX=") + tcTeam4X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam4Y->GetValue() + wxT(";\n\t}\n"));
//            case 3:
//                file.Write(wxT("\t[TEAM2]\n\t{\n\t\tStartPosX=") + tcTeam3X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam3Y->GetValue() + wxT(";\n\t}\n"));
//            case 2:
//                file.Write(wxT("\t[TEAM1]\n\t{\n\t\tStartPosX=") + tcTeam2X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam2Y->GetValue() + wxT(";\n\t}\n"));
//                file.Write(wxT("\t[TEAM0]\n\t{\n\t\tStartPosX=") + tcTeam1X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam1Y->GetValue() + wxT(";\n\t}\n"));
//        }
        file.Write(wxT("\n}"));

    file.Close();
}


