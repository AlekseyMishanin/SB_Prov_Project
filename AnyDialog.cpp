#include "CrossFrm.h"

MYSQL* conn; //создаем объект MYSQL
int flag_conn_mysql=0; //флаг соединения с БД: 0 - успешно, 1 - не успешно (программа закрывается).
connect_user usr; //создаем объект юзера с параметрами:хост,бд,логин,пароль
ListMatchFio listFio; //объект класса в который пишутся все найденные совпадения по ФИО при добавлении проверки физ.лица

extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;

extern void insertStrDateToCtrl (wxString& str, wxDatePickerCtrl* window);
extern void EditStringFio (wxString& str); //функция редактирует строку wxString меняя ИВАНОВ ИВАН ИВАНОВИЧ на Иванов И.И.
extern int proverka_bl_sb(MYSQL* conn, wxString& str, int type); //функция проверяет str на предмет наличия в ЧС СБ. type - тип ЧС СБ для проверки, 0 - ТО, 1 - физики

/* определения методов класса ListMatchFio */
void ListMatchFio::Clear (void) //метод очищает данные-члены класса
{
    idReestrFio.Clear();
    fio.Clear();
    seriy_pasp.Clear();
    number_pasp.Clear();
    dr.Clear();
    count=0;
}
/*конец определения методов класса ListMatchFio*/





/*
Dialog - EnterPassword - start
*/

BEGIN_EVENT_TABLE(EnterPassword,wxDialog)
    EVT_BUTTON (wxID_OK, EnterPassword::OnButton)
    EVT_BUTTON (wxID_CANCEL, EnterPassword::OnButton)
END_EVENT_TABLE()

EnterPassword::EnterPassword(wxWindow *parent, wxWindowID id, const wxString &caption, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);

    hr1->Add(new wxStaticText(this,wxID_ANY,"Хост"), 1, wxEXPAND|wxLEFT ,5);
    hr1->Add(new wxTextCtrl(this,wxID_DL_TEXT_HOST, wxT("msk1-cro")), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr2->Add(new wxStaticText(this,wxID_ANY,"База данных"), 1, wxEXPAND|wxLEFT,5);
    hr2->Add(new wxTextCtrl(this,wxID_DL_TEXT_BD, wxT("proverka")), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr3->Add(new wxStaticText(this,wxID_ANY,"Логин"), 1, wxEXPAND|wxLEFT,5);
    hr3->Add(new wxTextCtrl(this,wxID_DL_TEXT_USER, wxGetUserName()), 0, wxEXPAND|wxLEFT|wxRIGHT,0); //обратите внимание используется функция wxGetUserName для подгрузки имени пользователя
    hr4->Add(new wxStaticText(this,wxID_ANY,"Пароль"), 1, wxEXPAND|wxLEFT,5);
    hr4->Add(new wxTextCtrl(this,wxID_DL_TEXT_PASS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT|wxTE_PASSWORD), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    vert_bos->Add(hr1, 0, wxEXPAND,0);
    vert_bos->Add(hr2, 0, wxEXPAND,0);
    vert_bos->Add(hr3, 0, wxEXPAND,0);
    vert_bos->Add(hr4, 0, wxEXPAND,0);
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0);
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    SetAffirmativeId(wxID_OK); //Задаем идентификатор для использования в качестве кнопки ОК
    (this->FindWindow(wxID_OK))->SetFocus(); //устанавливаем фокус ввода на кнопку ОК
}

void EnterPassword::OnButton( wxCommandEvent& event)
{
	if(event.GetId()==wxID_OK)
	{
        usr.host = ((wxTextCtrl*)(this->FindWindow(wxID_DL_TEXT_HOST)))->GetValue();
        usr.bd = ((wxTextCtrl*)(this->FindWindow(wxID_DL_TEXT_BD)))->GetValue();
        usr.user = ((wxTextCtrl*)(this->FindWindow(wxID_DL_TEXT_USER)))->GetValue();
        usr.password = ((wxTextCtrl*)(this->FindWindow(wxID_DL_TEXT_PASS)))->GetValue();
        if(!usr.user.compare(wxGetUserName())||!usr.user.compare(wxString("root"))) {;} else {InformationSleep(wxINFO_LOGIN,sec_for_sleep_window_info,this); return;} //проверяем чтобы введенный логин совпадал с именем пользователя в ОС или с root
        /*
        mysql_init выделяет или инициализирует объект MYSQL, подходящий для функции mysql_real_connect(). 
        Если аргумент mysql представляет собой указатель NULL, то эта функция выделяет, инициализирует и 
        возвращает новый объект. В противном случае инициализируется указанный объект и возвращается его адрес. 
        Если функция mysql_init() выделяет новый объект, то он будет освобожден при вызове функции 
        mysql_close(), чтобы закрыть данное соединение.
        */
        conn=mysql_init(NULL);
        //Функция mysql_real_connect() пытается установить соединение с сервером баз данных MySQL, работающим на хосте host. 
        if(mysql_real_connect(conn, usr.host.c_str(), 
                                usr.user.c_str(),
                                usr.password.c_str(),
                                usr.bd.c_str(),
                                0, NULL, 0) == NULL)
        {
            //Подключаемся к БД. Если соединение не установлено, то сообщаем пользователю об ошибке и завершаем работу приложения
            wxMessageBox(mysql_error(conn), wxERROR);
            flag_conn_mysql=1;
        };
        this->EndModal(wxID_OK);
    }
    if(event.GetId()==wxID_CANCEL)
	{
        this->EndModal(wxID_CANCEL);
    }
}
EnterPassword::~EnterPassword()
{
}

/*
Dialog - EnterPassword - end
*/

/*
Dialog - EnterAssortiment - start
*/

BEGIN_EVENT_TABLE(EnterAssortiment,wxDialog)
    EVT_BUTTON (wxID_OK, EnterAssortiment::OnButton)
    EVT_BUTTON (wxID_CANCEL, EnterAssortiment::OnButton)
    EVT_CHILD_FOCUS(EnterAssortiment::NewFocus)
END_EVENT_TABLE()

EnterAssortiment::EnterAssortiment(wxWindow *parent, wxWindowID id, const wxString &inn_text, const wxString &caption, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    inn = inn_text;
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);

    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PROD_GROUP), 0, wxEXPAND|wxLEFT ,5);
    hr1->Add(new wxTextCtrl(this,wxID_AS_TEXT_GROUP, wxT(""), wxDefaultPosition, wxSize(250,-1),wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
    LocArray.Alloc(MyProdGroupArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyProdGroupArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyProdGroupArray.Item(i).nameProdGroup));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_AS_TEXT_GROUP))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PROD_SUBGROUP), 0, wxEXPAND|wxLEFT,5);
    hr2->Add(new wxTextCtrl(this,wxID_AS_TEXT_SUBGROUP, wxT("")), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    vert_bos->Add(hr1, 0, wxEXPAND,0);
    vert_bos->Add(hr2, 0, wxEXPAND,0);
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0);
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    SetAffirmativeId(wxID_OK); //Задаем идентификатор для использования в качестве кнопки ОК
    (this->FindWindow(wxID_AS_TEXT_GROUP))->SetFocus(); //устанавливаем фокус ввода  
}

void EnterAssortiment::NewFocus(wxChildFocusEvent& event)
{
    if(window_last->GetId()==wxID_AS_TEXT_GROUP) 
    {
        int flag=0;                                       //флаг совпадения значения текстового поля со значением массива. 0 - нет совпадения, 1 - есть совпадение                                                  
        wxString str = ((wxTextCtrl*)window_last)->GetValue();          //присваиваем переменной значение текстового поля
        str.MakeUpper();                                                //приводим символы переменной к верхнему регистру
        for(register int i =0; i<MyProdGroupArray.GetCount();++i)       //запускаем цикл поиска совпадений в массиве наименований групп товаров
        {
            if (!str.compare(MyProdGroupArray.Item(i).nameProdGroup))
            {flag=1; id_group=MyProdGroupArray.Item(i).idProdGroup; break;}      //совпадение найдено: меняем значение флага, присваиваем переменной id_group айди товарной группы, выходим из цикла
        }
        if(flag==0){((wxTextCtrl*)window_last)->Clear(); id_group=0;/*id_group.Clear();*/}               //флаг=0, совпадений в цикле не выявлено => очищаем текстовое поле
        if(flag==1)
        {
            wxArrayString LocArray;                                     //объявляем массив для автозаполнения в текстовом поле
            LocArray.Alloc(MyProdGroupArray.GetCount());                //Резервирует достаточно памяти для хранения nCount предметов   
            for(register int i =0; i<MyProdNameArray.GetCount();++i)   //заполняем локальный массив наименованиями торговых сетей
            {
                //if(!id_group.compare(MyProdNameArray.Item(i).idProdGroup))
                if(id_group==MyProdNameArray.Item(i).idProdGroup)
                {LocArray.Add(MyProdNameArray.Item(i).nameProdName);}
            }
            ((wxTextCtrl*)this->FindWindow(wxID_AS_TEXT_SUBGROUP))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
            //((wxTextCtrl*)this->FindWindow(wxID_AS_TEXT_SUBGROUP))->Clear();                
        }
    }
    if(window_last->GetId()==wxID_AS_TEXT_SUBGROUP) 
    {
        int flag=0;                                                     //флаг совпадения значения текстового поля со значением массива. 0 - нет совпадения, 1 - есть совпадение
        wxString str = ((wxTextCtrl*)window_last)->GetValue();          //присваиваем переменной значение текстового поля
        wxString str1 = ((wxTextCtrl*)(this->FindWindow(wxID_AS_TEXT_GROUP)))->GetValue();
        str.MakeUpper();                                                //приводим символы переменной к верхнему регистру
        for(register int i =0; i<MyProdNameArray.GetCount();++i)       //запускаем цикл поиска совпадений в массиве наименований подгрупп товаров
        {
            //if ((!str.compare(MyProdNameArray.Item(i).nameProdName))&&(!id_group.compare(MyProdNameArray.Item(i).idProdGroup))&&(!str1.IsEmpty())) //условие: значение переменноей совпадает со значением массива, айди группы совпадает со значением массива, текстовое поле с товарное группой не пустое
            if ((!str.compare(MyProdNameArray.Item(i).nameProdName))&&(id_group==MyProdNameArray.Item(i).idProdGroup)&&(!str1.IsEmpty()))
            {flag=1; break;}      //совпадение найдено: меняем значение флага, выходим из цикла
        }
        if(flag==0){((wxTextCtrl*)window_last)->Clear();}               //флаг=0, совпадений в цикле не выявлено => очищаем текстовое поле
    }
    window_last=event.GetWindow(); //присваиваем переменной идентификатор окна, которое получило фокус ввода. Переменная нужна для if при получении фокуса ввода следующим окном. ПРИСВАИВАНИЕ ОБЯЗАТЕЛЬНО В КОНЦЕ СПИСКА ОПЕРАТОРОВ
}

void EnterAssortiment::OnButton( wxCommandEvent& event)
{
    if(event.GetId()==wxID_OK)
	{
        wxString idGroup = ((wxTextCtrl*)(this->FindWindow(wxID_AS_TEXT_GROUP)))->GetValue(); //пишем в переменную значение поля товарной группы
        wxString idSubGroup =((wxTextCtrl*)(this->FindWindow(wxID_AS_TEXT_SUBGROUP)))->GetValue(); idSubGroup.MakeUpper(); //пишем в переменную значение поля товарной подгруппы
        if(idGroup.IsEmpty()) {InformationSleep(wxINFO_NOT_PROD_GROUP,sec_for_sleep_window_info,this); return;}             //если поле с товарной группой пустое, информируем об этом пользователя и завершаем обработку
        if(idSubGroup.IsEmpty()) {InformationSleep(wxINFO_NOT_PROD_SUBGROUP,sec_for_sleep_window_info,this); return;}       //если поле с товарной подгруппой пустое, информируем об этом пользователя и завершаем обработку
        for(register int i =0; i<MyProdNameArray.GetCount();++i)       //запускаем цикл поиска совпадений в массиве наименований подгрупп товаров
        {
            //if ((!idSubGroup.compare(MyProdNameArray.Item(i).nameProdName))&&(!id_group.compare(MyProdNameArray.Item(i).idProdGroup)))
            if ((!idSubGroup.compare(MyProdNameArray.Item(i).nameProdName))&&(id_group==MyProdNameArray.Item(i).idProdGroup))
            //{idSubGroup=MyProdNameArray.Item(i).idProdName; idGroup=MyProdNameArray.Item(i).idProdGroup; break;}      //совпадение найдено: присваиваем переменным айди группы и подгруппы, выходим из цикла
            {idSubGroup.Clear(); idSubGroup<<MyProdNameArray.Item(i).idProdName; idGroup.Clear(); idGroup<<MyProdNameArray.Item(i).idProdGroup; break;} 
        }
        wxString sqlText; sqlText<<wxSqlTextInsAssorti;
        sqlText<<inn; sqlText<<wxSqlCommaText;
        sqlText<<idGroup; sqlText<<wxSqlCommaText;
        sqlText<<idSubGroup; sqlText<<wxSqlEndRightBracketText;
        //ProvToFrm *parentWindow = (ProvToFrm*)this->GetParent(); //присваиваем переменной указатель на родительское окно
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
        else
        {
            this->EndModal(wxID_OK);
            /*wxString inn_to = ((wxTextCtrl*)((parentWindow)->FindWindow(wxID_TO_INN)))->GetValue(); //пишем в переменную значение текстового поля родительского окна
            if (inn_to.IsNumber()&&!inn_to.IsEmpty()) //проверка того, что ИНН не пуст, и что это число
            { 
                wxString sqlText; sqlText<<wxSqlTextAssortiTo; sqlText<<inn_to; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
                        wxListView* listview = ((wxListView*)(parentWindow)->FindWindow(wxID_LISTVIEW_ASRT));
                        ((wxListView*)(parentWindow)->FindWindow(wxID_LISTVIEW_ASRT))->DeleteAllItems();
                        for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[2])); //прячем уникальный айди
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                listview->SetItem(i,l,row[l]); //пишем в листвьюев найденные пары группа-подгруппа
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                        //wxString status = wxCOUNT_ASSORTI; 
                        (parentWindow->count_assorti)=num_rows;
                        //parentWindow->SetStatusText(status,2);
                    } else {;}
                    mysql_free_result(res); // Очищаем результаты
                    
                    //(parentWindow->FindWindow(wxID_BUTTON_INS_ASRT))->SetFocus();
                }
            }*/
        }
    }
    if(event.GetId()==wxID_CANCEL)
	{
        //ProvToFrm *parentWindow = (ProvToFrm*)this->GetParent(); //присваиваем переменной указатель на родительское окно
        this->EndModal(wxID_CANCEL);
        //(parentWindow->FindWindow(wxID_BUTTON_INS_ASRT))->SetFocus();
    }
}

EnterAssortiment::~EnterAssortiment()
{
}

/*
Dialog - EnterAssortiment - end
*/

/*
Dialog - EnterProvTo - start
*/

BEGIN_EVENT_TABLE(EnterProvTo,wxDialog)
    EVT_BUTTON (wxID_OK, EnterProvTo::OnButton)
    EVT_BUTTON (wxID_CANCEL, EnterProvTo::OnButton)
    EVT_CHILD_FOCUS(EnterProvTo::NewFocus)
    EVT_CHAR_HOOK(EnterProvTo::OnChar)
END_EVENT_TABLE()

