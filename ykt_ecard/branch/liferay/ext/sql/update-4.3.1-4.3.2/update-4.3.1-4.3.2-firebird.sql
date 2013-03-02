alter table Group_ add typeSettings varchar(4000);

alter table SCProductEntry add tags varchar(300);
alter table SCProductEntry add author varchar(75);

create table SCProductScreenshot (
	productScreenshotId int64 not null primary key,
	companyId int64,
	groupId int64,
	productEntryId int64,
	thumbnailId int64,
	fullImageId int64,
	priority integer
);

alter table TagsAsset add description varchar(4000);
alter table TagsAsset add summary varchar(4000);
