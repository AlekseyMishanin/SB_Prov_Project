#include "CrossFrm.h"

extern MYSQL* conn;
extern int sec_for_sleep_window_info;
extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern void SaveDataIntoFile (wxWindow* parent, wxString& sLine, wxString& sqlText);

BEGIN_EVENT_TABLE(ContactFrm,wxFrame)
    EVT_SIZE(ContactFrm::OnSize)
	EVT_MOVE_END(ContactFrm::OnMove)
    EVT_LIST_ITEM_FOCUSED(wxID_C_LISTVIEW_SP_COMP,ContactFrm::ChangeStringList)
    EVT_LIST_ITEM_FOCUSED(wxID_C_LISTVIEW_FIO_CONTACT,ContactFrm::ChangeStringList)
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_C_COLLPANE_DOPINFO, ContactFrm::CollapChanged) //нажата складная панель
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_C_COLLPANE_CALL_HIST, ContactFrm::CollapChanged) //нажата складная панель
    EVT_MENU(wxID_C_BUTTON_COMP_INS,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_COMP_UPD,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_COMP_DEL,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_CONT_INS,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_CONT_UPD,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_CONT_DEL,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_COMP_S_ALL,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_COMP_S_BANK,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_COMP_S_ORG,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_COMP_S_INSU,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_CALL_U,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_CALL_F,ContactFrm::OnButton)
    EVT_MENU(wxID_C_BUTTON_CALL_DELL,ContactFrm::OnButton)
    EVT_MENU(wxID_MENU_SAVE_CONTACT,ContactFrm::OnButton)
    EVT_TEXT_ENTER(wxID_C_SEARCHCTRL_COMPANY, ContactFrm::OnEnter)
    
END_EVENT_TABLE()


