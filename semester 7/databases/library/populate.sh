#!/bin/bash

# A scary script which creates a whole database from scratch

DB_FILE="library.db"
SCHEMA_FILE="library.sql"

create_database() {
	sqlite3 "$DB_FILE" < "$SCHEMA_FILE"
}

insert_human() {
	people="People(first_name, last_name, middle_name, address, passport_number, birthday_date)"
	last_insert="$(echo "INSERT INTO $people VALUES($1); SELECT last_insert_rowid();" | sqlite3 "$DB_FILE")"
	LAST_INSERT_HUMAN_ROWID="$last_insert"
}

insert_number() {
	number="PhoneNumbers(phone_number, human_id)"
	echo "INSERT INTO $number VALUES($1, $LAST_INSERT_HUMAN_ROWID);" | sqlite3 "$DB_FILE"
}

insert_email() {
	email="Emails(email, human_id)"
	echo "INSERT INTO $email VALUES($1, $LAST_INSERT_HUMAN_ROWID);" | sqlite3 "$DB_FILE"
}

insert_reader() {
	reader="Readers(human_id)"
	last_insert="$(echo "INSERT INTO $reader VALUES($LAST_INSERT_HUMAN_ROWID); SELECT last_insert_rowid();" | sqlite3 "$DB_FILE")"
	LAST_INSERT_READER_ROWID="$last_insert"
}

insert_visit() {
	visit="Visits(reader_id, date)"
	echo "INSERT INTO $visit VALUES($LAST_INSERT_READER_ROWID, $1);" | sqlite3 "$DB_FILE"
}

insert_subscription() {
	subscription="Subscriptions(reader_id, expires_at_date)"
	echo "INSERT INTO "$subscription" VALUES($LAST_INSERT_READER_ROWID, $1)" | sqlite3 "$DB_FILE"
}

insert_employee() {
	employee="Employees(human_id, position, started_working_date)"
	echo "INSERT INTO $employee VALUES($LAST_INSERT_HUMAN_ROWID, $1);" | sqlite3 "$DB_FILE"
}

insert_catalog() {
	catalog="Catalogs(name)"
	last_insert="$(echo "INSERT INTO $catalog VALUES($1); SELECT last_insert_rowid();" | sqlite3 "$DB_FILE")"
	LAST_INSERT_CATALOG_ROWID="$last_insert"
}

insert_book() {
	book="Books(catalog_id, isbn, author, name, publisher, publication_year)"
	echo "INSERT INTO $book VALUES($LAST_INSERT_CATALOG_ROWID, $1);" | sqlite3 "$DB_FILE"
}

if [ -f "$DB_FILE" ]; then
	rm "$DB_FILE"
fi

create_database

insert_human "'Vasya', 'Pupkin', 'Ivanovich', 'street 3', 15143, '1995-8-15'"
insert_number "'8-800-555-35-35'"
insert_number "'+7-905-915-12-03'"
insert_email "'vasyapupkin@mail.ru'"
insert_email "'vasyapupkin@gmail.com'"
insert_email "'vasya.pupkin@tuta.nota'"
insert_reader
insert_visit "'2020-02-03'"
insert_visit "'2020-02-07'"
insert_visit "'2020-03-15'"
insert_subscription "'2021-02-03'"

insert_human "'Linus', 'Torvalds', 'Benedict', 'street 5', 19853, '1982-5-13'"
insert_number "'0-000-00-00-00'"
insert_email "'linustorvalds@kernel.org'"
insert_employee "'observer', 2014-5-2"

insert_catalog "'Fantastics'"
insert_book "'1-S-WHATEVER', 'Robert Schekley', 'Mindswap', 'Interstellar Space', 1985"
insert_book "'2-S-WHATEVER', 'Robert Schekley', 'Immortality', 'Interstellar Space', 1987"

insert_catalog "'Classics'"
insert_book "'1-Q-WHATEVER', 'Lev Tolstoy', 'War and Peace', 'Somewhere in Russia', 1973"
