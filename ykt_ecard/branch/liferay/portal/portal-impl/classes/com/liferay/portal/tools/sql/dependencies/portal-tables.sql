create table Account_ (
	accountId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	parentAccountId LONG,
	name VARCHAR(75) null,
	legalName VARCHAR(75) null,
	legalId VARCHAR(75) null,
	legalType VARCHAR(75) null,
	sicCode VARCHAR(75) null,
	tickerSymbol VARCHAR(75) null,
	industry VARCHAR(75) null,
	type_ VARCHAR(75) null,
	size_ VARCHAR(75) null
);

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

create table Address (
	addressId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	street1 VARCHAR(75) null,
	street2 VARCHAR(75) null,
	street3 VARCHAR(75) null,
	city VARCHAR(75) null,
	zip VARCHAR(75) null,
	regionId LONG,
	countryId LONG,
	typeId INTEGER,
	mailing BOOLEAN,
	primary_ BOOLEAN
);

create table BlogsCategory (
	categoryId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	parentCategoryId LONG,
	name VARCHAR(75) null,
	description STRING null
);

create table BlogsEntry (
	uuid_ VARCHAR(75) null,
	entryId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	title VARCHAR(150) null,
	urlTitle VARCHAR(150) null,
	content TEXT null,
	displayDate DATE null
);

create table BlogsStatsUser (
	statsUserId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	entryCount INTEGER,
	lastPostDate DATE null,
	ratingsTotalEntries INTEGER,
	ratingsTotalScore DOUBLE,
	ratingsAverageScore DOUBLE
);

create table BookmarksEntry (
	uuid_ VARCHAR(75) null,
	entryId LONG not null primary key,
	companyId LONG,
	userId LONG,
	createDate DATE null,
	modifiedDate DATE null,
	folderId LONG,
	name VARCHAR(300) null,
	url STRING null,
	comments STRING null,
	visits INTEGER,
	priority INTEGER
);

create table BookmarksFolder (
	uuid_ VARCHAR(75) null,
	folderId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	createDate DATE null,
	modifiedDate DATE null,
	parentFolderId LONG,
	name VARCHAR(75) null,
	description STRING null
);

create table CalEvent (
	uuid_ VARCHAR(75) null,
	eventId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	title VARCHAR(75) null,
	description STRING null,
	startDate DATE null,
	endDate DATE null,
	durationHour INTEGER,
	durationMinute INTEGER,
	allDay BOOLEAN,
	timeZoneSensitive BOOLEAN,
	type_ VARCHAR(75) null,
	repeating BOOLEAN,
	recurrence TEXT null,
	remindBy VARCHAR(75) null,
	firstReminder INTEGER,
	secondReminder INTEGER
);

create table ClassName_ (
	classNameId LONG not null primary key,
	value VARCHAR(200) null
);

create table Company (
	companyId LONG not null primary key,
	accountId LONG,
	webId VARCHAR(75) null,
	key_ TEXT null,
	virtualHost VARCHAR(75) null,
	mx VARCHAR(75) null,
	logoId LONG
);

create table Contact_ (
	contactId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	accountId LONG,
	parentContactId LONG,
	firstName VARCHAR(75) null,
	middleName VARCHAR(75) null,
	lastName VARCHAR(75) null,
	prefixId INTEGER,
	suffixId INTEGER,
	male BOOLEAN,
	birthday DATE null,
	smsSn VARCHAR(75) null,
	aimSn VARCHAR(75) null,
	icqSn VARCHAR(75) null,
	jabberSn VARCHAR(75) null,
	msnSn VARCHAR(75) null,
	skypeSn VARCHAR(75) null,
	ymSn VARCHAR(75) null,
	employeeStatusId VARCHAR(75) null,
	employeeNumber VARCHAR(75) null,
	jobTitle VARCHAR(100) null,
	jobClass VARCHAR(75) null,
	hoursOfOperation VARCHAR(75) null
);

create table Counter (
	name VARCHAR(75) not null primary key,
	currentId LONG
);

