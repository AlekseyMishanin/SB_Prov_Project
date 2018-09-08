#include "CrossFrm.h"

extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;
extern int proverka_bl_sb(MYSQL* conn, wxString& str, int type); //������� ��������� str �� ������� ������� � �� ��. type - ��� �� �� ��� ��������, 0 - ��, 1 - ������

//extern ProvToFrm* frame_to;

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
extern PositionSotrArray MyPositionSotrArray; //������ ������ ���������� � ���������

BEGIN_EVENT_TABLE(ProvToFrm,wxPanel)
	EVT_CLOSE(ProvToFrm::OnClose)
	EVT_CHAR_HOOK(ProvToFrm::OnChar)
	//EVT_SIZE(ProvToFrm::OnSize)
	//EVT_MOVE_END(ProvToFrm::OnMove)
	EVT_COMBOBOX(wxID_TO_FLAG_INET,ProvToFrm::OnComboBox)
	EVT_TOGGLEBUTTON(wxID_BUTTON_SP_ASRT,ProvToFrm::OnButton)
	EVT_TOGGLEBUTTON(wxID_BUTTON_SP_PROV,ProvToFrm::OnButton)
	EVT_TOGGLEBUTTON(wxID_BUTTON_SP_SOTR,ProvToFrm::OnButton)
	EVT_TOGGLEBUTTON(wxID_BUTTON_KT_KONTRACT,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_INS_TO,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_UPD_TO,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_DEL_TO,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_CLR_TO,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_INN_TO,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_INS_ASRT,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_DEL_ASRT,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_INS_PROV,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_UPD_PROV,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_DEL_PROV,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_KOM_PROV,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_INS_SOTR,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_UPD_SOTR,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_DEL_SOTR,ProvToFrm::OnButton)
	EVT_BUTTON(wxID_BUTTON_KOM_SOTR,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_INS_ASRT,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_DEL_ASRT,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_INS_PROV,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_UPD_PROV,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_DEL_PROV,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_KOM_PROV,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_INS_SOTR,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_UPD_SOTR,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_DEL_SOTR,ProvToFrm::OnButton)
	EVT_MENU(wxID_BUTTON_KOM_SOTR,ProvToFrm::OnButton)	
	EVT_TEXT(wxID_TO_BRAND,ProvToFrm::OnTextCtrl)
	EVT_CHOICE(wxID_CHOISE_COOPERATION, ProvToFrm::ChangeChoice)
END_EVENT_TABLE()


ProvToFrm::ProvToFrm(wxWindow *parent, wxWindowID id, /*const wxString &title,*/ const wxPoint& pos, const wxSize& size , long style )
        : wxPanel(parent, id, /*title,*/ pos, size, style)
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
        //wxMenuBar *menubar = new wxMenuBar;
	    //wxMenu *file_menu = new wxMenu;
        //file_menu->Append(wxID_MENU_FILE_POISK, "&�����");
	    //menubar->Append(file_menu, "&����");
	    //SetMenuBar(menubar);
	    //Connect(wxID_MENU_FILE_POISK, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(ProvToFrm::OnMenu));
	            
        //this = new wxPanel(this,wxID_ANY);
        wxString str_full, str_first, str_last;
        vert = new wxBoxSizer(wxVERTICAL);
        
        
        
        stBoxCooperation = new wxStaticBox(this,wxID_STBOX_COOPERATION,"��� ��������������");
        to_static_box_cooperation = new wxStaticBoxSizer(stBoxCooperation,wxHORIZONTAL);
        wxString strTypeCoop[] = {"POS","���������� ������","��������-���������","����� ������","����������","���", "�� �� ������ ��������"}; //������� ����������� ������ � ������ ��������������
        type_cooperation = new wxChoice(this,wxID_CHOISE_COOPERATION,wxDefaultPosition, wxDefaultSize, sizeof(strTypeCoop)/sizeof(wxString),strTypeCoop);
        to_static_box_cooperation->Add(type_cooperation,1,wxEXPAND|wxALL,5); //������� ������� ���������� � ������ ��������������
        type_cooperation->SetSelection(0); //�������� �� ������ ������ ������
        
        
        stBox1 = new wxStaticBox(this,wxID_STBOX_CARD_TO,"�������� ��");
        stBox1_1 = new wxStaticBox(this,wxID_STBOX_COMMAND,"�������");
        stBox2 = new wxStaticBox(this,wxID_STBOX_PARAM_TO,"��������� ��");

        to_static_box1 = new wxStaticBoxSizer(stBox1,wxVERTICAL);
        to_static_box2 = new wxStaticBoxSizer(stBox2,wxVERTICAL);
        to_static_box1_1 = new wxStaticBoxSizer(stBox1_1,wxVERTICAL);

        to_1 = new wxBoxSizer(wxHORIZONTAL);
        to_2 = new wxBoxSizer(wxHORIZONTAL);
        
        to_1->Add(new wxStaticText(this,wxID_TO_STATICBOX_INN,wxCAPTION_COLUMN_INN), 0,wxEXPAND |wxALL,0);
        to_1->Add(new wxTextCtrl(this,wxID_TO_INN, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT,5);
        ((wxTextCtrl*)this->FindWindow(wxID_TO_INN))->SetMaxLength(12); //������������� ����������� �� ���������� �������� �������� � ���� � ���        
        str_first = dir.GetName(); str_last= wxSEE_ICO; str_full=str_first; str_full+=str_last;
        wxImage *image = new wxImage(str_full,wxBITMAP_TYPE_ICO);
        image->Rescale(16,16);
        to_1->Add(new wxBitmapButton(this,wxID_BUTTON_INN_TO, wxBitmap(*image), wxDefaultPosition,wxSize(24,24)),0, wxEXPAND|wxALL,0);
        to_2->Add(new wxStaticText(this,wxID_TO_STATICBOX_TO,wxCAPTION_COLUMN_TO),0, wxEXPAND|wxALL,0);
        to_2->Add(new wxTextCtrl(this,wxID_TO_NAME, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT,5);
        
        /*���������*/
        ((wxTextCtrl*)this->FindWindow(wxID_TO_INN))->SetHint(wxString("������� ���"));
        ((wxTextCtrl*)this->FindWindow(wxID_TO_NAME))->SetHint(wxString("������� ������������ ��/��"));
        
        /***********/
        to_static_box1->Add(to_1, 0, wxEXPAND|wxALIGN_CENTRE_VERTICAL,0);
        to_static_box1->Add(to_2, 0, wxEXPAND,0);
        
        
        to_static_box1_1->Add(new wxButton(this,wxID_BUTTON_INS_TO,wxCAPTION_BUTTON_INSERT), 0, wxEXPAND,0);
        to_static_box1_1->Add(new wxButton(this,wxID_BUTTON_UPD_TO,wxCAPTION_BUTTON_UPDATE), 0, wxEXPAND,0);
        to_static_box1_1->Add(new wxButton(this,wxID_BUTTON_DEL_TO,wxCAPTION_BUTTON_DELETE), 0, wxEXPAND,0);
        to_static_box1_1->Add(new wxButton(this,wxID_BUTTON_CLR_TO,wxCAPTION_BUTTON_CLEAR), 0, wxEXPAND,0);
        hr1 = new wxBoxSizer(wxHORIZONTAL);
        vert = new wxBoxSizer(wxVERTICAL);

        
        to_static_box2->Add(new wxToggleButton(this,wxID_BUTTON_SP_PROV,wxCAPTION_BUTTON_PROV), 0, wxEXPAND|wxALL,0);
        to_static_box2->Add(new wxToggleButton(this,wxID_BUTTON_SP_SOTR,wxCAPTION_BUTTON_SOTR), 0, wxEXPAND|wxALL,0);
        hr1->Add(to_static_box1, 1, wxEXPAND,0);
        hr1->Add(to_static_box1_1, 0, wxEXPAND,0);
        hr1->Add(to_static_box2, 0, wxEXPAND,0);
        id_to=0;

        vert->Add(to_static_box_cooperation, 0, wxEXPAND|wxALL,0);
        vert->Add(hr1, 0, wxEXPAND|wxALL,5);
        this->SetSizer(vert);
        //this->CreateStatusBar(3,wxSTB_DEFAULT_STYLE,wxID_TO_STATUSBAR);
              
        wxCommandEvent event_local; //������� ������ ������ �������
        event_local.SetId(wxID_CHOISE_COOPERATION); //������������� ������������� ��������� � ���� ��������
        event_local.SetEventType(wxEVT_COMMAND_CHOICE_SELECTED); //������������� ��� �������
        this->ProcessWindowEventLocally(event_local); //��������� ��� ������� ���� ����� ����������� ����������� ��� ������� event_local
    
        
        //wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
        //for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) {(*it)->SetBackgroundColour(*wxWHITE);} //����� �������� ���������� ��� ���� � ������ ���� ����
        /*wxWindowList list1 = panel->GetChildren(); //�������� ������ ���� �������� ����
        //for(register wxWindowList::const_iterator it = list1.begin(); it!=list1.end(); ++it) {(*it)->SetBackgroundColour(*wxWHITE);} //����� �������� ���������� ��� ���� � ������ ���� ����
        for(register wxWindowList::const_iterator it = list1.begin(); it!=list1.end(); ++it) 
        {
            if(((*it)->GetId())==) {wxMessageBox("dfdf");}
            
        }*/
        //Center(); //������������ ����
                
    }
}

