create table ActivityTracker (
	activityTrackerId int8 not null primary key,
	groupId int8,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	classNameId int8,
	classPK int8,
	activity varchar(75),
	extraData text,
	receiverUserId int8,
	receiverUserName varchar(75)
)
extent size 16 next size 16
lock mode row;

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
alter table JournalArticle add smallImage boolean;
alter table JournalArticle add smallImageId int8;
alter table JournalArticle add smallImageURL varchar(75);

alter table JournalArticleImage add uuid_ varchar(75);

create table JournalFeed (
	uuid_ varchar(75),
	id_ int8 not null primary key,
	groupId int8,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	feedId varchar(75),
	name varchar(75),
	description lvarchar,
	type_ varchar(75),
	structureId varchar(75),
	templateId varchar(75),
	rendererTemplateId varchar(75),
	delta int,
	orderByCol varchar(75),
	orderByType varchar(75),
	targetLayoutFriendlyUrl varchar(75),
	targetPortletId varchar(75),
	contentField varchar(75),
	feedType varchar(75),
	feedVersion float
)
extent size 16 next size 16
lock mode row;

alter table JournalStructure add uuid_ varchar(75);

alter table JournalTemplate add uuid_ varchar(75);
alter table JournalTemplate add cacheable boolean;



update JournalTemplate set cacheable = 'T';

alter table MBCategory add uuid_ varchar(75);

alter table MBMessage add uuid_ varchar(75);

create table MembershipRequest (
	membershipRequestId int8 not null primary key,
	companyId int8,
	userId int8,
	createDate datetime YEAR TO FRACTION,
	groupId int8,
	comments lvarchar,
	replyComments lvarchar,
	replyDate datetime YEAR TO FRACTION,
	replierUserId int8,
	statusId int
)
extent size 16 next size 16
lock mode row;

alter table PollsChoice add uuid_ varchar(75);

alter table PollsQuestion add uuid_ varchar(75);

alter table TagsAsset add groupId int8;
alter table TagsAsset add priority float;
alter table TagsAsset add viewCount int;



update TagsAsset set priority = 0, viewCount = 0;

alter table User_ add uuid_ varchar(75);

create table WebDAVProps (
	webDavPropsId int8 not null primary key,
	companyId int8,
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	classNameId int8,
	classPK int8,
	props text
)
extent size 16 next size 16
lock mode row;

alter table WikiNode add uuid_ varchar(75);

alter table WikiPage add uuid_ varchar(75);
