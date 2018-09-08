///-----------------------------------------------------------------
///
/// @file      CrossFrm.cpp
/// @author    mishaninaa
/// Created:   07.07.2016 15:46:35
/// @section   DESCRIPTION
///            CrossFrm class implementation
///
///------------------------------------------------------------------

#include "CrossFrm.h"

extern MYSQL* conn;
int sec_for_sleep_window_info = wxID_SLEEP_DEFAULT;
extern void InformationSleep (wxString str, int sec, wxWindow * parent);

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// CrossFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++

////Event Table Start
BEGIN_EVENT_TABLE(CrossFrm,wxFrame)
	EVT_CLOSE(CrossFrm::OnClose)
	EVT_TIMER(wxID_TIMER, CrossFrm::OnTimer) //связываю идентификатор таймера с методом класса
END_EVENT_TABLE()

////Event Table End

extern void CreateSpravochnic();    //функция загрузки справочников
extern void DeleteSpravochnic ();   //функция очистки массивов под справочники
extern void CreatePrivelege();
/*
extern MacroregArray MyMacroregArray; //массив Макрорегион
extern OcArray MyOcArray; //массив ОЦ
extern GcArray MyGcArray; //массив ГЦ
extern HolidayTypeArray MyHolidayTypeArray; //массив причин отсутствия
extern BrandNameArray MyBrandNameArray; //массив наименования сетей/брендов
extern BrandTypeArray MyBrandTypeArray; //массив типов сетей/брендов
extern UkRfArray MyUkRfArray; //массив статей УК РФ
extern FioSbArray MyFioSbArray; //массив фио сотрудников СБ ГО
extern RezProvArray MyRezProvArray; //массив результат проверки
extern ProdGroupArray MyProdGroupArray; //массив группа продуктов
extern ProdNameArray MyProdNameArray; //массив наименование продукта продуктов
extern DolznostArray MyDolznostArray; //массив должности
extern SovetnicArray MySovetnicArray; //массив Советники
extern TechCentrArray MyTechCentrArray; //массив дерево техцентра
extern SovConnectRegArray MySovConnectRegArray; //массив связь гц и советника
extern TypeProvArray MyTypeProvArray; //массив тип проверки
extern RootInfoArray MyRootInfoArray; //массив источник данных черный список СБ
extern PositionSotrHistoryArray MyPositionSotrHistoryArray; //массив связей сотрудника и должности
extern PositionSotrArray MyPositionSotrArray; //массив связей сотрудника и должности
extern TypeCooperationArray MyTypeCooperationArray; //массив типов сотрудничества
extern PrivilegeUserArray MyPrivilegeUserArray; //массив инициаторов проверки контрагента
*/