create table Country (
	countryId LONG not null primary key,
	name VARCHAR(75) null,
	a2 VARCHAR(75) null,
	a3 VARCHAR(75) null,
	number_ VARCHAR(75) null,
	idd_ VARCHAR(75) null,
	active_ BOOLEAN
);

create table CyrusUser (
	userId VARCHAR(75) not null primary key,
	password_ VARCHAR(75) not null
);

create table CyrusVirtual (
	emailAddress VARCHAR(75) not null primary key,
	userId VARCHAR(75) not null
);

create table DLFileEntry (
	uuid_ VARCHAR(75) null,
	fileEntryId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	versionUserId LONG,
	versionUserName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	folderId LONG,
	name VARCHAR(300) null,
	title VARCHAR(300) null,
	description STRING null,
	version DOUBLE,
	size_ INTEGER,
	readCount INTEGER,
	extraSettings TEXT null
);

create table DLFileRank (
	fileRankId LONG not null primary key,
	companyId LONG,
	userId LONG,
	createDate DATE null,
	folderId LONG,
	name VARCHAR(300) null
);

create table DLFileShortcut (
	uuid_ VARCHAR(75) null,
	fileShortcutId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	folderId LONG,
	toFolderId LONG,
	toName VARCHAR(300) null
);

create table DLFileVersion (
	fileVersionId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	folderId LONG,
	name VARCHAR(300) null,
	version DOUBLE,
	size_ INTEGER
);

create table DLFolder (
	uuid_ VARCHAR(75) null,
	folderId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	parentFolderId LONG,
	name VARCHAR(100) null,
	description STRING null,
	lastPostDate DATE null
);

create table EmailAddress (
	emailAddressId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	address VARCHAR(75) null,
	typeId INTEGER,
	primary_ BOOLEAN
);

create table Group_ (
	groupId LONG not null primary key,
	companyId LONG,
	creatorUserId LONG,
	classNameId LONG,
	classPK LONG,
	parentGroupId LONG,
	liveGroupId LONG,
	name VARCHAR(75) null,
	description STRING null,
	type_ INTEGER,
	typeSettings STRING null,
	friendlyURL VARCHAR(100) null,
	active_ BOOLEAN
);

create table Groups_Orgs (
	groupId LONG not null,
	organizationId LONG not null,
	primary key (groupId, organizationId)
);

create table Groups_Permissions (
	groupId LONG not null,
	permissionId LONG not null,
	primary key (groupId, permissionId)
);

create table Groups_Roles (
	groupId LONG not null,
	roleId LONG not null,
	primary key (groupId, roleId)
);

create table Groups_UserGroups (
	groupId LONG not null,
	userGroupId LONG not null,
	primary key (groupId, userGroupId)
);

create table IGFolder (
	uuid_ VARCHAR(75) null,
	folderId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	createDate DATE null,
	modifiedDate DATE null,
	parentFolderId LONG,
	name VARCHAR(75) null,
	description STRING null
);

create table IGImage (
	uuid_ VARCHAR(75) null,
	imageId LONG not null primary key,
	companyId LONG,
	userId LONG,
	createDate DATE null,
	modifiedDate DATE null,
	folderId LONG,
	description STRING null,
	smallImageId LONG,
	largeImageId LONG
);

create table Image (
	imageId LONG not null primary key,
	modifiedDate DATE null,
	text_ TEXT null,
	type_ VARCHAR(75) null,
	height INTEGER,
	width INTEGER,
	size_ INTEGER
);

create table JournalArticle (
	uuid_ VARCHAR(75) null,
	id_ LONG not null primary key,
	resourcePrimKey LONG,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	articleId VARCHAR(75) null,
	version DOUBLE,
	title VARCHAR(100) null,
	description STRING null,
	content TEXT null,
	type_ VARCHAR(75) null,
	structureId VARCHAR(75) null,
	templateId VARCHAR(75) null,
	displayDate DATE null,
	approved BOOLEAN,
	approvedByUserId LONG,
	approvedByUserName VARCHAR(75) null,
	approvedDate DATE null,
	expired BOOLEAN,
	expirationDate DATE null,
	reviewDate DATE null,
	indexable BOOLEAN,
	smallImage BOOLEAN,
	smallImageId LONG,
	smallImageURL VARCHAR(75) null
);

