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

insert into User values (1, "cm1", "Content Manager 1", "35838e20b2dbbe9314aaef4f1db266b2a96cf64a|123", 1);
insert into ContentManager values (1);

insert into User values (2, "cm2", "Content Manager 2", "1f6bf5e152fe4549e9fd1ffda4278bec736d9075|123", 1);
insert into ContentManager values (2);

insert into User values (3, "student1", "Student 1", "98c7003d92888a99c40f2f6163cbccdfeefa775f|123", 2);
insert into ContentManager values (3);

insert into User values (4, "student2", "Student 2", "b207e950d1acbcd07718a74614cce0c309b72bee|123", 2);
insert into ContentManager values (4);

insert into Course values (1, "COMP3000", "Operating Systems", 'A', 2014);
insert into Course values (2, "COMP3004", "Object-Oriented Software Engineering", 'A', 2014);
insert into Course values (3, "COMP3005", "Database Management Systems", 'B', 2014);
insert into Course values (4, "COMP3007", "Programming Paradigms", 'A', 2014);
insert into Course values (5, "COMP3008", "Human-computer Interaction", 'D', 2014);
insert into Course values (6, "COMP4109", "Applied Cryptography", 'C', 2014);

insert into User_Course values (3,1);
insert into User_Course values (3,3);
insert into User_Course values (3,5);
insert into User_Course values (3,6);
insert into User_Course values (4,1);
insert into User_Course values (4,2);
insert into User_Course values (4,4);

insert into SellableItem values (1, "Object-Oriented Software Engineering: Using UML, Patterns, and Java", "10000", 1);
insert into SellableItem values (2, "Introduction", "200", 1);
insert into SellableItem values (3, "UML Diagrams", "200", 1);
insert into SellableItem values (4, "System Design", "200", 1);

insert into SellableItem values (5, "Welcome", "100", 1);
insert into SellableItem values (6, "Foreword", "100", 1);
insert into SellableItem values (7, "Use Case Diagrams", "100", 1);
insert into SellableItem values (8, "Sequence Diagrams", "100", 1);
insert into SellableItem values (9, "Functional Model", "100", 1);
insert into SellableItem values (10, "Dynamic Model", "100", 1);

insert into SellableItem values (11, "Cryptography Engineering", "50000", 1);
insert into SellableItem values (12, "Operation Systems: The Three Parts", "30000", 1);

insert into Textbook values (1, "1", "John Author", "123-456-7890");
insert into Textbook values (11, "2", "Ferguson, Schneier, Kohno", "987-456-1270");
insert into Textbook values (12, "7", "Two People", "356-910-7890");

insert into Chapter values (2, 1, 1);
insert into Chapter values (3, 1, 2);
insert into Chapter values (4, 1, 3);

insert into Section values (5, 2, 1);
insert into Section values (6, 2, 2);
insert into Section values (7, 3, 1);
insert into Section values (8, 3, 2);
insert into Section values (9, 4, 1);
insert into Section values (10, 4, 2);

insert into Course_Textbook values (2,1);
insert into Course_Textbook values (6,11);
insert into Course_Textbook values (1,12);

