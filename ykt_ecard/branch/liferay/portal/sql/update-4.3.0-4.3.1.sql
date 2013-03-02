alter table BookmarksEntry add priority INTEGER;

alter table Layout add description STRING null;
alter table Layout add dlFolderId LONG;

alter table Organization_ add location BOOLEAN;

COMMIT_TRANSACTION;

update Organization_ set location = FALSE;