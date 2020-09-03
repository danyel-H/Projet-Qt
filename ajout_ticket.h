#ifndef AJOUT_TICKET_H
#define AJOUT_TICKET_H

#include <QWidget>

namespace Ui
    {
    class ajout_ticket;
    }

class ajout_ticket : public QWidget
    {
        Q_OBJECT

    public:
        explicit ajout_ticket(QWidget *parent = 0);
        void clear_fields();
        ~ajout_ticket();

    private:
        Ui::ajout_ticket *ui;

    private slots:
        void insert_ticket();
    };

#endif // AJOUT_TICKET_H
