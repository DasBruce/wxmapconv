/// \file uiutils.cpp

/* Copyright (C) 2007 The SpringLobby Team. All rights reserved. */

#include <wx/colour.h>
#include <wx/image.h>
#include <wx/mstream.h>
#include <wx/bitmap.h>
#include <wx/log.h>
#include <wx/image.h>
#include <wx/clipbrd.h>
#include <wx/cmndata.h>
#include <wx/colordlg.h>
#include <wx/dataobj.h>

#include <cmath>
#include "conversion.h"
#include "uiutils.h"

wxString RTFtoText( const wxString& rtfinput )
{
    wxString ret = rtfinput;
    ret = ret.AfterFirst( '{' ).BeforeLast( '}' );

    ret.Replace( _T("\\pard"), _T("") ); // remove a ambiguus char

    ret.Replace( _T("\\par"), _T(" \n") ); // convert the end of lines

    wxString BeforeBrack = ret.BeforeFirst( '{' );
    wxString AfterBrack = ret.AfterLast( '}' );
    ret = BeforeBrack + AfterBrack; // remove everyhting that matches { text }

    wxString out;
    while ( ret.Find('\\') >= 0 ) //remove anything in the form \please\ignore\this
    {
        out += ret.BeforeFirst( '\\' );
        ret = ret.AfterFirst ( '\\' );
        ret = ret.AfterFirst ( ' ' );
    } ;

    return out;
}

bool AreColoursSimilar( const wxColour& col1, const wxColour& col2, int mindiff )
{
    int r,g,b;
    r = col1.Red() - col2.Red();
    g = col1.Green() - col2.Green();
    b = col1.Blue() - col2.Blue();
    r = r>0?r:-r;
    g = g>0?g:-g;
    b = b>0?b:-b;
    int difference = std::min( r, g );
    difference = std::min( difference, b );
    return difference < mindiff;
}


void ColourDelta( int& r, int& g, int& b, const int& delta )
{
    int tmpdelta;
    if ( delta > 0 )
    {
        r += delta;
        tmpdelta = delta;
        if ( r > 255 )
        {
            tmpdelta += r - 255;
            r = 255;
        }
        g += tmpdelta;
        tmpdelta = delta;
        if ( g > 255 )
        {
            tmpdelta += g - 255;
            g = 255;
        }
        b += tmpdelta;
        if ( b > 255 ) b = 255;
    }
    else
    {
        r += delta;
        tmpdelta = -delta;
        if ( r < 0 )
        {
            tmpdelta -= r;
            r = 0;
        }
        g -= tmpdelta;
        tmpdelta = -delta;
        if ( g < 0 )
        {
            tmpdelta -= g;
            g = 0;
        }
        b -= tmpdelta;
        if ( b < 0 ) b = 0;
    }
}

wxColour ColourDelta( const wxColour& colour, const int& delta )
{
    int r = colour.Red();
    int g = colour.Green();
    int b = colour.Blue();
    ColourDelta( r, g, b, delta );
    return wxColour( r, g, b );
}

wxBitmap charArr2wxBitmap(const unsigned char * arg, int size)
{
    return wxBitmap( charArr2wxImage( arg, size) );
}

wxImage charArr2wxImage(const unsigned char * arg, int size)
{
    wxMemoryInputStream istream( arg, size );
    return wxImage( istream, wxBITMAP_TYPE_PNG );
}

namespace {
//! Helper class for BorderInvariantResizeImage
struct Resizer
{
	// Author: Tobi Vollebregt

	Resizer( wxImage& result, const wxImage& image, bool alpha )
		: width( result.GetWidth() )
		, height( result.GetHeight() )
		, imwidth( image.GetWidth() )
		, imheight( image.GetHeight() )
		, half_min_width( (std::min(width, imwidth) + 1) / 2 )    // round up to cover middle pixel
		, half_min_height( (std::min(height, imheight) + 1) / 2 ) // if new width/height is uneven.
		, bytes_per_pixel( alpha ? 1 : 3 )
		, image_data( alpha ? image.GetAlpha() : image.GetData() )
		, result_data( alpha ? result.GetAlpha() : result.GetData() )
	{
	}

	void CopyRow( int result_y, int image_y )
	{
		unsigned char* result_row = result_data + bytes_per_pixel * result_y * width;
		const unsigned char* image_row = image_data + bytes_per_pixel * image_y * imwidth;
		const int bytes = bytes_per_pixel * half_min_width;

		memcpy( result_row, image_row, bytes );
		memcpy( result_row + bytes_per_pixel * width - bytes, image_row + bytes_per_pixel * imwidth - bytes, bytes );

		if ( width > imwidth )
		{
			unsigned char* result_pixel = result_row + bytes;
			const unsigned char* image_pixel = image_row + bytes;

			for (int x = half_min_width; x < width - half_min_width; ++x, result_pixel += bytes_per_pixel)
			{
				memcpy( result_pixel, image_pixel, bytes_per_pixel );
			}
		}
	}

	void CopyTopAndBottomRows()
	{
		for (int y = 0; y < half_min_height; ++y)
		{
			CopyRow( y, y );
			CopyRow( height - 1 - y, imheight - 1 - y );
		}
	}

	void CopyCenterRows()
	{
		for (int y = half_min_height; y < height - half_min_height; ++y)
		{
			CopyRow( y, half_min_height - 1 );
		}
	}

	void operator () ()
	{
		CopyTopAndBottomRows();
		CopyCenterRows();
	}

	const int width, height;
	const int imwidth, imheight;
	const int half_min_width, half_min_height;
	const int bytes_per_pixel;
	const unsigned char* const image_data;
	unsigned char* const result_data;
};
}

wxImage BorderInvariantResizeImage(  const wxImage& image, int width, int height )
{
	if ( !image.IsOk() || (width == image.GetWidth() && height == image.GetHeight()) )
		return image;

	wxImage ret( width, height );
	Resizer data_resize( ret, image, false );
	data_resize();

	if ( image.HasAlpha() )
	{
		ret.InitAlpha();
		Resizer alpha_resize( ret, image, true );
		alpha_resize();
	}

	return ret;
}

wxSize MakeFit(const wxSize &original, const wxSize &bounds)
{
  if( ( bounds.GetWidth() <= 0 ) || ( bounds.GetHeight() <= 0 ) ) return wxSize(0,0);
  int sizex = ( original.GetWidth() * bounds.GetHeight() ) / original.GetHeight();
  if( sizex <= bounds.GetWidth() )
  {
    return wxSize( sizex, bounds.GetHeight() );
  }
  else
  {
    int sizey = ( original.GetHeight() * bounds.GetWidth() ) / original.GetWidth();
    return wxSize( bounds.GetWidth(), sizey );
  }
}

void CopyToClipboard( const wxString& text )
{
    if ( wxTheClipboard->Open() ) {
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData( new wxTextDataObject( text ) );
        wxTheClipboard->Close();
    }
}
