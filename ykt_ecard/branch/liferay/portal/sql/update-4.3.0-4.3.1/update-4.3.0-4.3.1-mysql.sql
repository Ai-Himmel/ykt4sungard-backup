alter table BookmarksEntry add priority integer;

alter table Layout add description longtext null;
alter table Layout add dlFolderId bigint;

alter table Organization_ add location tinyint;

commit;

update Organization_ set location = 0;
