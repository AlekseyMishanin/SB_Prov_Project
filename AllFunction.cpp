#include "CrossFrm.h"

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

void insertStrDateToCtrl (wxString& str, wxDatePickerCtrl* window); //������� ���� ����� ���������� ���� � ������ � ��������� ��������� �������� � ���� ����
void EditTheLine(wxString &str, wxWindow* win); //������� ����������� ������ ��� ������� ���� win �������� ������� \n
void InformationSleep (wxString str, int sec, wxWindow * parent); //������� ������� ��������������� ��������� str, ������� ����� ����� ������������� sec ������
void EditStringFio (wxString& str); //������� ����������� ������ wxString ����� ������ ���� �������� �� ������ �.�.
void EditStringFioFull (wxString& str); //������� ����������� ������ wxString ����� ������ ���� �������� �� ������ ���� ��������
int proverka_bl_sb(MYSQL* conn, wxString& str, int type); //������� ��������� str �� ������� ������� � �� ��. type - ��� �� �� ��� ��������, 0 - ��, 1 - ������
void SaveDataIntoFile (wxWindow* parent, wxString& sLine, wxString& sqlText); //������� ��������� ��������� ��������� sql-������� � ����, ��������� ������� = sLine

void insertStrDateToCtrl (wxString& str, wxDatePickerCtrl* window)
{
    if(!str.IsEmpty())
    {
        wxDateTime dt;                  //������� ������ ������ wxDateTime
        wxString::const_iterator end;   //������� �������� ����������� �� ����� ������, ��� ��� ����������� �������������� ������
        dt.ParseDate(str, &end);        //����������� ������ � ���������� ����
        if (dt.IsValid())               //���������, ��� ������ ������������ ����� ���������� ������ �������
        {
            window->SetValue(dt); //����������� ��������� �������� � ������� � �����
        }
    }
}

void InformationSleep (wxString str, int sec, wxWindow * parent)
{
    wxBusyInfo wait(str, parent);
    wxSleep(sec);
}

void EditTheLine(wxString &str, wxWindow* win)
{
    //wxString str = str1;
    if(str.IsEmpty()) {return;}
    else
    {
        wxClientDC *dc = new wxClientDC(win); //������� ��������� �� �������� ����������
        wxSize sizeStr = dc->GetTextExtent(str); //���������� ����� ������ � ��������
        delete dc;
                        
        wxSize sizeWin = win->GetClientSize(); //���������� ������� ���������� ������� ����
        int elem = sizeStr.GetWidth()/str.Len(); //���������� ������ ������ ������� � ��������

        wxString::size_type pos = 0;
        int a = sizeWin.GetWidth()-190;
        for (wxString::size_type pos = 0, j=0; (pos = str.find_first_of(' ',(pos+1)))!=wxString::npos; )
        {if(((pos-j)*elem)>a) {j=pos; str.SetChar(pos,'\n');}}
    }
}

void EditStringFio (wxString& str)
{
    str.Trim(true); str.Trim(false);
    for(register int i=0, pos=0; i<str.Len();++i) 
    {
        if(wxIsdigit(str[i].GetValue())) {pos=i; str.Truncate(pos); break;} //����� ������ ����� � �������� ������ � ������� � ������� ������ ����� �� ����� ������
    }
    str.MakeCapitalized(); //������ ������ ������ ������ �������� � �������� ��������, ��� ������ � �������
    for(register int i=0,pos=0,pos_old=0, k=0; i<str.Freq(' ');++i)
    {
        pos=str.find_first_of(' ',pos+1); //����� ������� �������
        if ((pos+1)<str.Len()) //���� ��������� ������� �� ��������� ����� ������
        {
            str[pos+1]=wxToupper(str[pos+1].GetValue()); //�������� � ������� ������� ������ ��������� �� ��������
            str.SetChar(pos+2,'.'); //�������� ������ ������ ����� ������� �� �����
            ++k; //������������ ���������� �����
            if(k==2) {str.Remove(pos+3); }  //���� ���-�� ����� ����� ����, �� �������� ������ ������� � ������� ���������� �� ������ ������              
            if(pos_old!=0&&pos_old<pos) {str.Remove(pos_old,pos-pos_old);} //������� ������� ����� ������ � ��������� ��������� ��������
            pos_old=pos+3;  //����������� ���������� ������� ����� �����
        }            
    } 
    str.Trim(true); str.Trim(false);
}

