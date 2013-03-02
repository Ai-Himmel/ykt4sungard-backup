create table Account_ (
	accountId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	parentAccountId number(30,0),
	name varchar2(75) null,
	legalName varchar2(75) null,
	legalId varchar2(75) null,
	legalType varchar2(75) null,
	sicCode varchar2(75) null,
	tickerSymbol varchar2(75) null,
	industry varchar2(75) null,
	type_ varchar2(75) null,
	size_ varchar2(75) null
);

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

create table Address (
	addressId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	street1 varchar2(75) null,
	street2 varchar2(75) null,
	street3 varchar2(75) null,
	city varchar2(75) null,
	zip varchar2(75) null,
	regionId number(30,0),
	countryId number(30,0),
	typeId number(30,0),
	mailing number(1, 0),
	primary_ number(1, 0)
);

create table BlogsCategory (
	categoryId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	parentCategoryId number(30,0),
	name varchar2(75) null,
	description varchar2(4000) null
);

create table BlogsEntry (
	uuid_ varchar2(75) null,
	entryId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	title varchar2(150) null,
	urlTitle varchar2(150) null,
	content clob null,
	displayDate timestamp null
);

create table BlogsStatsUser (
	statsUserId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	entryCount number(30,0),
	lastPostDate timestamp null,
	ratingsTotalEntries number(30,0),
	ratingsTotalScore number(30,20),
	ratingsAverageScore number(30,20)
);

create table BookmarksEntry (
	uuid_ varchar2(75) null,
	entryId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	createDate timestamp null,
	modifiedDate timestamp null,
	folderId number(30,0),
	name varchar2(300) null,
	url varchar2(4000) null,
	comments varchar2(4000) null,
	visits number(30,0),
	priority number(30,0)
);

create table BookmarksFolder (
	uuid_ varchar2(75) null,
	folderId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	createDate timestamp null,
	modifiedDate timestamp null,
	parentFolderId number(30,0),
	name varchar2(75) null,
	description varchar2(4000) null
);

create table CalEvent (
	uuid_ varchar2(75) null,
	eventId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	title varchar2(75) null,
	description varchar2(4000) null,
	startDate timestamp null,
	endDate timestamp null,
	durationHour number(30,0),
	durationMinute number(30,0),
	allDay number(1, 0),
	timeZoneSensitive number(1, 0),
	type_ varchar2(75) null,
	repeating number(1, 0),
	recurrence clob null,
	remindBy varchar2(75) null,
	firstReminder number(30,0),
	secondReminder number(30,0)
);

create table ClassName_ (
	classNameId number(30,0) not null primary key,
	value varchar2(200) null
);

create table Company (
	companyId number(30,0) not null primary key,
	accountId number(30,0),
	webId varchar2(75) null,
	key_ clob null,
	virtualHost varchar2(75) null,
	mx varchar2(75) null,
	logoId number(30,0)
);

create table Contact_ (
	contactId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	accountId number(30,0),
	parentContactId number(30,0),
	firstName varchar2(75) null,
	middleName varchar2(75) null,
	lastName varchar2(75) null,
	prefixId number(30,0),
	suffixId number(30,0),
	male number(1, 0),
	birthday timestamp null,
	smsSn varchar2(75) null,
	aimSn varchar2(75) null,
	icqSn varchar2(75) null,
	jabberSn varchar2(75) null,
	msnSn varchar2(75) null,
	skypeSn varchar2(75) null,
	ymSn varchar2(75) null,
	employeeStatusId varchar2(75) null,
	employeeNumber varchar2(75) null,
	jobTitle varchar2(100) null,
	jobClass varchar2(75) null,
	hoursOfOperation varchar2(75) null
);

create table Counter (
	name varchar2(75) not null primary key,
	currentId number(30,0)
);

create table Country (
	countryId number(30,0) not null primary key,
	name varchar2(75) null,
	a2 varchar2(75) null,
	a3 varchar2(75) null,
	number_ varchar2(75) null,
	idd_ varchar2(75) null,
	active_ number(1, 0)
);

create table CyrusUser (
	userId varchar2(75) not null primary key,
	password_ varchar2(75) not null
);

create table CyrusVirtual (
	emailAddress varchar2(75) not null primary key,
	userId varchar2(75) not null
);

create table DLFileEntry (
	uuid_ varchar2(75) null,
	fileEntryId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	versionUserId number(30,0),
	versionUserName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	folderId number(30,0),
	name varchar2(300) null,
	title varchar2(300) null,
	description varchar2(4000) null,
	version number(30,20),
	size_ number(30,0),
	readCount number(30,0),
	extraSettings clob null
);

create table DLFileRank (
	fileRankId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	createDate timestamp null,
	folderId number(30,0),
	name varchar2(300) null
);

create table DLFileShortcut (
	uuid_ varchar2(75) null,
	fileShortcutId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	folderId number(30,0),
	toFolderId number(30,0),
	toName varchar2(300) null
);

create table DLFileVersion (
	fileVersionId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	folderId number(30,0),
	name varchar2(300) null,
	version number(30,20),
	size_ number(30,0)
);

create table DLFolder (
	uuid_ varchar2(75) null,
	folderId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	parentFolderId number(30,0),
	name varchar2(100) null,
	description varchar2(4000) null,
	lastPostDate timestamp null
);

create table EmailAddress (
	emailAddressId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	address varchar2(75) null,
	typeId number(30,0),
	primary_ number(1, 0)
);

create table Group_ (
	groupId number(30,0) not null primary key,
	companyId number(30,0),
	creatorUserId number(30,0),
	classNameId number(30,0),
	classPK number(30,0),
	parentGroupId number(30,0),
	liveGroupId number(30,0),
	name varchar2(75) null,
	description varchar2(4000) null,
	type_ number(30,0),
	typeSettings varchar2(4000) null,
	friendlyURL varchar2(100) null,
	active_ number(1, 0)
);

create table Groups_Orgs (
	groupId number(30,0) not null,
	organizationId number(30,0) not null,
	primary key (groupId, organizationId)
);

create table Groups_Permissions (
	groupId number(30,0) not null,
	permissionId number(30,0) not null,
	primary key (groupId, permissionId)
);

create table Groups_Roles (
	groupId number(30,0) not null,
	roleId number(30,0) not null,
	primary key (groupId, roleId)
);

create table Groups_UserGroups (
	groupId number(30,0) not null,
	userGroupId number(30,0) not null,
	primary key (groupId, userGroupId)
);

create table IGFolder (
	uuid_ varchar2(75) null,
	folderId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	createDate timestamp null,
	modifiedDate timestamp null,
	parentFolderId number(30,0),
	name varchar2(75) null,
	description varchar2(4000) null
);