ContactFrm::ContactFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint& pos, const wxSize& size , long style )
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
        wxMenuBar *menubar = new wxMenuBar;
        wxMenu *file_menu = new wxMenu;
        file_menu->Append(wxID_MENU_SAVE_CONTACT, "&Выгрузить контакты", "Выгрузить телефонный справочник в файл");
        menubar->Append(file_menu, "&Файл");
	    SetMenuBar(menubar);
        panel_contact = new wxPanel(this, wxID_ANY);
        bx_contact = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer *vr_local_1 = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *vr_local_2 = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *hr_local_2_1 = new wxBoxSizer(wxHORIZONTAL);
         
        wxListView *listview_company = new wxListView(panel_contact, wxID_C_LISTVIEW_SP_COMP, wxDefaultPosition, wxDefaultSize,wxLC_REPORT|wxLC_SINGLE_SEL); //создаем листвьев
        listview_company->InsertColumn(0,wxCAPTION_COLUMN_NAME_COM);
        listview_company->InsertColumn(1,wxCAPTION_COLUMN_TYPE); 
        
        listview_company->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(ContactFrm::OnMouse)); //добавляем в таблицу событий элемента управления обработку события нажатия правой кнопки мыши
        vr_local_1->Add(new wxSearchCtrl(panel_contact,wxID_C_SEARCHCTRL_COMPANY, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT), 0, wxEXPAND|wxALL, 5);
        vr_local_1->Add(listview_company, 1, wxEXPAND|wxALL, 5);
        
        wxListView *listview_fio = new wxListView(panel_contact, wxID_C_LISTVIEW_FIO_CONTACT, wxDefaultPosition, wxDefaultSize,wxLC_REPORT|wxLC_SINGLE_SEL); //создаем листвьев
        listview_fio->InsertColumn(0,wxCAPTION_COLUMN_FIO);
        listview_fio->InsertColumn(1,wxCAPTION_COLUMN_REGION); 
        listview_fio->InsertColumn(2,wxCAPTION_COLUMN_TEL); 
        listview_fio->InsertColumn(3,wxCAPTION_COLUMN_DOB); 
        listview_fio->InsertColumn(4,wxCAPTION_COLUMN_DOP); 
        listview_fio->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(ContactFrm::OnMouse)); //добавляем в таблицу событий элемента управления обработку события нажатия правой кнопки мыши
        
        wxCollapsiblePane *collpane1 = new wxCollapsiblePane(panel_contact, wxID_C_COLLPANE_DOPINFO, wxCAPTION_COLLPANE_DOP_INFO, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE); //создаем раскрввающуюся кнопку со стилем запрещающим перестраивать окна под мин.размер
        hr_local_2_1->Add(collpane1, 1, wxEXPAND|wxALL,5);
        wxWindow *win1 = collpane1->GetPane();
        wxSizer *paneSz1 = new wxBoxSizer(wxHORIZONTAL);
        paneSz1->Add(new wxStaticText(win1,wxID_C_STATICTEXT_COMMENT, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxALIGN_LEFT), 1, wxEXPAND|wxALL, 5);
        win1->SetSizer(paneSz1);
        paneSz1->SetSizeHints(win1);
        
        wxCollapsiblePane *collpane2 = new wxCollapsiblePane(panel_contact, wxID_C_COLLPANE_CALL_HIST, wxCAPTION_COLLPANE_CALL_HIST, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE); //создаем раскрввающуюся кнопку со стилем запрещающим перестраивать окна под мин.размер
        hr_local_2_1->Add(collpane2, 1, wxEXPAND|wxALL,5);
        wxWindow *win2 = collpane2->GetPane();
        wxSizer *paneSz2 = new wxBoxSizer(wxHORIZONTAL);
        wxListView *listview_call = new wxListView(win2, wxID_C_LISTVIEW_SP_CALL, wxDefaultPosition, wxDefaultSize,wxLC_REPORT|wxLC_SINGLE_SEL); //создаем листвьев
        listview_call->InsertColumn(0,wxCAPTION_COLUMN_DATE);
        listview_call->InsertColumn(1,wxCAPTION_COLUMN_REZ); 
        listview_call->InsertColumn(2,wxCAPTION_COLUMN_FIO);
        listview_call->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(ContactFrm::OnMouse)); //добавляем в таблицу событий элемента управления обработку события нажатия правой кнопки мыши
        
        paneSz2->Add(listview_call, 1, wxEXPAND|wxALL, 5);
        win2->SetSizer(paneSz2);
        paneSz2->SetSizeHints(win2);
        
        vr_local_2->Add(listview_fio, 1, wxEXPAND|wxALL, 5);
        vr_local_2->Add(hr_local_2_1, 0, wxEXPAND|wxALL, 5);
        
        bx_contact->Add(vr_local_1, 1, wxEXPAND|wxALL, 5);
        bx_contact->Add(vr_local_2, 2, wxEXPAND|wxALL, 5);
        
        panel_contact->SetSizer(bx_contact);
        
        this->CreateStatusBar(2); //создаем строку состояния, кол-во полей = 2
        int widths_field[] ={150,-1};
        this->SetStatusWidths(2,widths_field); //устанавливаем ширину полей строки состояния
    }
}

void ContactFrm::OnButton(wxCommandEvent& event)
{
    switch(event.GetId())
    {
        case wxID_MENU_SAVE_CONTACT:
        {
            wxString strTitle = "Тип\tНаименование компании\tРегион\tНаименование контакта\tОсновной телефон\tДобавочный\tДоп.телефон\tКомментарий";
            wxString sqlText = wxSqlTextSelAllContactInFile;
            SaveDataIntoFile (this, strTitle, sqlText);
            break;
        }
        case wxID_C_BUTTON_COMP_INS:
        {
            UpdateCompanyDialog UpdCompany(this, 1);  
            if(UpdCompany.ShowModal() == wxID_CANCEL) {return;} else {;}
            break;
        }
        case wxID_C_BUTTON_COMP_UPD:
        {
            wxListView *listview_company = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_SP_COMP);
            int item_sel = listview_company->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
            if(item_sel!=-1)
            {
                UpdateCompanyDialog UpdCompany(this, 2);  
                if(UpdCompany.ShowModal() == wxID_CANCEL) {return;} else {;}
            } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
            break;
        }
        case wxID_C_BUTTON_COMP_DEL:
        {
            DeleteCompany();
            break;
        }
        case wxID_C_BUTTON_CONT_INS:
        {
            wxListView *listview_company = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_SP_COMP);
            int item_sel = listview_company->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
            if(item_sel!=-1)
            {
                UpdateFioContactDialog UpdContact(this, 1);  
                if(UpdContact.ShowModal() == wxID_CANCEL) {return;} else {;}
            } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
            break;
        }
        case wxID_C_BUTTON_CONT_UPD:
        {
            wxListView *listview_company = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_SP_COMP);
            int item_sel = listview_company->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
            if(item_sel!=-1) //выбрана строка в таблице компаний
            {
                wxListView *listview_fio = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
                int item_sel_cont = listview_fio->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
                if(item_sel_cont!=-1) //выбрана строка в таблице контактов
                {
                    UpdateFioContactDialog UpdContact(this, 2);  
                    if(UpdContact.ShowModal() == wxID_CANCEL) {return;} else {;}
                } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
            } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
            break;
        }
        case wxID_C_BUTTON_CONT_DEL:
        {
            DeleteContact();
            break;
        }
        case wxID_C_BUTTON_CALL_U:
        {
            InsertCallRezult(1);
            break;
        }
        case wxID_C_BUTTON_CALL_F:
        {
            InsertCallRezult(2);
            break;
        }
        case wxID_C_BUTTON_CALL_DELL:
        {
            DeleteCall();
            break;
        }    
        case wxID_C_BUTTON_COMP_S_ALL:
        {
            SelectAllCompany(); //выгружаем все компании
            break;
        }
        case wxID_C_BUTTON_COMP_S_BANK:
        {
            int id_type=2; //id тип компании
            SelectPrivateCompany(id_type);
            break;
        }
        case wxID_C_BUTTON_COMP_S_ORG:
        {
            int id_type=4; //id тип компании
            SelectPrivateCompany(id_type);
            break;
        }
        case wxID_C_BUTTON_COMP_S_INSU:
        {
            int id_type=3; //id тип компании
            SelectPrivateCompany(id_type);
            break;
        }
        default:break;
    }
}

