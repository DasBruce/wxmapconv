#include "previewtab.h"

_previewTab::_previewTab(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
    bShowWater = false;
    bShowWater = false;
    bHeightmapLoaded = false;
    bTextureLoaded = false;
    bMetalLoaded = false;
    bFeatureLoaded = false;
    bTypemapLoaded = false;

    wxBoxSizer *hboxPreview = new wxBoxSizer(wxHORIZONTAL);
        wxStaticBoxSizer *gboxPreviewBig = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Preview"));

        wxBitmap bmTemp = charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) );

        //imHeightmap = bmTemp.ConvertToImage();
        imTexture = bmTemp.ConvertToImage();
        imMetal = bmTemp.ConvertToImage();
        imFeature = bmTemp.ConvertToImage();
        imTypemap = bmTemp.ConvertToImage();

        imHeightmapWater = bmTemp.ConvertToImage();
        imTextureWater = bmTemp.ConvertToImage();
        imMetalWater = bmTemp.ConvertToImage();
        imFeatureWater = bmTemp.ConvertToImage();
        imTypemapWater = bmTemp.ConvertToImage();

        wxPanel *pnlPreviewBig = new wxPanel(this, -1);
        wxBoxSizer *vboxPreviewBig = new wxBoxSizer(wxVERTICAL);
        sbmPreviewBig = new wxStaticBitmap(pnlPreviewBig, wxID_ANY, charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) ), wxPoint(10, 10));

        vboxPreviewBig->Add(sbmPreviewBig, 1, wxEXPAND, 5);
        pnlPreviewBig->SetSizer(vboxPreviewBig);
        gboxPreviewBig->Add(pnlPreviewBig, 1, wxEXPAND | wxRIGHT | wxLEFT | wxBOTTOM | wxTOP, 5);
        sbmPreviewBig->CentreOnParent();

        wxBoxSizer *vboxOptions = new wxBoxSizer(wxVERTICAL);
                wxArrayString *asPreview = new wxArrayString();
                asPreview->Add(wxT("Heightmap"), 1);
                asPreview->Add(wxT("Texture"), 1);
                asPreview->Add(wxT("Metal"), 1);
                asPreview->Add(wxT("Feature"), 1);
                asPreview->Add(wxT("Type"), 1);
            rbxPreview = new wxRadioBox(this, IDRBX_PREVIEW, wxT("Select File for Preview"), wxDefaultPosition, wxDefaultSize, *asPreview, 0, wxRA_SPECIFY_ROWS, wxDefaultValidator, wxT("radioBox"));
            wxStaticBoxSizer *gboxWaterOptions = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Water"));
                cbOverlayWater = new wxCheckBox(this, IDCB_WATER_OVERLAY, wxT("Show Water"));
                //cbOverlayWater->Enable(false);
                btnRecalculateWater = new wxButton(this, IDBTN_RECALCULATEWATER, wxT("Recalc Water"));
            gboxWaterOptions->Add(cbOverlayWater, wxTOP | wxBOTTOM, wxEXPAND, 5);
            gboxWaterOptions->Add(btnRecalculateWater, wxTOP | wxBOTTOM, wxEXPAND, 5);

            vboxOptions->Add(rbxPreview, 0, wxEXPAND, 5);
            vboxOptions->Add(gboxWaterOptions, 0, wxEXPAND, 5);


    hboxPreview->Add(gboxPreviewBig, 1, wxEXPAND, 5);
    hboxPreview->Add(vboxOptions, 0, wxEXPAND, 5);
    this->SetSizer(hboxPreview);

    Connect(IDRBX_PREVIEW, wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(_previewTab::OnChangePreview));
    Connect(IDBTN_RECALCULATEWATER, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(_previewTab::OnClickRecalculateWater));
    Connect(IDCB_WATER_OVERLAY, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(_previewTab::OnClickShowWater));
}

void _previewTab::OnClickShowWater(wxCommandEvent& event){
    UpdatePreview();
}


