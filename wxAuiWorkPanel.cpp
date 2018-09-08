#include "CrossFrm.h"
extern MYSQL* conn;
extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;


BEGIN_EVENT_TABLE(wxAuiWorkPanel,wxFrame)
    EVT_SIZE(wxAuiWorkPanel::OnSize)
	EVT_MOVE_END(wxAuiWorkPanel::OnMove)
    EVT_TOOL(wxID_TOOLBAR_SEARCH_FL,wxAuiWorkPanel::OnButton)
    EVT_TOOL(wxID_TOOLBAR_COMMAND_FL,wxAuiWorkPanel::OnButton)
    EVT_TOOL(wxID_TOOLBAR_SEARCH_UL,wxAuiWorkPanel::OnButton)
    EVT_TOOL(wxID_TOOLBAR_PAGE_FL,wxAuiWorkPanel::OnButton)
    EVT_TOOL(wxID_TOOLBAR_PAGE_UL,wxAuiWorkPanel::OnButton)
    EVT_SEARCHCTRL_SEARCH_BTN(wxID_SEARCH_FLOATPANEL, wxAuiWorkPanel::SearchFL)
    EVT_TEXT_ENTER(wxID_SEARCH_FLOATPANEL, wxAuiWorkPanel::SearchFL)
    EVT_SEARCHCTRL_SEARCH_BTN(wxID_PS_SEARCHCTRL_POISK, wxAuiWorkPanel::SearchUL)
    EVT_SEARCHCTRL_CANCEL_BTN(wxID_PS_SEARCHCTRL_POISK, wxAuiWorkPanel::ClearSearchUL)
    EVT_TEXT_ENTER(wxID_PS_SEARCHCTRL_POISK, wxAuiWorkPanel::SearchUL)
    EVT_AUINOTEBOOK_PAGE_CHANGED(wxID_WORKPLACE_AUI_NOTEBOOK, wxAuiWorkPanel::ChangeNotebookPage)
    EVT_BUTTON(wxID_AG_CM_BUTTON_INS,wxAuiWorkPanel::OnButton)
	EVT_BUTTON(wxID_AG_CM_BUTTON_UPD,wxAuiWorkPanel::OnButton)
	EVT_BUTTON(wxID_AG_CM_BUTTON_DEL,wxAuiWorkPanel::OnButton)
	EVT_BUTTON(wxID_AG_CM_BUTTON_PRV,wxAuiWorkPanel::OnButton)
	EVT_BUTTON(wxID_AG_CM_BUTTON_CLR,wxAuiWorkPanel::OnButton)
	EVT_LIST_ITEM_FOCUSED(wxID_PS_LISTVIEW_RESULT,wxAuiWorkPanel::ChangeStringList)
	EVT_AUINOTEBOOK_PAGE_CLOSED(wxID_WORKPLACE_AUI_NOTEBOOK,wxAuiWorkPanel::ClosePage)
	EVT_AUINOTEBOOK_PAGE_CLOSED(wxID_PAGE_UL,wxAuiWorkPanel::ClosePage)
END_EVENT_TABLE()

wxAuiWorkPanel::wxAuiWorkPanel()
{}

