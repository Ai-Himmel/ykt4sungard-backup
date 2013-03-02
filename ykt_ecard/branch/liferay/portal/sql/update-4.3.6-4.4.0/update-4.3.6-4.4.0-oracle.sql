create table ActivityTracker (
	activityTrackerId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	activity varchar2(75) null,
	extraData clob null,
	receiverUserId number(30,0),
	receiverUserName varchar2(75) null
);

alter table BlogsEntry add uuid_ varchar2(75) null;

alter table BookmarksEntry add uuid_ varchar2(75) null;

alter table BookmarksFolder add uuid_ varchar2(75) null;

alter table CalEvent add uuid_ varchar2(75) null;

alter table DLFileEntry add uuid_ varchar2(75) null;

alter table DLFileShortcut add uuid_ varchar2(75) null;

alter table DLFolder add uuid_ varchar2(75) null;

update Group_ set type_ = '0' where type_ is null;
update Group_ set type_ = '0' where type_ = '';
update Group_ set type_ = '1' where type_ = 'COMMUNITY_OPEN';
update Group_ set type_ = '2' where type_ = 'COMMUNITY_RESTRICTED';
update Group_ set type_ = '3' where type_ = 'COMMUNITY_CLOSED';
update Group_ set type_ = '3' where type_ = '0';

alter table IGFolder add uuid_ varchar2(75) null;

alter table IGImage add uuid_ varchar2(75) null;

alter table JournalArticle add uuid_ varchar2(75) null;
alter table JournalArticle add smallImage number(1, 0);
alter table JournalArticle add smallImageId number(30,0);
alter table JournalArticle add smallImageURL varchar2(75) null;

alter table JournalArticleImage add uuid_ varchar2(75) null;

create table JournalFeed (
	uuid_ varchar2(75) null,
	id_ number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	feedId varchar2(75) null,
	name varchar2(75) null,
	description varchar2(4000) null,
	type_ varchar2(75) null,
	structureId varchar2(75) null,
	templateId varchar2(75) null,
	rendererTemplateId varchar2(75) null,
	delta number(30,0),
	orderByCol varchar2(75) null,
	orderByType varchar2(75) null,
	targetLayoutFriendlyUrl varchar2(75) null,
	targetPortletId varchar2(75) null,
	contentField varchar2(75) null,
	feedType varchar2(75) null,
	feedVersion number(30,20)
);

alter table JournalStructure add uuid_ varchar2(75) null;

alter table JournalTemplate add uuid_ varchar2(75) null;
alter table JournalTemplate add cacheable number(1, 0);

commit;

update JournalTemplate set cacheable = 1;

alter table MBCategory add uuid_ varchar2(75) null;

alter table MBMessage add uuid_ varchar2(75) null;

create table MembershipRequest (
	membershipRequestId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	createDate timestamp null,
	groupId number(30,0),
	comments varchar2(4000) null,
	replyComments varchar2(4000) null,
	replyDate timestamp null,
	replierUserId number(30,0),
	statusId number(30,0)
);

alter table PollsChoice add uuid_ varchar2(75) null;

alter table PollsQuestion add uuid_ varchar2(75) null;

alter table TagsAsset add groupId number(30,0);
alter table TagsAsset add priority number(30,20);
alter table TagsAsset add viewCount number(30,0);

commit;

update TagsAsset set priority = 0, viewCount = 0;

alter table User_ add uuid_ varchar2(75) null;

create table WebDAVProps (
	webDavPropsId number(30,0) not null primary key,
	companyId number(30,0),
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	props clob null
);

alter table WikiNode add uuid_ varchar2(75) null;

alter table WikiPage add uuid_ varchar2(75) null;
