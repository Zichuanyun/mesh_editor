#ifndef HIGHLIGHTEDITEM_H
#define HIGHLIGHTEDITEM_H
#include "drawable.h"
#include "meshcomponents.h"

class highlightedItem : public Drawable
{
public:
    highlightedItem(GLWidget277 *context);
    void create();
    ~highlightedItem();
    virtual GLenum drawMode() override;
    void updateState(Vertex*);
    void updateState(Face*);
    void updateState(HalfEdge*);
    void setNull();
private:
    int state = 0; //0 for nothing, 1 point, 2 line, face;
    Vertex* m_vert;
    Face* m_face;
    HalfEdge* m_halfEdge;
};

#endif // HIGHLIGHTEDITEM_H
