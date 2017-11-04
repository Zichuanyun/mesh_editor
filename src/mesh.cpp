#include "mesh.h"
#include <iostream>


using namespace glm;

Mesh::Mesh(GLWidget277 *context)
    : Drawable(context),
      objLoader()
{
    generateCubeHalfEdgeData();
}

Mesh::~Mesh() {
    m_clearData();
}

void Mesh::m_clearData()
{
    for(int i = 0; i < m_verts.size(); i++) {
        delete m_verts.at(i);
    }
    m_verts.clear();

    for(int i = 0; i < m_faces.size(); i++) {
        delete m_faces.at(i);
    }
    m_faces.clear();

    for(int i = 0; i < m_halfedges.size(); i++) {
        delete m_halfedges.at(i);
    }
    m_halfedges.clear();
}

void Mesh::generateCubeHalfEdgeData() {
    //Eight verts
    m_verts.push_back(new Vertex(vec3(0.5, 0.5, 0.5)));
    m_verts.push_back(new Vertex(vec3(0.5, 0.5, -0.5)));
    m_verts.push_back(new Vertex(vec3(-0.5, 0.5, -0.5)));
    m_verts.push_back(new Vertex(vec3(-0.5, 0.5, 0.5)));

    m_verts.push_back(new Vertex(vec3(0.5, -0.5, 0.5)));
    m_verts.push_back(new Vertex(vec3(0.5, -0.5, -0.5)));
    m_verts.push_back(new Vertex(vec3(-0.5, -0.5, -0.5)));
    m_verts.push_back(new Vertex(vec3(-0.5, -0.5, 0.5)));

    Face* tempFace = new Face(vec3(0, 0, 1)); // front face
    m_faces.push_back(tempFace);

    m_halfedges.push_back(new HalfEdge(m_verts.at(3), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(7), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(4), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(0), tempFace));
    tempFace->halfEdge = m_halfedges.at(0);

    m_halfedges.at(0)->nextHalfEdge = m_halfedges.at(1);
    m_halfedges.at(1)->nextHalfEdge = m_halfedges.at(2);
    m_halfedges.at(2)->nextHalfEdge = m_halfedges.at(3);
    m_halfedges.at(3)->nextHalfEdge = m_halfedges.at(0);

    tempFace = new Face(vec3(0, 1, 0)); // top face
    m_faces.push_back(tempFace);

    m_halfedges.push_back(new HalfEdge(m_verts.at(0), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(1), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(2), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(3), tempFace));
    tempFace->halfEdge = m_halfedges.at(4);

    m_halfedges.at(4)->nextHalfEdge = m_halfedges.at(5);
    m_halfedges.at(5)->nextHalfEdge = m_halfedges.at(6);
    m_halfedges.at(6)->nextHalfEdge = m_halfedges.at(7);
    m_halfedges.at(7)->nextHalfEdge = m_halfedges.at(4);

    tempFace = new Face(vec3(1, 0.0, 0.0)); // right face
    m_faces.push_back(tempFace);

    m_halfedges.push_back(new HalfEdge(m_verts.at(5), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(1), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(0), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(4), tempFace));
    tempFace->halfEdge = m_halfedges.at(8);

    m_halfedges.at(8)->nextHalfEdge = m_halfedges.at(9);
    m_halfedges.at(9)->nextHalfEdge = m_halfedges.at(10);
    m_halfedges.at(10)->nextHalfEdge = m_halfedges.at(11);
    m_halfedges.at(11)->nextHalfEdge = m_halfedges.at(8);

    tempFace = new Face(vec3(0.0, 1, 1)); // left face
    m_faces.push_back(tempFace);

    m_halfedges.push_back(new HalfEdge(m_verts.at(7), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(3), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(2), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(6), tempFace));
    tempFace->halfEdge = m_halfedges.at(12);

    m_halfedges.at(12)->nextHalfEdge = m_halfedges.at(13);
    m_halfedges.at(13)->nextHalfEdge = m_halfedges.at(14);
    m_halfedges.at(14)->nextHalfEdge = m_halfedges.at(15);
    m_halfedges.at(15)->nextHalfEdge = m_halfedges.at(12);

    tempFace = new Face(vec3(1, 1, 0)); // back face
    m_faces.push_back(tempFace);

    m_halfedges.push_back(new HalfEdge(m_verts.at(6), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(2), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(1), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(5), tempFace));
    tempFace->halfEdge = m_halfedges.at(16);

    m_halfedges.at(16)->nextHalfEdge = m_halfedges.at(17);
    m_halfedges.at(17)->nextHalfEdge = m_halfedges.at(18);
    m_halfedges.at(18)->nextHalfEdge = m_halfedges.at(19);
    m_halfedges.at(19)->nextHalfEdge = m_halfedges.at(16);

    tempFace = new Face(vec3(1, 0, 1)); // bottom face
    m_faces.push_back(tempFace);

    m_halfedges.push_back(new HalfEdge(m_verts.at(7), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(6), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(5), tempFace));
    m_halfedges.push_back(new HalfEdge(m_verts.at(4), tempFace));
    tempFace->halfEdge = m_halfedges.at(20);

    m_halfedges.at(20)->nextHalfEdge = m_halfedges.at(21);
    m_halfedges.at(21)->nextHalfEdge = m_halfedges.at(22);
    m_halfedges.at(22)->nextHalfEdge = m_halfedges.at(23);
    m_halfedges.at(23)->nextHalfEdge = m_halfedges.at(20);

    //Set up sym half edge
    //Face 0
    m_halfedges.at(0)->symHalfEdge = m_halfedges.at(4);
    m_halfedges.at(1)->symHalfEdge = m_halfedges.at(13);
    m_halfedges.at(2)->symHalfEdge = m_halfedges.at(20);
    m_halfedges.at(3)->symHalfEdge = m_halfedges.at(11);

    //Face 1
    m_halfedges.at(4)->symHalfEdge = m_halfedges.at(0);
    m_halfedges.at(5)->symHalfEdge = m_halfedges.at(10);
    m_halfedges.at(6)->symHalfEdge = m_halfedges.at(18);
    m_halfedges.at(7)->symHalfEdge = m_halfedges.at(14);

    //Face 2
    m_halfedges.at(8)->symHalfEdge = m_halfedges.at(23);
    m_halfedges.at(9)->symHalfEdge = m_halfedges.at(19);
    m_halfedges.at(10)->symHalfEdge = m_halfedges.at(5);
    m_halfedges.at(11)->symHalfEdge = m_halfedges.at(3);

    //Face 3
    m_halfedges.at(12)->symHalfEdge = m_halfedges.at(21);
    m_halfedges.at(13)->symHalfEdge = m_halfedges.at(1);
    m_halfedges.at(14)->symHalfEdge = m_halfedges.at(7);
    m_halfedges.at(15)->symHalfEdge = m_halfedges.at(17);

    //Face 4
    m_halfedges.at(16)->symHalfEdge = m_halfedges.at(22);
    m_halfedges.at(17)->symHalfEdge = m_halfedges.at(15);
    m_halfedges.at(18)->symHalfEdge = m_halfedges.at(6);
    m_halfedges.at(19)->symHalfEdge = m_halfedges.at(9);

    //Face 5
    m_halfedges.at(20)->symHalfEdge = m_halfedges.at(2);
    m_halfedges.at(21)->symHalfEdge = m_halfedges.at(12);
    m_halfedges.at(22)->symHalfEdge = m_halfedges.at(16);
    m_halfedges.at(23)->symHalfEdge = m_halfedges.at(8);

    //Set up vert->halfedge, always points to the smallest one
    m_verts.at(0)->halfEdge = m_halfedges.at(3);
    m_verts.at(1)->halfEdge = m_halfedges.at(5);
    m_verts.at(2)->halfEdge = m_halfedges.at(6);
    m_verts.at(3)->halfEdge = m_halfedges.at(0);

    m_verts.at(4)->halfEdge = m_halfedges.at(2);
    m_verts.at(5)->halfEdge = m_halfedges.at(8);
    m_verts.at(6)->halfEdge = m_halfedges.at(16);
    m_verts.at(7)->halfEdge = m_halfedges.at(1);
}

