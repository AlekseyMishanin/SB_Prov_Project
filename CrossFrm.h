///-----------------------------------------------------------------
///
/// @file      CrossFrm.h
/// @author    mishaninaa
/// Created:   07.07.2016 15:46:35
/// @section   DESCRIPTION
///            CrossFrm class declaration
///
///------------------------------------------------------------------

#ifndef __CROSSFRM_H__
#define __CROSSFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
////Header Include End

////Dialog Style Start
#undef CrossFrm_STYLE
#define CrossFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
#undef ProvToFrm_STYLE
#define ProvToFrm_STYLE wxTAB_TRAVERSAL //wxDEFAULT_FRAME_STYLE
#undef ProvAgFrm_STYLE
#define ProvAgFrm_STYLE wxTAB_TRAVERSAL //wxDEFAULT_FRAME_STYLE
#undef HolidayFrm_STYLE
#define HolidayFrm_STYLE wxDEFAULT_FRAME_STYLE
#undef NotebookOtchet_STYLE
#define NotebookOtchet_STYLE wxDEFAULT_FRAME_STYLE
#undef NotebookSovetnik_STYLE
#define NotebookSovetnik_STYLE wxDEFAULT_FRAME_STYLE
#undef NotebookAdmin_STYLE
#define NotebookAdmin_STYLE wxDEFAULT_FRAME_STYLE
#undef ContactFrm_STYLE
#define ContactFrm_STYLE wxDEFAULT_FRAME_STYLE

////Dialog Style End
#include <wx/custombgwin.h> //��� wxCustomBackgroundWindow

#include <mysql.h>

#include "id.h"
#include "word.h"
#include <wx/dir.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h> //��� wxToggleButton
#include <wx/srchctrl.h> //��� wxSearchCtrl
#include <wx/utils.h> //������� � ���� �������, ������������ ��� ��������� ���������� � ������� ���������� �/��� �������������
#include <wx/aboutdlg.h> // wxAboutDialogInfo
#include <wx/arrimpl.cpp> // wxObjArray. ���������� ���������� �������, ���������� ���������� ����� ������ � ���.������� WX_DEFINE_OBJARRAY
#include <wx/fileconf.h> //wxFileConfig
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/busyinfo.h>        //wxBusyInfo
#include <wx/utils.h>           //wxSleep (INT)
#include <wx/datectrl.h>        //wxDatePickerCtrl 
#include <wx/checkbox.h>        //wxCheckBox
#include <wx/bannerwindow.h>    //wxBannerWindow
#include <wx/textdlg.h>         //����������� �������
#include <wx/clipbrd.h>         //wxClipboard
#include <wx/notebook.h>        //wxNotebook
#include <wx/treelist.h>        //wxTreeListCtrl
#include <wx/treectrl.h>        //wxTreeCtrl
#include <wx/collpane.h>        //wxCollapsiblePan
//#include <wx/richtooltip.h>     //wxRichToolTip
#include <wx/infobar.h>         //wxInfoBar
#include <wx/propgrid/propgrid.h>  //wxPropertyGrid
#include <wx/propgrid/advprops.h>


//#include <wx/rearrangectrl.h>

#include <wx/aui/aui.h>    //wxAui
#include <wx/timer.h>               //wxTimer Class Reference
#include <wx/notifmsg.h> //wxNotificationMessage Reference Class
#include <wx/strconv.h> //wxCSConv Reference Class


extern MYSQL* conn;
extern int flag_conn_mysql;
extern int sec_for_sleep_window_info;

WX_DECLARE_HASH_MAP(wxString, int, wxStringHash, wxStringEqual, hash_map);

