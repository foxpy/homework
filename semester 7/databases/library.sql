CREATE TABLE People (
	human_id INTEGER PRIMARY KEY,
	first_name TEXT NOT NULL,
	last_name TEXT NOT NULL,
	middle_name TEXT,
	address TEXT NOT NULL,
	passport_number INTEGER NOT NULL,
	birthday_date TEXT NOT NULL
);

CREATE TABLE PhoneNumbers (
	phone_number_id INTEGER PRIMARY KEY,
	phone_number TEXT NOT NULL,
	human_id INTEGER NOT NULL REFERENCES People
);

CREATE TABLE Emails (
	email_id INTEGER PRIMARY KEY,
	email TEXT NOT NULL,
	human_id INTEGER NOT NULL REFERENCES People
);

CREATE TABLE Employees (
	employee_id INTEGER PRIMARY KEY,
	human_id INTEGER NOT NULL REFERENCES People,
	position TEXT NOT NULL,
	started_working_date TEXT NOT NULL
);

CREATE TABLE Readers (
	reader_id INTEGER PRIMARY KEY,
	human_id INTEGER NOT NULL REFERENCES People
);

CREATE TABLE Visits (
	visit_id INTEGER PRIMARY KEY,
	reader_id INTEGER NOT NULL REFERENCES Readers,
	date TEXT NOT NULL
);

CREATE TABLE Subscriptions (
	subscription_id INTEGER PRIMARY KEY,
	reader_id INTEGER NOT NULL REFERENCES Readers,
	expires_at_date TEXT NOT NULL
);

CREATE TABLE Catalogs (
	catalog_id INTEGER PRIMARY KEY,
	name TEXT NOT NULL
);

CREATE TABLE Books (
	book_id INTEGER PRIMARY KEY,
	catalog_id INTEGER NOT NULL REFERENCES Catalogs,
	isbn TEXT NOT NULL,
	author TEXT NOT NULL,
	name TEXT NOT NULL,
	publisher TEXT NOT NULL,
	publication_year TEXT NOT NULL
);
