QList<NameInfo> ReadNameInfo(QTextStream& stream)
{
    QList<NameInfo> Names;
    QString line;
    bool readProperty = false,
         readError = false,
         nameGiven = false;
    char key[64], value[128];
    do {
        line = stream.readLine();
        if(line.size()) {
            if(readProperty == false && line == "{") {
                if(nameGiven == false)
                {
                    qDebug() << "Error!";
                    readError = true;
                    continue;
                }
                readProperty = true;
            }
            else if(readProperty && line == "}") {
                readProperty = false;
                nameGiven = false;
                readError = false;
            }
            else
            {
                if(readError)   continue;
                if(readProperty)
                {
                    QList<NameInfo>::iterator it = Names.end() - 1;
                    if(line.count("Surname", Qt::CaseInsensitive))
                    {
                        sscanf(qPrintable(line), "%[^=]=%s", key, value);
                        it->SetSurname(QString(QString::fromLocal8Bit(value)));
                    }
                    else if(line.count("Fathername_m", Qt::CaseInsensitive))
                    {
                        sscanf(qPrintable(line), "%[^=]=%s", key, value);
                        it->SetFathername_m(QString(QString::fromLocal8Bit(value)));
                    }
                    else if(line.count("Fathername_f", Qt::CaseInsensitive))
                    {
                        sscanf(qPrintable(line), "%[^=]=%s", key, value);
                        it->SetFathername_f(QString(QString::fromLocal8Bit(value)));
                    }
                    else if(line.count("Gender", Qt::CaseInsensitive))
                    {
                        sscanf(qPrintable(line), "%[^=]=%s", key, value);
                        it->SetGender(QChar(value[0]));
                    }
                }
                else
                {
                    sscanf(qPrintable(line), "%s", value);
                    Names += NameInfo(QString(QString::fromLocal8Bit(value)));
                    nameGiven = true;
                }
            }
        }
    } while (!line.isNull());
    return Names;
}

QList<FullName> ReadNameRecords(QTextStream& stream)
{
    QList<FullName> Names;
    QString line;
    char Surname[32], Name[32], Fathername[32];
    do {
        line = stream.readLine();
        if(line.size()) {
            QByteArray ar = line.toLocal8Bit();
            char *sBuf = ar.data();

            sscanf(sBuf, "%s %s %s", Surname, Name, Fathername);

            FullName fn;
            fn.Surname = QString(QString::fromLocal8Bit(Surname));
            fn.Name = QString(QString::fromLocal8Bit(Name));
            fn.Fathername = QString(QString::fromLocal8Bit(Fathername));
            Names += fn;
        }
    } while (!line.isNull());
    return Names;
}

void WriteNameRecords(QTextStream& stream, QList<FullName>& vrec)
{
    for(QList<FullName>::iterator it = vrec.begin(); it < vrec.end(); it++) {
        stream << it->Surname << " " << it->Name << " " << it->Fathername << endl;
    }
}
