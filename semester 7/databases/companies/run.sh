#!/bin/sh
sqlite3 tmp.db <populate.sql
sqlite3 tmp.db "SELECT Providers.name AS provider, Goods.name as goods FROM Providers JOIN Goods ON Providers.tier >= Goods.tier"
rm tmp.db
