#include "data.h"

NameInfo::NameInfo(const QString& name) {
    SetName(name);
}

void NameInfo::SetName(const QString& name)  {
    this->Name = name;
}

void NameInfo::SetSurname(const QString& surname)    {
    this->Surname = surname;
}

void NameInfo::SetFathername_m(const QString& fathername_m)  {
    this->Fathername_m = fathername_m;
}

void NameInfo::SetFathername_f(const QString& fathername_f)  {
    this->Fathername_f = fathername_f;
}

void NameInfo::SetGender(const QChar& gender)    {
    this->Gender = gender;
}

QString NameInfo::GetName(){
    return this->Name;
}

QString NameInfo::GetSurname(){
    if(Surname.isNull())    {
        if(Gender.isNull())
            Gender = GetGender();
        if(Gender == 'm')
            Surname = GenerateSurname(Name);
    }
    return this->Surname;
}

QString NameInfo::GetFathername_m(){
    if(Fathername_m.isNull())
        Fathername_m = GenerateFathername_m(Name);
    return Fathername_m;
}

QString NameInfo::GetFathername_f(){
    if(Fathername_f.isNull())
        Fathername_f = GenerateFathername_f(Name);
    return this->Fathername_f;
}

QChar NameInfo::GetGender(){
    if(Gender.isNull()) {
        Gender = DetermineGender(Name);
    }
    return this->Gender;
}

/*  Функция эврестического определения пола на основании имени      */
QChar NameInfo::DetermineGender(const QString& source)
{
    QChar gender;
    switch(source[source.size() - 1].unicode())
    {
        //  А или Я
        case 1040:  case 1071:  case 1072:  case 1103:
            gender = 'f';
            break;
        default:
            gender = 'm';
    }
    return gender;
}

QString NameInfo::ChangeFormat(const QString& name, const char* addCh, int delCh)
{
    QString source = name;
    if(delCh) source.chop(delCh);
    source.append(addCh);
    return source;
}

/*  Функция эврестического определения отчества на основании имени      */
QString NameInfo::GenerateFathername_m(const QString& name)
{
    QString fathername;
    switch(name[name.size() - 1].unicode())
    {
        case 1040:  case 1072:  //  А
            fathername = ChangeFormat(name, "ович", 1);
            break;
        case 1051:  case 1083:  //  Л
            fathername = ChangeFormat(name, "лович", 2);
            break;
        case 1049:  case 1081:  //  Й
            switch(name[name.size() - 2].unicode())
            {
                case 1048:  case 1080:  //  И
                    fathername = ChangeFormat(name, "ьевич", 2);
                    break;
                default:
                    fathername = ChangeFormat(name, "евич", 1);
                    break;
            }
            break;
        case 1071:  case 1103:  //  Я
            fathername = ChangeFormat(name, "ич", 1);
            break;
        default:
            fathername = ChangeFormat(name, "ович");
    }
    return fathername;
}

QString NameInfo::GenerateFathername_f(const QString& name)
{
    QString fathername;
    switch(name[name.size() - 1].unicode())
    {
        case 1040:  case 1072:  //  А
            fathername = ChangeFormat(name, "овна", 1);
            break;
        case 1051:  case 1083:  //  Л
            fathername = ChangeFormat(name, "ловна", 2);
            break;
        case 1049:  case 1081:  //  Й
            switch(name[name.size() - 2].unicode())
            {
                case 1048:  case 1080:  //  И
                    fathername = ChangeFormat(name, "ьевна", 2);
                    break;
                default:
                    fathername = ChangeFormat(name, "евна", 1);
                    break;
            }
            break;
        case 1071:  case 1103:  //  Я
            fathername = ChangeFormat(name, "инична", 1);
            break;
        default:
            fathername = ChangeFormat(name, "овна");
    }
    return fathername;
}

/*  Функция эврестического определения фамилии на основании имени      */
QString NameInfo::GenerateSurname(const QString& name)
{
    QString surname;
    switch(name[name.size() - 1].unicode())
    {
        case 1040:  case 1072:  //  А
            surname = ChangeFormat(name, "ов", 1);
            break;
        case 1051:  case 1083:  //  Л
            surname = ChangeFormat(name, "лов", 2);
            break;
        case 1049:  case 1081:  //  Й
            switch(name[name.size() - 2].unicode())
            {
                case 1048:  case 1080:  //  И
                    surname = ChangeFormat(name, "ьев", 2);
                    break;
                default:
                    surname = ChangeFormat(name, "ев", 1);
                    break;
            }
            break;
        case 1071:  case 1103:  //  Я
            surname = ChangeFormat(name, "ин", 1);
            break;
        default:
            surname = ChangeFormat(name, "ов");
    }
    return surname;
}
