#include "CrossFrm.h"

MYSQL* conn; //������� ������ MYSQL
int flag_conn_mysql=0; //���� ���������� � ��: 0 - �������, 1 - �� ������� (��������� �����������).
connect_user usr; //������� ������ ����� � �����������:����,��,�����,������
ListMatchFio listFio; //������ ������ � ������� ������� ��� ��������� ���������� �� ��� ��� ���������� �������� ���.����

extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;

extern void insertStrDateToCtrl (wxString& str, wxDatePickerCtrl* window);
extern void EditStringFio (wxString& str); //������� ����������� ������ wxString ����� ������ ���� �������� �� ������ �.�.
extern int proverka_bl_sb(MYSQL* conn, wxString& str, int type); //������� ��������� str �� ������� ������� � �� ��. type - ��� �� �� ��� ��������, 0 - ��, 1 - ������

/* ����������� ������� ������ ListMatchFio */
void ListMatchFio::Clear (void) //����� ������� ������-����� ������
{
    idReestrFio.Clear();
    fio.Clear();
    seriy_pasp.Clear();
    number_pasp.Clear();
    dr.Clear();
    count=0;
}
/*����� ����������� ������� ������ ListMatchFio*/





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

    hr1->Add(new wxStaticText(this,wxID_ANY,"����"), 1, wxEXPAND|wxLEFT ,5);
    hr1->Add(new wxTextCtrl(this,wxID_DL_TEXT_HOST, wxT("msk1-cro")), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr2->Add(new wxStaticText(this,wxID_ANY,"���� ������"), 1, wxEXPAND|wxLEFT,5);
    hr2->Add(new wxTextCtrl(this,wxID_DL_TEXT_BD, wxT("proverka")), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr3->Add(new wxStaticText(this,wxID_ANY,"�����"), 1, wxEXPAND|wxLEFT,5);
    hr3->Add(new wxTextCtrl(this,wxID_DL_TEXT_USER, wxGetUserName()), 0, wxEXPAND|wxLEFT|wxRIGHT,0); //�������� �������� ������������ ������� wxGetUserName ��� ��������� ����� ������������
    hr4->Add(new wxStaticText(this,wxID_ANY,"������"), 1, wxEXPAND|wxLEFT,5);
    hr4->Add(new wxTextCtrl(this,wxID_DL_TEXT_PASS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT|wxTE_PASSWORD), 0, wxEXPAND|wxLEFT|wxRIGHT,0);
    vert_bos->Add(hr1, 0, wxEXPAND,0);
    vert_bos->Add(hr2, 0, wxEXPAND,0);
    vert_bos->Add(hr3, 0, wxEXPAND,0);
    vert_bos->Add(hr4, 0, wxEXPAND,0);
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0);
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    SetAffirmativeId(wxID_OK); //������ ������������� ��� ������������� � �������� ������ ��
    (this->FindWindow(wxID_OK))->SetFocus(); //������������� ����� ����� �� ������ ��
}

void EnterPassword::OnButton( wxCommandEvent& event)
{
	if(event.GetId()==wxID_OK)
	{
        usr.host = ((wxTextCtrl*)(this->FindWindow(wxID_DL_TEXT_HOST)))->GetValue();
        usr.bd = ((wxTextCtrl*)(this->FindWindow(wxID_DL_TEXT_BD)))->GetValue();
        usr.user = ((wxTextCtrl*)(this->FindWindow(wxID_DL_TEXT_USER)))->GetValue();
        usr.password = ((wxTextCtrl*)(this->FindWindow(wxID_DL_TEXT_PASS)))->GetValue();
        if(!usr.user.compare(wxGetUserName())||!usr.user.compare(wxString("root"))) {;} else {InformationSleep(wxINFO_LOGIN,sec_for_sleep_window_info,this); return;} //��������� ����� ��������� ����� �������� � ������ ������������ � �� ��� � root
        /*
        mysql_init �������� ��� �������������� ������ MYSQL, ���������� ��� ������� mysql_real_connect(). 
        ���� �������� mysql ������������ ����� ��������� NULL, �� ��� ������� ��������, �������������� � 
        ���������� ����� ������. � ��������� ������ ���������������� ��������� ������ � ������������ ��� �����. 
        ���� ������� mysql_init() �������� ����� ������, �� �� ����� ���������� ��� ������ ������� 
        mysql_close(), ����� ������� ������ ����������.
        */
        conn=mysql_init(NULL);
        //������� mysql_real_connect() �������� ���������� ���������� � �������� ��� ������ MySQL, ���������� �� ����� host. 
        if(mysql_real_connect(conn, usr.host.c_str(), 
                                usr.user.c_str(),
                                usr.password.c_str(),
                                usr.bd.c_str(),
                                0, NULL, 0) == NULL)
        {
            //������������ � ��. ���� ���������� �� �����������, �� �������� ������������ �� ������ � ��������� ������ ����������
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
    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
    LocArray.Alloc(MyProdGroupArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyProdGroupArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyProdGroupArray.Item(i).nameProdGroup));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_AS_TEXT_GROUP))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PROD_SUBGROUP), 0, wxEXPAND|wxLEFT,5);
    hr2->Add(new wxTextCtrl(this,wxID_AS_TEXT_SUBGROUP, wxT("")), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    vert_bos->Add(hr1, 0, wxEXPAND,0);
    vert_bos->Add(hr2, 0, wxEXPAND,0);
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0);
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    SetAffirmativeId(wxID_OK); //������ ������������� ��� ������������� � �������� ������ ��
    (this->FindWindow(wxID_AS_TEXT_GROUP))->SetFocus(); //������������� ����� �����  
}

