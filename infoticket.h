#ifndef INFOTICKET_H
#define INFOTICKET_H

#include <QMainWindow>
#include <dbmanager.h>

namespace Ui
    {
    class infoticket;
    }

class infoticket : public QMainWindow
    {
        Q_OBJECT

    signals:
        void closed();

    public:
        explicit infoticket(QWidget *parent = 0, QString = "0");
        void closeEvent(QCloseEvent *e);
        ~infoticket();

    private:
        Ui::infoticket *ui;
        QString id_tic;
        DBManager db;

    private slots:
        void traiter_ticket();
    };

#endif // INFOTICKET_H
