#!/bin/sh
sqlite3 tmp.db <populate.sql
printf ".mode box\nSELECT Providers.name AS provider, Goods.name as goods FROM Providers JOIN Goods ON Providers.tier >= Goods.tier;\n" | sqlite3 tmp.db
rm tmp.db
