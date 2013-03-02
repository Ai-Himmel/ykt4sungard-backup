create table ActivityTracker (
	activityTrackerId int64 not null primary key,
	groupId int64,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	classNameId int64,
	classPK int64,
	activity varchar(75),
	extraData blob,
	receiverUserId int64,
	receiverUserName varchar(75)
);

alter table BlogsEntry add uuid_ varchar(75);

alter table BookmarksEntry add uuid_ varchar(75);

alter table BookmarksFolder add uuid_ varchar(75);

alter table CalEvent add uuid_ varchar(75);

alter table DLFileEntry add uuid_ varchar(75);

alter table DLFileShortcut add uuid_ varchar(75);

alter table DLFolder add uuid_ varchar(75);


alter table IGFolder add uuid_ varchar(75);

alter table IGImage add uuid_ varchar(75);

alter table JournalArticle add uuid_ varchar(75);
alter table JournalArticle add smallImage smallint;
alter table JournalArticle add smallImageId int64;
alter table JournalArticle add smallImageURL varchar(75);

alter table JournalArticleImage add uuid_ varchar(75);

create table JournalFeed (
	uuid_ varchar(75),
	id_ int64 not null primary key,
	groupId int64,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	feedId varchar(75),
	name varchar(75),
	description varchar(4000),
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
	feedVersion double precision
);

alter table JournalStructure add uuid_ varchar(75);

alter table JournalTemplate add uuid_ varchar(75);
alter table JournalTemplate add cacheable smallint;

commit;


alter table MBCategory add uuid_ varchar(75);

alter table MBMessage add uuid_ varchar(75);

create table MembershipRequest (
	membershipRequestId int64 not null primary key,
	companyId int64,
	userId int64,
	createDate timestamp,
	groupId int64,
	comments varchar(4000),
	replyComments varchar(4000),
	replyDate timestamp,
	replierUserId int64,
	statusId integer
);

alter table PollsChoice add uuid_ varchar(75);

alter table PollsQuestion add uuid_ varchar(75);

alter table TagsAsset add groupId int64;
alter table TagsAsset add priority double precision;
alter table TagsAsset add viewCount integer;

commit;


alter table User_ add uuid_ varchar(75);

create table WebDAVProps (
	webDavPropsId int64 not null primary key,
	companyId int64,
	createDate timestamp,
	modifiedDate timestamp,
	classNameId int64,
	classPK int64,
	props blob
);

alter table WikiNode add uuid_ varchar(75);

alter table WikiPage add uuid_ varchar(75);
