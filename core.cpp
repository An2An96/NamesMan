QList<FullName> GenerateNameRecords(QList<NameInfo>& info)
{
    QList<FullName> Records;
    for(QList<NameInfo>::iterator s = info.begin(); s < info.end(); s++)
    {
        for(QList<NameInfo>::iterator n = info.begin(); n < info.end(); n++)
        {
            for(QList<NameInfo>::iterator f = info.begin(); f < info.end(); f++)
            {
                FullName fn;
                fn.Surname = s->GetSurname();
                fn.Name = n->GetName();
                if(n->GetGender() == 'm')   {
                    fn.Fathername = f->GetFathername_m();
                }
                else    {
                    fn.Fathername = f->GetFathername_f();
                }
                Records += fn;
            }
        }
    }
    return Records;
}

void VerifyNames(QList<FullName>& vrec, QList<NameInfo>& info, QTextStream& log)
{
    //  Проверяем имена
    bool find = false;
    for(QList<FullName>::iterator cur_vr = vrec.begin(); cur_vr < vrec.end(); cur_vr++)
    {
        qDebug() << cur_vr->Name;

        for(QList<NameInfo>::iterator cur_inf = info.begin(); cur_inf < info.end(); cur_inf++)
        {
            if(cur_vr->Name == cur_inf->GetName())  {
                find = true;
            }
        }
        if(find == false)   {
            log << QString(QString::fromUtf8("Неизвестное имя ")) << cur_vr->Name << endl;
            QChar gender = NameInfo::DetermineGender(cur_vr->Name);  //  определяем пол
            qDebug() << "Определенный пол: " << gender;
        }
        find = false;
    }

    //  Проверяем фамилии
    for(QList<FullName>::iterator cur_vr = vrec.begin(); cur_vr < vrec.end(); cur_vr++)
    {
        qDebug() << cur_vr->Surname;

        for(QList<NameInfo>::iterator cur_inf = info.begin(); cur_inf < info.end(); cur_inf++)
        {
            if(cur_vr->Surname == cur_inf->GetSurname())  {
                find = true;
                if(cur_inf->CheckKind(cur_vr->Name, cur_vr->Surname) == false)   {
                    log << QString(QString::fromUtf8("Рода имени и фамилии не совпадают")) << endl;
                }
            }
        }
        if(find == false)   {
            log << QString(QString::fromUtf8("Неизвестная фамилия ")) << cur_vr->Surname << endl;
            QChar gender = NameInfo::DetermineGender(cur_vr->Surname);  //  определяем пол
            qDebug() << "Определенный пол: " << gender;
        }
        find = false;
    }

    //  Проверяем отчества
    for(QList<FullName>::iterator cur_vr = vrec.begin(); cur_vr < vrec.end(); cur_vr++)
    {
        qDebug() << cur_vr->Fathername;

        for(QList<NameInfo>::iterator cur_inf = info.begin(); cur_inf < info.end(); cur_inf++)
        {
            if(cur_vr->Fathername == cur_inf->GetFathername_m())  {
                find = true;
                if(cur_inf->CheckKind(cur_vr->Name, cur_vr->Fathername) == false)   {
                    log << QString(QString::fromUtf8("Рода имени и фамилии не совпадают")) << endl;
                }
            }
        }
        if(find == false)   {
            log << QString(QString::fromUtf8("Неизвестное отчество ")) << cur_vr->Fathername << endl;
            QChar gender = NameInfo::DetermineGender(cur_vr->Fathername);  //  определяем пол
            qDebug() << "Определенный пол: " << gender;
        }
        find = false;
    }
}
