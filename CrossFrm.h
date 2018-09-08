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
#include <wx/custombgwin.h> //для wxCustomBackgroundWindow

#include <mysql.h>

#include "id.h"
#include "word.h"
#include <wx/dir.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h> //для wxToggleButton
#include <wx/srchctrl.h> //для wxSearchCtrl
#include <wx/utils.h> //Функции в этом разделе, используются для получения информации о текущем компьютере и/или пользователях
#include <wx/aboutdlg.h> // wxAboutDialogInfo
#include <wx/arrimpl.cpp> // wxObjArray. Определяет реализацию шаблона, определяет реализацию моего класса с пом.макроса WX_DEFINE_OBJARRAY
#include <wx/fileconf.h> //wxFileConfig
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/busyinfo.h>        //wxBusyInfo
#include <wx/utils.h>           //wxSleep (INT)
#include <wx/datectrl.h>        //wxDatePickerCtrl 
#include <wx/checkbox.h>        //wxCheckBox
#include <wx/bannerwindow.h>    //wxBannerWindow
#include <wx/textdlg.h>         //стандартные диалоги
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

WX_DECLARE_OBJARRAY(Macroreg, MacroregArray); //объявляем и частично реализуем класс MacroregArray
WX_DECLARE_OBJARRAY(Oc, OcArray); //объявляем и частично реализуем класс OcArray
WX_DECLARE_OBJARRAY(Gc, GcArray); //объявляем и частично реализуем класс OcArray
WX_DECLARE_OBJARRAY(HolidayType, HolidayTypeArray); //объявляем и частично реализуем класс HolidayTypeArray
WX_DECLARE_OBJARRAY(BrandName, BrandNameArray); //объявляем и частично реализуем класс BrandNameArray
WX_DECLARE_OBJARRAY(BrandType, BrandTypeArray); //объявляем и частично реализуем класс BrandTypeArray
WX_DECLARE_OBJARRAY(UkRf, UkRfArray); //объявляем и частично реализуем класс UkRfArray
WX_DECLARE_OBJARRAY(FioSb, FioSbArray); //объявляем и частично реализуем класс FioSbArray
WX_DECLARE_OBJARRAY(RezProv, RezProvArray); //объявляем и частично реализуем класс RezProvArray
WX_DECLARE_OBJARRAY(ProdGroup, ProdGroupArray); //объявляем и частично реализуем класс ProdGroupArray
WX_DECLARE_OBJARRAY(ProdName, ProdNameArray); //объявляем и частично реализуем класс ProdNameArray
WX_DECLARE_OBJARRAY(Dolznost, DolznostArray); //объявляем и частично реализуем класс DolznostArray
WX_DECLARE_OBJARRAY(Sovetnic, SovetnicArray); //объявляем и частично реализуем класс SovetnicArray
WX_DECLARE_OBJARRAY(TechCentr, TechCentrArray); //объявляем и частично реализуем класс TechCentrArray
WX_DECLARE_OBJARRAY(SovConnectReg, SovConnectRegArray); //объявляем и частично реализуем класс SovConnectRegArray
WX_DECLARE_OBJARRAY(TypeProv, TypeProvArray); //объявляем и частично реализуем класс TypeProvArray
WX_DECLARE_OBJARRAY(RootInfo, RootInfoArray); //объявляем и частично реализуем класс RootInfoArray
WX_DECLARE_OBJARRAY(PositionSotrHistory, PositionSotrHistoryArray); //объявляем и частично реализуем класс PositionSotrHistoryArray
WX_DECLARE_OBJARRAY(PositionSotr, PositionSotrArray); //объявляем и частично реализуем класс PositionSotrArray
WX_DECLARE_OBJARRAY(TypeCooperation, TypeCooperationArray); //объявляем и частично реализуем класс TypeCooperationArray
WX_DECLARE_OBJARRAY(InitiatorChecks, InitiatorChecksArray); //объявляем и частично реализуем класс InitiatorChecksArray
WX_DECLARE_OBJARRAY(PrivilegeUser, PrivilegeUserArray); //объявляем и частично реализуем класс PrivilegeUserArray
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
extern PositionSotrArray MyPositionSotrArray; //массив наименование должностей сотрудников СБ
extern TypeCooperationArray MyTypeCooperationArray; //массив типов сотрудничества
extern InitiatorChecksArray MyInitiatorChecksArray; //массив инициаторов проверки контрагента
extern PrivilegeUserArray MyPrivilegeUserArray; //массив инициаторов проверки контрагента