void ContactFrm::ChangeStringList (wxListEvent& event)
{
    switch (event.GetId())
    {
        case wxID_C_LISTVIEW_SP_COMP:
        {
            int idCompany = 0; 
            idCompany = event.GetData();
            if(idCompany!=0)
            {
                SelectFioContact(idCompany);
                WorkStatusBar(); //заполняем статусбар
            }
            break;
        }
        case wxID_C_LISTVIEW_FIO_CONTACT:
        {
            int idContact = 0; 
            idContact = event.GetData();
            if(idContact!=0)
            {
                SelectCommentContact(idContact);
                SelectCallContact(idContact);
                wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_contact->FindWindow(wxID_C_COLLPANE_DOPINFO));
                wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_contact->FindWindow(wxID_C_COLLPANE_CALL_HIST));
                if(collpane1->IsExpanded()||collpane2->IsExpanded())
                {
                    panel_contact->Layout(); //просим компоновщик, привязанный к панели на странице со структурой регионов, перестроить окна
                    this->Refresh(); //перерисовываем окно
                }
            }
            break;
        }
        default:break;
    }
}

void ContactFrm::SelectFioContact (int& id_company)
{
    wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_contact->FindWindow(wxID_C_COLLPANE_DOPINFO)); 
    wxWindow *win1 = collpane1->GetPane();
    wxStaticText *stText = (wxStaticText*)(win1->FindWindow(wxID_C_STATICTEXT_COMMENT));
    stText->SetLabel(wxNULL_STRING);
    
    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_contact->FindWindow(wxID_C_COLLPANE_CALL_HIST)); 
    wxWindow *win2 = collpane2->GetPane();
    wxListView *listview_call = (wxListView*)(win2->FindWindow(wxID_C_LISTVIEW_SP_CALL));
    listview_call->DeleteAllItems();

    wxListView *listview_fio = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
    listview_fio->DeleteAllItems();
    wxString sqlText; 
    sqlText<<wxSqlTextSelFioCont; sqlText<<id_company;
    sqlText<<wxSqlEndText;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {   
            for (register int i = 0; i < num_rows; i++) // Вывод таблицы
            {
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                f->SetColumn(0);
                f->SetData(wxAtoi(row[5])); //прячем уникальный айди
                f->SetId(i);
                listview_fio->InsertItem(*f); 
                for (register int l = 0; l < (num_fields-1); l++) {listview_fio->SetItem(i,l,row[l]);}
            }
        }
        mysql_free_result(res); // Очищаем результаты
        for (register int i=0; i<(listview_fio->GetColumnCount());++i) {listview_fio->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента      
    }
}

