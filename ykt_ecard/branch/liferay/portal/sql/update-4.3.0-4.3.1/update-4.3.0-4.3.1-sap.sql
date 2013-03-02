alter table BookmarksEntry add priority int;

alter table Layout add description varchar null;
alter table Layout add dlFolderId bigint;

alter table Organization_ add location boolean;

commit;

update Organization_ set location = FALSE;
