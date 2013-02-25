create tablespace TS_SG_CUR
datafile 
'{dbfile_dir}/ts_sgcur.dbf' size 100M reuse  autoextend on  next 100M  maxsize 20000M
logging
extent management  local  autoallocate
segment space management auto
flashback on;
create tablespace TS_SG_PHOTO
datafile  
'{dbfile_dir}/ts_sgphoto.dbf' size 400M reuse  autoextend on  next 100M  maxsize 20000M
logging
extent management  local  autoallocate
segment space management auto
flashback on;