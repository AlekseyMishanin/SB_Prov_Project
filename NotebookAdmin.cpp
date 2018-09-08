#include "CrossFrm.h"

extern MYSQL* conn;
extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;
extern void EditStringFioFull (wxString& str);
extern void EditTheLine(wxString &str, wxWindow* win); //������� ����������� ������ ��� ������� ���� win �������� ������� \n
extern void insertStrDateToCtrl (wxString& str, wxDatePickerCtrl* window);

BEGIN_EVENT_TABLE(NotebookAdmin,wxFrame)
    EVT_CHAR_HOOK(NotebookAdmin::OnChar)
    EVT_SIZE(NotebookAdmin::OnSize)
	EVT_MOVE_END(NotebookAdmin::OnMove)
    EVT_NOTEBOOK_PAGE_CHANGED(wxID_ADM_NOTEBOOK,NotebookAdmin::GhangePageNotebook) //��������� �������� ��������
    EVT_NOTEBOOK_PAGE_CHANGED(wxID_ADM_NOTEBOOK_SPR,NotebookAdmin::GhangePageNotebook) //��������� �������� ��������
    EVT_CHILD_FOCUS(NotebookAdmin::NewFocus)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_0,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_GROUP_0,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_1,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_GROUP_1,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_2,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_3,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_GROUP_3,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_4,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_5,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_6,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_7,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_LVL_7,NotebookAdmin::GhangeRadiobox)
    EVT_RADIOBOX(wxID_ADM_RADIOBOX_TYPE_8,NotebookAdmin::GhangeRadiobox)
    EVT_BUTTON(wxID_OK,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_CANCEL,NotebookAdmin::OnButton)
    EVT_PG_ITEM_COLLAPSED(wxID_ADM_PROPERTYGRID_SOV, NotebookAdmin::CollapsedPropgrid) //������� ������������, ����� ����������� ���������
    EVT_PG_ITEM_EXPANDED(wxID_ADM_PROPERTYGRID_SOV, NotebookAdmin::ExpandedPropgrid) //������� ������������, ����� ��������� ���������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_COLLPANE_SOV_REG, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_COLLPANE_SOV_DOLZ, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_COLLPANE_SOV_R_1, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_COLLPANE_SOV_D_1, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_COLLPANE_SOV_D_2, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_BL_COLLPANE_SEARCH, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_BL_COLLPANE_INS, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_BL_COLLPANE_UPD, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_COLLPANE_SOV_HOL, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_COLLPANE_HOL_INS, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_ADM_COLLPANE_HOL_UPD, NotebookAdmin::CollapChanged) //������ �������� ������
    EVT_TEXT_ENTER(wxID_ADM_SEARCH_SOV_FIO, NotebookAdmin::OnEnter) //����� ENTER � ���� ������
    EVT_TEXT_ENTER(wxID_ADM_BL_SEARCH, NotebookAdmin::OnEnter) //����� ENTER � ���� ������
    EVT_LIST_ITEM_FOCUSED (wxID_ADM_LISTVIEW_SOV_SP, NotebookAdmin::FocusedItemListview)
    EVT_LIST_ITEM_FOCUSED (wxID_ADM_LISTVIEW_SOV_D, NotebookAdmin::FocusedItemListview)
    EVT_LIST_ITEM_FOCUSED (wxID_ADM_BL_LISTVIEW_SP, NotebookAdmin::FocusedItemListview)
    EVT_LIST_ITEM_FOCUSED (wxID_ADM_SOV_LISTVIEW_HOL, NotebookAdmin::FocusedItemListview)
    EVT_COMBOBOX(wxID_ADM_COMBOBOX_LVL_R, NotebookAdmin::ChangeCombobox)
    EVT_COMBOBOX(wxID_ADM_BL_COMBOBOX_T_BL, NotebookAdmin::ChangeCombobox)
    EVT_BUTTON(wxID_ADM_BUTTON_SOV_UPD_PD,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_SAVE_R,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_CANCEL_R,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_SAVE_D,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_CANCEL_D,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_SAVE_D1,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_CANCEL_D1,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_DEL_R,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_DEL_D,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_PLACE_R,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUT_EXTRACT_R,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BL_SAVE_INS_1,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BL_CANCEL_INS_1,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BL_SAVE_UPD_1,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BL_CANCEL_UPD_1,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BL_BUTTON_DEL,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BL_BUTTON_DOP_INF,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUTTON_HOL_S_1,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUTTON_HOL_D_1,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUTTON_HOL_S_1_U,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUTTON_HOL_D_1_U,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_BUTTON_HOL_DEL,NotebookAdmin::OnButton)
    EVT_LISTBOX(wxID_ADM_PV_LISTBOX_SP_P1,NotebookAdmin::ListBoxWork)
    EVT_LISTBOX(wxID_ADM_PV_LISTBOX_SP_P2,NotebookAdmin::ListBoxWork)
    EVT_COMBOBOX(wxID_ADM_PV_COMBOBOX_P1,NotebookAdmin::ComboBoxWork)
    EVT_BUTTON(wxID_ADM_PV_BUTTOM_INS,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_PV_BUTTOM_DEL,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_PV_BUTTOM_TO,NotebookAdmin::OnButton)
    EVT_BUTTON(wxID_ADM_PV_BUTTOM_FROM,NotebookAdmin::OnButton)
END_EVENT_TABLE()


NotebookAdmin::NotebookAdmin(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint& pos, const wxSize& size , long style )
        : wxFrame(parent, id, title, pos, size, style)
{    
    wxDir dir(wxGetCwd());
    if (!dir.IsOpened())
    {
        wxMessageBox(wxERROR_OPEN_PROGRAM,wxERROR);
        Destroy();
    }
    else
    {
        vert_bos = new wxBoxSizer(wxVERTICAL);
        wxString str_full, str_first, str_last; //���������� ���������� ��� ���������� ���� � �������
        str_first = dir.GetName(); str_last= wxADMIN_CAP_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������
        SetIcon(wxIcon(str_full,wxBITMAP_TYPE_ICO)); //��������� ������ � ��������� ����
        wxImageList *imageList = new wxImageList(16,16);
        wxIcon icon;
        str_last= wxADMIN_SPR_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������                                                    //������� ������
        icon.LoadFile(str_full,wxBITMAP_TYPE_ICO);                      //��������� �������� �� �����
        imageList->Add(icon);                                           //��������� ����� ����������� � ������
        str_last= wxADMIN_OTP_SOV_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������
        icon.LoadFile(str_full,wxBITMAP_TYPE_ICO);                      //��������� �������� �� �����
        imageList->Add(icon);                                           //��������� ����� ����������� � ������
        str_last= wxBL_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������
        icon.LoadFile(str_full,wxBITMAP_TYPE_ICO);                      //��������� �������� �� �����
        imageList->Add(icon);                                           //��������� ����� ����������� � ������   
        str_last= wxPRIVKEY_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������
        icon.LoadFile(str_full,wxBITMAP_TYPE_ICO);                      //��������� �������� �� �����
        imageList->Add(icon);                                           //��������� ����� ����������� � ������   
        nb = new wxNotebook(this, wxID_ADM_NOTEBOOK, wxPoint(-1, -1), wxSize(-1, -1), wxNB_LEFT);
        wxPanel *panel1 = new wxPanel(nb, wxID_ADM_PAGE_SPR);
        panel_sovetnic = new wxPanel(nb, wxID_ADM_PAGE_SOV);
        panel_bd = new wxPanel(nb, wxID_ADM_PAGE_BL);
        panel_privkey = new wxPanel(nb, wxID_ADM_PAGE_PRIVKEY);
        nb->AddPage(panel1, (wxCAPTION_NOTEBOOK_PAGE_ADM_SPR)); //��������� � �������� ������ �� �������������
        nb->AddPage(panel_sovetnic, (wxCAPTION_NOTEBOOK_PAGE_ADM_SOV)); //��������� � �������� ������ �� ������� ����������
        nb->AddPage(panel_bd, (wxCAPTION_NOTEBOOK_PAGE_ADM_BL)); //��������� � ��������  ������ � �� ��
        nb->AddPage(panel_privkey, (wxCAPTION_NOTEBOOK_PAGE_ADM_PRKEY)); //��������� � �������� ������ 
	    nb->SetImageList(imageList); //������������� ������ ����������� ��� �������������
	    nb->SetPageImage(0,0); //������������� ����������� ��� ������ ��������
	    nb->SetPageImage(1,1);
	    nb->SetPageImage(2,2);
	    nb->SetPageImage(3,3);
	    vert_bos->Add(nb, 1, wxEXPAND|wxBOTTOM ,0);
	    this->SetSizer(vert_bos);
	    this->SetAutoLayout(true);
	    CreateSubNotebookPrivilege();
	    CreateSubNotebookBl();
	    CreateSubNotebookSpr();  
        CreateSubNotebookSov();  
        this->Layout();  
    }
}

void NotebookAdmin::BuildNotebookSpr (wxNotebook* nb_sub)
{
    panel_first_line->DestroyChildren();
    panel_second_line->DestroyChildren();
    switch (nb_sub->GetSelection())
    {
        default:break;
    }
}

void NotebookAdmin::CreateSubNotebookSpr (void)
{
    wxBoxSizer *vert_page = new wxBoxSizer(wxVERTICAL);
    vert_sub_note = new wxBoxSizer(wxVERTICAL);
    nb_spr = new wxNotebook(nb->FindWindow(wxID_ADM_PAGE_SPR), wxID_ADM_NOTEBOOK_SPR, wxPoint(-1, -1), wxSize(-1, -1), wxNB_TOP|wxNB_MULTILINE);
    vert_page->Add(nb_spr,1, wxEXPAND|wxBOTTOM ,0);
    wxPanel *panel = new wxPanel(nb_spr, wxID_ADM_PAGE_SPR_1);
	panel_first_line = new wxPanel(panel, wxID_ANY);
	panel_second_line = new wxPanel(panel, wxID_ANY);
    
    hr_local_1 = new wxBoxSizer(wxHORIZONTAL);
    vr_local_2 = new wxBoxSizer(wxVERTICAL);
    hr_local_3 = new wxBoxSizer(wxHORIZONTAL);
    hr_local_3->AddStretchSpacer(1);
    hr_local_3->Add(new wxButton(panel,wxID_OK,wxSTRING_APPLY), 0, wxEXPAND|wxALL,5);
    hr_local_3->Add(new wxButton(panel,wxID_CANCEL,wxSTRING_CANCEL), 0, wxEXPAND|wxALL,5);
    vert_sub_note->Add(panel_first_line, 0, wxEXPAND|wxBOTTOM ,0);
    vert_sub_note->Add(panel_second_line, 1, wxEXPAND|wxBOTTOM ,0);
    vert_sub_note->Add(hr_local_3, 0, wxEXPAND|wxALIGN_RIGHT,0);
    vert_sub_note->Add(new wxInfoBar(panel,wxID_ADM_INFOBAR_SPR_ALL), 0, wxEXPAND|wxALIGN_RIGHT,0);
	
	nb_spr->InsertPage(0,panel,wxCAPTION_NOTEBOOK_PAGE_ASSORTI);
	nb_spr->InsertPage(1,panel,wxCAPTION_NOTEBOOK_PAGE_DOLZ);
	nb_spr->InsertPage(2,panel,wxCAPTION_NOTEBOOK_PAGE_REZPROV);
	nb_spr->InsertPage(3,panel,wxCAPTION_NOTEBOOK_PAGE_BRAND);
	nb_spr->InsertPage(4,panel,wxCAPTION_NOTEBOOK_PAGE_UKRF);
	nb_spr->InsertPage(5,panel,wxCAPTION_NOTEBOOK_PAGE_SOV);
	nb_spr->InsertPage(6,panel,wxCAPTION_NOTEBOOK_PAGE_SBGO);
	nb_spr->InsertPage(7,panel,wxCAPTION_NOTEBOOK_PAGE_REG);
	nb_spr->InsertPage(8,panel,wxCAPTION_NOTEBOOK_PAGE_EVENT);
	nb_spr->SetSelection(1); //��������� ������ ��������, ����� ��������� ���������������� ����-
	
	(nb->FindWindow(wxID_ADM_PAGE_SPR))->SetSizer(vert_page);
	panel->SetSizer(vert_sub_note);
	panel_first_line->SetSizer(hr_local_1);
	panel_second_line->SetSizer(vr_local_2);
}

void NotebookAdmin::OnSize(wxSizeEvent& event) //����� ������� ���� �� ����� ������� ��������� ������ ��� ������ �������
{
	wxRect rect = GetRect(); //��������� ������� ������� ����
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_ADMIN_BD/x"), rect.GetX() );
    config->Write( wxT("/FORM_ADMIN_BD/y"), rect.GetY() );
    config->Write( wxT("/FORM_ADMIN_BD/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_ADMIN_BD/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    wxString str1= wxINFO_RISK_ACTION; //�������������� ���������� ��������������� �� ��������� ���������� � ��������
    ProcessInfoBar(str1, ((wxInfoBar*)((nb_spr->FindWindow(wxID_ADM_PAGE_SPR_1))->FindWindow(wxID_ADM_INFOBAR_SPR_ALL)))); //��������� � ������� ������ �������� ������� ���� � ������
    (nb_spr->FindWindow(wxID_ADM_PAGE_SPR_1))->Layout(); //������ ������������ ���� ������������ ������������
    event.Skip(true);
}
void NotebookAdmin::OnMove(wxMoveEvent& event) //����� ������� ���� �� ����� ������� ������������ ����
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_ADMIN_BD/x"), rect.GetX() );
    config->Write( wxT("/FORM_ADMIN_BD/y"), rect.GetY() );
    config->Write( wxT("/FORM_ADMIN_BD/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_ADMIN_BD/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}

void NotebookAdmin::GhangePageNotebook(wxBookCtrlEvent& event)
{
    switch (event.GetId()) //���������� �� ������ �������� ������ �������
    {
        case wxID_ADM_NOTEBOOK: //�������� �������
        {
            break;
        }
        case wxID_ADM_NOTEBOOK_SPR: //������� ������������
        {
            wxString str1= wxINFO_RISK_ACTION; //�������������� ���������� ��������������� �� ��������� ���������� � ��������
            ProcessInfoBar(str1, ((wxInfoBar*)((nb_spr->FindWindow(wxID_ADM_PAGE_SPR_1))->FindWindow(wxID_ADM_INFOBAR_SPR_ALL)))); //��������� � ������� ������ �������� ������� ���� � ������
            hr_local_1->Clear(); //����������� ����� �� ������������
            vr_local_2->Clear(); //����������� ����� �� ������������
            panel_first_line->DestroyChildren();  //��������� ���� ����� � ������������� ����
            panel_second_line->DestroyChildren(); //��������� ���� ����� � ������������� ����
            int idRadioBox=0; //���������� ��� ������ id radiobox ���������� ����� ��������
            switch (event.GetSelection()) //���������� ����� ��������� ��������
            {
                case 0:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE};
                    wxString rboxName1[] = {wxCAPTION_COLUMN_PROD_GROUP,wxCAPTION_COLUMN_PROD_SUBGROUP};     
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_0,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_GROUP_0,wxCAPTION_RADIOBOX_TABLE,wxDefaultPosition,wxDefaultSize,sizeof(rboxName1)/sizeof(wxString),rboxName1,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_0;
                    break;
                }
                case 1:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE};
                    wxString rboxName1[] = {wxCAPTION_RADIO_CH_DOLZ_1,wxCAPTION_RADIO_CH_DOLZ_2};     
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_1,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_GROUP_1,wxCAPTION_RADIOBOX_TABLE,wxDefaultPosition,wxDefaultSize,sizeof(rboxName1)/sizeof(wxString),rboxName1,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_1;
                    break;
                }
                case 2:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE};   
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_2,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_2;
	                break;
                }
                case 3:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE};
                    wxString rboxName1[] = {wxCAPTION_COLUMN_TYPE_BRAND,wxCAPTION_COLUMN_NAME_BRAND};     
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_3,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_GROUP_3,wxCAPTION_RADIOBOX_TABLE,wxDefaultPosition,wxDefaultSize,sizeof(rboxName1)/sizeof(wxString),rboxName1,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_3;
                    break;
                }
                case 4:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE};   
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_4,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_4;
	                break;
                }
                case 5:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE};   
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_5,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_5;
	                break;
                }
                case 6:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE};   
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_6,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_6;
	                break;
                }
                case 7:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE,wxCAPTION_BUTTON_ARCHIV};
                    wxString rboxName1[] = {wxCAPTION_COLUMN_MR,wxCAPTION_COLUMN_OC,wxCAPTION_COLUMN_GC};     
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_7,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_LVL_7,wxCAPTION_RADIOBOX_LVL,wxDefaultPosition,wxDefaultSize,sizeof(rboxName1)/sizeof(wxString),rboxName1,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_7;
                    break;
                }
                case 8:
                {
                    wxString rboxName[] = {wxCAPTION_BUTTON_INSERT,wxCAPTION_BUTTON_UPDATE,wxCAPTION_BUTTON_DELETE};   
	                hr_local_1->Add(new wxRadioBox(panel_first_line,wxID_ADM_RADIOBOX_TYPE_8,wxCAPTION_RADIOBOX_OPERATION,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_COLS), 1, wxEXPAND,0);
	                panel_first_line->Layout();
	                idRadioBox=wxID_ADM_RADIOBOX_TYPE_8;
	                break;
                }
                default:break;
            }
            (nb_spr->FindWindow(wxID_ADM_PAGE_SPR_1))->Layout();
            wxCommandEvent eventRadioBox; //������� ������ �������
            eventRadioBox.SetId(idRadioBox); //������������� ������������� ��������� � �������� (���� ���������)
            eventRadioBox.SetEventType(wxEVT_COMMAND_RADIOBOX_SELECTED); //������������� ��� �������
            this->ProcessWindowEvent(eventRadioBox);  //���� � ���� ���������� �������
            break;
        }
        default:break;
    }
}
void NotebookAdmin::GhangeRadiobox (wxCommandEvent& event)
{
    vr_local_2->Clear(); //����������� ����� �� ������������
    panel_second_line->DestroyChildren(); //��������� ���� ����� � ������������� ����
    switch (event.GetId()) //��������� id radiobox � ������� ��������� �������
    {
        case wxID_ADM_RADIOBOX_TYPE_0:
        case wxID_ADM_RADIOBOX_GROUP_0: 
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==0)      //���.������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_PROD_GROUP),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ����� �������� �������� ������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==1)      //���.���������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyProdGroupArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyProdGroupArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyProdGroupArray.Item(i).nameProdGroup));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_PROD_GROUP),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� �������� ������");
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_PROD_SUBGROUP),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� �������� ���������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==0)      //���.������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyProdGroupArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyProdGroupArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyProdGroupArray.Item(i).nameProdGroup));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� �������� ������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� �������� ������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==1)      //���.���������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyProdGroupArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyProdGroupArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyProdGroupArray.Item(i).nameProdGroup));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_PROD_GROUP),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� �������� ������");
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� ����������� �������� ���������");
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("������� ����� �������� �������� ���������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==0)      //���.������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyProdGroupArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyProdGroupArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyProdGroupArray.Item(i).nameProdGroup));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_PROD_GROUP),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� �������� ������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetToolTip("������ ����� ������������ ������� �� ��. ������ �����������.");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==1)      //���.���������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyProdGroupArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyProdGroupArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyProdGroupArray.Item(i).nameProdGroup));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_PROD_GROUP),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� �������� ������");
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_PROD_SUBGROUP),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� ��������� �������� �������� ���������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetToolTip("������ ����� ������������ ������� �� ��. ������ �����������.");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            break;
        }
        case wxID_ADM_RADIOBOX_TYPE_1:
        case wxID_ADM_RADIOBOX_GROUP_1: 
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==0)      //��������� ���������� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_JOB),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ����� �������� ��������� ���������� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==1)      //��������� ���������� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_JOB),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ����� �������� ��������� ���������� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==0)      //��������� ���������� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyDolznostArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyDolznostArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyDolznostArray.Item(i).nameDolznost));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� ��������� ���������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� ��������� ���������� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==1)      //��������� ���������� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyPositionSotrArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyPositionSotrArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyPositionSotrArray.Item(i).namePosition));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� ��������� ���������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� ��������� ���������� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==0)      //��������� ���������� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyDolznostArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyDolznostArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyDolznostArray.Item(i).nameDolznost));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� ��������� ���������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetToolTip("������ ����� ������������ ������� �� ��. ������ �����������.");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==1)      //��������� ���������� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyPositionSotrArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyPositionSotrArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyPositionSotrArray.Item(i).namePosition));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� ��������� ���������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetToolTip("������ ����� ������������ ������� �� ��. ������ �����������.");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            break;
        }
        case wxID_ADM_RADIOBOX_TYPE_2: //��������� ��������
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_2))->GetSelection()==0)   //��������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_REZ),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ����� �������� ���������� ��������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_2))->GetSelection()==1)   //��������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyRezProvArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyRezProvArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyRezProvArray.Item(i).nameRezProv));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� ���������� ��������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� ���������� ��������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_2))->GetSelection()==2)   //�������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyRezProvArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyRezProvArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyRezProvArray.Item(i).nameRezProv));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� ���������� ��������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetToolTip("������ ����� ������������ ������� �� ��. ������ �����������.");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            break;
        }
        case wxID_ADM_RADIOBOX_TYPE_3: 
        case wxID_ADM_RADIOBOX_GROUP_3: 
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==0)      //��� ����/������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_TYPE_BRAND),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ����� �������� ���� ����");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==1)      //������������ ����/������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyBrandTypeArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyBrandTypeArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyBrandTypeArray.Item(i).nameBrandType));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_TYPE_BRAND),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_NAME_BRAND),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��� ����");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� ������������ ����/������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==0)      //��� ����/������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyBrandTypeArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyBrandTypeArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyBrandTypeArray.Item(i).nameBrandType));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� ���� ����/������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� ���� ����/������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==1)      //������������ ����/������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyBrandNameArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyBrandNameArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyBrandNameArray.Item(i).nameBrandName));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_TYPE_BRAND),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� ������������ ����/������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� ��� ����/������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("������� ����� �������� ������������ ����/������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetToolTip("��� ���������� ����� �������� ��� ����. ������ ����� ������������");
                       
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==0)      //��� ����/������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyBrandTypeArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyBrandTypeArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyBrandTypeArray.Item(i).nameBrandType));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� ���� ����/������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==1)      //������������ ����/������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyBrandNameArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyBrandNameArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyBrandNameArray.Item(i).nameBrandName));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� ���� ����/������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetToolTip("������ ����� ������������ ������� �� ��. ������ �����������.");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            break;
        }
        case wxID_ADM_RADIOBOX_TYPE_4: 
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_4))->GetSelection()==0)   //�������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_UK),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ����� ������ �� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_4))->GetSelection()==1)   //�������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyUkRfArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyUkRfArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyUkRfArray.Item(i).nameUkRf));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� �� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� �� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_4))->GetSelection()==2)   //������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyUkRfArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyUkRfArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyUkRfArray.Item(i).nameUkRf));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_UK),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� �� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetToolTip("������ ����� ������������ ������� �� ��. ������ �����������.");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            break;
        }
        case wxID_ADM_RADIOBOX_TYPE_5: 
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_5))->GetSelection()==0)   //�������� ���������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_FIO_SOV),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_DATE_ROJD),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_SL_TEL),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ��� ������ ���������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ���� �������� � ������� YYYY-MM-DD");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("������� ����� ��.�������� � ������� 8-888-888-88-88");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_5))->GetSelection()==1)   //�������� ���������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_4 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MySovetnicArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MySovetnicArray.GetCount();++i) //��������� ��������� ������ �������������� 
                {
                    LocArray.Add((MySovetnicArray.Item(i).nameSovetnic));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_OLD_FIO),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_NEW_FIO),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_NEW_TEL),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                hr_loc_4->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_NEW_ROJD),0,wxEXPAND|wxRIGHT,10);
                hr_loc_4->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR3),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� ��� ���������� ������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� ��� ���������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("������� ����� ��������� �������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR3))->SetHint("������� ����� ���� ��������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_4,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_5))->GetSelection()==2)   //������� ���������
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MySovetnicArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MySovetnicArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MySovetnicArray.Item(i).nameSovetnic));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_FIO_SOV),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� ��� �������� �� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetToolTip("������ ����� ������������ ������� �� ��. ������ �����������.");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            break;
        }
        case wxID_ADM_RADIOBOX_TYPE_6: 
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_6))->GetSelection()==0)   //�������� ���������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_SOTRSBGO),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ������ ���������� �� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_6))->GetSelection()==1)   //�������� ���������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyFioSbArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyFioSbArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyFioSbArray.Item(i).nameFioSb));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� ���������� �� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� ���������� �� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_6))->GetSelection()==2)   //������� ���������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyFioSbArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyFioSbArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyFioSbArray.Item(i).nameFioSb));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_SOTRSBGO),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� ���������� �� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            break;
        }
        case wxID_ADM_RADIOBOX_TYPE_7:
        case wxID_ADM_RADIOBOX_LVL_7: 
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==0)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ������������ ������ ������������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();  
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==1)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_OC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� ��� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ������������ ������ ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();    
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==0&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==2)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_OC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_GC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� �����������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� �� ��� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("������� ������������ ������ ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();  
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==0)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� ��� ����������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� ������������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();      
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==1)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� �� ��� ����������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("������� ����� �������� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();   
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==1&&   //��������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==2)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_4 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_OC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                hr_loc_4->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_4->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR3),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� �� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("�������� �� ��� ����������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR3))->SetHint("������� ����� �������� ��");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_4,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();  
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==0)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� ��� ��������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();     
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==1)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_OC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� �� ��� ��������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();   
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==2&&   //�������
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==2)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_OC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_GC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� �� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("�������� �� ��� ��������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();   
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==3&&   //��������� � �����
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==0)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� ��� ��������� � �����");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(new wxCheckBox(panel_second_line,wxID_ADM_CHACKBOX_PR_GR,wxCAPTION_CHECKBOX_FLAG_KASKAD),0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();     
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==3&&   //��������� � �����
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==1)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_OC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� �� ��� ��������� � �����");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(new wxCheckBox(panel_second_line,wxID_ADM_CHACKBOX_PR_GR,wxCAPTION_CHECKBOX_FLAG_KASKAD),0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();   
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==3&&   //��������� � �����
            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==2)        //��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_3 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyMacroregArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyMacroregArray.Item(i).nameMacroreg));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_MR),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_OC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                hr_loc_3->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_GC),0,wxEXPAND|wxRIGHT,10);
                hr_loc_3->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR2),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("�������� �� � �������� �������� ��");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->SetHint("�������� �� ��� ��������� � �����");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_3,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();   
            }
            break;
        }
        case wxID_ADM_RADIOBOX_TYPE_8: 
        {
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_8))->GetSelection()==0)   //�������� ���������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_EVENT),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("������� ����� �������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_8))->GetSelection()==1)   //�������� ���������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxBoxSizer *hr_loc_2 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyHolidayTypeArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyHolidayTypeArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyHolidayTypeArray.Item(i).nameHolidayType));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_OLD_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                hr_loc_2->Add(new wxStaticText(panel_second_line,wxID_ANY,wxSTRING_NEW_VALUE),0,wxEXPAND|wxRIGHT,10);
                hr_loc_2->Add(new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR1),1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ����������� �������� �������");
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->SetHint("������� ����� �������� �������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                vr_local_2->Add(hr_loc_2,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_8))->GetSelection()==2)   //������� ���������� �� ��
            {
                wxBoxSizer *hr_loc_1 = new wxBoxSizer(wxHORIZONTAL);
                wxTextCtrl * textGroup = new wxTextCtrl(panel_second_line,wxID_ADM_TEXTCTRL_PR_GR);
                wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                LocArray.Alloc(MyHolidayTypeArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                for(register int i =0; i<MyHolidayTypeArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                {
                    LocArray.Add((MyHolidayTypeArray.Item(i).nameHolidayType));
                }
                textGroup->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                LocArray.Clear(); //������� ���������� ������� � ����������� ������
                hr_loc_1->Add(new wxStaticText(panel_second_line,wxID_ANY,wxCAPTION_COLUMN_EVENT),0,wxEXPAND|wxRIGHT,10);
                hr_loc_1->Add(textGroup,1,wxEXPAND,0);
                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->SetHint("�������� ��������� �������� �������");
                vr_local_2->Add(hr_loc_1,0,wxEXPAND|wxALL,5);
                panel_second_line->Layout();
            }
            break;
        }
        default:break;
    }
}