void Mesh::create()
{
    std::vector<GLuint> face_vert_idx;
    std::vector<vec4> face_vert_pos;
    std::vector<vec4> face_vert_nor;
    std::vector<vec3> face_vert_col;

    for(int i = 0; i < m_faces.size(); i++) {
        Face* curFace = m_faces.at(i);
        HalfEdge* startHalfEdge = curFace->halfEdge;
        HalfEdge* curHalfEdge = startHalfEdge;
        std::vector<vec3> this_face_vert_pos;

        do {
            this_face_vert_pos.push_back(curHalfEdge->vert->pos);
            curHalfEdge = curHalfEdge->nextHalfEdge;

        } while(curHalfEdge != startHalfEdge);

        vec4 curNomal;
        {
            vec3 v0 = this_face_vert_pos.at(2) - this_face_vert_pos.at(1);
            vec3 v1 = this_face_vert_pos.at(0) - this_face_vert_pos.at(1);
            vec3 normal = cross(v0, v1);
            curNomal = vec4(normalize(normal), 1.);
        }

        for(int i = 1, start = face_vert_pos.size(); i < this_face_vert_pos.size() - 1; i++) {
            face_vert_idx.push_back(start);
            face_vert_idx.push_back(start + i);
            face_vert_idx.push_back(start + i + 1);
        }

        for(int i = 0; i < this_face_vert_pos.size(); i++) {
            face_vert_pos.push_back(vec4(this_face_vert_pos.at(i), 1.));
            face_vert_col.push_back(curFace->color);
            face_vert_nor.push_back(curNomal);
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

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, face_vert_nor.size() * sizeof(glm::vec4), face_vert_nor.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, face_vert_col.size() * sizeof(glm::vec3), face_vert_col.data(), GL_STATIC_DRAW);
}

//no need to retur, just add all the elements again in main window
void Mesh::addVert(HalfEdge* i_halfEdge) {
    HalfEdge *e1a, *e1b, *e1n;
    HalfEdge *e2a, *e2b, *e2n;

    Vertex *v1, *v2, *vm;

    //e1a, e1b, v1, e2a, e2b, v2
    e1a = i_halfEdge;
    e1b = e1a;
    do {
        e1b = e1b->nextHalfEdge;
    } while(e1b->nextHalfEdge != e1a);
    v1 = e1a->vert;

    e2a = e1a->symHalfEdge;
    e2b = e2a;
    do {
        e2b = e2b->nextHalfEdge;
    } while(e2b->nextHalfEdge != e2a);
    v2 = e2a->vert;

//#define NOPE
#ifdef NOPE
    //the following is to check whether I get all elements right
    std::cout << "e1a: " << e1a->id << std::endl;
    std::cout << "e1b: " << e1b->id << std::endl;
    std::cout << "v1: " << v1->id << std::endl;
    std::cout << "e2a: " << e2a->id << std::endl;
    std::cout << "e2b: " << e2b->id << std::endl;
    std::cout << "v2: " << v2->id << std::endl;
#endif

    vm = new Vertex(vec3(v1->pos + v2->pos) * 0.5f);
    m_verts.push_back(vm);

    //1 set new edge's vertex
    e1n = new HalfEdge(vm);
    e2n = new HalfEdge(vm);
    m_halfedges.push_back(e1n);
    m_halfedges.push_back(e2n);

    //2
    e1n->nextHalfEdge = e1a;
    e2n->nextHalfEdge = e2a;

    //3
    e1n->symHalfEdge = e2a;
    e2a->symHalfEdge = e1n;
    e2n->symHalfEdge = e1a;
    e1a->symHalfEdge = e2n;

    //4 set next halfedge of previous edge
    e1b->nextHalfEdge = e1n;
    e2b->nextHalfEdge = e2n;

    //5
    e1n->face = e1a->face;
    e2n->face = e2a->face;

    //6 set new vert' halfedge
    //e1n is created first, so is smaller
    vm->halfEdge = e1n;
}

void Mesh::triangulateFace(Face* i_face)
{
    std::vector<Vertex*> verts;
    std::vector<HalfEdge*> edges;
    std::vector<Face*> faces;

    int e_count, v_count, f_count;

    HalfEdge* startEdge = i_face->halfEdge;
    HalfEdge* curEdge = startEdge;

    do{
        verts.push_back(curEdge->vert);
        edges.push_back(curEdge);
        curEdge = curEdge->nextHalfEdge;
    } while(curEdge->nextHalfEdge != startEdge);

    verts.push_back(curEdge->vert);
    edges.push_back(curEdge);
    verts.insert(verts.begin(), curEdge->vert);
    verts.erase(verts.end() - 1);

    v_count = edges.size();
    e_count = edges.size();
    f_count = e_count - 2;

    if(v_count == 3)
        return;

    faces.push_back(i_face);
    for(int i = 1; i < f_count; i++) {
        faces.push_back(new Face(i_face->color));
    }

    HalfEdge *e1, *e2, *e3, *esym;
    e1 = edges.at(0);
    e2 = edges.at(1);
    edges.push_back(new HalfEdge(verts.at(0)));
    e3 = edges.at(e_count);

    e3->nextHalfEdge = e1;
    e3->face = faces.at(0);
    faces.at(0)->halfEdge = e3;
    e2->nextHalfEdge = e3;

    for(int i = 1; i < f_count - 1; i++) {
        e1 = new HalfEdge(verts.at(i + 1));
        e2 = edges.at(i + 1);
        e3 = new HalfEdge(verts.at(0));

        edges.push_back(e1);
        edges.push_back(e3);

        //2 & 5
        e1->nextHalfEdge = e2;
        e2->nextHalfEdge = e3;
        e3->nextHalfEdge = e1;

        //3
        e1->face = faces.at(i);
        e2->face = faces.at(i);
        e3->face = faces.at(i);

        //4
        faces.at(i)->halfEdge = e1;

        //6
        esym = edges.at(edges.size() - 3);
        e1->symHalfEdge = esym;
        esym->symHalfEdge = e1;
    }

    edges.push_back(new HalfEdge(verts.at(v_count - 2)));
    e1 = edges.at(e_count - 1 + (f_count - 2) * 2 + 2);

    e2 = edges.at(e_count - 2);
    e3 = edges.at(e_count - 1);

    //2
    e1->nextHalfEdge = e2;
    //3
    e1->face = faces.at(f_count - 1);
    e2->face = faces.at(f_count - 1);
    e3->face = faces.at(f_count - 1);
    //4
    faces.at(f_count - 1)->halfEdge = e1;
    //5
    e3->nextHalfEdge = e1;
    //6 set sym
    esym = edges.at(e_count - 1 + (f_count - 2) * 2 + 1);
    e1->symHalfEdge = esym;
    esym->symHalfEdge = e1;

    for(int i = e_count; i < edges.size(); i++) {
        m_halfedges.push_back(edges.at(i));
    }

    for(int i = 1; i < faces.size(); i++) {
        m_faces.push_back(faces.at(i));
    }
}

void Mesh::subdivision()
{
    int e_count = m_halfedges.size();
    int v_count = m_verts.size();
    int f_count = m_faces.size();

    //find centroids
    //this index is the same as face index
    //so we can directly find a face's centroid
    std::vector<Vertex*> face_centroids;
    for(int i = 0; i < f_count; i++) {
        Face* face = m_faces.at(i);
        Vertex* vert = new Vertex();
        vec3 pos = vec3(0);

        HalfEdge* startEdge = face->halfEdge;
        HalfEdge* curEdge = startEdge;
        int edge_count = 0;
        do{
            edge_count += 1;
            pos += curEdge->vert->pos;
            curEdge = curEdge->nextHalfEdge;
        } while(curEdge != startEdge);

        pos = pos / (float)edge_count;
        vert->pos = pos;
        face_centroids.push_back(vert);

        //add into the total verts
        //for visual debugging
        m_verts.push_back(vert);
    }

    //find mid points
    //The following line will be complained by clang but not by MingGW
    //int he_mid_set[e_count] = {0};
    std::vector<int> he_mid_set(e_count);

    for(int i = 0; i < e_count; i++) {
        HalfEdge *e1a, *e1b, *e1n;
        HalfEdge *e2a, *e2b, *e2n;
        Vertex *v1, *v2, *vm, *vf1, *vf2;

        //e1a, e1b, v1, e2a, e2b, v2
        e1a = m_halfedges[i];
        e2a = e1a->symHalfEdge;
        if(he_mid_set[e1a->id] == 1 || e2a->id > e_count ||he_mid_set[e2a->id] == 1) continue;

        he_mid_set[e1a->id] = 1;
        he_mid_set[e2a->id] = 1;

        e1b = e1a;
        do {
            e1b = e1b->nextHalfEdge;
        } while(e1b->nextHalfEdge != e1a);
        v1 = e1a->vert;
        e2b = e2a;
        do {
            e2b = e2b->nextHalfEdge;
        } while(e2b->nextHalfEdge != e2a);
        v2 = e2a->vert;

        vf1 = face_centroids.at(e1a->face->id);
        vf2 = face_centroids.at(e2a->face->id);

        vm = new Vertex(vec3(v1->pos + v2->pos + vf1->pos + vf2->pos) * 0.25f);
        m_verts.push_back(vm);

        //1 set new edge's vertex
        e1n = new HalfEdge(vm);
        e2n = new HalfEdge(vm);
        m_halfedges.push_back(e1n);
        m_halfedges.push_back(e2n);

        //2
        e1n->nextHalfEdge = e1a;
        e2n->nextHalfEdge = e2a;

        //3
        e1n->symHalfEdge = e2a;
        e2a->symHalfEdge = e1n;
        e2n->symHalfEdge = e1a;
        e1a->symHalfEdge = e2n;

        //4 set next halfedge of previous edge
        e1b->nextHalfEdge = e1n;
        e2b->nextHalfEdge = e2n;

        //5
        e1n->face = e1a->face;
        e2n->face = e2a->face;

        //6 set new vert' halfedge
        //e1n is created first, so is smaller
        vm->halfEdge = e1n;
    }

    //change the original vertex
    for(int i = 0; i < v_count; i++) {
        Vertex* vert = m_verts.at(i);
        //the one pointing to a mid point
        HalfEdge* startEdge = vert->halfEdge->nextHalfEdge;
        HalfEdge* curEdge = startEdge;
        float n = 0.0;
        vec3 midPointPos = vec3(0);
        vec3 faceCentroidsPos = vec3(0);

        do {
            midPointPos += curEdge->vert->pos;
            faceCentroidsPos += face_centroids.at(curEdge->face->id)->pos;
            n += 1;
            curEdge = curEdge->symHalfEdge->nextHalfEdge;
        }while(curEdge != startEdge);

        vert->pos = (n - 2) * vert->pos / n + (midPointPos + faceCentroidsPos) / (n*n);
    }

    //connect the face
    for(int i = 0; i < f_count; i++) {
        Face* face = m_faces.at(i);
        Vertex* centroid = face_centroids.at(i);

        std::vector<HalfEdge*> oldEdges;
        std::vector<HalfEdge*> newEdges;
        std::vector<Vertex*> verts;
        std::vector<Face*> newFaces;
        int n = 0;

        HalfEdge* startEdge = face->halfEdge;
        //make sure the start edge is pointing to the original verts
        if(startEdge->vert->id >= v_count)
            startEdge = startEdge->nextHalfEdge;

        oldEdges.push_back(startEdge);
        verts.push_back(startEdge->vert);

        for(HalfEdge* curEdge = startEdge->nextHalfEdge; curEdge != startEdge; curEdge = curEdge->nextHalfEdge) {
            oldEdges.push_back(curEdge);
            verts.push_back(curEdge->vert);
        }
        n = verts.size();

        newEdges.push_back(new HalfEdge(verts.at(n - 1)));
        newEdges.push_back(new HalfEdge(centroid));
        //syms are not set for now

        for(int j = 1; j < n / 2; j++) {
            vec3 col = face->color;
            col = col * ((float)j * 2 / (float)n);
            Face* thisFace = new Face(col);
            newFaces.push_back(thisFace);
            m_faces.push_back(thisFace);
        }

        {
            HalfEdge* tempEdge0 = newEdges.at(0);
            HalfEdge* tempEdge1 = newEdges.at(1);

            //set 0
            //2
            tempEdge1->nextHalfEdge = tempEdge0;
            oldEdges.at(1)->nextHalfEdge = tempEdge1;
            //3 no sym for now
            //4
            tempEdge0->nextHalfEdge = oldEdges.at(0);
            tempEdge1->nextHalfEdge = tempEdge0;
            //5
            tempEdge0->face = newFaces.at(0);
            tempEdge1->face = newFaces.at(0);
            oldEdges.at(0)->face = newFaces.at(0);
            oldEdges.at(1)->face = newFaces.at(0);
            newFaces.at(0)->halfEdge = tempEdge1;
            centroid->halfEdge = tempEdge1;
        }

        for(int j = 1; j < n / 2; j++) {
            HalfEdge *new_e0, *new_e1, *old_e0, *old_e1;
            new_e0 = new HalfEdge(verts.at(j * 2 - 1));
            new_e1 = new HalfEdge(centroid);
            newEdges.push_back(new_e0);
            newEdges.push_back(new_e1);
            old_e0 = oldEdges.at(j * 2);
            old_e1 = oldEdges.at(j * 2 + 1);

            //set 0
            //2
            new_e1->nextHalfEdge = new_e0;
            old_e1->nextHalfEdge = new_e1;
            //3
            new_e0->symHalfEdge = newEdges.at(j * 2 - 1);
            newEdges.at(j * 2 - 1)->symHalfEdge = new_e0;

            if(j == n / 2 - 1) {
                new_e1->symHalfEdge = newEdges.at(0);
                newEdges.at(0)->symHalfEdge = new_e1;
            }
            //4
            new_e0->nextHalfEdge = old_e0;
            new_e1->nextHalfEdge = new_e0;
            //5
            if(j == n / 2 - 1) {
                new_e0->face = face;
                new_e1->face = face;
                old_e0->face = face;
                old_e1->face = face;
                face->halfEdge = new_e1;
            } else {
                new_e0->face = newFaces.at(j);
                new_e1->face = newFaces.at(j);
                old_e0->face = newFaces.at(j);
                old_e1->face = newFaces.at(j);
                newFaces.at(j)->halfEdge = new_e1;
            }
        }

        //push_back to member variable together at here
        for(int j = 0; j < newEdges.size(); j++) {
            m_halfedges.push_back(newEdges.at(j));
        }
    }
}

void Mesh::loadFromFile()
{
    m_clearData();
    Vertex::resetID();
    Face::resetID();
    HalfEdge::resetID();
    std::vector<Vertex*>& r_verts = m_verts;
    std::vector<Face*>& r_faces = m_faces;
    std::vector<HalfEdge*>& r_halfedges = m_halfedges;
    objLoader.loadOBJ(r_verts, r_faces, r_halfedges);
    std::cout << "vert number: " << m_verts.size() << std::endl;
    std::cout << "face number: " << m_faces.size() << std::endl;
    std::cout << "halfedge number: " << m_halfedges.size() << std::endl;
}

void Mesh::extrudeFace(Face* i_face, float dis)
{
    std::vector<HalfEdge*> old_edges;
    std::vector<HalfEdge*> old_sym_edges;
    std::vector<HalfEdge*> new_edges_0; //old's sym
    std::vector<HalfEdge*> new_edges_1; //to old sym
    std::vector<HalfEdge*> new_edges_2; //old sym's sym
    std::vector<HalfEdge*> new_edges_3; //to old
    std::vector<Vertex*> old_verts;
    std::vector<Vertex*> new_verts; //extrude this
    std::vector<Face*> new_faces;
    vec3 extrudeVec;
    vec3 col = i_face->color;

    {
        HalfEdge* startEdge = i_face->halfEdge;
        HalfEdge* curEdge = startEdge->nextHalfEdge;

        old_edges.push_back(startEdge);
        old_sym_edges.push_back(startEdge->symHalfEdge);

        old_verts.push_back(startEdge->vert);

        while(curEdge != startEdge) {
            old_edges.push_back(curEdge);
            old_sym_edges.push_back(curEdge->symHalfEdge);
            old_verts.push_back(curEdge->vert);
            curEdge = curEdge->nextHalfEdge;
        }

        vec3 v1 = old_verts.at(1)->pos - old_verts.at(0)->pos;
        vec3 v2 = old_verts.at(old_verts.size() - 1)->pos - old_verts.at(0)->pos;
        extrudeVec = cross(v1, v2);
        extrudeVec = normalize(extrudeVec) * dis;
    }

    for(int i = 0; i < old_edges.size(); i++) {
        Vertex* old_vert = old_verts.at(i);
        Vertex* vert = new Vertex(old_vert->pos + extrudeVec);
        new_verts.push_back(vert);
        old_edges.at(i)->vert = vert;
        vert->halfEdge = old_edges.at(i);
    }

    //set 0-3 sym, new face this run
    for(int i = 0; i < old_edges.size(); i++) {
        Face* face = new Face(col * 0.6f);
        new_faces.push_back(face);

        Vertex *v0, *v1, *v2, *v3;

        v2 = old_verts.at(i);
        v3 = new_verts.at(i);

        if(i == 0) {
            v0 = new_verts.at(new_verts.size() - 1);
            v1 = old_verts.at(old_verts.size() - 1);
        } else {
            v0 = new_verts.at(i - 1);
            v1 = old_verts.at(i - 1);
        }

        HalfEdge *e0, *e1, *e2, *e3;

        e0 = new HalfEdge(v0);
        e1 = new HalfEdge(v1);
        e2 = new HalfEdge(v2);
        e3 = new HalfEdge(v3);

        new_edges_0.push_back((e0));
        new_edges_1.push_back((e1));
        new_edges_2.push_back((e2));
        new_edges_3.push_back((e3));

        e0->nextHalfEdge = e1;
        e1->nextHalfEdge = e2;
        e2->nextHalfEdge = e3;
        e3->nextHalfEdge = e0;

        e0->face = face;
        e1->face = face;
        e2->face = face;
        e3->face = face;
        face->halfEdge = e0;

        e0->symHalfEdge = old_edges.at(i);
        old_edges.at(i)->symHalfEdge = e0;

        e2->symHalfEdge = old_sym_edges.at(i);
        old_sym_edges.at(i)->symHalfEdge = e2;
    }

    //set 1-3 sym the next run
    for(int i = 0; i < old_edges.size(); i++) {
        HalfEdge *e1, *e3;

        e3 = new_edges_3.at(i);
        if(i == old_edges.size() - 1) {
            e1 = new_edges_1.at(0);
        } else {
            e1 = new_edges_1.at(i + 1);
        }
        e1->symHalfEdge = e3;
        e3->symHalfEdge = e1;

        m_verts.push_back(new_verts.at(i));
        m_halfedges.push_back(new_edges_0.at(i));
        m_halfedges.push_back(new_edges_1.at(i));
        m_halfedges.push_back(new_edges_2.at(i));
        m_halfedges.push_back(new_edges_3.at(i));
        m_faces.push_back(new_faces.at(i));
    }
}

void Mesh::bevelEdge(HalfEdge* edge, float dis_ratio_inv) {
    float dis_ratio = 1 - dis_ratio_inv;

    HalfEdge *e1, *e2, *e11, *e12, *e21, *e22, *e12y, *e22y;
    HalfEdge *e1n, *e2n, *e1y, *e2y, *e1ny, *e2ny;

    Vertex *v1, *v2, *v11, *v12, *v21, *v22;
    Vertex *v1n, *v2n;

    Face *f1, *f2, *fn;

    HalfEdge* e_temp;

    e1 = edge;
    e2 = e1->symHalfEdge;

    v1 = e1->vert;
    v2 = e2->vert;

    e_temp = e1;
    while(e_temp->nextHalfEdge != e2) {
        e_temp = e_temp->nextHalfEdge->symHalfEdge;
    }

    e12 = e_temp->symHalfEdge;
    e12y = e12->symHalfEdge;


    v12 = e12->vert;

    e11 = e12->nextHalfEdge;
    while(e11->nextHalfEdge != e12) {
        v11 = e11->vert;
        e11 = e11->nextHalfEdge;
    }

    f1 = e11->face;

    //test out put
    printf("e12: %d\n", e12->id);   //18
    printf("v12: %d\n", v12->id);   //1
    printf("e11: %d\n", e11->id);   //17
    printf("v11: %d\n", v11->id);   //6

    e21 = e2->nextHalfEdge->symHalfEdge;

    e22 = e21->nextHalfEdge;
    e22y = e22->symHalfEdge;


    v22 = e22->vert;

    e_temp = e21;
    while(e_temp->nextHalfEdge != e21) {
        e_temp = e_temp->nextHalfEdge;
        v21 = e_temp->vert;
    }

    f2 = e21->face;

    //test out put
    printf("e21: %d\n", e21->id);   //0
    printf("v21: %d\n", v21->id);   //0
    printf("e22: %d\n", e22->id);   //1
    printf("v22: %d\n", v22->id);   //7


    vec3 v1n_pos = v1->pos * dis_ratio_inv + v12->pos * dis_ratio;
    vec3 v2n_pos = v2->pos * dis_ratio_inv + v22->pos * dis_ratio;
    v1->pos = v11->pos * dis_ratio + v1->pos * dis_ratio_inv;
    v2->pos = v21->pos * dis_ratio + v2->pos * dis_ratio_inv;

    v1n = new Vertex(v1n_pos);
    v2n = new Vertex(v2n_pos);
    v1n->halfEdge = e1n;
    v2n->halfEdge = e2n;

    e1n = new HalfEdge(v1n);
    e2n = new HalfEdge(v2n);

    e1n->nextHalfEdge = e12;
    e2n->nextHalfEdge = e22;
    e11->nextHalfEdge = e1n;
    e21->nextHalfEdge = e2n;

    //following two part consist the loop
    e1y = new HalfEdge(v2n);
    e2y = new HalfEdge(v1n);

    e1ny = new HalfEdge(v1);
    e2ny = new HalfEdge(v2);

    e1y->symHalfEdge = e1;
    e2y->symHalfEdge = e2;
    e1->symHalfEdge = e1y;
    e2->symHalfEdge = e2y;

    e1ny->symHalfEdge = e1n;
    e1n->symHalfEdge = e1ny;
    e2ny->symHalfEdge = e2n;
    e2n->symHalfEdge = e2ny;

    e1y->nextHalfEdge = e2ny;
    e2ny->nextHalfEdge = e2y;
    e2y->nextHalfEdge = e1ny;
    e1ny->nextHalfEdge = e1y;

    fn = new Face(vec3(((float) rand() / (RAND_MAX)), 1 - ((float) rand() / (RAND_MAX)), ((float) rand() / (RAND_MAX))));
    fn->halfEdge = e1y;

    e12y->vert = v1n;
    e22y->vert = v2n;


    e1n->face = f1;
    e2n->face = f2;

    e1y->face = fn;
    e2y->face = fn;
    e1ny->face = fn;
    e2ny->face = fn;

    m_verts.push_back(v1n);
    m_verts.push_back(v2n);

    m_halfedges.push_back(e1n);
    m_halfedges.push_back(e2n);
    m_halfedges.push_back(e1y);
    m_halfedges.push_back(e2y);
    m_halfedges.push_back(e1ny);
    m_halfedges.push_back(e2ny);

    m_faces.push_back(fn);
}

