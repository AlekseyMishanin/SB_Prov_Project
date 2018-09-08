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
        ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->SetDescriptiveText(wxString("������� ��� ��� ������...")); //����� �� ��������� � ������ ������
        ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->ShowCancelButton(1); //������ �������� ������ ������
        wxMenu *file_menu = new wxMenu; //������� ���� ��� ������
        file_menu->Append(wxID_AG_PS_MENU_FIO, "&���"); 
        file_menu->Append(wxID_AG_PS_MENU_PASP, "&�������");
        ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->SetMenu(file_menu); //���������� ���� � ��������� ������
        //to_static_box1->Add(new wxButton(panel,wxID_AG_PS_BUTTON_WORK,"�����"), 0, wxEXPAND|wxLEFT|wxRIGHT ,10);
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
        //listview->SetBackgroundStyle(wxBG_STYLE_TRANSPARENT); //������ ��� ����������
        
        //listview->SetOwnBackgroundColour(wxTransparentColour); //���������� ���
        //listview->SetOwnForegroundColour(wxTransparentColour);
        //listview->SetBackgroundStyle(wxBG_STYLE_CUSTOM); //��� ���������������� �������������
        //listview->Connect(wxEVT_ERASE_BACKGROUND,wxEraseEventHandler(ProvAgFrm::OnEaraseListbox)); //��� ������� ���������� ���� ��������� ���� �����
        //listview->Connect(wxEVT_PAINT,wxPaintEventHandler(ProvAgFrm::OnPaintListbox)); //��� ������� ��������� ��������� ���� �����
        
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
        wxWindowList list = this->GetChildren(); //�������� ������ ���� �������� ����
        for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) {(*it)->SetBackgroundColour(*wxWHITE);} //����� �������� ���������� ��� ���� � ������ ���� ����
        wxWindowList list1 = this->GetChildren(); //�������� ������ ���� �������� ����
        for(register wxWindowList::const_iterator it = list1.begin(); it!=list1.end(); ++it) {(*it)->SetBackgroundColour(*wxWHITE);} //����� �������� ���������� ��� ���� � ������ ���� ����
        //Center(); //���������� ����
    }
}
void ProvAgFrm::OnPaintListbox(wxPaintEvent& event) //�������� �������� ���. ����. ��� ��������, � ��� ��������� - ���. ������� ��� ������
{

}
void ProvAgFrm::OnEaraseListbox(wxEraseEvent& event) //������� ����������� ����. ��� ������, �� ������ ��������� �� 20-25%. ��������� ����������� ��� ���.�������� ����
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
void ProvAgFrm::OnSize(wxSizeEvent& event) //����� ������� ���� �� ����� ������� ��������� ������ ��� ������ �������
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
void ProvAgFrm::OnMove(wxMoveEvent& event) //����� ������� ���� �� ����� ������� ������������ ����
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
    textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
    if(textPoisk.IsEmpty()) {InformationSleep (wxINFO_EMPTY_POISK, sec_for_sleep_window_info, this);} //���� ������ ������ �����, ������������� �� ���� ������������
    else 
    {
        textPoisk.Replace("?","_",true); //� �������� ������ ������ ? �� _ ��� sql-�������
        wxString sqlText;
        if(id_menu==0) //����� �� ���
        {
            sqlText<<wxSqlTextPoiskFzFio;
            sqlText<<textPoisk; sqlText<<wxSqlPercentEnd;
        }
        if(id_menu==1) //����� �� ���������
        {
            textPoisk.Replace(" ","",true); //� �������� ������ ������ ������ �� ������ �������� ��� sql-�������
            sqlText<<wxSqlTextPoiskFzPasp;
            sqlText<<textPoisk; sqlText<<wxSqlPercentEnd;
        }
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
        else 
        {
            MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
            int num_fields = mysql_num_fields(res); // ���������� �����
            int num_rows = mysql_num_rows(res); // � ���������� �����.
            if(num_rows>0)
            {   
                count_find+=num_rows; //���������� ���������� ���������� ���-�� ���������� �����
                wxListView* listview = ((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES));
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
                GetItemCountListCtrl();        //������� ����� ���-�� ����� � ���������
            } else {InformationSleep (wxINFO_EMPTY_REZ_POISK_FZ, sec_for_sleep_window_info, this);}
            mysql_free_result(res); // ������� ����������
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
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES)); //�������� ��������� �� ��������� 
        int count = 0;
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} //�� ������� ������ ������, ������� ������� �� �����
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
            (((this->GetParent())->GetParent())->FindWindow(wxID_AG_CM_BUTTON_UPD))->SetFocus(); 
        }
    }
    if(event.GetId()==wxID_AG_CM_BUTTON_DEL)  
    {
        DeleteFz(); ((wxAuiWorkPanel*)((this->GetParent())->GetParent()))->WorkStatusBar();    
    }
    if(event.GetId()==wxID_AG_CM_BUTTON_PRV)  
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES)); //�������� ��������� �� ��������� 
        if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;}
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
                ListProvFz ListPrFz(this,wxAtoi(idFz),captionFioAndPasp,wxID_ANY,wxPoint(x,y),wxSize(width,height)); //������� ���������� ���� � ���������� ���������� ���.���� � ���������� �� ���+�������
                if(ListPrFz.ShowModal() == wxID_CANCEL) {;} else {;}
            }
             else                   //��������� ������������ �� ��������� �� ini-�����
            {
                ListProvFz ListPrFz(this,wxAtoi(idFz),captionFioAndPasp); //������� ���������� ���� � ���������� ���������� ���.���� � ���������� �� ���+�������
                if(ListPrFz.ShowModal() == wxID_CANCEL) {;} else {;}
            }
        }
        (((this->GetParent())->GetParent())->FindWindow(wxID_AG_CM_BUTTON_PRV))->SetFocus();     
    }
}
void ProvAgFrm::OnMenu (wxCommandEvent& event)
{
    if(event.GetId()==wxID_AG_PS_MENU_FIO) {id_menu=0; ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->SetDescriptiveText(wxString("������� ��� ��� ������...")); ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->Clear();} // ��� ����� ��������� ������(���, �������) ������������: ����������, ������ ���������, ������� ���� �����
    if(event.GetId()==wxID_AG_PS_MENU_PASP) {id_menu=1; ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->SetDescriptiveText(wxString("������� ������� ��� ������...")); ((wxSearchCtrl*)this->FindWindow(wxID_AG_PS_TEXT_NAME))->Clear();} // ��� ����� ��������� ������(���, �������) ������������: ����������, ������ ���������, ������� ���� �����
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
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_AG_SP_LIST_RES)); //�������� ��������� �� ���������  
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
                    /*sqlText = wxSqlTextDelFzProvStart; sqlText<<idFz; sqlText<<wxSqlEndText;
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
            (((this->GetParent())->GetParent())->FindWindow(wxID_AG_CM_BUTTON_DEL))->SetFocus();
        }
}
void ProvAgFrm::OnMouse(wxMouseEvent& event)
{
	if (event.GetId()==wxID_AG_SP_LIST_RES)
	{
        //�������� ������ ������ ��-�� menuitem
        wxPoint point = event.GetPosition(); //���������� ����������� ����������� ��������� ����
        wxMenu *menu = new wxMenu;
        //wxMenuItem *menuitem = new wxMenuItem(NULL, wxID_BUTTON_DEF_MENU,"�������");
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