void EnterAssortiment::NewFocus(wxChildFocusEvent& event)
{
    if(window_last->GetId()==wxID_AS_TEXT_GROUP) 
    {
        int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
        wxString str = ((wxTextCtrl*)window_last)->GetValue();          //����������� ���������� �������� ���������� ����
        str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
        for(register int i =0; i<MyProdGroupArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ ����� �������
        {
            if (!str.compare(MyProdGroupArray.Item(i).nameProdGroup))
            {flag=1; id_group=MyProdGroupArray.Item(i).idProdGroup; break;}      //���������� �������: ������ �������� �����, ����������� ���������� id_group ���� �������� ������, ������� �� �����
        }
        if(flag==0){((wxTextCtrl*)window_last)->Clear(); id_group=0;/*id_group.Clear();*/}               //����=0, ���������� � ����� �� �������� => ������� ��������� ����
        if(flag==1)
        {
            wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
            LocArray.Alloc(MyProdGroupArray.GetCount());                //����������� ���������� ������ ��� �������� nCount ���������   
            for(register int i =0; i<MyProdNameArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
            {
                //if(!id_group.compare(MyProdNameArray.Item(i).idProdGroup))
                if(id_group==MyProdNameArray.Item(i).idProdGroup)
                {LocArray.Add(MyProdNameArray.Item(i).nameProdName);}
            }
            ((wxTextCtrl*)this->FindWindow(wxID_AS_TEXT_SUBGROUP))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
            //((wxTextCtrl*)this->FindWindow(wxID_AS_TEXT_SUBGROUP))->Clear();                
        }
    }
    if(window_last->GetId()==wxID_AS_TEXT_SUBGROUP) 
    {
        int flag=0;                                                     //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������
        wxString str = ((wxTextCtrl*)window_last)->GetValue();          //����������� ���������� �������� ���������� ����
        wxString str1 = ((wxTextCtrl*)(this->FindWindow(wxID_AS_TEXT_GROUP)))->GetValue();
        str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
        for(register int i =0; i<MyProdNameArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ �������� �������
        {
            //if ((!str.compare(MyProdNameArray.Item(i).nameProdName))&&(!id_group.compare(MyProdNameArray.Item(i).idProdGroup))&&(!str1.IsEmpty())) //�������: �������� ����������� ��������� �� ��������� �������, ���� ������ ��������� �� ��������� �������, ��������� ���� � �������� ������� �� ������
            if ((!str.compare(MyProdNameArray.Item(i).nameProdName))&&(id_group==MyProdNameArray.Item(i).idProdGroup)&&(!str1.IsEmpty()))
            {flag=1; break;}      //���������� �������: ������ �������� �����, ������� �� �����
        }
        if(flag==0){((wxTextCtrl*)window_last)->Clear();}               //����=0, ���������� � ����� �� �������� => ������� ��������� ����
    }
    window_last=event.GetWindow(); //����������� ���������� ������������� ����, ������� �������� ����� �����. ���������� ����� ��� if ��� ��������� ������ ����� ��������� �����. ������������ ����������� � ����� ������ ����������
}

void EnterAssortiment::OnButton( wxCommandEvent& event)
{
    if(event.GetId()==wxID_OK)
	{
        wxString idGroup = ((wxTextCtrl*)(this->FindWindow(wxID_AS_TEXT_GROUP)))->GetValue(); //����� � ���������� �������� ���� �������� ������
        wxString idSubGroup =((wxTextCtrl*)(this->FindWindow(wxID_AS_TEXT_SUBGROUP)))->GetValue(); idSubGroup.MakeUpper(); //����� � ���������� �������� ���� �������� ���������
        if(idGroup.IsEmpty()) {InformationSleep(wxINFO_NOT_PROD_GROUP,sec_for_sleep_window_info,this); return;}             //���� ���� � �������� ������� ������, ����������� �� ���� ������������ � ��������� ���������
        if(idSubGroup.IsEmpty()) {InformationSleep(wxINFO_NOT_PROD_SUBGROUP,sec_for_sleep_window_info,this); return;}       //���� ���� � �������� ���������� ������, ����������� �� ���� ������������ � ��������� ���������
        for(register int i =0; i<MyProdNameArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ �������� �������
        {
            //if ((!idSubGroup.compare(MyProdNameArray.Item(i).nameProdName))&&(!id_group.compare(MyProdNameArray.Item(i).idProdGroup)))
            if ((!idSubGroup.compare(MyProdNameArray.Item(i).nameProdName))&&(id_group==MyProdNameArray.Item(i).idProdGroup))
            //{idSubGroup=MyProdNameArray.Item(i).idProdName; idGroup=MyProdNameArray.Item(i).idProdGroup; break;}      //���������� �������: ����������� ���������� ���� ������ � ���������, ������� �� �����
            {idSubGroup.Clear(); idSubGroup<<MyProdNameArray.Item(i).idProdName; idGroup.Clear(); idGroup<<MyProdNameArray.Item(i).idProdGroup; break;} 
        }
        wxString sqlText; sqlText<<wxSqlTextInsAssorti;
        sqlText<<inn; sqlText<<wxSqlCommaText;
        sqlText<<idGroup; sqlText<<wxSqlCommaText;
        sqlText<<idSubGroup; sqlText<<wxSqlEndRightBracketText;
        //ProvToFrm *parentWindow = (ProvToFrm*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
        else
        {
            this->EndModal(wxID_OK);
            /*wxString inn_to = ((wxTextCtrl*)((parentWindow)->FindWindow(wxID_TO_INN)))->GetValue(); //����� � ���������� �������� ���������� ���� ������������� ����
            if (inn_to.IsNumber()&&!inn_to.IsEmpty()) //�������� ����, ��� ��� �� ����, � ��� ��� �����
            { 
                wxString sqlText; sqlText<<wxSqlTextAssortiTo; sqlText<<inn_to; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    int num_fields = mysql_num_fields(res); // ���������� �����
                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                    if(num_rows>0)
                    {   
                        wxListView* listview = ((wxListView*)(parentWindow)->FindWindow(wxID_LISTVIEW_ASRT));
                        ((wxListView*)(parentWindow)->FindWindow(wxID_LISTVIEW_ASRT))->DeleteAllItems();
                        for (register int i = 0; i < num_rows; i++) // ����� �������
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[2])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                listview->SetItem(i,l,row[l]); //����� � ��������� ��������� ���� ������-���������
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                        //wxString status = wxCOUNT_ASSORTI; 
                        (parentWindow->count_assorti)=num_rows;
                        //parentWindow->SetStatusText(status,2);
                    } else {;}
                    mysql_free_result(res); // ������� ����������
                    
                    //(parentWindow->FindWindow(wxID_BUTTON_INS_ASRT))->SetFocus();
                }
            }*/
        }
    }
    if(event.GetId()==wxID_CANCEL)
	{
        //ProvToFrm *parentWindow = (ProvToFrm*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
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
    hr5 = new wxBoxSizer(wxHORIZONTAL); //������ ���������� ������������ ��� ������ ���� �������������� - ����������
    wxBoxSizer *hr6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hr7 = new wxBoxSizer(wxHORIZONTAL);
    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_TYPE "*"), 0, wxEXPAND|wxLEFT ,5);
    hr1->Add(new wxTextCtrl(this,wxID_PR_TYPE_COOPER, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
    LocArray.Alloc(MyTypeCooperationArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyTypeCooperationArray.GetCount();++i) //��������� ��������� ������ �������������� ����� ��������������
    {
        LocArray.Add((MyTypeCooperationArray.Item(i).nameTypeCooperation));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_COOPER))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    hr1->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_PROV "*"), 0, wxEXPAND|wxLEFT ,5);
    hr1->Add(new wxTextCtrl(this,wxID_PR_TYPE_PROV, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyTypeProvArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyTypeProvArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyTypeProvArray.Item(i).nameTypeProv));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_PROV))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_OC "*"), 0, wxEXPAND|wxLEFT ,5);
    hr2->Add(new wxTextCtrl(this,wxID_PR_OC, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyOcArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyOcArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        //if(!MyOcArray.Item(i).activOc.compare("1")) {LocArray.Add((MyOcArray.Item(i).nameOc));} else {continue;}
        if(MyOcArray.Item(i).activOc==1) {LocArray.Add((MyOcArray.Item(i).nameOc));} else {continue;}
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_OC))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    hr2->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_GC "*"), 0, wxEXPAND|wxLEFT ,5);
    hr2->Add(new wxTextCtrl(this,wxID_PR_GC, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_COMENT), 0, wxEXPAND|wxLEFT ,5);
    hr3->Add(new wxTextCtrl(this,wxID_PR_COMMENT, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    hr4->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_UK), 0, wxEXPAND|wxLEFT ,5);
    hr4->Add(new wxTextCtrl(this,wxID_PR_UK, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyUkRfArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyUkRfArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyUkRfArray.Item(i).nameUkRf));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_UK))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    hr6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_REZ "*"), 0, wxEXPAND|wxLEFT ,5);
    hr6->Add(new wxTextCtrl(this,wxID_PR_REZULT, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyRezProvArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyRezProvArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyRezProvArray.Item(i).nameRezProv));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_REZULT))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    hr6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_SOTRSB "*"), 0, wxEXPAND|wxLEFT ,5);
    hr6->Add(new wxTextCtrl(this,wxID_PR_SOTR_SB, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
    LocArray.Alloc(MyFioSbArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyFioSbArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyFioSbArray.Item(i).nameFioSb));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_SOTR_SB))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
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
    id_<<id1;                 //����������� ���������� ���� ��, ��� ���� �������� ��
    type_operation<<type;    //����������� ���������� ������� ��������: �������� (0), �������� (1)
    //wxButton *fastComment = new wxButton(this,wxID_PR_FASTCOMMENT, wxT("fastComment")); //������� ������ ���������� ��� ������������
    //fastComment->Hide();	//�������� ������ �� ������������
    /*�������� ������������*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*����� � ��������������*/
    if(type==1)
    {
        wxString sqlText; sqlText<<wxSqlTextProvToOne;
        sqlText<<id_; sqlText<<wxSqlEndText;
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
                    for (register int l = 0; l < num_fields; l++)
                    {
                        if (l==0) 
                        {
                            for(register int k =0; k<MyTypeCooperationArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(wxAtoi(MyTypeCooperationArray.Item(k).idTypeCooperation.c_str())==wxAtoi(row[l])) //���������� �������
                                if(MyTypeCooperationArray.Item(k).idTypeCooperation==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_COOPER))->ChangeValue(MyTypeCooperationArray.Item(k).nameTypeCooperation);
                                    /*���� ��� ����������� �������� - ����������, �� ������� ���� � ����������� �������� � ���������� � ���� ��������*/
                                    if(!MyTypeCooperationArray.Item(k).nameTypeCooperation.compare(wxSTRING_CONTRACTOR))
                                    {
                                        hr5->Add(new wxStaticText(this,wxID_PR_ST_INITIATOR,wxCAPTION_STATICTEXT_INITIATOR "*"), 0, wxEXPAND|wxLEFT ,5);
                                        hr5->Add(new wxTextCtrl(this,wxID_PR_TC_INITIATOR, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
                                        wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                                        LocArray.Alloc(MyTypeCooperationArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                                        for(register int i =0; i<MyInitiatorChecksArray.GetCount();++i) //��������� ��������� ������ �������������� ����� ��������������
                                        {
                                            LocArray.Add((MyInitiatorChecksArray.Item(i).nameInitiatorChecks));
                                            //if(!MyInitiatorChecksArray.Item(i).idInitiatorChecks.compare(row[9]))
                                            if(MyInitiatorChecksArray.Item(i).idInitiatorChecks==wxAtoi(row[9]))
                                            {
                                                ((wxTextCtrl*)this->FindWindow(wxID_PR_TC_INITIATOR))->ChangeValue(MyInitiatorChecksArray.Item(i).nameInitiatorChecks); //���������� � ���� ����������
                                            }
                                        }
                                        ((wxTextCtrl*)this->FindWindow(wxID_PR_TC_INITIATOR))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                                        LocArray.Clear(); //������� ���������� ������� � ����������� ������
                                        wxTextCtrl *wxUk = ((wxTextCtrl*)this->FindWindow(wxID_PR_UK)); //�������� ��������� �� ��������� �������� � �� ��
                                        (this->FindWindow(wxID_PR_TC_INITIATOR))->MoveAfterInTabOrder(wxUk); //���������� ���� ���������� �� ����� ����� �� �� �� ������� ���  
                                    }
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==1) 
                        {
                            for(register int k =0; k<MyTypeProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(wxAtoi(MyTypeProvArray.Item(k).idTypeProv.c_str())==wxAtoi(row[l])) //���������� �������
                                if(MyTypeProvArray.Item(k).idTypeProv==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_PROV))->ChangeValue(MyTypeProvArray.Item(k).nameTypeProv);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==2) 
                        {
                            for(register int k =0; k<MyOcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(wxAtoi(MyOcArray.Item(k).idOc.c_str())==wxAtoi(row[l])) //���������� �������
                                if(MyOcArray.Item(k).idOc==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_OC))->ChangeValue(MyOcArray.Item(k).nameOc);
                                    id_oc=wxAtoi(row[l]);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==3) 
                        {
                            for(register int k =0; k<MyGcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(wxAtoi(MyGcArray.Item(k).idGc.c_str())==wxAtoi(row[l])) //���������� �������
                                if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //���������� �������
                                {   
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->ChangeValue(MyGcArray.Item(k).nameGc);
                                    id_gc=wxAtoi(row[l]);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==4)  {((wxTextCtrl*)this->FindWindow(wxID_PR_COMMENT))->ChangeValue(row[l]);}
                        if (l==5) 
                        {
                            for(register int k =0; k<MyUkRfArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(wxAtoi(MyUkRfArray.Item(k).idUkRf.c_str())==wxAtoi(row[l])) //���������� �������
                                if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_UK))->ChangeValue(MyUkRfArray.Item(k).nameUkRf);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==6) 
                        {
                            for(register int k =0; k<MyRezProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(wxAtoi(MyRezProvArray.Item(k).idRezProv.c_str())==wxAtoi(row[l])) //���������� �������
                                if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_REZULT))->ChangeValue(MyRezProvArray.Item(k).nameRezProv);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==7) 
                        {
                            for(register int k =0; k<MyFioSbArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(wxAtoi(MyFioSbArray.Item(k).idFioSb.c_str())==wxAtoi(row[l])) //���������� �������
                                if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_SOTR_SB))->ChangeValue(MyFioSbArray.Item(k).nameFioSb);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==8) 
                        {
                            wxString str=row[l]; //����� ���� �� ���������� ������� ������� � ����������
                            
                            insertStrDateToCtrl (str, (wxDatePickerCtrl*)this->FindWindow(wxID_PR_DATE_PROV));
                        }
                    }
                }
            }
            mysql_free_result(res); // ������� ����������
        }
    }
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    this->SetAffirmativeId(wxID_OK); //������ ������������� ��� ������������� � �������� ������ ��
    (this->FindWindow(wxID_PR_TYPE_COOPER))->SetFocus(); //������������� ����� ����� �� ���� ��� ��������������
}