WX_DECLARE_OBJARRAY(Macroreg, MacroregArray); //��������� � �������� ��������� ����� MacroregArray
WX_DECLARE_OBJARRAY(Oc, OcArray); //��������� � �������� ��������� ����� OcArray
WX_DECLARE_OBJARRAY(Gc, GcArray); //��������� � �������� ��������� ����� OcArray
WX_DECLARE_OBJARRAY(HolidayType, HolidayTypeArray); //��������� � �������� ��������� ����� HolidayTypeArray
WX_DECLARE_OBJARRAY(BrandName, BrandNameArray); //��������� � �������� ��������� ����� BrandNameArray
WX_DECLARE_OBJARRAY(BrandType, BrandTypeArray); //��������� � �������� ��������� ����� BrandTypeArray
WX_DECLARE_OBJARRAY(UkRf, UkRfArray); //��������� � �������� ��������� ����� UkRfArray
WX_DECLARE_OBJARRAY(FioSb, FioSbArray); //��������� � �������� ��������� ����� FioSbArray
WX_DECLARE_OBJARRAY(RezProv, RezProvArray); //��������� � �������� ��������� ����� RezProvArray
WX_DECLARE_OBJARRAY(ProdGroup, ProdGroupArray); //��������� � �������� ��������� ����� ProdGroupArray
WX_DECLARE_OBJARRAY(ProdName, ProdNameArray); //��������� � �������� ��������� ����� ProdNameArray
WX_DECLARE_OBJARRAY(Dolznost, DolznostArray); //��������� � �������� ��������� ����� DolznostArray
WX_DECLARE_OBJARRAY(Sovetnic, SovetnicArray); //��������� � �������� ��������� ����� SovetnicArray
WX_DECLARE_OBJARRAY(TechCentr, TechCentrArray); //��������� � �������� ��������� ����� TechCentrArray
WX_DECLARE_OBJARRAY(SovConnectReg, SovConnectRegArray); //��������� � �������� ��������� ����� SovConnectRegArray
WX_DECLARE_OBJARRAY(TypeProv, TypeProvArray); //��������� � �������� ��������� ����� TypeProvArray
WX_DECLARE_OBJARRAY(RootInfo, RootInfoArray); //��������� � �������� ��������� ����� RootInfoArray
WX_DECLARE_OBJARRAY(PositionSotrHistory, PositionSotrHistoryArray); //��������� � �������� ��������� ����� PositionSotrHistoryArray
WX_DECLARE_OBJARRAY(PositionSotr, PositionSotrArray); //��������� � �������� ��������� ����� PositionSotrArray
WX_DECLARE_OBJARRAY(TypeCooperation, TypeCooperationArray); //��������� � �������� ��������� ����� TypeCooperationArray
WX_DECLARE_OBJARRAY(InitiatorChecks, InitiatorChecksArray); //��������� � �������� ��������� ����� InitiatorChecksArray
WX_DECLARE_OBJARRAY(PrivilegeUser, PrivilegeUserArray); //��������� � �������� ��������� ����� PrivilegeUserArray
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
extern PositionSotrArray MyPositionSotrArray; //������ ������������ ���������� ����������� ��
extern TypeCooperationArray MyTypeCooperationArray; //������ ����� ��������������
extern InitiatorChecksArray MyInitiatorChecksArray; //������ ����������� �������� �����������
extern PrivilegeUserArray MyPrivilegeUserArray; //������ ����������� �������� �����������

extern void CreateSpravochnic();    //������� �������� ������������
extern void DeleteSpravochnic ();   //������� ������� �������� ��� �����������
extern void InformationSleep (wxString str, int sec, wxWindow * parent); //������� ������� ��������������� ��������� str, ������� ����� ����� ������������� sec ������
extern void EditStringFio (wxString& str); //������� ����������� ������ wxString ����� ������ ���� �������� �� ������ �.�.
extern void CreatePrivelege();

class MyPanel : public wxCustomBackgroundWindow<wxPanel>
{
    public:
    
