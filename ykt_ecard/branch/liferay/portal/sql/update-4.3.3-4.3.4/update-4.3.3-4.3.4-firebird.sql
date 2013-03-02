alter table BlogsEntry add urlTitle varchar(150);

create table BlogsStatsUser (
	statsUserId int64 not null primary key,
	groupId int64,
	companyId int64,
	userId int64,
	entryCount integer,
	lastPostDate timestamp,
	ratingsTotalEntries integer,
	ratingsTotalScore double precision,
	ratingsAverageScore double precision
);

alter table BlogsStatsUser add ratingsTotalEntries integer;
alter table BlogsStatsUser add ratingsTotalScore double precision;
alter table BlogsStatsUser add ratingsAverageScore double precision;

delete from MBStatsUser where groupId = 0;
