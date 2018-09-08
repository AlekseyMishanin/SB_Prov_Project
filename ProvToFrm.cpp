#include "CrossFrm.h"

extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern int sec_for_sleep_window_info;
extern int proverka_bl_sb(MYSQL* conn, wxString& str, int type); //функция проверяет str на предмет наличия в ЧС СБ. type - тип ЧС СБ для проверки, 0 - ТО, 1 - физики

//extern ProvToFrm* frame_to;

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
extern PositionSotrArray MyPositionSotrArray; //массив связей сотрудника и должности

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
        //file_menu->Append(wxID_MENU_FILE_POISK, "&Поиск");
	    //menubar->Append(file_menu, "&Файл");
	    //SetMenuBar(menubar);
	    //Connect(wxID_MENU_FILE_POISK, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(ProvToFrm::OnMenu));
	            
        //this = new wxPanel(this,wxID_ANY);
        wxString str_full, str_first, str_last;
        vert = new wxBoxSizer(wxVERTICAL);
        
        
        
        stBoxCooperation = new wxStaticBox(this,wxID_STBOX_COOPERATION,"Тип сотрудничества");
        to_static_box_cooperation = new wxStaticBoxSizer(stBoxCooperation,wxHORIZONTAL);
        wxString strTypeCoop[] = {"POS","Зарплатный проект","Интернет-эквайринг","Малый бизнес","Контрагент","РКО", "ТО по приему платежей"}; //создаем статический массив с типами сотрудничества
        type_cooperation = new wxChoice(this,wxID_CHOISE_COOPERATION,wxDefaultPosition, wxDefaultSize, sizeof(strTypeCoop)/sizeof(wxString),strTypeCoop);
        to_static_box_cooperation->Add(type_cooperation,1,wxEXPAND|wxALL,5); //создаем элемент управления с типами сотрудничества
        type_cooperation->SetSelection(0); //выбираем из списка первую строку
        
        
        stBox1 = new wxStaticBox(this,wxID_STBOX_CARD_TO,"Карточка ТО");
        stBox1_1 = new wxStaticBox(this,wxID_STBOX_COMMAND,"Команды");
        stBox2 = new wxStaticBox(this,wxID_STBOX_PARAM_TO,"Параметры ТО");

        to_static_box1 = new wxStaticBoxSizer(stBox1,wxVERTICAL);
        to_static_box2 = new wxStaticBoxSizer(stBox2,wxVERTICAL);
        to_static_box1_1 = new wxStaticBoxSizer(stBox1_1,wxVERTICAL);

        to_1 = new wxBoxSizer(wxHORIZONTAL);
        to_2 = new wxBoxSizer(wxHORIZONTAL);
        
        to_1->Add(new wxStaticText(this,wxID_TO_STATICBOX_INN,wxCAPTION_COLUMN_INN), 0,wxEXPAND |wxALL,0);
        to_1->Add(new wxTextCtrl(this,wxID_TO_INN, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT,5);
        ((wxTextCtrl*)this->FindWindow(wxID_TO_INN))->SetMaxLength(12); //устанавливаем ограничение на количество вводимых символов в поле с ИНН        
        str_first = dir.GetName(); str_last= wxSEE_ICO; str_full=str_first; str_full+=str_last;
        wxImage *image = new wxImage(str_full,wxBITMAP_TYPE_ICO);
        image->Rescale(16,16);
        to_1->Add(new wxBitmapButton(this,wxID_BUTTON_INN_TO, wxBitmap(*image), wxDefaultPosition,wxSize(24,24)),0, wxEXPAND|wxALL,0);
        to_2->Add(new wxStaticText(this,wxID_TO_STATICBOX_TO,wxCAPTION_COLUMN_TO),0, wxEXPAND|wxALL,0);
        to_2->Add(new wxTextCtrl(this,wxID_TO_NAME, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT,5);
        
        /*подсказки*/
        ((wxTextCtrl*)this->FindWindow(wxID_TO_INN))->SetHint(wxString("введите ИНН"));
        ((wxTextCtrl*)this->FindWindow(wxID_TO_NAME))->SetHint(wxString("введите наименование ТО/ИП"));
        
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
              
        wxCommandEvent event_local; //создаем объект класса событие
        event_local.SetId(wxID_CHOISE_COOPERATION); //устанавливаем идентификатор связанный с этим событием
        event_local.SetEventType(wxEVT_COMMAND_CHOICE_SELECTED); //устанавливаем тип события
        this->ProcessWindowEventLocally(event_local); //запускаем для данного окна поиск подходящего обработчика для события event_local
    
        
        //wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
        //for(register wxWindowList::const_iterator it = list.begin(); it!=list.end(); ++it) {(*it)->SetBackgroundColour(*wxWHITE);} //через итератор перебираем все окна и меняем цвет фона
        /*wxWindowList list1 = panel->GetChildren(); //получаем список всех дочерних окон
        //for(register wxWindowList::const_iterator it = list1.begin(); it!=list1.end(); ++it) {(*it)->SetBackgroundColour(*wxWHITE);} //через итератор перебираем все окна и меняем цвет фона
        for(register wxWindowList::const_iterator it = list1.begin(); it!=list1.end(); ++it) 
        {
            if(((*it)->GetId())==) {wxMessageBox("dfdf");}
            
        }*/
        //Center(); //центрировать окно
                
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
                case 0: //пос
                {
                    wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
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
                            
                            if(((*it)->GetId())==wxID_BUTTON_SP_PROV) {((wxToggleButton*)(*it))->SetValue(false);} //переводим кнопку в не нажатое состояние
                            if(((*it)->GetId())==wxID_BUTTON_SP_SOTR) {((wxToggleButton*)(*it))->SetValue(false);} //переводим кнопку в не нажатое состояние
                        } else {(*it)->Destroy();}     //разрушаем элемент управления
                    }
                    to_3 = new wxBoxSizer(wxHORIZONTAL);
                    to_4 = new wxBoxSizer(wxHORIZONTAL);
                    to_5 = new wxBoxSizer(wxHORIZONTAL);
                    to_6 = new wxBoxSizer(wxHORIZONTAL);
                    to_7 = new wxBoxSizer(wxHORIZONTAL);
        
                    to_3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_NET),0,wxEXPAND |wxALL,0);
                    to_3->Add(new wxTextCtrl(this,wxID_TO_BRAND, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT|wxRIGHT,5);
                    wxArrayString LocBrendArray; //объявляем массив для автозаполнения в текстовом поле
                    LocBrendArray.Alloc(MyBrandNameArray.GetCount());  //Резервирует достаточно памяти для хранения nCount предметов   
                    for(register int i =0; i<MyBrandNameArray.GetCount();++i) //заполняем локальный массив наименованиями торговых сетей
                    {
                        LocBrendArray.Add((MyBrandNameArray.Item(i).nameBrandName));
                    }
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->AutoComplete(LocBrendArray); //подключаем к текстовому полю функцию автоматического завершения текста
                    to_3->Add(new wxStaticText(this,wxID_TO_TYPE_BRAND,wxBRAND_DEFAULT),0, wxEXPAND |wxALL,0);
                    to_4->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_COUNT_TT),0, wxEXPAND |wxALL,0);
                    to_4->Add(new wxTextCtrl(this,wxID_TO_KOL_TT, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT,5);
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_KOL_TT))->SetMaxLength(4); //устанавливаем ограничение на количество вводимых символов в поле с кол-вом ТТ
                    to_5->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_BANK_KONK),0, wxEXPAND |wxALL,0);
                    to_5->Add(new wxTextCtrl(this,wxID_TO_BANK_KONK, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT,5);
                    to_6->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_INET_SALES),0, wxEXPAND |wxALL,0);
                    to_6->Add(new wxComboBox(this,wxID_TO_FLAG_INET, wxEmptyString, wxDefaultPosition, wxDefaultSize,0,NULL,wxCB_READONLY),0, wxEXPAND |wxLEFT,5);
                    ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->Insert(wxSTRING_YES,0);
                    ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->Insert(wxSTRING_NO,0);
                    ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->SetSelection(0);
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->SetHint(wxString("выберите сеть"));
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_KOL_TT))->SetHint(wxString("укажите количество ТТ"));
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_BANK_KONK))->SetHint(wxString("перечислите банки-конкуренты"));
                    to_static_box1->Add(to_3, 0, wxEXPAND,0);
                    to_static_box1->Add(to_4, 0, wxEXPAND,0);
                    to_static_box1->Add(to_5, 0, wxEXPAND,0);
                    to_static_box1->Add(to_6, 0, wxEXPAND,0);
                    to_static_box1->Add(to_7, 0, wxEXPAND,0);
        
                    to_static_box2->Add(new wxToggleButton(this,wxID_BUTTON_SP_ASRT,wxCAPTION_BUTTON_ASSORTI), 0, wxEXPAND|wxALL,0);
                    ClearForm(1); //очищаем поля формы
                    vert->Layout(); 
                    break;
                }
                case 1: //зарплатный проект
                {
                    wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
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
                        } else {(*it)->Destroy();}     //разрушаем элемент управления
                    }
                    to_3 = new wxBoxSizer(wxHORIZONTAL);
                    to_3->Add(new wxStaticText(this,wxID_ANY,wxCAPTION_COLUMN_KOLSOTR),0,wxEXPAND |wxALL,0);
                    to_3->Add(new wxTextCtrl(this,wxID_UL_KOL_SOTR, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE),1, wxEXPAND |wxLEFT|wxRIGHT,5);
                    ((wxTextCtrl*)this->FindWindow(wxID_UL_KOL_SOTR))->SetHint(wxString("укажите количество сотрудников"));
                    to_static_box1->Add(to_3, 0, wxEXPAND,0);
                    ClearForm(1); //очищаем поля формы
                    vert->Layout(); 
                    break;
                }
                case 2: //интернет-эквайринг
                {
                    wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
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
                        } else {(*it)->Destroy();}     //разрушаем элемент управления
                    }
                    to_3 = new wxBoxSizer(wxHORIZONTAL);
                    to_3->Add(new wxStaticText(this,wxID_ANY,"Интернет-сайт ЮЛ"),0, wxEXPAND |wxALL,0);
                    to_3->Add(new wxTextCtrl(this,wxID_TO_SITE_INET, wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_CENTRE|wxTE_AUTO_URL),1, wxEXPAND |wxLEFT|wxRIGHT,5);
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_SITE_INET))->SetHint(wxString("укажите интернет-сайт компании"));
                    to_4 = new wxBoxSizer(wxHORIZONTAL);
                    to_4->Add(new wxStaticText(this,wxID_ANY,"Интернет-сайт эквайринга"),0,wxEXPAND |wxALL,0);
                    to_4->Add(new wxTextCtrl(this,wxID_TO_EK_SITE_INET, wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_CENTRE|wxTE_AUTO_URL),1, wxEXPAND |wxLEFT|wxRIGHT,5);
                    ((wxTextCtrl*)this->FindWindow(wxID_TO_EK_SITE_INET))->SetHint(wxString("укажите интернет-сайт эквайринга"));
                    to_static_box1->Add(to_3, 0, wxEXPAND,0);
                    to_static_box1->Add(to_4, 0, wxEXPAND,0);
                    ClearForm(1); //очищаем поля формы
                    vert->Layout(); 
                    break;
                }
                case 3: //малый бизнес
                {
                    wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
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
                        } else {(*it)->Destroy();}     //разрушаем элемент управления
                    }
                    ClearForm(1); //очищаем поля формы
                    vert->Layout(); 
                    break;
                }
                case 4: //контрагент
                {
                    wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
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
                        } else {(*it)->Destroy();}     //разрушаем элемент управления
                    }
                    to_3 = new wxBoxSizer(wxHORIZONTAL);
                    to_3->Add(new wxCheckBox(this,wxID_TO_CHECKBOX_FL_IP,wxCAPTION_CHECKBOX_FL_IP),0,wxEXPAND |wxALL,0);
                    ((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetToolTip(wxString("признак проставляется в отношении физических лиц или юридических лиц, привлекаемых к сотрудничеству в качестве контрагентов, но без ИНН"));
                    to_static_box1->Add(to_3, 0, wxEXPAND,0);
                    to_static_box2->Add(new wxToggleButton(this,wxID_BUTTON_KT_KONTRACT,wxCAPTION_BUTTON_KONTRACT), 0, wxEXPAND|wxALL,0);
                    ClearForm(1); //очищаем поля формы
                    vert->Layout(); 
                    break;
                }
                case 5: //РКО
                {
                    wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
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
                        } else {(*it)->Destroy();}     //разрушаем элемент управления
                    }
                    ClearForm(1); //очищаем поля формы
                    vert->Layout(); 
                    break;
                }
                case 6: //ТО по приему платежей
                {
                    wxWindowList list = this->GetChildren(); //получаем список всех дочерних окон
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
                        } else {(*it)->Destroy();}     //разрушаем элемент управления
                    }
                    ClearForm(1); //очищаем поля формы
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
void ProvToFrm::OnSize(wxSizeEvent& event) //ловим размеры окна во время события изменения нижней или правой границы
{
	wxRect rect = GetRect(); //считываем текущие размеры окна
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
void ProvToFrm::OnMove(wxMoveEvent& event) //ловим размеры окна во время события передвижения окна
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
        wxString str = ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->GetValue(); //получаем текст контрола
        str = str.MakeUpper();                                                      //приводим текст к верхнему регистрку
        ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->ChangeValue(str);          //заменяем текст контрола
        ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->SetInsertionPointEnd();    //устанавливаем курсор ввода на конец текста
        for(register int i =0; i<MyBrandNameArray.GetCount();++i) //запускаем цикл поиска в справочнике типов сетей точного совпадения со значением введенным в текстовом поле
        {
            if(!str.compare(MyBrandNameArray.Item(i).nameBrandName)) //совпадение найдено
            {
                for(register int j =0; j<MyBrandTypeArray.GetCount();++j) //запускаем цикл поиска в справочнике типов сетей типа сети соответствующего найденному значению
                {
                    //if(!MyBrandNameArray.Item(i).idBrandType.compare(MyBrandTypeArray.Item(j).idBrandType)) //совпадение найдено
                    if(MyBrandNameArray.Item(i).idBrandType==MyBrandTypeArray.Item(j).idBrandType) //совпадение найдено
                    {
                        
                        ((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(MyBrandTypeArray.Item(j).nameBrandType); //выводим в статическое поле тип сети
                        break; //выходим из вложенного цикла поиска типа сети
                    }
                }
                break; //выходим из вложенного цикла поиска совпадения по наименованию сети
            } else {((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(wxBRAND_DEFAULT);}
        }
        vert->Layout(); //просим сайзер перестроить все дочерние элементы
    }
}
void ProvToFrm::KillFocuss(wxFocusEvent& event)
{
	if((event.GetWindow())->GetId()==wxID_TO_BRAND)
	{        
    }
    event.Skip(true);
	 
}
void ProvToFrm::OnChar(wxKeyEvent& event) //обрабатываем нажатие клавиш
{
    switch(event.GetId())
    {
        case wxID_TO_INN: //запрещаем в поле с ИНН вводить символы отличные от цифр
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
        case wxID_TO_KOL_TT: //запрещаем в поле с ТТ вводить символы отличные от цифр
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
        case wxID_UL_KOL_SOTR: //запрещаем в поле с количеством сотрудников вводить символы отличные от цифр
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
        if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //если признак интернет сайта - Да, создаем два поля
        {
            
            if(!(wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) to_7->Add(new wxStaticText(this,wxID_TO_STATIC_SITE,"Интернет-сайт"),0, wxEXPAND |wxALL,5);
            if(!(wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) to_7->Add(new wxTextCtrl(this,wxID_TO_SITE_INET, wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_AUTO_URL),1, wxEXPAND |wxALL,5);
            vert->Layout(); //просим сайзеры перестроить заново всех детей
            this->Refresh(); //перерисовываем фрейм
        }
        if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==0) //если признак интернет сайта - Нет, разрушаем поля.
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
        //возможна утечка памяти из-за menuitem
        wxPoint point = event.GetPosition(); //определяем коородинаты физического положения мыши
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
        wxPoint point = event.GetPosition(); //определяем коородинаты физического положения мыши
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
        wxPoint point = event.GetPosition(); //определяем коородинаты физического положения мыши
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
        ClearForm(1); //очищаем поля формы
    }
    if (event.GetId()==wxID_BUTTON_DEL_SOTR)
	{
        DeleteProvSotrTo();
        
    }
    if (event.GetId()==wxID_BUTTON_KOM_SOTR)
	{
        CommentProvSotrTo();
    }
    if (event.GetId()==wxID_BUTTON_INS_SOTR||event.GetId()==wxID_BUTTON_UPD_SOTR) //нажата кнопка добавить/обновить проверку сотрудника ТО
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
                    ListViewProvSotr(); //перерисовываем листвьев с проверками сотрудников ТО
                }
                (this->FindWindow(wxID_BUTTON_INS_SOTR))->SetFocus();
            }
            if (type_dialog==1)
            {
                wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR)); //получаем указатель на листвьюев с проверками сотрудников то
                int count = 0;
                if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} //не выбрана ниодна строка
                for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
                {
                    wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
                    f->SetId(idItem); //устанавливаем позицию выбранного элемента
                    f->SetMask(wxLIST_MASK_DATA); //возвращаем данные связанные с элементом
                    listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
                    int idProvSotrTo=0; idProvSotrTo=f->GetData(); //пишем в переменную данные связанные с элементом
                    if(idProvSotrTo>0)
                    {
                        EnterProvSotrTo EntProvSotrTo(this, idProvSotrTo, type_dialog); 
                        if(EntProvSotrTo.ShowModal() == wxID_CANCEL) {;} else 
                        {
                            ++count; //считаем кол-во строк, который были обновлены;
                        } 
                    } else {wxMessageBox(wxWARNING_NO_DATA,wxATTENTION,wxOK,this);}
                    delete f;
                }
                if (count>0)
                {
                    ListViewProvSotr(); //перерисовываем листвьев с проверками сотрудников ТО
                    wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_UPD_COUNT; str<<count; //строим строку с кол-вом обновленных строк
                    InformationSleep(str,sec_for_sleep_window_info,this);
                    //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
                } else {;} //если не выбрана ни одна строка, то предупреждаем об этом пользователя и завершаем обработку
                (this->FindWindow(wxID_BUTTON_UPD_SOTR))->SetFocus();
                
            }
        }
    }
    if (event.GetId()==wxID_BUTTON_INS_PROV||event.GetId()==wxID_BUTTON_UPD_PROV) //нажата кнопка добавить/обновить проверку ТО
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
                    ListViewProvTo(); //перерисовываем листвьев с проверками ТО
                }
                (this->FindWindow(wxID_BUTTON_INS_PROV))->SetFocus();
            }
            if (type_dialog==1)
            {
                wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV)); //получаем указатель на листвьюев с проверками то
                int count = 0;
                if((int)listview->GetFirstSelected()==-1){InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this); return;} //не выбрана ниодна строка
                for(register int idItem = (int)listview->GetFirstSelected(); idItem!=-1; idItem = (int)listview->GetNextSelected(idItem))
                {
                    wxListItem *f = new wxListItem(); //создаем указатель на объект класса wxListItem для хранения информации об элементе класса wxListCtrl
                    f->SetId(idItem); //устанавливаем позицию выбранного элемента
                    f->SetMask(wxLIST_MASK_DATA); //возвращаем данные связанные с элементом
                    listview->GetItem(*f); //пришем в переменную информацию о выбранном элементе
                    int idProvTo=0; idProvTo=f->GetData(); //пишем в переменную данные связанные с элементом
                    if(idProvTo>0)
                    {
                        EnterProvTo EntProvTo(this, idProvTo, type_dialog);
                        if(EntProvTo.ShowModal() == wxID_CANCEL) {;} else 
                        {
                            ++count; //считаем кол-во строк, который были обновлены;
                        } 
                    } else {wxMessageBox(wxWARNING_NO_DATA,wxATTENTION,wxOK,this);}
                    delete f;
                }
                if (count>0)
                {
                    ListViewProvTo(); //перерисовываем листвьев с проверками ТО
                    wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_UPD_COUNT; str<<count; //строим строку с кол-вом обновленных строк
                    InformationSleep(str,sec_for_sleep_window_info,this);
                    //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
                } else {;} //если не выбрана ни одна строка, то предупреждаем об этом пользователя и завершаем обработку
                (this->FindWindow(wxID_BUTTON_UPD_PROV))->SetFocus();
                
            }
        }         
    }
    if (event.GetId()==wxID_BUTTON_DEL_PROV) //нажата кнопка удалить проверку ТО
	{
        DeleteProvTo();               
    }
    if (event.GetId()==wxID_BUTTON_KOM_PROV) //натажа кнопка комментарий проверки ТО
	{
        CommentProvTo();                  
    }
    if (event.GetId()==wxID_BUTTON_DEL_ASRT) //нажата кнопка удалить ассортимент
	{
        DeleteAssorti();                 
    }
    if (event.GetId()==wxID_BUTTON_INS_ASRT) //нажата кнопка добавить ассортимент
	{
        InsertAssorti();
    }
    if (event.GetId()==wxID_BUTTON_INS_TO||event.GetId()==wxID_BUTTON_UPD_TO) //нажата кнопка добавить/обновить карточку ТО
	{
        int flag_find_inn=0; //флаг того, что запись с данным инн существует. 0-не существует, 1 - существует
        wxString inn_to, name_to, brand_to, tt_to, bank_konk_to, sotr_to, flNotIp; //переменные для извлечения значений органов управления
        int type_cooper=0; //тип сотрудничества. Переменой присваивается значение выбранной строки wxChoice
        inn_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue();
        name_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->GetValue();
        if(type_cooperation->GetSelection()==4&&((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->GetValue()) //выбран контрагент и есть пометка, что он без ИНН
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
                for(register int i =0; i<MyBrandNameArray.GetCount();++i) //запускаем цикл поиска в справочнике сетей точного совпадения со значением введенным в текстовом поле
                {
                    if(!MyBrandNameArray.Item(i).nameBrandName.compare(brand_to)) //совпадение найдено
                    {        
                        //brand_to=MyBrandNameArray.Item(i).idBrandName;
                        brand_to.Clear(); brand_to<<MyBrandNameArray.Item(i).idBrandName;
                        break; //выходим из вложенного цикла поиска типа сети
                    }
                }
                if(!brand_to.IsNumber()) {wxMessageBox(wxWARNING_BRAND,wxATTENTION,wxOK|wxCENTRE|wxICON_WARNING,this); return;}
                type_cooper=0;
                break;
            }
            case 1: //зп
            {
                sotr_to=((wxTextCtrl*)(this->FindWindow(wxID_UL_KOL_SOTR)))->GetValue();
                if ((int)sotr_to.Len()==0) {sotr_to=wxSOTR_DEFAULT; ((wxTextCtrl*)(this->FindWindow(wxID_UL_KOL_SOTR)))->ChangeValue(wxSOTR_DEFAULT);}
                type_cooper=1;
                break;
            }
            case 2: //интернет-эквайринг
            {
                type_cooper=2;
                break;
            }
            case 3: //малый бизнес
            {
                type_cooper=3;
                break;
            }
            case 4: //контрагент
            {
                if(((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->GetValue())
                {flNotIp = "1"; } else {flNotIp =wxSQL_DEFAULT; }
                type_cooper=4;
                break;
            }
            case 5: //РКО
            {
                type_cooper=5;
                break;
            }
            case 6: //ТО по приему платежей
            {
                type_cooper=6;
                break;
            }
            default:break;
        }
        if(((CrossFrm*)this->GetParent())->flag_bl_sb) {if(proverka_bl_sb(conn, inn_to, 0)==1) {;} else {return;}} //если флаг проверки по ЧС СБ =1, то запускаем функцию проверки наличия совпадений в ЧС СБ
        if(event.GetId()==wxID_BUTTON_INS_TO)
        {
            //если выбран контрагент с признаком НЕ резидент или фл БЕЗ инн, то не проверяем ИНН
            if(type_cooper==4&&((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->GetValue()) {}
            else
            {
                //проверяем ИНН по базе на предмет наличия совпадения
                wxString sqlText; sqlText<<wxSqlTextFindInnTo;
                sqlText<<inn_to; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}
                else
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
                        InformationSleep (wxINFO_INN_2, sec_for_sleep_window_info, this); //выводим информационное сообщение о выявленном совпадении
                        if(wxMessageBox(wxQUESTION_FIND_INN,wxATTENTION,wxYES_NO,this)==wxYES) //отправляем пользователю запрос на изменение найденной записи
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            id_to = wxAtoi(row[0]); //присваиваем переменной класса значение айди найденной то
                            flag_find_inn=1;
                        } else {mysql_free_result(res); return;}
                    }
                    else {if(mysql_field_count(conn) == 0) {flag_find_inn=0;}}
                    mysql_free_result(res); // Очищаем результаты
                }
            }
        
        if(flag_find_inn==1) //если код ТО существует
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
                    if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //если признак интернет сайта - Да
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
                    //wxMessageBox(sqlText,"Внимание",wxOK,this);
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
        if(flag_find_inn==0) //если код ТО не существует
        {
            wxString site, sqlText;
            switch (type_cooper)
            {
                case 0:
                {
                    sqlText=wxSqlTextInsertTo_1;
                    if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //если признак интернет сайта - Да
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
                    if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //если признак интернет сайта - Да
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
                    //wxMessageBox(sqlText,"Внимание",wxOK,this);
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
            mysql_query (conn,"SET character_set_client='utf8'");  /*устанавливает кодировку данных отправляемых ОТ клиента*/
            if (mysql_query(conn, sqlText.utf8_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
            else
            {
                //запрос к БД, чтобы получить id_reestr_to
                wxString sqlTextId=wxSqlTextFindInnTo;
                if(type_cooperation->GetSelection()==4&&((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->GetValue()) //выбран контрагент и есть пометка, что он без ИНН
                {
                    //на случай когда контрагент без ИНН
                    sqlTextId<<"1"; sqlTextId<<wxSqlTextUpdToNameto; sqlTextId<<name_to; sqlTextId<<wxSqlCharStr; sqlTextId<<wxSqlEndText;
                }
                else
                {
                    //на все остальные случаи
                    sqlTextId<<inn_to; sqlTextId<<wxSqlEndText;
                }
                if (mysql_query(conn, sqlTextId.utf8_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;} 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        id_to = wxAtoi(row[0]); //присваиваем переменной класса значение айди найденной то
                        flag_find_inn=1;
                    }
                    else {;}
                    InformationSleep(wxID_SUCCESS_OPERATION,sec_for_sleep_window_info,this);
                    mysql_free_result(res); // Очищаем результаты
                }                
            }
            mysql_query (conn,"SET character_set_client='cp1251'");  /*устанавливает кодировку данных отправляемых ОТ клиента*/                   
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
                    if(((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->GetSelection()==1) //если признак интернет сайта - Да
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
    if (event.GetId()==wxID_BUTTON_DEL_TO) //нажата кнопка удалить карточку ТО
	{
        DeleteCardTo();
        ClearForm(1);
    }
    if (event.GetId()==wxID_BUTTON_INN_TO) //нажата кнопка проверить ИНН
	{
        ProvInnTo();
    }
    if (event.GetId()==wxID_BUTTON_SP_SOTR) //нажата кнопка список проверок сотрудников
	{
        if(((wxToggleButton*)this->FindWindow(wxID_BUTTON_SP_SOTR))->GetValue())      //нажата кнопка
        {        
            ListViewProvSotr(); //создаем/перерисовываем листвьев со списком проверок сотрудников
        }
        else                                                                            //не нажата кнопка 
            {
                
                if(to_static_box5->GetItemCount()>0)
                {
                    (this->FindWindow(wxID_LISTVIEW_SOTR))->Destroy();     //разрушаем листвиев
                    (this->FindWindow(wxID_BUTTON_INS_SOTR))->Destroy();   //разрушаем кнопку
                    (this->FindWindow(wxID_BUTTON_UPD_SOTR))->Destroy();   //разрушаем кнопку
                    (this->FindWindow(wxID_BUTTON_DEL_SOTR))->Destroy();   //разрушаем кнопку
                    (this->FindWindow(wxID_BUTTON_KOM_SOTR))->Destroy();   //разрушаем кнопку
                    to_static_box5->Detach(vr5);                           //отсоединяем статический сайзер
                    vert->Detach(to_static_box5);                           //отсоединяем статический сайзер
                    delete vr5;                                          //освобождаем память выделенную под сайзер
                    delete stBox5;                                          //освобождаем память выделенную под статическое окно
                    delete to_static_box5;                                  //освобождаем память выделенную под сайзер со статическим окном
                    //this->SetStatusText("",1);
                    vert->Layout();                                         //просим основной сайзер перестроить всех детей
                }
            }
        }
    if (event.GetId()==wxID_BUTTON_SP_PROV) //нажата кнопка список проверок ТО
	   {
            if(((wxToggleButton*)this->FindWindow(wxID_BUTTON_SP_PROV))->GetValue())      //нажата кнопка
            {
                ListViewProvTo(); //создаем/перерисовываем листвьев со списком проверок ТО
            }
            else                                                                            //не нажата кнопка 
            {
                
                if(to_static_box4->GetItemCount()>0)
                {
                    (this->FindWindow(wxID_LISTVIEW_PROV))->Destroy();     //разрушаем листвиев
                    (this->FindWindow(wxID_BUTTON_INS_PROV))->Destroy();   //разрушаем кнопку
                    (this->FindWindow(wxID_BUTTON_UPD_PROV))->Destroy();   //разрушаем кнопку
                    (this->FindWindow(wxID_BUTTON_DEL_PROV))->Destroy();   //разрушаем кнопку
                    (this->FindWindow(wxID_BUTTON_KOM_PROV))->Destroy();   //разрушаем кнопку
                    to_static_box4->Detach(vr4);                           //отсоединяем статический сайзер
                    vert->Detach(to_static_box4);                           //отсоединяем статический сайзер
                    delete stBox4;                                          //освобождаем память выделенную под статическое окно
                    delete to_static_box4;                                  //освобождаем память выделенную под сайзер со статическим окном
                    //this->SetStatusText("",0);
                    vert->Layout();                                         //просим основной сайзер перестроить всех детей
                }
            }
        }
    if (event.GetId()==wxID_BUTTON_SP_ASRT) //нажата кнопка список ассортимента
	   {
            if(((wxToggleButton*)this->FindWindow(wxID_BUTTON_SP_ASRT))->GetValue())      //нажата кнопка
            {
                ListViewAssortiment(); //создаем/перерисовываем листвьев со списком ассортимента
            }
            else                                                                            //не нажата кнопка            
            {
                
                if(to_static_box3->GetItemCount()>0)
                {
                    (this->FindWindow(wxID_LISTVIEW_ASRT))->Destroy();     //разрушаем листвиев
                    (this->FindWindow(wxID_BUTTON_INS_ASRT))->Destroy();   //разрушаем кнопку
                    (this->FindWindow(wxID_BUTTON_DEL_ASRT))->Destroy();   //разрушаем кнопку
                    to_static_box3->Detach(vr3);                           //отсоединяем статический сайзер
                    vert->Detach(to_static_box3);                           //отсоединяем статический сайзер
                    delete stBox3;                                          //освобождаем память выделенную под статическое окно
                    delete to_static_box3;                                  //освобождаем память выделенную под сайзер со статическим окном
                    //this->SetStatusText("",2);
                    vert->Layout();                                         //просим основной сайзер перестроить всех детей
                } 
            }                                                    
        }
    if (event.GetId()==wxID_BUTTON_KT_KONTRACT) //нажата кнопка список проверок ТО
	   {
            if(((wxToggleButton*)this->FindWindow(wxID_BUTTON_KT_KONTRACT))->GetValue())      //нажата кнопка
            {
                ListViewKontract(); //создаем/перерисовываем листвьев со списком контрактов
            }
            else                                                                            //не нажата кнопка 
            {
                
                if(to_static_box6->GetItemCount()>0)
                {
                    (this->FindWindow(wxID_LISTVIEW_KONTRACT))->Destroy();     //разрушаем листвиев
                    //to_static_box6->Detach(vr6);                           //отсоединяем статический сайзер
                    vert->Detach(to_static_box6);                           //отсоединяем статический сайзер
                    delete stBox6;                                          //освобождаем память выделенную под статическое окно
                    delete to_static_box6;                                  //освобождаем память выделенную под сайзер со статическим окном
                    //this->SetStatusText("",0);
                    vert->Layout();                                         //просим основной сайзер перестроить всех детей
                }
            }
        }
    }
}

void ProvToFrm::ClearForm (int flag) //если флаг =0, то очищаются все поля за исключением ИНН. Если флаг >0 очищается и поле с ИНН
{
    if(flag>0) { ((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->Clear();}
    id_to=0; //стираем айди то
    count_assorti=0; 
    count_to_prov=0; 
    count_sotr_prov=0;
    switch (type_cooperation->GetSelection())
    {
        case 0: //pos
        {
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->Clear(); //очищаем наименование ТО
            ((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(wxBRAND_DEFAULT); //устанавливаем значение по умолчанию сети 
            ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->Clear(); //SetLabelText(wxBRAND_DEFAULT); //устанавливаем значение по умолчанию типа сети
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_KOL_TT)))->Clear(); //очищаем кол-во ТТ
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_BANK_KONK)))->Clear(); //очищаем банки-конкуренты
            ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->SetSelection(0); //выбираем признак интернет магазина - нет
            if((wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) {(wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))->Destroy();} //если существует, разрушаем надпись - интернет-магазин
            if((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) {(wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))->Destroy();} //если существует, разрушеам поле с интернет-сайтом
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_ASRT))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->DeleteAllItems();}
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();} 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();}
            if((wxCheckBox*)(this->FindWindow(wxID_TO_CHECKBOX_FL_IP))) {((wxCheckBox*)(this->FindWindow(wxID_TO_CHECKBOX_FL_IP)))->SetValue(false);} //если существует, снимаем галку в чек-боксе
            break;
        }
        case 1: //зп проект
        {
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->Clear(); //очищаем наименование ТО
            ((wxTextCtrl*)(this->FindWindow(wxID_UL_KOL_SOTR)))->Clear(); //очищаем наименование ТО
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();} 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();}
            break;
        }
        case 2: //интернет-эквайринг
        {
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->Clear(); //очищаем наименование ТО
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->Clear(); //очищаем 
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_EK_SITE_INET)))->Clear(); //очищаем 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();} 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();}
            break;
        }
        case 3: //малый бизнес
        case 5: //РКО
        case 6: //ТО по приему платежей
        case 4: //контрагент
        {
            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->Clear(); //очищаем наименование ТО
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();} 
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR))->DeleteAllItems();}
            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_KONTRACT))) {((wxListView*)this->FindWindow(wxID_LISTVIEW_KONTRACT))->DeleteAllItems();}
            break;
        }
        default:break;
    }
    wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
    grandParentWindow->WorkStatusBar();
    //this->SetStatusText(wxREADDY_,0); this->SetStatusText(wxNULL_STRING,1); this->SetStatusText(wxNULL_STRING,2);
    vert->Layout(); //просим сайзеры перестроить заново всех детей
    this->Refresh(); //перерисовываем фрейм   
}
void ProvToFrm::ListViewProvSotr (void)
{
    ((wxToggleButton*)(this->FindWindow(wxID_BUTTON_SP_SOTR)))->SetValue(true);
    if(!(wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) //окно со списком не открыто
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
            (this->FindWindow(wxID_BUTTON_INS_SOTR))->SetToolTip("Добавить строку");
            (this->FindWindow(wxID_BUTTON_UPD_SOTR))->SetToolTip("Обновить строку");
            (this->FindWindow(wxID_BUTTON_DEL_SOTR))->SetToolTip("Удалить строку");
            (this->FindWindow(wxID_BUTTON_KOM_SOTR))->SetToolTip("Прочитать комментарий");
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
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
                        for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[5])); //прячем уникальный айди
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields; l++)
                            {
                                if (l==0) {listview->SetItem(i,l,row[l]);}
                                if (l==1) 
                                {
                                    for(register int k =0; k<MyDolznostArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyDolznostArray.Item(k).idDolznost.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyDolznostArray.Item(k).idDolznost==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyDolznostArray.Item(k).nameDolznost);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==2) //паспорт 
                                {
                                    wxString str; str<<row[3]; str<<" "; str<<row[2]; //соединеям номер и серию в одной переменной
                                    listview->SetItem(i,2,str);
                                }
                                if (l==4) 
                                {
                                    for(register int k =0; k<MyGcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,3,MyGcArray.Item(k).nameGc);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==6) 
                                {
                                    for(register int k =0; k<MyUkRfArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,4,MyUkRfArray.Item(k).nameUkRf);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==7) 
                                {
                                    for(register int k =0; k<MyRezProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,5,MyRezProvArray.Item(k).nameRezProv);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==8) 
                                {
                                    for(register int k =0; k<MyFioSbArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,6,MyFioSbArray.Item(k).nameFioSb);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==9) {listview->SetItem(i,7,row[l]);}
                                if (l==10) 
                                {
                                    if(atoi(row[l])==0) //запись не в архиве
                                    {
                                        listview->SetItem(i,8,"ДА");
                                    }
                                    else                //запись в архиве
                                    {
                                        listview->SetItem(i,8,"НЕТ");
                                    }
                                }
                            }
                            delete f;
                        }
                    for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                    //wxString status = wxCOUNT_PROV_SOTR; 
                    count_sotr_prov=num_rows;
                    //this->SetStatusText(status,1);
                    wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // Очищаем результаты
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
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
                        for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[5])); //прячем уникальный айди
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields; l++)
                            {
                                if (l==0) {listview->SetItem(i,l,row[l]);}
                                if (l==1) 
                                {
                                    for(register int k =0; k<MyDolznostArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyDolznostArray.Item(k).idDolznost.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyDolznostArray.Item(k).idDolznost==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyDolznostArray.Item(k).nameDolznost);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==2) //паспорт 
                                {
                                    wxString str; str<<row[3]; str<<" "; str<<row[2]; //соединеям номер и серию в одной переменной
                                    listview->SetItem(i,2,str);
                                }
                                if (l==4) 
                                {
                                    for(register int k =0; k<MyGcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,3,MyGcArray.Item(k).nameGc);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==6) 
                                {
                                    for(register int k =0; k<MyUkRfArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,4,MyUkRfArray.Item(k).nameUkRf);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==7) 
                                {
                                    for(register int k =0; k<MyRezProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,5,MyRezProvArray.Item(k).nameRezProv);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==8) 
                                {
                                    for(register int k =0; k<MyFioSbArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,6,MyFioSbArray.Item(k).nameFioSb);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==9) {listview->SetItem(i,7,row[l]);}
                                if (l==10) 
                                {
                                    if(atoi(row[l])==0) //запись не в архиве
                                    {
                                        listview->SetItem(i,8,"ДА");
                                    }
                                    else                //запись в архиве
                                    {
                                        listview->SetItem(i,8,"НЕТ");
                                    }
                                }
                            }
                            delete f;
                        }
                    for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                    //wxString status = wxCOUNT_PROV_SOTR; 
                    count_sotr_prov=num_rows;
                    //this->SetStatusText(status,1);
                    wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // Очищаем результаты
                }
            }
    }
}

