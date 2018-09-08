#include "CrossFrm.h"
extern MYSQL* conn;
void CreateSpravochnic ();
void DeleteSpravochnic ();
void CreatePrivelege();

WX_DEFINE_OBJARRAY(MacroregArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(OcArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(GcArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(HolidayTypeArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(BrandNameArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(BrandTypeArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(UkRfArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(FioSbArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(RezProvArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(ProdGroupArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(ProdNameArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(DolznostArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(SovetnicArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(TechCentrArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(SovConnectRegArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(TypeProvArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(RootInfoArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(PositionSotrHistoryArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(PositionSotrArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(TypeCooperationArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(InitiatorChecksArray); //определяем реализацию класса
WX_DEFINE_OBJARRAY(PrivilegeUserArray); //определяем реализацию класса

MacroregArray MyMacroregArray; //создаем экземплаяр массива
OcArray MyOcArray; //создаем экземплаяр массива
GcArray MyGcArray; //создаем экземплаяр массива
HolidayTypeArray MyHolidayTypeArray; //массив причин отсутствия
BrandNameArray MyBrandNameArray; //массив наименования сетей/брендов
BrandTypeArray MyBrandTypeArray; //массив типов сетей/брендов
UkRfArray MyUkRfArray; //массив статей УК РФ
FioSbArray MyFioSbArray; //массив фио сотрудников СБ ГО
RezProvArray MyRezProvArray; //массив результат проверки
ProdGroupArray MyProdGroupArray; //массив группа продуктов
ProdNameArray MyProdNameArray; //массив наименование продукта продуктов
DolznostArray MyDolznostArray; //массив должности
SovetnicArray MySovetnicArray; //массив Советники
TechCentrArray MyTechCentrArray; //массив дерево техцентра
SovConnectRegArray MySovConnectRegArray; //массив связь гц и советника
TypeProvArray MyTypeProvArray; //массив тип проверки
RootInfoArray MyRootInfoArray; //массив источник данных черный список СБ*/
PositionSotrHistoryArray MyPositionSotrHistoryArray; //массив связей сотрудников сб и должностей
PositionSotrArray MyPositionSotrArray; //массив наименование должности сотрудника сб
TypeCooperationArray MyTypeCooperationArray; //массив типов сотрудничества
InitiatorChecksArray MyInitiatorChecksArray; //массив инициаторов проверки контрагентов
PrivilegeUserArray MyPrivilegeUserArray; //массив привилегий

void CreatePrivelege(void)
{
    int num_fields;     // количество полей
    int num_rows;       // количество строк.
    MYSQL_RES *res;     // указатель на результат 
    
    //справочник Макрорегион
    wxString sqlText; sqlText<<wxSqlTextSelPrivilege; sqlText<<wxSqlCharStr; sqlText<<wxGetUserName(); sqlText<<wxSqlCharStr; sqlText<<wxSqlEndText;
    
    if (mysql_query(conn, sqlText.c_str()) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        PrivilegeUser privilegeUser;  
        privilegeUser.name = row[0];         
        privilegeUser.id_sotr = wxAtoi(row[1]);              
        MyPrivilegeUserArray.Add(privilegeUser); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
}

void CreateSpravochnic (void)
{
    int num_fields;     // количество полей
    int num_rows;       // количество строк.
    MYSQL_RES *res;     // указатель на результат 
    
    //справочник Макрорегион
    if (mysql_query(conn, wxSqlTextSprMacroreg) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        Macroreg macro; //определяем объект класса Макрорегион
        macro.nameMacroreg = row[0];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса Макрорегион
        macro.idMacroreg = wxAtoi(row[1]);          //записываем айди макрорегиона из строки выборки в член-данные объекта класса Макрорегион
        macro.activMacroreg = wxAtoi(row[2]);       //записываем признак активности макрорегиона из строки выборки в член-данные объекта класса Макрорегион
        (macro.nameMacroreg).MakeUpper();     //приводим символы к верхнему регистру
        //if(macro.activMacroreg.Contains("0")){macro.nameMacroreg<<" (АРХИВ)";} //ищем в строке символ 0. Если есть совпадение, то дописываем к наименованию признак архива
        if(macro.activMacroreg==0){macro.nameMacroreg<<" (АРХИВ)";} //ищем в строке символ 0. Если есть совпадение, то дописываем к наименованию признак архива
        MyMacroregArray.Add(macro); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты

    //справочник ОЦ
    if (mysql_query(conn, wxSqlTextSprOc) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        Oc oc; //определяем объект класса Макрорегион
        oc.nameOc = row[0];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса ОЦ
        oc.idOc = wxAtoi(row[1]);          //записываем айди макрорегиона из строки выборки в член-данные объекта класса ОЦ
        oc.activOc = wxAtoi(row[2]);       //записываем признак активности макрорегиона из строки выборки в член-данные объекта класса ОЦ
        (oc.nameOc).MakeUpper();     //приводим символы к верхнему регистру
        //if(oc.activOc.Contains("0")){oc.nameOc<<" (АРХИВ)";}
        if(oc.activOc==0){oc.nameOc<<" (АРХИВ)";}
        MyOcArray.Add(oc); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты

    //справочник ГЦ
    if (mysql_query(conn, wxSqlTextSprGc) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        Gc gc; //определяем объект класса Макрорегион
        gc.nameGc = row[0];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса ГЦ
        gc.idGc = wxAtoi(row[1]);          //записываем айди макрорегиона из строки выборки в член-данные объекта класса ГЦ
        gc.activGc = wxAtoi(row[2]);       //записываем признак активности макрорегиона из строки выборки в член-данные объекта класса ГЦ
        (gc.nameGc).MakeUpper();     //приводим символы к верхнему регистру
        //if(gc.activGc.Contains("0")){gc.nameGc<<" (АРХИВ)";}
        if(gc.activGc==0){gc.nameGc<<" (АРХИВ)";}
        MyGcArray.Add(gc); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник типы отпусков
    if (mysql_query(conn, wxSqlTextSprHoliday) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        HolidayType holidaytype; //определяем объект класса Макрорегион
        holidaytype.idHolidayType = wxAtoi(row[0]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        holidaytype.nameHolidayType = row[1];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (holidaytype.nameHolidayType).MakeUpper();     //приводим символы к верхнему регистру
        MyHolidayTypeArray.Add(holidaytype); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник наименования сетей/брендов
    if (mysql_query(conn, wxSqlTextBrandName) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        BrandName brandname; //определяем объект класса Макрорегион
        brandname.nameBrandName = row[0];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        brandname.idBrandName = wxAtoi(row[1]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        brandname.idBrandType = wxAtoi(row[2]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (brandname.nameBrandName).MakeUpper();     //приводим символы к верхнему регистру
        MyBrandNameArray.Add(brandname); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник типов сетей/брендов
    if (mysql_query(conn, wxSqlTextBrandType) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        BrandType brandtype; //определяем объект класса Макрорегион
        brandtype.nameBrandType = row[0];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        brandtype.idBrandType = wxAtoi(row[1]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (brandtype.nameBrandType).MakeUpper();     //приводим символы к верхнему регистру
        MyBrandTypeArray.Add(brandtype); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник статей УК РФ
    if (mysql_query(conn, wxSqlTextUk) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        UkRf ukrf; //определяем объект класса Макрорегион
        ukrf.nameUkRf = row[0];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        ukrf.idUkRf = wxAtoi(row[1]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (ukrf.nameUkRf).MakeUpper();     //приводим символы к верхнему регистру
        MyUkRfArray.Add(ukrf); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник фио сотрудников СБ ГО
    if (mysql_query(conn, wxSqlTextFioSb) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        FioSb fiosb; //определяем объект класса Макрорегион
        fiosb.nameFioSb = row[0];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        fiosb.idFioSb = wxAtoi(row[1]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (fiosb.nameFioSb).MakeUpper();     //приводим символы к верхнему регистру
        MyFioSbArray.Add(fiosb); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник результат проверки
    if (mysql_query(conn, wxSqlTextRezProv) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        RezProv rezprov; //определяем объект класса Макрорегион
        rezprov.nameRezProv = row[0];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        rezprov.idRezProv = wxAtoi(row[1]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (rezprov.nameRezProv).MakeUpper();     //приводим символы к верхнему регистру
        MyRezProvArray.Add(rezprov); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник группа продуктов
    if (mysql_query(conn, wxSqlTextProdGroup) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        ProdGroup prodgroup; //определяем объект класса Макрорегион
        prodgroup.idProdGroup = wxAtoi(row[0]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        prodgroup.nameProdGroup = row[1];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (prodgroup.nameProdGroup).MakeUpper();     //приводим символы к верхнему регистру
        MyProdGroupArray.Add(prodgroup); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник наименование продуктов
    if (mysql_query(conn, wxSqlTextProdName) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        ProdName prodname; //определяем объект класса Макрорегион
        prodname.nameProdName = row[2];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        prodname.idProdName = wxAtoi(row[1]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        prodname.idProdGroup = wxAtoi(row[0]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (prodname.nameProdName).MakeUpper();     //приводим символы к верхнему регистру
        MyProdNameArray.Add(prodname); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник должности
    if (mysql_query(conn, wxSqlTextDolznost) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        Dolznost dolznost; //определяем объект класса Макрорегион
        dolznost.nameDolznost = row[1];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        dolznost.idDolznost = wxAtoi(row[0]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        (dolznost.nameDolznost).MakeUpper();     //приводим символы к верхнему регистру
        MyDolznostArray.Add(dolznost); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник Советники
    if (mysql_query(conn, wxSqlTextSovetnic) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        Sovetnic sovetnic; //определяем объект класса Макрорегион
        sovetnic.nameSovetnic = row[1];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        sovetnic.idSovetnic = wxAtoi(row[0]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        sovetnic.activSovetnic = wxAtoi(row[2]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        sovetnic.drSovetnic = row[3];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        sovetnic.pfoneSovetnic = row[4];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        sovetnic.dateOpen = row[5]; 
        sovetnic.dateClose = row[6]; 
        (sovetnic.nameSovetnic).MakeUpper();     //приводим символы к верхнему регистру
        MySovetnicArray.Add(sovetnic); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник Дерево техцентра
    if (mysql_query(conn, wxSqlTextTechCentr) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        TechCentr techtentr; //определяем объект класса Макрорегион
        techtentr.parent = wxAtoi(row[0]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        techtentr.son = wxAtoi(row[1]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        MyTechCentrArray.Add(techtentr); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник связь региона и Советника
    if (mysql_query(conn, wxSqlTextSovConnectReg) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        SovConnectReg sovconnectreg; //определяем объект класса Макрорегион
        sovconnectreg.idReestr = wxAtoi(row[0]);
        sovconnectreg.idRegion = wxAtoi(row[1]);         
        sovconnectreg.idSovetnic = wxAtoi(row[2]);  
        sovconnectreg.activ = wxAtoi(row[3]);
        sovconnectreg.dateChange = row[4];       
        MySovConnectRegArray.Add(sovconnectreg); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник тип проверки
    if (mysql_query(conn, wxSqlTextTypeProv) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        TypeProv typeprov; //определяем объект класса Макрорегион
        typeprov.nameTypeProv = row[1];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        typeprov.idTypeProv = wxAtoi(row[0]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        typeprov.nameTypeProv.Trim(true); typeprov.nameTypeProv.Trim(false); //в БД в значениях предпоследним символом был \n, поэтому удаляем слева и справа пробелы
        MyTypeProvArray.Add(typeprov); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник источник данных ЧС СБ
    if (mysql_query(conn, wxSqlTextRootInfo) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        RootInfo rootinfo; //определяем объект класса Макрорегион
        rootinfo.nameRootInfo = row[1];        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        rootinfo.idRootInfo = wxAtoi(row[0]);        //записываем наименование макрорегиона из строки выборки в член-данные объекта класса типы отпусков
        MyRootInfoArray.Add(rootinfo); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник связей сотрудников с должностями
    if (mysql_query(conn, wxSqlTextPositionSotrHistory) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        PositionSotrHistory positionsotrhis; //определяем объект класса Макрорегион
        positionsotrhis.idReestr = wxAtoi(row[0]);         
        positionsotrhis.idSotr = wxAtoi(row[1]);
        positionsotrhis.idPosition = wxAtoi(row[2]);   
        positionsotrhis.activ = wxAtoi(row[3]);
        positionsotrhis.dateOn = row[4];   
        positionsotrhis.dateOff = row[5];            
        MyPositionSotrHistoryArray.Add(positionsotrhis); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник должностей сотрудников СБ
    if (mysql_query(conn, wxSqlTextPositionSotr) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        PositionSotr positionsotr; //определяем объект класса Макрорегион
        positionsotr.idPosition = wxAtoi(row[0]);         
        positionsotr.namePosition = row[1];     
        positionsotr.namePosition.MakeUpper();        
        MyPositionSotrArray.Add(positionsotr); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник типов сотрудничества
    if (mysql_query(conn, wxSqlTextTypeCooperation) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        TypeCooperation typecooperation; //определяем объект класса Макрорегион
        typecooperation.idTypeCooperation = wxAtoi(row[0]);         
        typecooperation.nameTypeCooperation = row[1];     
        typecooperation.nameTypeCooperation.MakeUpper();        
        MyTypeCooperationArray.Add(typecooperation); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
    
    //справочник инициаторов проверки контрагента
    if (mysql_query(conn, wxSqlTextInitiatorChecks) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // Берем результат,
    num_fields = mysql_num_fields(res); // количество полей
    num_rows = mysql_num_rows(res); // и количество строк.
    for (register int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
        InitiatorChecks initiatorchecks; //определяем объект класса Макрорегион
        initiatorchecks.idInitiatorChecks = wxAtoi(row[0]);         
        initiatorchecks.nameInitiatorChecks = row[1];     
        initiatorchecks.nameInitiatorChecks.MakeUpper();        
        MyInitiatorChecksArray.Add(initiatorchecks); //вставляем объект. Массив владеет объектом
    }
    mysql_free_result(res); // Очищаем результаты
}

void DeleteSpravochnic (void)
{
    MyMacroregArray.Clear();
    MyOcArray.Clear();
    MyGcArray.Clear();
    MyHolidayTypeArray.Clear();
    MyBrandNameArray.Clear();
    MyBrandTypeArray.Clear();
    MyUkRfArray.Clear();
    MyFioSbArray.Clear();
    MyRezProvArray.Clear();
    MyProdGroupArray.Clear();
    MyProdNameArray.Clear();
    MyDolznostArray.Clear();
    MySovetnicArray.Clear();
    MyTechCentrArray.Clear();
    MySovConnectRegArray.Clear();
    MyTypeProvArray.Clear();
    MyRootInfoArray.Clear();
    MyPositionSotrHistoryArray.Clear();
    MyPositionSotrArray.Clear();
    MyTypeCooperationArray.Clear();
    MyInitiatorChecksArray.Clear();
}
