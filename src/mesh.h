#ifndef MESH_H
#define MESH_H
#include "drawable.h"
#include "meshcomponents.h"
#include "objloader.h"


class Mesh : public Drawable
{
public:
    Mesh(GLWidget277 *context);
    void create();
    ~Mesh();

    OBJLoader objLoader;

    void generateCubeHalfEdgeData();

    std::vector<Vertex*> m_verts;
    std::vector<Face*> m_faces;
    std::vector<HalfEdge*> m_halfedges;

    void addVert(HalfEdge* i_halfEdge);
    void triangulateFace(Face* i_face);

    void subdivision();

    void loadFromFile();

    void extrudeFace(Face* i_face, float dis);

    void bevelEdge(HalfEdge* edge, float dis_ratio_inv);
private:
    void m_clearData();

};

#endif // MESH_H
