alter table Group_ add typeSettings varchar2(4000) null;

alter table SCProductEntry add tags varchar2(300) null;
alter table SCProductEntry add author varchar2(75) null;

create table SCProductScreenshot (
	productScreenshotId number(30,0) not null primary key,
	companyId number(30,0),
	groupId number(30,0),
	productEntryId number(30,0),
	thumbnailId number(30,0),
	fullImageId number(30,0),
	priority number(30,0)
);

alter table TagsAsset add description varchar2(4000) null;
alter table TagsAsset add summary varchar2(4000) null;