    MyPanel(wxWindow* parent, wxBitmap &bitmap)
    {
        Create(parent, wxID_ANY);
        SetBackgroundBitmap(bitmap);
    }
    
};
/*
class MyListView : public wxCustomBackgroundWindow<wxListView> 
{
    public:
    
    MyListView(wxWindow* parent, wxBitmap &bitmap, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_REPORT) 
    {
        Create(parent, id, pos, size, style);
        SetBackgroundBitmap(bitmap);
    }
    
};*/
class CrossFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
	//	CrossFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Cross"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = CrossFrm_STYLE);

        virtual ~CrossFrm();   	
    	CrossFrm(const wxString& title);
        
        wxMenuBar *menubar;
	    wxMenu *file_menu;
	    wxMenu *command_menu;
	    wxMenu *sub_prov_menu;
	    wxMenu *sub_prov_menu_instument;
	    wxMenu *sub_prov_menu_otchet;
	    wxMenu *help_menu;
        MyPanel *mypanel;
        wxString fastComment;   //���������� ��� �������� �����������
        int flag_bl_sb;         //���� �������������� �������� �� �� ��
    	wxTimer m_timer;
        int flag_timer_fast;    //���� ����, ��� ����� ������� ����� ������������� ����	0 - ��-���������, 1 - ����� ����� ����������� ����� ������������� � ��, �� ������������ ��� �� ������� �����������, 2 - ������������ ������� �����������, �� ����� ����������� �� ������ ����������
	private:
		enum
		{
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
        void OnTimer(wxTimerEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnQuit(wxCommandEvent& event);
		void OnWorkingMenu(wxCommandEvent& event);
		void OnButton(wxCommandEvent& event);
};
class ProvToFrm : public wxPanel//public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		ProvToFrm(wxWindow *parent, wxWindowID id = wxID_WINDOW_TO, /*const wxString &title = wxCAPTION_TO,*/ const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = ProvToFrm_STYLE);

        virtual ~ProvToFrm();   	
    	ProvToFrm(const wxString& title);       
        
      
        
        //wxPanel *panel_to;
        wxStaticBoxSizer *to_static_box1,   //�������� ��
        *to_static_box1_1,                  //������� ��
        *to_static_box2,                    //��������� ��
        *to_static_box3,                    //������ ������ ������
        *to_static_box4,                    //������ ������ ������
        *to_static_box5,                    //������ ������ ������
        *to_static_box6,                    //4-� ������ ������
        *to_static_box_cooperation;          //��� ��������������
        wxBoxSizer *to_1,   //���
        *to_2,              //������������ ��
        *to_3,              //�����
        *to_4,              //���-�� ��
        *to_5,              //�����-����������
        *to_6,              //�������� �������
        *to_7,              //��������-����
        *hr1,               //������ ������: �������� ��, ��������� ��
        *vr3,               //������ ������: �������� ��, ��������� ��
        *vr4,               //������ ������: �������� ��, ��������� ��
        *vr5,               //������ ������: �������� ��, ��������� ��
        *vr6,
        *vert;              //������������ ������ ��� ������
        wxStaticBox *stBox1, *stBox1_1, *stBox2, *stBox3, *stBox4, *stBox5, *stBox6, *stBoxCooperation;
        int id_to;              //���������� ���� ��
        int count_assorti, count_to_prov, count_sotr_prov;
        wxChoice *type_cooperation; //��.���������� � �������� ����� ��������������    
        void ListUpdate (void);
    
	private:
		enum {ID_DUMMY_VALUE_}; //don't remove this value unless you have other enum values};
		void ChangeChoice (wxCommandEvent& event);
		void OnChar(wxKeyEvent& event);
		void OnComboBox (wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnButton (wxCommandEvent& event);
        void OnMenu(wxCommandEvent& event);
        void KillFocuss (wxFocusEvent& event);
        void OnTextCtrl (wxCommandEvent& event);
        //void OnSize (wxSizeEvent& event);
        void OnMouse (wxMouseEvent& event);
        //void OnMove (wxMoveEvent& event);
        void ClearForm (int flag=0);
        void ListViewAssortiment(void);
        void ListViewProvTo (void);
        void ListViewKontract (void);
        void ListViewProvSotr (void);
        void DeleteAssorti (void);
        void InsertAssorti (void);
        void ProvInnTo (void);
        void DeleteCardTo (void);
        void CommentProvTo (void);
        void DeleteProvTo (void);
        void CommentProvSotrTo (void);
        void DeleteProvSotrTo (void);
};
class ProvAgFrm : public wxPanel //public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		ProvAgFrm(wxWindow *parent, wxWindowID id = wxID_WINDOW_AGENT, /*const wxString &title = wxCAPTION_AGENT,*/ const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = ProvAgFrm_STYLE);

        virtual ~ProvAgFrm();   	
    	ProvAgFrm(const wxString& title);       
        
        //MyPanel *panel;
        //wxPanel *panel;
        wxStaticBox *stBox1, *stBox2, *stBox3;
        wxStaticBoxSizer *to_static_box1,   //�����
        *to_static_box2,                    //������
        *to_static_box3;                    //������
        wxBoxSizer *vert_bos,
        *hr1;
        
        int id_menu;
        int count_find; //���������� ������������ ���-�� ��������� ���������� ����� �����
        int count_add;  //���������� ������������ ���-�� ����� ����������� �������
        
	private:
		enum {ID_DUMMY_VALUE_}; //don't remove this value unless you have other enum values};
		void OnClose(wxCloseEvent& event);
		//void OnSize (wxSizeEvent& event);
        //void OnMove (wxMoveEvent& event);
        void OnEnter (wxCommandEvent& event);
        void OnMenu (wxCommandEvent& event);
        void GetItemCountListCtrl (void); //������������ ���-�� ����� � ��������
        void ClearPoisk (wxCommandEvent& event);
        void OnButton (wxCommandEvent& event);
        void DeleteFz (void);
        void OnMouse(wxMouseEvent& event);
        void OnEaraseListbox(wxEraseEvent& event);
        void OnPaintListbox(wxPaintEvent& event);

};

