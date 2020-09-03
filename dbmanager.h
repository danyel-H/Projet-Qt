#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

/***************************************
 * Classe gérant toutes les intéractions à la base de données
 * Le constructeur demande un booléen lors de son appel afin de se connecter à la base de données
 * si le booléen est vrai.
 * La fermeture est opérée via close_db()
 * **************************************/

class DBManager
    {
    private:
        QSqlDatabase db;
        static QString login;
        static QString nom;
        static int type;
        static QString id_u;

    public:
        DBManager(bool = false);
        void connect_db();
        void close_db();
        bool connect_user(QString, QString);
        bool insert_user(QString, QString, QString, QString, QString);
        bool insert_ticket(QString, QString, QString,QString);
        bool traiter_ticket(QString, QString);
        bool supprimer_ticket(QString);
        bool supprimer_user(QString);
        QString get_nom();
        QString get_login();
        int get_type();

    };

#endif // DBMANAGER_H
