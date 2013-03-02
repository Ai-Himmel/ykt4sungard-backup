alter table BookmarksEntry add priority integer;

alter table Layout add description long varchar null;
alter table Layout add dlFolderId bigint;

alter table Organization_ add location boolean;

commit;

update Organization_ set location = FALSE;
