#ifndef GESTION_TICKET_H
#define GESTION_TICKET_H

#include <QWidget>
#include <infoticket.h>

/***************************************
 *Widget permettant à un utilisateur de gérer les tickets auxquels il a accès
 * Les Administrateurs ont accès aux tickets de tous
 * Les Demandeurs ont accès à leurs tickets uniquement
 * Le contenu de la table affichée s'adapte donc selon le type d'utilisateur.
 * ************************************/

namespace Ui
    {
    class gestion_ticket;
    }

class gestion_ticket : public QWidget
    {
    Q_OBJECT

    public:
        explicit gestion_ticket(QWidget *parent = 0);
        ~gestion_ticket();

    private:
        Ui::gestion_ticket *ui;
        bool supp_possible;
        infoticket * i;
        QAction *u;
        QAction *u2;

    private slots:
        void search();
        void showContextMenu(QPoint);
    };

#endif // GESTION_TICKET_H
