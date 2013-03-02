use master
exec sp_dboption 'lportal', 'allow nulls by default' , true
go

exec sp_dboption 'lportal', 'select into/bulkcopy/pllsort' , true
go

use lportal

create table Account_ (
	accountId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	parentAccountId decimal(20,0),
	name varchar(75) null,
	legalName varchar(75) null,
	legalId varchar(75) null,
	legalType varchar(75) null,
	sicCode varchar(75) null,
	tickerSymbol varchar(75) null,
	industry varchar(75) null,
	type_ varchar(75) null,
	size_ varchar(75) null
)
go

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

create table Address (
	addressId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	street1 varchar(75) null,
	street2 varchar(75) null,
	street3 varchar(75) null,
	city varchar(75) null,
	zip varchar(75) null,
	regionId decimal(20,0),
	countryId decimal(20,0),
	typeId int,
	mailing int,
	primary_ int
)
go

create table BlogsCategory (
	categoryId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	parentCategoryId decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null
)
go

create table BlogsEntry (
	uuid_ varchar(75) null,
	entryId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	title varchar(150) null,
	urlTitle varchar(150) null,
	content text null,
	displayDate datetime null
)
go

create table BlogsStatsUser (
	statsUserId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	entryCount int,
	lastPostDate datetime null,
	ratingsTotalEntries int,
	ratingsTotalScore float,
	ratingsAverageScore float
)
go

create table BookmarksEntry (
	uuid_ varchar(75) null,
	entryId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	createDate datetime null,
	modifiedDate datetime null,
	folderId decimal(20,0),
	name varchar(300) null,
	url varchar(1000) null,
	comments varchar(1000) null,
	visits int,
	priority int
)
go

create table BookmarksFolder (
	uuid_ varchar(75) null,
	folderId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	createDate datetime null,
	modifiedDate datetime null,
	parentFolderId decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null
)
go

create table CalEvent (
	uuid_ varchar(75) null,
	eventId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	title varchar(75) null,
	description varchar(1000) null,
	startDate datetime null,
	endDate datetime null,
	durationHour int,
	durationMinute int,
	allDay int,
	timeZoneSensitive int,
	type_ varchar(75) null,
	repeating int,
	recurrence text null,
	remindBy varchar(75) null,
	firstReminder int,
	secondReminder int
)
go

create table ClassName_ (
	classNameId decimal(20,0) not null primary key,
	value varchar(200) null
)
go

create table Company (
	companyId decimal(20,0) not null primary key,
	accountId decimal(20,0),
	webId varchar(75) null,
	key_ text null,
	virtualHost varchar(75) null,
	mx varchar(75) null,
	logoId decimal(20,0)
)
go

create table Contact_ (
	contactId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	accountId decimal(20,0),
	parentContactId decimal(20,0),
	firstName varchar(75) null,
	middleName varchar(75) null,
	lastName varchar(75) null,
	prefixId int,
	suffixId int,
	male int,
	birthday datetime null,
	smsSn varchar(75) null,
	aimSn varchar(75) null,
	icqSn varchar(75) null,
	jabberSn varchar(75) null,
	msnSn varchar(75) null,
	skypeSn varchar(75) null,
	ymSn varchar(75) null,
	employeeStatusId varchar(75) null,
	employeeNumber varchar(75) null,
	jobTitle varchar(100) null,
	jobClass varchar(75) null,
	hoursOfOperation varchar(75) null
)
go

create table Counter (
	name varchar(75) not null primary key,
	currentId decimal(20,0)
)
go

create table Country (
	countryId decimal(20,0) not null primary key,
	name varchar(75) null,
	a2 varchar(75) null,
	a3 varchar(75) null,
	number_ varchar(75) null,
	idd_ varchar(75) null,
	active_ int
)
go

create table CyrusUser (
	userId varchar(75) not null primary key,
	password_ varchar(75) not null
)
go

create table CyrusVirtual (
	emailAddress varchar(75) not null primary key,
	userId varchar(75) not null
)
go

create table DLFileEntry (
	uuid_ varchar(75) null,
	fileEntryId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	versionUserId decimal(20,0),
	versionUserName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	folderId decimal(20,0),
	name varchar(300) null,
	title varchar(300) null,
	description varchar(1000) null,
	version float,
	size_ int,
	readCount int,
	extraSettings text null
)
go

create table DLFileRank (
	fileRankId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	createDate datetime null,
	folderId decimal(20,0),
	name varchar(300) null
)
go

create table DLFileShortcut (
	uuid_ varchar(75) null,
	fileShortcutId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	folderId decimal(20,0),
	toFolderId decimal(20,0),
	toName varchar(300) null
)
go

create table DLFileVersion (
	fileVersionId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	folderId decimal(20,0),
	name varchar(300) null,
	version float,
	size_ int
)
go

create table DLFolder (
	uuid_ varchar(75) null,
	folderId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	parentFolderId decimal(20,0),
	name varchar(100) null,
	description varchar(1000) null,
	lastPostDate datetime null
)
go

create table EmailAddress (
	emailAddressId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	address varchar(75) null,
	typeId int,
	primary_ int
)
go

create table Group_ (
	groupId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	creatorUserId decimal(20,0),
	classNameId decimal(20,0),
	classPK decimal(20,0),
	parentGroupId decimal(20,0),
	liveGroupId decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null,
	type_ int,
	typeSettings varchar(1000) null,
	friendlyURL varchar(100) null,
	active_ int
)
go

create table Groups_Orgs (
	groupId decimal(20,0) not null,
	organizationId decimal(20,0) not null,
	primary key (groupId, organizationId)
)
go

create table Groups_Permissions (
	groupId decimal(20,0) not null,
	permissionId decimal(20,0) not null,
	primary key (groupId, permissionId)
)
go

create table Groups_Roles (
	groupId decimal(20,0) not null,
	roleId decimal(20,0) not null,
	primary key (groupId, roleId)
)
go

create table Groups_UserGroups (
	groupId decimal(20,0) not null,
	userGroupId decimal(20,0) not null,
	primary key (groupId, userGroupId)
)
go

create table IGFolder (
	uuid_ varchar(75) null,
	folderId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	createDate datetime null,
	modifiedDate datetime null,
	parentFolderId decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null
)
go

create table IGImage (
	uuid_ varchar(75) null,
	imageId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	createDate datetime null,
	modifiedDate datetime null,
	folderId decimal(20,0),
	description varchar(1000) null,
	smallImageId decimal(20,0),
	largeImageId decimal(20,0)
)
go

create table Image (
	imageId decimal(20,0) not null primary key,
	modifiedDate datetime null,
	text_ text null,
	type_ varchar(75) null,
	height int,
	width int,
	size_ int
)
go

create table JournalArticle (
	uuid_ varchar(75) null,
	id_ decimal(20,0) not null primary key,
	resourcePrimKey decimal(20,0),
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	articleId varchar(75) null,
	version float,
	title varchar(100) null,
	description varchar(1000) null,
	content text null,
	type_ varchar(75) null,
	structureId varchar(75) null,
	templateId varchar(75) null,
	displayDate datetime null,
	approved int,
	approvedByUserId decimal(20,0),
	approvedByUserName varchar(75) null,
	approvedDate datetime null,
	expired int,
	expirationDate datetime null,
	reviewDate datetime null,
	indexable int,
	smallImage int,
	smallImageId decimal(20,0),
	smallImageURL varchar(75) null
)
go

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

create table JournalStructure (
	uuid_ varchar(75) null,
	id_ decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	structureId varchar(75) null,
	name varchar(75) null,
	description varchar(1000) null,
	xsd text null
)
go

create table JournalTemplate (
	uuid_ varchar(75) null,
	id_ decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	templateId varchar(75) null,
	structureId varchar(75) null,
	name varchar(75) null,
	description varchar(1000) null,
	xsl text null,
	langType varchar(75) null,
	cacheable int,
	smallImage int,
	smallImageId decimal(20,0),
	smallImageURL varchar(75) null
)
go

create table Layout (
	plid decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	privateLayout int,
	layoutId decimal(20,0),
	parentLayoutId decimal(20,0),
	name varchar(1000) null,
	title varchar(1000) null,
	description varchar(1000) null,
	type_ varchar(75) null,
	typeSettings text null,
	hidden_ int,
	friendlyURL varchar(100) null,
	iconImage int,
	iconImageId decimal(20,0),
	themeId varchar(75) null,
	colorSchemeId varchar(75) null,
	wapThemeId varchar(75) null,
	wapColorSchemeId varchar(75) null,
	css varchar(1000) null,
	priority int,
	dlFolderId decimal(20,0)
)
go

