create table ActivityTracker (
	activityTrackerId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	classNameId LONG,
	classPK LONG,
	activity VARCHAR(75) null,
	extraData TEXT null,
	receiverUserId LONG,
	receiverUserName VARCHAR(75) null
);

alter table BlogsEntry add uuid_ VARCHAR(75) null;

alter table BookmarksEntry add uuid_ VARCHAR(75) null;

alter table BookmarksFolder add uuid_ VARCHAR(75) null;

alter table CalEvent add uuid_ VARCHAR(75) null;

alter table DLFileEntry add uuid_ VARCHAR(75) null;

alter table DLFileShortcut add uuid_ VARCHAR(75) null;

alter table DLFolder add uuid_ VARCHAR(75) null;

update Group_ set type_ = '0' where type_ is null;
update Group_ set type_ = '0' where type_ = '';
update Group_ set type_ = '1' where type_ = 'COMMUNITY_OPEN';
update Group_ set type_ = '2' where type_ = 'COMMUNITY_RESTRICTED';
update Group_ set type_ = '3' where type_ = 'COMMUNITY_CLOSED';
update Group_ set type_ = '3' where type_ = '0';

alter table IGFolder add uuid_ VARCHAR(75) null;

alter table IGImage add uuid_ VARCHAR(75) null;

alter table JournalArticle add uuid_ VARCHAR(75) null;
alter table JournalArticle add smallImage BOOLEAN;
alter table JournalArticle add smallImageId LONG;
alter table JournalArticle add smallImageURL VARCHAR(75) null;

alter table JournalArticleImage add uuid_ VARCHAR(75) null;

create table JournalFeed (
	uuid_ VARCHAR(75) null,
	id_ LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	feedId VARCHAR(75) null,
	name VARCHAR(75) null,
	description STRING null,
	type_ VARCHAR(75) null,
	structureId VARCHAR(75) null,
	templateId VARCHAR(75) null,
	rendererTemplateId VARCHAR(75) null,
	delta INTEGER,
	orderByCol VARCHAR(75) null,
	orderByType VARCHAR(75) null,
	targetLayoutFriendlyUrl VARCHAR(75) null,
	targetPortletId VARCHAR(75) null,
	contentField VARCHAR(75) null,
	feedType VARCHAR(75) null,
	feedVersion DOUBLE
);

alter table JournalStructure add uuid_ VARCHAR(75) null;

alter table JournalTemplate add uuid_ VARCHAR(75) null;
alter table JournalTemplate add cacheable BOOLEAN;

COMMIT_TRANSACTION;

update JournalTemplate set cacheable = TRUE;

alter table MBCategory add uuid_ VARCHAR(75) null;

alter table MBMessage add uuid_ VARCHAR(75) null;

create table MembershipRequest (
	membershipRequestId LONG not null primary key,
	companyId LONG,
	userId LONG,
	createDate DATE null,
	groupId LONG,
	comments STRING null,
	replyComments STRING null,
	replyDate DATE null,
	replierUserId LONG,
	statusId INTEGER
);

alter table PollsChoice add uuid_ VARCHAR(75) null;

alter table PollsQuestion add uuid_ VARCHAR(75) null;

alter table TagsAsset add groupId LONG;
alter table TagsAsset add priority DOUBLE;
alter table TagsAsset add viewCount INTEGER;

COMMIT_TRANSACTION;

update TagsAsset set priority = 0, viewCount = 0;

alter table User_ add uuid_ VARCHAR(75) null;

create table WebDAVProps (
	webDavPropsId LONG not null primary key,
	companyId LONG,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	props TEXT null
);

alter table WikiNode add uuid_ VARCHAR(75) null;

alter table WikiPage add uuid_ VARCHAR(75) null;