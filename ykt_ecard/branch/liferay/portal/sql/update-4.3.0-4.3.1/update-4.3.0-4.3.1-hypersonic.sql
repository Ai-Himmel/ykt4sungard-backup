alter table BookmarksEntry add priority int;

alter table Layout add description longvarchar null;
alter table Layout add dlFolderId bigint;

alter table Organization_ add location bit;

commit;

update Organization_ set location = false;