class EnterPassword : public wxDialog //���������� ���� � ������ ������� ������
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterPassword(wxWindow *parent, wxWindowID id = wxID_ANY,const wxString &caption=wxCAPTION_ACCOUNT, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterPassword();
    private:
        void OnButton( wxCommandEvent &event);
};

class EnterAssortiment : public wxDialog //���������� ���� � ������/��������������� ������������ ��
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterAssortiment(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &inn="", const wxString &caption=wxCAPTION_ASSORTI, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterAssortiment();
        wxWindow *window_last;     //���� ����, ������� ����� ����� ����� �����.
        int id_group;
        wxString inn;
    private:
        void OnButton (wxCommandEvent &event);
        void NewFocus (wxChildFocusEvent &event);
};

class EnterProvTo : public wxDialog //���������� ���� �����/�������������� �������� ��
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterProvTo(wxWindow *parent, int id1, int type, wxWindowID id = wxID_ANY, const wxString &caption=wxCAPTION_PROV_TO, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterProvTo();
        int idWindowFocus;               //���� ����, ������� ����� ����� ����� �����.
        int id_oc;                  //���� ��. ������������� ����� ������ ������ ����� ��������� ����� � ��
        int id_gc;                  //���� ��. ������������� ����� ������ ������ ����� ��������� ����� � ��
        wxString id_;                    //���� �� (���� ��������� ����� �������� ��) ��� ���� �������� ��(���� ����������� �������� ��).
        wxString type_operation;         //��� ��������: 0 - ����������, 1 - ����������.
        wxBoxSizer *vert_bos, *hr5; //������ ���������� ������������ ��� ������ ���� �������������� - ����������
    private:
        void OnButton (wxCommandEvent &event);
        void NewFocus (wxChildFocusEvent &event);
        void OnChar(wxKeyEvent& event);
};

class EnterProvSotrTo : public wxDialog //���������� ���� �����/�������������� ����������� ��
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterProvSotrTo(wxWindow *parent, int id1, int type, wxWindowID id = wxID_ANY, const wxString &caption=wxCAPTION_PROV_FZ, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterProvSotrTo();
        int idWindowFocus;               //���� ����, ������� ����� ����� ����� �����.
        wxString id_;                    //���� �� (���� ��������� ����� �������� ��) ��� ���� �������� ��(���� ����������� �������� ��).
        wxString id_fio;                 //���� ���.����
        wxString type_operation;         //��� ��������: 0 - ����������, 1 - ����������.
    private:
        void OnButton (wxCommandEvent &event);
        void OnChar(wxKeyEvent& event);
        void NewFocus (wxChildFocusEvent &event);
};

class ListFindFio : public wxDialog //���������� ���� �� ������� ��������� ���������� �� ���
{
    
    private:
        DECLARE_EVENT_TABLE();
    
    public:
        ListFindFio(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &caption=wxNULL_STRING, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION |wxRESIZE_BORDER );
        virtual ~ListFindFio();
    private:
        void OnChar(wxKeyEvent& event);
};

class EnterFz : public wxDialog //���������� ���� �����/�������������� ���.����
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterFz(wxWindow *parent, int id1, int type, wxWindowID id = wxID_ANY,  const wxString &caption=wxCAPTION_FZ, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterFz();
        wxString select_string;                    //����� ���������� ������ � ������ �������
        wxString id_fio;                    //���� ���.����
        wxString type_operation;         //��� ��������: 0 - ����������, 1 - ����������.
        
    private:
        void OnButton (wxCommandEvent &event);
        void OnChar(wxKeyEvent& event);
        FioData old_data; //������ ������ �� ��, �� ���������� ������������� ������ � ���������
        
};

