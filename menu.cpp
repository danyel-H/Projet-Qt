#include "menu.h"
#include "ui_menu.h"


menu::menu(QWidget *parent) : QWidget(parent), ui(new Ui::menu)
    {
    ui->setupUi(this);
    ui->bienvenueLbl->setText("Bienvenue, "+ db.get_nom());
    connect(ui->gestion_bout,SIGNAL(clicked()), this, SLOT(click_gestion()));
    connect(ui->inscription_bout,SIGNAL(clicked()), this, SLOT(click_inscription()));
    if(db.get_type() == 2)
        {
        ui->inscription_bout->setHidden(true);
        }
    }

menu::~menu()
    {
    delete ui;
    }

void menu::click_gestion()
    {
    g = new gestion_materiel(this);
    ui->conteneur->addWidget(g);
    g->show();
    ui->gestion_bout->setEnabled(false);
    ui->inscription_bout->setEnabled(true);
    }

void menu::click_inscription()
    {
        g->close();
        /*ui->conteneur->addWidget(g);
        g->show();
        ui->inscription_bout->setEnabled(false);*/
        ui->gestion_bout->setEnabled(true);
    }
