#include "ajout_materiel.h"
#include "ui_ajout_materiel.h"
#include <iostream>
#include <QMessageBox>
#include <dbmanager.h>
#include <QSqlQueryModel>

ajout_materiel::ajout_materiel(QWidget *parent) : QMainWindow(parent), ui(new Ui::ajout_materiel)
    {
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Ajouter un matériel"));
    QString req = "select libelle from clubs";
    QSqlQueryModel * modele = new QSqlQueryModel;
    modele->setQuery(req);
    ui->selectClub->setModel(modele);
    ui->nbSpin->setMinimum(0);
    ui->nbSpin->setMaximum(100);
    connect(ui->ajout_bout,SIGNAL(clicked()), this, SLOT(ajouter_materiel()));
    }

ajout_materiel::~ajout_materiel()
    {
    delete ui;
    }

void ajout_materiel::ajouter_materiel()
    {
    DBManager db;
    QString nom = ui->nomEdit->text();
    QString marque = ui->marqueEdit->text();
    QString qte = ui->nbSpin->text();
    QString club = ui->selectClub->currentText();
    if(nom.length() >= 3 && marque.length() >= 3)
        {
        /*if(db->insert_user(login, mdp, nom, categorie))
            {
            QMessageBox msgBox;
            msgBox.setText("L'insertion a bien eu lieu.");
            msgBox.exec();
            }
        else
            {
            QMessageBox msgBox;
            msgBox.setText("Une erreur a eu lieu.");
            msgBox.exec();
            }*/
        db.insert_ticket(nom, marque, qte, club);
        QMessageBox msgBox;
        msgBox.setText("L'insertion a bien eu lieu.");
        msgBox.exec();
        }
    else
        {
        QMessageBox msgBox;
        msgBox.setText(QString::fromUtf8("Veillez à garder une taille minimale de 3 caractères pour chaque entrée."));
        msgBox.exec();
        }

    }