void ProvToFrm::ChangeChoice (wxCommandEvent& event)
{
    switch (event.GetId())
    {
        case wxID_CHOISE_COOPERATION:
        {
            switch (type_cooperation->GetSelection())
            {
                case 0: //���
                {
                    wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
                    for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) 
                    {
                        if
                        (
                        ((*it)->GetId())==wxID_STBOX_COOPERATION||
                        ((*it)->GetId())==wxID_STBOX_CARD_TO||
                        ((*it)->GetId())==wxID_STBOX_COMMAND||
                        ((*it)->GetId())==wxID_STBOX_PARAM_TO||
                        ((*it)->GetId())==wxID_CHOISE_COOPERATION||
                        ((*it)->GetId())==wxID_TO_STATICBOX_TO||
                        ((*it)->GetId())==wxID_TO_STATICBOX_INN||
                        ((*it)->GetId())==wxID_TO_INN||
                        ((*it)->GetId())==wxID_BUTTON_INN_TO||
                        ((*it)->GetId())==wxID_TO_NAME||
                        ((*it)->GetId())==wxID_BUTTON_INS_TO||
                        ((*it)->GetId())==wxID_BUTTON_UPD_TO||
                        ((*it)->GetId())==wxID_BUTTON_DEL_TO||
                        ((*it)->GetId())==wxID_BUTTON_CLR_TO||
                        ((*it)->GetId())==wxID_BUTTON_SP_PROV||
                        ((*it)->GetId())==wxID_BUTTON_SP_SOTR
                        ) 
                        {
                            
                            if(((*it)->GetId())==wxID_BUTTON_SP_PROV) {((wxToggleButton*)(*it))->SetValue(false);} //��������� ������ � �� ������� ���������
                            if(((*it)->GetId())==wxID_BUTTON_SP_SOTR) {((wxToggleButton*)(*it))->SetValue(false);} //��������� ������ � �� ������� ���������
                        } else {(*it)->Destroy();}     //��������� ������� ����������
                    }
                    to_3 = new wxBoxSizer(wxHORIZONTAL);
                    to_4 = new wxBoxSizer(wxHORIZONTAL);
                    to_5 = new wxBoxSizer(wxHORIZONTAL);
                    to_6 = new wxBoxSizer(wxHORIZONTAL);
                    to_7 = new wxBoxSizer(wxHORIZONTAL);
        
                    to_3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_NET),0,wxEXPAND |wxALL,0);
                    to_3->Add(new wxTextCtrl(this,wxID_TO_BRAND, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT|wxRIGHT,5);
                    wxArrayString LocBrendArray; //��������� ������ ��� �������������� � ��������� ����
                    LocBrendArray.Alloc(MyBrandNameArray.GetCount());  //����������� ���������� ������ ��� �������� nCount ���������   
                    for(register int i =0; i<MyBrandNameArray.GetCount();++i) //��������� ��������� ������ �������������� �������� �����
                    {
                        LocBrendArray.Add((MyBrandNameArray.Item(i).nameBrandName));
                    }
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->AutoComplete(LocBrendArray); //���������� � ���������� ���� ������� ��������������� ���������� ������
                    to_3->Add(new wxStaticText(this,wxID_TO_TYPE_BRAND,wxBRAND_DEFAULT),0, wxEXPAND |wxALL,0);
                    to_4->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_COUNT_TT),0, wxEXPAND |wxALL,0);
                    to_4->Add(new wxTextCtrl(this,wxID_TO_KOL_TT, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT,5);
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_KOL_TT))->SetMaxLength(4); //������������� ����������� �� ���������� �������� �������� � ���� � ���-��� ��
                    to_5->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_BANK_KONK),0, wxEXPAND |wxALL,0);
                    to_5->Add(new wxTextCtrl(this,wxID_TO_BANK_KONK, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT,5);
                    to_6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_INET_SALES),0, wxEXPAND |wxALL,0);
                    to_6->Add(new wxComboBox(this,wxID_TO_FLAG_INET, wxEmptyString, wxDefaultPosition, wxDefaultSize,0,NULL,wxCB_READONLY),0, wxEXPAND |wxLEFT,5);
                    ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->Insert(wxSTRING_YES,0);
                    ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->Insert(wxSTRING_NO,0);
                    ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->SetSelection(0);
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->SetHint(wxString("�������� ����"));
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_KOL_TT))->SetHint(wxString("������� ���������� ��"));
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_BANK_KONK))->SetHint(wxString("����������� �����-����������"));
                    to_static_box1->Add(to_3, 0, wxEXPAND,0);
                    to_static_box1->Add(to_4, 0, wxEXPAND,0);
                    to_static_box1->Add(to_5, 0, wxEXPAND,0);
                    to_static_box1->Add(to_6, 0, wxEXPAND,0);
                    to_static_box1->Add(to_7, 0, wxEXPAND,0);
        
                    to_static_box2->Add(new wxToggleButton(this,wxID_BUTTON_SP_ASRT,wxCAPTION_BUTTON_ASSORTI), 0, wxEXPAND|wxALL,0);
                    ClearForm(1); //������� ���� �����
                    vert->Layout(); 
                    break;
                }
                case 1: //���������� ������
                {
                    wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
                    for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) 
                    {
                        if
                        (
                        ((*it)->GetId())==wxID_STBOX_COOPERATION||
                        ((*it)->GetId())==wxID_STBOX_CARD_TO||
                        ((*it)->GetId())==wxID_STBOX_COMMAND||
                        ((*it)->GetId())==wxID_STBOX_PARAM_TO||
                        ((*it)->GetId())==wxID_CHOISE_COOPERATION||
                        ((*it)->GetId())==wxID_TO_STATICBOX_TO||
                        ((*it)->GetId())==wxID_TO_STATICBOX_INN||
                        ((*it)->GetId())==wxID_TO_INN||
                        ((*it)->GetId())==wxID_BUTTON_INN_TO||
                        ((*it)->GetId())==wxID_TO_NAME||
                        ((*it)->GetId())==wxID_BUTTON_INS_TO||
                        ((*it)->GetId())==wxID_BUTTON_UPD_TO||
                        ((*it)->GetId())==wxID_BUTTON_DEL_TO||
                        ((*it)->GetId())==wxID_BUTTON_CLR_TO||
                        ((*it)->GetId())==wxID_BUTTON_SP_PROV||
                        ((*it)->GetId())==wxID_BUTTON_SP_SOTR
                        ) 
                        {
                            if(((*it)->GetId())==wxID_BUTTON_SP_PROV) {((wxToggleButton*)(*it))->SetValue(false);}
                            if(((*it)->GetId())==wxID_BUTTON_SP_SOTR) {((wxToggleButton*)(*it))->SetValue(false);}
                        } else {(*it)->Destroy();}     //��������� ������� ����������
                    }
                    to_3 = new wxBoxSizer(wxHORIZONTAL);
                    to_3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_KOLSOTR),0,wxEXPAND |wxALL,0);
                    to_3->Add(new wxTextCtrl(this,wxID_UL_KOL_SOTR, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT|wxRIGHT,5);
                    ((wxTextCtrl*)this->FindWindow(wxID_UL_KOL_SOTR))->SetHint(wxString("������� ���������� �����������"));
                    to_static_box1->Add(to_3, 0, wxEXPAND,0);
                    ClearForm(1); //������� ���� �����
                    vert->Layout(); 
                    break;
                }
                case 2: //��������-���������
                {
                    wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
                    for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) 
                    {
                        if
                        (
                        ((*it)->GetId())==wxID_STBOX_COOPERATION||
                        ((*it)->GetId())==wxID_STBOX_CARD_TO||
                        ((*it)->GetId())==wxID_STBOX_COMMAND||
                        ((*it)->GetId())==wxID_STBOX_PARAM_TO||
                        ((*it)->GetId())==wxID_CHOISE_COOPERATION||
                        ((*it)->GetId())==wxID_TO_STATICBOX_TO||
                        ((*it)->GetId())==wxID_TO_STATICBOX_INN||
                        ((*it)->GetId())==wxID_TO_INN||
                        ((*it)->GetId())==wxID_BUTTON_INN_TO||
                        ((*it)->GetId())==wxID_TO_NAME||
                        ((*it)->GetId())==wxID_BUTTON_INS_TO||
                        ((*it)->GetId())==wxID_BUTTON_UPD_TO||
                        ((*it)->GetId())==wxID_BUTTON_DEL_TO||
                        ((*it)->GetId())==wxID_BUTTON_CLR_TO||
                        ((*it)->GetId())==wxID_BUTTON_SP_PROV||
                        ((*it)->GetId())==wxID_BUTTON_SP_SOTR
                        ) 
                        {
                            
                            if(((*it)->GetId())==wxID_BUTTON_SP_PROV) {((wxToggleButton*)(*it))->SetValue(false);}
                            if(((*it)->GetId())==wxID_BUTTON_SP_SOTR) {((wxToggleButton*)(*it))->SetValue(false);}
                        } else {(*it)->Destroy();}     //��������� ������� ����������
                    }
                    to_3 = new wxBoxSizer(wxHORIZONTAL);
                    to_3->Add(new wxStaticText(this,wxID_ANY,"��������-���� ��"),0, wxEXPAND |wxALL,0);
                    to_3->Add(new wxTextCtrl(this,wxID_TO_SITE_INET, wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_CENTRE|wxTE_AUTO_URL),1, wxEXPAND |wxLEFT|wxRIGHT,5);
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_SITE_INET))->SetHint(wxString("������� ��������-���� ��������"));
                    to_4 = new wxBoxSizer(wxHORIZONTAL);
                    to_4->Add(new wxStaticText(this,wxID_ANY,"��������-���� ����������"),0,wxEXPAND |wxALL,0);
                    to_4->Add(new wxTextCtrl(this,wxID_TO_EK_SITE_INET, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE|wxTE_AUTO_URL),1, wxEXPAND |wxLEFT|wxRIGHT,5);
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_EK_SITE_INET))->SetHint(wxString("������� ��������-���� ����������"));
                    to_static_box1->Add(to_3, 0, wxEXPAND,0);
                    to_static_box1->Add(to_4, 0, wxEXPAND,0);
                    ClearForm(1); //������� ���� �����
                    vert->Layout(); 
                    break;
                }
                case 3: //����� ������
                {
                    wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
                    for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) 
                    {
                        if
                        (
                        ((*it)->GetId())==wxID_STBOX_COOPERATION||
                        ((*it)->GetId())==wxID_STBOX_CARD_TO||
                        ((*it)->GetId())==wxID_STBOX_COMMAND||
                        ((*it)->GetId())==wxID_STBOX_PARAM_TO||
                        ((*it)->GetId())==wxID_CHOISE_COOPERATION||
                        ((*it)->GetId())==wxID_TO_STATICBOX_TO||
                        ((*it)->GetId())==wxID_TO_STATICBOX_INN||
                        ((*it)->GetId())==wxID_TO_INN||
                        ((*it)->GetId())==wxID_BUTTON_INN_TO||
                        ((*it)->GetId())==wxID_TO_NAME||
                        ((*it)->GetId())==wxID_BUTTON_INS_TO||
                        ((*it)->GetId())==wxID_BUTTON_UPD_TO||
                        ((*it)->GetId())==wxID_BUTTON_DEL_TO||
                        ((*it)->GetId())==wxID_BUTTON_CLR_TO||
                        ((*it)->GetId())==wxID_BUTTON_SP_PROV||
                        ((*it)->GetId())==wxID_BUTTON_SP_SOTR
                        ) 
                        {
                            
                            if(((*it)->GetId())==wxID_BUTTON_SP_PROV) {((wxToggleButton*)(*it))->SetValue(false);}
                            if(((*it)->GetId())==wxID_BUTTON_SP_SOTR) {((wxToggleButton*)(*it))->SetValue(false);}
                        } else {(*it)->Destroy();}     //��������� ������� ����������
                    }
                    ClearForm(1); //������� ���� �����
                    vert->Layout(); 
                    break;
                }
                case 4: //����������
                {
                    wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
                    for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) 
                    {
                        if
                        (
                        ((*it)->GetId())==wxID_STBOX_COOPERATION||
                        ((*it)->GetId())==wxID_STBOX_CARD_TO||
                        ((*it)->GetId())==wxID_STBOX_COMMAND||
                        ((*it)->GetId())==wxID_STBOX_PARAM_TO||
                        ((*it)->GetId())==wxID_CHOISE_COOPERATION||
                        ((*it)->GetId())==wxID_TO_STATICBOX_TO||
                        ((*it)->GetId())==wxID_TO_STATICBOX_INN||
                        ((*it)->GetId())==wxID_TO_INN||
                        ((*it)->GetId())==wxID_BUTTON_INN_TO||
                        ((*it)->GetId())==wxID_TO_NAME||
                        ((*it)->GetId())==wxID_BUTTON_INS_TO||
                        ((*it)->GetId())==wxID_BUTTON_UPD_TO||
                        ((*it)->GetId())==wxID_BUTTON_DEL_TO||
                        ((*it)->GetId())==wxID_BUTTON_CLR_TO||
                        ((*it)->GetId())==wxID_BUTTON_SP_PROV||
                        ((*it)->GetId())==wxID_BUTTON_SP_SOTR
                        ) 
                        {
                            
                            if(((*it)->GetId())==wxID_BUTTON_SP_PROV) {((wxToggleButton*)(*it))->SetValue(false);}
                            if(((*it)->GetId())==wxID_BUTTON_SP_SOTR) {((wxToggleButton*)(*it))->SetValue(false);}
                        } else {(*it)->Destroy();}     //��������� ������� ����������
                    }
                    to_3 = new wxBoxSizer(wxHORIZONTAL);
                    to_3->Add(new wxCheckBox(this,wxID_TO_CHECKBOX_FL_IP,wxCAPTION_CHECKBOX_FL_IP),0,wxEXPAND |wxALL,0);
                    ((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetToolTip(wxString("������� ������������� � ��������� ���������� ��� ��� ����������� ���, ������������ � �������������� � �������� ������������, �� ��� ���"));
                    to_static_box1->Add(to_3, 0, wxEXPAND,0);
                    to_static_box2->Add(new wxToggleButton(this,wxID_BUTTON_KT_KONTRACT,wxCAPTION_BUTTON_KONTRACT), 0, wxEXPAND|wxALL,0);
                    ClearForm(1); //������� ���� �����
                    vert->Layout(); 
                    break;
                }
                case 5: //���
                {
                    wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
                    for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) 
                    {
                        if
                        (
                        ((*it)->GetId())==wxID_STBOX_COOPERATION||
                        ((*it)->GetId())==wxID_STBOX_CARD_TO||
                        ((*it)->GetId())==wxID_STBOX_COMMAND||
                        ((*it)->GetId())==wxID_STBOX_PARAM_TO||
                        ((*it)->GetId())==wxID_CHOISE_COOPERATION||
                        ((*it)->GetId())==wxID_TO_STATICBOX_TO||
                        ((*it)->GetId())==wxID_TO_STATICBOX_INN||
                        ((*it)->GetId())==wxID_TO_INN||
                        ((*it)->GetId())==wxID_BUTTON_INN_TO||
                        ((*it)->GetId())==wxID_TO_NAME||
                        ((*it)->GetId())==wxID_BUTTON_INS_TO||
                        ((*it)->GetId())==wxID_BUTTON_UPD_TO||
                        ((*it)->GetId())==wxID_BUTTON_DEL_TO||
                        ((*it)->GetId())==wxID_BUTTON_CLR_TO||
                        ((*it)->GetId())==wxID_BUTTON_SP_PROV||
                        ((*it)->GetId())==wxID_BUTTON_SP_SOTR
                        ) 
                        {
                            
                            if(((*it)->GetId())==wxID_BUTTON_SP_PROV) {((wxToggleButton*)(*it))->SetValue(false);}
                            if(((*it)->GetId())==wxID_BUTTON_SP_SOTR) {((wxToggleButton*)(*it))->SetValue(false);}
                        } else {(*it)->Destroy();}     //��������� ������� ����������
                    }
                    ClearForm(1); //������� ���� �����
                    vert->Layout(); 
                    break;
                }
                case 6: //�� �� ������ ��������
                {
                    wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
                    for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) 
                    {
                        if
                        (
                        ((*it)->GetId())==wxID_STBOX_COOPERATION||
                        ((*it)->GetId())==wxID_STBOX_CARD_TO||
                        ((*it)->GetId())==wxID_STBOX_COMMAND||
                        ((*it)->GetId())==wxID_STBOX_PARAM_TO||
                        ((*it)->GetId())==wxID_CHOISE_COOPERATION||
                        ((*it)->GetId())==wxID_TO_STATICBOX_TO||
                        ((*it)->GetId())==wxID_TO_STATICBOX_INN||
                        ((*it)->GetId())==wxID_TO_INN||
                        ((*it)->GetId())==wxID_BUTTON_INN_TO||
                        ((*it)->GetId())==wxID_TO_NAME||
                        ((*it)->GetId())==wxID_BUTTON_INS_TO||
                        ((*it)->GetId())==wxID_BUTTON_UPD_TO||
                        ((*it)->GetId())==wxID_BUTTON_DEL_TO||
                        ((*it)->GetId())==wxID_BUTTON_CLR_TO||
                        ((*it)->GetId())==wxID_BUTTON_SP_PROV||
                        ((*it)->GetId())==wxID_BUTTON_SP_SOTR
                        ) 
                        {
                            
                            if(((*it)->GetId())==wxID_BUTTON_SP_PROV) {((wxToggleButton*)(*it))->SetValue(false);}
                            if(((*it)->GetId())==wxID_BUTTON_SP_SOTR) {((wxToggleButton*)(*it))->SetValue(false);}
                        } else {(*it)->Destroy();}     //��������� ������� ����������
                    }
                    ClearForm(1); //������� ���� �����
                    vert->Layout(); 
                    break;
                }
                default:break;
            }
        }
        default:break;
    }
}

