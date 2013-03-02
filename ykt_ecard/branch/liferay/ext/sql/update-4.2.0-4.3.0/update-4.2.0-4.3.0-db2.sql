delete from Groups_Orgs where groupId not in (select groupId from Group_);
delete from Groups_Orgs where organizationId not in (select organizationId from Organization_);

delete from Groups_Permissions where groupId not in (select groupId from Group_);
delete from Groups_Permissions where permissionId not in (select permissionId from Permission_);

delete from Groups_Roles where groupId not in (select groupId from Group_);
delete from Groups_Roles where roleId not in (select roleId from Role_);

delete from Groups_UserGroups where groupId not in (select groupId from Group_);
delete from Groups_UserGroups where userGroupId not in (select userGroupId from UserGroup);

delete from Roles_Permissions where roleId not in (select roleId from Role_);
delete from Roles_Permissions where permissionId not in (select permissionId from Permission_);

delete from Users_Groups where userId not in (select userId from User_);
delete from Users_Groups where groupId not in (select groupId from Group_);

delete from Users_Orgs where userId not in (select userId from User_);
delete from Users_Orgs where organizationId not in (select organizationId from Organization_);

delete from Users_Permissions where userId not in (select userId from User_);
delete from Users_Permissions where permissionId not in (select permissionId from Permission_);

delete from Users_Roles where userId not in (select userId from User_);
delete from Users_Roles where roleId not in (select roleId from Role_);

delete from Users_UserGroups where userId not in (select userId from User_);
delete from Users_UserGroups where userGroupId not in (select userGroupId from UserGroup);

commit;

update Account_ set parentAccountId = '0';
update Account_ set legalName = 'Liferay, Inc.' where legalName = 'Liferay, LLC';

alter table Address add column classNameId varchar(75);
update Address set classNameId = className;
alter table Address drop column className

create table ClassName_ (
	classNameId bigint not null primary key,
	value varchar(200)
);

drop table ColorScheme;

alter table Company add accountId bigint;
alter table Company add webId varchar(75);
alter table Company add virtualHost varchar(75);
alter table Company add logoId bigint;

commit;

update Company set webId = companyId;

update Contact_ set parentContactId = '0';
update Contact_ set prefixId = '0' where prefixId is;
update Contact_ set prefixId = '0' where prefixId = '';
update Contact_ set suffixId = '0' where suffixId is;
update Contact_ set suffixId = '0' where suffixId = '';

update Country set countryId = '51' where countryId = '51`';

drop table DataTracker;

alter table DLFileEntry add fileEntryId bigint;

alter table DLFileRank add fileRankId bigint;

alter table DLFileVersion add fileVersionId bigint;

alter table EmailAddress add column classNameId varchar(75);
update EmailAddress set classNameId = className;
alter table EmailAddress drop column className

alter table Group_ add creatorUserId varchar(75);
alter table Group_ add column classNameId varchar(75);
update Group_ set classNameId = className;
alter table Group_ drop column className
alter table Group_ add liveGroupId bigint;
alter table Group_ add typeSettings varchar(500);
alter table Group_ add active_ smallint;

commit;

update Group_ set parentGroupId = '0';
update Group_ set liveGroupId = 0;
update Group_ set friendlyURL = '' where classNameId = 'com.liferay.portal.model.User';
update Group_ set active_ = 1;

alter table IGImage add smallImageId bigint;
alter table IGImage add largeImageId bigint;

alter table Image add height integer;
alter table Image add width integer;
alter table Image add size_ integer;
delete from Image where type_ = 'na';

alter table JournalArticle add id_ varchar(75);
alter table JournalArticle add resourcePrimKey bigint;
alter table JournalArticle add indexable smallint;

commit;

update JournalArticle set id_ = articleId;
update JournalArticle set indexable = 1;

create table JournalArticleImage (
	articleImageId bigint not null primary key,
	groupId bigint,
	articleId varchar(75),
	version double,
	elName varchar(75),
	languageId varchar(75),
	tempImage smallint
);

create table JournalArticleResource (
	resourcePrimKey bigint not null primary key,
	groupId bigint,
	articleId varchar(75)
);

drop table JournalContentSearch;
create table JournalContentSearch (
	contentSearchId bigint not null primary key,
	groupId bigint,
	companyId bigint,
	privateLayout smallint,
	layoutId bigint,
	portletId varchar(200),
	articleId varchar(75)
);

alter table JournalStructure add id_ varchar(75);