create table IGImage (
	uuid_ varchar2(75) null,
	imageId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	createDate timestamp null,
	modifiedDate timestamp null,
	folderId number(30,0),
	description varchar2(4000) null,
	smallImageId number(30,0),
	largeImageId number(30,0)
);

create table Image (
	imageId number(30,0) not null primary key,
	modifiedDate timestamp null,
	text_ clob null,
	type_ varchar2(75) null,
	height number(30,0),
	width number(30,0),
	size_ number(30,0)
);

create table JournalArticle (
	uuid_ varchar2(75) null,
	id_ number(30,0) not null primary key,
	resourcePrimKey number(30,0),
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	articleId varchar2(75) null,
	version number(30,20),
	title varchar2(100) null,
	description varchar2(4000) null,
	content clob null,
	type_ varchar2(75) null,
	structureId varchar2(75) null,
	templateId varchar2(75) null,
	displayDate timestamp null,
	approved number(1, 0),
	approvedByUserId number(30,0),
	approvedByUserName varchar2(75) null,
	approvedDate timestamp null,
	expired number(1, 0),
	expirationDate timestamp null,
	reviewDate timestamp null,
	indexable number(1, 0),
	smallImage number(1, 0),
	smallImageId number(30,0),
	smallImageURL varchar2(75) null
);

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

create table JournalContentSearch (
	contentSearchId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	privateLayout number(1, 0),
	layoutId number(30,0),
	portletId varchar2(200) null,
	articleId varchar2(75) null
);

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

create table JournalStructure (
	uuid_ varchar2(75) null,
	id_ number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	structureId varchar2(75) null,
	name varchar2(75) null,
	description varchar2(4000) null,
	xsd clob null
);

create table JournalTemplate (
	uuid_ varchar2(75) null,
	id_ number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	templateId varchar2(75) null,
	structureId varchar2(75) null,
	name varchar2(75) null,
	description varchar2(4000) null,
	xsl clob null,
	langType varchar2(75) null,
	cacheable number(1, 0),
	smallImage number(1, 0),
	smallImageId number(30,0),
	smallImageURL varchar2(75) null
);

create table Layout (
	plid number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	privateLayout number(1, 0),
	layoutId number(30,0),
	parentLayoutId number(30,0),
	name varchar2(4000) null,
	title varchar2(4000) null,
	description varchar2(4000) null,
	type_ varchar2(75) null,
	typeSettings clob null,
	hidden_ number(1, 0),
	friendlyURL varchar2(100) null,
	iconImage number(1, 0),
	iconImageId number(30,0),
	themeId varchar2(75) null,
	colorSchemeId varchar2(75) null,
	wapThemeId varchar2(75) null,
	wapColorSchemeId varchar2(75) null,
	css varchar2(4000) null,
	priority number(30,0),
	dlFolderId number(30,0)
);

create table LayoutSet (
	layoutSetId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	privateLayout number(1, 0),
	logo number(1, 0),
	logoId number(30,0),
	themeId varchar2(75) null,
	colorSchemeId varchar2(75) null,
	wapThemeId varchar2(75) null,
	wapColorSchemeId varchar2(75) null,
	css varchar2(75) null,
	pageCount number(30,0),
	virtualHost varchar2(75) null
);

create table ListType (
	listTypeId number(30,0) not null primary key,
	name varchar2(75) null,
	type_ varchar2(75) null
);

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

create table MBCategory (
	uuid_ varchar2(75) null,
	categoryId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	parentCategoryId number(30,0),
	name varchar2(75) null,
	description varchar2(4000) null,
	lastPostDate timestamp null
);

create table MBDiscussion (
	discussionId number(30,0) not null primary key,
	classNameId number(30,0),
	classPK number(30,0),
	threadId number(30,0)
);

create table MBMessage (
	uuid_ varchar2(75) null,
	messageId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	categoryId number(30,0),
	threadId number(30,0),
	parentMessageId number(30,0),
	subject varchar2(75) null,
	body clob null,
	attachments number(1, 0),
	anonymous number(1, 0)
);

create table MBMessageFlag (
	messageFlagId number(30,0) not null primary key,
	userId number(30,0),
	messageId number(30,0),
	flag number(30,0)
);

create table MBStatsUser (
	statsUserId number(30,0) not null primary key,
	groupId number(30,0),
	userId number(30,0),
	messageCount number(30,0),
	lastPostDate timestamp null
);

create table MBThread (
	threadId number(30,0) not null primary key,
	categoryId number(30,0),
	rootMessageId number(30,0),
	messageCount number(30,0),
	viewCount number(30,0),
	lastPostByUserId number(30,0),
	lastPostDate timestamp null,
	priority number(30,20)
);

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

create table Organization_ (
	organizationId number(30,0) not null primary key,
	companyId number(30,0),
	parentOrganizationId number(30,0),
	name varchar2(100) null,
	location number(1, 0),
	recursable number(1, 0),
	regionId number(30,0),
	countryId number(30,0),
	statusId number(30,0),
	comments varchar2(4000) null
);

create table OrgGroupPermission (
	organizationId number(30,0) not null,
	groupId number(30,0) not null,
	permissionId number(30,0) not null,
	primary key (organizationId, groupId, permissionId)
);

create table OrgGroupRole (
	organizationId number(30,0) not null,
	groupId number(30,0) not null,
	roleId number(30,0) not null,
	primary key (organizationId, groupId, roleId)
);