void EnterProvTo::NewFocus(wxChildFocusEvent& event)
{
    if(idWindowFocus==wxID_PR_TYPE_COOPER)
    {
        wxString strCooperation = ((wxTextCtrl*)this->FindWindow(wxID_PR_TYPE_COOPER))->GetValue();
        if(!strCooperation.IsEmpty()) //������ �� �����
        {
            strCooperation.MakeUpper(); //�������� � �������� ��������
            if(!strCooperation.compare(wxSTRING_CONTRACTOR)) //������ == ����������
            {
                if(this->FindWindow(wxID_PR_TC_INITIATOR)) {;}//���� ����������, �� �������
                else
                {
                    hr5->Add(new wxStaticText(this,wxID_PR_ST_INITIATOR,wxCAPTION_STATICTEXT_INITIATOR "*"), 0, wxEXPAND|wxLEFT ,5);
                    hr5->Add(new wxTextCtrl(this,wxID_PR_TC_INITIATOR, wxT(""), wxDefaultPosition, wxDefaultSize,wxTE_CHARWRAP), 1, wxEXPAND|wxLEFT|wxRIGHT,0);
                    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
                    LocArray.Alloc(MyInitiatorChecksArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                    for(register int i =0; i<MyInitiatorChecksArray.GetCount();++i) //��������� ��������� ������ �������������� ����� ��������������
                    {
                        LocArray.Add((MyInitiatorChecksArray.Item(i).nameInitiatorChecks));
                    }
                    ((wxTextCtrl*)this->FindWindow(wxID_PR_TC_INITIATOR))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                    LocArray.Clear(); //������� ���������� ������� � ����������� ������
                    wxTextCtrl *wxUk = ((wxTextCtrl*)this->FindWindow(wxID_PR_UK)); //�������� ��������� �� ��������� �������� � �� ��
                    (this->FindWindow(wxID_PR_TC_INITIATOR))->MoveAfterInTabOrder(wxUk); //���������� ���� ���������� �� ����� ����� �� �� �� ������� ���                     
                }
            }
            else
            {
                if(this->FindWindow(wxID_PR_TC_INITIATOR)) //���� ����������, ��������� 
                {
                    hr5->Clear(); //����������� ���� �� ������������
                    (wxStaticText*)(this->FindWindow(wxID_PR_ST_INITIATOR))->Destroy();  //������� ����
                    (wxTextCtrl*)(this->FindWindow(wxID_PR_TC_INITIATOR))->Destroy(); 
                }
            }
        }
        else
        {
            if(this->FindWindow(wxID_PR_TC_INITIATOR)) //���� ����������, ��������� 
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
        int flag=0;                                       //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������                                                  
        wxString str = ((wxTextCtrl*)this->FindWindow(wxID_PR_OC))->GetValue();          //����������� ���������� �������� ���������� ����
        int idReg=0;
        str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
        for(register int i =0; i<MyOcArray.GetCount();++i)       //��������� ���� ������ ���������� � ������� ������������ ����� �������
        {
            if ((MyOcArray.Item(i).activOc==1)&&(!str.compare(MyOcArray.Item(i).nameOc)))
            {flag=1; idReg=MyOcArray.Item(i).idOc; /*str = MyOcArray.Item(i).idOc;*/ id_oc=MyOcArray.Item(i).idOc; break;}      //���������� �������: ������ �������� �����,  ������� �� �����
        }
        if(flag==0){((wxTextCtrl*)this->FindWindow(wxID_PR_OC))->Clear(); id_oc=0; /*id_oc.Clear();*/}               //����=0, ���������� � ����� �� �������� => ������� ��������� ����
        if(flag==1)
        {
            wxArrayString LocArray;                                     //��������� ������ ��� �������������� � ��������� ����
            for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
            {
                //if(!str.compare(MyTechCentrArray.Item(i).son))
                if(idReg==MyTechCentrArray.Item(i).son)
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
            ((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������                                   
        }
    }
    if(idWindowFocus==wxID_PR_GC) 
    {
        int flag=0;                                                     //���� ���������� �������� ���������� ���� �� ��������� �������. 0 - ��� ����������, 1 - ���� ����������
        wxString str = ((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->GetValue();          //����������� ���������� �������� ���������� ����
        int idReg=0;
        str.MakeUpper();                                                //�������� ������� ���������� � �������� ��������
        for(register int j =0; j<MyGcArray.GetCount();++j)   //��������� ��������� ������ �������������� �������� �����
        {
            //if((!MyGcArray.Item(j).activGc.compare("1"))&&(!MyGcArray.Item(j).nameGc.compare(str)))
            if((MyGcArray.Item(j).activGc==1)&&(!MyGcArray.Item(j).nameGc.compare(str)))
            {
                for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
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
        for(register int i =0; i<MyTechCentrArray.GetCount();++i)   //��������� ��������� ������ �������������� �������� �����
        {
            //if ((!id_oc.compare(MyTechCentrArray.Item(i).son))&&(!MyTechCentrArray.Item(i).parent.compare(str))) //�������: �������� ����������� ��������� �� ��������� �������, ���� ������ ��������� �� ��������� �������, ��������� ���� � �������� ������� �� ������
            if ((id_oc==MyTechCentrArray.Item(i).son)&&(MyTechCentrArray.Item(i).parent==idReg)) //�������: �������� ����������� ��������� �� ��������� �������, ���� ������ ��������� �� ��������� �������, ��������� ���� � �������� ������� �� ������
            {flag=1; id_gc=idReg; break;}      //���������� �������: ������ �������� �����, ������� �� �����
        }
        if(flag==0){((wxTextCtrl*)this->FindWindow(wxID_PR_GC))->Clear(); id_gc=0;}               //����=0, ���������� � ����� �� �������� => ������� ��������� ����
    }
    idWindowFocus=(event.GetWindow())->GetId();
}

void EnterProvTo::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    switch(event.GetId())
    {
        case wxID_PR_COMMENT: //������� ������ �� ���� � ������������
            {
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //���� ����� ctrl+z
                {
                    if(wxTheClipboard->Open()) //��������� ����� ������
                    {
                        wxTheClipboard->SetData(new wxTextDataObject(((CrossFrm*)(this->GetGrandParent())->GetGrandParent())->fastComment)); //�������� � ����� ������ ����� �� ������ ����� ����������� ����
                        if(wxTheClipboard->IsSupported(wxDF_TEXT)) //���������� ����� , ���� ���� ������ , ������� ������������� ������� ������ ������ wxDF_TEXT
                        {
                            wxTextDataObject textData; //������� ������ ��� ����������� ������ �� ������ ������
                            wxTheClipboard->GetData(textData); //��������� ����� �� ������ ������ � ������-��������
                            //if((wxWindow::FindFocus())->GetId()==wxID_PR_COMMENT) //��������� ��, ��� ����� ����� ��������� � ���� ��� �����������
                            {
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(textData.GetText()); //��������� � ���� � ������������ ����� �� �������.
                                wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)this->GetGrandParent())->fastComment); //��������� ����� �� ������-����� ����������� � ���� � ������� �����  
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
        wxString idTypeCoop = ((wxTextCtrl*)(this->FindWindow(wxID_PR_TYPE_COOPER)))->GetValue(); //����� � ���������� �������� ����
        wxString idTypeProv = ((wxTextCtrl*)(this->FindWindow(wxID_PR_TYPE_PROV)))->GetValue(); //����� � ���������� �������� ����
        //wxString idOc = ((wxTextCtrl*)(this->FindWindow(wxID_PR_OC)))->GetValue(); //����� � ���������� �������� ����
        //wxString idGc = ((wxTextCtrl*)(this->FindWindow(wxID_PR_GC)))->GetValue(); //����� � ���������� �������� ����
        wxString idComment = ((wxTextCtrl*)(this->FindWindow(wxID_PR_COMMENT)))->GetValue(); //����� � ���������� �������� ����
        wxString idUk = ((wxTextCtrl*)(this->FindWindow(wxID_PR_UK)))->GetValue(); //����� � ���������� �������� ����
        wxString idRezult = ((wxTextCtrl*)(this->FindWindow(wxID_PR_REZULT)))->GetValue(); //����� � ���������� �������� ����
        wxString idSotrSb = ((wxTextCtrl*)(this->FindWindow(wxID_PR_SOTR_SB)))->GetValue(); //����� � ���������� �������� ����
        wxString idDate = (((wxDatePickerCtrl*)(this->FindWindow(wxID_PR_DATE_PROV)))->GetValue()).FormatISODate(); //����� � ���������� �������� ����
        wxString idInitiator;
        if(this->FindWindow(wxID_PR_TC_INITIATOR))//���� ����������, �� ����� � ���������
        {
            idInitiator = ((wxTextCtrl*)(this->FindWindow(wxID_PR_TC_INITIATOR)))->GetValue();
            idInitiator.MakeUpper();
            if(idInitiator.IsEmpty()) {InformationSleep(wxINFO_NOT_INITIATOR,sec_for_sleep_window_info,this); return;}
        } else {idInitiator=wxSQL_DEFAULT;}
        idTypeCoop.MakeUpper(); idTypeProv.MakeUpper(); /*idOc.MakeUpper(); idGc.MakeUpper();*/ idUk.MakeUpper(); idRezult.MakeUpper(); idSotrSb.MakeUpper(); //�������� �������� � �������� ��������
        
        if(idTypeCoop.IsEmpty()) {InformationSleep(wxINFO_NOT_TYPE_PROV,sec_for_sleep_window_info,this); return;}             //���� ����  ������, ����������� �� ���� ������������ � ��������� ���������
        if(idTypeProv.IsEmpty()) {InformationSleep(wxINFO_NOT_TYPE_PROV,sec_for_sleep_window_info,this); return;}             //���� ����  ������, ����������� �� ���� ������������ � ��������� ���������
        if(/*idOc.IsEmpty()*/id_oc==0) {InformationSleep(wxINFO_NOT_OC,sec_for_sleep_window_info,this); return;}             //���� ����  ������, ����������� �� ���� ������������ � ��������� ���������
        if(/*idGc.IsEmpty()*/id_gc==0) {InformationSleep(wxINFO_NOT_GC,sec_for_sleep_window_info,this); return;}             //���� ����  ������, ����������� �� ���� ������������ � ��������� ���������
        //if(idUk.IsEmpty()) {InformationSleep(wxINFO_NOT_PROD_GROUP,sec_for_sleep_window_info,this); return;}             //���� ����  ������, ����������� �� ���� ������������ � ��������� ���������
        if(idRezult.IsEmpty()) {InformationSleep(wxINFO_NOT_RESULT,sec_for_sleep_window_info,this); return;}             //���� ����  ������, ����������� �� ���� ������������ � ��������� ���������
        if(idSotrSb.IsEmpty()) {InformationSleep(wxINFO_NOT_SOTR_SB,sec_for_sleep_window_info,this); return;}             //���� ����  ������, ����������� �� ���� ������������ � ��������� ���������
        if(idDate.IsEmpty()) {InformationSleep(wxINFO_NOT_DATE,sec_for_sleep_window_info,this); return;}             //���� ����  ������, ����������� �� ���� ������������ � ��������� ���������
        
        for(register int i =0; i<MyTypeCooperationArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idTypeCoop.compare(MyTypeCooperationArray.Item(i).nameTypeCooperation))
            //{idTypeCoop=MyTypeCooperationArray.Item(i).idTypeCooperation; break;}      //���������� �������
            {idTypeCoop.Clear(); idTypeCoop<<MyTypeCooperationArray.Item(i).idTypeCooperation; break;}      //���������� �������
        }
        for(register int i =0; i<MyTypeProvArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idTypeProv.compare(MyTypeProvArray.Item(i).nameTypeProv))
            //{idTypeProv=MyTypeProvArray.Item(i).idTypeProv; break;}      //���������� �������
            {idTypeProv.Clear(); idTypeProv<<MyTypeProvArray.Item(i).idTypeProv; break;}      //���������� �������
        }
        /*for(register int i =0; i<MyOcArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            //if ((!idOc.compare(MyOcArray.Item(i).nameOc))&&(!MyOcArray.Item(i).activOc.compare("1")))
            //{idOc=MyOcArray.Item(i).idOc; break;}      //���������� �������
            if ((!idOc.compare(MyOcArray.Item(i).nameOc))&&(MyOcArray.Item(i).activOc==1))
            {idOc.Clear(); idOc<<MyOcArray.Item(i).idOc; break;}      //���������� �������
        }
        for(register int i =0; i<MyGcArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            //if ((!idGc.compare(MyGcArray.Item(i).nameGc))&&(!MyGcArray.Item(i).activGc.compare("1")))
            //{idGc=MyGcArray.Item(i).idGc; break;}      //���������� �������
            if ((!idGc.compare(MyGcArray.Item(i).nameGc))&&(MyGcArray.Item(i).activGc==1))
            {idGc.Clear(); idGc<<MyGcArray.Item(i).idGc; break;}      //���������� �������
        }*/
        if(idComment.IsEmpty()) {idComment=wxNULL_STRING;}
        if(idUk.IsEmpty()) {idUk=wxUK_DEFAULT;} 
        else
        {
            for(register int i =0; i<MyUkRfArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!idUk.compare(MyUkRfArray.Item(i).nameUkRf))
                //{idUk=MyUkRfArray.Item(i).idUkRf; break;}      //���������� �������
                {idUk.Clear(); idUk<<MyUkRfArray.Item(i).idUkRf; break;}      //���������� �������
            }
        }
        for(register int i =0; i<MyRezProvArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idRezult.compare(MyRezProvArray.Item(i).nameRezProv))
            //{idRezult=MyRezProvArray.Item(i).idRezProv; break;}      //���������� �������
            {idRezult.Clear(); idRezult<<MyRezProvArray.Item(i).idRezProv; break;}      //���������� �������
        }
        for(register int i =0; i<MyFioSbArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idSotrSb.compare(MyFioSbArray.Item(i).nameFioSb))
            //{idSotrSb=MyFioSbArray.Item(i).idFioSb; break;}      //���������� �������
            {idSotrSb.Clear(); idSotrSb<<MyFioSbArray.Item(i).idFioSb; break;}      //���������� �������
        }
        if(idInitiator.compare(wxSQL_DEFAULT)) //�� ����� �������� ��-���������
        {
            for(register int i =0; i<MyInitiatorChecksArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!idInitiator.compare(MyInitiatorChecksArray.Item(i).nameInitiatorChecks))
                //{idInitiator=MyInitiatorChecksArray.Item(i).idInitiatorChecks; break;}      //���������� �������
                {idInitiator.Clear(); idInitiator<<MyInitiatorChecksArray.Item(i).idInitiatorChecks; break;}      //���������� �������
            }
            if(idInitiator.IsNumber()) {;} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        }
        
        
        if(idTypeCoop.IsNumber()&&idTypeProv.IsNumber()&&/*idOc.IsNumber()*/id_oc!=0&&/*idGc.IsNumber()*/id_gc!=0&&idUk.IsNumber()&&idRezult.IsNumber()&&idSotrSb.IsNumber()) {;} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        
        wxString sqlText; 
        if(!type_operation.compare("0")) //��������� �������� ��
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
        if(!type_operation.compare("1")) //��������� �������� ��
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
        //ProvToFrm *parentWindow = (ProvToFrm*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
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
    for (register int i = 0; i < listFio.count; i++) // ����� �������
    {
        wxListItem *f = new wxListItem();
        f->SetState(wxLIST_STATE_FOCUSED);
        f->SetMask(wxLIST_MASK_TEXT);
        f->SetColumn(0);
        f->SetData(wxAtoi(listFio.idReestrFio.Item(i))); //������ ���������� ����
        f->SetId(i);
        listview->InsertItem(*f); 
        listview->SetItem(i,0,listFio.fio.Item(i));
        listview->SetItem(i,1,listFio.seriy_pasp.Item(i));
        listview->SetItem(i,2,listFio.number_pasp.Item(i));
        listview->SetItem(i,3,listFio.dr.Item(i));
        delete f;
    }
    for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
    this->SetSizer(to_static_box); 
    this->SetAffirmativeId(wxID_OK);
    this->SetEscapeId(wxID_CANCEL);
    /*�������� ������������*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*����� � ��������������*/
}

void ListFindFio::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    if(event.GetKeyCode()==13) //������ ������ Enter
    {
        wxString sqlText, sqlIdFl; 
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_LISTFIO)); //�������� ��������� �� ���������
        EnterProvSotrTo *parentWindow = (EnterProvSotrTo*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
        int idItem = (int)listview->GetFirstSelected();
        if (idItem==-1) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} 
        wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
        f->SetId(idItem); //������������� ������� ���������� ��������
        f->SetColumn(0); //������� � ���
        f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT); //���������� ������ ��������� � ���������
        listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
        ((wxTextCtrl*)parentWindow->FindWindow(wxID_PR_FZ_FIO))->ChangeValue(f->GetText());
        (parentWindow->id_fio).Clear(); 
        (parentWindow->id_fio)<<f->GetData(); //����� � ���������� ������ ��������� � ���������
        sqlIdFl<<f->GetData();
        f->SetColumn(1); //������� � ������ ��������
        listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
        ((wxTextCtrl*)parentWindow->FindWindow(wxID_PR_FZ_SERIY))->ChangeValue(f->GetText());
        f->SetColumn(2); //������� � ������� ��������
        listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
        ((wxTextCtrl*)parentWindow->FindWindow(wxID_PR_FZ_NOMER))->ChangeValue(f->GetText());
        f->SetColumn(3); //������� � ������� ��������
        listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
        wxString strDate = f->GetText();
        insertStrDateToCtrl (strDate, (wxDatePickerCtrl*)parentWindow->FindWindow(wxID_PR_FZ_DR));
        /*wxDateTime dt;
        wxString::const_iterator end;
        dt.ParseDate(f->GetText(), &end);
        ((wxDatePickerCtrl*)parentWindow->FindWindow(wxID_PR_FZ_DR))->SetValue(dt);
        */
        delete f;
        
        /*
        ��������� ���� �������� � ������ ������� ��.
        */
        sqlText<<wxSqlTextUpdFzStart1;
        sqlText<<strDate; sqlText<<wxSqlCharStr; sqlText<<wxSqlTextUpdFz4;
        sqlText<<sqlIdFl; sqlText<<wxSqlEndText; 
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} else {;}
        
        this->EndModal(wxID_OK);
        event.Skip(false);
    }
    if(event.GetKeyCode()==WXK_ESCAPE) //������ ������ Esc
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
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0); //��������� ����� wxDialog ������� ������������� �� ������������ ��������, ����������� �� ��������� ����� �������
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    id_opera=id_operation;
    if(id_opera==1) {this->SetTitle(wxCAPTION_HOLSOV1);}
    if(id_opera==2) {this->SetTitle(wxCAPTION_HOLSOV2);}
    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
    LocArray.Alloc(MyHolidayTypeArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MyHolidayTypeArray.GetCount();++j)   //��������� ��������� ������
    {
        LocArray.Add(MyHolidayTypeArray.Item(j).nameHolidayType);
    }
    ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_1))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(listveiwFio->GetItemCount());  //����������� ���������� ������ ��� �������� nCount ���������
    for(register int j =0; j<listveiwFio->GetItemCount();++j)   //��������� ��������� ������
    {
        LocArray.Add(listveiwFio->GetItemText(j));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_2))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    ((wxTextCtrl*)this->FindWindow(wxID_DIALOG_HOLSOTR_TEXT_3))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
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
            for(register int i =0; i<MyHolidayTypeArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!strEvent.compare(MyHolidayTypeArray.Item(i).nameHolidayType))
                //{idEvent=wxAtoi(MyHolidayTypeArray.Item(i).idHolidayType); break;}      //���������� �������
                {idEvent=MyHolidayTypeArray.Item(i).idHolidayType; break;}      //���������� �������
            }
            if(idEvent==0) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
            if(!strZamKand.IsEmpty())
            {
                strZamKand.MakeUpper();
                for(register int i =0; i<MySovetnicArray.GetCount();++i)       //��������� ���� ������ ���������� 
                {
                    if (!strZamKand.compare(MySovetnicArray.Item(i).nameSovetnic)&&MySovetnicArray.Item(i).activSovetnic==1)
                    //{idZamKand=wxAtoi(MySovetnicArray.Item(i).idSovetnic); break;}      //���������� �������
                    {idZamKand=MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
                }
                if(idZamKand==0) {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
            }
            if(!strZamTo.IsEmpty())
            {
                strZamTo.MakeUpper();
                for(register int i =0; i<MySovetnicArray.GetCount();++i)       //��������� ���� ������ ���������� 
                {
                    if (!strZamTo.compare(MySovetnicArray.Item(i).nameSovetnic)&&MySovetnicArray.Item(i).activSovetnic==1)
                    //{idZamTo=wxAtoi(MySovetnicArray.Item(i).idSovetnic); break;}      //���������� ������
                    {idZamTo=MySovetnicArray.Item(i).idSovetnic; break;}      //���������� �������
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
    else {hr2->Add(new wxDatePickerCtrl(this,wxID_PR_FZ_DR,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_ALLOWNONE)); ((wxDatePickerCtrl*)this->FindWindow(wxID_PR_FZ_DR))->Enable(false);} //������� ��������� ������������ ���� ������ � ���� � �����
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
    vert_bos->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND|wxALIGN_LEFT,0); //��������� ����� wxDialog ������� ������������� �� ������������ ��������, ���������� �� ��������� ����� �������
    this->SetSizer(vert_bos);
    vert_bos->SetSizeHints(this);
    
    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
    LocArray.Alloc(MyGcArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MyGcArray.GetCount();++j)   //��������� ��������� ������
    {
        //if(!MyGcArray.Item(j).activGc.compare("1")) {LocArray.Add(MyGcArray.Item(j).nameGc);}
        if(MyGcArray.Item(j).activGc==1) {LocArray.Add(MyGcArray.Item(j).nameGc);}
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_GC))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MyDolznostArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyDolznostArray.GetCount();++i) //��������� ��������� ������ 
    {
        LocArray.Add((MyDolznostArray.Item(i).nameDolznost));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_DOLZ))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MyUkRfArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyUkRfArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyUkRfArray.Item(i).nameUkRf));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_UK))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MyRezProvArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyRezProvArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyRezProvArray.Item(i).nameRezProv));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_REZULT))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MyFioSbArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������
    for(register int i =0; i<MyFioSbArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyFioSbArray.Item(i).nameFioSb));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SOTR_SB))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SERIY))->SetMaxLength(4); //������������� ����������� �� ���������� �������� �������� � ���� � ������ ��������   
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_NOMER))->SetMaxLength(6); //������������� ����������� �� ���������� �������� �������� � ���� � ������� ��������
    ((wxCheckBox*)this->FindWindow(wxID_PR_FZ_COMPARE))->SetValue(true); //������ ������� � ��������
    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_FIO))->SetFocus(); //������������� ����� ����� �� ���� � ���
    SetAffirmativeId(wxID_OK);      //������ ������������� ��� ������������� � �������� ������ ��
    id_<<id1;                       //id �� (���� ��������� ����� ��������) ��� ������ � ������� �������� �������(���� ��������� ������ ��������)
    type_operation<<type;           //����������� ���������� ������� ��������: �������� (0), �������� (1)
    /*�������� ������������*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*����� � ��������������*/
    if(type==1)
    {
        wxString sqlText; sqlText<<wxSqlTextSotrToOne;
        sqlText<<id_; sqlText<<wxSqlEndText;
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
                    for (register int l = 0; l < num_fields; l++)
                    {
                        if (l==0) { ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_FIO))->ChangeValue(row[0]); }
                        if (l==1) 
                        { 
                            wxString str=row[1]; //����� ���� �� ���������� ������� ������� � ����������
                            insertStrDateToCtrl (str, (wxDatePickerCtrl*)this->FindWindow(wxID_PR_FZ_DR));
                        }
                        if (l==2) 
                        {
                            for(register int k =0; k<MyDolznostArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(atoi(MyDolznostArray.Item(k).idDolznost.c_str())==atoi(row[l])) //���������� �������
                                if(MyDolznostArray.Item(k).idDolznost==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_DOLZ))->ChangeValue(MyDolznostArray.Item(k).nameDolznost);
                                    break; //������� �� ���������� �����
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
                            for(register int k =0; k<MyGcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //���������� �������
                                if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //���������� �������
                                {   
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_GC))->ChangeValue(MyGcArray.Item(k).nameGc);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==6)  {((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_COMMENT))->ChangeValue(row[l]);}
                        if (l==7) 
                        {
                            for(register int k =0; k<MyUkRfArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //���������� �������
                                if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_UK))->ChangeValue(MyUkRfArray.Item(k).nameUkRf);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==8) 
                        {
                            for(register int k =0; k<MyRezProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //���������� �������
                                if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_REZULT))->ChangeValue(MyRezProvArray.Item(k).nameRezProv);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==9) 
                        {
                            for(register int k =0; k<MyFioSbArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //���������� �������
                                if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //���������� �������
                                {
                                    ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SOTR_SB))->ChangeValue(MyFioSbArray.Item(k).nameFioSb);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                        if (l==10) 
                        {
                            wxString str=row[l]; //����� ���� �� ���������� ������� ������� � ����������
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
            mysql_free_result(res); // ������� ����������
        }
    } 
}

