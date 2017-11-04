#include "objloader.h"
#include <QFileDialog>
#include <QFile>
#include <iostream>
#include "la.h"
#include <fstream>
#include <sstream>
#include <map>
#include "meshcomponents.h"

using namespace glm;

OBJLoader::OBJLoader()
{

}

void OBJLoader::loadOBJ()
{

}

void OBJLoader::loadOBJ(std::vector<Vertex*>& i_verts, std::vector<Face*>& i_faces, std::vector<HalfEdge*>& i_halfedges)
{
    QString Q_filename = QFileDialog::getOpenFileName(Q_NULLPTR, QString("Select obj file"), QString("../assignment_package/obj_files"), QString("ALL file ();;OBJ (*.obj);;Text files (*.txt)"));
    if(Q_filename == nullptr) {
        std::cout << "No file opened." << std::endl;
        return;
    }
    std::string filename = Q_filename.toStdString();
    std::ifstream filestream(filename.c_str());

    std::vector<std::vector<int>> faces;

    int maxchars = 8192; //it is said (by Adam :)) to be enough size
    std::vector<char> buf(maxchars);

    while(filestream.peek() != -1) {
        filestream.getline(&buf[0], maxchars);
        std::string linebuf(&buf[0]);

        if(linebuf.size() > 0) {
            if(linebuf[linebuf.size() - 1] == '/n')
                linebuf.erase(linebuf.size() - 1);
        }

        if(linebuf.size() > 0) {
            if(linebuf[linebuf.size() - 1] == '/r')
                linebuf.erase(linebuf.size() - 1);
        }

        if(linebuf.size() == 0)
            continue;

        //skip the comment
        if(linebuf[0] == '#')
            continue;

        if(linebuf[0] == 'v'  && linebuf[1] == ' ') {

            std::istringstream stringstream(linebuf);
            char tc;
            stringstream >>tc;

            float x, y, z;
            stringstream >> x;
            stringstream >> y;
            stringstream >> z;
            i_verts.push_back(new Vertex(vec3(x, y, z)));
        }

//#define NOPE
#ifdef NOPE
        for(int i = 0; i < v_pos.size(); i++) {
            std::cout << v_pos[i].x << " " << v_pos[i].y << " " << v_pos[i].z << std::endl;
        }
#endif

        if(linebuf[0] == 'f'  && linebuf[1] == ' ') {
            std::istringstream stringstream(linebuf);
            std::vector<int> thisFaceIdx;
            std::string thisGroup;

            stringstream.get();

            while(stringstream >> thisGroup) {
                //the second variable stands for length not index;
                int idx = std::stoi(thisGroup.substr(0, thisGroup.find("/")));
                //IMPORTANT: remember that obj file's index starts from 1
                //so - 1
                thisFaceIdx.push_back(idx - 1);
            }
            faces.push_back(thisFaceIdx);
        }
    }

    //#define NOPE
    #ifdef NOPE
            for(int i = 0; i < faces.size(); i++) {
                for(int j = 0; j < faces[i].size(); j++) {
                    std::cout << faces[i][j] << " ";
                }
                std::cout << std::endl;
            }
    #endif  
    std::map<std::vector<int>, HalfEdge*> he_map;
    for(std::vector<int> face_idxes: faces) {
        //create face
        Face* face = new Face(vec3(((float) rand() / (RAND_MAX)), 1 - ((float) rand() / (RAND_MAX)), ((float) rand() / (RAND_MAX))));
        i_faces.push_back(face);
        std::vector<HalfEdge*> new_edges;
        for(int i = 0; i < face_idxes.size(); i++) {
            int end_idx = face_idxes[i];
            int start_idx;
            if(i == 0)
                start_idx = face_idxes[face_idxes.size() - 1];
            else
                start_idx = face_idxes[i - 1];
            HalfEdge* edge = new HalfEdge(i_verts.at(end_idx));
            i_verts.at(end_idx)->halfEdge = edge;
            new_edges.push_back(edge);

            std::vector<int> key_vector;
            key_vector.push_back(start_idx);
            key_vector.push_back(end_idx);
            he_map[key_vector] = edge;

            //reverse order to find sym edge
            key_vector.clear();
            key_vector.push_back(end_idx);
            key_vector.push_back(start_idx);

            //find sym
            if(he_map[key_vector] != 0) {
                HalfEdge* sym_edge = he_map[key_vector];
                sym_edge->symHalfEdge = edge;
                edge->symHalfEdge = sym_edge;
            }
        }

        for(int i = 0; i < new_edges.size(); i++) {
            HalfEdge* edge = new_edges.at(i);
            i_halfedges.push_back(edge);
            if(i == new_edges.size() - 1) {
                edge->nextHalfEdge = new_edges.at(0);
            } else {
                edge->nextHalfEdge = new_edges.at(i + 1);
            }
            edge->face = face;
        }
        face->halfEdge = new_edges.at(0);
    }
    //#define NOPE
#ifdef NOPE
    for(int i = 0; i < i_halfedges.size(); i++) {
        HalfEdge* edge = i_halfedges.at(i);
        if(edge->symHalfEdge == nullptr)
            std::cout << "sym null" << std::endl;
        if(edge->nextHalfEdge == nullptr)
            std::cout << "next null" << std::endl;
        if(edge->face == nullptr)
            std::cout << "face null" << std::endl;
        if(edge->vert == nullptr)
            std::cout << "vert null" << std::endl;
    }
#endif
}

