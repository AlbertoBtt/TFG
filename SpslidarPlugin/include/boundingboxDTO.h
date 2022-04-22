#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "coord.h"

class boundingBoxDTO
{
public:
    boundingBoxDTO();
    boundingBoxDTO(const coord &southWestBottom, const coord &northEastTop);
    const coord &getSouthWestBottom() const;
    void setSouthWestBottom(const coord &newSouthWestBottom);
    const coord &getNorthEastTop() const;
    void setNorthEastTop(const coord &newNorthEastTop);
private:
    coord southWestBottom;
    coord northEastTop;
};

#endif // BOUNDINGBOX_H
