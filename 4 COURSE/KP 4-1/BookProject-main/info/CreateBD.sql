create database Book
go
create table AUTHORIZED
(
    Id         int identity
        primary key,
    USER_EMAIL nvarchar(20) not null
        unique,
    PASSWORD   nvarchar(20) not null
        unique
)
go

create table AUTHORS
(
    Id          int identity
        primary key,
    AUTHOR_NAME nvarchar(25) not null
        unique
)
go

create table GENRE
(
    Id         int identity
        primary key,
    GENRE_NAME nvarchar(50) not null
        unique
)
go

create table TAG
(
    TAGId    int identity
        primary key,
    TAG_NAME nvarchar(50) not null
        unique
)
go

create table USERS
(
    Id            int identity
        primary key,
    USER_NAME     nvarchar(20)                    not null,
    USER_INFO     nvarchar(max),
    USER_AVATAR   nvarchar(256),
    ACCESS_LEVEL  bit           default 0         not null,
    DATA_CREATE   smalldatetime default getdate() not null,
    ID_AUTHORIZED int                             not null
        references AUTHORIZED
)
go

create table BOOKS
(
    Id               int identity
        primary key,
    BOOK_NAME        nvarchar(max) not null,
    BOOK_STATUS      bit default 0,
    BOOK_SERIES      nvarchar(max),
    ID_USER_ADD      int           not null
        references USERS,
    BOOK_DESCRIPTION nvarchar(max),
    BOOK_IMAGE       nvarchar(max),
    BOOK_FILE        nvarchar(max),
    Chapters         int,
    DATA_RELEASE     int
)
go

create table BOOK_AUTHOR
(
    BOOKId   int not null
        references BOOKS,
    AUTHORId int not null
        references AUTHORS,
    Id       int identity
        constraint BOOK_AUTHOR_pk
            primary key
)
go

create table BOOK_GENRE
(
    BOOKId  int not null
        references BOOKS,
    GENREId int not null
        references GENRE,
    Id      int identity
        constraint BOOK_GENRE_pk
            primary key
)
go

create table BOOK_TAG
(
    BOOKId int not null
        references BOOKS,
    TAGId  int not null
        references TAG,
    Id     int identity
        constraint BOOK_TAG_pk
            primary key
)
go

create table FEEDBACK
(
    Id       int identity
        primary key,
    ID_USER  int                             not null
        references USERS,
    ID_BOOK  int                             not null
        references BOOKS,
    FEEDBACK nvarchar(max),
    RATING   real                            not null
        check ([RATING] >= 0 AND [RATING] <= 10),
    DATE     smalldatetime default getdate() not null
)
go



create unique index USERS_ID_AUTHORIZED_uindex
    on USERS (ID_AUTHORIZED)
go

create table USER_BOOKMARKS
(
    USERId         int                    not null
        references USERS,
    BOOKId         int                    not null
        references BOOKS,
    STATUS_READING nvarchar(25)           not null,
    PRESENCE       bit  default 0         not null,
    DATA_READING   smalldatetime,
    DATA_ADD       date default getdate() not null,
    MARKS          int,
    Id             int identity
        constraint USER_BOOKMARKS_pk
            primary key
)
go


