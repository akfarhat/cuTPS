create table if not exists User (
    id int primary key not null,
    username text not null,
    name text not null,
    password text not null
);

create table if not exists Student(
    user_id integer primary key not null,
    student_num int not null,
    email char(255),
    foreign key(user_id) references User(id)
);

create table if not exists ContentManager(
    user_id integer primary key not null,
    foreign key(user_id) references User(id)
);

create table if not exists Administrator(
    user_id integer primary key not null,
    foreign key(user_id) references User(id)
);

create table if not exists DeliveryInfo(
    user_id integer primary key not null,
    email char(255) not null,
    foreign key(user_id) references User(id)
);

create table if not exists CreditCardInfo(
    user_id integer primary key not null,
    type text not null,
    holder_name text not null,
    number char(19) not null,
    expiry_date text not null,
    security_code text not null,
    foreign key(user_id) references User(id)
);

create table if not exists User_Course(
    user_id int not null,
    course_id int  not null,
    primary key( user_id, course_id ),
    foreign key(user_id) references User(id),
    foreign key(course_id) references Course(id)
);

create table if not exists Course(
    id integer primary key not null,
    code char(10) not null,
    name text not null
);

create table if not exists Course_Textbook(
    course_id int not null,
    textbook_id int not null,
    primary key( course_id, textbook_id ),
    foreign key(course_id) references Course(id),
    foreign key(textbook_id) references Textbook(id)
);

create table if not exists SellableItem(
   id integer primary key not null,
   name text not null,
   price_cents integer not null,
   available int not null
);

create table if not exists Textbook(
    item_id integer primary key not null,
    isbn text,
    foreign key(item_id) references SellableItem(id)
);

create table if not exists Chapter(
    item_id integer primary key not null,
    textbook_id int not null,
    chapter_num int not null,
    foreign key(textbook_id) references Textbook(id),
    foreign key(item_id) references SellableItem(id)
);

create table if not exists Section(
    item_id integer primary key not null,
    chapter_id int not null,
    section_num float not null,
    foreign key(chapter_id) references Chapter(id),
    foreign key(item_id) references SellableItem(id)
);

create table if not exists Report(
    id integer primary key not null,
    name text not null,
    script text not null
);

insert into User values (1, "admin", "Administrator", "pass");
insert into Administrator values (1);

insert into User values (2, "cm", "Content Manager", "pass");
insert into ContentManager values (2);

insert into User values (3, "student", "John Doe", "pass");
insert into Student values (3, "100123456", "student@cmail.carleton.ca");

insert into User_Course values (3,1);

insert into Course values (1, "COMP3004", "Object-Oriented Software Engineering");

insert into Textbook values (1, "Ojbect-Oriented Software Engineering: Using UML, Patterns, and
Java", "123456", 1);

insert into Course_Textbook values (1,1);

