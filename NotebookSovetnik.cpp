#include "CrossFrm.h"

extern MYSQL* conn;
extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;
extern void EditStringFioFull (wxString& str);

BEGIN_EVENT_TABLE(NotebookSovetnik,wxFrame)
    EVT_SIZE(NotebookSovetnik::OnSize)
	EVT_MOVE_END(NotebookSovetnik::OnMove)
    EVT_NOTEBOOK_PAGE_CHANGED(wxID_SOV_NOTEBOOK,NotebookSovetnik::GhangePageNotebook) //��������� �������� ��������
    EVT_LIST_ITEM_SELECTED(wxID_SOV_LISTVIEW_LIST_SOV,NotebookSovetnik::ListviewChangedItem) //��������� ������ � listview �� ������� ����������
    EVT_TEXT_ENTER(wxID_SOV_SEARCHCTRL_F_REG, NotebookSovetnik::OnEnter) //������ ������ ����� � ��������� ���� ������
    EVT_TEXT_ENTER(wxID_SOV_SEARCHCTRL_F_SOV, NotebookSovetnik::OnEnter) //������ ������ ����� � ��������� ���� ������
    EVT_TEXT_ENTER(wxID_SOV_SEARCHCTRL_F_HIS, NotebookSovetnik::OnEnter) //������ ������ ����� � ��������� ���� ������
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_SOV_COLLPANE_F_REG, NotebookSovetnik::CollapChanged) //������ �������� ������ �����
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_SOV_COLLPANE_SOV_SPIS, NotebookSovetnik::CollapChanged) //������ �������� ������ �����
    EVT_COLLAPSIBLEPANE_CHANGED(wxID_SOV_COLLPANE_HIS_OTP, NotebookSovetnik::CollapChanged) //������ �������� ������ �����
    EVT_TREELIST_ITEM_CHECKED(wxID_SOV_LISTVIEW_TEK_OTP, NotebookSovetnik::TreeListChanged)
END_EVENT_TABLE()

