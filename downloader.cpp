#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotFinished(QNetworkReply*)));
}

void Downloader::download(const QUrl & url)
{
    QNetworkRequest request(url);
    QNetworkReply* rep = nam->get(request);
    connect(rep, SIGNAL(downloadProgress(qint64, qint64)),
            this, SIGNAL(downloadProgress(qint64, qint64)));
}

void Downloader::slotFinished(QNetworkReply* rep)
{
    if (rep->error()!=QNetworkReply::NoError) {
        emit error();
    } else {
        emit done(rep->url(), rep->readAll());
    }
    rep->deleteLater();
}
