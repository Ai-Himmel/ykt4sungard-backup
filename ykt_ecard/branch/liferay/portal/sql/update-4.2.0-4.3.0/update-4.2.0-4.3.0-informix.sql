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



update Account_ set parentAccountId = '0';
update Account_ set legalName = 'Liferay, Inc.' where legalName = 'Liferay, LLC';

rename column Address.className TO classNameId;

create table ClassName_ (
	classNameId int8 not null primary key,
	value varchar(200)
)
extent size 16 next size 16
lock mode row;

drop table ColorScheme;

alter table Company add accountId int8;
alter table Company add webId varchar(75);
alter table Company add virtualHost varchar(75);
alter table Company add logoId int8;



update Company set webId = companyId;

update Contact_ set parentContactId = '0';
update Contact_ set prefixId = '0' where prefixId is;
update Contact_ set prefixId = '0' where prefixId = '';
update Contact_ set suffixId = '0' where suffixId is;
update Contact_ set suffixId = '0' where suffixId = '';

update Country set countryId = '51' where countryId = '51`';

drop table DataTracker;

alter table DLFileEntry add fileEntryId int8;

alter table DLFileRank add fileRankId int8;

alter table DLFileVersion add fileVersionId int8;

rename column EmailAddress.className TO classNameId;

alter table Group_ add creatorUserId varchar(75);
rename column Group_.className TO classNameId;
alter table Group_ add liveGroupId int8;
alter table Group_ add typeSettings lvarchar;
alter table Group_ add active_ boolean;



update Group_ set parentGroupId = '0';
update Group_ set liveGroupId = 0;
update Group_ set friendlyURL = '' where classNameId = 'com.liferay.portal.model.User';
update Group_ set active_ = 'T';

alter table IGImage add smallImageId int8;
alter table IGImage add largeImageId int8;

alter table Image add height int;
alter table Image add width int;
alter table Image add size_ int;
delete from Image where type_ = 'na';

alter table JournalArticle add id_ varchar(75);
alter table JournalArticle add resourcePrimKey int8;
alter table JournalArticle add indexable boolean;



update JournalArticle set id_ = articleId;
update JournalArticle set indexable = 'T';

create table JournalArticleImage (
	articleImageId int8 not null primary key,
	groupId int8,
	articleId varchar(75),
	version float,
	elName varchar(75),
	languageId varchar(75),
	tempImage boolean
)
extent size 16 next size 16
lock mode row;

create table JournalArticleResource (
	resourcePrimKey int8 not null primary key,
	groupId int8,
	articleId varchar(75)
)
extent size 16 next size 16
lock mode row;

drop table JournalContentSearch;
create table JournalContentSearch (
	contentSearchId int8 not null primary key,
	groupId int8,
	companyId int8,
	privateLayout boolean,
	layoutId int8,
	portletId varchar(200),
	articleId varchar(75)
)
extent size 16 next size 16
lock mode row;

alter table JournalStructure add id_ varchar(75);



update JournalStructure set id_ = structureId;

alter table JournalTemplate add id_ varchar(75);
alter table JournalTemplate add smallImageId int8;



update JournalTemplate set id_ = templateId;

alter table Layout add plid int8;
alter table Layout add groupId int8;
alter table Layout add privateLayout boolean;
alter table Layout add iconImage boolean;
alter table Layout add iconImageId int8;
alter table Layout add wapThemeId varchar(75);
alter table Layout add wapColorSchemeId varchar(75);
alter table Layout add css varchar(75);
update Layout set parentLayoutId = '0' where parentLayoutId = '-1';

alter table LayoutSet add layoutSetId int8;
alter table LayoutSet add logo boolean;
alter table LayoutSet add logoId int8;
alter table LayoutSet add wapThemeId varchar(75);
alter table LayoutSet add wapColorSchemeId varchar(75);
alter table LayoutSet add css varchar(75);



update LayoutSet set logo = 'F';

create table MBBan (
	banId int8 not null primary key,
	groupId int8,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	banUserId int8
)
extent size 16 next size 16
lock mode row;

