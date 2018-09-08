#include "CrossFrm.h"

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

void insertStrDateToCtrl (wxString& str, wxDatePickerCtrl* window); //функция если может распознает дату в тексте и вставляет найденное значение в поле даты
void EditTheLine(wxString &str, wxWindow* win); //функция подгодняеет строку под размеры окна win вставляя символы \n
void InformationSleep (wxString str, int sec, wxWindow * parent); //функция выводит предупреждающее сообщение str, которое висит перед пользователем sec секунд
void EditStringFio (wxString& str); //функция редактирует строку wxString меняя ИВАНОВ ИВАН ИВАНОВИЧ на Иванов И.И.
void EditStringFioFull (wxString& str); //функция редактирует строку wxString меняя ИВАНОВ ИВАН ИВАНОВИЧ на Иванов Иван Иванович
int proverka_bl_sb(MYSQL* conn, wxString& str, int type); //функция проверяет str на предмет наличия в ЧС СБ. type - тип ЧС СБ для проверки, 0 - ТО, 1 - физики
void SaveDataIntoFile (wxWindow* parent, wxString& sLine, wxString& sqlText); //функция сохраняет результат выполения sql-запроса в файл, заголовки колонок = sLine

void insertStrDateToCtrl (wxString& str, wxDatePickerCtrl* window)
{
    if(!str.IsEmpty())
    {
        wxDateTime dt;                  //создаем объект класса wxDateTime
        wxString::const_iterator end;   //создаем итератор указывающий на конец строки, где был остановлени синтаксический разбор
        dt.ParseDate(str, &end);        //анализируем строку и распознаем дату
        if (dt.IsValid())               //проверяем, что объект представляет собой правильный момент времени
        {
            window->SetValue(dt); //присваиваем найденное значение в контрол с датой
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
        wxClientDC *dc = new wxClientDC(win); //создаем указатель на контекст устройства
        wxSize sizeStr = dc->GetTextExtent(str); //определяем длину строки в пикселях
        delete dc;
                        
        wxSize sizeWin = win->GetClientSize(); //определяем размеры клиентской области окна
        int elem = sizeStr.GetWidth()/str.Len(); //определяем ширину одного символа в пикселях

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
        if(wxIsdigit(str[i].GetValue())) {pos=i; str.Truncate(pos); break;} //нашли первую цифру и обрезали строку с начиная с позиции первой цифры до конца строки
    }
    str.MakeCapitalized(); //Первый символ начала строки приводим к верхнему регистру, все прочие к нижнему
    for(register int i=0,pos=0,pos_old=0, k=0; i<str.Freq(' ');++i)
    {
        pos=str.find_first_of(' ',pos+1); //нашли позицию пробела
        if ((pos+1)<str.Len()) //если найденная позиция не превышает длину строки
        {
            str[pos+1]=wxToupper(str[pos+1].GetValue()); //возводим в верхний регистр символ следующий за пробелом
            str.SetChar(pos+2,'.'); //заменяем второй символ после пробела на точку
            ++k; //подсчитываем количество точек
            if(k==2) {str.Remove(pos+3); }  //если кол-во точек равно двум, то обрезаем строку начиная с символа следующего за второй точкой              
            if(pos_old!=0&&pos_old<pos) {str.Remove(pos_old,pos-pos_old);} //удаляем символы между точкой и следующим найденным пробелом
            pos_old=pos+3;  //присваиваем переменной позицию после точки
        }            
    } 
    str.Trim(true); str.Trim(false);
}

void EditStringFioFull (wxString& str)
{
    str.Trim(true); str.Trim(false);
    str.MakeCapitalized(); //Первый символ начала строки приводим к верхнему регистру, все прочие к нижнему
    for(register int i=0,pos=0; i<str.Freq(' ');++i)
    {
        pos=str.find_first_of(' ',pos+1); //нашли позицию пробела
        if ((pos+1)<str.Len()) //если найденная позиция не превышает длину строки
        {
            str[pos+1]=wxToupper(str[pos+1].GetValue()); //возводим в верхний регистр символ следующий за пробелом
        }            
    }
}

int proverka_bl_sb(MYSQL* conn, wxString& str, int type)
{
    /*
    *type определяет тип проверки: 0-ТО, 1-физлица; str - или ИНН ТО, или ФИО физика
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
                    res = mysql_store_result(conn); // Берем результат,
                    num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {
                        if(wxMessageBox(wxQUESTION_BL_SB,wxATTENTION,wxYES_NO)==wxYES)
                        {
                            row = mysql_fetch_row(res); //берем первую строку выборки
                            wxString result; result="";
                            for (; row; row = mysql_fetch_row(res)) // Вывод таблицы
                            {
                                result+=row[2]; result+="\t"; result+=row[0]; result+="\t"; result+=row[1];
                                result+="\n"; result+="Комментарий: "; result+=row[3];
                                result+="\n\n";
                            }
                            mysql_free_result(res); // Очищаем результаты
                            result+="Продолжить операцию?";
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
                    res = mysql_store_result(conn); // Берем результат,
                    num_rows = mysql_num_rows(res); // и количество строк.
                    if(num_rows>0)
                    {
                        if(wxMessageBox(wxQUESTION_BL_SB,wxATTENTION,wxYES_NO)==wxYES)
                        {
                            row = mysql_fetch_row(res); //берем первую строку выборки
                            wxString result; result="";
                            for (; row; row = mysql_fetch_row(res)) // Вывод таблицы
                            {
                                result+=row[2]; result+="\t"; result+=row[0]; result+="\t"; result+=row[1];
                                result+="\n"; result+="Комментарий: "; result+=row[3];
                                result+="\n\n";
                            }
                            mysql_free_result(res); // Очищаем результаты
                            result+="Продолжить операцию?";
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
        srtCaption = "Сохранить файл";
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
                MYSQL_RES *res = mysql_store_result(conn); // Берем результат,
                int num_fields = mysql_num_fields(res); // количество полей
                int num_rows = mysql_num_rows(res); // и количество строк.

                if(num_rows>0)
                {                     
                    wxCSConv convFrom(wxFONTENCODING_CP1251);
                    wxCSConv convTo(wxFONTENCODING_ISO8859_5);
                    wxTextFile file(strPath);
                    if(file.Exists()) {file.Open(); file.Clear();} else {file.Create(); file.Open();} //если файл существует, то открываем и удаляем строки. Если не существует то создаем и открываем
                    if(file.IsOpened()) //если файл открыт
                    {
                        for (register int i = 0, j=0; i < num_rows; i++) // Вывод таблицы
                        {
                            wxString strLine;
                            if(j==0) 
                            {
                                //strLine = "Тип\tНаименование компании\tРегион\tНаименование контакта\tОсновной телефон\tДобавочный\tДоп.телефон\tКомментарий"; 
                                strLine = sLine;
                                j=1; 
                                file.AddLine(strLine); 
                                strLine.Clear();
                            }
                            MYSQL_ROW row = mysql_fetch_row(res); // получаем строку
                            for (register int l = 0; l < num_fields; l++)
                            {
                                wxString str = row[l];
                                if(str.IsNumber()&&!str.IsEmpty()&&(dialog.GetFilterIndex()==1||dialog.GetFilterIndex()==2)) {str='\'' + str;} //если выбрано расширение csv/xls, то перед числами ставим апостроф, чтобы преобразовать число в текст
                                if(l==0) {} else {strLine+='\t';}
                                if(l==(num_fields-1)) {wxString strOld1='\n', strOld2='\r', strNew=' '; str.Replace(strOld1,strNew,true); str.Replace(strOld2,strNew,true);}
                                        
                                //if(convFrom.IsOk()&&convTo.IsOk())
                                //{
                                //strLine+=wxString(str.wc_str(convFrom), wxConvLocal);
                                //}
                                //strLine+=wxString((const char*)str.c_str(), convTo);
                                strLine+=str;
                            }
                            file.AddLine(strLine); //добавляем строку в конец
                        }
                    }
                    file.Write(wxTextFileType_None,convFrom); //записываем файл на диск
                    file.Close(); //закрываем файл и освобождаем память
                } else {;}
                mysql_free_result(res); // Очищаем результаты
            }
        }
    }
}