void EnterProvSotrTo::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    switch(event.GetId())
    {
        case wxID_PR_FZ_SERIY: //��������� � ���� � ��� ������� ������� �������� �� ����
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //���� ����� ����, ������ ��� ����, �� ���������� ������� ����� � ��������
                {event.Skip(true);} 
                else {
                    if((event.GetKeyCode()>=32&&event.GetKeyCode()<=47)||(event.GetKeyCode()>=58&&event.GetKeyCode()<=255)) //���� ������� ������ ������ � ���������, �� �� ���������� ������� ����� � ��������
                        {event.Skip(false);}
                    else {event.Skip(true);}
                }
                break;
            }
        case wxID_PR_FZ_NOMER: //��������� � ���� � �� ������� ������� �������� �� ����
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //���� ����� ����, ������ ��� ����, �� ���������� ������� ����� � ��������
                {event.Skip(true);} 
                else {
                    if((event.GetKeyCode()>=32&&event.GetKeyCode()<=47)||(event.GetKeyCode()>=58&&event.GetKeyCode()<=255)) //���� ������� ������ ������ � ���������, �� �� ���������� ������� ����� � ��������
                        {event.Skip(false);}
                    else {event.Skip(true);}
                }
                break;
            }
        case wxID_PR_FZ_COMMENT: //������� ������ �� ���� � ������������
            /*{
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //���� ����� ctrl+z
                {
                    wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                    ((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)this->GetGrandParent())->fastComment); //��������� ����� �� ������-����� ����������� � ���� � ������� �����          
                }
                event.Skip(true); 
                break;
            }*/
            {
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //���� ����� ctrl+z
                {
                    if(wxTheClipboard->Open()) //��������� ����� ������
                    {
                        wxTheClipboard->SetData(new wxTextDataObject(((CrossFrm*)(this->GetGrandParent())->GetGrandParent())->fastComment)); //�������� � ����� ������ ����� �� ������ ����� ����������� ����
                        if(wxTheClipboard->IsSupported(wxDF_TEXT)) //���������� ����� , ���� ���� ������ , ������� ������������� ������� ������ ������ wxDF_TEXT
                        {
                            wxTextDataObject textData; //������� ������ ��� ����������� ������ �� ������ ������
                            wxTheClipboard->GetData(textData); //��������� ����� �� ������ ������ � ������-��������
                            //if((wxWindow::FindFocus())->GetId()==wxID_PR_COMMENT) //��������� ��, ��� ����� ����� ��������� � ���� ��� �����������
                            {
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(textData.GetText()); //��������� � ���� � ������������ ����� �� �������.
                                wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)this->GetGrandParent())->fastComment); //��������� ����� �� ������-����� ����������� � ���� � ������� �����  
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
        fio = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_FIO))->GetValue(); //����� ���������� �� ������� if, �.�. � ��������� ������ ���������� ������ � ��� �������� �� �� �� ������������ ��� ������
        if(!type_operation.compare("0")||!type_operation.compare("1"))                                                 //���� ��� �������� - ����������, �� ������������ ���� � ���/�������.
        {
        seriy = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SERIY))->GetValue();
        number = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_NOMER))->GetValue();
        fio.Trim(true); fio.Trim(false); seriy.Trim(true); seriy.Trim(false); number.Trim(true); number.Trim(false); //������� �������
        if (fio.IsEmpty()) {InformationSleep(wxINFO_NOT_FIO_SOTR,sec_for_sleep_window_info,this); return;}
        switch(seriy.Len())
        {
            case 0:
            {
                seriy<<wxNULL_;
                flag_seriy=1; //������� ����, ��� ����� ��� ����� ��������
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
                flag_number=1; //������� ����, ��� ����� ��� ������ ��������
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
        if(((CrossFrm*)(this->GetGrandParent()))->flag_bl_sb) {if(proverka_bl_sb(conn, fio, 1)==1) {;} else {return;}} //�������� �� �� ��
        if((((wxDatePickerCtrl*)(this->FindWindow(wxID_PR_FZ_DR)))->GetValue()).IsValid())
        {strDr = (((wxDatePickerCtrl*)(this->FindWindow(wxID_PR_FZ_DR)))->GetValue()).FormatISODate();}
        idGc = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_GC))->GetValue();
        idDolz = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_DOLZ))->GetValue();
        idUk = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_UK))->GetValue();
        idComment = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_COMMENT))->GetValue();
        idRez = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_REZULT))->GetValue();
        idSotr = ((wxTextCtrl*)this->FindWindow(wxID_PR_FZ_SOTR_SB))->GetValue();
        idDate = (((wxDatePickerCtrl*)(this->FindWindow(wxID_PR_FZ_DATE_PROV)))->GetValue()).FormatISODate(); //����� � ���������� �������� ����
        fio.MakeUpper(); idGc.MakeUpper(); idDolz.MakeUpper(); idUk.MakeUpper(); idRez.MakeUpper(); idSotr.MakeUpper();
        
        if(strDr.IsEmpty()) {strDr=wxSQL_DEFAULT;} 
        if(idDolz.IsEmpty()||idRez.IsEmpty()||idSotr.IsEmpty()) {InformationSleep(wxINFO_EMPTY_CONTROL,sec_for_sleep_window_info,this); return;}
        if(idComment.IsEmpty()) {idComment=wxNULL_STRING;}        
        if(idGc.IsEmpty()||(!idGc.compare(wxNOT_DATA))) {idGc=wxNULL_;} 
        else
        {
            for(register int i =0; i<MyGcArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                //if (!idGc.compare(MyGcArray.Item(i).nameGc)&&(!MyGcArray.Item(i).activGc.compare("1")))
                //{idGc=MyGcArray.Item(i).idGc; break;}      //���������� �������
                if (!idGc.compare(MyGcArray.Item(i).nameGc)&&(MyGcArray.Item(i).activGc==1))
                {idGc.Clear(); idGc<<MyGcArray.Item(i).idGc; break;}      //���������� �������
            }
        }
        for(register int i =0; i<MyDolznostArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idDolz.compare(MyDolznostArray.Item(i).nameDolznost))
            //{idDolz=MyDolznostArray.Item(i).idDolznost; break;}      //���������� �������
            {idDolz.Clear(); idDolz<<MyDolznostArray.Item(i).idDolznost; break;}      //���������� �������
        }
        if(idUk.IsEmpty()) {idUk=wxUK_DEFAULT;}
        else
        {
            for(register int i =0; i<MyUkRfArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!idUk.compare(MyUkRfArray.Item(i).nameUkRf))
                //{idUk=MyUkRfArray.Item(i).idUkRf; break;}      //���������� �������
                {idUk.Clear(); idUk<<MyUkRfArray.Item(i).idUkRf; break;}      //���������� �������
            }
        }
        for(register int i =0; i<MyRezProvArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idRez.compare(MyRezProvArray.Item(i).nameRezProv))
            //{idRez=MyRezProvArray.Item(i).idRezProv; break;}      //���������� �������
            {idRez.Clear(); idRez<<MyRezProvArray.Item(i).idRezProv; break;}      //���������� �������
        }
        for(register int i =0; i<MyFioSbArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idSotr.compare(MyFioSbArray.Item(i).nameFioSb))
            //{idSotr=MyFioSbArray.Item(i).idFioSb; break;}      //���������� �������
            {idSotr.Clear(); idSotr<<MyFioSbArray.Item(i).idFioSb; break;}      //���������� �������
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
                �������. ���� ����� �����, �� ��������� ������� ���������� �� �������� ��� ��� (��� ��������) � ������� ������.
                ���� ���������� ���� - ������� ���������� ������ � ������������ ������ ������������� ������.
                ���� ����� �� �����, �� ��� �������� ����� � ������ ������� ����� ������ -> �������� ����� ���������
        */
        if(((wxCheckBox*)this->FindWindow(wxID_PR_FZ_COMPARE))->GetValue())
        {
            wxString sqlText;
            if (flag_seriy==1 && flag_number==1) //������ sql ������ ��� ���������� ������
            {
                sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd;
            }
            if (flag_seriy==0 && flag_number==0) //������ sql ������ � ����������� �������
            {
                sqlText<<wxSqlTextSelComparePaspProvSotrToStart;
                sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                sqlText<<number; sqlText<<wxSqlEndText;
            }
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            {
                listFio.Clear();
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                if(num_rows>0)
                {   
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
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
                    mysql_free_result(res); // ������� ����������
                }
                else 
                {
                    mysql_free_result(res); // ������� ����������
                    sqlText.Clear(); //������� ���������� �� ����������� sql �������
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
                        sqlText.Clear(); //������� ���������� �� ����������� sql �������
                        if (flag_seriy==1 && flag_number==1) //������ sql ������ ��� ���������� ������
                        {
                            sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                            sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd1;
                        }
                        if (flag_seriy==0 && flag_number==0) //������ sql ������ � ����������� �������
                        {
                            sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                            sqlText<<fio; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd1;
                            sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                            sqlText<<number; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd2;
                        }
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                        {
                            res = mysql_store_result(conn); // ����� ���������,
                            num_rows = mysql_num_rows(res); // � ���������� �����.
                            if(num_rows>0) // ������ ��������, ��������� ������������ �� ������
                            {
                                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                id_fio=row[0]; 
                            }
                            mysql_free_result(res); // ������� ����������
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
                sqlText.Clear(); //������� ���������� �� ����������� sql �������
                if (flag_seriy==1 && flag_number==1) //������ sql ������ ��� ���������� ������
                {
                    sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                    sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd1;
                }
                if (flag_seriy==0 && flag_number==0) //������ sql ������ � ����������� �������
                {
                    sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                    sqlText<<fio; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd1;
                    sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                    sqlText<<number; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd2;
                }
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                    if(num_rows>0) // ������ ��������, ��������� ������������ �� ������
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        id_fio=row[0]; 
                    }
                    mysql_free_result(res); // ������� ����������
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
    ((wxTextCtrl*)this->FindWindow(wxID_FZ_SER_PASP_TEXTCTRL))->SetMaxLength(4); //������������� ����������� �� ���������� �������� �������� � ���� � ������ ��������   
    ((wxTextCtrl*)this->FindWindow(wxID_FZ_NUM_PASP_TEXTCTRL))->SetMaxLength(6); //������������� ����������� �� ���������� �������� �������� � ���� � ������� ��������
    ((wxCheckBox*)this->FindWindow(wxID_FZ_SPS_PROV_CHECKBOX))->SetValue(true); //������ ������� � ��������
    ((wxTextCtrl*)this->FindWindow(wxID_FZ_FIO_TEXTCTRL))->SetFocus(); //������������� ����� ����� �� ���� � ���
    SetAffirmativeId(wxID_OK);      //������ ������������� ��� ������������� � �������� ������ ��
    type_operation<<type;           //��� ��������
    /*�������� ������������*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*����� � ��������������*/
    if(type==1) 
    {
        select_string<<id1;     //���� �������� ����������,�� ����������� ���������� ����� ���������� ������
        ProvAgFrm *parentWindow = (ProvAgFrm*)this->GetParent();                                //����������� ���������� ��������� �� ������������ ����
        wxListView* listview = ((wxListView*)parentWindow->FindWindow(wxID_AG_SP_LIST_RES));    //�������� ��������� �� ��������� �� ������� ������
        wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
        f->SetId(id1); //������������� ������� ���������� ��������
        f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT); //���������� ������ ��������� � ���������
        listview->GetItem(*f);
        id_fio<<f->GetData(); //����� � ���������� ������ ��������� � ���������
        (old_data.idReestrFio)<<f->GetData(); //������ ������ �� ���������� ������ ��������
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
                old_data.dr = f->GetText(); //������ ������ �� ���������� ������ ��������
                insertStrDateToCtrl (strDrDate, (wxDatePickerCtrl*)this->FindWindow(wxID_FZ_DR_FZ));
            }
        }
        delete f;
    }
}

