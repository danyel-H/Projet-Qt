#ifndef CONNEXION_H
#define CONNEXION_H

#include <dbmanager.h>
#include <QString>
#include <QWidget>

namespace Ui
    {
    class connexion;
    }

class connexion : public QWidget
    {
        Q_OBJECT

    public:
        explicit connexion(QWidget *parent = 0);
        ~connexion();
        void success_connect();

    private:
        Ui::connexion *ui;
        DBManager *db;

    private slots:
        void click_connect();

    };

#endif // CONNEXION_H

