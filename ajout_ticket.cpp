#include "ajout_ticket.h"
#include "ui_ajout_ticket.h"
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <dbmanager.h>

ajout_ticket::ajout_ticket(QWidget *parent) : QWidget(parent), ui(new Ui::ajout_ticket)
    {
    ui->setupUi(this);

    //Ajout des différents types sur le comboBox voué à ça
    QString req = "select libelle from type_tic";
    QSqlQueryModel * modele_type = new QSqlQueryModel;
    modele_type->setQuery(req);
    ui->selectType->setModel(modele_type);

    //Ajout des différentes urgences sur le comboBox voué à ça
    QString req2 = "select libelle from urgences";
    QSqlQueryModel * modele_urgence = new QSqlQueryModel;
    modele_urgence->setQuery(req2);
    ui->selectUrgence->setModel(modele_urgence);

    //affectation des signals au différents slots
    connect(ui->valider_bout,SIGNAL(clicked()), this, SLOT(insert_ticket()));
    }

ajout_ticket::~ajout_ticket()
    {
    delete ui;
    }

void ajout_ticket::insert_ticket()
    {
    QString titre = ui->editTitre->text().replace(";",".").replace("'","''");
    QString desc = ui->editDescr->toPlainText().replace(";",".").replace("'","''");
    QString type = ui->selectType->currentText();
    QString urgence = ui->selectUrgence->currentText();
    DBManager db;
    QMessageBox msgBox;
    if(titre.length() >= 4 && desc.length() >= 4)
        {
        db.insert_ticket(titre, desc, type, urgence);
        clear_fields();
        msgBox.setText("L'insertion a bien eu lieu.");
        }
    else
        {
        msgBox.setText(QString::fromUtf8("Veillez à garder une taille minimale de 4 caractères pour chaque entrée."));
        }
    msgBox.exec();
    }

void ajout_ticket::clear_fields()
    {
    ui->editTitre->clear();
    ui->editDescr->clear();
    }