void EnterFz::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    switch(event.GetId())
    {
        case wxID_FZ_SER_PASP_TEXTCTRL: //��������� � ���� � ��� ������� ������� �������� �� ����
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
        case wxID_FZ_NUM_PASP_TEXTCTRL: //��������� � ���� � �� ������� ������� �������� �� ����
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
void EnterFz::OnButton (wxCommandEvent &event)
{
    if(event.GetId()==wxID_OK)
	{
        wxString fio, seriy, number, dr;
        int flag_sboy=0, flag_seriy=0, flag_number=0;
        
        fio = ((wxTextCtrl*)this->FindWindow(wxID_FZ_FIO_TEXTCTRL))->GetValue();
        seriy = ((wxTextCtrl*)this->FindWindow(wxID_FZ_SER_PASP_TEXTCTRL))->GetValue();
        number = ((wxTextCtrl*)this->FindWindow(wxID_FZ_NUM_PASP_TEXTCTRL))->GetValue();
        if((((wxDatePickerCtrl*)(this->FindWindow(wxID_FZ_DR_FZ)))->GetValue()).IsValid()) //��������� �� ������ �� ���� � �����
        {dr = (((wxDatePickerCtrl*)(this->FindWindow(wxID_FZ_DR_FZ)))->GetValue()).FormatISODate();} //���� �� ������, �� ����������� ���������� ��������
        if(dr.IsEmpty()) {dr=wxSQL_DEFAULT;}
        fio.Trim(true); fio.Trim(false); seriy.Trim(true); seriy.Trim(false); number.Trim(true); number.Trim(false); //������� ������� ������ � �����
        if (fio.IsEmpty()) {InformationSleep(wxINFO_NOT_FIO_SOTR,sec_for_sleep_window_info,this); return;}
        fio.MakeUpper();
        switch(seriy.Len())
        {
            case 0:
            {
                seriy<<wxNULL_;
                flag_seriy=1; //������� ����, ��� ����� ��� ����� ��������
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
                flag_number=1; //������� ����, ��� ����� ��� ������ ��������
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
        
        if(((CrossFrm*)(this->GetGrandParent()))->flag_bl_sb) {if(proverka_bl_sb(conn, fio, 1)==1) {;} else {return;}} //�������� �� �� ��
        
        wxString sqlText;   //���������� ��� ����� sql-�������
        ProvAgFrm *parentWindow = (ProvAgFrm*)this->GetParent();                                //����������� ���������� ��������� �� ������������ ����
        wxListView* listview = ((wxListView*)parentWindow->FindWindow(wxID_AG_SP_LIST_RES));    //�������� ��������� �� ��������� �� ������� ������
        if(!type_operation.compare("0"))                                                 //���� ��� �������� - ����������
        {    
        if(((wxCheckBox*)this->FindWindow(wxID_FZ_SPS_PROV_CHECKBOX))->GetValue())
        {
            if (flag_seriy==1 && flag_number==1) //������ sql ������ ��� ���������� ������
            {
                sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd;
            }
            if (flag_seriy==0 && flag_number==0) //������ sql ������ � ����������� �������
            {
                sqlText<<wxSqlTextSelComparePaspProvSotrToStart;
                sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                sqlText<<number; sqlText<<wxSqlEndText;
            }
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            {
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                int num_fields = mysql_num_fields(res); // ���������� �����
                if(num_rows>0)
                {  
                    parentWindow->count_find+=1; //������ �������� �������� ���-�� ��������� �����.
                    int lastItem=0;
                    for (register int i = 0; i < num_rows; i++) // ����� �������
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT);
                        f->SetColumn(0);
                        f->SetData(wxAtoi(row[0])); //������ ���������� ����
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
                    for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                
                    for(register int i =0; i<listview->GetItemCount();++i) {listview->Select(i,false);} //������� ��������� �����
                    listview->Select(lastItem,true); //�������� ��������� ��������� ������
                    listview->Focus(lastItem); //������������� ����� �� ��������� ��������� ������
                    mysql_free_result(res); // ������� ����������
                }
                else 
                {
                    mysql_free_result(res); // ������� ����������
                    sqlText.Clear(); //������� ���������� �� ����������� sql �������
                    sqlText<<wxSqlTextInsFioAndPasp;
                    sqlText<<fio; sqlText<<wxSqlLeftCaw;
                    sqlText<<seriy; sqlText<<wxSqlCommaText;
                    sqlText<<number; sqlText<<wxSqlCommaText;
                    if(!dr.compare(wxSQL_DEFAULT)) {sqlText<<dr;}
                    else {sqlText<<wxSqlCharStr; sqlText<<dr; sqlText<<wxSqlCharStr;}
                    sqlText<<wxSqlEndRightBracketText;
                    
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                    {
                        sqlText.Clear(); //������� ���������� �� ����������� sql �������
                        if (flag_seriy==1 && flag_number==1) //������ sql ������ ��� ���������� ������
                        {
                            sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                            sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd1;
                        }
                        if (flag_seriy==0 && flag_number==0) //������ sql ������ � ����������� �������
                        {
                            sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                            sqlText<<fio; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd1;
                            sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                            sqlText<<number; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd2;
                        }
                        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                        {
                            res = mysql_store_result(conn); // ����� ���������,
                            num_rows = mysql_num_rows(res); // � ���������� �����.
                            if(num_rows>0)
                            {
                                parentWindow->count_add+=1; //������ �������� �������� ���-�� ����������� �����.  
                                int lastItem=0;
                                for (register int i = 0; i < num_rows; i++) // ����� �������
                                {
                                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                                    wxListItem *f = new wxListItem();
                                    f->SetState(wxLIST_STATE_FOCUSED);
                                    f->SetMask(wxLIST_MASK_TEXT);
                                    f->SetColumn(0);
                                    f->SetData(atoi(row[0])); //������ ���������� ����
                                    f->SetId(i);
                                    listview->InsertItem(*f); 
                                    for (register int l = 1; l < num_fields; l++)
                                    {
                                        listview->SetItem(i,l-1,row[l]);
                                    }
                                    lastItem=i;
                                    delete f;
                                }
                                for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                
                                for(register int i =0; i<listview->GetItemCount();++i) {listview->Select(i,false);} //������� ��������� �����
                                listview->Select(lastItem,true); //�������� ��������� ��������� ������
                                listview->Focus(lastItem); //������������� ����� �� ��������� ��������� ������
                            }
                            mysql_free_result(res); // ������� ����������
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
                sqlText.Clear(); //������� ���������� �� ����������� sql �������
                if (flag_seriy==1 && flag_number==1) //������ sql ������ ��� ���������� ������
                {
                    sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                    sqlText<<fio; sqlText<<wxSqlTextSelCompareFioProvSotrToEnd1;
                }
                if (flag_seriy==0 && flag_number==0) //������ sql ������ � ����������� �������
                {
                    sqlText<<wxSqlTextSelCompareFioProvSotrToStart;
                    sqlText<<fio; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd1;
                    sqlText<<seriy; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd;
                    sqlText<<number; sqlText<<wxSqlTextSelComparePaspProvSotrToEnd2;
                }
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                else
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                    int num_fields = mysql_num_fields(res); // ���������� �����
                    if(num_rows>0)
                    {  
                        parentWindow->count_add+=1; //������ �������� �������� ���-�� ����������� �����.
                        int lastItem=0;
                        for (register int i = 0; i < num_rows; i++) // ����� �������
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[0])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 1; l < num_fields; l++)
                            {
                                listview->SetItem(i,l-1,row[l]);
                            }
                            lastItem=i;
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                
                        for(register int i =0; i<listview->GetItemCount();++i) {listview->Select(i,false);} //������� ��������� �����
                        listview->Select(lastItem,true); //�������� ��������� ��������� ������
                        listview->Focus(lastItem); //������������� ����� �� ��������� ��������� ������
                    }
                    mysql_free_result(res); // ������� ����������
                }
            }
        }}
        if(!type_operation.compare("1"))                                                 //���� ��� �������� - ����������
        {
            sqlText<<wxSqlTextPoiskFzID; //������ �� ��������� ������ ������ �� ������� �� ���������� � ������� � �� (�������� ����� ������ ������������ ����� �������� ������)
            sqlText<<id_fio;
            sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            else
            {
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                int num_fields = mysql_num_fields(res); // ���������� �����
                if(num_rows>0)
                {  
                    wxString strComp("������ ������������ ����� �������� ������."), strfio, strser, strnum, strdr; 
                    int flagFio=0, flagSer=0, flagNum=0, flagDr=0;
                    for (register int i = 0; i < num_rows; i++) // ����� �������
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        strfio=row[0]; strser=row[1]; strnum=row[2]; strdr=row[3];
                        if(old_data.fio.compare(row[0])) {flagFio=1; strComp<<"\n���"; strComp<<"\t������ �������� �� - "; strComp<<strfio;}
                        if(old_data.seriy_pasp.compare(row[1])) {flagSer=1; strComp<<"\n����� ��������"; strComp<<"\t������ �������� �� - "; strComp<<strser;}
                        if(old_data.number_pasp.compare(row[2])) {flagNum=1; strComp<<"\n����� ��������"; strComp<<"\t������ �������� �� - "; strComp<<strnum;}
                        if(old_data.dr.compare(row[3])) {flagDr=1; strComp<<"\n���� ��������"; strComp<<"\t������ �������� �� - "; strComp<<strdr;}   
                    }
                    if (flagFio||flagSer||flagNum||flagDr)
                    {
                        strComp<<"\n\n������ ����� ������������. ���������� ��������?";
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
                mysql_free_result(res); // ������� ����������
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
    
    id_fio<<id_; //����������� ���� ���.���� ���������� �������
    
    SelectInfoFromBD(); //��������� ��������� ����������
    (this->FindWindow(wxID_INS_PR_FZ_BUTTON))->SetFocus(); //������������� ����� ����� �� ������ ��������
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
        int flag_succes=0; //���� ����, ��� � ���������� ���� ���������� �������� ��� ����� ��
        wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
        wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
        /*
        ��������� �� ����� ������������ ������� ���������� ��������� ����.
        ���� ����� �� ����������, ��� ��������� ��������� �� ���������
        */
        long x = config->ReadLong("/FORM_AGENT_PROV_INS/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
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
        if(flag_succes==1) {SelectInfoFromBD(); (this->FindWindow(wxID_UPD_PR_FZ_BUTTON))->SetFocus();} //�������������� ���������� ���������
    }
    if(event.GetId()==wxID_UPD_PR_FZ_BUTTON)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LIST_PR_FZ_LISTVIEW)); //�������� ��������� �� ��������� � ���������� ����������� ��
        int count = 0;
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} //�� ������� ������ ������
        for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
        {
            //wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
            //f->SetId(idItem); //������������� ������� ���������� ��������
            //f->SetMask(wxLIST_MASK_DATA); //���������� ������ ��������� � ���������
            //listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
            //int idProvSotrTo=0; idProvSotrTo=f->GetData(); //����� � ���������� ������ ��������� � ���������
            //if(idProvSotrTo>0)
            //{
                //wxString buffer; buffer<<idProvSotrTo;
                wxString buffer; buffer<<idItem;
                wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
                wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
                /*
                ��������� �� ����� ������������ ������� ���������� ��������� ����.
                ���� ����� �� ����������, ��� ��������� ��������� �� ���������
                */
                long x = config->ReadLong("/FORM_AGENT_PROV_INS/x", 0); //���� �� ������� ������� ��������, �� ����������� ���������� 0
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
            SelectInfoFromBD(); //�������������� ���������� ���������
            wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_UPD_COUNT; str<<count; //������ ������ � ���-��� ����������� �����
            InformationSleep(str,sec_for_sleep_window_info,this);
        } else {;} //���� �� ������� �� ���� ������, �� ������������� �� ���� ������������ � ��������� ���������
        (this->FindWindow(wxID_UPD_PR_FZ_BUTTON))->SetFocus();
    }
}
void ListProvFz::CommentProv (void)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LIST_PR_FZ_LISTVIEW)); //�������� ��������� �� ���������  
        /*
        GetFirstSelected()      - �������� ����� ������� �������� ����������� � ���������
        GetNextSelected(idItem) - �������� ����� ���������� ����������� �������� ����� idItem
        idItem!=-1              - ��� ������ ���������� �����.
        */
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
        for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
        {
            wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
            f->SetId(idItem); //������������� ������� ���������� ��������
            f->SetMask(wxLIST_MASK_DATA); //���������� ������ ��������� � ���������
            listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
            wxString idReestrProvFl; idReestrProvFl<<f->GetData(); //����� � ���������� ������ ��������� � ���������
            if(!idReestrProvFl.IsEmpty())
            {
                
                wxString sqlText = wxSqlTextComProvSotrToStart; sqlText<<idReestrProvFl; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
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
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LIST_PR_FZ_LISTVIEW)); //�������� ��������� �� ��������� � ����������  
        int count = 0;
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
        {
            for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
            {
                wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
                f->SetId(idItem); //������������� ������� ���������� ��������
                f->SetMask(wxLIST_MASK_DATA); //���������� ������ ��������� � ���������
                listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
                wxString idReestrProvFl; idReestrProvFl<<f->GetData(); //����� � ���������� ������ ��������� � ���������
                if(!idReestrProvFl.IsEmpty())
                {
                    wxString sqlText = wxSqlTextDelProvSotrToStart; sqlText<<idReestrProvFl; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                    else 
                    {
                        ++count; //������� ���-�� �����, ������� ���� �������
                    } 
                } else {InformationSleep(wxWARNING_NO_DATA,sec_for_sleep_window_info,this);} 
                delete f;
            }
            if (count>0)
            {
                SelectInfoFromBD(); //�������������� �������� � ����������
                wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_DEL_COUNT; str<<count; //������ ������ � ���-��� ��������� �����
                InformationSleep(str,sec_for_sleep_window_info,this);
                //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
            } else {;} //���� �� ������� �� ���� ������, �� ������������� �� ���� ������������ � ��������� ���������
            (this->FindWindow(wxID_DEL_PR_FZ_BUTTON))->SetFocus();
        }
}
void ListProvFz::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    if(event.GetKeyCode()==13) //������ ������ Enter
    {
        this->EndModal(wxID_OK);
        event.Skip(false);
    }
    if(event.GetKeyCode()==WXK_ESCAPE) //������ ������ Esc
    {
        this->EndModal(wxID_CANCEL);
        event.Skip(false);
    }    
        else {event.Skip(true);}
}

