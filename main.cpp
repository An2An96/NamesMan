#define _CRT_SECURE_NO_WARNINGS

#include <QCoreApplication>
#include <QList>
#include <QFile>
#include <QTextStream>

#include <QDebug>

#include "data.h"       //  реализация класса с данными об именах
#include "loader.cpp"   //  реализация выгрузок и сохранений из файла
#include "core.cpp"     //  реализация требуемых действий

void ShowNameInfo(QList<NameInfo>& ni)
{
    for(QList<NameInfo>::iterator it = ni.begin(); it < ni.end(); it++) {
        qDebug() << "Имя: " << it->GetName() << ", Фамилия: " << it->GetSurname() << ", Отчество М: " << it->GetFathername_m() << ", Отчество Ж: " << it->GetFathername_f() << ", Пол: " << it->GetGender();
    }
}

void ShowNameRecord(QList<FullName>& nr)
{
    for(QList<FullName>::iterator it = nr.begin(); it < nr.end(); it++) {
        qDebug() << it->Surname << it->Name << it->Fathername;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_ALL, "russian");

    QList<NameInfo> VecNameInfo;
    QList<FullName> VecNameRecord;

    QFile file("C:/Qt/Projects/NamesMan/name.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        VecNameInfo = ReadNameInfo(stream);
    }
    file.close();

    file.setFileName("C:/Qt/Projects/NamesMan/fio.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        VecNameRecord = ReadNameRecords(stream);
    }
    file.close();

    file.setFileName("C:/Qt/Projects/NamesMan/log.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        VerifyNames(VecNameRecord, VecNameInfo, stream);
    }
    file.close();

    ShowNameInfo(VecNameInfo);
    ShowNameRecord(VecNameRecord);
    return a.exec();
}