CrossFrm::CrossFrm(const wxString& title)
	: wxFrame(NULL, wxID_WINDOW_BOS, title, wxDefaultPosition, wxSize(0, 0),wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxCLIP_CHILDREN|wxMINIMIZE_BOX)
	, m_timer(this, wxID_TIMER) //создаю таймер и связываю его с родительским окном
{
    wxImage::AddHandler(new wxICOHandler);
    
    wxDir dir(wxGetCwd());
    if (!dir.IsOpened())
    {
        wxMessageBox(wxERROR_OPEN_PROGRAM,wxERROR);
        Destroy();
    }
    else
    {
        EnterPassword EntPas(this, wxID_ANY); //создаем диалоговое окно с запросом хоста,бд,пароля,логина
        if(EntPas.ShowModal () == wxID_CANCEL) {this->Destroy();} //если юзер нажал кнопку "отмена", то разрушаем фрейм
        else{
            if(flag_conn_mysql==1) {mysql_close(conn); this->Destroy();} //проверяем флаг подключения к БД. Если флаг =1, то к БД не удалось подключиться следовательно закрываем прогу.
            else
            {
                mysql_query (conn,"SET character_set_results='cp1251'"); /*устанавливает кодировку данных отправляемых К клиенту*/
                mysql_query (conn,"SET character_set_client='cp1251'");  /*устанавливает кодировку данных отправляемых ОТ клиента*/
                mysql_query (conn,"SET character_set_connection='utf8'"); /*устанавливает кодировку, в которую преобразуется информация пришедшая от клиента, перед выполнением запроса на сервере.*/
                //wxLocale m_locale;
                //m_locale.Init(wxLANGUAGE_RUSSIAN);
                CreateSpravochnic();    //загружаем справочники
                CreatePrivelege();      //загружаем привилегии пользователя (вытягивается по логину пользователя
                m_timer.Start(60*60*1000); // определяю шаг для запуска метода связанного с таймером (1000=1секунда)           
                wxString str_full, str_first, str_last;
                str_first = dir.GetName(); str_last= wxTRASH_EMPTY_ICO; str_full=str_first; str_full+=str_last;
                SetIcon(wxIcon(str_full,wxBITMAP_TYPE_ICO ));
                menubar = new wxMenuBar;
	            file_menu = new wxMenu;
	            command_menu = new wxMenu;
	            help_menu = new wxMenu;
	            sub_prov_menu = new wxMenu;
	            sub_prov_menu_instument = new wxMenu;
	            sub_prov_menu_otchet = new wxMenu;
	            //file_menu->Append(wxID_TEST, "&test", "test");
	            wxMenuItem *contactTel = file_menu->Append(wxID_CONTACT_TEL, "&Контакты банков", "Телефонный справочник");
                file_menu->AppendSeparator();
	            file_menu->Append(wxID_EXIT, "&Выход\t ALT+F4", "Выйти из программы");
	            wxMenuItem *formProv = sub_prov_menu->Append(wxID_PPOVERKI_AUI, "&Проверки", "Форма ввода данных проверки");
	            wxMenuItem *formHold = sub_prov_menu->Append(wxID_HOLIDAY_FRM, "&Отпуск", "Форма ввода данных о причинах/сроках отсутствия сотрудника");
	            //sub_prov_menu->Append(wxID_PPOVERKI_AG_MENU, "&Агент", "Форма ввода данных проверки агента");
	            wxMenuItem *menuAdm = sub_prov_menu_instument->Append(wxID_SETTINGS_ADMIN_BD, "&Администрирование");
	            //sub_prov_menu_instument->Append(wxID_SETTINGS_MYSQL_PING, "&Проверка соединения");
	            wxMenuItem *menuUpd = sub_prov_menu_instument->Append(wxID_SETTINGS_UPDATE_SPR, "&Обновить справочники");
	            wxMenuItem *menuFc = sub_prov_menu_instument->Append(wxID_SETTINGS_COMMENT_MENU, "&Быстрый комментарий");
	            wxMenuItem *menuBl = sub_prov_menu_instument->AppendCheckItem(wxID_SETTINGS_FLAG_BL_SB_MENU, "&Автоматическая проверка по ЧС СБ");
	            wxMenuItem *menuOt = sub_prov_menu_otchet->Append(wxID_SETTINGS_OTCHET_PROV, "&Проверки");
	            wxMenuItem *menuSv = sub_prov_menu_otchet->Append(wxID_SETTINGS_OTCHET_SOV, "&Советники");
	            command_menu->AppendSubMenu(sub_prov_menu, "&Рабочие формы");
	            command_menu->AppendSubMenu(sub_prov_menu_otchet, "&Отчеты");
	            command_menu->AppendSubMenu(sub_prov_menu_instument, "&Настройки");
	            help_menu->Append(wxID_ABOUT_MENU, "&О программе", "Справочная информация");
	            menubar->Append(file_menu, "&Файл");
	            menubar->Append(command_menu, "&ЭО СБ");
	            menubar->Append(help_menu, "&Справка");
	            SetMenuBar(menubar);
	            Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnQuit));
	            Connect(wxID_ABOUT_MENU, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_PPOVERKI_AUI, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            //Connect(wxID_PPOVERKI_AG_MENU, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_SETTINGS_COMMENT_MENU, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_SETTINGS_FLAG_BL_SB_MENU, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_SETTINGS_OTCHET_PROV, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_SETTINGS_OTCHET_SOV, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_SETTINGS_UPDATE_SPR, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_SETTINGS_ADMIN_BD, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_CONTACT_TEL, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            Connect(wxID_HOLIDAY_FRM, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
	            
	            //Connect(wxID_TEST, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CrossFrm::OnWorkingMenu));
                
                CreateStatusBar();
	            SetStatusText("Готово");
	            int menu_height = wxSystemSettings::GetMetric(wxSYS_MENU_Y);
	            SetClientSize(300,0);
	            
	            /*Считываем из ini-файла стандартный комментарий*/
                wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
                wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
                config->Read("/STRONG_OPTION/fastcomment", &fastComment,""); //если не удалось считать параметр, то присваиваем переменной ""
                config->Read("/STRONG_OPTION/auto_bl_sb", &flag_bl_sb,0); //если не удалось считать параметр, то присваиваем переменной 0
                if(flag_bl_sb) {command_menu->Check(wxID_SETTINGS_FLAG_BL_SB_MENU,true);} else {command_menu->Check(wxID_SETTINGS_FLAG_BL_SB_MENU,false);}
                config->Flush();
                delete config;
                flag_timer_fast=0;    
                int flag_priv = 0;          
                for(register int i =0; i<MyPrivilegeUserArray.GetCount();++i)   //меняем активность пунктов меню в зависимости от привилегий пользователя
                {
                    if(MyPrivilegeUserArray.Item(i).name=="admin_global")
                    {
                        file_menu->Enable(wxID_CONTACT_TEL,true);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_ADMIN_BD,true);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_UPDATE_SPR,true);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_COMMENT_MENU,true);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_FLAG_BL_SB_MENU,true);
                        sub_prov_menu_otchet->Enable(wxID_SETTINGS_OTCHET_PROV,true);
                        sub_prov_menu_otchet->Enable(wxID_SETTINGS_OTCHET_SOV,true);
                        sub_prov_menu->Enable(wxID_PPOVERKI_AUI,true);
                        sub_prov_menu->Enable(wxID_HOLIDAY_FRM,true);
                        flag_priv=1;
                        break;
                    }
                    if(MyPrivilegeUserArray.Item(i).name=="admin_holiday")
                    {
                        file_menu->Enable(wxID_CONTACT_TEL,false);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_ADMIN_BD,false);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_UPDATE_SPR,true);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_COMMENT_MENU,false);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_FLAG_BL_SB_MENU,false);
                        sub_prov_menu_otchet->Enable(wxID_SETTINGS_OTCHET_PROV,false);
                        sub_prov_menu_otchet->Enable(wxID_SETTINGS_OTCHET_SOV,true);
                        sub_prov_menu->Enable(wxID_PPOVERKI_AUI,false);
                        sub_prov_menu->Enable(wxID_HOLIDAY_FRM,true);
                        flag_priv=1;
                        continue;
                    }
                }
                if(flag_priv==0) //если пользователю не назначена ниодна привилегия
                {
                    file_menu->Enable(wxID_CONTACT_TEL,false);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_ADMIN_BD,false);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_UPDATE_SPR,false);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_COMMENT_MENU,false);
                        sub_prov_menu_instument->Enable(wxID_SETTINGS_FLAG_BL_SB_MENU,false);
                        sub_prov_menu_otchet->Enable(wxID_SETTINGS_OTCHET_PROV,false);
                        sub_prov_menu_otchet->Enable(wxID_SETTINGS_OTCHET_SOV,false);
                        sub_prov_menu->Enable(wxID_PPOVERKI_AUI,false);
                        help_menu->Enable(wxID_ABOUT_MENU,false);
                        sub_prov_menu->Enable(wxID_HOLIDAY_FRM,false);
                }
                Center();
            }
        }
    }
}