create table JournalArticleImage (
	articleImageId LONG not null primary key,
	groupId LONG,
	articleId VARCHAR(75) null,
	version DOUBLE,
	elName VARCHAR(75) null,
	languageId VARCHAR(75) null,
	tempImage BOOLEAN
);

create table JournalArticleResource (
	resourcePrimKey LONG not null primary key,
	groupId LONG,
	articleId VARCHAR(75) null
);

create table JournalContentSearch (
	contentSearchId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	privateLayout BOOLEAN,
	layoutId LONG,
	portletId VARCHAR(200) null,
	articleId VARCHAR(75) null
);

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

create table JournalStructure (
	uuid_ VARCHAR(75) null,
	id_ LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	structureId VARCHAR(75) null,
	name VARCHAR(75) null,
	description STRING null,
	xsd TEXT null
);

create table JournalTemplate (
	uuid_ VARCHAR(75) null,
	id_ LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	templateId VARCHAR(75) null,
	structureId VARCHAR(75) null,
	name VARCHAR(75) null,
	description STRING null,
	xsl TEXT null,
	langType VARCHAR(75) null,
	cacheable BOOLEAN,
	smallImage BOOLEAN,
	smallImageId LONG,
	smallImageURL VARCHAR(75) null
);

create table Layout (
	plid LONG not null primary key,
	groupId LONG,
	companyId LONG,
	privateLayout BOOLEAN,
	layoutId LONG,
	parentLayoutId LONG,
	name STRING null,
	title STRING null,
	description STRING null,
	type_ VARCHAR(75) null,
	typeSettings TEXT null,
	hidden_ BOOLEAN,
	friendlyURL VARCHAR(100) null,
	iconImage BOOLEAN,
	iconImageId LONG,
	themeId VARCHAR(75) null,
	colorSchemeId VARCHAR(75) null,
	wapThemeId VARCHAR(75) null,
	wapColorSchemeId VARCHAR(75) null,
	css STRING null,
	priority INTEGER,
	dlFolderId LONG
);

create table LayoutSet (
	layoutSetId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	privateLayout BOOLEAN,
	logo BOOLEAN,
	logoId LONG,
	themeId VARCHAR(75) null,
	colorSchemeId VARCHAR(75) null,
	wapThemeId VARCHAR(75) null,
	wapColorSchemeId VARCHAR(75) null,
	css VARCHAR(75) null,
	pageCount INTEGER,
	virtualHost VARCHAR(75) null
);

create table ListType (
	listTypeId INTEGER not null primary key,
	name VARCHAR(75) null,
	type_ VARCHAR(75) null
);

create table MBBan (
	banId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	banUserId LONG
);

create table MBCategory (
	uuid_ VARCHAR(75) null,
	categoryId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	parentCategoryId LONG,
	name VARCHAR(75) null,
	description STRING null,
	lastPostDate DATE null
);

create table MBDiscussion (
	discussionId LONG not null primary key,
	classNameId LONG,
	classPK LONG,
	threadId LONG
);

create table MBMessage (
	uuid_ VARCHAR(75) null,
	messageId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	categoryId LONG,
	threadId LONG,
	parentMessageId LONG,
	subject VARCHAR(75) null,
	body TEXT null,
	attachments BOOLEAN,
	anonymous BOOLEAN
);

create table MBMessageFlag (
	messageFlagId LONG not null primary key,
	userId LONG,
	messageId LONG,
	flag INTEGER
);

create table MBStatsUser (
	statsUserId LONG not null primary key,
	groupId LONG,
	userId LONG,
	messageCount INTEGER,
	lastPostDate DATE null
);

create table MBThread (
	threadId LONG not null primary key,
	categoryId LONG,
	rootMessageId LONG,
	messageCount INTEGER,
	viewCount INTEGER,
	lastPostByUserId LONG,
	lastPostDate DATE null,
	priority DOUBLE
);

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

