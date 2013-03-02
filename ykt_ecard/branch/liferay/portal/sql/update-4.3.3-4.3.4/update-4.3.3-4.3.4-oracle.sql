alter table BlogsEntry add urlTitle varchar2(150) null;

create table BlogsStatsUser (
	statsUserId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	entryCount number(30,0),
	lastPostDate timestamp null,
	ratingsTotalEntries number(30,0),
	ratingsTotalScore number(30,20),
	ratingsAverageScore number(30,20)
);

alter table BlogsStatsUser add ratingsTotalEntries number(30,0);
alter table BlogsStatsUser add ratingsTotalScore number(30,20);
alter table BlogsStatsUser add ratingsAverageScore number(30,20);

delete from MBStatsUser where groupId = 0;
