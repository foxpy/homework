CREATE TABLE my_object(
	id INTEGER NOT NULL,
	time_create TIMESTAMP NOT NULL,
	time_dead TIMESTAMP,
	PRIMARY KEY(id, time_create)
);

CREATE TABLE Books(
	name VARCHAR NOT NULL
) INHERITS(my_object);
CREATE UNIQUE INDEX Books_idx ON Books(id, time_create);

CREATE TABLE Visitors(
	first_name VARCHAR NOT NULL,
	last_name VARCHAR NOT NULL
) INHERITS(my_object);
CREATE UNIQUE INDEX Visitors_idx ON Visitors(id, time_create);

CREATE TABLE Catalogs(
	name VARCHAR NOT NULL
) INHERITS(my_object);
CREATE UNIQUE INDEX Catalogs_idx ON Catalogs(id, time_create);


CREATE FUNCTION on_books_insert() RETURNS trigger AS $on_books_insert$
	BEGIN
		IF (SELECT count(DISTINCT id) FROM Books WHERE id = NEW.id) > 0 THEN
			UPDATE Books SET time_dead = current_timestamp
				WHERE id = NEW.id AND time_create =
					(SELECT max(time_create) FROM Books WHERE id = NEW.id);
			NEW.time_create := (SELECT time_dead FROM Books
				WHERE id = NEW.id ORDER BY time_create DESC LIMIT 1);
			NEW.time_dead := NULL;
		ELSE
			NEW.time_create = current_timestamp;
		END IF;
		RETURN NEW;
	END;
$on_books_insert$ LANGUAGE plpgsql;

CREATE TRIGGER on_books_insert BEFORE INSERT ON Books
	FOR EACH ROW EXECUTE FUNCTION on_books_insert();


CREATE FUNCTION on_catalogs_insert() RETURNS trigger AS $on_catalogs_insert$
	BEGIN
		IF (SELECT count(DISTINCT id) FROM Catalogs WHERE id = NEW.id) > 0 THEN
			UPDATE Catalogs SET time_dead = current_timestamp
				WHERE id = NEW.id AND time_create =
					(SELECT max(time_create) FROM Catalogs WHERE id = NEW.id);
			NEW.time_create := (SELECT time_dead FROM Catalogs
				WHERE id = NEW.id ORDER BY time_create DESC LIMIT 1);
			NEW.time_dead := NULL;
		ELSE
			NEW.time_create = current_timestamp;
		END IF;
		RETURN NEW;
	END;
$on_catalogs_insert$ LANGUAGE plpgsql;

CREATE TRIGGER on_catalogs_insert BEFORE INSERT ON Catalogs
	FOR EACH ROW EXECUTE FUNCTION on_catalogs_insert();

CREATE FUNCTION my_string_concat (text, text, text)
RETURNS text AS
$$
	SELECT $1 || $2 || $3;
$$ LANGUAGE 'sql' STRICT;

CREATE AGGREGATE cat(text, text)
(
	sfunc = my_string_concat,
	stype = text,
	initcond = ''
);