void EditStringFioFull (wxString& str)
{
    str.Trim(true); str.Trim(false);
    str.MakeCapitalized(); //������ ������ ������ ������ �������� � �������� ��������, ��� ������ � �������
    for(register int i=0,pos=0; i<str.Freq(' ');++i)
    {
        pos=str.find_first_of(' ',pos+1); //����� ������� �������
        if ((pos+1)<str.Len()) //���� ��������� ������� �� ��������� ����� ������
        {
            str[pos+1]=wxToupper(str[pos+1].GetValue()); //�������� � ������� ������� ������ ��������� �� ��������
        }            
    }
}

int proverka_bl_sb(MYSQL* conn, wxString& str, int type)
{
    /*
    *type ���������� ��� ��������: 0-��, 1-�������; str - ��� ��� ��, ��� ��� ������
    */
    switch(type)
    {
        case 0:
            {
                MYSQL_ROW row;
                MYSQL_RES *res;
                int num_fields, num_rows;
                wxString sqlText;
                sqlText<<wxSqlTextSelBadTo;
                sqlText<<str; sqlText<<wxSqlEndText;
                
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR); return 0;} 
                {
                    res = mysql_store_result(conn); // ����� ���������,
                    num_rows = mysql_num_rows(res); // � ���������� �����.
                    if(num_rows>0)
                    {
                        if(wxMessageBox(wxQUESTION_BL_SB,wxATTENTION,wxYES_NO)==wxYES)
                        {
                            row = mysql_fetch_row(res); //����� ������ ������ �������
                            wxString result; result="";
                            for (; row; row = mysql_fetch_row(res)) // ����� �������
                            {
                                result+=row[2]; result+="\t"; result+=row[0]; result+="\t"; result+=row[1];
                                result+="\n"; result+="�����������: "; result+=row[3];
                                result+="\n\n";
                            }
                            mysql_free_result(res); // ������� ����������
                            result+="���������� ��������?";
                            if(wxMessageBox(result,wxCAPTION_BL_SB,wxYES_NO)==wxYES)
                            {return 1;} else {return 0;}
                        } else {mysql_free_result(res); return 0;}
                    } else {mysql_free_result(res); return 1;}
                }
            }
        case 1:
            {
                MYSQL_ROW row;
                MYSQL_RES *res;
                int num_fields, num_rows;
                wxString sqlText;
                sqlText<<wxSqlTextSelBadFl;
                sqlText<<str; sqlText<<wxSqlPercentEnd;
                
                if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR); return 0;} 
                {
                    res = mysql_store_result(conn); // ����� ���������,
                    num_rows = mysql_num_rows(res); // � ���������� �����.
                    if(num_rows>0)
                    {
                        if(wxMessageBox(wxQUESTION_BL_SB,wxATTENTION,wxYES_NO)==wxYES)
                        {
                            row = mysql_fetch_row(res); //����� ������ ������ �������
                            wxString result; result="";
                            for (; row; row = mysql_fetch_row(res)) // ����� �������
                            {
                                result+=row[2]; result+="\t"; result+=row[0]; result+="\t"; result+=row[1];
                                result+="\n"; result+="�����������: "; result+=row[3];
                                result+="\n\n";
                            }
                            mysql_free_result(res); // ������� ����������
                            result+="���������� ��������?";
                            if(wxMessageBox(result,wxCAPTION_BL_SB,wxYES_NO)==wxYES)
                            {return 1;} else {return 0;}
                        } else {mysql_free_result(res); return 0;}
                    } else {mysql_free_result(res); return 1;}
                }
            }
        default: return 1;
    }
}
void SaveDataIntoFile (wxWindow* parent, wxString& sLine, wxString& sqlText)
{
    wxDir dir(wxGetCwd());
    if (!dir.IsOpened()) { wxMessageBox(wxERROR_OPEN_PROGRAM,wxERROR); return;}
    else
    {
        wxString srtCaption, strWildcard, strDefaultDir, strDefaultFileName, strPath/*, sqlText*/;
        srtCaption = "��������� ����";
        strWildcard = "TXT files (*.txt)|*.txt|CSV files (*.csv)|*.csv|XLS files (*.xls)|*.xls";
        strDefaultDir = dir.GetName();
        strDefaultFileName = wxEmptyString;
        wxFileDialog dialog (parent, srtCaption, strDefaultDir, strDefaultFileName, strWildcard, wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if (dialog.ShowModal()==wxID_OK)
        {
            strPath = dialog.GetPath();
            //sqlText=wxSqlTextSelAllContactInFile;
            //if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
            if (mysql_query(conn, sqlText.c_str())>0) {wxMessageBox(mysql_error(conn),wxERROR,wxOK|wxCENTRE|wxICON_ERROR);}
            else
            {
                MYSQL_RES *res = mysql_store_result(conn); // ����� ���������,
                int num_fields = mysql_num_fields(res); // ���������� �����
                int num_rows = mysql_num_rows(res); // � ���������� �����.

                if(num_rows>0)
                {                     
                    wxCSConv convFrom(wxFONTENCODING_CP1251);
                    wxCSConv convTo(wxFONTENCODING_ISO8859_5);
                    wxTextFile file(strPath);
                    if(file.Exists()) {file.Open(); file.Clear();} else {file.Create(); file.Open();} //���� ���� ����������, �� ��������� � ������� ������. ���� �� ���������� �� ������� � ���������
                    if(file.IsOpened()) //���� ���� ������
                    {
                        for (register int i = 0, j=0; i < num_rows; i++) // ����� �������
                        {
                            wxString strLine;
                            if(j==0) 
                            {
                                //strLine = "���\t������������ ��������\t������\t������������ ��������\t�������� �������\t����������\t���.�������\t�����������"; 
                                strLine = sLine;
                                j=1; 
                                file.AddLine(strLine); 
                                strLine.Clear();
                            }
                            MYSQL_ROW row = mysql_fetch_row(res); // �������� ������
                            for (register int l = 0; l < num_fields; l++)
                            {
                                wxString str = row[l];
                                if(str.IsNumber()&&!str.IsEmpty()&&(dialog.GetFilterIndex()==1||dialog.GetFilterIndex()==2)) {str='\'' + str;} //���� ������� ���������� csv/xls, �� ����� ������� ������ ��������, ����� ������������� ����� � �����
                                if(l==0) {} else {strLine+='\t';}
                                if(l==(num_fields-1)) {wxString strOld1='\n', strOld2='\r', strNew=' '; str.Replace(strOld1,strNew,true); str.Replace(strOld2,strNew,true);}
                                        
                                //if(convFrom.IsOk()&&convTo.IsOk())
                                //{
                                //strLine+=wxString(str.wc_str(convFrom), wxConvLocal);
                                //}
                                //strLine+=wxString((const char*)str.c_str(), convTo);
                                strLine+=str;
                            }
                            file.AddLine(strLine); //��������� ������ � �����
                        }
                    }
                    file.Write(wxTextFileType_None,convFrom); //���������� ���� �� ����
                    file.Close(); //��������� ���� � ����������� ������
                } else {;}
                mysql_free_result(res); // ������� ����������
            }
        }
    }
}
