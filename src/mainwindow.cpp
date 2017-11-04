#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"
#include <iostream>
#include "la.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    curItem(nullptr)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    connect(ui->mygl,SIGNAL(changeSelected(QListWidgetItem*, int)),this,SLOT(on_changeSelected(QListWidgetItem*, int)));
    connect(ui->mygl,SIGNAL(updateLists()),this,SLOT(on_updateLists()));

    initLists();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLists() {
    Mesh* mesh = ui->mygl->getMesh();
    for(int i = 0; i < mesh->m_verts.size(); i++) {
        ui->list_vert->addItem(mesh->m_verts.at(i));
    }

    for(int i = 0; i < mesh->m_halfedges.size(); i++) {
        ui->list_halfedge->addItem(mesh->m_halfedges.at(i));
    }

    for(int i = 0; i < mesh->m_faces.size(); i++) {
        ui->list_face->addItem(mesh->m_faces.at(i));
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}

void MainWindow::on_list_vert_itemClicked(QListWidgetItem *item)
{

    curItem = item;
    Vertex* curVert = static_cast<Vertex*>(item);

    if(curVert != nullptr) {
        //curVert = temp;
        ui->dsp_vert_pos_x->setEnabled(true);
        ui->dsp_vert_pos_y->setEnabled(true);
        ui->dsp_vert_pos_z->setEnabled(true);

        ui->dsp_face_col_r->setEnabled(false);
        ui->dsp_face_col_g->setEnabled(false);
        ui->dsp_face_col_b->setEnabled(false);

        ui->dsp_vert_pos_x->setValue(curVert->pos.x);
        ui->dsp_vert_pos_y->setValue(curVert->pos.y);
        ui->dsp_vert_pos_z->setValue(curVert->pos.z);
    }
    ui->mygl->updateSeleted(curItem);
    ui->mygl->meshChange(curItem);
}

void MainWindow::on_dsp_vert_pos_x_valueChanged(double arg1)
{

    Vertex* curVert = dynamic_cast<Vertex*>(curItem);

    if(curVert != nullptr) {
        curVert->pos = glm::vec3(arg1,
                                 curVert->pos.y,
                                 curVert->pos.z);
        ui->mygl->meshChange(curItem);
    }
}



void MainWindow::on_dsp_vert_pos_y_valueChanged(double arg1)
{
    Vertex* curVert = dynamic_cast<Vertex*>(curItem);

    if(curVert != nullptr) {
        curVert->pos = glm::vec3(curVert->pos.x,
                                 arg1,
                                 curVert->pos.z);
        ui->mygl->meshChange(curItem);
    }
}

void MainWindow::on_dsp_vert_pos_z_valueChanged(double arg1)
{
    Vertex* curVert = dynamic_cast<Vertex*>(curItem);

    if(curVert != nullptr) {
        curVert->pos = glm::vec3(curVert->pos.x,
                                 curVert->pos.y,
                                 arg1);
        ui->mygl->meshChange(curItem);
    }
}

void MainWindow::on_list_face_itemClicked(QListWidgetItem *item)
{
    curItem = item;
    Face* curFace = static_cast<Face*>(item);

    if(curFace != nullptr) {
        //curVert = temp;
        ui->dsp_vert_pos_x->setEnabled(false);
        ui->dsp_vert_pos_y->setEnabled(false);
        ui->dsp_vert_pos_z->setEnabled(false);

        ui->dsp_face_col_r->setEnabled(true);
        ui->dsp_face_col_g->setEnabled(true);
        ui->dsp_face_col_b->setEnabled(true);

        ui->dsp_face_col_r->setValue(curFace->color.r);
        ui->dsp_face_col_g->setValue(curFace->color.g);
        ui->dsp_face_col_b->setValue(curFace->color.b);
    }
    ui->mygl->updateSeleted(curItem);
    ui->mygl->meshChange(curItem);
}

void MainWindow::on_dsp_face_col_r_valueChanged(double arg1)
{
    Face* curFace = dynamic_cast<Face*>(curItem);

    if(curFace != nullptr) {
        curFace->color = glm::vec3(arg1,
                                 curFace->color.g,
                                 curFace->color.b);
        ui->mygl->meshChange(curItem);
    }
}

void MainWindow::on_dsp_face_col_g_valueChanged(double arg1)
{
    Face* curFace = dynamic_cast<Face*>(curItem);

    if(curFace != nullptr) {
        curFace->color = glm::vec3(curFace->color.r,
                                 arg1,
                                 curFace->color.b);
        ui->mygl->meshChange(curItem);
    }
}

void MainWindow::on_dsp_face_col_b_valueChanged(double arg1)
{
    Face* curFace = dynamic_cast<Face*>(curItem);

    if(curFace != nullptr) {
        curFace->color = glm::vec3(curFace->color.r,
                                 curFace->color.g,
                                 arg1);
        ui->mygl->meshChange(curItem);
    }
}

void MainWindow::on_list_halfedge_itemClicked(QListWidgetItem *item)
{
    curItem = item;
    HalfEdge* curHalfEdge = static_cast<HalfEdge*>(item);
    if(curHalfEdge != nullptr) {
        //curVert = temp;
        ui->dsp_vert_pos_x->setEnabled(false);
        ui->dsp_vert_pos_y->setEnabled(false);
        ui->dsp_vert_pos_z->setEnabled(false);

        ui->dsp_face_col_r->setEnabled(false);
        ui->dsp_face_col_g->setEnabled(false);
        ui->dsp_face_col_b->setEnabled(false);
    }
    ui->mygl->updateSeleted(curItem);
    ui->mygl->meshChange(curItem);
}

void MainWindow::on_changeSelected(QListWidgetItem *item, int type) {
    if(type == 1) {
        on_list_vert_itemClicked(item);
    } else if(type == 2) {
        on_list_halfedge_itemClicked(item);
    } else { // 3
        on_list_face_itemClicked(item);
    }
    item->setSelected(true);
}

void MainWindow::on_updateLists() {
    initLists();
}

void MainWindow::on_pb_addVert_clicked()
{
    ui->mygl->addVert();
    ui->mygl->meshChange();
}

void MainWindow::on_pb_triangulate_clicked()
{
    ui->mygl->triangulateFace();
    ui->mygl->meshChange();
}

void MainWindow::on_pb_subdivision_clicked()
{
    ui->mygl->subdivision();
    ui->mygl->meshChange();
}

void MainWindow::on_actionLoad_obj_triggered()
{
    ui->mygl->loadFromFile();
    ui->mygl->meshChange();
}

void MainWindow::on_pb_extrudeface_clicked()
{
    ui->mygl->extrudeFace();
    ui->mygl->meshChange();
}

void MainWindow::on_pb_bevelEdge_clicked()
{
    ui->mygl->bevelEdge();
    ui->mygl->meshChange();
}
