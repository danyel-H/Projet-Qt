#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QWidget>
#include <dbmanager.h>

namespace Ui
    {
    class inscription;
    }

class inscription : public QWidget
    {
        Q_OBJECT

    public:
        explicit inscription(QWidget *parent = 0);
        void clear_fields();
        ~inscription();

    private:
        Ui::inscription *ui;
        DBManager *db;

    private slots:
        void inscrire_user();
    };

#endif // INSCRIPTION_H
