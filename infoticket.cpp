#include "infoticket.h"
#include "ui_infoticket.h"
#include <QSqlQuery>
#include <QMessageBox>

infoticket::infoticket(QWidget *parent, QString id) : QMainWindow(parent), ui(new Ui::infoticket)
    {
    ui->setupUi(this);

    id_tic = id;

    //Selection des informations nécessaires
    QString select = "select titre, description, type_tic.libelle, urgences.libelle, etats.id_e, utilisateurs.nom, clubs.libelle from tickets ";
    select += "join type_tic on type_tic.id_type = tickets.id_type ";
    select += "join urgences on urgences.id_ur = tickets.id_ur ";
    select += "join etats on etats.id_e = tickets.id_e ";
    select += "join utilisateurs on utilisateurs.id_u = tickets.id_u ";
    select += "join clubs on utilisateurs.id_club = clubs.id_club ";
    select += "where tickets.id_tic = "+id+"";
    QSqlQuery req(select);

    //Affichage des informations
    req.next();
    ui->introduction->setText("Détails du ticket \""+req.value(0).toString()+"\"");
    ui->sujetData->setText(req.value(0).toString());
    ui->descriptionData->setText(req.value(1).toString());
    ui->typeData->setText(req.value(2).toString());
    ui->urgenceData->setText(req.value(3).toString());
    ui->emetteurData->setText(req.value(5).toString());
    ui->clubData->setText(req.value(6).toString());
    setWindowTitle("Détails du ticket \""+req.value(0).toString()+"\"");

    //Impossible de commenter ou de valider si utilisateur Demandeur ou Ticket traité
    if(db.get_type() == 2 || req.value(4).toString() == "2")
        {
        ui->commentaireData->setReadOnly(true);
        ui->valider_bout->close();
        }

    QString comm = "select com from commentaires where id_tic = "+id+"";
    QSqlQuery req2(comm);
    if(req2.next())
        {
        ui->commentaireData->setPlainText(req2.value(0).toString());
        }

    //connexion des signaux aux bons slots
    connect(ui->valider_bout, SIGNAL(clicked()), this, SLOT(traiter_ticket()));
    }

infoticket::~infoticket()
    {
    delete ui;
    }

void infoticket::traiter_ticket()
    {
    QString comm = ui->commentaireData->toPlainText().replace(";",".").replace("'","''");
    QMessageBox msgBox;
    if(comm.length() >= 4 && comm.length() <= 500)
        {
        db.traiter_ticket(comm, id_tic);
        msgBox.setText("Le ticket a bien été traité.");
        close();
        }
    else
        {
        msgBox.setText(QString::fromUtf8("Veillez à garder une taille minimale de 4 caractères et une taille maximale de 500 caractères."));
        }
    msgBox.exec();
    }

//Méthode surdéfinie appelée lors de la fermeture de la fenêtre
void infoticket::closeEvent(QCloseEvent *e)
    {
    emit closed();
    e->accept();
    }
