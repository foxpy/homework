#!/bin/bash
psql -d istudents -c "drop index istudents.tmark_fk_idx;"
psql -d istudents -c "alter table istudents.mark drop constraint mark_pk;"
