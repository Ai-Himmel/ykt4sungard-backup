alter table BookmarksEntry add priority integer;

alter table Layout add description text null;
alter table Layout add dlFolderId bigint;

alter table Organization_ add location bool;

commit;

update Organization_ set location = false;
