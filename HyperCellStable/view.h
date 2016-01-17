/* Auteurs          : Ramseyer Sylvain, Roy Axel, Ruedin Cyril
 * Date de modif.   : 17.01.2016
 * Classe           : View
 * Resumé           : Caméra qui montre à l'utilisateur une certaine zone de jeu
 * version          : 0.0
 */

#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class QKeyEvent;

class View : public QGraphicsView
{
public:
    static char keysStatment;
    View(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
signals:
    void wheelEvent(QWheelEvent* e);
};

#endif // VIEW_H
