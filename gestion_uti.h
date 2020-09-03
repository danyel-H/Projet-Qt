#ifndef GESTION_UTI_H
#define GESTION_UTI_H

#include <QWidget>

/******************************************
 * Widget n'étant disponible que pour les administrateurs et permettant de modifier le login,
 * le Nom et le type d'utilisateur de n'importe quel utilisateur selon son club
 * ***************************************/


namespace Ui
    {
    class gestion_uti;
    }

class gestion_uti : public QWidget
    {
    Q_OBJECT

    public:
        explicit gestion_uti(QWidget *parent = 0);
        ~gestion_uti();

    private:
        Ui::gestion_uti *ui;

    private slots:
        void init_tableau();
        void showContextMenu(QPoint);
        void verif_type(const QModelIndex&, const QModelIndex&);
    };

#endif // GESTION_UTI_H