void NotebookAdmin::NewFocus(wxChildFocusEvent& event)
{
    switch (idWindowFocus) //��������� ����, ������� ������ �����
    {
        case wxID_ADM_TEXTCTRL_PR_GR:
        {
            if(nb_spr->GetSelection()==0) //������� 1 �������� ��������
            {
            switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()) //���������� ��������� ������� ������� radiobox
            {
                case 1:
                case 2:
                {
                    switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()) //���������� ��������� ������� ������� radiobox
                    {
                        case 1:
                        {
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->Clear();
                            int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
                            wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();          //����������� ���������� �������� ���������� ����
                            str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
                            for(register int i =0; i<MyProdGroupArray.GetCount();++i)       //��������� ���� ������ ���������� � �������
                            {
                                if (!str.compare(MyProdGroupArray.Item(i).nameProdGroup))
                                //{flag=1; str = MyProdGroupArray.Item(i).idProdGroup; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                                {flag=1; str.Clear(); str<<MyProdGroupArray.Item(i).idProdGroup; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                            }
                            if(flag==1)
                            {
                                wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
                                for(register int i =0; i<MyProdNameArray.GetCount();++i)   //��������� ��������� ������ �������������� 
                                {
                                    //if(!str.compare(MyProdNameArray.Item(i).idProdGroup))
                                    if(wxAtoi(str)==MyProdNameArray.Item(i).idProdGroup)
                                    {
                                        LocArray.Add(MyProdNameArray.Item(i).nameProdName);
                                    }
                                }
                                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������                                   
                            }
                            break;
                        }
                        default:break;
                    }
                    break;
                }
                default:break;
            }}
            if(nb_spr->GetSelection()==3) //������� 4 �������� ��������
            {
            switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()) //���������� ��������� ������� ������� radiobox
            {
                case 1:
                {
                    switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()) //���������� ��������� ������� ������� radiobox
                    {
                        case 1:
                        {
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->Clear();
                            int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
                            wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();          //����������� ���������� �������� ���������� ����
                            str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
                            for(register int i =0; i<MyBrandNameArray.GetCount();++i)       //��������� ���� ������ ���������� � �������
                            {
                                if (!str.compare(MyBrandNameArray.Item(i).nameBrandName))
                                //{flag=1; str = MyBrandNameArray.Item(i).idBrandType; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                                {flag=1; str.Clear(); str<<MyBrandNameArray.Item(i).idBrandType; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                            }
                            if(flag==1)
                            {
                                wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
                                for(register int i =0; i<MyBrandTypeArray.GetCount();++i)   //��������� ��������� ������ �������������� 
                                {
                                    
                                    LocArray.Add(MyBrandTypeArray.Item(i).nameBrandType);
                                    //if(!str.compare(MyBrandTypeArray.Item(i).idBrandType))
                                    if(wxAtoi(str)==MyBrandTypeArray.Item(i).idBrandType)  
                                    {
                                        ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->ChangeValue(MyBrandTypeArray.Item(i).nameBrandType); //����� �������� ���� ����
                                    }
                                }
                                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������                                   
                            }
                            break;
                        }
                        default:break;
                    }
                    break;
                }
                default:break;
            }}
            if(nb_spr->GetSelection()==5) //������� 6 �������� ��������
            {
            switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_5))->GetSelection()) //���������� ��������� ������� ������� radiobox
            {
                case 1:
                {
                    ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->Clear();
                    ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->Clear();
                    ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR3))->Clear();                                               
                    wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();          //����������� ���������� �������� ���������� ����
                    str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
                    for(register int i =0; i<MySovetnicArray.GetCount();++i)       //��������� ���� ������ ���������� � �������
                    {
                        if (!str.compare(MySovetnicArray.Item(i).nameSovetnic))
                        {
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->ChangeValue(MySovetnicArray.Item(i).pfoneSovetnic); //����� �������� ���� ����
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR3))->ChangeValue(MySovetnicArray.Item(i).drSovetnic); //����� �������� ���� ����
                            break;
                        }      //���������� �������
                    }
                    break;
                }
                default:break;
            }}
            if(nb_spr->GetSelection()==7) //������� 8 �������� ��������
            {
            switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()) //���������� ��������� ������� ������� radiobox
            {
                case 0: //��������
                { 
                    switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()) //���������� ��������� ������� 2 radiobox
                    {
                        case 2: //��
                        {
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->Clear();
                            int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
                            wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();          //����������� ���������� �������� ���������� ����
                            str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
                            for(register int i =0; i<MyMacroregArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ ����� �������
                            {
                                //if (!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1"))
                                //{flag=1; str = MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                                if (!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1)
                                {flag=1; str.Clear(); str<<MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                            }
                            if(flag==1)
                            {
                                wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
                                for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
                                {
                                    //if(!str.compare(MyTechCentrArray.Item(i).son))
                                    if(wxAtoi(str)==MyTechCentrArray.Item(i).son)
                                    {
                                        for(register int j =0; j<MyOcArray.GetCount();++j)   //��������� ��������� ������ �������������� �������� �����
                                        {
                                            //if((!MyOcArray.Item(j).activOc.compare("1"))&&(!MyTechCentrArray.Item(i).parent.compare(MyOcArray.Item(j).idOc)))
                                            if((MyOcArray.Item(j).activOc==1)&&(MyTechCentrArray.Item(i).parent==MyOcArray.Item(j).idOc))
                                            {
                                                LocArray.Add(MyOcArray.Item(j).nameOc); break;
                                            }
                                        }
                                    }
                                }
                                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������                                   
                            }
                            break;
                        }
                        default:break;
                    }
                    break;
                }
                case 1: //��������
                { 
                    switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()) //���������� ��������� ������� 2 radiobox
                    {
                        case 1: //��
                        case 2: //��
                        {
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->Clear();
                            int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
                            wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();          //����������� ���������� �������� ���������� ����
                            str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
                            for(register int i =0; i<MyMacroregArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ ����� �������
                            {
                                //if (!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1"))
                                //{flag=1; str = MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                                if (!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1)
                                {flag=1; str.Clear(); str<<MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                            }
                            if(flag==1)
                            {
                                wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
                                for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
                                {
                                    //if(!str.compare(MyTechCentrArray.Item(i).son))
                                    if(wxAtoi(str)==MyTechCentrArray.Item(i).son)
                                    {
                                        for(register int j =0; j<MyOcArray.GetCount();++j)   //��������� ��������� ������ �������������� �������� �����
                                        {
                                            //if((!MyOcArray.Item(j).activOc.compare("1"))&&(!MyTechCentrArray.Item(i).parent.compare(MyOcArray.Item(j).idOc)))
                                            if((MyOcArray.Item(j).activOc==1)&&(MyTechCentrArray.Item(i).parent==MyOcArray.Item(j).idOc))
                                            {
                                                LocArray.Add(MyOcArray.Item(j).nameOc); break;
                                            }
                                        }
                                    }
                                }
                                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������                                   
                            }
                            break;
                        }
                        default:break;
                    }
                    break;
                }
                case 2: //�������
                { 
                    switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()) //���������� ��������� ������� 2 radiobox
                    {
                        case 1: //��
                        case 2: //��
                        {
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->Clear();
                            int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
                            wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();          //����������� ���������� �������� ���������� ����
                            str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
                            for(register int i =0; i<MyMacroregArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ ����� �������
                            {
                                //if (!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1"))
                                //{flag=1; str = MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                                if (!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1)
                                {flag=1; str.Clear(); str<<MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                            }
                            if(flag==1)
                            {
                                wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
                                for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
                                {
                                    //if(!str.compare(MyTechCentrArray.Item(i).son))
                                    if(wxAtoi(str)==MyTechCentrArray.Item(i).son)
                                    {
                                        for(register int j =0; j<MyOcArray.GetCount();++j)   //��������� ��������� ������ �������������� �������� �����
                                        {
                                            //if((!MyOcArray.Item(j).activOc.compare("1"))&&(!MyTechCentrArray.Item(i).parent.compare(MyOcArray.Item(j).idOc)))
                                            if((MyOcArray.Item(j).activOc==1)&&(MyTechCentrArray.Item(i).parent==MyOcArray.Item(j).idOc))
                                            {
                                                LocArray.Add(MyOcArray.Item(j).nameOc); break;
                                            }
                                        }
                                    }
                                }
                                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������                                   
                            }
                            break;
                        }
                        default:break;
                    }
                    break;
                }
                case 3: //��������� � �����
                { 
                    switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()) //���������� ��������� ������� 2 radiobox
                    {
                        case 1: //��
                        case 2: //��
                        {
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->Clear();
                            int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
                            wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();          //����������� ���������� �������� ���������� ����
                            str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
                            for(register int i =0; i<MyMacroregArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ ����� �������
                            {
                                //if (!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1"))
                                //{flag=1; str = MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                                if (!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1)
                                {flag=1; str.Clear(); str<<MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                            }
                            if(flag==1)
                            {
                                wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
                                for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
                                {
                                    //if(!str.compare(MyTechCentrArray.Item(i).son))
                                    if(wxAtoi(str)==MyTechCentrArray.Item(i).son)
                                    {
                                        for(register int j =0; j<MyOcArray.GetCount();++j)   //��������� ��������� ������ �������������� �������� �����
                                        {
                                            //if((!MyOcArray.Item(j).activOc.compare("1"))&&(!MyTechCentrArray.Item(i).parent.compare(MyOcArray.Item(j).idOc)))
                                            if((MyOcArray.Item(j).activOc==1)&&(MyTechCentrArray.Item(i).parent==MyOcArray.Item(j).idOc))
                                            {
                                                LocArray.Add(MyOcArray.Item(j).nameOc); break;
                                            }
                                        }
                                    }
                                }
                                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������                                   
                            }
                            break;
                        }
                        default:break;
                    }
                    break;
                }
                default:break;
            }}
            break;
        }
        case wxID_ADM_TEXTCTRL_PR_GR1:
        {
            if(nb_spr->GetSelection()==7) //������� 8 �������� ��������
            {
            switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()) //���������� ��������� ������� ������� radiobox
            {
                case 1: //��������
                case 2: //�������
                case 3: //��������� � �����
                { 
                    switch (((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()) //���������� ��������� ������� 2 radiobox
                    {
                        case 2: //��
                        {
                            ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->Clear();
                            int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
                            wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();          //����������� ���������� �������� ���������� ����
                            str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
                            for(register int i =0; i<MyOcArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ ����� �������
                            {
                                //if (!str.compare(MyOcArray.Item(i).nameOc)&&!MyOcArray.Item(i).activOc.compare("1"))
                                //{flag=1; str = MyOcArray.Item(i).idOc; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                                if (!str.compare(MyOcArray.Item(i).nameOc)&&MyOcArray.Item(i).activOc==1)
                                {flag=1; str.Clear(); str<<MyOcArray.Item(i).idOc; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
                            }
                            if(flag==1)
                            {
                                wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
                                for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
                                {
                                    //if(!str.compare(MyTechCentrArray.Item(i).son))
                                    if(wxAtoi(str)==MyTechCentrArray.Item(i).son)
                                    {
                                        for(register int j =0; j<MyGcArray.GetCount();++j)   //��������� ��������� ������ �������������� �������� �����
                                        {
                                            //if((!MyGcArray.Item(j).activGc.compare("1"))&&(!MyTechCentrArray.Item(i).parent.compare(MyGcArray.Item(j).idGc)))
                                            if((MyGcArray.Item(j).activGc==1)&&(MyTechCentrArray.Item(i).parent==MyGcArray.Item(j).idGc))
                                            {
                                                LocArray.Add(MyGcArray.Item(j).nameGc); break;
                                            }
                                        }
                                    }
                                }
                                ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������                                   
                            }
                            break;
                        }
                        default:break;
                    }
                    break;
                }
                default:break;
            }}
            break;
        }
        default:break;
    }
    idWindowFocus=(event.GetWindow())->GetId();
}

void NotebookAdmin::OnButton (wxCommandEvent &event)
{
    switch (event.GetId())
    {
        case wxID_ADM_PV_BUTTOM_FROM:
        {
            wxComboBox *combobox = (wxComboBox*)panel_privkey->FindWindow(wxID_ADM_PV_COMBOBOX_P1);
            wxListBox *listbox = (wxListBox*)panel_privkey->FindWindow(wxID_ADM_PV_LISTBOX_SP_P2);
            wxString nameLogin, namePrivilege, textMessage;
            int selectCombo=wxNOT_FOUND, selectList=wxNOT_FOUND; //wxNOT_FOUND==-1
            if((selectCombo=combobox->GetSelection())!=wxNOT_FOUND) {nameLogin=combobox->GetString(selectCombo);}
            if((selectList=listbox->GetSelection())!=wxNOT_FOUND) 
            {
                namePrivilege=listbox->GetString(selectList);
                textMessage="����������: "; textMessage<<namePrivilege; textMessage<<"(����� - "; textMessage<<nameLogin; textMessage<<")";
                textMessage<<"\n"; textMessage<<wxQUESTION_DELETE_STR;
                if(wxMessageBox(textMessage,wxATTENTION,wxYES_NO,this)==wxYES)
                {
                    wxString sqlText = wxSqlTextDelConLP;
                    sqlText<<arrayIdReestrPriv.Item(selectList); sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                    else 
                    {
                        listbox->Delete(selectList);
                        int *item = (int *)arrayIdReestrPriv[selectList];
                        arrayIdReestrPriv.RemoveAt(selectList);
                        //delete item;
                    }
                }
            } else {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;}
            break;
        }
        case wxID_ADM_PV_BUTTOM_TO:
        {
            wxComboBox *combobox = (wxComboBox*)panel_privkey->FindWindow(wxID_ADM_PV_COMBOBOX_P1);
            wxListBox *listbox1 = (wxListBox*)panel_privkey->FindWindow(wxID_ADM_PV_LISTBOX_SP_P1);
            wxListBox *listbox2 = (wxListBox*)panel_privkey->FindWindow(wxID_ADM_PV_LISTBOX_SP_P2);
            wxString nameLogin, namePrivilege, textMessage;
            int selectCombo=wxNOT_FOUND, selectList=wxNOT_FOUND, idSotr=0; //wxNOT_FOUND==-1
            if((selectCombo=combobox->GetSelection())!=wxNOT_FOUND) {nameLogin=combobox->GetString(selectCombo);} 
            else {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;}
            if((selectList=listbox1->GetSelection())!=wxNOT_FOUND) 
            {
                namePrivilege=listbox1->GetString(selectList);
                if(listbox2->FindString(namePrivilege)==wxNOT_FOUND)
                {
                    textMessage="�������� "; textMessage<<nameLogin; textMessage<<" ���������� "; textMessage<<namePrivilege; textMessage<<"?";
                    if(wxMessageBox(textMessage,wxATTENTION,wxYES_NO,this)==wxYES)
                    {
                        if(!(listbox1->GetString(selectList)).compare("mr_reg"))
                        {
                            wxArrayString arrSotr;
                            arrSotr.Alloc(MySovetnicArray.GetCount());
                            for(register int j =0; j<MySovetnicArray.GetCount();++j) 
                            {
                                if(MySovetnicArray.Item(j).activSovetnic==1) {arrSotr.Add(MySovetnicArray.Item(j).nameSovetnic); continue;}
                            }
                            wxString nameRegSotr = wxGetSingleChoice("�������� ���������� ���������������� ������� ������ � ������������ � ������������","�������������� ���������",arrSotr, this);
                            arrSotr.Clear();
                            if(!nameRegSotr.IsEmpty())
                            {
                                for(register int j =0; j<MySovetnicArray.GetCount();++j) 
                                {
                                    if(!MySovetnicArray.Item(j).nameSovetnic.compare(nameRegSotr)) {idSotr=MySovetnicArray.Item(j).idSovetnic; break;}
                                }
                                if(idSotr==0) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                            } else {InformationSleep (wxINFO_NOT_SOTR_SB, sec_for_sleep_window_info, this); break;}
                        }
                        wxString sqlText = wxSqlTextInsConLP;
                        sqlText<<arrayIdLogin.Item(selectCombo); sqlText<<wxSqlCommaText;
                        sqlText<<arrayIdPrivilege.Item(selectList); sqlText<<wxSqlCommaText;
                        if(!(listbox1->GetString(selectList)).compare("mr_reg")) {sqlText<<idSotr;} else {sqlText<<wxSQL_DEFAULT;}
                        sqlText<<wxSqlEndRightBracketText;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                        else 
                        {
                            sqlText.Clear();
                            sqlText=wxSqlTextSelConLP; sqlText<<arrayIdLogin.Item(selectCombo);
                            sqlText<<wxSqlTextSelConLP1;
                            sqlText<<arrayIdPrivilege.Item(selectList); sqlText<<wxSqlEndTextOrderByDescI;
                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                            else 
                            {
                                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
                                arrayIdReestrPriv.Add(wxAtoi(row[0]));
                                listbox2->Append(namePrivilege);
                                mysql_free_result(res);
                            }
                        }
                    }
                } else {InformationSleep (wxINFO_CMP_PRIVILEGE, sec_for_sleep_window_info, this); break;}
            } else {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;}
            break;
        }
        case wxID_ADM_PV_BUTTOM_DEL:
        {
            wxComboBox *combobox = (wxComboBox*)panel_privkey->FindWindow(wxID_ADM_PV_COMBOBOX_P1);
            if(combobox->IsTextEmpty()) {InformationSleep (wxINFO_EMPTY_STRING, sec_for_sleep_window_info, this); break;}
            int select = combobox->GetSelection();
            if(select==wxNOT_FOUND) {InformationSleep (wxINFO_NOT_FOUND_LOGIN, sec_for_sleep_window_info, this); break;}
            wxString nameLogin("�����: "); 
            nameLogin<<combobox->GetString(select);
            nameLogin<<"\n"; nameLogin<<wxQUESTION_DELETE_STR;
            if(wxMessageBox(nameLogin,wxATTENTION,wxYES_NO,this)==wxYES)
            {
                wxString sqlText = wxSqlTextDelLogin;
                int id_Login = (arrayIdLogin.Item(select));
                sqlText<<id_Login; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    combobox->Delete(select);
                    int *item = (int*)arrayIdLogin[select];
                    //delete item;
                    arrayIdLogin.RemoveAt(select);
                }
            }
            break;
        }
        case wxID_ADM_PV_BUTTOM_INS:
        {
            wxComboBox *combobox = (wxComboBox*)panel_privkey->FindWindow(wxID_ADM_PV_COMBOBOX_P1);
            wxString str = combobox->GetValue();
            if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_STRING, sec_for_sleep_window_info, this); break;}
            wxString sqlText = wxSqlTextSelLoginCmp;
            sqlText<<str; sqlText<<wxSqlStrongEnd;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
            else 
            {
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
                if(wxAtoi(row[0])!=0) {wxMessageBox(wxMATCH_IS_FOUND,wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;}
                mysql_free_result(res);
            }
            sqlText.Clear();
            sqlText=wxSqlTextInsLogin; sqlText<<str; sqlText<<wxSqlTextStrongEnd;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
            else 
            {
                sqlText.Clear();
                sqlText=wxSqlTextSelLoginCmp1; sqlText<<str; sqlText<<wxSqlStrongEnd;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
                    arrayIdLogin.Add(wxAtoi(row[0]));
                    combobox->Append(row[1]);
                    mysql_free_result(res);
                }
            } 
            break;
        }
        case wxID_ADM_BL_BUTTON_DOP_INF:
        {
            wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
            wxBannerWindow *banner = (wxBannerWindow*)panel_bd->FindWindow(wxID_ADM_BL_BANNER_DOP_INF);
            switch (combobox->GetCurrentSelection())
            {
                case 0: //�����
                {
                    wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP); //��������� �� ��������� �� �������
                    int sel_item = listview->GetFocusedItem(); //���������� ������ � ������� �����
                    if(sel_item==-1) {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;} //������ �� ��������, ������� ��������� ���������
                    int id_reestr_bl = listview->GetItemData(sel_item); //�������� ���� �� ���������� ������ ������ 
                    if(id_reestr_bl==0) {InformationSleep (wxWARNING_NO_DATA, sec_for_sleep_window_info, this); break;}
                    else
                    {
                        wxString sqlText=wxSqlTextSelBlTo;
                        sqlText<<id_reestr_bl; sqlText<<wxSqlEndText;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                        else
                        {
                            MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                            //int num_fields = mysql_num_fields(res); // ���������� �����
                            int num_rows = mysql_num_rows(res); // � ���������� �����.
                            if(num_rows>0)
                            {
                                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                wxString strBunner1, strBunner2, strComm, strRoot;
                                for(register int i =0; i<MyRootInfoArray.GetCount();++i)       //��������� ���� ������ ���������� 
                                {
                                    //if (!MyRootInfoArray.Item(i).idRootInfo.compare(row[2]))
                                    if (MyRootInfoArray.Item(i).idRootInfo==wxAtoi(row[2]))
                                    {strRoot=MyRootInfoArray.Item(i).nameRootInfo; break;}      //���������� �������
                                }
                                strComm=wxSTRING_DOP_INFO; strComm<<wxSTRING_DASH; strComm<<row[3];
                                EditTheLine(strComm, this);
                                strBunner1=wxSTRING_TO; strBunner1<<wxSTRING_DASH; strBunner1<<row[0]; //strBunner1<<wxSTR_NEW;
                                strBunner2=wxSTRING_INN; strBunner2<<wxSTRING_DASH; strBunner2<<row[1]; strBunner2<<wxSTR_NEW;
                                strBunner2<<wxSTRING_ROOT_INFO; strBunner2<<wxSTRING_DASH; strBunner2<<strRoot; strBunner2<<wxSTR_NEW;
                                strBunner2<<strComm;
                                banner->SetText(strBunner1, strBunner2);
                                panel_bd->Layout(); //������ �����������,   ����������� ����
                                this->Refresh(); //�������������� ����                    
                            } else {InformationSleep (wxERROR, sec_for_sleep_window_info, this);}
                            mysql_free_result(res); // ������� ����������
                        }
                    }
                    break;
                }
                case 1: //������
                {
                    wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP); //��������� �� ��������� �� �������
                    int sel_item = listview->GetFocusedItem(); //���������� ������ � ������� �����
                    if(sel_item==-1) {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;} //������ �� ��������, ������� ��������� ���������
                    int id_reestr_bl = listview->GetItemData(sel_item); //�������� ���� �� ���������� ������ ������ 
                    if(id_reestr_bl==0) {InformationSleep (wxWARNING_NO_DATA, sec_for_sleep_window_info, this); break;}
                    else
                    {
                        wxString sqlText=wxSqlTextSelBlFl;
                        sqlText<<id_reestr_bl; sqlText<<wxSqlEndText;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                        else
                        {
                            MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                            //int num_fields = mysql_num_fields(res); // ���������� �����
                            int num_rows = mysql_num_rows(res); // � ���������� �����.
                            if(num_rows>0)
                            {
                                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                wxString strBunner1, strBunner2, strComm, strRoot;
                                for(register int i =0; i<MyRootInfoArray.GetCount();++i)       //��������� ���� ������ ���������� 
                                {
                                    //if (!MyRootInfoArray.Item(i).idRootInfo.compare(row[2]))
                                    if (MyRootInfoArray.Item(i).idRootInfo==wxAtoi(row[2]))
                                    {strRoot=MyRootInfoArray.Item(i).nameRootInfo; break;}      //���������� �������
                                }
                                strComm=wxSTRING_DOP_INFO; strComm<<wxSTRING_DASH; strComm<<row[3];
                                EditTheLine(strComm, this);
                                strBunner1=wxSTRING_FIO; strBunner1<<wxSTRING_DASH; strBunner1<<row[0]; //strBunner<<wxSTR_NEW;
                                strBunner2=wxSTRING_DR; strBunner2<<wxSTRING_DASH; strBunner2<<row[1]; strBunner2<<wxSTR_NEW;
                                strBunner2<<wxSTRING_ROOT_INFO; strBunner2<<wxSTRING_DASH; strBunner2<<strRoot; strBunner2<<wxSTR_NEW;
                                strBunner2<<strComm;
                                banner->SetText(strBunner1, strBunner2);
                                panel_bd->Layout(); //������ �����������,   ����������� ����
                                this->Refresh(); //�������������� ����                    
                            } else {InformationSleep (wxERROR, sec_for_sleep_window_info, this);}
                            mysql_free_result(res); // ������� ����������
                        }
                    }
                    break;
                }
                default:break;
            }
            break;
        }
        case wxID_ADM_BL_BUTTON_DEL:
        {
            wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
            switch (combobox->GetCurrentSelection())
            {
                case 0: //�����
                {
                    wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP); //��������� �� ��������� �� �������
                    int sel_item = listview->GetFocusedItem(); //���������� ������ � ������� �����
                    if(sel_item==-1) {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;} //������ �� ��������, ������� ��������� ���������
                    int id_reestr_bl = listview->GetItemData(sel_item); //�������� ���� �� ���������� ������ ������ 
                    if(id_reestr_bl==0) {InformationSleep (wxWARNING_NO_DATA, sec_for_sleep_window_info, this); break;}
                    else
                    {
                        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
                        {
                            wxString sqlText=wxSqlTextDelBlTo;
                            sqlText<<id_reestr_bl; sqlText<<wxSqlEndText;
                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                            else
                            {
                                listview->DeleteItem(sel_item);
                                for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������             
                            }
                        }
                    }
                    break;
                }
                case 1: //������
                {
                    wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP); //��������� �� ��������� �� �������
                    int sel_item = listview->GetFocusedItem(); //���������� ������ � ������� �����
                    if(sel_item==-1) {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;} //������ �� ��������, ������� ��������� ���������
                    int id_reestr_bl = listview->GetItemData(sel_item); //�������� ���� �� ���������� ������ ������ 
                    if(id_reestr_bl==0) {InformationSleep (wxWARNING_NO_DATA, sec_for_sleep_window_info, this); break;}
                    else
                    {
                        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
                        {
                            wxString sqlText=wxSqlTextDelBlFl;
                            sqlText<<id_reestr_bl; sqlText<<wxSqlEndText;
                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                            else
                            {
                                listview->DeleteItem(sel_item);
                                for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������             
                            }
                        }
                    }
                    break;
                }
                default:break;
            }
            break;
        }
        case wxID_ADM_BL_CANCEL_INS_1:
        {
            wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_INS); //��������� �� �������� ������
            wxWindow *win2 = collpane2->GetPane();
            wxSizer *sz = win2->GetSizer();
            win2->DestroyChildren(); sz->Clear();
            collpane2->Collapse(); //����������� ������
            panel_bd->Layout(); //������ �����������,   ����������� ����
            this->Refresh(); //�������������� ����
            break;
        }
        case wxID_ADM_BL_CANCEL_UPD_1:
        {
            wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_UPD);
            wxWindow *win3 = collpane3->GetPane();
            wxSizer *sz = win3->GetSizer();
            win3->DestroyChildren(); sz->Clear();
            collpane3->Collapse();
            panel_bd->Layout(); //������ �����������,   ����������� ����
            this->Refresh(); //�������������� ����
            break;
        }
        case wxID_ADM_BL_SAVE_UPD_1:
        {
            wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
            switch (combobox->GetCurrentSelection())
            {
                case 0: //�����
                {
                    wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP); //��������� �� ��������� �� �������
                    int sel_item = listview->GetFocusedItem(); //���������� ������ � ������� �����
                    if(sel_item==-1) {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;} //������ �� ��������, ������� ��������� ���������
                    int id_reestr_bl = listview->GetItemData(sel_item); //�������� ���� �� ���������� ������ ������ 
                    if(id_reestr_bl==0) {InformationSleep (wxWARNING_NO_DATA, sec_for_sleep_window_info, this); break;}
                    else
                    {
                        wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_UPD);
                        wxWindow *win3 = collpane3->GetPane();
                        wxString idRoot;
                        wxString strName = ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_1))->GetValue();
                        wxString strInn = ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_3))->GetValue();
                        wxString strRoot = ((wxComboBox*)win3->FindWindow(wxID_ADM_BL_COMBOBOX_UPD_1))->GetValue();
                        wxString strComment = ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_2))->GetValue();
                        if(strName.IsEmpty()||strInn.IsEmpty()||strRoot.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}
                        if(strComment.IsEmpty()) {strComment=wxSQL_DEFAULT;}
                        strName.MakeUpper();
                        for(register int i =0; i<MyRootInfoArray.GetCount();++i)       //��������� ���� ������ ���������� 
                        {
                            if (!strRoot.compare(MyRootInfoArray.Item(i).nameRootInfo))
                            //{idRoot=MyRootInfoArray.Item(i).idRootInfo; break;}      //���������� �������
                            {idRoot<<MyRootInfoArray.Item(i).idRootInfo; break;}      //���������� �������
                        }
                        if(idRoot.IsEmpty()) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
                        wxString sqlText;
                        sqlText=wxSqlTextUpdBlTo;
                        sqlText<<strInn; sqlText<<wxSqlTextUpdBlToSet1; sqlText<<strName;
                        sqlText<<wxSqlTextUpdBlToSet2; sqlText<<idRoot;
                        sqlText<<wxSqlTextUpdBlToSet3;
                        if (!strComment.compare(wxSQL_DEFAULT)) {sqlText<<strComment;}
                        else {sqlText<<wxSqlCharStr; sqlText<<strComment; sqlText<<wxSqlCharStr;}
                        sqlText<<wxSqlTextUpdBlToWhere; sqlText<<id_reestr_bl; sqlText<<wxSqlEndText;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                        else
                        {
                            listview->SetItem(sel_item,0,strName);
                            listview->SetItem(sel_item,1,strInn);
                            for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������             
                        }
                    }
                    break;
                }
                case 1: //������
                {
                    wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP); //��������� �� ��������� �� �������
                    int sel_item = listview->GetFocusedItem(); //���������� ������ � ������� �����
                    if(sel_item==-1) {InformationSleep (wxINFO_NOT_SELECT_STRING, sec_for_sleep_window_info, this); break;} //������ �� ��������, ������� ��������� ���������
                    int id_reestr_bl = listview->GetItemData(sel_item); //�������� ���� �� ���������� ������ ������ 
                    if(id_reestr_bl==0) {InformationSleep (wxWARNING_NO_DATA, sec_for_sleep_window_info, this); break;}
                    else
                    {
                        wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_UPD);
                        wxWindow *win3 = collpane3->GetPane();
                        wxString idRoot;
                        wxString strFio = ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_1))->GetValue();
                        wxString strData = (((wxDatePickerCtrl*)(win3->FindWindow(wxID_ADM_BL_DATECTRL_UPD_1)))->GetValue()).FormatISODate();
                        wxString strRoot = ((wxComboBox*)win3->FindWindow(wxID_ADM_BL_COMBOBOX_UPD_1))->GetValue();
                        wxString strComment = ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_2))->GetValue();
                        if(strFio.IsEmpty()||strData.IsEmpty()||strRoot.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}
                        if(strComment.IsEmpty()) {strComment=wxSQL_DEFAULT;}
                        strFio.MakeUpper();
                        for(register int i =0; i<MyRootInfoArray.GetCount();++i)       //��������� ���� ������ ���������� 
                        {
                            if (!strRoot.compare(MyRootInfoArray.Item(i).nameRootInfo))
                            //{idRoot=MyRootInfoArray.Item(i).idRootInfo; break;}      //���������� �������
                            {idRoot<<MyRootInfoArray.Item(i).idRootInfo; break;}      //���������� �������
                        }
                        if(idRoot.IsEmpty()) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
                        wxString sqlText;
                        sqlText=wxSqlTextUpdBlFl;
                        sqlText<<strFio; sqlText<<wxSqlTextUpdBlFlSet1; sqlText<<strData;
                        sqlText<<wxSqlTextUpdBlFlSet2; sqlText<<idRoot;
                        sqlText<<wxSqlTextUpdBlFlSet3;
                        if (!strComment.compare(wxSQL_DEFAULT)) {sqlText<<strComment;}
                        else {sqlText<<wxSqlCharStr; sqlText<<strComment; sqlText<<wxSqlCharStr;}
                        sqlText<<wxSqlTextUpdBlFlWhere; sqlText<<id_reestr_bl; sqlText<<wxSqlEndText;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                        else
                        {
                            listview->SetItem(sel_item,0,strFio);
                            listview->SetItem(sel_item,1,strData);
                            for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������             
                        }
                    }
                    break;
                }
                default:break;
            }   
            break;
        }
        case wxID_ADM_BL_SAVE_INS_1:
        {
            wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
            switch (combobox->GetCurrentSelection())
            {
                case 0: //�����
                {
                    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_INS);
                    wxWindow *win2 = collpane2->GetPane();
                    wxString idRoot;
                    wxString strName = ((wxTextCtrl*)win2->FindWindow(wxID_ADM_BL_TEXTCTRL_INS_1))->GetValue();
                    wxString strInn = ((wxTextCtrl*)win2->FindWindow(wxID_ADM_BL_TEXTCTRL_INS_3))->GetValue();
                    wxString strRoot = ((wxComboBox*)win2->FindWindow(wxID_ADM_BL_COMBOBOX_INS_1))->GetValue();
                    wxString strComment = ((wxTextCtrl*)win2->FindWindow(wxID_ADM_BL_TEXTCTRL_INS_2))->GetValue();
                    if(strName.IsEmpty()||strInn.IsEmpty()||strRoot.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}
                    if(strComment.IsEmpty()) {strComment=wxSQL_DEFAULT;}
                    strName.MakeUpper();
                    for(register int i =0; i<MyRootInfoArray.GetCount();++i)       //��������� ���� ������ ���������� 
                    {
                        if (!strRoot.compare(MyRootInfoArray.Item(i).nameRootInfo))
                        //{idRoot=MyRootInfoArray.Item(i).idRootInfo; break;}      //���������� �������
                        {idRoot<<MyRootInfoArray.Item(i).idRootInfo; break;}      //���������� �������
                    }
                    if(idRoot.IsEmpty()) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
                    wxString sqlText;
                    sqlText=wxSqlTextInsTo;
                    sqlText<<strInn; sqlText<<wxSqlCommaText; sqlText<<wxSqlCharStr; sqlText<<strName;
                    sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText; sqlText<<idRoot;
                    sqlText<<wxSqlCommaText;
                    if (!strComment.compare(wxSQL_DEFAULT)) {sqlText<<strComment; sqlText<<wxSqlEndRightBracketText;}
                    else {sqlText<<wxSqlCharStr; sqlText<<strComment; sqlText<<wxSqlTextBracketEnd;}
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                    else
                    {
                        sqlText.Clear();
                        sqlText=wxSqlTextSelIdTo; 
                        sqlText<<strInn; sqlText<<wxSqlEndTextOrderByDescI;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                        else
                        {
                            MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                            //int num_fields = mysql_num_fields(res); // ���������� �����
                            int num_rows = mysql_num_rows(res); // � ���������� �����.
                            if(num_rows>0)
                            {
                                wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP);
                                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                wxListItem *f = new wxListItem();
                                f->SetState(wxLIST_STATE_FOCUSED);
                                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                                f->SetColumn(0);
                                f->SetData(wxAtoi(row[0])); //������ ���������� ����
                                f->SetId(0);
                                listview->InsertItem(*f); 
                                delete f;
                                listview->SetItem(0,0,strName);
                                listview->SetItem(0,1,strInn);
                                for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������      
                                //InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this);
                            } else {InformationSleep (wxERROR, sec_for_sleep_window_info, this);}
                            mysql_free_result(res); // ������� ����������
                        } 
                    } 
                    break;
                }
                case 1: //������
                {
                    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_INS);
                    wxWindow *win2 = collpane2->GetPane();
                    wxString idRoot;
                    wxString strFio = ((wxTextCtrl*)win2->FindWindow(wxID_ADM_BL_TEXTCTRL_INS_1))->GetValue();
                    wxString strData = (((wxDatePickerCtrl*)(win2->FindWindow(wxID_ADM_BL_DATECTRL_INS_1)))->GetValue()).FormatISODate();
                    wxString strRoot = ((wxComboBox*)win2->FindWindow(wxID_ADM_BL_COMBOBOX_INS_1))->GetValue();
                    wxString strComment = ((wxTextCtrl*)win2->FindWindow(wxID_ADM_BL_TEXTCTRL_INS_2))->GetValue();
                    if(strFio.IsEmpty()||strData.IsEmpty()||strRoot.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}
                    if(strComment.IsEmpty()) {strComment=wxSQL_DEFAULT;}
                    strFio.MakeUpper();
                    for(register int i =0; i<MyRootInfoArray.GetCount();++i)       //��������� ���� ������ ���������� 
                    {
                        if (!strRoot.compare(MyRootInfoArray.Item(i).nameRootInfo))
                        //{idRoot=MyRootInfoArray.Item(i).idRootInfo; break;}      //���������� �������
                        {idRoot<<MyRootInfoArray.Item(i).idRootInfo; break;}      //���������� �������
                    }
                    if(idRoot.IsEmpty()) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
                    wxString sqlText;
                    sqlText=wxSqlTextInsFl;
                    sqlText<<strFio; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText; sqlText<<wxSqlCharStr;
                    sqlText<<strData; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;
                    sqlText<<idRoot; sqlText<<wxSqlCommaText;
                    if (!strComment.compare(wxSQL_DEFAULT)) {sqlText<<strComment; sqlText<<wxSqlEndRightBracketText;}
                    else {sqlText<<wxSqlCharStr; sqlText<<strComment; sqlText<<wxSqlTextBracketEnd;}
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                    else
                    {
                        sqlText.Clear();
                        sqlText=wxSqlTextSelIdFl; 
                        sqlText<<strFio; sqlText<<wxSqlCharStr; sqlText<<wxSqlAnd; sqlText<<wxSqlTextSelIdFlWhere; 
                        sqlText<<wxSqlCharStr; sqlText<<strData; sqlText<<wxSqlCharStr; sqlText<<wxSqlEndTextOrderByDescI;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                        {
                            MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                            //int num_fields = mysql_num_fields(res); // ���������� �����
                            int num_rows = mysql_num_rows(res); // � ���������� �����.
                            if(num_rows>0)
                            {
                                wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP);
                                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                wxListItem *f = new wxListItem();
                                f->SetState(wxLIST_STATE_FOCUSED);
                                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                                f->SetColumn(0);
                                f->SetData(wxAtoi(row[0])); //������ ���������� ����
                                f->SetId(0);
                                listview->InsertItem(*f); 
                                delete f;
                                listview->SetItem(0,0,strFio);
                                listview->SetItem(0,1,strData);
                                for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������      
                                //InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this);
                            } else {InformationSleep (wxERROR, sec_for_sleep_window_info, this);}
                            mysql_free_result(res); // ������� ����������
                        } 
                    } 
                    break;
                }
                default:break;
            }   
            break;
        }
        case wxID_ADM_BUT_SAVE_R:
        {
            wxString sqlText, strLvl, strAct, strDate, strIdReg;
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_sov==0) {InformationSleep(wxINFO_NOT_SOV,sec_for_sleep_window_info,this); break;}
            wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_REG));
            wxWindow *win1 = collpane1->GetPane();
            wxListView *listviewR = (wxListView*)(win1->FindWindow(wxID_ADM_LISTVIEW_SOV_R));
            wxCollapsiblePane *collpane1_1 = (wxCollapsiblePane*)(win1->FindWindow(wxID_ADM_COLLPANE_SOV_R_1));
            wxWindow *win1_1 = collpane1_1->GetPane();
            wxComboBox* comb = (wxComboBox*)(win1_1->FindWindow(wxID_ADM_COMBOBOX_LVL_R));
            wxString strRegion = ((wxTextCtrl*)win1_1->FindWindow(wxID_ADM_TEXTCTRL_N_R))->GetValue();
            if(strRegion.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
            strRegion.MakeUpper();
            switch (comb->GetSelection())
            {
                /*������������� � ��������� �������� ������ � �������: 1 - ��, 2 - ��, 3 - ��*/
                case 0:
                {
                    strLvl=wxCAPTION_COLUMN_MR;
                    for(register int i =0; i<MyMacroregArray.GetCount();++i)       //��������� ���� ������ ���������� 
                    {
                        //if (!strRegion.compare(MyMacroregArray.Item(i).nameMacroreg)&&(!MyMacroregArray.Item(i).activMacroreg.compare("1")))
                        //{strIdReg=MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������
                        if (!strRegion.compare(MyMacroregArray.Item(i).nameMacroreg)&&(MyMacroregArray.Item(i).activMacroreg==1))
                        {strIdReg<<MyMacroregArray.Item(i).idMacroreg; break;}      //���������� �������
                    }
                    break;
                }
                case 1:
                {
                    strLvl=wxCAPTION_COLUMN_OC;
                    for(register int i =0; i<MyOcArray.GetCount();++i)       //��������� ���� ������ ���������� 
                    {
                        //if (!strRegion.compare(MyOcArray.Item(i).nameOc)&&(!MyOcArray.Item(i).activOc.compare("1")))
                        //{strIdReg=MyOcArray.Item(i).idOc; break;}      //���������� �������
                        if (!strRegion.compare(MyOcArray.Item(i).nameOc)&&(MyOcArray.Item(i).activOc==1))
                        {strIdReg<<MyOcArray.Item(i).idOc; break;}      //���������� �������
                    }
                    break;
                }
                case 2:
                {
                    strLvl=wxCAPTION_COLUMN_GC;
                    for(register int i =0; i<MyGcArray.GetCount();++i)       //��������� ���� ������ ���������� 
                    {
                        //if (!strRegion.compare(MyGcArray.Item(i).nameGc)&&(!MyGcArray.Item(i).activGc.compare("1")))
                        //{strIdReg=MyGcArray.Item(i).idGc; break;}      //���������� �������
                        if (!strRegion.compare(MyGcArray.Item(i).nameGc)&&(MyGcArray.Item(i).activGc==1))
                        {strIdReg<<MyGcArray.Item(i).idGc; break;}      //���������� �������
                    }
                    break;
                }
                default:break;
            }
            if(strIdReg.IsNumber()&&!strIdReg.IsEmpty()) {} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); break;}
            strAct = "1";
            strDate = (wxDateTime::Now()).FormatISODate();
            sqlText<<wxSqlTextInsConnectSAndR;
            sqlText<<strIdReg; sqlText<<wxSqlCommaText;
            sqlText<<id_sov; sqlText<<wxSqlTextInsConnectSAndREnd;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
            listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));
            int item_number = listviewR->GetItemCount();
            wxListItem *f = new wxListItem();
            f->SetState(wxLIST_STATE_FOCUSED);
            f->SetMask(wxLIST_MASK_TEXT);
            f->SetColumn(0);
            f->SetId(item_number);
            f->SetText(strLvl);
            listviewR->InsertItem(*f); 
            listviewR->SetItem(item_number,1,strRegion);
            listviewR->SetItem(item_number,2,strAct);
            listviewR->SetItem(item_number,3,strDate);
            for(register int i=0;i<(listviewR->GetColumnCount());++i) listviewR->SetColumnWidth(i,wxLIST_AUTOSIZE);
            //listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));
            delete f;
            break;
        }
        case wxID_ADM_BUT_CANCEL_R:
        {
            wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_REG));
            wxWindow *win1 = collpane1->GetPane();
            wxListView *listviewR = (wxListView*)(win1->FindWindow(wxID_ADM_LISTVIEW_SOV_R));
            wxCollapsiblePane *collpane1_1 = (wxCollapsiblePane*)(win1->FindWindow(wxID_ADM_COLLPANE_SOV_R_1));
            collpane1_1->Collapse(true); //����������� ������
            panel_sovetnic->Layout();
            break;
        }
        case wxID_ADM_BUT_PLACE_R:
        {
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_REG));
            wxWindow *win1 = collpane1->GetPane();
            wxListView *listviewR = (wxListView*)(win1->FindWindow(wxID_ADM_LISTVIEW_SOV_R));
            int id_reestr = listviewR->GetItemData(listviewR->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_reestr==0) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;}
            wxString sqlText;
            sqlText<<wxSqlTextUpdConnectSAndR2;
            sqlText<<id_reestr; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;}
            wxString strAct="0";
            listviewR->SetItem(listviewR->GetFocusedItem(),2,strAct);
            listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));
            break;
        }
        case wxID_ADM_BUT_EXTRACT_R:
        {
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_REG));
            wxWindow *win1 = collpane1->GetPane();
            wxListView *listviewR = (wxListView*)(win1->FindWindow(wxID_ADM_LISTVIEW_SOV_R));
            int id_reestr = listviewR->GetItemData(listviewR->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_reestr==0) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;}
            wxString sqlText;
            sqlText<<wxSqlTextUpdConnectSAndR1;
            sqlText<<id_reestr; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;}
            wxString strAct="1";
            listviewR->SetItem(listviewR->GetFocusedItem(),2,strAct);
            listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));
            break;
        }
        case wxID_ADM_BUT_DEL_R:
        {
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_REG));
            wxWindow *win1 = collpane1->GetPane();
            wxListView *listviewR = (wxListView*)(win1->FindWindow(wxID_ADM_LISTVIEW_SOV_R));
            int id_reestr = listviewR->GetItemData(listviewR->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_reestr==0) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;}
            wxString sqlText;
            sqlText<<wxSqlTextDelConnectSAndR;
            sqlText<<id_reestr; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;}
            listviewR->DeleteItem(listviewR->GetFocusedItem());
            listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));
            break;
        }
        case wxID_ADM_BUT_CANCEL_D:
        {
            wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_DOLZ));
            wxWindow *win2 = collpane2->GetPane();
            //wxListView *listviewD = (wxListView*)(win2->FindWindow(wxID_ADM_LISTVIEW_SOV_D));
            wxCollapsiblePane *collpane2_1 = (wxCollapsiblePane*)(win2->FindWindow(wxID_ADM_COLLPANE_SOV_D_1));
            collpane2_1->Collapse(true); //����������� ������
            panel_sovetnic->Layout();
            break;
        }
        case wxID_ADM_BUT_CANCEL_D1:
        {
            wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_DOLZ));
            wxWindow *win2 = collpane2->GetPane();
            //wxListView *listviewD = (wxListView*)(win2->FindWindow(wxID_ADM_LISTVIEW_SOV_D));
            wxCollapsiblePane *collpane2_2 = (wxCollapsiblePane*)(win2->FindWindow(wxID_ADM_COLLPANE_SOV_D_2));
            collpane2_2->Collapse(true); //����������� ������
            panel_sovetnic->Layout();
            break;
        }
        case wxID_ADM_BUTTON_HOL_D_1:
        {
            wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_HOL)); //�������� ��������� �� �������� ������
            wxWindow *win3 = collpane3->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxCollapsiblePane *collpane3_1 = (wxCollapsiblePane*)(win3->FindWindow(wxID_ADM_COLLPANE_HOL_INS)); //��������� �� ��������� �������� ������
            collpane3_1->Collapse(true); //����������� ������
            panel_sovetnic->Layout();
            break;
        }
        case wxID_ADM_BUTTON_HOL_D_1_U:
        {
            wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_HOL)); //�������� ��������� �� �������� ������
            wxWindow *win3 = collpane3->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxCollapsiblePane *collpane3_2 = (wxCollapsiblePane*)(win3->FindWindow(wxID_ADM_COLLPANE_HOL_UPD)); //��������� �� ��������� �������� ������
            collpane3_2->Collapse(true); //����������� ������
            panel_sovetnic->Layout();
            break;
        }
        case wxID_ADM_BUTTON_HOL_S_1:
        {
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_sov==0) {InformationSleep(wxINFO_NOT_SOV,sec_for_sleep_window_info,this); break;} //���� ���� �� ������ ������� ��������� � ���, ��� ������ �� �������
            wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_HOL)); //�������� ��������� �� �������� ������
            wxWindow *win3 = collpane3->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxListView *listviewhol = (wxListView*)(win3->FindWindow(wxID_ADM_SOV_LISTVIEW_HOL)); //��������� �� ������� � �����������
            wxCollapsiblePane *collpane3_1 = (wxCollapsiblePane*)(win3->FindWindow(wxID_ADM_COLLPANE_HOL_INS)); //��������� �� ��������� �������� ������
            wxWindow *win3_1 = collpane3_1->GetPane(); //��������� �� ���� ����������� � ��������� �������� ������
            wxTextCtrl* textCtrl = (wxTextCtrl*)(win3_1->FindWindow(wxID_ADM_TEXTCTRL_HOL_EVT));             //��������� �� ��������� ��������
            wxDatePickerCtrl* dateCtrl1 = (wxDatePickerCtrl*)(win3_1->FindWindow(wxID_ADM_DATECTRL_HOL_ON1)); //��������� �� ������� ���������� � �����
            wxDatePickerCtrl* dateCtrl2 = (wxDatePickerCtrl*)(win3_1->FindWindow(wxID_ADM_DATECTRL_HOL_OF2)); //��������� �� ������� ���������� � �����
            wxTextCtrl* textCtrlK = (wxTextCtrl*)(win3_1->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_K));             //��������� �� ��������� ��������
            wxTextCtrl* textCtrlA = (wxTextCtrl*)(win3_1->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_A));             //��������� �� ��������� ��������
            wxString strEvt, idEvt, strDateOn, strDateOff, sqlZamKand, sqlZamAgent, idZamKand, idZamAgent; //����������
            strEvt=textCtrl->GetValue(); //����� � ���������� �������� �� ���������� ���������
            if(strEvt.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); break;} //���� ���������� ������, �� ������� �������������� � ��������� ������
            strEvt.MakeUpper();
            if((dateCtrl1->GetValue()).IsValid()) {strDateOn=(dateCtrl1->GetValue()).FormatISODate();} else {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); break;}//����� � ���������� �������� �� ��.���������� � ����� ���� � ������� ���������� �� ������
            if((dateCtrl2->GetValue()).IsValid()) {strDateOff=(dateCtrl2->GetValue()).FormatISODate();} else {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); break;}//����� � ���������� �������� �� ��.���������� � ����� ���� � ������� ���������� �� ������
            sqlZamKand=textCtrlK->GetValue(); //����� � ���������� �������� �� ���������� ���������
            sqlZamAgent=textCtrlA->GetValue(); //����� � ���������� �������� �� ���������� ���������
            
            for(register int i =0; i<MyHolidayTypeArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!strEvt.compare(MyHolidayTypeArray.Item(i).nameHolidayType))
                //{idEvt=MyHolidayTypeArray.Item(i).idHolidayType; break;}      //���������� �������
                {idEvt<<MyHolidayTypeArray.Item(i).idHolidayType; break;}      //���������� �������
            }
            if(idEvt.IsNumber()) {} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); break;} //���� � ���������� �� �������� �����, �� ����.� ����������� �� ������� ����������
            if(sqlZamKand.IsEmpty()) {idZamKand=wxSQL_DEFAULT;}
            else
            {
                sqlZamKand.MakeUpper();
                for(register int i =0; i<MySovetnicArray.GetCount();++i)       //��������� ���� ������ ���������� 
                {
                    if (!sqlZamKand.compare(MySovetnicArray.Item(i).nameSovetnic))
                    //{idZamKand=MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                    {idZamKand<<MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                }
            }
            if(sqlZamAgent.IsEmpty()) {idZamAgent=wxSQL_DEFAULT;}
            else
            {
                sqlZamAgent.MakeUpper();
                for(register int i =0; i<MySovetnicArray.GetCount();++i)       //��������� ���� ������ ���������� 
                {
                    if (!sqlZamAgent.compare(MySovetnicArray.Item(i).nameSovetnic))
                    //{idZamAgent=MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                    {idZamAgent<<MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                }
            }
            wxString sqlText;
            sqlText<<wxSqlTextInsHolSov;
            sqlText<<id_sov; sqlText<<wxSqlCommaText; sqlText<<wxSqlCharStr; sqlText<<strDateOn; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;
            sqlText<<wxSqlCharStr; sqlText<<strDateOff; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText; sqlText<<idEvt; sqlText<<wxSqlCommaText;
            sqlText<<idZamKand; sqlText<<wxSqlCommaText; sqlText<<idZamAgent; sqlText<<wxSqlEndRightBracketText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
            else {LoadHolidayForSov();}
            break;
        }
        case wxID_ADM_BUTTON_HOL_S_1_U:
        {
            wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_HOL)); //�������� ��������� �� �������� ������
            wxWindow *win3 = collpane3->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxListView *listviewhol = (wxListView*)(win3->FindWindow(wxID_ADM_SOV_LISTVIEW_HOL)); //��������� �� ������� � �����������
            int id_reestr = listviewhol->GetItemData(listviewhol->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_reestr==0) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;} //���� ���� �� ������ ������� ��������� � ���, ��� ������ �� �������
            
            wxCollapsiblePane *collpane3_2 = (wxCollapsiblePane*)(win3->FindWindow(wxID_ADM_COLLPANE_HOL_UPD)); //��������� �� ��������� �������� ������
            wxWindow *win3_2 = collpane3_2->GetPane(); //��������� �� ���� ����������� � ��������� �������� ������
            wxTextCtrl* textCtrl = (wxTextCtrl*)(win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_EVT_U));             //��������� �� ��������� ��������
            wxDatePickerCtrl* dateCtrl1 = (wxDatePickerCtrl*)(win3_2->FindWindow(wxID_ADM_DATECTRL_HOL_ON1_U)); //��������� �� ������� ���������� � �����
            wxDatePickerCtrl* dateCtrl2 = (wxDatePickerCtrl*)(win3_2->FindWindow(wxID_ADM_DATECTRL_HOL_OF2_U)); //��������� �� ������� ���������� � �����
            wxTextCtrl* textCtrlK = (wxTextCtrl*)(win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_K_U));             //��������� �� ��������� ��������
            wxTextCtrl* textCtrlA = (wxTextCtrl*)(win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_A_U));             //��������� �� ��������� ��������
            wxString strEvt, idEvt, strDateOn, strDateOff, sqlZamKand, sqlZamAgent, idZamKand, idZamAgent; //����������
            strEvt=textCtrl->GetValue(); //����� � ���������� �������� �� ���������� ���������
            if(strEvt.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); break;} //���� ���������� ������, �� ������� �������������� � ��������� ������
            strEvt.MakeUpper();
            if((dateCtrl1->GetValue()).IsValid()) {strDateOn=(dateCtrl1->GetValue()).FormatISODate();} else {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); break;}//����� � ���������� �������� �� ��.���������� � ����� ���� � ������� ���������� �� ������
            if((dateCtrl2->GetValue()).IsValid()) {strDateOff=(dateCtrl2->GetValue()).FormatISODate();} else {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); break;}//����� � ���������� �������� �� ��.���������� � ����� ���� � ������� ���������� �� ������
            sqlZamKand=textCtrlK->GetValue(); //����� � ���������� �������� �� ���������� ���������
            sqlZamAgent=textCtrlA->GetValue(); //����� � ���������� �������� �� ���������� ���������
            for(register int i =0; i<MyHolidayTypeArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!strEvt.compare(MyHolidayTypeArray.Item(i).nameHolidayType))
                //{idEvt=MyHolidayTypeArray.Item(i).idHolidayType; break;}      //���������� �������
                {idEvt<<MyHolidayTypeArray.Item(i).idHolidayType; break;}      //���������� �������
            }
            if(idEvt.IsNumber()) {} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); break;} //���� � ���������� �� �������� �����, �� ����.� ����������� �� ������� ����������
            if(sqlZamKand.IsEmpty()||!sqlZamKand.compare("���")) {idZamKand=wxSQL_DEFAULT;}
            else
            {
                sqlZamKand.MakeUpper();
                for(register int i =0; i<MySovetnicArray.GetCount();++i)       //��������� ���� ������ ���������� 
                {
                    if (!sqlZamKand.compare(MySovetnicArray.Item(i).nameSovetnic))
                    //{idZamKand=MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                    {idZamKand<<MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                }
            }
            if(sqlZamAgent.IsEmpty()||!sqlZamAgent.compare("���")) {idZamAgent=wxSQL_DEFAULT;}
            else
            {
                sqlZamAgent.MakeUpper();
                for(register int i =0; i<MySovetnicArray.GetCount();++i)       //��������� ���� ������ ���������� 
                {
                    if (!sqlZamAgent.compare(MySovetnicArray.Item(i).nameSovetnic))
                    //{idZamAgent=MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                    {idZamAgent<<MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                }
            }
            wxString sqlText;
            sqlText<<wxSqlTextUpdHolSov; sqlText<<strDateOn;
            sqlText<<wxSqlTextUpdHolSov1; sqlText<<strDateOff;
            sqlText<<wxSqlTextUpdHolSov2; sqlText<<idEvt;
            sqlText<<wxSqlTextUpdHolSov3; sqlText<<idZamKand;
            sqlText<<wxSqlTextUpdHolSov4; sqlText<<idZamAgent;
            sqlText<<wxSqlTextUpdHolSov5; sqlText<<id_reestr;
            sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
            else {LoadHolidayForSov();}
            break;
        }
        case wxID_ADM_BUTTON_HOL_DEL:
        {
            wxListView *listviewhol = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_SOV_LISTVIEW_HOL);
            int id_reestr = listviewhol->GetItemData(listviewhol->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_reestr==0) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;} //���� ���� �� ������ ������� ��������� � ���, ��� ������ �� �������
            
            wxString sqlText;
            sqlText<<wxSqlTextDelHolSov;
            sqlText<<id_reestr; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
            else
            {
                listviewhol->DeleteItem(listviewhol->GetFocusedItem());
            }
            break;
        }
        case wxID_ADM_BUT_SAVE_D:
        {
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_sov==0) {InformationSleep(wxINFO_NOT_SOV,sec_for_sleep_window_info,this); break;} //���� ���� �� ������ ������� ��������� � ���, ��� ������ �� �������
            wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_DOLZ)); //�������� ��������� �� �������� ������
            wxWindow *win2 = collpane2->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxListView *listviewD = (wxListView*)(win2->FindWindow(wxID_ADM_LISTVIEW_SOV_D)); //��������� �� ������� � �����������
            wxCollapsiblePane *collpane2_1 = (wxCollapsiblePane*)(win2->FindWindow(wxID_ADM_COLLPANE_SOV_D_1)); //��������� �� ��������� �������� ������
            wxWindow *win2_1 = collpane2_1->GetPane(); //��������� �� ���� ����������� � ��������� �������� ������
            wxTextCtrl* textCtrl = (wxTextCtrl*)(win2_1->FindWindow(wxID_ADM_TEXTCTRL_N_D_1));             //��������� �� ��������� ��������
            wxDatePickerCtrl* dateCtrl = (wxDatePickerCtrl*)(win2_1->FindWindow(wxID_ADM_DATECTRL_D_ON_1)); //��������� �� ������� ���������� � �����
            wxString strDolz, strDate, idDolz, sqlText, strAct; //����������
            strDolz=textCtrl->GetValue(); //����� � ���������� �������� �� ���������� ���������
            if((dateCtrl->GetValue()).IsValid()) {strDate=(dateCtrl->GetValue()).FormatISODate();} else {strDate=wxSQL_DEFAULT;}//����� � ���������� �������� �� ��.���������� � ����� ���� � ������� ���������� �� ������
            if(strDolz.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); break;} //���� ���������� ������, �� ������� �������������� � ��������� ������
            strDolz.MakeUpper();
            for(register int i =0; i<MyPositionSotrArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!strDolz.compare(MyPositionSotrArray.Item(i).namePosition))
                //{idDolz=MyPositionSotrArray.Item(i).idPosition; break;}      //���������� �������
                {idDolz<<MyPositionSotrArray.Item(i).idPosition; break;}      //���������� �������
            }
            if(idDolz.IsNumber()&&!idDolz.IsEmpty()) {} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); break;} //���� � ���������� �� �������� �����, �� ����.� ����������� �� ������� ����������
            sqlText<<wxSqlTextInsPositEmpSb;
            sqlText<<id_sov; sqlText<<wxSqlCommaText;
            sqlText<<idDolz; 
            if(!(dateCtrl->GetValue()).IsValid()) {sqlText<<wxSqlCommaText; sqlText<<strDate; sqlText<<wxSqlTextInsPositEmpSbEnd;} //���� ���� ���������� �� �������, �� ����������� sql-������ ��� �������
            else {sqlText<<wxSqlRightCaw; sqlText<<strDate; sqlText<<wxSqlTextInsPositEmpSbEnd1;} //���� ���� ���������� �������, �� ����������� ������ � ���������
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
            listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));

            int item_number = listviewD->GetItemCount();
            wxListItem *f = new wxListItem();
            f->SetState(wxLIST_STATE_FOCUSED);
            f->SetMask(wxLIST_MASK_TEXT);
            f->SetColumn(0);
            f->SetId(item_number);
            strDolz.Capitalize();
            f->SetText(strDolz);
            strAct="1";
            listviewD->InsertItem(*f); 
            listviewD->SetItem(item_number,1,strAct);
            if((dateCtrl->GetValue()).IsValid()) {listviewD->SetItem(item_number,2,strDate);}
            for(register int i=0;i<(listviewD->GetColumnCount());++i) listviewD->SetColumnWidth(i,wxLIST_AUTOSIZE);
            delete f;
            break;
        }
        case wxID_ADM_BUT_SAVE_D1:
        {
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_sov==0) {InformationSleep(wxINFO_NOT_SOV,sec_for_sleep_window_info,this); break;} //���� ���� �� ������ ������� ��������� � ���, ��� ������ �� �������
            wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_DOLZ)); //�������� ��������� �� �������� ������
            wxWindow *win2 = collpane2->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxListView *listviewD = (wxListView*)(win2->FindWindow(wxID_ADM_LISTVIEW_SOV_D)); //��������� �� ������� � �����������
            int id_reestr = listviewD->GetItemData(listviewD->GetFocusedItem()); //�������� ���� ������ � ������� � �������� ����������
            if(id_reestr==0) {InformationSleep(wxINFO_NOT_DOLZ_SOV,sec_for_sleep_window_info,this); break;}
            wxCollapsiblePane *collpane2_2 = (wxCollapsiblePane*)(win2->FindWindow(wxID_ADM_COLLPANE_SOV_D_2)); //��������� �� ��������� �������� ������
            wxWindow *win2_2 = collpane2_2->GetPane(); //��������� �� ���� ����������� � ��������� �������� ������
            wxString strDolz, idDolz, strDateOn, strDateOff, strAct;
            wxTextCtrl* textCtrl = (wxTextCtrl*)(win2_2->FindWindow(wxID_ADM_TEXTCTRL_N_D_2));             //��������� �� ��������� ��������
            wxDatePickerCtrl* dateCtrl1 = (wxDatePickerCtrl*)(win2_2->FindWindow(wxID_ADM_DATECTRL_D_ON_2)); //��������� �� ������� ���������� � �����
            wxDatePickerCtrl* dateCtrl2 = (wxDatePickerCtrl*)(win2_2->FindWindow(wxID_ADM_DATECTRL_D_OF_2)); //��������� �� ������� ���������� � �����
            int ar = ((wxCheckBox*)(win2_2->FindWindow(wxID_ADM_CHECK_D_1)))->GetValue();
            strDolz=textCtrl->GetValue();
            strDolz.MakeUpper();
            for(register int i =0; i<MyPositionSotrArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!strDolz.compare(MyPositionSotrArray.Item(i).namePosition))
                //{idDolz=MyPositionSotrArray.Item(i).idPosition; break;}      //���������� �������
                {idDolz<<MyPositionSotrArray.Item(i).idPosition; break;}      //���������� �������
            }
            if(idDolz.IsNumber()&&!idDolz.IsEmpty()) {} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); break;} //���� � ���������� �� �������� �����, �� ����.� ����������� �� ������� ����������
            if((dateCtrl1->GetValue()).IsValid()) {strDateOn=(dateCtrl1->GetValue()).FormatISODate();} else {strDateOn=wxSQL_DEFAULT;}//����� � ���������� �������� �� ��.���������� � ����� ���� � ������� ���������� �� ������
            if((dateCtrl2->GetValue()).IsValid()) {strDateOff=(dateCtrl2->GetValue()).FormatISODate();} else {strDateOff=wxSQL_DEFAULT;}//����� � ���������� �������� �� ��.���������� � ����� ���� � ������� ���������� �� ������
            if(ar==0) {strAct="1";} else {strAct="0";}
            wxString sqlText;
            sqlText<<wxSqlTextUpdPositEmpSb; sqlText<<idDolz;
            if((dateCtrl1->GetValue()).IsValid()) 
            {
                sqlText<<wxSqlTextUpdPositEmpSbSet1_2; sqlText<<strDateOn;
                if((dateCtrl2->GetValue()).IsValid())
                {
                    sqlText<<wxSqlTextUpdPositEmpSbSet2_4; sqlText<<strDateOff;
                    sqlText<<wxSqlTextUpdPositEmpSbSet3_2; sqlText<<strAct;
                }
                else
                {
                    sqlText<<wxSqlTextUpdPositEmpSbSet2_3; sqlText<<strDateOff;
                    sqlText<<wxSqlTextUpdPositEmpSbSet3_1; sqlText<<strAct;
                }
            } 
            else 
            {
                sqlText<<wxSqlTextUpdPositEmpSbSet1_1; sqlText<<strDateOn;
                if((dateCtrl2->GetValue()).IsValid())
                {
                    sqlText<<wxSqlTextUpdPositEmpSbSet2_2; sqlText<<strDateOff;
                    sqlText<<wxSqlTextUpdPositEmpSbSet3_2; sqlText<<strAct;
                }
                else
                {
                    sqlText<<wxSqlTextUpdPositEmpSbSet2_1; sqlText<<strDateOff;
                    sqlText<<wxSqlTextUpdPositEmpSbSet3_1; sqlText<<strAct;
                }
            }
            sqlText<<wxSqlTextUpdPositEmpSbWhere; sqlText<<id_reestr; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
            listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));
            int item_number = listviewD->GetFocusedItem();
            strDolz.Capitalize();
            listviewD->SetItem(item_number,0,strDolz);
            listviewD->SetItem(item_number,1,strAct);
            if((dateCtrl1->GetValue()).IsValid()) {listviewD->SetItem(item_number,2,strDateOn);}
            if((dateCtrl2->GetValue()).IsValid()) {listviewD->SetItem(item_number,3,strDateOff);}
            for(register int i=0;i<(listviewD->GetColumnCount());++i) listviewD->SetColumnWidth(i,wxLIST_AUTOSIZE);
            break;
        }
        case wxID_ADM_BUT_DEL_D:
        {
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_sov==0) {InformationSleep(wxINFO_NOT_SOV,sec_for_sleep_window_info,this); break;} //���� ���� �� ������ ������� ��������� � ���, ��� ������ �� �������
            wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_DOLZ)); //�������� ��������� �� �������� ������
            wxWindow *win2 = collpane2->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxListView *listviewD = (wxListView*)(win2->FindWindow(wxID_ADM_LISTVIEW_SOV_D)); //��������� �� ������� � �����������
            int id_reestr = listviewD->GetItemData(listviewD->GetFocusedItem()); //�������� ���� ������ � ������� � �������� ����������
            if(id_reestr==0) {InformationSleep(wxINFO_NOT_DOLZ_SOV,sec_for_sleep_window_info,this); break;}
            wxString sqlText;
            sqlText<<wxSqlTextDelPositEmpSb;
            sqlText<<id_reestr; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
            listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));
            listviewD->DeleteItem(listviewD->GetFocusedItem());
            break;
        }
        case wxID_ADM_BUTTON_SOV_UPD_PD:
        {
            wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
            int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
            if(id_sov==0) {InformationSleep(wxINFO_NOT_SOV,sec_for_sleep_window_info,this); break;}
            wxPropertyGrid *pD = (wxPropertyGrid*)panel_sovetnic->FindWindow(wxID_ADM_PROPERTYGRID_SOV); //��������� �� ����� ������� 
            wxPGProperty *pgp1 = pD->GetProperty(wxString("pd")); //��������� �� ��������� ����� �������
            if(pgp1) //��������� �� ��������� �� ������
            {
                wxPGProperty *pgp1_1 = pgp1->GetPropertyByName("fio"); //�������� ��������� �� ������ ��������
                wxDateProperty *pgp1_2 = (wxDateProperty*)pgp1->GetPropertyByName("dr");
                wxPGProperty *pgp1_3 = pgp1->GetPropertyByName("tel");
                wxDateProperty *pgp1_4 = (wxDateProperty*)pgp1->GetPropertyByName("dete_open");
                wxDateProperty *pgp1_5 = (wxDateProperty*)pgp1->GetPropertyByName("date_close");
                wxBoolProperty *pgp1_6 = (wxBoolProperty*)pgp1->GetPropertyByName("activ");
                if(pgp1_1&&pgp1_2&&pgp1_3&&pgp1_4&&pgp1_5&&pgp1_6) //��������� ��, ��� ��������� �� ������
                {
                    wxString strFio = pgp1_1->GetValueAsString();
                    wxString strDr = pgp1_2->GetValueAsString();
                    wxString strTel = pgp1_3->GetValueAsString();
                    wxString strDateOp = pgp1_4->GetValueAsString();
                    wxString strDateCl = pgp1_5->GetValueAsString();
                    wxString strActiv = pgp1_6->GetValueAsString();
                    if(strFio.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;} //���� ��� ������ -> ���������� ���������
                    strFio.MakeUpper();
                    if(strDr.IsEmpty()||!strDr.MakeUpper().compare("INVALID")) {strDr=wxSQL_DEFAULT;} else {strDr = (pgp1_2->GetDateValue()).FormatISODate();} //���� ���� � ����� ������ ��� �������� �������� Invalid, �� ����������� ���������� �������� DEFAULT, � ��������� ������ �������� �������� �������� � ������� yyyy-mm-dd � ����������� ����������
                    if(strDateOp.IsEmpty()||!strDateOp.MakeUpper().compare("INVALID")) {strDateOp=wxSQL_DEFAULT;} else {strDateOp = (pgp1_4->GetDateValue()).FormatISODate();}
                    if(strDateCl.IsEmpty()||!strDateCl.MakeUpper().compare("INVALID")) {strDateCl=wxSQL_DEFAULT;} else {strDateCl = (pgp1_5->GetDateValue()).FormatISODate();}
                    if(!strActiv.MakeUpper().compare("TRUE")) {strActiv="1";} else {strActiv="0";}
                    wxString sqlText;
                    sqlText<<wxSqlTextUpdSov;
                    if(!strDr.compare(wxSQL_DEFAULT)) 
                    {
                        sqlText<<wxSqlTextUpdSovSet1_1; sqlText<<strDr;
                        sqlText<<wxSqlTextUpdSovSet2_1; sqlText<<strTel;
                    } 
                    else 
                    {
                        sqlText<<wxSqlTextUpdSovSet1; sqlText<<strDr;
                        sqlText<<wxSqlTextUpdSovSet2; sqlText<<strTel;
                    }
                    
                    sqlText<<wxSqlTextUpdSovSet3; sqlText<<strFio;
                    if(!strDateOp.compare(wxSQL_DEFAULT)) 
                    {
                        sqlText<<wxSqlTextUpdSovSet4_1; sqlText<<strDateOp;
                        if(!strDateCl.compare(wxSQL_DEFAULT)) 
                        {
                            sqlText<<wxSqlTextUpdSovSet5_1; sqlText<<strDateCl; sqlText<<wxSqlTextUpdSovSet6_1; sqlText<<strActiv; sqlText<<wxSqlTextUpdSovWhere_1; sqlText<<id_sov;
                        }
                        else {sqlText<<wxSqlTextUpdSovSet5_2; sqlText<<strDateCl; sqlText<<wxSqlTextUpdSovSet6; sqlText<<strActiv; sqlText<<wxSqlTextUpdSovWhere_1; sqlText<<id_sov;}
                    }
                    else
                    {
                        sqlText<<wxSqlTextUpdSovSet4; sqlText<<strDateOp;
                        if(!strDateCl.compare(wxSQL_DEFAULT)) 
                        {
                            sqlText<<wxSqlTextUpdSovSet5_3; sqlText<<strDateCl; sqlText<<wxSqlTextUpdSovSet6_1; sqlText<<strActiv; sqlText<<wxSqlTextUpdSovWhere_1; sqlText<<id_sov;
                        }
                        else {sqlText<<wxSqlTextUpdSovSet5; sqlText<<strDateCl;  sqlText<<wxSqlTextUpdSovSet6; sqlText<<strActiv; sqlText<<wxSqlTextUpdSovWhere_1; sqlText<<id_sov;}
                    }
                    sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                    listview->SetItemTextColour(listview->GetFocusedItem(),(*wxRED));
                }   
            }
            break;
        }
        case wxID_OK:
        {
            switch (nb->GetSelection())
            {
                case 0: //������� 1 �������� ��������� ��������
                {
                    switch (nb_spr->GetSelection())
                    {
                        case 0: //������� 1 �������� �������� - �����������
                        {
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==0)      //���.������
                            {
                                wxString sqlText, str; //��������� ����������
                                str  = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue(); //��������� �������� �� �������� � ����������
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;} //�������� �� ������ ��������
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //�������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelAssortiMain; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK);
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsAssortiMain;
                                        sqlText<<str; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==1)      //���.���������
                            {
                                wxString sqlText, str_main, str_submain, idMain; //��������� ����������
                                str_main = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue(); //��������� �������� �� �������� � ����������
                                str_submain = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue(); //��������� �������� �� �������� � ����������
                                if(str_main.IsEmpty()||str_submain.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;} //��������� ������ ��������
                                str_main.MakeUpper(); str_submain.MakeUpper(); //�������� � �������� ��������
                                str_submain.Trim(true); str_submain.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyProdGroupArray.GetCount();++i) //���� �� ����� id �������� �� ����������� ���� �������
                                {
                                    if(!str_main.compare(MyProdGroupArray.Item(i).nameProdGroup)) 
                                    //{idMain=MyProdGroupArray.Item(i).idProdGroup; break;}
                                    {idMain<<MyProdGroupArray.Item(i).idProdGroup; break;}
                                }
                                if(idMain.IsEmpty()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;} //��������� ������ ��������
                                
                                sqlText=wxSqlTextSelAssortiSubMain; sqlText<<str_submain; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK);
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsAssortiSubMain;
                                        sqlText<<str_main; sqlText<<wxSqlRightCaw;
                                        sqlText<<str_submain; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==0)      //���.������
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyProdGroupArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyProdGroupArray.Item(i).nameProdGroup)) 
                                    //{str_old=MyProdGroupArray.Item(i).idProdGroup; break;}
                                    {str_old.Clear(); str_old<<MyProdGroupArray.Item(i).idProdGroup; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdAssortiMain;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdAssortiMainWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==1)      //���.���������
                            {
                                wxString sqlText;
                                wxString str_main = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()||str_main.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); str_main.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyProdGroupArray.GetCount();++i) 
                                {
                                    if(!str_main.compare(MyProdGroupArray.Item(i).nameProdGroup)) 
                                    //{str_main=MyProdGroupArray.Item(i).idProdGroup; break;}
                                    {str_main.Clear(); str_main<<MyProdGroupArray.Item(i).idProdGroup; break;}
                                }
                                if(!str_main.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                for(register int i =0; i<MyProdNameArray.GetCount();++i) 
                                {
                                    //if(!str_old.compare(MyProdNameArray.Item(i).nameProdName)&&!str_main.compare(MyProdNameArray.Item(i).idProdGroup)) {str_old=MyProdNameArray.Item(i).idProdName; break;}
                                    if(!str_old.compare(MyProdNameArray.Item(i).nameProdName)&&wxAtoi(str_main)==MyProdNameArray.Item(i).idProdGroup) {str_old.Clear(); str_old<<MyProdNameArray.Item(i).idProdName; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdAssortiSubMain;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdAssortiSubMainWhere1;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==0)      //���.������
                            {
                                wxString sqlText;
                                wxString str_main = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str_main.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_main.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyProdGroupArray.GetCount();++i) 
                                {
                                    if(!str_main.compare(MyProdGroupArray.Item(i).nameProdGroup)) 
                                    //{str_main=MyProdGroupArray.Item(i).idProdGroup; break;}
                                    {str_main.Clear(); str_main<<MyProdGroupArray.Item(i).idProdGroup; break;}
                                }
                                if(!str_main.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelAssortiMain;
                                sqlText<<str_main; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_0))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_0))->GetSelection()==1)      //���.���������
                            {
                                wxString sqlText;
                                wxString str_main = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_submain = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_submain.IsEmpty()||str_main.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_submain.MakeUpper(); str_main.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyProdGroupArray.GetCount();++i) 
                                {
                                    if(!str_main.compare(MyProdGroupArray.Item(i).nameProdGroup)) 
                                    //{str_main=MyProdGroupArray.Item(i).idProdGroup; break;}
                                    {str_main.Clear(); str_main<<MyProdGroupArray.Item(i).idProdGroup; break;}
                                }
                                if(!str_main.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                for(register int i =0; i<MyProdNameArray.GetCount();++i) 
                                {
                                    //if(!str_submain.compare(MyProdNameArray.Item(i).nameProdName)&&!str_main.compare(MyProdNameArray.Item(i).idProdGroup)) {str_submain=MyProdNameArray.Item(i).idProdName; break;}
                                    if(!str_submain.compare(MyProdNameArray.Item(i).nameProdName)&&wxAtoi(str_main)==MyProdNameArray.Item(i).idProdGroup) {str_submain.Clear(); str_submain<<MyProdNameArray.Item(i).idProdName; break;}
                                }
                                if(!str_submain.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelAssortiSubMain;
                                sqlText<<str_submain; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            break;
                        }
                        case 1: //������� 2 �������� �������� - �����������
                        {
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==0)      //��������� ���������� ��
                            {
                                wxString sqlText, str; //��������� ����������
                                str  = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue(); //��������� �������� �� �������� � ����������
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;} //��������� ������ ��������
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelDolzAgent; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsDolzAgent;
                                        sqlText<<str; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==1)      //��������� ���������� ��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelDolzSotrSb; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsDolzSotrSb;
                                        sqlText<<str; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==0)      //��������� ���������� ��
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyDolznostArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyDolznostArray.Item(i).nameDolznost)) 
                                    //{str_old=MyDolznostArray.Item(i).idDolznost; break;}
                                    {str_old.Clear(); str_old<<MyDolznostArray.Item(i).idDolznost; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdDolzAgent;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdDolzAgentWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==1)      //��������� ���������� ��
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyPositionSotrArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyPositionSotrArray.Item(i).namePosition)) 
                                    //{str_old=MyPositionSotrArray.Item(i).idPosition; break;}
                                    {str_old.Clear(); str_old<<MyPositionSotrArray.Item(i).idPosition; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdDolzSotrSb;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdDolzSotrSbWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==0)      //��������� ���������� ��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyDolznostArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyDolznostArray.Item(i).nameDolznost)) 
                                    //{str=MyDolznostArray.Item(i).idDolznost; break;}
                                    {str.Clear(); str<<MyDolznostArray.Item(i).idDolznost; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelDolzAgent;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_1))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_1))->GetSelection()==1)      //��������� ���������� ��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyPositionSotrArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyPositionSotrArray.Item(i).namePosition)) 
                                    //{str=MyPositionSotrArray.Item(i).idPosition; break;}
                                    {str.Clear(); str<<MyPositionSotrArray.Item(i).idPosition; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelDolzSotrSb;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            break;
                        }
                        case 2: //������� 3 �������� �������� - �����������
                        {
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_2))->GetSelection()==0)   //�������� ���������� ��������
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelRezProv; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsRezProv;
                                        sqlText<<str; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_2))->GetSelection()==1)   //�������� ���������� ��������
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyRezProvArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyRezProvArray.Item(i).nameRezProv)) 
                                    //{str_old=MyRezProvArray.Item(i).idRezProv; break;}
                                    {str_old.Clear(); str_old<<MyRezProvArray.Item(i).idRezProv; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdRezProv;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdRezProvWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_2))->GetSelection()==2)   //������� ���������� ��������
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyRezProvArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyRezProvArray.Item(i).nameRezProv)) 
                                    //{str=MyRezProvArray.Item(i).idRezProv; break;}
                                    {str.Clear(); str<<MyRezProvArray.Item(i).idRezProv; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelRezProv;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            break;
                        }
                        case 3: //������� 4 �������� �������� - �����������
                        {
                            
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==0)      //��� ����/������
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelTypeNet; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsTypeNet;
                                        sqlText<<str; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==1)      //������������ ����/������
                            {
                                wxString sqlText, str_type, idTypeNet, str;
                                str_type  = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                str  = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_type.IsEmpty()||str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); str_type.MakeUpper();  //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyBrandTypeArray.GetCount();++i) 
                                {
                                    if(!str_type.compare(MyBrandTypeArray.Item(i).nameBrandType)) 
                                    //{idTypeNet=MyBrandTypeArray.Item(i).idBrandType; break;}
                                    {idTypeNet.Clear(); idTypeNet<<MyBrandTypeArray.Item(i).idBrandType; break;}
                                }
                                if(idTypeNet.IsEmpty()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                
                                sqlText=wxSqlTextSelNameNet; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsNameNet;
                                        sqlText<<str; sqlText<<wxSqlLeftCaw;
                                        sqlText<<idTypeNet; sqlText<<wxSqlEndRightBracketText;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==0)      //��� ����/������
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyBrandTypeArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyBrandTypeArray.Item(i).nameBrandType)) 
                                    //{str_old=MyBrandTypeArray.Item(i).idBrandType; break;}
                                    {str_old.Clear(); str_old<<MyBrandTypeArray.Item(i).idBrandType; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdTypeNet;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdTypeNetWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==1)      //������������ ����/������
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_newType = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                wxString str_newName = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                if(str_old.IsEmpty()||str_newType.IsEmpty()||str_newName.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_newType.MakeUpper(); str_newName.MakeUpper(); //�������� � �������� ��������
                                str_newName.Trim(true); str_newName.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyBrandTypeArray.GetCount();++i) 
                                {
                                    if(!str_newType.compare(MyBrandTypeArray.Item(i).nameBrandType)) 
                                    //{str_newType=MyBrandTypeArray.Item(i).idBrandType; break;}
                                    {str_newType.Clear(); str_newType<<MyBrandTypeArray.Item(i).idBrandType; break;}
                                }
                                if(!str_newType.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                for(register int i =0; i<MyBrandNameArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyBrandNameArray.Item(i).nameBrandName)) 
                                    //{str_old=MyBrandNameArray.Item(i).idBrandName; break;}
                                    {str_old.Clear(); str_old<<MyBrandNameArray.Item(i).idBrandName; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                
                                sqlText<<wxSqlTextUpdNameNet;
                                sqlText<<str_newName; sqlText<<wxSqlTextUpdNameNetSet;
                                sqlText<<str_newType; sqlText<<wxSqlTextUpdNameNetWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==0)      //��� ����/������
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyBrandTypeArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyBrandTypeArray.Item(i).nameBrandType)) 
                                    //{str=MyBrandTypeArray.Item(i).idBrandType; break;}
                                    {str.Clear(); str<<MyBrandTypeArray.Item(i).idBrandType; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelTypeNet;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_3))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_GROUP_3))->GetSelection()==1)      //������������ ����/������
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyBrandNameArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyBrandNameArray.Item(i).nameBrandName)) 
                                    //{str=MyBrandNameArray.Item(i).idBrandName; break;}
                                    {str.Clear(); str<<MyBrandNameArray.Item(i).idBrandName; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelNameNet;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            break;
                        }
                        case 4: //������� 5 �������� �������� - �����������
                        {
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_4))->GetSelection()==0)   //�������� �� ��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelUk; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsUk;
                                        sqlText<<str; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_4))->GetSelection()==1)   //�������� �� ��
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyUkRfArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyUkRfArray.Item(i).nameUkRf)) 
                                    //{str_old=MyUkRfArray.Item(i).idUkRf; break;}
                                    {str_old.Clear(); str_old<<MyUkRfArray.Item(i).idUkRf; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdUk;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdUkWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_4))->GetSelection()==2)   //������� �� ��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyUkRfArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyUkRfArray.Item(i).nameUkRf)) 
                                    //{str=MyUkRfArray.Item(i).idUkRf; break;}
                                    {str.Clear(); str<<MyUkRfArray.Item(i).idUkRf; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelUk;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            break;
                        }
                        case 5: //������� 6 �������� �������� - �����������
                        {
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_5))->GetSelection()==0)   //�������� ���������
                            {
                                wxString sqlText;
                                wxString str_fio = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_rojd = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                wxString str_pfone = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                if(str_fio.IsEmpty()||str_rojd.IsEmpty()||str_pfone.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_fio.MakeUpper(); //�������� � �������� ��������
                                str_fio.Trim(true); str_fio.Trim(false); //������� ���������� ������� ������ � �����
                                str_rojd.Trim(true); str_rojd.Trim(false); //������� ���������� ������� ������ � �����
                                str_pfone.Trim(true); str_pfone.Trim(false); //������� ���������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelSov; sqlText<<str_fio; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsSov;
                                        sqlText<<str_fio; sqlText<<wxSqlBothCaw;
                                        sqlText<<str_rojd; sqlText<<wxSqlBothCaw;
                                        sqlText<<str_pfone; sqlText<<wxSqlCawNumberOneEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_5))->GetSelection()==1)   //�������� ���������
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                wxString str_pfone = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                wxString str_rojd = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR3))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()||str_pfone.IsEmpty()||str_rojd.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                str_pfone.Trim(true); str_pfone.Trim(false); //������� ���������� ������� ������ � �����
                                str_rojd.Trim(true); str_rojd.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MySovetnicArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MySovetnicArray.Item(i).nameSovetnic)) 
                                    //{str_old=MySovetnicArray.Item(i).idSovetnic; break;}
                                    {str_old.Clear(); str_old<<MySovetnicArray.Item(i).idSovetnic; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdSov; sqlText<<wxSqlTextUpdSovSet1;
                                sqlText<<str_rojd; sqlText<<wxSqlTextUpdSovSet2;
                                sqlText<<str_pfone; sqlText<<wxSqlTextUpdSovSet3;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdSovWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_5))->GetSelection()==2)   //������� ���������
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MySovetnicArray.GetCount();++i) 
                                {
                                    if(!str.compare(MySovetnicArray.Item(i).nameSovetnic)) 
                                    //{str=MySovetnicArray.Item(i).idSovetnic; break;}
                                    {str.Clear(); str<<MySovetnicArray.Item(i).idSovetnic; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelSov;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            break;
                        }
                        case 6: //������� 7 �������� �������� - �����������
                        {
                            
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_6))->GetSelection()==0)   //�������� ���������� �� ��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                
                                
                                sqlText=wxSqlTextSelSbGo; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsSbGo;
                                        sqlText<<str; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_6))->GetSelection()==1)   //�������� ���������� �� ��
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyFioSbArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyFioSbArray.Item(i).nameFioSb)) 
                                    //{str_old=MyFioSbArray.Item(i).idFioSb; break;}
                                    {str_old.Clear(); str_old<<MyFioSbArray.Item(i).idFioSb; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdSbGo;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdSbGoWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_6))->GetSelection()==2)   //������� ���������� �� ��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyFioSbArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyFioSbArray.Item(i).nameFioSb)) 
                                    //{str=MyFioSbArray.Item(i).idFioSb; break;}
                                    {str.Clear(); str<<MyFioSbArray.Item(i).idFioSb; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelSbGo;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            break;
                        }
                        case 7: //������� 8 �������� �������� - �����������
                        {
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==0)        //��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelMr; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsRegion;
                                        sqlText<<str; sqlText<<"\" ,1 ,1) ;";
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break; 
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==1)        //��
                            {
                                wxString sqlText, str_mr, idMr, str_oc, idOc;
                                str_mr = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                str_oc = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_mr.IsEmpty()||str_oc.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_mr.MakeUpper(); str_oc.MakeUpper(); //�������� � �������� ��������
                                str_oc.Trim(true); str_oc.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {idMr=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {idMr.Clear(); idMr<<MyMacroregArray.Item(i).idMacroreg; break;}
                                
                                }
                                if(idMr.IsEmpty()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                
                                sqlText=wxSqlTextSelOc; sqlText<<str_oc; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ������������ ��
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� 
                                    {
                                        int flag_compare = 0; //���� ����, ��� ������� ���������� �� ������������ � region � �� ��/�� � ���.������
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            sqlText.Clear();
                                            sqlText<<wxSqlTextSelTechCentr; sqlText<<row[0]; //���� � ��������� ���������� ���� ��/��
                                            sqlText<<wxSqlTextSelTechCentr1; sqlText<<idMr; sqlText<<wxSqlEndText;
                                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                            else 
                                            {
                                                MYSQL_RES *res1 = mysql_store_result(conn); // ����� ���������
                                                int num_rows1 = mysql_num_rows(res1); // � ���������� �����.
                                                if(num_rows1>0) //���� ���������� �������, �� 
                                                {
                                                    flag_compare=1;
                                                    tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1]; //��������� ���� ���������
                                                }
                                                mysql_free_result(res1); // ������� ����������
                                            }
                                        }
                                        mysql_free_result(res); // ������� ����������
                                        if (flag_compare==1) 
                                        {
                                            wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        }
                                        else
                                        {
                                            sqlText.Clear();
                                            sqlText<<wxSqlTextInsRegion; //���������� � ������� region ����� ��������
                                            sqlText<<str_oc; sqlText<<"\" ,2 ,1) ;";
                                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                            else 
                                            {
                                                sqlText.Clear();
                                                sqlText<<wxSqlTextSelIdOc; //���������� �� ������� region id ������ ��� ������������ ��������
                                                sqlText<<str_oc; sqlText<<wxSqlEndTextOrderByDescL;
                                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                                else 
                                                {
                                                    MYSQL_RES *res = mysql_use_result(conn); // ����� ���������,
                                                    MYSQL_ROW row = mysql_fetch_row(res); //����� ������ ������ �������
                                                    for (; row; row = mysql_fetch_row(res)) // ����� �������
                                                    {
                                                        idOc = row[0]; //����������� ���������� id ������ ��
                                                        break;
                                                    }
                                                    mysql_free_result(res); // ������� ����������
                                                    if(idOc.IsEmpty()) {InformationSleep (wxWARNING_NOT_ID_REG, sec_for_sleep_window_info, this); break;} //��������� ������ ��������
                                                    sqlText.Clear();
                                                    sqlText<<wxSqlTextInsTechCentr; //��������� � �������� ���� ��/��
                                                    sqlText<<idOc; sqlText<<wxSqlCommaText;
                                                    sqlText<<idMr; sqlText<<wxSqlEndRightBracketText;
                                                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                                    else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsRegion;
                                        sqlText<<str_oc; sqlText<<"\" ,2 ,1) ;";
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else 
                                        {
                                            sqlText.Clear();
                                            sqlText<<wxSqlTextSelIdOc;
                                            sqlText<<str_oc; sqlText<<wxSqlEndTextOrderByDesc;
                                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                            else 
                                            {
                                                MYSQL_RES *res = mysql_use_result(conn); // ����� ���������,
                                                MYSQL_ROW row = mysql_fetch_row(res); //����� ������ ������ �������
                                                for (; row; row = mysql_fetch_row(res)) // ����� �������
                                                {
                                                    idOc = row[0];
                                                    break;
                                                }
                                                mysql_free_result(res); // ������� ����������
                                                if(idOc.IsEmpty()) {InformationSleep (wxWARNING_NOT_ID_REG, sec_for_sleep_window_info, this); break;}
                                                sqlText.Clear();
                                                sqlText<<wxSqlTextInsTechCentr;
                                                sqlText<<idOc; sqlText<<wxSqlCommaText;
                                                sqlText<<idMr; sqlText<<wxSqlEndRightBracketText;
                                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                            }
                                        }
                                    }   
                                }
                                break;   
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==0&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==2)        //��
                            {
                                wxString sqlText, str_mr, str_oc, str_gc, idMr, idOc, idGc;
                                str_mr = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                str_oc = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                str_gc = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                if(str_mr.IsEmpty()||str_oc.IsEmpty()||str_gc.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_mr.MakeUpper(); str_oc.MakeUpper(); str_gc.MakeUpper(); //�������� � �������� ��������
                                str_gc.Trim(true); str_gc.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {idMr=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {idMr.Clear(); idMr<<MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                for(register int i =0; i<MyOcArray.GetCount();++i) 
                                {
                                    //if(!str_oc.compare(MyOcArray.Item(i).nameOc)&&!MyOcArray.Item(i).activOc.compare("1")) {idOc=MyOcArray.Item(i).idOc; break;}
                                    if(!str_oc.compare(MyOcArray.Item(i).nameOc)&&MyOcArray.Item(i).activOc==1) {idOc.Clear(); idOc<<MyOcArray.Item(i).idOc; break;}
                                }
                                if(idMr.IsEmpty()||idOc.IsEmpty()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                
                                sqlText=wxSqlTextSelGc; sqlText<<str_gc; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ������������ ��
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� 
                                    {
                                        int flag_compare = 0; //���� ����, ��� ������� ���������� �� ������������ � region � �� ��/�� � ���.������
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            sqlText.Clear();
                                            sqlText<<wxSqlTextSelTechCentr; sqlText<<row[0]; //���� � ��������� ���������� ���� ��/��
                                            sqlText<<wxSqlTextSelTechCentr1; sqlText<<idOc; sqlText<<wxSqlEndText;
                                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                            else 
                                            {
                                                MYSQL_RES *res1 = mysql_store_result(conn); // ����� ���������
                                                int num_rows1 = mysql_num_rows(res1); // � ���������� �����.
                                                if(num_rows1>0) //���� ���������� �������, �� 
                                                {
                                                    flag_compare=1;
                                                    tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1]; //��������� ���� ���������
                                                }
                                                mysql_free_result(res1); // ������� ����������
                                            }
                                        }
                                        mysql_free_result(res); // ������� ����������
                                        if (flag_compare==1) 
                                        {
                                            wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        }
                                        else
                                        {
                                            sqlText.Clear();
                                            sqlText<<wxSqlTextInsRegion;
                                            sqlText<<str_gc; sqlText<<"\" ,3 ,1) ;";
                                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                            else 
                                            {
                                                sqlText.Clear();
                                                sqlText<<wxSqlTextSelIdgc;
                                                sqlText<<str_gc; sqlText<<wxSqlEndTextOrderByDesc;
                                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                                else 
                                                {
                                                    MYSQL_RES *res = mysql_use_result(conn); // ����� ���������,
                                                    MYSQL_ROW row = mysql_fetch_row(res); //����� ������ ������ �������
                                                    for (; row; row = mysql_fetch_row(res)) // ����� �������
                                                    {
                                                        idGc = row[0];
                                                        break;
                                                    }
                                                    mysql_free_result(res); // ������� ����������
                                                    if(idGc.IsEmpty()) {InformationSleep (wxWARNING_NOT_ID_REG, sec_for_sleep_window_info, this); break;}
                                                    sqlText.Clear();
                                                    sqlText<<wxSqlTextInsTechCentr;
                                                    sqlText<<idGc; sqlText<<wxSqlCommaText;
                                                    sqlText<<idOc; sqlText<<wxSqlEndRightBracketText;
                                                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                                    else 
                                                    {
                                                        sqlText.Clear();
                                                        sqlText<<wxSqlTextInsTechCentr;
                                                        sqlText<<idMr; sqlText<<wxSqlCommaText;
                                                        sqlText<<idGc; sqlText<<wxSqlEndRightBracketText;
                                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                                        else  {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsRegion;
                                        sqlText<<str_gc; sqlText<<"\" ,3 ,1) ;";
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else 
                                        {
                                            sqlText.Clear();
                                            sqlText<<wxSqlTextSelIdgc;
                                            sqlText<<str_gc; sqlText<<wxSqlEndTextOrderByDesc;
                                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                            else 
                                            {
                                                MYSQL_RES *res = mysql_use_result(conn); // ����� ���������,
                                                MYSQL_ROW row = mysql_fetch_row(res); //����� ������ ������ �������
                                                for (; row; row = mysql_fetch_row(res)) // ����� �������
                                                {
                                                    idGc = row[0];
                                                    break;
                                                }
                                                mysql_free_result(res); // ������� ����������
                                                if(idGc.IsEmpty()) {InformationSleep (wxWARNING_NOT_ID_REG, sec_for_sleep_window_info, this); break;}
                                                sqlText.Clear();
                                                sqlText<<wxSqlTextInsTechCentr;
                                                sqlText<<idGc; sqlText<<wxSqlCommaText;
                                                sqlText<<idOc; sqlText<<wxSqlEndRightBracketText;
                                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                                else 
                                                {
                                                    sqlText.Clear();
                                                    sqlText<<wxSqlTextInsTechCentr;
                                                    sqlText<<idMr; sqlText<<wxSqlCommaText;
                                                    sqlText<<idGc; sqlText<<wxSqlEndRightBracketText;
                                                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                                    else  {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                                }
                                            }
                                        }
                                    }   
                                }
                                break;   
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==0)        //��
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str_old.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {str_old=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str_old.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {str_old.Clear(); str_old<<MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdRegion;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdRegionWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==1)        //��
                            {
                                wxString sqlText;
                                wxString str_mr = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()||str_mr.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); str_mr.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {str_mr=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {str_mr.Clear(); str_mr<<MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                for(register int i =0; i<MyOcArray.GetCount();++i) 
                                {
                                    //if(!str_old.compare(MyOcArray.Item(i).nameOc)&&!MyOcArray.Item(i).activOc.compare("1")) {str_old=MyOcArray.Item(i).idOc; break;}
                                    if(!str_old.compare(MyOcArray.Item(i).nameOc)&&MyOcArray.Item(i).activOc==1) {str_old.Clear(); str_old<<MyOcArray.Item(i).idOc; break;}
                                }
                                if(!str_old.IsNumber()||!str_mr.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdRegion;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdRegionWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;   
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==1&&   //��������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==2)        //��
                            {
                                wxString sqlText;
                                wxString str_mr = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_oc = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR3))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()||str_mr.IsEmpty()||str_oc.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); str_mr.MakeUpper(); str_oc.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {str_mr=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {str_mr.Clear(); str_mr<<MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                for(register int i =0; i<MyOcArray.GetCount();++i) 
                                {
                                    //if(!str_oc.compare(MyOcArray.Item(i).nameOc)&&!MyOcArray.Item(i).activOc.compare("1")) {str_oc=MyOcArray.Item(i).idOc; break;}
                                    if(!str_oc.compare(MyOcArray.Item(i).nameOc)&&MyOcArray.Item(i).activOc==1) {str_oc.Clear(); str_oc<<MyOcArray.Item(i).idOc; break;}
                                }
                                for(register int i =0; i<MyGcArray.GetCount();++i) 
                                {
                                    //if(!str_old.compare(MyGcArray.Item(i).nameGc)&&!MyGcArray.Item(i).activGc.compare("1")) {str_old=MyGcArray.Item(i).idGc; break;}
                                    if(!str_old.compare(MyGcArray.Item(i).nameGc)&&MyGcArray.Item(i).activGc==1) {str_old.Clear(); str_old<<MyGcArray.Item(i).idGc; break;}
                                }
                                if(!str_old.IsNumber()||!str_mr.IsNumber()||!str_oc.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdRegion;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdRegionWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==0)        //��
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {str=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {str.Clear(); str<<MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelRegion;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    sqlText.Clear();
                                    sqlText<<wxSqlTextDelTechCentr;
                                    sqlText<<str; sqlText<<wxSqlTextDelTechCentrDop;
                                    sqlText<<str; sqlText<<wxSqlEndText;
                                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                    else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                }
                                break;  
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==1)        //��
                            {
                                wxString sqlText;
                                wxString str_mr = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); str_mr.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {str_mr=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {str_mr.Clear(); str_mr<<MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                for(register int i =0; i<MyOcArray.GetCount();++i) 
                                {
                                    //if(!str.compare(MyOcArray.Item(i).nameOc)&&!MyOcArray.Item(i).activOc.compare("1")) {str=MyOcArray.Item(i).idOc; break;}
                                    if(!str.compare(MyOcArray.Item(i).nameOc)&&MyOcArray.Item(i).activOc==1) {str.Clear(); str<<MyOcArray.Item(i).idOc; break;}
                                }
                                if(!str.IsNumber()||!str_mr.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelRegion;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    sqlText.Clear();
                                    sqlText<<wxSqlTextDelTechCentr;
                                    sqlText<<str; sqlText<<wxSqlTextDelTechCentrDop;
                                    sqlText<<str; sqlText<<wxSqlEndText;
                                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                    else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                }
                                break; 
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==2&&   //�������
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==2)        //��
                            {
                                wxString sqlText;
                                wxString str_mr = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_oc = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); str_oc.MakeUpper();  str_mr.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {str_mr=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {str_mr.Clear(); str_mr<<MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                for(register int i =0; i<MyOcArray.GetCount();++i) 
                                {
                                    //if(!str_oc.compare(MyOcArray.Item(i).nameOc)&&!MyOcArray.Item(i).activOc.compare("1")) {str_oc=MyOcArray.Item(i).idOc; break;}
                                    if(!str_oc.compare(MyOcArray.Item(i).nameOc)&&MyOcArray.Item(i).activOc==1) {str_oc.Clear(); str_oc<<MyOcArray.Item(i).idOc; break;}
                                }
                                for(register int i =0; i<MyGcArray.GetCount();++i) 
                                {
                                    //if(!str.compare(MyGcArray.Item(i).nameGc)&&!MyGcArray.Item(i).activGc.compare("1")) {str=MyGcArray.Item(i).idGc; break;}
                                    if(!str.compare(MyGcArray.Item(i).nameGc)&&MyGcArray.Item(i).activGc==1) {str.Clear(); str<<MyGcArray.Item(i).idGc; break;}
                                }
                                if(!str.IsNumber()||!str_mr.IsNumber()||!str_oc.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelRegion;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    sqlText.Clear();
                                    sqlText<<wxSqlTextDelTechCentr;
                                    sqlText<<str; sqlText<<wxSqlTextDelTechCentrDop;
                                    sqlText<<str; sqlText<<wxSqlEndText;
                                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                    else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                }
                                break;  
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==3&&   //��������� � �����
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==0)        //��
                            {
                                wxString sqlText;       //���������� ��� ����� sql-�������
                                int idMr=0;             //���������� ��� id ������������
                                int flag_kaskad=0;      //���� ����, ��� ������ ������� ���������� ����������
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                flag_kaskad = ((wxCheckBox*)panel_second_line->FindWindow(wxID_ADM_CHACKBOX_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {idMr=MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                if(idMr==0) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                switch(flag_kaskad)
                                {
                                    case 0: //�� ���������� ���� ���������� ����������
                                    {
                                        sqlText<<wxSqlTextUpdMrOcGc;
                                        sqlText<<idMr; sqlText<<wxSqlEndRightBracketText;
                                        wxMessageBox(sqlText);
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                        break;
                                    }
                                    case 1: //���������� ���� ���������� ����������
                                    {
                                        wxString tempId; //������ id ��+��+��
                                        tempId<<idMr; 
                                        for(register int i =0; i<MyTechCentrArray.GetCount();++i)   
                                        {
                                            if(idMr==MyTechCentrArray.Item(i).son)
                                            {
                                                tempId<<", "; tempId<<MyTechCentrArray.Item(i).parent;
                                                for(register int j =0; j<MyTechCentrArray.GetCount();++j)   
                                                {
                                                    if(MyTechCentrArray.Item(i).parent==MyTechCentrArray.Item(j).son)
                                                    {
                                                        tempId<<", "; tempId<<MyTechCentrArray.Item(j).parent;
                                                    }
                                                }
                                            }
                                        }
                                        sqlText<<wxSqlTextUpdMrOcGc;
                                        sqlText<<tempId; sqlText<<wxSqlEndRightBracketText;
                                        wxMessageBox(sqlText);
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                        break;
                                    }
                                    default: break;
                                }
                                break;  
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==3&&   //��������� � �����
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==1)        //��
                            {
                                wxString sqlText;
                                int idMr=0, idOc=0;             //���������� ��� id 
                                int flag_kaskad=0;      //���� ����, ��� ������ ������� ���������� ����������
                                wxString str_mr = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                flag_kaskad = ((wxCheckBox*)panel_second_line->FindWindow(wxID_ADM_CHACKBOX_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); str_mr.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    //if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&!MyMacroregArray.Item(i).activMacroreg.compare("1")) {str_mr=MyMacroregArray.Item(i).idMacroreg; break;}
                                    if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {idMr=MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                for(register int i =0; i<MyOcArray.GetCount();++i) 
                                {
                                    //if(!str.compare(MyOcArray.Item(i).nameOc)&&!MyOcArray.Item(i).activOc.compare("1")) {str=MyOcArray.Item(i).idOc; break;}
                                    if(!str.compare(MyOcArray.Item(i).nameOc)&&MyOcArray.Item(i).activOc==1) {idOc=MyOcArray.Item(i).idOc; break;}
                                }
                                if(idMr==0||idOc==0) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                switch(flag_kaskad)
                                {
                                    case 0: //�� ���������� ���� ���������� ����������
                                    {
                                        sqlText<<wxSqlTextUpdMrOcGc;
                                        sqlText<<idOc; sqlText<<wxSqlEndRightBracketText;
                                        wxMessageBox(sqlText);
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                        break;
                                    }
                                    case 1: //���������� ���� ���������� ����������
                                    {
                                        wxString tempId; //������ id ��+��+��
                                        tempId<<idOc; 
                                        for(register int i =0; i<MyTechCentrArray.GetCount();++i)   
                                        {
                                            if(idOc==MyTechCentrArray.Item(i).son)
                                            {
                                                tempId<<", "; tempId<<MyTechCentrArray.Item(i).parent;
                                            }
                                        }
                                        sqlText<<wxSqlTextUpdMrOcGc;
                                        sqlText<<tempId; sqlText<<wxSqlEndRightBracketText;
                                        wxMessageBox(sqlText);
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                        break;
                                    }
                                    default: break;
                                }
                                break; 
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_7))->GetSelection()==3&&   //��������� � �����
                            ((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_LVL_7))->GetSelection()==2)        //��
                            {
                                wxString sqlText;
                                int idMr=0, idOc=0, idGc=0;             //���������� ��� id 
                                wxString str_mr = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_oc = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR2))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); str_oc.MakeUpper();  str_mr.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyMacroregArray.GetCount();++i) 
                                {
                                    if(!str_mr.compare(MyMacroregArray.Item(i).nameMacroreg)&&MyMacroregArray.Item(i).activMacroreg==1) {idMr=MyMacroregArray.Item(i).idMacroreg; break;}
                                }
                                for(register int i =0; i<MyOcArray.GetCount();++i) 
                                {
                                    if(!str_oc.compare(MyOcArray.Item(i).nameOc)&&MyOcArray.Item(i).activOc==1) {idOc=MyOcArray.Item(i).idOc; break;}
                                }
                                for(register int i =0; i<MyGcArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyGcArray.Item(i).nameGc)&&MyGcArray.Item(i).activGc==1) {idGc=MyGcArray.Item(i).idGc; break;}
                                }
                                if(idMr==0||idOc==0||idGc==0) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdMrOcGc;
                                sqlText<<idGc; sqlText<<wxSqlEndRightBracketText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;  
                            }
                            break;
                        }
                        case 8: //������� 9 �������� �������� - �����������
                        {
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_8))->GetSelection()==0)   //�������� ������� ����������
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                str.Trim(true); str.Trim(false); //������� ���������� ������� ������ � �����
                                
                                sqlText=wxSqlTextSelEvent; sqlText<<str; sqlText<<wxSqlStrongEnd; //���� � ������� ���������� �� ��������
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else 
                                {
                                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                                    if(num_rows>0) //���� ���������� �������, �� ��������� �������� � ����������� ������������
                                    {
                                        wxString tempText=wxMATCH_IS_FOUND; //���������� ��� ������ ��������� � ��������� ����������
                                        tempText+='\n'; tempText+=wxSTRING_ID; tempText+='\t'; tempText+=wxSTRING_NAME; 
                                        for (register int i = 0; i < num_rows; i++) // ����� �������
                                        {
                                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                            tempText+='\n'; tempText+=row[0]; tempText+='\t'; tempText+=row[1];
                                        }
                                        wxMessageBox(tempText, wxOperationIsProhibited,  wxOK); //������� ���������� ���� � ����������
                                        mysql_free_result(res); // ������� ����������
                                        break;
                                    }
                                    else //���� ���������� �� �������, �� ��������� ��������
                                    {
                                        mysql_free_result(res); // ������� ����������
                                        sqlText.Clear();
                                        sqlText<<wxSqlTextInsEvent;
                                        sqlText<<str; sqlText<<wxSqlTextBracketEnd;
                                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                        else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                    }   
                                }
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_8))->GetSelection()==1)   //�������� ������� ����������
                            {
                                wxString sqlText;
                                wxString str_old = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                wxString str_new = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR1))->GetValue();
                                if(str_old.IsEmpty()||str_new.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str_old.MakeUpper(); str_new.MakeUpper(); //�������� � �������� ��������
                                str_new.Trim(true); str_new.Trim(false); //������� ���������� ������� ������ � �����
                                for(register int i =0; i<MyHolidayTypeArray.GetCount();++i) 
                                {
                                    if(!str_old.compare(MyHolidayTypeArray.Item(i).nameHolidayType)) 
                                    //{str_old=MyHolidayTypeArray.Item(i).idHolidayType; break;}
                                    {str_old.Clear(); str_old<<MyHolidayTypeArray.Item(i).idHolidayType; break;}
                                }
                                if(!str_old.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextUpdEvent;
                                sqlText<<str_new; sqlText<<wxSqlTextUpdEventWhere;
                                sqlText<<str_old; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            if(((wxRadioBox*)panel_first_line->FindWindow(wxID_ADM_RADIOBOX_TYPE_8))->GetSelection()==2)   //������� ������� ����������
                            {
                                wxString sqlText;
                                wxString str = ((wxTextCtrl*)panel_second_line->FindWindow(wxID_ADM_TEXTCTRL_PR_GR))->GetValue();
                                if(str.IsEmpty()) {InformationSleep (wxINFO_EMPTY_CONTROL, sec_for_sleep_window_info, this); break;}
                                str.MakeUpper(); //�������� � �������� ��������
                                for(register int i =0; i<MyHolidayTypeArray.GetCount();++i) 
                                {
                                    if(!str.compare(MyHolidayTypeArray.Item(i).nameHolidayType)) 
                                    //{str=MyHolidayTypeArray.Item(i).idHolidayType; break;}
                                    {str.Clear(); str<<MyHolidayTypeArray.Item(i).idHolidayType; break;}
                                }
                                if(!str.IsNumber()) {InformationSleep (wxINFO_NOT_SPRAVOCHNIK_STRING, sec_for_sleep_window_info, this); break;}
                                sqlText<<wxSqlTextDelEvent;
                                sqlText<<str; sqlText<<wxSqlEndText;
                                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); break;} 
                                else {InformationSleep (wxID_SUCCESS_OPERATION, sec_for_sleep_window_info, this);}
                                break;
                            }
                            break;
                        }
                        default:break;
                    }
                    break;
                }
                default:break;
            }
            break;
        }
        case wxID_CANCEL:
        {
            Destroy();
            break;
        }
        default:break;
    }
}