create table OrgLabor (
	orgLaborId number(30,0) not null primary key,
	organizationId number(30,0),
	typeId number(30,0),
	sunOpen number(30,0),
	sunClose number(30,0),
	monOpen number(30,0),
	monClose number(30,0),
	tueOpen number(30,0),
	tueClose number(30,0),
	wedOpen number(30,0),
	wedClose number(30,0),
	thuOpen number(30,0),
	thuClose number(30,0),
	friOpen number(30,0),
	friClose number(30,0),
	satOpen number(30,0),
	satClose number(30,0)
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

create table PasswordTracker (
	passwordTrackerId number(30,0) not null primary key,
	userId number(30,0),
	createDate timestamp null,
	password_ varchar2(75) null
);

create table Permission_ (
	permissionId number(30,0) not null primary key,
	companyId number(30,0),
	actionId varchar2(75) null,
	resourceId number(30,0)
);

create table Phone (
	phoneId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	number_ varchar2(75) null,
	extension varchar2(75) null,
	typeId number(30,0),
	primary_ number(1, 0)
);

create table PluginSetting (
	pluginSettingId number(30,0) not null primary key,
	companyId number(30,0),
	pluginId varchar2(75) null,
	pluginType varchar2(75) null,
	roles varchar2(4000) null,
	active_ number(1, 0)
);

create table PollsChoice (
	uuid_ varchar2(75) null,
	choiceId number(30,0) not null primary key,
	questionId number(30,0),
	name varchar2(75) null,
	description varchar2(1000) null
);

create table PollsQuestion (
	uuid_ varchar2(75) null,
	questionId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	title varchar2(500) null,
	description varchar2(4000) null,
	expirationDate timestamp null,
	lastVoteDate timestamp null
);

create table PollsVote (
	voteId number(30,0) not null primary key,
	userId number(30,0),
	questionId number(30,0),
	choiceId number(30,0),
	voteDate timestamp null
);

create table Portlet (
	id_ number(30,0) not null primary key,
	companyId number(30,0),
	portletId varchar2(200) null,
	roles varchar2(4000) null,
	active_ number(1, 0)
);

create table PortletPreferences (
	portletPreferencesId number(30,0) not null primary key,
	ownerId number(30,0),
	ownerType number(30,0),
	plid number(30,0),
	portletId varchar2(200) null,
	preferences clob null
);

create table RatingsEntry (
	entryId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	score number(30,20)
);

create table RatingsStats (
	statsId number(30,0) not null primary key,
	classNameId number(30,0),
	classPK number(30,0),
	totalEntries number(30,0),
	totalScore number(30,20),
	averageScore number(30,20)
);

create table Region (
	regionId number(30,0) not null primary key,
	countryId number(30,0),
	regionCode varchar2(75) null,
	name varchar2(75) null,
	active_ number(1, 0)
);

create table Release_ (
	releaseId number(30,0) not null primary key,
	createDate timestamp null,
	modifiedDate timestamp null,
	buildNumber number(30,0),
	buildDate timestamp null,
	verified number(1, 0)
);

create table Resource_ (
	resourceId number(30,0) not null primary key,
	codeId number(30,0),
	primKey varchar2(300) null
);

create table ResourceCode (
	codeId number(30,0) not null primary key,
	companyId number(30,0),
	name varchar2(300) null,
	scope number(30,0)
);

create table Role_ (
	roleId number(30,0) not null primary key,
	companyId number(30,0),
	classNameId number(30,0),
	classPK number(30,0),
	name varchar2(75) null,
	description varchar2(4000) null,
	type_ number(30,0)
);

create table Roles_Permissions (
	roleId number(30,0) not null,
	permissionId number(30,0) not null,
	primary key (roleId, permissionId)
);

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
	directDownloadURL varchar2(2000) null,
	repoStoreArtifact number(1, 0)
);

create table ServiceComponent (
	serviceComponentId number(30,0) not null primary key,
	buildNamespace varchar2(75) null,
	buildNumber number(30,0),
	buildDate number(30,0),
	data_ clob null
);

create table ShoppingCart (
	cartId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	itemIds varchar2(4000) null,
	couponCodes varchar2(75) null,
	altShipping number(30,0),
	insure number(1, 0)
);

create table ShoppingCategory (
	categoryId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	parentCategoryId number(30,0),
	name varchar2(75) null,
	description varchar2(4000) null
);

create table ShoppingCoupon (
	couponId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	code_ varchar2(75) null,
	name varchar2(75) null,
	description varchar2(4000) null,
	startDate timestamp null,
	endDate timestamp null,
	active_ number(1, 0),
	limitCategories varchar2(4000) null,
	limitSkus varchar2(4000) null,
	minOrder number(30,20),
	discount number(30,20),
	discountType varchar2(75) null
);

create table ShoppingItem (
	itemId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	categoryId number(30,0),
	sku varchar2(75) null,
	name varchar2(200) null,
	description varchar2(4000) null,
	properties varchar2(4000) null,
	fields_ number(1, 0),
	fieldsQuantities varchar2(4000) null,
	minQuantity number(30,0),
	maxQuantity number(30,0),
	price number(30,20),
	discount number(30,20),
	taxable number(1, 0),
	shipping number(30,20),
	useShippingFormula number(1, 0),
	requiresShipping number(1, 0),
	stockQuantity number(30,0),
	featured_ number(1, 0),
	sale_ number(1, 0),
	smallImage number(1, 0),
	smallImageId number(30,0),
	smallImageURL varchar2(75) null,
	mediumImage number(1, 0),
	mediumImageId number(30,0),
	mediumImageURL varchar2(75) null,
	largeImage number(1, 0),
	largeImageId number(30,0),
	largeImageURL varchar2(75) null
);

create table ShoppingItemField (
	itemFieldId number(30,0) not null primary key,
	itemId number(30,0),
	name varchar2(75) null,
	values_ varchar2(4000) null,
	description varchar2(4000) null
);

create table ShoppingItemPrice (
	itemPriceId number(30,0) not null primary key,
	itemId number(30,0),
	minQuantity number(30,0),
	maxQuantity number(30,0),
	price number(30,20),
	discount number(30,20),
	taxable number(1, 0),
	shipping number(30,20),
	useShippingFormula number(1, 0),
	status number(30,0)
);

create table ShoppingOrder (
	orderId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	number_ varchar2(75) null,
	tax number(30,20),
	shipping number(30,20),
	altShipping varchar2(75) null,
	requiresShipping number(1, 0),
	insure number(1, 0),
	insurance number(30,20),
	couponCodes varchar2(75) null,
	couponDiscount number(30,20),
	billingFirstName varchar2(75) null,
	billingLastName varchar2(75) null,
	billingEmailAddress varchar2(75) null,
	billingCompany varchar2(75) null,
	billingStreet varchar2(75) null,
	billingCity varchar2(75) null,
	billingState varchar2(75) null,
	billingZip varchar2(75) null,
	billingCountry varchar2(75) null,
	billingPhone varchar2(75) null,
	shipToBilling number(1, 0),
	shippingFirstName varchar2(75) null,
	shippingLastName varchar2(75) null,
	shippingEmailAddress varchar2(75) null,
	shippingCompany varchar2(75) null,
	shippingStreet varchar2(75) null,
	shippingCity varchar2(75) null,
	shippingState varchar2(75) null,
	shippingZip varchar2(75) null,
	shippingCountry varchar2(75) null,
	shippingPhone varchar2(75) null,
	ccName varchar2(75) null,
	ccType varchar2(75) null,
	ccNumber varchar2(75) null,
	ccExpMonth number(30,0),
	ccExpYear number(30,0),
	ccVerNumber varchar2(75) null,
	comments varchar2(4000) null,
	ppTxnId varchar2(75) null,
	ppPaymentStatus varchar2(75) null,
	ppPaymentGross number(30,20),
	ppReceiverEmail varchar2(75) null,
	ppPayerEmail varchar2(75) null,
	sendOrderEmail number(1, 0),
	sendShippingEmail number(1, 0)
);

