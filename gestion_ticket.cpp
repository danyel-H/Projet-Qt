#include "gestion_ticket.h"
#include "ui_gestion_ticket.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <ajout_materiel.h>
#include <QSqlQueryModel>
#include <dbmanager.h>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QModelIndexList>

gestion_ticket::gestion_ticket(QWidget *parent) : QWidget(parent),ui(new Ui::gestion_ticket)
    {
    ui->setupUi(this);
    QString req = "select libelle from etats";
    QSqlQueryModel * modele = new QSqlQueryModel;
    modele->setQuery(req);
    ui->selectEtat->setModel(modele);

    search();

    //Configuration du Menu : Sélection sur toute une ligne et seulement une, invoquant un menu préfait
    ui->table_tickets->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_tickets->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_tickets->setContextMenuPolicy(Qt::CustomContextMenu);

    //Connexion des différents slots et signaux
    connect(ui->table_tickets, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->selectEtat,SIGNAL(currentIndexChanged(int)), this, SLOT(search()));
    }

gestion_ticket::~gestion_ticket()
    {
    delete ui;
    }


void gestion_ticket::search()
    {
    QString etat(ui->selectEtat->currentText());
    if(etat == "En Attente")
        {
        supp_possible = true;
        }
    else
        {
        DBManager db;
        if (db.get_type() == 2)
            {
            supp_possible = false;
            }
        }

    DBManager db;

    QString req = "select id_tic as \"Numero\", titre as \"Titre\", type_tic.libelle as \"Type\", urgences.libelle as \"Niveau\" from tickets";
    req += " join type_tic on tickets.id_type = type_tic.id_type";
    req += " join urgences on tickets.id_ur = urgences.id_ur";
    req += " where id_e = (select id_e from etats where libelle = '"+etat+"')";
    if(db.get_type() == 2)
        {
        req += "and tickets.id_u = (select id_u from utilisateurs where login = '"+db.get_login()+"')";
        }

    QSqlQueryModel * modele = new QSqlQueryModel;
    modele->setQuery(req);
    ui->table_tickets->setModel(modele);
    ui->table_tickets->setColumnWidth(1,245);
    ui->table_tickets->hideColumn(0);
    }

void gestion_ticket::showContextMenu(QPoint pos)
    {
    QMenu menu(this);

    u = menu.addAction("Plus d'infos");
    u2 = menu.addAction("Supprimer la ligne");

    if(!supp_possible)
        {
        u2->setDisabled(true);
        }

    QAction *a = menu.exec(ui->table_tickets->viewport()->mapToGlobal(pos));
    //Cas "plus d'infos"
    if (a == u)
        {
        //Retourne la liste des lignes sélectionnées
        QModelIndexList selection = ui->table_tickets->selectionModel()->selectedRows();

        if (selection.count() > 0)
            {
            QModelIndexList selection = ui->table_tickets->selectionModel()->selectedRows();

            int ligneChoisie = selection.at(0).row();

            if (selection.count() > 0)
                {
                QModelIndex indexLigne = selection.at(0);
                QString id_ticket = ui->table_tickets->model()->data(indexLigne).toString();
                i = new infoticket(this, id_ticket);
                connect(i, SIGNAL(closed()), this, SLOT(search()));
                i->show();
                }
            }
        }
    else
        {
        //Cas "Supprimer"
        if(a == u2)
            {
            QMessageBox confirm;
            confirm.setWindowTitle("Confirmer");
            confirm.setText(QString::fromUtf8("Êtes-vous sûr ?"));
            confirm.setStandardButtons(QMessageBox::Yes);
            confirm.addButton(QMessageBox::No);

            if (confirm.exec() == QMessageBox::Yes)
                {
                //Retourne la liste des lignes sélectionnées
                QModelIndexList selection = ui->table_tickets->selectionModel()->selectedRows();

                if (selection.count() > 0)
                    {
                    //Obtenir l'index de la ligne sélectionnée sous forme de QModelIndex et d'entier
                    QModelIndex indexLigne = selection.at(0);
                    int ligneChoisie = indexLigne.row();

                    QString id_ticket = ui->table_tickets->model()->data(indexLigne).toString();

                    DBManager db;
                    db.supprimer_ticket(id_ticket);

                    search();
                    }
                }
            }
        }
    }