void NotebookAdmin::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    switch(event.GetId())
    {
        case wxID_ADM_BL_TEXTCTRL_UPD_3: //��������� � ���� � ��� ������� ������� �������� �� ����
        case wxID_ADM_BL_TEXTCTRL_INS_3: //��������� � ���� � ��� ������� ������� �������� �� ����
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //���� ����� ����, ������ ��� ����, �� ���������� ������� ����� � ��������
                {event.Skip(true);} 
                else {
                    if((event.GetKeyCode()>=32&&event.GetKeyCode()<=47)||(event.GetKeyCode()>=58&&event.GetKeyCode()<=255&&event.GetKeyCode()!=127)) //���� ������� ������ ������ � ���������, �� �� ���������� ������� ����� � ��������
                        {event.Skip(false);}
                    else {event.Skip(true);}
                }
                break;
            }
        default: event.Skip(true);
    }
}

void NotebookAdmin::ProcessInfoBar(wxString &str1, wxInfoBar* ihfobar)
{
    wxString str = str1;
    wxClientDC *dc = new wxClientDC(this); //������� ��������� �� �������� ����������
    wxSize sizeStr = dc->GetTextExtent(str); //���������� ����� ������ � ��������
    delete dc;
                        
    wxSize sizeWin = this->GetClientSize(); //���������� ������� ���������� ������� ����
    int elem = sizeStr.GetWidth()/str.Len(); //���������� ������ ������ ������� � ��������

    wxString::size_type pos = 0;
    int a = sizeWin.GetWidth()-190;
    for (wxString::size_type pos = 0, j=0; (pos = str.find_first_of(' ',(pos+1)))!=wxString::npos; )
    {if(((pos-j)*elem)>a) {j=pos; str.SetChar(pos,'\n');}}
            
    ihfobar->SetShowHideEffects(wxSHOW_EFFECT_ROLL_TO_RIGHT, wxSHOW_EFFECT_ROLL_TO_RIGHT); //������������� ������ ��������/�������� ��������
    ihfobar->ShowMessage(str, wxICON_INFORMATION); //���������� ��������� ��������
}

