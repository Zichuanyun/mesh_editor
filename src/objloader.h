#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "meshcomponents.h"

class OBJLoader
{
public:
    OBJLoader();
    void loadOBJ();
    void loadJASON();
    void loadOBJ(std::vector<Vertex*>& verts, std::vector<Face*>& faces, std::vector<HalfEdge*>& halfedges);
};

#endif // OBJLOADER_H