EnterProvTo::EnterProvTo(wxWindow *parent, int id1, int type, wxWindowID id, const wxString &caption, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
    hr5 = new wxBoxSizer(wxHORIZONTAL); //органы управления подгружаются при выборе типа сотрудничества - контрагент
    wxBoxSizer *hr6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr7 = new wxBoxSizer(wxHORIZONTAL);
    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_TYPE "*"), 0, wxEXPAND|wxLEFT ,5);
    hr1->Add(new wxTextCtrl(this,wxID_PR_TYPE_COOPER, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
    LocArray.Alloc(MyTypeCooperationArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyTypeCooperationArray.GetCount();++i) //заполняем локальный массив наименованиями типов сотрудничества
    {
        LocArray.Add((MyTypeCooperationArray.Item(i).nameTypeCooperation));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_COOPER))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PROV "*"), 0, wxEXPAND|wxLEFT ,5);
    hr1->Add(new wxTextCtrl(this,wxID_PR_TYPE_PROV, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyTypeProvArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyTypeProvArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyTypeProvArray.Item(i).nameTypeProv));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_PROV))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_OC "*"), 0, wxEXPAND|wxLEFT ,5);
    hr2->Add(new wxTextCtrl(this,wxID_PR_OC, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyOcArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyOcArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        //if(!MyOcArray.Item(i).activOc.compare("1")) {LocArray.Add((MyOcArray.Item(i).nameOc));} else {continue;}
        if(MyOcArray.Item(i).activOc==1) {LocArray.Add((MyOcArray.Item(i).nameOc));} else {continue;}
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_OC))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_GC "*"), 0, wxEXPAND|wxLEFT ,5);
    hr2->Add(new wxTextCtrl(this,wxID_PR_GC, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_COMENT), 0, wxEXPAND|wxLEFT ,5);
    hr3->Add(new wxTextCtrl(this,wxID_PR_COMMENT, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr4->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_UK), 0, wxEXPAND|wxLEFT ,5);
    hr4->Add(new wxTextCtrl(this,wxID_PR_UK, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyUkRfArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyUkRfArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyUkRfArray.Item(i).nameUkRf));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_UK))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    hr6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_REZ "*"), 0, wxEXPAND|wxLEFT ,5);
    hr6->Add(new wxTextCtrl(this,wxID_PR_REZULT, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyRezProvArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyRezProvArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyRezProvArray.Item(i).nameRezProv));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_REZULT))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    hr6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_SOTRSB "*"), 0, wxEXPAND|wxLEFT ,5);
    hr6->Add(new wxTextCtrl(this,wxID_PR_SOTR_SB, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyFioSbArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyFioSbArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyFioSbArray.Item(i).nameFioSb));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_SOTR_SB))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    hr7->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_DATE "*"), 0, wxEXPAND|wxLEFT ,5);
    hr7->Add(new wxDatePickerCtrl(this,wxID_PR_DATE_PROV,  wxDefaultDateTime, wxDefaultPosition, wxDefaultSize,wxDP_DEFAULT), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr7->AddSpacer(50);
    hr7->Add(new wxButton(this,wxID_OK, wxT("Ok")), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr7->Add(new wxButton(this,wxID_CANCEL, wxT("Cancel")), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    vert_bos->Add(hr1, 0, wxEXPAND,0);
    vert_bos->Add(hr2, 0, wxEXPAND,0);
    vert_bos->Add(hr3, 0, wxEXPAND,0);
    vert_bos->Add(hr4, 0, wxEXPAND,0);
    vert_bos->Add(hr5, 0, wxEXPAND,0);
    vert_bos->Add(hr6, 0, wxEXPAND,0);
    vert_bos->Add(hr7, 0, wxEXPAND,0);
    id_<<id1;                 //присваиваем переменной айди то, или айди проверки то
    type_operation<<type;    //присваиваем переменной признак операции: добавить (0), обновить (1)
    //wxButton *fastComment = new wxButton(this,wxID_PR_FASTCOMMENT, wxT("fastComment")); //создаем кнопку специально для акселератора
    //fastComment->Hide();	//скрываем кнопку от пользователя
    /*Включаем акселераторы*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*конец с акселераторами*/
    if(type==1)
    {
        wxString sqlText; sqlText<<wxSqlTextProvToOne;
        sqlText<<id_; sqlText<<wxSqlEndText;
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
                    for (register int l = 0; l < num_fields; l++)
                    {
                        if (l==0) 
                        {
                            for(register int k =0; k<MyTypeCooperationArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(wxAtoi(MyTypeCooperationArray.Item(k).idTypeCooperation.c_str())==wxAtoi(row[l])) //совпадение найдено
                                if(MyTypeCooperationArray.Item(k).idTypeCooperation==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_COOPER))->ChangeValue(MyTypeCooperationArray.Item(k).nameTypeCooperation);
                                    /*если тип обновляемой проверки - контрагент, то создаем поле с инициатором проверки и подгружаем в поле значение*/
                                    if(!MyTypeCooperationArray.Item(k).nameTypeCooperation.compare(wxSTRING_CONTRACTOR))
                                    {
                                        hr5->Add(new wxStaticText(this,wxID_PR_ST_INITIATOR,wxCAPTION_STATICTEXT_INITIATOR "*"), 0, wxEXPAND|wxLEFT ,5);
                                        hr5->Add(new wxTextCtrl(this,wxID_PR_TC_INITIATOR, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
                                        wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
                                        LocArray.Alloc(MyTypeCooperationArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
                                        for(register int i =0; i<MyInitiatorChecksArray.GetCount();++i) //заполняем локальный массив наименованиями типов сотрудничества
                                        {
                                            LocArray.Add((MyInitiatorChecksArray.Item(i).nameInitiatorChecks));
                                            //if(!MyInitiatorChecksArray.Item(i).idInitiatorChecks.compare(row[9]))
                                            if(MyInitiatorChecksArray.Item(i).idInitiatorChecks==wxAtoi(row[9]))
                                            {
                                                ((wxTextCtrl*)this->FindWindow(wxID_PR_TC_INITIATOR))->ChangeValue(MyInitiatorChecksArray.Item(i).nameInitiatorChecks); //подгружаем в поле инициатора
                                            }
                                        }
                                        ((wxTextCtrl*)this->FindWindow(wxID_PR_TC_INITIATOR))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
                                        LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
                                        wxTextCtrl *wxUk = ((wxTextCtrl*)this->FindWindow(wxID_PR_UK)); //получаем указатель на текстовый редактор с УК РФ
                                        (this->FindWindow(wxID_PR_TC_INITIATOR))->MoveAfterInTabOrder(wxUk); //перемещаем окно инициатора на место послу УК РФ по нажатию таб  
                                    }
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==1) 
                        {
                            for(register int k =0; k<MyTypeProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(wxAtoi(MyTypeProvArray.Item(k).idTypeProv.c_str())==wxAtoi(row[l])) //совпадение найдено
                                if(MyTypeProvArray.Item(k).idTypeProv==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_PROV))->ChangeValue(MyTypeProvArray.Item(k).nameTypeProv);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==2) 
                        {
                            for(register int k =0; k<MyOcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(wxAtoi(MyOcArray.Item(k).idOc.c_str())==wxAtoi(row[l])) //совпадение найдено
                                if(MyOcArray.Item(k).idOc==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_OC))->ChangeValue(MyOcArray.Item(k).nameOc);
                                    id_oc=wxAtoi(row[l]);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==3) 
                        {
                            for(register int k =0; k<MyGcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(wxAtoi(MyGcArray.Item(k).idGc.c_str())==wxAtoi(row[l])) //совпадение найдено
                                if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //совпадение найдено
                                {   
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->ChangeValue(MyGcArray.Item(k).nameGc);
                                    id_gc=wxAtoi(row[l]);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==4)  {((wxTextCtrl*)this->FindWindow(wxID_PR_COMMENT))->ChangeValue(row[l]);}
                        if (l==5) 
                        {
                            for(register int k =0; k<MyUkRfArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(wxAtoi(MyUkRfArray.Item(k).idUkRf.c_str())==wxAtoi(row[l])) //совпадение найдено
                                if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_UK))->ChangeValue(MyUkRfArray.Item(k).nameUkRf);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==6) 
                        {
                            for(register int k =0; k<MyRezProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(wxAtoi(MyRezProvArray.Item(k).idRezProv.c_str())==wxAtoi(row[l])) //совпадение найдено
                                if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_REZULT))->ChangeValue(MyRezProvArray.Item(k).nameRezProv);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==7) 
                        {
                            for(register int k =0; k<MyFioSbArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(wxAtoi(MyFioSbArray.Item(k).idFioSb.c_str())==wxAtoi(row[l])) //совпадение найдено
                                if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_SOTR_SB))->ChangeValue(MyFioSbArray.Item(k).nameFioSb);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==8) 
                        {
                            wxString str=row[l]; //пишем дату из результата выборки запроса в переменную
                            
                            insertStrDateToCtrl (str, (wxDatePickerCtrl*)this->FindWindow(wxID_PR_DATE_PROV));
                        }
                    }
                }
            }
            mysql_free_result(res); // Очищаем результаты
        }
    }
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    this->SetAffirmativeId(wxID_OK); //Задаем идентификатор для использования в качестве кнопки ОК
    (this->FindWindow(wxID_PR_TYPE_COOPER))->SetFocus(); //устанавливаем фокус ввода на поле Тип сотрудничества
}

void EnterProvTo::NewFocus(wxChildFocusEvent& event)
{
    if(idWindowFocus==wxID_PR_TYPE_COOPER)
    {
        wxString strCooperation = ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_COOPER))->GetValue();
        if(!strCooperation.IsEmpty()) //строка не пуста
        {
            strCooperation.MakeUpper(); //приводим к вершнему регистру
            if(!strCooperation.compare(wxSTRING_CONTRACTOR)) //строка == КОНТРАГЕНТ
            {
                if(this->FindWindow(wxID_PR_TC_INITIATOR)) {;}//если существует, не создаем
                else
                {
                    hr5->Add(new wxStaticText(this,wxID_PR_ST_INITIATOR,wxCAPTION_STATICTEXT_INITIATOR "*"), 0, wxEXPAND|wxLEFT ,5);
                    hr5->Add(new wxTextCtrl(this,wxID_PR_TC_INITIATOR, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
                    wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
                    LocArray.Alloc(MyInitiatorChecksArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
                    for(register int i =0; i<MyInitiatorChecksArray.GetCount();++i) //заполняем локальный массив наименованиями типов сотрудничества
                    {
                        LocArray.Add((MyInitiatorChecksArray.Item(i).nameInitiatorChecks));
                    }
                    ((wxTextCtrl*)this->FindWindow(wxID_PR_TC_INITIATOR))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
                    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
                    wxTextCtrl *wxUk = ((wxTextCtrl*)this->FindWindow(wxID_PR_UK)); //получаем указатель на текстовый редактор с УК РФ
                    (this->FindWindow(wxID_PR_TC_INITIATOR))->MoveAfterInTabOrder(wxUk); //перемещаем окно инициатора на место послу УК РФ по нажатию таб                     
                }
            }
            else
            {
                if(this->FindWindow(wxID_PR_TC_INITIATOR)) //если существует, разрушеам 
                {
                    hr5->Clear(); //отсоединяем окна от компоновщика
                    (wxStaticText*)(this->FindWindow(wxID_PR_ST_INITIATOR))->Destroy();  //удаляем окно
                    (wxTextCtrl*)(this->FindWindow(wxID_PR_TC_INITIATOR))->Destroy(); 
                }
            }
        }
        else
        {
            if(this->FindWindow(wxID_PR_TC_INITIATOR)) //если существует, разрушеам 
            {
                hr5->Clear();
                (wxStaticText*)(this->FindWindow(wxID_PR_ST_INITIATOR))->Destroy(); 
                (wxTextCtrl*)(this->FindWindow(wxID_PR_TC_INITIATOR))->Destroy(); 
            }
        }
        this->Layout();
        this->Refresh();
        this->SetSizerAndFit(vert_bos);
    }
    if(idWindowFocus==wxID_PR_OC)
    {
        ((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->Clear();
        int flag=0;                                       //флаг совпадения значения текстового поля со значением массива. 0 - нет совпадения, 1 - есть совпадение                                                  
        wxString str = ((wxTextCtrl*)this->FindWindow(wxID_PR_OC))->GetValue();          //присваиваем переменной значение текстового поля
        int idReg=0;
        str.MakeUpper();                                                //приводим символы переменной к верхнему регистру
        for(register int i =0; i<MyOcArray.GetCount();++i)       //запускаем цикл поиска совпадений в массиве наименований групп товаров
        {
            if ((MyOcArray.Item(i).activOc==1)&&(!str.compare(MyOcArray.Item(i).nameOc)))
            {flag=1; idReg=MyOcArray.Item(i).idOc; /*str = MyOcArray.Item(i).idOc;*/ id_oc=MyOcArray.Item(i).idOc; break;}      //совпадение найдено: меняем значение флага,  выходим из цикла
        }
        if(flag==0){((wxTextCtrl*)this->FindWindow(wxID_PR_OC))->Clear(); id_oc=0; /*id_oc.Clear();*/}               //флаг=0, совпадений в цикле не выявлено => очищаем текстовое поле
        if(flag==1)
        {
            wxArrayString LocArray;                                     //объявляем массив для автозаполнения в текстовом поле
            for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //заполняем локальный массив наименованиями торговых сетей
            {
                //if(!str.compare(MyTechCentrArray.Item(i).son))
                if(idReg==MyTechCentrArray.Item(i).son)
                {
                    for(register int j =0; j<MyGcArray.GetCount();++j)   //заполняем локальный массив наименованиями торговых сетей
                    {
                        //if((!MyGcArray.Item(j).activGc.compare("1"))&&(!MyTechCentrArray.Item(i).parent.compare(MyGcArray.Item(j).idGc)))
                        if((MyGcArray.Item(j).activGc==1)&&(MyTechCentrArray.Item(i).parent==MyGcArray.Item(j).idGc))
                        {
                            LocArray.Add(MyGcArray.Item(j).nameGc); break;
                        }
                    }
                }
            }
            ((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста                                   
        }
    }
    if(idWindowFocus==wxID_PR_GC) 
    {
        int flag=0;                                                     //флаг совпадения значения текстового поля со значением массива. 0 - нет совпадения, 1 - есть совпадение
        wxString str = ((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->GetValue();          //присваиваем переменной значение текстового поля
        int idReg=0;
        str.MakeUpper();                                                //приводим символы переменной к верхнему регистру
        for(register int j =0; j<MyGcArray.GetCount();++j)   //заполняем локальный массив наименованиями торговых сетей
        {
            //if((!MyGcArray.Item(j).activGc.compare("1"))&&(!MyGcArray.Item(j).nameGc.compare(str)))
            if((MyGcArray.Item(j).activGc==1)&&(!MyGcArray.Item(j).nameGc.compare(str)))
            {
                for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //заполняем локальный массив наименованиями торговых сетей
                {
                            //if((!MyGcArray.Item(j).activGc.compare("1"))&&(!MyTechCentrArray.Item(i).parent.compare(MyGcArray.Item(j).idGc)))
                            if((MyTechCentrArray.Item(i).son==id_oc)&&(MyTechCentrArray.Item(i).parent==MyGcArray.Item(j).idGc))
                            {
                                idReg=MyGcArray.Item(j).idGc; break;
                            }
                }
               //str=MyGcArray.Item(j).idGc; break;
               
            }
        }
        for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //заполняем локальный массив наименованиями торговых сетей
        {
            //if ((!id_oc.compare(MyTechCentrArray.Item(i).son))&&(!MyTechCentrArray.Item(i).parent.compare(str))) //условие: значение переменноей совпадает со значением массива, айди группы совпадает со значением массива, текстовое поле с товарное группой не пустое
            if ((id_oc==MyTechCentrArray.Item(i).son)&&(MyTechCentrArray.Item(i).parent==idReg)) //условие: значение переменноей совпадает со значением массива, айди группы совпадает со значением массива, текстовое поле с товарное группой не пустое
            {flag=1; id_gc=idReg; break;}      //совпадение найдено: меняем значение флага, выходим из цикла
        }
        if(flag==0){((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->Clear(); id_gc=0;}               //флаг=0, совпадений в цикле не выявлено => очищаем текстовое поле
    }
    idWindowFocus=(event.GetWindow())->GetId();
}

void EnterProvTo::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    switch(event.GetId())
    {
        case wxID_PR_COMMENT: //команда пришла из поля с комментарием
            {
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //если зажат ctrl+z
                {
                    if(wxTheClipboard->Open()) //открываем буфер обмена
                    {
                        wxTheClipboard->SetData(new wxTextDataObject(((CrossFrm*)(this->GetGrandParent())->GetGrandParent())->fastComment)); //копируем в буфер обмена текст из данных члена прародителя окна
                        if(wxTheClipboard->IsSupported(wxDF_TEXT)) //возвращает верно , если есть данные , которые соответствуют формату данных данных wxDF_TEXT
                        {
                            wxTextDataObject textData; //создаем объект для копирования текста из буфера обмена
                            wxTheClipboard->GetData(textData); //извлекаем текст из буфера обмена в объект-приемник
                            //if((wxWindow::FindFocus())->GetId()==wxID_PR_COMMENT) //проверяем то, что фокус ввода находится в поле для комментария
                            {
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(textData.GetText()); //вставляем в поле с комментарием текст из объекта.
                                wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)this->GetGrandParent())->fastComment); //вставляем текст из данных-члена прародителя в окно с фокусом ввода  
                                ((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + textData.GetText());
                            }
                        }
                    wxTheClipboard->Close();
                    }                  
                }
                event.Skip(true); 
                break;
            }
        default: event.Skip(true);
    }
}
void EnterProvTo::OnButton( wxCommandEvent& event)
{
    if(event.GetId()==wxID_OK)
	{
        wxString idTypeCoop = ((wxTextCtrl*)(this->FindWindow(wxID_PR_TYPE_COOPER)))->GetValue(); //пишем в переменную значение поля
        wxString idTypeProv = ((wxTextCtrl*)(this->FindWindow(wxID_PR_TYPE_PROV)))->GetValue(); //пишем в переменную значение поля
        //wxString idOc = ((wxTextCtrl*)(this->FindWindow(wxID_PR_OC)))->GetValue(); //пишем в переменную значение поля
        //wxString idGc = ((wxTextCtrl*)(this->FindWindow(wxID_PR_GC)))->GetValue(); //пишем в переменную значение поля
        wxString idComment = ((wxTextCtrl*)(this->FindWindow(wxID_PR_COMMENT)))->GetValue(); //пишем в переменную значение поля
        wxString idUk = ((wxTextCtrl*)(this->FindWindow(wxID_PR_UK)))->GetValue(); //пишем в переменную значение поля
        wxString idRezult = ((wxTextCtrl*)(this->FindWindow(wxID_PR_REZULT)))->GetValue(); //пишем в переменную значение поля
        wxString idSotrSb = ((wxTextCtrl*)(this->FindWindow(wxID_PR_SOTR_SB)))->GetValue(); //пишем в переменную значение поля
        wxString idDate = (((wxDatePickerCtrl*)(this->FindWindow(wxID_PR_DATE_PROV)))->GetValue()).FormatISODate(); //пишем в переменную значение поля
        wxString idInitiator;
        if(this->FindWindow(wxID_PR_TC_INITIATOR))//если существует, то пишем в переменню
        {
            idInitiator = ((wxTextCtrl*)(this->FindWindow(wxID_PR_TC_INITIATOR)))->GetValue();
            idInitiator.MakeUpper();
            if(idInitiator.IsEmpty()) {InformationSleep(wxINFO_NOT_INITIATOR,sec_for_sleep_window_info,this); return;}
        } else {idInitiator=wxSQL_DEFAULT;}
        idTypeCoop.MakeUpper(); idTypeProv.MakeUpper(); /*idOc.MakeUpper(); idGc.MakeUpper();*/ idUk.MakeUpper(); idRezult.MakeUpper(); idSotrSb.MakeUpper(); //приводим значения к верхнему регистру
        
        if(idTypeCoop.IsEmpty()) {InformationSleep(wxINFO_NOT_TYPE_PROV,sec_for_sleep_window_info,this); return;}             //если поле  пустое, информируем об этом пользователя и завершаем обработку
        if(idTypeProv.IsEmpty()) {InformationSleep(wxINFO_NOT_TYPE_PROV,sec_for_sleep_window_info,this); return;}             //если поле  пустое, информируем об этом пользователя и завершаем обработку
        if(/*idOc.IsEmpty()*/id_oc==0) {InformationSleep(wxINFO_NOT_OC,sec_for_sleep_window_info,this); return;}             //если поле  пустое, информируем об этом пользователя и завершаем обработку
        if(/*idGc.IsEmpty()*/id_gc==0) {InformationSleep(wxINFO_NOT_GC,sec_for_sleep_window_info,this); return;}             //если поле  пустое, информируем об этом пользователя и завершаем обработку
        //if(idUk.IsEmpty()) {InformationSleep(wxINFO_NOT_PROD_GROUP,sec_for_sleep_window_info,this); return;}             //если поле  пустое, информируем об этом пользователя и завершаем обработку
        if(idRezult.IsEmpty()) {InformationSleep(wxINFO_NOT_RESULT,sec_for_sleep_window_info,this); return;}             //если поле  пустое, информируем об этом пользователя и завершаем обработку
        if(idSotrSb.IsEmpty()) {InformationSleep(wxINFO_NOT_SOTR_SB,sec_for_sleep_window_info,this); return;}             //если поле  пустое, информируем об этом пользователя и завершаем обработку
        if(idDate.IsEmpty()) {InformationSleep(wxINFO_NOT_DATE,sec_for_sleep_window_info,this); return;}             //если поле  пустое, информируем об этом пользователя и завершаем обработку
        
        for(register int i =0; i<MyTypeCooperationArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idTypeCoop.compare(MyTypeCooperationArray.Item(i).nameTypeCooperation))
            //{idTypeCoop=MyTypeCooperationArray.Item(i).idTypeCooperation; break;}      //совпадение найдено
            {idTypeCoop.Clear(); idTypeCoop<<MyTypeCooperationArray.Item(i).idTypeCooperation; break;}      //совпадение найдено
        }
        for(register int i =0; i<MyTypeProvArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idTypeProv.compare(MyTypeProvArray.Item(i).nameTypeProv))
            //{idTypeProv=MyTypeProvArray.Item(i).idTypeProv; break;}      //совпадение найдено
            {idTypeProv.Clear(); idTypeProv<<MyTypeProvArray.Item(i).idTypeProv; break;}      //совпадение найдено
        }
        /*for(register int i =0; i<MyOcArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            //if ((!idOc.compare(MyOcArray.Item(i).nameOc))&&(!MyOcArray.Item(i).activOc.compare("1")))
            //{idOc=MyOcArray.Item(i).idOc; break;}      //совпадение найдено
            if ((!idOc.compare(MyOcArray.Item(i).nameOc))&&(MyOcArray.Item(i).activOc==1))
            {idOc.Clear(); idOc<<MyOcArray.Item(i).idOc; break;}      //совпадение найдено
        }
        for(register int i =0; i<MyGcArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            //if ((!idGc.compare(MyGcArray.Item(i).nameGc))&&(!MyGcArray.Item(i).activGc.compare("1")))
            //{idGc=MyGcArray.Item(i).idGc; break;}      //совпадение найдено
            if ((!idGc.compare(MyGcArray.Item(i).nameGc))&&(MyGcArray.Item(i).activGc==1))
            {idGc.Clear(); idGc<<MyGcArray.Item(i).idGc; break;}      //совпадение найдено
        }*/
        if(idComment.IsEmpty()) {idComment=wxNULL_STRING;}
        if(idUk.IsEmpty()) {idUk=wxUK_DEFAULT;} 
        else
        {
            for(register int i =0; i<MyUkRfArray.GetCount();++i)       //запускаем цикл поиска совпадений 
            {
                if (!idUk.compare(MyUkRfArray.Item(i).nameUkRf))
                //{idUk=MyUkRfArray.Item(i).idUkRf; break;}      //совпадение найдено
                {idUk.Clear(); idUk<<MyUkRfArray.Item(i).idUkRf; break;}      //совпадение найдено
            }
        }
        for(register int i =0; i<MyRezProvArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idRezult.compare(MyRezProvArray.Item(i).nameRezProv))
            //{idRezult=MyRezProvArray.Item(i).idRezProv; break;}      //совпадение найдено
            {idRezult.Clear(); idRezult<<MyRezProvArray.Item(i).idRezProv; break;}      //совпадение найдено
        }
        for(register int i =0; i<MyFioSbArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idSotrSb.compare(MyFioSbArray.Item(i).nameFioSb))
            //{idSotrSb=MyFioSbArray.Item(i).idFioSb; break;}      //совпадение найдено
            {idSotrSb.Clear(); idSotrSb<<MyFioSbArray.Item(i).idFioSb; break;}      //совпадение найдено
        }
        if(idInitiator.compare(wxSQL_DEFAULT)) //не равно значению по-умолчанию
        {
            for(register int i =0; i<MyInitiatorChecksArray.GetCount();++i)       //запускаем цикл поиска совпадений 
            {
                if (!idInitiator.compare(MyInitiatorChecksArray.Item(i).nameInitiatorChecks))
                //{idInitiator=MyInitiatorChecksArray.Item(i).idInitiatorChecks; break;}      //совпадение найдено
                {idInitiator.Clear(); idInitiator<<MyInitiatorChecksArray.Item(i).idInitiatorChecks; break;}      //совпадение найдено
            }
            if(idInitiator.IsNumber()) {;} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        }
        
        
        if(idTypeCoop.IsNumber()&&idTypeProv.IsNumber()&&/*idOc.IsNumber()*/id_oc!=0&&/*idGc.IsNumber()*/id_gc!=0&&idUk.IsNumber()&&idRezult.IsNumber()&&idSotrSb.IsNumber()) {;} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        
        wxString sqlText; 
        if(!type_operation.compare("0")) //добавляем проверку то
        {
            sqlText<<wxSqlTextInsProvTo;
            sqlText<<idUk; sqlText<<wxSqlCommaText;
            sqlText<<idSotrSb; sqlText<<wxSqlCommaText;
            sqlText<<idRezult; sqlText<<wxSqlRightCaw;
            sqlText<<idDate; sqlText<<wxSqlBothCaw;
            sqlText<<idComment; sqlText<<wxSqlLeftCaw;
            sqlText<<id_oc; sqlText<<wxSqlCommaText;
            sqlText<<id_gc; sqlText<<wxSqlCommaText;
            sqlText<<idTypeProv; sqlText<<wxSqlCommaText;
            sqlText<<id_; sqlText<<wxSqlCommaText;
            sqlText<<idTypeCoop; sqlText<<wxSqlCommaText;
            sqlText<<idInitiator; sqlText<<wxSqlEndRightBracketText;
            //wxMessageBox(sqlText,wxATTENTION,wxOK,this);
        }
        if(!type_operation.compare("1")) //обновляем проверку то
        {
            sqlText<<wxSqlTextUpdProvTo;
            sqlText<<idUk; sqlText<<wxSqlTextUpdProvTo_1;
            sqlText<<idSotrSb; sqlText<<wxSqlTextUpdProvTo_2;
            sqlText<<idRezult; sqlText<<wxSqlTextUpdProvTo_3;
            sqlText<<idDate; sqlText<<wxSqlTextUpdProvTo_4;
            sqlText<<idComment; sqlText<<wxSqlTextUpdProvTo_5;
            sqlText<<id_oc; sqlText<<wxSqlTextUpdProvTo_6;
            sqlText<<id_gc; sqlText<<wxSqlTextUpdProvTo_7;
            sqlText<<idTypeProv; sqlText<<wxSqlTextUpdProvTo_8;
            sqlText<<idTypeCoop; sqlText<<wxSqlTextUpdProvTo_9;
            sqlText<<idInitiator; sqlText<<wxSqlTextUpdProvTo_where;
            sqlText<<id_; sqlText<<wxSqlEndText; 
            //wxMessageBox(sqlText,wxATTENTION,wxOK,this);
        }
        //ProvToFrm *parentWindow = (ProvToFrm*)this->GetParent(); //присваиваем переменной указатель на родительское окно
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} else {;}
        this->EndModal(wxID_OK);
    }
    if(event.GetId()==wxID_CANCEL)
	{
        this->EndModal(wxID_CANCEL);
    }
}

EnterProvTo::~EnterProvTo()
{
}

/*
Dialog - EnterProvTo - end
*/

/*
Dialog - ListFindFio - start
*/
BEGIN_EVENT_TABLE(ListFindFio,wxDialog)
    EVT_CHAR_HOOK(ListFindFio::OnChar)
END_EVENT_TABLE()

ListFindFio::ListFindFio(wxWindow *parent, wxWindowID id, const wxString &caption, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    wxStaticBox *stBox = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_LIST_COMPARE);
    wxStaticBoxSizer *to_static_box = new wxStaticBoxSizer(stBox,wxVERTICAL);
    wxListView *listview = new wxListView(this, wxID_LISTVIEW_LISTFIO, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL);
    listview->InsertColumn(0,wxCAPTION_COLUMN_FIO);
    listview->InsertColumn(1,wxCAPTION_COLUMN_PASP_SER);
    listview->InsertColumn(2,wxCAPTION_COLUMN_PASP_NUM);
    listview->InsertColumn(3,wxCAPTION_COLUMN_DATE_ROJD);
    to_static_box->Add(listview, 1, wxEXPAND,0);
    for (register int i = 0; i < listFio.count; i++) // Вывод таблицы
    {
        wxListItem *f = new wxListItem();
        f->SetState(wxLIST_STATE_FOCUSED);
        f->SetMask(wxLIST_MASK_TEXT);
        f->SetColumn(0);
        f->SetData(wxAtoi(listFio.idReestrFio.Item(i))); //прячем уникальный айди
        f->SetId(i);
        listview->InsertItem(*f); 
        listview->SetItem(i,0,listFio.fio.Item(i));
        listview->SetItem(i,1,listFio.seriy_pasp.Item(i));
        listview->SetItem(i,2,listFio.number_pasp.Item(i));
        listview->SetItem(i,3,listFio.dr.Item(i));
        delete f;
    }
    for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
    this->SetSizer(to_static_box); 
    this->SetAffirmativeId(wxID_OK);
    this->SetEscapeId(wxID_CANCEL);
    /*Включаем акселераторы*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*конец с акселераторами*/
}

void ListFindFio::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    if(event.GetKeyCode()==13) //нажата кнопка Enter
    {
        wxString sqlText, sqlIdFl; 
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_LISTFIO)); //получаем указатель на листвьюев
        EnterProvSotrTo *parentWindow = (EnterProvSotrTo*)this->GetParent(); //присваиваем переменной указатель на родительское окно
        int idItem = (int)listview->GetFirstSelected();
        if (idItem==-1) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} 
        wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
        f->SetId(idItem); //устанавливаем позицию выбранного элемента
        f->SetColumn(0); //колонка с фио
        f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT); //возвращаем данные связанные с элементом
        listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
        ((wxTextCtrl*)parentWindow->FindWindow(wxID_PR_FZ_FIO))->ChangeValue(f->GetText());
        (parentWindow->id_fio).Clear(); 
        (parentWindow->id_fio)<<f->GetData(); //пишем в переменную данные связанные с элементом
        sqlIdFl<<f->GetData();
        f->SetColumn(1); //колонка с серией паспорта
        listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
        ((wxTextCtrl*)parentWindow->FindWindow(wxID_PR_FZ_SERIY))->ChangeValue(f->GetText());
        f->SetColumn(2); //колонка с номером паспорта
        listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
        ((wxTextCtrl*)parentWindow->FindWindow(wxID_PR_FZ_NOMER))->ChangeValue(f->GetText());
        f->SetColumn(3); //колонка с номером паспорта
        listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
        wxString strDate = f->GetText();
        insertStrDateToCtrl (strDate, (wxDatePickerCtrl*)parentWindow->FindWindow(wxID_PR_FZ_DR));
        /*wxDateTime dt;
        wxString::const_iterator end;
        dt.ParseDate(f->GetText(), &end);
        ((wxDatePickerCtrl*)parentWindow->FindWindow(wxID_PR_FZ_DR))->SetValue(dt);
        */
        delete f;
        
        /*
        Обновляем дату рождения в записи таблицы БД.
        */
        sqlText<<wxSqlTextUpdFzStart1;
        sqlText<<strDate; sqlText<<wxSqlCharStr; sqlText<<wxSqlTextUpdFz4;
        sqlText<<sqlIdFl; sqlText<<wxSqlEndText; 
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} else {;}
        
        this->EndModal(wxID_OK);
        event.Skip(false);
    }
    if(event.GetKeyCode()==WXK_ESCAPE) //нажата кнопка Esc
    {
        this->EndModal(wxID_CANCEL);
        event.Skip(false);
    }    
        else {event.Skip(true);}
}
ListFindFio::~ListFindFio()
{
}