bool _previewTab::LoadPreviewImage(int type, wxImage *image){

    switch(type){
        case ID_HEIGHT:
			imHeightmap = image->Copy();
			GenerateWaterImage(&imHeightmap, image, ID_HEIGHT);
			bHeightmapLoaded = true;

			if(bTextureLoaded)
                GenerateWaterImage(&imHeightmap, image, ID_TEXTURE);
			if(bMetalLoaded)
                GenerateWaterImage(&imHeightmap, image, ID_METAL);
			if(bFeatureLoaded)
                GenerateWaterImage(&imHeightmap, image, ID_FEATURE);
			if(bTypemapLoaded)
                GenerateWaterImage(&imHeightmap, image, ID_TYPE);

            break;
        case ID_TEXTURE:
			imTexture = image->Copy();
			bTextureLoaded = true;
			if(bHeightmapLoaded)
                GenerateWaterImage(&imHeightmap, image, ID_TEXTURE);
            break;
        case ID_METAL:
			imMetal = image->Copy();
			bMetalLoaded = true;
			if(bHeightmapLoaded)
                GenerateWaterImage(&imHeightmap, image, ID_METAL);
            break;
        case ID_FEATURE:
			imFeature = image->Copy();
			bFeatureLoaded = true;
			if(bHeightmapLoaded)
                GenerateWaterImage(&imHeightmap, image, ID_FEATURE);
            break;
        case ID_TYPE:
			imTypemap = image->Copy();
			bTypemapLoaded = true;
			if(bHeightmapLoaded)
                GenerateWaterImage(&imHeightmap, image, ID_TYPE);
            break;
        default:
            break;
    }
    bmBitmap = new wxBitmap(*image);

    if(type == rbxPreview->GetSelection()){
        sbmPreviewBig->SetBitmap(*bmBitmap);
        sbmPreviewBig->CentreOnParent();
    }
    sbmPreviewBig->Refresh();
}

void _previewTab::GenerateWaterImage(wxImage *imHeight, wxImage *imUnderlay, int type){
    unsigned char *dataHeight = imHeight->GetData();
    unsigned char *data = imUnderlay->GetData();
    for(int y=0; y<440; y++){
        for(int x=0; x<1320; x+=3){
            if(dataHeight[x+y*1320] < 123){//fWaterHeight){
                data[x+y*1320] = 0;
                data[x+y*1320+1] = 0;
                data[x+y*1320+2] = 255;
            }
        }
    }
    switch(type){
        case ID_HEIGHT:
            imHeightmapWater = imUnderlay->Copy();
            break;
        case ID_TEXTURE:
            imTextureWater = imUnderlay->Copy();
            break;
        case ID_METAL:
            imMetalWater = imUnderlay->Copy();
            break;
        case ID_FEATURE:
            imFeatureWater = imUnderlay->Copy();
            break;
        case ID_TYPE:
            imTypemapWater = imUnderlay->Copy();
            break;
        default:
            break;
    }
}

void _previewTab::OnClickRecalculateWater(wxCommandEvent& event){
//    int selection = rbxPreview->GetSelection();
//    bShowWater = cbOverlayWater->GetValue();
//
//    switch(selection){
//        case ID_HEIGHT:
//            if(bShowWater)
//                bmBitmap = new wxBitmap(imHeightmapWater);
//            else
//                bmBitmap = new wxBitmap(imHeightmap);
//            break;
//        case ID_TEXTURE:
//            if(bShowWater)
//                bmBitmap = new wxBitmap(imTexturepWater);
//            else
//                bmBitmap = new wxBitmap(imTexture);
//            break;
//        case ID_METAL:
//            if(bShowWater)
//                bmBitmap = new wxBitmap(imMetalWater);
//            else
//                bmBitmap = new wxBitmap(imMetal);
//            break;
//        case ID_FEATURE:
//            if(bShowWater)
//                bmBitmap = new wxBitmap(imFeatureWater);
//            else
//                bmBitmap = new wxBitmap(imFeature);
//            break;
//        case ID_TYPE:
//            if(bShowWater)
//                bmBitmap = new wxBitmap(imTypemapWater);
//            else
//                bmBitmap = new wxBitmap(imTypemap);
//            break;
//        default:
//            break;
//    }
}


void _previewTab::OnChangePreview(wxCommandEvent& event){
    UpdatePreview();
}

void _previewTab::UpdatePreview(void){
    int selection = rbxPreview->GetSelection();
    bShowWater = cbOverlayWater->GetValue();

    switch(selection){
        case ID_HEIGHT:
            if(bShowWater)
                bmBitmap = new wxBitmap(imHeightmapWater);
            else
                bmBitmap = new wxBitmap(imHeightmap);
            break;
        case ID_TEXTURE:
            if(bShowWater)
                bmBitmap = new wxBitmap(imTextureWater);
            else
                bmBitmap = new wxBitmap(imTexture);
            break;
        case ID_METAL:
            if(bShowWater)
                bmBitmap = new wxBitmap(imMetalWater);
            else
                bmBitmap = new wxBitmap(imMetal);
            break;
        case ID_FEATURE:
            if(bShowWater)
                bmBitmap = new wxBitmap(imFeatureWater);
            else
                bmBitmap = new wxBitmap(imFeature);
            break;
        case ID_TYPE:
            if(bShowWater)
                bmBitmap = new wxBitmap(imTypemapWater);
            else
                bmBitmap = new wxBitmap(imTypemap);
            break;
        default:
            break;
    }
    sbmPreviewBig->SetBitmap(*bmBitmap);
    sbmPreviewBig->CentreOnParent();
    sbmPreviewBig->Refresh();
}
