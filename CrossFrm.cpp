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
	EVT_TIMER(wxID_TIMER, CrossFrm::OnTimer) //�������� ������������� ������� � ������� ������
END_EVENT_TABLE()

////Event Table End

extern void CreateSpravochnic();    //������� �������� ������������
extern void DeleteSpravochnic ();   //������� ������� �������� ��� �����������
extern void CreatePrivelege();
/*
extern MacroregArray MyMacroregArray; //������ �����������
extern OcArray MyOcArray; //������ ��
extern GcArray MyGcArray; //������ ��
extern HolidayTypeArray MyHolidayTypeArray; //������ ������ ����������
extern BrandNameArray MyBrandNameArray; //������ ������������ �����/�������
extern BrandTypeArray MyBrandTypeArray; //������ ����� �����/�������
extern UkRfArray MyUkRfArray; //������ ������ �� ��
extern FioSbArray MyFioSbArray; //������ ��� ����������� �� ��
extern RezProvArray MyRezProvArray; //������ ��������� ��������
extern ProdGroupArray MyProdGroupArray; //������ ������ ���������
extern ProdNameArray MyProdNameArray; //������ ������������ �������� ���������
extern DolznostArray MyDolznostArray; //������ ���������
extern SovetnicArray MySovetnicArray; //������ ���������
extern TechCentrArray MyTechCentrArray; //������ ������ ���������
extern SovConnectRegArray MySovConnectRegArray; //������ ����� �� � ���������
extern TypeProvArray MyTypeProvArray; //������ ��� ��������
extern RootInfoArray MyRootInfoArray; //������ �������� ������ ������ ������ ��
extern PositionSotrHistoryArray MyPositionSotrHistoryArray; //������ ������ ���������� � ���������
extern PositionSotrArray MyPositionSotrArray; //������ ������ ���������� � ���������
extern TypeCooperationArray MyTypeCooperationArray; //������ ����� ��������������
extern PrivilegeUserArray MyPrivilegeUserArray; //������ ����������� �������� �����������
*/

