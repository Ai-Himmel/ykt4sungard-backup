alter table BookmarksEntry add priority int;

alter table Layout add description varchar(2000) null;
alter table Layout add dlFolderId bigint;

alter table Organization_ add location bit;

go

update Organization_ set location = 0;
