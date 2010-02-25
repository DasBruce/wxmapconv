/// \file uiutils.h

#ifndef SPRINGLOBBY_HEADERGUARD_UIUTILS_H
#define SPRINGLOBBY_HEADERGUARD_UIUTILS_H

#include <wx/intl.h>
#include <vector>

class wxColour;
class wxImage;
class wxBitmap;


#define wxDefaultBitmap wxBitmap()

wxString RTFtoText( const wxString& rtfinput );
bool AreColoursSimilar( const wxColour& col1, const wxColour& col2, int mindiff = 10 );

void ColourDelta( int& r, int& g, int& b, const int& delta );
wxColour ColourDelta( const wxColour& colour, const int& delta );

wxColour GetColorFromFloatStrng( const wxString& color );

//! takes best fitting size of original inside bounds keeping aspect ratio
wxSize MakeFit(const wxSize &original, const wxSize &bounds);

//! used to load png data into a wxImage
wxImage charArr2wxImage(const unsigned char * arg, int size);
//! used to load png data into a wxBitmap
wxBitmap charArr2wxBitmap(const unsigned char * arg, int size);

//! shrinks/expands image by removing/duplicating rows/columns from the center of the image
wxImage BorderInvariantResizeImage(  const wxImage& image, int width, int height );

void CopyToClipboard( const wxString& text );

//! open either plattform default browser or binary saved in settings with given url
void OpenWebBrowser( const wxString& url );

#endif
// SPRINGLOBBY_HEADERGUARD_UIUTILS_H

