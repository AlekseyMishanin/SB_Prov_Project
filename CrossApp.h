//---------------------------------------------------------------------------
//
// Name:        CrossApp.h
// Author:      mishaninaa
// Created:     07.07.2016 15:46:35
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __CROSSFRMApp_h__
#define __CROSSFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class CrossFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