class ListProvFz : public wxDialog //���������� ���� ������ ��������  ���.����
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        ListProvFz(wxWindow *parent, int id_fio, const wxString &caption, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER|wxCLOSE_BOX);
        virtual ~ListProvFz();
        wxString id_fio;                    //���� ���.����
    private:
        void OnButton (wxCommandEvent &event);
        void OnChar(wxKeyEvent& event);
        void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
        void CommentProv (void);
        void DeleteProv (void);
        void SelectInfoFromBD (void);
};

class InsProvFz : public wxDialog //���������� ���� ��������/�������� �������� ���.����.
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        InsProvFz(wxWindow *parent, const wxString &idItem, const wxString &id_fio, const wxString &caption, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER);
        virtual ~InsProvFz();
        wxString id_prov_fz;                    //���� �������� ���.����
        wxString id_fio;                        //���� ���.����
        wxString idItemListView;                //����� ��������� ������ � ������� � ����������
        wxString textBunner;                    //���������� ��� ������ �������
        int idWindowFocus;                      //���� ���� ������� ��������� ����� ����� ����� 
    private:
        ProvFlData old_data; //���� ����� ����������� � �����. �� ��������� �������������. ��� ��������� ������ � ��.
        void OnButton (wxCommandEvent &event);
        void OnChar(wxKeyEvent& event);
        void NewFocus(wxChildFocusEvent& event);
        void completeListView (void);
        void SelectItemListView (wxListEvent& event);
        void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
};

class NotebookOtchet : public wxFrame //���� � ������� � ��������� ��/������� �� ������� ����
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		NotebookOtchet(wxWindow *parent, wxWindowID id = wxID_WINDOW_OTCHET, const wxString &title = wxCAPTION_OTCHET, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = NotebookOtchet_STYLE);

        virtual ~NotebookOtchet();   	
    	NotebookOtchet(const wxString& title);       
        int id_menu;
        wxBoxSizer *vert_bos;
        wxNotebook *nb;
        
	private:
		enum {ID_DUMMY_VALUE_}; //don't remove this value unless you have other enum values};
		void WorkSql(void);
		void OnButton (wxCommandEvent &event);
		void CollapChanged (wxCollapsiblePaneEvent& event);
		void GhangePageNotebook (wxBookCtrlEvent& event);
		void GhangeTreeListCtrl (wxTreeListEvent& event);
		void GhangeListview (wxListEvent& event);
		void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
};

class PoiskToDialog : public wxDialog //���������� ���� ������ �������� ����������� �� �������� ����������
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        PoiskToDialog(wxWindow *parent, const wxString &caption = wxCAPTION_POISK_TO, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER);
        virtual ~PoiskToDialog();
        
        wxBoxSizer *vert_bos, *hr_1, *vert_1;
        
    private:
        void OnChar(wxKeyEvent& event);
        void ClearPoisk (wxCommandEvent& event);
        void DClickMouse (wxMouseEvent& event);
};

class NotebookSovetnik : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		NotebookSovetnik(wxWindow *parent, wxWindowID id = wxID_WINDOW_SOVETNIK, const wxString &title = wxCAPTION_SOVETNIK, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = NotebookSovetnik_STYLE);

        virtual ~NotebookSovetnik();   	
    	NotebookSovetnik(const wxString& title);       
        
        wxNotebook          *nb;
        wxBoxSizer          *vert_bos;
        wxBannerWindow      *banner; //���� ��� �� � ���
        wxTreeCtrl          *treeRegion; //���� ��� �������
        wxStaticText        *staticDolz; //���� ��� ������� ����������
        wxTreeCtrl          *treeRegionBasic; //���� ��� �������       
	private:
        void CollapChanged (wxCollapsiblePaneEvent& event);
        void OnEnter (wxCommandEvent& event);
        void ListviewChangedItem (wxListEvent& event);
        void GhangePageNotebook (wxBookCtrlEvent& event);
        void GhangeStatusbar (int& page);
        void OtpuskNow (void);
        void OtpuskHistory (void);
        void ListSovetnik (void);
        void TreeRegion (void);
        void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
        void TreeListChanged(wxTreeListEvent& event);
		enum {ID_DUMMY_VALUE_}; //don't remove this value unless you have other enum values};
};