void NotebookAdmin::CreateSubNotebookSov (void)
{
    wxDir dir(wxGetCwd());
    wxString str_full, str_first, str_last;
    wxBoxSizer *hr_sub_page_sov = new wxBoxSizer (wxHORIZONTAL);
    hr_propgrid = new wxBoxSizer (wxHORIZONTAL);
    wxBoxSizer *vert_local_1 = new wxBoxSizer (wxVERTICAL);
    wxBoxSizer *vert_local_2 = new wxBoxSizer (wxVERTICAL);
    //panel_sovetnic = (wxPanel*)nb->FindWindow(wxID_ADM_PAGE_SOV);
    //panel_sovetnic = (wxScrolledWindow *)nb->FindWindow(wxID_ADM_PAGE_SOV);
    wxListView *listview = new wxListView(panel_sovetnic, wxID_ADM_LISTVIEW_SOV_SP);
    vert_local_2->Add(new wxSearchCtrl(panel_sovetnic,wxID_ADM_SEARCH_SOV_FIO, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT),0,wxEXPAND,0);
    vert_local_2->Add(listview,1,wxEXPAND,0);
    listview->InsertColumn(0,wxCAPTION_COLUMN_FIO);
    listview->InsertColumn(1,wxCAPTION_COLUMN_ARCHIVE);
    for(register int i =0,j=0; i<MySovetnicArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        //if(wxAtoi(MySovetnicArray.Item(i).idSovetnic)==49) {continue;} else 
        if(MySovetnicArray.Item(i).idSovetnic==49) {continue;} else 
        {
            wxListItem *f = new wxListItem(); //������� ������ ���������� ���� �� ��������  wxListCtrl
            f->SetState(wxLIST_STATE_FOCUSED); //������� ����� �����
            f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
            f->SetColumn(0);
            //f->SetData(wxAtoi(MySovetnicArray.Item(i).idSovetnic)); //������ ���������� ����
            f->SetData(MySovetnicArray.Item(i).idSovetnic); //������ ���������� ����
            wxString strFio = MySovetnicArray.Item(i).nameSovetnic;
            EditStringFioFull(strFio);
            f->SetText(strFio);
            f->SetId(j);
            listview->InsertItem(*f); 
            listview->SetItem(j,1,wxString::Format(L"%i",MySovetnicArray.Item(i).activSovetnic));
            ++j; //��������� � ��������� ������
            delete f;
        }
    }
    listview->SetColumnWidth(0,wxLIST_AUTOSIZE);
    listview->SetColumnWidth(1,wxLIST_AUTOSIZE);
    
    wxPropertyGrid *propertyGrid = new wxPropertyGrid(panel_sovetnic,wxID_ADM_PROPERTYGRID_SOV, wxDefaultPosition, wxSize(-1,10),wxPG_DEFAULT_STYLE);
    
    wxString category_pd = "������������ ������";
    wxString category_pd_sub_fio = "���";
    wxString category_pd_sub_dr = "���� ��������";
    wxString category_pd_sub_tel = "�������";
    wxString category_pd_sub_d_op = "���� ������";
    wxString category_pd_sub_d_cl = "���� ����������";
    wxString category_pd_sub_act = "�������";
    wxString wxPGPpd = "pd";
    wxString wxPGPpdFio = "fio";
    wxString wxPGPpdDr = "dr";
    wxString wxPGPpdTel = "tel";
    wxString wxPGPpdDateOpen = "dete_open";
    wxString wxPGPpdDateClose = "date_close";
    wxString wxPGPpdActiv = "activ";
    
    wxPGProperty *pD = propertyGrid->Append(new wxStringProperty(category_pd,wxPGPpd));
    //pD->SetValueFromString(pD->GenerateComposedValue()); //���������� ����� �� �������� �������� �������
    
    propertyGrid->SetPropertyReadOnly(pD,true, wxPG_DONT_RECURSE); //������������� �������� ������ ������ ��� ���� ���������
    pD->AppendChild(new wxLongStringProperty(category_pd_sub_fio,wxPGPpdFio));
    wxPGProperty *pD1 = pD->AppendChild(new wxDateProperty(category_pd_sub_dr,wxPGPpdDr));
    pD->AppendChild(new wxLongStringProperty(category_pd_sub_tel,wxPGPpdTel));
    wxPGProperty *pD2 = pD->AppendChild(new wxDateProperty(category_pd_sub_d_op,wxPGPpdDateOpen));
    wxPGProperty *pD3 = pD->AppendChild(new wxDateProperty(category_pd_sub_d_cl,wxPGPpdDateClose));
    pD->AppendChild(new wxBoolProperty(category_pd_sub_act,wxPGPpdActiv));
    
    pD1->SetAttribute(wxPG_DATE_PICKER_STYLE, wxDP_DEFAULT|wxDP_SHOWCENTURY|wxDP_ALLOWNONE); //������������� ������� ��� ����� ��������. �� ��������� wxDP_DEFAULT|wxDP_SHOWCENTURY. ������������� wxDP_ALLOWNONE ������� ��������� �������������� �������� � ���������.
    pD2->SetAttribute(wxPG_DATE_PICKER_STYLE, wxDP_DEFAULT|wxDP_SHOWCENTURY|wxDP_ALLOWNONE);
    pD3->SetAttribute(wxPG_DATE_PICKER_STYLE, wxDP_DEFAULT|wxDP_SHOWCENTURY|wxDP_ALLOWNONE);
 
    
   /* propertyGrid->SetWindowStyleFlag(wxPG_SPLITTER_AUTO_CENTER); //��������� �������� ����� wxPG_SPLITTER_AUTO_CENTER
    propertyGrid->SetColumnProportion(0,1); //������ ���������� 1-� �������
    propertyGrid->SetColumnProportion(1,3); //������ ��������� 2-� �������
    propertyGrid->ResetColumnSizes();
    */
    
    propertyGrid->CollapseAll();  //����������� ��� ���������
    
    str_first = dir.GetName(); str_last= wxUPDATE_ICO; str_full=str_first; str_full+=str_last;
    wxImage *image = new wxImage(str_full,wxBITMAP_TYPE_ICO);
    image->Rescale(16,16);
    
    hr_propgrid->Add(propertyGrid,1,wxEXPAND,0); //��������� � ���������� ������������ property
    hr_propgrid->Add(new wxBitmapButton(panel_sovetnic,wxID_ADM_BUTTON_SOV_UPD_PD,wxBitmap(*image)), 0, wxEXPAND,0); //��������� � ���������� ������������ ������
    (panel_sovetnic->FindWindow(wxID_ADM_BUTTON_SOV_UPD_PD))->SetToolTip(wxCAPTION_TOOLTIP_B_1); //� ������ ������������ ���������
    
    wxCollapsiblePane *collpane1 = new wxCollapsiblePane(panel_sovetnic, wxID_ADM_COLLPANE_SOV_REG, wxCAPTION_COLLPANE_REG, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win1 = collpane1->GetPane();
    wxSizer *paneSz1 = new wxBoxSizer(wxHORIZONTAL);
    wxListView *listview1 = new wxListView(win1, wxID_ADM_LISTVIEW_SOV_R);
    listview1->InsertColumn(0,wxCAPTION_COLUMN_LVL);
    listview1->InsertColumn(1,wxCAPTION_COLUMN_NAME);
    listview1->InsertColumn(2,wxCAPTION_COLUMN_ARCHIVE);
    listview1->InsertColumn(3,wxCAPTION_COLUMN_DATE);
    wxBoxSizer *reg_loc_vr = new wxBoxSizer(wxVERTICAL);
    
    wxStaticBox *stBox1 = new wxStaticBox(win1,wxID_ANY,wxCAPTION_STATICBOX_ARCHIV);
    wxStaticBoxSizer *to_static_box1 = new wxStaticBoxSizer(stBox1,wxHORIZONTAL);
    to_static_box1->Add(new wxButton(stBox1,wxID_ADM_BUT_PLACE_R, wxCAPTION_BUTTON_PLACE),0,wxEXPAND,0);
    to_static_box1->Add(new wxButton(stBox1,wxID_ADM_BUT_EXTRACT_R, wxCAPTION_BUTTON_EXTRACT),0,wxEXPAND,0);
    
    wxCollapsiblePane *collpane1_1 = new wxCollapsiblePane(win1, wxID_ADM_COLLPANE_SOV_R_1, wxCAPTION_COLLPANE_PRIV_REG, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win1_1 = collpane1_1->GetPane();
    wxSizer *paneSz1_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *ins_reg_loc = new wxBoxSizer(wxHORIZONTAL);
    ins_reg_loc->Add(new wxButton(win1_1,wxID_ADM_BUT_SAVE_R,wxCAPTION_BUTTON_SAVE),0,wxALIGN_RIGHT|wxRIGHT,10);
    ins_reg_loc->Add(new wxButton(win1_1,wxID_ADM_BUT_CANCEL_R,wxCAPTION_BUTTON_CANCEL),0,wxALIGN_RIGHT|wxRIGHT,10);
    paneSz1_1->Add(new wxStaticText(win1_1,wxID_ANY,wxCAPTION_STATICTEXT_LVL_REG), 0, wxEXPAND|wxALL, 1);
    wxString strlvl[]={wxCAPTION_COLUMN_MR,wxCAPTION_COLUMN_OC,wxCAPTION_COLUMN_GC}; //������� ������ ����� �������
    paneSz1_1->Add(new wxComboBox(win1_1,wxID_ADM_COMBOBOX_LVL_R, wxCAPTION_COLUMN_OC,wxDefaultPosition, wxDefaultSize,3,strlvl,wxCB_DROPDOWN|wxCB_READONLY), 1, wxEXPAND|wxALL, 1); //������� �������� �������� ������ � ������������ ����� �� ��
    
    paneSz1_1->Add(new wxStaticText(win1_1,wxID_ANY,wxCAPTION_STATICTEXT_NAME_REG), 0, wxEXPAND|wxALL, 1);
    paneSz1_1->Add(new wxTextCtrl(win1_1,wxID_ADM_TEXTCTRL_N_R), 1, wxEXPAND|wxALL, 1); //������� ��������� �������� � ������� ����������� �������
    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
    LocArray.Alloc(MyOcArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MyOcArray.GetCount();++j)   //��������� ��������� ������
    {
        //if(!MyOcArray.Item(j).activOc.compare("1")) {LocArray.Add(MyOcArray.Item(j).nameOc);}
        if(MyOcArray.Item(j).activOc==1) {LocArray.Add(MyOcArray.Item(j).nameOc);}
    }
    ((wxTextCtrl*)win1_1->FindWindow(wxID_ADM_TEXTCTRL_N_R))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    paneSz1_1->Add(ins_reg_loc, 0, wxEXPAND|wxALL, 5);
    win1_1->SetSizer(paneSz1_1);
    paneSz1_1->SetSizeHints(win1_1);
    
    reg_loc_vr->Add(collpane1_1,0,wxEXPAND,0);
    reg_loc_vr->Add(to_static_box1,0,wxEXPAND,0);
    reg_loc_vr->Add(new wxButton(win1,wxID_ADM_BUT_DEL_R, wxCAPTION_BUTTON_DEL_BC),0,wxEXPAND,0);
    paneSz1->Add(listview1, 1, wxEXPAND|wxALL, 5);
    paneSz1->Add(reg_loc_vr, 0, wxEXPAND|wxALL, 5);
    win1->SetSizer(paneSz1);
    paneSz1->SetSizeHints(win1);
    
    wxCollapsiblePane *collpane2 = new wxCollapsiblePane(panel_sovetnic, wxID_ADM_COLLPANE_SOV_DOLZ, wxCAPTION_COLLPANE_DOLZ, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win2 = collpane2->GetPane();
    wxSizer *paneSz2 = new wxBoxSizer(wxHORIZONTAL);
    wxListView *listview2 = new wxListView(win2, wxID_ADM_LISTVIEW_SOV_D);
    listview2->InsertColumn(0,wxCAPTION_COLUMN_JOB);
    listview2->InsertColumn(1,wxCAPTION_COLUMN_ARCHIVE);
    listview2->InsertColumn(2,wxCAPTION_COLUMN_C);
    listview2->InsertColumn(3,wxCAPTION_COLUMN_PO);
    wxBoxSizer *dol_loc_vr = new wxBoxSizer(wxVERTICAL);
    
    
    wxCollapsiblePane *collpane2_1 = new wxCollapsiblePane(win2, wxID_ADM_COLLPANE_SOV_D_1, wxCAPTION_COLLPANE_INS, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win2_1 = collpane2_1->GetPane();
    wxSizer *paneSz2_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *ins_dolz_loc = new wxBoxSizer(wxHORIZONTAL);
    ins_dolz_loc->Add(new wxButton(win2_1,wxID_ADM_BUT_SAVE_D,wxCAPTION_BUTTON_SAVE),0,wxALIGN_RIGHT|wxRIGHT,10);
    ins_dolz_loc->Add(new wxButton(win2_1,wxID_ADM_BUT_CANCEL_D,wxCAPTION_BUTTON_CANCEL),0,wxALIGN_RIGHT|wxRIGHT,10);
    paneSz2_1->Add(new wxStaticText(win2_1,wxID_ANY,wxCAPTION_STATICTEXT_NAME_DOL), 0, wxEXPAND|wxALL, 1);
    paneSz2_1->Add(new wxTextCtrl(win2_1,wxID_ADM_TEXTCTRL_N_D_1), 1, wxEXPAND|wxALL, 1);
    LocArray.Alloc(MyOcArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MyPositionSotrArray.GetCount();++j)   //��������� ��������� ������
    {
        LocArray.Add(MyPositionSotrArray.Item(j).namePosition);
    }
    ((wxTextCtrl*)win2_1->FindWindow(wxID_ADM_TEXTCTRL_N_D_1))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    //LocArray.Clear(); //������� ���������� ������� � ����������� ������
    paneSz2_1->Add(new wxStaticText(win2_1,wxID_ANY,wxCAPTION_STATICTEXT_DATE_NAZ), 0, wxEXPAND|wxALL, 1);
    paneSz2_1->Add(new wxDatePickerCtrl(win2_1,wxID_ADM_DATECTRL_D_ON_1,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxALL, 1);
    paneSz2_1->Add(ins_dolz_loc, 0, wxEXPAND|wxALL, 5);
    win2_1->SetSizer(paneSz2_1);
    paneSz2_1->SetSizeHints(win2_1);
    
    wxCollapsiblePane *collpane2_2 = new wxCollapsiblePane(win2, wxID_ADM_COLLPANE_SOV_D_2, wxCAPTION_COLLPANE_EDIT, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win2_2 = collpane2_2->GetPane();
    wxSizer *paneSz2_2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *upd_dolz_loc = new wxBoxSizer(wxHORIZONTAL);
    upd_dolz_loc->Add(new wxButton(win2_2,wxID_ADM_BUT_SAVE_D1,wxCAPTION_BUTTON_SAVE),0,wxALIGN_RIGHT|wxRIGHT,10);
    upd_dolz_loc->Add(new wxButton(win2_2,wxID_ADM_BUT_CANCEL_D1,wxCAPTION_BUTTON_CANCEL),0,wxALIGN_RIGHT|wxRIGHT,10);
    paneSz2_2->Add(new wxStaticText(win2_2,wxID_ANY,wxCAPTION_STATICTEXT_NAME_DOL), 0, wxEXPAND|wxALL, 1);
    paneSz2_2->Add(new wxTextCtrl(win2_2,wxID_ADM_TEXTCTRL_N_D_2), 1, wxEXPAND|wxALL, 1);
    ((wxTextCtrl*)win2_2->FindWindow(wxID_ADM_TEXTCTRL_N_D_2))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    paneSz2_2->Add(new wxStaticText(win2_2,wxID_ANY,wxCAPTION_STATICTEXT_DATE_NAZ), 0, wxEXPAND|wxALL, 1);
    paneSz2_2->Add(new wxDatePickerCtrl(win2_2,wxID_ADM_DATECTRL_D_ON_2,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxALL, 1);
    paneSz2_2->Add(new wxStaticText(win2_2,wxID_ANY,wxCAPTION_STATICTEXT_DATE_SACK), 0, wxEXPAND|wxALL, 1);
    paneSz2_2->Add(new wxDatePickerCtrl(win2_2,wxID_ADM_DATECTRL_D_OF_2,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxALL, 1);
    paneSz2_2->Add(new wxCheckBox(win2_2,wxID_ADM_CHECK_D_1,wxCAPTION_CHECKBOX_FLAG_ARCHIVE), 1, wxEXPAND|wxALL, 1);
    
    paneSz2_2->Add(upd_dolz_loc, 0, wxEXPAND|wxALL, 5);
    win2_2->SetSizer(paneSz2_2);
    paneSz2_2->SetSizeHints(win2_2);
        
    dol_loc_vr->Add(collpane2_1,0,wxEXPAND,0);
    dol_loc_vr->Add(collpane2_2,0,wxEXPAND,0);
    dol_loc_vr->Add(new wxButton(win2,wxID_ADM_BUT_DEL_D, wxCAPTION_BUTTON_DEL_BC),0,wxEXPAND,0);
    paneSz2->Add(listview2, 1, wxEXPAND|wxALL, 5);
    paneSz2->Add(dol_loc_vr, 0, wxEXPAND|wxALL, 5);
    win2->SetSizer(paneSz2);
    paneSz2->SetSizeHints(win2);
    
    wxCollapsiblePane *collpane3 = new wxCollapsiblePane(panel_sovetnic, wxID_ADM_COLLPANE_SOV_HOL, wxCAPTION_COLLPANE_HOLIDAY, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win3 = collpane3->GetPane();
    wxSizer *paneSz3 = new wxBoxSizer(wxHORIZONTAL);
    wxListView *listview3 = new wxListView(win3, wxID_ADM_SOV_LISTVIEW_HOL);
    listview3->InsertColumn(0,wxCAPTION_COLUMN_EVENT);
    listview3->InsertColumn(1,wxCAPTION_COLUMN_C);
    listview3->InsertColumn(2,wxCAPTION_COLUMN_PO);
    listview3->InsertColumn(3,wxCAPTION_COLUMN_ZAMKAND);
    listview3->InsertColumn(4,wxCAPTION_COLUMN_ZAMTO);
    
    wxCollapsiblePane *collpane3_1 = new wxCollapsiblePane(win3, wxID_ADM_COLLPANE_HOL_INS, wxCAPTION_COLLPANE_INS, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win3_1 = collpane3_1->GetPane();
    wxSizer *paneSz3_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *paneSz3_1_loc_hr = new wxBoxSizer(wxHORIZONTAL);
    paneSz3_1->Add(new wxStaticText(win3_1,wxID_ANY,wxCAPTION_STATICTEXT_EVENT), 0, wxEXPAND|wxALL, 1);
    paneSz3_1->Add(new wxTextCtrl(win3_1,wxID_ADM_TEXTCTRL_HOL_EVT), 0, wxEXPAND|wxALL, 1);
    paneSz3_1_loc_hr->Add(new wxStaticText(win3_1,wxID_ANY,wxCAPTION_STATICTEXT_S), 0, wxEXPAND|wxALL, 1);
    paneSz3_1_loc_hr->Add(new wxDatePickerCtrl(win3_1,wxID_ADM_DATECTRL_HOL_ON1,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxALL, 1);
    paneSz3_1_loc_hr->Add(new wxStaticText(win3_1,wxID_ANY,wxCAPTION_STATICTEXT_PO), 0, wxEXPAND|wxALL, 1);
    paneSz3_1_loc_hr->Add(new wxDatePickerCtrl(win3_1,wxID_ADM_DATECTRL_HOL_OF2,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxALL, 1);
    paneSz3_1->Add(paneSz3_1_loc_hr, 0, wxEXPAND|wxALL, 1);
    paneSz3_1->Add(new wxStaticText(win3_1,wxID_ANY,wxCAPTION_STATICTEXT_ZAMKAND), 0, wxEXPAND|wxALL, 1);
    paneSz3_1->Add(new wxTextCtrl(win3_1,wxID_ADM_TEXTCTRL_HOL_Z_K), 0, wxEXPAND|wxALL, 1);
    paneSz3_1->Add(new wxStaticText(win3_1,wxID_ANY,wxCAPTION_STATICTEXT_ZAMTO), 0, wxEXPAND|wxALL, 1);
    paneSz3_1->Add(new wxTextCtrl(win3_1,wxID_ADM_TEXTCTRL_HOL_Z_A), 0, wxEXPAND|wxALL, 1);
    LocArray.Alloc(MyHolidayTypeArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MyHolidayTypeArray.GetCount();++j)   //��������� ��������� ������
    {
        LocArray.Add(MyHolidayTypeArray.Item(j).nameHolidayType);
    }
    ((wxTextCtrl*)win3_1->FindWindow(wxID_ADM_TEXTCTRL_HOL_EVT))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MySovetnicArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MySovetnicArray.GetCount();++j)   //��������� ��������� ������
    {
        LocArray.Add(MySovetnicArray.Item(j).nameSovetnic);
    }
    ((wxTextCtrl*)win3_1->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_K))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    ((wxTextCtrl*)win3_1->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_A))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    
    wxBoxSizer *hol_ins_loc = new wxBoxSizer(wxHORIZONTAL);
    hol_ins_loc->Add(new wxButton(win3_1,wxID_ADM_BUTTON_HOL_S_1,wxCAPTION_BUTTON_SAVE),0,wxALIGN_RIGHT|wxRIGHT,0);
    hol_ins_loc->Add(new wxButton(win3_1,wxID_ADM_BUTTON_HOL_D_1,wxCAPTION_BUTTON_CANCEL),0,wxALIGN_RIGHT|wxRIGHT,0);
    paneSz3_1->Add(hol_ins_loc, 1, wxEXPAND|wxALL, 10);
    win3_1->SetSizer(paneSz3_1);
    paneSz3_1->SetSizeHints(win3_1);
    
    wxCollapsiblePane *collpane3_2 = new wxCollapsiblePane(win3, wxID_ADM_COLLPANE_HOL_UPD, wxCAPTION_COLLPANE_EDIT, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win3_2 = collpane3_2->GetPane();
    wxSizer *paneSz3_2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *paneSz3_2_loc_hr = new wxBoxSizer(wxHORIZONTAL);
    paneSz3_2->Add(new wxStaticText(win3_2,wxID_ANY,wxCAPTION_STATICTEXT_EVENT), 0, wxEXPAND|wxALL, 1);
    paneSz3_2->Add(new wxTextCtrl(win3_2,wxID_ADM_TEXTCTRL_HOL_EVT_U), 0, wxEXPAND|wxALL, 1);
    paneSz3_2_loc_hr->Add(new wxStaticText(win3_2,wxID_ANY,wxCAPTION_STATICTEXT_S), 0, wxEXPAND|wxALL, 1);
    paneSz3_2_loc_hr->Add(new wxDatePickerCtrl(win3_2,wxID_ADM_DATECTRL_HOL_ON1_U,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxALL, 1);
    paneSz3_2_loc_hr->Add(new wxStaticText(win3_2,wxID_ANY,wxCAPTION_STATICTEXT_PO), 0, wxEXPAND|wxALL, 1);
    paneSz3_2_loc_hr->Add(new wxDatePickerCtrl(win3_2,wxID_ADM_DATECTRL_HOL_OF2_U,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxALL, 1);
    paneSz3_2->Add(paneSz3_2_loc_hr, 0, wxEXPAND|wxALL, 1);
    paneSz3_2->Add(new wxStaticText(win3_2,wxID_ANY,wxCAPTION_STATICTEXT_ZAMKAND), 0, wxEXPAND|wxALL, 1);
    paneSz3_2->Add(new wxTextCtrl(win3_2,wxID_ADM_TEXTCTRL_HOL_Z_K_U), 0, wxEXPAND|wxALL, 1);
    paneSz3_2->Add(new wxStaticText(win3_2,wxID_ANY,wxCAPTION_STATICTEXT_ZAMTO), 0, wxEXPAND|wxALL, 1);
    paneSz3_2->Add(new wxTextCtrl(win3_2,wxID_ADM_TEXTCTRL_HOL_Z_A_U), 0, wxEXPAND|wxALL, 1);
    LocArray.Alloc(MyHolidayTypeArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MyHolidayTypeArray.GetCount();++j)   //��������� ��������� ������
    {
        LocArray.Add(MyHolidayTypeArray.Item(j).nameHolidayType);
    }
    ((wxTextCtrl*)win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_EVT_U))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MySovetnicArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MySovetnicArray.GetCount();++j)   //��������� ��������� ������
    {
        LocArray.Add(MySovetnicArray.Item(j).nameSovetnic);
    }
    ((wxTextCtrl*)win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_K_U))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    ((wxTextCtrl*)win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_A_U))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    
    wxBoxSizer *hol_upd_loc = new wxBoxSizer(wxHORIZONTAL);
    hol_upd_loc->Add(new wxButton(win3_2,wxID_ADM_BUTTON_HOL_S_1_U,wxCAPTION_BUTTON_SAVE),0,wxALIGN_RIGHT|wxRIGHT,0);
    hol_upd_loc->Add(new wxButton(win3_2,wxID_ADM_BUTTON_HOL_D_1_U,wxCAPTION_BUTTON_CANCEL),0,wxALIGN_RIGHT|wxRIGHT,0);
    paneSz3_2->Add(hol_upd_loc, 1, wxEXPAND|wxALL, 10);
    win3_2->SetSizer(paneSz3_2);
    paneSz3_2->SetSizeHints(win3_2);
    
    wxBoxSizer *hol_vert = new wxBoxSizer(wxVERTICAL);
    hol_vert->Add(collpane3_1, 0, wxEXPAND|wxALL, 0);
    hol_vert->Add(collpane3_2, 0, wxEXPAND|wxALL, 0);
    hol_vert->Add(new wxButton(win3,wxID_ADM_BUTTON_HOL_DEL, wxCAPTION_BUTTON_DELETE), 0, wxEXPAND|wxALL, 0);
    
    paneSz3->Add(listview3, 1, wxEXPAND|wxALL, 5);
    paneSz3->Add(hol_vert, 0, wxEXPAND|wxALL, 5);
    win3->SetSizer(paneSz3);
    paneSz3->SetSizeHints(win3);
    
    vert_local_1->Add(hr_propgrid,0,wxEXPAND,0);
    vert_local_1->Add(collpane1,0,wxEXPAND|wxALL,5);
    vert_local_1->Add(collpane2,0,wxEXPAND|wxALL,5);
    vert_local_1->Add(collpane3,0,wxEXPAND|wxALL,5); 
    
    hr_sub_page_sov->Add(vert_local_2,1,wxEXPAND,0);
    hr_sub_page_sov->Add(vert_local_1,2,wxEXPAND,0);
    panel_sovetnic->SetSizer(hr_sub_page_sov);
}

void NotebookAdmin::CollapChanged (wxCollapsiblePaneEvent& event)
{
    switch (event.GetId())
    {
        case wxID_ADM_COLLPANE_SOV_REG:
        case wxID_ADM_COLLPANE_SOV_DOLZ:
        case wxID_ADM_COLLPANE_SOV_HOL:
        case wxID_ADM_COLLPANE_HOL_INS:
        case wxID_ADM_COLLPANE_HOL_UPD:
        case wxID_ADM_COLLPANE_SOV_R_1:
        case wxID_ADM_COLLPANE_SOV_D_1:
        case wxID_ADM_COLLPANE_SOV_D_2:
        {
            panel_sovetnic->Layout(); //������ �����������,   ����������� ����
            this->Refresh(); //�������������� ����
            break;
        }
        case wxID_ADM_BL_COLLPANE_SEARCH:
        {
            panel_bd->Layout(); //������ �����������,   ����������� ����
            this->Refresh(); //�������������� ����
            break;
        }
        case wxID_ADM_BL_COLLPANE_INS:
        {
            wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
            switch (combobox->GetCurrentSelection())
            {
                case 1: //������
                {
                    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_INS);
                    wxWindow *win2 = collpane2->GetPane();
                    wxSizer *sz = win2->GetSizer();
                    if (collpane2->IsCollapsed()) {win2->DestroyChildren(); sz->Clear();}
                    if (collpane2->IsExpanded()) 
                    {
                        wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
                        hr1->Add(new wxStaticText(win2,wxID_ANY,wxCAPTION_STATICTEXT_FIO),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        hr1->Add(new wxTextCtrl(win2,wxID_ADM_BL_TEXTCTRL_INS_1),1,wxEXPAND,0);
                        hr2->Add(new wxStaticText(win2,wxID_ANY,wxCAPTION_STATICTEXT_DATE_ROJD),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        hr2->Add(new wxDatePickerCtrl(win2,wxID_ADM_BL_DATECTRL_INS_1,  wxDefaultDateTime, wxDefaultPosition, wxDefaultSize,wxDP_DEFAULT),0,wxEXPAND,0);
                        hr3->Add(new wxStaticText(win2,wxID_ANY,wxCAPTION_STATICTEXT_DATA_SOURCE),0,wxEXPAND,0);
                        wxComboBox *combo = new wxComboBox(win2, wxID_ADM_BL_COMBOBOX_INS_1,wxEmptyString, wxDefaultPosition, wxDefaultSize,0,NULL, wxCB_DROPDOWN|wxCB_READONLY);
                        hr3->Add(combo,0,wxEXPAND,0);
                        hr4->Add(new wxButton(win2, wxID_ADM_BL_SAVE_INS_1,wxCAPTION_BUTTON_SAVE),0,wxEXPAND|wxALL,10);
                        hr4->Add(new wxButton(win2, wxID_ADM_BL_CANCEL_INS_1,wxCAPTION_BUTTON_CANCEL),0,wxEXPAND|wxALL,10);
                        
                        for(register int k =0; k<MyRootInfoArray.GetCount();++k) //��������� ���� ������ � ����������� 
                        {
                            combo->Append(MyRootInfoArray.Item(k).nameRootInfo);
                        }
                        
                        sz->Add(hr1,0,wxEXPAND,0);
                        sz->Add(hr2,0,wxEXPAND,0);
                        sz->Add(hr3,0,wxEXPAND,0);
                        sz->Add(new wxStaticText(win2,wxID_ANY,wxCAPTION_STATICTEXT_DOP_INFO),0,wxEXPAND,0);
                        sz->Add(new wxTextCtrl(win2,wxID_ADM_BL_TEXTCTRL_INS_2),0,wxEXPAND,0);
                        sz->Add(hr4,0,wxEXPAND,0);
                    }
                    break;
                }
                case 0: //�����
                {
                    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_INS);
                    wxWindow *win2 = collpane2->GetPane();
                    wxSizer *sz = win2->GetSizer();
                    if (collpane2->IsCollapsed()) {win2->DestroyChildren(); sz->Clear();}
                    if (collpane2->IsExpanded()) 
                    {
                        wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
                        hr1->Add(new wxStaticText(win2,wxID_ANY,wxCAPTION_STATICTEXT_TO),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        hr1->Add(new wxTextCtrl(win2,wxID_ADM_BL_TEXTCTRL_INS_1),1,wxEXPAND,0);
                        hr2->Add(new wxStaticText(win2,wxID_ANY,wxCAPTION_STATICTEXT_INN),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        hr2->Add(new wxTextCtrl(win2,wxID_ADM_BL_TEXTCTRL_INS_3),1,wxEXPAND,0);
                        ((wxTextCtrl*)win2->FindWindow(wxID_ADM_BL_TEXTCTRL_INS_3))->SetMaxLength(12); //������������� ����������� �� ���������� �������� �������� � ���� � ��� 
                        hr3->Add(new wxStaticText(win2,wxID_ANY,wxCAPTION_STATICTEXT_DATA_SOURCE),0,wxEXPAND,0);
                        wxComboBox *combo = new wxComboBox(win2, wxID_ADM_BL_COMBOBOX_INS_1,wxEmptyString, wxDefaultPosition, wxDefaultSize,0,NULL, wxCB_DROPDOWN|wxCB_READONLY);
                        hr3->Add(combo,0,wxEXPAND,0);
                        hr4->Add(new wxButton(win2, wxID_ADM_BL_SAVE_INS_1,wxCAPTION_BUTTON_SAVE),0,wxEXPAND|wxALL,10);
                        hr4->Add(new wxButton(win2, wxID_ADM_BL_CANCEL_INS_1,wxCAPTION_BUTTON_CANCEL),0,wxEXPAND|wxALL,10);
                        
                        for(register int k =0; k<MyRootInfoArray.GetCount();++k) //��������� ���� ������ � ����������� 
                        {
                            combo->Append(MyRootInfoArray.Item(k).nameRootInfo);
                        }
                        
                        sz->Add(hr1,0,wxEXPAND,0);
                        sz->Add(hr2,0,wxEXPAND,0);
                        sz->Add(hr3,0,wxEXPAND,0);
                        sz->Add(new wxStaticText(win2,wxID_ANY,wxCAPTION_STATICTEXT_DOP_INFO),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        sz->Add(new wxTextCtrl(win2,wxID_ADM_BL_TEXTCTRL_INS_2),0,wxEXPAND|wxALL,0);
                        sz->Add(hr4,0,wxEXPAND,0);
                    }
                    break;
                }
                default: break;
            }
            
            
            panel_bd->Layout(); //������ �����������,   ����������� ����
            this->Refresh(); //�������������� ����
            break;
        }
        case wxID_ADM_BL_COLLPANE_UPD:
        {
            wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
            switch (combobox->GetCurrentSelection())
            {
                case 1:
                {
                    wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_UPD);
                    wxWindow *win3 = collpane3->GetPane();
                    wxSizer *sz = win3->GetSizer();
                    if (collpane3->IsCollapsed()) {win3->DestroyChildren(); sz->Clear();}
                    if (collpane3->IsExpanded()) 
                    {
                        wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
                        hr1->Add(new wxStaticText(win3,wxID_ANY,wxCAPTION_STATICTEXT_FIO),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        hr1->Add(new wxTextCtrl(win3,wxID_ADM_BL_TEXTCTRL_UPD_1),1,wxEXPAND,0);
                        hr2->Add(new wxStaticText(win3,wxID_ANY,wxCAPTION_STATICTEXT_DATE_ROJD),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        hr2->Add(new wxDatePickerCtrl(win3,wxID_ADM_BL_DATECTRL_UPD_1,  wxDefaultDateTime, wxDefaultPosition, wxDefaultSize,wxDP_DEFAULT),0,wxEXPAND,0);
                        hr3->Add(new wxStaticText(win3,wxID_ANY,wxCAPTION_STATICTEXT_DATA_SOURCE),0,wxEXPAND,0);
                        wxComboBox *combo = new wxComboBox(win3, wxID_ADM_BL_COMBOBOX_UPD_1,wxEmptyString, wxDefaultPosition, wxDefaultSize,0,NULL, wxCB_DROPDOWN|wxCB_READONLY);
                        hr3->Add(combo,0,wxEXPAND,0);
                        hr4->Add(new wxButton(win3, wxID_ADM_BL_SAVE_UPD_1,wxCAPTION_BUTTON_SAVE),0,wxEXPAND|wxALL,10);
                        hr4->Add(new wxButton(win3, wxID_ADM_BL_CANCEL_UPD_1,wxCAPTION_BUTTON_CANCEL),0,wxEXPAND|wxALL,10);
                        
                        for(register int k =0; k<MyRootInfoArray.GetCount();++k) //��������� ���� ������ � ����������� 
                        {
                            combo->Append(MyRootInfoArray.Item(k).nameRootInfo);
                        }
                        
                        sz->Add(hr1,0,wxEXPAND,0);
                        sz->Add(hr2,0,wxEXPAND,0);
                        sz->Add(hr3,0,wxEXPAND,0);
                        sz->Add(new wxStaticText(win3,wxID_ANY,wxCAPTION_STATICTEXT_DOP_INFO),0,wxEXPAND,0);
                        sz->Add(new wxTextCtrl(win3,wxID_ADM_BL_TEXTCTRL_UPD_2),0,wxEXPAND,0);
                        sz->Add(hr4,0,wxEXPAND,0);
                        FillCollpaneBLUpd();
                    }
                    break;
                }
                case 0:
                {
                    wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_UPD);
                    wxWindow *win3 = collpane3->GetPane();
                    wxSizer *sz = win3->GetSizer();
                    if (collpane3->IsCollapsed()) {win3->DestroyChildren(); sz->Clear();}
                    if (collpane3->IsExpanded()) 
                    {
                        wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
                        wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
                        hr1->Add(new wxStaticText(win3,wxID_ANY,wxCAPTION_STATICTEXT_TO),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        hr1->Add(new wxTextCtrl(win3,wxID_ADM_BL_TEXTCTRL_UPD_1),1,wxEXPAND,0);
                        hr2->Add(new wxStaticText(win3,wxID_ANY,wxCAPTION_STATICTEXT_INN),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        hr2->Add(new wxTextCtrl(win3,wxID_ADM_BL_TEXTCTRL_UPD_3),1,wxEXPAND,0);
                        ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_3))->SetMaxLength(12); //������������� ����������� �� ���������� �������� �������� � ���� � ��� 
                        hr3->Add(new wxStaticText(win3,wxID_ANY,wxCAPTION_STATICTEXT_DATA_SOURCE),0,wxEXPAND,0);
                        wxComboBox *combo = new wxComboBox(win3, wxID_ADM_BL_COMBOBOX_UPD_1,wxEmptyString, wxDefaultPosition, wxDefaultSize,0,NULL, wxCB_DROPDOWN|wxCB_READONLY);
                        hr3->Add(combo,0,wxEXPAND,0);
                        hr4->Add(new wxButton(win3, wxID_ADM_BL_SAVE_UPD_1,wxCAPTION_BUTTON_SAVE),0,wxEXPAND|wxALL,10);
                        hr4->Add(new wxButton(win3, wxID_ADM_BL_CANCEL_UPD_1,wxCAPTION_BUTTON_CANCEL),0,wxEXPAND|wxALL,10);
                        
                        for(register int k =0; k<MyRootInfoArray.GetCount();++k) //��������� ���� ������ � ����������� 
                        {
                            combo->Append(MyRootInfoArray.Item(k).nameRootInfo);
                        }
                        
                        sz->Add(hr1,0,wxEXPAND,0);
                        sz->Add(hr2,0,wxEXPAND,0);
                        sz->Add(hr3,0,wxEXPAND,0);
                        sz->Add(new wxStaticText(win3,wxID_ANY,wxCAPTION_STATICTEXT_DOP_INFO),0,wxEXPAND|wxLEFT|wxRIGHT,5);
                        sz->Add(new wxTextCtrl(win3,wxID_ADM_BL_TEXTCTRL_UPD_2),0,wxEXPAND|wxALL,0);
                        sz->Add(hr4,0,wxEXPAND,0);
                        FillCollpaneBLUpd();
                    }
                    break;
                }
                default: break;
            }
            
            
            panel_bd->Layout(); //������ �����������,   ����������� ����
            this->Refresh(); //�������������� ����
            break;
        }
        default: {break;}
    }
    
    event.Skip();
}

void NotebookAdmin::FillCollpaneBLUpd (void)
{
    wxBannerWindow *banner = (wxBannerWindow*)panel_bd->FindWindow(wxID_ADM_BL_BANNER_DOP_INF);
    banner->SetText(wxNULL_STRING,wxNULL_STRING); //������� ���� ������� �� ������
    wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_UPD);
    wxWindow *win3 = collpane3->GetPane();
    if(collpane3->IsExpanded())
    {
        wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
        switch (combobox->GetCurrentSelection())
        {
            case 0: //�����
            {
                wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP); //��������� �� ��������� �� �������
                int sel_item = listview->GetFocusedItem(); //���������� ������ � ������� �����
                if(sel_item==-1) {break;} //������ �� ��������, ������� ��������� ���������
                int id_reestr_bl = listview->GetItemData(sel_item); //�������� ���� �� ���������� ������ ������ 
                if(id_reestr_bl==0) {;}
                else
                {
                    wxString sqlText;
                    sqlText<<wxSqlTextSelBlTo; sqlText<<id_reestr_bl; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                        //int num_fields = mysql_num_fields(res); // ���������� �����
                        int num_rows = mysql_num_rows(res); // � ���������� �����.
                        if(num_rows>0)
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_1))->ChangeValue(row[0]);
                            ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_3))->ChangeValue(row[1]);
                            for(register int k =0; k<MyRootInfoArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(!MyRootInfoArray.Item(k).idRootInfo.compare(row[2]))
                                if(MyRootInfoArray.Item(k).idRootInfo==wxAtoi(row[2]))
                                {
                                    wxComboBox *combo = (wxComboBox*)win3->FindWindow(wxID_ADM_BL_COMBOBOX_UPD_1);
                                    combo->SetSelection(combo->FindString(MyRootInfoArray.Item(k).nameRootInfo));
                                }
                            }
                            ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_2))->ChangeValue(row[3]);
                        } else {InformationSleep (wxWARNING_NOT_ID, sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // ������� ����������
                    }
                }
                break;
            }
            case 1: //������
            {
                wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP); //��������� �� ��������� �� �������
                int sel_item = listview->GetFocusedItem(); //���������� ������ � ������� �����
                if(sel_item==-1) {break;} //������ �� ��������, ������� ��������� ���������
                int id_reestr_bl = listview->GetItemData(sel_item); //�������� ���� �� ���������� ������ ������ 
                if(id_reestr_bl==0) {;}
                else
                {
                    wxString sqlText;
                    sqlText<<wxSqlTextSelBlFl; sqlText<<id_reestr_bl; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                        //int num_fields = mysql_num_fields(res); // ���������� �����
                        int num_rows = mysql_num_rows(res); // � ���������� �����.
                        if(num_rows>0)
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_1))->ChangeValue(row[0]); //���
                            wxString str=row[1]; //����� ���� �� ���������� ������� ������� � ����������
                            insertStrDateToCtrl (str, (wxDatePickerCtrl*)win3->FindWindow(wxID_ADM_BL_DATECTRL_UPD_1));
                            /*
                            wxDateTime dt;      //������� ������ ������ wxDateTime
                            wxString::const_iterator end; //������� �������� ����������� �� ����� ������, ��� ��� ����������� �������������� ������
                            dt.ParseDate(str, &end); //����������� ������ � ���������� ����
                            ((wxDatePickerCtrl*)win3->FindWindow(wxID_ADM_BL_DATECTRL_UPD_1))->SetValue(dt); //����������� ��������� �������� � ������� � �����
                            */
                            for(register int k =0; k<MyRootInfoArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(!MyRootInfoArray.Item(k).idRootInfo.compare(row[2]))
                                if(MyRootInfoArray.Item(k).idRootInfo==wxAtoi(row[2]))
                                {
                                    wxComboBox *combo = (wxComboBox*)win3->FindWindow(wxID_ADM_BL_COMBOBOX_UPD_1);
                                    combo->SetSelection(combo->FindString(MyRootInfoArray.Item(k).nameRootInfo)); //�������� ������
                                }
                            }
                            ((wxTextCtrl*)win3->FindWindow(wxID_ADM_BL_TEXTCTRL_UPD_2))->ChangeValue(row[3]); //�����������
                        } else {InformationSleep (wxWARNING_NOT_ID, sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // ������� ����������
                    }
                }
                break;
            }
            default:break;
        }
    }
    else{return;}
}

