alter table BookmarksEntry add priority int;

alter table Layout add description lvarchar;
alter table Layout add dlFolderId int8;

alter table Organization_ add location boolean;



update Organization_ set location = 'F';
