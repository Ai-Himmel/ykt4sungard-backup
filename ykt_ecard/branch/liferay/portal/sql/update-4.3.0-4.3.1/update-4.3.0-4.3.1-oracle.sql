alter table BookmarksEntry add priority number(30,0);

alter table Layout add description varchar2(4000) null;
alter table Layout add dlFolderId number(30,0);

alter table Organization_ add location number(1, 0);

commit;

update Organization_ set location = 0;
