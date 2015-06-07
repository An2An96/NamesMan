#pragma once

#include <QString>

struct FullName {
    QString Surname;
    QString Name;
    QString Fathername;
};

class NameInfo  {
public:
    NameInfo(const QString& name);

    void SetName(const QString&);
    void SetSurname(const QString&);
    void SetFathername_m(const QString&);
    void SetFathername_f(const QString&);
    void SetGender(const QChar&);

    QString GetName();
    QString GetSurname();
    QString GetFathername_m();
    QString GetFathername_f();
    QChar GetGender();

    static QString GenerateSurname(const QString&);
    static QString GenerateFathername_m(const QString&);
    static QString GenerateFathername_f(const QString&);
    static QChar DetermineGender(const QString&source);
    static bool CheckKind(const QString&, const QString&);

private:
    static QString ChangeFormat(const QString&, const char*, int = 0);

    QString Name,
            Surname,
            Fathername_m,
            Fathername_f;
    QChar   Gender;
};
