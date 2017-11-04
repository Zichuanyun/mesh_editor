#ifndef MESHCOMPONENTS_H
#define MESHCOMPONENTS_H
#include <la.h>
#include "QListWidgetItem"

class HalfEdge;
class Vertex;
class Face;

//Vertex
class Vertex : public QListWidgetItem
{
public:
    HalfEdge* halfEdge;
    int id;
    glm::vec3 pos;
    Vertex(int i_id, glm::vec3 i_pos = glm::vec3(0, 0, 0), HalfEdge* i_halfEdge = nullptr);
    static int elementCount;
    Vertex(glm::vec3 i_pos = glm::vec3(0, 0, 0), HalfEdge* i_halfEdge = nullptr);
    static void resetID();
};


//Face
class Face : public QListWidgetItem
{
public:
    HalfEdge* halfEdge;
    glm::vec3 color;
    int id;
    Face(int i_id, glm::vec3 i_color = glm::vec3(1, 0, 1), HalfEdge* i_halfEdge = nullptr);
    Face(glm::vec3 i_color = glm::vec3(0, 0, 0), HalfEdge* i_halfEdge = nullptr);
    static int elementCount;
    static void resetID();
};

//HalfEdge
class HalfEdge : public QListWidgetItem
{
public:
    HalfEdge* nextHalfEdge;
    HalfEdge* symHalfEdge;
    Vertex* vert;
    Face* face;
    int id;
    HalfEdge(int i_id, Vertex* i_vert = nullptr, Face* i_face = nullptr, HalfEdge* i_nextHalfEdge = nullptr, HalfEdge* symHalfEdge = nullptr);
    HalfEdge(Vertex* i_vert = nullptr, Face* i_face = nullptr, HalfEdge* i_nextHalfEdge = nullptr, HalfEdge* symHalfEdge = nullptr);
    static int elementCount;
    void addVertex();
    static void resetID();
};

#endif // MESHCOMPONENTS_H

