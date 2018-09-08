#include "CrossFrm.h"
#include <wx/dcbuffer.h>
extern MYSQL* conn;
extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;

BEGIN_EVENT_TABLE(ProvAgFrm,wxPanel)
	EVT_CLOSE(ProvAgFrm::OnClose)
	//EVT_SIZE(ProvAgFrm::OnSize)
	//EVT_MOVE_END(ProvAgFrm::OnMove)
	EVT_TEXT_ENTER(wxID_AG_PS_TEXT_NAME, ProvAgFrm::OnEnter)
	EVT_MENU(wxID_AG_PS_MENU_FIO, ProvAgFrm::OnMenu)
	EVT_MENU(wxID_AG_PS_MENU_PASP, ProvAgFrm::OnMenu)
	EVT_SEARCHCTRL_CANCEL_BTN(wxID_AG_PS_TEXT_NAME, ProvAgFrm::ClearPoisk)
	EVT_BUTTON(wxID_AG_CM_BUTTON_INS,ProvAgFrm::OnButton)
	EVT_BUTTON(wxID_AG_CM_BUTTON_UPD,ProvAgFrm::OnButton)
	EVT_BUTTON(wxID_AG_CM_BUTTON_DEL,ProvAgFrm::OnButton)
	EVT_BUTTON(wxID_AG_CM_BUTTON_PRV,ProvAgFrm::OnButton)
	EVT_BUTTON(wxID_AG_CM_BUTTON_CLR,ProvAgFrm::OnButton)
	EVT_MENU(wxID_AG_CM_BUTTON_INS,ProvAgFrm::OnButton)
	EVT_MENU(wxID_AG_CM_BUTTON_UPD,ProvAgFrm::OnButton)
	EVT_MENU(wxID_AG_CM_BUTTON_DEL,ProvAgFrm::OnButton)
	EVT_MENU(wxID_AG_CM_BUTTON_PRV,ProvAgFrm::OnButton)
	EVT_MENU(wxID_AG_CM_BUTTON_CLR,ProvAgFrm::OnButton)
END_EVENT_TABLE()


