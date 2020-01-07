#ifndef DEBUG_H
#define DEBUG_H

#include <QObject>

class debug : public QObject
{
    Q_OBJECT
public:
    explicit debug(QObject *parent = nullptr);
    void debug_str(QString msg, unsigned char *pBuf, unsigned short size);
    void debug_str(QString msg, const unsigned char *pBuf, unsigned short size);
    void debug_str(QString msg, QByteArray arr);
    void debug_str(QByteArray arr);

signals:

public slots:
};

#endif // DEBUG_H