void CrossFrm::OnTimer(wxTimerEvent& event)
{
    if(flag_timer_fast==2)
    {
        m_timer.Stop();
        m_timer.Start(60*60*1000); //интервал каждые 60 минут
        flag_timer_fast=0;
        return;
    }
    wxString sqlText, strTextInfo, srtListModSpr;
    int flag = 0;
    sqlText=wxSqlTextSprMacroregP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyMacroregArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr="MyMacroregArray";} else {srtListModSpr=", MyMacroregArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextSprOcP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyOcArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyOcArray";} else {srtListModSpr+=", MyOcArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextSprGcP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyGcArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyGcArray";} else {srtListModSpr+=", MyGcArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextSprHolidayP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyHolidayTypeArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyHolidayTypeArray";} else {srtListModSpr+=", MyHolidayTypeArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextBrandNameP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyBrandNameArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyBrandNameArray";} else {srtListModSpr+=", MyBrandNameArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextBrandTypeP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyBrandTypeArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyBrandTypeArray";} else {srtListModSpr+=", MyBrandTypeArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextUkP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyUkRfArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyUkRfArray";} else {srtListModSpr+=", MyUkRfArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextFioSbP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyFioSbArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyFioSbArray";} else {srtListModSpr+=", MyFioSbArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextRezProvP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyRezProvArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyRezProvArray";} else {srtListModSpr+=", MyRezProvArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextProdGroupP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyProdGroupArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyProdGroupArray";} else {srtListModSpr+=", MyRezProvArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextProdNameP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyProdNameArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyProdNameArray";} else {srtListModSpr+=", MyProdNameArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextDolznostP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyDolznostArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyDolznostArray";} else {srtListModSpr+=", MyDolznostArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextSovetnicP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MySovetnicArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MySovetnicArray";} else {srtListModSpr+=", MySovetnicArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextTechCentrP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyTechCentrArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyTechCentrArray";} else {srtListModSpr+=", MyTechCentrArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextSovConnectRegP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MySovConnectRegArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MySovConnectRegArray";} else {srtListModSpr+=", MySovConnectRegArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextTypeProvP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyTypeProvArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyTypeProvArray";} else {srtListModSpr+=", MyTypeProvArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextRootInfoP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyRootInfoArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyRootInfoArray";} else {srtListModSpr+=", MyRootInfoArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextPositionSotrHistoryP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyPositionSotrHistoryArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyPositionSotrHistoryArray";} else {srtListModSpr+=", MyPositionSotrHistoryArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextPositionSotrP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyPositionSotrArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyPositionSotrArray";} else {srtListModSpr+=", MyPositionSotrArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextTypeCooperationP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyTypeCooperationArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyTypeCooperationArray";} else {srtListModSpr+=", MyTypeCooperationArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    sqlText.Clear();
    sqlText=wxSqlTextInitiatorChecksP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            if((MyInitiatorChecksArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyInitiatorChecksArray";} else {srtListModSpr+=", MyInitiatorChecksArray";}}                 
        }
        mysql_free_result(res); // Очищаем результаты
    }
    if(flag>0)
    {
        strTextInfo="База данных была обновлена. "; strTextInfo<<"Несколько виртуальных справочников, используемых в программе, устарели";
        strTextInfo<<"\nУстарели: "; strTextInfo<<srtListModSpr;
        strTextInfo<<"\nДля корректной работы необходимо обновить справочники.";
        wxNotificationMessage NotifiMes;
        NotifiMes.SetFlags(wxICON_WARNING);
        NotifiMes.SetMessage(strTextInfo);
        NotifiMes.SetTitle(wxATTENTION);
        NotifiMes.Show();
        NotifiMes.Close();
        if(flag_timer_fast==0)
        {
            m_timer.Stop();
            m_timer.Start(10*60*1000); //интервал каждые 10 минут
            flag_timer_fast=1;
        }
    }
}

