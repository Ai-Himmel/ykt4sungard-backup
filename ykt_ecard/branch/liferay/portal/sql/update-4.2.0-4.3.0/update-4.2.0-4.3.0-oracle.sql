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

alter table Address rename column className to classNameId;

create table ClassName_ (
	classNameId number(30,0) not null primary key,
	value varchar2(200) null
);

drop table ColorScheme;

alter table Company add accountId number(30,0);
alter table Company add webId varchar2(75) null;
alter table Company add virtualHost varchar2(75) null;
alter table Company add logoId number(30,0);

commit;

update Company set webId = companyId;

update Contact_ set parentContactId = '0';
update Contact_ set prefixId = '0' where prefixId is null;
update Contact_ set prefixId = '0' where prefixId = '';
update Contact_ set suffixId = '0' where suffixId is null;
update Contact_ set suffixId = '0' where suffixId = '';

update Country set countryId = '51' where countryId = '51`';

drop table DataTracker;

alter table DLFileEntry add fileEntryId number(30,0);

alter table DLFileRank add fileRankId number(30,0);

alter table DLFileVersion add fileVersionId number(30,0);

alter table EmailAddress rename column className to classNameId;

alter table Group_ add creatorUserId varchar2(75) null;
alter table Group_ rename column className to classNameId;
alter table Group_ add liveGroupId number(30,0);
alter table Group_ add typeSettings varchar2(4000) null;
alter table Group_ add active_ number(1, 0);

commit;

update Group_ set parentGroupId = '0';
update Group_ set liveGroupId = 0;
update Group_ set friendlyURL = '' where classNameId = 'com.liferay.portal.model.User';
update Group_ set active_ = 1;

alter table IGImage add smallImageId number(30,0);
alter table IGImage add largeImageId number(30,0);

alter table Image add height number(30,0);
alter table Image add width number(30,0);
alter table Image add size_ number(30,0);
delete from Image where type_ = 'na';

alter table JournalArticle add id_ varchar2(75) null;
alter table JournalArticle add resourcePrimKey number(30,0);
alter table JournalArticle add indexable number(1, 0);

commit;

update JournalArticle set id_ = articleId;
update JournalArticle set indexable = 1;

create table JournalArticleImage (
	articleImageId number(30,0) not null primary key,
	groupId number(30,0),
	articleId varchar2(75) null,
	version number(30,20),
	elName varchar2(75) null,
	languageId varchar2(75) null,
	tempImage number(1, 0)
);

create table JournalArticleResource (
	resourcePrimKey number(30,0) not null primary key,
	groupId number(30,0),
	articleId varchar2(75) null
);

drop table JournalContentSearch;
create table JournalContentSearch (
	contentSearchId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	privateLayout number(1, 0),
	layoutId number(30,0),
	portletId varchar2(200) null,
	articleId varchar2(75) null
);

alter table JournalStructure add id_ varchar2(75) null;

commit;

update JournalStructure set id_ = structureId;

alter table JournalTemplate add id_ varchar2(75) null;
alter table JournalTemplate add smallImageId number(30,0);

commit;

update JournalTemplate set id_ = templateId;

alter table Layout add plid number(30,0);
alter table Layout add groupId number(30,0);
alter table Layout add privateLayout number(1, 0);
alter table Layout add iconImage number(1, 0);
alter table Layout add iconImageId number(30,0);
alter table Layout add wapThemeId varchar2(75) null;
alter table Layout add wapColorSchemeId varchar2(75) null;
alter table Layout add css varchar2(75) null;
update Layout set parentLayoutId = '0' where parentLayoutId = '-1';

alter table LayoutSet add layoutSetId number(30,0);
alter table LayoutSet add logo number(1, 0);
alter table LayoutSet add logoId number(30,0);
alter table LayoutSet add wapThemeId varchar2(75) null;
alter table LayoutSet add wapColorSchemeId varchar2(75) null;
alter table LayoutSet add css varchar2(75) null;

commit;

