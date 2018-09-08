//---------------------------------------------------------------------------
//
// Name:        CrossApp.cpp
// Author:      mishaninaa
// Created:     07.07.2016 15:46:35
// Description: 
//
//---------------------------------------------------------------------------

#include "CrossApp.h"
#include "CrossFrm.h"

IMPLEMENT_APP(CrossFrmApp)

bool CrossFrmApp::OnInit()
{
    CrossFrm* frame = new CrossFrm("ÓÏÒÎèÀ");
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int CrossFrmApp::OnExit()
{
	return 0;
}
