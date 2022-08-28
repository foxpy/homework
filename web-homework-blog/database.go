package main

import (
	"database/sql"
	"fmt"
	_ "github.com/lib/pq"
	"log"
	"time"
)

type Article struct {
	Id       uint64
	Name     string
	Username string
	Date     time.Time
	Brief    string
	Content  string
}

type UserLink struct {
	NumArticles uint64
	Username    string
}

const (
	// A crude way to specify database connection parameters.
	// Not if a care too much about flexibility in this case, it is
	// sufficient just to manually edit constants and rebuild package.
	user     = "blog"
	dbname   = "blog"
	password = "blog"
	sslmode  = "disable"
)

var (
	db = setupDB()
)

func setupDB() *sql.DB {
	connStr := fmt.Sprintf("user=%s dbname=%s password=%s sslmode=%s", user, dbname, password, sslmode)
	_db, err := sql.Open("postgres", connStr)
	if err != nil {
		panic(err.Error())
	}
	return _db
}

func closeRows(rows *sql.Rows) {
	err := rows.Close()
	if err != nil {
		log.Println(err.Error())
	}
}

func rowsToArticleLinks(rows *sql.Rows) ([]Article, error) {
	var artileLinks []Article
	for rows.Next() {
		var b Article
		err := rows.Scan(&b.Id, &b.Name, &b.Username, &b.Date, &b.Brief)
		if err != nil {
			return nil, err
		}
		artileLinks = append(artileLinks, b)
	}
	return artileLinks, nil
}

func rowsToUserLinks(rows *sql.Rows) ([]UserLink, error) {
	var userLinks []UserLink
	for rows.Next() {
		var l UserLink
		err := rows.Scan(&l.NumArticles, &l.Username)
		if err != nil {
			return nil, err
		}
		userLinks = append(userLinks, l)
	}
	return userLinks, nil
}

func GetArticleLinks() ([]Article, error) {
	rows, err := db.Query("select id, name, username, publish_date, brief from articles order by publish_date desc;")
	if err != nil {
		return nil, err
	}
	defer closeRows(rows)
	return rowsToArticleLinks(rows)
}

func GetArticleLinksByUser(username string) ([]Article, error) {
	rows, err := db.Query(
		`select id, name, username, publish_date, brief
from articles where username = $1 order by publish_date desc;`, username)
	if err != nil {
		return nil, err
	}
	defer closeRows(rows)
	return rowsToArticleLinks(rows)
}

func GetArticleByID(id uint64) (*Article, error) {
	row := db.QueryRow("select id, name, username, publish_date, brief, content from articles where id = $1;", id)
	b := &Article{}
	err := row.Scan(&b.Id, &b.Name, &b.Username, &b.Date, &b.Brief, &b.Content)
	if err != nil {
		return nil, err
	}
	return b, nil
}

func DeleteArticleByID(id uint64) error {
	_, err := db.Exec("delete from articles where id = $1;", id)
	return err
}

func InsertNewArticle(b Article) (id uint64, err error) {
	err = db.QueryRow(
		`insert into articles(name, username, publish_date, brief, content)
values($1, $2, now(), $3, $4)
returning id;`,
		b.Name, b.Username, b.Brief, b.Content).Scan(&id)
	return
}

func UpdateArticle(b Article) error {
	// TODO: store edit date and display it online
	_, err := db.Exec(`update articles set name=$1, username=$2, brief=$3, content=$4 where id = $5;`,
		b.Name, b.Username, b.Brief, b.Content, b.Id)
	return err
}

func GetUserLinks() ([]UserLink, error) {
	rows, err := db.Query("select count(id) as numarticles, username from articles group by username;")
	if err != nil {
		return nil, err
	}
	defer closeRows(rows)
	return rowsToUserLinks(rows)
}
