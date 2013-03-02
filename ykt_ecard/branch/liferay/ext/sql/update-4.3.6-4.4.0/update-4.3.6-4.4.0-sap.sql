create table ActivityTracker (
	activityTrackerId bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	userName varchar(75) null,
	createDate timestamp null,
	classNameId bigint,
	classPK bigint,
	activity varchar(75) null,
	extraData varchar null,
	receiverUserId bigint,
	receiverUserName varchar(75) null
);

alter table BlogsEntry add uuid_ varchar(75) null;

alter table BookmarksEntry add uuid_ varchar(75) null;

alter table BookmarksFolder add uuid_ varchar(75) null;

alter table CalEvent add uuid_ varchar(75) null;

alter table DLFileEntry add uuid_ varchar(75) null;

alter table DLFileShortcut add uuid_ varchar(75) null;

alter table DLFolder add uuid_ varchar(75) null;

update Group_ set type_ = '0' where type_ is null;
update Group_ set type_ = '0' where type_ = '';
update Group_ set type_ = '1' where type_ = 'COMMUNITY_OPEN';
update Group_ set type_ = '2' where type_ = 'COMMUNITY_RESTRICTED';
update Group_ set type_ = '3' where type_ = 'COMMUNITY_CLOSED';
update Group_ set type_ = '3' where type_ = '0';

alter table IGFolder add uuid_ varchar(75) null;

alter table IGImage add uuid_ varchar(75) null;

alter table JournalArticle add uuid_ varchar(75) null;
alter table JournalArticle add smallImage boolean;
alter table JournalArticle add smallImageId bigint;
alter table JournalArticle add smallImageURL varchar(75) null;

alter table JournalArticleImage add uuid_ varchar(75) null;

create table JournalFeed (
	uuid_ varchar(75) null,
	id_ bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	userName varchar(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	feedId varchar(75) null,
	name varchar(75) null,
	description varchar null,
	type_ varchar(75) null,
	structureId varchar(75) null,
	templateId varchar(75) null,
	rendererTemplateId varchar(75) null,
	delta int,
	orderByCol varchar(75) null,
	orderByType varchar(75) null,
	targetLayoutFriendlyUrl varchar(75) null,
	targetPortletId varchar(75) null,
	contentField varchar(75) null,
	feedType varchar(75) null,
	feedVersion float
);

alter table JournalStructure add uuid_ varchar(75) null;

alter table JournalTemplate add uuid_ varchar(75) null;
alter table JournalTemplate add cacheable boolean;

commit;

update JournalTemplate set cacheable = TRUE;

alter table MBCategory add uuid_ varchar(75) null;

alter table MBMessage add uuid_ varchar(75) null;

create table MembershipRequest (
	membershipRequestId bigint not null primary key,
	companyId bigint,
	userId bigint,
	createDate timestamp null,
	groupId bigint,
	comments varchar null,
	replyComments varchar null,
	replyDate timestamp null,
	replierUserId bigint,
	statusId int
);

alter table PollsChoice add uuid_ varchar(75) null;

alter table PollsQuestion add uuid_ varchar(75) null;

alter table TagsAsset add groupId bigint;
alter table TagsAsset add priority float;
alter table TagsAsset add viewCount int;

commit;

update TagsAsset set priority = 0, viewCount = 0;

alter table User_ add uuid_ varchar(75) null;

create table WebDAVProps (
	webDavPropsId bigint not null primary key,
	companyId bigint,
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId bigint,
	classPK bigint,
	props varchar null
);

alter table WikiNode add uuid_ varchar(75) null;

alter table WikiPage add uuid_ varchar(75) null;
