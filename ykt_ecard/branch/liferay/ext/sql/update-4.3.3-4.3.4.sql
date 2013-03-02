alter table BlogsEntry add urlTitle VARCHAR(150) null;

create table BlogsStatsUser (
	statsUserId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	entryCount INTEGER,
	lastPostDate DATE null,
	ratingsTotalEntries INTEGER,
	ratingsTotalScore DOUBLE,
	ratingsAverageScore DOUBLE
);

alter table BlogsStatsUser add ratingsTotalEntries INTEGER;
alter table BlogsStatsUser add ratingsTotalScore DOUBLE;
alter table BlogsStatsUser add ratingsAverageScore DOUBLE;

delete from MBStatsUser where groupId = 0;