create table Organization_ (
	organizationId LONG not null primary key,
	companyId LONG,
	parentOrganizationId LONG,
	name VARCHAR(100) null,
	location BOOLEAN,
	recursable BOOLEAN,
	regionId LONG,
	countryId LONG,
	statusId INTEGER,
	comments STRING null
);

create table OrgGroupPermission (
	organizationId LONG not null,
	groupId LONG not null,
	permissionId LONG not null,
	primary key (organizationId, groupId, permissionId)
);

create table OrgGroupRole (
	organizationId LONG not null,
	groupId LONG not null,
	roleId LONG not null,
	primary key (organizationId, groupId, roleId)
);

create table OrgLabor (
	orgLaborId LONG not null primary key,
	organizationId LONG,
	typeId INTEGER,
	sunOpen INTEGER,
	sunClose INTEGER,
	monOpen INTEGER,
	monClose INTEGER,
	tueOpen INTEGER,
	tueClose INTEGER,
	wedOpen INTEGER,
	wedClose INTEGER,
	thuOpen INTEGER,
	thuClose INTEGER,
	friOpen INTEGER,
	friClose INTEGER,
	satOpen INTEGER,
	satClose INTEGER
);

create table PasswordPolicy (
	passwordPolicyId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	defaultPolicy BOOLEAN,
	name VARCHAR(75) null,
	description STRING null,
	changeable BOOLEAN,
	changeRequired BOOLEAN,
	minAge LONG,
	checkSyntax BOOLEAN,
	allowDictionaryWords BOOLEAN,
	minLength INTEGER,
	history BOOLEAN,
	historyCount INTEGER,
	expireable BOOLEAN,
	maxAge LONG,
	warningTime LONG,
	graceLimit INTEGER,
	lockout BOOLEAN,
	maxFailure INTEGER,
	lockoutDuration LONG,
	requireUnlock BOOLEAN,
	resetFailureCount LONG
);

create table PasswordPolicyRel (
	passwordPolicyRelId LONG not null primary key,
	passwordPolicyId LONG,
	classNameId LONG,
	classPK LONG
);

create table PasswordTracker (
	passwordTrackerId LONG not null primary key,
	userId LONG,
	createDate DATE null,
	password_ VARCHAR(75) null
);

create table Permission_ (
	permissionId LONG not null primary key,
	companyId LONG,
	actionId VARCHAR(75) null,
	resourceId LONG
);

create table Phone (
	phoneId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	number_ VARCHAR(75) null,
	extension VARCHAR(75) null,
	typeId INTEGER,
	primary_ BOOLEAN
);

create table PluginSetting (
	pluginSettingId LONG not null primary key,
	companyId LONG,
	pluginId VARCHAR(75) null,
	pluginType VARCHAR(75) null,
	roles STRING null,
	active_ BOOLEAN
);

create table PollsChoice (
	uuid_ VARCHAR(75) null,
	choiceId LONG not null primary key,
	questionId LONG,
	name VARCHAR(75) null,
	description VARCHAR(1000) null
);

create table PollsQuestion (
	uuid_ VARCHAR(75) null,
	questionId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	title VARCHAR(500) null,
	description STRING null,
	expirationDate DATE null,
	lastVoteDate DATE null
);

create table PollsVote (
	voteId LONG not null primary key,
	userId LONG,
	questionId LONG,
	choiceId LONG,
	voteDate DATE null
);

create table Portlet (
	id_ LONG not null primary key,
	companyId LONG,
	portletId VARCHAR(200) null,
	roles STRING null,
	active_ BOOLEAN
);

create table PortletPreferences (
	portletPreferencesId LONG not null primary key,
	ownerId LONG,
	ownerType INTEGER,
	plid LONG,
	portletId VARCHAR(200) null,
	preferences TEXT null
);

create table RatingsEntry (
	entryId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	score DOUBLE
);

create table RatingsStats (
	statsId LONG not null primary key,
	classNameId LONG,
	classPK LONG,
	totalEntries INTEGER,
	totalScore DOUBLE,
	averageScore DOUBLE
);