CrossFrm::~CrossFrm()
{
    
}

void CrossFrm::OnClose(wxCloseEvent& event)
{
	wxMessageDialog *dial = new wxMessageDialog(NULL,"Вы действительно хотите закрыть программу?", "Подтверждение действия",wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
	int ret = dial->ShowModal();
	dial->Destroy();
	if (ret == wxID_YES) {
        mysql_close(conn);
		Destroy();
	} else {
		event.Veto();
	}
}
void CrossFrm::OnQuit(wxCommandEvent& event)
{
    mysql_close(conn);
	Destroy();
}
void CrossFrm::OnButton(wxCommandEvent& event)
{
	if (event.GetId()==10)
	{}
}

void CrossFrm::OnWorkingMenu(wxCommandEvent& event)
{
    /*if (event.GetId()==wxID_SETTINGS_MYSQL_PING)
	{
        switch (mysql_ping(conn))
        {
            case 0:
            {
                wxMessageBox("1");
                break;
            }
            case CR_COMMANDS_OUT_OF_SYNC:
            {
                wxMessageBox("2");
                break;
            }
            case CR_SERVER_GONE_ERROR:
            {
                wxMessageBox("3");
                break;
            }
            case CR_UNKNOWN_ERROR:
            {
                wxMessageBox("4");
                break;
            }
            default:break;
        }
    }*/
    
    if (event.GetId()==wxID_HOLIDAY_FRM)
	{
        
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //Считываем из файла конфигурация размеры последнего открытого окна.
        //Если файла не существует, про применяем параметры по умолчанию
        
        long x = config->ReadLong("/FORM_HOLIDAY/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_HOLIDAY/y", 0);
        long width = config->ReadLong("/FORM_HOLIDAY/width", 0);
        long height = config->ReadLong("/FORM_HOLIDAY/height", 0);
        if(width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_HOL_P))) {HolidayFrm* frame = new HolidayFrm(this,wxID_WINDOW_HOL_P, wxCAPTION_ACCHOLD,wxPoint(x,y),wxSize(width,height)); frame->Show();} //проверяем наличие окна с идентификатором 2. Если окно не существует, то создаем, есни существует, но не создаем.
        }
        else {if (!(this->FindWindow(wxID_WINDOW_HOL_P))) {HolidayFrm* frame = new HolidayFrm(this,wxID_WINDOW_HOL_P); frame->Show();}} //проверяем наличие окна с идентификатором 2. Если окно не существует, то создаем, есни существует, но не создаем.}
        config->Flush();
        delete config;
    }
    
    if (event.GetId()==wxID_PPOVERKI_AUI)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //Считываем из файла конфигурация размеры последнего открытого окна.
        //Если файла не существует, про применяем параметры по умолчанию
        
        long x = config->ReadLong("/FORM_AUI_WORKPANEL/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_AUI_WORKPANEL/y", 0);
        long width = config->ReadLong("/FORM_AUI_WORKPANEL/width", 0);
        long height = config->ReadLong("/FORM_AUI_WORKPANEL/height", 0);
        if(width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_AUI_W_P))) {wxAuiWorkPanel* frame = new wxAuiWorkPanel(this,wxID_WINDOW_AUI_W_P, wxCAPTION_ACCDATA,wxPoint(x,y),wxSize(width,height)); frame->Show();} //проверяем наличие окна с идентификатором 2. Если окно не существует, то создаем, есни существует, но не создаем.
        }
        else {if (!(this->FindWindow(wxID_WINDOW_AUI_W_P))) {wxAuiWorkPanel* frame = new wxAuiWorkPanel(this,wxID_WINDOW_AUI_W_P); frame->Show();}} //проверяем наличие окна с идентификатором 2. Если окно не существует, то создаем, есни существует, но не создаем.}
        config->Flush();
        delete config;
    }
    if (event.GetId()==wxID_CONTACT_TEL)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        /*
        Считываем из файла конфигурация размеры последнего открытого окна.
        Если файла не существует, про применяем параметры по умолчанию
        */
        long x = config->ReadLong("/FORM_CONTACT/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_CONTACT/y", 0);
        long width = config->ReadLong("/FORM_CONTACT/width", 0);
        long height = config->ReadLong("/FORM_CONTACT/height", 0);
        if(width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_CONTACT))) {ContactFrm* frame_contact = new ContactFrm(this,wxID_WINDOW_CONTACT,wxCAPTION_CONTACT_TEL,wxPoint(x,y),wxSize(width,height)); frame_contact->Show();}
        }
        else {if (!(this->FindWindow(wxID_WINDOW_CONTACT))) {ContactFrm* frame_contact = new ContactFrm(this); frame_contact->Show();}}
        config->Flush();
        delete config;
    }
    if (event.GetId()==wxID_SETTINGS_UPDATE_SPR)
	{ 
        DeleteSpravochnic(); //очищаем массивы справочников
        CreateSpravochnic(); //заполняем массивы справочников
        if(flag_timer_fast==1) {flag_timer_fast=2;}
        InformationSleep (wxINFO_UPD_SPR, sec_for_sleep_window_info, this); //выводим информационное сообщение для пользователя
    }
    if (event.GetId()==wxID_SETTINGS_ADMIN_BD)
	{ 
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //Считываем из файла конфигурация размеры последнего открытого окна.
        //Если файла не существует, про применяем параметры по умолчанию
        
        long x = config->ReadLong("/FORM_ADMIN_BD/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_ADMIN_BD/y", 0);
        long width = config->ReadLong("/FORM_ADMIN_BD/width", 0);
        long height = config->ReadLong("/FORM_ADMIN_BD/height", 0);
        if(width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_ADMIN))) {NotebookAdmin* frame_adm = new NotebookAdmin(this,wxID_WINDOW_ADMIN,wxCAPTION_ADMIN_BD,wxPoint(x,y),wxSize(width,height)); frame_adm->Show();}
        }
        else {if (!(this->FindWindow(wxID_WINDOW_ADMIN))) {NotebookAdmin* frame_adm = new NotebookAdmin(this,wxID_WINDOW_ADMIN,wxCAPTION_ADMIN_BD); frame_adm->Show();}}
        config->Flush();
        delete config;
        
    }
    if (event.GetId()==wxID_SETTINGS_OTCHET_SOV)
	{ 
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        /*
        Считываем из файла конфигурация размеры последнего открытого окна.
        Если файла не существует, про применяем параметры по умолчанию
        */
        long x = config->ReadLong("/FORM_SOVETNIC/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_SOVETNIC/y", 0);
        long width = config->ReadLong("/FORM_SOVETNIC/width", 0);
        long height = config->ReadLong("/FORM_SOVETNIC/height", 0);
        if(width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_SOVETNIK))) {NotebookSovetnik* frame_sovetnik = new NotebookSovetnik(this,wxID_WINDOW_SOVETNIK,wxCAPTION_SOVETNIK,wxPoint(x,y),wxSize(width,height)); frame_sovetnik->Show();}
        }
        else {if (!(this->FindWindow(wxID_WINDOW_SOVETNIK))) {NotebookSovetnik* frame_sovetnik = new NotebookSovetnik(this,wxID_WINDOW_SOVETNIK,wxCAPTION_SOVETNIK); frame_sovetnik->Show();}}
        config->Flush();
        delete config;
        
    }
    if (event.GetId()==wxID_SETTINGS_OTCHET_PROV)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        /*
        Считываем из файла конфигурация размеры последнего открытого окна.
        Если файла не существует, про применяем параметры по умолчанию
        */
        long x = config->ReadLong("/FORM_OTCHET_FAST/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_OTCHET_FAST/y", 0);
        long width = config->ReadLong("/FORM_OTCHET_FAST/width", 0);
        long height = config->ReadLong("/FORM_OTCHET_FAST/height", 0);
        if(width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_OTCHET))) {NotebookOtchet* frame_otchet = new NotebookOtchet(this,wxID_WINDOW_OTCHET,wxCAPTION_OTCHET,wxPoint(x,y),wxSize(width,height)); frame_otchet->Show();}
        }
        else {if (!(this->FindWindow(wxID_WINDOW_OTCHET))) {NotebookOtchet* frame_otchet = new NotebookOtchet(this,wxID_WINDOW_OTCHET,wxCAPTION_OTCHET); frame_otchet->Show();}}
        config->Flush();
        delete config;
    }
    if (event.GetId()==wxID_SETTINGS_FLAG_BL_SB_MENU)
	{ 
        if(command_menu->IsChecked(wxID_SETTINGS_FLAG_BL_SB_MENU))  {flag_bl_sb=1;} else {flag_bl_sb=0;}
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        config->Write( wxT("/STRONG_OPTION/auto_bl_sb"), flag_bl_sb);
        config->Flush();
        delete config;
    }
    if (event.GetId()==wxID_SETTINGS_COMMENT_MENU)
	{
        fastComment = wxGetTextFromUser(wxINFO_FASTCOMMENT, wxCAPTION_FAST_COMMENT, fastComment, this); //выводим стандартное диалоговое окно запрашивающее у пользователя текстовую строку
        /*пишем новую текстовую строку в ини-файл*/
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        config->Write( wxT("/STRONG_OPTION/fastcomment"), fastComment);
        config->Flush();
        delete config;
    }
	if (event.GetId()==wxID_ABOUT_MENU)
	{
        wxAboutDialogInfo aboutInfo;
        aboutInfo.SetName("УПТОиА");
        aboutInfo.SetVersion("0.1");
        aboutInfo.SetDescription("Программа учета проверок торговых организаций и агентов.");
        aboutInfo.SetCopyright("(C) 2015-2016");
        wxDir dir(wxGetCwd());
        wxString str_full, str_first, str_last;
        str_first = dir.GetName(); str_last= wxTRASH_EMPTY_ICO; str_full=str_first; str_full+=str_last;
        aboutInfo.SetIcon(wxIcon(str_full,wxBITMAP_TYPE_ICO ));
        aboutInfo.SetWebSite("http://pochtabank.ru");
        aboutInfo.AddDeveloper("Экспертный отдел Службы безопасности: \nАрхитектор - Ананьев Николай Николаевич\nРазработчик - Мишанин Алексей Алексеевич");
        wxAboutBox(aboutInfo);
    }
   /* if (event.GetId()==wxID_PPOVERKI_TO_MENU)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //Считываем из файла конфигурация размеры последнего открытого окна.
        //Если файла не существует, про применяем параметры по умолчанию
        
        long x = config->ReadLong("/FORM_TO/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_TO/y", 0);
        long width = config->ReadLong("/FORM_TO/width", 0);
        long height = config->ReadLong("/FORM_TO/height", 0);
        if(x&&y&&width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_TO))) {ProvToFrm* frame_to = new ProvToFrm(this,wxID_WINDOW_TO,wxCAPTION_TO,wxPoint(x,y),wxSize(width,height)); frame_to->Show();} //проверяем наличие окна с идентификатором 2. Если окно не существует, то создаем, есни существует, но не создаем.
        }
        else {if (!(this->FindWindow(wxID_WINDOW_TO))) {ProvToFrm* frame_to = new ProvToFrm(this,wxID_WINDOW_TO,wxCAPTION_TO); frame_to->Show();}} //проверяем наличие окна с идентификатором 2. Если окно не существует, то создаем, есни существует, но не создаем.}
        config->Flush();
        delete config;
    }
    if (event.GetId()==wxID_PPOVERKI_AG_MENU)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //Считываем из файла конфигурация размеры последнего открытого окна.
        //Если файла не существует, про применяем параметры по умолчанию
        
        long x = config->ReadLong("/FORM_AGENT/x", 0); //если не удалось считать параметр, то присваиваем переменной 0
        long y = config->ReadLong("/FORM_AGENT/y", 0);
        long width = config->ReadLong("/FORM_AGENT/width", 0);
        long height = config->ReadLong("/FORM_AGENT/height", 0);
        if(x&&y&&width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_AGENT))) {ProvAgFrm* frame_ag = new ProvAgFrm(this,wxID_WINDOW_AGENT,wxCAPTION_AGENT,wxPoint(x,y),wxSize(width,height)); frame_ag->Show();} //проверяем наличие окна с идентификатором 3. Если окно не существует, то создаем, есни существует, но не создаем.
        }
        else {if (!(this->FindWindow(wxID_WINDOW_AGENT))) {ProvAgFrm* frame_ag = new ProvAgFrm(this); frame_ag->Show();}} //проверяем наличие окна с идентификатором 2. Если окно не существует, то создаем, есни существует, но не создаем.}
        config->Flush();
        delete config;
    }*/
}