/*
Dialog - ListFindFio - end
*/

/*
Dialog - InsUpdHolidaySotrDialog - start
*/
BEGIN_EVENT_TABLE(InsUpdHolidaySotrDialog,wxDialog)
    EVT_BUTTON (wxID_OK, InsUpdHolidaySotrDialog::OnButton)
    EVT_BUTTON (wxID_CANCEL, InsUpdHolidaySotrDialog::OnButton)
END_EVENT_TABLE()

InsUpdHolidaySotrDialog::InsUpdHolidaySotrDialog(wxWindow *parent, int id_operation, const wxString &caption, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    wxListView *listveiwFio = (wxListView*)parent->FindWindow(wxID_HOLFRM_LISTVIEW_S_SOTR);
    wxListView *listveiwHoliday = (wxListView*)parent->FindWindow(wxID_HOLFRM_LISTVIEW_S_OTP);
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr7 = new wxBoxSizer(wxHORIZONTAL);
    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_STATICTEXT_EVENT "*"), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr1->Add(new wxTextCtrl(this,wxID_DIALOG_HOLSOTR_TEXT_1, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_STATICTEXT_DATE_START "*"), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr2->Add(new wxDatePickerCtrl(this,wxID_DIALOG_HOLSOTR_DATE_1,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_STATICTEXT_DATE_END), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr3->Add(new wxDatePickerCtrl(this,wxID_DIALOG_HOLSOTR_DATE_2,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr4->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_STATICTEXT_ZAMKAND), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr5->Add(new wxTextCtrl(this,wxID_DIALOG_HOLSOTR_TEXT_2, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_STATICTEXT_ZAMTO), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr7->Add(new wxTextCtrl(this,wxID_DIALOG_HOLSOTR_TEXT_3, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    vert_bos->Add(hr1, 0, wxEXPAND,0);
    vert_bos->Add(hr2, 0, wxEXPAND,0);
    vert_bos->Add(hr3, 0, wxEXPAND,0);
    vert_bos->Add(hr4, 0, wxEXPAND,0);
    vert_bos->Add(hr5, 0, wxEXPAND,0);
    vert_bos->Add(hr6, 0, wxEXPAND,0);
    vert_bos->Add(hr7, 0, wxEXPAND,0);
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0); //используя метод wxDialog создаем классификатор со стандартными кнопками, отделенными от остальной части полосой
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    id_opera=id_operation;
    if(id_opera==1) {this->SetTitle(wxCAPTION_HOLSOV1);}
    if(id_opera==2) {this->SetTitle(wxCAPTION_HOLSOV2);}
    wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
    LocArray.Alloc(MyHolidayTypeArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int j =0; j<MyHolidayTypeArray.GetCount();++j)   //заполняем локальный массив
    {
        LocArray.Add(MyHolidayTypeArray.Item(j).nameHolidayType);
    }
    ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_1))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(listveiwFio->GetItemCount());  //Резервирует достаточно памяти для хранения nCount предметов
    for(register int j =0; j<listveiwFio->GetItemCount();++j)   //заполняем локальный массив
    {
        LocArray.Add(listveiwFio->GetItemText(j));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_2))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_3))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    if(id_opera==2)
    {
        int select_item = listveiwHoliday->GetFirstSelected();
        ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_1))->ChangeValue(listveiwHoliday->GetItemText(select_item,1));
        wxString str;
        str = listveiwHoliday->GetItemText(select_item,2);
        insertStrDateToCtrl (str, (wxDatePickerCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_DATE_1));
        str = listveiwHoliday->GetItemText(select_item,3);
        insertStrDateToCtrl (str, (wxDatePickerCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_DATE_2));
        ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_2))->ChangeValue(listveiwHoliday->GetItemText(select_item,4));
        ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_3))->ChangeValue(listveiwHoliday->GetItemText(select_item,5));
    }
}
void InsUpdHolidaySotrDialog::OnButton( wxCommandEvent& event)
{
    if(event.GetId()==wxID_OK)
	{
        wxString strEvent, strDateOn, strDateOff, strZamKand, strZamTo;
        int idReestrString=0, idEvent=0, idZamKand=0, idZamTo=0, idSotr=0, select_item=0;
        HolidayFrm *parent = (HolidayFrm*)this->GetParent();
        wxListView *listveiwFio = (wxListView*)parent->FindWindow(wxID_HOLFRM_LISTVIEW_S_SOTR);
        wxListView *listveiwHoliday = (wxListView*)parent->FindWindow(wxID_HOLFRM_LISTVIEW_S_OTP);
        if(id_opera==2)
        {
            select_item = listveiwHoliday->GetFirstSelected();
            idReestrString = (int)listveiwHoliday->GetItemData(select_item);
        }
        select_item = listveiwFio->GetFirstSelected();
        idSotr=(int)listveiwFio->GetItemData(select_item);
        if(idSotr>0)
        {
            strEvent=((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_1))->GetValue();
            if((((wxDatePickerCtrl*)(this->FindWindow(wxID_DIALOG_HOLSOTR_DATE_1)))->GetValue()).IsValid())
            {
                strDateOn = (((wxDatePickerCtrl*)(this->FindWindow(wxID_DIALOG_HOLSOTR_DATE_1)))->GetValue()).FormatISODate();
            }
            if((((wxDatePickerCtrl*)(this->FindWindow(wxID_DIALOG_HOLSOTR_DATE_2)))->GetValue()).IsValid())
            {
                strDateOff = (((wxDatePickerCtrl*)(this->FindWindow(wxID_DIALOG_HOLSOTR_DATE_2)))->GetValue()).FormatISODate();
            }
            strZamKand=((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_2))->GetValue();
            strZamTo=((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_3))->GetValue();
            strEvent.MakeUpper();
            for(register int i =0; i<MyHolidayTypeArray.GetCount();++i)       //запускаем цикл поиска совпадений 
            {
                if (!strEvent.compare(MyHolidayTypeArray.Item(i).nameHolidayType))
                //{idEvent=wxAtoi(MyHolidayTypeArray.Item(i).idHolidayType); break;}      //совпадение найдено
                {idEvent=MyHolidayTypeArray.Item(i).idHolidayType; break;}      //совпадение найдено
            }
            if(idEvent==0) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
            if(!strZamKand.IsEmpty())
            {
                strZamKand.MakeUpper();
                for(register int i =0; i<MySovetnicArray.GetCount();++i)       //запускаем цикл поиска совпадений 
                {
                    if (!strZamKand.compare(MySovetnicArray.Item(i).nameSovetnic)&&MySovetnicArray.Item(i).activSovetnic==1)
                    //{idZamKand=wxAtoi(MySovetnicArray.Item(i).idSovetnic); break;}      //совпадение найдено
                    {idZamKand=MySovetnicArray.Item(i).idSovetnic; break;}      //совпадение найдено
                }
                if(idZamKand==0) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
            }
            if(!strZamTo.IsEmpty())
            {
                strZamTo.MakeUpper();
                for(register int i =0; i<MySovetnicArray.GetCount();++i)       //запускаем цикл поиска совпадений 
                {
                    if (!strZamTo.compare(MySovetnicArray.Item(i).nameSovetnic)&&MySovetnicArray.Item(i).activSovetnic==1)
                    //{idZamTo=wxAtoi(MySovetnicArray.Item(i).idSovetnic); break;}      //совпадение найден
                    {idZamTo=MySovetnicArray.Item(i).idSovetnic; break;}      //совпадение найдено
                }
                if(idZamTo==0) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
            }
            wxString sqlText;
            if(id_opera==1)
            {
                sqlText<<wxSqlTextInsOtpFrm;
                sqlText<<idSotr; sqlText<<wxSqlCommaText;  
                sqlText<<wxSqlCharStr; sqlText<<strDateOn; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;
                if(strDateOff.IsEmpty()) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<wxSqlCharStr; sqlText<<strDateOff; sqlText<<wxSqlCharStr;}
                sqlText<<wxSqlCommaText; sqlText<<idEvent; sqlText<<wxSqlCommaText;
                if(idZamKand==0) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<idZamKand;} 
                sqlText<<wxSqlCommaText;
                if(idZamTo==0) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<idZamTo;}
                sqlText<<wxSqlEndRightBracketText;
            }
            if(id_opera==2)
            {
                sqlText<<wxSqlTextUpdOtpFrm;
                sqlText<<wxSqlCharStr; sqlText<<strDateOn; sqlText<<wxSqlCharStr; sqlText<<wxSqlTextUpdOtpFrm1;
                if(strDateOff.IsEmpty()) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<wxSqlCharStr; sqlText<<strDateOff; sqlText<<wxSqlCharStr;}
                sqlText<<wxSqlTextUpdOtpFrm2; sqlText<<idEvent; sqlText<<wxSqlTextUpdOtpFrm3;
                if(idZamKand==0) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<idZamKand;} 
                sqlText<<wxSqlTextUpdOtpFrm4;
                if(idZamTo==0) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<idZamTo;}
                sqlText<<wxSqlTextUpdOtpFrm5; sqlText<<idReestrString; sqlText<<wxSqlEndText; 
            }
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
            else {;}
            this->EndModal(wxID_OK);
        }
    }
    if(event.GetId()==wxID_CANCEL)
	{
        this->EndModal(wxID_CANCEL);
    }
}
InsUpdHolidaySotrDialog::~InsUpdHolidaySotrDialog()
{
}
/*
Dialog - InsUpdHolidaySotrDialog - end
*/

/*
Dialog - EnterProvSotrTo - start
*/

BEGIN_EVENT_TABLE(EnterProvSotrTo,wxDialog)
    EVT_BUTTON (wxID_OK, EnterProvSotrTo::OnButton)
    EVT_BUTTON (wxID_CANCEL, EnterProvSotrTo::OnButton)
    EVT_CHAR_HOOK(EnterProvSotrTo::OnChar)
    EVT_CHILD_FOCUS(EnterProvSotrTo::NewFocus)
END_EVENT_TABLE()

EnterProvSotrTo::EnterProvSotrTo(wxWindow *parent, int id1, int type, wxWindowID id, const wxString &caption, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr8 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr9 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBox *stBox1 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_PASSPORT);
    wxStaticBoxSizer *to_static_box1 = new wxStaticBoxSizer(stBox1,wxHORIZONTAL);
    
    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_FIO "*"), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    
    hr1->Add(new wxTextCtrl(this,wxID_PR_FZ_FIO, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    to_static_box1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PASP_SER), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    to_static_box1->Add(new wxTextCtrl(this,wxID_PR_FZ_SERIY, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    to_static_box1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PASP_NUM), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    to_static_box1->Add(new wxTextCtrl(this,wxID_PR_FZ_NOMER, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_DATE_ROJD), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr2->Add(new wxDatePickerCtrl(this,wxID_PR_FZ_DR,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE));
    
    /*
    if(type==0)
        {hr1->Add(new wxTextCtrl(this,wxID_PR_FZ_FIO, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);}
    else {hr1->Add(new wxTextCtrl(this,wxID_PR_FZ_FIO, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE|wxTE_READONLY ), 1, wxEXPAND|wxLEFT|wxRIGHT,0);}
    to_static_box1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PASP_SER), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    if(type==0)
        {to_static_box1->Add(new wxTextCtrl(this,wxID_PR_FZ_SERIY, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);}
    else {to_static_box1->Add(new wxTextCtrl(this,wxID_PR_FZ_SERIY, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE|wxTE_READONLY), 1, wxEXPAND|wxLEFT|wxRIGHT,0);}
    to_static_box1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PASP_NUM), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    if(type==0)
        {to_static_box1->Add(new wxTextCtrl(this,wxID_PR_FZ_NOMER, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);}
    else {to_static_box1->Add(new wxTextCtrl(this,wxID_PR_FZ_NOMER, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE|wxTE_READONLY), 1, wxEXPAND|wxLEFT|wxRIGHT,0);}
    
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_DATE_ROJD), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    if(type==0)
        {hr2->Add(new wxDatePickerCtrl(this,wxID_PR_FZ_DR,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE));} 
    else {hr2->Add(new wxDatePickerCtrl(this,wxID_PR_FZ_DR,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE)); ((wxDatePickerCtrl*)this->FindWindow(wxID_PR_FZ_DR))->Enable(false);} //вручную запрещаем пользователю ввод данных в поле с датой
    */    
    hr3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_GC), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr3->Add(new wxTextCtrl(this,wxID_PR_FZ_GC, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr4->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_JOB "*"), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr4->Add(new wxTextCtrl(this,wxID_PR_FZ_DOLZ, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr5->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_UK), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr5->Add(new wxTextCtrl(this,wxID_PR_FZ_UK, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_COMENT), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr6->Add(new wxTextCtrl(this,wxID_PR_FZ_COMMENT, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr7->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_REZ "*"), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr7->Add(new wxTextCtrl(this,wxID_PR_FZ_REZULT, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr8->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_SOTRSB "*"), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr8->Add(new wxTextCtrl(this,wxID_PR_FZ_SOTR_SB, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr9->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_DATE "*"), 0, wxEXPAND|wxLEFT|wxRIGHT ,5);
    hr9->Add(new wxDatePickerCtrl(this,wxID_PR_FZ_DATE_PROV,  wxDefaultDateTime, wxDefaultPosition, wxDefaultSize,wxDP_DEFAULT), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    if(type==0)
        {hr9->Add(new wxCheckBox(this,wxID_PR_FZ_COMPARE,wxCAPTION_CHECKBOX_PROV_COMPARE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);}
    else {hr9->Add(new wxCheckBox(this,wxID_PR_FZ_COMPARE,wxCAPTION_CHECKBOX_FLAG_ARCHIVE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);}
    vert_bos->Add(hr1, 0, wxEXPAND,0);
    vert_bos->Add(to_static_box1, 0, wxEXPAND,0);
    vert_bos->Add(hr2, 0, wxEXPAND,0);
    vert_bos->Add(hr3, 0, wxEXPAND,0);
    vert_bos->Add(hr4, 0, wxEXPAND,0);
    vert_bos->Add(hr5, 0, wxEXPAND,0);
    vert_bos->Add(hr6, 0, wxEXPAND,0);
    vert_bos->Add(hr7, 0, wxEXPAND,0);
    vert_bos->Add(hr8, 0, wxEXPAND,0);
    vert_bos->Add(hr9, 0, wxEXPAND,0);
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0); //используя метод wxDialog создаем классификатор со стандартными кнопками, отделенных от остальной части полосой
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    
    wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
    LocArray.Alloc(MyGcArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int j =0; j<MyGcArray.GetCount();++j)   //заполняем локальный массив
    {
        //if(!MyGcArray.Item(j).activGc.compare("1")) {LocArray.Add(MyGcArray.Item(j).nameGc);}
        if(MyGcArray.Item(j).activGc==1) {LocArray.Add(MyGcArray.Item(j).nameGc);}
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_GC))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(MyDolznostArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyDolznostArray.GetCount();++i) //заполняем локальный массив 
    {
        LocArray.Add((MyDolznostArray.Item(i).nameDolznost));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_DOLZ))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(MyUkRfArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyUkRfArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyUkRfArray.Item(i).nameUkRf));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_UK))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(MyRezProvArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyRezProvArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyRezProvArray.Item(i).nameRezProv));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_REZULT))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(MyFioSbArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов
    for(register int i =0; i<MyFioSbArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyFioSbArray.Item(i).nameFioSb));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SOTR_SB))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SERIY))->SetMaxLength(4); //устанавливаем ограничение на количество вводимых символов в поле с серией паспорта   
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_NOMER))->SetMaxLength(6); //устанавливаем ограничение на количество вводимых символов в поле с номером паспорта
    ((wxCheckBox*)this->FindWindow(wxID_PR_FZ_COMPARE))->SetValue(true); //ставим галочку в чекбоксе
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_FIO))->SetFocus(); //устанавливаем фокус ввода на поле с ФИО
    SetAffirmativeId(wxID_OK);      //Задаем идентификатор для использования в качестве кнопки ОК
    id_<<id1;                       //id то (если добавляем новую проверку) или записи в реестре проверок физиков(если обновляем старую проверку)
    type_operation<<type;           //присваиваем переменной признак операции: добавить (0), обновить (1)
    /*Включаем акселераторы*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*конец с акселераторами*/
    if(type==1)
    {
        wxString sqlText; sqlText<<wxSqlTextSotrToOne;
        sqlText<<id_; sqlText<<wxSqlEndText;
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
                    for (register int l = 0; l < num_fields; l++)
                    {
                        if (l==0) { ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_FIO))->ChangeValue(row[0]); }
                        if (l==1) 
                        { 
                            wxString str=row[1]; //пишем дату из результата выборки запроса в переменную
                            insertStrDateToCtrl (str, (wxDatePickerCtrl*)this->FindWindow(wxID_PR_FZ_DR));
                        }
                        if (l==2) 
                        {
                            for(register int k =0; k<MyDolznostArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(atoi(MyDolznostArray.Item(k).idDolznost.c_str())==atoi(row[l])) //совпадение найдено
                                if(MyDolznostArray.Item(k).idDolznost==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_DOLZ))->ChangeValue(MyDolznostArray.Item(k).nameDolznost);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==3) 
                        { 
                            ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SERIY))->ChangeValue(row[4]); 
                            ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_NOMER))->ChangeValue(row[3]); 
                        }
                        if (l==5) 
                        {
                            for(register int k =0; k<MyGcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //совпадение найдено
                                if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //совпадение найдено
                                {   
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_GC))->ChangeValue(MyGcArray.Item(k).nameGc);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==6)  {((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_COMMENT))->ChangeValue(row[l]);}
                        if (l==7) 
                        {
                            for(register int k =0; k<MyUkRfArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //совпадение найдено
                                if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_UK))->ChangeValue(MyUkRfArray.Item(k).nameUkRf);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==8) 
                        {
                            for(register int k =0; k<MyRezProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //совпадение найдено
                                if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_REZULT))->ChangeValue(MyRezProvArray.Item(k).nameRezProv);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==9) 
                        {
                            for(register int k =0; k<MyFioSbArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //совпадение найдено
                                if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //совпадение найдено
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SOTR_SB))->ChangeValue(MyFioSbArray.Item(k).nameFioSb);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                        if (l==10) 
                        {
                            wxString str=row[l]; //пишем дату из результата выборки запроса в переменную
                            insertStrDateToCtrl (str, (wxDatePickerCtrl*)this->FindWindow(wxID_PR_FZ_DATE_PROV));
                        }
                        if (l==11) 
                        {
                            if (atoi(row[l])==1) {((wxCheckBox*)this->FindWindow(wxID_PR_FZ_COMPARE))->SetValue(false);}
                            if (atoi(row[l])==0) {((wxCheckBox*)this->FindWindow(wxID_PR_FZ_COMPARE))->SetValue(true);}
                        }
                        if (l==12) 
                        {
                            id_fio=row[l];
                        }
                    }
                }
            }
            mysql_free_result(res); // Очищаем результаты
        }
    } 
}

