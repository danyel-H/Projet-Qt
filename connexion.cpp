#include "connexion.h"
#include "ui_connexion.h"
#include <QMessageBox>
#include <fenetre.h>
#include <menu.h>
#include <menus.h>

connexion::connexion(QWidget *parent) : QWidget(parent), ui(new Ui::connexion)
    {
    ui->setupUi(this);
    connect(ui->boutonConnect,SIGNAL(clicked()), this, SLOT(click_connect()));
    }

connexion::~connexion()
    {
    delete ui;
    }

void connexion::success_connect()
    {
    QMessageBox msgBox;
    msgBox.setText("OK.");
    msgBox.exec();
    close();


    menus *m1;
    m1 = new menus(this);
    m1->show();
    //fenetre *f;
    //f = new fenetre(this);
    //menu * m = new menu(f);
    //f->show();
    //close();
    }

void connexion::click_connect()
    {
    db = new DBManager();
    if(db->connect_user(ui->LoginEdit->text(), ui->MdpEdit->text()))
        {
        success_connect();
        }
    else
        {
        QMessageBox msgBox;
        msgBox.setText("Votre mot de passe ou votre identifiant est incorrect.");
        msgBox.exec();
        }
    }