extern void CreateSpravochnic();    //функция загрузки справочников
extern void DeleteSpravochnic ();   //функция очистки массивов под справочники
extern void InformationSleep (wxString str, int sec, wxWindow * parent); //функция выводит предупреждающее сообщение str, которое висит перед пользователем sec секунд
extern void EditStringFio (wxString& str); //функция редактирует строку wxString меняя ИВАНОВ ИВАН ИВАНОВИЧ на Иванов И.И.
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
        wxString fastComment;   //переменная для быстрого комментария
        int flag_bl_sb;         //флаг автоматической проверки по ЧС СБ
    	wxTimer m_timer;
        int flag_timer_fast;    //флаг того, что метод таймера нужно перезапускать чаще	0 - по-умолчанию, 1 - метод нашел расхождение между справочниками и БД, но пользователь еще не обновил справочники, 2 - пользователь обновил справочники, но метод запускается со старым интервалом
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
        wxStaticBoxSizer *to_static_box1,   //карточка то
        *to_static_box1_1,                  //команды то
        *to_static_box2,                    //параметры то
        *to_static_box3,                    //первая полоса списка
        *to_static_box4,                    //вторая полоса списка
        *to_static_box5,                    //третья полоса списка
        *to_static_box6,                    //4-я полоса списка
        *to_static_box_cooperation;          //тип сотрудничества
        wxBoxSizer *to_1,   //инн
        *to_2,              //наименование то
        *to_3,              //бренд
        *to_4,              //кол-во тт
        *to_5,              //банки-конкуренты
        *to_6,              //интернет продажи
        *to_7,              //интернет-сайт
        *hr1,               //первая полоса: карточка то, параметры то
        *vr3,               //первая полоса: карточка то, параметры то
        *vr4,               //первая полоса: карточка то, параметры то
        *vr5,               //первая полоса: карточка то, параметры то
        *vr6,
        *vert;              //вертикальная полоса под списки
        wxStaticBox *stBox1, *stBox1_1, *stBox2, *stBox3, *stBox4, *stBox5, *stBox6, *stBoxCooperation;
        int id_to;              //уникальный айди ТО
        int count_assorti, count_to_prov, count_sotr_prov;
        wxChoice *type_cooperation; //эл.управления с перечнем типов сотрудничества    
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
        wxStaticBoxSizer *to_static_box1,   //поиск
        *to_static_box2,                    //кнопки
        *to_static_box3;                    //список
        wxBoxSizer *vert_bos,
        *hr1;
        
        int id_menu;
        int count_find; //переменная подсчитывает кол-во найденных совпадений через поиск
        int count_add;  //переменная подсчитывает кол-во строк добавленных вручную
        
	private:
		enum {ID_DUMMY_VALUE_}; //don't remove this value unless you have other enum values};
		void OnClose(wxCloseEvent& event);
		//void OnSize (wxSizeEvent& event);
        //void OnMove (wxMoveEvent& event);
        void OnEnter (wxCommandEvent& event);
        void OnMenu (wxCommandEvent& event);
        void GetItemCountListCtrl (void); //подсчитывает кол-во строк в листвюев
        void ClearPoisk (wxCommandEvent& event);
        void OnButton (wxCommandEvent& event);
        void DeleteFz (void);
        void OnMouse(wxMouseEvent& event);
        void OnEaraseListbox(wxEraseEvent& event);
        void OnPaintListbox(wxPaintEvent& event);

};

class EnterPassword : public wxDialog //диалоговое окно с вводом учетных данных
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