create table ShoppingOrderItem (
	orderItemId number(30,0) not null primary key,
	orderId number(30,0),
	itemId varchar2(75) null,
	sku varchar2(75) null,
	name varchar2(200) null,
	description varchar2(4000) null,
	properties varchar2(4000) null,
	price number(30,20),
	quantity number(30,0),
	shippedDate timestamp null
);

create table Subscription (
	subscriptionId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	frequency varchar2(75) null
);

create table TagsAsset (
	assetId number(30,0) not null primary key,
	groupId number(30,0),
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
	width number(30,0),
	priority number(30,20),
	viewCount number(30,0)
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

create table User_ (
	uuid_ varchar2(75) null,
	userId number(30,0) not null primary key,
	companyId number(30,0),
	createDate timestamp null,
	modifiedDate timestamp null,
	defaultUser number(1, 0),
	contactId number(30,0),
	password_ varchar2(75) null,
	passwordEncrypted number(1, 0),
	passwordReset number(1, 0),
	passwordModifiedDate timestamp null,
	graceLoginCount number(30,0),
	screenName varchar2(75) null,
	emailAddress varchar2(75) null,
	portraitId number(30,0),
	languageId varchar2(75) null,
	timeZoneId varchar2(75) null,
	greeting varchar2(75) null,
	comments varchar2(4000) null,
	loginDate timestamp null,
	loginIP varchar2(75) null,
	lastLoginDate timestamp null,
	lastLoginIP varchar2(75) null,
	lastFailedLoginDate timestamp null,
	failedLoginAttempts number(30,0),
	lockout number(1, 0),
	lockoutDate timestamp null,
	agreedToTermsOfUse number(1, 0),
	active_ number(1, 0)
);

create table UserGroup (
	userGroupId number(30,0) not null primary key,
	companyId number(30,0),
	parentUserGroupId number(30,0),
	name varchar2(75) null,
	description varchar2(4000) null
);

create table UserGroupRole (
	userId number(30,0) not null,
	groupId number(30,0) not null,
	roleId number(30,0) not null,
	primary key (userId, groupId, roleId)
);

create table UserIdMapper (
	userIdMapperId number(30,0) not null primary key,
	userId number(30,0),
	type_ varchar2(75) null,
	description varchar2(75) null,
	externalUserId varchar2(75) null
);

create table Users_Groups (
	userId number(30,0) not null,
	groupId number(30,0) not null,
	primary key (userId, groupId)
);

create table Users_Orgs (
	userId number(30,0) not null,
	organizationId number(30,0) not null,
	primary key (userId, organizationId)
);

create table Users_Permissions (
	userId number(30,0) not null,
	permissionId number(30,0) not null,
	primary key (userId, permissionId)
);

create table Users_Roles (
	userId number(30,0) not null,
	roleId number(30,0) not null,
	primary key (userId, roleId)
);

create table Users_UserGroups (
	userId number(30,0) not null,
	userGroupId number(30,0) not null,
	primary key (userId, userGroupId)
);

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

create table UserTrackerPath (
	userTrackerPathId number(30,0) not null primary key,
	userTrackerId number(30,0),
	path_ varchar2(4000) null,
	pathDate timestamp null
);

create table WebDAVProps (
	webDavPropsId number(30,0) not null primary key,
	companyId number(30,0),
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	props clob null
);

create table Website (
	websiteId number(30,0) not null primary key,
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	classNameId number(30,0),
	classPK number(30,0),
	url varchar2(4000) null,
	typeId number(30,0),
	primary_ number(1, 0)
);

create table WikiNode (
	uuid_ varchar2(75) null,
	nodeId number(30,0) not null primary key,
	groupId number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	modifiedDate timestamp null,
	name varchar2(75) null,
	description varchar2(4000) null,
	lastPostDate timestamp null
);

create table WikiPage (
	uuid_ varchar2(75) null,
	pageId number(30,0) not null primary key,
	resourcePrimKey number(30,0),
	companyId number(30,0),
	userId number(30,0),
	userName varchar2(75) null,
	createDate timestamp null,
	nodeId number(30,0),
	title varchar2(75) null,
	version number(30,20),
	content clob null,
	format varchar2(75) null,
	head number(1, 0)
);

create table WikiPageResource (
	resourcePrimKey number(30,0) not null primary key,
	nodeId number(30,0),
	title varchar2(75) null
);



insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (1, 'Canada', 'CA', 'CAN', '124', '001', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (2, 'China', 'CN', 'CHN', '156', '086', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (3, 'France', 'FR', 'FRA', '250', '033', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (4, 'Germany', 'DE', 'DEU', '276', '049', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (5, 'Hong Kong', 'HK', 'HKG', '344', '852', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (6, 'Hungary', 'HU', 'HUN', '348', '036', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (7, 'Israel', 'IL', 'ISR', '376', '972', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (8, 'Italy', 'IT', 'ITA', '380', '039', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (9, 'Japan', 'JP', 'JPN', '392', '081', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (10, 'South Korea', 'KP', 'KOR', '410', '082', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (11, 'Netherlands', 'NL', 'NLD', '528', '031', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (12, 'Portugal', 'PT', 'PRT', '620', '351', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (13, 'Russia', 'RU', 'RUS', '643', '007', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (14, 'Singapore', 'SG', 'SGP', '702', '065', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (15, 'Spain', 'ES', 'ESP', '724', '034', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (16, 'Turkey', 'TR', 'TUR', '792', '090', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (17, 'Vietnam', 'VM', 'VNM', '704', '084', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (18, 'United Kingdom', 'GB', 'GBR', '826', '044', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (19, 'United States', 'US', 'USA', '840', '001', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (20, 'Afghanistan', 'AF', 'AFG', '4', '093', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (21, 'Albania', 'AL', 'ALB', '8', '355', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (22, 'Algeria', 'DZ', 'DZA', '12', '213', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (23, 'American Samoa', 'AS', 'ASM', '16', '684', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (24, 'Andorra', 'AD', 'AND', '20', '376', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (25, 'Angola', 'AO', 'AGO', '24', '244', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (26, 'Anguilla', 'AI', 'AIA', '660', '264', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (27, 'Antarctica', 'AQ', 'ATA', '10', '672', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (28, 'Antigua', 'AG', 'ATG', '28', '268', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (29, 'Argentina', 'AR', 'ARG', '32', '054', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (30, 'Armenia', 'AM', 'ARM', '51', '374', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (31, 'Aruba', 'AW', 'ABW', '533', '297', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (32, 'Australia', 'AU', 'AUS', '36', '061', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (33, 'Austria', 'AT', 'AUT', '40', '043', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (34, 'Azerbaijan', 'AZ', 'AZE', '31', '994', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (35, 'Bahamas', 'BS', 'BHS', '44', '242', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (36, 'Bahrain', 'BH', 'BHR', '48', '973', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (37, 'Bangladesh', 'BD', 'BGD', '50', '880', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (38, 'Barbados', 'BB', 'BRB', '52', '246', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (39, 'Belarus', 'BY', 'BLR', '112', '375', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (40, 'Belgium', 'BE', 'BEL', '56', '032', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (41, 'Belize', 'BZ', 'BLZ', '84', '501', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (42, 'Benin', 'BJ', 'BEN', '204', '229', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (43, 'Bermuda', 'BM', 'BMU', '60', '441', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (44, 'Bhutan', 'BT', 'BTN', '64', '975', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (45, 'Bolivia', 'BO', 'BOL', '68', '591', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (46, 'Bosnia-Herzegovina', 'BA', 'BIH', '70', '387', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (47, 'Botswana', 'BW', 'BWA', '72', '267', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (48, 'Brazil', 'BR', 'BRA', '76', '055', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (49, 'British Virgin Islands', 'VG', 'VGB', '92', '284', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (50, 'Brunei', 'BN', 'BRN', '96', '673', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (51, 'Bulgaria', 'BG', 'BGR', '100', '359', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (52, 'Burkina Faso', 'BF', 'BFA', '854', '226', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (53, 'Burma (Myanmar)', 'MM', 'MMR', '104', '095', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (54, 'Burundi', 'BI', 'BDI', '108', '257', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (55, 'Cambodia', 'KH', 'KHM', '116', '855', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (56, 'Cameroon', 'CM', 'CMR', '120', '237', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (57, 'Cape Verde Island', 'CV', 'CPV', '132', '238', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (58, 'Cayman Islands', 'KY', 'CYM', '136', '345', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (59, 'Central African Republic', 'CF', 'CAF', '140', '236', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (60, 'Chad', 'TD', 'TCD', '148', '235', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (61, 'Chile', 'CL', 'CHL', '152', '056', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (62, 'Christmas Island', 'CX', 'CXR', '162', '061', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (63, 'Cocos Islands', 'CC', 'CCK', '166', '061', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (64, 'Colombia', 'CO', 'COL', '170', '057', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (65, 'Comoros', 'KM', 'COM', '174', '269', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (66, 'Republic of Congo', 'CD', 'COD', '180', '242', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (67, 'Democratic Republic of Congo', 'CG', 'COG', '178', '243', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (68, 'Cook Islands', 'CK', 'COK', '184', '682', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (69, 'Costa Rica', 'CI', 'CRI', '188', '506', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (70, 'Croatia', 'HR', 'HRV', '191', '385', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (71, 'Cuba', 'CU', 'CUB', '192', '053', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (72, 'Cyprus', 'CY', 'CYP', '196', '357', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (73, 'Czech Republic', 'CZ', 'CZE', '203', '420', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (74, 'Denmark', 'DK', 'DNK', '208', '045', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (75, 'Djibouti', 'DJ', 'DJI', '262', '253', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (76, 'Dominica', 'DM', 'DMA', '212', '767', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (77, 'Dominican Republic', 'DO', 'DOM', '214', '809', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (78, 'Ecuador', 'EC', 'ECU', '218', '593', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (79, 'Egypt', 'EG', 'EGY', '818', '020', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (80, 'El Salvador', 'SV', 'SLV', '222', '503', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (81, 'Equatorial Guinea', 'GQ', 'GNQ', '226', '240', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (82, 'Eritrea', 'ER', 'ERI', '232', '291', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (83, 'Estonia', 'EE', 'EST', '233', '372', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (84, 'Ethiopia', 'ET', 'ETH', '231', '251', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (85, 'Faeroe Islands', 'FO', 'FRO', '234', '298', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (86, 'Falkland Islands', 'FK', 'FLK', '238', '500', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (87, 'Fiji Islands', 'FJ', 'FJI', '242', '679', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (88, 'Finland', 'FI', 'FIN', '246', '358', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (89, 'French Guiana', 'GF', 'GUF', '254', '594', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (90, 'French Polynesia', 'PF', 'PYF', '258', '689', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (91, 'Gabon', 'GA', 'GAB', '266', '241', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (92, 'Gambia', 'GM', 'GMB', '270', '220', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (93, 'Georgia', 'GE', 'GEO', '268', '995', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (94, 'Ghana', 'GH', 'GHA', '288', '233', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (95, 'Gibraltar', 'GI', 'GIB', '292', '350', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (96, 'Greece', 'GR', 'GRC', '300', '030', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (97, 'Greenland', 'GL', 'GRL', '304', '299', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (98, 'Grenada', 'GD', 'GRD', '308', '473', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (99, 'Guadeloupe', 'GP', 'GLP', '312', '590', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (100, 'Guam', 'GU', 'GUM', '316', '671', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (101, 'Guatemala', 'GT', 'GTM', '320', '502', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (102, 'Guinea', 'GN', 'GIN', '324', '224', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (103, 'Guinea-Bissau', 'GW', 'GNB', '624', '245', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (104, 'Guyana', 'GY', 'GUY', '328', '592', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (105, 'Haiti', 'HT', 'HTI', '332', '509', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (106, 'Honduras', 'HN', 'HND', '340', '504', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (107, 'Iceland', 'IS', 'ISL', '352', '354', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (108, 'India', 'IN', 'IND', '356', '091', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (109, 'Indonesia', 'ID', 'IDN', '360', '062', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (110, 'Iran', 'IR', 'IRN', '364', '098', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (111, 'Iraq', 'IQ', 'IRQ', '368', '964', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (112, 'Ireland', 'IE', 'IRL', '372', '353', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (113, 'Ivory Coast', 'CI', 'CIV', '384', '225', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (114, 'Jamaica', 'JM', 'JAM', '388', '876', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (115, 'Jordan', 'JO', 'JOR', '400', '962', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (116, 'Kazakhstan', 'KZ', 'KAZ', '398', '007', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (117, 'Kenya', 'KE', 'KEN', '404', '254', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (118, 'Kiribati', 'KI', 'KIR', '408', '686', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (119, 'Kuwait', 'KW', 'KWT', '414', '965', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (120, 'North Korea', 'KP', 'PRK', '408', '850', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (121, 'Kyrgyzstan', 'KG', 'KGZ', '471', '996', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (122, 'Laos', 'LA', 'LAO', '418', '856', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (123, 'Latvia', 'LV', 'LVA', '428', '371', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (124, 'Lebanon', 'LB', 'LBN', '422', '961', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (125, 'Lesotho', 'LS', 'LSO', '426', '266', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (126, 'Liberia', 'LR', 'LBR', '430', '231', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (127, 'Libya', 'LY', 'LBY', '434', '218', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (128, 'Liechtenstein', 'LI', 'LIE', '438', '423', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (129, 'Lithuania', 'LT', 'LTU', '440', '370', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (130, 'Luxembourg', 'LU', 'LUX', '442', '352', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (131, 'Macau', 'MO', 'MAC', '446', '853', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (132, 'Macedonia', 'MK', 'MKD', '807', '389', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (133, 'Madagascar', 'MG', 'MDG', '450', '261', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (134, 'Malawi', 'MW', 'MWI', '454', '265', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (135, 'Malaysia', 'MY', 'MYS', '458', '060', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (136, 'Maldives', 'MV', 'MDV', '462', '960', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (137, 'Mali', 'ML', 'MLI', '466', '223', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (138, 'Malta', 'MT', 'MLT', '470', '356', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (139, 'Marshall Islands', 'MH', 'MHL', '584', '692', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (140, 'Martinique', 'MQ', 'MTQ', '474', '596', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (141, 'Mauritania', 'MR', 'MRT', '478', '222', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (142, 'Mauritius', 'MU', 'MUS', '480', '230', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (143, 'Mayotte Island', 'YT', 'MYT', '175', '269', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (144, 'Mexico', 'MX', 'MEX', '484', '052', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (145, 'Micronesia', 'FM', 'FSM', '583', '691', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (146, 'Moldova', 'MD', 'MDA', '498', '373', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (147, 'Monaco', 'MC', 'MCO', '492', '377', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (148, 'Mongolia', 'MN', 'MNG', '496', '976', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (149, 'Montserrat', 'MS', 'MSR', '500', '664', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (150, 'Morocco', 'MA', 'MAR', '504', '212', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (151, 'Mozambique', 'MZ', 'MOZ', '508', '258', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (152, 'Myanmar (Burma)', 'MM', 'MMR', '104', '095', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (153, 'Namibia', 'NA', 'NAM', '516', '264', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (154, 'Nauru', 'NR', 'NRU', '520', '674', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (155, 'Nepal', 'NP', 'NPL', '524', '977', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (156, 'Netherlands Antilles', 'AN', 'ANT', '530', '599', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (157, 'New Caledonia', 'NC', 'NCL', '540', '687', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (158, 'New Zealand', 'NZ', 'NZL', '554', '064', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (159, 'Nicaragua', 'NE', 'NER', '558', '505', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (160, 'Niger', 'NE', 'NER', '562', '227', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (161, 'Nigeria', 'NG', 'NGA', '566', '234', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (162, 'Niue', 'NU', 'NIU', '570', '683', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (163, 'Norfolk Island', 'NF', 'NFK', '574', '672', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (164, 'Norway', 'NO', 'NOR', '578', '047', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (165, 'Oman', 'OM', 'OMN', '512', '968', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (166, 'Pakistan', 'PK', 'PAK', '586', '092', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (167, 'Palau', 'PW', 'PLW', '585', '680', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (168, 'Palestine', 'PS', 'PSE', '275', '970', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (169, 'Panama', 'PA', 'PAN', '591', '507', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (170, 'Papua New Guinea', 'PG', 'PNG', '598', '675', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (171, 'Paraguay', 'PY', 'PRY', '600', '595', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (172, 'Peru', 'PE', 'PER', '604', '051', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (173, 'Philippines', 'PH', 'PHL', '608', '063', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (174, 'Poland', 'PL', 'POL', '616', '048', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (175, 'Puerto Rico', 'PR', 'PRI', '630', '787', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (176, 'Qatar', 'QA', 'QAT', '634', '974', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (177, 'Reunion Island', 'RE', 'REU', '638', '262', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (178, 'Romania', 'RO', 'ROU', '642', '040', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (179, 'Rwanda', 'RW', 'RWA', '646', '250', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (180, 'St. Helena', 'SH', 'SHN', '654', '290', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (181, 'St. Kitts', 'KN', 'KNA', '659', '869', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (182, 'St. Lucia', 'LC', 'LCA', '662', '758', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (183, 'St. Pierre & Miquelon', 'PM', 'SPM', '666', '508', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (184, 'St. Vincent', 'VC', 'VCT', '670', '784', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (185, 'San Marino', 'SM', 'SMR', '674', '378', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (186, 'Sao Tome & Principe', 'ST', 'STP', '678', '239', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (187, 'Saudi Arabia', 'SA', 'SAU', '682', '966', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (188, 'Senegal', 'SN', 'SEN', '686', '221', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (189, 'Serbia', 'CS', 'SCG', '891', '381', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (190, 'Seychelles', 'SC', 'SYC', '690', '248', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (191, 'Sierra Leone', 'SL', 'SLE', '694', '249', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (192, 'Slovakia', 'SK', 'SVK', '703', '421', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (193, 'Slovenia', 'SI', 'SVN', '705', '386', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (194, 'Solomon Islands', 'SB', 'SLB', '90', '677', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (195, 'Somalia', 'SO', 'SOM', '706', '252', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (196, 'South Africa', 'ZA', 'ZAF', '710', '027', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (197, 'Sri Lanka', 'LK', 'LKA', '144', '094', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (198, 'Sudan', 'SD', 'SDN', '736', '095', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (199, 'Suriname', 'SR', 'SUR', '740', '597', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (200, 'Swaziland', 'SZ', 'SWZ', '748', '268', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (201, 'Sweden', 'SE', 'SWE', '752', '046', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (202, 'Switzerland', 'CH', 'CHE', '756', '041', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (203, 'Syria', 'SY', 'SYR', '760', '963', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (204, 'Taiwan', 'TW', 'TWN', '158', '886', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (205, 'Tajikistan', 'TJ', 'TJK', '762', '992', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (206, 'Tanzania', 'TZ', 'TZA', '834', '255', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (207, 'Thailand', 'TH', 'THA', '764', '066', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (208, 'Togo', 'TG', 'TGO', '768', '228', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (209, 'Tonga', 'TO', 'TON', '776', '676', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (210, 'Trinidad & Tobago', 'TT', 'TTO', '780', '868', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (211, 'Tunisia', 'TN', 'TUN', '788', '216', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (212, 'Turkmenistan', 'TM', 'TKM', '795', '993', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (213, 'Turks & Caicos', 'TC', 'TCA', '796', '649', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (214, 'Tuvalu', 'TV', 'TUV', '798', '688', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (215, 'Uganda', 'UG', 'UGA', '800', '256', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (216, 'Ukraine', 'UA', 'UKR', '804', '380', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (217, 'United Arab Emirates', 'AE', 'ARE', '784', '971', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (218, 'Uruguay', 'UY', 'URY', '858', '598', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (219, 'Uzbekistan', 'UZ', 'UZB', '860', '998', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (220, 'Vanuatu', 'VU', 'VUT', '548', '678', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (221, 'Vatican City', 'VA', 'VAT', '336', '039', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (222, 'Venezuela', 'VE', 'VEN', '862', '058', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (223, 'Wallis & Futuna', 'WF', 'WLF', '876', '681', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (224, 'Western Samoa', 'EH', 'ESH', '732', '685', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (225, 'Yemen', 'YE', 'YEM', '887', '967', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (226, 'Yugoslavia', 'MK', 'MKD', '446', '381', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (227, 'Zambia', 'ZM', 'ZMB', '894', '260', 1);
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (228, 'Zimbabwe', 'ZW', 'ZWE', '716', '263', 1);

insert into Region (regionId, countryId, regionCode, name, active_) values (1, 19, 'AL', 'Alabama', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (2, 19, 'AK', 'Alaska', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (3, 19, 'AZ', 'Arizona', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (4, 19, 'AR', 'Arkansas', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (5, 19, 'CA', 'California', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (6, 19, 'CO', 'Colorado', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (7, 19, 'CT', 'Connecticut', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (8, 19, 'DC', 'District of Columbia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (9, 19, 'DE', 'Delaware', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (10, 19, 'FL', 'Florida', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (11, 19, 'GA', 'Georgia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (12, 19, 'HI', 'Hawaii', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (13, 19, 'ID', 'Idaho', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (14, 19, 'IL', 'Illinois', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (15, 19, 'IN', 'Indiana', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (16, 19, 'IA', 'Iowa', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (17, 19, 'KS', 'Kansas', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (18, 19, 'KY', 'Kentucky ', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (19, 19, 'LA', 'Louisiana ', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (20, 19, 'ME', 'Maine', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (21, 19, 'MD', 'Maryland', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (22, 19, 'MA', 'Massachusetts', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (23, 19, 'MI', 'Michigan', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (24, 19, 'MN', 'Minnesota', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (25, 19, 'MS', 'Mississippi', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (26, 19, 'MO', 'Missouri', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (27, 19, 'MT', 'Montana', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (28, 19, 'NE', 'Nebraska', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (29, 19, 'NV', 'Nevada', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (30, 19, 'NH', 'New Hampshire', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (31, 19, 'NJ', 'New Jersey', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (32, 19, 'NM', 'New Mexico', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (33, 19, 'NY', 'New York', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (34, 19, 'NC', 'North Carolina', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (35, 19, 'ND', 'North Dakota', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (36, 19, 'OH', 'Ohio', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (37, 19, 'OK', 'Oklahoma ', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (38, 19, 'OR', 'Oregon', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (39, 19, 'PA', 'Pennsylvania', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (40, 19, 'PR', 'Puerto Rico', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (41, 19, 'RI', 'Rhode Island', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (42, 19, 'SC', 'South Carolina', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (43, 19, 'SD', 'South Dakota', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (44, 19, 'TN', 'Tennessee', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (45, 19, 'TX', 'Texas', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (46, 19, 'UT', 'Utah', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (47, 19, 'VT', 'Vermont', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (48, 19, 'VA', 'Virginia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (49, 19, 'WA', 'Washington', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (50, 19, 'WV', 'West Virginia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (51, 19, 'WI', 'Wisconsin', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (52, 19, 'WY', 'Wyoming', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (53, 1, 'AL', 'Alberta', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (54, 1, 'BC', 'British Columbia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (55, 1, 'MB', 'Manitoba', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (56, 1, 'NB', 'New Brunswick', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (57, 1, 'NL', 'Newfoundland and Labrador', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (58, 1, 'NT', 'Northwest Territories', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (59, 1, 'NS', 'Nova Scotia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (60, 1, 'NU', 'Nunavut', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (61, 1, 'ON', 'Ontario', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (62, 1, 'PE', 'Prince Edward Island', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (63, 1, 'QC', 'Quebec', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (64, 1, 'SK', 'Saskatchewan', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (65, 1, 'YT', 'Yukon', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (66, 15, 'AN', 'Andalusia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (67, 15, 'AR', 'Aragon', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (68, 15, 'AS', 'Asturias', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (69, 15, 'IB', 'Balearic Islands', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (70, 15, 'PV', 'Basque Country', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (71, 15, 'CN', 'Canary Islands', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (72, 15, 'CB', 'Cantabria', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (73, 15, 'CL', 'Castile and Leon', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (74, 15, 'CM', 'Castile-La Mancha', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (75, 15, 'CT', 'Catalonia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (76, 15, 'CE', 'Ceuta', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (77, 15, 'EX', 'Extremadura', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (78, 15, 'GA', 'Galicia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (79, 15, 'LO', 'La Rioja', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (80, 15, 'M', 'Madrid', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (81, 15, 'ML', 'Melilla', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (82, 15, 'MU', 'Murcia', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (83, 15, 'NA', 'Navarra', 1);
insert into Region (regionId, countryId, regionCode, name, active_) values (84, 15, 'VC', 'Valencia', 1);

--
-- List types for accounts
--

insert into ListType (listTypeId, name, type_) values (10000, 'Billing', 'com.liferay.portal.model.Account.address');
insert into ListType (listTypeId, name, type_) values (10001, 'Other', 'com.liferay.portal.model.Account.address');
insert into ListType (listTypeId, name, type_) values (10002, 'P.O. Box', 'com.liferay.portal.model.Account.address');
insert into ListType (listTypeId, name, type_) values (10003, 'Shipping', 'com.liferay.portal.model.Account.address');

insert into ListType (listTypeId, name, type_) values (10004, 'E-mail', 'com.liferay.portal.model.Account.emailAddress');
insert into ListType (listTypeId, name, type_) values (10005, 'E-mail 2', 'com.liferay.portal.model.Account.emailAddress');
insert into ListType (listTypeId, name, type_) values (10006, 'E-mail 3', 'com.liferay.portal.model.Account.emailAddress');

insert into ListType (listTypeId, name, type_) values (10007, 'Fax', 'com.liferay.portal.model.Account.phone');
insert into ListType (listTypeId, name, type_) values (10008, 'Local', 'com.liferay.portal.model.Account.phone');
insert into ListType (listTypeId, name, type_) values (10009, 'Other', 'com.liferay.portal.model.Account.phone');
insert into ListType (listTypeId, name, type_) values (10010, 'Toll-Free', 'com.liferay.portal.model.Account.phone');
insert into ListType (listTypeId, name, type_) values (10011, 'TTY', 'com.liferay.portal.model.Account.phone');

insert into ListType (listTypeId, name, type_) values (10012, 'Intranet', 'com.liferay.portal.model.Account.website');
insert into ListType (listTypeId, name, type_) values (10013, 'Public', 'com.liferay.portal.model.Account.website');

--
-- List types for contacts
--

insert into ListType (listTypeId, name, type_) values (11000, 'Business', 'com.liferay.portal.model.Contact.address');
insert into ListType (listTypeId, name, type_) values (11001, 'Other', 'com.liferay.portal.model.Contact.address');
insert into ListType (listTypeId, name, type_) values (11002, 'Personal', 'com.liferay.portal.model.Contact.address');

insert into ListType (listTypeId, name, type_) values (11003, 'E-mail', 'com.liferay.portal.model.Contact.emailAddress');
insert into ListType (listTypeId, name, type_) values (11004, 'E-mail 2', 'com.liferay.portal.model.Contact.emailAddress');
insert into ListType (listTypeId, name, type_) values (11005, 'E-mail 3', 'com.liferay.portal.model.Contact.emailAddress');

insert into ListType (listTypeId, name, type_) values (11006, 'Business', 'com.liferay.portal.model.Contact.phone');
insert into ListType (listTypeId, name, type_) values (11007, 'Business Fax', 'com.liferay.portal.model.Contact.phone');
insert into ListType (listTypeId, name, type_) values (11008, 'Mobile', 'com.liferay.portal.model.Contact.phone');
insert into ListType (listTypeId, name, type_) values (11009, 'Other', 'com.liferay.portal.model.Contact.phone');
insert into ListType (listTypeId, name, type_) values (11010, 'Pager', 'com.liferay.portal.model.Contact.phone');
insert into ListType (listTypeId, name, type_) values (11011, 'Personal', 'com.liferay.portal.model.Contact.phone');
insert into ListType (listTypeId, name, type_) values (11012, 'Personal Fax', 'com.liferay.portal.model.Contact.phone');
insert into ListType (listTypeId, name, type_) values (11013, 'TTY', 'com.liferay.portal.model.Contact.phone');

insert into ListType (listTypeId, name, type_) values (11014, 'Dr.', 'com.liferay.portal.model.Contact.prefix');
insert into ListType (listTypeId, name, type_) values (11015, 'Mr.', 'com.liferay.portal.model.Contact.prefix');
insert into ListType (listTypeId, name, type_) values (11016, 'Mrs.', 'com.liferay.portal.model.Contact.prefix');
insert into ListType (listTypeId, name, type_) values (11017, 'Ms.', 'com.liferay.portal.model.Contact.prefix');

insert into ListType (listTypeId, name, type_) values (11020, 'II', 'com.liferay.portal.model.Contact.suffix');
insert into ListType (listTypeId, name, type_) values (11021, 'III', 'com.liferay.portal.model.Contact.suffix');
insert into ListType (listTypeId, name, type_) values (11022, 'IV', 'com.liferay.portal.model.Contact.suffix');
insert into ListType (listTypeId, name, type_) values (11023, 'Jr.', 'com.liferay.portal.model.Contact.suffix');
insert into ListType (listTypeId, name, type_) values (11024, 'PhD.', 'com.liferay.portal.model.Contact.suffix');
insert into ListType (listTypeId, name, type_) values (11025, 'Sr.', 'com.liferay.portal.model.Contact.suffix');

insert into ListType (listTypeId, name, type_) values (11026, 'Blog', 'com.liferay.portal.model.Contact.website');
insert into ListType (listTypeId, name, type_) values (11027, 'Business', 'com.liferay.portal.model.Contact.website');
insert into ListType (listTypeId, name, type_) values (11028, 'Other', 'com.liferay.portal.model.Contact.website');
insert into ListType (listTypeId, name, type_) values (11029, 'Personal', 'com.liferay.portal.model.Contact.website');

--
-- List types for organizations
--

insert into ListType (listTypeId, name, type_) values (12000, 'Billing', 'com.liferay.portal.model.Organization.address');
insert into ListType (listTypeId, name, type_) values (12001, 'Other', 'com.liferay.portal.model.Organization.address');
insert into ListType (listTypeId, name, type_) values (12002, 'P.O. Box', 'com.liferay.portal.model.Organization.address');
insert into ListType (listTypeId, name, type_) values (12003, 'Shipping', 'com.liferay.portal.model.Organization.address');

insert into ListType (listTypeId, name, type_) values (12004, 'E-mail', 'com.liferay.portal.model.Organization.emailAddress');
insert into ListType (listTypeId, name, type_) values (12005, 'E-mail 2', 'com.liferay.portal.model.Organization.emailAddress');
insert into ListType (listTypeId, name, type_) values (12006, 'E-mail 3', 'com.liferay.portal.model.Organization.emailAddress');

insert into ListType (listTypeId, name, type_) values (12007, 'Fax', 'com.liferay.portal.model.Organization.phone');
insert into ListType (listTypeId, name, type_) values (12008, 'Local', 'com.liferay.portal.model.Organization.phone');
insert into ListType (listTypeId, name, type_) values (12009, 'Other', 'com.liferay.portal.model.Organization.phone');
insert into ListType (listTypeId, name, type_) values (12010, 'Toll-Free', 'com.liferay.portal.model.Organization.phone');
insert into ListType (listTypeId, name, type_) values (12011, 'TTY', 'com.liferay.portal.model.Organization.phone');

insert into ListType (listTypeId, name, type_) values (12012, 'Administrative', 'com.liferay.portal.model.Organization.service');
insert into ListType (listTypeId, name, type_) values (12013, 'Contracts', 'com.liferay.portal.model.Organization.service');
insert into ListType (listTypeId, name, type_) values (12014, 'Donation', 'com.liferay.portal.model.Organization.service');
insert into ListType (listTypeId, name, type_) values (12015, 'Retail', 'com.liferay.portal.model.Organization.service');
insert into ListType (listTypeId, name, type_) values (12016, 'Training', 'com.liferay.portal.model.Organization.service');

insert into ListType (listTypeId, name, type_) values (12017, 'Full Member', 'com.liferay.portal.model.Organization.status');
insert into ListType (listTypeId, name, type_) values (12018, 'Provisional Member', 'com.liferay.portal.model.Organization.status');

insert into ListType (listTypeId, name, type_) values (12019, 'Intranet', 'com.liferay.portal.model.Organization.website');
insert into ListType (listTypeId, name, type_) values (12020, 'Public', 'com.liferay.portal.model.Organization.website');


insert into Counter values ('com.liferay.counter.model.Counter', 10000);


insert into Release_ (releaseId, createDate, modifiedDate, buildNumber, verified) values (1, sysdate, sysdate, 4401, 0);


commit;