void ProvToFrm::ListViewKontract (void){
    ((wxToggleButton*)(this->FindWindow(wxID_BUTTON_KT_KONTRACT)))->SetValue(true);
    
    if(!(wxListView*)(this->FindWindow(wxID_LISTVIEW_KONTRACT))) //окно со списком не открыто
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
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
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
                                if (l==1||l==2||l==3) { if(row[l]) { listview->SetItem(i,l-1,row[l]); } }
                                if (l==4) {
                                    if(row[l]){
                                    wxString temp_1 = row[l]; //строка содержащая цену договора и подлажащая форматированию
                                    wxString temp_2;            //отформатированная строка
                                    
                                    /*
                                    first - начало обрезаемой строки
                                    last - конец обрезаемой строки
                                    i - шаг итерации;
                                    temp_1.Len()%3==0 ? 3: temp_1.Len()%3   - если первые цифры не кратны 3-м, то присваиваем в качестве конца первой обрезаемой строки остаток от деления по модулю
                                    */
                                    for(int first = 0, i = (temp_1.Len()%3==0 ? 3: temp_1.Len()%3), last = i; i<temp_1.Len(); i+=3) {
                                        temp_2.Append(temp_1.Mid(first,last));  //добавляем обрезанный кусок
                                        temp_2.Append(" ");                     //добавляем пробел (разделитель)
                                        first=i; last=3;                        //меряем начало и конец следующего обрезаемого куска
                                        if((i+3)>=temp_1.Len()) {temp_2.Append(temp_1.Mid(first,3)); temp_2.Append(" р.");} //если на следующем шаге будет достигнут конец строки, то вставляем последний отрезок и добавляем в конце символ валюты РФ
                                    }
                                    listview->SetItem(i,l-1,temp_2);
                                    } else {
                                    listview->SetItem(i,l-1,"");}
                                }
                                
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                        //wxString status = wxCOUNT_PROV_TO; 
                        //count_to_prov=num_rows;
                        //this->SetStatusText(status,0);
                        //wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
                        //wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
                        //grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // Очищаем результаты
                }  
            }
        }
    }
    else //окно со списком открыто
    {
        ((wxListView*)this->FindWindow(wxID_LISTVIEW_KONTRACT))->DeleteAllItems();
        {
                wxString sqlText; sqlText<<wxSqlTextSelAllContKontr;
                sqlText<<id_to; sqlText<<wxSqlEndTextOrderAsc3;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else
                {
                    wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_KONTRACT));
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
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
                                if (l==1||l==2||l==3||l==4) { if(row[l]) { listview->SetItem(i,l-1,row[l] ? row[l] : ""); } }
                                if (l==4) {
                                    if(row[l]){
                                    wxString temp_1 = row[l]; //строка содержащая цену договора и подлажащая форматированию
                                    wxString temp_2;            //отформатированная строка
                                    
                                    /*
                                    first - начало обрезаемой строки
                                    last - конец обрезаемой строки
                                    i - шаг итерации;
                                    temp_1.Len()%3==0 ? 3: temp_1.Len()%3   - если первые цифры не кратны 3-м, то присваиваем в качестве конца первой обрезаемой строки остаток от деления по модулю
                                    */
                                    for(int first = 0, i = (temp_1.Len()%3==0 ? 3: temp_1.Len()%3), last = i; i<temp_1.Len(); i+=3) {
                                        temp_2.Append(temp_1.Mid(first,last));  //добавляем обрезанный кусок
                                        temp_2.Append(" ");                     //добавляем пробел (разделитель)
                                        first=i; last=3;                        //меряем начало и конец следующего обрезаемого куска
                                        if((i+3)>=temp_1.Len()) {temp_2.Append(temp_1.Mid(first,3)); temp_2.Append(" р.");} //если на следующем шаге будет достигнут конец строки, то вставляем последний отрезок и добавляем в конце символ валюты РФ
                                    }
                                    listview->SetItem(i,l-1,temp_2);
                                    } else {
                                    listview->SetItem(i,l-1,"");}
                                }
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                        //wxString status = wxCOUNT_PROV_TO; 
                        //count_to_prov=num_rows;
                        //this->SetStatusText(status,0);
                        //wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
                        //wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
                        //grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // Очищаем результаты
                }  
            }
    }
}
void ProvToFrm::ListViewProvTo (void)
{
    ((wxToggleButton*)(this->FindWindow(wxID_BUTTON_SP_PROV)))->SetValue(true);
    if(!(wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) //окно со списком не открыто
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
            (this->FindWindow(wxID_BUTTON_INS_PROV))->SetToolTip("Добавить строку");
            (this->FindWindow(wxID_BUTTON_UPD_PROV))->SetToolTip("Обновить строку");
            (this->FindWindow(wxID_BUTTON_DEL_PROV))->SetToolTip("Удалить строку");
            (this->FindWindow(wxID_BUTTON_KOM_PROV))->SetToolTip("Прочитать комментарий");
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
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
                        for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(wxAtoi(row[8])); //прячем уникальный айди
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                if (l==0) 
                                {
                                    for(register int k =0; k<MyTypeCooperationArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyTypeCooperationArray.Item(k).idTypeCooperation.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyTypeCooperationArray.Item(k).idTypeCooperation==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyTypeCooperationArray.Item(k).nameTypeCooperation);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==1) 
                                {
                                    for(register int k =0; k<MyTypeProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyTypeProvArray.Item(k).idTypeProv.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyTypeProvArray.Item(k).idTypeProv==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyTypeProvArray.Item(k).nameTypeProv);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==2) 
                                {
                                    for(register int k =0; k<MyOcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyOcArray.Item(k).idOc.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyOcArray.Item(k).idOc==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyOcArray.Item(k).nameOc);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==3) 
                                {
                                    for(register int k =0; k<MyGcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //совпадение найдено
                                        {   
                                            listview->SetItem(i,l,MyGcArray.Item(k).nameGc);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==4) 
                                {
                                    for(register int k =0; k<MyUkRfArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyUkRfArray.Item(k).nameUkRf);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==5) 
                                {
                                    for(register int k =0; k<MyRezProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyRezProvArray.Item(k).nameRezProv);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==6) 
                                {
                                    for(register int k =0; k<MyFioSbArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyFioSbArray.Item(k).nameFioSb);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==7) {listview->SetItem(i,l,row[l]);}
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                        //wxString status = wxCOUNT_PROV_TO; 
                        count_to_prov=num_rows;
                        //this->SetStatusText(status,0);
                        wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // Очищаем результаты
                }  
            }
            delete image; delete image1; delete image2; delete image3;
        }
    }
    else //окно со списком открыто
    {
        ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV))->DeleteAllItems();
        {
                wxString sqlText; sqlText<<wxSqlTextProvTo;
                sqlText<<id_to; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
                else
                {
                    wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV));
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {   
                        for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(atoi(row[8])); //прячем уникальный айди
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                if (l==0) 
                                {
                                    for(register int k =0; k<MyTypeCooperationArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyTypeCooperationArray.Item(k).idTypeCooperation.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyTypeCooperationArray.Item(k).idTypeCooperation==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyTypeCooperationArray.Item(k).nameTypeCooperation);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==1) 
                                {
                                    for(register int k =0; k<MyTypeProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyTypeProvArray.Item(k).idTypeProv.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyTypeProvArray.Item(k).idTypeProv==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyTypeProvArray.Item(k).nameTypeProv);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==2) 
                                {
                                    for(register int k =0; k<MyOcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyOcArray.Item(k).idOc.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyOcArray.Item(k).idOc==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyOcArray.Item(k).nameOc);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==3) 
                                {
                                    for(register int k =0; k<MyGcArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyGcArray.Item(k).idGc.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyGcArray.Item(k).idGc==wxAtoi(row[l])) //совпадение найдено
                                        {   
                                            listview->SetItem(i,l,MyGcArray.Item(k).nameGc);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==4) 
                                {
                                    for(register int k =0; k<MyUkRfArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyUkRfArray.Item(k).idUkRf.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyUkRfArray.Item(k).idUkRf==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyUkRfArray.Item(k).nameUkRf);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==5) 
                                {
                                    for(register int k =0; k<MyRezProvArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyRezProvArray.Item(k).idRezProv.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyRezProvArray.Item(k).idRezProv==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyRezProvArray.Item(k).nameRezProv);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==6) 
                                {
                                    for(register int k =0; k<MyFioSbArray.GetCount();++k) //запускаем цикл поиска в справочнике 
                                    {
                                        //if(atoi(MyFioSbArray.Item(k).idFioSb.c_str())==atoi(row[l])) //совпадение найдено
                                        if(MyFioSbArray.Item(k).idFioSb==wxAtoi(row[l])) //совпадение найдено
                                        {
                                            listview->SetItem(i,l,MyFioSbArray.Item(k).nameFioSb);
                                            break; //выходим из вложенного цикла
                                        }
                                    }
                                }
                                if (l==7) {listview->SetItem(i,l,row[l]);}
                            }
                            delete f;
                        }
                        for (register int i=0; i<(listview->GetColumnCount());++i) {listview->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента
                        //wxString status = wxCOUNT_PROV_TO; 
                        count_to_prov=num_rows;
                        //this->SetStatusText(status,0);
                        wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // Очищаем результаты
                }  
            }
    }
}
void ProvToFrm::ListViewAssortiment (void)
{
    if(!(wxListView*)(this->FindWindow(wxID_LISTVIEW_ASRT))) //окно со списком не открыто
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
        (this->FindWindow(wxID_BUTTON_INS_ASRT))->SetToolTip("Добавить строку");
        (this->FindWindow(wxID_BUTTON_DEL_ASRT))->SetToolTip("Удалить строку");
        (this->FindWindow(wxID_BUTTON_INS_ASRT))->SetBackgroundColour(*wxWHITE);
        (this->FindWindow(wxID_BUTTON_DEL_ASRT))->SetBackgroundColour(*wxWHITE);
        {
            if(!((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->IsEmpty())
            {
                wxString inn_to = ((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue();
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
                        for (register int i = 0; i < num_rows; i++) // Вывод таблицы
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            wxListItem *f = new wxListItem();
                            f->SetState(wxLIST_STATE_FOCUSED);
                            f->SetMask(wxLIST_MASK_TEXT);
                            f->SetColumn(0);
                            f->SetData(wxAtoi(row[2])); //прячем уникальный айди
                            f->SetId(i);
                            listview->InsertItem(*f); 
                            for (register int l = 0; l < num_fields-1; l++)
                            {
                                wxString str; str<<row[l];
                                listview->SetItem(i,l,str);
                            }
                            delete f;
                        }
                        listview->SetColumnWidth(0,wxLIST_AUTOSIZE); //изменяем размер столбца по длине самого большого элемента
                        listview->SetColumnWidth(1,wxLIST_AUTOSIZE); //изменяем размер столбца по длине самого большого элемента
                        //wxString status = wxCOUNT_ASSORTI; 
                        count_assorti=num_rows;
                        //this->SetStatusText(status,2);
                        wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
    grandParentWindow->WorkStatusBar();
                    } else {;}
                    mysql_free_result(res); // Очищаем результаты
                }
            }}
            delete image; delete image1;
        }}
    }
    else                    //окно со списком открыто
    {
        ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->DeleteAllItems();
        {
            wxString sqlText; sqlText<<wxSqlTextAssortiTo;
            sqlText<<((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue(); sqlText<<wxSqlEndText;
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
                        wxListItem *f = new wxListItem();
                        f->SetState(wxLIST_STATE_FOCUSED);
                        f->SetMask(wxLIST_MASK_TEXT);
                        f->SetColumn(0); //первая колонка
                        f->SetData(atoi(row[2])); //прячем уникальный айди
                        f->SetId(i); //присваиваем номер строки
                        ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->InsertItem(*f); 
                        for (register int l = 0; l < num_fields-1; l++)
                        {
                            wxString str; str<<row[l];
                            ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->SetItem(i,l,str); //пишем значение элемента в каждый столбец
                        }
                        delete f;
                    }
                    ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->SetColumnWidth(0,wxLIST_AUTOSIZE); //изменяем размер столбца по длине самого большого элемента
                    ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT))->SetColumnWidth(1,wxLIST_AUTOSIZE); //изменяем размер столбца по длине самого большого элемента
                    //wxString status = wxCOUNT_ASSORTI; 
                    count_assorti=num_rows;
                    //this->SetStatusText(status,2);
                    wxAuiNotebook *parentWindow = (wxAuiNotebook*)this->GetParent(); //присваиваем переменной указатель на родительское окно
    wxAuiWorkPanel *grandParentWindow = (wxAuiWorkPanel*)parentWindow->GetParent(); //присваиваем переменной указатель на родительское окно
    grandParentWindow->WorkStatusBar();
                } else {;}
                mysql_free_result(res); // Очищаем результаты
            }
        }
    } 
}