void ContactFrm::DeleteCall (void)
{
    wxString strIdContact, sqlText;
    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)panel_contact->FindWindow(wxID_C_COLLPANE_CALL_HIST);
    wxWindow *win2 = collpane2->GetPane();
    wxListView *listview_call = (wxListView*)win2->FindWindow(wxID_C_LISTVIEW_SP_CALL);
    int item_sel = listview_call->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
    if(item_sel!=-1) {strIdContact<<(listview_call->GetItemData(item_sel));}
    if(strIdContact.IsEmpty()) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
    sqlText<<wxSqlTextDelCallHis; 
    sqlText<<strIdContact; sqlText<<wxSqlEndText;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else  
    {
        listview_call->DeleteItem(item_sel);
    }
}

void ContactFrm::DeleteCompany (void)
{
    wxListView *listview_company = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_SP_COMP);
    wxListView *listview_fio = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
    int item_sel = listview_company->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
    if(item_sel!=-1)
    {
        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
        {
            wxString sqlText;
            sqlText<<wxSqlTextDelCompany; sqlText<<(listview_company->GetItemData(item_sel)); sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
            else  
            {
                sqlText.Clear();
                sqlText<<wxSqlTextDelCompanyCon; sqlText<<(listview_company->GetItemData(item_sel)); sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else  {listview_fio->DeleteAllItems();} //удаляем из таблицы контактов все контакты привязанные к компании
                listview_company->DeleteItem(item_sel); //удаляем компанию из таблицы компаний
            }
            
        }
    }
    else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
}

void ContactFrm::DeleteContact (void)
{
    wxListView *listview_fio = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
    int item_sel = listview_fio->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
    if(item_sel!=-1)
    {
        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
        {
            wxString sqlText;
            sqlText<<wxSqlTextDelCompanyCon1; sqlText<<(listview_fio->GetItemData(item_sel)); sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
            else  
            {
                listview_fio->DeleteItem(item_sel); //удаляем компанию из таблицы компаний
            }
            
        }
    }
    else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
}

void ContactFrm::SelectAllCompany (void)
{
    wxListView *listview_company = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_SP_COMP);
    listview_company->DeleteAllItems();
    wxString sqlText; sqlText<<wxSqlTextSelCont;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {   
            for (register int i = 0; i < num_rows; i++) // Вывод таблицы
            {
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                f->SetColumn(0);
                f->SetData(wxAtoi(row[2])); //прячем уникальный айди
                f->SetId(i);
                listview_company->InsertItem(*f); 
                for (register int l = 0; l < (num_fields-1); l++) {listview_company->SetItem(i,l,row[l]);}
            }
            WorkStatusBar(); //заполняем статусбар
        }
        mysql_free_result(res); // Очищаем результаты
        for (register int i=0; i<(listview_company->GetColumnCount());++i) {listview_company->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента      
    }
}

void ContactFrm::SelectPrivateCompany (int& id)
{
    wxListView *listview_company = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_SP_COMP);
    listview_company->DeleteAllItems();
    wxString sqlText; sqlText<<wxSqlTextSelPrivate;
    sqlText<<id; sqlText<<wxSqlEndText;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {   
            for (register int i = 0; i < num_rows; i++) // Вывод таблицы
            {
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                f->SetColumn(0);
                f->SetData(wxAtoi(row[2])); //прячем уникальный айди
                f->SetId(i);
                listview_company->InsertItem(*f); 
                for (register int l = 0; l < (num_fields-1); l++) {listview_company->SetItem(i,l,row[l]);}
            }
            WorkStatusBar(); //заполняем статусбар
        }
        mysql_free_result(res); // Очищаем результаты
        for (register int i=0; i<(listview_company->GetColumnCount());++i) {listview_company->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента      
    }
}

void ContactFrm::SelectCallContact (int& id_contact)
{
    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_contact->FindWindow(wxID_C_COLLPANE_CALL_HIST)); 
    wxWindow *win2 = collpane2->GetPane();
    wxListView *listview_call = (wxListView*)(win2->FindWindow(wxID_C_LISTVIEW_SP_CALL));
    listview_call->DeleteAllItems();
    
    wxString sqlText = wxSqlTextSelCallHist;
    sqlText<<id_contact;  sqlText<<wxSqlEndTextOrderByDesc1;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
    else 
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {   
            for (register int i = 0; i < num_rows; i++) // Вывод таблицы
            {
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                f->SetColumn(0);
                f->SetData(wxAtoi(row[4])); //прячем уникальный айди
                f->SetId(i);
                listview_call->InsertItem(*f); 
                for (register int l = 0; l < num_fields-1; l++)
                {
                    listview_call->SetItem(i,l,row[l]);
                }
                delete f;
            }
            for (register int i=0; i<(listview_call->GetColumnCount());++i) {listview_call->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента      
        } else {;}
        mysql_free_result(res); // Очищаем результаты
    }
}

