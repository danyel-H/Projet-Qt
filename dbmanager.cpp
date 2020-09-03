#include "dbmanager.h"
QString DBManager::login= "Anonyme";
QString DBManager::id_u = "0";
QString DBManager::nom = "Anon";
int DBManager::type = 2;

DBManager::DBManager(bool b)
    {
    if(b)
        {
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("e4_appli");
        db.setUserName("e4_appli_admin");
        db.setPassword("admin");
        db.open();
        }
    }

void DBManager::close_db()
    {
    db.close();
    }

bool DBManager::connect_user(QString l, QString m)
    {
    bool co = false;
    QString verif = "select count(id_u),id_u, login, nom, id_type from utilisateurs where login ='"+l+"' and mdp=md5('"+m+"') group by id_u";
    QSqlQuery req(verif);
    req.next();

    QString count = req.value(0).toString();
    if(count == "1")
    {
        id_u = req.value(1).toString();
        login = req.value(2).toString();
        nom = req.value(3).toString();
        type = req.value(4).toInt();
        co = true;
    }
    return co;
    }

bool DBManager::insert_user(QString l, QString m, QString n,QString c,QString t)
    {
    bool i = false;
    QString verif = "select count(id_u) from utilisateurs where login ='"+l+"'";
    QSqlQuery req(verif);
    req.next();

    QString count = req.value(0).toString();
    if(count < "1")
        {
        QString insert = "insert into utilisateurs(id_u,login, mdp, nom, id_club,id_type) values";
        insert += "((select max(id_u) from utilisateurs)+1, '"+l+"', md5('"+m+"'),'"+n+"',";
        insert += "(select id_club from clubs where libelle = '"+c+"'),";
        insert += "(select id_type from type_uti where libelle = '"+t+"'))";
        QSqlQuery req2(insert);
        if(req2.exec())
            {
            i = true;
            }
        }
    return i;
    }

bool DBManager::insert_ticket(QString t, QString d, QString ty, QString ur)
    {
    bool i = false;
    QString insert = "insert into tickets(id_tic, titre, description, id_type, id_ur, id_e, id_u) values";
    insert += "((select max(id_tic) from tickets)+1, '"+t+"','"+d+"',";
    insert += "(select id_type from type_tic where libelle = '"+ty+"'),";
    insert += "(select id_ur from urgences where libelle = '"+ur+"'),";
    insert += "1,"+id_u+")";
    QSqlQuery req2(insert);

    if(req2.exec())
        {
        i = true;
        }
    return i;
    }

bool DBManager::supprimer_ticket(QString id)
    {
    bool i = false;
    QString supp_comm= "delete from commentaires where id_tic = "+id+"";
    QString supp = "delete from tickets where id_tic = "+id+"";
    QSqlQuery req0(supp_comm);
    QSqlQuery req(supp);
    req0.exec();
    if(req0.exec() && req.exec())
        {
        i = true;
        }
    return i;
    }

bool DBManager::traiter_ticket(QString com, QString id)
    {
    bool i = false;
    QString insert = "insert into commentaires(id_com, com, id_tic) values((select max(id_com) from commentaires)+1,";
    insert += "'"+com+"', "+id+")";
    QSqlQuery req(insert);
    QString change = "update tickets set id_e = 2 where id_tic ="+id+"";
    QSqlQuery req2(change);
    req2.exec();
    if(req.exec())
        {
        i = true;
        }
    return i;
    }

bool DBManager::supprimer_user(QString id)
    {
    bool i = false;
    QString supp = "delete from utilisateurs where id_u = "+id+"";
    QSqlQuery req(supp);
    if(req.exec())
        {
        i = true;
        }
    return i;
    }

QString DBManager::get_login()
    {
    QString l;
    l = login;
    return l;
    }

QString DBManager::get_nom()
    {
    QString s;
    s = nom;
    return s;
    }

int DBManager::get_type()
    {
    int t;
    t = type;
    return t;
    }
