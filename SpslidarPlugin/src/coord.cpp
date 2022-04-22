#include "coord.h"

coord::coord()
{
    easting="0";
    northing="0";
    zone="16N";
    height="0";
}

coord::coord(const QString &easting, const QString &northing, const QString &zone, const QString &height) : easting(easting),
    northing(northing),
    zone(zone),
    height(height)
{}

const QString &coord::getHeight() const
{
    return height;
}

void coord::setHeight(const QString &newHeight)
{
    height = newHeight;
}

const QString &coord::getZone() const
{
    return zone;
}

void coord::setZone(const QString &newZone)
{
    zone = newZone;
}

const QString &coord::getNorthing() const
{
    return northing;
}

void coord::setNorthing(const QString &newNorthing)
{
    northing = newNorthing;
}

const QString &coord::getEasting() const
{
    return easting;
}

void coord::setEasting(const QString &newEasting)
{
    easting = newEasting;
}


