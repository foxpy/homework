CREATE TABLE IF NOT EXISTS temporary_object(
	id INTEGER NOT NULL,
	time_create TIMESTAMP NOT NULL,
	time_dead TIMESTAMP,
	PRIMARY KEY(id, time_create)
);

CREATE TABLE IF NOT EXISTS Goods(
	name VARCHAR NOT NULL,
	price INTEGER NOT NULL
) INHERITS(temporary_object);
CREATE UNIQUE INDEX IF NOT EXISTS GoodsIdx ON Goods(id, time_create);

CREATE TABLE IF NOT EXISTS Employees(
	name VARCHAR NOT NULL,
	salary INTEGER NOT NULL
) INHERITS(temporary_object);
CREATE UNIQUE INDEX IF NOT EXISTS EmployeesIdx ON Employees(id, time_create);

CREATE OR REPLACE FUNCTION OnGoodsInsert() RETURNS trigger AS $OnGoodsInsert$
BEGIN
	IF (SELECT count(DISTINCT id) FROM Goods WHERE id = NEW.id) > 0 THEN
		UPDATE Goods SET time_dead = current_timestamp WHERE id = NEW.id AND time_create = (SELECT max(time_create) FROM Goods WHERE id = NEW.id);
		NEW.time_create := (SELECT time_dead FROM Goods WHERE id = NEW.id ORDER BY time_create DESC LIMIT 1);
	ELSE
		NEW.time_create := current_timestamp;
	END IF;
	NEW.time_dead := NULL;
	RETURN NEW;
END;
$OnGoodsInsert$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS OnGoodsInsert ON Goods;
CREATE TRIGGER OnGoodsInsert BEFORE INSERT ON Goods FOR EACH ROW EXECUTE FUNCTION OnGoodsInsert();

CREATE OR REPLACE FUNCTION OnEmployeesInsert() RETURNS trigger AS $OnEmployeesInsert$
BEGIN
	IF (SELECT count(DISTINCT id) FROM Employees WHERE id = NEW.id) > 0 THEN
		UPDATE Employees SET time_dead = current_timestamp WHERE id = NEW.id AND time_create = (SELECT max(time_create) FROM Employees WHERE id = NEW.id);
		NEW.time_create := (SELECT time_dead FROM Employees WHERE id = NEW.id ORDER BY time_create DESC LIMIT 1);
	ELSE
		NEW.time_create := current_timestamp;
	END IF;
	NEW.time_dead := NULL;
	RETURN NEW;
END;
$OnEmployeesInsert$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS OnEmployeesInsert ON Employees;
CREATE TRIGGER OnEmployeesInsert BEFORE INSERT ON Employees FOR EACH ROW EXECUTE FUNCTION OnEmployeesInsert();

CREATE OR REPLACE VIEW ActualGoods AS SELECT id, name, price FROM Goods WHERE time_dead IS NULL;
CREATE OR REPLACE VIEW ActualEmployees AS SELECT id, name, salary FROM Employees WHERE time_dead IS NULL;

GRANT SELECT ON ActualGoods TO reader;
GRANT SELECT ON ActualEmployees TO reader;

GRANT SELECT ON ActualGoods TO writer;
GRANT SELECT ON ActualEmployees TO writer;
GRANT INSERT ON ActualGoods TO writer;
GRANT SELECT ON Goods TO writer;
GRANT UPDATE ON Goods TO writer;
GRANT INSERT ON Goods TO writer;

CREATE OR REPLACE FUNCTION OnActualGoodsInsert() RETURNS trigger AS $OnActualGoodsInsert$
BEGIN
	INSERT INTO Goods(id, name, price) VALUES(NEW.id, NEW.name, NEW.price);
	RETURN NEW;
END;
$OnActualGoodsInsert$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS OnActualGoodsInsert ON ActualGoods;
CREATE TRIGGER OnActualGoodsInsert INSTEAD OF INSERT ON ActualGoods FOR EACH ROW EXECUTE FUNCTION OnActualGoodsInsert();