void NotebookAdmin::CollapsedPropgrid (wxPropertyGridEvent &event)
{
    switch (event.GetId())
    {   
        case wxID_ADM_PROPERTYGRID_SOV:
        {
            wxPropertyGrid* pD = ((wxPropertyGrid*)panel_sovetnic->FindWindow(wxID_ADM_PROPERTYGRID_SOV));
            int rowHeight = 0;
            int width = 0;
            pD->GetSize(&width, &rowHeight);
            rowHeight = pD->GetRowHeight();
            pD->SetSize(width,rowHeight);
            hr_propgrid->SetMinSize(width,rowHeight); //������ ����������� ������ ������������ � ��������� propgrid
            pD->FitColumns();
            panel_sovetnic->Layout(); //������ ���� ����������� ������������
            this->Refresh(); //�������������� ����
            
            break;
        }
        default:break;
    }
}

void NotebookAdmin::ExpandedPropgrid (wxPropertyGridEvent &event)
{
    switch (event.GetId())
    {   
        case wxID_ADM_PROPERTYGRID_SOV:
        {
            wxPropertyGrid* pD = ((wxPropertyGrid*)panel_sovetnic->FindWindow(wxID_ADM_PROPERTYGRID_SOV));
            int rowHeight = 0;
            int width = 0;
            pD->GetSize(&width, &rowHeight);
            rowHeight = 8*pD->GetRowHeight();
            pD->SetSize(width,rowHeight);
            hr_propgrid->SetMinSize(width,rowHeight);
            pD->FitColumns();
            panel_sovetnic->Layout();
            this->Refresh();
            break;
        }
        default:break;
    }
}