void ProvToFrm::DeleteAssorti (void)
{
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_ASRT)); //получаем указатель на листвьюев с ассортиментом
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
                wxString idAssirti; idAssirti<<f->GetData(); //пишем в переменную данные связанные с элементом
                if(!idAssirti.IsEmpty())
                {
                    wxString sqlText = wxSqlTextDelAssorti; sqlText<<idAssirti; sqlText<<wxSqlEndText;
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
                ListViewAssortiment(); //перерисовываем листвьев с ассортиментом
                wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_DEL_COUNT; str<<count; //строим строку с кол-вом удаленных строк
                InformationSleep(str,sec_for_sleep_window_info,this);
            } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);} //если не выбрана ни одна строка, то предупреждаем об этом пользователя и завершаем обработку
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
        ClearForm(); //очищаем поля формы
        wxString inn_to=((wxTextCtrl*)(this->FindWindow(wxID_TO_INN)))->GetValue();
        if((type_cooperation->GetSelection())==4) //выбран контрагент и есть пометка, что он без ИНН
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
                    MYSQL_RES *res = mysql_store_result(::conn); // Берем результат,
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0) //проверяем наличие строк после SELECT. 
                    {
                        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                        id_to=wxAtoi(row[0]); //присваиваем члену айди то
                        ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //вставляем в контрол наименование то
                        for(register int i =0; i<MyBrandNameArray.GetCount();++i) //запускаем цикл поиска в справочнике типов сетей точного совпадения со значением введенным в текстовом поле
                        {
                            //if(!(MyBrandNameArray.Item(i).idBrandName).compare(row[2])) //совпадение найдено
                            if(MyBrandNameArray.Item(i).idBrandName==wxAtoi(row[2])) //совпадение найдено
                            {
                                ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->ChangeValue(MyBrandNameArray.Item(i).nameBrandName); //выводим в поле наименование сети
                                for(register int j =0; j<MyBrandTypeArray.GetCount();++j) //запускаем цикл поиска в справочнике типов сетей типа сети соответствующего найденному значению
                                {
                                    //if(!MyBrandNameArray.Item(i).idBrandType.compare(MyBrandTypeArray.Item(j).idBrandType)) //совпадение найдено
                                    if(MyBrandNameArray.Item(i).idBrandType==MyBrandTypeArray.Item(j).idBrandType) //совпадение найдено
                                    {
                        
                                        ((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(MyBrandTypeArray.Item(j).nameBrandType); //выводим в статическое поле тип сети
                                        break; //выходим из вложенного цикла поиска типа сети
                                    }
                                }
                                break; //выходим из вложенного цикла поиска совпадения по наименованию сети
                            } else {((wxStaticText*)this->FindWindow(wxID_TO_TYPE_BRAND))->SetLabelText(wxBRAND_DEFAULT); ((wxTextCtrl*)this->FindWindow(wxID_TO_BRAND))->SetLabelText(wxBRAND_DEFAULT);}
                        }
                        if(row[3]) {((wxTextCtrl*)this->FindWindow(wxID_TO_KOL_TT))->SetLabelText(row[3]);} else {((wxTextCtrl*)this->FindWindow(wxID_TO_KOL_TT))->SetLabelText(wxTT_DEFAULT);}
                        if(row[4]) {((wxTextCtrl*)this->FindWindow(wxID_TO_BANK_KONK))->SetLabelText(row[4]);} else {((wxTextCtrl*)this->FindWindow(wxID_TO_BANK_KONK))->SetLabelText(wxNOT_DEFAULT);}
                        if(row[5])
                        {
                            wxString inetFlag = row[5];
                            if(inetFlag.compare("0")==0)
                            {
                                ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->SetSelection(0); //выбираем признак интернет магазина - нет
                                if((wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) (wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))->Destroy(); //если существует, разрушаем надпись - интернет-магазин
                                if((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) (wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))->Destroy(); //если существует, разрушеам поле с интернет-сайтом
                            }
                            if(inetFlag.compare("1")==0)
                            {
                                ((wxComboBox*)this->FindWindow(wxID_TO_FLAG_INET))->SetSelection(1); //выбираем признак интернет магазина - да
                                if(row[6])
                                {
                                    if(!(wxStaticText*)(this->FindWindow(wxID_TO_STATIC_SITE))) to_7->Add(new wxStaticText(this,wxID_TO_STATIC_SITE,"Интернет-сайт"),0, wxEXPAND |wxALL,5);
                                    if(!(wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET))) to_7->Add(new wxTextCtrl(this,wxID_TO_SITE_INET, wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_AUTO_URL),1, wxEXPAND |wxALL,5);
                                    ((wxTextCtrl*)this->FindWindow(wxID_TO_SITE_INET))->ChangeValue(row[6]);                              
                                }
                            }
                        }
                        if((wxListView*)(this->FindWindow(wxID_LISTVIEW_ASRT))) {ListViewAssortiment();}
                        if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                        if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                        vert->Layout(); //просим сайзеры перестроить заново всех детей
                        this->Refresh(); //перерисовываем фрейм      
                    }
                    else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                    mysql_free_result(res); // Очищаем результаты
                }
                break;
                }
                case 1: //зп проект
                {
                    sqlText<<wxSqlTextProvInn1; sqlText<<inn_to; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(::conn); // Берем результат,
                        int num_fields = mysql_num_fields(res); // количество полей
                        int num_rows = mysql_num_rows(res); // и количество строк.
                        if(num_rows>0) //проверяем наличие строк после SELECT. 
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            id_to=wxAtoi(row[0]); //присваиваем члену айди то
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //вставляем в контрол наименование то
                            if(row[2]) {((wxTextCtrl*)this->FindWindow(wxID_UL_KOL_SOTR))->SetLabelText(row[2]);} else {((wxTextCtrl*)this->FindWindow(wxID_UL_KOL_SOTR))->SetLabelText(wxSOTR_DEFAULT);}

                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                            vert->Layout(); //просим сайзеры перестроить заново всех детей
                            this->Refresh(); //перерисовываем фрейм      
                        }
                        else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // Очищаем результаты
                    }
                    break;
                }
                case 2: //интернет-эквайринг
                {
                    sqlText<<wxSqlTextProvInn2; sqlText<<inn_to; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(::conn); // Берем результат,
                        int num_fields = mysql_num_fields(res); // количество полей
                        int num_rows = mysql_num_rows(res); // и количество строк.
                        if(num_rows>0) //проверяем наличие строк после SELECT. 
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            id_to=wxAtoi(row[0]); //присваиваем члену айди то
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //вставляем в контрол наименование то
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_SITE_INET)))->ChangeValue(wxString(row[2])); //вставляем в контрол наименование то
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_EK_SITE_INET)))->ChangeValue(wxString(row[3])); //вставляем в контрол наименование то
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                            vert->Layout(); //просим сайзеры перестроить заново всех детей
                            this->Refresh(); //перерисовываем фрейм      
                        }
                        else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // Очищаем результаты
                    }
                    break;
                }
                case 3: //малый бизнес
                case 5: //РКО
                case 6: //ТО по приему платежей
                {
                    sqlText<<wxSqlTextProvInn2; sqlText<<inn_to; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(::conn); // Берем результат,
                        int num_fields = mysql_num_fields(res); // количество полей
                        int num_rows = mysql_num_rows(res); // и количество строк.
                        if(num_rows>0) //проверяем наличие строк после SELECT. 
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            id_to=wxAtoi(row[0]); //присваиваем члену айди то
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //вставляем в контрол наименование то
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                            vert->Layout(); //просим сайзеры перестроить заново всех детей
                            this->Refresh(); //перерисовываем фрейм      
                        }
                        else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // Очищаем результаты
                    }
                    break;
                }
                case 4: //контрагент
                {
                    if(inn_to.IsEmpty()) {InformationSleep(wxWARNING_INN,sec_for_sleep_window_info, this); break;}
                    sqlText<<wxSqlTextProvInn3; sqlText<<inn_to; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn));}
                    else
                    {
                        MYSQL_RES *res = mysql_store_result(::conn); // Берем результат,
                        int num_fields = mysql_num_fields(res); // количество полей
                        int num_rows = mysql_num_rows(res); // и количество строк.
                        if(num_rows>0) //проверяем наличие строк после SELECT. 
                        {
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            id_to=wxAtoi(row[0]); //присваиваем члену айди то
                            ((wxTextCtrl*)(this->FindWindow(wxID_TO_NAME)))->ChangeValue(wxString(row[1])); //вставляем в контрол наименование то
                            wxString flag_fl_not_ip = row[2]; //получаем признак того, что физик не является ип
                            if(!flag_fl_not_ip.IsEmpty()) {((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(true);} else {((wxCheckBox*)this->FindWindow(wxID_TO_CHECKBOX_FL_IP))->SetValue(false);}//если переменная не пуста, то ставим галку в чекбоксе и наоборот
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_PROV))) {ListViewProvTo();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_SOTR))) {ListViewProvSotr();}
                            if((wxListView*)(this->FindWindow(wxID_LISTVIEW_KONTRACT))) {ListViewKontract();}
                            vert->Layout(); //просим сайзеры перестроить заново всех детей
                            this->Refresh(); //перерисовываем фрейм      
                        }
                        else {InformationSleep(wxINFO_INN_1,sec_for_sleep_window_info, this);}
                        mysql_free_result(res); // Очищаем результаты
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
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV)); //получаем указатель на листвьюев с проверками ТО
        int flag = 0;
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
            wxString idProvTo; idProvTo<<f->GetData(); //пишем в переменную данные связанные с элементом
            if(!idProvTo.IsEmpty())
            {
                
                wxString sqlText = wxSqlTextSpComProvTo; sqlText<<idProvTo; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    MYSQL_ROW row = mysql_fetch_row(res); // получаем строку 
                    for (;row;row=mysql_fetch_row(res))
                    {
                        flag=1; //признак того, что комментарий найден в БД
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
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_PROV)); //получаем указатель на листвьюев с проверками то
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
                wxString idProvTo; idProvTo<<f->GetData(); //пишем в переменную данные связанные с элементом
                if(!idProvTo.IsEmpty())
                {
                    wxString sqlText = wxSqlTextDelProvTo; sqlText<<idProvTo; sqlText<<wxSqlEndText;
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
                ListViewProvTo(); //перерисовываем листвьев с ассортиментом
                wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_DEL_COUNT; str<<count; //строим строку с кол-вом удаленных строк
                InformationSleep(str,sec_for_sleep_window_info,this);
                //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
            } else {;} //если не выбрана ни одна строка, то предупреждаем об этом пользователя и завершаем обработку
            (this->FindWindow(wxID_BUTTON_DEL_PROV))->SetFocus();
        }
}

