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


alter table Address alter column "className" to "classNameId";

create table ClassName_ (
	classNameId int64 not null primary key,
	value varchar(200)
);

drop table ColorScheme;

alter table Company add accountId int64;
alter table Company add webId varchar(75);
alter table Company add virtualHost varchar(75);
alter table Company add logoId int64;

commit;




drop table DataTracker;

alter table DLFileEntry add fileEntryId int64;

alter table DLFileRank add fileRankId int64;

alter table DLFileVersion add fileVersionId int64;

alter table EmailAddress alter column "className" to "classNameId";

alter table Group_ add creatorUserId varchar(75);
alter table Group_ alter column "className" to "classNameId";
alter table Group_ add liveGroupId int64;
alter table Group_ add typeSettings varchar(4000);
alter table Group_ add active_ smallint;

commit;


alter table IGImage add smallImageId int64;
alter table IGImage add largeImageId int64;

alter table Image add height integer;
alter table Image add width integer;
alter table Image add size_ integer;
delete from Image where type_ = 'na';

alter table JournalArticle add id_ varchar(75);
alter table JournalArticle add resourcePrimKey int64;
alter table JournalArticle add indexable smallint;

commit;


create table JournalArticleImage (
	articleImageId int64 not null primary key,
	groupId int64,
	articleId varchar(75),
	version double precision,
	elName varchar(75),
	languageId varchar(75),
	tempImage smallint
);

create table JournalArticleResource (
	resourcePrimKey int64 not null primary key,
	groupId int64,
	articleId varchar(75)
);

drop table JournalContentSearch;
create table JournalContentSearch (
	contentSearchId int64 not null primary key,
	groupId int64,
	companyId int64,
	privateLayout smallint,
	layoutId int64,
	portletId varchar(200),
	articleId varchar(75)
);

alter table JournalStructure add id_ varchar(75);

commit;


alter table JournalTemplate add id_ varchar(75);
alter table JournalTemplate add smallImageId int64;

commit;


alter table Layout add plid int64;
alter table Layout add groupId int64;
alter table Layout add privateLayout smallint;
alter table Layout add iconImage smallint;
alter table Layout add iconImageId int64;
alter table Layout add wapThemeId varchar(75);
alter table Layout add wapColorSchemeId varchar(75);
alter table Layout add css varchar(75);

alter table LayoutSet add layoutSetId int64;
alter table LayoutSet add logo smallint;
alter table LayoutSet add logoId int64;
alter table LayoutSet add wapThemeId varchar(75);
alter table LayoutSet add wapColorSchemeId varchar(75);
alter table LayoutSet add css varchar(75);

commit;


create table MBBan (
	banId int64 not null primary key,
	groupId int64,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	banUserId int64
);




alter table MBDiscussion alter column "className" to "classNameId";

alter table MBMessageFlag add messageFlagId int64;

alter table MBStatsUser add statsUserId int64;

drop table MBTopic;

drop table OrgGroupRole;
create table OrgGroupRole (
	organizationId int64 not null,
	groupId int64 not null,
	roleId int64 not null,
	primary key (organizationId, groupId, roleId)
);

create table PasswordPolicy (
	passwordPolicyId int64 not null primary key,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	defaultPolicy smallint,
	name varchar(75),
	description varchar(4000),
	changeable smallint,
	changeRequired smallint,
	minAge int64,
	checkSyntax smallint,
	allowDictionaryWords smallint,
	minLength integer,
	history smallint,
	historyCount integer,
	expireable smallint,
	maxAge int64,
	warningTime int64,
	graceLimit integer,
	lockout smallint,
	maxFailure integer,
	lockoutDuration int64,
	requireUnlock smallint,
	resetFailureCount int64
);

create table PasswordPolicyRel (
	passwordPolicyRelId int64 not null primary key,
	passwordPolicyId int64,
	classNameId int64,
	classPK int64
);

alter table Phone alter column "className" to "classNameId";

create table PluginSetting (
	pluginSettingId int64 not null primary key,
	companyId int64,
	pluginId varchar(75),
	pluginType varchar(75),
	roles varchar(4000),
	active_ smallint
);

alter table PollsChoice add name varchar(75);

commit;


alter table PollsVote add voteId int64;

alter table Portlet add id_ int64;

alter table PortletPreferences add portletPreferencesId int64;
alter table PortletPreferences add ownerType integer;
alter table PortletPreferences add plid int64;

commit;


alter table RatingsEntry alter column "className" to "classNameId";

alter table RatingsStats alter column "className" to "classNameId";

alter table Release_ add verified smallint;

alter table Resource_ add codeId int64;