ProvToFrm::~ProvToFrm()
{
   
}

void ProvToFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}
/*
void ProvToFrm::OnSize(wxSizeEvent& event) //����� ������� ���� �� ����� ������� ��������� ������ ��� ������ �������
{
	wxRect rect = GetRect(); //��������� ������� ������� ����
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_TO/x"), rect.GetX() );
    config->Write( wxT("/FORM_TO/y"), rect.GetY() );
    config->Write( wxT("/FORM_TO/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_TO/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void ProvToFrm::OnMove(wxMoveEvent& event) //����� ������� ���� �� ����� ������� ������������ ����
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_TO/x"), rect.GetX() );
    config->Write( wxT("/FORM_TO/y"), rect.GetY() );
    config->Write( wxT("/FORM_TO/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_TO/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
*/
void ProvToFrm::OnTextCtrl(wxCommandEvent& event)
{
	if(event.GetId()==wxID_TO_BRAND)
	{
        wxString str = ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->GetValue(); //�������� ����� ��������
        str = str.MakeUpper();                                                      //�������� ����� � �������� ���������
        ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->ChangeValue(str);          //�������� ����� ��������
        ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->SetInsertionPointEnd();    //������������� ������ ����� �� ����� ������
        for(register int i =0; i<MyBrandNameArray.GetCount();++i) //��������� ���� ������ � ����������� ����� ����� ������� ���������� �� ��������� ��������� � ��������� ����
        {
            if(!str.compare(MyBrandNameArray.Item(i).nameBrandName)) //���������� �������
            {
                for(register int j =0; j<MyBrandTypeArray.GetCount();++j) //��������� ���� ������ � ����������� ����� ����� ���� ���� ���������������� ���������� ��������
                {
                    //if(!MyBrandNameArray.Item(i).idBrandType.compare(MyBrandTypeArray.Item(j).idBrandType)) //���������� �������
                    if(MyBrandNameArray.Item(i).idBrandType==MyBrandTypeArray.Item(j).idBrandType) //���������� �������
                    {
                        
                        ((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(MyBrandTypeArray.Item(j).nameBrandType); //������� � ����������� ���� ��� ����
                        break; //������� �� ���������� ����� ������ ���� ����
                    }
                }
                break; //������� �� ���������� ����� ������ ���������� �� ������������ ����
            } else {((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(wxBRAND_DEFAULT);}
        }
        vert->Layout(); //������ ������ ����������� ��� �������� ��������
    }
}
void ProvToFrm::KillFocuss(wxFocusEvent& event)
{
	if((event.GetWindow())->GetId()==wxID_TO_BRAND)
	{        
    }
    event.Skip(true);
	 
}
void ProvToFrm::OnChar(wxKeyEvent& event) //������������ ������� ������
{
    switch(event.GetId())
    {
        case wxID_TO_INN: //��������� � ���� � ��� ������� ������� �������� �� ����
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
        case wxID_TO_KOL_TT: //��������� � ���� � �� ������� ������� �������� �� ����
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
        case wxID_UL_KOL_SOTR: //��������� � ���� � ����������� ����������� ������� ������� �������� �� ����
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

void ProvToFrm::OnMenu(wxCommandEvent& event)
{
	if (event.GetId()==wxID_MENU_FILE_POISK)
	{
        PoiskToDialog PoiskTo(this);  
        if(PoiskTo.ShowModal() == wxID_CANCEL) {return;} else {;}
        //(panel->FindWindow(wxID_BUTTON_INS_SOTR))->SetFocus();
    }    
}

void ProvToFrm::OnComboBox(wxCommandEvent& event)
{
	if (event.GetId()==wxID_TO_FLAG_INET)
	{
        if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //���� ������� �������� ����� - ��, ������� ��� ����
        {
            
            if(!(wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) to_7->Add(new wxStaticText(this,wxID_TO_STATIC_SITE,"��������-����"),0, wxEXPAND |wxALL,5);
            if(!(wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) to_7->Add(new wxTextCtrl(this,wxID_TO_SITE_INET, wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_AUTO_URL),1, wxEXPAND |wxALL,5);
            vert->Layout(); //������ ������� ����������� ������ ���� �����
            this->Refresh(); //�������������� �����
        }
        if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==0) //���� ������� �������� ����� - ���, ��������� ����.
        {
            if((wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) (wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))->Destroy();
            if((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) (wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))->Destroy();
            vert->Layout();
            this->Refresh();
        }
    }    
}

void ProvToFrm::OnMouse(wxMouseEvent& event)
{
	if (event.GetId()==wxID_LISTVIEW_ASRT)
	{
        //�������� ������ ������ ��-�� menuitem
        wxPoint point = event.GetPosition(); //���������� ����������� ����������� ��������� ����
        wxMenu *menu = new wxMenu;
        wxMenuItem *menuitem = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,wxCAPTION_MENU_ASSORTI);
        menuitem->SetTextColour(*wxWHITE);
        menuitem->SetBackgroundColour(*wxBLACK);
        menu->Append(menuitem);
        menu->AppendSeparator();
        menu->Append(wxID_BUTTON_INS_ASRT,wxCAPTION_BUTTON_INSERT);
        menu->Append(wxID_BUTTON_DEL_ASRT,wxCAPTION_BUTTON_DELETE);
        PopupMenu(menu,point);
        delete menu; 
    }
    if (event.GetId()==wxID_LISTVIEW_PROV)
	{
        wxPoint point = event.GetPosition(); //���������� ����������� ����������� ��������� ����
        wxMenu *menu = new wxMenu;
        wxMenuItem *menuitem = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,wxCAPTION_MENU_PROV_TO);
        menuitem->SetTextColour(*wxWHITE);
        menuitem->SetBackgroundColour(*wxBLACK);
        menu->Append(menuitem);
        menu->AppendSeparator();
        menu->Append(wxID_BUTTON_INS_PROV,wxCAPTION_BUTTON_INSERT);
        menu->Append(wxID_BUTTON_UPD_PROV,wxCAPTION_BUTTON_UPDATE);
        menu->Append(wxID_BUTTON_DEL_PROV,wxCAPTION_BUTTON_DELETE);
        menu->Append(wxID_BUTTON_KOM_PROV,wxCAPTION_BUTTON_COMMENT);
        PopupMenu(menu,point);
        delete menu; 
    }
    if (event.GetId()==wxID_LISTVIEW_SOTR)
	{
        wxPoint point = event.GetPosition(); //���������� ����������� ����������� ��������� ����
        wxMenu *menu = new wxMenu;
        wxMenuItem *menuitem = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,wxCAPTION_MENU_SOTR_TO);
        menuitem->SetTextColour(*wxWHITE);
        menuitem->SetBackgroundColour(*wxBLACK);
        menu->Append(menuitem);
        menu->AppendSeparator();
        menu->Append(wxID_BUTTON_INS_SOTR,wxCAPTION_BUTTON_INSERT);
        menu->Append(wxID_BUTTON_UPD_SOTR,wxCAPTION_BUTTON_UPDATE);
        menu->Append(wxID_BUTTON_DEL_SOTR,wxCAPTION_BUTTON_DELETE);
        menu->Append(wxID_BUTTON_KOM_SOTR,wxCAPTION_BUTTON_COMMENT);
        PopupMenu(menu,point);
        delete menu; 
    }    
}

void ProvToFrm::OnButton(wxCommandEvent& event)
{
    wxDir dir(wxGetCwd());
    if (dir.IsOpened())
    {
    wxString str_full, str_first, str_last;
    if (event.GetId()==wxID_BUTTON_CLR_TO)
	{
        ClearForm(1); //������� ���� �����
    }
    if (event.GetId()==wxID_BUTTON_DEL_SOTR)
	{
        DeleteProvSotrTo();
        
    }
    if (event.GetId()==wxID_BUTTON_KOM_SOTR)
	{
        CommentProvSotrTo();
    }
    if (event.GetId()==wxID_BUTTON_INS_SOTR||event.GetId()==wxID_BUTTON_UPD_SOTR) //������ ������ ��������/�������� �������� ���������� ��
	{
        if (id_to==0) {InformationSleep(wxINFO_NOT_TO,sec_for_sleep_window_info,this);}
        else
        {            
            int type_dialog=0;
            if (event.GetId()==wxID_BUTTON_INS_SOTR) {type_dialog=0;}
            if (event.GetId()==wxID_BUTTON_UPD_SOTR ) {type_dialog=1;}
            if (type_dialog==0)
            {
                EnterProvSotrTo EntProvSotrTo(this, id_to, type_dialog);  
                if(EntProvSotrTo.ShowModal() == wxID_CANCEL) {return;} else 
                {
                    ListViewProvSotr(); //�������������� �������� � ���������� ����������� ��
                }
                (this->FindWindow(wxID_BUTTON_INS_SOTR))->SetFocus();
            }
            if (type_dialog==1)
            {
                wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR)); //�������� ��������� �� ��������� � ���������� ����������� ��
                int count = 0;
                if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} //�� ������� ������ ������
                for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
                {
                    wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
                    f->SetId(idItem); //������������� ������� ���������� ��������
                    f->SetMask(wxLIST_MASK_DATA); //���������� ������ ��������� � ���������
                    listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
                    int idProvSotrTo=0; idProvSotrTo=f->GetData(); //����� � ���������� ������ ��������� � ���������
                    if(idProvSotrTo>0)
                    {
                        EnterProvSotrTo EntProvSotrTo(this, idProvSotrTo, type_dialog); 
                        if(EntProvSotrTo.ShowModal() == wxID_CANCEL) {;} else 
                        {
                            ++count; //������� ���-�� �����, ������� ���� ���������;
                        } 
                    } else {wxMessageBox(wxWARNING_NO_DATA,wxATTENTION,wxOK,this);}
                    delete f;
                }
                if (count>0)
                {
                    ListViewProvSotr(); //�������������� �������� � ���������� ����������� ��
                    wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_UPD_COUNT; str<<count; //������ ������ � ���-��� ����������� �����
                    InformationSleep(str,sec_for_sleep_window_info,this);
                    //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
                } else {;} //���� �� ������� �� ���� ������, �� ������������� �� ���� ������������ � ��������� ���������
                (this->FindWindow(wxID_BUTTON_UPD_SOTR))->SetFocus();
                
            }
        }
    }
    if (event.GetId()==wxID_BUTTON_INS_PROV||event.GetId()==wxID_BUTTON_UPD_PROV) //������ ������ ��������/�������� �������� ��
	{
        if (id_to==0) {InformationSleep(wxINFO_NOT_TO,sec_for_sleep_window_info,this);}
        else
        {
            int type_dialog=0;
            if (event.GetId()==wxID_BUTTON_INS_PROV) {type_dialog=0;}
            if (event.GetId()==wxID_BUTTON_UPD_PROV) {type_dialog=1;}
            if (type_dialog==0)
            {
                EnterProvTo EntProvTo(this, id_to, type_dialog);  
                if(EntProvTo.ShowModal() == wxID_CANCEL) {return;} else 
                {
                    ListViewProvTo(); //�������������� �������� � ���������� ��
                }
                (this->FindWindow(wxID_BUTTON_INS_PROV))->SetFocus();
            }
            if (type_dialog==1)
            {
                wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV)); //�������� ��������� �� ��������� � ���������� ��
                int count = 0;
                if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} //�� ������� ������ ������
                for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
                {
                    wxListItem *f = new wxListItem(); //������� ��������� �� ������ ������ wxListItem ��� �������� ���������� �� �������� ������ wxListCtrl
                    f->SetId(idItem); //������������� ������� ���������� ��������
                    f->SetMask(wxLIST_MASK_DATA); //���������� ������ ��������� � ���������
                    listview->GetItem(*f); //������ � ���������� ���������� � ��������� ��������
                    int idProvTo=0; idProvTo=f->GetData(); //����� � ���������� ������ ��������� � ���������
                    if(idProvTo>0)
                    {
                        EnterProvTo EntProvTo(this, idProvTo, type_dialog);
                        if(EntProvTo.ShowModal() == wxID_CANCEL) {;} else 
                        {
                            ++count; //������� ���-�� �����, ������� ���� ���������;
                        } 
                    } else {wxMessageBox(wxWARNING_NO_DATA,wxATTENTION,wxOK,this);}
                    delete f;
                }
                if (count>0)
                {
                    ListViewProvTo(); //�������������� �������� � ���������� ��
                    wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_UPD_COUNT; str<<count; //������ ������ � ���-��� ����������� �����
                    InformationSleep(str,sec_for_sleep_window_info,this);
                    //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
                } else {;} //���� �� ������� �� ���� ������, �� ������������� �� ���� ������������ � ��������� ���������
                (this->FindWindow(wxID_BUTTON_UPD_PROV))->SetFocus();
                
            }
        }         
    }
    if (event.GetId()==wxID_BUTTON_DEL_PROV) //������ ������ ������� �������� ��
	{
        DeleteProvTo();               
    }
    if (event.GetId()==wxID_BUTTON_KOM_PROV) //������ ������ ����������� �������� ��
	{
        CommentProvTo();                  
    }
    if (event.GetId()==wxID_BUTTON_DEL_ASRT) //������ ������ ������� �����������
	{
        DeleteAssorti();                 
    }
    if (event.GetId()==wxID_BUTTON_INS_ASRT) //������ ������ �������� �����������
	{
        InsertAssorti();
    }
    if (event.GetId()==wxID_BUTTON_INS_TO||event.GetId()==wxID_BUTTON_UPD_TO) //������ ������ ��������/�������� �������� ��
	{
        int flag_find_inn=0; //���� ����, ��� ������ � ������ ��� ����������. 0-�� ����������, 1 - ����������
        wxString inn_to, name_to, brand_to, tt_to, bank_konk_to, sotr_to, flNotIp; //���������� ��� ���������� �������� ������� ����������
        int type_cooper=0; //��� ��������������. ��������� ������������� �������� ��������� ������ wxChoice
        inn_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue();
        name_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->GetValue();
        if(type_cooperation->GetSelection()==4&&((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->GetValue()) //������ ���������� � ���� �������, ��� �� ��� ���
        {
            if ((int)inn_to.Len()!=10&&(int)inn_to.Len()!=12) {inn_to="1";}
        }
        else
        {
            if ((int)inn_to.Len()!=10&&(int)inn_to.Len()!=12) {InformationSleep(wxWARNING_INN,sec_for_sleep_window_info, this); return;}
        }
        if ((int)name_to.Len()==0) {InformationSleep(wxINFO_NAME_TO_1,sec_for_sleep_window_info, this); return;}
        
        switch (type_cooperation->GetSelection())
        {
            case 0: //pos
            {
                brand_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_BRAND)))->GetValue();
                tt_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_KOL_TT)))->GetValue();
                bank_konk_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_BANK_KONK)))->GetValue();
                if ((int)brand_to.Len()==0) {brand_to=wxBRAND_DEFAULT; ((wxTextCtrl*)(this->FindWindow(wxID_TO_BRAND)))->ChangeValue(wxBRAND_DEFAULT);}
                if ((int)tt_to.Len()==0) {tt_to=wxTT_DEFAULT; ((wxTextCtrl*)(this->FindWindow(wxID_TO_KOL_TT)))->ChangeValue(wxTT_DEFAULT);}
                if ((int)bank_konk_to.Len()==0) {bank_konk_to=wxNOT_DEFAULT; ((wxTextCtrl*)(this->FindWindow(wxID_TO_BANK_KONK)))->ChangeValue(wxNOT_DEFAULT);}
                for(register int i =0; i<MyBrandNameArray.GetCount();++i) //��������� ���� ������ � ����������� ����� ������� ���������� �� ��������� ��������� � ��������� ����
                {
                    if(!MyBrandNameArray.Item(i).nameBrandName.compare(brand_to)) //���������� �������
                    {        
                        //brand_to=MyBrandNameArray.Item(i).idBrandName;
                        brand_to.Clear(); brand_to<<MyBrandNameArray.Item(i).idBrandName;
                        break; //������� �� ���������� ����� ������ ���� ����
                    }
                }
                if(!brand_to.IsNumber()) {wxMessageBox(wxWARNING_BRAND,wxATTENTION,wxOK|wxCENTRE|wxICON_WARNING,this); return;}
                type_cooper=0;
                break;
            }
            case 1: //��
            {
                sotr_to=((wxTextCtrl*)(this->FindWindow(wxID_UL_KOL_SOTR)))->GetValue();
                if ((int)sotr_to.Len()==0) {sotr_to=wxSOTR_DEFAULT; ((wxTextCtrl*)(this->FindWindow(wxID_UL_KOL_SOTR)))->ChangeValue(wxSOTR_DEFAULT);}
                type_cooper=1;
                break;
            }
            case 2: //��������-���������
            {
                type_cooper=2;
                break;
            }
            case 3: //����� ������
            {
                type_cooper=3;
                break;
            }
            case 4: //����������
            {
                if(((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->GetValue())
                {flNotIp = "1"; } else {flNotIp =wxSQL_DEFAULT; }
                type_cooper=4;
                break;
            }
            case 5: //���
            {
                type_cooper=5;
                break;
            }
            case 6: //�� �� ������ ��������
            {
                type_cooper=6;
                break;
            }
            default:break;
        }
        if(((CrossFrm*)this->GetParent())->flag_bl_sb) {if(proverka_bl_sb(conn, inn_to, 0)==1) {;} else {return;}} //���� ���� �������� �� �� �� =1, �� ��������� ������� �������� ������� ���������� � �� ��
        if(event.GetId()==wxID_BUTTON_INS_TO)
        {
            //���� ������ ���������� � ��������� �� �������� ��� �� ��� ���, �� �� ��������� ���
            if(type_cooper==4&&((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->GetValue()) {}
            else
            {
                //��������� ��� �� ���� �� ������� ������� ����������
                wxString sqlText; sqlText<<wxSqlTextFindInnTo;
                sqlText<<inn_to; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                else
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                    if(num_rows>0)
                    {   
                        InformationSleep (wxINFO_INN_2, sec_for_sleep_window_info, this); //������� �������������� ��������� � ���������� ����������
                        if(wxMessageBox(wxQUESTION_FIND_INN,wxATTENTION,wxYES_NO,this)==wxYES) //���������� ������������ ������ �� ��������� ��������� ������
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            id_to = wxAtoi(row[0]); //����������� ���������� ������ �������� ���� ��������� ��
                            flag_find_inn=1;
                        } else {mysql_free_result(res); return;}
                    }
                    else {if(mysql_field_count(conn) == 0) {flag_find_inn=0;}}
                    mysql_free_result(res); // ������� ����������
                }
            }
        
        if(flag_find_inn==1) //���� ��� �� ����������
        {
            wxString 
            sqlText=wxSqlTextUpdToStart; sqlText<<name_to;
            switch (type_cooper)
            {
                case 0:
                {
                    sqlText<<wxSqlTextUpdToIdNet; sqlText<<brand_to;
                    sqlText<<wxSqlTextUpdToKolTt; sqlText<<tt_to;
                    sqlText<<wxSqlTextUpdToBankkonk; sqlText<<bank_konk_to;
                    sqlText<<wxSqlTextUpdToInetPriz; 
                    if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //���� ������� �������� ����� - ��
                    {
                        sqlText<<wxSqlTextUpdToInetSite;
                        wxString site = ((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->GetValue();
                        if ((int)site.Len()==0) {InformationSleep(wxWARNING_SITE,sec_for_sleep_window_info, this); return;}
                        else
                        {
                            sqlText<<site; sqlText<<wxSqlTextUpdToIdReestr1;
                        }                 
                    }
                    else {sqlText<<wxSqlTextUpdToIdReestr2;}
                    break;
                }
                case 1:
                {
                    sqlText<<wxSqlTextUpdToSotr; sqlText<<sotr_to;
                    sqlText<<wxSqlTextUpdToIdReestr3;
                    break;
                }
                case 2:
                {
                    wxString siteTo =((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->GetValue();
                    wxString siteEk=((wxTextCtrl*)(this->FindWindow(wxID_TO_EK_SITE_INET)))->GetValue();
                    sqlText<<wxSqlCharStr; sqlText<<wxSqlTextUpdToInetTo; 
                    if (siteTo.IsEmpty()) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<wxSqlCharStr; sqlText<<siteTo; sqlText<<wxSqlCharStr;}
                    sqlText<<wxSqlTextUpdToInetEk;
                    if (siteEk.IsEmpty()) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<wxSqlCharStr; sqlText<<siteEk; sqlText<<wxSqlCharStr;}
                    sqlText<<wxSqlTextUpdToIdReestr3;
                    //wxMessageBox(sqlText,"��������",wxOK,this);
                    break;
                }
                case 3:
                {
                    sqlText<<wxSqlTextUpdToIdReestr1;
                    break;
                }
                case 4:
                {
                    sqlText<<wxSqlTextUpdToFlIp;
                    sqlText<<flNotIp;
                    sqlText<<wxSqlTextUpdToInnTo;
                    sqlText<<"1";
                    sqlText<<wxSqlTextUpdToIdReestr3;
                    break;
                }
                case 5:
                {
                    sqlText<<wxSqlTextUpdToIdReestr1;
                    break;
                }
                case 6:
                {
                    sqlText<<wxSqlTextUpdToIdReestr1;
                    break;
                }
                default:break;
            }
            sqlText<<id_to; sqlText<<wxSqlEndText;
            //wxMessageBox(sqlText,wxATTENTION,wxYES_NO,this);
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
            else {InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this);}                          
        }
        if(flag_find_inn==0) //���� ��� �� �� ����������
        {
            wxString site, sqlText;
            switch (type_cooper)
            {
                case 0:
                {
                    sqlText=wxSqlTextInsertTo_1;
                    if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //���� ������� �������� ����� - ��
                    {
                        sqlText<<wxSqlTextInsertTo_1_1;
                        site = ((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->GetValue();
                        if ((int)site.Len()==0) {InformationSleep(wxWARNING_SITE,sec_for_sleep_window_info, this); return;}
                    } else {sqlText<<wxSqlTextInsertTo_1_2;}
                    sqlText<<inn_to; sqlText<<wxSqlRightCaw;
                    sqlText<<name_to; sqlText<<wxSqlLeftCaw;
                    sqlText<<brand_to; sqlText<<wxSqlCommaText;
                    sqlText<<tt_to; sqlText<<wxSqlRightCaw;
                    sqlText<<bank_konk_to; sqlText<<wxSqlLeftCaw;
                    if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //���� ������� �������� ����� - ��
                    {sqlText<<wxSqlOneAndText; sqlText<<site; sqlText<<wxSqlTextBracketEnd;}
                    else {sqlText<<wxSqlZeroBracketEnd;}
                    break;
                }
                case 1:
                {
                    sqlText<<wxSqlTextInsertTo_2;
                    sqlText<<inn_to; sqlText<<wxSqlRightCaw;
                    sqlText<<name_to; sqlText<<wxSqlLeftCaw;
                    sqlText<<sotr_to; sqlText<<wxSqlEndRightBracketText;
                    break;
                }
                case 2:
                {
                    wxString siteTo =((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->GetValue();
                    wxString siteEk=((wxTextCtrl*)(this->FindWindow(wxID_TO_EK_SITE_INET)))->GetValue();
                    
                    
                    sqlText<<wxSqlTextInsertTo_5;
                    sqlText<<inn_to; sqlText<<wxSqlRightCaw;
                    sqlText<<name_to; sqlText<<wxSqlLeftCaw;
                    if (siteTo.IsEmpty()) {sqlText<<wxSQL_DEFAULT; sqlText<<wxSqlCommaText;} else {sqlText<<wxSqlCharStr; sqlText<<siteTo; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;}
                    if (siteEk.IsEmpty()) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<wxSqlCharStr; sqlText<<siteEk; sqlText<<wxSqlCharStr;}
                    sqlText<<wxSqlEndRightBracketText;
                    //wxMessageBox(sqlText,"��������",wxOK,this);
                    break;
                }
                case 3:
                {
                    sqlText<<wxSqlTextInsertTo_3;
                    sqlText<<inn_to; sqlText<<wxSqlRightCaw;
                    sqlText<<name_to; sqlText<<wxSqlTextBracketEnd;
                    break;
                }
                case 4:
                {
                    sqlText<<wxSqlTextInsertTo_4;
                    sqlText<<inn_to; sqlText<<wxSqlRightCaw;
                    sqlText<<name_to; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;
                    sqlText<<flNotIp; sqlText<<wxSqlEndRightBracketText;
                    break;
                }
                case 5:
                {
                    sqlText<<wxSqlTextInsertTo_3;
                    sqlText<<inn_to; sqlText<<wxSqlRightCaw;
                    sqlText<<name_to; sqlText<<wxSqlTextBracketEnd;
                    break;
                }
                case 6:
                {
                    sqlText<<wxSqlTextInsertTo_3;
                    sqlText<<inn_to; sqlText<<wxSqlRightCaw;
                    sqlText<<name_to; sqlText<<wxSqlTextBracketEnd;
                    break;
                }
                default:break;
            }
            mysql_query (conn,"SET character_set_client='utf8'");  /*������������� ��������� ������ ������������ �� �������*/
            if (mysql_query(conn, sqlText.utf8_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
            else
            {
                //������ � ��, ����� �������� id_reestr_to
                wxString sqlTextId=wxSqlTextFindInnTo;
                if(type_cooperation->GetSelection()==4&&((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->GetValue()) //������ ���������� � ���� �������, ��� �� ��� ���
                {
                    //�� ������ ����� ���������� ��� ���
                    sqlTextId<<"1"; sqlTextId<<wxSqlTextUpdToNameto; sqlTextId<<name_to; sqlTextId<<wxSqlCharStr; sqlTextId<<wxSqlEndText;
                }
                else
                {
                    //�� ��� ��������� ������
                    sqlTextId<<inn_to; sqlTextId<<wxSqlEndText;
                }
                if (mysql_query(conn, sqlTextId.utf8_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                    if(num_rows>0)
                    {   
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        id_to = wxAtoi(row[0]); //����������� ���������� ������ �������� ���� ��������� ��
                        flag_find_inn=1;
                    }
                    else {;}
                    InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this);
                    mysql_free_result(res); // ������� ����������
                }                
            }
            mysql_query (conn,"SET character_set_client='cp1251'");  /*������������� ��������� ������ ������������ �� �������*/                   
        }}
        if(event.GetId()==wxID_BUTTON_UPD_TO)
        {
            wxString sqlText=wxSqlTextUpdToStart; sqlText<<name_to;
            switch (type_cooper)
            {
                case 0:
                {
                    sqlText<<wxSqlTextUpdToIdNet; sqlText<<brand_to;
                    sqlText<<wxSqlTextUpdToInnTo; sqlText<<inn_to;
                    sqlText<<wxSqlTextUpdToKolTt; sqlText<<tt_to;
                    sqlText<<wxSqlTextUpdToBankkonk; sqlText<<bank_konk_to;
                    sqlText<<wxSqlTextUpdToInetPriz; 
                    if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //���� ������� �������� ����� - ��
                    {
                        sqlText<<wxSqlTextUpdToInetSite;
                        wxString site = ((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->GetValue();
                        if ((int)site.Len()==0) {InformationSleep(wxWARNING_SITE,sec_for_sleep_window_info, this); return;}
                        else
                        {
                            sqlText<<site; sqlText<<wxSqlTextUpdToIdReestr1;
                        }                 
                    }
                    else {sqlText<<wxSqlTextUpdToIdReestr2;}
                    break;
                }
                case 1:
                {
                    sqlText<<wxSqlTextUpdToSotr; sqlText<<sotr_to;
                    sqlText<<wxSqlTextUpdToIdReestr3;
                    break;
                }
                case 2:
                {
                    wxString siteTo =((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->GetValue();
                    wxString siteEk=((wxTextCtrl*)(this->FindWindow(wxID_TO_EK_SITE_INET)))->GetValue();
                    sqlText<<wxSqlCharStr; sqlText<<wxSqlTextUpdToInetTo; 
                    if (siteTo.IsEmpty()) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<wxSqlCharStr; sqlText<<siteTo; sqlText<<wxSqlCharStr; sqlText<<wxSqlCommaText;}
                    sqlText<<wxSqlTextUpdToInetEk;
                    if (siteEk.IsEmpty()) {sqlText<<wxSQL_DEFAULT;} else {sqlText<<wxSqlCharStr; sqlText<<siteEk; sqlText<<wxSqlCharStr;}
                    sqlText<<wxSqlTextUpdToIdReestr3;
                    break;
                }
                case 3:
                {
                    sqlText<<wxSqlTextUpdToIdReestr1;
                    break;
                }
                case 4:
                {
                    sqlText<<wxSqlTextUpdToFlIp;
                    sqlText<<flNotIp;
                    sqlText<<wxSqlTextUpdToInnto;
                    sqlText<<inn_to;
                    sqlText<<wxSqlTextUpdToIdReestr3;
                    break;
                }
                case 5:
                {
                    sqlText<<wxSqlTextUpdToIdReestr1;
                    break;
                }
                case 6:
                {
                    sqlText<<wxSqlTextUpdToIdReestr1;
                    break;
                }
                default:break;
            }
            sqlText<<id_to; sqlText<<wxSqlEndText;
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
            else {InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this);}
        }                             
    }
    if (event.GetId()==wxID_BUTTON_DEL_TO) //������ ������ ������� �������� ��
	{
        DeleteCardTo();
        ClearForm(1);
    }
    if (event.GetId()==wxID_BUTTON_INN_TO) //������ ������ ��������� ���
	{
        ProvInnTo();
    }
    if (event.GetId()==wxID_BUTTON_SP_SOTR) //������ ������ ������ �������� �����������
	{
        if(((wxToggleButton*)this->FindWindow(wxID_BUTTON_SP_SOTR))->GetValue())      //������ ������
        {        
            ListViewProvSotr(); //�������/�������������� �������� �� ������� �������� �����������
        }
        else                                                                            //�� ������ ������ 
            {
                
                if(to_static_box5->GetItemCount()>0)
                {
                    (this->FindWindow(wxID_LISTVIEW_SOTR))->Destroy();     //��������� ��������
                    (this->FindWindow(wxID_BUTTON_INS_SOTR))->Destroy();   //��������� ������
                    (this->FindWindow(wxID_BUTTON_UPD_SOTR))->Destroy();   //��������� ������
                    (this->FindWindow(wxID_BUTTON_DEL_SOTR))->Destroy();   //��������� ������
                    (this->FindWindow(wxID_BUTTON_KOM_SOTR))->Destroy();   //��������� ������
                    to_static_box5->Detach(vr5);                           //����������� ����������� ������
                    vert->Detach(to_static_box5);                           //����������� ����������� ������
                    delete vr5;                                          //����������� ������ ���������� ��� ������
                    delete stBox5;                                          //����������� ������ ���������� ��� ����������� ����
                    delete to_static_box5;                                  //����������� ������ ���������� ��� ������ �� ����������� �����
                    //this->SetStatusText("",1);
                    vert->Layout();                                         //������ �������� ������ ����������� ���� �����
                }
            }
        }
    if (event.GetId()==wxID_BUTTON_SP_PROV) //������ ������ ������ �������� ��
	   {
            if(((wxToggleButton*)this->FindWindow(wxID_BUTTON_SP_PROV))->GetValue())      //������ ������
            {
                ListViewProvTo(); //�������/�������������� �������� �� ������� �������� ��
            }
            else                                                                            //�� ������ ������ 
            {
                
                if(to_static_box4->GetItemCount()>0)
                {
                    (this->FindWindow(wxID_LISTVIEW_PROV))->Destroy();     //��������� ��������
                    (this->FindWindow(wxID_BUTTON_INS_PROV))->Destroy();   //��������� ������
                    (this->FindWindow(wxID_BUTTON_UPD_PROV))->Destroy();   //��������� ������
                    (this->FindWindow(wxID_BUTTON_DEL_PROV))->Destroy();   //��������� ������
                    (this->FindWindow(wxID_BUTTON_KOM_PROV))->Destroy();   //��������� ������
                    to_static_box4->Detach(vr4);                           //����������� ����������� ������
                    vert->Detach(to_static_box4);                           //����������� ����������� ������
                    delete stBox4;                                          //����������� ������ ���������� ��� ����������� ����
                    delete to_static_box4;                                  //����������� ������ ���������� ��� ������ �� ����������� �����
                    //this->SetStatusText("",0);
                    vert->Layout();                                         //������ �������� ������ ����������� ���� �����
                }
            }
        }
    if (event.GetId()==wxID_BUTTON_SP_ASRT) //������ ������ ������ ������������
	   {
            if(((wxToggleButton*)this->FindWindow(wxID_BUTTON_SP_ASRT))->GetValue())      //������ ������
            {
                ListViewAssortiment(); //�������/�������������� �������� �� ������� ������������
            }
            else                                                                            //�� ������ ������            
            {
                
                if(to_static_box3->GetItemCount()>0)
                {
                    (this->FindWindow(wxID_LISTVIEW_ASRT))->Destroy();     //��������� ��������
                    (this->FindWindow(wxID_BUTTON_INS_ASRT))->Destroy();   //��������� ������
                    (this->FindWindow(wxID_BUTTON_DEL_ASRT))->Destroy();   //��������� ������
                    to_static_box3->Detach(vr3);                           //����������� ����������� ������
                    vert->Detach(to_static_box3);                           //����������� ����������� ������
                    delete stBox3;                                          //����������� ������ ���������� ��� ����������� ����
                    delete to_static_box3;                                  //����������� ������ ���������� ��� ������ �� ����������� �����
                    //this->SetStatusText("",2);
                    vert->Layout();                                         //������ �������� ������ ����������� ���� �����
                } 
            }                                                    
        }
    if (event.GetId()==wxID_BUTTON_KT_KONTRACT) //������ ������ ������ �������� ��
	   {
            if(((wxToggleButton*)this->FindWindow(wxID_BUTTON_KT_KONTRACT))->GetValue())      //������ ������
            {
                ListViewKontract(); //�������/�������������� �������� �� ������� ����������
            }
            else                                                                            //�� ������ ������ 
            {
                
                if(to_static_box6->GetItemCount()>0)
                {
                    (this->FindWindow(wxID_LISTVIEW_KONTRACT))->Destroy();     //��������� ��������
                    //to_static_box6->Detach(vr6);                           //����������� ����������� ������
                    vert->Detach(to_static_box6);                           //����������� ����������� ������
                    delete stBox6;                                          //����������� ������ ���������� ��� ����������� ����
                    delete to_static_box6;                                  //����������� ������ ���������� ��� ������ �� ����������� �����
                    //this->SetStatusText("",0);
                    vert->Layout();                                         //������ �������� ������ ����������� ���� �����
                }
            }
        }
    }
}

void ProvToFrm::ClearForm (int flag) //���� ���� =0, �� ��������� ��� ���� �� ����������� ���. ���� ���� >0 ��������� � ���� � ���
{
    if(flag>0) { ((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->Clear();}
    id_to=0; //������� ���� ��
    count_assorti=0; 
    count_to_prov=0; 
    count_sotr_prov=0;
    switch (type_cooperation->GetSelection())
    {
        case 0: //pos
        {
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->Clear(); //������� ������������ ��
            ((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(wxBRAND_DEFAULT); //������������� �������� �� ��������� ���� 
            ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->Clear(); //SetLabelText(wxBRAND_DEFAULT); //������������� �������� �� ��������� ���� ����
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_KOL_TT)))->Clear(); //������� ���-�� ��
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_BANK_KONK)))->Clear(); //������� �����-����������
            ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->SetSelection(0); //�������� ������� �������� �������� - ���
            if((wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) {(wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))->Destroy();} //���� ����������, ��������� ������� - ��������-�������
            if((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) {(wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))->Destroy();} //���� ����������, ��������� ���� � ��������-������
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_ASRT))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->DeleteAllItems();}
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();} 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();}
            if((wxCheckBox*)(this->FindWindow(wxID_TO_CHECKBOX_FL_IP))) {((wxCheckBox*)(this->FindWindow(wxID_TO_CHECKBOX_FL_IP)))->SetValue(false);} //���� ����������, ������� ����� � ���-�����
            break;
        }
        case 1: //�� ������
        {
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->Clear(); //������� ������������ ��
            ((wxTextCtrl*)(this->FindWindow(wxID_UL_KOL_SOTR)))->Clear(); //������� ������������ ��
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();} 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();}
            break;
        }
        case 2: //��������-���������
        {
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->Clear(); //������� ������������ ��
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->Clear(); //������� 
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_EK_SITE_INET)))->Clear(); //������� 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();} 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();}
            break;
        }
        case 3: //����� ������
        case 5: //���
        case 6: //�� �� ������ ��������
        case 4: //����������
        {
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->Clear(); //������� ������������ ��
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();} 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();}
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_KONTRACT))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_KONTRACT))->DeleteAllItems();}
            break;
        }
        default:break;
    }
    wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
    grandParentWindow->WorkStatusBar();
    //this->SetStatusText(wxREADDY_,0); this->SetStatusText(wxNULL_STRING,1); this->SetStatusText(wxNULL_STRING,2);
    vert->Layout(); //������ ������� ����������� ������ ���� �����
    this->Refresh(); //�������������� �����   
}
void ProvToFrm::ListViewProvSotr (void)
{
    ((wxToggleButton*)(this->FindWindow(wxID_BUTTON_SP_SOTR)))->SetValue(true);
    if(!(wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) //���� �� ������� �� �������
    {
        wxDir dir(wxGetCwd());
        if (dir.IsOpened())
        {
            wxString str_full, str_first, str_last;
            vr5 = new wxBoxSizer(wxVERTICAL);
            stBox5 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_LIST_SOTR_TO);
            to_static_box5 = new wxStaticBoxSizer(stBox5,wxHORIZONTAL);
            wxListView *listview = new wxListView(this, wxID_LISTVIEW_SOTR);
            listview->InsertColumn(0,wxCAPTION_COLUMN_FIO);
            listview->InsertColumn(1,wxCAPTION_COLUMN_JOB);
            listview->InsertColumn(2,wxCAPTION_COLUMN_PASSPORT);
            listview->InsertColumn(3,wxCAPTION_COLUMN_GC);
            listview->InsertColumn(4,wxCAPTION_COLUMN_UK);
            listview->InsertColumn(5,wxCAPTION_COLUMN_REZ);
            listview->InsertColumn(6,wxCAPTION_COLUMN_SOTRSB);
            listview->InsertColumn(7,wxCAPTION_COLUMN_DATE);
            listview->InsertColumn(8,wxCAPTION_COLUMN_ARCHIVE);
            str_first = dir.GetName(); str_last= wxINSERT_ICO; str_full=str_first; str_full+=str_last;
            wxImage *image = new wxImage(str_full,wxBITMAP_TYPE_ICO);
            image->Rescale(16,16);
            vr5->Add(new wxBitmapButton(this,wxID_BUTTON_INS_SOTR,wxBitmap(*image)), 1, wxEXPAND,0);
            str_first = dir.GetName(); str_last= wxUPDATE_ICO; str_full=str_first; str_full+=str_last;
            wxImage *image1 = new wxImage(str_full,wxBITMAP_TYPE_ICO);
            image->Rescale(16,16);
            vr5->Add(new wxBitmapButton(this,wxID_BUTTON_UPD_SOTR,wxBitmap(*image1)), 1, wxEXPAND,0);
            str_first = dir.GetName(); str_last= wxDELETE_ICO; str_full=str_first; str_full+=str_last;
            wxImage *image2 = new wxImage(str_full,wxBITMAP_TYPE_ICO);
            image->Rescale(16,16);
            vr5->Add(new wxBitmapButton(this,wxID_BUTTON_DEL_SOTR,wxBitmap(*image2)), 1, wxEXPAND,0);
            str_first = dir.GetName(); str_last= wxCOMMENT_ICO; str_full=str_first; str_full+=str_last;
            wxImage *image3 = new wxImage(str_full,wxBITMAP_TYPE_ICO);
            image->Rescale(16,16);
            vr5->Add(new wxBitmapButton(this,wxID_BUTTON_KOM_SOTR,wxBitmap(*image3)), 1, wxEXPAND,0);
            to_static_box5->Add(vr5, 0, wxEXPAND,0);
            to_static_box5->Add(listview, 1, wxEXPAND,0);
            vert->Add(to_static_box5, 1, wxEXPAND,0);
            //this->SetStatusText(wxCOUNT_PROV_SOTR,1);
            vert->Layout();
            (this->FindWindow(wxID_LISTVIEW_SOTR))->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(ProvToFrm::OnMouse));
            (this->FindWindow(wxID_BUTTON_INS_SOTR))->SetToolTip("�������� ������");
            (this->FindWindow(wxID_BUTTON_UPD_SOTR))->SetToolTip("�������� ������");
            (this->FindWindow(wxID_BUTTON_DEL_SOTR))->SetToolTip("������� ������");
            (this->FindWindow(wxID_BUTTON_KOM_SOTR))->SetToolTip("��������� �����������");
            (this->FindWindow(wxID_BUTTON_INS_SOTR))->SetBackgroundColour(*wxWHITE);
            (this->FindWindow(wxID_BUTTON_UPD_SOTR))->SetBackgroundColour(*wxWHITE);
            (this->FindWindow(wxID_BUTTON_DEL_SOTR))->SetBackgroundColour(*wxWHITE);
            (this->FindWindow(wxID_BUTTON_KOM_SOTR))->SetBackgroundColour(*wxWHITE);
            if(id_to!=0)
            {
                wxString sqlText; sqlText<<wxSqlTextSotrTo;
                sqlText<<id_to; sqlText<<wxSqlEndText;
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
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[5])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields; l++)
                            {
                                if (l==0) {listview->SetItem(i,l,row[l]);}
                                if (l==1) 
                                {
                                    for(register int k =0; k<MyDolznostArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyDolznostArray.Item(k).idDolznost.c_str())==atoi(row[l])) //���������� �������
                                        if(MyDolznostArray.Item(k).idDolznost==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyDolznostArray.Item(k).nameDolznost);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==2) //������� 
                                {
                                    wxString str; str<<row[3]; str<<" "; str<<row[2]; //��������� ����� � ����� � ����� ����������
                                    listview->SetItem(i,2,str);
                                }
                                if (l==4) 
                                {
                                    for(register int k =0; k<MyGcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //���������� �������
                                        if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,3,MyGcArray.Item(k).nameGc);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==6) 
                                {
                                    for(register int k =0; k<MyUkRfArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //���������� �������
                                        if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,4,MyUkRfArray.Item(k).nameUkRf);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==7) 
                                {
                                    for(register int k =0; k<MyRezProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //���������� �������
                                        if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,5,MyRezProvArray.Item(k).nameRezProv);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==8) 
                                {
                                    for(register int k =0; k<MyFioSbArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //���������� �������
                                        if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,6,MyFioSbArray.Item(k).nameFioSb);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==9) {listview->SetItem(i,7,row[l]);}
                                if (l==10) 
                                {
                                    if(atoi(row[l])==0) //������ �� � ������
                                    {
                                        listview->SetItem(i,8,"��");
                                    }
                                    else                //������ � ������
                                    {
                                        listview->SetItem(i,8,"���");
                                    }
                                }
                            }
                            delete f;
                        }
                    for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                    //wxString status = wxCOUNT_PROV_SOTR; 
                    count_sotr_prov=num_rows;
                    //this->SetStatusText(status,1);
                    wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // ������� ����������
                }
            }
            delete image; delete image1; delete image2; delete image3;
        }
    }
    else
    {
        ((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();
        if(id_to!=0)
            {
                wxString sqlText; sqlText<<wxSqlTextSotrTo;
                sqlText<<id_to; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else
                {
                    wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR));
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
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[5])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields; l++)
                            {
                                if (l==0) {listview->SetItem(i,l,row[l]);}
                                if (l==1) 
                                {
                                    for(register int k =0; k<MyDolznostArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyDolznostArray.Item(k).idDolznost.c_str())==atoi(row[l])) //���������� �������
                                        if(MyDolznostArray.Item(k).idDolznost==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyDolznostArray.Item(k).nameDolznost);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==2) //������� 
                                {
                                    wxString str; str<<row[3]; str<<" "; str<<row[2]; //��������� ����� � ����� � ����� ����������
                                    listview->SetItem(i,2,str);
                                }
                                if (l==4) 
                                {
                                    for(register int k =0; k<MyGcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //���������� �������
                                        if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,3,MyGcArray.Item(k).nameGc);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==6) 
                                {
                                    for(register int k =0; k<MyUkRfArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //���������� �������
                                        if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,4,MyUkRfArray.Item(k).nameUkRf);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==7) 
                                {
                                    for(register int k =0; k<MyRezProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //���������� �������
                                        if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,5,MyRezProvArray.Item(k).nameRezProv);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==8) 
                                {
                                    for(register int k =0; k<MyFioSbArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //���������� �������
                                        if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,6,MyFioSbArray.Item(k).nameFioSb);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==9) {listview->SetItem(i,7,row[l]);}
                                if (l==10) 
                                {
                                    if(atoi(row[l])==0) //������ �� � ������
                                    {
                                        listview->SetItem(i,8,"��");
                                    }
                                    else                //������ � ������
                                    {
                                        listview->SetItem(i,8,"���");
                                    }
                                }
                            }
                            delete f;
                        }
                    for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                    //wxString status = wxCOUNT_PROV_SOTR; 
                    count_sotr_prov=num_rows;
                    //this->SetStatusText(status,1);
                    wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // ������� ����������
                }
            }
    }
}

