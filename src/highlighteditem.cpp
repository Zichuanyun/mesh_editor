#include "highlighteditem.h"
#include <iostream>

using namespace glm;

//state 0 for nothing, 1 point, 2 line, face;

highlightedItem::highlightedItem(GLWidget277 *context)
    : Drawable(context)
{}

highlightedItem::~highlightedItem() {

}

void highlightedItem::updateState(Vertex* i_vert) {
    m_vert = i_vert;
    state = 1;
}

void highlightedItem::updateState(HalfEdge* i_edge) {
    m_halfEdge = i_edge;
    state = 2;
}

void highlightedItem::updateState(Face* i_face) {
    m_face = i_face;
    state = 3;
}

GLenum highlightedItem::drawMode() {
    if(state == 1)
        return GL_POINTS;
    else
        return GL_LINES;
}

void highlightedItem::create()
{
    if(state == 0) {
        count = 0;
        generateIdx();
        return;
    }
    std::vector<GLuint> face_vert_idx;
    std::vector<vec4> face_vert_pos;
    std::vector<vec3> face_vert_col;

    if(state == 1)
    {
        face_vert_idx.push_back(0);
        face_vert_pos.push_back(vec4(m_vert->pos, 1));
        face_vert_col.push_back(vec3(1, 1, 1));
    }
    else if(state == 2)
    {
        face_vert_idx.push_back(0);
        face_vert_idx.push_back(1);

        face_vert_pos.push_back(vec4(m_halfEdge->symHalfEdge->vert->pos, 1));
        face_vert_pos.push_back(vec4(m_halfEdge->vert->pos, 1));

        face_vert_col.push_back(vec3(1, 0, 0));
        face_vert_col.push_back(vec3(1, 1, 0));

    }
    else // state == 3
    {
        Face* curFace = m_face;
        HalfEdge* startHalfEdge = curFace->halfEdge;
        HalfEdge* curHalfEdge = startHalfEdge;
        std::vector<vec3> this_face_vert_pos;

        do {
            this_face_vert_pos.push_back(curHalfEdge->vert->pos);
            curHalfEdge = curHalfEdge->nextHalfEdge;

        } while(curHalfEdge != startHalfEdge);

        for(int i = 0; i < this_face_vert_pos.size() - 1; i++) {
            face_vert_idx.push_back(i);
            face_vert_idx.push_back(i + 1);
        }
        face_vert_idx.push_back(this_face_vert_pos.size() - 1);
        face_vert_idx.push_back(0);

        for(int i = 0; i < this_face_vert_pos.size(); i++) {
            face_vert_pos.push_back(vec4(this_face_vert_pos.at(i), 1.));
            face_vert_col.push_back(vec3(1 - curFace->color.r,
                                         1 - curFace->color.g,
                                         1 - curFace->color.b));
        }
    }

    count = face_vert_idx.size();
    // Create a VBO on our GPU and store its handle in bufIdx
    generateIdx();
    // Tell OpenGL that we want to perform subsequent operations on the VBO referred to by bufIdx
    // and that it will be treated as an element array buffer (since it will contain triangle indices)
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    // Pass the data stored in cyl_idx into the bound buffer, reading a number of bytes equal to
    // SPH_IDX_COUNT multiplied by the size of a GLuint. This data is sent to the GPU to be read by shader programs.
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_vert_idx.size() * sizeof(GLuint), face_vert_idx.data(), GL_STATIC_DRAW);

    // The next few sets of function calls are basically the same as above, except bufPos and bufNor are
    // array buffers rather than element array buffers, as they store vertex attributes like position.
    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, face_vert_pos.size() * sizeof(glm::vec4), face_vert_pos.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, face_vert_col.size() * sizeof(glm::vec3), face_vert_col.data(), GL_STATIC_DRAW);
}

void highlightedItem::setNull(){
    state = 0;
}