create table ResourceCode (
	codeId int64 not null primary key,
	companyId int64,
	name varchar(300),
	scope integer
);

alter table Role_ alter column "className" to "classNameId";
alter table Role_ add type_ integer;

commit;


create table SCFrameworkVersi_SCProductVers (
	productVersionId int64 not null,
	frameworkVersionId int64 not null,
	primary key (productVersionId, frameworkVersionId)
);

create table SCFrameworkVersion (
	frameworkVersionId int64 not null primary key,
	groupId int64,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	name varchar(75),
	url varchar(4000),
	active_ smallint,
	priority integer
);

create table SCLicense (
	licenseId int64 not null primary key,
	name varchar(75),
	url varchar(4000),
	openSource smallint,
	active_ smallint,
	recommended smallint
);

create table SCLicenses_SCProductEntries (
	productEntryId int64 not null,
	licenseId int64 not null,
	primary key (productEntryId, licenseId)
);

create table SCProductEntry (
	productEntryId int64 not null primary key,
	groupId int64,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	name varchar(75),
	type_ varchar(75),
	tags varchar(300),
	shortDescription varchar(4000),
	longDescription varchar(4000),
	pageURL varchar(4000),
	author varchar(75),
	repoGroupId varchar(75),
	repoArtifactId varchar(75)
);

create table SCProductScreenshot (
	productScreenshotId int64 not null primary key,
	companyId int64,
	groupId int64,
	productEntryId int64,
	thumbnailId int64,
	fullImageId int64,
	priority integer
);

create table SCProductVersion (
	productVersionId int64 not null primary key,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	productEntryId int64,
	version varchar(75),
	changeLog varchar(4000),
	downloadPageURL varchar(4000),
	directDownloadURL varchar(4000),
	repoStoreArtifact smallint
);

alter table ShoppingCart alter column "couponIds" to "couponCodes";

alter table ShoppingCoupon add code_ varchar(75);

commit;


alter table ShoppingItem add smallImageId int64;
alter table ShoppingItem add mediumImageId int64;
alter table ShoppingItem add largeImageId int64;

alter table ShoppingOrder add number_ varchar(75);
alter table ShoppingOrder alter column "couponIds" to "couponCodes";

commit;


alter table ShoppingOrderItem add orderItemId int64;

alter table Subscription alter column "className" to "classNameId";

create table TagsAsset (
	assetId int64 not null primary key,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	classNameId int64,
	classPK int64,
	startDate timestamp,
	endDate timestamp,
	publishDate timestamp,
	expirationDate timestamp,
	mimeType varchar(75),
	title varchar(300),
	description varchar(4000),
	summary varchar(4000),
	url varchar(4000),
	height integer,
	width integer
);

create table TagsAssets_TagsEntries (
	assetId int64 not null,
	entryId int64 not null,
	primary key (assetId, entryId)
);

create table TagsEntry (
	entryId int64 not null primary key,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	name varchar(75)
);

create table TagsProperty (
	propertyId int64 not null primary key,
	companyId int64,
	userId int64,
	userName varchar(75),
	createDate timestamp,
	modifiedDate timestamp,
	entryId int64,
	key_ varchar(75),
	value varchar(300)
);

create table TagsSource (
	sourceId int64 not null primary key,
	parentSourceId int64,
	name varchar(75),
	acronym varchar(75)
);

alter table User_ add defaultUser smallint;
alter table User_ add passwordModifiedDate timestamp;
alter table User_ add graceLoginCount integer;
alter table User_ add screenName varchar(75);
alter table User_ add portraitId int64;
alter table User_ add lastFailedLoginDate timestamp;
alter table User_ add lockout smallint;
alter table User_ add lockoutDate timestamp;
alter table User_ drop column resolution;

commit;



create table UserGroupRole (
	userId int64 not null,
	groupId int64 not null,
	roleId int64 not null,
	primary key (userId, groupId, roleId)
);

alter table UserIdMapper add userIdMapperId int64;

drop table UserTracker;
create table UserTracker (
	userTrackerId int64 not null primary key,
	companyId int64,
	userId int64,
	modifiedDate timestamp,
	sessionId varchar(200),
	remoteAddr varchar(75),
	remoteHost varchar(75),
	userAgent varchar(200)
);

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId int64 not null primary key,
	userTrackerId int64,
	path_ varchar(4000),
	pathDate timestamp
);

alter table Website alter column "className" to "classNameId";

alter table WikiPage add pageId int64;
alter table WikiPage add resourcePrimKey int64;

create table WikiPageResource (
	resourcePrimKey int64 not null primary key,
	nodeId int64,
	title varchar(75)
);
