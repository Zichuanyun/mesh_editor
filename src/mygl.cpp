#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>

MyGL::MyGL(QWidget *parent)
    : GLWidget277(parent),
      m_geomCylinder(this), m_geomSphere(this),
      m_progLambert(this), m_progFlat(this),
      m_glCamera(), m_mesh(this), m_highlight(this),
      m_curFace(nullptr), m_curHalfEdge(nullptr),
      m_curItem(nullptr), m_curVert(nullptr)
{
    m_meshPointer = &m_mesh;
    setFocusPolicy(Qt::StrongFocus);
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    m_geomCylinder.destroy();
    m_geomSphere.destroy();
    m_mesh.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the instances of Cylinder and Sphere.
    m_geomCylinder.create();

    m_geomSphere.create();

    m_mesh.create();

    m_highlight.create();

    // Create and set up the diffuse shader
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    m_progFlat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    // Set a color with which to draw geometry since you won't have one
    // defined until you implement the Node classes.
    // This makes your geometry render green.
    m_progLambert.setGeometryColor(glm::vec4(0,1,0,1));

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
//    vao.bind();
    glBindVertexArray(vao);
}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    m_glCamera = Camera(w, h);
    glm::mat4 viewproj = m_glCamera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    m_progLambert.setViewProjMatrix(viewproj);
    m_progFlat.setViewProjMatrix(viewproj);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
//DO NOT CONSTRUCT YOUR SCENE GRAPH IN THIS FUNCTION!
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_progFlat.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setViewProjMatrix(m_glCamera.getViewProj());

    glm::mat4 model;

    model = glm::translate(glm::mat4(1.0f), glm::vec3(-2,0,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(3,3,3));
    //Send the geometry's transformation matrix to the shader
    m_progFlat.setModelMatrix(model);

    //Draw the example sphere using our lambert shader
    m_progFlat.draw(m_mesh);

    if(m_curItem != nullptr) {
        glDisable(GL_DEPTH_TEST);
        m_progFlat.setModelMatrix(model);
        m_progFlat.draw(m_highlight);
        glEnable(GL_DEPTH_TEST);
    }

#define NOPE
#ifndef NOPE
    //Create a model matrix. This one scales the sphere uniformly by 3, then translates it by <-2,0,0>.
    //Note that we have to transpose the model matrix before passing it to the shader
    //This is because OpenGL expects column-major matrices, but you've
    //implemented row-major matrices.
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-2,0,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(3,3,3));
    //Send the geometry's transformation matrix to the shader
    m_progLambert.setModelMatrix(model);
    //Draw the example sphere using our lambert shader
    m_progLambert.draw(m_mesh);
    //Now do the same to render the cylinder
    //We've rotated it -45 degrees on the Z axis, then translated it to the point <2,2,0>
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2,2,0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0,0,1));
    m_progLambert.setModelMatrix(model);
    m_progLambert.draw(m_mesh);
#endif
}