void ContactFrm::SelectCommentContact (int& id_contact)
{
    wxListView *listview_fio = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
    wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_contact->FindWindow(wxID_C_COLLPANE_DOPINFO));
    wxWindow *win1 = collpane1->GetPane();
    
    wxStaticText *statictext = (wxStaticText*)win1->FindWindow(wxID_C_STATICTEXT_COMMENT);
    statictext->SetLabel(wxNULL_STRING);
    wxString sqlText; sqlText<<wxSqlTextSelCommentContact;
    sqlText<<id_contact; sqlText<<wxSqlEndText;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {   
            for (register int i = 0; i < num_rows; i++) // Вывод таблицы
            {
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxString str = row[0];
                if(str.Find("NULL")!=wxNOT_FOUND)
                {str=wxNOT_DATA; statictext->SetLabel(str);}
                else {statictext->SetLabel(str);}
            }
        }
        mysql_free_result(res); // Очищаем результаты
    }
}

void ContactFrm::InsertCallRezult (int i) //i=1 - дозвон, i=2 - недозвон
{
    wxString strFio, strId, sqlText, strIdContact;
    wxListView *listview_fio = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
    wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)panel_contact->FindWindow(wxID_C_COLLPANE_CALL_HIST);
    wxWindow *win2 = collpane2->GetPane();
    wxListView *listview_call = (wxListView*)win2->FindWindow(wxID_C_LISTVIEW_SP_CALL);
    int item_sel = listview_fio->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
    if(item_sel!=-1) {strIdContact<<(listview_fio->GetItemData(item_sel));}
    if(strIdContact.IsEmpty()) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
    wxArrayString strFioAr;
    strFioAr.Add("Ананьев Н.Н.");
    strFioAr.Add("Мишанин А.А.");
    strFioAr.Add("Соцков М.И.");
    strFio = wxGetSingleChoice (wxINFO_SELECT_FIO_CALL, wxCAPTION_CALL, strFioAr);
    strFio.MakeUpper();
    for(register int j =0; j<MyFioSbArray.GetCount();++j)   //заполняем локальный массив
    {
        if(!MyFioSbArray.Item(j).nameFioSb.compare(strFio)) {strId.Clear(); strId<<MyFioSbArray.Item(j).idFioSb;}
    }
    if(strId.IsEmpty()) {return;}
    if(i==1) {sqlText<<wxSqlTextInsCallHis1;} 
    if(i==2) {sqlText<<wxSqlTextInsCallHis2;} 
    sqlText<<strId; sqlText<<wxSqlCommaText;
    sqlText<<strIdContact; sqlText<<wxSqlEndRightBracketText;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    else
    {
        sqlText.Clear();
        sqlText<<wxSqlTextSelIdCall; sqlText<<strIdContact;
        sqlText<<wxSqlTextSelIdCallWhere; sqlText<<strId;
        sqlText<<wxSqlEndTextOrderByDescI;
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
        else
        {
            MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
            //int num_fields = mysql_num_fields(res); // количество полей
            int num_rows = mysql_num_rows(res); // и количество строк.
            if(num_rows>0)
            {   
                //for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                //{
                //int item_number = listview_call->GetItemCount(); //определяем номер последнего элемента для вставки нового
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                f->SetColumn(0);
                f->SetData(wxAtoi(row[0])); //прячем уникальный айди
                f->SetId(0);
                listview_call->InsertItem(*f); 
                delete f;
                wxDateTime dt=dt.Now();
                listview_call->SetItem(0,0,dt.FormatISODate());
                if(i==1) {listview_call->SetItem(0,1,wxCAPTION_BUTTON_CALL_U);}
                if(i==2) {listview_call->SetItem(0,1,wxCAPTION_BUTTON_CALL_F);}
                listview_call->SetItem(0,2,strFio);
                //}

                for (register int i=0; i<(listview_call->GetColumnCount());++i) {listview_call->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента      
            } else {InformationSleep (wxERROR, sec_for_sleep_window_info, this);}
            mysql_free_result(res); // Очищаем результаты
        } 
    }
}