void ProvToFrm::ListViewKontract (void){
    ((wxToggleButton*)(this->FindWindow(wxID_BUTTON_KT_KONTRACT)))->SetValue(true);
    
    if(!(wxListView*)(this->FindWindow(wxID_LISTVIEW_KONTRACT))) //���� �� ������� �� �������
    {
        wxDir dir(wxGetCwd());
        if (dir.IsOpened())
        {
            wxString str_full, str_first, str_last;
            //vr6 = new wxBoxSizer(wxVERTICAL);
            stBox6 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_LIST_KONTRACT);
            to_static_box6 = new wxStaticBoxSizer(stBox6,wxHORIZONTAL);
            wxListView *listview = new wxListView(this, wxID_LISTVIEW_KONTRACT,wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
            listview->InsertColumn(0,wxCAPTION_COLUMN_DOGOVOR);
            listview->InsertColumn(1,wxCAPTION_COLUMN_D_SIGN);
            listview->InsertColumn(2,wxCAPTION_COLUMN_D_END);
            listview->InsertColumn(3,wxCAPTION_COLUMN_D_PRICE);

            //to_static_box4->Add(vr6, 0, wxEXPAND,0);
            to_static_box6->Add(listview, 1, wxEXPAND,0);
            vert->Add(to_static_box6, 1, wxEXPAND,0);
            //this->SetStatusText(wxCOUNT_PROV_TO,0);
            vert->Layout();
            //(this->FindWindow(wxID_LISTVIEW_PROV))->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(ProvToFrm::OnMouse));
            if(id_to!=0)
            {
                wxString sqlText; sqlText<<wxSqlTextSelAllContKontr;
                sqlText<<id_to; sqlText<<wxSqlEndTextOrderAsc3;
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
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(wxAtoi(row[0])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 1; l < num_fields; l++)
                            {
                                if (l==1||l==2||l==3) { if(row[l]) { listview->SetItem(i,l-1,row[l]); } }
                                if (l==4) {
                                    if(row[l]){
                                    wxString temp_1 = row[l]; //������ ���������� ���� �������� � ���������� ��������������
                                    wxString temp_2;            //����������������� ������
                                    
                                    /*
                                    first - ������ ���������� ������
                                    last - ����� ���������� ������
                                    i - ��� ��������;
                                    temp_1.Len()%3==0 ? 3: temp_1.Len()%3   - ���� ������ ����� �� ������ 3-�, �� ����������� � �������� ����� ������ ���������� ������ ������� �� ������� �� ������
                                    */
                                    for(int first = 0, i = (temp_1.Len()%3==0 ? 3: temp_1.Len()%3), last = i; i<temp_1.Len(); i+=3) {
                                        temp_2.Append(temp_1.Mid(first,last));  //��������� ���������� �����
                                        temp_2.Append(" ");                     //��������� ������ (�����������)
                                        first=i; last=3;                        //������ ������ � ����� ���������� ����������� �����
                                        if((i+3)>=temp_1.Len()) {temp_2.Append(temp_1.Mid(first,3)); temp_2.Append(" �.");} //���� �� ��������� ���� ����� ��������� ����� ������, �� ��������� ��������� ������� � ��������� � ����� ������ ������ ��
                                    }
                                    listview->SetItem(i,l-1,temp_2);
                                    } else {
                                    listview->SetItem(i,l-1,"");}
                                }
                                
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                        //wxString status = wxCOUNT_PROV_TO; 
                        //count_to_prov=num_rows;
                        //this->SetStatusText(status,0);
                        //wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
                        //wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
                        //grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // ������� ����������
                }  
            }
        }
    }
    else //���� �� ������� �������
    {
        ((wxListView*)this->FindWindow(wxID_LISTVIEW_KONTRACT))->DeleteAllItems();
        {
                wxString sqlText; sqlText<<wxSqlTextSelAllContKontr;
                sqlText<<id_to; sqlText<<wxSqlEndTextOrderAsc3;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else
                {
                    wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_KONTRACT));
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
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[0])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 1; l < num_fields; l++)
                            {
                                if (l==1||l==2||l==3||l==4) { if(row[l]) { listview->SetItem(i,l-1,row[l] ? row[l] : ""); } }
                                if (l==4) {
                                    if(row[l]){
                                    wxString temp_1 = row[l]; //������ ���������� ���� �������� � ���������� ��������������
                                    wxString temp_2;            //����������������� ������
                                    
                                    /*
                                    first - ������ ���������� ������
                                    last - ����� ���������� ������
                                    i - ��� ��������;
                                    temp_1.Len()%3==0 ? 3: temp_1.Len()%3   - ���� ������ ����� �� ������ 3-�, �� ����������� � �������� ����� ������ ���������� ������ ������� �� ������� �� ������
                                    */
                                    for(int first = 0, i = (temp_1.Len()%3==0 ? 3: temp_1.Len()%3), last = i; i<temp_1.Len(); i+=3) {
                                        temp_2.Append(temp_1.Mid(first,last));  //��������� ���������� �����
                                        temp_2.Append(" ");                     //��������� ������ (�����������)
                                        first=i; last=3;                        //������ ������ � ����� ���������� ����������� �����
                                        if((i+3)>=temp_1.Len()) {temp_2.Append(temp_1.Mid(first,3)); temp_2.Append(" �.");} //���� �� ��������� ���� ����� ��������� ����� ������, �� ��������� ��������� ������� � ��������� � ����� ������ ������ ��
                                    }
                                    listview->SetItem(i,l-1,temp_2);
                                    } else {
                                    listview->SetItem(i,l-1,"");}
                                }
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                        //wxString status = wxCOUNT_PROV_TO; 
                        //count_to_prov=num_rows;
                        //this->SetStatusText(status,0);
                        //wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
                        //wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
                        //grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // ������� ����������
                }  
            }
    }
}
void ProvToFrm::ListViewProvTo (void)
{
    ((wxToggleButton*)(this->FindWindow(wxID_BUTTON_SP_PROV)))->SetValue(true);
    if(!(wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) //���� �� ������� �� �������
    {
        wxDir dir(wxGetCwd());
        if (dir.IsOpened())
        {
            wxString str_full, str_first, str_last;
            vr4 = new wxBoxSizer(wxVERTICAL);
            stBox4 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_LIST_PROV_TO);
            to_static_box4 = new wxStaticBoxSizer(stBox4,wxHORIZONTAL);
            wxListView *listview = new wxListView(this, wxID_LISTVIEW_PROV,wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
            listview->InsertColumn(0,wxCAPTION_COLUMN_COOPER);
            listview->InsertColumn(1,wxCAPTION_COLUMN_PROV);
            listview->InsertColumn(2,wxCAPTION_COLUMN_OC);
            listview->InsertColumn(3,wxCAPTION_COLUMN_GC);
            listview->InsertColumn(4,wxCAPTION_COLUMN_UK);
            listview->InsertColumn(5,wxCAPTION_COLUMN_REZ);
            listview->InsertColumn(6,wxCAPTION_COLUMN_SOTRSB);
            listview->InsertColumn(7,wxCAPTION_COLUMN_DATE);
            str_first = dir.GetName(); str_last= wxINSERT_ICO; str_full=str_first; str_full+=str_last;
            wxImage *image = new wxImage(str_full,wxBITMAP_TYPE_ICO);
            image->Rescale(16,16);
            vr4->Add(new wxBitmapButton(this,wxID_BUTTON_INS_PROV,wxBitmap(*image)), 1, wxEXPAND,0);
            str_first = dir.GetName(); str_last= wxUPDATE_ICO; str_full=str_first; str_full+=str_last;
            wxImage *image1 = new wxImage(str_full,wxBITMAP_TYPE_ICO);
            image->Rescale(16,16);
            vr4->Add(new wxBitmapButton(this,wxID_BUTTON_UPD_PROV,wxBitmap(*image1)), 1, wxEXPAND,0);
            str_first = dir.GetName(); str_last= wxDELETE_ICO; str_full=str_first; str_full+=str_last;
            wxImage *image2 = new wxImage(str_full,wxBITMAP_TYPE_ICO);
            image->Rescale(16,16);
            vr4->Add(new wxBitmapButton(this,wxID_BUTTON_DEL_PROV,wxBitmap(*image2)), 1, wxEXPAND,0);
            str_first = dir.GetName(); str_last= wxCOMMENT_ICO; str_full=str_first; str_full+=str_last;
            wxImage *image3 = new wxImage(str_full,wxBITMAP_TYPE_ICO);
            image->Rescale(16,16);
            vr4->Add(new wxBitmapButton(this,wxID_BUTTON_KOM_PROV,wxBitmap(*image3)), 1, wxEXPAND,0);
            to_static_box4->Add(vr4, 0, wxEXPAND,0);
            to_static_box4->Add(listview, 1, wxEXPAND,0);
            vert->Add(to_static_box4, 1, wxEXPAND,0);
            //this->SetStatusText(wxCOUNT_PROV_TO,0);
            vert->Layout();
            (this->FindWindow(wxID_LISTVIEW_PROV))->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(ProvToFrm::OnMouse));
            (this->FindWindow(wxID_BUTTON_INS_PROV))->SetToolTip("�������� ������");
            (this->FindWindow(wxID_BUTTON_UPD_PROV))->SetToolTip("�������� ������");
            (this->FindWindow(wxID_BUTTON_DEL_PROV))->SetToolTip("������� ������");
            (this->FindWindow(wxID_BUTTON_KOM_PROV))->SetToolTip("��������� �����������");
            (this->FindWindow(wxID_BUTTON_INS_PROV))->SetBackgroundColour(*wxWHITE);
            (this->FindWindow(wxID_BUTTON_UPD_PROV))->SetBackgroundColour(*wxWHITE);
            (this->FindWindow(wxID_BUTTON_DEL_PROV))->SetBackgroundColour(*wxWHITE);
            (this->FindWindow(wxID_BUTTON_KOM_PROV))->SetBackgroundColour(*wxWHITE);
            if(id_to!=0)
            {
                wxString sqlText; sqlText<<wxSqlTextProvTo;
                sqlText<<id_to; sqlText<<wxSqlEndText;
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
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(wxAtoi(row[8])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                if (l==0) 
                                {
                                    for(register int k =0; k<MyTypeCooperationArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyTypeCooperationArray.Item(k).idTypeCooperation.c_str())==atoi(row[l])) //���������� �������
                                        if(MyTypeCooperationArray.Item(k).idTypeCooperation==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyTypeCooperationArray.Item(k).nameTypeCooperation);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==1) 
                                {
                                    for(register int k =0; k<MyTypeProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyTypeProvArray.Item(k).idTypeProv.c_str())==atoi(row[l])) //���������� �������
                                        if(MyTypeProvArray.Item(k).idTypeProv==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyTypeProvArray.Item(k).nameTypeProv);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==2) 
                                {
                                    for(register int k =0; k<MyOcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyOcArray.Item(k).idOc.c_str())==atoi(row[l])) //���������� �������
                                        if(MyOcArray.Item(k).idOc==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyOcArray.Item(k).nameOc);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==3) 
                                {
                                    for(register int k =0; k<MyGcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //���������� �������
                                        if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //���������� �������
                                        {   
                                            listview->SetItem(i,l,MyGcArray.Item(k).nameGc);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==4) 
                                {
                                    for(register int k =0; k<MyUkRfArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //���������� �������
                                        if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyUkRfArray.Item(k).nameUkRf);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==5) 
                                {
                                    for(register int k =0; k<MyRezProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //���������� �������
                                        if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyRezProvArray.Item(k).nameRezProv);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==6) 
                                {
                                    for(register int k =0; k<MyFioSbArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //���������� �������
                                        if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyFioSbArray.Item(k).nameFioSb);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==7) {listview->SetItem(i,l,row[l]);}
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                        //wxString status = wxCOUNT_PROV_TO; 
                        count_to_prov=num_rows;
                        //this->SetStatusText(status,0);
                        wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // ������� ����������
                }  
            }
            delete image; delete image1; delete image2; delete image3;
        }
    }
    else //���� �� ������� �������
    {
        ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();
        {
                wxString sqlText; sqlText<<wxSqlTextProvTo;
                sqlText<<id_to; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else
                {
                    wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV));
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
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[8])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                if (l==0) 
                                {
                                    for(register int k =0; k<MyTypeCooperationArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyTypeCooperationArray.Item(k).idTypeCooperation.c_str())==atoi(row[l])) //���������� �������
                                        if(MyTypeCooperationArray.Item(k).idTypeCooperation==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyTypeCooperationArray.Item(k).nameTypeCooperation);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==1) 
                                {
                                    for(register int k =0; k<MyTypeProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyTypeProvArray.Item(k).idTypeProv.c_str())==atoi(row[l])) //���������� �������
                                        if(MyTypeProvArray.Item(k).idTypeProv==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyTypeProvArray.Item(k).nameTypeProv);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==2) 
                                {
                                    for(register int k =0; k<MyOcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyOcArray.Item(k).idOc.c_str())==atoi(row[l])) //���������� �������
                                        if(MyOcArray.Item(k).idOc==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyOcArray.Item(k).nameOc);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==3) 
                                {
                                    for(register int k =0; k<MyGcArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //���������� �������
                                        if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //���������� �������
                                        {   
                                            listview->SetItem(i,l,MyGcArray.Item(k).nameGc);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==4) 
                                {
                                    for(register int k =0; k<MyUkRfArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //���������� �������
                                        if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyUkRfArray.Item(k).nameUkRf);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==5) 
                                {
                                    for(register int k =0; k<MyRezProvArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //���������� �������
                                        if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyRezProvArray.Item(k).nameRezProv);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==6) 
                                {
                                    for(register int k =0; k<MyFioSbArray.GetCount();++k) //��������� ���� ������ � ����������� 
                                    {
                                        //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //���������� �������
                                        if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //���������� �������
                                        {
                                            listview->SetItem(i,l,MyFioSbArray.Item(k).nameFioSb);
                                            break; //������� �� ���������� �����
                                        }
                                    }
                                }
                                if (l==7) {listview->SetItem(i,l,row[l]);}
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //�������� ������ ������� �� ����� ������ �������� ��������
                        //wxString status = wxCOUNT_PROV_TO; 
                        count_to_prov=num_rows;
                        //this->SetStatusText(status,0);
                        wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // ������� ����������
                }  
            }
    }
}
void ProvToFrm::ListViewAssortiment (void)
{
    if(!(wxListView*)(this->FindWindow(wxID_LISTVIEW_ASRT))) //���� �� ������� �� �������
    {
        wxDir dir(wxGetCwd());
        if (dir.IsOpened())
        {
        wxString str_full, str_first, str_last;
        vr3 = new wxBoxSizer(wxVERTICAL);
        stBox3 = new wxStaticBox(this,wxID_ANY,wxCAPTION_STATICBOX_LIST_ASSORTI);
        to_static_box3 = new wxStaticBoxSizer(stBox3,wxHORIZONTAL);
        wxListView *listview = new wxListView(this, wxID_LISTVIEW_ASRT);
        listview->InsertColumn(0,wxCAPTION_COLUMN_PROD_GROUP);
        listview->InsertColumn(1,wxCAPTION_COLUMN_PROD_SUBGROUP);
        str_first = dir.GetName(); str_last= wxINSERT_ICO; str_full=str_first; str_full+=str_last;
        wxImage *image = new wxImage(str_full,wxBITMAP_TYPE_ICO);
        image->Rescale(16,16);
        vr3->Add(new wxBitmapButton(this,wxID_BUTTON_INS_ASRT,wxBitmap(*image)), 1, wxEXPAND,0);
        str_first = dir.GetName(); str_last= wxDELETE_ICO; str_full=str_first; str_full+=str_last;
        wxImage *image1 = new wxImage(str_full,wxBITMAP_TYPE_ICO);
        image->Rescale(16,16);
        vr3->Add(new wxBitmapButton(this,wxID_BUTTON_DEL_ASRT,wxBitmap(*image1)), 1, wxEXPAND,0);
        to_static_box3->Add(vr3, 0, wxEXPAND,0);
        to_static_box3->Add(listview, 1, wxEXPAND,0);
        vert->Add(to_static_box3, 1, wxEXPAND,0);
        //this->SetStatusText(wxCOUNT_ASSORTI,2);
        vert->Layout();
        (this->FindWindow(wxID_LISTVIEW_ASRT))->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(ProvToFrm::OnMouse));
        (this->FindWindow(wxID_BUTTON_INS_ASRT))->SetToolTip("�������� ������");
        (this->FindWindow(wxID_BUTTON_DEL_ASRT))->SetToolTip("������� ������");
        (this->FindWindow(wxID_BUTTON_INS_ASRT))->SetBackgroundColour(*wxWHITE);
        (this->FindWindow(wxID_BUTTON_DEL_ASRT))->SetBackgroundColour(*wxWHITE);
        {
            if(!((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->IsEmpty())
            {
                wxString inn_to = ((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue();
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
                        for (register int i = 0; i < num_rows; i++) // ����� �������
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(wxAtoi(row[2])); //������ ���������� ����
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                wxString str; str<<row[l];
                                listview->SetItem(i,l,str);
                            }
                            delete f;
                        }
                        listview->SetColumnWidth(0,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� ��������
                        listview->SetColumnWidth(1,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� ��������
                        //wxString status = wxCOUNT_ASSORTI; 
                        count_assorti=num_rows;
                        //this->SetStatusText(status,2);
                        wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // ������� ����������
                }
            }}
            delete image; delete image1;
        }}
    }
    else                    //���� �� ������� �������
    {
        ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->DeleteAllItems();
        {
            wxString sqlText; sqlText<<wxSqlTextAssortiTo;
            sqlText<<((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue(); sqlText<<wxSqlEndText;
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
                        f->SetMask(wxLIST_MASK_TEXT);
                        f->SetColumn(0); //������ �������
                        f->SetData(atoi(row[2])); //������ ���������� ����
                        f->SetId(i); //����������� ����� ������
                        ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->InsertItem(*f); 
                        for (register int l = 0; l < num_fields-1; l++)
                        {
                            wxString str; str<<row[l];
                            ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->SetItem(i,l,str); //����� �������� �������� � ������ �������
                        }
                        delete f;
                    }
                    ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->SetColumnWidth(0,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� ��������
                    ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->SetColumnWidth(1,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� ��������
                    //wxString status = wxCOUNT_ASSORTI; 
                    count_assorti=num_rows;
                    //this->SetStatusText(status,2);
                    wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //����������� ���������� ��������� �� ������������ ����
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //����������� ���������� ��������� �� ������������ ����
    grandParentWindow->WorkStatusBar();
                } else {;}
                mysql_free_result(res); // ������� ����������
            }
        }
    } 
}

void ProvToFrm::DeleteAssorti (void)
{
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT)); //�������� ��������� �� ��������� � �������������
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
                wxString idAssirti; idAssirti<<f->GetData(); //����� � ���������� ������ ��������� � ���������
                if(!idAssirti.IsEmpty())
                {
                    wxString sqlText = wxSqlTextDelAssorti; sqlText<<idAssirti; sqlText<<wxSqlEndText;
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
                ListViewAssortiment(); //�������������� �������� � �������������
                wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_DEL_COUNT; str<<count; //������ ������ � ���-��� ��������� �����
                InformationSleep(str,sec_for_sleep_window_info,this);
            } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);} //���� �� ������� �� ���� ������, �� ������������� �� ���� ������������ � ��������� ���������
            (this->FindWindow(wxID_BUTTON_DEL_ASRT))->SetFocus();
        }
}
void ProvToFrm::InsertAssorti (void)
{
    if (id_to==0) {InformationSleep(wxINFO_NOT_TO,sec_for_sleep_window_info,this);}
        else
        {
            wxString inn_text = ((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue();
            EnterAssortiment EntAss(this, wxID_ANY, inn_text);  
            if(EntAss.ShowModal () == wxID_CANCEL) {;} 
            else 
            {
                ListViewAssortiment();
            }
            (this->FindWindow(wxID_BUTTON_INS_ASRT))->SetFocus();
        }
}
void ProvToFrm::ProvInnTo (void)
    {
        ClearForm(); //������� ���� �����
        wxString inn_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue();
        if((type_cooperation->GetSelection())==4) //������ ���������� � ���� �������, ��� �� ��� ���
        {}
        else
        {
            if ((int)inn_to.Len()!=10&&(int)inn_to.Len()!=12) {InformationSleep(wxWARNING_INN,sec_for_sleep_window_info, this); return;}
        }
        //else
        {
            //if(flag_bl_sb==1)  {if(proverka_bl_sb(conn, inn_to, 0)==1) {;} else {return;}}
            wxString sqlText;
            switch (type_cooperation->GetSelection())
            {
                case 0: //pos
                {
                sqlText<<wxSqlTextProvInn; sqlText<<inn_to; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                else
                {
                    MYSQL_RES *res = mysql_store_result(::conn); // ����� ���������,
                    int num_fields = mysql_num_fields(res); // ���������� �����
                    int num_rows = mysql_num_rows(res); // � ���������� �����.
                    if(num_rows>0) //��������� ������� ����� ����� SELECT. 
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                        id_to=wxAtoi(row[0]); //����������� ����� ���� ��
                        ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //��������� � ������� ������������ ��
                        for(register int i =0; i<MyBrandNameArray.GetCount();++i) //��������� ���� ������ � ����������� ����� ����� ������� ���������� �� ��������� ��������� � ��������� ����
                        {
                            //if(!(MyBrandNameArray.Item(i).idBrandName).compare(row[2])) //���������� �������
                            if(MyBrandNameArray.Item(i).idBrandName==wxAtoi(row[2])) //���������� �������
                            {
                                ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->ChangeValue(MyBrandNameArray.Item(i).nameBrandName); //������� � ���� ������������ ����
                                for(register int j =0; j<MyBrandTypeArray.GetCount();++j) //��������� ���� ������ � ����������� ����� ����� ���� ���� ���������������� ���������� ��������
                                {
                                    //if(!MyBrandNameArray.Item(i).idBrandType.compare(MyBrandTypeArray.Item(j).idBrandType)) //���������� �������
                                    if(MyBrandNameArray.Item(i).idBrandType==MyBrandTypeArray.Item(j).idBrandType) //���������� �������
                                    {
                        
                                        ((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(MyBrandTypeArray.Item(j).nameBrandType); //������� � ����������� ���� ��� ����
                                        break; //������� �� ���������� ����� ������ ���� ����
                                    }
                                }
                                break; //������� �� ���������� ����� ������ ���������� �� ������������ ����
                            } else {((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(wxBRAND_DEFAULT); ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->SetLabelText(wxBRAND_DEFAULT);}
                        }
                        if(row[3]) {((wxTextCtrl*)this->FindWindow(wxID_TO_KOL_TT))->SetLabelText(row[3]);} else {((wxTextCtrl*)this->FindWindow(wxID_TO_KOL_TT))->SetLabelText(wxTT_DEFAULT);}
                        if(row[4]) {((wxTextCtrl*)this->FindWindow(wxID_TO_BANK_KONK))->SetLabelText(row[4]);} else {((wxTextCtrl*)this->FindWindow(wxID_TO_BANK_KONK))->SetLabelText(wxNOT_DEFAULT);}
                        if(row[5])
                        {
                            wxString inetFlag = row[5];
                            if(inetFlag.compare("0")==0)
                            {
                                ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->SetSelection(0); //�������� ������� �������� �������� - ���
                                if((wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) (wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))->Destroy(); //���� ����������, ��������� ������� - ��������-�������
                                if((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) (wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))->Destroy(); //���� ����������, ��������� ���� � ��������-������
                            }
                            if(inetFlag.compare("1")==0)
                            {
                                ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->SetSelection(1); //�������� ������� �������� �������� - ��
                                if(row[6])
                                {
                                    if(!(wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) to_7->Add(new wxStaticText(this,wxID_TO_STATIC_SITE,"��������-����"),0, wxEXPAND |wxALL,5);
                                    if(!(wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) to_7->Add(new wxTextCtrl(this,wxID_TO_SITE_INET, wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_AUTO_URL),1, wxEXPAND |wxALL,5);
                                    ((wxTextCtrl*)this->FindWindow(wxID_TO_SITE_INET))->ChangeValue(row[6]);                              
                                }
                            }
                        }
                        if((wxListView*)(this->FindWindow(wxID_LISTVIEW_ASRT))) {ListViewAssortiment();}
                        if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                        if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                        vert->Layout(); //������ ������� ����������� ������ ���� �����
                        this->Refresh(); //�������������� �����      
                    }
                    else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                    mysql_free_result(res); // ������� ����������
                }
                break;
                }
                case 1: //�� ������
                {
                    sqlText<<wxSqlTextProvInn1; sqlText<<inn_to; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(::conn); // ����� ���������,
                        int num_fields = mysql_num_fields(res); // ���������� �����
                        int num_rows = mysql_num_rows(res); // � ���������� �����.
                        if(num_rows>0) //��������� ������� ����� ����� SELECT. 
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            id_to=wxAtoi(row[0]); //����������� ����� ���� ��
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //��������� � ������� ������������ ��
                            if(row[2]) {((wxTextCtrl*)this->FindWindow(wxID_UL_KOL_SOTR))->SetLabelText(row[2]);} else {((wxTextCtrl*)this->FindWindow(wxID_UL_KOL_SOTR))->SetLabelText(wxSOTR_DEFAULT);}

                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                            vert->Layout(); //������ ������� ����������� ������ ���� �����
                            this->Refresh(); //�������������� �����      
                        }
                        else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // ������� ����������
                    }
                    break;
                }
                case 2: //��������-���������
                {
                    sqlText<<wxSqlTextProvInn2; sqlText<<inn_to; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(::conn); // ����� ���������,
                        int num_fields = mysql_num_fields(res); // ���������� �����
                        int num_rows = mysql_num_rows(res); // � ���������� �����.
                        if(num_rows>0) //��������� ������� ����� ����� SELECT. 
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            id_to=wxAtoi(row[0]); //����������� ����� ���� ��
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //��������� � ������� ������������ ��
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->ChangeValue(wxString(row[2])); //��������� � ������� ������������ ��
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_EK_SITE_INET)))->ChangeValue(wxString(row[3])); //��������� � ������� ������������ ��
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                            vert->Layout(); //������ ������� ����������� ������ ���� �����
                            this->Refresh(); //�������������� �����      
                        }
                        else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // ������� ����������
                    }
                    break;
                }
                case 3: //����� ������
                case 5: //���
                case 6: //�� �� ������ ��������
                {
                    sqlText<<wxSqlTextProvInn2; sqlText<<inn_to; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(::conn); // ����� ���������,
                        int num_fields = mysql_num_fields(res); // ���������� �����
                        int num_rows = mysql_num_rows(res); // � ���������� �����.
                        if(num_rows>0) //��������� ������� ����� ����� SELECT. 
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            id_to=wxAtoi(row[0]); //����������� ����� ���� ��
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //��������� � ������� ������������ ��
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                            vert->Layout(); //������ ������� ����������� ������ ���� �����
                            this->Refresh(); //�������������� �����      
                        }
                        else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // ������� ����������
                    }
                    break;
                }
                case 4: //����������
                {
                    if(inn_to.IsEmpty()) {InformationSleep(wxWARNING_INN,sec_for_sleep_window_info, this); break;}
                    sqlText<<wxSqlTextProvInn3; sqlText<<inn_to; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(::conn); // ����� ���������,
                        int num_fields = mysql_num_fields(res); // ���������� �����
                        int num_rows = mysql_num_rows(res); // � ���������� �����.
                        if(num_rows>0) //��������� ������� ����� ����� SELECT. 
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            id_to=wxAtoi(row[0]); //����������� ����� ���� ��
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //��������� � ������� ������������ ��
                            wxString flag_fl_not_ip = row[2]; //�������� ������� ����, ��� ����� �� �������� ��
                            if(!flag_fl_not_ip.IsEmpty()) {((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(true);} else {((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(false);}//���� ���������� �� �����, �� ������ ����� � �������� � ��������
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_KONTRACT))) {ListViewKontract();}
                            vert->Layout(); //������ ������� ����������� ������ ���� �����
                            this->Refresh(); //�������������� �����      
                        }
                        else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // ������� ����������
                    }
                    break;
                }
                default: break;
            }
        }
    }
    