void ListProvFz::SelectInfoFromBD(void)
{
    wxListView *listview = ((wxListView*)this->FindWindow(wxID_LIST_PR_FZ_LISTVIEW)); //�������� ��������� �� ��������� � ����������
    listview->DeleteAllItems(); //������� ��������� �� ���� ���������
    wxString sqlText;
    sqlText<<wxSqlTextSelProvFzStart;
    sqlText<<id_fio; sqlText<<wxSqlEndText;
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
                f->SetMask(wxLIST_MASK_TEXT);
                f->SetColumn(0);
                f->SetData(atoi(row[0])); //������ ���������� ����
                f->SetId(i);
                listview->InsertItem(*f); 
                for (register int l = 1; l < num_fields; l++)
                {
                    if(l==1)
                    {
                        wxString buff; buff=row[l];
                        if(!buff.IsEmpty())
                        {
                            for(register int k =0; k<MyGcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                            {
                                //if(atoi(MyGcArray.Item(k).idGc.c_str())==wxAtoi(buff)) //���������� �������
                                if(MyGcArray.Item(k).idGc==wxAtoi(buff)) //���������� �������
                                {   
                                    listview->SetItem(i,l-1,MyGcArray.Item(k).nameGc);
                                    break; //������� �� ���������� �����
                                }
                            }
                        }
                    }
                    if(l==2) {listview->SetItem(i,l-1,row[l]);}
                    if(l==3)
                    {
                        for(register int k =0; k<MyDolznostArray.GetCount();++k) //��������� ���� ������ � ����������� 
                        {
                            //if(atoi(MyDolznostArray.Item(k).idDolznost.c_str())==atoi(row[l])) //���������� �������
                            if(MyDolznostArray.Item(k).idDolznost==wxAtoi(row[l])) //���������� �������
                            {
                                listview->SetItem(i,l-1,MyDolznostArray.Item(k).nameDolznost);
                                break; //������� �� ���������� �����
                            }
                        }
                    }
                    if(l==4)
                    {
                        for(register int k =0; k<MyUkRfArray.GetCount();++k) //��������� ���� ������ � ����������� 
                        {
                            //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //���������� �������
                            if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //���������� �������
                            {
                                listview->SetItem(i,l-1,MyUkRfArray.Item(k).nameUkRf);
                                break; //������� �� ���������� �����
                            }
                        }
                    }
                    if(l==5)
                    {
                        for(register int k =0; k<MyRezProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                        {
                            //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //���������� �������
                            if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //���������� �������
                            {
                                listview->SetItem(i,l-1,MyRezProvArray.Item(k).nameRezProv);
                                break; //������� �� ���������� �����
                            }
                        }
                    }
                    if(l==6)
                    {
                        for(register int k =0; k<MyFioSbArray.GetCount();++k) //��������� ���� ������ � ����������� 
                        {
                            //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //���������� �������
                            if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //���������� �������
                            {
                                listview->SetItem(i,l-1,MyFioSbArray.Item(k).nameFioSb);
                                break; //������� �� ���������� �����
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
                listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� ��������
            }  
            listview->Select(num_rows-1);  
        }
        mysql_free_result(res); // ������� ����������
    }    
}
void ListProvFz::OnSize(wxSizeEvent& event) //����� ������� ���� �� ����� ������� ��������� ������ ��� ������ �������
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
void ListProvFz::OnMove(wxMoveEvent& event) //����� ������� ���� �� ����� ������� ������������ ����
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
    EVT_LIST_ITEM_FOCUSED(wxID_LISTTO_PR_FZ_LISTVIEW, InsProvFz::SelectItemListView) //���������� ��� ����������� ���������� ������ � ��������
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
    
    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
    LocArray.Alloc(MyGcArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int j =0; j<MyGcArray.GetCount();++j)   //��������� ��������� ������
    {
        //if(!MyGcArray.Item(j).activGc.compare("1")) {LocArray.Add(MyGcArray.Item(j).nameGc);}
        if(MyGcArray.Item(j).activGc==1) {LocArray.Add(MyGcArray.Item(j).nameGc);}
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MyDolznostArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyDolznostArray.GetCount();++i) //��������� ��������� ������ 
    {
        LocArray.Add((MyDolznostArray.Item(i).nameDolznost));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMEDL_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MyUkRfArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyUkRfArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyUkRfArray.Item(i).nameUkRf));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMEUK_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MyRezProvArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
    for(register int i =0; i<MyRezProvArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyRezProvArray.Item(i).nameRezProv));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMERZ_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    LocArray.Alloc(MyFioSbArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������
    for(register int i =0; i<MyFioSbArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
    {
        LocArray.Add((MyFioSbArray.Item(i).nameFioSb));
    }
    ((wxTextCtrl*)this->FindWindow(wxID_NAMESB_PR_FZ_TEXTCTRL))->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    id_fio=id_fio_; //����������� ���������� ������� ���� �������
    /*�������� ������������*/
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL , (int) 13, wxID_OK);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    /*����� � ��������������*/
    //(this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->MoveAfterInTabOrder(this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL));
    //(this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL))->MoveAfterInTabOrder(this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW));
    //(this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW))->MoveAfterInTabOrder(this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL));
    (this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->SetFocus();
    if(!idItem.IsEmpty())
    {
        idItemListView=idItem; //����������� ���������� ������� ����� ��������� ������ � ������� � ����������
        ListProvFz *parentWindow = (ListProvFz*)this->GetParent();
        wxListView *listview = ((wxListView*)parentWindow->FindWindow(wxID_LIST_PR_FZ_LISTVIEW));  
        wxListItem *f = new wxListItem();  
        f->SetId(wxAtoi(idItem));  
        f->SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT);  
        listview->GetItem(*f);  
        int idProvSotrTo=0; idProvSotrTo=f->GetData();  
        if(idProvSotrTo>0)
        {
            id_prov_fz<<idProvSotrTo; //����������� ���������� ������� ���� �������� �������
            f->SetColumn(0); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMEGC_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(1); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMETO_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(2); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMEDL_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(3); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMEUK_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(4); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMERZ_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText()); 
            f->SetColumn(5); listview->GetItem(*f);((wxTextCtrl*)this->FindWindow(wxID_NAMESB_PR_FZ_TEXTCTRL))->ChangeValue(f->GetText());
            f->SetColumn(6); listview->GetItem(*f);
            wxString str=f->GetText(); //����� ���� �� ���������� ������� ������� � ����������
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
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                if(num_rows>0)
                {  
                    //for (register int i = 0; i < num_rows; i++) // ����� �������
                    //{
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
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
                mysql_free_result(res); // ������� ���������� 
            }
            
            
            
        } else {InformationSleep(wxWARNING_NO_DATA,sec_for_sleep_window_info,this);}
        delete f;
    }
    /*if(((wxTextCtrl*)this->FindWindow(wxID_COMMEN_PR_FZ_TEXTCTRL))->IsEmpty()) //���� ���� � ������������ ������, �� ��������� ���
    {
        wxString strComm = this->GetLabel();
        EditStringFio (strComm); //������� ����������� ������ wxString ����� ������ ���� �������� �� ������ �.�.
        ((wxTextCtrl*)this->FindWindow(wxID_COMMEN_PR_FZ_TEXTCTRL))->ChangeValue(strComm);
    }*/
}

