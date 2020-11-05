CREATE TABLE Goods (
	goods_id INTEGER PRIMARY KEY,
	name TEXT NOT NULL,
	tier INTEGER NOT NULL
);

CREATE TABLE Providers (
	provider_id INTEGER PRIMARY KEY,
	name TEXT NOT NULL,
	tier INTEGER NOT NULL
);

INSERT INTO Goods(name, tier) VALUES('Intel Atom Z3740', 1);
INSERT INTO Goods(name, tier) VALUES('Intel Atom N2800', 1);
INSERT INTO Goods(name, tier) VALUES('Intel Celeron G1830', 2);
INSERT INTO Goods(name, tier) VALUES('Intel Pentium G3420', 2);
INSERT INTO Goods(name, tier) VALUES('Intel Pentium Gold G6500', 2);
INSERT INTO Goods(name, tier) VALUES('Intel Core i5-3210M', 3);
INSERT INTO Goods(name, tier) VALUES('Intel Core i5-6400', 3);
INSERT INTO Goods(name, tier) VALUES('Intel Core i7-7200U', 3);
INSERT INTO Goods(name, tier) VALUES('Intel Core i9-8950HK', 4);
INSERT INTO Goods(name, tier) VALUES('Intel Xeon Platinum 8280', 4);

INSERT INTO Goods(name, tier) VALUES('AMD Athlon II M300', 1);
INSERT INTO Goods(name, tier) VALUES('AMD Athlon 7750', 1);
INSERT INTO Goods(name, tier) VALUES('AMD A6-3500 APU', 1);
INSERT INTO Goods(name, tier) VALUES('AMD Athlon 3000G', 2);
INSERT INTO Goods(name, tier) VALUES('AMD Opteron 4171 HE', 2);
INSERT INTO Goods(name, tier) VALUES('AMD Phenom II X4 B65', 2);
INSERT INTO Goods(name, tier) VALUES('AMD FX-9370', 3);
INSERT INTO Goods(name, tier) VALUES('AMD Ryzen 5 1400', 3);
INSERT INTO Goods(name, tier) VALUES('AMD Ryzen 7 3900X', 4);
INSERT INTO Goods(name, tier) VALUES('AMD EPYC 7F52', 4);

INSERT INTO Providers(name, tier) VALUES('Подвал дяди Васи', 1);
INSERT INTO Providers(name, tier) VALUES('Подвал дяди Пети', 1);
INSERT INTO Providers(name, tier) VALUES('TPSHOP', 2);
INSERT INTO Providers(name, tier) VALUES('Pleer.ru', 2);
INSERT INTO Providers(name, tier) VALUES('citilink.ru', 3);
INSERT INTO Providers(name, tier) VALUES('dns-shop.ru', 3);
INSERT INTO Providers(name, tier) VALUES('regard.ru', 4);
INSERT INTO Providers(name, tier) VALUES('computeruniverse.net', 4);