update MBCategory set categoryId = '0' where categoryId = 'system';
update MBCategory set companyId = '0', userId = '0' where companyId = 'system';

update MBMessage set categoryId = '0' where categoryId = 'system';

update MBThread set categoryId = '0' where categoryId = 'system';

rename column MBDiscussion.className TO classNameId;

alter table MBMessageFlag add messageFlagId int8;
update MBMessageFlag set flag = '1';

alter table MBStatsUser add statsUserId int8;

drop table MBTopic;

drop table OrgGroupRole;
create table OrgGroupRole (
	organizationId int8 not null,
	groupId int8 not null,
	roleId int8 not null,
	primary key (organizationId, groupId, roleId)
)
extent size 16 next size 16
lock mode row;

create table PasswordPolicy (
	passwordPolicyId int8 not null primary key,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	defaultPolicy boolean,
	name varchar(75),
	description lvarchar,
	changeable boolean,
	changeRequired boolean,
	minAge int8,
	checkSyntax boolean,
	allowDictionaryWords boolean,
	minLength int,
	history boolean,
	historyCount int,
	expireable boolean,
	maxAge int8,
	warningTime int8,
	graceLimit int,
	lockout boolean,
	maxFailure int,
	lockoutDuration int8,
	requireUnlock boolean,
	resetFailureCount int8
)
extent size 16 next size 16
lock mode row;

create table PasswordPolicyRel (
	passwordPolicyRelId int8 not null primary key,
	passwordPolicyId int8,
	classNameId int8,
	classPK int8
)
extent size 16 next size 16
lock mode row;

rename column Phone.className TO classNameId;

create table PluginSetting (
	pluginSettingId int8 not null primary key,
	companyId int8,
	pluginId varchar(75),
	pluginType varchar(75),
	roles lvarchar,
	active_ boolean
)
extent size 16 next size 16
lock mode row;

alter table PollsChoice add name varchar(75);



update PollsChoice set name = choiceId;

alter table PollsVote add voteId int8;

alter table Portlet add id_ int8;

alter table PortletPreferences add portletPreferencesId int8;
alter table PortletPreferences add ownerType int;
alter table PortletPreferences add plid int8;



update PortletPreferences set plid = 0;

rename column RatingsEntry.className TO classNameId;

rename column RatingsStats.className TO classNameId;

alter table Release_ add verified boolean;

alter table Resource_ add codeId int8;

create table ResourceCode (
	codeId int8 not null primary key,
	companyId int8,
	name lvarchar(300),
	scope int
)
extent size 16 next size 16
lock mode row;

rename column Role_.className TO classNameId;
alter table Role_ add type_ int;



update Role_ SET classNameId = '0';
update Role_ SET classPK = '0';
update Role_ SET type_ = 1;

create table SCFrameworkVersi_SCProductVers (
	productVersionId int8 not null,
	frameworkVersionId int8 not null,
	primary key (productVersionId, frameworkVersionId)
)
extent size 16 next size 16
lock mode row;

create table SCFrameworkVersion (
	frameworkVersionId int8 not null primary key,
	groupId int8,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	name varchar(75),
	url lvarchar,
	active_ boolean,
	priority int
)
extent size 16 next size 16
lock mode row;

create table SCLicense (
	licenseId int8 not null primary key,
	name varchar(75),
	url lvarchar,
	openSource boolean,
	active_ boolean,
	recommended boolean
)
extent size 16 next size 16
lock mode row;

create table SCLicenses_SCProductEntries (
	productEntryId int8 not null,
	licenseId int8 not null,
	primary key (productEntryId, licenseId)
)
extent size 16 next size 16
lock mode row;

create table SCProductEntry (
	productEntryId int8 not null primary key,
	groupId int8,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	name varchar(75),
	type_ varchar(75),
	tags lvarchar(300),
	shortDescription lvarchar,
	longDescription lvarchar,
	pageURL lvarchar,
	author varchar(75),
	repoGroupId varchar(75),
	repoArtifactId varchar(75)
)
extent size 16 next size 16
lock mode row;

create table SCProductScreenshot (
	productScreenshotId int8 not null primary key,
	companyId int8,
	groupId int8,
	productEntryId int8,
	thumbnailId int8,
	fullImageId int8,
	priority int
)
extent size 16 next size 16
lock mode row;