create table LayoutSet (
	layoutSetId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	privateLayout int,
	logo int,
	logoId decimal(20,0),
	themeId varchar(75) null,
	colorSchemeId varchar(75) null,
	wapThemeId varchar(75) null,
	wapColorSchemeId varchar(75) null,
	css varchar(75) null,
	pageCount int,
	virtualHost varchar(75) null
)
go

create table ListType (
	listTypeId int not null primary key,
	name varchar(75) null,
	type_ varchar(75) null
)
go

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

create table MBCategory (
	uuid_ varchar(75) null,
	categoryId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	parentCategoryId decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null,
	lastPostDate datetime null
)
go

create table MBDiscussion (
	discussionId decimal(20,0) not null primary key,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	threadId decimal(20,0)
)
go

create table MBMessage (
	uuid_ varchar(75) null,
	messageId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	categoryId decimal(20,0),
	threadId decimal(20,0),
	parentMessageId decimal(20,0),
	subject varchar(75) null,
	body text null,
	attachments int,
	anonymous int
)
go

create table MBMessageFlag (
	messageFlagId decimal(20,0) not null primary key,
	userId decimal(20,0),
	messageId decimal(20,0),
	flag int
)
go

create table MBStatsUser (
	statsUserId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	userId decimal(20,0),
	messageCount int,
	lastPostDate datetime null
)
go

create table MBThread (
	threadId decimal(20,0) not null primary key,
	categoryId decimal(20,0),
	rootMessageId decimal(20,0),
	messageCount int,
	viewCount int,
	lastPostByUserId decimal(20,0),
	lastPostDate datetime null,
	priority float
)
go

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

create table Organization_ (
	organizationId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	parentOrganizationId decimal(20,0),
	name varchar(100) null,
	location int,
	recursable int,
	regionId decimal(20,0),
	countryId decimal(20,0),
	statusId int,
	comments varchar(1000) null
)
go

create table OrgGroupPermission (
	organizationId decimal(20,0) not null,
	groupId decimal(20,0) not null,
	permissionId decimal(20,0) not null,
	primary key (organizationId, groupId, permissionId)
)
go

create table OrgGroupRole (
	organizationId decimal(20,0) not null,
	groupId decimal(20,0) not null,
	roleId decimal(20,0) not null,
	primary key (organizationId, groupId, roleId)
)
go

create table OrgLabor (
	orgLaborId decimal(20,0) not null primary key,
	organizationId decimal(20,0),
	typeId int,
	sunOpen int,
	sunClose int,
	monOpen int,
	monClose int,
	tueOpen int,
	tueClose int,
	wedOpen int,
	wedClose int,
	thuOpen int,
	thuClose int,
	friOpen int,
	friClose int,
	satOpen int,
	satClose int
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

create table PasswordTracker (
	passwordTrackerId decimal(20,0) not null primary key,
	userId decimal(20,0),
	createDate datetime null,
	password_ varchar(75) null
)
go

create table Permission_ (
	permissionId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	actionId varchar(75) null,
	resourceId decimal(20,0)
)
go

create table Phone (
	phoneId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	number_ varchar(75) null,
	extension varchar(75) null,
	typeId int,
	primary_ int
)
go

create table PluginSetting (
	pluginSettingId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	pluginId varchar(75) null,
	pluginType varchar(75) null,
	roles varchar(1000) null,
	active_ int
)
go

create table PollsChoice (
	uuid_ varchar(75) null,
	choiceId decimal(20,0) not null primary key,
	questionId decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null
)
go

create table PollsQuestion (
	uuid_ varchar(75) null,
	questionId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	title varchar(500) null,
	description varchar(1000) null,
	expirationDate datetime null,
	lastVoteDate datetime null
)
go

create table PollsVote (
	voteId decimal(20,0) not null primary key,
	userId decimal(20,0),
	questionId decimal(20,0),
	choiceId decimal(20,0),
	voteDate datetime null
)
go

create table Portlet (
	id_ decimal(20,0) not null primary key,
	companyId decimal(20,0),
	portletId varchar(200) null,
	roles varchar(1000) null,
	active_ int
)
go

create table PortletPreferences (
	portletPreferencesId decimal(20,0) not null primary key,
	ownerId decimal(20,0),
	ownerType int,
	plid decimal(20,0),
	portletId varchar(200) null,
	preferences text null
)
go

create table RatingsEntry (
	entryId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	score float
)
go

create table RatingsStats (
	statsId decimal(20,0) not null primary key,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	totalEntries int,
	totalScore float,
	averageScore float
)
go

create table Region (
	regionId decimal(20,0) not null primary key,
	countryId decimal(20,0),
	regionCode varchar(75) null,
	name varchar(75) null,
	active_ int
)
go

create table Release_ (
	releaseId decimal(20,0) not null primary key,
	createDate datetime null,
	modifiedDate datetime null,
	buildNumber int,
	buildDate datetime null,
	verified int
)
go

create table Resource_ (
	resourceId decimal(20,0) not null primary key,
	codeId decimal(20,0),
	primKey varchar(300) null
)
go

create table ResourceCode (
	codeId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	name varchar(300) null,
	scope int
)
go

create table Role_ (
	roleId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	classNameId decimal(20,0),
	classPK decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null,
	type_ int
)
go

create table Roles_Permissions (
	roleId decimal(20,0) not null,
	permissionId decimal(20,0) not null,
	primary key (roleId, permissionId)
)
go

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
	directDownloadURL varchar(2000) null,
	repoStoreArtifact int
)
go

create table ServiceComponent (
	serviceComponentId decimal(20,0) not null primary key,
	buildNamespace varchar(75) null,
	buildNumber decimal(20,0),
	buildDate decimal(20,0),
	data_ text null
)
go

create table ShoppingCart (
	cartId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	itemIds varchar(1000) null,
	couponCodes varchar(75) null,
	altShipping int,
	insure int
)
go

create table ShoppingCategory (
	categoryId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	parentCategoryId decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null
)
go

create table ShoppingCoupon (
	couponId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	code_ varchar(75) null,
	name varchar(75) null,
	description varchar(1000) null,
	startDate datetime null,
	endDate datetime null,
	active_ int,
	limitCategories varchar(1000) null,
	limitSkus varchar(1000) null,
	minOrder float,
	discount float,
	discountType varchar(75) null
)
go

create table ShoppingItem (
	itemId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	categoryId decimal(20,0),
	sku varchar(75) null,
	name varchar(200) null,
	description varchar(1000) null,
	properties varchar(1000) null,
	fields_ int,
	fieldsQuantities varchar(1000) null,
	minQuantity int,
	maxQuantity int,
	price float,
	discount float,
	taxable int,
	shipping float,
	useShippingFormula int,
	requiresShipping int,
	stockQuantity int,
	featured_ int,
	sale_ int,
	smallImage int,
	smallImageId decimal(20,0),
	smallImageURL varchar(75) null,
	mediumImage int,
	mediumImageId decimal(20,0),
	mediumImageURL varchar(75) null,
	largeImage int,
	largeImageId decimal(20,0),
	largeImageURL varchar(75) null
)
go

create table ShoppingItemField (
	itemFieldId decimal(20,0) not null primary key,
	itemId decimal(20,0),
	name varchar(75) null,
	values_ varchar(1000) null,
	description varchar(1000) null
)
go

create table ShoppingItemPrice (
	itemPriceId decimal(20,0) not null primary key,
	itemId decimal(20,0),
	minQuantity int,
	maxQuantity int,
	price float,
	discount float,
	taxable int,
	shipping float,
	useShippingFormula int,
	status int
)
go

create table ShoppingOrder (
	orderId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	number_ varchar(75) null,
	tax float,
	shipping float,
	altShipping varchar(75) null,
	requiresShipping int,
	insure int,
	insurance float,
	couponCodes varchar(75) null,
	couponDiscount float,
	billingFirstName varchar(75) null,
	billingLastName varchar(75) null,
	billingEmailAddress varchar(75) null,
	billingCompany varchar(75) null,
	billingStreet varchar(75) null,
	billingCity varchar(75) null,
	billingState varchar(75) null,
	billingZip varchar(75) null,
	billingCountry varchar(75) null,
	billingPhone varchar(75) null,
	shipToBilling int,
	shippingFirstName varchar(75) null,
	shippingLastName varchar(75) null,
	shippingEmailAddress varchar(75) null,
	shippingCompany varchar(75) null,
	shippingStreet varchar(75) null,
	shippingCity varchar(75) null,
	shippingState varchar(75) null,
	shippingZip varchar(75) null,
	shippingCountry varchar(75) null,
	shippingPhone varchar(75) null,
	ccName varchar(75) null,
	ccType varchar(75) null,
	ccNumber varchar(75) null,
	ccExpMonth int,
	ccExpYear int,
	ccVerNumber varchar(75) null,
	comments varchar(1000) null,
	ppTxnId varchar(75) null,
	ppPaymentStatus varchar(75) null,
	ppPaymentGross float,
	ppReceiverEmail varchar(75) null,
	ppPayerEmail varchar(75) null,
	sendOrderEmail int,
	sendShippingEmail int
)
go