CrossFrm::CrossFrm(const wxString& title)
	: wxFrame(NULL, wxID_WINDOW_BOS, title, wxDefaultPosition, wxSize(0, 0),wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxCLIP_CHILDREN|wxMINIMIZE_BOX)
	, m_timer(this, wxID_TIMER) //������ ������ � �������� ��� � ������������ �����
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
        EnterPassword EntPas(this, wxID_ANY); //������� ���������� ���� � �������� �����,��,������,������
        if(EntPas.ShowModal () == wxID_CANCEL) {this->Destroy();} //���� ���� ����� ������ "������", �� ��������� �����
        else{
            if(flag_conn_mysql==1) {mysql_close(conn); this->Destroy();} //��������� ���� ����������� � ��. ���� ���� =1, �� � �� �� ������� ������������ ������������� ��������� �����.
            else
            {
                mysql_query (conn,"SET character_set_results='cp1251'"); /*������������� ��������� ������ ������������ � �������*/
                mysql_query (conn,"SET character_set_client='cp1251'");  /*������������� ��������� ������ ������������ �� �������*/
                mysql_query (conn,"SET character_set_connection='utf8'"); /*������������� ���������, � ������� ������������� ���������� ��������� �� �������, ����� ����������� ������� �� �������.*/
                //wxLocale m_locale;
                //m_locale.Init(wxLANGUAGE_RUSSIAN);
                CreateSpravochnic();    //��������� �����������
                CreatePrivelege();      //��������� ���������� ������������ (������������ �� ������ ������������
                m_timer.Start(60*60*1000); // ��������� ��� ��� ������� ������ ���������� � �������� (1000=1�������)           
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
	            wxMenuItem *contactTel = file_menu->Append(wxID_CONTACT_TEL, "&�������� ������", "���������� ����������");
                file_menu->AppendSeparator();
	            file_menu->Append(wxID_EXIT, "&�����\t ALT+F4", "����� �� ���������");
	            wxMenuItem *formProv = sub_prov_menu->Append(wxID_PPOVERKI_AUI, "&��������", "����� ����� ������ ��������");
	            wxMenuItem *formHold = sub_prov_menu->Append(wxID_HOLIDAY_FRM, "&������", "����� ����� ������ � ��������/������ ���������� ����������");
	            //sub_prov_menu->Append(wxID_PPOVERKI_AG_MENU, "&�����", "����� ����� ������ �������� ������");
	            wxMenuItem *menuAdm = sub_prov_menu_instument->Append(wxID_SETTINGS_ADMIN_BD, "&�����������������");
	            //sub_prov_menu_instument->Append(wxID_SETTINGS_MYSQL_PING, "&�������� ����������");
	            wxMenuItem *menuUpd = sub_prov_menu_instument->Append(wxID_SETTINGS_UPDATE_SPR, "&�������� �����������");
	            wxMenuItem *menuFc = sub_prov_menu_instument->Append(wxID_SETTINGS_COMMENT_MENU, "&������� �����������");
	            wxMenuItem *menuBl = sub_prov_menu_instument->AppendCheckItem(wxID_SETTINGS_FLAG_BL_SB_MENU, "&�������������� �������� �� �� ��");
	            wxMenuItem *menuOt = sub_prov_menu_otchet->Append(wxID_SETTINGS_OTCHET_PROV, "&��������");
	            wxMenuItem *menuSv = sub_prov_menu_otchet->Append(wxID_SETTINGS_OTCHET_SOV, "&���������");
	            command_menu->AppendSubMenu(sub_prov_menu, "&������� �����");
	            command_menu->AppendSubMenu(sub_prov_menu_otchet, "&������");
	            command_menu->AppendSubMenu(sub_prov_menu_instument, "&���������");
	            help_menu->Append(wxID_ABOUT_MENU, "&� ���������", "���������� ����������");
	            menubar->Append(file_menu, "&����");
	            menubar->Append(command_menu, "&�� ��");
	            menubar->Append(help_menu, "&�������");
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
	            SetStatusText("������");
	            int menu_height = wxSystemSettings::GetMetric(wxSYS_MENU_Y);
	            SetClientSize(300,0);
	            
	            /*��������� �� ini-����� ����������� �����������*/
                wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
                wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
                config->Read("/STRONG_OPTION/fastcomment", &fastComment,""); //���� �� ������� ������� ��������, �� ����������� ���������� ""
                config->Read("/STRONG_OPTION/auto_bl_sb", &flag_bl_sb,0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
                if(flag_bl_sb) {command_menu->Check(wxID_SETTINGS_FLAG_BL_SB_MENU,true);} else {command_menu->Check(wxID_SETTINGS_FLAG_BL_SB_MENU,false);}
                config->Flush();
                delete config;
                flag_timer_fast=0;    
                int flag_priv = 0;          
                for(register int i =0; i<MyPrivilegeUserArray.GetCount();++i)   //������ ���������� ������� ���� � ����������� �� ���������� ������������
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
                if(flag_priv==0) //���� ������������ �� ��������� ������ ����������
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
        m_timer.Start(60*60*1000); //�������� ������ 60 �����
        flag_timer_fast=0;
        return;
    }
    wxString sqlText, strTextInfo, srtListModSpr;
    int flag = 0;
    sqlText=wxSqlTextSprMacroregP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyMacroregArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr="MyMacroregArray";} else {srtListModSpr=", MyMacroregArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextSprOcP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyOcArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyOcArray";} else {srtListModSpr+=", MyOcArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextSprGcP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyGcArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyGcArray";} else {srtListModSpr+=", MyGcArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextSprHolidayP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyHolidayTypeArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyHolidayTypeArray";} else {srtListModSpr+=", MyHolidayTypeArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextBrandNameP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyBrandNameArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyBrandNameArray";} else {srtListModSpr+=", MyBrandNameArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextBrandTypeP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyBrandTypeArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyBrandTypeArray";} else {srtListModSpr+=", MyBrandTypeArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextUkP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyUkRfArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyUkRfArray";} else {srtListModSpr+=", MyUkRfArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextFioSbP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyFioSbArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyFioSbArray";} else {srtListModSpr+=", MyFioSbArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextRezProvP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyRezProvArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyRezProvArray";} else {srtListModSpr+=", MyRezProvArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextProdGroupP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyProdGroupArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyProdGroupArray";} else {srtListModSpr+=", MyRezProvArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextProdNameP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyProdNameArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyProdNameArray";} else {srtListModSpr+=", MyProdNameArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextDolznostP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyDolznostArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyDolznostArray";} else {srtListModSpr+=", MyDolznostArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextSovetnicP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MySovetnicArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MySovetnicArray";} else {srtListModSpr+=", MySovetnicArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextTechCentrP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyTechCentrArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyTechCentrArray";} else {srtListModSpr+=", MyTechCentrArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextSovConnectRegP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MySovConnectRegArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MySovConnectRegArray";} else {srtListModSpr+=", MySovConnectRegArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextTypeProvP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyTypeProvArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyTypeProvArray";} else {srtListModSpr+=", MyTypeProvArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextRootInfoP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyRootInfoArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyRootInfoArray";} else {srtListModSpr+=", MyRootInfoArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextPositionSotrHistoryP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyPositionSotrHistoryArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyPositionSotrHistoryArray";} else {srtListModSpr+=", MyPositionSotrHistoryArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextPositionSotrP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyPositionSotrArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyPositionSotrArray";} else {srtListModSpr+=", MyPositionSotrArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextTypeCooperationP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyTypeCooperationArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyTypeCooperationArray";} else {srtListModSpr+=", MyTypeCooperationArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    sqlText.Clear();
    sqlText=wxSqlTextInitiatorChecksP;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
            if((MyInitiatorChecksArray.GetCount())!=wxAtoi(row[0])) {++flag; if(srtListModSpr.IsEmpty()) {srtListModSpr+="MyInitiatorChecksArray";} else {srtListModSpr+=", MyInitiatorChecksArray";}}                 
        }
        mysql_free_result(res); // ������� ����������
    }
    if(flag>0)
    {
        strTextInfo="���� ������ ���� ���������. "; strTextInfo<<"��������� ����������� ������������, ������������ � ���������, ��������";
        strTextInfo<<"\n��������: "; strTextInfo<<srtListModSpr;
        strTextInfo<<"\n��� ���������� ������ ���������� �������� �����������.";
        wxNotificationMessage NotifiMes;
        NotifiMes.SetFlags(wxICON_WARNING);
        NotifiMes.SetMessage(strTextInfo);
        NotifiMes.SetTitle(wxATTENTION);
        NotifiMes.Show();
        NotifiMes.Close();
        if(flag_timer_fast==0)
        {
            m_timer.Stop();
            m_timer.Start(10*60*1000); //�������� ������ 10 �����
            flag_timer_fast=1;
        }
    }
}