void EnterProvSotrTo::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    switch(event.GetId())
    {
        case wxID_PR_FZ_SERIY: //запрещаем в поле с ИНН вводить символы отличные от цифр
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //если зажат шифт, контрл или альт, то отправляем событие вверх к родителю
                {event.Skip(true);} 
                else {
                    if((event.GetKeyCode()>=32&&event.GetKeyCode()<=47)||(event.GetKeyCode()>=58&&event.GetKeyCode()<=255)) //если нажатая кнопка попала в диапазоны, то не пропускаем событие вверх к родителю
                        {event.Skip(false);}
                    else {event.Skip(true);}
                }
                break;
            }
        case wxID_PR_FZ_NOMER: //запрещаем в поле с ТТ вводить символы отличные от цифр
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //если зажат шифт, контрл или альт, то отправляем событие вверх к родителю
                {event.Skip(true);} 
                else {
                    if((event.GetKeyCode()>=32&&event.GetKeyCode()<=47)||(event.GetKeyCode()>=58&&event.GetKeyCode()<=255)) //если нажатая кнопка попала в диапазоны, то не пропускаем событие вверх к родителю
                        {event.Skip(false);}
                    else {event.Skip(true);}
                }
                break;
            }
        case wxID_PR_FZ_COMMENT: //команда пришла из поля с комментарием
            /*{
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //если зажат ctrl+z
                {
                    wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                    ((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)this->GetGrandParent())->fastComment); //вставляем текст из данных-члена прародителя в окно с фокусом ввода          
                }
                event.Skip(true); 
                break;
            }*/
            {
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //если зажат ctrl+z
                {
                    if(wxTheClipboard->Open()) //открываем буфер обмена
                    {
                        wxTheClipboard->SetData(new wxTextDataObject(((CrossFrm*)(this->GetGrandParent())->GetGrandParent())->fastComment)); //копируем в буфер обмена текст из данных члена прародителя окна
                        if(wxTheClipboard->IsSupported(wxDF_TEXT)) //возвращает верно , если есть данные , которые соответствуют формату данных данных wxDF_TEXT
                        {
                            wxTextDataObject textData; //создаем объект для копирования текста из буфера обмена
                            wxTheClipboard->GetData(textData); //извлекаем текст из буфера обмена в объект-приемник
                            //if((wxWindow::FindFocus())->GetId()==wxID_PR_COMMENT) //проверяем то, что фокус ввода находится в поле для комментария
                            {
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(textData.GetText()); //вставляем в поле с комментарием текст из объекта.
                                wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)this->GetGrandParent())->fastComment); //вставляем текст из данных-члена прародителя в окно с фокусом ввода  
                                ((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + textData.GetText());
                            }
                        }
                    wxTheClipboard->Close();
                    }                  
                }
                event.Skip(true); 
                break;
            }
        default: event.Skip(true);
    }
}

void EnterProvSotrTo::NewFocus(wxChildFocusEvent& event)
{
    if(idWindowFocus==wxID_PR_FZ_FIO)
    {
        if(((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_COMMENT))->IsEmpty())
        {
            if(((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_COMMENT))->IsEmpty())
            {
                wxString strFio = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_FIO))->GetValue();
                EditStringFio(strFio);
                ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_COMMENT))->ChangeValue(strFio);
            }
        }
    }
    idWindowFocus=(event.GetWindow())->GetId();
}

void EnterProvSotrTo::OnButton( wxCommandEvent& event)
{
    if(event.GetId()==wxID_OK)
	{
        wxString fio, seriy, number, strDr, idGc, idDolz, idUk, idComment, idRez, idSotr, idDate, idArchive;
        int flag_sboy=0, flag_seriy=0, flag_number=0;
        fio = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_FIO))->GetValue(); //вынес переменную за условие if, т.к. в противном случае переменная пустая и при проверке по ЧС СБ вытягиваются все записи
        if(!type_operation.compare("0")||!type_operation.compare("1"))                                                 //если тип операции - добавление, то обрабатываем поля с фио/поспорт.
        {
        seriy = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SERIY))->GetValue();
        number = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_NOMER))->GetValue();
        fio.Trim(true); fio.Trim(false); seriy.Trim(true); seriy.Trim(false); number.Trim(true); number.Trim(false); //удаляем пробелы
        if (fio.IsEmpty()) {InformationSleep(wxINFO_NOT_FIO_SOTR,sec_for_sleep_window_info,this); return;}
        switch(seriy.Len())
        {
            case 0:
            {
                seriy<<wxNULL_;
                flag_seriy=1; //признак того, что физик без серии паспорта
                break;
            }
            case 1:
            case 2:
            case 3:
            {
                flag_sboy=1;
                break;
            }
            default: break;
        }
        switch(number.Len())
        {
            case 0:
            {
                number<<wxNULL_;
                flag_number=1; //признак того, что физик без номера паспорта
                break;
            }
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            {
                flag_sboy=1;
                break;
            }
            default: break;
        }
        if(flag_sboy==1||(flag_seriy==0&&flag_number==1)||(flag_seriy==1&&flag_number==0)) {InformationSleep(wxINFO_WRONG_PASPORT,sec_for_sleep_window_info,this); return;}
        }
        if(((CrossFrm*)(this->GetGrandParent()))->flag_bl_sb) {if(proverka_bl_sb(conn, fio, 1)==1) {;} else {return;}} //проверка по ЧС СБ
        if((((wxDatePickerCtrl*)(this->FindWindow(wxID_PR_FZ_DR)))->GetValue()).IsValid())
        {strDr = (((wxDatePickerCtrl*)(this->FindWindow(wxID_PR_FZ_DR)))->GetValue()).FormatISODate();}
        idGc = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_GC))->GetValue();
        idDolz = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_DOLZ))->GetValue();
        idUk = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_UK))->GetValue();
        idComment = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_COMMENT))->GetValue();
        idRez = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_REZULT))->GetValue();
        idSotr = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SOTR_SB))->GetValue();
        idDate = (((wxDatePickerCtrl*)(this->FindWindow(wxID_PR_FZ_DATE_PROV)))->GetValue()).FormatISODate(); //пишем в переменную значение поля
        fio.MakeUpper(); idGc.MakeUpper(); idDolz.MakeUpper(); idUk.MakeUpper(); idRez.MakeUpper(); idSotr.MakeUpper();
        
        if(strDr.IsEmpty()) {strDr=wxSQL_DEFAULT;} 
        if(idDolz.IsEmpty()||idRez.IsEmpty()||idSotr.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}
        if(idComment.IsEmpty()) {idComment=wxNULL_STRING;}        
        if(idGc.IsEmpty()||(!idGc.compare(wxNOT_DATA))) {idGc=wxNULL_;} 
        else
        {
            for(register int i =0; i<MyGcArray.GetCount();++i)       //запускаем цикл поиска совпадений 
            {
                //if (!idGc.compare(MyGcArray.Item(i).nameGc)&&(!MyGcArray.Item(i).activGc.compare("1")))
                //{idGc=MyGcArray.Item(i).idGc; break;}      //совпадение найдено
                if (!idGc.compare(MyGcArray.Item(i).nameGc)&&(MyGcArray.Item(i).activGc==1))
                {idGc.Clear(); idGc<<MyGcArray.Item(i).idGc; break;}      //совпадение найдено
            }
        }
        for(register int i =0; i<MyDolznostArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idDolz.compare(MyDolznostArray.Item(i).nameDolznost))
            //{idDolz=MyDolznostArray.Item(i).idDolznost; break;}      //совпадение найдено
            {idDolz.Clear(); idDolz<<MyDolznostArray.Item(i).idDolznost; break;}      //совпадение найдено
        }
        if(idUk.IsEmpty()) {idUk=wxUK_DEFAULT;}
        else
        {
            for(register int i =0; i<MyUkRfArray.GetCount();++i)       //запускаем цикл поиска совпадений 
            {
                if (!idUk.compare(MyUkRfArray.Item(i).nameUkRf))
                //{idUk=MyUkRfArray.Item(i).idUkRf; break;}      //совпадение найдено
                {idUk.Clear(); idUk<<MyUkRfArray.Item(i).idUkRf; break;}      //совпадение найдено
            }
        }
        for(register int i =0; i<MyRezProvArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idRez.compare(MyRezProvArray.Item(i).nameRezProv))
            //{idRez=MyRezProvArray.Item(i).idRezProv; break;}      //совпадение найдено
            {idRez.Clear(); idRez<<MyRezProvArray.Item(i).idRezProv; break;}      //совпадение найдено
        }
        for(register int i =0; i<MyFioSbArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idSotr.compare(MyFioSbArray.Item(i).nameFioSb))
            //{idSotr=MyFioSbArray.Item(i).idFioSb; break;}      //совпадение найдено
            {idSotr.Clear(); idSotr<<MyFioSbArray.Item(i).idFioSb; break;}      //совпадение найдено
        }
        if(!type_operation.compare("1"))
        {
            if(((wxCheckBox*)this->FindWindow(wxID_PR_FZ_COMPARE))->GetValue())
            { idArchive="0"; } else { idArchive="1"; }
        }
        if(idDolz.IsNumber()||idUk.IsNumber()||idRez.IsNumber()||idSotr.IsNumber()) {} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        if (!type_operation.compare("0")||!type_operation.compare("1"))
        {
        /*
                Чекбокс. Если галка стоит, то проверяем наличие совпадения по паспорту или фио (без паспорта) в реестре физлиц.
                Если совпадения есть - выводим диалоговую панель с возможностью выбора интересующего физика.
                Если галка не стоит, то без проверки пишем в реестр физиков новую запись -> возможны дубли паспортов
        */
        if(((wxCheckBox*)this->FindWindow(wxID_PR_FZ_COMPARE))->GetValue())
        {
            wxString sqlText;
            if (flag_seriy==1 && flag_number==1) //строим sql запрос БЕЗ паспортных данных
            {
                sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd;
            }
            if (flag_seriy==0 && flag_number==0) //строим sql запрос С паспортными данными
            {
                sqlText<<wxSqlTextSelComparePaspProvSotrToStart;
                sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                sqlText<<number; sqlText<<wxSqlEndText;
            }
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            {
                listFio.Clear();
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                int num_rows = mysql_num_rows(res); // и количество строк.
                if(num_rows>0)
                {   
                    MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                    for(;row;row = mysql_fetch_row(res))
                    {
                        listFio.idReestrFio.Add(row[0]);
                        listFio.fio.Add(row[1]);
                        listFio.seriy_pasp.Add(row[2]);
                        listFio.number_pasp.Add(row[3]);
                        if(strDr==wxSQL_DEFAULT) {listFio.dr.Add(row[4]);} else {listFio.dr.Add(strDr);}
                        listFio.count+=1;
                    }
                    ListFindFio DialogListFio (this);  
                    if(DialogListFio.ShowModal() == wxID_CANCEL) {mysql_free_result(res); return;} else {;}
                    mysql_free_result(res); // Очищаем результаты
                }
                else 
                {
                    mysql_free_result(res); // Очищаем результаты
                    sqlText.Clear(); //очищаем переменную от предыдущего sql запроса
                    if (!type_operation.compare("0"))
                    {
                    sqlText<<wxSqlTextInsFioAndPasp;
                    sqlText<<fio; sqlText<<wxSqlLeftCaw;
                    sqlText<<seriy; sqlText<<wxSqlCommaText;
                    sqlText<<number; sqlText<<wxSqlCommaText;
                    if(!strDr.compare(wxSQL_DEFAULT)) {sqlText<<strDr;}
                    else {sqlText<<wxSqlCharStr; sqlText<<strDr; sqlText<<wxSqlCharStr;}
                    sqlText<<wxSqlEndRightBracketText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                    {
                        sqlText.Clear(); //очищаем переменную от предыдущего sql запроса
                        if (flag_seriy==1 && flag_number==1) //строим sql запрос БЕЗ паспортных данных
                        {
                            sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                            sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd1;
                        }
                        if (flag_seriy==0 && flag_number==0) //строим sql запрос С паспортными данными
                        {
                            sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                            sqlText<<fio; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd1;
                            sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                            sqlText<<number; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd2;
                        }
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                        {
                            res = mysql_store_result(conn); // Берем результат,
                            num_rows = mysql_num_rows(res); // и количество строк.
                            if(num_rows>0) // запрос выполнен, обработка возвращенных им данных
                            {
                                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                                id_fio=row[0]; 
                            }
                            mysql_free_result(res); // Очищаем результаты
                        }
                    }
                    }
                    if (!type_operation.compare("1")) 
                    {
                        sqlText<<wxSqlTextUpdFzStart;
                        sqlText<<fio; sqlText<<wxSqlTextUpdFz1;
                        sqlText<<seriy; sqlText<<wxSqlTextUpdFz2;
                        sqlText<<number; sqlText<<wxSqlTextUpdFz3;
                        if(!strDr.compare(wxSQL_DEFAULT)) {sqlText<<strDr;}
                        else {sqlText<<wxSqlCharStr; sqlText<<strDr; sqlText<<wxSqlCharStr;}
                        sqlText<<wxSqlTextUpdFz4; sqlText<<id_fio; sqlText<<wxSqlEndText;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                        {}
                    } 
                }
            }
        }
        else
        {
            if (!type_operation.compare("0"))
            {
            wxString sqlText;
            sqlText<<wxSqlTextInsFioAndPasp;
            sqlText<<fio; sqlText<<wxSqlLeftCaw;
            sqlText<<seriy; sqlText<<wxSqlCommaText;
            sqlText<<number; sqlText<<wxSqlCommaText;
            if(!strDr.compare(wxSQL_DEFAULT)) {sqlText<<strDr;}
            else {sqlText<<wxSqlCharStr; sqlText<<strDr; sqlText<<wxSqlCharStr;}
            sqlText<<wxSqlEndRightBracketText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            {
                sqlText.Clear(); //очищаем переменную от предыдущего sql запроса
                if (flag_seriy==1 && flag_number==1) //строим sql запрос БЕЗ паспортных данных
                {
                    sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                    sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd1;
                }
                if (flag_seriy==0 && flag_number==0) //строим sql запрос С паспортными данными
                {
                    sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                    sqlText<<fio; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd1;
                    sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                    sqlText<<number; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd2;
                }
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0) // запрос выполнен, обработка возвращенных им данных
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        id_fio=row[0]; 
                    }
                    mysql_free_result(res); // Очищаем результаты
                }
            } 
            }
            if (!type_operation.compare("1")) 
                    {
                        wxString sqlText;
                        sqlText<<wxSqlTextUpdFzStart;
                        sqlText<<fio; sqlText<<wxSqlTextUpdFz1;
                        sqlText<<seriy; sqlText<<wxSqlTextUpdFz2;
                        sqlText<<number; sqlText<<wxSqlTextUpdFz3;
                        if(!strDr.compare(wxSQL_DEFAULT)) {sqlText<<strDr;}
                        else {sqlText<<wxSqlCharStr; sqlText<<strDr; sqlText<<wxSqlCharStr;}
                        sqlText<<wxSqlTextUpdFz4; sqlText<<id_fio; sqlText<<wxSqlEndText;
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                        {}
                    }            
        }
        if (!type_operation.compare("0"))
        {
            wxString sqlText;
            sqlText<<wxSqlTextInsProvSotrToStart;
            sqlText<<id_fio; sqlText<<wxSqlCommaText;
            sqlText<<id_; sqlText<<wxSqlCommaText;
            sqlText<<idDolz; sqlText<<wxSqlCommaText;
            sqlText<<idUk; sqlText<<wxSqlCommaText;
            sqlText<<idRez; sqlText<<wxSqlCommaText;
            sqlText<<idSotr; sqlText<<wxSqlRightCaw;
            sqlText<<idDate; sqlText<<wxSqlBothCaw;
            sqlText<<idComment; sqlText<<wxSqlLeftCaw;
            sqlText<<idGc; sqlText<<wxSqlNumberOneEnd;
           // wxMessageBox(sqlText,wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            {
                //InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this);
                //wxMessageBox(wxID_SUCCESS_OPERATION,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
            }
        }
        if (!type_operation.compare("1"))
        {
            wxString sqlText;
            sqlText<<wxSqlTextUpdProvSotrToStart;
            sqlText<<idDolz; sqlText<<wxSqlTextUpdProvSotrTo_1;
            sqlText<<idUk; sqlText<<wxSqlTextUpdProvSotrTo_2;
            sqlText<<idRez; sqlText<<wxSqlTextUpdProvSotrTo_3;
            sqlText<<idSotr; sqlText<<wxSqlTextUpdProvSotrTo_4;
            sqlText<<idGc; sqlText<<wxSqlTextUpdProvSotrTo_5;
            sqlText<<idDate; sqlText<<wxSqlTextUpdProvSotrTo_6;
            sqlText<<idComment; sqlText<<wxSqlTextUpdProvSotrTo_7;
            sqlText<<idArchive; sqlText<<wxSqlTextUpdProvSotrTo_where;
            sqlText<<id_; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            {
                //InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this);
                //wxMessageBox(wxID_SUCCESS_OPERATION,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
            }
        }
        }
        this->EndModal(wxID_OK);
    }
    if(event.GetId()==wxID_CANCEL)
	{
        this->EndModal(wxID_CANCEL);
    }
}

EnterProvSotrTo::~EnterProvSotrTo()
{
}

/*
Dialog - EnterProvSotrTo - end
*/

/*
Dialog - EnterFz - start
*/
BEGIN_EVENT_TABLE(EnterFz,wxDialog)
    EVT_BUTTON (wxID_OK, EnterFz::OnButton)
    EVT_BUTTON (wxID_CANCEL, EnterFz::OnButton)
    EVT_CHAR_HOOK(EnterFz::OnChar)
END_EVENT_TABLE()