create table ShoppingOrderItem (
	orderItemId decimal(20,0) not null primary key,
	orderId decimal(20,0),
	itemId varchar(75) null,
	sku varchar(75) null,
	name varchar(200) null,
	description varchar(1000) null,
	properties varchar(1000) null,
	price float,
	quantity int,
	shippedDate datetime null
)
go

create table Subscription (
	subscriptionId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	frequency varchar(75) null
)
go

create table TagsAsset (
	assetId decimal(20,0) not null primary key,
	groupId decimal(20,0),
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
	width int,
	priority float,
	viewCount int
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

create table User_ (
	uuid_ varchar(75) null,
	userId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	createDate datetime null,
	modifiedDate datetime null,
	defaultUser int,
	contactId decimal(20,0),
	password_ varchar(75) null,
	passwordEncrypted int,
	passwordReset int,
	passwordModifiedDate datetime null,
	graceLoginCount int,
	screenName varchar(75) null,
	emailAddress varchar(75) null,
	portraitId decimal(20,0),
	languageId varchar(75) null,
	timeZoneId varchar(75) null,
	greeting varchar(75) null,
	comments varchar(1000) null,
	loginDate datetime null,
	loginIP varchar(75) null,
	lastLoginDate datetime null,
	lastLoginIP varchar(75) null,
	lastFailedLoginDate datetime null,
	failedLoginAttempts int,
	lockout int,
	lockoutDate datetime null,
	agreedToTermsOfUse int,
	active_ int
)
go

create table UserGroup (
	userGroupId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	parentUserGroupId decimal(20,0),
	name varchar(75) null,
	description varchar(1000) null
)
go

create table UserGroupRole (
	userId decimal(20,0) not null,
	groupId decimal(20,0) not null,
	roleId decimal(20,0) not null,
	primary key (userId, groupId, roleId)
)
go

create table UserIdMapper (
	userIdMapperId decimal(20,0) not null primary key,
	userId decimal(20,0),
	type_ varchar(75) null,
	description varchar(75) null,
	externalUserId varchar(75) null
)
go

create table Users_Groups (
	userId decimal(20,0) not null,
	groupId decimal(20,0) not null,
	primary key (userId, groupId)
)
go

create table Users_Orgs (
	userId decimal(20,0) not null,
	organizationId decimal(20,0) not null,
	primary key (userId, organizationId)
)
go

create table Users_Permissions (
	userId decimal(20,0) not null,
	permissionId decimal(20,0) not null,
	primary key (userId, permissionId)
)
go

create table Users_Roles (
	userId decimal(20,0) not null,
	roleId decimal(20,0) not null,
	primary key (userId, roleId)
)
go

create table Users_UserGroups (
	userId decimal(20,0) not null,
	userGroupId decimal(20,0) not null,
	primary key (userId, userGroupId)
)
go

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

create table UserTrackerPath (
	userTrackerPathId decimal(20,0) not null primary key,
	userTrackerId decimal(20,0),
	path_ varchar(1000) null,
	pathDate datetime null
)
go

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

create table Website (
	websiteId decimal(20,0) not null primary key,
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	classNameId decimal(20,0),
	classPK decimal(20,0),
	url varchar(1000) null,
	typeId int,
	primary_ int
)
go

create table WikiNode (
	uuid_ varchar(75) null,
	nodeId decimal(20,0) not null primary key,
	groupId decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	modifiedDate datetime null,
	name varchar(75) null,
	description varchar(1000) null,
	lastPostDate datetime null
)
go

create table WikiPage (
	uuid_ varchar(75) null,
	pageId decimal(20,0) not null primary key,
	resourcePrimKey decimal(20,0),
	companyId decimal(20,0),
	userId decimal(20,0),
	userName varchar(75) null,
	createDate datetime null,
	nodeId decimal(20,0),
	title varchar(75) null,
	version float,
	content text null,
	format varchar(75) null,
	head int
)
go

create table WikiPageResource (
	resourcePrimKey decimal(20,0) not null primary key,
	nodeId decimal(20,0),
	title varchar(75) null
)
go



insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (1, 'Canada', 'CA', 'CAN', '124', '001', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (2, 'China', 'CN', 'CHN', '156', '086', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (3, 'France', 'FR', 'FRA', '250', '033', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (4, 'Germany', 'DE', 'DEU', '276', '049', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (5, 'Hong Kong', 'HK', 'HKG', '344', '852', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (6, 'Hungary', 'HU', 'HUN', '348', '036', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (7, 'Israel', 'IL', 'ISR', '376', '972', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (8, 'Italy', 'IT', 'ITA', '380', '039', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (9, 'Japan', 'JP', 'JPN', '392', '081', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (10, 'South Korea', 'KP', 'KOR', '410', '082', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (11, 'Netherlands', 'NL', 'NLD', '528', '031', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (12, 'Portugal', 'PT', 'PRT', '620', '351', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (13, 'Russia', 'RU', 'RUS', '643', '007', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (14, 'Singapore', 'SG', 'SGP', '702', '065', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (15, 'Spain', 'ES', 'ESP', '724', '034', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (16, 'Turkey', 'TR', 'TUR', '792', '090', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (17, 'Vietnam', 'VM', 'VNM', '704', '084', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (18, 'United Kingdom', 'GB', 'GBR', '826', '044', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (19, 'United States', 'US', 'USA', '840', '001', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (20, 'Afghanistan', 'AF', 'AFG', '4', '093', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (21, 'Albania', 'AL', 'ALB', '8', '355', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (22, 'Algeria', 'DZ', 'DZA', '12', '213', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (23, 'American Samoa', 'AS', 'ASM', '16', '684', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (24, 'Andorra', 'AD', 'AND', '20', '376', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (25, 'Angola', 'AO', 'AGO', '24', '244', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (26, 'Anguilla', 'AI', 'AIA', '660', '264', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (27, 'Antarctica', 'AQ', 'ATA', '10', '672', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (28, 'Antigua', 'AG', 'ATG', '28', '268', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (29, 'Argentina', 'AR', 'ARG', '32', '054', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (30, 'Armenia', 'AM', 'ARM', '51', '374', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (31, 'Aruba', 'AW', 'ABW', '533', '297', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (32, 'Australia', 'AU', 'AUS', '36', '061', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (33, 'Austria', 'AT', 'AUT', '40', '043', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (34, 'Azerbaijan', 'AZ', 'AZE', '31', '994', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (35, 'Bahamas', 'BS', 'BHS', '44', '242', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (36, 'Bahrain', 'BH', 'BHR', '48', '973', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (37, 'Bangladesh', 'BD', 'BGD', '50', '880', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (38, 'Barbados', 'BB', 'BRB', '52', '246', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (39, 'Belarus', 'BY', 'BLR', '112', '375', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (40, 'Belgium', 'BE', 'BEL', '56', '032', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (41, 'Belize', 'BZ', 'BLZ', '84', '501', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (42, 'Benin', 'BJ', 'BEN', '204', '229', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (43, 'Bermuda', 'BM', 'BMU', '60', '441', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (44, 'Bhutan', 'BT', 'BTN', '64', '975', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (45, 'Bolivia', 'BO', 'BOL', '68', '591', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (46, 'Bosnia-Herzegovina', 'BA', 'BIH', '70', '387', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (47, 'Botswana', 'BW', 'BWA', '72', '267', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (48, 'Brazil', 'BR', 'BRA', '76', '055', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (49, 'British Virgin Islands', 'VG', 'VGB', '92', '284', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (50, 'Brunei', 'BN', 'BRN', '96', '673', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (51, 'Bulgaria', 'BG', 'BGR', '100', '359', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (52, 'Burkina Faso', 'BF', 'BFA', '854', '226', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (53, 'Burma (Myanmar)', 'MM', 'MMR', '104', '095', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (54, 'Burundi', 'BI', 'BDI', '108', '257', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (55, 'Cambodia', 'KH', 'KHM', '116', '855', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (56, 'Cameroon', 'CM', 'CMR', '120', '237', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (57, 'Cape Verde Island', 'CV', 'CPV', '132', '238', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (58, 'Cayman Islands', 'KY', 'CYM', '136', '345', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (59, 'Central African Republic', 'CF', 'CAF', '140', '236', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (60, 'Chad', 'TD', 'TCD', '148', '235', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (61, 'Chile', 'CL', 'CHL', '152', '056', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (62, 'Christmas Island', 'CX', 'CXR', '162', '061', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (63, 'Cocos Islands', 'CC', 'CCK', '166', '061', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (64, 'Colombia', 'CO', 'COL', '170', '057', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (65, 'Comoros', 'KM', 'COM', '174', '269', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (66, 'Republic of Congo', 'CD', 'COD', '180', '242', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (67, 'Democratic Republic of Congo', 'CG', 'COG', '178', '243', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (68, 'Cook Islands', 'CK', 'COK', '184', '682', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (69, 'Costa Rica', 'CI', 'CRI', '188', '506', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (70, 'Croatia', 'HR', 'HRV', '191', '385', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (71, 'Cuba', 'CU', 'CUB', '192', '053', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (72, 'Cyprus', 'CY', 'CYP', '196', '357', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (73, 'Czech Republic', 'CZ', 'CZE', '203', '420', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (74, 'Denmark', 'DK', 'DNK', '208', '045', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (75, 'Djibouti', 'DJ', 'DJI', '262', '253', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (76, 'Dominica', 'DM', 'DMA', '212', '767', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (77, 'Dominican Republic', 'DO', 'DOM', '214', '809', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (78, 'Ecuador', 'EC', 'ECU', '218', '593', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (79, 'Egypt', 'EG', 'EGY', '818', '020', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (80, 'El Salvador', 'SV', 'SLV', '222', '503', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (81, 'Equatorial Guinea', 'GQ', 'GNQ', '226', '240', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (82, 'Eritrea', 'ER', 'ERI', '232', '291', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (83, 'Estonia', 'EE', 'EST', '233', '372', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (84, 'Ethiopia', 'ET', 'ETH', '231', '251', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (85, 'Faeroe Islands', 'FO', 'FRO', '234', '298', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (86, 'Falkland Islands', 'FK', 'FLK', '238', '500', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (87, 'Fiji Islands', 'FJ', 'FJI', '242', '679', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (88, 'Finland', 'FI', 'FIN', '246', '358', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (89, 'French Guiana', 'GF', 'GUF', '254', '594', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (90, 'French Polynesia', 'PF', 'PYF', '258', '689', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (91, 'Gabon', 'GA', 'GAB', '266', '241', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (92, 'Gambia', 'GM', 'GMB', '270', '220', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (93, 'Georgia', 'GE', 'GEO', '268', '995', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (94, 'Ghana', 'GH', 'GHA', '288', '233', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (95, 'Gibraltar', 'GI', 'GIB', '292', '350', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (96, 'Greece', 'GR', 'GRC', '300', '030', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (97, 'Greenland', 'GL', 'GRL', '304', '299', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (98, 'Grenada', 'GD', 'GRD', '308', '473', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (99, 'Guadeloupe', 'GP', 'GLP', '312', '590', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (100, 'Guam', 'GU', 'GUM', '316', '671', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (101, 'Guatemala', 'GT', 'GTM', '320', '502', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (102, 'Guinea', 'GN', 'GIN', '324', '224', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (103, 'Guinea-Bissau', 'GW', 'GNB', '624', '245', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (104, 'Guyana', 'GY', 'GUY', '328', '592', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (105, 'Haiti', 'HT', 'HTI', '332', '509', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (106, 'Honduras', 'HN', 'HND', '340', '504', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (107, 'Iceland', 'IS', 'ISL', '352', '354', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (108, 'India', 'IN', 'IND', '356', '091', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (109, 'Indonesia', 'ID', 'IDN', '360', '062', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (110, 'Iran', 'IR', 'IRN', '364', '098', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (111, 'Iraq', 'IQ', 'IRQ', '368', '964', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (112, 'Ireland', 'IE', 'IRL', '372', '353', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (113, 'Ivory Coast', 'CI', 'CIV', '384', '225', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (114, 'Jamaica', 'JM', 'JAM', '388', '876', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (115, 'Jordan', 'JO', 'JOR', '400', '962', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (116, 'Kazakhstan', 'KZ', 'KAZ', '398', '007', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (117, 'Kenya', 'KE', 'KEN', '404', '254', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (118, 'Kiribati', 'KI', 'KIR', '408', '686', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (119, 'Kuwait', 'KW', 'KWT', '414', '965', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (120, 'North Korea', 'KP', 'PRK', '408', '850', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (121, 'Kyrgyzstan', 'KG', 'KGZ', '471', '996', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (122, 'Laos', 'LA', 'LAO', '418', '856', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (123, 'Latvia', 'LV', 'LVA', '428', '371', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (124, 'Lebanon', 'LB', 'LBN', '422', '961', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (125, 'Lesotho', 'LS', 'LSO', '426', '266', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (126, 'Liberia', 'LR', 'LBR', '430', '231', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (127, 'Libya', 'LY', 'LBY', '434', '218', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (128, 'Liechtenstein', 'LI', 'LIE', '438', '423', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (129, 'Lithuania', 'LT', 'LTU', '440', '370', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (130, 'Luxembourg', 'LU', 'LUX', '442', '352', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (131, 'Macau', 'MO', 'MAC', '446', '853', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (132, 'Macedonia', 'MK', 'MKD', '807', '389', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (133, 'Madagascar', 'MG', 'MDG', '450', '261', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (134, 'Malawi', 'MW', 'MWI', '454', '265', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (135, 'Malaysia', 'MY', 'MYS', '458', '060', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (136, 'Maldives', 'MV', 'MDV', '462', '960', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (137, 'Mali', 'ML', 'MLI', '466', '223', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (138, 'Malta', 'MT', 'MLT', '470', '356', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (139, 'Marshall Islands', 'MH', 'MHL', '584', '692', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (140, 'Martinique', 'MQ', 'MTQ', '474', '596', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (141, 'Mauritania', 'MR', 'MRT', '478', '222', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (142, 'Mauritius', 'MU', 'MUS', '480', '230', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (143, 'Mayotte Island', 'YT', 'MYT', '175', '269', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (144, 'Mexico', 'MX', 'MEX', '484', '052', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (145, 'Micronesia', 'FM', 'FSM', '583', '691', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (146, 'Moldova', 'MD', 'MDA', '498', '373', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (147, 'Monaco', 'MC', 'MCO', '492', '377', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (148, 'Mongolia', 'MN', 'MNG', '496', '976', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (149, 'Montserrat', 'MS', 'MSR', '500', '664', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (150, 'Morocco', 'MA', 'MAR', '504', '212', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (151, 'Mozambique', 'MZ', 'MOZ', '508', '258', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (152, 'Myanmar (Burma)', 'MM', 'MMR', '104', '095', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (153, 'Namibia', 'NA', 'NAM', '516', '264', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (154, 'Nauru', 'NR', 'NRU', '520', '674', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (155, 'Nepal', 'NP', 'NPL', '524', '977', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (156, 'Netherlands Antilles', 'AN', 'ANT', '530', '599', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (157, 'New Caledonia', 'NC', 'NCL', '540', '687', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (158, 'New Zealand', 'NZ', 'NZL', '554', '064', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (159, 'Nicaragua', 'NE', 'NER', '558', '505', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (160, 'Niger', 'NE', 'NER', '562', '227', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (161, 'Nigeria', 'NG', 'NGA', '566', '234', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (162, 'Niue', 'NU', 'NIU', '570', '683', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (163, 'Norfolk Island', 'NF', 'NFK', '574', '672', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (164, 'Norway', 'NO', 'NOR', '578', '047', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (165, 'Oman', 'OM', 'OMN', '512', '968', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (166, 'Pakistan', 'PK', 'PAK', '586', '092', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (167, 'Palau', 'PW', 'PLW', '585', '680', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (168, 'Palestine', 'PS', 'PSE', '275', '970', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (169, 'Panama', 'PA', 'PAN', '591', '507', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (170, 'Papua New Guinea', 'PG', 'PNG', '598', '675', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (171, 'Paraguay', 'PY', 'PRY', '600', '595', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (172, 'Peru', 'PE', 'PER', '604', '051', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (173, 'Philippines', 'PH', 'PHL', '608', '063', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (174, 'Poland', 'PL', 'POL', '616', '048', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (175, 'Puerto Rico', 'PR', 'PRI', '630', '787', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (176, 'Qatar', 'QA', 'QAT', '634', '974', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (177, 'Reunion Island', 'RE', 'REU', '638', '262', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (178, 'Romania', 'RO', 'ROU', '642', '040', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (179, 'Rwanda', 'RW', 'RWA', '646', '250', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (180, 'St. Helena', 'SH', 'SHN', '654', '290', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (181, 'St. Kitts', 'KN', 'KNA', '659', '869', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (182, 'St. Lucia', 'LC', 'LCA', '662', '758', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (183, 'St. Pierre & Miquelon', 'PM', 'SPM', '666', '508', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (184, 'St. Vincent', 'VC', 'VCT', '670', '784', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (185, 'San Marino', 'SM', 'SMR', '674', '378', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (186, 'Sao Tome & Principe', 'ST', 'STP', '678', '239', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (187, 'Saudi Arabia', 'SA', 'SAU', '682', '966', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (188, 'Senegal', 'SN', 'SEN', '686', '221', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (189, 'Serbia', 'CS', 'SCG', '891', '381', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (190, 'Seychelles', 'SC', 'SYC', '690', '248', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (191, 'Sierra Leone', 'SL', 'SLE', '694', '249', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (192, 'Slovakia', 'SK', 'SVK', '703', '421', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (193, 'Slovenia', 'SI', 'SVN', '705', '386', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (194, 'Solomon Islands', 'SB', 'SLB', '90', '677', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (195, 'Somalia', 'SO', 'SOM', '706', '252', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (196, 'South Africa', 'ZA', 'ZAF', '710', '027', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (197, 'Sri Lanka', 'LK', 'LKA', '144', '094', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (198, 'Sudan', 'SD', 'SDN', '736', '095', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (199, 'Suriname', 'SR', 'SUR', '740', '597', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (200, 'Swaziland', 'SZ', 'SWZ', '748', '268', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (201, 'Sweden', 'SE', 'SWE', '752', '046', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (202, 'Switzerland', 'CH', 'CHE', '756', '041', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (203, 'Syria', 'SY', 'SYR', '760', '963', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (204, 'Taiwan', 'TW', 'TWN', '158', '886', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (205, 'Tajikistan', 'TJ', 'TJK', '762', '992', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (206, 'Tanzania', 'TZ', 'TZA', '834', '255', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (207, 'Thailand', 'TH', 'THA', '764', '066', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (208, 'Togo', 'TG', 'TGO', '768', '228', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (209, 'Tonga', 'TO', 'TON', '776', '676', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (210, 'Trinidad & Tobago', 'TT', 'TTO', '780', '868', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (211, 'Tunisia', 'TN', 'TUN', '788', '216', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (212, 'Turkmenistan', 'TM', 'TKM', '795', '993', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (213, 'Turks & Caicos', 'TC', 'TCA', '796', '649', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (214, 'Tuvalu', 'TV', 'TUV', '798', '688', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (215, 'Uganda', 'UG', 'UGA', '800', '256', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (216, 'Ukraine', 'UA', 'UKR', '804', '380', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (217, 'United Arab Emirates', 'AE', 'ARE', '784', '971', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (218, 'Uruguay', 'UY', 'URY', '858', '598', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (219, 'Uzbekistan', 'UZ', 'UZB', '860', '998', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (220, 'Vanuatu', 'VU', 'VUT', '548', '678', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (221, 'Vatican City', 'VA', 'VAT', '336', '039', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (222, 'Venezuela', 'VE', 'VEN', '862', '058', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (223, 'Wallis & Futuna', 'WF', 'WLF', '876', '681', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (224, 'Western Samoa', 'EH', 'ESH', '732', '685', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (225, 'Yemen', 'YE', 'YEM', '887', '967', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (226, 'Yugoslavia', 'MK', 'MKD', '446', '381', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (227, 'Zambia', 'ZM', 'ZMB', '894', '260', 1)
go
insert into Country (countryId, name, a2, a3, number_, idd_, active_) values (228, 'Zimbabwe', 'ZW', 'ZWE', '716', '263', 1)
go

insert into Region (regionId, countryId, regionCode, name, active_) values (1, 19, 'AL', 'Alabama', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (2, 19, 'AK', 'Alaska', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (3, 19, 'AZ', 'Arizona', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (4, 19, 'AR', 'Arkansas', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (5, 19, 'CA', 'California', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (6, 19, 'CO', 'Colorado', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (7, 19, 'CT', 'Connecticut', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (8, 19, 'DC', 'District of Columbia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (9, 19, 'DE', 'Delaware', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (10, 19, 'FL', 'Florida', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (11, 19, 'GA', 'Georgia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (12, 19, 'HI', 'Hawaii', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (13, 19, 'ID', 'Idaho', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (14, 19, 'IL', 'Illinois', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (15, 19, 'IN', 'Indiana', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (16, 19, 'IA', 'Iowa', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (17, 19, 'KS', 'Kansas', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (18, 19, 'KY', 'Kentucky ', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (19, 19, 'LA', 'Louisiana ', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (20, 19, 'ME', 'Maine', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (21, 19, 'MD', 'Maryland', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (22, 19, 'MA', 'Massachusetts', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (23, 19, 'MI', 'Michigan', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (24, 19, 'MN', 'Minnesota', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (25, 19, 'MS', 'Mississippi', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (26, 19, 'MO', 'Missouri', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (27, 19, 'MT', 'Montana', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (28, 19, 'NE', 'Nebraska', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (29, 19, 'NV', 'Nevada', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (30, 19, 'NH', 'New Hampshire', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (31, 19, 'NJ', 'New Jersey', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (32, 19, 'NM', 'New Mexico', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (33, 19, 'NY', 'New York', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (34, 19, 'NC', 'North Carolina', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (35, 19, 'ND', 'North Dakota', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (36, 19, 'OH', 'Ohio', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (37, 19, 'OK', 'Oklahoma ', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (38, 19, 'OR', 'Oregon', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (39, 19, 'PA', 'Pennsylvania', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (40, 19, 'PR', 'Puerto Rico', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (41, 19, 'RI', 'Rhode Island', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (42, 19, 'SC', 'South Carolina', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (43, 19, 'SD', 'South Dakota', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (44, 19, 'TN', 'Tennessee', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (45, 19, 'TX', 'Texas', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (46, 19, 'UT', 'Utah', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (47, 19, 'VT', 'Vermont', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (48, 19, 'VA', 'Virginia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (49, 19, 'WA', 'Washington', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (50, 19, 'WV', 'West Virginia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (51, 19, 'WI', 'Wisconsin', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (52, 19, 'WY', 'Wyoming', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (53, 1, 'AL', 'Alberta', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (54, 1, 'BC', 'British Columbia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (55, 1, 'MB', 'Manitoba', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (56, 1, 'NB', 'New Brunswick', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (57, 1, 'NL', 'Newfoundland and Labrador', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (58, 1, 'NT', 'Northwest Territories', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (59, 1, 'NS', 'Nova Scotia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (60, 1, 'NU', 'Nunavut', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (61, 1, 'ON', 'Ontario', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (62, 1, 'PE', 'Prince Edward Island', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (63, 1, 'QC', 'Quebec', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (64, 1, 'SK', 'Saskatchewan', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (65, 1, 'YT', 'Yukon', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (66, 15, 'AN', 'Andalusia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (67, 15, 'AR', 'Aragon', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (68, 15, 'AS', 'Asturias', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (69, 15, 'IB', 'Balearic Islands', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (70, 15, 'PV', 'Basque Country', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (71, 15, 'CN', 'Canary Islands', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (72, 15, 'CB', 'Cantabria', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (73, 15, 'CL', 'Castile and Leon', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (74, 15, 'CM', 'Castile-La Mancha', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (75, 15, 'CT', 'Catalonia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (76, 15, 'CE', 'Ceuta', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (77, 15, 'EX', 'Extremadura', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (78, 15, 'GA', 'Galicia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (79, 15, 'LO', 'La Rioja', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (80, 15, 'M', 'Madrid', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (81, 15, 'ML', 'Melilla', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (82, 15, 'MU', 'Murcia', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (83, 15, 'NA', 'Navarra', 1)
go
insert into Region (regionId, countryId, regionCode, name, active_) values (84, 15, 'VC', 'Valencia', 1)
go

--
-- List types for accounts
--

insert into ListType (listTypeId, name, type_) values (10000, 'Billing', 'com.liferay.portal.model.Account.address')
go
insert into ListType (listTypeId, name, type_) values (10001, 'Other', 'com.liferay.portal.model.Account.address')
go
insert into ListType (listTypeId, name, type_) values (10002, 'P.O. Box', 'com.liferay.portal.model.Account.address')
go
insert into ListType (listTypeId, name, type_) values (10003, 'Shipping', 'com.liferay.portal.model.Account.address')
go

insert into ListType (listTypeId, name, type_) values (10004, 'E-mail', 'com.liferay.portal.model.Account.emailAddress')
go
insert into ListType (listTypeId, name, type_) values (10005, 'E-mail 2', 'com.liferay.portal.model.Account.emailAddress')
go
insert into ListType (listTypeId, name, type_) values (10006, 'E-mail 3', 'com.liferay.portal.model.Account.emailAddress')
go

insert into ListType (listTypeId, name, type_) values (10007, 'Fax', 'com.liferay.portal.model.Account.phone')
go
insert into ListType (listTypeId, name, type_) values (10008, 'Local', 'com.liferay.portal.model.Account.phone')
go
insert into ListType (listTypeId, name, type_) values (10009, 'Other', 'com.liferay.portal.model.Account.phone')
go
insert into ListType (listTypeId, name, type_) values (10010, 'Toll-Free', 'com.liferay.portal.model.Account.phone')
go
insert into ListType (listTypeId, name, type_) values (10011, 'TTY', 'com.liferay.portal.model.Account.phone')
go

insert into ListType (listTypeId, name, type_) values (10012, 'Intranet', 'com.liferay.portal.model.Account.website')
go
insert into ListType (listTypeId, name, type_) values (10013, 'Public', 'com.liferay.portal.model.Account.website')
go

--
-- List types for contacts
--

insert into ListType (listTypeId, name, type_) values (11000, 'Business', 'com.liferay.portal.model.Contact.address')
go
insert into ListType (listTypeId, name, type_) values (11001, 'Other', 'com.liferay.portal.model.Contact.address')
go
insert into ListType (listTypeId, name, type_) values (11002, 'Personal', 'com.liferay.portal.model.Contact.address')
go

insert into ListType (listTypeId, name, type_) values (11003, 'E-mail', 'com.liferay.portal.model.Contact.emailAddress')
go
insert into ListType (listTypeId, name, type_) values (11004, 'E-mail 2', 'com.liferay.portal.model.Contact.emailAddress')
go
insert into ListType (listTypeId, name, type_) values (11005, 'E-mail 3', 'com.liferay.portal.model.Contact.emailAddress')
go

insert into ListType (listTypeId, name, type_) values (11006, 'Business', 'com.liferay.portal.model.Contact.phone')
go
insert into ListType (listTypeId, name, type_) values (11007, 'Business Fax', 'com.liferay.portal.model.Contact.phone')
go
insert into ListType (listTypeId, name, type_) values (11008, 'Mobile', 'com.liferay.portal.model.Contact.phone')
go
insert into ListType (listTypeId, name, type_) values (11009, 'Other', 'com.liferay.portal.model.Contact.phone')
go
insert into ListType (listTypeId, name, type_) values (11010, 'Pager', 'com.liferay.portal.model.Contact.phone')
go
insert into ListType (listTypeId, name, type_) values (11011, 'Personal', 'com.liferay.portal.model.Contact.phone')
go
insert into ListType (listTypeId, name, type_) values (11012, 'Personal Fax', 'com.liferay.portal.model.Contact.phone')
go
insert into ListType (listTypeId, name, type_) values (11013, 'TTY', 'com.liferay.portal.model.Contact.phone')
go

insert into ListType (listTypeId, name, type_) values (11014, 'Dr.', 'com.liferay.portal.model.Contact.prefix')
go
insert into ListType (listTypeId, name, type_) values (11015, 'Mr.', 'com.liferay.portal.model.Contact.prefix')
go
insert into ListType (listTypeId, name, type_) values (11016, 'Mrs.', 'com.liferay.portal.model.Contact.prefix')
go
insert into ListType (listTypeId, name, type_) values (11017, 'Ms.', 'com.liferay.portal.model.Contact.prefix')
go

insert into ListType (listTypeId, name, type_) values (11020, 'II', 'com.liferay.portal.model.Contact.suffix')
go
insert into ListType (listTypeId, name, type_) values (11021, 'III', 'com.liferay.portal.model.Contact.suffix')
go
insert into ListType (listTypeId, name, type_) values (11022, 'IV', 'com.liferay.portal.model.Contact.suffix')
go
insert into ListType (listTypeId, name, type_) values (11023, 'Jr.', 'com.liferay.portal.model.Contact.suffix')
go
insert into ListType (listTypeId, name, type_) values (11024, 'PhD.', 'com.liferay.portal.model.Contact.suffix')
go
insert into ListType (listTypeId, name, type_) values (11025, 'Sr.', 'com.liferay.portal.model.Contact.suffix')
go

insert into ListType (listTypeId, name, type_) values (11026, 'Blog', 'com.liferay.portal.model.Contact.website')
go
insert into ListType (listTypeId, name, type_) values (11027, 'Business', 'com.liferay.portal.model.Contact.website')
go
insert into ListType (listTypeId, name, type_) values (11028, 'Other', 'com.liferay.portal.model.Contact.website')
go
insert into ListType (listTypeId, name, type_) values (11029, 'Personal', 'com.liferay.portal.model.Contact.website')
go

--
-- List types for organizations
--

insert into ListType (listTypeId, name, type_) values (12000, 'Billing', 'com.liferay.portal.model.Organization.address')
go
insert into ListType (listTypeId, name, type_) values (12001, 'Other', 'com.liferay.portal.model.Organization.address')
go
insert into ListType (listTypeId, name, type_) values (12002, 'P.O. Box', 'com.liferay.portal.model.Organization.address')
go
insert into ListType (listTypeId, name, type_) values (12003, 'Shipping', 'com.liferay.portal.model.Organization.address')
go

insert into ListType (listTypeId, name, type_) values (12004, 'E-mail', 'com.liferay.portal.model.Organization.emailAddress')
go
insert into ListType (listTypeId, name, type_) values (12005, 'E-mail 2', 'com.liferay.portal.model.Organization.emailAddress')
go
insert into ListType (listTypeId, name, type_) values (12006, 'E-mail 3', 'com.liferay.portal.model.Organization.emailAddress')
go

insert into ListType (listTypeId, name, type_) values (12007, 'Fax', 'com.liferay.portal.model.Organization.phone')
go
insert into ListType (listTypeId, name, type_) values (12008, 'Local', 'com.liferay.portal.model.Organization.phone')
go
insert into ListType (listTypeId, name, type_) values (12009, 'Other', 'com.liferay.portal.model.Organization.phone')
go
insert into ListType (listTypeId, name, type_) values (12010, 'Toll-Free', 'com.liferay.portal.model.Organization.phone')
go
insert into ListType (listTypeId, name, type_) values (12011, 'TTY', 'com.liferay.portal.model.Organization.phone')
go

insert into ListType (listTypeId, name, type_) values (12012, 'Administrative', 'com.liferay.portal.model.Organization.service')
go
insert into ListType (listTypeId, name, type_) values (12013, 'Contracts', 'com.liferay.portal.model.Organization.service')
go
insert into ListType (listTypeId, name, type_) values (12014, 'Donation', 'com.liferay.portal.model.Organization.service')
go
insert into ListType (listTypeId, name, type_) values (12015, 'Retail', 'com.liferay.portal.model.Organization.service')
go
insert into ListType (listTypeId, name, type_) values (12016, 'Training', 'com.liferay.portal.model.Organization.service')
go

insert into ListType (listTypeId, name, type_) values (12017, 'Full Member', 'com.liferay.portal.model.Organization.status')
go
insert into ListType (listTypeId, name, type_) values (12018, 'Provisional Member', 'com.liferay.portal.model.Organization.status')
go

insert into ListType (listTypeId, name, type_) values (12019, 'Intranet', 'com.liferay.portal.model.Organization.website')
go
insert into ListType (listTypeId, name, type_) values (12020, 'Public', 'com.liferay.portal.model.Organization.website')
go


insert into Counter values ('com.liferay.counter.model.Counter', 10000)
go


insert into Release_ (releaseId, createDate, modifiedDate, buildNumber, verified) values (1, getdate(), getdate(), 4401, 0)
go


go


create index IX_125EE7A4 on ActivityTracker (classNameId, classPK)
go
create index IX_57B7CA39 on ActivityTracker (companyId)
go
create index IX_8EEF8AFB on ActivityTracker (groupId)
go
create index IX_A9E541D8 on ActivityTracker (receiverUserId)
go
create index IX_B57EB3C9 on ActivityTracker (userId)
go

create index IX_93D5AD4E on Address (companyId)
go
create index IX_ABD7DAC0 on Address (companyId, classNameId)
go
create index IX_71CB1123 on Address (companyId, classNameId, classPK)
go
create index IX_5BC8B0D4 on Address (userId)
go

create index IX_72EF6041 on BlogsEntry (companyId)
go
create index IX_8CACE77B on BlogsEntry (companyId, userId)
go
create index IX_81A50303 on BlogsEntry (groupId)
go
create index IX_DB780A20 on BlogsEntry (groupId, urlTitle)
go
create index IX_C07CA83D on BlogsEntry (groupId, userId)
go
create index IX_69157A4D on BlogsEntry (uuid_)
go
create index IX_1B1040FD on BlogsEntry (uuid_, groupId)
go

create index IX_90CDA39A on BlogsStatsUser (companyId, entryCount)
go
create index IX_43840EEB on BlogsStatsUser (groupId)
go
create index IX_28C78D5C on BlogsStatsUser (groupId, entryCount)
go
create index IX_82254C25 on BlogsStatsUser (groupId, userId)
go
create index IX_BB51F1D9 on BlogsStatsUser (userId)
go

create index IX_443BDC38 on BookmarksEntry (folderId)
go
create index IX_B670BA39 on BookmarksEntry (uuid_)
go

create index IX_2ABA25D7 on BookmarksFolder (companyId)
go
create index IX_7F703619 on BookmarksFolder (groupId)
go
create index IX_967799C0 on BookmarksFolder (groupId, parentFolderId)
go
create index IX_451E7AE3 on BookmarksFolder (uuid_)
go
create index IX_DC2F8927 on BookmarksFolder (uuid_, groupId)
go

create index IX_12EE4898 on CalEvent (groupId)
go
create index IX_FCD7C63D on CalEvent (groupId, type_)
go
create index IX_C1AD2122 on CalEvent (uuid_)
go
create index IX_5CCE79C8 on CalEvent (uuid_, groupId)
go

create index IX_B27A301F on ClassName_ (value)
go

create index IX_38EFE3FD on Company (logoId)
go
create index IX_12566EC2 on Company (mx)
go
create index IX_975996C0 on Company (virtualHost)
go
create index IX_EC00543C on Company (webId)
go

create index IX_66D496A3 on Contact_ (companyId)
go


create index IX_4CB1B2B4 on DLFileEntry (companyId)
go
create index IX_24A846D1 on DLFileEntry (folderId)
go
create index IX_8F6C75D0 on DLFileEntry (folderId, name)
go
create index IX_A9951F17 on DLFileEntry (folderId, title)
go
create index IX_64F0FE40 on DLFileEntry (uuid_)
go

create index IX_CE705D48 on DLFileRank (companyId, userId, folderId, name)
go
create index IX_40B56512 on DLFileRank (folderId, name)
go
create index IX_EED06670 on DLFileRank (userId)
go

create index IX_E56EC6AD on DLFileShortcut (folderId)
go
create index IX_CA2708A2 on DLFileShortcut (toFolderId, toName)
go
create index IX_4831EBE4 on DLFileShortcut (uuid_)
go

create index IX_9CD91DB6 on DLFileVersion (folderId, name)
go
create index IX_6C5E6512 on DLFileVersion (folderId, name, version)
go

create index IX_A74DB14C on DLFolder (companyId)
go
create index IX_F2EA1ACE on DLFolder (groupId)
go
create index IX_49C37475 on DLFolder (groupId, parentFolderId)
go
create index IX_902FD874 on DLFolder (groupId, parentFolderId, name)
go
create index IX_51556082 on DLFolder (parentFolderId, name)
go
create index IX_CBC408D8 on DLFolder (uuid_)
go
create index IX_3CC1DED2 on DLFolder (uuid_, groupId)
go

create index IX_1BB072CA on EmailAddress (companyId)
go
create index IX_49D2DEC4 on EmailAddress (companyId, classNameId)
go
create index IX_551A519F on EmailAddress (companyId, classNameId, classPK)
go
create index IX_7B43CD8 on EmailAddress (userId)
go

create index IX_D0D5E397 on Group_ (companyId, classNameId, classPK)
go
create index IX_5BDDB872 on Group_ (companyId, friendlyURL)
go
create index IX_5AA68501 on Group_ (companyId, name)
go
create index IX_16218A38 on Group_ (liveGroupId)
go

create index LIFERAY_001 on Groups_Permissions (permissionId)
go

create index IX_60214CF6 on IGFolder (companyId)
go
create index IX_206498F8 on IGFolder (groupId)
go
create index IX_1A605E9F on IGFolder (groupId, parentFolderId)
go
create index IX_F73C0982 on IGFolder (uuid_)
go
create index IX_B10EFD68 on IGFolder (uuid_, groupId)
go

create index IX_4438CA80 on IGImage (folderId)
go
create index IX_64F0B572 on IGImage (largeImageId)
go
create index IX_D3D32126 on IGImage (smallImageId)
go
create index IX_265BB0F1 on IGImage (uuid_)
go

create index IX_6A925A4D on Image (size_)
go

create index IX_DFF98523 on JournalArticle (companyId)
go
create index IX_9356F865 on JournalArticle (groupId)
go
create index IX_68C0F69C on JournalArticle (groupId, articleId)
go
create index IX_85C52EEC on JournalArticle (groupId, articleId, version)
go
create index IX_2E207659 on JournalArticle (groupId, structureId)
go
create index IX_8DEAE14E on JournalArticle (groupId, templateId)
go
create index IX_EF9B7028 on JournalArticle (smallImageId)
go
create index IX_F029602F on JournalArticle (uuid_)
go
create index IX_3463D95B on JournalArticle (uuid_, groupId)
go

create index IX_3B51BB68 on JournalArticleImage (groupId)
go
create index IX_158B526F on JournalArticleImage (groupId, articleId, version)
go
create index IX_D67292FC on JournalArticleImage (groupId, articleId, version, elName, languageId)
go

create index IX_F8433677 on JournalArticleResource (groupId)
go
create index IX_88DF994A on JournalArticleResource (groupId, articleId)
go

create index IX_6838E427 on JournalContentSearch (groupId, articleId)
go

create index IX_35A2DB2F on JournalFeed (groupId)
go
create index IX_65576CBC on JournalFeed (groupId, feedId)
go
create index IX_50C36D79 on JournalFeed (uuid_)
go
create index IX_39031F51 on JournalFeed (uuid_, groupId)
go

create index IX_B97F5608 on JournalStructure (groupId)
go
create index IX_AB6E9996 on JournalStructure (groupId, structureId)
go
create index IX_8831E4FC on JournalStructure (structureId)
go
create index IX_6702CA92 on JournalStructure (uuid_)
go
create index IX_42E86E58 on JournalStructure (uuid_, groupId)
go

create index IX_77923653 on JournalTemplate (groupId)
go
create index IX_1701CB2B on JournalTemplate (groupId, structureId)
go
create index IX_E802AA3C on JournalTemplate (groupId, templateId)
go
create index IX_25FFB6FA on JournalTemplate (smallImageId)
go
create index IX_1B12CA20 on JournalTemplate (templateId)
go
create index IX_2857419D on JournalTemplate (uuid_)
go
create index IX_62D1B3AD on JournalTemplate (uuid_, groupId)
go

create index IX_C7FBC998 on Layout (companyId)
go
create index IX_FAD05595 on Layout (dlFolderId)
go
create index IX_C099D61A on Layout (groupId)
go
create index IX_23922F7D on Layout (iconImageId)
go

create index IX_A40B8BEC on LayoutSet (groupId)
go
create index IX_5ABC2905 on LayoutSet (virtualHost)
go

create index IX_2932DD37 on ListType (type_)
go

create index IX_69951A25 on MBBan (banUserId)
go
create index IX_5C3FF12A on MBBan (groupId)
go
create index IX_8ABC4E3B on MBBan (groupId, banUserId)
go
create index IX_48814BBA on MBBan (userId)
go

create index IX_BC735DCF on MBCategory (companyId)
go
create index IX_BB870C11 on MBCategory (groupId)
go
create index IX_ED292508 on MBCategory (groupId, parentCategoryId)
go
create index IX_C2626EDB on MBCategory (uuid_)
go
create index IX_F7D28C2F on MBCategory (uuid_, groupId)
go

create index IX_33A4DE38 on MBDiscussion (classNameId, classPK)
go

create index IX_3C865EE5 on MBMessage (categoryId)
go
create index IX_138C7F1E on MBMessage (categoryId, threadId)
go
create index IX_B1432D30 on MBMessage (companyId)
go
create index IX_75B95071 on MBMessage (threadId)
go
create index IX_A7038CD7 on MBMessage (threadId, parentMessageId)
go
create index IX_C57B16BC on MBMessage (uuid_)
go

create index IX_D180D4AE on MBMessageFlag (messageId)
go
create index IX_7B2917BE on MBMessageFlag (userId)
go
create index IX_94A83834 on MBMessageFlag (userId, messageId)
go

create index IX_A00A898F on MBStatsUser (groupId)
go
create index IX_FAB5A88B on MBStatsUser (groupId, messageCount)
go
create index IX_9168E2C9 on MBStatsUser (groupId, userId)
go
create index IX_847F92B5 on MBStatsUser (userId)
go

create index IX_CB854772 on MBThread (categoryId)
go

create index IX_8A1CC4B on MembershipRequest (groupId)
go
create index IX_C28C72EC on MembershipRequest (groupId, statusId)
go
create index IX_66D70879 on MembershipRequest (userId)
go

create index IX_A425F71A on OrgGroupPermission (groupId)
go
create index IX_6C53DA4E on OrgGroupPermission (permissionId)
go

create index IX_4A527DD3 on OrgGroupRole (groupId)
go
create index IX_AB044D1C on OrgGroupRole (roleId)
go

create index IX_6AF0D434 on OrgLabor (organizationId)
go

create index IX_834BCEB6 on Organization_ (companyId)
go
create index IX_E301BDF5 on Organization_ (companyId, name)
go
create index IX_418E4522 on Organization_ (companyId, parentOrganizationId)
go

create index IX_3FBFA9F4 on PasswordPolicy (companyId, name)
go

create index IX_C3A17327 on PasswordPolicyRel (classNameId, classPK)
go
create index IX_ED7CF243 on PasswordPolicyRel (passwordPolicyId, classNameId, classPK)
go

create index IX_326F75BD on PasswordTracker (userId)
go

create index IX_4D19C2B8 on Permission_ (actionId, resourceId)
go
create index IX_F090C113 on Permission_ (resourceId)
go

create index IX_9F704A14 on Phone (companyId)
go
create index IX_A2E4AFBA on Phone (companyId, classNameId)
go
create index IX_9A53569 on Phone (companyId, classNameId, classPK)
go
create index IX_F202B9CE on Phone (userId)
go

create index IX_B9746445 on PluginSetting (companyId)
go
create index IX_7171B2E8 on PluginSetting (companyId, pluginId, pluginType)
go

create index IX_EC370F10 on PollsChoice (questionId)
go
create index IX_D76DD2CF on PollsChoice (questionId, name)
go
create index IX_6660B399 on PollsChoice (uuid_)
go

create index IX_9FF342EA on PollsQuestion (groupId)
go
create index IX_51F087F4 on PollsQuestion (uuid_)
go
create index IX_F3C9F36 on PollsQuestion (uuid_, groupId)
go

create index IX_D5DF7B54 on PollsVote (choiceId)
go
create index IX_12112599 on PollsVote (questionId)
go
create index IX_1BBFD4D3 on PollsVote (questionId, userId)
go

create index IX_80CC9508 on Portlet (companyId)
go
create index IX_12B5E51D on Portlet (companyId, portletId)
go

create index IX_E4F13E6E on PortletPreferences (ownerId, ownerType, plid)
go
create index IX_C7057FF7 on PortletPreferences (ownerId, ownerType, plid, portletId)
go
create index IX_F15C1C4F on PortletPreferences (plid)
go
create index IX_D340DB76 on PortletPreferences (plid, portletId)
go

create index IX_16184D57 on RatingsEntry (classNameId, classPK)
go
create index IX_B47E3C11 on RatingsEntry (userId, classNameId, classPK)
go

create index IX_A6E99284 on RatingsStats (classNameId, classPK)
go

create index IX_16D87CA7 on Region (countryId)
go

create index IX_717FDD47 on ResourceCode (companyId)
go
create index IX_A32C097E on ResourceCode (companyId, name, scope)
go
create index IX_AACAFF40 on ResourceCode (name)
go

create index IX_2578FBD3 on Resource_ (codeId)
go
create index IX_67DE7856 on Resource_ (codeId, primKey)
go

create index IX_449A10B9 on Role_ (companyId)
go
create index IX_A88E424E on Role_ (companyId, classNameId, classPK)
go
create index IX_EBC931B8 on Role_ (companyId, name)
go

create index LIFERAY_002 on Roles_Permissions (permissionId)
go

create index IX_C98C0D78 on SCFrameworkVersion (companyId)
go
create index IX_272991FA on SCFrameworkVersion (groupId)
go


create index IX_5D25244F on SCProductEntry (companyId)
go
create index IX_72F87291 on SCProductEntry (groupId)
go
create index IX_98E6A9CB on SCProductEntry (groupId, userId)
go
create index IX_7311E812 on SCProductEntry (repoGroupId, repoArtifactId)
go

create index IX_AE8224CC on SCProductScreenshot (fullImageId)
go
create index IX_467956FD on SCProductScreenshot (productEntryId)
go
create index IX_DA913A55 on SCProductScreenshot (productEntryId, priority)
go
create index IX_6C572DAC on SCProductScreenshot (thumbnailId)
go

create index IX_7020130F on SCProductVersion (directDownloadURL)
go
create index IX_8377A211 on SCProductVersion (productEntryId)
go

create index IX_7338606F on ServiceComponent (buildNamespace)
go
create index IX_4F0315B8 on ServiceComponent (buildNamespace, buildNumber)
go

create index IX_C28B41DC on ShoppingCart (groupId)
go
create index IX_FC46FE16 on ShoppingCart (groupId, userId)
go
create index IX_54101CC8 on ShoppingCart (userId)
go

create index IX_5F615D3E on ShoppingCategory (groupId)
go
create index IX_1E6464F5 on ShoppingCategory (groupId, parentCategoryId)
go

create index IX_DC60CFAE on ShoppingCoupon (code_)
go
create index IX_3251AF16 on ShoppingCoupon (groupId)
go

create index IX_C8EACF2E on ShoppingItem (categoryId)
go
create index IX_1C717CA6 on ShoppingItem (companyId, sku)
go
create index IX_903DC750 on ShoppingItem (largeImageId)
go
create index IX_D217AB30 on ShoppingItem (mediumImageId)
go
create index IX_FF203304 on ShoppingItem (smallImageId)
go

create index IX_6D5F9B87 on ShoppingItemField (itemId)
go

create index IX_EA6FD516 on ShoppingItemPrice (itemId)
go

create index IX_1D15553E on ShoppingOrder (groupId)
go
create index IX_119B5630 on ShoppingOrder (groupId, userId, ppPaymentStatus)
go
create index IX_D7D6E87A on ShoppingOrder (number_)
go

create index IX_B5F82C7A on ShoppingOrderItem (orderId)
go

create index IX_786D171A on Subscription (companyId, classNameId, classPK)
go
create index IX_2E1A92D4 on Subscription (companyId, userId, classNameId, classPK)
go
create index IX_54243AFD on Subscription (userId)
go

create index IX_1AB6D6D2 on TagsAsset (classNameId, classPK)
go
create index IX_AB3D8BCB on TagsAsset (companyId)
go

create index IX_10563688 on TagsEntry (companyId, name)
go

create index IX_C134234 on TagsProperty (companyId)
go
create index IX_EB974D08 on TagsProperty (companyId, key_)
go
create index IX_5200A629 on TagsProperty (entryId)
go
create index IX_F505253D on TagsProperty (entryId, key_)
go

create index IX_524FEFCE on UserGroup (companyId)
go
create index IX_23EAD0D on UserGroup (companyId, name)
go
create index IX_69771487 on UserGroup (companyId, parentUserGroupId)
go

create index IX_1B988D7A on UserGroupRole (groupId)
go
create index IX_871412DF on UserGroupRole (groupId, roleId)
go
create index IX_887A2C95 on UserGroupRole (roleId)
go
create index IX_887BE56A on UserGroupRole (userId)
go
create index IX_4D040680 on UserGroupRole (userId, groupId)
go

create index IX_41A32E0D on UserIdMapper (type_, externalUserId)
go
create index IX_E60EA987 on UserIdMapper (userId)
go
create index IX_D1C44A6E on UserIdMapper (userId, type_)
go

create index IX_29BA1CF5 on UserTracker (companyId)
go
create index IX_46B0AE8E on UserTracker (sessionId)
go
create index IX_E4EFBA8D on UserTracker (userId)
go

create index IX_14D8BCC0 on UserTrackerPath (userTrackerId)
go

create index IX_3A1E834E on User_ (companyId)
go
create index IX_615E9F7A on User_ (companyId, emailAddress)
go
create index IX_765A87C6 on User_ (companyId, password_)
go
create index IX_C5806019 on User_ (companyId, screenName)
go
create index IX_9782AD88 on User_ (companyId, userId)
go
create index IX_5ADBE171 on User_ (contactId)
go
create index IX_A18034A4 on User_ (portraitId)
go
create index IX_E0422BDA on User_ (uuid_)
go

create index LIFERAY_003 on Users_Permissions (permissionId)
go

create index IX_97DFA146 on WebDAVProps (classNameId, classPK)
go

create index IX_96F07007 on Website (companyId)
go
create index IX_4F0F0CA7 on Website (companyId, classNameId)
go
create index IX_F960131C on Website (companyId, classNameId, classPK)
go
create index IX_F75690BB on Website (userId)
go

create index IX_5D6FE3F0 on WikiNode (companyId)
go
create index IX_B480A672 on WikiNode (groupId)
go
create index IX_6C112D7C on WikiNode (uuid_)
go
create index IX_7609B2AE on WikiNode (uuid_, groupId)
go

create index IX_C8A9C476 on WikiPage (nodeId)
go
create index IX_997EEDD2 on WikiPage (nodeId, title)
go
create index IX_3D4AF476 on WikiPage (nodeId, title, version)
go
create index IX_9C0E478F on WikiPage (uuid_)
go

create index IX_21277664 on WikiPageResource (nodeId, title)
go


