#include "CrossFrm.h"

extern MYSQL* conn;
extern int sec_for_sleep_window_info;
extern void InformationSleep (wxString str, int sec, wxWindow * parent);
extern void SaveDataIntoFile (wxWindow* parent, wxString& sLine, wxString& sqlText);

BEGIN_EVENT_TABLE(HolidayFrm,wxFrame)
    EVT_SIZE(HolidayFrm::OnSize)
	EVT_MOVE_END(HolidayFrm::OnMove)
    EVT_LIST_ITEM_FOCUSED (wxID_HOLFRM_LISTVIEW_S_SOTR, HolidayFrm::FocusedItemListview)
    EVT_MENU(wxID_HOLFRM_BUT_S_OTP_INS,HolidayFrm::OnButton)
	EVT_MENU(wxID_HOLFRM_BUT_S_OTP_UPD,HolidayFrm::OnButton)
	EVT_MENU(wxID_HOLFRM_BUT_S_OTP_DEL,HolidayFrm::OnButton)
	EVT_BUTTON(wxID_HOLFRM_BITMAPBUTSAVE1,HolidayFrm::OnButton)
END_EVENT_TABLE()


HolidayFrm::HolidayFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint& pos, const wxSize& size , long style )
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

        wxBoxSizer *bos = new wxBoxSizer(wxHORIZONTAL);
        wxListView *listveiwFio = new wxListView(this, wxID_HOLFRM_LISTVIEW_S_SOTR);
        wxListView *listveiw = new wxListView(this, wxID_HOLFRM_LISTVIEW_S_OTP);
        listveiwFio->InsertColumn(0,wxCAPTION_COLUMN_FIO);
        listveiwFio->InsertColumn(1,wxCAPTION_COLUMN_REGION);
        listveiw->InsertColumn(0,wxCAPTION_COLUMN_STATUS);
        listveiw->InsertColumn(1,wxCAPTION_COLUMN_EVENT);
        listveiw->InsertColumn(2,wxCAPTION_COLUMN_C);
        listveiw->InsertColumn(3,wxCAPTION_COLUMN_PO);
        listveiw->InsertColumn(4,wxCAPTION_COLUMN_ZAMKAND);
        listveiw->InsertColumn(5,wxCAPTION_COLUMN_ZAMTO);
        listveiw->Connect(wxEVT_RIGHT_DOWN,wxMouseEventHandler(HolidayFrm::OnMouse));
        int flag_priv_lvl = 0;
        int flag_reg_lvl = 0;
        int id_sotr=0;
        for(register int i =0; i<MyPrivilegeUserArray.GetCount();++i)    
        {
            if(MyPrivilegeUserArray.Item(i).name=="mr_reg") {flag_reg_lvl=1; id_sotr=MyPrivilegeUserArray.Item(i).id_sotr;}
            if(MyPrivilegeUserArray.Item(i).name=="admin_global") {flag_priv_lvl=1;}
            if(MyPrivilegeUserArray.Item(i).name=="admin_holiday") {flag_priv_lvl=2;}
        }
        id_reg=0;
        if(flag_priv_lvl==2&&flag_reg_lvl==1&&id_sotr!=0)
        {
            wxString str_first, str_last, str_full;
            str_first = dir.GetName(); str_last= wxSAVEDATA_ICO; str_full=str_first; str_full+=str_last;
            bos->Add(new wxBitmapButton(this,wxID_HOLFRM_BITMAPBUTSAVE1,wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), wxDefaultPosition),0,wxALIGN_CENTRE_VERTICAL|wxALL,3);
            (this->FindWindow(wxID_HOLFRM_BITMAPBUTSAVE1))->SetToolTip("Выгрузить данные в файл");
            
            for(register int j =0; j<MySovConnectRegArray.GetCount();++j)    
            {
                //if(id_sotr==wxAtoi(MySovConnectRegArray.Item(j).idSovetnic)&&wxAtoi(MySovConnectRegArray.Item(j).activ)==1)
                if(id_sotr==MySovConnectRegArray.Item(j).idSovetnic&&MySovConnectRegArray.Item(j).activ==1)
                {
                    //id_reg = wxAtoi(MySovConnectRegArray.Item(j).idRegion); break;
                    id_reg = MySovConnectRegArray.Item(j).idRegion; break;
                }
            }
                for(register int iMr =0; iMr<MyMacroregArray.GetCount();++iMr) //проверяем id на совпадение с МР
                {
                    //if(wxAtoi(MyMacroregArray.Item(iMr).idMacroreg)==id_reg) //нашли то, что айди принадлежит МР
                    if(MyMacroregArray.Item(iMr).idMacroreg==id_reg) //нашли то, что айди принадлежит МР
                    {
                        wxListItem *f1 = new wxListItem();
                        f1->SetState(wxLIST_STATE_FOCUSED);
                        f1->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                        f1->SetColumn(0); //первая колонка
                        f1->SetData(id_sotr); //прячем уникальный айди
                        int item_num = listveiwFio->GetItemCount();
                        f1->SetId(item_num); //присваиваем номер строки
                        listveiwFio->InsertItem(*f1); 
                        for(register int j =0; j<MySovetnicArray.GetCount();++j) //ищем фио советника
                        {
                            //if((id_sotr==wxAtoi(MySovetnicArray.Item(j).idSovetnic))&&(wxAtoi(MySovetnicArray.Item(j).activSovetnic)==1))
                            if((id_sotr==MySovetnicArray.Item(j).idSovetnic)&&(MySovetnicArray.Item(j).activSovetnic==1))
                            {
                                listveiwFio->SetItem(item_num,0,MySovetnicArray.Item(j).nameSovetnic); //пишем значение элемента в каждый столбец
                                break;
                            }
                        }
                        wxString str = "МР " + MyMacroregArray.Item(iMr).nameMacroreg;
                        listveiwFio->SetItem(item_num,1,str); //пишем значение элемента в каждый столбец
                        delete f1;                
                        for(register int lvl1 =0; lvl1<MyTechCentrArray.GetCount();++lvl1)    //ищем в дереве техцентра связку оц/мр
                        {
                            //if(id_reg==wxAtoi(MyTechCentrArray.Item(lvl1).son)) //нашли
                            if(id_reg==MyTechCentrArray.Item(lvl1).son) //нашли
                            { 
                                for(register int i =0; i<MySovConnectRegArray.GetCount();++i)    
                                {
                                    //if((wxAtoi(MyTechCentrArray.Item(lvl1).parent)==wxAtoi(MySovConnectRegArray.Item(i).idRegion))&&(wxAtoi(MySovConnectRegArray.Item(i).activ)==1))
                                    if((MyTechCentrArray.Item(lvl1).parent==MySovConnectRegArray.Item(i).idRegion)&&(MySovConnectRegArray.Item(i).activ==1))
                                    {
                                        wxListItem *f = new wxListItem();
                                        f->SetState(wxLIST_STATE_FOCUSED);
                                        f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                                        f->SetColumn(0); //первая колонка
                                        f->SetData(MySovConnectRegArray.Item(i).idSovetnic); //прячем уникальный айди
                                        int item_numb = listveiwFio->GetItemCount();
                                        f->SetId(item_numb); //присваиваем номер строки
                                        listveiwFio->InsertItem(*f); 
                                        for(register int j =0; j<MySovetnicArray.GetCount();++j) //ищем фио советника
                                        {
                                            //if((wxAtoi(MySovConnectRegArray.Item(i).idSovetnic)==wxAtoi(MySovetnicArray.Item(j).idSovetnic))&&(wxAtoi(MySovetnicArray.Item(j).activSovetnic)==1))
                                            if((MySovConnectRegArray.Item(i).idSovetnic==MySovetnicArray.Item(j).idSovetnic)&&(MySovetnicArray.Item(j).activSovetnic==1))
                                            {
                                                listveiwFio->SetItem(item_numb,0,MySovetnicArray.Item(j).nameSovetnic); //пишем значение элемента в каждый столбец
                                                break;
                                            }
                                        }
                                        for(register int j =0; j<MyOcArray.GetCount();++j) //ищем имя региона
                                        {
                                            //if((wxAtoi(MySovConnectRegArray.Item(i).idRegion)==wxAtoi(MyOcArray.Item(j).idOc))&&(wxAtoi(MyOcArray.Item(j).activOc)==1))
                                            if((MySovConnectRegArray.Item(i).idRegion==MyOcArray.Item(j).idOc)&&(MyOcArray.Item(j).activOc==1))
                                            {
                                                wxString str = "ОЦ " + MyOcArray.Item(j).nameOc;
                                                listveiwFio->SetItem(item_numb,1,str); //пишем значение элемента в каждый столбец
                                                break;
                                            }
                                        }
                                        delete f;
                                    }
                                }
                                for(register int lvl2 =0; lvl2<MyTechCentrArray.GetCount();++lvl2) //ищем в дереве техцентра связку гц/оц
                                {
                                    //if(!MyTechCentrArray.Item(lvl1).parent.compare(MyTechCentrArray.Item(lvl2).son)) //нашли
                                    if(MyTechCentrArray.Item(lvl1).parent==MyTechCentrArray.Item(lvl2).son) //нашли
                                    {
                                        for(register int iGc =0; iGc<MyGcArray.GetCount();++iGc) //ищем в справочнике наименование оц
                                        {
                                            //if(!MyTechCentrArray.Item(lvl2).parent.compare(MyGcArray.Item(iGc).idGc)) //нашли
                                            if(MyTechCentrArray.Item(lvl2).parent==MyGcArray.Item(iGc).idGc) //нашли
                                            {
                                                
                                                for(register int i =0; i<MySovConnectRegArray.GetCount();++i)    
                                                {
                                                    //if((wxAtoi(MyTechCentrArray.Item(lvl2).parent)==wxAtoi(MySovConnectRegArray.Item(i).idRegion))&&(wxAtoi(MySovConnectRegArray.Item(i).activ)==1))
                                                    if((MyTechCentrArray.Item(lvl2).parent==MySovConnectRegArray.Item(i).idRegion)&&(MySovConnectRegArray.Item(i).activ==1))
                                                    {
                                                        wxListItem *f = new wxListItem();
                                                        f->SetState(wxLIST_STATE_FOCUSED);
                                                        f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                                                        f->SetColumn(0); //первая колонка
                                                        f->SetData(MySovConnectRegArray.Item(i).idSovetnic); //прячем уникальный айди
                                                        int item_numb = listveiwFio->GetItemCount();
                                                        f->SetId(item_numb); //присваиваем номер строки
                                                        listveiwFio->InsertItem(*f); 
                                                        for(register int j =0; j<MySovetnicArray.GetCount();++j) //ищем фио советника
                                                        {
                                                            //if((wxAtoi(MySovConnectRegArray.Item(i).idSovetnic)==wxAtoi(MySovetnicArray.Item(j).idSovetnic))&&(wxAtoi(MySovetnicArray.Item(j).activSovetnic)==1))
                                                            if((MySovConnectRegArray.Item(i).idSovetnic==MySovetnicArray.Item(j).idSovetnic)&&(MySovetnicArray.Item(j).activSovetnic==1))
                                                            {
                                                                listveiwFio->SetItem(item_numb,0,MySovetnicArray.Item(j).nameSovetnic); //пишем значение элемента в каждый столбец
                                                                break;
                                                            }
                                                        }
                                                        wxString str = "ГЦ " + MyGcArray.Item(iGc).nameGc;
                                                        listveiwFio->SetItem(item_numb,1,str); //пишем значение элемента в каждый столбец
                                                        delete f;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }   
                }
        }
        if(((flag_priv_lvl==1||flag_priv_lvl==2)&&(flag_reg_lvl==0))||((flag_priv_lvl==1)&&(flag_reg_lvl>0)))
        {
            wxString str_first, str_last, str_full;
            str_first = dir.GetName(); str_last= wxSAVEDATA_ICO; str_full=str_first; str_full+=str_last;
            bos->Add(new wxBitmapButton(this,wxID_HOLFRM_BITMAPBUTSAVE1,wxBitmap(wxImage(str_full,wxBITMAP_TYPE_ICO)), wxDefaultPosition),0,wxALIGN_CENTRE_VERTICAL|wxALL,3);
            (this->FindWindow(wxID_HOLFRM_BITMAPBUTSAVE1))->SetToolTip("Выгрузить данные в файл");
            
            for(register int i =0; i<MySovetnicArray.GetCount();++i) //ищем фио советника
            {
                //if(wxAtoi(MySovetnicArray.Item(i).activSovetnic)==1)
                if(MySovetnicArray.Item(i).activSovetnic==1)
                {
                    wxListItem *f = new wxListItem();
                    f->SetState(wxLIST_STATE_FOCUSED);
                    f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                    f->SetColumn(0); //первая колонка
                    f->SetData(MySovetnicArray.Item(i).idSovetnic); //прячем уникальный айди
                    int item_numb = listveiwFio->GetItemCount();
                    f->SetId(item_numb); //присваиваем номер строки
                    listveiwFio->InsertItem(*f); 
                    listveiwFio->SetItem(item_numb,0,MySovetnicArray.Item(i).nameSovetnic); //пишем значение элемента в каждый столбец
                    for(register int j =0; j<MySovConnectRegArray.GetCount();++j)    
                    {
                        //if((wxAtoi(MySovConnectRegArray.Item(j).idSovetnic)==wxAtoi(MySovetnicArray.Item(i).idSovetnic))&&(wxAtoi(MySovConnectRegArray.Item(j).activ)==1))
                        if((MySovConnectRegArray.Item(j).idSovetnic==MySovetnicArray.Item(i).idSovetnic)&&(MySovConnectRegArray.Item(j).activ==1))
                        {
                            int flag_reg_comp=0;
                            if(!flag_reg_comp)
                            {
                                for(register int iMr =0; iMr<MyMacroregArray.GetCount();++iMr) //проверяем id на совпадение с МР
                                {
                                    //if((wxAtoi(MyMacroregArray.Item(iMr).idMacroreg)==wxAtoi(MySovConnectRegArray.Item(j).idRegion))&&(wxAtoi(MyMacroregArray.Item(iMr).activMacroreg)==1)) //нашли то, что айди принадлежит МР
                                    if((MyMacroregArray.Item(iMr).idMacroreg==MySovConnectRegArray.Item(j).idRegion)&&(MyMacroregArray.Item(iMr).activMacroreg==1)) //нашли то, что айди принадлежит МР
                                    {
                                        flag_reg_comp=1;
                                        wxString str = "МР " + MyMacroregArray.Item(iMr).nameMacroreg;
                                        listveiwFio->SetItem(item_numb,1,str); //пишем значение элемента в каждый столбец
                                        break;
                                    }
                                }
                            }
                            if(!flag_reg_comp)
                            {
                                for(register int iOr =0; iOr<MyOcArray.GetCount();++iOr) //проверяем id на совпадение с МР
                                {
                                    //if((wxAtoi(MyOcArray.Item(iOr).idOc)==wxAtoi(MySovConnectRegArray.Item(j).idRegion))&&(wxAtoi(MyOcArray.Item(iOr).activOc)==1)) //нашли то, что айди принадлежит МР
                                    if((MyOcArray.Item(iOr).idOc==MySovConnectRegArray.Item(j).idRegion)&&(MyOcArray.Item(iOr).activOc==1)) //нашли то, что айди принадлежит МР
                                    {
                                        flag_reg_comp=1;
                                        wxString str = "ОЦ " + MyOcArray.Item(iOr).nameOc;
                                        listveiwFio->SetItem(item_numb,1,str); //пишем значение элемента в каждый столбец
                                        break;
                                    }
                                }
                            }
                            if(!flag_reg_comp)
                            {
                                for(register int iGr =0; iGr<MyGcArray.GetCount();++iGr) //проверяем id на совпадение с МР
                                {
                                    //if((wxAtoi(MyGcArray.Item(iGr).idGc)==wxAtoi(MySovConnectRegArray.Item(j).idRegion))&&(wxAtoi(MyGcArray.Item(iGr).activGc)==1)) //нашли то, что айди принадлежит МР
                                    if((MyGcArray.Item(iGr).idGc==MySovConnectRegArray.Item(j).idRegion)&&(MyGcArray.Item(iGr).activGc==1)) //нашли то, что айди принадлежит МР
                                    {
                                        flag_reg_comp=1;
                                        wxString str = "ГЦ " + MyGcArray.Item(iGr).nameGc;
                                        listveiwFio->SetItem(item_numb,1,str); //пишем значение элемента в каждый столбец
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }
            
        }
        for(register int i=0;i<(listveiwFio->GetColumnCount());++i) listveiwFio->SetColumnWidth(i,wxLIST_AUTOSIZE);     //изменяем размер столбца по длине самого большого элемента
        for(register int i=0;i<(listveiw->GetColumnCount());++i) listveiw->SetColumnWidth(i,wxLIST_AUTOSIZE);           //изменяем размер столбца по длине самого большого элемента

        bos->Add(listveiwFio,1,wxEXPAND|wxTOP|wxBOTTOM,5);
        bos->Add(listveiw,2,wxEXPAND|wxALL,5);
        SetSizer(bos);
    }
}

void HolidayFrm::FocusedItemListview (wxListEvent& event)
{
    switch (event.GetId())
    {
        case wxID_HOLFRM_LISTVIEW_S_SOTR:
        {
            //int id = event.GetData();
            FillTableHoliday();
            break;
        }
        default:break;
    }
}
void HolidayFrm::FillTableHoliday ()
{
    wxListView *listveiwFio = (wxListView*)this->FindWindow(wxID_HOLFRM_LISTVIEW_S_SOTR);
    wxListView *listveiwHoliday = (wxListView*)this->FindWindow(wxID_HOLFRM_LISTVIEW_S_OTP);
    int select_item = listveiwFio->GetFirstSelected(); //получаем выбранную строку
    int idSotr = (int)listveiwFio->GetItemData(select_item); //получаем вшитый в троку data
    listveiwHoliday->DeleteAllItems();
    if(idSotr==0||idSotr<0) {return;} 
    wxString sqlText;
    sqlText<<wxSqlTextSelNowOtpFrm; sqlText<<idSotr; sqlText<<wxSqlEndText;
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR); return;}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {   
            for (register int i = 0; i < num_rows; i++) // Вывод таблицы
            {
                MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                wxListItem *f = new wxListItem();
                f->SetState(wxLIST_STATE_FOCUSED);
                f->SetMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                f->SetColumn(0);
                f->SetData(wxAtoi(row[0])); //прячем уникальный айди
                f->SetId(i);
                listveiwHoliday->InsertItem(*f);
                listveiwHoliday->SetItem(i,0,row[1]); 
                for(register int j =0; j<MyHolidayTypeArray.GetCount();++j)       //запускаем цикл поиска совпадений 
                {
                    //if (wxAtoi(MyHolidayTypeArray.Item(j).idHolidayType)==wxAtoi(row[2]))
                    if (MyHolidayTypeArray.Item(j).idHolidayType==wxAtoi(row[2]))
                    {listveiwHoliday->SetItem(i,1,MyHolidayTypeArray.Item(j).nameHolidayType); break;}      //совпадение найдено
                }
                listveiwHoliday->SetItem(i,2,row[3]); 
                listveiwHoliday->SetItem(i,3,row[4]); 
                for(register int j =0; j<MySovetnicArray.GetCount();++j)       //запускаем цикл поиска совпадений 
                {
                    //if (wxAtoi(MySovetnicArray.Item(j).idSovetnic)==wxAtoi(row[5])) {listveiwHoliday->SetItem(i,4,MySovetnicArray.Item(j).nameSovetnic); }      //совпадение найдено
                    //if (wxAtoi(MySovetnicArray.Item(j).idSovetnic)==wxAtoi(row[6])) {listveiwHoliday->SetItem(i,5,MySovetnicArray.Item(j).nameSovetnic); }      //совпадение найдено
                    if (MySovetnicArray.Item(j).idSovetnic==wxAtoi(row[5])) {listveiwHoliday->SetItem(i,4,MySovetnicArray.Item(j).nameSovetnic); }      //совпадение найдено
                    if (MySovetnicArray.Item(j).idSovetnic==wxAtoi(row[6])) {listveiwHoliday->SetItem(i,5,MySovetnicArray.Item(j).nameSovetnic); }      //совпадение найдено
                }
                
                delete f;
            }
        for (register int i=0; i<(listveiwHoliday->GetColumnCount());++i) {listveiwHoliday->SetColumnWidth(i,wxLIST_AUTOSIZE);} //изменяем размер столбца по длине самого большого элемента  
        } else {;}
        mysql_free_result(res); // Очищаем результаты
    }      
    
}
void HolidayFrm::OnButton(wxCommandEvent& event)
{
    switch(event.GetId())
    {
        case wxID_HOLFRM_BITMAPBUTSAVE1:
        {
            wxString strTitle = "Регион\tФИО сотрудника\tСобытие\tДата начала\tДата окончания\tЗамена по кандидатам\tЗамена по ТО/Агентам/Контрагентам";
            wxString sqlText;
            /*int idMr=0;
            if(id_sotr!=0)
            {
                for(register int i =0; i<MySovConnectRegArray.GetCount();++i)    
                {
                    if(MySovConnectRegArray.Item(i).idSovetnic==id_sotr) {idMr=MySovConnectRegArray.Item(i).idRegion; break;}
                }
            }*/
            //if(idMr!=0) id_reg
            if(id_reg!=0) 
            {
                sqlText = wxSqlTextSelNowOtpFrm1_1_1;
                sqlText<<wxSqlTextSelNowOtpFrm1_1_2; sqlText<<id_reg;
                sqlText<<wxSqlTextSelNowOtpFrm1_1_3; sqlText<<id_reg;
                sqlText<<wxSqlTextSelNowOtpFrm1_1_4; sqlText<<id_reg;
                sqlText<<wxSqlTextSelNowOtpFrm1_1_5;
            }
            else
            {sqlText = wxSqlTextSelNowOtpFrm1;}
            SaveDataIntoFile (this, strTitle, sqlText);
            break;
        }
        case wxID_HOLFRM_BUT_S_OTP_INS:
        {
            wxListView *listveiwFio = (wxListView*)this->FindWindow(wxID_HOLFRM_LISTVIEW_S_SOTR);
            wxListView *listveiwHoliday = (wxListView*)this->FindWindow(wxID_HOLFRM_LISTVIEW_S_OTP);
            if(listveiwFio->GetFirstSelected()!=-1)
            {
                if ((event.GetId())==wxID_HOLFRM_BUT_S_OTP_INS) {InsUpdHolidaySotrDialog insUpdHolidaySotrDialog(this,1); if(insUpdHolidaySotrDialog.ShowModal() == wxID_OK) {FillTableHoliday();} else {;}} //создаем диалоговое окно
                break;
            } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
            break;
        }
        case wxID_HOLFRM_BUT_S_OTP_UPD:
        {
            wxListView *listveiwFio = (wxListView*)this->FindWindow(wxID_HOLFRM_LISTVIEW_S_SOTR);
            wxListView *listveiwHoliday = (wxListView*)this->FindWindow(wxID_HOLFRM_LISTVIEW_S_OTP);
            if((listveiwFio->GetFirstSelected()!=-1)&&(listveiwHoliday->GetFirstSelected()!=-1))
            {
                if(ChackSign(listveiwHoliday)==1) //проверяем наличие признака проставления замещения
                {
                    if ((event.GetId())==wxID_HOLFRM_BUT_S_OTP_UPD) {InsUpdHolidaySotrDialog insUpdHolidaySotrDialog(this,2); if(insUpdHolidaySotrDialog.ShowModal() == wxID_OK) {FillTableHoliday();} else {;}} //создаем диалоговое окно  
                    break;
                } else {break;}
            } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
            break;
        }
        case wxID_HOLFRM_BUT_S_OTP_DEL:
        {
            wxListView *listveiwFio = (wxListView*)this->FindWindow(wxID_HOLFRM_LISTVIEW_S_SOTR);
            wxListView *listveiwHoliday = (wxListView*)this->FindWindow(wxID_HOLFRM_LISTVIEW_S_OTP);
            if((listveiwFio->GetFirstSelected()!=-1)&&(listveiwHoliday->GetFirstSelected()!=-1))
            {
                int select_item = listveiwHoliday->GetFirstSelected(); //получаем выбранную строку
                int idReestr = (int)listveiwHoliday->GetItemData(select_item); //получаем вшитый в троку data
                if(wxMessageBox(wxQUESTION_DELETE_STR,wxATTENTION,wxYES_NO,this)==wxYES)
                {
                    wxString sqlText = wxSqlTextDelOtpFrm; sqlText<<idReestr; sqlText<<wxSqlEndText;
                    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR,this); return;}               
                    else 
                    {
                        listveiwHoliday->DeleteItem(select_item);
                    }
                }
                break;
            } else {InformationSleep(wxINFO_NOT_SELECT_STRING,sec_for_sleep_window_info,this);}
            break;
        }
        default:break;
    }
}
void HolidayFrm::OnMouse(wxMouseEvent& event)
{
	if (event.GetId()==wxID_HOLFRM_LISTVIEW_S_OTP)
	{
        //возможна утечка памяти из-за menuitem
        wxPoint point = event.GetPosition(); //определяем коородинаты физического положения мыши
        wxMenu *menu = new wxMenu;
        menu->Append(wxID_HOLFRM_BUT_S_OTP_INS,wxCAPTION_BUTTON_INSERT);
        menu->Append(wxID_HOLFRM_BUT_S_OTP_UPD,wxCAPTION_BUTTON_PRAVKA);
        //menu->Append(wxID_HOLFRM_BUT_S_OTP_DEL,wxCAPTION_BUTTON_DELETE);
        PopupMenu(menu,point);
        delete menu; 
    }    
}
void HolidayFrm::OnSize(wxSizeEvent& event) //ловим размеры окна во время события изменения нижней или правой границы
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_HOLIDAY/x"), rect.GetX() );
    config->Write( wxT("/FORM_HOLIDAY/y"), rect.GetY() );
    config->Write( wxT("/FORM_HOLIDAY/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_HOLIDAY/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}
void HolidayFrm::OnMove(wxMoveEvent& event) //ловим размеры окна во время события передвижения окна
{
	wxRect rect = GetRect();
	wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "CONFIG.INI";
    wxFileConfig *config = new wxFileConfig( "", "", ini_filename);
    config->Write( wxT("/FORM_HOLIDAY/x"), rect.GetX() );
    config->Write( wxT("/FORM_HOLIDAY/y"), rect.GetY() );
    config->Write( wxT("/FORM_HOLIDAY/width"), rect.GetWidth() );
    config->Write( wxT("/FORM_HOLIDAY/height"), rect.GetHeight() );
    config->Flush();
    delete config;
    event.Skip(true);
}

int HolidayFrm::ChackSign(wxListView* listveiwHoliday)
{
    wxString sqlText;
    int flagSamech, select_item, idReestrString;
    select_item = listveiwHoliday->GetFirstSelected(); //определяем номер выделенной строки
    idReestrString = (int)listveiwHoliday->GetItemData(select_item); //определяем айди зашитый в строку
    sqlText=wxSqlTextSelFlafZamech; //строим запрос
    sqlText<<idReestrString; sqlText<<wxSqlEndText; //строим запрос
    if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR); return 0;}
    else
    {
        MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
        int num_rows = mysql_num_rows(res); // и количество строк.
        if(num_rows>0)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
            flagSamech = wxAtoi(row[0]);
        }
        mysql_free_result(res); // Очищаем результаты
        if (flagSamech==1) {wxMessageBox(wxINFO_UPD_OTP_STOP,wxATTENTION,wxOK|wxCENTRE); return 0;} else {return 1;}
    }
}


HolidayFrm::~HolidayFrm()
{
}
