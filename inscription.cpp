#include "inscription.h"
#include "ui_inscription.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <iostream>

inscription::inscription(QWidget *parent) : QWidget(parent), ui(new Ui::inscription)
    {
    ui->setupUi(this);

    //Ajout des différents types sur le ComboBox voué à cet effet
    QString req = "select libelle from type_uti";
    QSqlQueryModel * modele = new QSqlQueryModel;
    modele->setQuery(req);
    ui->selectType->setModel(modele);

    //Ajout des différents clubs sur le comboBox voué à ça
    QString req2 = "select libelle from clubs";
    QSqlQueryModel * modele_club = new QSqlQueryModel;
    modele_club->setQuery(req2);
    ui->selectClub->setModel(modele_club);

    connect(ui->boutonInscrire,SIGNAL(clicked()), this, SLOT(inscrire_user()));
    }

inscription::~inscription()
    {
    delete ui;
    }

void inscription::inscrire_user()
    {
    db = new DBManager();
    QMessageBox msgBox;
    QString login = ui->LoginEdit->text().replace(";",".").replace("'","''");
    QString mdp = ui->MdpEdit->text().replace(";",".").replace("'","''");
    QString nom = ui->nomEdit->text().replace(";",".").replace("'","''");
    QString club = ui->selectClub->currentText();
    QString categorie = ui->selectType->currentText();
    if(login.length() >= 4 && mdp.length() >= 4 && nom.length() >= 4)
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
        db->insert_user(login, mdp, nom, club, categorie);
        clear_fields();
        msgBox.setText("L'insertion a bien eu lieu.");
        }
    else
        {
        msgBox.setText(QString::fromUtf8("Veillez à garder une taille minimale de 4 caractères pour chaque entrée."));
        }
    msgBox.exec();
    }

void inscription::clear_fields()
    {
    ui->LoginEdit->clear();
    ui->MdpEdit->clear();
    ui->nomEdit->clear();
    }