class EnterAssortiment : public wxDialog //диалоговое окно с вводом/редактированием ассортимента ТО
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterAssortiment(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &inn="", const wxString &caption=wxCAPTION_ASSORTI, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterAssortiment();
        wxWindow *window_last;     //айди окна, которое ранее имело фокус ввода.
        int id_group;
        wxString inn;
    private:
        void OnButton (wxCommandEvent &event);
        void NewFocus (wxChildFocusEvent &event);
};

class EnterProvTo : public wxDialog //диалоговое окно ввода/редактирования проверок ТО
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterProvTo(wxWindow *parent, int id1, int type, wxWindowID id = wxID_ANY, const wxString &caption=wxCAPTION_PROV_TO, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterProvTo();
        int idWindowFocus;               //айди окна, которое ранее имело фокус ввода.
        int id_oc;                  //айди оц. Присваивается после потери фокуса ввода текстовым полем с оц
        int id_gc;                  //айди гц. Присваивается после потери фокуса ввода текстовым полем с гц
        wxString id_;                    //айди то (если добавляем новую проверку то) или айди проверки то(если редактируем проверку то).
        wxString type_operation;         //тип операции: 0 - добавление, 1 - обновление.
        wxBoxSizer *vert_bos, *hr5; //органы управления подгружаются при выборе типа сотрудничества - контрагент
    private:
        void OnButton (wxCommandEvent &event);
        void NewFocus (wxChildFocusEvent &event);
        void OnChar(wxKeyEvent& event);
};

class EnterProvSotrTo : public wxDialog //диалоговое окно ввода/редактирования сотрудников ТО
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterProvSotrTo(wxWindow *parent, int id1, int type, wxWindowID id = wxID_ANY, const wxString &caption=wxCAPTION_PROV_FZ, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterProvSotrTo();
        int idWindowFocus;               //айди окна, которое ранее имело фокус ввода.
        wxString id_;                    //айди то (если добавляем новую проверку то) или айди проверки то(если редактируем проверку то).
        wxString id_fio;                 //айди физ.лица
        wxString type_operation;         //тип операции: 0 - добавление, 1 - обновление.
    private:
        void OnButton (wxCommandEvent &event);
        void OnChar(wxKeyEvent& event);
        void NewFocus (wxChildFocusEvent &event);
};

class ListFindFio : public wxDialog //диалоговое окно со списком найденных совпадений по фио
{
    
    private:
        DECLARE_EVENT_TABLE();
    
    public:
        ListFindFio(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &caption=wxNULL_STRING, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION |wxRESIZE_BORDER );
        virtual ~ListFindFio();
    private:
        void OnChar(wxKeyEvent& event);
};

class EnterFz : public wxDialog //диалоговое окно ввода/редактирования физ.лица
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        EnterFz(wxWindow *parent, int id1, int type, wxWindowID id = wxID_ANY,  const wxString &caption=wxCAPTION_FZ, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION);
        virtual ~EnterFz();
        wxString select_string;                    //номер выделенной строки в списке агентов
        wxString id_fio;                    //айди физ.лица
        wxString type_operation;         //тип операции: 0 - добавление, 1 - обновление.
        
    private:
        void OnButton (wxCommandEvent &event);
        void OnChar(wxKeyEvent& event);
        FioData old_data; //старые данные по фл, до обновления пользователем данных в контролах
        
};

class ListProvFz : public wxDialog //диалоговое окно список проверок  физ.лица
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        ListProvFz(wxWindow *parent, int id_fio, const wxString &caption, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER|wxCLOSE_BOX);
        virtual ~ListProvFz();
        wxString id_fio;                    //айди физ.лица
    private:
        void OnButton (wxCommandEvent &event);
        void OnChar(wxKeyEvent& event);
        void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
        void CommentProv (void);
        void DeleteProv (void);
        void SelectInfoFromBD (void);
};