class NotebookAdmin : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		NotebookAdmin(wxWindow *parent, wxWindowID id = wxID_WINDOW_ADMIN, const wxString &title = wxCAPTION_ADMIN_BD, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = NotebookAdmin_STYLE);

        virtual ~NotebookAdmin();   	
    	NotebookAdmin(const wxString& title);       
        
        wxBoxSizer *vert_bos;
        wxBoxSizer *vert_sub_note, *hr_local_1, *vr_local_2, *hr_local_3, *vr_local_1;
        wxBoxSizer *hr_propgrid;
        wxPanel *panel_first_line, *panel_second_line; //������ ������������ � �������� - ����������. ������ ������ - ��� ����������, ������� ������ - ��� ��������� � ����������� ����
        wxPanel *panel_sovetnic; //������ ������������ ��� ��������� ���������� �� ����������
        wxPanel *panel_bd;      //������ ������������ ��� ������ � �� ��
        wxPanel *panel_privkey;      //������ ������������ ��� �������������� ����������
        //wxScrolledWindow *panel_sovetnic;
        wxNotebook *nb;
        wxNotebook *nb_spr; //��������� �� ������� �� �������������
        int idWindowFocus;               //���� ����, ������� ����� ����� ����� �����.
        wxArrayInt arrayIdLogin, arrayIdPrivilege, arrayIdReestrPriv; //������� ������������ �� �������� ���������� ��� �������� id ������� � ����������, � ����� id ������ �����/����������. 
    private:
        void OnChar(wxKeyEvent& event);
        void ChangeCombobox (wxCommandEvent& event);
        void FocusedItemListview (wxListEvent& event);
        void OnEnter (wxCommandEvent& event);
        void CollapChanged (wxCollapsiblePaneEvent& event);
        void CollapsedPropgrid (wxPropertyGridEvent &event);
        void ExpandedPropgrid (wxPropertyGridEvent &event);
        void ProcessInfoBar(wxString &str1, wxInfoBar* ihfobar);
        void OnButton (wxCommandEvent &event);
        void NewFocus (wxChildFocusEvent &event);
        void BuildNotebookSpr (wxNotebook* nb_sub);
        void CreateBlList (void);
        void CreateSubNotebookPrivilege (void);
        void CreateSubNotebookBl (void);
        void CreateSubNotebookSov (void);
        void CreateSubNotebookSpr (void); //������� ������� ��������� ������� �� �������������
        void FillCollpaneBLUpd (void); //������� ���������� �������� ������ (�������� ���������� � �� ��)
        void GhangeRadiobox (wxCommandEvent& event);
        void GhangePageNotebook (wxBookCtrlEvent& event);
        void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
        void LoadHolidayForSov(void);
        void LoadRegionForSov(void);
        void LoadDolzForSov(void);
        void LoadPersDanForSov(void);
        void LoadPrivListbox (void); //������� � ��������� ������� ����������(���) � ��������� ������ arrayIdPrivilege
        void ListBoxWork (wxCommandEvent& event); 
        void LoadLoginCombobox (void); //������� � ��������� ������� �������(���) � ��������� ������ arrayIdLogin
        void ComboBoxWork (wxCommandEvent& event); 
        
		enum {ID_DUMMY_VALUE_}; //don't remove this value unless you have other enum values};
};

class ContactFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		ContactFrm(wxWindow *parent, wxWindowID id = wxID_WINDOW_CONTACT, const wxString &title = wxCAPTION_CONTACT_TEL, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = ContactFrm_STYLE);

        virtual ~ContactFrm();   	
    	ContactFrm(const wxString& title);   
        wxPanel *panel_contact;  
        wxBoxSizer *bx_contact;
        wxStaticText *text_;  
                    
	private:
        void InsertCallRezult (int i);
        void WorkStatusBar (void);
        void OnEnter (wxCommandEvent& event);
        void OnButton(wxCommandEvent& event);
        void OnMouse(wxMouseEvent& event);
        void CollapChanged (wxCollapsiblePaneEvent& event);
        void ChangeStringList (wxListEvent& event);
        void SelectAllCompany (void);
        void SelectPrivateCompany (int& id);
        void DeleteCompany (void);
        void DeleteContact (void);
        void DeleteCall (void);
        void SelectFioContact (int& id_company);
        void SelectCommentContact (int& id_contact);
        void SelectCallContact (int& id_contact);
        void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
        
};