void InsProvFz::NewFocus(wxChildFocusEvent& event)
{
    if(idWindowFocus==wxID_LISTTO_PR_FZ_LISTVIEW)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW)); //�������� ��������� �� ��������� � ����������
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

void InsProvFz::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    switch(event.GetId())
    {
        case wxID_NAMETO_PR_FZ_TEXTCTRL: //����� ������� ��� � ���� � ������������� �� ��������� ��������.
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //���� ����� ����, ������ ��� ����, �� ���������� ������� ����� � ��������
                {event.Skip(true);} 
                else {
                    if(event.GetKeyCode()==WXK_TAB)
                        {
                            wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW)); //�������� ��������� �� ��������� � ����������
                            completeListView(); 
                            listview->SetFocus(); 
                            event.Skip(false);
                        }
                    else {event.Skip(true);}
                }
                break;
            }
        case wxID_LISTTO_PR_FZ_LISTVIEW: //��������� � ���� � ��� ������� ������� �������� �� ����
            {
                if(event.ControlDown()||event.ShiftDown()||event.AltDown()) //���� ����� ����, ������ ��� ����, �� ���������� ������� ����� � ��������
                {event.Skip(true);} 
                else {
                    if(event.GetKeyCode()==WXK_TAB)
                        {
                            wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW)); //�������� ��������� �� ��������� � ����������
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
        case wxID_COMMEN_PR_FZ_TEXTCTRL: //������� ������ �� ���� � ������������
            /*{
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //���� ����� ctrl+z
                {
                    wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                    ((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)(this->GetGrandParent())->GetParent())->fastComment); //��������� ����� �� ������-����� ����������� � ���� � ������� �����          
                }
                event.Skip(true); 
                break;
            }*/
            {
                if(event.ControlDown()&&event.GetKeyCode()=='Z') //���� ����� ctrl+z
                {
                    if(wxTheClipboard->Open()) //��������� ����� ������
                    {
                        wxTheClipboard->SetData(new wxTextDataObject(((CrossFrm*)((this->GetGrandParent())->GetGrandParent())->GetParent())->fastComment)); //�������� � ����� ������ ����� �� ������ ����� ����������� ����
                        if(wxTheClipboard->IsSupported(wxDF_TEXT)) //���������� ����� , ���� ���� ������ , ������� ������������� ������� ������ ������ wxDF_TEXT
                        {
                            wxTextDataObject textData; //������� ������ ��� ����������� ������ �� ������ ������
                            wxTheClipboard->GetData(textData); //��������� ����� �� ������ ������ � ������-��������
                            //if((wxWindow::FindFocus())->GetId()==wxID_PR_COMMENT) //��������� ��, ��� ����� ����� ��������� � ���� ��� �����������
                            {
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(textData.GetText()); //��������� � ���� � ������������ ����� �� �������.
                                wxString str = ((wxTextCtrl*)wxWindow::FindFocus())->GetValue();
                                //((wxTextCtrl*)wxWindow::FindFocus())->ChangeValue(str + ((CrossFrm*)this->GetGrandParent())->fastComment); //��������� ����� �� ������-����� ����������� � ���� � ������� �����  
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
wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTTO_PR_FZ_LISTVIEW)); //�������� ��������� �� ��������� � ����������
                            listview->DeleteAllItems(); //������� ��������� �� ���� ���������
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
                                            f->SetMask(wxLIST_MASK_TEXT);
                                            f->SetColumn(0);
                                            f->SetData(atoi(row[0])); //������ ���������� ����
                                            f->SetId(i);
                                            listview->InsertItem(*f); 
                                            for (register int l = 0; l < num_fields; l++)
                                            {
                                                listview->SetItem(i,l,row[l]);
                                            }
                                            delete f;
                                        }
                                        for (register int i = 0; i < listview->GetColumnCount(); i++) // ����� �������
                                        {
                                            listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� ��������
                                        }
                                        textBunner = wxCOUNT_STRING; textBunner<<listview->GetItemCount();
                                        ((wxBannerWindow*)this->FindWindow(wxID_ITOG_PR_FZ_BANNER))->SetText(textBunner, wxNULL_STRING);
                                    }
                                    mysql_free_result(res); // ������� ����������
                                }
                            }
}

