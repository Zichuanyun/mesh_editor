#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>
#include "camera.h"
#include "mesh.h"
#include "highlighteditem.h"
#include "QWidgetItem"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>


class MyGL
    : public GLWidget277
{

    Q_OBJECT

private:
    Cylinder m_geomCylinder;// The instance of a unit cylinder we can use to render any cylinder
    Sphere m_geomSphere;// The instance of a unit sphere we can use to render any sphere
    Mesh m_mesh;
    Mesh* m_meshPointer;
    ShaderProgram m_progLambert;// A shader program that uses lambertian reflection
    ShaderProgram m_progFlat;// A shader program that uses "flat" reflection (no shadowing at all)
    highlightedItem m_highlight;

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    Camera m_glCamera;

    QListWidgetItem* m_curItem;
    Vertex* m_curVert;
    HalfEdge* m_curHalfEdge;
    Face* m_curFace;

public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    Mesh* getMesh();

    void updateSeleted(QListWidgetItem* item = nullptr);
    void meshChange(QListWidgetItem* item = nullptr);

    void addVert();
    void triangulateFace();
    void subdivision();
    void loadFromFile();
    void extrudeFace();
    void bevelEdge();

protected:
    void keyPressEvent(QKeyEvent *e);

signals:
    void changeSelected(QListWidgetItem* item, int type);
    void updateLists();
};


#endif // MYGL_H
