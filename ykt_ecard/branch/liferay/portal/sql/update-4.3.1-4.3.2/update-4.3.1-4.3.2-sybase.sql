alter table Group_ add typeSettings varchar(1000) null;

alter table SCProductEntry add tags varchar(300) null;
alter table SCProductEntry add author varchar(75) null;

create table SCProductScreenshot (
	productScreenshotId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	groupId decimal(20,0),
	productEntryId decimal(20,0),
	thumbnailId decimal(20,0),
	fullImageId decimal(20,0),
	priority int
)
go

alter table TagsAsset add description varchar(1000) null;
alter table TagsAsset add summary varchar(1000) null;
