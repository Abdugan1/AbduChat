#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <QDataStream>

class DataStream : public QDataStream
{
public:
    explicit DataStream(QIODevice *ioDevice)
        : QDataStream(ioDevice)
    {
        setVersion(Qt_5_15);
    }
};

#endif // DATASTREAM_H