NotebookSovetnik::NotebookSovetnik(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint& pos, const wxSize& size , long style )
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
        wxString str_full, str_first, str_last; //���������� ���������� ��� ���������� ���� � �������
        wxImageList *imageList = new wxImageList(16,16);                //������� �����. �������� ������ �����������
        str_first = dir.GetName(); str_last= wxCALENDAR_NOW_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������
        wxIcon icon;                                                    //������� ������
        icon.LoadFile(str_full,wxBITMAP_TYPE_ICO);                      //��������� �������� �� �����
        imageList->Add(icon);                                           //��������� ����� ����������� � ������
        str_last= wxCALENDAR_HISTORY_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������
        icon.LoadFile(str_full,wxBITMAP_TYPE_ICO);                      //��������� �������� �� �����
        imageList->Add(icon);                                           //��������� ����� ����������� � ������
        str_last= wxSECURITY_MAN_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������
        icon.LoadFile(str_full,wxBITMAP_TYPE_ICO);                      //��������� �������� �� �����
        imageList->Add(icon);                                           //��������� ����� ����������� � ������
        str_last= wxWORLD_WIDE_ICO; str_full=str_first; str_full+=str_last;     //���������� ���� � ��������
        icon.LoadFile(str_full,wxBITMAP_TYPE_ICO);                      //��������� �������� �� �����
        imageList->Add(icon);                                           //��������� ����� ����������� � ������
        nb = new wxNotebook(this, wxID_SOV_NOTEBOOK, wxPoint(-1, -1), wxSize(-1, -1), wxNB_LEFT);
        wxPanel *panel1 = new wxPanel(nb, wxID_PANEL_LIST_SOV);     //������ ��� ��������� �������� ���������
        wxBoxSizer *vert_page_sotr = new wxBoxSizer(wxVERTICAL);    //��������� ����������� ���� ��� �������� ���������
        wxBoxSizer *horz_local = new wxBoxSizer(wxHORIZONTAL);      //��������� ����������� ���� ��� �������� ���������
        wxBoxSizer *vr_1 = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *vr_2 = new wxBoxSizer(wxVERTICAL);
        wxCollapsiblePane *collpane1 = new wxCollapsiblePane(panel1, wxID_SOV_COLLPANE_SOV_SPIS, wxSTRING_FIND, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE); //������� �������������� ������ �� ������ ����������� ������������� ���� ��� ���.������
        vr_2->Add(collpane1, 0, wxEXPAND|wxALL,5);
        wxWindow *win1 = collpane1->GetPane();
        wxSizer *paneSz1 = new wxBoxSizer(wxHORIZONTAL);
        paneSz1->Add(new wxSearchCtrl(win1,wxID_SOV_SEARCHCTRL_F_SOV, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT), 1, wxEXPAND|wxALL, 5);
        win1->SetSizer(paneSz1);
        paneSz1->SetSizeHints(win1);
        vr_2->Add(new wxListView(panel1, wxID_SOV_LISTVIEW_LIST_SOV), 1, wxEXPAND); //������� ������� �� �������� ����������
        horz_local->Add(vr_2, 2, wxEXPAND);
        //horz_local->Add(new wxListView(panel1, wxID_SOV_LISTVIEW_LIST_SOV), 2, wxEXPAND); //������� ������� �� �������� ����������
        wxStaticBox *stBox = new wxStaticBox(panel1,wxID_ANY,wxCAPTION_STATICBOX_HIS_DOLZ); //������� ���������� ��� �������� �� ������� ����������
        wxStaticBoxSizer *to_static_box = new wxStaticBoxSizer(stBox,wxVERTICAL); //������� ����������� ��� �������� �� ������� ����������
        staticDolz = new wxStaticText(panel1,wxID_SOV_STATICTEXT_HIS_DOLZ,wxNOT_DATA); //������� ����������� ��������� ���� �� ������� ������� ����������
        to_static_box->Add(staticDolz,0,wxEXPAND|wxALL,5); //��������� ����������� ��������� ���� � ������������
        treeRegion = new wxTreeCtrl(panel1, wxID_SOV_TREEVIEW_REGION); //������� ������ � ��������� ��� �������� �� ������� ����������
        vr_1->Add(treeRegion, 3, wxEXPAND); //��������� ������ ��� � ������������� ���������� ������������
        vr_1->Add(to_static_box, 2, wxEXPAND); //��������� ����������� ����������� � ���������� ������������
        horz_local->Add(vr_1, 1, wxEXPAND); //��������� ����������� � ������� � �������� � ���������� ��������������� ������������
        banner = new wxBannerWindow(panel1, wxID_SOV_BANNER_SOV_INFO, wxDOWN); //������� ������� ������
        vr_1->Add(banner, 1, wxEXPAND|wxALL,5); //��������� ������� � ������������� ���������� ������������
        vert_page_sotr->Add(horz_local, 1, wxEXPAND); //�������� ����������� � �������� ������������� ������������ ��������
        banner->SetText(wxSTRING_PERSONAL_DATA, wxNULL_STRING); //����� � ������ ������
        banner->SetGradient(*wxWHITE,*wxLIGHT_GREY); //������������� ���� ��� �������
        wxPanel *panel2 = new wxPanel(nb, wxID_PANEL_LIST_REGION); //������� ������ ��� �������� � ���������
        wxBoxSizer *vert_page_region = new wxBoxSizer(wxVERTICAL);    //��������� ����������� ���� ��� �������� ������
        treeRegionBasic = new wxTreeCtrl(panel2, wxID_SOV_TREEVIEW_REGION_BASIC, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_ROW_LINES|wxTR_MULTIPLE); //������� ������ � ��������� �� ������ ������������
        //wxStaticBox *stBox1 = new wxStaticBox(panel2,wxID_ANY,wxCAPTION_STATICBOX_FIND_STRING);  //������� ����������� ����
        //wxStaticBoxSizer *to_static_box1 = new wxStaticBoxSizer(stBox1,wxVERTICAL); //��������� ����.���� �� ����������� �������������
        wxCollapsiblePane *collpane = new wxCollapsiblePane(panel2, wxID_SOV_COLLPANE_F_REG, wxSTRING_FIND, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
        //to_static_box1->Add(new wxSearchCtrl(panel2,wxID_SOV_SEARCHCTRL_F_REG, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT),1,wxEXPAND|wxALL,5); //��������� ��������� ������ �� ����������� ������
        vert_page_region->Add(collpane, 0, wxEXPAND|wxALL,5);
        //vert_page_region->Add(to_static_box1, 0, wxEXPAND); //��������� � �������� ������������ �������� ����������� �����������
        vert_page_region->Add(treeRegionBasic, 1, wxEXPAND); //��������� � �������� ������������ �������� ������ � ���������
        wxWindow *win = collpane->GetPane();
        wxSizer *paneSz = new wxBoxSizer(wxHORIZONTAL);
        paneSz->Add(new wxSearchCtrl(win,wxID_SOV_SEARCHCTRL_F_REG, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT), 1, wxEXPAND|wxALL, 5);
        win->SetSizer(paneSz);
        paneSz->SetSizeHints(win);
        
        wxBoxSizer *vert_page_history = new wxBoxSizer(wxVERTICAL);    //��������� ����������� ���� ��� �������� ������� ��������
        wxPanel *panel3 = new wxPanel(nb, wxID_PANEL_LIST_HIS_OTP); //������� ������ ��� �������� � �������� ��������
        wxCollapsiblePane *collpane2 = new wxCollapsiblePane(panel3, wxID_SOV_COLLPANE_HIS_OTP, wxSTRING_FIND, wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE);
        vert_page_history->Add(collpane2, 0, wxEXPAND|wxALL,5);
        wxWindow *win2 = collpane2->GetPane();
        wxSizer *paneSz2 = new wxBoxSizer(wxHORIZONTAL);
        paneSz2->Add(new wxSearchCtrl(win2,wxID_SOV_SEARCHCTRL_F_HIS, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER|wxTE_LEFT), 1, wxEXPAND|wxALL, 5);
        win2->SetSizer(paneSz2);
        paneSz2->SetSizeHints(win2);
        wxListView *listview2 = new wxListView(panel3, wxID_SOV_LISTVIEW_TEK_HIS); //������� �������� ��� �������� � ���.��������
        vert_page_history->Add(listview2, 1, wxEXPAND|wxALL,5);
        
        //wxListView *listview1 = new wxListView(nb, wxID_SOV_LISTVIEW_TEK_OTP); //������� �������� ��� �������� � ���.���������
        wxTreeListCtrl *treelist = new wxTreeListCtrl(nb, wxID_SOV_LISTVIEW_TEK_OTP, wxDefaultPosition, wxDefaultSize,wxTL_SINGLE);
        for(register int i=0, j=0; i<MyPrivilegeUserArray.GetCount();++i)   //������ ���������� ������� ���� � ����������� �� ���������� ������������
        {
            if(MyPrivilegeUserArray.Item(i).name=="admin_global"&&j==0)
            {
                j=1;
                //wxTreeListCtrl *treelist = new wxTreeListCtrl(nb, wxID_SOV_LISTVIEW_TEK_OTP, wxDefaultPosition, wxDefaultSize,wxTL_SINGLE|wxTL_CHECKBOX);
                treelist->SetWindowStyleFlag(wxTL_SINGLE|wxTL_CHECKBOX);
                treelist->Refresh();
                break;
            }
            /*if(MyPrivilegeUserArray.Item(i).name!="admin_global"&&j==1) 
            {
                //wxTreeListCtrl *treelist = new wxTreeListCtrl(nb, wxID_SOV_LISTVIEW_TEK_OTP, wxDefaultPosition, wxDefaultSize,wxTL_SINGLE);
                treelist->SetWindowStyleFlag(wxTL_SINGLE);
                treelist->Refresh();
                break;
            }*/
        } 
        nb->AddPage(treelist, (wxCAPTION_NOTEBOOK_PAGE_OTP_NOW)); //��������� � �������� �������� � ���.���������
        nb->AddPage(panel3, (wxCAPTION_NOTEBOOK_PAGE_OTP_HIS)); //��������� � �������� �������� � ���.��������
        nb->AddPage(panel1, (wxCAPTION_NOTEBOOK_PAGE_SOV_LIST)); //��������� � �������� ������ �� ������� ����������
        nb->AddPage(panel2, (wxCAPTION_NOTEBOOK_PAGE_REGION)); //��������� � �������� ������ � ������� ��������
	    nb->SetImageList(imageList); //������������� ������ ����������� ��� �������������
	    nb->SetPageImage(0,0); //������������� ����������� ��� ������ ��������
	    nb->SetPageImage(1,1);
	    nb->SetPageImage(2,2);
	    nb->SetPageImage(3,3);
	    OtpuskNow(); //����� ��������� ���� � ����������� ��������
	    OtpuskHistory(); //����� �������� ���� �� ������� ��������
	    ListSovetnik(); //����� ��������� ���� � ����������
	    TreeRegion(); //��������� ����������� ������
        vert_bos->Add(nb, 1, wxEXPAND|wxBOTTOM ,0);
        panel3->SetSizer(vert_page_history);
        panel2->SetSizer(vert_page_region);
        panel1->SetSizer(vert_page_sotr);
        this->SetSizer(vert_bos);	
        this->CreateStatusBar(1,wxSTB_DEFAULT_STYLE,wxID_SOV_STATUSBAR);
        int select_page=0;
        GhangeStatusbar(select_page);
    }
}
void NotebookSovetnik::ListviewChangedItem (wxListEvent& event)
{
    if(event.GetId()==wxID_SOV_LISTVIEW_LIST_SOV)
    {
        wxString strData;
        strData<<event.GetData();
        treeRegion->DeleteAllItems();
        for(register int i =0; i<MySovetnicArray.GetCount();++i) //������ � ���� �� � ��� ��� �������
        {
            //if(!MySovetnicArray.Item(i).idSovetnic.compare(strData))
            if(MySovetnicArray.Item(i).idSovetnic==wxAtoi(strData))  
            {
                wxString strBanner;
                strBanner=wxSTRING_DATE_ROJD; strBanner+=MySovetnicArray.Item(i).drSovetnic; strBanner+="\n";
                strBanner+=wxSTRING_RAB_TEL; strBanner+=MySovetnicArray.Item(i).pfoneSovetnic; strBanner+="\n";
                strBanner+=wxSTRING_DATE_PR; strBanner+=MySovetnicArray.Item(i).dateOpen; strBanner+="\n";
                strBanner+=wxSTRING_DATE_UV; strBanner+=MySovetnicArray.Item(i).dateClose;
                banner->SetText(wxSTRING_PERSONAL_DATA, strBanner);
            }
        }
        wxTreeItemId treeItemLvl1=treeRegion->AddRoot(wxSTRING_REG_ROOT); //��������� �������� ������� �������
        for(register int i =0; i<MySovConnectRegArray.GetCount();++i) //������ ������� ����������� � ���������� ��� �������
        {
            //if(!MySovConnectRegArray.Item(i).idSovetnic.compare(strData))
            if(MySovConnectRegArray.Item(i).idSovetnic==wxAtoi(strData))    
            {
                wxString idReg; idReg<<MySovConnectRegArray.Item(i).idRegion;
                for(register int iMr =0; iMr<MyMacroregArray.GetCount();++iMr) //��������� id �� ���������� � ��
                {
                    //if(!MyMacroregArray.Item(iMr).idMacroreg.compare(idReg)) //����� ��, ��� ���� ����������� ��
                    if(MyMacroregArray.Item(iMr).idMacroreg==wxAtoi(idReg)) //����� ��, ��� ���� ����������� ��
                    {
                        wxString srtMr(wxSTRING_REG_MR), strOc, strGc; //������� ���������� ��� ������������ ������ ������
                        srtMr += MyMacroregArray.Item(iMr).nameMacroreg; //����� � ���������� ��� ��
                        //if(!MySovConnectRegArray.Item(i).activ.compare("0")&&!MyMacroregArray.Item(iMr).activMacroreg.compare("1")) {srtMr +=wxSTRING_REG_ARCH;} //���� ������ ��������, �� ����� ��������� � ������� ��������, �� ���������� � ����� �� ����� �����
                         if(MySovConnectRegArray.Item(i).activ==0&&MyMacroregArray.Item(iMr).activMacroreg==1) {srtMr +=wxSTRING_REG_ARCH;} //���� ������ ��������, �� ����� ��������� � ������� ��������, �� ���������� � ����� �� ����� �����
                        wxTreeItemId treeItemLvl2=treeRegion->AppendItem(treeItemLvl1, srtMr); //��������� �������
                        for(register int lvl1 =0; lvl1<MyTechCentrArray.GetCount();++lvl1)    //���� � ������ ��������� ������ ��/��
                        {
                            //if(!idReg.compare(MyTechCentrArray.Item(lvl1).son)) //�����
                            if(wxAtoi(idReg)==MyTechCentrArray.Item(lvl1).son) //�����
                            { 
                                wxTreeItemId treeItemLvl3; //���������� �������� ������
                                for(register int iOc =0; iOc<MyOcArray.GetCount();++iOc) //���� � ����������� ������������ ��
                                {
                                    //if(!MyTechCentrArray.Item(lvl1).parent.compare(MyOcArray.Item(iOc).idOc)) //�����
                                    if(MyTechCentrArray.Item(lvl1).parent==MyOcArray.Item(iOc).idOc) //�����
                                    {
                                        strOc=MyOcArray.Item(iOc).nameOc; //����� � ���������� ��� ��
                                        //if(!MySovConnectRegArray.Item(i).activ.compare("0")&&!MyOcArray.Item(iOc).activOc.compare("1")) {strOc +=wxSTRING_REG_ARCH;}  //���� ������ ��������, �� ����� ��������� � ������� ��������, �� ���������� � ����� �� ����� �����
                                        if(MySovConnectRegArray.Item(i).activ==0&&MyOcArray.Item(iOc).activOc==1) {strOc +=wxSTRING_REG_ARCH;}  //���� ������ ��������, �� ����� ��������� � ������� ��������, �� ���������� � ����� �� ����� �����
                                        treeItemLvl3=treeRegion->AppendItem(treeItemLvl2, strOc); //��������� �������� � ������
                                        break;
                                    }
                                } 
                                for(register int lvl2 =0; lvl2<MyTechCentrArray.GetCount();++lvl2) //���� � ������ ��������� ������ ��/��
                                {
                                    //if(!MyTechCentrArray.Item(lvl1).parent.compare(MyTechCentrArray.Item(lvl2).son)) //�����
                                    if(MyTechCentrArray.Item(lvl1).parent==MyTechCentrArray.Item(lvl2).son) //�����
                                    {
                                        for(register int iGc =0; iGc<MyGcArray.GetCount();++iGc) //���� � ����������� ������������ ��
                                        {
                                            //if(!MyTechCentrArray.Item(lvl2).parent.compare(MyGcArray.Item(iGc).idGc)) //�����
                                            if(MyTechCentrArray.Item(lvl2).parent==MyGcArray.Item(iGc).idGc) //�����
                                            {
                                                strGc=MyGcArray.Item(iGc).nameGc; //����� � ���������� ��� ��
                                                //if(!MySovConnectRegArray.Item(i).activ.compare("0")&&!MyGcArray.Item(iGc).activGc.compare("1")) {strGc +=wxSTRING_REG_ARCH;} //���� ������ ��������, �� ����� ��������� � ������� ��������, �� ���������� � ����� �� ����� �����
                                                if(MySovConnectRegArray.Item(i).activ==0&&MyGcArray.Item(iGc).activGc==1) {strGc +=wxSTRING_REG_ARCH;} //���� ������ ��������, �� ����� ��������� � ������� ��������, �� ���������� � ����� �� ����� �����
                                                treeRegion->AppendItem(treeItemLvl3, strGc); //��������� ����� �� ��������
                                                break;
                                                
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }   
                }
                for(register int iOc =0; iOc<MyOcArray.GetCount();++iOc) //��������� id �� ���������� � ��
                {
                    //if(!MyOcArray.Item(iOc).idOc.compare(idReg)) //����� ��, ��� ���� ����������� ��
                    if(MyOcArray.Item(iOc).idOc==wxAtoi(idReg)) //����� ��, ��� ���� ����������� ��
                    {
                        wxString strOc(wxSTRING_REG_OC), strGc; 
                        strOc += MyOcArray.Item(iOc).nameOc;
                        //if(!MySovConnectRegArray.Item(i).activ.compare("0")&&!MyOcArray.Item(iOc).activOc.compare("1")) {strOc +=wxSTRING_REG_ARCH;}
                        if(MySovConnectRegArray.Item(i).activ==0&&MyOcArray.Item(iOc).activOc==1) {strOc +=wxSTRING_REG_ARCH;} 
                        wxTreeItemId treeItemLvl2=treeRegion->AppendItem(treeItemLvl1, strOc); //��������� �������               
                        for(register int lvl1 =0; lvl1<MyTechCentrArray.GetCount();++lvl1)    //���� � ������ ��������� ������ ��/��
                        {
                            //if(!idReg.compare(MyTechCentrArray.Item(lvl1).son)) //�����
                            if(wxAtoi(idReg)==MyTechCentrArray.Item(lvl1).son) //�����
                            { 
                                wxTreeItemId treeItemLvl3;
                                for(register int iGc =0; iGc<MyGcArray.GetCount();++iGc) //���� � ����������� ������������ ��
                                {
                                    //if(!MyTechCentrArray.Item(lvl1).parent.compare(MyGcArray.Item(iGc).idGc)) //�����
                                    if(MyTechCentrArray.Item(lvl1).parent==MyGcArray.Item(iGc).idGc) //�����
                                    {
                                        strGc=MyGcArray.Item(iGc).nameGc;
                                        //if(!MySovConnectRegArray.Item(i).activ.compare("0")&&!MyGcArray.Item(iGc).activGc.compare("1")) {strGc +=wxSTRING_REG_ARCH;} 
                                        if(MySovConnectRegArray.Item(i).activ==0&&MyGcArray.Item(iGc).activGc==1) {strGc +=wxSTRING_REG_ARCH;}          
                                        treeItemLvl3=treeRegion->AppendItem(treeItemLvl2, strGc); //��������� �������� � ������
                                        break;
                                    }
                                } 
                            }
                        }
                        break;
                    }   
                }
                for(register int iGc =0; iGc<MyGcArray.GetCount();++iGc) //��������� id �� ���������� � ��
                {
                    //if(!MyGcArray.Item(iGc).idGc.compare(idReg)) //����� ��, ��� ���� ����������� ��
                    if(MyGcArray.Item(iGc).idGc==wxAtoi(idReg)) //����� ��, ��� ���� ����������� ��
                    {
                        wxString strGc(wxSTRING_REG_GC); 
                        strGc += MyGcArray.Item(iGc).nameGc;
                        //if(!MySovConnectRegArray.Item(i).activ.compare("0")&&!MyGcArray.Item(iGc).activGc.compare("1")) {strGc +=wxSTRING_REG_ARCH;} 
                        if(MySovConnectRegArray.Item(i).activ==0&&MyGcArray.Item(iGc).activGc==1) {strGc +=wxSTRING_REG_ARCH;} 
                                               
                        wxTreeItemId treeItemLvl2=treeRegion->AppendItem(treeItemLvl1, strGc); //��������� �������
                        break;
                    }   
                }
            }                 
        }
        treeRegion->Expand(treeItemLvl1); //���������� �������� ������� ������
        wxString strStatic; //������� ���������� ��� ������ ������� ����������
        for(register int i =0; i<MyPositionSotrHistoryArray.GetCount();++i) //������ � ���� ������� ����������
        {
            //if(!MyPositionSotrHistoryArray.Item(i).idSotr.compare(strData)) 
            if(MyPositionSotrHistoryArray.Item(i).idSotr==wxAtoi(strData)) 
            {
                wxString strDolz, strDate; //������� ��������� ���������� ��� ������������ ��������� � ���� ��������� ���������
                for(register int j =0; j<MyPositionSotrArray.GetCount();++j) //���������� �� ����������� ������������ ���������
                {
                    //if(!MyPositionSotrHistoryArray.Item(i).idPosition.compare(MyPositionSotrArray.Item(j).idPosition))
                    if(MyPositionSotrHistoryArray.Item(i).idPosition==MyPositionSotrArray.Item(j).idPosition)
                    {
                        strStatic+=wxSTR_NEW; //��������� �� ������� ���������� ������ ����� ������.
                        strDolz=MyPositionSotrArray.Item(j).namePosition; break; //����� � ���������� ������������ ���������
                    }
                }
                strStatic+=strDolz; //����� �� ������� ���������� ������������ ���������
                //if(!MyPositionSotrHistoryArray.Item(i).activ.compare("1")) {strStatic+=" �� "; strStatic+=wxSTRING_NOW_TIME;} //���� ����� ��������, �� ���������� �� ����.������������ �/�
                //if(!MyPositionSotrHistoryArray.Item(i).activ.compare("0")) {strStatic+=" � "; strStatic+=MyPositionSotrHistoryArray.Item(i).dateOn; strStatic+=" �� "; strStatic+=MyPositionSotrHistoryArray.Item(i).dateOff;} //���� ����� �������� �� ���������� ����
                if(MyPositionSotrHistoryArray.Item(i).activ==1) {strStatic+=" �� "; strStatic+=wxSTRING_NOW_TIME;} //���� ����� ��������, �� ���������� �� ����.������������ �/�
                if(MyPositionSotrHistoryArray.Item(i).activ==0) {strStatic+=" � "; strStatic+=MyPositionSotrHistoryArray.Item(i).dateOn; strStatic+=" �� "; strStatic+=MyPositionSotrHistoryArray.Item(i).dateOff;} //���� ����� �������� �� ���������� ����
            }
        }
        if(strStatic.IsEmpty()) {staticDolz->SetLabel(wxNOT_DATA);} else {staticDolz->SetLabel(strStatic); } //����� � ����� ���������� �������� ����������
    }
}
void NotebookSovetnik::OnEnter (wxCommandEvent& event)
{
    switch (event.GetId())
    {
        case wxID_SOV_SEARCHCTRL_F_REG:
        {
            //treeRegionBasic->CollapseAll(); //����������� �������� �������
            treeRegionBasic->UnselectAll(); //������� ���������
            wxString textPoisk = ((wxSearchCtrl*)(nb->FindWindow(wxID_PANEL_LIST_REGION))->FindWindow(wxID_SOV_SEARCHCTRL_F_REG))->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
            textPoisk.MakeUpper(); //�������� ��� ������� � �������� ��������
    
            wxTreeItemId treeitem = treeRegionBasic->GetRootItem();
            treeRegionBasic->SelectItem(treeitem, false); //������� ���������
            wxTreeItemIdValue param;
            for(register wxTreeItemId iMr = treeRegionBasic->GetFirstChild(treeitem, param);iMr.IsOk();iMr=treeRegionBasic->GetNextSibling(iMr))
            {
                if(((treeRegionBasic->GetItemText(iMr)).Find(textPoisk))!=wxNOT_FOUND) 
                {
                    if(!treeRegionBasic->IsVisible(iMr)) {treeRegionBasic->Expand(treeitem);} //���� �� �� �����, �� ���������� �������� �������
                    treeRegionBasic->SelectItem(iMr,true);
                } //���� ���� ����������, �� �������� �������
                else {treeRegionBasic->Collapse(iMr);}
                for(register wxTreeItemId iOr = treeRegionBasic->GetFirstChild(iMr, param);iOr.IsOk();iOr=treeRegionBasic->GetNextSibling(iOr))
                {
                    if(((treeRegionBasic->GetItemText(iOr)).Find(textPoisk))!=wxNOT_FOUND) 
                    {
                        if(!treeRegionBasic->IsVisible(iOr)) {treeRegionBasic->Expand(iMr);} //���� �� �� �����, �� ���������� ��
                        treeRegionBasic->SelectItem(iOr,true);
                    } //���� ���� ����������, �� �������� �������
                    else {treeRegionBasic->Collapse(iOr);}
                    for(register wxTreeItemId iGr = treeRegionBasic->GetFirstChild(iOr, param);iGr.IsOk();iGr=treeRegionBasic->GetNextChild(iGr, param))
                    {
                        if(((treeRegionBasic->GetItemText(iGr)).Find(textPoisk))!=wxNOT_FOUND) 
                        {
                            if(!treeRegionBasic->IsVisible(iOr)) {treeRegionBasic->Expand(iMr);} //���� �� �� �����, �� ���������� ��
                            if(!treeRegionBasic->IsVisible(iGr)) {treeRegionBasic->Expand(iOr);} //���� �� �� �����, �� ���������� ��
                            treeRegionBasic->SelectItem(iGr,true);
                        } //���� ���� ����������, �� �������� �������
                    }
                }
            }
            treeRegionBasic->SetFocus();
            break;
        }
        case wxID_SOV_SEARCHCTRL_F_SOV:
        {
            wxListView *listview = (wxListView*)(nb->FindWindow(wxID_PANEL_LIST_SOV))->FindWindow(wxID_SOV_LISTVIEW_LIST_SOV);
            wxString textPoisk = ((wxSearchCtrl*)(nb->FindWindow(wxID_PANEL_LIST_SOV))->FindWindow(wxID_SOV_SEARCHCTRL_F_SOV))->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
            textPoisk.MakeUpper(); //�������� ��� ������� � �������� ��������
            for(register int i=0;i<listview->GetItemCount();++i) 
            {
                if(((listview->GetItemText(i)).MakeUpper()).Find(textPoisk)!=wxNOT_FOUND)
                {
                    listview->Select(i,true); //�������� ������
                    listview->Focus(i);
                }
                else
                {
                    listview->Select(i,false); //������� ���������� ������
                }
            }
            listview->SetFocus();
            break;
        }
        case wxID_SOV_SEARCHCTRL_F_HIS:
        {
            wxListView *listview = (wxListView*)(nb->FindWindow(wxID_PANEL_LIST_HIS_OTP))->FindWindow(wxID_SOV_LISTVIEW_TEK_HIS);
            wxString textPoisk = ((wxSearchCtrl*)(nb->FindWindow(wxID_PANEL_LIST_HIS_OTP))->FindWindow(wxID_SOV_SEARCHCTRL_F_HIS))->GetValue();
            textPoisk.Trim(true); textPoisk.Trim(false); //������� � ������ ������ ������� ������ � �����
            textPoisk.MakeUpper(); //�������� ��� ������� � �������� ��������
            for(register int i=0;i<listview->GetItemCount();++i) 
            {
                if(((listview->GetItemText(i)).MakeUpper()).Find(textPoisk)!=wxNOT_FOUND)
                {
                    listview->Select(i,true); //�������� ������
                    listview->Focus(i);
                }
                else
                {
                    listview->Select(i,false); //������� ���������� ������
                }
            }
            listview->SetFocus();
            break;
        }    
    }
}

void NotebookSovetnik::CollapChanged (wxCollapsiblePaneEvent& event)
{
    switch (event.GetId())
    {
        case wxID_SOV_COLLPANE_F_REG:
        {
            (nb->FindWindow(wxID_PANEL_LIST_REGION))->Layout(); //������ �����������, ����������� � ������ �� �������� �� ���������� ��������, ����������� ����
            break;
        }
        case wxID_SOV_COLLPANE_SOV_SPIS:
        {
            (nb->FindWindow(wxID_PANEL_LIST_SOV))->Layout(); //������ �����������, ����������� � ������ �� �������� �� ���������� ��������, ����������� ����
            break;
        }
        case wxID_SOV_COLLPANE_HIS_OTP:
        {
            (nb->FindWindow(wxID_PANEL_LIST_HIS_OTP))->Layout(); //������ �����������, ����������� � ������ �� �������� �� ���������� ��������, ����������� ����
            break;
        }
        default: {break;}
    }
    
    event.Skip();
}
void NotebookSovetnik::TreeRegion (void)
{
     treeRegionBasic->DeleteAllItems();
     wxTreeItemId treeItemLvl1=treeRegionBasic->AddRoot(wxSTRING_STRUCT_TREE); //��������� �������� �������
     for(register int iMr =0; iMr<MyMacroregArray.GetCount();++iMr) //�������� id  ��
     {
            //if(!MyMacroregArray.Item(iMr).activMacroreg.compare("1"))
            if(MyMacroregArray.Item(iMr).activMacroreg==1)
            { 
                wxString idMr; idMr<<MyMacroregArray.Item(iMr).idMacroreg;
                wxString srtMr, strOc, strGc; //������� ���������� ��� ������������ ������ ������
                srtMr += MyMacroregArray.Item(iMr).nameMacroreg; //����� � ���������� ��� ��
                wxTreeItemId treeItemLvl2=treeRegionBasic->AppendItem(treeItemLvl1, srtMr); //��������� �������
                for(register int lvl1 =0; lvl1<MyTechCentrArray.GetCount();++lvl1)    //���� � ������ ��������� ������ ��/��
                {
                    //if(!idMr.compare(MyTechCentrArray.Item(lvl1).son)) //�����
                    if(wxAtoi(idMr)==MyTechCentrArray.Item(lvl1).son) //�����
                    { 
                        wxTreeItemId treeItemLvl3; //���������� �������� ������
                        int flag_oc_archiv=0;
                        for(register int iOc =0; iOc<MyOcArray.GetCount();++iOc) //���� � ����������� ������������ ��
                        {
                            //if(!MyTechCentrArray.Item(lvl1).parent.compare(MyOcArray.Item(iOc).idOc)) //�����
                            if(MyTechCentrArray.Item(lvl1).parent==MyOcArray.Item(iOc).idOc) //�����
                            {
                                strOc=MyOcArray.Item(iOc).nameOc; //����� � ���������� ��� ��
                                //if(!MyOcArray.Item(iOc).activOc.compare("1"))
                                if(MyOcArray.Item(iOc).activOc==1)  
                                { 
                                    treeItemLvl3=treeRegionBasic->AppendItem(treeItemLvl2, strOc); //��������� �������� � ������
                                } else {flag_oc_archiv=1;}
                            }
                        }
                        if(flag_oc_archiv==1) {continue;} //�� ������ ������ ����� ���� �� ��������
                        for(register int lvl2 =0; lvl2<MyTechCentrArray.GetCount();++lvl2) //���� � ������ ��������� ������ ��/��
                        {
                            //if(!MyTechCentrArray.Item(lvl1).parent.compare(MyTechCentrArray.Item(lvl2).son)) //�����
                            if(MyTechCentrArray.Item(lvl1).parent==MyTechCentrArray.Item(lvl2).son) //�����
                            {
                                for(register int iGc =0; iGc<MyGcArray.GetCount();++iGc) //���� � ����������� ������������ ��
                                {
                                    //if(!MyTechCentrArray.Item(lvl2).parent.compare(MyGcArray.Item(iGc).idGc)) //�����
                                    if(MyTechCentrArray.Item(lvl2).parent==MyGcArray.Item(iGc).idGc) //�����
                                    {
                                        strGc=MyGcArray.Item(iGc).nameGc; //����� � ���������� ��� ��
                                        //if(!MyGcArray.Item(iGc).activGc.compare("1")) 
                                        if(MyGcArray.Item(iGc).activGc==1) 
                                        {
                                            treeRegionBasic->AppendItem(treeItemLvl3, strGc); //��������� ����� �� ��������
                                        } else {;}
                                                
                                    }
                                }
                            }
                        }
                    }
                }
            }   
                     
    }
    treeRegionBasic->Expand(treeItemLvl1); //���������� �������� ������� ������
}
void NotebookSovetnik::ListSovetnik (void)
{
    wxListView *listview = ((wxListView*)this->FindWindow(wxID_SOV_LISTVIEW_LIST_SOV));
    listview->DeleteAllItems();
    listview->InsertColumn(0,wxCAPTION_COLUMN_FIO);
    listview->InsertColumn(1,wxCAPTION_COLUMN_JOB);
    listview->InsertColumn(2,wxCAPTION_COLUMN_STATUS);
    wxString sqlText; sqlText<<wxSqlTextSelListSovetnik;
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
                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                f->SetColumn(0);
                f->SetData(atoi(row[3])); //������ ���������� ����
                f->SetId(i);
                listview->InsertItem(*f); 
                for (register int l = 0; l < (num_fields-1); l++)
                {
                    if(l==0) {wxString str=row[l]; EditStringFioFull(str); listview->SetItem(i,l,str);} else {listview->SetItem(i,l,row[l]);}
                }
                delete f;
            }
            for(register int i=0; i<listview->GetColumnCount();++i)
            {
                listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� �������� (����� ������� � ������������)
            }
        }
        mysql_free_result(res); // ������� ����������
    }
}
void NotebookSovetnik::OtpuskNow (void)
{
    /*wxListView *listview = ((wxListView*)this->FindWindow(wxID_SOV_LISTVIEW_TEK_OTP));
    listview->DeleteAllItems();
    listview->InsertColumn(0,wxCAPTION_COLUMN_REGION);
    listview->InsertColumn(1,wxCAPTION_COLUMN_FIO);
    listview->InsertColumn(2,wxCAPTION_COLUMN_STATUS);
    listview->InsertColumn(3,wxCAPTION_COLUMN_EVENT);
    listview->InsertColumn(4,wxCAPTION_COLUMN_C);
    listview->InsertColumn(5,wxCAPTION_COLUMN_PO);
    listview->InsertColumn(6,wxCAPTION_COLUMN_ZAMKAND);
    listview->InsertColumn(7,wxCAPTION_COLUMN_ZAMTO);*/
    wxTreeListCtrl *treelist = ((wxTreeListCtrl*)this->FindWindow(wxID_SOV_LISTVIEW_TEK_OTP));
    treelist->DeleteAllItems();
    treelist->AppendColumn(wxCAPTION_COLUMN_REGION);
    treelist->AppendColumn(wxCAPTION_COLUMN_FIO);
    treelist->AppendColumn(wxCAPTION_COLUMN_STATUS);
    treelist->AppendColumn(wxCAPTION_COLUMN_EVENT);
    treelist->AppendColumn(wxCAPTION_COLUMN_C);
    treelist->AppendColumn(wxCAPTION_COLUMN_PO);
    treelist->AppendColumn(wxCAPTION_COLUMN_ZAMKAND);
    treelist->AppendColumn(wxCAPTION_COLUMN_ZAMTO);
    treelist->AppendColumn(wxCAPTION_COLUMN_ID, wxCOL_WIDTH_AUTOSIZE,wxALIGN_LEFT,wxCOL_HIDDEN);
    wxString sqlText; sqlText<<wxSqlTextSelNowOtpusk;
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
                /*wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT);
                f->SetColumn(0);
                f->SetId(i);
                listview->InsertItem(*f);*/ 
                wxTreeListItem tritem;
                for (register int l = 0; l < num_fields; l++)
                {
                    switch (l)
                    {
                        case 0:
                            {
                                tritem = treelist->AppendItem(treelist->GetRootItem(),row[0]);
                                break;
                            }
                        case 1:
                            {
                                wxString str=row[l];
                                EditStringFioFull(str);
                                //listview->SetItem(i,l,str);
                                treelist->SetItemText(tritem,l,str);
                                break;
                            }
                        case 6:
                        case 7:
                            {
                                wxString str=row[l];
                                EditStringFio(str);
                                //listview->SetItem(i,l,str);
                                treelist->SetItemText(tritem,l,str);
                                break;
                            }
                        case 9:
                            {
                                if(wxAtoi(row[l])==0) {treelist->CheckItem(tritem,wxCHK_UNCHECKED); break;}
                                if(wxAtoi(row[l])==1) {treelist->CheckItem(tritem,wxCHK_CHECKED); break;}
                                break;
                            }
                        default:
                            {
                                //listview->SetItem(i,l,row[l]);
                                treelist->SetItemText(tritem,l,row[l]);
                                break;
                            }
                    }
                }
                //delete f;
            }
            for(register int i=0; i<treelist->GetColumnCount();++i)
            {
                //listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� �������� (����� ������� � ������������)
                treelist->SetColumnWidth(i,wxCOL_WIDTH_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� ��������
            }
        }
        mysql_free_result(res); // ������� ����������
    }
}
void NotebookSovetnik::TreeListChanged(wxTreeListEvent& event)
{
    wxTreeListCtrl *treelist = ((wxTreeListCtrl*)this->FindWindow(wxID_SOV_LISTVIEW_TEK_OTP));
    if((treelist->GetCheckedState(event.GetItem()))==wxCHK_CHECKED)
    {
        wxString sqlText; sqlText<<wxSqlTextUpdZamOtpusk2; sqlText<<(treelist->GetItemText(event.GetItem(),8)); sqlText<<wxSqlEndText;
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
        else {;}
    }
    if((treelist->GetCheckedState(event.GetItem()))==wxCHK_UNCHECKED)
    {
        wxString sqlText; sqlText<<wxSqlTextUpdZamOtpusk1; sqlText<<(treelist->GetItemText(event.GetItem(),8)); sqlText<<wxSqlEndText;
        if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
        else {;}
    }
}

void NotebookSovetnik::OtpuskHistory (void)
{
    wxListView *listview = ((wxListView*)this->FindWindow(wxID_SOV_LISTVIEW_TEK_HIS));
    listview->DeleteAllItems();
    listview->InsertColumn(0,wxCAPTION_COLUMN_FIO);
    listview->InsertColumn(1,wxCAPTION_COLUMN_C);
    listview->InsertColumn(2,wxCAPTION_COLUMN_PO);
    listview->InsertColumn(3,wxCAPTION_COLUMN_EVENT);
    listview->InsertColumn(4,wxCAPTION_COLUMN_ZAMKAND);
    listview->InsertColumn(5,wxCAPTION_COLUMN_ZAMTO);
    wxString sqlText; sqlText<<wxSqlTextSelHistoryOtpusk;
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
                f->SetId(i);
                listview->InsertItem(*f); 
                for (register int l = 0; l < num_fields; l++)
                {
                    switch (l)
                    {
                        case 0:
                            {
                                wxString str=row[l];
                                EditStringFioFull(str);
                                listview->SetItem(i,l,str);
                                break;
                            }
                        case 4:
                        case 5:
                            {
                                wxString str=row[l];
                                EditStringFio(str);
                                listview->SetItem(i,l,str);
                                break;
                            }
                        default:
                            {
                                listview->SetItem(i,l,row[l]);
                                break;
                            }
                    }
                }
                delete f;
            }
            for(register int i=0; i<listview->GetColumnCount();++i)
            {
                listview->SetColumnWidth(i,wxLIST_AUTOSIZE); //�������� ������ ������� �� ����� ������ �������� �������� (����� ������� � ������������)
            }
        }
        mysql_free_result(res); // ������� ����������
    }
}


