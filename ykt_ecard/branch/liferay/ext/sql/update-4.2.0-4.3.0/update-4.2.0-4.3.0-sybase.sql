delete from Groups_Orgs where groupId not in (select groupId from Group_)
go
delete from Groups_Orgs where organizationId not in (select organizationId from Organization_)
go

delete from Groups_Permissions where groupId not in (select groupId from Group_)
go
delete from Groups_Permissions where permissionId not in (select permissionId from Permission_)
go

delete from Groups_Roles where groupId not in (select groupId from Group_)
go
delete from Groups_Roles where roleId not in (select roleId from Role_)
go

delete from Groups_UserGroups where groupId not in (select groupId from Group_)
go
delete from Groups_UserGroups where userGroupId not in (select userGroupId from UserGroup)
go

delete from Roles_Permissions where roleId not in (select roleId from Role_)
go
delete from Roles_Permissions where permissionId not in (select permissionId from Permission_)
go

delete from Users_Groups where userId not in (select userId from User_)
go
delete from Users_Groups where groupId not in (select groupId from Group_)
go

delete from Users_Orgs where userId not in (select userId from User_)
go
delete from Users_Orgs where organizationId not in (select organizationId from Organization_)
go

delete from Users_Permissions where userId not in (select userId from User_)
go
delete from Users_Permissions where permissionId not in (select permissionId from Permission_)
go

delete from Users_Roles where userId not in (select userId from User_)
go
delete from Users_Roles where roleId not in (select roleId from Role_)
go

delete from Users_UserGroups where userId not in (select userId from User_)
go
delete from Users_UserGroups where userGroupId not in (select userGroupId from UserGroup)
go

go

update Account_ set parentAccountId = '0';
update Account_ set legalName = 'Liferay, Inc.' where legalName = 'Liferay, LLC';

exec sp_rename 'Address.className', 'classNameId', 'column';

create table ClassName_ (
	classNameId decimal(20,0) not null primary key,
	value varchar(200) null
)
go

drop table ColorScheme;

alter table Company add accountId decimal(20,0)
go
alter table Company add webId varchar(75) null;
alter table Company add virtualHost varchar(75) null;
alter table Company add logoId decimal(20,0)
go

go

update Company set webId = companyId;

update Contact_ set parentContactId = '0';
update Contact_ set prefixId = '0' where prefixId is null;
update Contact_ set prefixId = '0' where prefixId = '';
update Contact_ set suffixId = '0' where suffixId is null;
update Contact_ set suffixId = '0' where suffixId = '';

update Country set countryId = '51' where countryId = '51`';

drop table DataTracker;

alter table DLFileEntry add fileEntryId decimal(20,0)
go

alter table DLFileRank add fileRankId decimal(20,0)
go

alter table DLFileVersion add fileVersionId decimal(20,0)
go

exec sp_rename 'EmailAddress.className', 'classNameId', 'column';

alter table Group_ add creatorUserId varchar(75) null;
exec sp_rename 'Group_.className', 'classNameId', 'column';
alter table Group_ add liveGroupId decimal(20,0)
go
alter table Group_ add typeSettings varchar(1000) null;
alter table Group_ add active_ int;

go

update Group_ set parentGroupId = '0';
update Group_ set liveGroupId = 0;
update Group_ set friendlyURL = '' where classNameId = 'com.liferay.portal.model.User';
update Group_ set active_ = 1;

alter table IGImage add smallImageId decimal(20,0)
go
alter table IGImage add largeImageId decimal(20,0)
go

alter table Image add height int;
alter table Image add width int;
alter table Image add size_ int;
delete from Image where type_ = 'na';

alter table JournalArticle add id_ varchar(75) null;
alter table JournalArticle add resourcePrimKey decimal(20,0)
go
alter table JournalArticle add indexable int;

go

update JournalArticle set id_ = articleId;
update JournalArticle set indexable = 1;

create table JournalArticleImage (
	articleImageId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	articleId varchar(75) null,
	version float,
	elName varchar(75) null,
	languageId varchar(75) null,
	tempImage int
)
go

create table JournalArticleResource (
	resourcePrimKey decimal(20,0) not null primary key,
	groupId decimal(20,0),
	articleId varchar(75) null
)
go

drop table JournalContentSearch;
create table JournalContentSearch (
	contentSearchId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	privateLayout int,
	layoutId decimal(20,0),
	portletId varchar(200) null,
	articleId varchar(75) null
)
go