EnterFz::EnterFz(wxWindow *parent, int id1, int type, wxWindowID id, const wxString &caption, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBox *stBox1 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_FIO);
    wxStaticBoxSizer *to_static_box1 = new wxStaticBoxSizer(stBox1,wxHORIZONTAL);
    wxStaticBox *stBox2 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_PASSPORT);
    wxStaticBoxSizer *to_static_box2 = new wxStaticBoxSizer(stBox2,wxHORIZONTAL);
    
    to_static_box1->Add(new wxTextCtrl(this,wxID_FZ_FIO_TEXTCTRL, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    to_static_box2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PASP_SER), 0, wxEXPAND|wxLEFT ,5);
    to_static_box2->Add(new wxTextCtrl(this,wxID_FZ_SER_PASP_TEXTCTRL, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    to_static_box2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PASP_NUM), 0, wxEXPAND|wxLEFT ,5);
    to_static_box2->Add(new wxTextCtrl(this,wxID_FZ_NUM_PASP_TEXTCTRL, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CENTRE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_STATICTEXT_DATE_ROJD), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr1->Add(new wxDatePickerCtrl(this,wxID_FZ_DR_FZ,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr2->Add(new wxCheckBox(this,wxID_FZ_SPS_PROV_CHECKBOX,wxCAPTION_CHECKBOX_PROV_COMPARE), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr2->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0);
    vert_bos->Add(to_static_box1, 0, wxEXPAND,0);
    vert_bos->Add(to_static_box2, 0, wxEXPAND,0);
    vert_bos->Add(hr1, 0, wxEXPAND,0);
    vert_bos->Add(hr2, 0, wxEXPAND,0);
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    ((wxTextCtrl*)this->FindWindow(wxID_FZ_SER_PASP_TEXTCTRL))->SetMaxLength(4); //устанавливаем ограничение на количество вводимых символов в поле с серией паспорта   
    ((wxTextCtrl*)this->FindWindow(wxID_FZ_NUM_PASP_TEXTCTRL))->SetMaxLength(6); //устанавливаем ограничение на количество вводимых символов в поле с номером паспорта
    ((wxCheckBox*)this->FindWindow(wxID_FZ_SPS_PROV_CHECKBOX))->SetValue(true); //ставим галочку в чекбоксе
    ((wxTextCtrl*)this->FindWindow(wxID_FZ_FIO_TEXTCTRL))->SetFocus(); //устанавливаем фокус ввода на поле с ФИО
    SetAffirmativeId(wxID_OK);      //Задаем идентификатор для использования в качестве кнопки ОК
    type_operation<<type;           //тип операции
    /*Включаем акселераторы*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*конец с акселераторами*/
    if(type==1) 
    {
        select_string<<id1;     //если операция обновления,то присваиваем переменной номер выделенной строки
        ProvAgFrm *parentWindow = (ProvAgFrm*)this->GetParent();                                //присваиваем переменной указатель на родительское окно
        wxListView* listview = ((wxListView*)parentWindow->FindWindow(wxID_AG_SP_LIST_RES));    //получаем указатель на листвьюев со списком физлиц
        wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
        f->SetId(id1); //устанавливаем позицию выбранного элемента
        f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT); //возвращаем данные связанные с элементом
        listview->GetItem(*f);
        id_fio<<f->GetData(); //пишем в переменную данные связанные с элементом
        (old_data.idReestrFio)<<f->GetData(); //старые данные до обновления данных контрола
        for(register int i=0; i<listview->GetColumnCount();++i)
        {
            f->SetColumn(i);
            listview->GetItem(*f);
            if(i==0) {((wxTextCtrl*)this->FindWindow(wxID_FZ_FIO_TEXTCTRL))->ChangeValue(f->GetText()); old_data.fio = f->GetText();}
            if(i==1) {((wxTextCtrl*)this->FindWindow(wxID_FZ_SER_PASP_TEXTCTRL))->ChangeValue(f->GetText()); old_data.seriy_pasp = f->GetText();}
            if(i==2) {((wxTextCtrl*)this->FindWindow(wxID_FZ_NUM_PASP_TEXTCTRL))->ChangeValue(f->GetText()); old_data.number_pasp = f->GetText();}
            if(i==3) 
            {
                wxString strDrDate = f->GetText();
                old_data.dr = f->GetText(); //старые данные до обновления данных контрола
                insertStrDateToCtrl (strDrDate, (wxDatePickerCtrl*)this->FindWindow(wxID_FZ_DR_FZ));
            }
        }
        delete f;
    }
}

void EnterFz::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    switch(event.GetId())
    {
        case wxID_FZ_SER_PASP_TEXTCTRL: //запрещаем в поле с ИНН вводить символы отличные от цифр
            {                
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //если зажат шифт, контрл или альт, то отправляем событие вверх к родителю
                {event.Skip(true);} 
                else {
                    if((event.GetKeyCode()>=32&&event.GetKeyCode()<=47)||(event.GetKeyCode()>=58&&event.GetKeyCode()<=255&&event.GetKeyCode()!=127)) //если нажатая кнопка попала в диапазоны, то не пропускаем событие вверх к родителю
                        {event.Skip(false);}
                    else {event.Skip(true);}
                }
                break;
            }
        case wxID_FZ_NUM_PASP_TEXTCTRL: //запрещаем в поле с ТТ вводить символы отличные от цифр
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //если зажат шифт, контрл или альт, то отправляем событие вверх к родителю
                {event.Skip(true);} 
                else {
                    if((event.GetKeyCode()>=32&&event.GetKeyCode()<=47)||(event.GetKeyCode()>=58&&event.GetKeyCode()<=255&&event.GetKeyCode()!=127)) //если нажатая кнопка попала в диапазоны, то не пропускаем событие вверх к родителю
                        {event.Skip(false);}
                    else {event.Skip(true);}
                }
                break;
            }
        default: event.Skip(true);
    }
}
void EnterFz::OnButton (wxCommandEvent &event)
{
    if(event.GetId()==wxID_OK)
	{
        wxString fio, seriy, number, dr;
        int flag_sboy=0, flag_seriy=0, flag_number=0;
        
        fio = ((wxTextCtrl*)this->FindWindow(wxID_FZ_FIO_TEXTCTRL))->GetValue();
        seriy = ((wxTextCtrl*)this->FindWindow(wxID_FZ_SER_PASP_TEXTCTRL))->GetValue();
        number = ((wxTextCtrl*)this->FindWindow(wxID_FZ_NUM_PASP_TEXTCTRL))->GetValue();
        if((((wxDatePickerCtrl*)(this->FindWindow(wxID_FZ_DR_FZ)))->GetValue()).IsValid()) //проверяем не пустое ли поле с датой
        {dr = (((wxDatePickerCtrl*)(this->FindWindow(wxID_FZ_DR_FZ)))->GetValue()).FormatISODate();} //если не пустое, то присваиваем переменной значение
        if(dr.IsEmpty()) {dr=wxSQL_DEFAULT;}
        fio.Trim(true); fio.Trim(false); seriy.Trim(true); seriy.Trim(false); number.Trim(true); number.Trim(false); //удаляем пробелы справа и слева
        if (fio.IsEmpty()) {InformationSleep(wxINFO_NOT_FIO_SOTR,sec_for_sleep_window_info,this); return;}
        fio.MakeUpper();
        switch(seriy.Len())
        {
            case 0:
            {
                seriy<<wxNULL_;
                flag_seriy=1; //признак того, что физик без серии паспорта
                break;
            }
            case 1:
            case 2:
            case 3:
            {
                flag_sboy=1;
                break;
            }
            default: break;
        }
        switch(number.Len())
        {
            case 0:
            {
                number<<wxNULL_;
                flag_number=1; //признак того, что физик без номера паспорта
                break;
            }
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            {
                flag_sboy=1;
                break;
            }
            default: break;
        }
        if(flag_sboy==1||(flag_seriy==0&&flag_number==1)||(flag_seriy==1&&flag_number==0)) {InformationSleep(wxINFO_WRONG_PASPORT,sec_for_sleep_window_info,this); return;}
        
        if(((CrossFrm*)(this->GetGrandParent()))->flag_bl_sb) {if(proverka_bl_sb(conn, fio, 1)==1) {;} else {return;}} //проверка по ЧС СБ
        
        wxString sqlText;   //переменная под текст sql-запроса
        ProvAgFrm *parentWindow = (ProvAgFrm*)this->GetParent();                                //присваиваем переменной указатель на родительское окно
        wxListView* listview = ((wxListView*)parentWindow->FindWindow(wxID_AG_SP_LIST_RES));    //получаем указатель на листвьюев со списком физлиц
        if(!type_operation.compare("0"))                                                 //если тип операции - добавление
        {    
        if(((wxCheckBox*)this->FindWindow(wxID_FZ_SPS_PROV_CHECKBOX))->GetValue())
        {
            if (flag_seriy==1 && flag_number==1) //строим sql запрос БЕЗ паспортных данных
            {
                sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd;
            }
            if (flag_seriy==0 && flag_number==0) //строим sql запрос С паспортными данными
            {
                sqlText<<wxSqlTextSelComparePaspProvSotrToStart;
                sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                sqlText<<number; sqlText<<wxSqlEndText;
            }
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            {
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                int num_rows = mysql_num_rows(res); // и количество строк.
                int num_fields = mysql_num_fields(res); // количество полей
                if(num_rows>0)
                {  
                    parentWindow->count_find+=1; //меняем значение счетчика кол-ва найденных строк.
                    int lastItem=0;
                    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT);
                        f->SetColumn(0);
                        f->SetData(wxAtoi(row[0])); //прячем уникальный айди
                        f->SetId(i);
                        listview->InsertItem(*f);
                        for (register int l = 1; l < num_fields; l++)
                        {
                            listview->SetItem(i,l-1,row[l]);
                        }
                        if(dr.compare(wxSQL_DEFAULT)&&wxString(row[4]).IsEmpty())
                        {
                            sqlText.Clear();
                            sqlText<<wxSqlTextUpdFzStart1; sqlText<<dr;  sqlText<<wxSqlCharStr;
                            sqlText<<wxSqlTextUpdFz4; sqlText<<row[0]; sqlText<<wxSqlEndText;
                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                            {
                                listview->SetItem(i,3,dr);                                
                            } 
                        } 
                        lastItem=i;
                        delete f;
                    }
                    for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                
                    for(register int i =0; i<listview->GetItemCount();++i) {listview->Select(i,false);} //снимаем выделение строк
                    listview->Select(lastItem,true); //выделяем последнюю найденную строку
                    listview->Focus(lastItem); //устанавливаем фокус на последнюю найденную строку
                    mysql_free_result(res); // Очищаем результаты
                }
                else 
                {
                    mysql_free_result(res); // Очищаем результаты
                    sqlText.Clear(); //очищаем переменную от предыдущего sql запроса
                    sqlText<<wxSqlTextInsFioAndPasp;
                    sqlText<<fio; sqlText<<wxSqlLeftCaw;
                    sqlText<<seriy; sqlText<<wxSqlCommaText;
                    sqlText<<number; sqlText<<wxSqlCommaText;
                    if(!dr.compare(wxSQL_DEFAULT)) {sqlText<<dr;}
                    else {sqlText<<wxSqlCharStr; sqlText<<dr; sqlText<<wxSqlCharStr;}
                    sqlText<<wxSqlEndRightBracketText;
                    
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                    {
                        sqlText.Clear(); //очищаем переменную от предыдущего sql запроса
                        if (flag_seriy==1 && flag_number==1) //строим sql запрос БЕЗ паспортных данных
                        {
                            sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                            sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd1;
                        }
                        if (flag_seriy==0 && flag_number==0) //строим sql запрос С паспортными данными
                        {
                            sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                            sqlText<<fio; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd1;
                            sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                            sqlText<<number; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd2;
                        }
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                        {
                            res = mysql_store_result(conn); // Берем результат,
                            num_rows = mysql_num_rows(res); // и количество строк.
                            if(num_rows>0)
                            {
                                parentWindow->count_add+=1; //меняем значение счетчика кол-ва добавленных строк.  
                                int lastItem=0;
                                for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                                {
                                    MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                                    wxListItem *f = new wxListItem();
                                    f->SetState(wxLIST_STATE_FOCUSED);
                                    f->SetMask(wxLIST_MASK_TEXT);
                                    f->SetColumn(0);
                                    f->SetData(atoi(row[0])); //прячем уникальный айди
                                    f->SetId(i);
                                    listview->InsertItem(*f); 
                                    for (register int l = 1; l < num_fields; l++)
                                    {
                                        listview->SetItem(i,l-1,row[l]);
                                    }
                                    lastItem=i;
                                    delete f;
                                }
                                for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                
                                for(register int i =0; i<listview->GetItemCount();++i) {listview->Select(i,false);} //снимаем выделение строк
                                listview->Select(lastItem,true); //выделяем последнюю найденную строку
                                listview->Focus(lastItem); //устанавливаем фокус на последнюю найденную строку
                            }
                            mysql_free_result(res); // Очищаем результаты
                        }
                    }  
                }
                //if(wxAtoi(flag_parent)==0)((wxButton*)parentWindow->FindWindow(wxID_AG_CM_BUTTON_INS))->SetFocus();
                //if(wxAtoi(flag_parent)==1) (((parentWindow->GetParent())->GetParent())->FindWindow(wxID_AG_CM_BUTTON_INS))->SetFocus();
            }
        }
        else
        {
            sqlText<<wxSqlTextInsFioAndPasp;
            sqlText<<fio; sqlText<<wxSqlLeftCaw;
            sqlText<<seriy; sqlText<<wxSqlCommaText;
            sqlText<<number; sqlText<<wxSqlCommaText;
            if(!dr.compare(wxSQL_DEFAULT)) {sqlText<<dr;}
            else {sqlText<<wxSqlCharStr; sqlText<<dr; sqlText<<wxSqlCharStr;}
            sqlText<<wxSqlEndRightBracketText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            {
                sqlText.Clear(); //очищаем переменную от предыдущего sql запроса
                if (flag_seriy==1 && flag_number==1) //строим sql запрос БЕЗ паспортных данных
                {
                    sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                    sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd1;
                }
                if (flag_seriy==0 && flag_number==0) //строим sql запрос С паспортными данными
                {
                    sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                    sqlText<<fio; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd1;
                    sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                    sqlText<<number; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd2;
                }
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                else
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    int num_fields = mysql_num_fields(res); // количество полей
                    if(num_rows>0)
                    {  
                        parentWindow->count_add+=1; //меняем значение счетчика кол-ва добавленных строк.
                        int lastItem=0;
                        for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[0])); //прячем уникальный айди
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 1; l < num_fields; l++)
                            {
                                listview->SetItem(i,l-1,row[l]);
                            }
                            lastItem=i;
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                
                        for(register int i =0; i<listview->GetItemCount();++i) {listview->Select(i,false);} //снимаем выделение строк
                        listview->Select(lastItem,true); //выделяем последнюю найденную строку
                        listview->Focus(lastItem); //устанавливаем фокус на последнюю найденную строку
                    }
                    mysql_free_result(res); // Очищаем результаты
                }
            }
        }}
        if(!type_operation.compare("1"))                                                 //если тип операции - обновление
        {
            sqlText<<wxSqlTextPoiskFzID; //запрос на сравнение старых данных на предмет не совпадения с данными в БД (ситуация когда другой пользователь успел обновить данные)
            sqlText<<id_fio;
            sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            else
            {
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат
                int num_rows = mysql_num_rows(res); // и количество строк.
                int num_fields = mysql_num_fields(res); // количество полей
                if(num_rows>0)
                {  
                    wxString strComp("Другой пользователь успел обновить данные."), strfio, strser, strnum, strdr; 
                    int flagFio=0, flagSer=0, flagNum=0, flagDr=0;
                    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        strfio=row[0]; strser=row[1]; strnum=row[2]; strdr=row[3];
                        if(old_data.fio.compare(row[0])) {flagFio=1; strComp<<"\nФИО"; strComp<<"\tданные изменены на - "; strComp<<strfio;}
                        if(old_data.seriy_pasp.compare(row[1])) {flagSer=1; strComp<<"\nСЕРИЯ ПАСПОРТА"; strComp<<"\tданные изменены на - "; strComp<<strser;}
                        if(old_data.number_pasp.compare(row[2])) {flagNum=1; strComp<<"\nНОМЕР ПАСПОРТА"; strComp<<"\tданные изменены на - "; strComp<<strnum;}
                        if(old_data.dr.compare(row[3])) {flagDr=1; strComp<<"\nДАТА РОЖДЕНИЯ"; strComp<<"\tданные изменены на - "; strComp<<strdr;}   
                    }
                    if (flagFio||flagSer||flagNum||flagDr)
                    {
                        strComp<<"\n\nДанные будут перезаписаны. Продолжить операцию?";
                        if(wxMessageBox(strComp,wxATTENTION,wxYES_NO,this)==wxYES)
                        {
                            sqlText.Clear();
                            sqlText<<wxSqlTextUpdFzStart;
                            sqlText<<fio; sqlText<<wxSqlTextUpdFz1;
                            sqlText<<seriy; sqlText<<wxSqlTextUpdFz2;
                            sqlText<<number; sqlText<<wxSqlTextUpdFz3;
                            if(!dr.compare(wxSQL_DEFAULT)) {sqlText<<dr;}
                            else {sqlText<<wxSqlCharStr; sqlText<<dr; sqlText<<wxSqlCharStr;}
                            sqlText<<wxSqlTextUpdFz4;
                            sqlText<<id_fio; sqlText<<wxSqlEndText;
                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                            else
                            {
                                listview->SetItem(wxAtoi(select_string),0,fio);
                                if(!seriy.compare(wxNULL_)) {seriy=""; listview->SetItem(wxAtoi(select_string),1,seriy);} else {listview->SetItem(wxAtoi(select_string),1,seriy);}
                                if(!number.compare(wxNULL_)) {number=""; listview->SetItem(wxAtoi(select_string),2,number);} else {listview->SetItem(wxAtoi(select_string),2,number);}
                                if(!dr.compare(wxSQL_DEFAULT)) {dr=""; listview->SetItem(wxAtoi(select_string),3,dr);} else {listview->SetItem(wxAtoi(select_string),3,dr);}
                            }  
                        } 
                        else 
                        {
                            if(flagFio) {listview->SetItem(wxAtoi(select_string),0,strfio);}
                            if(flagSer) {listview->SetItem(wxAtoi(select_string),1,strser);}
                            if(flagNum) {listview->SetItem(wxAtoi(select_string),2,strnum);}
                            if(flagDr) {listview->SetItem(wxAtoi(select_string),3,strdr);}
                            this->EndModal(wxID_CANCEL); return;
                        }
                    }
                    else
                    {
                        sqlText.Clear();
                            sqlText<<wxSqlTextUpdFzStart;
                            sqlText<<fio; sqlText<<wxSqlTextUpdFz1;
                            sqlText<<seriy; sqlText<<wxSqlTextUpdFz2;
                            sqlText<<number; sqlText<<wxSqlTextUpdFz3;
                            if(!dr.compare(wxSQL_DEFAULT)) {sqlText<<dr;}
                            else {sqlText<<wxSqlCharStr; sqlText<<dr; sqlText<<wxSqlCharStr;}
                            sqlText<<wxSqlTextUpdFz4;
                            sqlText<<id_fio; sqlText<<wxSqlEndText;
                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                            else
                            {
                                listview->SetItem(wxAtoi(select_string),0,fio);
                                if(!seriy.compare(wxNULL_)) {seriy=""; listview->SetItem(wxAtoi(select_string),1,seriy);} else {listview->SetItem(wxAtoi(select_string),1,seriy);}
                                if(!number.compare(wxNULL_)) {number=""; listview->SetItem(wxAtoi(select_string),2,number);} else {listview->SetItem(wxAtoi(select_string),2,number);}
                                if(!dr.compare(wxSQL_DEFAULT)) {dr=""; listview->SetItem(wxAtoi(select_string),3,dr);} else {listview->SetItem(wxAtoi(select_string),3,dr);}
                            }
                    }
                }
                mysql_free_result(res); // Очищаем результаты
            }   
        } 
        this->EndModal(wxID_OK);
    }
	if(event.GetId()==wxID_CANCEL)
	{
        this->EndModal(wxID_CANCEL);
    }
}

EnterFz::~EnterFz()
{
}

/*
Dialog - EnterFz - end
*/

/*
Dialog - ListProvFz - start
*/
BEGIN_EVENT_TABLE(ListProvFz,wxDialog)
    EVT_BUTTON (wxID_INS_PR_FZ_BUTTON, ListProvFz::OnButton)
    EVT_BUTTON (wxID_UPD_PR_FZ_BUTTON, ListProvFz::OnButton)
    EVT_BUTTON (wxID_DEL_PR_FZ_BUTTON, ListProvFz::OnButton)
    EVT_BUTTON (wxID_COMMENT_PR_FZ_BUTTON, ListProvFz::OnButton)
    EVT_CHAR_HOOK(ListProvFz::OnChar)
    EVT_SIZE(ListProvFz::OnSize)
	EVT_MOVE_END(ListProvFz::OnMove)
END_EVENT_TABLE()

