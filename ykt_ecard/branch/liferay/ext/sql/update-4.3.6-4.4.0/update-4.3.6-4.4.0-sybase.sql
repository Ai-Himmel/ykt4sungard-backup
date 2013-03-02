create table ActivityTracker (
	activityTrackerId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	activity varchar(75) null,
	extraData text null,
	receiverUserId decimal(20,0),
	receiverUserName varchar(75) null
)
go

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
alter table JournalArticle add smallImage int;
alter table JournalArticle add smallImageId decimal(20,0)
go
alter table JournalArticle add smallImageURL varchar(75) null;

alter table JournalArticleImage add uuid_ varchar(75) null;

create table JournalFeed (
	uuid_ varchar(75) null,
	id_ decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	feedId varchar(75) null,
	name varchar(75) null,
	description varchar(1000) null,
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
)
go

alter table JournalStructure add uuid_ varchar(75) null;

alter table JournalTemplate add uuid_ varchar(75) null;
alter table JournalTemplate add cacheable int;

go

update JournalTemplate set cacheable = 1;

alter table MBCategory add uuid_ varchar(75) null;

alter table MBMessage add uuid_ varchar(75) null;

create table MembershipRequest (
	membershipRequestId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	createDate datetime null,
	groupId decimal(20,0),
	comments varchar(1000) null,
	replyComments varchar(1000) null,
	replyDate datetime null,
	replierUserId decimal(20,0),
	statusId int
)
go

alter table PollsChoice add uuid_ varchar(75) null;

alter table PollsQuestion add uuid_ varchar(75) null;

alter table TagsAsset add groupId decimal(20,0)
go
alter table TagsAsset add priority float;
alter table TagsAsset add viewCount int;

go

update TagsAsset set priority = 0, viewCount = 0;

alter table User_ add uuid_ varchar(75) null;

create table WebDAVProps (
	webDavPropsId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	createDate datetime null,
	modifiedDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	props text null
)
go

alter table WikiNode add uuid_ varchar(75) null;

alter table WikiPage add uuid_ varchar(75) null;
