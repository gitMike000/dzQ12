#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    void download(const QUrl&);

private:
    QNetworkAccessManager* nam;

signals:
    void downloadProgress(qint64, qint64);
    void done(const QUrl&, const QByteArray&);
    void error();

public slots:
    void slotFinished(QNetworkReply*);
};

#endif // DOWNLOADER_H
