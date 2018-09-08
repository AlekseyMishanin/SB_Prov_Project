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
	m_Notebook->AddPage(m_Page1, _("Физические лица"));
	m_Notebook->AddPage(m_Page2, _("Юридические лица"));
    
    m_Manager.AddPane(m_Notebook, wxAuiPaneInfo().CenterPane().Resizable());
    m_Manager.AddPane(new wxSearchCtrl(this,wxID_SEARCH_FLOATPANEL, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT|wxTE_MULTILINE), 
    wxAuiPaneInfo().Top().Floatable(true).MinimizeButton().MaximizeButton().Layer(1).Position(1).Caption("Поиск физического лица").Name(_("search_fl")));
    
    CreateButtonPanel(); //создаем панель с кнопками
    
    m_Notebook->SetArtProvider(( wxAuiTabArt *)new wxAuiSimpleTabArt()); //меняем внешний вид вкладок блокнота
    m_Manager.Update();
    
    CreateToolbar(); //создаем тулбар
    CreatePanelSearchUL(); //создаем панель поиска юр.лиц
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
    m_Manager.AddPane(pp,wxAuiPaneInfo().Left().Floatable(true).MinimizeButton().MaximizeButton().Layer(1).Position(1).Caption("Команды ФЛ").Name(_("command_fl")).BestSize(70,130));
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
                m_StdToolBar->AddTool(wxID_TOOLBAR_SEARCH_FL, _("search_toolbar_fl"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("Панель поиска физического лица"));
                str_last= wxSEARCHUL_ICO; str_full=str_first; str_full+=str_last;
                m_StdToolBar->AddTool(wxID_TOOLBAR_SEARCH_UL, _("search_toolbar_ul"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("Панель поиска юридического лица"));
                str_last= wxGRIDBUTTON_ICO; str_full=str_first; str_full+=str_last;
                m_StdToolBar->AddTool(wxID_TOOLBAR_COMMAND_FL, _("command_toolbar_fl"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("Панель команд физического лица"));
                m_StdToolBar->SetToolLongHelp(wxID_TOOLBAR_SEARCH_FL,_("Скрыть/показать панель"));
                m_StdToolBar->SetToolLongHelp(wxID_TOOLBAR_COMMAND_FL,_("Скрыть/показать панель"));
                m_StdToolBar->SetToolLongHelp(wxID_TOOLBAR_SEARCH_UL,_("Скрыть/показать панель"));
                m_StdToolBar->Realize();
                
                m_PageToolBar = new wxToolBar(this, wxID_TOOLBAR_CTRL_PAGE, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTB_HORIZONTAL|wxTB_NODIVIDER|wxTB_FLAT);
                m_PageToolBar->SetToolBitmapSize(wxSize(12, 12));
                str_last= wxAGENT_ICO; str_full=str_first; str_full+=str_last;
                m_PageToolBar->AddTool(wxID_TOOLBAR_PAGE_FL, _("page_fl"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("Вкладка - физические лица"));
                str_last= wxTO_ICO; str_full=str_first; str_full+=str_last;
                m_PageToolBar->AddTool(wxID_TOOLBAR_PAGE_UL, _("page_ul"), wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), _("Вкладка - юридические лица"));
                m_PageToolBar->SetToolLongHelp(wxID_TOOLBAR_PAGE_FL,_("Скрыть/показать вкладку"));
                m_PageToolBar->SetToolLongHelp(wxID_TOOLBAR_PAGE_UL,_("Скрыть/показать вкладку"));
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
    //searchCtrl->SetDescriptiveText(wxString("введите значение для поиска и нажмите Enter ...")); //текст по умолчанию в строке поиска
    //searchCtrl->SetToolTip("введите значение для поиска и нажмите Enter ...");
    searchCtrl->ShowCancelButton(1); //делаем активной кнопку отмены
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
    m_Manager.AddPane(panel_search, wxAuiPaneInfo().Top().Floatable(true).MinimizeButton().MaximizeButton().Layer(2).Position(1).Caption("Поиск юридического лица").Name(_("search_ul")));
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
                m_Notebook->AddPage(m_Page1, _("Физические лица"));
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
                m_Notebook->AddPage(m_Page2, _("Юридические лица"));
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
            wxListView *listview = ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES)); //получаем указатель на листвьюев 
            int count = 0;
            if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;} //не выбрана ниодна строка, поэтому выходим из цикла
            for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
            {
                EnterFz EntFz(this, idItem, 1); 
                if(EntFz.ShowModal() == wxID_CANCEL) {;} else 
                {
                    ++count; //считаем кол-во строк, который были обновлены;
                } 
                if (count>0)
                {   
                    wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_UPD_COUNT; str<<count; //строим строку с кол-вом обновленных строк
                    InformationSleep(str,sec_for_sleep_window_info,this);
                } else {;} //если не выбрана ни одна строка, то предупреждаем об этом пользователя и завершаем обработку
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
            wxListView *listview = ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES)); //получаем указатель на листвьюев 
            if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); break;}
            for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
            {
                wxString idFz; //id физ.лица
                wxString captionFioAndPasp; //фио+паспорт в заголовок окна
            
                wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
                f->SetId(idItem); //устанавливаем позицию выбранного элемента
                f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT); //возвращаем данные связанные с элементом
                listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
                idFz<<f->GetData(); //пишем в переменную данные связанные с элементом
                f->SetColumn(0); listview->GetItem(*f); //извлекаем из листвьюев фио
                captionFioAndPasp<<f->GetText(); captionFioAndPasp<<" "; //пишем фио в переменную
                f->SetColumn(1); listview->GetItem(*f); //извлекаем из листвьюев сению паспорта
                captionFioAndPasp<<f->GetText(); captionFioAndPasp<<" "; //пишем серию паспорта в переменную
                f->SetColumn(2); listview->GetItem(*f); //извлекаем из листвьюев номер паспорта
                captionFioAndPasp<<f->GetText(); //пишем номер паспорта в переменную
            
                wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
                wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
            /*
            Считываем из файла конфигурация размеры последнего открытого окна.
            Если файла не существует, про применяем параметры по умолчанию
            */
                long x = config->ReadLong("/FORM_AGENT_PROV/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
                long y = config->ReadLong("/FORM_AGENT_PROV/y", 0);
                long width = config->ReadLong("/FORM_AGENT_PROV/width", 0);
                long height = config->ReadLong("/FORM_AGENT_PROV/height", 0);
                if(x&&y&&width&&height) //параметры конфигурации прочитаны из ini-файла
                {
                    ListProvFz ListPrFz(m_Page1,wxAtoi(idFz),captionFioAndPasp,wxID_ANY,wxPoint(x,y),wxSize(width,height)); //создаем диалоговое окно с проверками выбранного физ.лица с заголовком из фио+паспорт
                    if(ListPrFz.ShowModal() == wxID_CANCEL) {;} else {;}
                }
                else                   //параметры конфигурации не прочитаны из ini-файла
                {
                    ListProvFz ListPrFz(m_Page1,wxAtoi(idFz),captionFioAndPasp); //создаем диалоговое окно с проверками выбранного физ.лица с заголовком из фио+паспорт
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
    textPoisk.Trim(true); textPoisk.Trim(false); //удаляем в строке поиска пробелы справа и слева
    textPoisk.Replace("\n","",true);
    textPoisk.Replace("\r","",true);
    if(textPoisk.IsEmpty()) {InformationSleep (wxINFO_EMPTY_POISK, sec_for_sleep_window_info, this);} //если строка поиска пуста, предупреждаем об этом пользователя
    else 
    {
        textPoisk.Replace("?","_",true); //в значении поиска меняем ? на _ для sql-запроса
        wxString sqlText, loctextPoisk;
        loctextPoisk = textPoisk;
        loctextPoisk.Replace(" ","",true); //в значении поиска меняем пробел на пустое значение
        if(!loctextPoisk.IsNumber()) //поиск по фио
        {
            sqlText<<wxSqlTextPoiskFzFio;
            sqlText<<textPoisk; sqlText<<wxSqlPercentEnd;
        }
        else //поиск по паоспорту
        {
            sqlText<<wxSqlTextPoiskFzPasp;
            sqlText<<loctextPoisk; sqlText<<wxSqlPercentEnd;
        }
        //wxMessageBox(sqlText);
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
        else 
        {
            //wxMessageBox(sqlText);
            MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
            int num_fields = mysql_num_fields(res); // количество полей
            int num_rows = mysql_num_rows(res); // и количество строк.
            if(num_rows>0)
            {   
                (m_Page1->count_find)+=num_rows; //прибавляем глобальной переменной кол-во найденнных строк
                wxListView* listview = ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES));
                int lastItem=0;
                for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                {
                    MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                    wxListItem *f = new wxListItem();
                    f->SetState(wxLIST_STATE_FOCUSED);
                    f->SetMask(wxLIST_MASK_TEXT);
                    f->SetColumn(0);
                    f->SetData(atoi(row[4])); //прячем уникальный айди
                    f->SetId(i);
                    listview->InsertItem(*f); 
                    for (register int l = 0; l < num_fields-1; l++)
                    {
                        listview->SetItem(i,l,row[l]);
                    }
                    lastItem=i;
                    delete f;
                }
                for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                for(register int i =0; i<listview->GetItemCount();++i) {listview->Select(i,false);} //снимаем выделение строк
                listview->Select(lastItem,true); //выделяем последнюю найденную строку
                listview->Focus(lastItem); //устанавливаем фокус на последнюю найденную строку
                WorkStatusBar();        //выводим общее кол-во строк в статусбар*/
            } else {InformationSleep (wxINFO_EMPTY_REZ_POISK_FZ, sec_for_sleep_window_info, this);}
            mysql_free_result(res); // Очищаем результаты
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
            textPoisk.Trim(true); textPoisk.Trim(false); //удаляем в строке поиска пробелы справа и слева
            textPoisk.Replace("\n","",true);
            textPoisk.Replace("\r","",true);
            textPoisk.Replace("?","_",true); //в значении поиска меняем ? на _ для sql-запроса
            int selectPole = radioBoxPole->GetSelection(); //возвращаем индекс выделенного элемента
            int selectType = radioBoxType->GetSelection(); //возвращаем индекс выделенного элемента
            listview->DeleteAllItems(); //очищаем listview
            
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
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат
                int num_rows = mysql_num_rows(res); // и количество строк.
                int num_fields = mysql_num_fields(res); // количество полей
                if(num_rows>0)
                {  
                    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                    {                     
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                        f->SetColumn(0);
                        f->SetData(atoi(row[0])); //прячем уникальный айди
                        f->SetId(i);
                        listview->InsertItem(*f); 
                        for (register int l = 1; l < num_fields; l++)
                        {
                            if(l==2) 
                            {
                                /*на 30.05.2017 поле с ИНН было числового типа bigint или decimal что не позволяло сохранить в начале числа 0, т.к. длиня числа могла быть различной и заполнять все значения 0 используя zerofil не целесообразно*/
                                wxString str = row[l];
                                if(str.Len()==9||str.Len()==11) {listview->SetItem(i,l-1,"0"+str);}
                                else {listview->SetItem(i,l-1,row[l]);}
                            }
                            else
                            {listview->SetItem(i,l-1,row[l]);}
                        }
                        delete f;
                    }
                    for (register int i = 0; i < listview->GetColumnCount(); i++) // Вывод таблицы
                    {
                        listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //изменяем размер столбца по длине самого большого элемента
                    }
                } else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info,this);}
                mysql_free_result(res); // Очищаем результаты
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
    WorkStatusBar(); //меняем значение статус бара*/
    event.Skip(true);
}
void wxAuiWorkPanel::DeleteFz (void)
{
        wxListView *listview = ((wxListView*)m_Page1->FindWindow(wxID_AG_SP_LIST_RES)); //получаем указатель на листвьюев  
        int count = 0; int acces = 0;
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
        {
            wxString stat; stat<<wxID_SUCCESS_OPERATION; stat<<wxINFO_DEL_FZ;
            for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
            {
                wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
                f->SetId(idItem); //устанавливаем позицию выбранного элемента
                f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT); //возвращаем данные связанные с элементом
                listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
                wxString idFz; idFz<<f->GetData(); //пишем в переменную данные связанные с элементом
                if(!idFz.IsEmpty())
                {
                    wxString sqlText;
                    /*
                    sqlText = wxSqlTextDelFzProvStart; sqlText<<idFz; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
                    else 
                    {
                        ++count; //считаем кол-во строк, который были удалены
                    }
                    sqlText.Clear(); //очищаем переменную
                    */
                    sqlText = wxSqlTextDelFzStart; sqlText<<idFz; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
                    else 
                    {
                        //if(count_add>0) {--count_add;} //меняем значение глобального счетчика кол-ва добавленных проверок.
                        acces=1; //флаг того, что запрос обработан успешно.
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
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат
                int num_rows = mysql_num_rows(res); // и количество строк.
                if(num_rows>0)
                {                   
                    MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                    if(wxIsdigit(*(row[0])))
                    {
                        if(wxAtoi(row[0])==1)
                        {((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(true);}
                        else {{((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(false);}}
                    } else {{((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(false);}}
                    

                } else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info,this);}
                mysql_free_result(res); // Очищаем результаты
            } 
        }
        /*if((listview->GetItemText(idItem,1)).Len()!=10&&(listview->GetItemText(idItem,1)).Len()!=12)
        {((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(true);}
        else {{((wxCheckBox*)m_Page2->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(false);}}*/
        m_Page2->ListUpdate();
    }
    else
    {
            
            wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
            f->SetId(idItem); //устанавливаем позицию выбранного элемента
            f->SetColumn(1); //колонка наименованием ТО
            f->SetMask(wxLIST_MASK_TEXT); //возвращаем данные связанные с элементом
            listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
            ((wxTextCtrl*)m_Page2->FindWindow(wxID_TO_INN))->ChangeValue(f->GetText()); //пишем в текстовое поле родительского окна выбранный инн
            delete f; //удаляем объект*/
            wxCommandEvent event_local; //создаем объект класса событие
            event_local.SetId(wxID_BUTTON_INN_TO); //устанавливаем идентификатор связанный с этим событием
            event_local.SetEventType(wxEVT_COMMAND_BUTTON_CLICKED); //устанавливаем тип события
            m_Page2->ProcessWindowEventLocally(event_local); //запускаем для данного окна поиск подходящего обработчика для события event_local
            break;
    }
        }
        default:break;
    }
}

void wxAuiWorkPanel::OnSize(wxSizeEvent& event) //ловим размеры окна во время события изменения нижней или правой границы
{
	wxRect rect = GetRect(); //считываем текущие размеры окна
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
void wxAuiWorkPanel::OnMove(wxMoveEvent& event) //ловим размеры окна во время события передвижения окна
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