void ContactFrm::OnEnter (wxCommandEvent& event)
{
    switch (event.GetId())
    {
        case wxID_C_SEARCHCTRL_COMPANY:
        {
            wxString textPoisk = ((wxSearchCtrl*)panel_contact->FindWindow(wxID_C_SEARCHCTRL_COMPANY))->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //удаляем в строке поиска пробелы справа и слева
            if(textPoisk.IsEmpty()) {InformationSleep (wxINFO_EMPTY_POISK, sec_for_sleep_window_info, this);} //если строка поиска пуста, предупреждаем об этом пользователя
            else 
            {
                wxListView *listview_company = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_SP_COMP);
                wxListView *listview_fio = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
                listview_company->DeleteAllItems();
                listview_fio->DeleteAllItems();
                
                wxCollapsiblePane *collpane1 = (wxCollapsiblePane*)(panel_contact->FindWindow(wxID_C_COLLPANE_DOPINFO)); 
                wxWindow *win1 = collpane1->GetPane();
                wxStaticText *stText = (wxStaticText*)(win1->FindWindow(wxID_C_STATICTEXT_COMMENT));
                stText->SetLabel(wxNULL_STRING);
    
                wxCollapsiblePane *collpane2 = (wxCollapsiblePane*)(panel_contact->FindWindow(wxID_C_COLLPANE_CALL_HIST)); 
                wxWindow *win2 = collpane2->GetPane();
                wxListView *listview_call = (wxListView*)(win2->FindWindow(wxID_C_LISTVIEW_SP_CALL));
                listview_call->DeleteAllItems();
                
                textPoisk.Replace("?","_",true); //в значении поиска меняем ? на _ для sql-запроса
                wxString sqlText;
                if(textPoisk.IsNumber()) {sqlText<<wxSqlTextSelFindCompByTel; 
                sqlText<<textPoisk; sqlText<<wxSqlTextSelFindCompByTelWhere; sqlText<<textPoisk; sqlText<<wxSqlPercentEnd1;} 
                else {sqlText<<wxSqlTextSelFindComp; sqlText<<textPoisk; sqlText<<wxSqlPercentEnd;}
                //sqlText<<textPoisk; sqlText<<wxSqlPercentEnd;
        
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
                        for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                            f->SetColumn(0);
                            f->SetData(wxAtoi(row[2])); //прячем уникальный айди
                            f->SetId(i);
                            listview_company->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                listview_company->SetItem(i,l,row[l]);
                            }
                            delete f;
                        }
                        WorkStatusBar(); //заполняем статусбар
                        for (register int i=0; i<(listview_company->GetColumnCount());++i) {listview_company->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента      
                    } else {InformationSleep (wxINFO_EMPTY_REZ_POISK, sec_for_sleep_window_info, this);}
                    mysql_free_result(res); // Очищаем результаты
                }
            }
            break;
        }
    default:break;
    }  
}

void ContactFrm::CollapChanged (wxCollapsiblePaneEvent& event)
{
    switch (event.GetId())
    {
        case wxID_C_COLLPANE_DOPINFO:
        case wxID_C_COLLPANE_CALL_HIST:
        {
            panel_contact->Layout(); //просим компоновщик, привязанный к панели на странице со структурой регионов, перестроить окна
            this->Refresh(); //перерисовываем окно
            break;
        }
        default: {break;}
    }
    event.Skip();
}

void ContactFrm::WorkStatusBar (void) //метод заполнаяет поля статус бара
{
    wxListView *listview_company = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_SP_COMP);
    wxListView *listview_fio = (wxListView*)panel_contact->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
    wxString strStBar_company, strStBar_contact, strNameComp;
    strNameComp=wxNULL_STRING;
    strStBar_company=wxCOUNT_STRING; strStBar_company<<listview_company->GetItemCount();
    int item_sel = listview_company->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
    if(item_sel!=-1) {strNameComp=listview_company->GetItemText(item_sel);}
    strStBar_contact=wxSTRING_CON_SEL; strStBar_contact+=strNameComp;
    strStBar_contact+=wxSTRING_CON_COUNT; strStBar_contact<<listview_fio->GetItemCount();
    
    this->SetStatusText(strStBar_company,0);
    this->SetStatusText(strStBar_contact,1);    
}