commit;

update JournalStructure set id_ = structureId;

alter table JournalTemplate add id_ varchar(75);
alter table JournalTemplate add smallImageId bigint;

commit;

update JournalTemplate set id_ = templateId;

alter table Layout add plid bigint;
alter table Layout add groupId bigint;
alter table Layout add privateLayout smallint;
alter table Layout add iconImage smallint;
alter table Layout add iconImageId bigint;
alter table Layout add wapThemeId varchar(75);
alter table Layout add wapColorSchemeId varchar(75);
alter table Layout add css varchar(75);
update Layout set parentLayoutId = '0' where parentLayoutId = '-1';

alter table LayoutSet add layoutSetId bigint;
alter table LayoutSet add logo smallint;
alter table LayoutSet add logoId bigint;
alter table LayoutSet add wapThemeId varchar(75);
alter table LayoutSet add wapColorSchemeId varchar(75);
alter table LayoutSet add css varchar(75);

commit;

update LayoutSet set logo = 0;

create table MBBan (
	banId bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	banUserId bigint
);

update MBCategory set categoryId = '0' where categoryId = 'system';
update MBCategory set companyId = '0', userId = '0' where companyId = 'system';

update MBMessage set categoryId = '0' where categoryId = 'system';

update MBThread set categoryId = '0' where categoryId = 'system';

alter table MBDiscussion add column classNameId varchar(75);
update MBDiscussion set classNameId = className;
alter table MBDiscussion drop column className

alter table MBMessageFlag add messageFlagId bigint;
update MBMessageFlag set flag = '1';

alter table MBStatsUser add statsUserId bigint;

drop table MBTopic;

drop table OrgGroupRole;
create table OrgGroupRole (
	organizationId bigint not null,
	groupId bigint not null,
	roleId bigint not null,
	primary key (organizationId, groupId, roleId)
);

create table PasswordPolicy (
	passwordPolicyId bigint not null primary key,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	defaultPolicy smallint,
	name varchar(75),
	description varchar(500),
	changeable smallint,
	changeRequired smallint,
	minAge bigint,
	checkSyntax smallint,
	allowDictionaryWords smallint,
	minLength integer,
	history smallint,
	historyCount integer,
	expireable smallint,
	maxAge bigint,
	warningTime bigint,
	graceLimit integer,
	lockout smallint,
	maxFailure integer,
	lockoutDuration bigint,
	requireUnlock smallint,
	resetFailureCount bigint
);

create table PasswordPolicyRel (
	passwordPolicyRelId bigint not null primary key,
	passwordPolicyId bigint,
	classNameId bigint,
	classPK bigint
);

alter table Phone add column classNameId varchar(75);
update Phone set classNameId = className;
alter table Phone drop column className

create table PluginSetting (
	pluginSettingId bigint not null primary key,
	companyId bigint,
	pluginId varchar(75),
	pluginType varchar(75),
	roles varchar(500),
	active_ smallint
);

alter table PollsChoice add name varchar(75);

commit;

update PollsChoice set name = choiceId;

alter table PollsVote add voteId bigint;

alter table Portlet add id_ bigint;

alter table PortletPreferences add portletPreferencesId bigint;
alter table PortletPreferences add ownerType integer;
alter table PortletPreferences add plid bigint;

commit;

update PortletPreferences set plid = 0;

alter table RatingsEntry add column classNameId varchar(75);
update RatingsEntry set classNameId = className;
alter table RatingsEntry drop column className

alter table RatingsStats add column classNameId varchar(75);
update RatingsStats set classNameId = className;
alter table RatingsStats drop column className

alter table Release_ add verified smallint;

alter table Resource_ add codeId bigint;

create table ResourceCode (
	codeId bigint not null primary key,
	companyId bigint,
	name varchar(300),
	scope integer
);

alter table Role_ add column classNameId varchar(75);
update Role_ set classNameId = className;
alter table Role_ drop column className
alter table Role_ add type_ integer;

commit;

update Role_ SET classNameId = '0';
update Role_ SET classPK = '0';
update Role_ SET type_ = 1;

create table SCFrameworkVersi_SCProductVers (
	productVersionId bigint not null,
	frameworkVersionId bigint not null,
	primary key (productVersionId, frameworkVersionId)
);

create table SCFrameworkVersion (
	frameworkVersionId bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	name varchar(75),
	url varchar(500),
	active_ smallint,
	priority integer
);