ListProvFz::ListProvFz(wxWindow *parent, int id_, const wxString &caption, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxStaticBox *stBox1 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_LIST_PROV_FZ);
    wxStaticBoxSizer *to_static_box1 = new wxStaticBoxSizer(stBox1,wxHORIZONTAL);
    wxStaticBox *stBox2 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_COMMAND_PANEL);
    wxStaticBoxSizer *to_static_box2 = new wxStaticBoxSizer(stBox2,wxHORIZONTAL);
    
    wxListView *listview = new wxListView(this, wxID_LIST_PR_FZ_LISTVIEW,wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
    listview->InsertColumn(0,wxCAPTION_COLUMN_GC);
    listview->InsertColumn(1,wxCAPTION_COLUMN_TO);
    listview->InsertColumn(2,wxCAPTION_COLUMN_JOB);
    listview->InsertColumn(3,wxCAPTION_COLUMN_UK);
    listview->InsertColumn(4,wxCAPTION_COLUMN_REZ);
    listview->InsertColumn(5,wxCAPTION_COLUMN_SOTRSB);
    listview->InsertColumn(6,wxCAPTION_COLUMN_DATE);
    listview->InsertColumn(7,wxCAPTION_COLUMN_ARCHIVE);
    
    to_static_box1->Add(listview, 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    to_static_box2->Add(new wxButton(this, wxID_INS_PR_FZ_BUTTON, wxCAPTION_BUTTON_INSERT,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE), 0, wxEXPAND);
    to_static_box2->Add(new wxButton(this, wxID_UPD_PR_FZ_BUTTON, wxCAPTION_BUTTON_UPDATE,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE), 0, wxEXPAND);
    to_static_box2->Add(new wxButton(this, wxID_DEL_PR_FZ_BUTTON, wxCAPTION_BUTTON_DELETE,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE), 0, wxEXPAND);
    to_static_box2->Add(new wxButton(this, wxID_COMMENT_PR_FZ_BUTTON, wxCAPTION_BUTTON_COMMENT,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE), 0, wxEXPAND);
    
    vert_bos->Add(to_static_box1, 1, wxEXPAND,0);
    vert_bos->Add(to_static_box2, 0, wxEXPAND,0);
    this->SetSizer(vert_bos);
    
    id_fio<<id_; //присваиваем айди физ.лица переменной диалога
    
    SelectInfoFromBD(); //заполняем листвьюев элементами
    (this->FindWindow(wxID_INS_PR_FZ_BUTTON))->SetFocus(); //устанавливаем фокус ввода на кнопку Добавить
}
void ListProvFz::OnButton (wxCommandEvent &event)
{
    if(event.GetId()==wxID_COMMENT_PR_FZ_BUTTON)
	{
        CommentProv();
    }
    if(event.GetId()==wxID_DEL_PR_FZ_BUTTON)
	{
        DeleteProv();
    }
    if(event.GetId()==wxID_INS_PR_FZ_BUTTON)
	{
        int flag_succes=0; //флаг того, что в диалоговом окне добавления проверки был нажат ОК
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        /*
        Считываем из файла конфигурация размеры последнего открытого окна.
        Если файла не существует, про применяем параметры по умолчанию
        */
        long x = config->ReadLong("/FORM_AGENT_PROV_INS/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_AGENT_PROV_INS/y", 0);
        long width = config->ReadLong("/FORM_AGENT_PROV_INS/width", 0);
        long height = config->ReadLong("/FORM_AGENT_PROV_INS/height", 0);
        if(x&&y&&width&&height)
        {
            InsProvFz InsPrFz(this,"",id_fio,this->GetLabel(),wxID_ANY,wxPoint(x,y),wxSize(width,height));
            if(InsPrFz.ShowModal() == wxID_CANCEL) {;} else {flag_succes=1;} 
        }
        else
        {
            InsProvFz InsPrFz(this,"",id_fio,this->GetLabel());
            if(InsPrFz.ShowModal() == wxID_CANCEL) {;} else {flag_succes=1;}
        }
        if(flag_succes==1) {SelectInfoFromBD(); (this->FindWindow(wxID_UPD_PR_FZ_BUTTON))->SetFocus();} //перерисовываем содержимое листвьюев
    }
    if(event.GetId()==wxID_UPD_PR_FZ_BUTTON)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LIST_PR_FZ_LISTVIEW)); //получаем указатель на листвьюев с проверками сотрудников то
        int count = 0;
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} //не выбрана ниодна строка
        for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
        {
            //wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
            //f->SetId(idItem); //устанавливаем позицию выбранного элемента
            //f->SetMask(wxLIST_MASK_DATA); //возвращаем данные связанные с элементом
            //listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
            //int idProvSotrTo=0; idProvSotrTo=f->GetData(); //пишем в переменную данные связанные с элементом
            //if(idProvSotrTo>0)
            //{
                //wxString buffer; buffer<<idProvSotrTo;
                wxString buffer; buffer<<idItem;
                wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
                wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
                /*
                Считываем из файла конфигурация размеры последнего открытого окна.
                Если файла не существует, про применяем параметры по умолчанию
                */
                long x = config->ReadLong("/FORM_AGENT_PROV_INS/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
                long y = config->ReadLong("/FORM_AGENT_PROV_INS/y", 0);
                long width = config->ReadLong("/FORM_AGENT_PROV_INS/width", 0);
                long height = config->ReadLong("/FORM_AGENT_PROV_INS/height", 0);
                if(x&&y&&width&&height)
                {
                    InsProvFz InsPrFz(this,buffer,id_fio,this->GetLabel(),wxID_ANY,wxPoint(x,y),wxSize(width,height));
                    if(InsPrFz.ShowModal() == wxID_CANCEL) {;} else {++count;} 
                }
                else
                {
                    InsProvFz InsPrFz(this,buffer,id_fio,this->GetLabel());
                    if(InsPrFz.ShowModal() == wxID_CANCEL) {;} else {++count;}
                }
            //} else {InformationSleep(wxWARNING_NO_DATA,sec_for_sleep_window_info,this);}
            //delete f;
        }
        if (count>0)
        {
            SelectInfoFromBD(); //перерисовываем содержимое листвьюев
            wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_UPD_COUNT; str<<count; //строим строку с кол-вом обновленных строк
            InformationSleep(str,sec_for_sleep_window_info,this);
        } else {;} //если не выбрана ни одна строка, то предупреждаем об этом пользователя и завершаем обработку
        (this->FindWindow(wxID_UPD_PR_FZ_BUTTON))->SetFocus();
    }
}
void ListProvFz::CommentProv (void)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LIST_PR_FZ_LISTVIEW)); //получаем указатель на листвьюев  
        /*
        GetFirstSelected()      - получает номер первого элемента выделенного в листвьюев
        GetNextSelected(idItem) - получает номер следующего выделенного элемента после idItem
        idItem!=-1              - нет больше выделенных строк.
        */
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
        for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
        {
            wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
            f->SetId(idItem); //устанавливаем позицию выбранного элемента
            f->SetMask(wxLIST_MASK_DATA); //возвращаем данные связанные с элементом
            listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
            wxString idReestrProvFl; idReestrProvFl<<f->GetData(); //пишем в переменную данные связанные с элементом
            if(!idReestrProvFl.IsEmpty())
            {
                
                wxString sqlText = wxSqlTextComProvSotrToStart; sqlText<<idReestrProvFl; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    MYSQL_ROW row = mysql_fetch_row(res); // получаем строку 
                    for (;row;row=mysql_fetch_row(res))
                    {
                        wxMessageBox(row[0],wxCAPTION_COMMENT,wxOK,this);
                    }
                    mysql_free_result(res);
                } 
            } else {InformationSleep(wxWARNING_NO_DATA,sec_for_sleep_window_info,this);} 
            delete f;
        }
        (this->FindWindow(wxID_COMMENT_PR_FZ_BUTTON))->SetFocus();
    }
void ListProvFz::DeleteProv (void)
{
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LIST_PR_FZ_LISTVIEW)); //получаем указатель на листвьюев с проверками  
        int count = 0;
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
        {
            for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
            {
                wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
                f->SetId(idItem); //устанавливаем позицию выбранного элемента
                f->SetMask(wxLIST_MASK_DATA); //возвращаем данные связанные с элементом
                listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
                wxString idReestrProvFl; idReestrProvFl<<f->GetData(); //пишем в переменную данные связанные с элементом
                if(!idReestrProvFl.IsEmpty())
                {
                    wxString sqlText = wxSqlTextDelProvSotrToStart; sqlText<<idReestrProvFl; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                    else 
                    {
                        ++count; //считаем кол-во строк, который были удалены
                    } 
                } else {InformationSleep(wxWARNING_NO_DATA,sec_for_sleep_window_info,this);} 
                delete f;
            }
            if (count>0)
            {
                SelectInfoFromBD(); //перерисовываем листвьев с проверками
                wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_DEL_COUNT; str<<count; //строим строку с кол-вом удаленных строк
                InformationSleep(str,sec_for_sleep_window_info,this);
                //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
            } else {;} //если не выбрана ни одна строка, то предупреждаем об этом пользователя и завершаем обработку
            (this->FindWindow(wxID_DEL_PR_FZ_BUTTON))->SetFocus();
        }
}
void ListProvFz::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    if(event.GetKeyCode()==13) //нажата кнопка Enter
    {
        this->EndModal(wxID_OK);
        event.Skip(false);
    }
    if(event.GetKeyCode()==WXK_ESCAPE) //нажата кнопка Esc
    {
        this->EndModal(wxID_CANCEL);
        event.Skip(false);
    }    
        else {event.Skip(true);}
}

void ListProvFz::SelectInfoFromBD(void)
{
    wxListView *listview = ((wxListView*)this->FindWindow(wxID_LIST_PR_FZ_LISTVIEW)); //получаем указатель на листвьюев с проверками
    listview->DeleteAllItems(); //очищаем листвьюев от всех элементов
    wxString sqlText;
    sqlText<<wxSqlTextSelProvFzStart;
    sqlText<<id_fio; sqlText<<wxSqlEndText;
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
                f->SetMask(wxLIST_MASK_TEXT);
                f->SetColumn(0);
                f->SetData(atoi(row[0])); //прячем уникальный айди
                f->SetId(i);
                listview->InsertItem(*f); 
                for (register int l = 1; l < num_fields; l++)
                {
                    if(l==1)
                    {
                        wxString buff; buff=row[l];
                        if(!buff.IsEmpty())
                        {
                            for(register int k =0; k<MyGcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                            {
                                //if(atoi(MyGcArray.Item(k).idGc.c_str())==wxAtoi(buff)) //совпадение найдено
                                if(MyGcArray.Item(k).idGc==wxAtoi(buff)) //совпадение найдено
                                {   
                                    listview->SetItem(i,l-1,MyGcArray.Item(k).nameGc);
                                    break; //выходим из вложенного цикла
                                }
                            }
                        }
                    }
                    if(l==2) {listview->SetItem(i,l-1,row[l]);}
                    if(l==3)
                    {
                        for(register int k =0; k<MyDolznostArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                        {
                            //if(atoi(MyDolznostArray.Item(k).idDolznost.c_str())==atoi(row[l])) //совпадение найдено
                            if(MyDolznostArray.Item(k).idDolznost==wxAtoi(row[l])) //совпадение найдено
                            {
                                listview->SetItem(i,l-1,MyDolznostArray.Item(k).nameDolznost);
                                break; //выходим из вложенного цикла
                            }
                        }
                    }
                    if(l==4)
                    {
                        for(register int k =0; k<MyUkRfArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                        {
                            //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //совпадение найдено
                            if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //совпадение найдено
                            {
                                listview->SetItem(i,l-1,MyUkRfArray.Item(k).nameUkRf);
                                break; //выходим из вложенного цикла
                            }
                        }
                    }
                    if(l==5)
                    {
                        for(register int k =0; k<MyRezProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                        {
                            //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //совпадение найдено
                            if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //совпадение найдено
                            {
                                listview->SetItem(i,l-1,MyRezProvArray.Item(k).nameRezProv);
                                break; //выходим из вложенного цикла
                            }
                        }
                    }
                    if(l==6)
                    {
                        for(register int k =0; k<MyFioSbArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                        {
                            //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //совпадение найдено
                            if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //совпадение найдено
                            {
                                listview->SetItem(i,l-1,MyFioSbArray.Item(k).nameFioSb);
                                break; //выходим из вложенного цикла
                            }
                        }
                    }
                    if(l==7||l==8)
                    {
                        listview->SetItem(i,l-1,row[l]);
                    }
                }
                delete f;
            }
            for(register int i=0;i<listview->GetColumnCount();++i)
            {
                listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //изменяем размер столбца по длине самого большого элемента
            }  
            listview->Select(num_rows-1);  
        }
        mysql_free_result(res); // Очищаем результаты
    }    
}
void ListProvFz::OnSize(wxSizeEvent& event) //ловим размеры окна во время события изменения нижней или правой границы
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_AGENT_PROV/x"), rect.GetX() );
    config->Write( wxT("/FORM_AGENT_PROV/y"), rect.GetY() );
    config->Write( wxT("/FORM_AGENT_PROV/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_AGENT_PROV/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void ListProvFz::OnMove(wxMoveEvent& event) //ловим размеры окна во время события передвижения окна
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_AGENT_PROV/x"), rect.GetX() );
    config->Write( wxT("/FORM_AGENT_PROV/y"), rect.GetY() );
    config->Write( wxT("/FORM_AGENT_PROV/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_AGENT_PROV/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
ListProvFz::~ListProvFz()
{
}
/*
Dialog - ListProvFz - end
*/

/*
Dialog - InsProvFz - start
*/
BEGIN_EVENT_TABLE(InsProvFz,wxDialog)
    EVT_CHILD_FOCUS(InsProvFz::NewFocus)
    EVT_CHAR_HOOK(InsProvFz::OnChar)
    EVT_BUTTON (wxID_OK, InsProvFz::OnButton)
    EVT_BUTTON (wxID_CANCEL, InsProvFz::OnButton)
    EVT_LIST_ITEM_FOCUSED(wxID_LISTTO_PR_FZ_LISTVIEW, InsProvFz::SelectItemListView) //используем для определения выделенной строки в листвьев
    EVT_SIZE(InsProvFz::OnSize)
	EVT_MOVE_END(InsProvFz::OnMove)
END_EVENT_TABLE()

InsProvFz::InsProvFz(wxWindow *parent, const wxString &idItem, const wxString &id_fio_, const wxString &caption, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    wxBoxSizer *horizontal_bos = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vert = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr8 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr9 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBox *stBox1 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_PARAM_PROV);
    wxStaticBoxSizer *to_static_box1 = new wxStaticBoxSizer(stBox1,wxHORIZONTAL);
    wxStaticBox *stBox2 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_LIST_TO);
    wxStaticBoxSizer *to_static_box2 = new wxStaticBoxSizer(stBox2,wxVERTICAL);
    
    wxListView *listview = new wxListView(this, wxID_LISTTO_PR_FZ_LISTVIEW,wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
    listview->InsertColumn(0,wxCAPTION_COLUMN_ID);
    listview->InsertColumn(1,wxCAPTION_COLUMN_TO);
    listview->InsertColumn(2,wxCAPTION_COLUMN_INN);
    listview->InsertColumn(3,wxCAPTION_COLUMN_REGION);
    
    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_GC), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr1->Add(new wxTextCtrl(this,wxID_NAMEGC_PR_FZ_TEXTCTRL), 1, wxEXPAND|wxLEFT|wxRIGHT,5);
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_TO "*"), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr2->Add(new wxTextCtrl(this,wxID_NAMETO_PR_FZ_TEXTCTRL), 1, wxEXPAND|wxLEFT|wxRIGHT,5);
    hr2->Add(new wxTextCtrl(this,wxID_IDTO_PR_FZ_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE), 0, wxEXPAND|wxRIGHT,5);
    hr3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_JOB "*"), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr3->Add(new wxTextCtrl(this,wxID_NAMEDL_PR_FZ_TEXTCTRL), 1, wxEXPAND|wxLEFT|wxRIGHT,5);
    hr4->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_COMENT), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr4->Add(new wxTextCtrl(this,wxID_COMMEN_PR_FZ_TEXTCTRL), 1, wxEXPAND|wxLEFT|wxRIGHT,5);
    hr5->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_UK), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr5->Add(new wxTextCtrl(this,wxID_NAMEUK_PR_FZ_TEXTCTRL), 1, wxEXPAND|wxLEFT|wxRIGHT,5);
    hr6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_REZ "*"), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr6->Add(new wxTextCtrl(this,wxID_NAMERZ_PR_FZ_TEXTCTRL), 1, wxEXPAND|wxLEFT|wxRIGHT,5);
    hr7->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_SOTRSB "*"), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr7->Add(new wxTextCtrl(this,wxID_NAMESB_PR_FZ_TEXTCTRL), 1, wxEXPAND|wxLEFT|wxRIGHT,5);
    hr8->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_DATE "*"), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr8->Add(new wxDatePickerCtrl(this,wxID_DATEPR_PR_FZ_DATECTRL,  wxDefaultDateTime, wxDefaultPosition, wxDefaultSize,wxDP_DEFAULT), 1, wxEXPAND|wxLEFT|wxRIGHT,5);
    if(!idItem.IsEmpty()) {hr8->Add(new wxCheckBox(this,wxID_ARHIV_PR_FZ_CHECKCTRL,wxCAPTION_CHECKBOX_FLAG_ARCHIVE), 1, wxEXPAND|wxLEFT|wxRIGHT,5);}
    hr9->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_RIGHT,0);
    vert->Add(hr1, 0, wxEXPAND,0);
    vert->Add(hr2, 0, wxEXPAND,0);
    vert->Add(hr3, 0, wxEXPAND,0);
    vert->Add(hr4, 0, wxEXPAND,0);
    vert->Add(hr5, 0, wxEXPAND,0);
    vert->Add(hr6, 0, wxEXPAND,0);
    vert->Add(hr7, 0, wxEXPAND,0);
    vert->Add(hr8, 0, wxEXPAND,0);
    vert->Add(hr9, 0, wxEXPAND,0);
    to_static_box1->Add(vert, 0, wxEXPAND,0);
    to_static_box2->Add(listview, 1, wxEXPAND);
    to_static_box2->Add(new wxBannerWindow(this, wxID_ITOG_PR_FZ_BANNER, wxBOTTOM), 0, wxEXPAND);
    ((wxBannerWindow*)this->FindWindow(wxID_ITOG_PR_FZ_BANNER))->SetText(wxCOUNT_STRING wxZERO_STRING, wxNULL_STRING);
    ((wxBannerWindow*)this->FindWindow(wxID_ITOG_PR_FZ_BANNER))->SetGradient(*wxWHITE,*wxLIGHT_GREY);
    
    horizontal_bos->Add(to_static_box1, 0, wxEXPAND,0);
    horizontal_bos->Add(to_static_box2, 1, wxEXPAND,0);
    this->SetSizer(horizontal_bos);
    
    wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
    LocArray.Alloc(MyGcArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int j =0; j<MyGcArray.GetCount();++j)   //заполняем локальный массив
    {
        //if(!MyGcArray.Item(j).activGc.compare("1")) {LocArray.Add(MyGcArray.Item(j).nameGc);}
        if(MyGcArray.Item(j).activGc==1) {LocArray.Add(MyGcArray.Item(j).nameGc);}
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(MyDolznostArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyDolznostArray.GetCount();++i) //заполняем локальный массив 
    {
        LocArray.Add((MyDolznostArray.Item(i).nameDolznost));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMEDL_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(MyUkRfArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyUkRfArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyUkRfArray.Item(i).nameUkRf));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMEUK_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(MyRezProvArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
    for(register int i =0; i<MyRezProvArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyRezProvArray.Item(i).nameRezProv));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMERZ_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    LocArray.Alloc(MyFioSbArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов
    for(register int i =0; i<MyFioSbArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
    {
        LocArray.Add((MyFioSbArray.Item(i).nameFioSb));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMESB_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    id_fio=id_fio_; //присваиваем переменной диалога айди физлица
    /*Включаем акселераторы*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*конец с акселераторами*/
    //(this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->MoveAfterInTabOrder(this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL));
    //(this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL))->MoveAfterInTabOrder(this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW));
    //(this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW))->MoveAfterInTabOrder(this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL));
    (this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->SetFocus();
    if(!idItem.IsEmpty())
    {
        idItemListView=idItem; //присваиваем переменной диалога номер выбранной строки в диалоге с проверками
        ListProvFz *parentWindow = (ListProvFz*)this->GetParent();
        wxListView *listview = ((wxListView*)parentWindow->FindWindow(wxID_LIST_PR_FZ_LISTVIEW));  
        wxListItem *f = new wxListItem();  
        f->SetId(wxAtoi(idItem));  
        f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT);  
        listview->GetItem(*f);  
        int idProvSotrTo=0; idProvSotrTo=f->GetData();  
        if(idProvSotrTo>0)
        {
            id_prov_fz<<idProvSotrTo; //присваиваем переменной диалога айди проверки физлица
            f->SetColumn(0); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(1); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(2); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMEDL_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(3); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMEUK_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(4); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMERZ_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText()); 
            f->SetColumn(5); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMESB_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(6); listview->GetItem(*f);
            wxString str=f->GetText(); //пишем дату из результата выборки запроса в переменную
            insertStrDateToCtrl (str, (wxDatePickerCtrl*)this->FindWindow(wxID_DATEPR_PR_FZ_DATECTRL));
            f->SetColumn(7); listview->GetItem(*f);
            str=f->GetText();
            if (wxAtoi(str)==1) {((wxCheckBox*)this->FindWindow(wxID_ARHIV_PR_FZ_CHECKCTRL))->SetValue(false);}
            if (wxAtoi(str)==0) {((wxCheckBox*)this->FindWindow(wxID_ARHIV_PR_FZ_CHECKCTRL))->SetValue(true);}
            wxString sqlText;
            sqlText<<wxSqlTextSelCommProvFz;
            sqlText<<id_prov_fz; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            else
            {
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат
                int num_rows = mysql_num_rows(res); // и количество строк.
                if(num_rows>0)
                {  
                    //for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                    //{
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        ((wxTextCtrl*)this->FindWindow(wxID_COMMEN_PR_FZ_TEXTCTRL))->ChangeValue(row[0]);
                        ((wxTextCtrl*)this->FindWindow(wxID_IDTO_PR_FZ_STATIC))->ChangeValue(row[1]);
                        /*old_data.idReestr=id_prov_fz;
                        old_data.idGc=row[7];
                        old_data.idTo=row[1];
                        old_data.idDolz=row[2];
                        old_data.idUk=row[3];
                        old_data.idRez=row[4];
                        old_data.idSotr=row[5];
                        old_data.idData=row[6];
                        old_data.idArhiv=row[8];*/
                        old_data.idReestr=wxAtoi(id_prov_fz);
                        old_data.idGc=wxAtoi(row[7]);
                        old_data.idTo=wxAtoi(row[1]);
                        old_data.idDolz=wxAtoi(row[2]);
                        old_data.idUk=wxAtoi(row[3]);
                        old_data.idRez=wxAtoi(row[4]);
                        old_data.idSotr=wxAtoi(row[5]);
                        old_data.idData=wxAtoi(row[6]);
                        old_data.idArhiv=wxAtoi(row[8]);
                    //}
                } else {InformationSleep(wxCAPTION_COMMENT wxWARNING_NO_DATA,sec_for_sleep_window_info,this);}
                mysql_free_result(res); // Очищаем результаты 
            }
            
            
            
        } else {InformationSleep(wxWARNING_NO_DATA,sec_for_sleep_window_info,this);}
        delete f;
    }
    /*if(((wxTextCtrl*)this->FindWindow(wxID_COMMEN_PR_FZ_TEXTCTRL))->IsEmpty()) //если поле с комментарием пустое, то вставляем ФИО
    {
        wxString strComm = this->GetLabel();
        EditStringFio (strComm); //функция редактирует строку wxString меняя ИВАНОВ ИВАН ИВАНОВИЧ на Иванов И.И.
        ((wxTextCtrl*)this->FindWindow(wxID_COMMEN_PR_FZ_TEXTCTRL))->ChangeValue(strComm);
    }*/
}

void InsProvFz::NewFocus(wxChildFocusEvent& event)
{
    if(idWindowFocus==wxID_LISTTO_PR_FZ_LISTVIEW)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW)); //получаем указатель на листвьюев с проверками
        int idItem = listview->GetFirstSelected();
        if(idItem==-1) {;}
        else
        {
            wxListItem *f = new wxListItem();
            f->SetMask(wxLIST_MASK_TEXT);
            f->SetColumn(0);
            f->SetId(idItem);
            listview->GetItem(*f);
            ((wxTextCtrl*)this->FindWindow(wxID_IDTO_PR_FZ_STATIC))->ChangeValue(f->GetText());
            f->SetColumn(1);
            listview->GetItem(*f);
            ((wxTextCtrl*)this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            delete f;
        }
    }
    idWindowFocus=(event.GetWindow())->GetId();
}