alter table JournalStructure add id_ varchar(75) null;

go

update JournalStructure set id_ = structureId;

alter table JournalTemplate add id_ varchar(75) null;
alter table JournalTemplate add smallImageId decimal(20,0)
go

go

update JournalTemplate set id_ = templateId;

alter table Layout add plid decimal(20,0)
go
alter table Layout add groupId decimal(20,0)
go
alter table Layout add privateLayout int;
alter table Layout add iconImage int;
alter table Layout add iconImageId decimal(20,0)
go
alter table Layout add wapThemeId varchar(75) null;
alter table Layout add wapColorSchemeId varchar(75) null;
alter table Layout add css varchar(75) null;
update Layout set parentLayoutId = '0' where parentLayoutId = '-1';

alter table LayoutSet add layoutSetId decimal(20,0)
go
alter table LayoutSet add logo int;
alter table LayoutSet add logoId decimal(20,0)
go
alter table LayoutSet add wapThemeId varchar(75) null;
alter table LayoutSet add wapColorSchemeId varchar(75) null;
alter table LayoutSet add css varchar(75) null;

go

update LayoutSet set logo = 0;

create table MBBan (
	banId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	banUserId decimal(20,0)
)
go

update MBCategory set categoryId = '0' where categoryId = 'system';
update MBCategory set companyId = '0', userId = '0' where companyId = 'system';

update MBMessage set categoryId = '0' where categoryId = 'system';

update MBThread set categoryId = '0' where categoryId = 'system';

exec sp_rename 'MBDiscussion.className', 'classNameId', 'column';

alter table MBMessageFlag add messageFlagId decimal(20,0)
go
update MBMessageFlag set flag = '1';

alter table MBStatsUser add statsUserId decimal(20,0)
go

drop table MBTopic;

drop table OrgGroupRole;
create table OrgGroupRole (
	organizationId decimal(20,0) not null,
	groupId decimal(20,0) not null,
	roleId decimal(20,0) not null,
	primary key (organizationId, groupId, roleId)
)
go

create table PasswordPolicy (
	passwordPolicyId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	defaultPolicy int,
	name varchar(75) null,
	description varchar(1000) null,
	changeable int,
	changeRequired int,
	minAge decimal(20,0),
	checkSyntax int,
	allowDictionaryWords int,
	minLength int,
	history int,
	historyCount int,
	expireable int,
	maxAge decimal(20,0),
	warningTime decimal(20,0),
	graceLimit int,
	lockout int,
	maxFailure int,
	lockoutDuration decimal(20,0),
	requireUnlock int,
	resetFailureCount decimal(20,0)
)
go

create table PasswordPolicyRel (
	passwordPolicyRelId decimal(20,0) not null primary key,
	passwordPolicyId decimal(20,0),
	classNameId decimal(20,0),
	classPK decimal(20,0)
)
go

exec sp_rename 'Phone.className', 'classNameId', 'column';

create table PluginSetting (
	pluginSettingId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	pluginId varchar(75) null,
	pluginType varchar(75) null,
	roles varchar(1000) null,
	active_ int
)
go

alter table PollsChoice add name varchar(75) null;

go

update PollsChoice set name = choiceId;

alter table PollsVote add voteId decimal(20,0)
go

alter table Portlet add id_ decimal(20,0)
go

alter table PortletPreferences add portletPreferencesId decimal(20,0)
go
alter table PortletPreferences add ownerType int;
alter table PortletPreferences add plid decimal(20,0)
go

go

update PortletPreferences set plid = 0;

exec sp_rename 'RatingsEntry.className', 'classNameId', 'column';

exec sp_rename 'RatingsStats.className', 'classNameId', 'column';

alter table Release_ add verified int;

alter table Resource_ add codeId decimal(20,0)
go

create table ResourceCode (
	codeId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	name varchar(300) null,
	scope int
)
go

exec sp_rename 'Role_.className', 'classNameId', 'column';
alter table Role_ add type_ int;

go

update Role_ SET classNameId = '0';
update Role_ SET classPK = '0';
update Role_ SET type_ = 1;

create table SCFrameworkVersi_SCProductVers (
	productVersionId decimal(20,0) not null,
	frameworkVersionId decimal(20,0) not null,
	primary key (productVersionId, frameworkVersionId)
)
go

create table SCFrameworkVersion (
	frameworkVersionId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	name varchar(75) null,
	url varchar(1000) null,
	active_ int,
	priority int
)
go

