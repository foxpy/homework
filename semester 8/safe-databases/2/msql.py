#!/usr/bin/env python3
import sys
import MySQLdb
assert(len(sys.argv) == 2)
cert="/etc/my.cnf.d/ssl/client-cert.pem"
key="/etc/my.cnf.d/ssl/client-key.pem"
ssl={"cert": cert, "key": key}
server="127.0.0.1"
user="tester"
password="87654321"
conn=MySQLdb.connect(host=server, user=user, passwd=password, ssl=ssl)
cursor=conn.cursor()
cursor.execute(sys.argv[1])
print(cursor.fetchall())
cursor.close()
conn.commit()
conn.close()