void ContactFrm::OnMouse(wxMouseEvent& event)
{
	if (event.GetId()==wxID_C_LISTVIEW_SP_COMP)
	{
        //возможна утечка памяти из-за menuitem
        wxPoint point = event.GetPosition(); //определяем коородинаты физического положения мыши
        wxMenu *menu = new wxMenu;
        wxMenuItem *menuitem = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,wxCAPTION_MENU_COMPANY);
        menuitem->SetTextColour(*wxWHITE);
        menuitem->SetBackgroundColour(*wxBLACK);
        menu->Append(menuitem);
        menu->AppendSeparator();
        menu->Append(wxID_C_BUTTON_COMP_INS,wxCAPTION_BUTTON_INSERT);
        menu->Append(wxID_C_BUTTON_COMP_UPD,wxCAPTION_BUTTON_UPDATE);
        menu->Append(wxID_C_BUTTON_COMP_DEL,wxCAPTION_BUTTON_DELETE);
        menu->AppendSeparator();
        wxMenuItem *menuitem1 = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,wxCAPTION_MENU_COMMON);
        menuitem1->SetTextColour(*wxWHITE);
        menuitem1->SetBackgroundColour(*wxBLACK);
        menu->Append(menuitem1);
        menu->AppendSeparator();
        menu->Append(wxID_C_BUTTON_COMP_S_ALL,wxCAPTION_BUTTON_ALL_COMP);
        menu->Append(wxID_C_BUTTON_COMP_S_BANK,wxCAPTION_BUTTON_BANK);
        menu->Append(wxID_C_BUTTON_COMP_S_ORG,wxCAPTION_BUTTON_ORG);
        menu->Append(wxID_C_BUTTON_COMP_S_INSU,wxCAPTION_BUTTON_INSU);
        PopupMenu(menu,point);
        delete menu; 
    }
    if (event.GetId()==wxID_C_LISTVIEW_FIO_CONTACT)
	{
        wxPoint point = event.GetPosition(); //определяем коородинаты физического положения мыши
        wxMenu *menu = new wxMenu;
        wxMenuItem *menuitem = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,wxCAPTION_MENU_CONTACT);
        menuitem->SetTextColour(*wxWHITE);
        menuitem->SetBackgroundColour(*wxBLACK);
        menu->Append(menuitem);
        menu->AppendSeparator();
        menu->Append(wxID_C_BUTTON_CONT_INS,wxCAPTION_BUTTON_INSERT);
        menu->Append(wxID_C_BUTTON_CONT_UPD,wxCAPTION_BUTTON_UPDATE);
        menu->Append(wxID_C_BUTTON_CONT_DEL,wxCAPTION_BUTTON_DELETE);
        PopupMenu(menu,point);
        delete menu; 
    }
    if (event.GetId()==wxID_C_LISTVIEW_SP_CALL)
	{
        wxPoint point = event.GetPosition(); //определяем коородинаты физического положения мыши
        wxMenu *menu = new wxMenu;
        wxMenuItem *menuitem = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,wxCAPTION_MENU_CALL);
        menuitem->SetTextColour(*wxWHITE);
        menuitem->SetBackgroundColour(*wxBLACK);
        menu->Append(menuitem);
        menu->AppendSeparator();
        menu->Append(wxID_C_BUTTON_CALL_U,wxCAPTION_BUTTON_CALL_U);
        menu->Append(wxID_C_BUTTON_CALL_F,wxCAPTION_BUTTON_CALL_F);
        menu->Append(wxID_C_BUTTON_CALL_DELL,wxCAPTION_BUTTON_DELETE);
        PopupMenu(menu,point);
        delete menu; 
    }
}

void ContactFrm::OnSize(wxSizeEvent& event) //ловим размеры окна во время события изменения нижней или правой границы
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_CONTACT/x"), rect.GetX() );
    config->Write( wxT("/FORM_CONTACT/y"), rect.GetY() );
    config->Write( wxT("/FORM_CONTACT/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_CONTACT/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void ContactFrm::OnMove(wxMoveEvent& event) //ловим размеры окна во время события передвижения окна
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_CONTACT/x"), rect.GetX() );
    config->Write( wxT("/FORM_CONTACT/y"), rect.GetY() );
    config->Write( wxT("/FORM_CONTACT/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_CONTACT/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}

ContactFrm::~ContactFrm()
{
}