create table SCLicense (
	licenseId decimal(20,0) not null primary key,
	name varchar(75) null,
	url varchar(1000) null,
	openSource int,
	active_ int,
	recommended int
)
go

create table SCLicenses_SCProductEntries (
	productEntryId decimal(20,0) not null,
	licenseId decimal(20,0) not null,
	primary key (productEntryId, licenseId)
)
go

create table SCProductEntry (
	productEntryId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	name varchar(75) null,
	type_ varchar(75) null,
	tags varchar(300) null,
	shortDescription varchar(1000) null,
	longDescription varchar(1000) null,
	pageURL varchar(1000) null,
	author varchar(75) null,
	repoGroupId varchar(75) null,
	repoArtifactId varchar(75) null
)
go

create table SCProductScreenshot (
	productScreenshotId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	groupId decimal(20,0),
	productEntryId decimal(20,0),
	thumbnailId decimal(20,0),
	fullImageId decimal(20,0),
	priority int
)
go

create table SCProductVersion (
	productVersionId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	productEntryId decimal(20,0),
	version varchar(75) null,
	changeLog varchar(1000) null,
	downloadPageURL varchar(1000) null,
	directDownloadURL varchar(1000) null,
	repoStoreArtifact int
)
go

exec sp_rename 'ShoppingCart.couponIds', 'couponCodes', 'column';

alter table ShoppingCoupon add code_ varchar(75) null;

go

update ShoppingCoupon set code_ = couponId;

alter table ShoppingItem add smallImageId decimal(20,0)
go
alter table ShoppingItem add mediumImageId decimal(20,0)
go
alter table ShoppingItem add largeImageId decimal(20,0)
go

alter table ShoppingOrder add number_ varchar(75) null;
exec sp_rename 'ShoppingOrder.couponIds', 'couponCodes', 'column';

go

update ShoppingOrder set number_ = orderId;

alter table ShoppingOrderItem add orderItemId decimal(20,0)
go

exec sp_rename 'Subscription.className', 'classNameId', 'column';

create table TagsAsset (
	assetId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	startDate datetime null,
	endDate datetime null,
	publishDate datetime null,
	expirationDate datetime null,
	mimeType varchar(75) null,
	title varchar(300) null,
	description varchar(1000) null,
	summary varchar(1000) null,
	url varchar(1000) null,
	height int,
	width int
)
go

create table TagsAssets_TagsEntries (
	assetId decimal(20,0) not null,
	entryId decimal(20,0) not null,
	primary key (assetId, entryId)
)
go

create table TagsEntry (
	entryId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	name varchar(75) null
)
go

create table TagsProperty (
	propertyId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	entryId decimal(20,0),
	key_ varchar(75) null,
	value varchar(300) null
)
go

create table TagsSource (
	sourceId decimal(20,0) not null primary key,
	parentSourceId decimal(20,0),
	name varchar(75) null,
	acronym varchar(75) null
)
go

alter table User_ add defaultUser int;
alter table User_ add passwordModifiedDate datetime null;
alter table User_ add graceLoginCount int;
alter table User_ add screenName varchar(75) null;
alter table User_ add portraitId decimal(20,0)
go
alter table User_ add lastFailedLoginDate datetime null;
alter table User_ add lockout int;
alter table User_ add lockoutDate datetime null;
alter table User_ drop resolution;

go

update User_ set defaultUser = 0;
update User_ set screenName = userId;

update UserGroup SET parentUserGroupId = '0';

create table UserGroupRole (
	userId decimal(20,0) not null,
	groupId decimal(20,0) not null,
	roleId decimal(20,0) not null,
	primary key (userId, groupId, roleId)
)
go

alter table UserIdMapper add userIdMapperId decimal(20,0)
go

drop table UserTracker;
create table UserTracker (
	userTrackerId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	modifiedDate datetime null,
	sessionId varchar(200) null,
	remoteAddr varchar(75) null,
	remoteHost varchar(75) null,
	userAgent varchar(200) null
)
go

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId decimal(20,0) not null primary key,
	userTrackerId decimal(20,0),
	path_ varchar(1000) null,
	pathDate datetime null
)
go

exec sp_rename 'Website.className', 'classNameId', 'column';

alter table WikiPage add pageId decimal(20,0)
go
alter table WikiPage add resourcePrimKey decimal(20,0)
go

create table WikiPageResource (
	resourcePrimKey decimal(20,0) not null primary key,
	nodeId decimal(20,0),
	title varchar(75) null
)
go
