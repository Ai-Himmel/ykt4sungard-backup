alter table JournalArticle add indexable smallint;

commit;


create table ServiceComponent (
	serviceComponentId int64 not null primary key,
	buildNamespace varchar(75),
	buildNumber int64,
	buildDate int64,
	data_ blob
);

delete from UserTracker;

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId int64 not null primary key,
	userTrackerId int64,
	path_ varchar(4000),
	pathDate timestamp
);