class UpdateCompanyDialog : public wxDialog //���������� ���� 
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        //id_operation: 1 - ������ ������ ��������, 2 - ������ ������ ��������
        UpdateCompanyDialog(wxWindow *parent, int id_operation, const wxString &caption = wxNULL_STRING, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE );
        virtual ~UpdateCompanyDialog();
        hash_map HashTypeCompany;
        int id_opera;
    private:
        void OnButton (wxCommandEvent &event);
};
class UpdateFioContactDialog : public wxDialog //���������� ���� 
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        //id_operation: 1 - ������ ������ ��������, 2 - ������ ������ ��������
        UpdateFioContactDialog(wxWindow *parent, int id_operation, const wxString &caption = wxNULL_STRING, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE );
        virtual ~UpdateFioContactDialog();
        hash_map HashNameRegion;
        int id_opera;
    private:
        void OnChar(wxKeyEvent& event);
        void OnButton (wxCommandEvent &event);
};

class InsUpdHolidaySotrDialog : public wxDialog //���������� ���� 
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        //id_operation: 1 - ������ ������ ��������, 2 - ������ ������ ��������
        InsUpdHolidaySotrDialog(wxWindow *parent, int id_operation, const wxString &caption = wxNULL_STRING, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE );
        virtual ~InsUpdHolidaySotrDialog();
        int id_opera;
    private:
        void OnButton (wxCommandEvent &event);
};
//extern ProvToFrm* frame_to;


/*
class test : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		test(wxWindow *parent, wxWindowID id = wxID_WINDOW_TEST, const wxString &title = "Test", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);

        virtual ~test();   	
    	test(const wxString& title);       
        
        wxAuiManager m_Manager;

	private:
		enum {ID_DUMMY_VALUE_}; //don't remove this value unless you have other enum values};

};
*/
class wxAuiWorkPanel : public wxFrame
{
    public:
        wxAuiManager m_Manager;
        wxAuiNotebook * m_Notebook;
        wxToolBar *m_StdToolBar;
        wxToolBar *m_PageToolBar;
        ProvAgFrm * m_Page1;
	    ProvToFrm * m_Page2;
	   void OnSize (wxSizeEvent& event);
       void OnMove (wxMoveEvent& event);
	   void CreateControl (void);
	   void CreateToolbar(void);
	   void CreateButtonPanel(void);
	   void WorkStatusBar (void);
	   void CreatePanelSearchUL(void);
	   void SearchFL(wxCommandEvent& event);
	   void SearchUL(wxCommandEvent& event);
	   void ClearSearchUL (wxCommandEvent& event);
	   void DeleteFz (void);
	   void ChangeStringList (wxListEvent& event);
	   void OnButton(wxCommandEvent& event);
	   void ChangeNotebookPage (wxAuiNotebookEvent& event);
	   void ClosePage (wxAuiNotebookEvent& event);
	   wxAuiWorkPanel();
	   wxAuiWorkPanel(wxWindow * parent, 
				wxWindowID id = wxID_WINDOW_AUI_W_P,
				const wxString & title = wxAuiTitleStr,
				const wxPoint & pos = wxDefaultPosition,
				const wxSize & size = wxDefaultSize,
				long style = wxDEFAULT_FRAME_STYLE);
	   ~wxAuiWorkPanel();
    private:
		DECLARE_EVENT_TABLE();
};

class HolidayFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		HolidayFrm(wxWindow *parent, wxWindowID id = wxID_WINDOW_HOL_P, const wxString &title = wxCAPTION_ACCHOLD, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = HolidayFrm_STYLE);

        virtual ~HolidayFrm();   	
    	HolidayFrm(const wxString& title);       
    	int id_reg; //���� ������������
        
	private:
		enum {ID_DUMMY_VALUE_}; //don't remove this value unless you have other enum values};
		void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
        void OnButton(wxCommandEvent& event);
        void FocusedItemListview (wxListEvent& event);
        void FillTableHoliday ();
        void OnMouse(wxMouseEvent& event);
        int ChackSign(wxListView* listveiwHoliday);


};
#endif
