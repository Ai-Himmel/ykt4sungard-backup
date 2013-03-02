alter table BookmarksEntry add priority int;

alter table Layout add description varchar(1000) null;
alter table Layout add dlFolderId decimal(20,0)
go

alter table Organization_ add location int;

go

update Organization_ set location = 0;