void InsProvFz::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    switch(event.GetId())
    {
        case wxID_NAMETO_PR_FZ_TEXTCTRL: //после нажатия таб в поле с наименованием ТО заполняем листвьев.
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //если зажат шифт, контрл или альт, то отправляем событие вверх к родителю
                {event.Skip(true);} 
                else {
                    if(event.GetKeyCode()==WXK_TAB)
                        {
                            wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW)); //получаем указатель на листвьюев с проверками
                            completeListView(); 
                            listview->SetFocus(); 
                            event.Skip(false);
                        }
                    else {event.Skip(true);}
                }
                break;
            }
        case wxID_LISTTO_PR_FZ_LISTVIEW: //запрещаем в поле с ИНН вводить символы отличные от цифр
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //если зажат шифт, контрл или альт, то отправляем событие вверх к родителю
                {event.Skip(true);} 
                else {
                    if(event.GetKeyCode()==WXK_TAB)
                        {
                            wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW)); //получаем указатель на листвьюев с проверками
                            int idItem = listview->GetFirstSelected();
                            if(idItem==-1) {;}
                            else
                            {
                                wxListItem *f = new wxListItem();
                                f->SetMask(wxLIST_MASK_TEXT);
                                f->SetColumn(0);
                                f->SetId(idItem);
                                listview->GetItem(*f);
                                ((wxTextCtrl*)this->FindWindow(wxID_IDTO_PR_FZ_STATIC))->ChangeValue(f->GetText());
                                f->SetColumn(1);
                                listview->GetItem(*f);
                                ((wxTextCtrl*)this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
                                delete f;
                            }
                            ((wxTextCtrl*)this->FindWindow(wxID_NAMEDL_PR_FZ_TEXTCTRL))->SetFocus(); 
                            event.Skip(false);
                        }
                    else {event.Skip(true);}
                }
                break;
            }
        case wxID_COMMEN_PR_FZ_TEXTCTRL: //команда пришла из поля с комментарием
            /*{
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //если зажат ctrl+z
                {
                    wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                    ((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)(this->GetGrandParent())->GetParent())->fastComment); //вставляем текст из данных-члена прародителя в окно с фокусом ввода          
                }
                event.Skip(true); 
                break;
            }*/
            {
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //если зажат ctrl+z
                {
                    if(wxTheClipboard->Open()) //открываем буфер обмена
                    {
                        wxTheClipboard->SetData(new wxTextDataObject(((CrossFrm*)((this->GetGrandParent())->GetGrandParent())->GetParent())->fastComment)); //копируем в буфер обмена текст из данных члена прародителя окна
                        if(wxTheClipboard->IsSupported(wxDF_TEXT)) //возвращает верно , если есть данные , которые соответствуют формату данных данных wxDF_TEXT
                        {
                            wxTextDataObject textData; //создаем объект для копирования текста из буфера обмена
                            wxTheClipboard->GetData(textData); //извлекаем текст из буфера обмена в объект-приемник
                            //if((wxWindow::FindFocus())->GetId()==wxID_PR_COMMENT) //проверяем то, что фокус ввода находится в поле для комментария
                            {
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(textData.GetText()); //вставляем в поле с комментарием текст из объекта.
                                wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)this->GetGrandParent())->fastComment); //вставляем текст из данных-члена прародителя в окно с фокусом ввода  
                                ((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + textData.GetText());
                            }
                        }
                    wxTheClipboard->Close();
                    }                  
                }
                event.Skip(true); 
                break;
            }
        default: event.Skip(true);
    }
}
void InsProvFz::completeListView (void)
{
wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW)); //получаем указатель на листвьюев с проверками
                            listview->DeleteAllItems(); //очищаем листвьюев от всех элементов
                            ((wxBannerWindow*)this->FindWindow(wxID_ITOG_PR_FZ_BANNER))->SetText(wxCOUNT_STRING wxZERO_STRING, wxNULL_STRING);
                            wxString sqlText, nameTo;
                            nameTo=((wxTextCtrl*)this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL))->GetValue();
                            if(nameTo.IsEmpty()) {;}
                            else
                            {
                                nameTo.MakeUpper();
                                sqlText<<wxSqlTextSelFindToStart;
                                sqlText<<nameTo; sqlText<<wxSqlPercentEnd;
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
                                            f->SetMask(wxLIST_MASK_TEXT);
                                            f->SetColumn(0);
                                            f->SetData(atoi(row[0])); //прячем уникальный айди
                                            f->SetId(i);
                                            listview->InsertItem(*f); 
                                            for (register int l = 0; l < num_fields; l++)
                                            {
                                                listview->SetItem(i,l,row[l]);
                                            }
                                            delete f;
                                        }
                                        for (register int i = 0; i < listview->GetColumnCount(); i++) // Вывод таблицы
                                        {
                                            listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //изменяем размер столбца по длине самого большого элемента
                                        }
                                        textBunner = wxCOUNT_STRING; textBunner<<listview->GetItemCount();
                                        ((wxBannerWindow*)this->FindWindow(wxID_ITOG_PR_FZ_BANNER))->SetText(textBunner, wxNULL_STRING);
                                    }
                                    mysql_free_result(res); // Очищаем результаты
                                }
                            }
}

void InsProvFz::OnSize(wxSizeEvent& event) //ловим размеры окна во время события изменения нижней или правой границы
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_AGENT_PROV_INS/x"), rect.GetX() );
    config->Write( wxT("/FORM_AGENT_PROV_INS/y"), rect.GetY() );
    config->Write( wxT("/FORM_AGENT_PROV_INS/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_AGENT_PROV_INS/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void InsProvFz::OnMove(wxMoveEvent& event) //ловим размеры окна во время события передвижения окна
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_AGENT_PROV_INS/x"), rect.GetX() );
    config->Write( wxT("/FORM_AGENT_PROV_INS/y"), rect.GetY() );
    config->Write( wxT("/FORM_AGENT_PROV_INS/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_AGENT_PROV_INS/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}

void InsProvFz::SelectItemListView (wxListEvent& event)
{
    wxString str=wxSELECT_STRING;   //пишем в переменную значение постоянного элемента
    str<<(event.GetIndex()+1);      //определяем индекс выделенной строки, прибавляем 1 и дописываем в переменную.
    ((wxBannerWindow*)this->FindWindow(wxID_ITOG_PR_FZ_BANNER))->SetText(textBunner, str); //переписываем значение баннера
}
void InsProvFz::OnButton (wxCommandEvent &event)
{
    if(event.GetId()==wxID_OK)
	{
        wxString idGc, idTo, idDolz, idComm, idUk, idRez, idSotr, idData, idArhiv;
        idGc = ((wxTextCtrl*)this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->GetValue();
        idTo = ((wxTextCtrl*)this->FindWindow(wxID_IDTO_PR_FZ_STATIC))->GetValue();
        idDolz = ((wxTextCtrl*)this->FindWindow(wxID_NAMEDL_PR_FZ_TEXTCTRL))->GetValue();
        idComm = ((wxTextCtrl*)this->FindWindow(wxID_COMMEN_PR_FZ_TEXTCTRL))->GetValue();
        idUk = ((wxTextCtrl*)this->FindWindow(wxID_NAMEUK_PR_FZ_TEXTCTRL))->GetValue();
        idRez = ((wxTextCtrl*)this->FindWindow(wxID_NAMERZ_PR_FZ_TEXTCTRL))->GetValue();
        idSotr = ((wxTextCtrl*)this->FindWindow(wxID_NAMESB_PR_FZ_TEXTCTRL))->GetValue();
        idData = (((wxDatePickerCtrl*)(this->FindWindow(wxID_DATEPR_PR_FZ_DATECTRL)))->GetValue()).FormatISODate();
        if(!idItemListView.IsEmpty()) {idArhiv <<(((wxCheckBox*)this->FindWindow(wxID_ARHIV_PR_FZ_CHECKCTRL))->GetValue());}
        if(idTo.IsEmpty()||idDolz.IsEmpty()||idRez.IsEmpty()||idSotr.IsEmpty()||idData.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}   
        idDolz.MakeUpper(); idUk.MakeUpper(); idRez.MakeUpper(); idSotr.MakeUpper();
            
        if(idGc.IsEmpty()||(!idGc.compare(wxNOT_DATA))) {idGc=wxNULL_;} 
        else
        {
            idGc.MakeUpper();
            for(register int i =0; i<MyGcArray.GetCount();++i)       //запускаем цикл поиска совпадений 
            {
                //if (!idGc.compare(MyGcArray.Item(i).nameGc)&&(!MyGcArray.Item(i).activGc.compare("1")))
                //{idGc=MyGcArray.Item(i).idGc; break;}      //совпадение найдено
                if (!idGc.compare(MyGcArray.Item(i).nameGc)&&(MyGcArray.Item(i).activGc==1))
                {idGc.Clear(); idGc<<MyGcArray.Item(i).idGc; break;}      //совпадение найдено
            }
        } 
        for(register int i =0; i<MyDolznostArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idDolz.compare(MyDolznostArray.Item(i).nameDolznost))
            //{idDolz=MyDolznostArray.Item(i).idDolznost; break;}      //совпадение найдено
            {idDolz.Clear(); idDolz<<MyDolznostArray.Item(i).idDolznost; break;}      //совпадение найдено
        }
        if(idComm.IsEmpty()) {idComm=wxNULL_STRING;} 
        if(idUk.IsEmpty()) {idUk=wxUK_DEFAULT;}
        else
        {
            for(register int i =0; i<MyUkRfArray.GetCount();++i)       //запускаем цикл поиска совпадений 
            {
                if (!idUk.compare(MyUkRfArray.Item(i).nameUkRf))
                //{idUk=MyUkRfArray.Item(i).idUkRf; break;}      //совпадение найдено
                {idUk.Clear(); idUk<<MyUkRfArray.Item(i).idUkRf; break;}      //совпадение найдено
            }
        }
        for(register int i =0; i<MyRezProvArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idRez.compare(MyRezProvArray.Item(i).nameRezProv))
            //{idRez=MyRezProvArray.Item(i).idRezProv; break;}      //совпадение найдено
            {idRez.Clear(); idRez<<MyRezProvArray.Item(i).idRezProv; break;}      //совпадение найдено
        }
        for(register int i =0; i<MyFioSbArray.GetCount();++i)       //запускаем цикл поиска совпадений 
        {
            if (!idSotr.compare(MyFioSbArray.Item(i).nameFioSb))
            //{idSotr=MyFioSbArray.Item(i).idFioSb; break;}      //совпадение найдено
            {idSotr.Clear(); idSotr<<MyFioSbArray.Item(i).idFioSb; break;}      //совпадение найдено
        }
        if(idDolz.IsNumber()||idUk.IsNumber()||idRez.IsNumber()||idSotr.IsNumber()) {} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        wxString sqlText;
        if (idItemListView.IsEmpty())
        {
            int flagInsert=0; //флаг того, что нужно добавить запись в БД
            sqlText<<wxSqlTextSelProvSotrToID; sqlText<<id_fio; sqlText<<wxSqlAnd;
            sqlText<<wxSqlTextSelProvSotrToID1; sqlText<<idTo; sqlText<<wxSqlAnd;
            sqlText<<wxSqlTextSelProvSotrToID2; sqlText<<idDolz; sqlText<<wxSqlAnd;
            sqlText<<wxSqlTextSelProvSotrToID3; sqlText<<wxSqlCharStr; sqlText<<idData; sqlText<<wxSqlCharStr;  sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            else
            {
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат
                int num_rows = mysql_num_rows(res); // и количество строк.
                if(num_rows>0)
                {
                    if(wxMessageBox("Недавно была добавлена проверка физического лица со схожими параметрами проверки. Совпадение по ФИО, ТО, должности, дате. Продолжить операцию?",wxATTENTION,wxYES_NO, this)==wxYES)
                    {flagInsert=1;}
                }
                else {flagInsert=1;}
                mysql_free_result(res); // Очищаем результаты
            }
            if(flagInsert)
            {
            sqlText.Clear();
            sqlText<<wxSqlTextInsProvSotrToStart;
            sqlText<<id_fio; sqlText<<wxSqlCommaText;
            sqlText<<idTo; sqlText<<wxSqlCommaText;
            sqlText<<idDolz; sqlText<<wxSqlCommaText;
            sqlText<<idUk; sqlText<<wxSqlCommaText;
            sqlText<<idRez; sqlText<<wxSqlCommaText;
            sqlText<<idSotr; sqlText<<wxSqlRightCaw;
            sqlText<<idData; sqlText<<wxSqlBothCaw;
            sqlText<<idComm; sqlText<<wxSqlLeftCaw;
            sqlText<<idGc; sqlText<<wxSqlNumberOneEnd;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
            }
        }
        else
        {
            sqlText<<wxSqlTextSelAllProvFz;
            sqlText<<id_prov_fz; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            else
            {
                int flagGc=0, flagTo=0, flagDolz=0, flagUk=0, flagRez=0, flagSotr=0, flagData=0, flagArhiv=0;
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат
                int num_rows = mysql_num_rows(res); // и количество строк.
                if(num_rows>0)
                {  
                    MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                    /*if(old_data.idGc.compare(row[6])) {flagGc=1;}
                    if(old_data.idTo.compare(row[0])) {flagTo=1;}
                    if(old_data.idDolz.compare(row[1])) {flagDolz=1;}
                    if(old_data.idUk.compare(row[2])) {flagUk=1;}
                    if(old_data.idRez.compare(row[3])) {flagRez=1;}
                    if(old_data.idSotr.compare(row[4])) {flagSotr=1;}
                    if(old_data.idData.compare(row[5])) {flagData=1;}
                    if(old_data.idArhiv.compare(row[7])) {flagArhiv=1;}*/
                    if(old_data.idGc!=wxAtoi(row[6])) {flagGc=1;}
                    if(old_data.idTo!=wxAtoi(row[0])) {flagTo=1;}
                    if(old_data.idDolz!=wxAtoi(row[1])) {flagDolz=1;}
                    if(old_data.idUk!=wxAtoi(row[2])) {flagUk=1;}
                    if(old_data.idRez!=wxAtoi(row[3])) {flagRez=1;}
                    if(old_data.idSotr!=wxAtoi(row[4])) {flagSotr=1;}
                    if(old_data.idData!=wxAtoi(row[5])) {flagData=1;}
                    if(old_data.idArhiv!=wxAtoi(row[7])) {flagArhiv=1;}
                    if(flagGc||flagTo||flagDolz||flagUk||flagRez||flagSotr||flagData||flagArhiv)
                    {
                        wxString strComp;
                        strComp<<"Другой пользователь недавно обновил запись с данной проверкой. Изменения были внесены в следующие поля:";
                        if(flagGc) {strComp<<"\nГЦ";}
                        if(flagTo) {strComp<<"\nТО";}
                        if(flagDolz) {strComp<<"\nДолжность";}
                        if(flagUk) {strComp<<"\nст.УК РФ";}
                        if(flagRez) {strComp<<"\nРезультат проверки";}
                        if(flagSotr) {strComp<<"\nФИО сотрудника СБ";}
                        if(flagData) {strComp<<"\nДата проверки";}
                        if(flagArhiv) {strComp<<"\nПризнак архива";}
                        strComp<<"\n\nДанные будут перезаписаны. Продолжить выполнение операции?";
                        if(wxMessageBox(strComp,wxATTENTION,wxYES_NO,this)==wxYES)
                        {
                            sqlText.Clear();
                            sqlText<<wxSqlTextUpdProvSotrToFzStart;
                            sqlText<<id_fio; sqlText<<wxSqlTextUpdProvSotrTo_8;
                            sqlText<<idTo; sqlText<<wxSqlTextUpdProvSotrTo_9;
                            sqlText<<idDolz; sqlText<<wxSqlTextUpdProvSotrTo_1;
                            sqlText<<idUk; sqlText<<wxSqlTextUpdProvSotrTo_2;
                            sqlText<<idRez; sqlText<<wxSqlTextUpdProvSotrTo_3;
                            sqlText<<idSotr; sqlText<<wxSqlTextUpdProvSotrTo_5;
                            sqlText<<idData; sqlText<<wxSqlTextUpdProvSotrTo_6;
                            sqlText<<idComm; sqlText<<wxSqlTextUpdProvSotrTo_10;
                            sqlText<<idGc; sqlText<<wxSqlTextUpdProvSotrTo_11;
                            sqlText<<idArhiv; sqlText<<wxSqlTextUpdProvSotrTo_where;
                            sqlText<<id_prov_fz; sqlText<<wxSqlEndText;
                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                        } else {this->EndModal(wxID_CANCEL); return;}
                    }
                    else
                    {
                        sqlText.Clear();
                            sqlText<<wxSqlTextUpdProvSotrToFzStart;
                            sqlText<<id_fio; sqlText<<wxSqlTextUpdProvSotrTo_8;
                            sqlText<<idTo; sqlText<<wxSqlTextUpdProvSotrTo_9;
                            sqlText<<idDolz; sqlText<<wxSqlTextUpdProvSotrTo_1;
                            sqlText<<idUk; sqlText<<wxSqlTextUpdProvSotrTo_2;
                            sqlText<<idRez; sqlText<<wxSqlTextUpdProvSotrTo_3;
                            sqlText<<idSotr; sqlText<<wxSqlTextUpdProvSotrTo_5;
                            sqlText<<idData; sqlText<<wxSqlTextUpdProvSotrTo_6;
                            sqlText<<idComm; sqlText<<wxSqlTextUpdProvSotrTo_10;
                            sqlText<<idGc; sqlText<<wxSqlTextUpdProvSotrTo_11;
                            sqlText<<idArhiv; sqlText<<wxSqlTextUpdProvSotrTo_where;
                            sqlText<<id_prov_fz; sqlText<<wxSqlEndText;
                            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                    }   
                } else {;}
                mysql_free_result(res); // Очищаем результаты 
            }
        }
        this->EndModal(wxID_OK);                    
    }
    if(event.GetId()==wxID_CANCEL)
	{
        this->EndModal(wxID_CANCEL);
    }
}

InsProvFz::~InsProvFz()
{
}    
/*
Dialog - InsProvFz - end
*/

/*
Dialog - PoiskToDialog - start
*/
BEGIN_EVENT_TABLE(PoiskToDialog,wxDialog)
    EVT_CHAR_HOOK(PoiskToDialog::OnChar) //отлавливаем нажатие клавиш
    EVT_SEARCHCTRL_CANCEL_BTN(wxID_PS_SEARCHCTRL_POISK, PoiskToDialog::ClearPoisk) //отлавливаем нажатие крестика в поле поиска
END_EVENT_TABLE()

PoiskToDialog::PoiskToDialog(wxWindow *parent, const wxString &caption, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    vert_bos = new wxBoxSizer(wxVERTICAL);
    hr_1 = new wxBoxSizer(wxHORIZONTAL);
    vert_1 = new wxBoxSizer(wxVERTICAL);
    wxString rboxName[] = {wxCAPTION_COLUMN_TO,wxCAPTION_COLUMN_INN,wxCAPTION_COLUMN_NET,wxCAPTION_COLUMN_SITE};
    wxString rboxType[] = {wxCAPTION_CTRL_CONTRAINS,wxCAPTION_CTRL_STARTS,wxCAPTION_CTRL_ENDS,wxCAPTION_CTRL_EQUAL,wxCAPTION_CTRL_NOTEQUAL};
    vert_1->Add(new wxRadioBox(this,wxID_PS_RADIOBOX_NAME,wxCAPTION_RADIOBOX_POLE,wxDefaultPosition,wxDefaultSize,sizeof(rboxName)/sizeof(wxString),rboxName,0,wxRA_SPECIFY_ROWS), 0, wxEXPAND,0);
    vert_1->Add(new wxRadioBox(this,wxID_PS_RADIOBOX_TYPE,wxCAPTION_RADIOBOX_TYPE,wxDefaultPosition,wxDefaultSize,sizeof(rboxType)/sizeof(wxString),rboxType,0,wxRA_SPECIFY_ROWS), 0, wxEXPAND,0);
    vert_bos->Add(new wxSearchCtrl(this,wxID_PS_SEARCHCTRL_POISK, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT), 0, wxEXPAND,0);
    ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK))->SetDescriptiveText(wxString("введите значение для поиска и нажмите Enter ...")); //текст по умолчанию в строке поиска
    ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK))->ShowCancelButton(1); //делаем активной кнопку отмены
    wxListView *listview = new wxListView(this, wxID_PS_LISTVIEW_RESULT,wxDefaultPosition,wxDefaultSize,wxLC_REPORT|wxLC_SINGLE_SEL);
    listview->InsertColumn(0,wxCAPTION_COLUMN_TO);
    listview->InsertColumn(1,wxCAPTION_COLUMN_INN);
    listview->InsertColumn(2,wxCAPTION_COLUMN_NET);
    listview->InsertColumn(3,wxCAPTION_COLUMN_SITE);
    listview->Connect(wxEVT_LEFT_DCLICK,wxMouseEventHandler(PoiskToDialog::DClickMouse));
    hr_1->Add(vert_1, 0, wxEXPAND,0);
    hr_1->Add(listview, 1, wxEXPAND,0);

    vert_bos->Add(hr_1, 0, wxEXPAND,0);
    this->SetSizerAndFit(vert_bos);
}

void PoiskToDialog::ClearPoisk (wxCommandEvent& event)
{
    ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK))->Clear(); //очищаем поле поиска
    
}

