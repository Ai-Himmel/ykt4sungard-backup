create tablespace TS_YKT_PHOTO
datafile  '+DG_YKT/yktdb/datafile/ts_photo.dbf'
size 1024M
reuse
  autoextend on
    next 1024M
    maxsize UNLIMITED
logging
extent management  local  autoallocate
segment space management auto
flashback on;
