#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mesh.h"
#include "meshcomponents.h"
#include "QListWidgetItem"
#include "QWidgetItem"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionCamera_Controls_triggered();

    void on_list_vert_itemClicked(QListWidgetItem *item);

    void on_dsp_vert_pos_x_valueChanged(double arg1);

    void on_dsp_vert_pos_y_valueChanged(double arg1);

    void on_dsp_vert_pos_z_valueChanged(double arg1);

    void on_list_face_itemClicked(QListWidgetItem *item);

    void on_dsp_face_col_r_valueChanged(double arg1);

    void on_dsp_face_col_g_valueChanged(double arg1);

    void on_dsp_face_col_b_valueChanged(double arg1);

    void on_list_halfedge_itemClicked(QListWidgetItem *item);

    void on_changeSelected(QListWidgetItem* item, int type);

    void on_updateLists();

    void on_pb_addVert_clicked();

    void on_pb_triangulate_clicked();

    void on_pb_subdivision_clicked();

    void on_actionLoad_obj_triggered();

    void on_pb_extrudeface_clicked();

    void on_pb_bevelEdge_clicked();

private:
    Ui::MainWindow *ui;
    void initLists();
    QListWidgetItem* curItem;
};

#endif // MAINWINDOW_H