create table SCProductVersion (
	productVersionId int8 not null primary key,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	productEntryId int8,
	version varchar(75),
	changeLog lvarchar,
	downloadPageURL lvarchar,
	directDownloadURL lvarchar,
	repoStoreArtifact boolean
)
extent size 16 next size 16
lock mode row;

rename column ShoppingCart.couponIds TO couponCodes;

alter table ShoppingCoupon add code_ varchar(75);



update ShoppingCoupon set code_ = couponId;

alter table ShoppingItem add smallImageId int8;
alter table ShoppingItem add mediumImageId int8;
alter table ShoppingItem add largeImageId int8;

alter table ShoppingOrder add number_ varchar(75);
rename column ShoppingOrder.couponIds TO couponCodes;



update ShoppingOrder set number_ = orderId;

alter table ShoppingOrderItem add orderItemId int8;

rename column Subscription.className TO classNameId;

create table TagsAsset (
	assetId int8 not null primary key,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	classNameId int8,
	classPK int8,
	startDate datetime YEAR TO FRACTION,
	endDate datetime YEAR TO FRACTION,
	publishDate datetime YEAR TO FRACTION,
	expirationDate datetime YEAR TO FRACTION,
	mimeType varchar(75),
	title lvarchar(300),
	description lvarchar,
	summary lvarchar,
	url lvarchar,
	height int,
	width int
)
extent size 16 next size 16
lock mode row;

create table TagsAssets_TagsEntries (
	assetId int8 not null,
	entryId int8 not null,
	primary key (assetId, entryId)
)
extent size 16 next size 16
lock mode row;

create table TagsEntry (
	entryId int8 not null primary key,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	name varchar(75)
)
extent size 16 next size 16
lock mode row;

create table TagsProperty (
	propertyId int8 not null primary key,
	companyId int8,
	userId int8,
	userName varchar(75),
	createDate datetime YEAR TO FRACTION,
	modifiedDate datetime YEAR TO FRACTION,
	entryId int8,
	key_ varchar(75),
	value lvarchar(300)
)
extent size 16 next size 16
lock mode row;

create table TagsSource (
	sourceId int8 not null primary key,
	parentSourceId int8,
	name varchar(75),
	acronym varchar(75)
)
extent size 16 next size 16
lock mode row;

alter table User_ add defaultUser boolean;
alter table User_ add passwordModifiedDate datetime YEAR TO FRACTION;
alter table User_ add graceLoginCount int;
alter table User_ add screenName varchar(75);
alter table User_ add portraitId int8;
alter table User_ add lastFailedLoginDate datetime YEAR TO FRACTION;
alter table User_ add lockout boolean;
alter table User_ add lockoutDate datetime YEAR TO FRACTION;
alter table User_ drop column resolution;



update User_ set defaultUser = 'F';
update User_ set screenName = userId;

update UserGroup SET parentUserGroupId = '0';

create table UserGroupRole (
	userId int8 not null,
	groupId int8 not null,
	roleId int8 not null,
	primary key (userId, groupId, roleId)
)
extent size 16 next size 16
lock mode row;

alter table UserIdMapper add userIdMapperId int8;

drop table UserTracker;
create table UserTracker (
	userTrackerId int8 not null primary key,
	companyId int8,
	userId int8,
	modifiedDate datetime YEAR TO FRACTION,
	sessionId varchar(200),
	remoteAddr varchar(75),
	remoteHost varchar(75),
	userAgent varchar(200)
)
extent size 16 next size 16
lock mode row;

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId int8 not null primary key,
	userTrackerId int8,
	path_ lvarchar,
	pathDate datetime YEAR TO FRACTION
)
extent size 16 next size 16
lock mode row;

rename column Website.className TO classNameId;

alter table WikiPage add pageId int8;
alter table WikiPage add resourcePrimKey int8;

create table WikiPageResource (
	resourcePrimKey int8 not null primary key,
	nodeId int8,
	title varchar(75)
)
extent size 16 next size 16
lock mode row;
