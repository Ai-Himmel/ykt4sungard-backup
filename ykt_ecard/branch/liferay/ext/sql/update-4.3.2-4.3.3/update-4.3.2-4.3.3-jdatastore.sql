alter table JournalArticle add indexable boolean;

commit;

update JournalArticle set indexable = TRUE;

create table ServiceComponent (
	serviceComponentId bigint not null primary key,
	buildNamespace varchar(75) null,
	buildNumber bigint,
	buildDate bigint,
	data_ long varchar null
);

delete from UserTracker;

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId bigint not null primary key,
	userTrackerId bigint,
	path_ long varchar null,
	pathDate date null
);