create table Region (
	regionId LONG not null primary key,
	countryId LONG,
	regionCode VARCHAR(75) null,
	name VARCHAR(75) null,
	active_ BOOLEAN
);

create table Release_ (
	releaseId LONG not null primary key,
	createDate DATE null,
	modifiedDate DATE null,
	buildNumber INTEGER,
	buildDate DATE null,
	verified BOOLEAN
);

create table Resource_ (
	resourceId LONG not null primary key,
	codeId LONG,
	primKey VARCHAR(300) null
);

create table ResourceCode (
	codeId LONG not null primary key,
	companyId LONG,
	name VARCHAR(300) null,
	scope INTEGER
);

create table Role_ (
	roleId LONG not null primary key,
	companyId LONG,
	classNameId LONG,
	classPK LONG,
	name VARCHAR(75) null,
	description STRING null,
	type_ INTEGER
);

create table Roles_Permissions (
	roleId LONG not null,
	permissionId LONG not null,
	primary key (roleId, permissionId)
);

create table SCFrameworkVersi_SCProductVers (
	productVersionId LONG not null,
	frameworkVersionId LONG not null,
	primary key (productVersionId, frameworkVersionId)
);

create table SCFrameworkVersion (
	frameworkVersionId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	name VARCHAR(75) null,
	url STRING null,
	active_ BOOLEAN,
	priority INTEGER
);

create table SCLicense (
	licenseId LONG not null primary key,
	name VARCHAR(75) null,
	url STRING null,
	openSource BOOLEAN,
	active_ BOOLEAN,
	recommended BOOLEAN
);

create table SCLicenses_SCProductEntries (
	productEntryId LONG not null,
	licenseId LONG not null,
	primary key (productEntryId, licenseId)
);

create table SCProductEntry (
	productEntryId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	name VARCHAR(75) null,
	type_ VARCHAR(75) null,
	tags VARCHAR(300) null,
	shortDescription STRING null,
	longDescription STRING null,
	pageURL STRING null,
	author VARCHAR(75) null,
	repoGroupId VARCHAR(75) null,
	repoArtifactId VARCHAR(75) null
);

create table SCProductScreenshot (
	productScreenshotId LONG not null primary key,
	companyId LONG,
	groupId LONG,
	productEntryId LONG,
	thumbnailId LONG,
	fullImageId LONG,
	priority INTEGER
);

create table SCProductVersion (
	productVersionId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	productEntryId LONG,
	version VARCHAR(75) null,
	changeLog STRING null,
	downloadPageURL STRING null,
	directDownloadURL VARCHAR(2000) null,
	repoStoreArtifact BOOLEAN
);

create table ServiceComponent (
	serviceComponentId LONG not null primary key,
	buildNamespace VARCHAR(75) null,
	buildNumber LONG,
	buildDate LONG,
	data_ TEXT null
);

create table ShoppingCart (
	cartId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	itemIds STRING null,
	couponCodes VARCHAR(75) null,
	altShipping INTEGER,
	insure BOOLEAN
);

create table ShoppingCategory (
	categoryId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	parentCategoryId LONG,
	name VARCHAR(75) null,
	description STRING null
);

create table ShoppingCoupon (
	couponId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	code_ VARCHAR(75) null,
	name VARCHAR(75) null,
	description STRING null,
	startDate DATE null,
	endDate DATE null,
	active_ BOOLEAN,
	limitCategories STRING null,
	limitSkus STRING null,
	minOrder DOUBLE,
	discount DOUBLE,
	discountType VARCHAR(75) null
);

create table ShoppingItem (
	itemId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	categoryId LONG,
	sku VARCHAR(75) null,
	name VARCHAR(200) null,
	description STRING null,
	properties STRING null,
	fields_ BOOLEAN,
	fieldsQuantities STRING null,
	minQuantity INTEGER,
	maxQuantity INTEGER,
	price DOUBLE,
	discount DOUBLE,
	taxable BOOLEAN,
	shipping DOUBLE,
	useShippingFormula BOOLEAN,
	requiresShipping BOOLEAN,
	stockQuantity INTEGER,
	featured_ BOOLEAN,
	sale_ BOOLEAN,
	smallImage BOOLEAN,
	smallImageId LONG,
	smallImageURL VARCHAR(75) null,
	mediumImage BOOLEAN,
	mediumImageId LONG,
	mediumImageURL VARCHAR(75) null,
	largeImage BOOLEAN,
	largeImageId LONG,
	largeImageURL VARCHAR(75) null
);

