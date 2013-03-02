create table ActivityTracker (
	activityTrackerId bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	classNameId bigint,
	classPK bigint,
	activity varchar(75),
	extraData clob,
	receiverUserId bigint,
	receiverUserName varchar(75)
);

alter table BlogsEntry add uuid_ varchar(75);

alter table BookmarksEntry add uuid_ varchar(75);

alter table BookmarksFolder add uuid_ varchar(75);

alter table CalEvent add uuid_ varchar(75);

alter table DLFileEntry add uuid_ varchar(75);

alter table DLFileShortcut add uuid_ varchar(75);

alter table DLFolder add uuid_ varchar(75);

update Group_ set type_ = '0' where type_ is;
update Group_ set type_ = '0' where type_ = '';
update Group_ set type_ = '1' where type_ = 'COMMUNITY_OPEN';
update Group_ set type_ = '2' where type_ = 'COMMUNITY_RESTRICTED';
update Group_ set type_ = '3' where type_ = 'COMMUNITY_CLOSED';
update Group_ set type_ = '3' where type_ = '0';

alter table IGFolder add uuid_ varchar(75);

alter table IGImage add uuid_ varchar(75);

alter table JournalArticle add uuid_ varchar(75);
alter table JournalArticle add smallImage smallint;
alter table JournalArticle add smallImageId bigint;
alter table JournalArticle add smallImageURL varchar(75);

alter table JournalArticleImage add uuid_ varchar(75);

create table JournalFeed (
	uuid_ varchar(75),
	id_ bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	feedId varchar(75),
	name varchar(75),
	description varchar(500),
	type_ varchar(75),
	structureId varchar(75),
	templateId varchar(75),
	rendererTemplateId varchar(75),
	delta integer,
	orderByCol varchar(75),
	orderByType varchar(75),
	targetLayoutFriendlyUrl varchar(75),
	targetPortletId varchar(75),
	contentField varchar(75),
	feedType varchar(75),
	feedVersion double
);

alter table JournalStructure add uuid_ varchar(75);

alter table JournalTemplate add uuid_ varchar(75);
alter table JournalTemplate add cacheable smallint;

commit;

update JournalTemplate set cacheable = 1;

alter table MBCategory add uuid_ varchar(75);

alter table MBMessage add uuid_ varchar(75);

create table MembershipRequest (
	membershipRequestId bigint not null primary key,
	companyId bigint,
	userId bigint,
	createDate timestamp,
	groupId bigint,
	comments varchar(500),
	replyComments varchar(500),
	replyDate timestamp,
	replierUserId bigint,
	statusId integer
);

alter table PollsChoice add uuid_ varchar(75);

alter table PollsQuestion add uuid_ varchar(75);

alter table TagsAsset add groupId bigint;
alter table TagsAsset add priority double;
alter table TagsAsset add viewCount integer;

commit;

update TagsAsset set priority = 0, viewCount = 0;

alter table User_ add uuid_ varchar(75);

create table WebDAVProps (
	webDavPropsId bigint not null primary key,
	companyId bigint,
	createDate timestamp,
	modifiedDate timestamp,
	classNameId bigint,
	classPK bigint,
	props clob
);

alter table WikiNode add uuid_ varchar(75);

alter table WikiPage add uuid_ varchar(75);
