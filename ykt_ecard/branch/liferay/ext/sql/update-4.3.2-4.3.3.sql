alter table JournalArticle add indexable BOOLEAN;

COMMIT_TRANSACTION;

update JournalArticle set indexable = TRUE;

create table ServiceComponent (
	serviceComponentId LONG not null primary key,
	buildNamespace VARCHAR(75) null,
	buildNumber LONG,
	buildDate LONG,
	data_ TEXT null
);

delete from UserTracker;

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId LONG not null primary key,
	userTrackerId LONG,
	path_ STRING null,
	pathDate DATE null
);