void NotebookAdmin::OnEnter (wxCommandEvent& event)
{
    switch(event.GetId())
    {
        case wxID_ADM_SEARCH_SOV_FIO:
        {
            wxListView *listview = (wxListView*)(panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP));
            wxString textPoisk = ((wxSearchCtrl*)(panel_sovetnic->FindWindow(wxID_ADM_SEARCH_SOV_FIO)))->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
            textPoisk.MakeUpper(); //�������� ��� ������� � �������� ��������
            if(textPoisk.IsEmpty()) {InformationSleep (wxINFO_EMPTY_POISK, sec_for_sleep_window_info, this);} //���� ������ ������ �����, ������������� �� ���� ������������
            else 
            {
                for(register int i=0;i<listview->GetItemCount();++i) 
                {
                    if(((listview->GetItemText(i)).MakeUpper()).Find(textPoisk)!=wxNOT_FOUND)
                    {
                        listview->Select(i,true); //�������� ������
                        listview->Focus(i);
                    }
                    else
                    {
                        listview->Select(i,false); //������� ���������� ������
                    }
                }
                listview->SetFocus();
            }
            break;
        }
        case wxID_ADM_BL_SEARCH:
        {
            wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP);
            wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
            wxString textPoisk = ((wxSearchCtrl*)(panel_bd->FindWindow(wxID_ADM_BL_SEARCH)))->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
            textPoisk.MakeUpper(); //�������� ��� ������� � �������� ��������
            if(textPoisk.IsEmpty()) {InformationSleep (wxINFO_EMPTY_POISK, sec_for_sleep_window_info, this);} //���� ������ ������ �����, ������������� �� ���� ������������
            else 
            {
                switch (combobox->GetCurrentSelection())
                {
                    case 0:
                    case 1:
                    {
                        for(register int i=0;i<listview->GetItemCount();++i) 
                        {
                            if(((listview->GetItemText(i)).MakeUpper()).Find(textPoisk)!=wxNOT_FOUND)
                            {
                                listview->Select(i,true); //�������� ������
                                listview->Focus(i);
                            }
                            else
                            {
                                listview->Select(i,false); //������� ���������� ������
                            }
                        }
                        listview->SetFocus();
                        break;
                    }
                    default:break;
                }
            }
            break;
        }
        default:break;
    }
}

