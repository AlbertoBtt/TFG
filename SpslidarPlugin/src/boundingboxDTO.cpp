#include "boundingboxDTO.h"

boundingBoxDTO::boundingBoxDTO()
{
    southWestBottom=coord();
    northEastTop=coord();
}

const coord &boundingBoxDTO::getNorthEastTop() const
{
    return northEastTop;
}

void boundingBoxDTO::setNorthEastTop(const coord &newNorthEastTop)
{
    northEastTop = newNorthEastTop;
}

const coord &boundingBoxDTO::getSouthWestBottom() const
{
    return southWestBottom;
}

void boundingBoxDTO::setSouthWestBottom(const coord &newSouthWestBottom)
{
    southWestBottom = newSouthWestBottom;
}

boundingBoxDTO::boundingBoxDTO(const coord &southWestBottom, const coord &northEastTop) : southWestBottom(southWestBottom),
    northEastTop(northEastTop)
{}
