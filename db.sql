create database e4_appli;
create role e4_appli_admin password 'admin' login;
grant all on database e4_appli to e4_appli_admin;

\c e4_appli

begin transaction;


create table type_uti
	(
	id_type int primary key,
	libelle varchar(50)
	);

create table type_tic
	(
	id_type int primary key,
	libelle varchar(50)
	);

create table urgences
	(
	id_ur int primary key,
	libelle varchar(100)
	);

create table clubs
	(
	id_club int primary key,
	libelle varchar(500)
	);

create table etats
	(
	id_e int primary key,
	libelle varchar(200)
	);

create table utilisateurs
	(
	id_u int primary key,
	login varchar(50),
	mdp  varchar(62),
	nom	 varchar(100),
	id_club int references clubs not null,
	id_type int references type_uti not null
	);

create table tickets
	(
	id_tic int primary key,
	titre varchar(200),
	description varchar(5000),
	id_type int references type_tic not null,
	id_ur int references urgences not null,
	id_e int references etats not null,
	id_u int references utilisateurs not null
	);

create table commentaires
	(
	id_com int primary key,
	com varchar(500),
	id_tic int references tickets not null
	);


alter table tickets owner to e4_appli_admin;
alter table clubs owner to e4_appli_admin;
alter table utilisateurs owner to e4_appli_admin;
alter table type_uti owner to e4_appli_admin;
alter table type_tic owner to e4_appli_admin;
alter table urgences owner to e4_appli_admin;
alter table etats owner to e4_appli_admin;


insert into type_uti(id_type, libelle)
			values(1, 'Administrateur');
insert into type_uti(id_type, libelle)
				values(2, 'Demandeur');

insert into type_tic(id_type, libelle)
			values(1, 'Incident');
insert into type_tic(id_type, libelle)
			values(2, 'Demande');

insert into urgences(id_ur, libelle)
			values(1, 'Faible');
insert into urgences(id_ur, libelle)
			values(2, 'Moyen');
insert into urgences(id_ur, libelle)
			values(3, 'Majeur');

insert into etats(id_e, libelle)
			values(1, 'En Attente');
insert into etats(id_e, libelle)
			values(2, 'Traité');

insert into clubs(id_club, libelle)
				values(1, 'Baseball');
insert into clubs(id_club, libelle)
				values(2, 'Pétanque');
insert into clubs(id_club, libelle)
				values(3, 'Athlétisme');
insert into clubs(id_club, libelle)
				values(4, 'Tennis');
insert into clubs(id_club, libelle)
				values(5, 'Natation');
insert into clubs(id_club, libelle)
				values(6, 'Football');


insert into utilisateurs(id_u,login, mdp, nom, id_club,id_type)
				values(1,'danyel', md5('toto'), 'Danyel', 2,1);
insert into utilisateurs(id_u,login, mdp, nom, id_club,id_type)
				values(2,'toto', md5('azertyuiop'), 'Toto', 4,2);
insert into utilisateurs(id_u,login, mdp, nom, id_club,id_type)
				values(3,'roger', md5('azertyuiop'), 'Roger', 6,2);

insert into tickets(id_tic, titre, description, id_type, id_ur, id_e, id_u)
				values(1, 'Imprimante désabusée','Elle a été fendue en deux', 1, 3, 1,2);
insert into tickets(id_tic, titre, description, id_type, id_ur, id_e, id_u)
				values(2, 'Internet ne marche plus','svp', 2, 1, 2,3);

insert into commentaires(id_com, com, id_tic)
				values(1, 'Rien à signaler, employé incompétent.', 2);
commit;
