#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QFile>
#include <QtXml>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>

namespace Ui {
class Translate;
}

class Translate : public QDialog
{
    Q_OBJECT
    
public:
    explicit Translate(QWidget *parent = 0);
    ~Translate();
    
private:
    Ui::Translate *ui;
    QString translatingFilePath;
    QString googleTranlatedFilePath;
    QString googleTranlatingFileSavePath;
    QString updatingTsFilePath;
    QStringList translatedStringList;

private slots:
    void selectTranslatingFileClicked();
    void selectGoogleTranslatedFileClicked();
    void genarateGoogleTranlatingInputFileClicked();
    void genarateUpdateTsFileClicked();
    void selectGoogleTranslatedFileSavePathClicked();
    void selectUpdatingTsFileClicked();
};

#endif // TRANSLATE_H