void ProvToFrm::DeleteCardTo (void)
    {
        if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
        {
            wxString inn_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue();
            //if ((int)inn_to.Len()!=10&&(int)inn_to.Len()!=12&&(id_to>0)) {InformationSleep(wxWARNING_INN,sec_for_sleep_window_info, this); return;}
            if (id_to<1) {InformationSleep(wxINFO_NOT_TO,sec_for_sleep_window_info, this); return;}
            else
            {
                wxString sqlText = wxSqlTextDeleteTo; 
                //sqlText<<inn_to; 
                sqlText<<id_to; 
                sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else {InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this); ClearForm(1);} 
            }
        }
    }
void ProvToFrm::CommentProvTo (void)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV)); //�������� ��������� �� ��������� � ���������� ��
        int flag = 0;
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
            wxString idProvTo; idProvTo<<f->GetData(); //����� � ���������� ������ ��������� � ���������
            if(!idProvTo.IsEmpty())
            {
                
                wxString sqlText = wxSqlTextSpComProvTo; sqlText<<idProvTo; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
                    for (;row;row=mysql_fetch_row(res))
                    {
                        flag=1; //������� ����, ��� ����������� ������ � ��
                        wxMessageBox(row[0],wxCAPTION_COMMENT,wxOK,this);
                    }
                    mysql_free_result(res);
                } 
            } else {InformationSleep(wxWARNING_NO_DATA,sec_for_sleep_window_info,this);} 
            delete f;
        }
        if(flag==0) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
        (this->FindWindow(wxID_BUTTON_KOM_PROV))->SetFocus();
    }

