#include "gestion_uti.h"
#include "ui_gestion_uti.h"
#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <dbmanager.h>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QModelIndexList>
#include <QModelIndex>

gestion_uti::gestion_uti(QWidget *parent) : QWidget(parent), ui(new Ui::gestion_uti)
    {
    ui->setupUi(this);

    //Ajout des différents clubs sur le comboBox voué à ça
    QString req2 = "select libelle from clubs";
    QSqlQueryModel * modele_club = new QSqlQueryModel;
    modele_club->setQuery(req2);
    ui->selectClub->setModel(modele_club);

    //Initialisation du tableau
    init_tableau();

    //Configuration du Menu : Sélection sur toute une ligne et seulement une, invoquant un menu préfait
    ui->table_uti->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_uti->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_uti->setContextMenuPolicy(Qt::CustomContextMenu);

    //Connexion des différents slots et signaux
    connect(ui->table_uti, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->selectClub,SIGNAL(currentIndexChanged(int)), this, SLOT(init_tableau()));
    //connect(ui->table_uti->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(verif_type(const QModelIndex&, const QModelIndex&)));
    }

gestion_uti::~gestion_uti()
    {
    delete ui;
    }

void gestion_uti::init_tableau()
    {
    QString club = ui->selectClub->currentText();
    QSqlTableModel * model = new QSqlTableModel();
    model->setTable("utilisateurs");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setFilter("id_club = (select id_club from clubs where libelle = '"+club+"')");
    model->filter();
    model->select();
    model->setHeaderData(1, Qt::Horizontal, tr("Identifiant"));
    model->setHeaderData(3, Qt::Horizontal, tr("Nom"));
    model->setHeaderData(5, Qt::Horizontal, tr("Type d'utilisateur"));

    ui->table_uti->setModel(model);
    ui->table_uti->hideColumn(0);
    ui->table_uti->hideColumn(2);
    ui->table_uti->hideColumn(4);
    ui->table_uti->setColumnWidth(1, 200);
    }

void gestion_uti::showContextMenu(QPoint pos)
    {
    QMenu menu(this);

    QAction *u = menu.addAction("Supprimer la ligne");
    QAction *a = menu.exec(ui->table_uti->viewport()->mapToGlobal(pos));
    if(a == u)
        {
        QMessageBox confirm;
        confirm.setWindowTitle("Confirmer");
        confirm.setText(QString::fromUtf8("Êtes-vous sûr ?"));
        confirm.setStandardButtons(QMessageBox::Yes);
        confirm.addButton(QMessageBox::No);

        if (confirm.exec() == QMessageBox::Yes)
            {
            //Retourne la liste des lignes sélectionnées
            QModelIndexList selection = ui->table_uti->selectionModel()->selectedRows();

            if (selection.count() > 0)
                {
                //Retourne la liste des lignes sélectionnées
                QModelIndexList selection = ui->table_uti->selectionModel()->selectedRows();

                //Obtenir l'index de la ligne sélectionnée sous forme de QModelIndex et d'entier
                QModelIndex indexLigne = selection.at(0);
                int ligneChoisie = indexLigne.row();

                QString id_u = ui->table_uti->model()->data(indexLigne).toString();

                DBManager db;
                db.supprimer_user(id_u);

                //Cache la ligne afin de "confirmer" la suppression
                //ui->table_uti->hideRow(ligneChoisie);
                init_tableau();
                }
            }
        }
    }

void gestion_uti::verif_type(const QModelIndex& a, const QModelIndex& b)
    {
    QMessageBox m;
    m.setText("");
    m.exec();
    }
