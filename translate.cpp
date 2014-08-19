#include "translate.h"
#include "ui_translate.h"

Translate::Translate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Translate)
{
    ui->setupUi(this);
    translatingFilePath="";
    googleTranlatedFilePath="";
    googleTranlatingFileSavePath="";
    updatingTsFilePath="";

}

Translate::~Translate()
{
    delete ui;
}


void Translate::selectTranslatingFileClicked()
{
    translatingFilePath=QFileDialog::getOpenFileName(this, tr("Select .ts file need to tranlate"),"D:/dk work/Motarola");
    ui->lETranlatingFilePath->setText(translatingFilePath);


}

void Translate::selectGoogleTranslatedFileClicked()
{
    googleTranlatedFilePath=QFileDialog::getOpenFileName(this, tr("Select Google translation input file Save Directry"),"D:/dk work/Motarola");
    ui->lEGoogleTranlatedFile->setText(googleTranlatedFilePath);


}

void Translate::selectGoogleTranslatedFileSavePathClicked()
{
    googleTranlatingFileSavePath=QFileDialog::getExistingDirectory(this, tr("Select Googe translated File"),"D:/dk work/Motarola");
    ui->lEgoogletranlatedfileSavePath->setText(googleTranlatingFileSavePath);

}

void Translate::selectUpdatingTsFileClicked()
{
    updatingTsFilePath=QFileDialog::getOpenFileName(this, tr("Select Qt .ts file to tranlate"),"D:/dk work/Motarola");
    ui->lEupdatingTsFile->setText(updatingTsFilePath);


}

void Translate::genarateGoogleTranlatingInputFileClicked()
{

    if(translatingFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select .ts file that need to translate");
        return;
    }

    if(googleTranlatingFileSavePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select Directry to save Google tranlation file");
        return;

    }


    QFile tranlatingFile(translatingFilePath);

    if(!tranlatingFile.open(QFile::ReadWrite| QIODevice::Text))
    {
        qDebug()<<"error";

    }
    else
    {
        QFile googleTranlatingFile(googleTranlatingFileSavePath+"/"+"googleTranlatingFile.txt");
        if(!googleTranlatingFile.open(QFile::ReadWrite| QIODevice::Text))
        {
            qDebug()<<"error";

        }
        else
        {

            QTextStream googletranlateFileGenarate(&googleTranlatingFile);



            QDomDocument document;

            document.setContent(&tranlatingFile);
            QDomElement root= document.firstChildElement();


            QDomNodeList context = root.elementsByTagName("context");

            for(int j=0;j<context.count();j++)
            {
                QDomNodeList messages=context.at(j).toElement().elementsByTagName("message");


                for(int i=0;i<messages.count();i++)
                {

                    QString source=messages.at(i).toElement().elementsByTagName("source").at(0).firstChild().nodeValue();
                    googletranlateFileGenarate<<source<<"\n";


                }

            }


        }



    googleTranlatingFile.close();
    tranlatingFile.close();
    QMessageBox::information(this,"Success","Google Tranlating File Created");




     }


}

void Translate::genarateUpdateTsFileClicked()
{

    if(googleTranlatedFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select Google tranlated File");
        return;
    }

    if(updatingTsFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select .ts File that need to Translate");
        return;

    }



    QFile googleTranlatedFile(googleTranlatedFilePath);
     googleTranlatedFile.open(QIODevice::ReadOnly | QIODevice::Text);


    QTextStream in(&googleTranlatedFile);
    while(!in.atEnd())
    {

        QString line = in.readLine();       
        translatedStringList.append(line);


    }


    QFile updatingTsFile(updatingTsFilePath);
    //set tranlating strings
    if(!updatingTsFile.open(QFile::ReadWrite| QIODevice::Text))
    {
        qDebug()<<"error";

    }
    else
    {
            QDomDocument document;

            document.setContent(&updatingTsFile);
            QDomElement root= document.firstChildElement();           


            QDomNodeList context = root.elementsByTagName("context");

            int x=0;

            for(int j=0;j<context.count();j++)
            {      
                QDomNodeList messages=context.at(j).toElement().elementsByTagName("message");


                for(int i=0;i<messages.count();i++)
                {
                    QDomElement tranlation=document.createElement("translation");
                    tranlation.appendChild(document.createTextNode(translatedStringList.at(x)));


                    messages.at(i).toElement().removeChild(messages.at(i).toElement().elementsByTagName("translation").at(0));
                    messages.at(i).toElement().appendChild(tranlation);





                    x++;


                }

            }

            document.appendChild(root);
            updatingTsFile.close();


            if(!updatingTsFile.open(QFile::ReadWrite|QIODevice::Truncate | QIODevice::Text))
            {
                qDebug()<<"error";

            }
            else
            {

                QTextStream stream(&updatingTsFile);
                stream.setCodec("UTF-8"); // change the file codec to UTF-8.
                stream <<document.toString();
                updatingTsFile.close();
                QMessageBox::information(this,"Success","Tranlated .ts File");



            }


         googleTranlatedFile.close();





     }


}
