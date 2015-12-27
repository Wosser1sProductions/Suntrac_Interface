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

list<display*>* string_to_ascii(string input)
{
	list<display*> *karakter  = new list<display*>();


//    char c = NULL;
//    int karakters;

//    unsigned lengte = input.length();

//    for(int i = 0; i < lengte; i++)                                                 //voor de volledige lengte van de string char omzette naar int
//    {
//        c = input[i];
//        karakters = c;

//        karakter.push_back(new display(karakters));                                 //karakters appart opslaan
//    }

	for (char c : input) {
		karakter->push_back(new display(c));
	}

	return karakter;
}

list<knop*>* xmlVerwerker (string path)
{
    int ID;
    string button;
	list<knop*> *knoppen = new list<knop*>();

    QFile *xmlFile = new QFile (path.c_str());

    if (!xmlFile -> open(QIODevice::ReadOnly | QIODevice::Text))                    //geeft een melding bij fout van het inlezen van xml
    {
        QMessageBox messageBox;
        QMessageBox::critical(nullptr,"Error", "kon MidiCommand.xml niet inlezen", QMessageBox::Ok);
        messageBox.setFixedSize(500,200);
		exit(1);
    }

	QXmlStreamReader *xml = new QXmlStreamReader(xmlFile);

	while(!xml->atEnd())
	{
		while(!xml->readNextStartElement()) {
			break;
		}

        if(xml->name() == "Commands")
        {
			if(xml->attributes().hasAttribute("ID")) {
				ID = xml->attributes().value("ID").toInt();
				knoppen->push_back(new knop(ID));
			}
		}

		if(xml->name() == "Command")
		{
			if(xml->attributes().hasAttribute("Button"))                            //er is een button tekst
			{                                                                       //leest de button tekst in achter #
				//button = xml->attributes().value("Button").split('#').at(1).toString().toStdString();

				QVector<QStringRef> splitted = xml->attributes().value("Button").split('#');

				if (splitted.size() > 1) {
					button = splitted.at(1).toString().toStdString();
					knoppen->back()->button = button;
					//nieuw->button = button;
				} else {
					cerr << "WARNING: Command " << ID << "'s Button string has no '#' or nothing following it!" << endl;
				}
			}

			//cout << "ID: " << ID << "   Button tekst: " << button << endl;
		}

//		cout << xml->hasError() << xml->errorString().toStdString();
    }

//    list<knop*>::iterator it;
//    for(it = knoppen->begin(); it != knoppen->end(); ++it)
//    {
//        string_to_ascii(button);                                                    //tekst naar ascii omvormer sturen
//    }

	for (knop* k : *knoppen) {
		k->karakters = string_to_ascii(k->button);
	}

    delete xmlFile;

	return knoppen;
}

void printKnoplijst(list<knop*> *lijst) {
	for (knop* k : *lijst) {
		printf("Button ID = %4d | tekst: %4s | ascii: ", k->ID, k->button.c_str());

		for (display* d : *(k->karakters)) {
			d->printkarakters();
			cout << " ";
		}

		cout << endl;
	}
}

int main()
{
    string path;

	cout <<"Geef de locatie van het xml bestand:" << endl;                           //de locatie van xml bestand
    cin >> path;

	list<knop*> *knoplijst = xmlVerwerker(path);

	cout << endl << "Button List:" << endl;
	printKnoplijst(knoplijst);

	return 0;
}
