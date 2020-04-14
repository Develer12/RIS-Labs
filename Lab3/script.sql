alter session set "_ORACLE_SCRIPT"=true;
CREATE USER RIS1 IDENTIFIED BY RIS1;
CREATE USER RIS2 IDENTIFIED BY RIS2;

GRANT ALL PRIVILEGES TO RIS1;
GRANT ALL PRIVILEGES TO RIS2;

--to ris1
create table Tris1(id int);
insert into Tris1 values(1);

create table Tris12
(
  id int,
  CONSTRAINT ris_pk PRIMARY KEY (id)
);
insert into Tris12 values(1);
--to ris2
create table Tris2(id int);
insert into Tris2 values(1);


CREATE PUBLIC DATABASE LINK riscon1
  CONNECT TO RIS1 IDENTIFIED BY "RIS1" USING 'RIS';

CREATE PUBLIC DATABASE LINK riscon2
  CONNECT TO RIS2 IDENTIFIED BY "RIS2" USING 'RIS';

  
select * from RIS2.Tris2@riscon2;

insert into RIS2.Tris2@riscon2 values(2);
insert into RIS2.Tris2@riscon2 values(3);
update RIS2.Tris2@riscon2 set id=4 where id=2;