void ProvToFrm::DeleteProvTo (void)
{
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV)); //�������� ��������� �� ��������� � ���������� ��
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
                wxString idProvTo; idProvTo<<f->GetData(); //����� � ���������� ������ ��������� � ���������
                if(!idProvTo.IsEmpty())
                {
                    wxString sqlText = wxSqlTextDelProvTo; sqlText<<idProvTo; sqlText<<wxSqlEndText;
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
                ListViewProvTo(); //�������������� �������� � �������������
                wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_DEL_COUNT; str<<count; //������ ������ � ���-��� ��������� �����
                InformationSleep(str,sec_for_sleep_window_info,this);
                //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
            } else {;} //���� �� ������� �� ���� ������, �� ������������� �� ���� ������������ � ��������� ���������
            (this->FindWindow(wxID_BUTTON_DEL_PROV))->SetFocus();
        }
}

void ProvToFrm::CommentProvSotrTo (void)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR)); //�������� ��������� �� ��������� � ���������� ��
        int flag = 0;
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
            wxString idProvSotrTo; idProvSotrTo<<f->GetData(); //����� � ���������� ������ ��������� � ���������
            if(!idProvSotrTo.IsEmpty())
            {
                
                wxString sqlText = wxSqlTextComProvSotrToStart; sqlText<<idProvSotrTo; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                    MYSQL_ROW row = mysql_fetch_row(res); // �������� ������ 
                    for (;row;row=mysql_fetch_row(res))
                    {
                        flag=1; //������� ����, ��� ����������� ������ � ��
                        wxMessageBox(row[0],wxCAPTION_COMMENT,wxOK,this);
                    }
                    mysql_free_result(res);
                } 
            } else {InformationSleep(wxWARNING_NO_DATA,sec_for_sleep_window_info,this);} 
            delete f;
        }
        if(flag==0) {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
        (this->FindWindow(wxID_BUTTON_KOM_SOTR))->SetFocus();
    }

void ProvToFrm::DeleteProvSotrTo (void)
{
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR)); //�������� ��������� �� ��������� � ���������� ����������� ��
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
                wxString idProvSotrTo; idProvSotrTo<<f->GetData(); //����� � ���������� ������ ��������� � ���������
                if(!idProvSotrTo.IsEmpty())
                {
                    wxString sqlText = wxSqlTextDelProvSotrToStart; sqlText<<idProvSotrTo; sqlText<<wxSqlEndText;
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
                ListViewProvSotr(); //�������������� �������� � �������������
                wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_DEL_COUNT; str<<count; //������ ������ � ���-��� ��������� �����
                InformationSleep(str,sec_for_sleep_window_info,this);
                //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
            } else {;} //���� �� ������� �� ���� ������, �� ������������� �� ���� ������������ � ��������� ���������
            (this->FindWindow(wxID_BUTTON_DEL_SOTR))->SetFocus();
        }
}
void ProvToFrm::ListUpdate (void)
{
    ListViewProvTo();
    ListViewProvSotr();
    return;
}