void ProvToFrm::CommentProvSotrTo (void)
    {
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR)); //получаем указатель на листвьюев с проверками ТО
        int flag = 0;
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
            wxString idProvSotrTo; idProvSotrTo<<f->GetData(); //пишем в переменную данные связанные с элементом
            if(!idProvSotrTo.IsEmpty())
            {
                
                wxString sqlText = wxSqlTextComProvSotrToStart; sqlText<<idProvSotrTo; sqlText<<wxSqlEndText;
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this);}               
                else 
                {
                    MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                    MYSQL_ROW row = mysql_fetch_row(res); // получаем строку 
                    for (;row;row=mysql_fetch_row(res))
                    {
                        flag=1; //признак того, что комментарий найден в БД
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
        wxListView *listview = ((wxListView*)this->FindWindow(wxID_LISTVIEW_SOTR)); //получаем указатель на листвьюев с проверками сотрудников то
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
                wxString idProvSotrTo; idProvSotrTo<<f->GetData(); //пишем в переменную данные связанные с элементом
                if(!idProvSotrTo.IsEmpty())
                {
                    wxString sqlText = wxSqlTextDelProvSotrToStart; sqlText<<idProvSotrTo; sqlText<<wxSqlEndText;
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
                ListViewProvSotr(); //перерисовываем листвьев с ассортиментом
                wxString str; str<<wxID_SUCCESS_OPERATION; str<<wxINFO_PROD_DEL_COUNT; str<<count; //строим строку с кол-вом удаленных строк
                InformationSleep(str,sec_for_sleep_window_info,this);
                //wxMessageBox(str,wxATTENTION,wxOK|wxICON_INFORMATION,this); 
            } else {;} //если не выбрана ни одна строка, то предупреждаем об этом пользователя и завершаем обработку
            (this->FindWindow(wxID_BUTTON_DEL_SOTR))->SetFocus();
        }
}
void ProvToFrm::ListUpdate (void)
{
    ListViewProvTo();
    ListViewProvSotr();
    return;
}
