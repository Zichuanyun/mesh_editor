#include "meshcomponents.h"

//Vertex
int Vertex::elementCount = 0;

void Vertex::resetID()
{
    Vertex::elementCount = 0;
}

Vertex::Vertex(int i_id, glm::vec3 i_pos, HalfEdge* i_halfEdge):
    id(i_id),
    pos(i_pos),
    halfEdge(i_halfEdge)
{
    setText("test");
}

Vertex::Vertex(glm::vec3 i_pos, HalfEdge* i_halfEdge):
    id(elementCount),
    pos(i_pos),
    halfEdge(i_halfEdge)
{
    setText(QString::number(elementCount));
    elementCount++;
}

//Face
int Face::elementCount = 0;

void Face::resetID()
{
    Face::elementCount = 0;
}

Face::Face(glm::vec3 i_color, HalfEdge* i_halfEdge):
    color(i_color),
    id(elementCount),
    halfEdge(i_halfEdge)
{
    setText(QString::number(elementCount));
    elementCount++;
}

Face::Face(int i_id, glm::vec3 i_color, HalfEdge* i_halfEdge):
    color(i_color),
    id(i_id),
    halfEdge(i_halfEdge)
{
    setText("test");
}

//HalfEdge
int HalfEdge::elementCount = 0;

void HalfEdge::resetID()
{
    HalfEdge::elementCount = 0;
}

HalfEdge::HalfEdge(int i_id, Vertex* i_vert, Face* i_face, HalfEdge* i_nextHalfEdge, HalfEdge* i_symHalfEdge):
    id(i_id),
    vert(i_vert),
    face(i_face),
    nextHalfEdge(i_nextHalfEdge),
    symHalfEdge(i_symHalfEdge)
{
    setText("test");
}

HalfEdge::HalfEdge(Vertex* i_vert, Face* i_face, HalfEdge* i_nextHalfEdge, HalfEdge* i_symHalfEdge):
    id(elementCount),
    vert(i_vert),
    face(i_face),
    nextHalfEdge(i_nextHalfEdge),
    symHalfEdge(i_symHalfEdge)
{
    setText(QString::number(elementCount));
    elementCount++;
}

void HalfEdge::addVertex()
{

}



