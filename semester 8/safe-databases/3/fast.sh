#!/bin/bash
psql -d istudents -c "alter table istudents.mark add constraint mark_pk primary key(id);"
psql -d istudents -c "create index tmark_fk_idx on istudents.mark(tmark_fk);"