wxAuiWorkPanel::wxAuiWorkPanel(
                        wxWindow *parent, 
                        wxWindowID id, 
                        const wxString &title, 
                        const wxPoint& pos, 
                        const wxSize& size , 
                        long style)
        : wxFrame(parent, id, title, pos, size, style)
{
    wxImage::AddHandler(new wxICOHandler);
    m_Manager.SetManagedWindow(this);
    CreateStatusBar(3);
    
    m_Notebook = new wxAuiNotebook(this, wxID_WORKPLACE_AUI_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 
    
    //wxAUI_NB_TOP |  wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_CLOSE_ON_ACTIVE_TAB | wxAUI_NB_MIDDLE_CLICK_CLOSE |wxAUI_NB_TAB_FIXED_WIDTH |wxAUI_NB_TAB_SPLIT  
    wxAUI_NB_DEFAULT_STYLE|wxNO_BORDER
    
    );
	m_Page1 = new ProvAgFrm(m_Notebook, wxID_PAGE_FL);
	m_Page2 = new ProvToFrm(m_Notebook, wxID_PAGE_UL);
	m_Notebook->AddPage(m_Page1, _("���������� ����"));
	m_Notebook->AddPage(m_Page2, _("����������� ����"));
    
    m_Manager.AddPane(m_Notebook, wxAuiPaneInfo().CenterPane().Resizable());
    m_Manager.AddPane(new wxSearchCtrl(this,wxID_SEARCH_FLOATPANEL, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT|wxTE_MULTILINE), 
    wxAuiPaneInfo().Top().Floatable(true).MinimizeButton().MaximizeButton().Layer(1).Position(1).Caption("����� ����������� ����").Name(_("search_fl")));
    
    CreateButtonPanel(); //������� ������ � ��������
    
    m_Notebook->SetArtProvider(( wxAuiTabArt *)new wxAuiSimpleTabArt()); //������ ������� ��� ������� ��������
    m_Manager.Update();
    
    CreateToolbar(); //������� ������
    CreatePanelSearchUL(); //������� ������ ������ ��.���
}
void wxAuiWorkPanel::CreateButtonPanel(void)
{
    wxPanel *pp = new wxPanel(this, wxID_ANY);
    pp->SetSizer(new wxBoxSizer(wxVERTICAL));
    (pp->GetSizer())->Add(new wxButton(pp,wxID_AG_CM_BUTTON_INS,wxCAPTION_BUTTON_INSERT), 0, wxEXPAND ,0);
    (pp->GetSizer())->Add(new wxButton(pp,wxID_AG_CM_BUTTON_UPD,wxCAPTION_BUTTON_UPDATE), 0, wxEXPAND ,0);
    (pp->GetSizer())->Add(new wxButton(pp,wxID_AG_CM_BUTTON_DEL,wxCAPTION_BUTTON_DELETE), 0, wxEXPAND ,0);
    (pp->GetSizer())->Add(new wxButton(pp,wxID_AG_CM_BUTTON_PRV,wxCAPTION_BUTTON_PROV), 0, wxEXPAND ,0);
    (pp->GetSizer())->Add(new wxButton(pp,wxID_AG_CM_BUTTON_CLR,wxCAPTION_BUTTON_CLEAR), 0, wxEXPAND ,0);
    m_Manager.AddPane(pp,wxAuiPaneInfo().Left().Floatable(true).MinimizeButton().MaximizeButton().Layer(1).Position(1).Caption("������� ��").Name(_("command_fl")).BestSize(70,130));
    m_Manager.Update();
}
void wxAuiWorkPanel::WorkStatusBar (void)
{
    if(m_Notebook->GetSelection()==m_Notebook->GetPageIndex(m_Page1)&&m_Notebook->GetPageIndex(m_Page1)!=wxNOT_FOUND)
    {
        wxString status1=wxCOUNT_FIND; status1<<m_Page1->count_find;
        wxString status2=wxCOUNT_ADD; status2<<m_Page1->count_add;
        this->SetStatusText(status1,1);
        this->SetStatusText(status2,2);
        this->SetStatusText(wxREADDY_,0);
    }
    if(m_Notebook->GetSelection()==m_Notebook->GetPageIndex(m_Page2)&&m_Notebook->GetPageIndex(m_Page2)!=wxNOT_FOUND)
    {
        wxString status1=wxCOUNT_PROV_TO; status1<<m_Page2->count_to_prov;
        wxString status2=wxCOUNT_PROV_SOTR; status2<<m_Page2->count_sotr_prov;
        wxString status3=wxCOUNT_ASSORTI; status3<<m_Page2->count_assorti;
        this->SetStatusText(status1,0);
        this->SetStatusText(status2,1);
        this->SetStatusText(status3,2);
    }    
}
void wxAuiWorkPanel::CreateToolbar(void)
{
    
    wxDir dir(wxGetCwd());
    if (!dir.IsOpened())
    {
        wxMessageBox(wxERROR_OPEN_PROGRAM,wxERROR);
        Destroy();
    }
    else
    {
        m_StdToolBar = new wxToolBar(this, wxID_TOOLBAR_CTRL, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTB_HORIZONTAL|wxTB_NODIVIDER|wxTB_FLAT);
        m_StdToolBar->SetToolBitmapSize(wxSize(12, 12));
                wxString str_full, str_first, str_last;
                
                str_first = dir.GetName(); str_last= wxSEARCHFL_ICO; str_full=str_first; str_full+=str_last;
                m_StdToolBar->AddTool(wxID_TOOLBAR_SEARCH_FL, _("search_toolbar_fl"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("������ ������ ����������� ����"));
                str_last= wxSEARCHUL_ICO; str_full=str_first; str_full+=str_last;
                m_StdToolBar->AddTool(wxID_TOOLBAR_SEARCH_UL, _("search_toolbar_ul"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("������ ������ ������������ ����"));
                str_last= wxGRIDBUTTON_ICO; str_full=str_first; str_full+=str_last;
                m_StdToolBar->AddTool(wxID_TOOLBAR_COMMAND_FL, _("command_toolbar_fl"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("������ ������ ����������� ����"));
                m_StdToolBar->SetToolLongHelp(wxID_TOOLBAR_SEARCH_FL,_("������/�������� ������"));
                m_StdToolBar->SetToolLongHelp(wxID_TOOLBAR_COMMAND_FL,_("������/�������� ������"));
                m_StdToolBar->SetToolLongHelp(wxID_TOOLBAR_SEARCH_UL,_("������/�������� ������"));
                m_StdToolBar->Realize();
                
                m_PageToolBar = new wxToolBar(this, wxID_TOOLBAR_CTRL_PAGE, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTB_HORIZONTAL|wxTB_NODIVIDER|wxTB_FLAT);
                m_PageToolBar->SetToolBitmapSize(wxSize(12, 12));
                str_last= wxAGENT_ICO; str_full=str_first; str_full+=str_last;
                m_PageToolBar->AddTool(wxID_TOOLBAR_PAGE_FL, _("page_fl"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("������� - ���������� ����"));
                str_last= wxTO_ICO; str_full=str_first; str_full+=str_last;
                m_PageToolBar->AddTool(wxID_TOOLBAR_PAGE_UL, _("page_ul"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("������� - ����������� ����"));
                m_PageToolBar->SetToolLongHelp(wxID_TOOLBAR_PAGE_FL,_("������/�������� �������"));
                m_PageToolBar->SetToolLongHelp(wxID_TOOLBAR_PAGE_UL,_("������/�������� �������"));
                m_PageToolBar->Realize();
                m_Manager.AddPane(m_StdToolBar, wxAuiPaneInfo().ToolbarPane().Top().Floatable(false));
                m_Manager.AddPane(m_PageToolBar, wxAuiPaneInfo().ToolbarPane().Top().Floatable(false));
        m_Manager.Update();
    }
}
void wxAuiWorkPanel::CreatePanelSearchUL(void)
{
    wxPanel *panel_search = new wxPanel(this, wxID_ANY);
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr_1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vert_1 = new wxBoxSizer(wxVERTICAL);
    wxString rboxName[] = {wxCAPTION_COLUMN_TO,wxCAPTION_COLUMN_INN,wxCAPTION_COLUMN_NET,wxCAPTION_COLUMN_SITE};
    wxString rboxType[] = {wxCAPTION_CTRL_CONTRAINS,wxCAPTION_CTRL_STARTS,wxCAPTION_CTRL_ENDS,wxCAPTION_CTRL_EQUAL,wxCAPTION_CTRL_NOTEQUAL};
    vert_1->Add(new wxRadioBox(panel_search,wxID_PS_RADIOBOX_NAME,wxCAPTION_RADIOBOX_POLE,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_ROWS), 0, wxEXPAND,0);
    vert_1->Add(new wxRadioBox(panel_search,wxID_PS_RADIOBOX_TYPE,wxCAPTION_RADIOBOX_TYPE,wxDefaultPosition,wxDefaultSize,sizeof(rboxType)/sizeof(wxString),rboxType,0,wxRA_SPECIFY_ROWS), 0, wxEXPAND,0);
    vert_bos->Add(new wxSearchCtrl(panel_search,wxID_PS_SEARCHCTRL_POISK, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT), 0, wxEXPAND,0);
    wxSearchCtrl* searchCtrl = (wxSearchCtrl*)panel_search->FindWindow(wxID_PS_SEARCHCTRL_POISK);
    //searchCtrl->SetDescriptiveText(wxString("������� �������� ��� ������ � ������� Enter ...")); //����� �� ��������� � ������ ������
    //searchCtrl->SetToolTip("������� �������� ��� ������ � ������� Enter ...");
    searchCtrl->ShowCancelButton(1); //������ �������� ������ ������
    //searchCtrl->SetForegroundColour(*wxBLACK);
    wxListView *listview = new wxListView(panel_search, wxID_PS_LISTVIEW_RESULT,wxDefaultPosition,wxDefaultSize,wxLC_REPORT|wxLC_SINGLE_SEL);
    listview->InsertColumn(0,wxCAPTION_COLUMN_TO);
    listview->InsertColumn(1,wxCAPTION_COLUMN_INN);
    listview->InsertColumn(2,wxCAPTION_COLUMN_NET);
    listview->InsertColumn(3,wxCAPTION_COLUMN_SITE);
    //listview->Connect(wxEVT_LEFT_DCLICK,wxMouseEventHandler(wxAuiWorkPanel::DClickMouse));
    hr_1->Add(vert_1, 0, wxEXPAND,0);
    hr_1->Add(listview, 1, wxEXPAND,0);

    vert_bos->Add(hr_1, 0, wxEXPAND,0);
    panel_search->SetSizer(vert_bos);
    m_Manager.AddPane(panel_search, wxAuiPaneInfo().Top().Floatable(true).MinimizeButton().MaximizeButton().Layer(2).Position(1).Caption("����� ������������ ����").Name(_("search_ul")));
    m_Manager.Update();
}
void wxAuiWorkPanel::ClosePage(wxAuiNotebookEvent& event)
{
    {
        size_t count = m_Notebook->GetPageCount ();
            int flag_compare=-1;
            for(register int i=0; i<count;++i)
            {
                if(((wxWindow*)m_Page1)==m_Notebook->GetPage(i)){flag_compare=i;}
            }
            if(flag_compare==-1) 
            {
                wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	       size_t i, count;
	       for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	       {		
		      if(all_panes.Item(i).name == "search_fl"||all_panes.Item(i).name == "command_fl")
		      {
			     all_panes.Item(i).Show(0);
			     m_Manager.Update();
		      }
	       }
                m_StdToolBar->EnableTool(wxID_TOOLBAR_SEARCH_FL,false);
	            m_StdToolBar->EnableTool(wxID_TOOLBAR_COMMAND_FL,false);
            } 
    } 
    {
        size_t count = m_Notebook->GetPageCount ();
            int flag_compare=-1;
            for(register int i=0; i<count;++i)
            {
                if(((wxWindow*)m_Page2)==m_Notebook->GetPage(i)) {flag_compare=i;}
            }
            if(flag_compare==-1) 
            {
                wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	       size_t i, count;
	       for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	       {		
		      if(all_panes.Item(i).name == "search_ul")
		      {
			     all_panes.Item(i).Show(0);
			     m_Manager.Update();
			     break;
		      }
	       }
                m_StdToolBar->EnableTool(wxID_TOOLBAR_SEARCH_UL,false);
            } 
    }
}
void wxAuiWorkPanel::OnButton(wxCommandEvent& event)
{
    switch(event.GetId())
    {
        case wxID_TOOLBAR_PAGE_FL:
        {
            size_t count = m_Notebook->GetPageCount ();
            int flag_compare=-1;
            for(register int i=0; i<count;++i)
            {
                if(((wxWindow*)m_Page1)==m_Notebook->GetPage(i)){flag_compare=i;}
            }
            if(flag_compare!=-1) 
            {
                m_Notebook->DeletePage(flag_compare);
                wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	       size_t i, count;
	       for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	       {		
		      if(all_panes.Item(i).name == "search_fl"||all_panes.Item(i).name == "command_fl")
		      {
			     all_panes.Item(i).Show(0);
			     m_Manager.Update();
			    
		      }
	       }
                m_StdToolBar->EnableTool(wxID_TOOLBAR_SEARCH_FL,false);
	            m_StdToolBar->EnableTool(wxID_TOOLBAR_COMMAND_FL,false);
            } 
            else 
            {
                m_Page1 = new ProvAgFrm(m_Notebook, wxID_PAGE_FL); 
                m_Notebook->AddPage(m_Page1, _("���������� ����"));
                m_StdToolBar->EnableTool(wxID_TOOLBAR_SEARCH_FL,true);
	            m_StdToolBar->EnableTool(wxID_TOOLBAR_COMMAND_FL,true);
            }
            
            break;
        }
        case wxID_TOOLBAR_PAGE_UL:
        {
            size_t count = m_Notebook->GetPageCount ();
            int flag_compare=-1;
            for(register int i=0; i<count;++i)
            {
                if(((wxWindow*)m_Page2)==m_Notebook->GetPage(i)) {flag_compare=i;}
            }
            if(flag_compare!=-1) 
            {
                m_Notebook->DeletePage(flag_compare);
                wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	       size_t i, count;
	       for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	       {		
		      if(all_panes.Item(i).name == "search_ul")
		      {
			     all_panes.Item(i).Show(0);
			     m_Manager.Update();
			     break;
		      }
	       }
                m_StdToolBar->EnableTool(wxID_TOOLBAR_SEARCH_UL,false);
            } 
            else 
            {
                m_Page2 = new ProvToFrm(m_Notebook, wxID_PAGE_UL); 
                m_Notebook->AddPage(m_Page2, _("����������� ����"));
                m_StdToolBar->EnableTool(wxID_TOOLBAR_SEARCH_UL,true);
            }
            
            break;
        }
        case wxID_TOOLBAR_SEARCH_FL:
        {
            wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	       size_t i, count;
	       for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	       {		
		      if(all_panes.Item(i).name == "search_fl")
		      {
			     all_panes.Item(i).Show(!all_panes.Item(i).IsShown());
			     m_Manager.Update();
			     break;
		      }
	       }
            break;
        }
        case wxID_TOOLBAR_COMMAND_FL:
        {
            wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	       size_t i, count;
	       for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	       {		
		      if(all_panes.Item(i).name == "command_fl")
		      {
			     all_panes.Item(i).Show(!all_panes.Item(i).IsShown());
			     m_Manager.Update();
			     break;
		      }
	       }
            break;
        }
        case wxID_TOOLBAR_SEARCH_UL:
        {
            wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	       size_t i, count;
	       for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	       {		
		      if(all_panes.Item(i).name == "search_ul")
		      {
			     all_panes.Item(i).Show(!all_panes.Item(i).IsShown());
			     m_Manager.Update();
			     break;
		      }
	       }
            break;
        }
        
        case wxID_AG_CM_BUTTON_CLR:
        {
            ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES))->DeleteAllItems(); 
            m_Page1->count_find=0; 
            m_Page1->count_add=0; 
            WorkStatusBar();
            break;
        }
        case wxID_AG_CM_BUTTON_INS:
        {
            EnterFz EntFz(this,0,0); 
            if(EntFz.ShowModal() == wxID_CANCEL) {;} else {WorkStatusBar();}
            (this->FindWindow(wxID_AG_CM_BUTTON_PRV))->SetFocus();
            break;
        }
        case wxID_AG_CM_BUTTON_UPD:
        {
            wxListView *listview = ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES)); //�������� ��������� �� ��������� 
            int count = 0;
            if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;} //�� ������� ������ ������, ������� ������� �� �����
            for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
            {
                EnterFz EntFz(this, idItem, 1); 
                if(EntFz.ShowModal() == wxID_CANCEL) {;} else 
                {
                    ++count; //������� ���-�� �����, ������� ���� ���������;
                } 
                if (count>0)
                {   
                    wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_UPD_COUNT; str<<count; //������ ������ � ���-��� ����������� �����
                    InformationSleep(str,sec_for_sleep_window_info,this);
                } else {;} //���� �� ������� �� ���� ������, �� ������������� �� ���� ������������ � ��������� ���������
                (this->FindWindow(wxID_AG_CM_BUTTON_UPD))->SetFocus();
            }
            break;
        }
        case wxID_AG_CM_BUTTON_DEL:
        {
            DeleteFz();
            WorkStatusBar();
            break;
        }
        case wxID_AG_CM_BUTTON_PRV:
        {
            wxListView *listview = ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES)); //�������� ��������� �� ��������� 
            if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;}
            for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
            {
                wxString idFz; //id ���.����
                wxString captionFioAndPasp; //���+������� � ��������� ����
            
                wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
                f->SetId(idItem); //������������� ������� ���������� ��������
                f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT); //���������� ������ ��������� � ���������
                listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
                idFz<<f->GetData(); //����� � ���������� ������ ��������� � ���������
                f->SetColumn(0); listview->GetItem(*f); //��������� �� ��������� ���
                captionFioAndPasp<<f->GetText(); captionFioAndPasp<<" "; //����� ��� � ����������
                f->SetColumn(1); listview->GetItem(*f); //��������� �� ��������� ����� ��������
                captionFioAndPasp<<f->GetText(); captionFioAndPasp<<" "; //����� ����� �������� � ����������
                f->SetColumn(2); listview->GetItem(*f); //��������� �� ��������� ����� ��������
                captionFioAndPasp<<f->GetText(); //����� ����� �������� � ����������
            
                wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
                wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
            /*
            ��������� �� ����� ������������ ������� ���������� ��������� ����.
            ���� ����� �� ����������, ��� ��������� ��������� �� ���������
            */
                long x = config->ReadLong("/FORM_AGENT_PROV/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
                long y = config->ReadLong("/FORM_AGENT_PROV/y", 0);
                long width = config->ReadLong("/FORM_AGENT_PROV/width", 0);
                long height = config->ReadLong("/FORM_AGENT_PROV/height", 0);
                if(x&&y&&width&&height) //��������� ������������ ��������� �� ini-�����
                {
                    ListProvFz ListPrFz(m_Page1,wxAtoi(idFz),captionFioAndPasp,wxID_ANY,wxPoint(x,y),wxSize(width,height)); //������� ���������� ���� � ���������� ���������� ���.���� � ���������� �� ���+�������
                    if(ListPrFz.ShowModal() == wxID_CANCEL) {;} else {;}
                }
                else                   //��������� ������������ �� ��������� �� ini-�����
                {
                    ListProvFz ListPrFz(m_Page1,wxAtoi(idFz),captionFioAndPasp); //������� ���������� ���� � ���������� ���������� ���.���� � ���������� �� ���+�������
                    if(ListPrFz.ShowModal() == wxID_CANCEL) {;} else {;}
                }
            }
            (this->FindWindow(wxID_AG_CM_BUTTON_PRV))->SetFocus();
            break;
        }

        default:break;
    }
}
void wxAuiWorkPanel::SearchFL (wxCommandEvent& event)
{
    wxString textPoisk = ((wxSearchCtrl*)this->FindWindow(wxID_SEARCH_FLOATPANEL))->GetValue();
    textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
    textPoisk.Replace("\n","",true);
    textPoisk.Replace("\r","",true);
    if(textPoisk.IsEmpty()) {InformationSleep (wxINFO_EMPTY_POISK, sec_for_sleep_window_info, this);} //���� ������ ������ �����, ������������� �� ���� ������������
    else 
    {
        textPoisk.Replace("?","_",true); //� �������� ������ ������ ? �� _ ��� sql-�������
        wxString sqlText, loctextPoisk;
        loctextPoisk = textPoisk;
        loctextPoisk.Replace(" ","",true); //� �������� ������ ������ ������ �� ������ ��������
        if(!loctextPoisk.IsNumber()) //����� �� ���
        {
            sqlText<<wxSqlTextPoiskFzFio;
            sqlText<<textPoisk; sqlText<<wxSqlPercentEnd;
        }
        else //����� �� ���������
        {
            sqlText<<wxSqlTextPoiskFzPasp;
            sqlText<<loctextPoisk; sqlText<<wxSqlPercentEnd;
        }
        //wxMessageBox(sqlText);
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
        else 
        {
            //wxMessageBox(sqlText);
            MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
            int num_fields = mysql_num_fields(res); // ���������� �����
            int num_rows = mysql_num_rows(res); // � ���������� �����.
            if(num_rows>0)
            {   
                (m_Page1->count_find)+=num_rows; //���������� ���������� ���������� ���-�� ���������� �����
                wxListView* listview = ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES));
                int lastItem=0;
                for (register int i = 0; i < num_rows; i++) // ����� �������
                {
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                    wxListItem *f = new wxListItem();
                    f->SetState(wxLIST_STATE_FOCUSED);
                    f->SetMask(wxLIST_MASK_TEXT);
                    f->SetColumn(0);
                    f->SetData(atoi(row[4])); //������ ���������� ����
                    f->SetId(i);
                    listview->InsertItem(*f); 
                    for (register int l = 0; l < num_fields-1; l++)
                    {
                        listview->SetItem(i,l,row[l]);
                    }
                    lastItem=i;
                    delete f;
                }
                for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                for(register int i =0; i<listview->GetItemCount();++i) {listview->Select(i,false);} //������� ��������� �����
                listview->Select(lastItem,true); //�������� ��������� ��������� ������
                listview->Focus(lastItem); //������������� ����� �� ��������� ��������� ������
                WorkStatusBar();        //������� ����� ���-�� ����� � ���������*/
            } else {InformationSleep (wxINFO_EMPTY_REZ_POISK_FZ, sec_for_sleep_window_info, this);}
            mysql_free_result(res); // ������� ����������
        }
    }
}

