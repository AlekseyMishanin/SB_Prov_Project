#include "CrossFrm.h"
extern MYSQL* conn;
void CreateSpravochnic ();
void DeleteSpravochnic ();
void CreatePrivelege();

WX_DEFINE_OBJARRAY(MacroregArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(OcArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(GcArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(HolidayTypeArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(BrandNameArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(BrandTypeArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(UkRfArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(FioSbArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(RezProvArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(ProdGroupArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(ProdNameArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(DolznostArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(SovetnicArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(TechCentrArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(SovConnectRegArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(TypeProvArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(RootInfoArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(PositionSotrHistoryArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(PositionSotrArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(TypeCooperationArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(InitiatorChecksArray); //���������� ���������� ������
WX_DEFINE_OBJARRAY(PrivilegeUserArray); //���������� ���������� ������

MacroregArray MyMacroregArray; //������� ���������� �������
OcArray MyOcArray; //������� ���������� �������
GcArray MyGcArray; //������� ���������� �������
HolidayTypeArray MyHolidayTypeArray; //������ ������ ����������
BrandNameArray MyBrandNameArray; //������ ������������ �����/�������
BrandTypeArray MyBrandTypeArray; //������ ����� �����/�������
UkRfArray MyUkRfArray; //������ ������ �� ��
FioSbArray MyFioSbArray; //������ ��� ����������� �� ��
RezProvArray MyRezProvArray; //������ ��������� ��������
ProdGroupArray MyProdGroupArray; //������ ������ ���������
ProdNameArray MyProdNameArray; //������ ������������ �������� ���������
DolznostArray MyDolznostArray; //������ ���������
SovetnicArray MySovetnicArray; //������ ���������
TechCentrArray MyTechCentrArray; //������ ������ ���������
SovConnectRegArray MySovConnectRegArray; //������ ����� �� � ���������
TypeProvArray MyTypeProvArray; //������ ��� ��������
RootInfoArray MyRootInfoArray; //������ �������� ������ ������ ������ ��*/
PositionSotrHistoryArray MyPositionSotrHistoryArray; //������ ������ ����������� �� � ����������
PositionSotrArray MyPositionSotrArray; //������ ������������ ��������� ���������� ��
TypeCooperationArray MyTypeCooperationArray; //������ ����� ��������������
InitiatorChecksArray MyInitiatorChecksArray; //������ ����������� �������� ������������
PrivilegeUserArray MyPrivilegeUserArray; //������ ����������

void CreatePrivelege(void)
{
    int num_fields;     // ���������� �����
    int num_rows;       // ���������� �����.
    MYSQL_RES *res;     // ��������� �� ��������� 
    
    //���������� �����������
    wxString sqlText; sqlText<<wxSqlTextSelPrivilege; sqlText<<wxSqlCharStr; sqlText<<wxGetUserName(); sqlText<<wxSqlCharStr; sqlText<<wxSqlEndText;
    
    if (mysql_query(conn, sqlText.c_str()) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        PrivilegeUser privilegeUser;  
        privilegeUser.name = row[0];         
        privilegeUser.id_sotr = wxAtoi(row[1]);              
        MyPrivilegeUserArray.Add(privilegeUser); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
}

void CreateSpravochnic (void)
{
    int num_fields;     // ���������� �����
    int num_rows;       // ���������� �����.
    MYSQL_RES *res;     // ��������� �� ��������� 
    
    //���������� �����������
    if (mysql_query(conn, wxSqlTextSprMacroreg) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        Macroreg macro; //���������� ������ ������ �����������
        macro.nameMacroreg = row[0];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ �����������
        macro.idMacroreg = wxAtoi(row[1]);          //���������� ���� ������������ �� ������ ������� � ����-������ ������� ������ �����������
        macro.activMacroreg = wxAtoi(row[2]);       //���������� ������� ���������� ������������ �� ������ ������� � ����-������ ������� ������ �����������
        (macro.nameMacroreg).MakeUpper();     //�������� ������� � �������� ��������
        //if(macro.activMacroreg.Contains("0")){macro.nameMacroreg<<" (�����)";} //���� � ������ ������ 0. ���� ���� ����������, �� ���������� � ������������ ������� ������
        if(macro.activMacroreg==0){macro.nameMacroreg<<" (�����)";} //���� � ������ ������ 0. ���� ���� ����������, �� ���������� � ������������ ������� ������
        MyMacroregArray.Add(macro); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������

    //���������� ��
    if (mysql_query(conn, wxSqlTextSprOc) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        Oc oc; //���������� ������ ������ �����������
        oc.nameOc = row[0];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ��
        oc.idOc = wxAtoi(row[1]);          //���������� ���� ������������ �� ������ ������� � ����-������ ������� ������ ��
        oc.activOc = wxAtoi(row[2]);       //���������� ������� ���������� ������������ �� ������ ������� � ����-������ ������� ������ ��
        (oc.nameOc).MakeUpper();     //�������� ������� � �������� ��������
        //if(oc.activOc.Contains("0")){oc.nameOc<<" (�����)";}
        if(oc.activOc==0){oc.nameOc<<" (�����)";}
        MyOcArray.Add(oc); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������

    //���������� ��
    if (mysql_query(conn, wxSqlTextSprGc) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        Gc gc; //���������� ������ ������ �����������
        gc.nameGc = row[0];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ��
        gc.idGc = wxAtoi(row[1]);          //���������� ���� ������������ �� ������ ������� � ����-������ ������� ������ ��
        gc.activGc = wxAtoi(row[2]);       //���������� ������� ���������� ������������ �� ������ ������� � ����-������ ������� ������ ��
        (gc.nameGc).MakeUpper();     //�������� ������� � �������� ��������
        //if(gc.activGc.Contains("0")){gc.nameGc<<" (�����)";}
        if(gc.activGc==0){gc.nameGc<<" (�����)";}
        MyGcArray.Add(gc); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ���� ��������
    if (mysql_query(conn, wxSqlTextSprHoliday) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        HolidayType holidaytype; //���������� ������ ������ �����������
        holidaytype.idHolidayType = wxAtoi(row[0]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        holidaytype.nameHolidayType = row[1];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (holidaytype.nameHolidayType).MakeUpper();     //�������� ������� � �������� ��������
        MyHolidayTypeArray.Add(holidaytype); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ������������ �����/�������
    if (mysql_query(conn, wxSqlTextBrandName) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        BrandName brandname; //���������� ������ ������ �����������
        brandname.nameBrandName = row[0];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        brandname.idBrandName = wxAtoi(row[1]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        brandname.idBrandType = wxAtoi(row[2]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (brandname.nameBrandName).MakeUpper();     //�������� ������� � �������� ��������
        MyBrandNameArray.Add(brandname); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ����� �����/�������
    if (mysql_query(conn, wxSqlTextBrandType) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        BrandType brandtype; //���������� ������ ������ �����������
        brandtype.nameBrandType = row[0];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        brandtype.idBrandType = wxAtoi(row[1]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (brandtype.nameBrandType).MakeUpper();     //�������� ������� � �������� ��������
        MyBrandTypeArray.Add(brandtype); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ������ �� ��
    if (mysql_query(conn, wxSqlTextUk) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        UkRf ukrf; //���������� ������ ������ �����������
        ukrf.nameUkRf = row[0];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        ukrf.idUkRf = wxAtoi(row[1]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (ukrf.nameUkRf).MakeUpper();     //�������� ������� � �������� ��������
        MyUkRfArray.Add(ukrf); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ��� ����������� �� ��
    if (mysql_query(conn, wxSqlTextFioSb) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        FioSb fiosb; //���������� ������ ������ �����������
        fiosb.nameFioSb = row[0];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        fiosb.idFioSb = wxAtoi(row[1]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (fiosb.nameFioSb).MakeUpper();     //�������� ������� � �������� ��������
        MyFioSbArray.Add(fiosb); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ��������� ��������
    if (mysql_query(conn, wxSqlTextRezProv) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        RezProv rezprov; //���������� ������ ������ �����������
        rezprov.nameRezProv = row[0];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        rezprov.idRezProv = wxAtoi(row[1]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (rezprov.nameRezProv).MakeUpper();     //�������� ������� � �������� ��������
        MyRezProvArray.Add(rezprov); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ������ ���������
    if (mysql_query(conn, wxSqlTextProdGroup) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        ProdGroup prodgroup; //���������� ������ ������ �����������
        prodgroup.idProdGroup = wxAtoi(row[0]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        prodgroup.nameProdGroup = row[1];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (prodgroup.nameProdGroup).MakeUpper();     //�������� ������� � �������� ��������
        MyProdGroupArray.Add(prodgroup); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ������������ ���������
    if (mysql_query(conn, wxSqlTextProdName) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        ProdName prodname; //���������� ������ ������ �����������
        prodname.nameProdName = row[2];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        prodname.idProdName = wxAtoi(row[1]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        prodname.idProdGroup = wxAtoi(row[0]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (prodname.nameProdName).MakeUpper();     //�������� ������� � �������� ��������
        MyProdNameArray.Add(prodname); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ���������
    if (mysql_query(conn, wxSqlTextDolznost) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        Dolznost dolznost; //���������� ������ ������ �����������
        dolznost.nameDolznost = row[1];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        dolznost.idDolznost = wxAtoi(row[0]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        (dolznost.nameDolznost).MakeUpper();     //�������� ������� � �������� ��������
        MyDolznostArray.Add(dolznost); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ���������
    if (mysql_query(conn, wxSqlTextSovetnic) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        Sovetnic sovetnic; //���������� ������ ������ �����������
        sovetnic.nameSovetnic = row[1];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        sovetnic.idSovetnic = wxAtoi(row[0]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        sovetnic.activSovetnic = wxAtoi(row[2]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        sovetnic.drSovetnic = row[3];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        sovetnic.pfoneSovetnic = row[4];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        sovetnic.dateOpen = row[5]; 
        sovetnic.dateClose = row[6]; 
        (sovetnic.nameSovetnic).MakeUpper();     //�������� ������� � �������� ��������
        MySovetnicArray.Add(sovetnic); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ������ ���������
    if (mysql_query(conn, wxSqlTextTechCentr) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        TechCentr techtentr; //���������� ������ ������ �����������
        techtentr.parent = wxAtoi(row[0]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        techtentr.son = wxAtoi(row[1]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        MyTechCentrArray.Add(techtentr); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ����� ������� � ���������
    if (mysql_query(conn, wxSqlTextSovConnectReg) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        SovConnectReg sovconnectreg; //���������� ������ ������ �����������
        sovconnectreg.idReestr = wxAtoi(row[0]);
        sovconnectreg.idRegion = wxAtoi(row[1]);         
        sovconnectreg.idSovetnic = wxAtoi(row[2]);  
        sovconnectreg.activ = wxAtoi(row[3]);
        sovconnectreg.dateChange = row[4];       
        MySovConnectRegArray.Add(sovconnectreg); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ��� ��������
    if (mysql_query(conn, wxSqlTextTypeProv) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        TypeProv typeprov; //���������� ������ ������ �����������
        typeprov.nameTypeProv = row[1];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        typeprov.idTypeProv = wxAtoi(row[0]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        typeprov.nameTypeProv.Trim(true); typeprov.nameTypeProv.Trim(false); //� �� � ��������� ������������� �������� ��� \n, ������� ������� ����� � ������ �������
        MyTypeProvArray.Add(typeprov); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� �������� ������ �� ��
    if (mysql_query(conn, wxSqlTextRootInfo) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        RootInfo rootinfo; //���������� ������ ������ �����������
        rootinfo.nameRootInfo = row[1];        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        rootinfo.idRootInfo = wxAtoi(row[0]);        //���������� ������������ ������������ �� ������ ������� � ����-������ ������� ������ ���� ��������
        MyRootInfoArray.Add(rootinfo); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ������ ����������� � �����������
    if (mysql_query(conn, wxSqlTextPositionSotrHistory) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        PositionSotrHistory positionsotrhis; //���������� ������ ������ �����������
        positionsotrhis.idReestr = wxAtoi(row[0]);         
        positionsotrhis.idSotr = wxAtoi(row[1]);
        positionsotrhis.idPosition = wxAtoi(row[2]);   
        positionsotrhis.activ = wxAtoi(row[3]);
        positionsotrhis.dateOn = row[4];   
        positionsotrhis.dateOff = row[5];            
        MyPositionSotrHistoryArray.Add(positionsotrhis); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ���������� ����������� ��
    if (mysql_query(conn, wxSqlTextPositionSotr) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        PositionSotr positionsotr; //���������� ������ ������ �����������
        positionsotr.idPosition = wxAtoi(row[0]);         
        positionsotr.namePosition = row[1];     
        positionsotr.namePosition.MakeUpper();        
        MyPositionSotrArray.Add(positionsotr); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ����� ��������������
    if (mysql_query(conn, wxSqlTextTypeCooperation) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        TypeCooperation typecooperation; //���������� ������ ������ �����������
        typecooperation.idTypeCooperation = wxAtoi(row[0]);         
        typecooperation.nameTypeCooperation = row[1];     
        typecooperation.nameTypeCooperation.MakeUpper();        
        MyTypeCooperationArray.Add(typecooperation); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
    
    //���������� ����������� �������� �����������
    if (mysql_query(conn, wxSqlTextInitiatorChecks) > 0) { wxMessageBox(mysql_error(conn), wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
    res = mysql_store_result(conn); // ����� ���������,
    num_fields = mysql_num_fields(res); // ���������� �����
    num_rows = mysql_num_rows(res); // � ���������� �����.
    for (register int i = 0; i < num_rows; i++) // ����� �������
    {
        MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
        InitiatorChecks initiatorchecks; //���������� ������ ������ �����������
        initiatorchecks.idInitiatorChecks = wxAtoi(row[0]);         
        initiatorchecks.nameInitiatorChecks = row[1];     
        initiatorchecks.nameInitiatorChecks.MakeUpper();        
        MyInitiatorChecksArray.Add(initiatorchecks); //��������� ������. ������ ������� ��������
    }
    mysql_free_result(res); // ������� ����������
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