create table ShoppingItemField (
	itemFieldId LONG not null primary key,
	itemId LONG,
	name VARCHAR(75) null,
	values_ STRING null,
	description STRING null
);

create table ShoppingItemPrice (
	itemPriceId LONG not null primary key,
	itemId LONG,
	minQuantity INTEGER,
	maxQuantity INTEGER,
	price DOUBLE,
	discount DOUBLE,
	taxable BOOLEAN,
	shipping DOUBLE,
	useShippingFormula BOOLEAN,
	status INTEGER
);

create table ShoppingOrder (
	orderId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	number_ VARCHAR(75) null,
	tax DOUBLE,
	shipping DOUBLE,
	altShipping VARCHAR(75) null,
	requiresShipping BOOLEAN,
	insure BOOLEAN,
	insurance DOUBLE,
	couponCodes VARCHAR(75) null,
	couponDiscount DOUBLE,
	billingFirstName VARCHAR(75) null,
	billingLastName VARCHAR(75) null,
	billingEmailAddress VARCHAR(75) null,
	billingCompany VARCHAR(75) null,
	billingStreet VARCHAR(75) null,
	billingCity VARCHAR(75) null,
	billingState VARCHAR(75) null,
	billingZip VARCHAR(75) null,
	billingCountry VARCHAR(75) null,
	billingPhone VARCHAR(75) null,
	shipToBilling BOOLEAN,
	shippingFirstName VARCHAR(75) null,
	shippingLastName VARCHAR(75) null,
	shippingEmailAddress VARCHAR(75) null,
	shippingCompany VARCHAR(75) null,
	shippingStreet VARCHAR(75) null,
	shippingCity VARCHAR(75) null,
	shippingState VARCHAR(75) null,
	shippingZip VARCHAR(75) null,
	shippingCountry VARCHAR(75) null,
	shippingPhone VARCHAR(75) null,
	ccName VARCHAR(75) null,
	ccType VARCHAR(75) null,
	ccNumber VARCHAR(75) null,
	ccExpMonth INTEGER,
	ccExpYear INTEGER,
	ccVerNumber VARCHAR(75) null,
	comments STRING null,
	ppTxnId VARCHAR(75) null,
	ppPaymentStatus VARCHAR(75) null,
	ppPaymentGross DOUBLE,
	ppReceiverEmail VARCHAR(75) null,
	ppPayerEmail VARCHAR(75) null,
	sendOrderEmail BOOLEAN,
	sendShippingEmail BOOLEAN
);

create table ShoppingOrderItem (
	orderItemId LONG not null primary key,
	orderId LONG,
	itemId VARCHAR(75) null,
	sku VARCHAR(75) null,
	name VARCHAR(200) null,
	description STRING null,
	properties STRING null,
	price DOUBLE,
	quantity INTEGER,
	shippedDate DATE null
);

create table Subscription (
	subscriptionId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	frequency VARCHAR(75) null
);

create table TagsAsset (
	assetId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	startDate DATE null,
	endDate DATE null,
	publishDate DATE null,
	expirationDate DATE null,
	mimeType VARCHAR(75) null,
	title VARCHAR(300) null,
	description STRING null,
	summary STRING null,
	url STRING null,
	height INTEGER,
	width INTEGER,
	priority DOUBLE,
	viewCount INTEGER
);

create table TagsAssets_TagsEntries (
	assetId LONG not null,
	entryId LONG not null,
	primary key (assetId, entryId)
);

create table TagsEntry (
	entryId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	name VARCHAR(75) null
);

create table TagsProperty (
	propertyId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	entryId LONG,
	key_ VARCHAR(75) null,
	value VARCHAR(300) null
);

