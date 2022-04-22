#ifndef COORD_H
#define COORD_H
#include <QtCore>

class coord
{
public:
    coord();
    coord(const QString &easting, const QString &northing, const QString &zone, const QString &height);
    const QString &getHeight() const;
    void setHeight(const QString &newHeight);

    const QString &getZone() const;
    void setZone(const QString &newZone);

    const QString &getNorthing() const;
    void setNorthing(const QString &newNorthing);

    const QString &getEasting() const;
    void setEasting(const QString &newEasting);

private:
    QString easting;
    QString northing;
    QString zone;
    QString height;
};

#endif // COORD_H
