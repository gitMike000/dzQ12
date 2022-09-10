#include "imggui.h"

ImgGUI::ImgGUI(QWidget *parent)
    : QWidget(parent)
{
    downloader = new Downloader(this);
    progressBar = new QProgressBar;
    lineEdit = new QLineEdit;
    pushButton = new QPushButton(tr("Go"));

    connect(pushButton, SIGNAL(clicked()), SLOT(slotGo()));
    connect(downloader, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(slotDownloadProgress(qint64,qint64)));
    connect(downloader, SIGNAL(done(const QUrl&, const QByteArray&)),
            this, SLOT(slotDone(const QUrl&, const QByteArray&)));

    lay = new QGridLayout;
    lay->addWidget(lineEdit, 0, 0);
    lay->addWidget(pushButton, 0, 1);
    lay->addWidget(progressBar, 1, 0, 1, 1);
    setLayout(lay);
}

ImgGUI::~ImgGUI()
{
}

void ImgGUI::showPic(QByteArray &pData, QGridLayout* l)
{
    QPixmap p;
    if(p.loadFromData(pData))//,"JPG"))
    {
        QLabel* label = new QLabel;
        label->setPixmap(p);
        label->setFixedSize(p.size());
        l->addWidget(label, ++row, 0, 1, 1);
    }
}

void ImgGUI::slotGo()
{
    downloader->download(QUrl("https://yandex.ru/images/search?text="+lineEdit->text()));    
}

void ImgGUI::slotError()
{
    QMessageBox::critical(0, tr("Error"), tr("Error download"));
}

void ImgGUI::slotDownloadProgress(qint64 received, qint64 total)
{
//    if (total <= 0) {
//        slotError();
//        return;
//    }
    progressBar->setValue(100*received/total);
}

void ImgGUI::slotDone(const QUrl &url, const QByteArray &ba)
{
    QString rq(ba);

    QRegExp RegExp("<img class=(\".*\") src=\"//(.*)\"");
    RegExp.setMinimal(true);
    int last = 0; int i = 0; row =0;

//    if (imgShow != nullptr) {
//        imgShow->deleteLater();
//    }
    imgShow = new QWidget;
    imgLay = new QGridLayout(imgShow);
    imgShow->setWindowTitle("Images");
    imgShow->setLayout(imgLay);

    while( (( last = RegExp.indexIn( rq, last ) ) != -1) && (i < 3) ) {
        last += RegExp.matchedLength();        

        ImgDownloader = new Downloader(this);
        connect(ImgDownloader, &Downloader::done,
                this,
                [&](const QUrl &url, const QByteArray &tArray)
                {
                    qDebug() << "Done";
                    imgArray = tArray;
                    showPic(imgArray, imgLay);
                });

        connect(ImgDownloader, &Downloader::downloadProgress,
                this,
                [&](qint64 received, qint64 total)
                {
                    if (total<0) {}
                    qDebug() << "Progress";
                    qDebug() << (100*double(received)/double(total));
                });

                connect(ImgDownloader, &Downloader::error,
                        this,
                        [&]()
                        {
                            qDebug() << "Error";
                        });

        qDebug() << RegExp.cap(2);
        ImgDownloader->download(QUrl("https://"+RegExp.cap(2)));
        ++i;
    }
    imgShow->show();
}