class InsProvFz : public wxDialog //диалоговое окно добавить/обновить проверку физ.лица.
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        InsProvFz(wxWindow *parent, const wxString &idItem, const wxString &id_fio, const wxString &caption, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER);
        virtual ~InsProvFz();
        wxString id_prov_fz;                    //айди проверки физ.лица
        wxString id_fio;                        //айди физ.лица
        wxString idItemListView;                //номер выбранной строки в диалоге с проверками
        wxString textBunner;                    //переменная для текста баннера
        int idWindowFocus;                      //айди окна которое последним имело фокус ввода 
    private:
        ProvFlData old_data; //айди полей загруженных в форму. До изменения пользователем. Для сравнения данных с БД.
        void OnButton (wxCommandEvent &event);
        void OnChar(wxKeyEvent& event);
        void NewFocus(wxChildFocusEvent& event);
        void completeListView (void);
        void SelectItemListView (wxListEvent& event);
        void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
};

class NotebookOtchet : public wxFrame //окно с отчетом о проверках ТО/агентов за текущий день
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

class PoiskToDialog : public wxDialog //диалоговое окно поиска торговой организации по заданным параметрам
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
        wxBannerWindow      *banner; //поле для ДР и тел
        wxTreeCtrl          *treeRegion; //поле для региона
        wxStaticText        *staticDolz; //поле для истории должностей
        wxTreeCtrl          *treeRegionBasic; //поле для региона       
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
        wxPanel *panel_first_line, *panel_second_line; //панели используются в блокноте - справочник. первая панель - это радиобоксы, второая панель - это текстовые и статические поля
        wxPanel *panel_sovetnic; //панель используется для элементов управления по советникам
        wxPanel *panel_bd;      //панель используется для работы с ЧС СБ
        wxPanel *panel_privkey;      //панель используется для предоставления привилегий
        //wxScrolledWindow *panel_sovetnic;
        wxNotebook *nb;
        wxNotebook *nb_spr; //указатель на блокнот со справочниками
        int idWindowFocus;               //айди окна, которое ранее имело фокус ввода.
        wxArrayInt arrayIdLogin, arrayIdPrivilege, arrayIdReestrPriv; //массивы используются на странице Привилегии для хранения id логинов и привилегий, а также id связки Логин/Привилегия. 
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
        void CreateSubNotebookSpr (void); //функция создает вложенный блокнот со справочниками
        void FillCollpaneBLUpd (void); //функция заполнения складной панели (операция обновления в ЧС СБ)
        void GhangeRadiobox (wxCommandEvent& event);
        void GhangePageNotebook (wxBookCtrlEvent& event);
        void OnSize (wxSizeEvent& event);
        void OnMove (wxMoveEvent& event);
        void LoadHolidayForSov(void);
        void LoadRegionForSov(void);
        void LoadDolzForSov(void);
        void LoadPersDanForSov(void);
        void LoadPrivListbox (void); //очищает и заполняет таблицу привилегий(все) и связанный массив arrayIdPrivilege
        void ListBoxWork (wxCommandEvent& event); 
        void LoadLoginCombobox (void); //очищает и заполняет таблицу логинов(все) и связанный массив arrayIdLogin
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

class UpdateCompanyDialog : public wxDialog //диалоговое окно 
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        //id_operation: 1 - нажата кнопка добавить, 2 - нажата кнопка обновить
        UpdateCompanyDialog(wxWindow *parent, int id_operation, const wxString &caption = wxNULL_STRING, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE );
        virtual ~UpdateCompanyDialog();
        hash_map HashTypeCompany;
        int id_opera;
    private:
        void OnButton (wxCommandEvent &event);
};
class UpdateFioContactDialog : public wxDialog //диалоговое окно 
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        //id_operation: 1 - нажата кнопка добавить, 2 - нажата кнопка обновить
        UpdateFioContactDialog(wxWindow *parent, int id_operation, const wxString &caption = wxNULL_STRING, wxWindowID id = wxID_ANY,   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE );
        virtual ~UpdateFioContactDialog();
        hash_map HashNameRegion;
        int id_opera;
    private:
        void OnChar(wxKeyEvent& event);
        void OnButton (wxCommandEvent &event);
};

class InsUpdHolidaySotrDialog : public wxDialog //диалоговое окно 
{
    
    private:
    //DECLARE_CLASS(EnterPassword);
    DECLARE_EVENT_TABLE();
    
    public:
        //id_operation: 1 - нажата кнопка добавить, 2 - нажата кнопка обновить
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
    	int id_reg; //айди макрорегиона
        
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
