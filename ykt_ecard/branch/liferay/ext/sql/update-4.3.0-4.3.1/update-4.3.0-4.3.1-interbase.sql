alter table BookmarksEntry add priority integer;

alter table Layout add description varchar(4000);
alter table Layout add dlFolderId int64;

alter table Organization_ add location smallint;

commit;

