alter table BlogsEntry add urlTitle varchar(150) null;

create table BlogsStatsUser (
	statsUserId bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	entryCount integer,
	lastPostDate timestamp null,
	ratingsTotalEntries integer,
	ratingsTotalScore double precision,
	ratingsAverageScore double precision
);

alter table BlogsStatsUser add ratingsTotalEntries integer;
alter table BlogsStatsUser add ratingsTotalScore double precision;
alter table BlogsStatsUser add ratingsAverageScore double precision;

delete from MBStatsUser where groupId = 0;