void InsProvFz::OnSize(wxSizeEvent& event) //����� ������� ���� �� ����� ������� ��������� ������ ��� ������ �������
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
void InsProvFz::OnMove(wxMoveEvent& event) //����� ������� ���� �� ����� ������� ������������ ����
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
    wxString str=wxSELECT_STRING;   //����� � ���������� �������� ����������� ��������
    str<<(event.GetIndex()+1);      //���������� ������ ���������� ������, ���������� 1 � ���������� � ����������.
    ((wxBannerWindow*)this->FindWindow(wxID_ITOG_PR_FZ_BANNER))->SetText(textBunner, str); //������������ �������� �������
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
            for(register int i =0; i<MyGcArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                //if (!idGc.compare(MyGcArray.Item(i).nameGc)&&(!MyGcArray.Item(i).activGc.compare("1")))
                //{idGc=MyGcArray.Item(i).idGc; break;}      //���������� �������
                if (!idGc.compare(MyGcArray.Item(i).nameGc)&&(MyGcArray.Item(i).activGc==1))
                {idGc.Clear(); idGc<<MyGcArray.Item(i).idGc; break;}      //���������� �������
            }
        } 
        for(register int i =0; i<MyDolznostArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idDolz.compare(MyDolznostArray.Item(i).nameDolznost))
            //{idDolz=MyDolznostArray.Item(i).idDolznost; break;}      //���������� �������
            {idDolz.Clear(); idDolz<<MyDolznostArray.Item(i).idDolznost; break;}      //���������� �������
        }
        if(idComm.IsEmpty()) {idComm=wxNULL_STRING;} 
        if(idUk.IsEmpty()) {idUk=wxUK_DEFAULT;}
        else
        {
            for(register int i =0; i<MyUkRfArray.GetCount();++i)       //��������� ���� ������ ���������� 
            {
                if (!idUk.compare(MyUkRfArray.Item(i).nameUkRf))
                //{idUk=MyUkRfArray.Item(i).idUkRf; break;}      //���������� �������
                {idUk.Clear(); idUk<<MyUkRfArray.Item(i).idUkRf; break;}      //���������� �������
            }
        }
        for(register int i =0; i<MyRezProvArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idRez.compare(MyRezProvArray.Item(i).nameRezProv))
            //{idRez=MyRezProvArray.Item(i).idRezProv; break;}      //���������� �������
            {idRez.Clear(); idRez<<MyRezProvArray.Item(i).idRezProv; break;}      //���������� �������
        }
        for(register int i =0; i<MyFioSbArray.GetCount();++i)       //��������� ���� ������ ���������� 
        {
            if (!idSotr.compare(MyFioSbArray.Item(i).nameFioSb))
            //{idSotr=MyFioSbArray.Item(i).idFioSb; break;}      //���������� �������
            {idSotr.Clear(); idSotr<<MyFioSbArray.Item(i).idFioSb; break;}      //���������� �������
        }
        if(idDolz.IsNumber()||idUk.IsNumber()||idRez.IsNumber()||idSotr.IsNumber()) {} else {InformationSleep(wxINFO_NOT_SPRAVOCHNIK_STRING,sec_for_sleep_window_info,this); return;}
        wxString sqlText;
        if (idItemListView.IsEmpty())
        {
            int flagInsert=0; //���� ����, ��� ����� �������� ������ � ��
            sqlText<<wxSqlTextSelProvSotrToID; sqlText<<id_fio; sqlText<<wxSqlAnd;
            sqlText<<wxSqlTextSelProvSotrToID1; sqlText<<idTo; sqlText<<wxSqlAnd;
            sqlText<<wxSqlTextSelProvSotrToID2; sqlText<<idDolz; sqlText<<wxSqlAnd;
            sqlText<<wxSqlTextSelProvSotrToID3; sqlText<<wxSqlCharStr; sqlText<<idData; sqlText<<wxSqlCharStr;  sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
            else
            {
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                if(num_rows>0)
                {
                    if(wxMessageBox("������� ���� ��������� �������� ����������� ���� �� ������� ����������� ��������. ���������� �� ���, ��, ���������, ����. ���������� ��������?",wxATTENTION,wxYES_NO, this)==wxYES)
                    {flagInsert=1;}
                }
                else {flagInsert=1;}
                mysql_free_result(res); // ������� ����������
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
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                if(num_rows>0)
                {  
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
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
                        strComp<<"������ ������������ ������� ������� ������ � ������ ���������. ��������� ���� ������� � ��������� ����:";
                        if(flagGc) {strComp<<"\n��";}
                        if(flagTo) {strComp<<"\n��";}
                        if(flagDolz) {strComp<<"\n���������";}
                        if(flagUk) {strComp<<"\n��.�� ��";}
                        if(flagRez) {strComp<<"\n��������� ��������";}
                        if(flagSotr) {strComp<<"\n��� ���������� ��";}
                        if(flagData) {strComp<<"\n���� ��������";}
                        if(flagArhiv) {strComp<<"\n������� ������";}
                        strComp<<"\n\n������ ����� ������������. ���������� ���������� ��������?";
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
                mysql_free_result(res); // ������� ���������� 
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
    EVT_CHAR_HOOK(PoiskToDialog::OnChar) //����������� ������� ������
    EVT_SEARCHCTRL_CANCEL_BTN(wxID_PS_SEARCHCTRL_POISK, PoiskToDialog::ClearPoisk) //����������� ������� �������� � ���� ������
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
    ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK))->SetDescriptiveText(wxString("������� �������� ��� ������ � ������� Enter ...")); //����� �� ��������� � ������ ������
    ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK))->ShowCancelButton(1); //������ �������� ������ ������
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
    ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK))->Clear(); //������� ���� ������
    
}

void PoiskToDialog::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    if(event.GetKeyCode()==13) //������ ������ Enter
    {
        wxSearchCtrl *searchCtrl = ((wxSearchCtrl*)this->FindWindow(wxID_PS_SEARCHCTRL_POISK));
        wxRadioBox   *radioBoxPole = ((wxRadioBox*)this->FindWindow(wxID_PS_RADIOBOX_NAME));
        wxRadioBox   *radioBoxType = ((wxRadioBox*)this->FindWindow(wxID_PS_RADIOBOX_TYPE));
        wxListView   *listview = ((wxListView*)this->FindWindow(wxID_PS_LISTVIEW_RESULT));
        if(!searchCtrl->IsEmpty())
        {
            wxString textPoisk = searchCtrl->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
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
                            listview->SetItem(i,l-1,row[l]);
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
    if(event.GetKeyCode()==WXK_ESCAPE) //������ ������ Esc
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
    
     
    wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
    f->SetId(idItem); //������������� ������� ���������� ��������
    f->SetColumn(1); //������� ������������� ��
    f->SetMask(wxLIST_MASK_TEXT); //���������� ������ ��������� � ���������
    listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
    ((wxTextCtrl*)parentWindow->FindWindow(wxID_TO_INN))->ChangeValue(f->GetText()); //����� � ��������� ���� ������������� ���� ��������� ���
    delete f; //������� ������
    wxCommandEvent event_local; //������� ������ ������ �������
    event_local.SetId(wxID_BUTTON_INN_TO); //������������� ������������� ��������� � ���� ��������
    event_local.SetEventType(wxEVT_COMMAND_BUTTON_CLICKED); //������������� ��� �������
    parentWindow->ProcessWindowEventLocally(event_local); //��������� ��� ������� ���� ����� ����������� ����������� ��� ������� event_local
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
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_fields = mysql_num_fields(res); // ���������� �����
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {   
            
            for (register int i = 0; i < num_rows; i++) // ����� �������
            {
                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                HashTypeCompany[wxString(row[0])]=wxAtoi(row[1]); //��������� � ����������� ����/��������
            }
        }
        mysql_free_result(res); // ������� ����������
    }
    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
    for(register hash_map::iterator i = HashTypeCompany.begin();i!=HashTypeCompany.end();++i){LocArray.Add(i->first);}
    textCtrl1->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    
    if(id_operation==1) {this->SetLabel(wxCAPTION_DIALOG_1);} //������ ����� ���� � ����������� �� ������� ������, ��������� ������
    if(id_operation==2) 
    {
        this->SetLabel(wxCAPTION_DIALOG_2); //������ ����� ���� � ����������� �� ������� ������, ��������� ������
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
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                //int num_fields = mysql_num_fields(res); // ���������� �����
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                if(num_rows>0)
                {   
                    //for (register int i = 0; i < num_rows; i++) // ����� �������
                    //{
                        int item_number = listview_company->GetItemCount(); //���������� ����� ���������� �������� ��� ������� ������
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                        f->SetColumn(0);
                        f->SetData(wxAtoi(row[0])); //������ ���������� ����
                        f->SetId(item_number);
                        listview_company->InsertItem(*f); 
                        listview_company->SetItem(item_number,0,textName);
                        listview_company->SetItem(item_number,1,textType);
                        delete f;
                    //}
                }
                mysql_free_result(res); // ������� ����������
                for (register int i=0; i<(listview_company->GetColumnCount());++i) {listview_company->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������      
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
        MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
        int num_fields = mysql_num_fields(res); // ���������� �����
        int num_rows = mysql_num_rows(res); // � ���������� �����.
        if(num_rows>0)
        {   
            
            for (register int i = 0; i < num_rows; i++) // ����� �������
            {
                MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                wxString str; str=row[0]; str.MakeUpper();
                str.Trim(false); str.Trim(true); //����� �����������. � �������� ��������� ��������� ������ \n
                HashNameRegion[str]=wxAtoi(row[1]); //��������� � ����������� ����/��������
            }
        }
        mysql_free_result(res); // ������� ����������
    }
    
    wxArrayString LocArray; //��������� ������ ��� �������������� � ��������� ����
    for(register hash_map::iterator i = HashNameRegion.begin();i!=HashNameRegion.end();++i){LocArray.Add(i->first);}
    textCtrl2->AutoComplete(LocArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
    LocArray.Clear(); //������� ���������� ������� � ����������� ������
    
    if(id_operation==1) {this->SetLabel(wxCAPTION_DIALOG_3);} //������ ����� ���� � ����������� �� ������� ������, ��������� ������
    if(id_operation==2) 
    {
        this->SetLabel(wxCAPTION_DIALOG_4); //������ ����� ���� � ����������� �� ������� ������, ��������� ������
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
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                //int num_fields = mysql_num_fields(res); // ���������� �����
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                if(num_rows>0)
                {   
                    for (register int i = 0; i < num_rows; i++) // ����� �������
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        textCtrl6->ChangeValue(row[0]);
                    }
                }
                mysql_free_result(res); // ������� ����������
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
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                //int num_fields = mysql_num_fields(res); // ���������� �����
                int num_rows = mysql_num_rows(res); // � ���������� �����.
                if(num_rows>0)
                {   
                    //for (register int i = 0; i < num_rows; i++) // ����� �������
                    //{
                        int item_number = listview_fio->GetItemCount(); //���������� ����� ���������� �������� ��� ������� ������
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                        f->SetColumn(0);
                        f->SetData(wxAtoi(row[0])); //������ ���������� ����
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
                mysql_free_result(res); // ������� ����������
                for (register int i=0; i<(listview_fio->GetColumnCount());++i) {listview_fio->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������      
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
                    for (register int i=0; i<(listview_fio->GetColumnCount());++i) {listview_fio->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������       
                }
            }
        this->EndModal(wxID_OK); 
        }}            
    }
}
void UpdateFioContactDialog::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    switch(event.GetId())
    {
        case wxID_K_DIL_TC_PRONE: //��������� � ���� � ��� ������� ������� �������� �� ����
        case wxID_K_DIL_TC_DOB: //��������� � ���� � ��� ������� ������� �������� �� ����
        case wxID_K_DIL_TC_DOP_PF: //��������� � ���� � ��� ������� ������� �������� �� ����
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
        default:{event.Skip(true); break;}
    }
}
UpdateFioContactDialog::~UpdateFioContactDialog()
{
}  

/*
Dialog - UpdateFioContactDialog - end
*/
