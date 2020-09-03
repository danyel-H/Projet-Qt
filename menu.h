#ifndef MENU_H
#define MENU_H

#include <dbmanager.h>
#include <gestion_materiel.h>


namespace Ui
    {
    class menu;
    }

class menu : public QWidget
    {
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    ~menu();

private:
    Ui::menu *ui;
    DBManager db;
    gestion_materiel * g;

private slots:
    void click_gestion();
    void click_inscription();
    };

#endif // MENU_H