CrossFrm::~CrossFrm()
{
    
}

void CrossFrm::OnClose(wxCloseEvent& event)
{
	wxMessageDialog *dial = new wxMessageDialog(NULL,"�� ������������� ������ ������� ���������?", "������������� ��������",wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
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
        
        //��������� �� ����� ������������ ������� ���������� ��������� ����.
        //���� ����� �� ����������, ��� ��������� ��������� �� ���������
        
        long x = config->ReadLong("/FORM_HOLIDAY/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
        long y = config->ReadLong("/FORM_HOLIDAY/y", 0);
        long width = config->ReadLong("/FORM_HOLIDAY/width", 0);
        long height = config->ReadLong("/FORM_HOLIDAY/height", 0);
        if(width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_HOL_P))) {HolidayFrm* frame = new HolidayFrm(this,wxID_WINDOW_HOL_P, wxCAPTION_ACCHOLD,wxPoint(x,y),wxSize(width,height)); frame->Show();} //��������� ������� ���� � ��������������� 2. ���� ���� �� ����������, �� �������, ���� ����������, �� �� �������.
        }
        else {if (!(this->FindWindow(wxID_WINDOW_HOL_P))) {HolidayFrm* frame = new HolidayFrm(this,wxID_WINDOW_HOL_P); frame->Show();}} //��������� ������� ���� � ��������������� 2. ���� ���� �� ����������, �� �������, ���� ����������, �� �� �������.}
        config->Flush();
        delete config;
    }
    
    if (event.GetId()==wxID_PPOVERKI_AUI)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //��������� �� ����� ������������ ������� ���������� ��������� ����.
        //���� ����� �� ����������, ��� ��������� ��������� �� ���������
        
        long x = config->ReadLong("/FORM_AUI_WORKPANEL/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
        long y = config->ReadLong("/FORM_AUI_WORKPANEL/y", 0);
        long width = config->ReadLong("/FORM_AUI_WORKPANEL/width", 0);
        long height = config->ReadLong("/FORM_AUI_WORKPANEL/height", 0);
        if(width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_AUI_W_P))) {wxAuiWorkPanel* frame = new wxAuiWorkPanel(this,wxID_WINDOW_AUI_W_P, wxCAPTION_ACCDATA,wxPoint(x,y),wxSize(width,height)); frame->Show();} //��������� ������� ���� � ��������������� 2. ���� ���� �� ����������, �� �������, ���� ����������, �� �� �������.
        }
        else {if (!(this->FindWindow(wxID_WINDOW_AUI_W_P))) {wxAuiWorkPanel* frame = new wxAuiWorkPanel(this,wxID_WINDOW_AUI_W_P); frame->Show();}} //��������� ������� ���� � ��������������� 2. ���� ���� �� ����������, �� �������, ���� ����������, �� �� �������.}
        config->Flush();
        delete config;
    }
    if (event.GetId()==wxID_CONTACT_TEL)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        /*
        ��������� �� ����� ������������ ������� ���������� ��������� ����.
        ���� ����� �� ����������, ��� ��������� ��������� �� ���������
        */
        long x = config->ReadLong("/FORM_CONTACT/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
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
        DeleteSpravochnic(); //������� ������� ������������
        CreateSpravochnic(); //��������� ������� ������������
        if(flag_timer_fast==1) {flag_timer_fast=2;}
        InformationSleep (wxINFO_UPD_SPR, sec_for_sleep_window_info, this); //������� �������������� ��������� ��� ������������
    }
    if (event.GetId()==wxID_SETTINGS_ADMIN_BD)
	{ 
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //��������� �� ����� ������������ ������� ���������� ��������� ����.
        //���� ����� �� ����������, ��� ��������� ��������� �� ���������
        
        long x = config->ReadLong("/FORM_ADMIN_BD/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
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
        ��������� �� ����� ������������ ������� ���������� ��������� ����.
        ���� ����� �� ����������, ��� ��������� ��������� �� ���������
        */
        long x = config->ReadLong("/FORM_SOVETNIC/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
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
        ��������� �� ����� ������������ ������� ���������� ��������� ����.
        ���� ����� �� ����������, ��� ��������� ��������� �� ���������
        */
        long x = config->ReadLong("/FORM_OTCHET_FAST/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
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
        fastComment = wxGetTextFromUser(wxINFO_FASTCOMMENT, wxCAPTION_FAST_COMMENT, fastComment, this); //������� ����������� ���������� ���� ������������� � ������������ ��������� ������
        /*����� ����� ��������� ������ � ���-����*/
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        config->Write( wxT("/STRONG_OPTION/fastcomment"), fastComment);
        config->Flush();
        delete config;
    }
	if (event.GetId()==wxID_ABOUT_MENU)
	{
        wxAboutDialogInfo aboutInfo;
        aboutInfo.SetName("������");
        aboutInfo.SetVersion("0.1");
        aboutInfo.SetDescription("��������� ����� �������� �������� ����������� � �������.");
        aboutInfo.SetCopyright("(C) 2015-2016");
        wxDir dir(wxGetCwd());
        wxString str_full, str_first, str_last;
        str_first = dir.GetName(); str_last= wxTRASH_EMPTY_ICO; str_full=str_first; str_full+=str_last;
        aboutInfo.SetIcon(wxIcon(str_full,wxBITMAP_TYPE_ICO ));
        aboutInfo.SetWebSite("http://pochtabank.ru");
        aboutInfo.AddDeveloper("���������� ����� ������ ������������: \n���������� - ������� ������� ����������\n����������� - ������� ������� ����������");
        wxAboutBox(aboutInfo);
    }
   /* if (event.GetId()==wxID_PPOVERKI_TO_MENU)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //��������� �� ����� ������������ ������� ���������� ��������� ����.
        //���� ����� �� ����������, ��� ��������� ��������� �� ���������
        
        long x = config->ReadLong("/FORM_TO/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
        long y = config->ReadLong("/FORM_TO/y", 0);
        long width = config->ReadLong("/FORM_TO/width", 0);
        long height = config->ReadLong("/FORM_TO/height", 0);
        if(x&&y&&width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_TO))) {ProvToFrm* frame_to = new ProvToFrm(this,wxID_WINDOW_TO,wxCAPTION_TO,wxPoint(x,y),wxSize(width,height)); frame_to->Show();} //��������� ������� ���� � ��������������� 2. ���� ���� �� ����������, �� �������, ���� ����������, �� �� �������.
        }
        else {if (!(this->FindWindow(wxID_WINDOW_TO))) {ProvToFrm* frame_to = new ProvToFrm(this,wxID_WINDOW_TO,wxCAPTION_TO); frame_to->Show();}} //��������� ������� ���� � ��������������� 2. ���� ���� �� ����������, �� �������, ���� ����������, �� �� �������.}
        config->Flush();
        delete config;
    }
    if (event.GetId()==wxID_PPOVERKI_AG_MENU)
	{
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        
        //��������� �� ����� ������������ ������� ���������� ��������� ����.
        //���� ����� �� ����������, ��� ��������� ��������� �� ���������
        
        long x = config->ReadLong("/FORM_AGENT/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
        long y = config->ReadLong("/FORM_AGENT/y", 0);
        long width = config->ReadLong("/FORM_AGENT/width", 0);
        long height = config->ReadLong("/FORM_AGENT/height", 0);
        if(x&&y&&width&&height)
        {
            if (!(this->FindWindow(wxID_WINDOW_AGENT))) {ProvAgFrm* frame_ag = new ProvAgFrm(this,wxID_WINDOW_AGENT,wxCAPTION_AGENT,wxPoint(x,y),wxSize(width,height)); frame_ag->Show();} //��������� ������� ���� � ��������������� 3. ���� ���� �� ����������, �� �������, ���� ����������, �� �� �������.
        }
        else {if (!(this->FindWindow(wxID_WINDOW_AGENT))) {ProvAgFrm* frame_ag = new ProvAgFrm(this); frame_ag->Show();}} //��������� ������� ���� � ��������������� 2. ���� ���� �� ����������, �� �������, ���� ����������, �� �� �������.}
        config->Flush();
        delete config;
    }*/
}