void PoiskToDialog::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    if(event.GetKeyCode()==13) //нажата кнопка Enter
    {
        wxSearchCtrl *searchCtrl = ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK));
        wxRadioBox   *radioBoxPole = ((wxRadioBox*)this->FindWindow(wxID_PS_RADIOBOX_NAME));
        wxRadioBox   *radioBoxType = ((wxRadioBox*)this->FindWindow(wxID_PS_RADIOBOX_TYPE));
        wxListView   *listview = ((wxListView*)this->FindWindow(wxID_PS_LISTVIEW_RESULT));
        if(!searchCtrl->IsEmpty())
        {
            wxString textPoisk = searchCtrl->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //удаляем в строке поиска пробелы справа и слева
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
                            listview->SetItem(i,l-1,row[l]);
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
    if(event.GetKeyCode()==WXK_ESCAPE) //нажата кнопка Esc
    {
        this->EndModal(wxID_CANCEL);
        event.Skip(false);
    }    
        else {event.Skip(true);}   
}
void PoiskToDialog::DClickMouse (wxMouseEvent& event)
{
    PoiskToDialog* thisWindow = (PoiskToDialog*)this->GetParent();
    ProvToFrm *parentWindow = (ProvToFrm*)thisWindow->GetParent();
    wxListView   *listview = ((wxListView*)thisWindow->FindWindow(wxID_PS_LISTVIEW_RESULT));
    int idItem = (int)listview->GetFirstSelected();
    if (idItem==-1) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,thisWindow); return;} 
    
     
    wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
    f->SetId(idItem); //устанавливаем позицию выбранного элемента
    f->SetColumn(1); //колонка наименованием ТО
    f->SetMask(wxLIST_MASK_TEXT); //возвращаем данные связанные с элементом
    listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
    ((wxTextCtrl*)parentWindow->FindWindow(wxID_TO_INN))->ChangeValue(f->GetText()); //пишем в текстовое поле родительского окна выбранный инн
    delete f; //удаляем объект
    wxCommandEvent event_local; //создаем объект класса событие
    event_local.SetId(wxID_BUTTON_INN_TO); //устанавливаем идентификатор связанный с этим событием
    event_local.SetEventType(wxEVT_COMMAND_BUTTON_CLICKED); //устанавливаем тип события
    parentWindow->ProcessWindowEventLocally(event_local); //запускаем для данного окна поиск подходящего обработчика для события event_local
    thisWindow->EndModal(wxID_OK);
    //event.Skip(false);
}
PoiskToDialog::~PoiskToDialog()
{
}    
/*
Dialog - PoiskToDialog - end
*/

/*
Dialog - UpdateCompanyDialog - start
*/
BEGIN_EVENT_TABLE(UpdateCompanyDialog,wxDialog)
    EVT_BUTTON (wxID_OK, UpdateCompanyDialog::OnButton)
END_EVENT_TABLE()

UpdateCompanyDialog::UpdateCompanyDialog(wxWindow *parent, int id_operation, const wxString &caption, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    id_opera=id_operation;
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr_1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr_2 = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *text1 = new wxStaticText(this, wxID_ANY, wxCAPTION_STATICTEXT_TYPE "*");
    wxStaticText *text2 = new wxStaticText(this, wxID_ANY, wxCAPTION_STATICTEXT_NAME "*");
    wxTextCtrl *textCtrl1 = new wxTextCtrl(this,wxID_C_DIL_TC_TYPE);
    wxTextCtrl *textCtrl2 = new wxTextCtrl(this,wxID_C_DIL_TC_NAME);
    
    wxString sqlText; sqlText<<wxSqlTextSelTypeCompany;
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
                HashTypeCompany[wxString(row[0])]=wxAtoi(row[1]); //добавляем в отображение ключ/значение
            }
        }
        mysql_free_result(res); // Очищаем результаты
    }
    wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
    for(register hash_map::iterator i = HashTypeCompany.begin();i!=HashTypeCompany.end();++i){LocArray.Add(i->first);}
    textCtrl1->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    
    if(id_operation==1) {this->SetLabel(wxCAPTION_DIALOG_1);} //меняем метку окна в зависимости от нажатой кнопки, создавшей диалог
    if(id_operation==2) 
    {
        this->SetLabel(wxCAPTION_DIALOG_2); //меняем метку окна в зависимости от нажатой кнопки, создавшей диалог
        ContactFrm *parentWindow = (ContactFrm*)this->GetParent();
        wxListView *listview_company = (wxListView*)parentWindow->FindWindow(wxID_C_LISTVIEW_SP_COMP);
        int item_sel = listview_company->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
        if(item_sel!=-1)
        {
            textCtrl1->ChangeValue(listview_company->GetItemText(item_sel,1));
            textCtrl2->ChangeValue(listview_company->GetItemText(item_sel,0));
        }
    }
    hr_1->Add(text1, 0, wxEXPAND,0);
    hr_1->Add(textCtrl1, 1, wxEXPAND,0);
    
    hr_2->Add(text2, 0, wxEXPAND,0);
    hr_2->Add(textCtrl2, 1, wxEXPAND,0);
    
    vert_bos->Add(hr_1, 0, wxEXPAND,0);
    vert_bos->Add(hr_2, 0, wxEXPAND,0);
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND,0);
    this->SetSizerAndFit(vert_bos);
    SetSize(400,-1);
}

void UpdateCompanyDialog::OnButton (wxCommandEvent &event)
{
    if(event.GetId()==wxID_OK)
	{
        
        int id_type=0;
        ContactFrm *parentWindow = (ContactFrm*)this->GetParent();
        wxListView *listview_company = (wxListView*)parentWindow->FindWindow(wxID_C_LISTVIEW_SP_COMP);
        wxString textType = ((wxTextCtrl*)this->FindWindow(wxID_C_DIL_TC_TYPE))->GetValue();
        wxString textName = ((wxTextCtrl*)this->FindWindow(wxID_C_DIL_TC_NAME))->GetValue();
        if(textType.IsEmpty()||textName.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}
        textType.MakeUpper(); 
        textName.Trim(true); textName.Trim(false);
        for(register hash_map::iterator i = HashTypeCompany.begin();i!=HashTypeCompany.end();++i)
        {
            wxString str = i->first; str.MakeUpper();
            if(!str.compare(textType)) {id_type=i->second;}
        }
        if(id_type==0) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        if(id_opera==1)
        {
        wxString sqlText = wxSqlTextInsNameCompany;
        sqlText<<textName; sqlText<<wxSqlLeftCaw;
        sqlText<<id_type; sqlText<<wxSqlEndRightBracketText;
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
        else
        {
            sqlText.Clear();
            sqlText<<wxSqlTextSelIDCompany; sqlText<<textName; sqlText<<wxSqlEndTextOrderByDescL;
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
                        int item_number = listview_company->GetItemCount(); //определяем номер последнего элемента для вставки нового
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                        f->SetColumn(0);
                        f->SetData(wxAtoi(row[0])); //прячем уникальный айди
                        f->SetId(item_number);
                        listview_company->InsertItem(*f); 
                        listview_company->SetItem(item_number,0,textName);
                        listview_company->SetItem(item_number,1,textType);
                        delete f;
                    //}
                }
                mysql_free_result(res); // Очищаем результаты
                for (register int i=0; i<(listview_company->GetColumnCount());++i) {listview_company->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента      
            }   
        }
        this->EndModal(wxID_OK);        
        }
        if(id_opera==2)
        {
            int item_sel = listview_company->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
            if(item_sel!=-1)
            {
            wxString sqlText = wxSqlTextUpdNameCompany;
            sqlText<<textName; sqlText<<wxSqlTextUpdNameCompany1;
            sqlText<<id_type; sqlText<<wxSqlTextUpdNameCompany2;
            sqlText<<(listview_company->GetItemData(item_sel)); sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
            else
            {
                listview_company->SetItemText(item_sel,textName);
                for(register hash_map::iterator i = HashTypeCompany.begin();i!=HashTypeCompany.end();++i)
                {
                    if(id_type==i->second) {listview_company->SetItem(item_sel,1,i->first); break;}
                }
            }
            }
        this->EndModal(wxID_OK); 
        }            
    }
}

UpdateCompanyDialog::~UpdateCompanyDialog()
{
}  

/*
Dialog - UpdateCompanyDialog - end
*/

/*
Dialog - UpdateCompanyDialog - start
*/
BEGIN_EVENT_TABLE(UpdateFioContactDialog,wxDialog)
    EVT_BUTTON (wxID_OK, UpdateFioContactDialog::OnButton)
    EVT_CHAR_HOOK(UpdateFioContactDialog::OnChar)
END_EVENT_TABLE()

UpdateFioContactDialog::UpdateFioContactDialog(wxWindow *parent, int id_operation, const wxString &caption, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
        : wxDialog (parent, id, caption, pos, size, style)
{
    id_opera=id_operation;
    wxBoxSizer *vert_bos = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hr_1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr_2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr_3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr_4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr_5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr_6 = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *text1 = new wxStaticText(this, wxID_ANY, wxCAPTION_STATICTEXT_FIO "*");
    wxStaticText *text2 = new wxStaticText(this, wxID_ANY, wxCAPTION_STATICTEXT_REGION);
    wxStaticText *text3 = new wxStaticText(this, wxID_ANY, wxCAPTION_STATICTEXT_PFONE "*");
    wxStaticText *text4 = new wxStaticText(this, wxID_ANY, wxCAPTION_STATICTEXT_DOB);
    wxStaticText *text5 = new wxStaticText(this, wxID_ANY, wxCAPTION_STATICTEXT_DOP_PFONE);
    wxStaticText *text6 = new wxStaticText(this, wxID_ANY, wxCAPTION_STATICTEXT_COMMENT);
    wxTextCtrl *textCtrl1 = new wxTextCtrl(this,wxID_K_DIL_TC_FIO);
    wxTextCtrl *textCtrl2 = new wxTextCtrl(this,wxID_K_DIL_TC_REG);
    wxTextCtrl *textCtrl3 = new wxTextCtrl(this,wxID_K_DIL_TC_PRONE);
    wxTextCtrl *textCtrl4 = new wxTextCtrl(this,wxID_K_DIL_TC_DOB);
    wxTextCtrl *textCtrl5 = new wxTextCtrl(this,wxID_K_DIL_TC_DOP_PF);
    wxTextCtrl *textCtrl6 = new wxTextCtrl(this,wxID_K_DIL_TC_COMMENT);
    
    wxString sqlText; 
    sqlText<<wxSqlTextSelNameRegion;
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
                wxString str; str=row[0]; str.MakeUpper();
                str.Trim(false); str.Trim(true); //ОЧЕНЬ ВНИМАТЕЛЬНО. В регионах контактов последний символ \n
                HashNameRegion[str]=wxAtoi(row[1]); //добавляем в отображение ключ/значение
            }
        }
        mysql_free_result(res); // Очищаем результаты
    }
    
    wxArrayString LocArray; //объявляем массив для автозаполнения в текстовом поле
    for(register hash_map::iterator i = HashNameRegion.begin();i!=HashNameRegion.end();++i){LocArray.Add(i->first);}
    textCtrl2->AutoComplete(LocArray); //подключаем к текстовому полю функцию автоматического завершения текста
    LocArray.Clear(); //Очищаем содержимое массива и освобождаем память
    
    if(id_operation==1) {this->SetLabel(wxCAPTION_DIALOG_3);} //меняем метку окна в зависимости от нажатой кнопки, создавшей диалог
    if(id_operation==2) 
    {
        this->SetLabel(wxCAPTION_DIALOG_4); //меняем метку окна в зависимости от нажатой кнопки, создавшей диалог
        ContactFrm *parentWindow = (ContactFrm*)this->GetParent();
        wxListView *listview_fio = (wxListView*)parentWindow->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
        int item_sel = listview_fio->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
        if(item_sel!=-1)
        {
            textCtrl1->ChangeValue(listview_fio->GetItemText(item_sel,0));
            textCtrl2->ChangeValue(listview_fio->GetItemText(item_sel,1));
            textCtrl3->ChangeValue(listview_fio->GetItemText(item_sel,2));
            textCtrl4->ChangeValue(listview_fio->GetItemText(item_sel,3));
            textCtrl5->ChangeValue(listview_fio->GetItemText(item_sel,4));
            wxString sqlText; sqlText<<wxSqlTextSelCommentContact;
            sqlText<<(listview_fio->GetItemData(item_sel)); sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
            else
            {
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                //int num_fields = mysql_num_fields(res); // количество полей
                int num_rows = mysql_num_rows(res); // и количество строк.
                if(num_rows>0)
                {   
                    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        textCtrl6->ChangeValue(row[0]);
                    }
                }
                mysql_free_result(res); // Очищаем результаты
            }
        }
    }
    hr_1->Add(text1, 0, wxEXPAND,0);
    hr_1->Add(textCtrl1, 1, wxEXPAND,0);
    
    hr_2->Add(text2, 0, wxEXPAND,0);
    hr_2->Add(textCtrl2, 1, wxEXPAND,0);
    
    hr_3->Add(text3, 0, wxEXPAND,0);
    hr_3->Add(textCtrl3, 1, wxEXPAND,0);
    
    hr_4->Add(text4, 0, wxEXPAND,0);
    hr_4->Add(textCtrl4, 1, wxEXPAND,0);
    
    hr_5->Add(text5, 0, wxEXPAND,0);
    hr_5->Add(textCtrl5, 1, wxEXPAND,0);
    
    hr_6->Add(text6, 0, wxEXPAND,0);
    hr_6->Add(textCtrl6, 1, wxEXPAND,0);
    
    vert_bos->Add(hr_1, 0, wxEXPAND,0);
    vert_bos->Add(hr_2, 0, wxEXPAND,0);
    vert_bos->Add(hr_3, 0, wxEXPAND,0);
    vert_bos->Add(hr_4, 0, wxEXPAND,0);
    vert_bos->Add(hr_5, 0, wxEXPAND,0);
    vert_bos->Add(hr_6, 0, wxEXPAND,0);
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND,0);
    this->SetSizerAndFit(vert_bos);
    SetSize(400,-1);
}

void UpdateFioContactDialog::OnButton (wxCommandEvent &event)
{
    if(event.GetId()==wxID_OK)
	{
        
        int id_reg=0;
        ContactFrm *parentWindow = (ContactFrm*)this->GetParent();
        wxListView *listview_company = (wxListView*)parentWindow->FindWindow(wxID_C_LISTVIEW_SP_COMP);
        wxListView *listview_fio = (wxListView*)parentWindow->FindWindow(wxID_C_LISTVIEW_FIO_CONTACT);
        int item_sel = listview_company->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
        if(item_sel!=-1)
        {
        int id_company=(listview_company->GetItemData(item_sel));
        wxString textFio = ((wxTextCtrl*)this->FindWindow(wxID_K_DIL_TC_FIO))->GetValue();
        wxString textReg = ((wxTextCtrl*)this->FindWindow(wxID_K_DIL_TC_REG))->GetValue();
        wxString textTel = ((wxTextCtrl*)this->FindWindow(wxID_K_DIL_TC_PRONE))->GetValue();
        wxString textDob = ((wxTextCtrl*)this->FindWindow(wxID_K_DIL_TC_DOB))->GetValue();
        wxString textDopTel = ((wxTextCtrl*)this->FindWindow(wxID_K_DIL_TC_DOP_PF))->GetValue();
        wxString textComment = ((wxTextCtrl*)this->FindWindow(wxID_K_DIL_TC_COMMENT))->GetValue();
        if(textFio.IsEmpty()||textTel.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}
        if(!textFio.IsEmpty()) {textFio.Trim(true); textFio.Trim(false);}
        if(!textReg.IsEmpty()) {textReg.Trim(true); textReg.Trim(false); textReg.MakeUpper();} else {textReg=wxNOT_DATA;}
        if(!textTel.IsEmpty()) {textTel.Trim(true); textTel.Trim(false);}
        if(!textDob.IsEmpty()) {textDob.Trim(true); textDob.Trim(false);} //else {textDob=wxSQL_DEFAULT;}
        if(!textDopTel.IsEmpty()) {textDopTel.Trim(true); textDopTel.Trim(false);} //else {textDopTel=wxSQL_DEFAULT;}
        if(!textComment.IsEmpty()) {textComment.Trim(true); textComment.Trim(false);} //else {textComment=wxSQL_DEFAULT;}
        
        for(register hash_map::iterator i = HashNameRegion.begin();i!=HashNameRegion.end();++i)
        {
            if(!textReg.compare(i->first)) {id_reg=i->second; break;}
        }
        if(id_reg==0) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        if(id_opera==1)
        {
        wxString sqlText = wxSqlTextInsNameContact;
        sqlText<<id_company; sqlText<<wxSqlCommaText;
        sqlText<<id_reg; sqlText<<wxSqlCommaText;
        sqlText<<wxSqlCharStr; sqlText<<textFio; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;
        sqlText<<wxSqlCharStr; sqlText<<textTel; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;
        
        if(!textDob.IsEmpty()) {sqlText<<wxSqlCharStr; sqlText<<textDob; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;} else {sqlText<<wxSQL_DEFAULT; sqlText<<wxSqlCommaText;}
        if(!textDopTel.IsEmpty()) {sqlText<<wxSqlCharStr; sqlText<<textDopTel; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;} else {sqlText<<wxSQL_DEFAULT; sqlText<<wxSqlCommaText;}
        if(!textComment.IsEmpty()) {sqlText<<wxSqlCharStr; sqlText<<textComment; sqlText<<wxSqlCharStr; sqlText<<wxSqlEndRightBracketText;} else {sqlText<<wxSQL_DEFAULT; sqlText<<wxSqlEndRightBracketText;}
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
        else
        {
            sqlText.Clear();
            sqlText<<wxSqlTextSelIDContact; sqlText<<id_company; sqlText<<wxSqlAnd;
            sqlText<<wxSqlTextSelIDContactW1; sqlText<<textFio; sqlText<<wxSqlCharStr; sqlText<<wxSqlAnd;
            sqlText<<wxSqlTextSelIDContactW2; sqlText<<textTel; sqlText<<wxSqlEndTextOrderByDescL;
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
                        int item_number = listview_fio->GetItemCount(); //определяем номер последнего элемента для вставки нового
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                        f->SetColumn(0);
                        f->SetData(wxAtoi(row[0])); //прячем уникальный айди
                        f->SetId(item_number);
                        listview_fio->InsertItem(*f); 
                        listview_fio->SetItem(item_number,0,textFio);
                        listview_fio->SetItem(item_number,1,textReg);
                        listview_fio->SetItem(item_number,2,textTel);
                        listview_fio->SetItem(item_number,3,textDob);
                        listview_fio->SetItem(item_number,4,textDopTel);
                        delete f;
                    //}
                }
                mysql_free_result(res); // Очищаем результаты
                for (register int i=0; i<(listview_fio->GetColumnCount());++i) {listview_fio->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента      
            }   
        }
        this->EndModal(wxID_OK);        
        }
        if(id_opera==2)
        {
            int item_sel_cont = listview_fio->GetNextItem((-1), wxLIST_NEXT_ALL,wxLIST_STATE_FOCUSED);
            if(item_sel_cont!=-1)
            {
                wxString sqlText = wxSqlTextUpdIDContact;
                sqlText<<id_reg; sqlText<<wxSqlTextUpdIDContact1;
                sqlText<<textFio; sqlText<<wxSqlTextUpdIDContact2;
                sqlText<<textTel; sqlText<<wxSqlTextUpdIDContact3;
                if(!textDob.IsEmpty()) {sqlText<<wxSqlCharStr; sqlText<<textDob; sqlText<<wxSqlCharStr; sqlText<<wxSqlTextUpdIDContact4;} else {sqlText<<wxSQL_DEFAULT; sqlText<<wxSqlTextUpdIDContact4;}
                if(!textDopTel.IsEmpty()) {sqlText<<wxSqlCharStr; sqlText<<textDopTel; sqlText<<wxSqlCharStr; sqlText<<wxSqlTextUpdIDContact5;} else {sqlText<<wxSQL_DEFAULT; sqlText<<wxSqlTextUpdIDContact5;}
                if(!textComment.IsEmpty()) {sqlText<<wxSqlCharStr; sqlText<<textComment; sqlText<<wxSqlCharStr; sqlText<<wxSqlTextUpdIDContact6;} else {sqlText<<wxSQL_DEFAULT; sqlText<<wxSqlTextUpdIDContact6;}
                sqlText<<(listview_fio->GetItemData(item_sel_cont)); sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else
                {
                    listview_fio->SetItemText(item_sel_cont,textFio);
                    listview_fio->SetItem(item_sel_cont,1,textReg);
                    listview_fio->SetItem(item_sel_cont,2,textTel);
                    listview_fio->SetItem(item_sel_cont,3,textDob);
                    listview_fio->SetItem(item_sel_cont,4,textDopTel);
                    for (register int i=0; i<(listview_fio->GetColumnCount());++i) {listview_fio->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента       
                }
            }
        this->EndModal(wxID_OK); 
        }}            
    }
}
void UpdateFioContactDialog::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    switch(event.GetId())
    {
        case wxID_K_DIL_TC_PRONE: //запрещаем в поле с ИНН вводить символы отличные от цифр
        case wxID_K_DIL_TC_DOB: //запрещаем в поле с ИНН вводить символы отличные от цифр
        case wxID_K_DIL_TC_DOP_PF: //запрещаем в поле с ИНН вводить символы отличные от цифр
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //если зажат шифт, контрл или альт, то отправляем событие вверх к родителю
                {event.Skip(true);} 
                else {
                    if((event.GetKeyCode()>=32&&event.GetKeyCode()<=47)||(event.GetKeyCode()>=58&&event.GetKeyCode()<=255&&event.GetKeyCode()!=127)) //если нажатая кнопка попала в диапазоны, то не пропускаем событие вверх к родителю
                        {event.Skip(false);}
                    else {event.Skip(true);}
                }
                break;
            }
        default:{event.Skip(true); break;}
    }
}
UpdateFioContactDialog::~UpdateFioContactDialog()
{
}  

/*
Dialog - UpdateFioContactDialog - end
*/
