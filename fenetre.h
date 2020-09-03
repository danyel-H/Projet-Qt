#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include <QWidget>
#include <menus.h>
#include <dbmanager.h>

/***************************************
 * Fenêtre principale de l'application, permet à l'utilisateur de se connecter.
 * Cette fenêtre ne se ferme jamais, elle est cependant inutilisable pendant
 * qu'une session est ouverte et requiert la fermeture de la fenêtre qui suit la connexion
 * afin de la rendre utilisable de nouveau.
 * *************************************/

namespace Ui
    {
    class fenetre;
    }

class fenetre : public QMainWindow
    {
    Q_OBJECT

    public:
        explicit fenetre(QWidget *parent = 0);
        void success_connect();
        ~fenetre();

    private:
        Ui::fenetre *ui;
        DBManager *db;
        menus *m1;

    private slots:
        void aPropos();
        void deconnect();
        void click_connect();
    };

#endif // FENETRE_H
