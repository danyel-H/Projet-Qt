#ifndef AJOUT_MATERIEL_H
#define AJOUT_MATERIEL_H

#include <QMainWindow>

namespace Ui
    {
    class ajout_materiel;
    }

class ajout_materiel : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit ajout_materiel(QWidget *parent = 0);
        ~ajout_materiel();

    private:
        Ui::ajout_materiel *ui;

    private slots:
        void ajouter_materiel();
    };

#endif // AJOUT_MATERIEL_H