void NotebookSovetnik::GhangeStatusbar (int& page)
{
    wxStatusBar *statusBar = this->GetStatusBar();
    switch (page)
    {
        case 0:
        {
            //wxListView *listview = ((wxListView*)this->FindWindow(wxID_SOV_LISTVIEW_TEK_OTP));
            wxTreeListCtrl *treeview = ((wxTreeListCtrl*)this->FindWindow(wxID_SOV_LISTVIEW_TEK_OTP));
            int count_sov_not_work=0;
            int count_sov_all=0;
            wxString textStatusBar(wxCOUNT_SOVETNIK);
            for(register int i =0; i<MySovetnicArray.GetCount();++i)    
            {
                //if(MySovetnicArray.Item(i).idSovetnic.compare("49")&&!MySovetnicArray.Item(i).activSovetnic.compare("1")) {++count_sov_all;}
                if(MySovetnicArray.Item(i).idSovetnic!=49&&MySovetnicArray.Item(i).activSovetnic==1) {++count_sov_all;}
            }
            textStatusBar<<count_sov_all;
            textStatusBar+=wxCOUNT_SOV_CONCAT_OTP;
            /*for(register int i=0; i<(listview->GetItemCount());++i)
            {
                if(!(listview->GetItemText(i,2)).compare(wxSTRING_NO_WORK)) {++count_sov_not_work;}
            }*/
            for(register wxTreeListItem i=treeview->GetFirstItem(); i.IsOk(); i=treeview->GetNextItem(i))
            {
                if(!(treeview->GetItemText(i,2)).compare(wxSTRING_NO_WORK)) {++count_sov_not_work;}
            }
            textStatusBar<<count_sov_not_work;
            statusBar->SetStatusText(textStatusBar);
            break;
        }
        case 1:
        {
            wxListView *listview = ((wxListView*)this->FindWindow(wxID_SOV_LISTVIEW_TEK_HIS));
            int count_string=0;
            wxString textStatusBar(wxCOUNT_STRING_ARCHIV);
            count_string=listview->GetItemCount();
            textStatusBar<<count_string;
            statusBar->SetStatusText(textStatusBar);
            break;
        }
        case 2:
        {
            wxListView *listview = ((wxListView*)this->FindWindow(wxID_SOV_LISTVIEW_LIST_SOV));
            int count_string=0;
            int count_really=0;
            int count_fired=0;
            wxString textStatusBar(wxCOUNT_SOVETNIK);
            count_string=listview->GetItemCount();
            textStatusBar<<count_string;
            
            for(register int i=0; i<(listview->GetItemCount());++i)
            {
                if(!(listview->GetItemText(i,2)).compare(wxSTRING_SOTR_REALLY)) {++count_really;}
                if(!(listview->GetItemText(i,2)).compare(wxSTRING_SOTR_FIRED)) {++count_fired;}
            }
            textStatusBar<<wxCOUNT_SOV_CONCAT_TEK; textStatusBar<<count_really;
            textStatusBar<<wxCOUNT_SOV_CONCAT_DEL; textStatusBar<<count_fired;
            statusBar->SetStatusText(textStatusBar);
            break;
        }
        case 3:
        {
            int cCount=0, cMr=0, cOc=0, cGc=0;
            wxString textStatusBar(wxCOUNT_STRING_TREE_REG);
            cCount=treeRegionBasic->GetCount();
            wxTreeItemId treeitem = treeRegionBasic->GetRootItem();
            wxTreeItemIdValue param;
            for(register wxTreeItemId iMr = treeRegionBasic->GetFirstChild(treeitem, param);iMr.IsOk();iMr=treeRegionBasic->GetNextSibling(iMr))
            {
                ++cMr;
                for(register wxTreeItemId iOr = treeRegionBasic->GetFirstChild(iMr, param);iOr.IsOk();iOr=treeRegionBasic->GetNextSibling(iOr))
                {
                    ++cOc;
                    for(register wxTreeItemId iGr = treeRegionBasic->GetFirstChild(iOr, param);iGr.IsOk();iGr=treeRegionBasic->GetNextChild(iGr, param))
                    {
                        ++cGc;
                    }
                }
            }
            textStatusBar<<cCount; textStatusBar<<wxCOUNT_STRING_IS;
            textStatusBar<<wxSTRING_REG_MR; textStatusBar<<"- "; textStatusBar<<cMr; textStatusBar<<wxCOUNT_STRING_COMMA;
            textStatusBar<<wxSTRING_REG_OC; textStatusBar<<"- "; textStatusBar<<cOc; textStatusBar<<wxCOUNT_STRING_COMMA;
            textStatusBar<<wxSTRING_REG_GC; textStatusBar<<"- "; textStatusBar<<cGc;
            statusBar->SetStatusText(textStatusBar);
            break;
        }
        default:
        {
            for(register int i=0;i<(statusBar->GetFieldsCount());++i)
            {
                if(i==0) {statusBar->SetStatusText(wxREADDY_);} else {statusBar->SetStatusText(wxNULL_STRING,i);}
            }
            break;
        }
    }
}
void NotebookSovetnik::OnSize(wxSizeEvent& event) //����� ������� ���� �� ����� ������� ��������� ������ ��� ������ �������
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_SOVETNIC/x"), rect.GetX() );
    config->Write( wxT("/FORM_SOVETNIC/y"), rect.GetY() );
    config->Write( wxT("/FORM_SOVETNIC/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_SOVETNIC/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void NotebookSovetnik::OnMove(wxMoveEvent& event) //����� ������� ���� �� ����� ������� ������������ ����
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_SOVETNIC/x"), rect.GetX() );
    config->Write( wxT("/FORM_SOVETNIC/y"), rect.GetY() );
    config->Write( wxT("/FORM_SOVETNIC/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_SOVETNIC/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void NotebookSovetnik::GhangePageNotebook(wxBookCtrlEvent& event)
{
    wxNotebook *nb = ((wxNotebook*)this->FindWindow(wxID_SOV_NOTEBOOK));
    int select_page = nb->GetSelection();
    GhangeStatusbar(select_page);
}
NotebookSovetnik::~NotebookSovetnik()
{
}
