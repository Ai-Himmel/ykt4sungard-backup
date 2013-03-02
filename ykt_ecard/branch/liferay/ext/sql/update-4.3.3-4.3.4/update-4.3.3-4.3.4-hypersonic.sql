alter table BlogsEntry add urlTitle varchar(150) null;

create table BlogsStatsUser (
	statsUserId bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	entryCount int,
	lastPostDate timestamp null,
	ratingsTotalEntries int,
	ratingsTotalScore double,
	ratingsAverageScore double
);

alter table BlogsStatsUser add ratingsTotalEntries int;
alter table BlogsStatsUser add ratingsTotalScore double;
alter table BlogsStatsUser add ratingsAverageScore double;

delete from MBStatsUser where groupId = 0;
