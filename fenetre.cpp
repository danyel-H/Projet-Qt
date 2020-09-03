#include "fenetre.h"
#include "ui_fenetre.h"
#include <QMessageBox>
#include <QLayout>
#include <QString>

fenetre::fenetre(QWidget *parent) : QMainWindow(parent),ui(new Ui::fenetre)
    {
    ui->setupUi(this);
    setWindowTitle("Connexion");
    db = new DBManager(true);
    connect(ui->actionA_propos,SIGNAL(triggered(bool)), this, SLOT(aPropos()));
    connect(ui->boutonConnect,SIGNAL(clicked()), this, SLOT(click_connect()));
    }

fenetre::~fenetre()
    {
    delete ui;
    }

void fenetre::success_connect()
    {
    //hide();
    m1 = new menus(this);
    connect(m1, SIGNAL(closed()), this, SLOT(deconnect()));

    m1->show();

    //Reinitialisation des informations afin qu'il n'y ai pas deux connexions simultannées
    ui->MdpEdit->clear();
    ui->avertissement->setText("Veuillez quitter votre ancienne session avant de \n\tvouloir vous reconnecter");
    ui->avertissement->setStyleSheet("color:red;");
    ui->boutonConnect->setDisabled(true);
    setWindowTitle("Session en cours");
    }

void fenetre::click_connect()
    {
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

void fenetre::aPropos()
    {
    QMessageBox m;
    m.setText(QString::fromUtf8("Bonjour, \n\nCette application a été développée par Hocquigny Danyel dans le cadre de son BTS SIO."));
    m.exec();
    }

void fenetre::deconnect()
    {
    ui->avertissement->setText("");;
    ui->boutonConnect->setDisabled(false);
    setWindowTitle("Connexion");
    }
