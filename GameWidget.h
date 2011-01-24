#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "Chunk.h"

#include <QGLWidget>
#include <QHash>
#include <QSharedPointer>
#include <QLinkedList>
#include <QKeyEvent>

#include <OpenEXR/ImathVec.h>
using namespace Imath;

class Camera;

class GameWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

    void start(QString user, QString password, QString server);

protected:
    void paintGL();
    void resizeGL(int w, int h);
    void initializeGL();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:

    struct Entity {
        Vec3<float> pos;
        Vec3<float> up;
        Vec3<float> look;
        double stance;
        bool on_ground;
    };

    QHash<Chunk::Coord, QSharedPointer<Chunk> > m_chunks;
    QLinkedList<QSharedPointer<Entity> > m_entities;
    Camera * m_camera;
    Entity * m_player;

    QHash<int, bool> m_key_down;

    static const int c_fps;
    static const double c_time_per_frame_msecs;
    double m_target_time_msecs;

private slots:
    void mainLoop();

private:
    void computeNextFrame();
};

#endif // GAMEWIDGET_H