create table TagsSource (
	sourceId LONG not null primary key,
	parentSourceId LONG,
	name VARCHAR(75) null,
	acronym VARCHAR(75) null
);

create table User_ (
	uuid_ VARCHAR(75) null,
	userId LONG not null primary key,
	companyId LONG,
	createDate DATE null,
	modifiedDate DATE null,
	defaultUser BOOLEAN,
	contactId LONG,
	password_ VARCHAR(75) null,
	passwordEncrypted BOOLEAN,
	passwordReset BOOLEAN,
	passwordModifiedDate DATE null,
	graceLoginCount INTEGER,
	screenName VARCHAR(75) null,
	emailAddress VARCHAR(75) null,
	portraitId LONG,
	languageId VARCHAR(75) null,
	timeZoneId VARCHAR(75) null,
	greeting VARCHAR(75) null,
	comments STRING null,
	loginDate DATE null,
	loginIP VARCHAR(75) null,
	lastLoginDate DATE null,
	lastLoginIP VARCHAR(75) null,
	lastFailedLoginDate DATE null,
	failedLoginAttempts INTEGER,
	lockout BOOLEAN,
	lockoutDate DATE null,
	agreedToTermsOfUse BOOLEAN,
	active_ BOOLEAN
);

create table UserGroup (
	userGroupId LONG not null primary key,
	companyId LONG,
	parentUserGroupId LONG,
	name VARCHAR(75) null,
	description STRING null
);

create table UserGroupRole (
	userId LONG not null,
	groupId LONG not null,
	roleId LONG not null,
	primary key (userId, groupId, roleId)
);

create table UserIdMapper (
	userIdMapperId LONG not null primary key,
	userId LONG,
	type_ VARCHAR(75) null,
	description VARCHAR(75) null,
	externalUserId VARCHAR(75) null
);

create table Users_Groups (
	userId LONG not null,
	groupId LONG not null,
	primary key (userId, groupId)
);

create table Users_Orgs (
	userId LONG not null,
	organizationId LONG not null,
	primary key (userId, organizationId)
);

create table Users_Permissions (
	userId LONG not null,
	permissionId LONG not null,
	primary key (userId, permissionId)
);

create table Users_Roles (
	userId LONG not null,
	roleId LONG not null,
	primary key (userId, roleId)
);

create table Users_UserGroups (
	userId LONG not null,
	userGroupId LONG not null,
	primary key (userId, userGroupId)
);

create table UserTracker (
	userTrackerId LONG not null primary key,
	companyId LONG,
	userId LONG,
	modifiedDate DATE null,
	sessionId VARCHAR(200) null,
	remoteAddr VARCHAR(75) null,
	remoteHost VARCHAR(75) null,
	userAgent VARCHAR(200) null
);

create table UserTrackerPath (
	userTrackerPathId LONG not null primary key,
	userTrackerId LONG,
	path_ STRING null,
	pathDate DATE null
);

create table WebDAVProps (
	webDavPropsId LONG not null primary key,
	companyId LONG,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	props TEXT null
);

create table Website (
	websiteId LONG not null primary key,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	classNameId LONG,
	classPK LONG,
	url STRING null,
	typeId INTEGER,
	primary_ BOOLEAN
);

create table WikiNode (
	uuid_ VARCHAR(75) null,
	nodeId LONG not null primary key,
	groupId LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	modifiedDate DATE null,
	name VARCHAR(75) null,
	description STRING null,
	lastPostDate DATE null
);

create table WikiPage (
	uuid_ VARCHAR(75) null,
	pageId LONG not null primary key,
	resourcePrimKey LONG,
	companyId LONG,
	userId LONG,
	userName VARCHAR(75) null,
	createDate DATE null,
	nodeId LONG,
	title VARCHAR(75) null,
	version DOUBLE,
	content TEXT null,
	format VARCHAR(75) null,
	head BOOLEAN
);

create table WikiPageResource (
	resourcePrimKey LONG not null primary key,
	nodeId LONG,
	title VARCHAR(75) null
);