void wxAuiWorkPanel::SearchUL (wxCommandEvent& event)
{
    wxSearchCtrl *searchCtrl = ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK));
        wxRadioBox   *radioBoxPole = ((wxRadioBox*)this->FindWindow(wxID_PS_RADIOBOX_NAME));
        wxRadioBox   *radioBoxType = ((wxRadioBox*)this->FindWindow(wxID_PS_RADIOBOX_TYPE));
        wxListView   *listview = ((wxListView*)this->FindWindow(wxID_PS_LISTVIEW_RESULT));
        if(!searchCtrl->IsEmpty())
        {
            wxString textPoisk = searchCtrl->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
            textPoisk.Replace("\n","",true);
            textPoisk.Replace("\r","",true);
            textPoisk.Replace("?","_",true); //� �������� ������ ������ ? �� _ ��� sql-�������
            int selectPole = radioBoxPole->GetSelection(); //���������� ������ ����������� ��������
            int selectType = radioBoxType->GetSelection(); //���������� ������ ����������� ��������
            listview->DeleteAllItems(); //������� listview
            
            wxString sqlText; sqlText=wxSqlTextSelToPoisk;
            if(!(radioBoxPole->GetString(selectPole)).compare(wxCAPTION_COLUMN_TO)) {sqlText+=wxSqlTextSelToPoiskWhereName1;}
            if(!(radioBoxPole->GetString(selectPole)).compare(wxCAPTION_COLUMN_INN)) {sqlText+=wxSqlTextSelToPoiskWhereName2;}
            if(!(radioBoxPole->GetString(selectPole)).compare(wxCAPTION_COLUMN_NET)) {sqlText+=wxSqlTextSelToPoiskWhereName3;}
            if(!(radioBoxPole->GetString(selectPole)).compare(wxCAPTION_COLUMN_SITE)) {sqlText+=wxSqlTextSelToPoiskWhereName4;}
            
            if(!(radioBoxType->GetString(selectType)).compare(wxCAPTION_CTRL_CONTRAINS)) {sqlText+=wxSqlLike1; sqlText+=textPoisk; sqlText+=wxSqlPercentEnd;}
            if(!(radioBoxType->GetString(selectType)).compare(wxCAPTION_CTRL_STARTS)) {sqlText+=wxSqlLike2; sqlText+=textPoisk; sqlText+=wxSqlPercentEnd;}
            if(!(radioBoxType->GetString(selectType)).compare(wxCAPTION_CTRL_ENDS)) {sqlText+=wxSqlLike1; sqlText+=textPoisk; sqlText+=wxSqlStrongEnd;}
            if(!(radioBoxType->GetString(selectType)).compare(wxCAPTION_CTRL_EQUAL)) {sqlText+=wxSqlEqualString; sqlText+=textPoisk; sqlText+=wxSqlStringEnd;}
            if(!(radioBoxType->GetString(selectType)).compare(wxCAPTION_CTRL_NOTEQUAL)) {sqlText+=wxSqlNotEqualString; sqlText+=textPoisk; sqlText+=wxSqlStringEnd;}
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            else
            {
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                int num_fields = mysql_num_fields(res); // ���������� �����
                if(num_rows>0)
                {  
                    for (register int i = 0; i < num_rows; i++) // ����� �������
                    {                     
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                        f->SetColumn(0);
                        f->SetData(atoi(row[0])); //������ ���������� ����
                        f->SetId(i);
                        listview->InsertItem(*f); 
                        for (register int l = 1; l < num_fields; l++)
                        {
                            if(l==2) 
                            {
                                /*�� 30.05.2017 ���� � ��� ���� ��������� ���� bigint ��� decimal ��� �� ��������� ��������� � ������ ����� 0, �.�. ����� ����� ����� ���� ��������� � ��������� ��� �������� 0 ��������� zerofil �� �������������*/
                                wxString str = row[l];
                                if(str.Len()==9||str.Len()==11) {listview->SetItem(i,l-1,"0"+str);}
                                else {listview->SetItem(i,l-1,row[l]);}
                            }
                            else
                            {listview->SetItem(i,l-1,row[l]);}
                        }
                        delete f;
                    }
                    for (register int i = 0; i < listview->GetColumnCount(); i++) // ����� �������
                    {
                        listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� ��������
                    }
                } else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info,this);}
                mysql_free_result(res); // ������� ����������
            }
            event.Skip(false);
        } else {InformationSleep(wxINFO_EMPTY_POISK,sec_for_sleep_window_info,this); event.Skip(true); return;}
}
void wxAuiWorkPanel::ClearSearchUL (wxCommandEvent& event)
{
    wxSearchCtrl *searchCtrl = ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK));
    wxListView   *listview = ((wxListView*)this->FindWindow(wxID_PS_LISTVIEW_RESULT));
    searchCtrl->Clear();
    listview->DeleteAllItems();
}
void wxAuiWorkPanel::ChangeNotebookPage (wxAuiNotebookEvent& event)
{
    /*if(m_Notebook->GetSelection()==m_Notebook->GetPageIndex(m_Page1)&&m_Notebook->GetPageIndex(m_Page1)!=wxNOT_FOUND)
    {
        wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	    size_t i, count;
	    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	    {		
		    if((all_panes.Item(i).name == "search_fl")&&!all_panes.Item(i).IsShown())
		    {
			    all_panes.Item(i).Show(true);
			    //m_Manager.Update();
			    continue;
		    }
		    if((all_panes.Item(i).name == "command_fl")&&!all_panes.Item(i).IsShown())
		    {
			    all_panes.Item(i).Show(true);
			    //m_Manager.Update();
			    continue;
		    }
		    if((all_panes.Item(i).name == "search_ul")&&all_panes.Item(i).IsShown())
		    {
			    all_panes.Item(i).Show(false);
			    //m_Manager.Update();
			    continue;
		    }
	    }
	    m_Manager.Update();
    }
    if(m_Notebook->GetSelection()==m_Notebook->GetPageIndex(m_Page2)&&m_Notebook->GetPageIndex(m_Page2)!=wxNOT_FOUND)
    {
        wxAuiPaneInfoArray& all_panes = m_Manager.GetAllPanes();
	    size_t i, count;
	    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	    {		
		    if((all_panes.Item(i).name == "search_fl")&&all_panes.Item(i).IsShown())
		    {
			    all_panes.Item(i).Show(false);
			    //m_Manager.Update();
			    continue;
		    }
		    if((all_panes.Item(i).name == "command_fl")&&all_panes.Item(i).IsShown())
		    {
			    all_panes.Item(i).Show(false);
			    //m_Manager.Update();
			    continue;
		    }
		    if((all_panes.Item(i).name == "search_ul")&&!all_panes.Item(i).IsShown())
		    {
			    all_panes.Item(i).Show(true);
			    //m_Manager.Update();
			    continue;
		    }
	    }
	    m_Manager.Update();
    }
    WorkStatusBar(); //������ �������� ������ ����*/
    event.Skip(true);
}
void wxAuiWorkPanel::DeleteFz (void)
{
        wxListView *listview = ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES)); //�������� ��������� �� ���������  
        int count = 0; int acces = 0;
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
        {
            wxString stat; stat<<wxID_SUCCESS_OPERATION; stat<<wxINFO_DEL_FZ;
            for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
            {
                wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
                f->SetId(idItem); //������������� ������� ���������� ��������
                f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT); //���������� ������ ��������� � ���������
                listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
                wxString idFz; idFz<<f->GetData(); //����� � ���������� ������ ��������� � ���������
                if(!idFz.IsEmpty())
                {
                    wxString sqlText;
                    /*
                    sqlText = wxSqlTextDelFzProvStart; sqlText<<idFz; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
                    else 
                    {
                        ++count; //������� ���-�� �����, ������� ���� �������
                    }
                    sqlText.Clear(); //������� ����������
                    */
                    sqlText = wxSqlTextDelFzStart; sqlText<<idFz; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
                    else 
                    {
                        //if(count_add>0) {--count_add;} //������ �������� ����������� �������� ���-�� ����������� ��������.
                        acces=1; //���� ����, ��� ������ ��������� �������.
                        f->SetColumn(0);
                        listview->GetItem(*f);
                        stat<<f->GetText(); stat<<wxINFO_DEL_FZ_DOP1; stat<<count; stat<<wxSTR_NEW;
                        listview->SetItemTextColour(idItem, (*wxRED));
                        //listview->Select(idItem,false);
                        //listview->DeleteItem(idItem); 
                        //idItem = (int)listview->GetFirstSelected();
                    }  
                } else {wxMessageBox(wxWARNING_NO_DATA,wxATTENTION,wxOK,this);} 
                delete f;
            }
            if(acces==1)
            {
                InformationSleep(stat,sec_for_sleep_window_info,this);
            } 
            (this->FindWindow(wxID_AG_CM_BUTTON_DEL))->SetFocus();
        }
}

