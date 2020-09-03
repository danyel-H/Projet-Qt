#ifndef MENUS_H
#define MENUS_H

#include <QMainWindow>
#include <gestion_tickets.h>
#include <ajout_ticket.h>
#include <gestion_uti.h>
#include <dbmanager.h>
#include <inscription.h>
#include <QPushButton>

/***********************************
 * Fenêtre s'ouvrant après la connexion d'un utilisateur
 * s'adapte selon l'utilisateur et permet d'afficher les widgets auquel l'utilisateur a accès
 * *******************************/

namespace Ui
    {
    class menus;
    }

class menus : public QMainWindow
    {
        Q_OBJECT

    signals:
        void closed();

    public:
        explicit menus(QWidget *parent = 0);
        void clear_content(int);
        void enable_all_except(QPushButton*);
        void closeEvent(QCloseEvent *e);
        ~menus();

    private:
        Ui::menus *ui;
        int choix = 0;
        DBManager db;
        gestion_ticket * g;
        gestion_uti * u;
        ajout_ticket *a;
        inscription *i;

    private slots:
        void click_gestion();
        void click_inscription();
        void click_ajout();
        void click_utilisateurs();
        void trigger_aide();
        void trigger_quit();
    };

#endif // MENUS_H
