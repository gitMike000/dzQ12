#ifndef IMGGUI_H
#define IMGGUI_H

#include <QWidget>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

#include <QUrl>
#include <QStandardPaths>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>

#include "downloader.h"

class ImgGUI : public QWidget
{
    Q_OBJECT

public:
    ImgGUI(QWidget *parent = nullptr);
    ~ImgGUI();

private:
    Downloader* downloader;    
    QProgressBar* progressBar;
    QLineEdit* lineEdit;
    QPushButton* pushButton;    
    QGridLayout* lay;

    Downloader* ImgDownloader;
    QWidget* imgShow = nullptr;
    QGridLayout* imgLay;


    int row;

public:
    QByteArray imgArray;

    void showPic(QByteArray&, QGridLayout*);

private slots:
    void slotGo();
    void slotError();
    void slotDownloadProgress(qint64, qint64);
    void slotDone(const QUrl&, const QByteArray&);

};
#endif // IMGGUI_H
