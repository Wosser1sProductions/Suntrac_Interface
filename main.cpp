#include <iostream>
#include <QXmlStreamReader>
#include <QtXml>
#include <QMessageBox>
#include <QApplication>
#include <stdlib.h>
#include <display.h>
#include <knop.h>
#include <list>

/* ==================================================== *
 * zoeken van button info in SunLight xml bestand       *
 * deze button info opslaan en verwerken tot ascii code *
 * ==================================================== */

using namespace std;

void string_to_ascii(string input)
{
    list<display*> karakter;
    char c = NULL;
    int karakters;

    unsigned lengte = input.length();

    for(int i = 0; i < lengte; i++)                                                 //voor de volledige lengte van de string char omzette naar int
    {
        c = input[i];
        karakters = c;

        karakter.push_back(new display(karakters));                                 //karakters appart opslaan
    }
}

void xmlVerwerker (string path)
{
    int ID;
    string button;
    list<knop*> knoppen;

    QFile *xmlFile = new QFile (path.c_str());

    if (!xmlFile -> open(QIODevice::ReadOnly | QIODevice::Text))                    //geeft een melding bij fout van het inlezen van xml
    {
        QMessageBox messageBox;
        QMessageBox::critical(nullptr,"Error", "kon MidiCommand.xml niet inlezen", QMessageBox::Ok);
        messageBox.setFixedSize(500,200);
    }

    QXmlStreamReader *xml = new QXmlStreamReader(xmlFile);
    while(!xml->atEnd())
    {
        while(!xml->readNextStartElement() );

        if(xml->name() == "Commands")
        {
            ID = xml->attributes().value("ID").toInt();
            knoppen.push_back(new knop(ID));
            continue;
        }

        if(xml->name() == "Command")
        {
            if(xml->attributes().hasAttribute("Button"))                            //er is een button tekst
            {                                                                       //leest de button tekst in achter #
                button = xml->attributes().value("Button").split('#').at(1).toString().toStdString();
                knoppen.push_back(new knop(button));
            }

            else                                                                    //standaard waarde button tekst = "    "
            {
                continue;
            }

           // cout << "ID: " << ID << "   Button tekst: " << button << endl;
        }

        //cout << xml->hasError() << xml->errorString().toStdString();
    }

    list<knop*>::iterator it;
    for(it = knoppen.begin(); it != knoppen.end(); ++it)
    {
        string_to_ascii(button);                                                    //tekst naar ascii omvormer sturen
    }

    delete xmlFile;
}

int main()
{
    string path;

    cout <<"geef de locatie van het xml bestand" << endl;                           //de locatie van xml bestand
    cin >> path;

    xmlVerwerker(path);
}
