#include "CrossFrm.h"

extern MYSQL* conn;
extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;
extern void EditTheLine(wxString &str, wxWindow* win);

BEGIN_EVENT_TABLE(NotebookOtchet,wxFrame)
    EVT_SIZE(NotebookOtchet::OnSize)
	EVT_MOVE_END(NotebookOtchet::OnMove)
    EVT_NOTEBOOK_PAGE_CHANGED(wxID_OTCH_NOTEBOOK,NotebookOtchet::GhangePageNotebook) //изменение страницы блокнота
    EVT_TREELIST_SELECTION_CHANGED(wxID_OTCH_TO_TREELIST,NotebookOtchet::GhangeTreeListCtrl) //изменение выделенной строки TreeListCtrl
    EVT_LIST_ITEM_SELECTED(wxID_OTCH_AG_LISTVIEV,NotebookOtchet::GhangeListview) //изменение выделенной строки listview
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_OTCH_COLLPANE, NotebookOtchet::CollapChanged) //нажата складная панель 
    EVT_BUTTON(wxID_OTCH_S_BUT_UNL,NotebookOtchet::OnButton)
END_EVENT_TABLE()


NotebookOtchet::NotebookOtchet(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint& pos, const wxSize& size , long style )
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
        wxString str_full, str_first, str_last; //определяем переменные для прописания пути к иконкам
        wxImageList *imageList = new wxImageList(16,16);                //создаем обект. содержит список изображений
        str_first = dir.GetName(); str_last= wxTO_ICO; str_full=str_first; str_full+=str_last;     //составляем путь к картинке
        wxIcon icon(str_full,wxBITMAP_TYPE_ICO);                        //создаем иконку, загружая картинку из файла
        imageList->Add(icon);                                           //добавляем новое изображение в список
        str_last= wxAGENT_ICO; str_full=str_first; str_full+=str_last; //составляем путь к картинке
        wxIcon icon1(str_full,wxBITMAP_TYPE_ICO);                       //создаем иконку, загружая картинку из файла
        imageList->Add(icon1);                                          //добавляем новое изображение в список

        nb = new wxNotebook(this, wxID_OTCH_NOTEBOOK, wxPoint(-1, -1), wxSize(-1, -1), wxNB_LEFT);
        wxListView *listview = new wxListView(nb, wxID_OTCH_AG_LISTVIEV);
        wxTreeListCtrl *treelist = new wxTreeListCtrl(nb, wxID_OTCH_TO_TREELIST, wxDefaultPosition, wxDefaultSize,wxTL_SINGLE);
        
        listview->InsertColumn(0,wxCAPTION_COLUMN_GC);
        listview->InsertColumn(1,wxCAPTION_COLUMN_FIO);
        listview->InsertColumn(2,wxCAPTION_COLUMN_TO);
        listview->InsertColumn(3,wxCAPTION_COLUMN_INN);
        listview->InsertColumn(4,wxCAPTION_COLUMN_COMENT);
        listview->InsertColumn(5,wxCAPTION_COLUMN_SOTRSB);
        listview->InsertColumn(6,wxCAPTION_COLUMN_REZ);

        treelist->AppendColumn(wxCAPTION_COLUMN_COOPER);
        treelist->AppendColumn(wxCAPTION_COLUMN_PROV);
        treelist->AppendColumn(wxCAPTION_COLUMN_OC);
        treelist->AppendColumn(wxCAPTION_COLUMN_GC);
        treelist->AppendColumn(wxCAPTION_COLUMN_TO);
        treelist->AppendColumn(wxCAPTION_COLUMN_INN);
        treelist->AppendColumn(wxCAPTION_COLUMN_UK,wxCOL_WIDTH_DEFAULT);
        treelist->AppendColumn(wxCAPTION_COLUMN_COMENT,wxCOL_WIDTH_DEFAULT);
        treelist->AppendColumn(wxCAPTION_COLUMN_SOTRSB);
        treelist->AppendColumn(wxCAPTION_COLUMN_REZ);

        wxCollapsiblePane *collpane1 = new wxCollapsiblePane(this, wxID_OTCH_COLLPANE, wxCAPTION_COLLPANE_UNLOAD, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE); //создаем раскрввающуюся кнопку со стилем запрещающим перестраивать окна под мин.размер
        wxWindow *win1 = collpane1->GetPane();
        wxSizer *paneSz1 = new wxBoxSizer(wxVERTICAL);
        wxSizer *paneSz1_1 = new wxBoxSizer(wxHORIZONTAL);
        paneSz1_1->Add(new wxStaticText(win1,wxID_ANY, wxCAPTION_STATICTEXT_S,wxDefaultPosition,wxDefaultSize,wxALIGN_LEFT), 0, wxEXPAND|wxALL, 5);
        paneSz1_1->Add(new wxDatePickerCtrl(win1,wxID_OTCH_S_DATE_ON,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT), 0, wxEXPAND|wxALL, 5);
        paneSz1_1->Add(new wxStaticText(win1,wxID_ANY, wxCAPTION_STATICTEXT_PO,wxDefaultPosition,wxDefaultSize,wxALIGN_LEFT), 0, wxEXPAND|wxALL, 5);
        paneSz1_1->Add(new wxDatePickerCtrl(win1,wxID_OTCH_S_DATE_OF,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT), 0, wxEXPAND|wxALL, 5);
        paneSz1_1->Add(new wxButton(win1,wxID_OTCH_S_BUT_UNL,wxCAPTION_BUTTON_QUERY,wxDefaultPosition,wxDefaultSize,0), 0, wxEXPAND|wxALL, 5);
        paneSz1->Add(paneSz1_1, 0, wxEXPAND|wxALL, 0);
        paneSz1->Add(new wxCheckBox(win1,wxID_OTCH_S_CHECK,wxCAPTION_CHECKBOX_AG_FOR_TO), 0, wxEXPAND|wxBOTTOM, 10);
        win1->SetSizer(paneSz1);
        paneSz1->SetSizeHints(win1);
        
        
        nb->AddPage(treelist, ("ТО"));
        nb->AddPage(listview, ("Агент ТО"));
	    nb->SetImageList(imageList); //устанавливаем список изображений для использования
	    nb->SetPageImage(0,0); //устанавливаем изображение для данной страницы
	    nb->SetPageImage(1,1);
        CreateStatusBar(3);
        int widths_field[] = {150,-1,-1};
        SetStatusWidths (3, widths_field);
        vert_bos->Add(collpane1, 0, wxEXPAND|wxBOTTOM ,0);
        vert_bos->Add(nb, 1, wxEXPAND|wxBOTTOM ,0);
        vert_bos->Add(new wxBannerWindow(this, wxID_OTCH_BANNER, wxBOTTOM), 0, wxEXPAND ,0);
        ((wxBannerWindow*)this->FindWindow(wxID_OTCH_BANNER))->SetText(wxNULL_STRING, wxNULL_STRING);
        ((wxBannerWindow*)this->FindWindow(wxID_OTCH_BANNER))->SetGradient(*wxWHITE,*wxLIGHT_GREY);
        this->SetSizer(vert_bos);	
        WorkSql();
    }
}

