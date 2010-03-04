#include "previewtab.h"

_previewTab::_previewTab(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{

    wxBoxSizer *hboxPreview = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *gboxPreviewBig = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Preview"));

	bmHeightmap = charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) );
	bmTexture = charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) );
	bmMetal = charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) );
	bmFeature = charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) );
	bmTypemap = charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) );

    wxPanel *pnlPreviewBig = new wxPanel(this, -1);
    wxBoxSizer *hboxPreviewBig = new wxBoxSizer(wxHORIZONTAL);
	sbmPreviewBig = new wxStaticBitmap(pnlPreviewBig, wxID_ANY, charArr2wxBitmap( placeholderbig_png, sizeof( placeholderbig_png ) ), wxPoint(10, 10));

    hboxPreviewBig->Add(sbmPreviewBig, 1, wxEXPAND, 5);
    pnlPreviewBig->SetSizer(hboxPreviewBig);
    gboxPreviewBig->Add(pnlPreviewBig, 1, wxEXPAND | wxRIGHT | wxLEFT | wxBOTTOM | wxTOP, 5);
    sbmPreviewBig->CentreOnParent();

        wxArrayString *asPreview = new wxArrayString();
        asPreview->Add(wxT("Heightmap"), 1);
        asPreview->Add(wxT("Texture"), 1);
        asPreview->Add(wxT("Metal"), 1);
        asPreview->Add(wxT("Feature"), 1);
        asPreview->Add(wxT("Type"), 1);
    rbxPreview = new wxRadioBox(this, IDRBX_PREVIEW, wxT("Select File for Preview"), wxDefaultPosition, wxDefaultSize, *asPreview, 0, wxRA_SPECIFY_ROWS, wxDefaultValidator, wxT("radioBox"));

    hboxPreview->Add(gboxPreviewBig, 1, wxEXPAND, 5);
    hboxPreview->Add(rbxPreview, 0, wxEXPAND, 5);
    this->SetSizer(hboxPreview);

    Connect(IDRBX_PREVIEW, wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(_previewTab::OnChangePreview));
}

void _previewTab::OnChangePreview(wxCommandEvent& event)
{
    int selection = rbxPreview->GetSelection();

    switch(selection){
        case ID_HEIGHT:
			sbmPreviewBig->SetBitmap(bmHeightmap);
            break;
        case ID_TEXTURE:
			sbmPreviewBig->SetBitmap(bmTexture);
            break;
        case ID_METAL:
			sbmPreviewBig->SetBitmap(bmMetal);
            break;
        case ID_FEATURE:
			sbmPreviewBig->SetBitmap(bmFeature);
            break;
        case ID_TYPE:
			sbmPreviewBig->SetBitmap(bmTypemap);
            break;
        default:
            break;
    }
    sbmPreviewBig->CentreOnParent();
    sbmPreviewBig->Refresh();
}

bool _previewTab::LoadPreviewImage(int type, wxImage *image)
{
    bool success = false;
    switch(type){
        case ID_HEIGHT:
			bmHeightmap = wxBitmap(*image, -1);
			if(bmHeightmap.Ok()){
                success = true;
                rbxPreview->Enable(ID_HEIGHT, true);
            }
            if(rbxPreview->GetSelection()==ID_HEIGHT)
				sbmPreviewBig->SetBitmap(bmHeightmap);
            break;
        case ID_TEXTURE:
			bmTexture = wxBitmap(*image, -1);
			if(bmTexture.Ok()){
                success = true;
                rbxPreview->Enable(ID_TEXTURE, true);
            }
            if(rbxPreview->GetSelection()==ID_TEXTURE)
				sbmPreviewBig->SetBitmap(bmTexture);
            break;
        case ID_METAL:
			bmMetal = wxBitmap(*image, -1);
			if(bmMetal.Ok()){
                success = true;
                rbxPreview->Enable(ID_HEIGHT, true);
            }
            if(rbxPreview->GetSelection()==ID_METAL)
				sbmPreviewBig->SetBitmap(bmMetal);
            break;
        case ID_FEATURE:
			bmFeature = wxBitmap(*image, -1);
			if(bmFeature.Ok()){
                success = true;
                rbxPreview->Enable(ID_HEIGHT, true);
            }
            if(rbxPreview->GetSelection()==ID_FEATURE)
				sbmPreviewBig->SetBitmap(bmFeature);
            break;
        case ID_TYPE:
			bmTypemap = wxBitmap(*image, -1);
			if(bmTypemap.Ok()){
                success = true;
                rbxPreview->Enable(ID_HEIGHT, true);
            }
            if(rbxPreview->GetSelection()==ID_TYPE)
				sbmPreviewBig->SetBitmap(bmTypemap);
            break;
        default:
            break;
    }
    sbmPreviewBig->CentreOnParent();
    return success;
}

