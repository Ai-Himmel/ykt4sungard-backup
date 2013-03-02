alter table BookmarksEntry add priority integer;

alter table Layout add description varchar(500);
alter table Layout add dlFolderId bigint;

alter table Organization_ add location smallint;

commit;

update Organization_ set location = 0;