void NotebookOtchet::WorkSql(void)
{
    wxString to_vsego, agent_vsego, date_now;
    to_vsego=wxSTRING_COUNT_PROV_TO;
    agent_vsego=wxSTRING_COUNT_PROV_AG;
    wxListView *listview = (wxListView*)nb->FindWindow(wxID_OTCH_AG_LISTVIEV);
    wxTreeListCtrl *treelist = (wxTreeListCtrl*)nb->FindWindow(wxID_OTCH_TO_TREELIST);
    listview->DeleteAllItems();
    treelist->DeleteAllItems();
    
    wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)this->FindWindow(wxID_OTCH_COLLPANE);
    wxWindow *win1 = collpane1->GetPane();
    wxCheckBox* check = (wxCheckBox*)win1->FindWindow(wxID_OTCH_S_CHECK);
    wxString idDate1 = (((wxDatePickerCtrl*)(win1->FindWindow(wxID_OTCH_S_DATE_ON)))->GetValue()).FormatISODate();
    wxString idDate2 = (((wxDatePickerCtrl*)(win1->FindWindow(wxID_OTCH_S_DATE_OF)))->GetValue()).FormatISODate();
        
    
    wxString sqlText; 
    sqlText<<wxSqlTextSelAgNowDay;
    sqlText<<idDate1; sqlText<<wxSqlCharStr; sqlText<<wxSqlAnd; sqlText<<wxSqlCharStr; sqlText<<idDate2; sqlText<<wxSqlCharStr; sqlText<<wxSqlEndText;  
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.
        agent_vsego<<num_rows;
        if(num_rows>0)
        {   
            for (register int i = 0; i < num_rows; i++) // Вывод таблицы
            {
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT);
                f->SetColumn(0);
                f->SetId(i);
                listview->InsertItem(*f); 
                for (register int l = 0; l < num_fields; l++)
                {
                    listview->SetItem(i,l,row[l]);
                }
                delete f;
            }
            for(register int i=0; i<listview->GetColumnCount();++i)
            {
                if(i!=4) listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //изменяем размер столбца по длине самого большого элемента (кроме столбца с комментарием)
            }
        }
        mysql_free_result(res); // Очищаем результаты
    }

    sqlText.Clear(); 
    sqlText<<wxSqlTextSelToNowDay;
    sqlText<<idDate1; sqlText<<wxSqlCharStr; sqlText<<wxSqlAnd; sqlText<<wxSqlCharStr; sqlText<<idDate2; sqlText<<wxSqlCharStr; sqlText<<wxSqlEndText;  
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.
        to_vsego<<num_rows;
        if(num_rows>0)
        {   
            for (register int i = 0; i < num_rows; i++) // Вывод таблицы
            {
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxTreeListItem tritem = treelist->AppendItem(treelist->GetRootItem(),row[0]);
                //treelist->AppendItem(tritem,"ghj,f");
                for(register int l=1; l<treelist->GetColumnCount();++l)
                {
                    if(l==5) 
                    {
                        /*на 30.05.2017 поле с ИНН было числового типа bigint или decimal что не позволяло сохранить в начале числа 0, т.к. длиня числа могла быть различной и заполнять все значения 0 используя zerofil не целесообразно*/
                        wxString str = row[l];
                        if(str.Len()==9||str.Len()==11) {treelist->SetItemText(tritem,l,"0"+str);}
                        else {treelist->SetItemText(tritem,l,row[l]);}
                    }
                    else
                    {treelist->SetItemText(tritem,l,row[l]);}
                }
                if(check->GetValue())
                {
                    sqlText.Clear();
                    sqlText<<wxSqlTextSelToFzNowDay; sqlText<<row[num_fields-1]; 
                    sqlText<<wxSqlAnd; sqlText<<wxSqlTextSelToFzNowDayWhere; sqlText<<wxSqlBetween;
                    sqlText<<wxSqlCharStr; sqlText<<idDate1; sqlText<<wxSqlCharStr; sqlText<<wxSqlAnd;
                    sqlText<<wxSqlCharStr; sqlText<<idDate2; sqlText<<wxSqlCharStr; sqlText<<wxSqlEndText; 
                
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                    else
                    {
                        MYSQL_RES *res1 = mysql_store_result(conn); // Берем результат,
                        int num_fields1 = mysql_num_fields(res1); // количество полей
                        int num_rows1 = mysql_num_rows(res1); // и количество строк.
                        if(num_rows1>0)
                        {
                            for (register int i = 0; i < num_rows1; i++) // Вывод таблицы
                            {
                                MYSQL_ROW row1 = mysql_fetch_row(res1); // получаем строку
                                wxTreeListItem tritem1 = treelist->AppendItem(tritem,wxNULL_STRING);
                                for(register int l=4, k=0; l<treelist->GetColumnCount();++l,++k)
                                {
                                    treelist->SetItemText(tritem1,l,row1[k]);
                                }
                            }
                        }
                        mysql_free_result(res1); // Очищаем результаты 
                    }
                }
            }
            for(register int l=0; l<treelist->GetColumnCount();++l)
            {
                if(l!=7||l!=6) {treelist->SetColumnWidth (l,wxCOL_WIDTH_AUTOSIZE);}
                else {if(l==7) {treelist->SetColumnWidth (l,0);}}
            }
        }
        mysql_free_result(res); // Очищаем результаты
    }
    date_now=wxNow(); //текущее время
    SetStatusText(date_now,0); SetStatusText(to_vsego,1); SetStatusText(agent_vsego,2);	
    wxBannerWindow* banner = ((wxBannerWindow*)this->FindWindow(wxID_OTCH_BANNER));
    banner->SetText(wxNULL_STRING, wxNULL_STRING);
}
void NotebookOtchet::OnButton(wxCommandEvent& event)
{
    switch(event.GetId())
    {
        case wxID_OTCH_S_BUT_UNL:
        {
            WorkSql();
            break;
        }
        default:break;
    }
}
void NotebookOtchet::OnSize(wxSizeEvent& event) //ловим размеры окна во время события изменения нижней или правой границы
{
	wxRect rect = GetRect(); //считываем текущие размеры окна
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_OTCHET_FAST/x"), rect.GetX() );
    config->Write( wxT("/FORM_OTCHET_FAST/y"), rect.GetY() );
    config->Write( wxT("/FORM_OTCHET_FAST/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_OTCHET_FAST/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void NotebookOtchet::OnMove(wxMoveEvent& event) //ловим размеры окна во время события передвижения окна
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_OTCHET_FAST/x"), rect.GetX() );
    config->Write( wxT("/FORM_OTCHET_FAST/y"), rect.GetY() );
    config->Write( wxT("/FORM_OTCHET_FAST/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_OTCHET_FAST/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}

void NotebookOtchet::GhangePageNotebook(wxBookCtrlEvent& event)
{
    wxBannerWindow* banner = ((wxBannerWindow*)this->FindWindow(wxID_OTCH_BANNER));
    banner->SetText(wxNULL_STRING, wxNULL_STRING);
    this->Layout();
}

void NotebookOtchet::GhangeTreeListCtrl(wxTreeListEvent& event)
{
    wxTreeListCtrl *treelist = ((wxTreeListCtrl*)this->FindWindow(wxID_OTCH_TO_TREELIST));
    wxBannerWindow* banner = ((wxBannerWindow*)this->FindWindow(wxID_OTCH_BANNER));
    wxTreeListItem treelistitem = treelist->GetSelection();
    wxString str;
    for(register int i=0; i<treelist->GetColumnCount();++i)
    {
        if(i==7) {wxString strEd=treelist->GetItemText(treelistitem,i); EditTheLine(strEd, this); str +=strEd;}
        else {str += treelist->GetItemText(treelistitem,i);}
        str +='\n';
    }
    banner->SetText(wxNULL_STRING, str);
    this->SetSizer(vert_bos);
    this->Layout();
}
void NotebookOtchet::GhangeListview (wxListEvent& event)
{
    wxListView *listview = ((wxListView*)this->FindWindow(wxID_OTCH_AG_LISTVIEV));
    wxBannerWindow* banner = ((wxBannerWindow*)this->FindWindow(wxID_OTCH_BANNER));
    int select_string = event.GetIndex();
    wxString str;
    for(register int i=0; i<listview->GetColumnCount();++i)
    {
        if(i==4) {wxString strEd=listview->GetItemText(select_string,i); EditTheLine(strEd, this); str +=strEd;}
        else {str += listview->GetItemText(select_string,i);}
        str +='\n';
    }
    banner->SetText(wxNULL_STRING, str);
    this->SetSizer(vert_bos);
    this->Layout();
}
void NotebookOtchet::CollapChanged (wxCollapsiblePaneEvent& event)
{
    switch (event.GetId())
    {
        case wxID_OTCH_COLLPANE:
        {
            this->Layout(); //просим компоновщик перестроить окна
            break;
        }
        
        default: {break;}
    }
    
    event.Skip();
}
NotebookOtchet::~NotebookOtchet()
{
}
