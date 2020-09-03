#ifndef GESTION_TICKET_H
#define GESTION_TICKET_H

#include <QWidget>

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

    private slots:
        void search();
        void ajout();
        void showContextMenu(QPoint);
    };

#endif // gestion_ticket_H
