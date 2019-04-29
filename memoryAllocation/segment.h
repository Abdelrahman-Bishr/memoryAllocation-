#ifndef SEGMENT_H
#define SEGMENT_H
#include <QString>


class Segment
{

public:
    Segment(QString segName, int segSize);
    QString getName();
    int getSize();
private:
    QString name;
    int size;
};

#endif // SEGMENT_H
