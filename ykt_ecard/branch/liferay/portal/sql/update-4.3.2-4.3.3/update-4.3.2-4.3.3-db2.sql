alter table JournalArticle add indexable smallint;

commit;

update JournalArticle set indexable = 1;

create table ServiceComponent (
	serviceComponentId bigint not null primary key,
	buildNamespace varchar(75),
	buildNumber bigint,
	buildDate bigint,
	data_ clob
);

delete from UserTracker;

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId bigint not null primary key,
	userTrackerId bigint,
	path_ varchar(500),
	pathDate timestamp
);