ProvAgFrm::ProvAgFrm(wxWindow *parent, wxWindowID id, /*const wxString &title,*/ const wxPoint& pos, const wxSize& size , long style )
        : wxPanel(parent, id, /*title,*/ pos, size, style)
{
    wxImage::AddHandler(new wxICOHandler);
    wxImage::AddHandler(new wxPNGHandler);
    wxDir dir(wxGetCwd());
    if (!dir.IsOpened())
    {
        wxMessageBox(wxERROR_OPEN_PROGRAM,wxERROR);
        Destroy();
    }
    else
    {
        
        //wxBitmap *bitmap = new wxBitmap(wxString("D:\\Dev-Cpp\\project_new\\Output\\MingW\\icon\\Desert.png"),wxBITMAP_TYPE_PNG);
        //panel = new MyPanel(this,*bitmap);
        
        //panel = new wxPanel(this,wxID_ANY);
        vert_bos = new wxBoxSizer(wxVERTICAL);
        hr1 = new wxBoxSizer(wxHORIZONTAL);
        //stBox1 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_FIND_STRING);
        //stBox2 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_COMMAND);
        stBox3 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_LIST);
        //to_static_box1 = new wxStaticBoxSizer(stBox1,wxHORIZONTAL);
        //to_static_box2 = new wxStaticBoxSizer(stBox2,wxVERTICAL);
        to_static_box3 = new wxStaticBoxSizer(stBox3,wxVERTICAL);
        /*
        to_static_box1->Add(new wxSearchCtrl(this,wxID_AG_PS_TEXT_NAME, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT), 1, wxEXPAND,0);
        ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->SetDescriptiveText(wxString("введите фио для поиска...")); //текст по умолчанию в строке поиска
        ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->ShowCancelButton(1); //делаем активной кнопку отмены
        wxMenu *file_menu = new wxMenu; //создаем меню для поиска
        file_menu->Append(wxID_AG_PS_MENU_FIO, "&ФИО"); 
        file_menu->Append(wxID_AG_PS_MENU_PASP, "&Паспорт");
        ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->SetMenu(file_menu); //подключаем меню к элементку поиска
        //to_static_box1->Add(new wxButton(panel,wxID_AG_PS_BUTTON_WORK,"Поиск"), 0, wxEXPAND|wxLEFT|wxRIGHT ,10);
        to_static_box2->Add(new wxButton(this,wxID_AG_CM_BUTTON_INS,wxCAPTION_BUTTON_INSERT), 0, wxEXPAND ,0);
        to_static_box2->Add(new wxButton(this,wxID_AG_CM_BUTTON_UPD,wxCAPTION_BUTTON_UPDATE), 0, wxEXPAND ,0);
        to_static_box2->Add(new wxButton(this,wxID_AG_CM_BUTTON_DEL,wxCAPTION_BUTTON_DELETE), 0, wxEXPAND ,0);
        to_static_box2->Add(new wxButton(this,wxID_AG_CM_BUTTON_PRV,wxCAPTION_BUTTON_PROV), 0, wxEXPAND ,0);
        to_static_box2->Add(new wxButton(this,wxID_AG_CM_BUTTON_CLR,wxCAPTION_BUTTON_CLEAR), 0, wxEXPAND ,0);
        */
        wxListView *listview = new wxListView(this, wxID_AG_SP_LIST_RES);
        //MyListView *listview = new MyListView(panel, *bitmap, wxID_AG_SP_LIST_RES);
        listview->InsertColumn(0,wxCAPTION_COLUMN_FIO);
        listview->InsertColumn(1,wxCAPTION_COLUMN_PASP_SER);
        listview->InsertColumn(2,wxCAPTION_COLUMN_PASP_NUM);
        listview->InsertColumn(3,wxCAPTION_COLUMN_DATE_ROJD);
        listview->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(ProvAgFrm::OnMouse));
        //listview->SetBackgroundStyle(wxBG_STYLE_TRANSPARENT); //делает фон прозрачным
        
        //listview->SetOwnBackgroundColour(wxTransparentColour); //прозрачный фон
        //listview->SetOwnForegroundColour(wxTransparentColour);
        //listview->SetBackgroundStyle(wxBG_STYLE_CUSTOM); //фон перерисовывается пользователем
        //listview->Connect(wxEVT_ERASE_BACKGROUND,wxEraseEventHandler(ProvAgFrm::OnEaraseListbox)); //при событии перекраски фона запускаем свой метод
        //listview->Connect(wxEVT_PAINT,wxPaintEventHandler(ProvAgFrm::OnPaintListbox)); //при событии рисования запускаем свой метод
        
        to_static_box3->Add(listview, 1, wxEXPAND,0);
        
        //hr1->Add(to_static_box2, 0, wxEXPAND,0);
        hr1->Add(to_static_box3, 1, wxEXPAND|wxLEFT,10);
        //vert_bos->Add(to_static_box1, 0, wxEXPAND|wxBOTTOM ,10);
        vert_bos->Add(hr1, 1, wxEXPAND ,0);
        this->SetSizer(vert_bos);
        //this->CreateStatusBar(2,wxSTB_DEFAULT_STYLE,wxID_AG_STATUSBAR);
        //this->SetStatusText(wxREADDY_,0);
        
        id_menu=0;
        count_find=0;
        count_add=0;
        wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
        for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) {(*it)->SetBackgroundColour(*wxWHITE);} //через итератор перебираем все окна и меняем цвет фона
        wxWindowList list1 = this->GetChildren(); //получаем список всех дочерних окон
        for(register wxWindowList::const_iterator it = list1.begin(); it!=list1.end(); ++it) {(*it)->SetBackgroundColour(*wxWHITE);} //через итератор перебираем все окна и меняем цвет фона
        //Center(); //центрируем окно
    }
}
void ProvAgFrm::OnPaintListbox(wxPaintEvent& event) //пробовал рисовать фон. итог. фон рисуется, а все остальное - нет. оставил для памяти
{

}
void ProvAgFrm::OnEaraseListbox(wxEraseEvent& event) //событие перерисовки фона. Фон рисует, но грузит процессор на 20-25%. Медленная перерисовка при изм.размеров окна
{

}
ProvAgFrm::~ProvAgFrm()
{
}

void ProvAgFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}
/*
void ProvAgFrm::OnSize(wxSizeEvent& event) //ловим размеры окна во время события изменения нижней или правой границы
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_AGENT/x"), rect.GetX() );
    config->Write( wxT("/FORM_AGENT/y"), rect.GetY() );
    config->Write( wxT("/FORM_AGENT/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_AGENT/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void ProvAgFrm::OnMove(wxMoveEvent& event) //ловим размеры окна во время события передвижения окна
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_AGENT/x"), rect.GetX() );
    config->Write( wxT("/FORM_AGENT/y"), rect.GetY() );
    config->Write( wxT("/FORM_AGENT/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_AGENT/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}*/

void ProvAgFrm::OnEnter (wxCommandEvent& event)
{
    wxString textPoisk = ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->GetValue();
    textPoisk.Trim(true); textPoisk.Trim(false); //удаляем в строке поиска пробелы справа и слева
    if(textPoisk.IsEmpty()) {InformationSleep (wxINFO_EMPTY_POISK, sec_for_sleep_window_info, this);} //если строка поиска пуста, предупреждаем об этом пользователя
    else 
    {
        textPoisk.Replace("?","_",true); //в значении поиска меняем ? на _ для sql-запроса
        wxString sqlText;
        if(id_menu==0) //поиск по фио
        {
            sqlText<<wxSqlTextPoiskFzFio;
            sqlText<<textPoisk; sqlText<<wxSqlPercentEnd;
        }
        if(id_menu==1) //поиск по паоспорту
        {
            textPoisk.Replace(" ","",true); //в значении поиска меняем пробел на пустое значение для sql-запроса
            sqlText<<wxSqlTextPoiskFzPasp;
            sqlText<<textPoisk; sqlText<<wxSqlPercentEnd;
        }
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
        else 
        {
            MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
            int num_fields = mysql_num_fields(res); // количество полей
            int num_rows = mysql_num_rows(res); // и количество строк.
            if(num_rows>0)
            {   
                count_find+=num_rows; //прибавляем глобальной переменной кол-во найденнных строк
                wxListView* listview = ((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES));
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
                GetItemCountListCtrl();        //выводим общее кол-во строк в статусбар
            } else {InformationSleep (wxINFO_EMPTY_REZ_POISK_FZ, sec_for_sleep_window_info, this);}
            mysql_free_result(res); // Очищаем результаты
        }
    }
    
}
void ProvAgFrm::OnButton( wxCommandEvent& event)
{
    if(event.GetId()==wxID_AG_CM_BUTTON_CLR)  {((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES))->DeleteAllItems(); count_find=0; count_add=0; GetItemCountListCtrl();}
    if(event.GetId()==wxID_AG_CM_BUTTON_INS)  
    {
        EnterFz EntFz(this,0,0); 
        if(EntFz.ShowModal() == wxID_CANCEL) {;} else {((wxAuiWorkPanel*)((this->GetParent())->GetParent()))->WorkStatusBar();}
        (((this->GetParent())->GetParent())->FindWindow(wxID_AG_CM_BUTTON_PRV))->SetFocus(); 
    }
    if(event.GetId()==wxID_AG_CM_BUTTON_UPD)  
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES)); //получаем указатель на листвьюев 
        int count = 0;
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} //не выбрана ниодна строка, поэтому выходим из цикла
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
            (((this->GetParent())->GetParent())->FindWindow(wxID_AG_CM_BUTTON_UPD))->SetFocus(); 
        }
    }
    if(event.GetId()==wxID_AG_CM_BUTTON_DEL)  
    {
        DeleteFz(); ((wxAuiWorkPanel*)((this->GetParent())->GetParent()))->WorkStatusBar();    
    }
    if(event.GetId()==wxID_AG_CM_BUTTON_PRV)  
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES)); //получаем указатель на листвьюев 
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
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
                ListProvFz ListPrFz(this,wxAtoi(idFz),captionFioAndPasp,wxID_ANY,wxPoint(x,y),wxSize(width,height)); //создаем диалоговое окно с проверками выбранного физ.лица с заголовком из фио+паспорт
                if(ListPrFz.ShowModal() == wxID_CANCEL) {;} else {;}
            }
             else                   //параметры конфигурации не прочитаны из ini-файла
            {
                ListProvFz ListPrFz(this,wxAtoi(idFz),captionFioAndPasp); //создаем диалоговое окно с проверками выбранного физ.лица с заголовком из фио+паспорт
                if(ListPrFz.ShowModal() == wxID_CANCEL) {;} else {;}
            }
        }
        (((this->GetParent())->GetParent())->FindWindow(wxID_AG_CM_BUTTON_PRV))->SetFocus();     
    }
}
void ProvAgFrm::OnMenu (wxCommandEvent& event)
{
    if(event.GetId()==wxID_AG_PS_MENU_FIO) {id_menu=0; ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->SetDescriptiveText(wxString("введите фио для поиска...")); ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->Clear();} // при смене параметра поиска(фио, паспорт) переписываем: переменную, строку подсказки, очищаем поле писка
    if(event.GetId()==wxID_AG_PS_MENU_PASP) {id_menu=1; ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->SetDescriptiveText(wxString("введите паспорт для поиска...")); ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->Clear();} // при смене параметра поиска(фио, паспорт) переписываем: переменную, строку подсказки, очищаем поле писка
}
void ProvAgFrm::ClearPoisk (wxCommandEvent& event)
{
    ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->Clear();
}
void ProvAgFrm::GetItemCountListCtrl (void)
{
    wxString status1=wxCOUNT_FIND; status1<<count_find;
    wxString status2=wxCOUNT_ADD; status2<<count_add;
    //this->SetStatusText(status1,0);
    //this->SetStatusText(status2,1);
}
void ProvAgFrm::DeleteFz (void)
{
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES)); //получаем указатель на листвьюев  
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
                    /*sqlText = wxSqlTextDelFzProvStart; sqlText<<idFz; sqlText<<wxSqlEndText;
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
            (((this->GetParent())->GetParent())->FindWindow(wxID_AG_CM_BUTTON_DEL))->SetFocus();
        }
}
void ProvAgFrm::OnMouse(wxMouseEvent& event)
{
	if (event.GetId()==wxID_AG_SP_LIST_RES)
	{
        //возможна утечка памяти из-за menuitem
        wxPoint point = event.GetPosition(); //определяем коородинаты физического положения мыши
        wxMenu *menu = new wxMenu;
        //wxMenuItem *menuitem = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,"Команды");
        //menuitem->SetTextColour(*wxWHITE);
        //menuitem->SetBackgroundColour(*wxBLACK);
        //menu->Append(menuitem);
        //menu->AppendSeparator();
        menu->Append(wxID_AG_CM_BUTTON_INS,wxCAPTION_BUTTON_INSERT);
        menu->Append(wxID_AG_CM_BUTTON_UPD,wxCAPTION_BUTTON_UPDATE);
        menu->Append(wxID_AG_CM_BUTTON_DEL,wxCAPTION_BUTTON_DELETE);
        menu->Append(wxID_AG_CM_BUTTON_PRV,wxCAPTION_BUTTON_PROV);
        menu->Append(wxID_AG_CM_BUTTON_CLR,wxCAPTION_BUTTON_CLEAR);
        PopupMenu(menu,point);
        delete menu; 
    }    
}