void NotebookAdmin::LoadHolidayForSov(void)
{
    wxListView *listviewhol = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_SOV_LISTVIEW_HOL);
    listviewhol->DeleteAllItems();
    wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
    int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
    if(id_sov==0) {return;}
    wxString sqlText;
    sqlText<<wxSqlTextSelHistoryHolSov; sqlText<<id_sov; sqlText<<wxSqlEndText;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_fields = mysql_num_fields(res); // ���������� �����
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            for (register int i = 0; i < num_rows; i++) // ����� �������
            {
                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                f->SetColumn(0);
                f->SetData(wxAtoi(row[0])); //������ ���������� ����
                f->SetId(i);
                listviewhol->InsertItem(*f); 
                for(register int k =0; k<MyHolidayTypeArray.GetCount();++k) //��������� ���� ������ � ����������� 
                {
                    //if(wxAtoi(MyHolidayTypeArray.Item(k).idHolidayType)==wxAtoi(row[3])) //���������� �������
                    if(MyHolidayTypeArray.Item(k).idHolidayType==wxAtoi(row[3])) //���������� �������
                    {
                        listviewhol->SetItem(i,0,MyHolidayTypeArray.Item(k).nameHolidayType);
                        break; //������� �� ���������� �����
                    }
                }
                listviewhol->SetItem(i,1,row[1]);
                listviewhol->SetItem(i,2,row[2]);
                listviewhol->SetItem(i,3,row[4]);
                listviewhol->SetItem(i,4,row[5]);
                delete f;
            }
            for (register int i=0; i<(listviewhol->GetColumnCount());++i) {listviewhol->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
        }
        mysql_free_result(res); // ������� ����������
    }   
}
void NotebookAdmin::LoadRegionForSov(void)
{
    wxListView *listviewreg = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_R);
    listviewreg->DeleteAllItems();
    wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
    int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
    if(id_sov==0) {return;}
    int item_list = 0;
    for(register int i =0; i<MySovConnectRegArray.GetCount();++i)       //��������� ���� ������ ���������� 
    {
        //if (id_sov==wxAtoi(MySovConnectRegArray.Item(i).idSovetnic))
        if (id_sov==MySovConnectRegArray.Item(i).idSovetnic)
        {
            wxListItem *f = new wxListItem();
            f->SetState(wxLIST_STATE_FOCUSED);
            f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
            f->SetColumn(0);
            //f->SetData(wxAtoi(MySovConnectRegArray.Item(i).idReestr)); //������ ���������� ����
            f->SetData(MySovConnectRegArray.Item(i).idReestr); //������ ���������� ����
            f->SetId(item_list);
            listviewreg->InsertItem(*f);
            int flag_reg=0; //���� ����, ��� ������ ������ � �� ����� �������� � ��������� ���� 
            for (register int j =0; j<MyMacroregArray.GetCount();++j)       //��������� ���� ������ ���������� 
            {
                //if(!MySovConnectRegArray.Item(i).idRegion.compare(MyMacroregArray.Item(j).idMacroreg))
                if(MySovConnectRegArray.Item(i).idRegion==MyMacroregArray.Item(j).idMacroreg)
                {listviewreg->SetItem(item_list,0,"��"); listviewreg->SetItem(item_list,1,MyMacroregArray.Item(j).nameMacroreg); flag_reg=1; break;}
            }
            if(flag_reg==0)
            {
                for (register int j =0; j<MyOcArray.GetCount();++j)       //��������� ���� ������ ���������� 
                {
                    //if(!MySovConnectRegArray.Item(i).idRegion.compare(MyOcArray.Item(j).idOc))
                    if(MySovConnectRegArray.Item(i).idRegion==MyOcArray.Item(j).idOc)
                    {listviewreg->SetItem(item_list,0,"��"); listviewreg->SetItem(item_list,1,MyOcArray.Item(j).nameOc); flag_reg=1; break;}
                }
            }
            if(flag_reg==0)
            {
                for (register int j =0; j<MyGcArray.GetCount();++j)       //��������� ���� ������ ���������� 
                {
                    //if(!MySovConnectRegArray.Item(i).idRegion.compare(MyGcArray.Item(j).idGc))
                    if(MySovConnectRegArray.Item(i).idRegion==MyGcArray.Item(j).idGc)
                    {listviewreg->SetItem(item_list,0,"��"); listviewreg->SetItem(item_list,1,MyGcArray.Item(j).nameGc); flag_reg=1; break;}
                }
            }
            listviewreg->SetItem(item_list,2,wxString::Format(L"%i",MySovConnectRegArray.Item(i).activ));
            listviewreg->SetItem(item_list,3,MySovConnectRegArray.Item(i).dateChange);
            for (register int i=0; i<(listviewreg->GetColumnCount());++i) {listviewreg->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
            ++item_list;
            delete f;                      
        }      
    }   
}
void NotebookAdmin::LoadDolzForSov(void)
{
    wxListView *listviewdol = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_D);
    listviewdol->DeleteAllItems();
    wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
    int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
    if(id_sov==0) {return;}
    int item_list = 0;
    for(register int i =0; i<MyPositionSotrHistoryArray.GetCount();++i)       //��������� ���� ������ ���������� 
    {
        //if (id_sov==wxAtoi(MyPositionSotrHistoryArray.Item(i).idSotr))
        if (id_sov==MyPositionSotrHistoryArray.Item(i).idSotr)
        {
            wxListItem *f = new wxListItem();
            f->SetState(wxLIST_STATE_FOCUSED);
            f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
            f->SetColumn(0);
            //f->SetData(wxAtoi(MyPositionSotrHistoryArray.Item(i).idReestr)); //������ ���������� ����
            f->SetData(MyPositionSotrHistoryArray.Item(i).idReestr); //������ ���������� ����
            f->SetId(item_list);
            listviewdol->InsertItem(*f); 
            for (register int j =0; j<MyPositionSotrArray.GetCount();++j)       //��������� ���� ������ ���������� 
            {
                //if(!MyPositionSotrHistoryArray.Item(i).idPosition.compare(MyPositionSotrArray.Item(j).idPosition))
                if(MyPositionSotrHistoryArray.Item(i).idPosition==MyPositionSotrArray.Item(j).idPosition)
                {listviewdol->SetItem(item_list,0,MyPositionSotrArray.Item(j).namePosition.Capitalize()); break;}
            }
            listviewdol->SetItem(item_list,1,wxString::Format(L"%i",MyPositionSotrHistoryArray.Item(i).activ));
            listviewdol->SetItem(item_list,2,MyPositionSotrHistoryArray.Item(i).dateOn);
            listviewdol->SetItem(item_list,3,MyPositionSotrHistoryArray.Item(i).dateOff);
            for (register int i=0; i<(listviewdol->GetColumnCount());++i) {listviewdol->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
            ++item_list;
            delete f;                      
        }      
    }   
}
void NotebookAdmin::LoadPersDanForSov(void)
{
    wxListView *listview = (wxListView*)panel_sovetnic->FindWindow(wxID_ADM_LISTVIEW_SOV_SP); //��������� �� ������ ����������
    int id_sov = listview->GetItemData(listview->GetFocusedItem()); //�������� ���� ��������� �� ���������� ������ ������ ����������
    if(id_sov==0) {return;}
    wxPropertyGrid *pD = (wxPropertyGrid*)panel_sovetnic->FindWindow(wxID_ADM_PROPERTYGRID_SOV);
    wxPGProperty *pgp1 = pD->GetProperty(wxString("pd"));
    if(pgp1) 
    {
        wxPGProperty *pgp1_1 = pgp1->GetPropertyByName("fio");
        wxDateProperty *pgp1_2 = (wxDateProperty*)pgp1->GetPropertyByName("dr");
        wxPGProperty *pgp1_3 = pgp1->GetPropertyByName("tel");
        wxDateProperty *pgp1_4 = (wxDateProperty*)pgp1->GetPropertyByName("dete_open");
        wxDateProperty *pgp1_5 = (wxDateProperty*)pgp1->GetPropertyByName("date_close");
        wxBoolProperty *pgp1_6 = (wxBoolProperty*)pgp1->GetPropertyByName("activ");
        if(pgp1_1) {pgp1_1->SetValue(listview->GetItemText(listview->GetFocusedItem(),0));}
        if(pgp1_2&&pgp1_3&&pgp1_4&&pgp1_5&&pgp1_6)
        {
            for(register int i =0; i<MySovetnicArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                //if (id_sov==wxAtoi(MySovetnicArray.Item(i).idSovetnic))
                if (id_sov==MySovetnicArray.Item(i).idSovetnic)
                {
                    wxDateTime dt;      //������� ������ ������ wxDateTime
                    wxDateTime dt_on;      //������� ������ ������ wxDateTime
                    wxDateTime dt_off;      //������� ������ ������ wxDateTime
                    wxString::const_iterator end; //������� �������� ����������� �� ����� ������, ��� ��� ����������� �������������� ������
                    dt.ParseDate(MySovetnicArray.Item(i).drSovetnic, &end); //����������� ������ � ���������� ����
                    dt_on.ParseDate(MySovetnicArray.Item(i).dateOpen, &end); //����������� ������ � ���������� ����
                    dt_off.ParseDate(MySovetnicArray.Item(i).dateClose, &end); //����������� ������ � ���������� ����
                    pgp1_2->SetDateValue(dt);
                    pgp1_3->SetValue(MySovetnicArray.Item(i).pfoneSovetnic);
                    pgp1_4->SetDateValue(dt_on);
                    pgp1_5->SetDateValue(dt_off);
                    //if (!MySovetnicArray.Item(i).activSovetnic.compare("1")) {pgp1_6->SetChoiceSelection(1);} else {pgp1_6->SetChoiceSelection(0);}      
                    if (MySovetnicArray.Item(i).activSovetnic==1) {pgp1_6->SetChoiceSelection(1);} else {pgp1_6->SetChoiceSelection(0);}                  
                    break;
                }      //���������� �������
            }
        }
        pgp1->SetValue(pgp1->GenerateComposedValue());
        pD->Refresh();  //�������������� ����, ����� ��������� ���������� ���� � ��������� ���������
    }  
}
void NotebookAdmin::FocusedItemListview (wxListEvent& event)
{
    switch (event.GetId())
    {
        case wxID_ADM_BL_LISTVIEW_SP: //��������� ������ � �� -> � ��������� ������ � �������������� ������, ���� ������ �������.
        {
            FillCollpaneBLUpd();
            break;
        }
        case wxID_ADM_LISTVIEW_SOV_SP:
        {
            LoadPersDanForSov();
            LoadDolzForSov();
            LoadRegionForSov();
            LoadHolidayForSov();
            break;
        }
        case wxID_ADM_SOV_LISTVIEW_HOL:
        {
            wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_HOL)); //�������� ��������� �� �������� ������
            wxWindow *win3 = collpane3->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxListView *listviewhol = (wxListView*)(win3->FindWindow(wxID_ADM_SOV_LISTVIEW_HOL)); //��������� �� ������� � �����������
            int id_select = event.GetIndex(); //�������� ������ ��������� ������
            if(id_select==0) {break;}
            
            wxCollapsiblePane *collpane3_2 = (wxCollapsiblePane*)(win3->FindWindow(wxID_ADM_COLLPANE_HOL_UPD)); //��������� �� ��������� �������� ������
            wxWindow *win3_2 = collpane3_2->GetPane(); //��������� �� ���� ����������� � ��������� �������� ������
            wxTextCtrl* textCtrl = (wxTextCtrl*)(win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_EVT_U));             //��������� �� ��������� ��������
            wxDatePickerCtrl* dateCtrl1 = (wxDatePickerCtrl*)(win3_2->FindWindow(wxID_ADM_DATECTRL_HOL_ON1_U)); //��������� �� ������� ���������� � �����
            wxDatePickerCtrl* dateCtrl2 = (wxDatePickerCtrl*)(win3_2->FindWindow(wxID_ADM_DATECTRL_HOL_OF2_U)); //��������� �� ������� ���������� � �����
            wxTextCtrl* textCtrlK = (wxTextCtrl*)(win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_K_U));             //��������� �� ��������� ��������
            wxTextCtrl* textCtrlA = (wxTextCtrl*)(win3_2->FindWindow(wxID_ADM_TEXTCTRL_HOL_Z_A_U));             //��������� �� ��������� ��������
            
            wxString strEvt, strDateOn, strDateOff, strZamKand, strZamAgent; //����������
            
            strEvt = listviewhol->GetItemText(id_select,0);
            strDateOn = listviewhol->GetItemText(id_select,1);
            strDateOff = listviewhol->GetItemText(id_select,2);
            strZamKand = listviewhol->GetItemText(id_select,3);
            strZamAgent = listviewhol->GetItemText(id_select,4);
            
            textCtrl->ChangeValue(strEvt);
            if(strZamKand.IsEmpty()) {textCtrlK->Clear();} else {textCtrlK->ChangeValue(strZamKand);}
            if(strZamAgent.IsEmpty()) {textCtrlA->Clear();} else {textCtrlA->ChangeValue(strZamAgent);}
            if(!strDateOn.IsEmpty()) 
            {
                insertStrDateToCtrl (strDateOn, (wxDatePickerCtrl*)win3_2->FindWindow(wxID_ADM_DATECTRL_HOL_ON1_U));
            }
            else
            {
                wxDateTime dt;
                ((wxDatePickerCtrl*)(win3_2->FindWindow(wxID_ADM_DATECTRL_HOL_ON1_U)))->SetValue(dt);
            }
            if(!strDateOff.IsEmpty())
            {
                insertStrDateToCtrl (strDateOff, (wxDatePickerCtrl*)win3_2->FindWindow(wxID_ADM_DATECTRL_HOL_OF2_U));
            }
            else
            {
                wxDateTime dt;
                ((wxDatePickerCtrl*)(win3_2->FindWindow(wxID_ADM_DATECTRL_HOL_OF2_U)))->SetValue(dt);
            }
            break;            
        }
        case wxID_ADM_LISTVIEW_SOV_D:
        {
            wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_DOLZ)); //�������� ��������� �� �������� ������
            wxWindow *win2 = collpane2->GetPane(); //�������� ��������� �� ���� ����������� � �����.������ 
            wxCollapsiblePane *collpane2_2 = (wxCollapsiblePane*)(win2->FindWindow(wxID_ADM_COLLPANE_SOV_D_2)); //��������� �� ��������� �������� ������
            wxWindow *win2_2 = collpane2_2->GetPane(); //��������� �� ���� ����������� � ��������� �������� ������
            wxString strDolz, strAct, strDateOp, strDateOff;
            wxListView *listviewD = (wxListView*)(win2->FindWindow(wxID_ADM_LISTVIEW_SOV_D)); //��������� �� ������� � �����������
            int item_select = listviewD->GetFocusedItem();
            strDolz = listviewD->GetItemText(item_select,0);
            strAct = listviewD->GetItemText(item_select,1);
            strDateOp = listviewD->GetItemText(item_select,2);
            strDateOff = listviewD->GetItemText(item_select,3);
            if(!strDolz.IsEmpty()) {((wxTextCtrl*)(win2_2->FindWindow(wxID_ADM_TEXTCTRL_N_D_2)))->ChangeValue(strDolz);}
            if(!strAct.compare("1")) {((wxCheckBox*)(win2_2->FindWindow(wxID_ADM_CHECK_D_1)))->SetValue(false);} else {((wxCheckBox*)(win2_2->FindWindow(wxID_ADM_CHECK_D_1)))->SetValue(true);} 
            if(!strDateOp.IsEmpty()) 
            {
                insertStrDateToCtrl (strDateOp, (wxDatePickerCtrl*)win2_2->FindWindow(wxID_ADM_DATECTRL_D_ON_2));
            }
            else
            {
                wxDateTime dt;
                ((wxDatePickerCtrl*)(win2_2->FindWindow(wxID_ADM_DATECTRL_D_ON_2)))->SetValue(dt);
            }
            if(!strDateOff.IsEmpty())
            {
                insertStrDateToCtrl (strDateOff, (wxDatePickerCtrl*)win2_2->FindWindow(wxID_ADM_DATECTRL_D_OF_2));
            }
            else
            {
                wxDateTime dt;
                ((wxDatePickerCtrl*)(win2_2->FindWindow(wxID_ADM_DATECTRL_D_OF_2)))->SetValue(dt);
            }
            break;
        }
        default:break;
    }
}
void NotebookAdmin::ChangeCombobox (wxCommandEvent& event)
{
    switch (event.GetId())
    {
        case wxID_ADM_COMBOBOX_LVL_R: //��������� ��������� �������� � ��������� � ����������� �� ���������� �������� � ���������
        {
            wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_sovetnic->FindWindow(wxID_ADM_COLLPANE_SOV_REG));
            wxWindow *win1 = collpane1->GetPane();
            wxCollapsiblePane *collpane1_1 = (wxCollapsiblePane*)(win1->FindWindow(wxID_ADM_COLLPANE_SOV_R_1));
            wxWindow *win1_1 = collpane1_1->GetPane();
            wxComboBox* comb = (wxComboBox*)(win1_1->FindWindow(wxID_ADM_COMBOBOX_LVL_R));
            ((wxTextCtrl*)win1_1->FindWindow(wxID_ADM_TEXTCTRL_N_R))->Clear();
            switch (comb->GetSelection())
            {
                case 0: //��
                {
                    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                    LocArray.Alloc(MyMacroregArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                    for(register int j =0; j<MyMacroregArray.GetCount();++j)   //��������� ��������� ������
                    {
                        //if(!MyMacroregArray.Item(j).activMacroreg.compare("1")) {LocArray.Add(MyMacroregArray.Item(j).nameMacroreg);}
                        if(MyMacroregArray.Item(j).activMacroreg==1) {LocArray.Add(MyMacroregArray.Item(j).nameMacroreg);}
                    }
                    ((wxTextCtrl*)win1_1->FindWindow(wxID_ADM_TEXTCTRL_N_R))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                    LocArray.Clear(); //������� ���������� ������� � ����������� ������
                    break;
                }
                case 1: //��
                {
                    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                    LocArray.Alloc(MyOcArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                    for(register int j =0; j<MyOcArray.GetCount();++j)   //��������� ��������� ������
                    {
                        //if(!MyOcArray.Item(j).activOc.compare("1")) {LocArray.Add(MyOcArray.Item(j).nameOc);}
                        if(MyOcArray.Item(j).activOc==1) {LocArray.Add(MyOcArray.Item(j).nameOc);}
                    }
                    ((wxTextCtrl*)win1_1->FindWindow(wxID_ADM_TEXTCTRL_N_R))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                    LocArray.Clear(); //������� ���������� ������� � ����������� ������
                    break;
                }
                case 2: //��
                {
                    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                    LocArray.Alloc(MyOcArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                    for(register int j =0; j<MyGcArray.GetCount();++j)   //��������� ��������� ������
                    {
                        //if(!MyGcArray.Item(j).activGc.compare("1")) {LocArray.Add(MyGcArray.Item(j).nameGc);}
                        if(MyGcArray.Item(j).activGc==1) {LocArray.Add(MyGcArray.Item(j).nameGc);}
                    }
                    ((wxTextCtrl*)win1_1->FindWindow(wxID_ADM_TEXTCTRL_N_R))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                    LocArray.Clear(); //������� ���������� ������� � ����������� ������
                    break;
                }
                default:break;
            }
            break;
        }
        case wxID_ADM_BL_COMBOBOX_T_BL: //��������� ������ ������ � ����������� �� ���������� ����(��, ��)
        {
            CreateBlList();
            break;
        }
        defaul:break;
    }
}
void NotebookAdmin::CreateBlList (void)
{
    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_INS);
    wxCollapsiblePane *collpane3 = (wxCollapsiblePane*)panel_bd->FindWindow(wxID_ADM_BL_COLLPANE_UPD);
    collpane2->Collapse(true); //����������� ���������� ������
    collpane3->Collapse(true); //����������� ���������� ������
    wxListView *listview = (wxListView*)panel_bd->FindWindow(wxID_ADM_BL_LISTVIEW_SP);
    wxComboBox *combobox = (wxComboBox*)panel_bd->FindWindow(wxID_ADM_BL_COMBOBOX_T_BL);
    wxBannerWindow *banner = (wxBannerWindow*)panel_bd->FindWindow(wxID_ADM_BL_BANNER_DOP_INF);
    banner->SetText(wxNULL_STRING,wxNULL_STRING); //������� ���� ������� �� ������
    listview->ClearAll();
    switch (combobox->GetCurrentSelection())
            {
                case 0:
                {
                    listview->InsertColumn(0,wxCAPTION_COLUMN_TO);
                    listview->InsertColumn(1,wxCAPTION_COLUMN_INN);
                    wxString sqlText; sqlText=wxSqlTextBlTo;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR); return;}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                        //int num_fields = mysql_num_fields(res); // ���������� �����
                        int num_rows = mysql_num_rows(res); // � ���������� �����.
                        if(num_rows>0)
                        {   
                            for (register int i = 0; i < num_rows; i++) // ����� �������
                            {
                                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                wxListItem *f = new wxListItem();
                                f->SetState(wxLIST_STATE_FOCUSED);
                                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                                f->SetColumn(0);
                                f->SetData(wxAtoi(row[2])); //������ ���������� ����
                                f->SetId(i);
                                listview->InsertItem(*f); 
                                listview->SetItem(i,0,row[0]);
                                listview->SetItem(i,1,row[1]);
                                delete f;
                            }
                            for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������  
                        } else {;}
                        mysql_free_result(res); // ������� ����������
                    }
                    break;
                }
                case 1:
                {
                    listview->InsertColumn(0,wxCAPTION_COLUMN_FIO);
                    listview->InsertColumn(1,wxCAPTION_COLUMN_DATE_ROJD);
                    wxString sqlText; sqlText=wxSqlTextBlFl;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR); return;}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                        //int num_fields = mysql_num_fields(res); // ���������� �����
                        int num_rows = mysql_num_rows(res); // � ���������� �����.
                        if(num_rows>0)
                        {   
                            for (register int i = 0; i < num_rows; i++) // ����� �������
                            {
                                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                wxListItem *f = new wxListItem();
                                f->SetState(wxLIST_STATE_FOCUSED);
                                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                                f->SetColumn(0);
                                f->SetData(wxAtoi(row[2])); //������ ���������� ����
                                f->SetId(i);
                                listview->InsertItem(*f); 
                                wxString strFio = row[0];
                                EditStringFioFull(strFio);
                                listview->SetItem(i,0,strFio);
                                listview->SetItem(i,1,row[1]);
                                delete f;
                            }
                            for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������  
                        } else {;}
                        mysql_free_result(res); // ������� ����������
                    }
                    break;
                }
                default:break;
            }
    wxWindow *win2 = collpane2->GetPane();
    wxWindow *win3 = collpane3->GetPane();
    wxSizer *sz2 = win2->GetSizer();
    wxSizer *sz3 = win3->GetSizer();
    win2->DestroyChildren(); sz2->Clear();
    win3->DestroyChildren(); sz3->Clear();
    panel_bd->Layout(); //������ �����������,   ����������� ����
    this->Refresh(); //�������������� ����
}
void NotebookAdmin::CreateSubNotebookBl (void)
{
    wxBoxSizer *hr_bos = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vert_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vert_2 = new wxBoxSizer(wxVERTICAL);
    wxComboBox *type_bl = new wxComboBox(panel_bd, wxID_ADM_BL_COMBOBOX_T_BL,wxEmptyString, wxDefaultPosition, wxDefaultSize,0,NULL, wxCB_DROPDOWN|wxCB_READONLY);
    type_bl->Append(wxCAPTION_COMBOBOX_BL_TO);
    type_bl->Append(wxCAPTION_COMBOBOX_BL_FL);
    vert_1->Add(type_bl,0,wxEXPAND,0);
    vert_1->Add(new wxListView(panel_bd, wxID_ADM_BL_LISTVIEW_SP),1,wxEXPAND,0);
    wxBannerWindow *banner = new wxBannerWindow(panel_bd, wxID_ADM_BL_BANNER_DOP_INF, wxBOTTOM);
    vert_1->Add(banner, 0, wxEXPAND);
    banner->SetText(wxNULL_STRING, wxNULL_STRING);
    banner->SetGradient(*wxWHITE,*wxLIGHT_GREY);
    
    wxCollapsiblePane *collpane1 = new wxCollapsiblePane(panel_bd, wxID_ADM_BL_COLLPANE_SEARCH, wxCAPTION_COLLPANE_SEARCH, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win1 = collpane1->GetPane();
    wxSizer *paneSz1 = new wxBoxSizer(wxHORIZONTAL);
    paneSz1->Add(new wxSearchCtrl(win1,wxID_ADM_BL_SEARCH, wxEmptyString,wxDefaultPosition,wxSize(250,-1),wxTE_PROCESS_ENTER|wxTE_LEFT),1,wxEXPAND,0);
    win1->SetSizer(paneSz1);
    paneSz1->SetSizeHints(win1);
    
    wxCollapsiblePane *collpane2 = new wxCollapsiblePane(panel_bd, wxID_ADM_BL_COLLPANE_INS, wxCAPTION_COLLPANE_INS, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win2 = collpane2->GetPane();
    wxSizer *paneSz2 = new wxBoxSizer(wxVERTICAL);
    win2->SetSizer(paneSz2);
    paneSz2->SetSizeHints(win2);
    
    wxCollapsiblePane *collpane3 = new wxCollapsiblePane(panel_bd, wxID_ADM_BL_COLLPANE_UPD, wxCAPTION_COLLPANE_EDIT, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
    wxWindow *win3 = collpane3->GetPane();
    wxSizer *paneSz3 = new wxBoxSizer(wxVERTICAL);
    win3->SetSizer(paneSz3);
    paneSz3->SetSizeHints(win3);
    
    vert_2->Add(collpane1,0,wxEXPAND,0);
    vert_2->Add(collpane2,0,wxEXPAND,0);
    vert_2->Add(collpane3,0,wxEXPAND,0);
    vert_2->Add(new wxButton(panel_bd,wxID_ADM_BL_BUTTON_DOP_INF,wxCAPTION_BUTTON_ADV_INF),0,wxEXPAND,0);
    vert_2->Add(new wxButton(panel_bd,wxID_ADM_BL_BUTTON_DEL,wxCAPTION_BUTTON_DELETE),0,wxEXPAND,0);
    
    hr_bos->Add(vert_1, 1, wxEXPAND|wxALL ,10);
    hr_bos->Add(vert_2, 0, wxEXPAND ,0);
    panel_bd->SetSizer(hr_bos);
}
void NotebookAdmin::CreateSubNotebookPrivilege (void)
{
    wxDir dir(wxGetCwd());
    if (dir.IsOpened())
{
    wxString str_full, str_first, str_last;
    wxBoxSizer *bos = new wxBoxSizer(wxVERTICAL);
    //wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBox *stBox= new wxStaticBox(panel_privkey,wxID_ANY,wxCAPTION_STATICBOX_USER);
    wxStaticBoxSizer *hr1 = new wxStaticBoxSizer(stBox,wxHORIZONTAL);
    wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vert_2_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vert_2_2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vert_2_3 = new wxBoxSizer(wxVERTICAL);
    
    hr2->Add(vert_2_1,1,wxEXPAND|wxALL,5);
    hr2->Add(vert_2_2,0,wxEXPAND|wxALL,15);
    hr2->Add(vert_2_3,1,wxEXPAND|wxALL,5);
    
    hr1->Add(new wxStaticText(panel_privkey,wxID_ANY, "�����: "),0,wxRIGHT,10);
    hr1->Add(new wxComboBox(panel_privkey,wxID_ADM_PV_COMBOBOX_P1),0,wxRIGHT,0);
    hr1->Add(new wxButton(panel_privkey,wxID_ADM_PV_BUTTOM_INS,wxCAPTION_BUTTON_INSERT),0,wxLEFT,15);
    hr1->Add(new wxButton(panel_privkey,wxID_ADM_PV_BUTTOM_DEL,wxCAPTION_BUTTON_DELETE),0,wxLEFT,5);
    vert_2_1->Add(new wxStaticText(panel_privkey,wxID_ANY, "���������� (���)"),0,wxBOTTOM,5);
    vert_2_1->Add(new wxListBox(panel_privkey,wxID_ADM_PV_LISTBOX_SP_P1),1,wxEXPAND|wxBOTTOM,0);
    str_first = dir.GetName(); str_last= wxRIGHTIND_ICO; str_full=str_first; str_full+=str_last;
    vert_2_2->Add(new wxBitmapButton(panel_privkey,wxID_ADM_PV_BUTTOM_TO,wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO))),0,wxFIXED_MINSIZE|wxALIGN_CENTRE|wxTOP,50);
    str_last= wxLEFTIND_ICO; str_full=str_first; str_full+=str_last;
    vert_2_2->Add(new wxBitmapButton(panel_privkey,wxID_ADM_PV_BUTTOM_FROM,wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO))),0,wxFIXED_MINSIZE|wxALIGN_CENTRE|wxTOP,10);
    vert_2_3->Add(new wxStaticText(panel_privkey,wxID_ANY, "���������� (������������)"),0,wxBOTTOM,5);
    vert_2_3->Add(new wxListBox(panel_privkey,wxID_ADM_PV_LISTBOX_SP_P2),1,wxEXPAND|wxBOTTOM,0);
    hr3->Add(new wxStaticText(panel_privkey,wxID_ADM_PV_STATICTEXT_2,wxNULL_STRING),1,wxEXPAND|wxALIGN_RIGHT ,0);
    hr4->Add(new wxStaticText(panel_privkey,wxID_ADM_PV_STATICTEXT_1,wxNULL_STRING),1,wxEXPAND|wxALIGN_RIGHT ,0);
    
    
    bos->Add(hr1,0,wxEXPAND|wxALL,5);
    bos->Add(hr2,2,wxEXPAND|wxALL,5);
    bos->Add(hr3,0,wxEXPAND|wxALL,5);
    bos->Add(hr4,1,wxEXPAND|wxALL,5);
    panel_privkey->SetSizer(bos);
    LoadPrivListbox();
    LoadLoginCombobox();
}
}

