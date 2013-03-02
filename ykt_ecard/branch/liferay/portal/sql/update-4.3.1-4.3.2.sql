alter table Group_ add typeSettings STRING null;

alter table SCProductEntry add tags VARCHAR(300) null;
alter table SCProductEntry add author VARCHAR(75) null;

create table SCProductScreenshot (
	productScreenshotId LONG not null primary key,
	companyId LONG,
	groupId LONG,
	productEntryId LONG,
	thumbnailId LONG,
	fullImageId LONG,
	priority INTEGER
);

alter table TagsAsset add description STRING null;
alter table TagsAsset add summary STRING null;