void wxAuiWorkPanel::ChangeStringList (wxListEvent& event)
{
    switch (event.GetId())
    {
        case wxID_PS_LISTVIEW_RESULT:
        {
            wxListView   *listview = ((wxListView*)this->FindWindow(wxID_PS_LISTVIEW_RESULT));
            int idItem = event.GetIndex();
            if (idItem==-1) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} 
            
            
    if((((wxChoice*)m_Page2->type_cooperation)->GetSelection())==4) 
    {
        (m_Page2->id_to)=listview->GetItemData(idItem);
        ((wxTextCtrl*)m_Page2->FindWindow(wxID_TO_INN))->SetValue(listview->GetItemText(idItem,1));
        ((wxTextCtrl*)m_Page2->FindWindow(wxID_TO_NAME))->SetValue(listview->GetItemText(idItem,0));
        {
            wxString sqlText;
            sqlText=wxSqlTextSelToPoiskFlagIP;
            sqlText<<listview->GetItemData(idItem);
            sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
            else 
            {
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                if(num_rows>0)
                {                   
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                    if(wxIsdigit(*(row[0])))
                    {
                        if(wxAtoi(row[0])==1)
                        {((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(true);}
                        else {{((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(false);}}
                    } else {{((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(false);}}
                    

                } else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info,this);}
                mysql_free_result(res); // ������� ����������
            } 
        }
        /*if((listview->GetItemText(idItem,1)).Len()!=10&&(listview->GetItemText(idItem,1)).Len()!=12)
        {((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(true);}
        else {{((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(false);}}*/
        m_Page2->ListUpdate();
    }
    else
    {
            
            wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
            f->SetId(idItem); //������������� ������� ���������� ��������
            f->SetColumn(1); //������� ������������� ��
            f->SetMask(wxLIST_MASK_TEXT); //���������� ������ ��������� � ���������
            listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
            ((wxTextCtrl*)m_Page2->FindWindow(wxID_TO_INN))->ChangeValue(f->GetText()); //����� � ��������� ���� ������������� ���� ��������� ���
            delete f; //������� ������*/
            wxCommandEvent event_local; //������� ������ ������ �������
            event_local.SetId(wxID_BUTTON_INN_TO); //������������� ������������� ��������� � ���� ��������
            event_local.SetEventType(wxEVT_COMMAND_BUTTON_CLICKED); //������������� ��� �������
            m_Page2->ProcessWindowEventLocally(event_local); //��������� ��� ������� ���� ����� ����������� ����������� ��� ������� event_local
            break;
    }
        }
        default:break;
    }
}

void wxAuiWorkPanel::OnSize(wxSizeEvent& event) //����� ������� ���� �� ����� ������� ��������� ������ ��� ������ �������
{
	wxRect rect = GetRect(); //��������� ������� ������� ����
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_AUI_WORKPANEL/x"), rect.GetX() );
    config->Write( wxT("/FORM_AUI_WORKPANEL/y"), rect.GetY() );
    config->Write( wxT("/FORM_AUI_WORKPANEL/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_AUI_WORKPANEL/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void wxAuiWorkPanel::OnMove(wxMoveEvent& event) //����� ������� ���� �� ����� ������� ������������ ����
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_AUI_WORKPANEL/x"), rect.GetX() );
    config->Write( wxT("/FORM_AUI_WORKPANEL/y"), rect.GetY() );
    config->Write( wxT("/FORM_AUI_WORKPANEL/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_AUI_WORKPANEL/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}

wxAuiWorkPanel::~wxAuiWorkPanel()
{
    m_Manager.UnInit();
}