void NotebookAdmin::LoadPrivListbox (void)
{   
    if (!arrayIdPrivilege.IsEmpty()) {arrayIdPrivilege.Clear();}
    wxListBox* listbox = (wxListBox*)panel_privkey->FindWindow(wxID_ADM_PV_LISTBOX_SP_P1);
    if((listbox->GetCount())>0) {listbox->Clear();}
    wxString sqlText;
    sqlText = wxSqlTextSelAllPrivl;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
    else 
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
        for (;row;row=mysql_fetch_row(res))
        {
            arrayIdPrivilege.Add(wxAtoi(row[0]));
            listbox->Append(row[1]);
        }
        mysql_free_result(res);
    }
}    

void NotebookAdmin::LoadLoginCombobox (void)
{
    if (!arrayIdLogin.IsEmpty()) {arrayIdLogin.Clear();}
    wxComboBox* combobox = (wxComboBox*)panel_privkey->FindWindow(wxID_ADM_PV_COMBOBOX_P1);
    if(!combobox->IsListEmpty()) {combobox->Clear();}
    wxString sqlText;
    sqlText = wxSqlTextSelAllLogin;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
    else 
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
        for (;row;row=mysql_fetch_row(res))
        {
            arrayIdLogin.Add(wxAtoi(row[0]));
            combobox->Append(row[1]);
        }
        mysql_free_result(res);
    }
}

void NotebookAdmin::ComboBoxWork (wxCommandEvent& event)
{
    switch(event.GetId())
    {
        case wxID_ADM_PV_COMBOBOX_P1:
        {
            wxListBox* list = (wxListBox*)panel_privkey->FindWindow(wxID_ADM_PV_LISTBOX_SP_P2);
            if((list->GetCount())>0) {list->Clear();}
            if(!arrayIdReestrPriv.IsEmpty()) {arrayIdReestrPriv.Clear();}
            int selectComboItem = event.GetSelection();
            if(selectComboItem>=0)
            {
                int idLogin = arrayIdLogin[selectComboItem];
                wxString sqlText;
                sqlText = wxSqlTextSelLocPrivl; sqlText<<idLogin; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
                    for (;row;row=mysql_fetch_row(res))
                    {
                        arrayIdReestrPriv.Add(wxAtoi(row[0]));
                        list->Append(row[1]);
                    }
                    mysql_free_result(res);
                }
            }
            break;
        }
        default:break;
    }
}    
void NotebookAdmin::ListBoxWork (wxCommandEvent& event)   
{
    switch(event.GetId())
    {
        case wxID_ADM_PV_LISTBOX_SP_P1:
        case wxID_ADM_PV_LISTBOX_SP_P2:
        {
            wxListBox* list1 = (wxListBox*)panel_privkey->FindWindow(wxID_ADM_PV_LISTBOX_SP_P1);
            wxListBox* list2 = (wxListBox*)panel_privkey->FindWindow(wxID_ADM_PV_LISTBOX_SP_P2);
            if(list1->HasFocus()) {list2->SetSelection(wxNOT_FOUND); ((wxStaticText*)panel_privkey->FindWindow(wxID_ADM_PV_STATICTEXT_2))->SetLabel(wxNULL_STRING);}
            if(list2->HasFocus()) 
            {
                list1->SetSelection(wxNOT_FOUND);
                if(!(event.GetString()).compare("mr_reg")) 
                {
                    int item = list2->GetSelection();
                    if(item!=wxNOT_FOUND)
                    {
                        wxString sqlText;
                        sqlText=wxSqlTextSelIdMr; 
                        sqlText<<arrayIdReestrPriv.Item(item);
                        sqlText<<wxSqlEndText;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                        else 
                        {
                            MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
                            for(register int j =0; j<MySovetnicArray.GetCount();++j)   //caiieiyai eieaeuiue iannea
                            {
                                if(MySovetnicArray.Item(j).idSovetnic==wxAtoi(row[0])) 
                                {
                                    wxString strMrPriv; strMrPriv = "�������� ID ����������: "; strMrPriv += MySovetnicArray.Item(j).nameSovetnic;
                                    ((wxStaticText*)panel_privkey->FindWindow(wxID_ADM_PV_STATICTEXT_2))->SetLabel(strMrPriv); 
                                    break;
                                }
                            }
                            mysql_free_result(res);
                        }
                    }
                } else {((wxStaticText*)panel_privkey->FindWindow(wxID_ADM_PV_STATICTEXT_2))->SetLabel(wxNULL_STRING);}
            }
            wxStaticText* text = (wxStaticText*)panel_privkey->FindWindow(wxID_ADM_PV_STATICTEXT_1);
            if(!(event.GetString()).compare("admin_global")) {text-> SetLabel("����� ����������� ��������������. ������� ������ ������ � ��: ������, ���.");}
            if(!(event.GetString()).compare("admin_holiday")) {text-> SetLabel("����� �������������� ��������. ������ ������������ ������ � �� ������. � �� ������ ������ ������ � ������� ����� \"������\", ������ \"���������\". ����� ������������� ����������� ��������� ����������� � ����������.");}
            if(!(event.GetString()).compare("mr_reg")) {text-> SetLabel("������� ���� - �����������. ������� ���� ����������� ����������� �� ��������� �����, �� ����������� admin_global. ��������, � ������ mr_reg + admin_holiday �������� � ����, ��� � ������� ����� \"������\" ����������� ������ ������ �� ����������� ����������� � ������������");}
            if(!(event.GetString()).compare("admin_dr")) {text-> SetLabel("����� �������������� ���� ��������. ������ ������ ������ � �� ���");}
            (panel_privkey->GetSizer())->Layout();
            //wxMessageBox(wxString::Format(wxT("%d"),arrayIdPrivilege[list->GetSelection()]));
            break;
        }
        default:break;
    }
}    

NotebookAdmin::~NotebookAdmin()
{
}
