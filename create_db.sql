create table if not exists User (
    id int primary key not null,
    username text not null,
    name text not null,
    password text not null,
    role int not null
);

create table if not exists Student(
    user_id integer primary key not null,
    student_num int not null,
    email char(255),
    foreign key(user_id) references User(id) on delete cascade
);

create table if not exists ContentManager(
    user_id integer primary key not null,
    foreign key(user_id) references User(id) on delete cascade
);

create table if not exists Administrator(
    user_id integer primary key not null,
    foreign key(user_id) references User(id) on delete cascade 
);

create table if not exists DeliveryInfo(
    user_id integer primary key not null,
    email char(255) not null,
    foreign key(user_id) references User(id) on delete cascade
);

create table if not exists CreditCardInfo(
    user_id integer primary key not null,
    holder_name text not null,
    number char(19) not null,
    expiry_date text not null,
    security_code text not null,
    foreign key(user_id) references User(id) on delete cascade
);

create table if not exists User_Course(
    user_id int not null,
    course_id int  not null,
    primary key( user_id, course_id ),
    foreign key(user_id) references User(id) on delete cascade,
    foreign key(course_id) references Course(id) on delete cascade
);

create table if not exists Course(
    id integer primary key not null,
    code char(10) not null,
    name text not null,
    term_section char(1) not null,
    term_year int not null
);

create table if not exists Course_Textbook(
    course_id int not null,
    textbook_id int not null,
    primary key( course_id, textbook_id ),
    foreign key(course_id) references Course(id) on delete cascade,
    foreign key(textbook_id) references Textbook(id) on delete cascade
);

create table if not exists SellableItem(
   id integer primary key not null,
   name text not null,
   price_cents integer not null,
   available int not null
);

create table if not exists Textbook(
    item_id integer primary key not null,
    edition text,
    authors text,
    isbn text,
    foreign key(item_id) references SellableItem(id) on delete cascade
);

create table if not exists Chapter(
    item_id integer primary key not null,
    textbook_id int not null,
    chapter_num int not null,
    foreign key(textbook_id) references Textbook(id) on delete cascade,
    foreign key(item_id) references SellableItem(id) on delete cascade
);

create table if not exists Section(
    item_id integer primary key not null,
    chapter_id int not null,
    section_num int not null,
    foreign key(chapter_id) references Chapter(id) on delete cascade,
    foreign key(item_id) references SellableItem(id) on delete cascade
);

create table if not exists Report(
    id integer primary key not null,
    name text not null,
    script text not null
);

insert into User values (1, "admin", "Administrator", "6768baac184359a3aab593bceec8fe4882fc8b6d|FP2BX", 0);
insert into Administrator values (1);

insert into User values (2, "cm", "Content Manager", "ad52a56dcdcc1348a60d639b952e4b22ef2675fc|8U8GW", 1);
insert into ContentManager values (2);

insert into User values (3, "joesmith", "Joe Smith", "246a98379322b1065d1f047a5b19e2fa1985265d|A3SY6", 2);
insert into Student values (3, "100123457", "joesmith@cmail.carleton.ca");

insert into User values (4, "woyorus", "woyorus", "c5bfcce2af6b93a2f9509549ffcbe0016ce56f44|JPO7X", 2);
insert into Student values (4, "100867357", "woyorus@gmail.com");

insert into Course values (1, "COMP3004", "Object-Oriented Software Engineering", 'A', 2014);
insert into Course values (2, "COMP3000", "Operating Systems", 'A', 2014);

insert into User_Course values (3,1);
insert into User_Course values (4,1);
insert into User_Course values (4,2);

insert into SellableItem values (1, "Object-Oriented Software Engineering: Using UML, Patterns, and Java", "12356", 1);
insert into SellableItem values (2, "Introduction", "1000", 1);
insert into SellableItem values (3, "Welcome", "345", 1);

insert into Textbook values (1, "2", "John Author", "123-456-7890");

insert into Chapter values (2, 1, 1);

insert into Section values (3, 2, 1);

insert into Course_Textbook values (1,1);

