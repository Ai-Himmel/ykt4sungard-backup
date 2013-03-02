alter table Group_ add typeSettings long varchar;

alter table SCProductEntry add tags varchar(300);
alter table SCProductEntry add author varchar(75);

create table SCProductScreenshot (
	productScreenshotId bigint not null primary key,
	companyId bigint,
	groupId bigint,
	productEntryId bigint,
	thumbnailId bigint,
	fullImageId bigint,
	priority integer
);

alter table TagsAsset add description long varchar;
alter table TagsAsset add summary long varchar;
