alter table Group_ add typeSettings lvarchar;

alter table SCProductEntry add tags lvarchar(300);
alter table SCProductEntry add author varchar(75);

create table SCProductScreenshot (
	productScreenshotId int8 not null primary key,
	companyId int8,
	groupId int8,
	productEntryId int8,
	thumbnailId int8,
	fullImageId int8,
	priority int
)
extent size 16 next size 16
lock mode row;

alter table TagsAsset add description lvarchar;
alter table TagsAsset add summary lvarchar;