void MyGL::keyPressEvent(QKeyEvent *e)
{
    float amount = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    // This could all be much more efficient if a switch
    // statement were used, but I really dislike their
    // syntax so I chose to be lazy and use a long
    // chain of if statements instead
    if (e->key() == Qt::Key_Escape) {
        QApplication::quit();
    } else if (e->key() == Qt::Key_Right) {
        m_glCamera.RotateAboutUp(-amount);
    } else if (e->key() == Qt::Key_Left) {
        m_glCamera.RotateAboutUp(amount);
    } else if (e->key() == Qt::Key_Up) {
        m_glCamera.RotateAboutRight(-amount);
    } else if (e->key() == Qt::Key_Down) {
        m_glCamera.RotateAboutRight(amount);
    } else if (e->key() == Qt::Key_1) {
        m_glCamera.fovy += amount;
    } else if (e->key() == Qt::Key_2) {
        m_glCamera.fovy -= amount;
    } else if (e->key() == Qt::Key_W) {
        m_glCamera.TranslateAlongLook(amount);
    } else if (e->key() == Qt::Key_S) {
        m_glCamera.TranslateAlongLook(-amount);
    } else if (e->key() == Qt::Key_D) {
        m_glCamera.TranslateAlongRight(amount);
    } else if (e->key() == Qt::Key_A) {
        m_glCamera.TranslateAlongRight(-amount);
    } else if (e->key() == Qt::Key_Q) {
        m_glCamera.TranslateAlongUp(-amount);
    } else if (e->key() == Qt::Key_E) {
        m_glCamera.TranslateAlongUp(amount);
    } else if (e->key() == Qt::Key_R) {
        m_glCamera = Camera(this->width(), this->height());
    }
    m_glCamera.RecomputeAttributes();

    //Debugging tool
    if(e->key() == Qt::Key_N) {
        if(m_curHalfEdge != nullptr
                && m_curHalfEdge->nextHalfEdge != nullptr) {
            m_curItem = m_curHalfEdge->nextHalfEdge;

            m_curHalfEdge = m_curHalfEdge->nextHalfEdge;
            m_curVert = nullptr;
            m_curFace = nullptr;

            emit(changeSelected(m_curItem, 2));
        }
    } else if(e->key() == Qt::Key_M) {
        if(m_curHalfEdge != nullptr
                && m_curHalfEdge->symHalfEdge != nullptr) {
            m_curItem = m_curHalfEdge->symHalfEdge;

            m_curHalfEdge = m_curHalfEdge->symHalfEdge;
            m_curVert = nullptr;
            m_curFace = nullptr;

            emit(changeSelected(m_curItem, 2));
        }
    } else if(e->key() == Qt::Key_F) {
        if(m_curHalfEdge != nullptr
                && m_curHalfEdge->face != nullptr) {
            m_curItem = m_curHalfEdge->face;

            m_curFace = m_curHalfEdge->face;
            m_curVert = nullptr;
            m_curHalfEdge = nullptr;

            emit(changeSelected(m_curItem, 3));
        }
    } else if(e->key() == Qt::Key_V) {
        if(m_curHalfEdge != nullptr
                && m_curHalfEdge->vert != nullptr) {
            m_curItem = m_curHalfEdge->vert;

            m_curVert = m_curHalfEdge->vert;
            m_curHalfEdge = nullptr;
            m_curFace = nullptr;

            emit(changeSelected(m_curItem, 1));
        }
    } else if(e->key() == Qt::Key_H && e->modifiers() != Qt::SHIFT) {
        if(m_curVert != nullptr
                && m_curVert->halfEdge != nullptr) {
            m_curItem = m_curVert->halfEdge;

            m_curHalfEdge = m_curVert->halfEdge;
            m_curVert = nullptr;
            m_curFace = nullptr;

            emit(changeSelected(m_curItem, 2));
        }
    } else if(e->key() == Qt::Key_H && e->modifiers() == Qt::SHIFT) {
        if(m_curFace != nullptr
                && m_curFace->halfEdge != nullptr) {
            m_curItem = m_curFace->halfEdge;

            m_curHalfEdge = m_curFace->halfEdge;
            m_curVert = nullptr;
            m_curFace = nullptr;

            emit(changeSelected(m_curItem, 2));
        }
    }
    update();  // Calls paintGL, among other things
}

Mesh* MyGL::getMesh() {
    return m_meshPointer;
}

void MyGL::updateSeleted(QListWidgetItem* item) {
    m_curItem = item;
    m_curVert = dynamic_cast<Vertex*>(item);
    m_curHalfEdge = dynamic_cast<HalfEdge*>(item);
    m_curFace = dynamic_cast<Face*>(item);
}

void MyGL::meshChange(QListWidgetItem* item) {
    m_mesh.destroy();
    m_mesh.create();
    m_curItem = item;
    Vertex* curVert = dynamic_cast<Vertex*>(item);
    if(curVert != nullptr) {
        m_highlight.updateState(curVert);
    }

    Face* curFace = dynamic_cast<Face*>(item);
    if(curFace != nullptr) {
        m_highlight.updateState(curFace);
    }

    HalfEdge* curHalfEdge = dynamic_cast<HalfEdge*>(item);
    if(curHalfEdge != nullptr) {
        m_highlight.updateState(curHalfEdge);
    }
    if(item != nullptr) {
        m_highlight.destroy();
        m_highlight.create();
    }
    update();
}

void MyGL::addVert()
{
    if(m_curHalfEdge == nullptr)
        return;

    m_mesh.addVert(m_curHalfEdge);
    meshChange();
    emit(updateLists());
}

void MyGL::triangulateFace()
{
    if(m_curFace == nullptr)
        return;

    m_mesh.triangulateFace(m_curFace);
    meshChange();
    emit(updateLists());
}

void MyGL::subdivision()
{
    m_mesh.subdivision();
    meshChange();
    emit(updateLists());
}

void MyGL::loadFromFile()
{

    m_mesh.loadFromFile();
    m_highlight.setNull();
    meshChange();
    emit(updateLists());
}

void MyGL::extrudeFace()
{
    if(m_curFace == nullptr)
        return;
    m_mesh.extrudeFace(m_curFace, 0.3);
    meshChange();
    emit(updateLists());
}

void MyGL::bevelEdge()
{
    if(m_curHalfEdge == nullptr)
        return;
    m_mesh.bevelEdge(m_curHalfEdge, 0.8);
    meshChange();
    emit(updateLists());
}