update LayoutSet set logo = 0;

create table MBBan (
	banId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	banUserId number(30,0)
);

update MBCategory set categoryId = '0' where categoryId = 'system';
update MBCategory set companyId = '0', userId = '0' where companyId = 'system';

update MBMessage set categoryId = '0' where categoryId = 'system';

update MBThread set categoryId = '0' where categoryId = 'system';

alter table MBDiscussion rename column className to classNameId;

alter table MBMessageFlag add messageFlagId number(30,0);
update MBMessageFlag set flag = '1';

alter table MBStatsUser add statsUserId number(30,0);

drop table MBTopic;

drop table OrgGroupRole;
create table OrgGroupRole (
	organizationId number(30,0) not null,
	groupId number(30,0) not null,
	roleId number(30,0) not null,
	primary key (organizationId, groupId, roleId)
);

create table PasswordPolicy (
	passwordPolicyId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	defaultPolicy number(1, 0),
	name varchar2(75) null,
	description varchar2(4000) null,
	changeable number(1, 0),
	changeRequired number(1, 0),
	minAge number(30,0),
	checkSyntax number(1, 0),
	allowDictionaryWords number(1, 0),
	minLength number(30,0),
	history number(1, 0),
	historyCount number(30,0),
	expireable number(1, 0),
	maxAge number(30,0),
	warningTime number(30,0),
	graceLimit number(30,0),
	lockout number(1, 0),
	maxFailure number(30,0),
	lockoutDuration number(30,0),
	requireUnlock number(1, 0),
	resetFailureCount number(30,0)
);

create table PasswordPolicyRel (
	passwordPolicyRelId number(30,0) not null primary key,
	passwordPolicyId number(30,0),
	classNameId number(30,0),
	classPK number(30,0)
);

alter table Phone rename column className to classNameId;

create table PluginSetting (
	pluginSettingId number(30,0) not null primary key,
	companyId number(30,0),
	pluginId varchar2(75) null,
	pluginType varchar2(75) null,
	roles varchar2(4000) null,
	active_ number(1, 0)
);

alter table PollsChoice add name varchar2(75) null;

commit;

update PollsChoice set name = choiceId;

alter table PollsVote add voteId number(30,0);

alter table Portlet add id_ number(30,0);

alter table PortletPreferences add portletPreferencesId number(30,0);
alter table PortletPreferences add ownerType number(30,0);
alter table PortletPreferences add plid number(30,0);

commit;

update PortletPreferences set plid = 0;

alter table RatingsEntry rename column className to classNameId;

alter table RatingsStats rename column className to classNameId;

alter table Release_ add verified number(1, 0);

alter table Resource_ add codeId number(30,0);

create table ResourceCode (
	codeId number(30,0) not null primary key,
	companyId number(30,0),
	name varchar2(300) null,
	scope number(30,0)
);

alter table Role_ rename column className to classNameId;
alter table Role_ add type_ number(30,0);

commit;

update Role_ SET classNameId = '0';
update Role_ SET classPK = '0';
update Role_ SET type_ = 1;

create table SCFrameworkVersi_SCProductVers (
	productVersionId number(30,0) not null,
	frameworkVersionId number(30,0) not null,
	primary key (productVersionId, frameworkVersionId)
);

create table SCFrameworkVersion (
	frameworkVersionId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	name varchar2(75) null,
	url varchar2(4000) null,
	active_ number(1, 0),
	priority number(30,0)
);

create table SCLicense (
	licenseId number(30,0) not null primary key,
	name varchar2(75) null,
	url varchar2(4000) null,
	openSource number(1, 0),
	active_ number(1, 0),
	recommended number(1, 0)
);

create table SCLicenses_SCProductEntries (
	productEntryId number(30,0) not null,
	licenseId number(30,0) not null,
	primary key (productEntryId, licenseId)
);