create table SCLicense (
	licenseId bigint not null primary key,
	name varchar(75),
	url varchar(500),
	openSource smallint,
	active_ smallint,
	recommended smallint
);

create table SCLicenses_SCProductEntries (
	productEntryId bigint not null,
	licenseId bigint not null,
	primary key (productEntryId, licenseId)
);

create table SCProductEntry (
	productEntryId bigint not null primary key,
	groupId bigint,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	name varchar(75),
	type_ varchar(75),
	tags varchar(300),
	shortDescription varchar(500),
	longDescription varchar(500),
	pageURL varchar(500),
	author varchar(75),
	repoGroupId varchar(75),
	repoArtifactId varchar(75)
);

create table SCProductScreenshot (
	productScreenshotId bigint not null primary key,
	companyId bigint,
	groupId bigint,
	productEntryId bigint,
	thumbnailId bigint,
	fullImageId bigint,
	priority integer
);

create table SCProductVersion (
	productVersionId bigint not null primary key,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	productEntryId bigint,
	version varchar(75),
	changeLog varchar(500),
	downloadPageURL varchar(500),
	directDownloadURL varchar(500),
	repoStoreArtifact smallint
);

alter table ShoppingCart add column couponCodes varchar(75);
update ShoppingCart set couponCodes = couponIds;
alter table ShoppingCart drop column couponIds

alter table ShoppingCoupon add code_ varchar(75);

commit;

update ShoppingCoupon set code_ = couponId;

alter table ShoppingItem add smallImageId bigint;
alter table ShoppingItem add mediumImageId bigint;
alter table ShoppingItem add largeImageId bigint;

alter table ShoppingOrder add number_ varchar(75);
alter table ShoppingOrder add column couponCodes varchar(75);
update ShoppingOrder set couponCodes = couponIds;
alter table ShoppingOrder drop column couponIds

commit;

update ShoppingOrder set number_ = orderId;

alter table ShoppingOrderItem add orderItemId bigint;

alter table Subscription add column classNameId varchar(75);
update Subscription set classNameId = className;
alter table Subscription drop column className

create table TagsAsset (
	assetId bigint not null primary key,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	classNameId bigint,
	classPK bigint,
	startDate timestamp,
	endDate timestamp,
	publishDate timestamp,
	expirationDate timestamp,
	mimeType varchar(75),
	title varchar(300),
	description varchar(500),
	summary varchar(500),
	url varchar(500),
	height integer,
	width integer
);

create table TagsAssets_TagsEntries (
	assetId bigint not null,
	entryId bigint not null,
	primary key (assetId, entryId)
);

create table TagsEntry (
	entryId bigint not null primary key,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	name varchar(75)
);

create table TagsProperty (
	propertyId bigint not null primary key,
	companyId bigint,
	userId bigint,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	entryId bigint,
	key_ varchar(75),
	value varchar(300)
);

create table TagsSource (
	sourceId bigint not null primary key,
	parentSourceId bigint,
	name varchar(75),
	acronym varchar(75)
);

alter table User_ add defaultUser smallint;
alter table User_ add passwordModifiedDate timestamp;
alter table User_ add graceLoginCount integer;
alter table User_ add screenName varchar(75);
alter table User_ add portraitId bigint;
alter table User_ add lastFailedLoginDate timestamp;
alter table User_ add lockout smallint;
alter table User_ add lockoutDate timestamp;
alter table User_ drop column resolution;

commit;

update User_ set defaultUser = 0;
update User_ set screenName = userId;

update UserGroup SET parentUserGroupId = '0';

create table UserGroupRole (
	userId bigint not null,
	groupId bigint not null,
	roleId bigint not null,
	primary key (userId, groupId, roleId)
);

alter table UserIdMapper add userIdMapperId bigint;

drop table UserTracker;
create table UserTracker (
	userTrackerId bigint not null primary key,
	companyId bigint,
	userId bigint,
	modifiedDate timestamp,
	sessionId varchar(200),
	remoteAddr varchar(75),
	remoteHost varchar(75),
	userAgent varchar(200)
);

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId bigint not null primary key,
	userTrackerId bigint,
	path_ varchar(500),
	pathDate timestamp
);

alter table Website add column classNameId varchar(75);
update Website set classNameId = className;
alter table Website drop column className

alter table WikiPage add pageId bigint;
alter table WikiPage add resourcePrimKey bigint;

create table WikiPageResource (
	resourcePrimKey bigint not null primary key,
	nodeId bigint,
	title varchar(75)
);
