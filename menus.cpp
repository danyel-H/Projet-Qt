#include "menus.h"
#include "ui_menus.h"
//Debug
#include <QMessageBox>
#include <QCloseEvent>

menus::menus(QWidget *parent) : QMainWindow(parent), ui(new Ui::menus)
    {
    ui->setupUi(this);
    setWindowTitle("Gestion - "+db.get_nom());
    ui->bienvenueLbl->setText("Bienvenue, "+ db.get_nom());

    //Connexion des signaux aux slots
    connect(ui->gestion_bout,SIGNAL(clicked()), this, SLOT(click_gestion()));
    connect(ui->inscription_bout,SIGNAL(clicked()), this, SLOT(click_inscription()));
    connect(ui->ajouter_bout,SIGNAL(clicked()), this, SLOT(click_ajout()));
    connect(ui->util_bout,SIGNAL(clicked()), this, SLOT(click_utilisateurs()));
    connect(ui->actionTest,SIGNAL(triggered(bool)), this, SLOT(trigger_aide()));
    connect(ui->actionQuitter,SIGNAL(triggered(bool)), this, SLOT(trigger_quit()));

    if(db.get_type() == 2)
        {
        ui->inscription_bout->setHidden(true);
        ui->util_bout->setHidden(true);
        }
    }

menus::~menus()
    {
    delete ui;
    }

void menus::click_gestion()
    {
    clear_content(1);

    g = new gestion_ticket(this);
    ui->conteneur->addWidget(g);
    g->show();

    enable_all_except(ui->gestion_bout);
    }

void menus::click_ajout()
    {
    clear_content(2);

    a = new ajout_ticket(this);
    ui->conteneur->addWidget(a);
    a->show();

    enable_all_except(ui->ajouter_bout);
    }


void menus::click_inscription()
    {
    clear_content(3);

    i = new inscription(this);
    ui->conteneur->addWidget(i);
    i->show();

    enable_all_except(ui->inscription_bout);
    }

void menus::click_utilisateurs()
    {
    clear_content(4);

    u = new gestion_uti(this);
    ui->conteneur->addWidget(u);
    u->show();

    enable_all_except(ui->util_bout);
    }

void menus::clear_content(int c)
    {
    //Efface le widget en cours en fonction de l'ancien widget activé, représenté par la variable "choix"
    //choix est par défaut activé à 0
    switch (choix)
        {
        case 1:
            g->close();
            break;
        case 2:
            a->close();
            break;
        case 3:
            i->close();
            break;
        case 4:
            u->close();
            break;
        default:
            break;
        }
    choix = c;
    }

void menus::enable_all_except(QPushButton * q)
    {
    ui->ajouter_bout->setEnabled(true);
    ui->inscription_bout->setEnabled(true);
    ui->gestion_bout->setEnabled(true);
    ui->util_bout->setEnabled(true);
    q->setEnabled(false);
    }

void menus::trigger_aide()
    {
    QMessageBox msgBox;
    msgBox.setText("Une erreur a eu lieu.");
    msgBox.exec();
    }

void menus::trigger_quit()
    {
    close();
    db.close_db();
    }

//Méthode surdéfinie appelée lors de la fermeture de la fenêtre
void menus::closeEvent(QCloseEvent *e)
    {
    emit closed();
    e->accept();
    }