create table SCProductEntry (
	productEntryId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	name varchar2(75) null,
	type_ varchar2(75) null,
	tags varchar2(300) null,
	shortDescription varchar2(4000) null,
	longDescription varchar2(4000) null,
	pageURL varchar2(4000) null,
	author varchar2(75) null,
	repoGroupId varchar2(75) null,
	repoArtifactId varchar2(75) null
);

create table SCProductScreenshot (
	productScreenshotId number(30,0) not null primary key,
	companyId number(30,0),
	groupId number(30,0),
	productEntryId number(30,0),
	thumbnailId number(30,0),
	fullImageId number(30,0),
	priority number(30,0)
);

create table SCProductVersion (
	productVersionId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	productEntryId number(30,0),
	version varchar2(75) null,
	changeLog varchar2(4000) null,
	downloadPageURL varchar2(4000) null,
	directDownloadURL varchar2(4000) null,
	repoStoreArtifact number(1, 0)
);

alter table ShoppingCart rename column couponIds to couponCodes;

alter table ShoppingCoupon add code_ varchar2(75) null;

commit;

update ShoppingCoupon set code_ = couponId;

alter table ShoppingItem add smallImageId number(30,0);
alter table ShoppingItem add mediumImageId number(30,0);
alter table ShoppingItem add largeImageId number(30,0);

alter table ShoppingOrder add number_ varchar2(75) null;
alter table ShoppingOrder rename column couponIds to couponCodes;

commit;

update ShoppingOrder set number_ = orderId;

alter table ShoppingOrderItem add orderItemId number(30,0);

alter table Subscription rename column className to classNameId;

create table TagsAsset (
	assetId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	startDate timestamp null,
	endDate timestamp null,
	publishDate timestamp null,
	expirationDate timestamp null,
	mimeType varchar2(75) null,
	title varchar2(300) null,
	description varchar2(4000) null,
	summary varchar2(4000) null,
	url varchar2(4000) null,
	height number(30,0),
	width number(30,0)
);

create table TagsAssets_TagsEntries (
	assetId number(30,0) not null,
	entryId number(30,0) not null,
	primary key (assetId, entryId)
);

create table TagsEntry (
	entryId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	name varchar2(75) null
);

create table TagsProperty (
	propertyId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	entryId number(30,0),
	key_ varchar2(75) null,
	value varchar2(300) null
);

create table TagsSource (
	sourceId number(30,0) not null primary key,
	parentSourceId number(30,0),
	name varchar2(75) null,
	acronym varchar2(75) null
);

alter table User_ add defaultUser number(1, 0);
alter table User_ add passwordModifiedDate timestamp null;
alter table User_ add graceLoginCount number(30,0);
alter table User_ add screenName varchar2(75) null;
alter table User_ add portraitId number(30,0);
alter table User_ add lastFailedLoginDate timestamp null;
alter table User_ add lockout number(1, 0);
alter table User_ add lockoutDate timestamp null;
alter table User_ drop column resolution;

commit;

update User_ set defaultUser = 0;
update User_ set screenName = userId;

update UserGroup SET parentUserGroupId = '0';

create table UserGroupRole (
	userId number(30,0) not null,
	groupId number(30,0) not null,
	roleId number(30,0) not null,
	primary key (userId, groupId, roleId)
);

alter table UserIdMapper add userIdMapperId number(30,0);

drop table UserTracker;
create table UserTracker (
	userTrackerId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	modifiedDate timestamp null,
	sessionId varchar2(200) null,
	remoteAddr varchar2(75) null,
	remoteHost varchar2(75) null,
	userAgent varchar2(200) null
);

drop table UserTrackerPath;
create table UserTrackerPath (
	userTrackerPathId number(30,0) not null primary key,
	userTrackerId number(30,0),
	path_ varchar2(4000) null,
	pathDate timestamp null
);

alter table Website rename column className to classNameId;

alter table WikiPage add pageId number(30,0);
alter table WikiPage add resourcePrimKey number(30,0);

create table WikiPageResource (
	resourcePrimKey number(30,0) not null primary key,
	nodeId number(30,0),
	title varchar2(75) null
);
