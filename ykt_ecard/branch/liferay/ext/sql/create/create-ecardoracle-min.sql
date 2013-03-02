grant select on YKT_CUR.T_TRANSDTL to YKT_PORTAL;
grant select on YKT_CUR.T_POSDTL to YKT_PORTAL;
grant select, insert, delete, index on YKT_CUR.T_MSGLIST to YKT_PORTAL;
grant select, insert, delete, index on YKT_CUR.T_CARDVER to YKT_PORTAL;
grant select on YKT_CUR.T_DICTIONARY to YKT_PORTAL;
grant select on YKT_CUR.T_TRANSCODE to YKT_PORTAL;
grant select, update on YKT_CUR.T_CARD to YKT_PORTAL;
grant select on YKT_CUR.T_DEVICE to YKT_PORTAL;
grant select on YKT_CUR.T_PHOTO to YKT_PORTAL;
grant select on YKT_CUR.T_SPECIALTY to YKT_PORTAL;
grant select on YKT_CUR.T_CUSTOMER to YKT_PORTAL;
grant select on YKT_CUR.T_DEPT to YKT_PORTAL;
grant select on YKT_CUR.T_ACCOUNT to YKT_PORTAL;
grant select on YKT_CUR.T_CARDTYPE to YKT_PORTAL;
grant select on ykt_cur.t_feetype to YKT_PORTAL;
grant select on YKT_CUR.t_cardtype to YKT_PORTAL;
grant select on YKT_CUR.t_area to YKT_PORTAL;
grant select, insert, update, delete, index on YKT_CUR.t_bankcard to YKT_PORTAL;
grant select on ykt_cur.t_brastransdtl to ykt_portal;

grant select on ykt_cur.t_rptposledger to YKT_PORTAL;
grant select on ykt_cur.t_rptshoprakeoff to YKT_PORTAL;
grant select on ykt_cur.t_shop to YKT_PORTAL;
grant select on ykt_cur.v_device to YKT_PORTAL;
grant select on ykt_cur.t_transtype to YKT_PORTAL;
grant select on ykt_cur.t_rptsubjledger to YKT_PORTAL;
grant select on ykt_cur.t_custtype to YKT_PORTAL;
grant select on ykt_cur.t_rptopercash to YKT_PORTAL;
grant select on ykt_cur.t_specialty to YKT_PORTAL;
grant select on ykt_cur.v_term to ykt_portal;
grant select on YKT_CUR.V_TRANSDTL to YKT_PORTAL;
grant select,insert,update,delete,index on ykt_cur.t_losscardinfo to YKT_PORTAL;
grant select,insert,update,delete,index on ykt_cur.t_losscardshop to YKT_PORTAL;
grant select on ykt_cur.v_accdtl to ykt_portal;


CREATE TABLE YKT_PORTAL.T_RPTTERMLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   TERMID               INTEGER                         NOT NULL,
   SUBJNO               VARCHAR(6)                      NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTTERMLEDGER PRIMARY KEY (ACCDATE, TERMID, ACCNO, SUMMARY)
);

COMMENT ON TABLE YKT_PORTAL.T_RPTTERMLEDGER IS
'T_RPTTERMLEDGER-终端分类账表';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.ACCDATE IS
'业务日期';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.TERMID IS
'终端编号';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_PORTAL.T_RPTTERMLEDGER.CRAMT IS
'贷方发生额';


CREATE TABLE YKT_PORTAL.T_RPTDEPTLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   DEPTCODE             VARCHAR(30)                     NOT NULL,
   SUBJNO               VARCHAR(6)                      NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTDEPTLEDGER PRIMARY KEY (ACCDATE, DEPTCODE, SUBJNO, SUMMARY)
);

COMMENT ON TABLE YKT_PORTAL.T_RPTDEPTLEDGER IS
'T_RPTDEPTLEDGER-部门分类账表';

COMMENT ON COLUMN YKT_PORTAL.T_RPTDEPTLEDGER.ACCDATE IS
'业务日期';

COMMENT ON COLUMN YKT_PORTAL.T_RPTDEPTLEDGER.DEPTCODE IS
'部门代码';

COMMENT ON COLUMN YKT_PORTAL.T_RPTDEPTLEDGER.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_PORTAL.T_RPTDEPTLEDGER.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_PORTAL.T_RPTDEPTLEDGER.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_PORTAL.T_RPTDEPTLEDGER.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_PORTAL.T_RPTDEPTLEDGER.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_PORTAL.T_RPTDEPTLEDGER.CRAMT IS
'贷方发生额';


-- Create table
create table YKT_PORTAL.T_RCSTATDATA
(
  CARD_NO INTEGER not null,
  MEAL    CHAR(20) not null,
  TX_DATE CHAR(8) not null,
  AMOUNT  NUMBER(15,2),
  CONSTRAINT PK_T_RCSTATDATA PRIMARY KEY (CARD_NO, MEAL, TX_DATE)
);
create index IDX_RCSTATDATA on YKT_PORTAL.T_RCSTATDATA (CARD_NO, MEAL, TX_DATE);
  
  
  

create table YKT_PORTAL.STORE_LIMIT (
   OPER_CODE  VARCHAR2(60) not null,
   STORE_CODE VARCHAR2(6) not null,
   primary key (OPER_CODE, STORE_CODE)
);

/*==============================================================*/
/* Table: ECARD_HIT_INFO                                        */
/*==============================================================*/
create table YKT_PORTAL.ECARD_HIT_INFO  (
   ID                   INTEGER                         not null,
   TITLE                VARCHAR2(500),
   INFO_ID              INTEGER                         not null,
   primary key (ID)
);

/*==============================================================*/
/* Table: ECARD_INFORMATION                                     */
/*==============================================================*/
create table YKT_PORTAL.ECARD_INFORMATION  (
   ID                   INTEGER                         not null,
   INFO_TYPE            VARCHAR2(20),
   INFO_TITLE           VARCHAR2(500),
   INFO_CONTENT         CLOB,
   ATTACHMENTS          VARCHAR2(90),
   CREATE_DATE          TIMESTAMP,
   CREATER              VARCHAR2(20),
   primary key (ID)
);

/*==============================================================*/
/* Table: ECARD_MSGBOARD                                        */
/*==============================================================*/
create table YKT_PORTAL.ECARD_MSGBOARD  (
   ID                   INTEGER                         not null,
   MSG_TITLE            VARCHAR2(200),
   POST_TIME            TIMESTAMP,
   POSTER               VARCHAR2(40),
   POST_CONTENT         CLOB,
   REPLY_TIME           TIMESTAMP,
   REPLYER              VARCHAR2(40),
   REPLY_CONTENT        CLOB,
   STATUS               CHAR(1),
   primary key (ID)
);

/*==============================================================*/
/* Table: ECARD_PIC_DELAY                                       */
/*==============================================================*/
create table YKT_PORTAL.ECARD_PIC_DELAY  (
   CUR_STUEMP_NO        VARCHAR2(20)                    not null,
   OLD_STUEMP_NO        VARCHAR2(20),
   STATUS               CHAR(1),
   primary key (CUR_STUEMP_NO)
);

/*==============================================================*/
/* Table: ECARD_POSTPONE_APPLY                                  */
/*==============================================================*/
create table YKT_PORTAL.ECARD_POSTPONE_APPLY  (
   ID                   INTEGER                         not null,
   STUEMPNO             VARCHAR2(20),
   REASON               VARCHAR2(900),
   POSTPONE_TIME        VARCHAR2(8),
   APPLY_TIME           TIMESTAMP,
   CHECK_RESULT         VARCHAR2(240),
   STATUS               CHAR(1),
   primary key (ID)
);

create table YKT_PORTAL.POSTPONE_FILES
(
  ID            INTEGER not null,
  GENERATE_DATE TIMESTAMP(6),
  FILE_CONTENT  CLOB,
  primary key (ID)
);

/*==============================================================*/
/* Table: INFO_TYPE                                             */
/*==============================================================*/
create table YKT_PORTAL.INFO_TYPE  (
   INFO_TYPE            VARCHAR2(20)                    not null,
   INFO_NAME            VARCHAR2(100),
   primary key (INFO_TYPE)
);

-- Create table
create table YKT_PORTAL.UPLOAD_FILES
(
  ID             INTEGER not null,
  STORE_FILENAME VARCHAR2(240),
  OLD_FILENAME   VARCHAR2(240),
  primary key (ID)
);



create table YKT_PORTAL.Account_ (
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

create table YKT_PORTAL.ActivityTracker (
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

create table YKT_PORTAL.Address (
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

create table YKT_PORTAL.BlogsCategory (
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

create table YKT_PORTAL.BlogsEntry (
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

create table YKT_PORTAL.BlogsStatsUser (
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

create table YKT_PORTAL.BookmarksEntry (
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

create table YKT_PORTAL.BookmarksFolder (
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

create table YKT_PORTAL.CalEvent (
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

create table YKT_PORTAL.ClassName_ (
    classNameId number(30,0) not null primary key,
    value varchar2(200) null
);

create table YKT_PORTAL.Company (
    companyId number(30,0) not null primary key,
    accountId number(30,0),
    webId varchar2(75) null,
    key_ clob null,
    virtualHost varchar2(75) null,
    mx varchar2(75) null,
    logoId number(30,0)
);

create table YKT_PORTAL.Contact_ (
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

create table YKT_PORTAL.Counter (
    name varchar2(75) not null primary key,
    currentId number(30,0)
);

create table YKT_PORTAL.Country (
    countryId number(30,0) not null primary key,
    name varchar2(75) null,
    a2 varchar2(75) null,
    a3 varchar2(75) null,
    number_ varchar2(75) null,
    idd_ varchar2(75) null,
    active_ number(1, 0)
);

create table YKT_PORTAL.CyrusUser (
    userId varchar2(75) not null primary key,
    password_ varchar2(75) not null
);

create table YKT_PORTAL.CyrusVirtual (
    emailAddress varchar2(75) not null primary key,
    userId varchar2(75) not null
);

create table YKT_PORTAL.DLFileEntry (
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

create table YKT_PORTAL.DLFileRank (
    fileRankId number(30,0) not null primary key,
    companyId number(30,0),
    userId number(30,0),
    createDate timestamp null,
    folderId number(30,0),
    name varchar2(300) null
);

create table YKT_PORTAL.DLFileShortcut (
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

create table YKT_PORTAL.DLFileVersion (
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

create table YKT_PORTAL.DLFolder (
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

create table YKT_PORTAL.EmailAddress (
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

create table YKT_PORTAL.Group_ (
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

create table YKT_PORTAL.Groups_Orgs (
    groupId number(30,0) not null,
    organizationId number(30,0) not null,
    primary key (groupId, organizationId)
);

create table YKT_PORTAL.Groups_Permissions (
    groupId number(30,0) not null,
    permissionId number(30,0) not null,
    primary key (groupId, permissionId)
);

create table YKT_PORTAL.Groups_Roles (
    groupId number(30,0) not null,
    roleId number(30,0) not null,
    primary key (groupId, roleId)
);

create table YKT_PORTAL.Groups_UserGroups (
    groupId number(30,0) not null,
    userGroupId number(30,0) not null,
    primary key (groupId, userGroupId)
);

create table YKT_PORTAL.IGFolder (
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

create table YKT_PORTAL.IGImage (
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

create table YKT_PORTAL.Image (
    imageId number(30,0) not null primary key,
    modifiedDate timestamp null,
    text_ clob null,
    type_ varchar2(75) null,
    height number(30,0),
    width number(30,0),
    size_ number(30,0)
);

create table YKT_PORTAL.JournalArticle (
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

create table YKT_PORTAL.JournalArticleImage (
    articleImageId number(30,0) not null primary key,
    groupId number(30,0),
    articleId varchar2(75) null,
    version number(30,20),
    elName varchar2(75) null,
    languageId varchar2(75) null,
    tempImage number(1, 0)
);

create table YKT_PORTAL.JournalArticleResource (
    resourcePrimKey number(30,0) not null primary key,
    groupId number(30,0),
    articleId varchar2(75) null
);

create table YKT_PORTAL.JournalContentSearch (
    contentSearchId number(30,0) not null primary key,
    groupId number(30,0),
    companyId number(30,0),
    privateLayout number(1, 0),
    layoutId number(30,0),
    portletId varchar2(200) null,
    articleId varchar2(75) null
);

create table YKT_PORTAL.JournalFeed (
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

create table YKT_PORTAL.JournalStructure (
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

create table YKT_PORTAL.JournalTemplate (
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

create table YKT_PORTAL.Layout (
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

create table YKT_PORTAL.LayoutSet (
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

create table YKT_PORTAL.ListType (
    listTypeId number(30,0) not null primary key,
    name varchar2(75) null,
    type_ varchar2(75) null
);

create table YKT_PORTAL.MBBan (
    banId number(30,0) not null primary key,
    groupId number(30,0),
    companyId number(30,0),
    userId number(30,0),
    userName varchar2(75) null,
    createDate timestamp null,
    modifiedDate timestamp null,
    banUserId number(30,0)
);

create table YKT_PORTAL.MBCategory (
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

create table YKT_PORTAL.MBDiscussion (
    discussionId number(30,0) not null primary key,
    classNameId number(30,0),
    classPK number(30,0),
    threadId number(30,0)
);

create table YKT_PORTAL.MBMessage (
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

create table YKT_PORTAL.MBMessageFlag (
    messageFlagId number(30,0) not null primary key,
    userId number(30,0),
    messageId number(30,0),
    flag number(30,0)
);

create table YKT_PORTAL.MBStatsUser (
    statsUserId number(30,0) not null primary key,
    groupId number(30,0),
    userId number(30,0),
    messageCount number(30,0),
    lastPostDate timestamp null
);

create table YKT_PORTAL.MBThread (
    threadId number(30,0) not null primary key,
    categoryId number(30,0),
    rootMessageId number(30,0),
    messageCount number(30,0),
    viewCount number(30,0),
    lastPostByUserId number(30,0),
    lastPostDate timestamp null,
    priority number(30,20)
);

create table YKT_PORTAL.MembershipRequest (
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

create table YKT_PORTAL.Organization_ (
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

create table YKT_PORTAL.OrgGroupPermission (
    organizationId number(30,0) not null,
    groupId number(30,0) not null,
    permissionId number(30,0) not null,
    primary key (organizationId, groupId, permissionId)
);

create table YKT_PORTAL.OrgGroupRole (
    organizationId number(30,0) not null,
    groupId number(30,0) not null,
    roleId number(30,0) not null,
    primary key (organizationId, groupId, roleId)
);

create table YKT_PORTAL.OrgLabor (
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

create table YKT_PORTAL.PasswordPolicy (
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

create table YKT_PORTAL.PasswordPolicyRel (
    passwordPolicyRelId number(30,0) not null primary key,
    passwordPolicyId number(30,0),
    classNameId number(30,0),
    classPK number(30,0)
);

create table YKT_PORTAL.PasswordTracker (
    passwordTrackerId number(30,0) not null primary key,
    userId number(30,0),
    createDate timestamp null,
    password_ varchar2(75) null
);

create table YKT_PORTAL.Permission_ (
    permissionId number(30,0) not null primary key,
    companyId number(30,0),
    actionId varchar2(75) null,
    resourceId number(30,0)
);

create table YKT_PORTAL.Phone (
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

create table YKT_PORTAL.PluginSetting (
    pluginSettingId number(30,0) not null primary key,
    companyId number(30,0),
    pluginId varchar2(75) null,
    pluginType varchar2(75) null,
    roles varchar2(4000) null,
    active_ number(1, 0)
);

create table YKT_PORTAL.PollsChoice (
    uuid_ varchar2(75) null,
    choiceId number(30,0) not null primary key,
    questionId number(30,0),
    name varchar2(75) null,
    description varchar2(1000) null
);

create table YKT_PORTAL.PollsQuestion (
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

create table YKT_PORTAL.PollsVote (
    voteId number(30,0) not null primary key,
    userId number(30,0),
    questionId number(30,0),
    choiceId number(30,0),
    voteDate timestamp null
);

create table YKT_PORTAL.Portlet (
    id_ number(30,0) not null primary key,
    companyId number(30,0),
    portletId varchar2(200) null,
    roles varchar2(4000) null,
    active_ number(1, 0)
);

create table YKT_PORTAL.PortletPreferences (
    portletPreferencesId number(30,0) not null primary key,
    ownerId number(30,0),
    ownerType number(30,0),
    plid number(30,0),
    portletId varchar2(200) null,
    preferences clob null
);

create table YKT_PORTAL.RatingsEntry (
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

create table YKT_PORTAL.RatingsStats (
    statsId number(30,0) not null primary key,
    classNameId number(30,0),
    classPK number(30,0),
    totalEntries number(30,0),
    totalScore number(30,20),
    averageScore number(30,20)
);

create table YKT_PORTAL.Region (
    regionId number(30,0) not null primary key,
    countryId number(30,0),
    regionCode varchar2(75) null,
    name varchar2(75) null,
    active_ number(1, 0)
);

create table YKT_PORTAL.Release_ (
    releaseId number(30,0) not null primary key,
    createDate timestamp null,
    modifiedDate timestamp null,
    buildNumber number(30,0),
    buildDate timestamp null,
    verified number(1, 0)
);

create table YKT_PORTAL.Resource_ (
    resourceId number(30,0) not null primary key,
    codeId number(30,0),
    primKey varchar2(300) null
);

create table YKT_PORTAL.ResourceCode (
    codeId number(30,0) not null primary key,
    companyId number(30,0),
    name varchar2(300) null,
    scope number(30,0)
);

create table YKT_PORTAL.Role_ (
    roleId number(30,0) not null primary key,
    companyId number(30,0),
    classNameId number(30,0),
    classPK number(30,0),
    name varchar2(75) null,
    description varchar2(4000) null,
    type_ number(30,0)
);

create table YKT_PORTAL.Roles_Permissions (
    roleId number(30,0) not null,
    permissionId number(30,0) not null,
    primary key (roleId, permissionId)
);

create table YKT_PORTAL.SCFrameworkVersi_SCProductVers (
    productVersionId number(30,0) not null,
    frameworkVersionId number(30,0) not null,
    primary key (productVersionId, frameworkVersionId)
);

create table YKT_PORTAL.SCFrameworkVersion (
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

create table YKT_PORTAL.SCLicense (
    licenseId number(30,0) not null primary key,
    name varchar2(75) null,
    url varchar2(4000) null,
    openSource number(1, 0),
    active_ number(1, 0),
    recommended number(1, 0)
);

create table YKT_PORTAL.SCLicenses_SCProductEntries (
    productEntryId number(30,0) not null,
    licenseId number(30,0) not null,
    primary key (productEntryId, licenseId)
);

create table YKT_PORTAL.SCProductEntry (
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

create table YKT_PORTAL.SCProductScreenshot (
    productScreenshotId number(30,0) not null primary key,
    companyId number(30,0),
    groupId number(30,0),
    productEntryId number(30,0),
    thumbnailId number(30,0),
    fullImageId number(30,0),
    priority number(30,0)
);

create table YKT_PORTAL.SCProductVersion (
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

create table YKT_PORTAL.ServiceComponent (
    serviceComponentId number(30,0) not null primary key,
    buildNamespace varchar2(75) null,
    buildNumber number(30,0),
    buildDate number(30,0),
    data_ clob null
);

create table YKT_PORTAL.ShoppingCart (
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

create table YKT_PORTAL.ShoppingCategory (
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

create table YKT_PORTAL.ShoppingCoupon (
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

create table YKT_PORTAL.ShoppingItem (
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

create table YKT_PORTAL.ShoppingItemField (
    itemFieldId number(30,0) not null primary key,
    itemId number(30,0),
    name varchar2(75) null,
    values_ varchar2(4000) null,
    description varchar2(4000) null
);

create table YKT_PORTAL.ShoppingItemPrice (
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

create table YKT_PORTAL.ShoppingOrder (
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

create table YKT_PORTAL.ShoppingOrderItem (
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

create table YKT_PORTAL.Subscription (
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

create table YKT_PORTAL.TagsAsset (
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

create table YKT_PORTAL.TagsAssets_TagsEntries (
    assetId number(30,0) not null,
    entryId number(30,0) not null,
    primary key (assetId, entryId)
);

create table YKT_PORTAL.TagsEntry (
    entryId number(30,0) not null primary key,
    companyId number(30,0),
    userId number(30,0),
    userName varchar2(75) null,
    createDate timestamp null,
    modifiedDate timestamp null,
    name varchar2(75) null
);

create table YKT_PORTAL.TagsProperty (
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

create table YKT_PORTAL.TagsSource (
    sourceId number(30,0) not null primary key,
    parentSourceId number(30,0),
    name varchar2(75) null,
    acronym varchar2(75) null
);

create table YKT_PORTAL.User_ (
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

create table YKT_PORTAL.UserGroup (
    userGroupId number(30,0) not null primary key,
    companyId number(30,0),
    parentUserGroupId number(30,0),
    name varchar2(75) null,
    description varchar2(4000) null
);

create table YKT_PORTAL.UserGroupRole (
    userId number(30,0) not null,
    groupId number(30,0) not null,
    roleId number(30,0) not null,
    primary key (userId, groupId, roleId)
);

create table YKT_PORTAL.UserIdMapper (
    userIdMapperId number(30,0) not null primary key,
    userId number(30,0),
    type_ varchar2(75) null,
    description varchar2(75) null,
    externalUserId varchar2(75) null
);

create table YKT_PORTAL.Users_Groups (
    userId number(30,0) not null,
    groupId number(30,0) not null,
    primary key (userId, groupId)
);

create table YKT_PORTAL.Users_Orgs (
    userId number(30,0) not null,
    organizationId number(30,0) not null,
    primary key (userId, organizationId)
);

create table YKT_PORTAL.Users_Permissions (
    userId number(30,0) not null,
    permissionId number(30,0) not null,
    primary key (userId, permissionId)
);

create table YKT_PORTAL.Users_Roles (
    userId number(30,0) not null,
    roleId number(30,0) not null,
    primary key (userId, roleId)
);

create table YKT_PORTAL.Users_UserGroups (
    userId number(30,0) not null,
    userGroupId number(30,0) not null,
    primary key (userId, userGroupId)
);

create table YKT_PORTAL.UserTracker (
    userTrackerId number(30,0) not null primary key,
    companyId number(30,0),
    userId number(30,0),
    modifiedDate timestamp null,
    sessionId varchar2(200) null,
    remoteAddr varchar2(75) null,
    remoteHost varchar2(75) null,
    userAgent varchar2(200) null
);

create table YKT_PORTAL.UserTrackerPath (
    userTrackerPathId number(30,0) not null primary key,
    userTrackerId number(30,0),
    path_ varchar2(4000) null,
    pathDate timestamp null
);

create table YKT_PORTAL.WebDAVProps (
    webDavPropsId number(30,0) not null primary key,
    companyId number(30,0),
    createDate timestamp null,
    modifiedDate timestamp null,
    classNameId number(30,0),
    classPK number(30,0),
    props clob null
);

create table YKT_PORTAL.Website (
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

create table YKT_PORTAL.WikiNode (
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

create table YKT_PORTAL.WikiPage (
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

create table YKT_PORTAL.WikiPageResource (
    resourcePrimKey number(30,0) not null primary key,
    nodeId number(30,0),
    title varchar2(75) null
);


delete from YKT_PORTAL.INFO_TYPE;
--
-- TABLE INSERT STATEMENTS
--
INSERT INTO YKT_PORTAL.INFO_TYPE ( INFO_TYPE, INFO_NAME ) VALUES ('4','FAQ');
INSERT INTO YKT_PORTAL.INFO_TYPE ( INFO_TYPE, INFO_NAME ) VALUES ('4.1','FAQ综述');
INSERT INTO YKT_PORTAL.INFO_TYPE ( INFO_TYPE, INFO_NAME ) VALUES ('4.2','照片相关');
INSERT INTO YKT_PORTAL.INFO_TYPE ( INFO_TYPE, INFO_NAME ) VALUES ('4.3','卡片使用');
INSERT INTO YKT_PORTAL.INFO_TYPE ( INFO_TYPE, INFO_NAME ) VALUES ('4.4','一卡通设备使用');
INSERT INTO YKT_PORTAL.INFO_TYPE ( INFO_TYPE, INFO_NAME ) VALUES ('4.5','查询网站使用');
INSERT INTO YKT_PORTAL.INFO_TYPE ( INFO_TYPE, INFO_NAME ) VALUES ('4.6','校园卡办理');
INSERT INTO YKT_PORTAL.INFO_TYPE ( INFO_TYPE, INFO_NAME ) VALUES ('4.7','联系方式');


delete from YKT_PORTAL.Ecard_Information; 
-- TABLE INSERT STATEMENTS
--
INSERT INTO YKT_PORTAL.ECARD_INFORMATION ( ID, INFO_TYPE, INFO_TITLE, INFO_CONTENT, ATTACHMENTS, CREATE_DATE, CREATER ) 
         VALUES ( 1, '8', '', '', '', CURRENT_TIMESTAMP , 'admin' );
INSERT INTO YKT_PORTAL.ECARD_INFORMATION ( ID, INFO_TYPE, INFO_TITLE, INFO_CONTENT, ATTACHMENTS, CREATE_DATE, CREATER ) 
         VALUES ( 2, '9', '', '', '', CURRENT_TIMESTAMP , 'admin' );
         
         
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1806, 14, 1, 0, 1, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">首页</name>
  <name language-id="en_US">Home</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">首页</title>
  <title language-id="en_US">Home</title>
</root>
',
 'portlet', 'column-3=ecardnews
column-2=ecardhit,
column-1=ext_login_png,
state-max=
state-min=
layout-template-id=1_2_1_columns
column-4=',
 0, '/home', 0, 0, 'brochure','', 0);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1807, 14, 1, 0, 2, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">校园卡简介</name>
  <name language-id="en_US">EcardAbout</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">校园卡简介</title>
  <title language-id="en_US">EcardAbout</title>
</root>',
 'portlet', 'column-1=ecardabout,
layout-template-id=1_column',
 0, '/ecardabout', 0, 0, 'brochure','', 1);
 
 insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1808, 14, 1, 0, 3, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">服务网点</name>
  <name language-id="en_US">ServicePoint</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">服务网点</title>
  <title language-id="en_US">ServiceNet</title>
</root>
',
 'portlet', 'column-1=serviceplace,
layout-template-id=1_column',
 0, '/serviceplace', 0, 0, 'brochure','', 2);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1809, 14, 1, 0, 4, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>

<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">规章制度</name>
  <name language-id="en_US">EcardRules</name>
</root>
',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">规章制度</title>
  <title language-id="en_US">EcardRules</title>
</root>
',
 'portlet', 'column-1=ecardrule,
layout-template-id=1_column',
 0, '/ecardrules', 0, 0, 'brochure','', 3);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1810, 14, 1, 0, 5, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">使用指南</name>
  <name language-id="en_US">EcardTurtorial</name>
</root>
',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">使用指南</title>
  <title language-id="en_US">EcardTurtorial</title>
</root>',
 'portlet', 'column-1=ecardtutorial,
layout-template-id=1_column',
 0, '/ecardturtorial', 0, 0, 'brochure','', 4);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1811, 14, 1, 0, 6, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<name language-id="zh_CN">业务办理</name>
	<name language-id="en_US">DoBusiness</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<title language-id="zh_CN">业务办理</title>
	<title language-id="en_US">DoBusiness</title>
</root>',
 'link_to_layout', 'privateLayout=false
groupId=14
sitemap-include=1
sitemap-changefreq=daily
target=
meta-robots=
linkToLayoutId=10
meta-description=
javascript-3=
sitemap-priority=
javascript-2=
javascript-1=
meta-keywords=',
 0, '/ecardbusiness', 0, 0, 'brochure','', 5);
 
  insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (320001, 14, 1, 0, 14, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<name language-id="zh_CN">办卡流程</name>
	<name language-id="en_US"></name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<title language-id="zh_CN">办卡流程</title>
	<title language-id="en_US"></title>
</root>',
 'portlet', 'column-1=ecardcardprocess
layout-template-id=1_column
state-min=
state-max-previous=
sitemap-include=1
state-max=
sitemap-changefreq=daily
meta-robots=
meta-description=
javascript-3=
javascript-2=
sitemap-priority=
meta-keywords=
javascript-1=',
 0, '/cardprocess', 0, 0, 'brochure','', 7);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1813, 14, 1, 0, 8, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">文档下载</name>
  <name language-id="en_US">EcardDoc</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">文档下载</title>
  <title language-id="en_US">EcardDoc</title>
</root>',
 'portlet', 'column-1=ecarddoc,
layout-template-id=1_2_columns_i',
 0, '/ecardservice', 0, 0, 'brochure','', 8);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1814, 14, 1, 1, 1, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>

<root default-locale="zh_CN" available-locales="en_US,zh_CN">
 <name language-id="en_US">card</name>
 <name language-id="zh_CN">卡片使用</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>

<root default-locale="zh_CN" available-locales="en_US,zh_CN">
  <title language-id="en_US">card</title>
  <title language-id="zh_CN">卡片使用</title>
</root>',
 'portlet', 'column-1=querydetail,querygatedetail,cardlost,
layout-template-id=2_columns_i
state-min=
state-max-previous=querygatedetail
sitemap-include=1
state-max=
sitemap-changefreq=daily
meta-robots=
meta-description=
javascript-3=
sitemap-priority=
javascript-2=
javascript-1=
meta-keywords=
column-2=carddelay,picdelay,',
 0, '/card', 0, 0, 'brochure','', 0);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1815, 14, 1, 1, 2, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>'||CHR(10)||''||CHR(10)||'<root default-locale="zh_CN" available-locales="en_US,zh_CN">'||CHR(10)||' <name language-id="en_US">message</name>'||CHR(10)||' <name language-id="zh_CN">留言本</name>'||CHR(10)||'</root>',
 '<?xml version="1.0" encoding="UTF-8"?>'||CHR(10)||''||CHR(10)||'<root default-locale="zh_CN" available-locales="en_US,zh_CN">'||CHR(10)||'    <title language-id="en_US">message</title>'||CHR(10)||' <title language-id="zh_CN">留言本</title>'||CHR(10)||'</root>',
 'portlet', 'column-1=ecardmsgboard'||CHR(10)||'layout-template-id=1_column'||CHR(10)||'state-min='||CHR(10)||'state-max-previous='||CHR(10)||'sitemap-include=1'||CHR(10)||'state-max='||CHR(10)||'sitemap-changefreq=daily'||CHR(10)||'meta-robots='||CHR(10)||'meta-description='||CHR(10)||'javascript-3='||CHR(10)||'sitemap-priority='||CHR(10)||'javascript-2='||CHR(10)||'javascript-1='||CHR(10)||'meta-keywords=',
 0, '/msg', 0, 0, 'brochure','', 1);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (300772, 14, 1, 0, 9, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">服务信息</name>
  <name language-id="en_US">ServiceInfo</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">服务信息</title>
  <title language-id="en_US">ServiceInfo</title>
</root>',
 'portlet', 'column-1=ecardservice,
layout-template-id=1_2_columns_i',
 0, '/serviceinfo', 0, 0, 'brochure','', 8);
 
 insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (307012, 14, 1, 0, 10, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<name language-id="zh_CN">用户登陆</name>
	<name language-id="en_US">UserLogin</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<title language-id="zh_CN">用户登陆</title>
	<title language-id="en_US">UserLogin</title>
</root>',
 'portlet', 'column-1=ext_login
layout-template-id=1_column
state-min=
state-max-previous=
sitemap-include=1
state-max=
sitemap-changefreq=daily
meta-robots=
meta-description=
javascript-3=
javascript-2=
sitemap-priority=
javascript-1=
meta-keywords=',
 1, '', 0, 0, 'brochure','', 9);
 
 insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (307018, 14, 1, 0, 11, 6, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<name language-id="zh_CN">校园卡挂失</name>
	<name language-id="en_US">cardLost</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<title language-id="zh_CN">校园卡挂失</title>
	<title language-id="en_US">cardLost</title>
</root>',
 'link_to_layout', 'privateLayout=false
groupId=14
sitemap-include=1
sitemap-changefreq=daily
target=
meta-robots=
linkToLayoutId=10
meta-description=
javascript-3=
sitemap-priority=
javascript-2=
javascript-1=
meta-keywords=',
 0, '', 0, 0, 'brochure','', 0);
 
 insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (307019, 14, 1, 0, 12, 6, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<name language-id="zh_CN">消费明细查询</name>
	<name language-id="en_US"></name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
	<title language-id="zh_CN">消费明细查询</title>
	<title language-id="en_US"></title>
</root>',
 'link_to_layout', 'privateLayout=false
groupId=14
sitemap-include=1
sitemap-changefreq=daily
target=
meta-robots=
linkToLayoutId=10
meta-description=
javascript-3=
sitemap-priority=
javascript-2=
javascript-1=
meta-keywords=',
 0, '', 0, 0, 'brochure','', 1);
 

 
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1816, 83, 1, 0, 1, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">首页</name>
  <name language-id="en_US">Home</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">首页</title>
  <title language-id="en_US">Home</title>
</root>',
 'portlet', 'column-3=
state-max-previous=86
column-2=
column-1=ecardnews,ecardhit,ext_shopbrasdetail,ext_shopdinnertotalreport,79,ext_shoptotalreport
state-max=
state-min=
layout-template-id=1_2_1_columns
column-4=ext_shopaccountdetail,ext_shopcatalogreport,ext_shoptodayreport,ext_shopposdinnerreport,ext_shopposcatalogreport,',
 0, '/home', 0, 0, 'adminbrochure','', 0);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1817, 83, 1, 0, 2, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">校园卡简介</name>
  <name language-id="en_US">EcardAbout</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">校园卡简介</title>
  <title language-id="en_US">EcardAbout</title>
</root>',
 'portlet', 'column-1=ecardabout,
layout-template-id=1_column',
 0, '/ecardabout', 0, 0, 'adminbrochure','', 1);
 
 insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1818, 83, 1, 0, 3, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>
<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <name language-id="zh_CN">服务网点</name>
  <name language-id="en_US">ServiceNet</name>
</root>',
 '<?xml version="1.0" encoding="UTF-8"?>

<root available-locales="zh_CN,en_US" default-locale="zh_CN">
  <title language-id="zh_CN">服务网点</title>
  <title language-id="en_US">ServiceNet</title>
</root>',
 'portlet', 'column-1=serviceplace,
layout-template-id=1_column',
 0, '', 0, 0, 'adminbrochure','', 2);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1819, 83, 1, 0, 4, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>'||CHR(10)||''||CHR(10)||'<root default-locale="zh_CN" available-locales="en_US,zh_CN">'||CHR(10)||' <name language-id="en_US">Rules</name>'||CHR(10)||' <name language-id="zh_CN">规章制度</name>'||CHR(10)||'</root>',
 '<?xml version="1.0" encoding="UTF-8"?>'||CHR(10)||''||CHR(10)||'<root default-locale="zh_CN" available-locales="en_US,zh_CN">'||CHR(10)||'    <title language-id="en_US">Rules</title>'||CHR(10)||'   <title language-id="zh_CN">规章制度</title>'||CHR(10)||'</root>',
 'portlet', 'column-1=ecardrule'||CHR(10)||'layout-template-id=1_2_columns_i'||CHR(10)||'state-min='||CHR(10)||'state-max-previous='||CHR(10)||'sitemap-include=1'||CHR(10)||'state-max='||CHR(10)||'sitemap-changefreq=daily'||CHR(10)||'meta-robots='||CHR(10)||'meta-description='||CHR(10)||'javascript-3='||CHR(10)||'sitemap-priority='||CHR(10)||'javascript-2='||CHR(10)||'column-3='||CHR(10)||'javascript-1='||CHR(10)||'meta-keywords='||CHR(10)||'column-2=',
 0, '/ecardrules', 0, 0, 'adminbrochure','', 3);
 
insert into ykt_portal.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, 
name, 
title, 
type_, typeSettings,
 hidden_, friendlyURL, iconImage, iconImageId,themeid, css, priority) values 
 (1820, 83, 1, 0, 5, 0, 
 '<?xml version="1.0" encoding="UTF-8"?>'||CHR(10)||''||CHR(10)||'<root default-locale="zh_CN" available-locales="en_US,zh_CN">'||CHR(10)||' <name language-id="en_US">Turtorial</name>'||CHR(10)||' <name language-id="zh_CN">操作指南</name>'||CHR(10)||'</root>',
 '<?xml version="1.0" encoding="UTF-8"?>'||CHR(10)||''||CHR(10)||'<root default-locale="zh_CN" available-locales="en_US,zh_CN">'||CHR(10)||'    <title language-id="en_US">Turtorial</title>'||CHR(10)||'   <title language-id="zh_CN">操作指南</title>'||CHR(10)||'</root>',
 'portlet', 'column-1=ecardtutorial'||CHR(10)||'layout-template-id=1_2_columns_i'||CHR(10)||'state-min='||CHR(10)||'state-max-previous='||CHR(10)||'sitemap-include=1'||CHR(10)||'state-max='||CHR(10)||'sitemap-changefreq=daily'||CHR(10)||'meta-robots='||CHR(10)||'meta-description='||CHR(10)||'javascript-3='||CHR(10)||'sitemap-priority='||CHR(10)||'javascript-2='||CHR(10)||'column-3='||CHR(10)||'javascript-1='||CHR(10)||'meta-keywords='||CHR(10)||'column-2=',
 0, '/ecardturtorial', 0, 0, 'adminbrochure','', 4);
 

insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (1, 'Canada', 'CA', 'CAN', '124', '001', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (2, 'China', 'CN', 'CHN', '156', '086', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (3, 'France', 'FR', 'FRA', '250', '033', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (4, 'Germany', 'DE', 'DEU', '276', '049', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (5, 'Hong Kong', 'HK', 'HKG', '344', '852', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (6, 'Hungary', 'HU', 'HUN', '348', '036', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (7, 'Israel', 'IL', 'ISR', '376', '972', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (8, 'Italy', 'IT', 'ITA', '380', '039', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (9, 'Japan', 'JP', 'JPN', '392', '081', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (10, 'South Korea', 'KP', 'KOR', '410', '082', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (11, 'Netherlands', 'NL', 'NLD', '528', '031', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (12, 'Portugal', 'PT', 'PRT', '620', '351', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (13, 'Russia', 'RU', 'RUS', '643', '007', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (14, 'Singapore', 'SG', 'SGP', '702', '065', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (15, 'Spain', 'ES', 'ESP', '724', '034', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (16, 'Turkey', 'TR', 'TUR', '792', '090', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (17, 'Vietnam', 'VM', 'VNM', '704', '084', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (18, 'United Kingdom', 'GB', 'GBR', '826', '044', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (19, 'United States', 'US', 'USA', '840', '001', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (20, 'Afghanistan', 'AF', 'AFG', '4', '093', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (21, 'Albania', 'AL', 'ALB', '8', '355', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (22, 'Algeria', 'DZ', 'DZA', '12', '213', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (23, 'American Samoa', 'AS', 'ASM', '16', '684', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (24, 'Andorra', 'AD', 'AND', '20', '376', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (25, 'Angola', 'AO', 'AGO', '24', '244', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (26, 'Anguilla', 'AI', 'AIA', '660', '264', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (27, 'Antarctica', 'AQ', 'ATA', '10', '672', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (28, 'Antigua', 'AG', 'ATG', '28', '268', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (29, 'Argentina', 'AR', 'ARG', '32', '054', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (30, 'Armenia', 'AM', 'ARM', '51', '374', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (31, 'Aruba', 'AW', 'ABW', '533', '297', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (32, 'Australia', 'AU', 'AUS', '36', '061', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (33, 'Austria', 'AT', 'AUT', '40', '043', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (34, 'Azerbaijan', 'AZ', 'AZE', '31', '994', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (35, 'Bahamas', 'BS', 'BHS', '44', '242', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (36, 'Bahrain', 'BH', 'BHR', '48', '973', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (37, 'Bangladesh', 'BD', 'BGD', '50', '880', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (38, 'Barbados', 'BB', 'BRB', '52', '246', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (39, 'Belarus', 'BY', 'BLR', '112', '375', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (40, 'Belgium', 'BE', 'BEL', '56', '032', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (41, 'Belize', 'BZ', 'BLZ', '84', '501', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (42, 'Benin', 'BJ', 'BEN', '204', '229', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (43, 'Bermuda', 'BM', 'BMU', '60', '441', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (44, 'Bhutan', 'BT', 'BTN', '64', '975', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (45, 'Bolivia', 'BO', 'BOL', '68', '591', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (46, 'Bosnia-Herzegovina', 'BA', 'BIH', '70', '387', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (47, 'Botswana', 'BW', 'BWA', '72', '267', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (48, 'Brazil', 'BR', 'BRA', '76', '055', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (49, 'British Virgin Islands', 'VG', 'VGB', '92', '284', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (50, 'Brunei', 'BN', 'BRN', '96', '673', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (51, 'Bulgaria', 'BG', 'BGR', '100', '359', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (52, 'Burkina Faso', 'BF', 'BFA', '854', '226', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (53, 'Burma (Myanmar)', 'MM', 'MMR', '104', '095', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (54, 'Burundi', 'BI', 'BDI', '108', '257', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (55, 'Cambodia', 'KH', 'KHM', '116', '855', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (56, 'Cameroon', 'CM', 'CMR', '120', '237', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (57, 'Cape Verde Island', 'CV', 'CPV', '132', '238', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (58, 'Cayman Islands', 'KY', 'CYM', '136', '345', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (59, 'Central African Republic', 'CF', 'CAF', '140', '236', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (60, 'Chad', 'TD', 'TCD', '148', '235', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (61, 'Chile', 'CL', 'CHL', '152', '056', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (62, 'Christmas Island', 'CX', 'CXR', '162', '061', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (63, 'Cocos Islands', 'CC', 'CCK', '166', '061', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (64, 'Colombia', 'CO', 'COL', '170', '057', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (65, 'Comoros', 'KM', 'COM', '174', '269', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (66, 'Republic of Congo', 'CD', 'COD', '180', '242', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (67, 'Democratic Republic of Congo', 'CG', 'COG', '178', '243', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (68, 'Cook Islands', 'CK', 'COK', '184', '682', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (69, 'Costa Rica', 'CI', 'CRI', '188', '506', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (70, 'Croatia', 'HR', 'HRV', '191', '385', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (71, 'Cuba', 'CU', 'CUB', '192', '053', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (72, 'Cyprus', 'CY', 'CYP', '196', '357', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (73, 'Czech Republic', 'CZ', 'CZE', '203', '420', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (74, 'Denmark', 'DK', 'DNK', '208', '045', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (75, 'Djibouti', 'DJ', 'DJI', '262', '253', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (76, 'Dominica', 'DM', 'DMA', '212', '767', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (77, 'Dominican Republic', 'DO', 'DOM', '214', '809', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (78, 'Ecuador', 'EC', 'ECU', '218', '593', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (79, 'Egypt', 'EG', 'EGY', '818', '020', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (80, 'El Salvador', 'SV', 'SLV', '222', '503', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (81, 'Equatorial Guinea', 'GQ', 'GNQ', '226', '240', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (82, 'Eritrea', 'ER', 'ERI', '232', '291', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (83, 'Estonia', 'EE', 'EST', '233', '372', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (84, 'Ethiopia', 'ET', 'ETH', '231', '251', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (85, 'Faeroe Islands', 'FO', 'FRO', '234', '298', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (86, 'Falkland Islands', 'FK', 'FLK', '238', '500', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (87, 'Fiji Islands', 'FJ', 'FJI', '242', '679', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (88, 'Finland', 'FI', 'FIN', '246', '358', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (89, 'French Guiana', 'GF', 'GUF', '254', '594', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (90, 'French Polynesia', 'PF', 'PYF', '258', '689', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (91, 'Gabon', 'GA', 'GAB', '266', '241', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (92, 'Gambia', 'GM', 'GMB', '270', '220', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (93, 'Georgia', 'GE', 'GEO', '268', '995', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (94, 'Ghana', 'GH', 'GHA', '288', '233', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (95, 'Gibraltar', 'GI', 'GIB', '292', '350', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (96, 'Greece', 'GR', 'GRC', '300', '030', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (97, 'Greenland', 'GL', 'GRL', '304', '299', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (98, 'Grenada', 'GD', 'GRD', '308', '473', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (99, 'Guadeloupe', 'GP', 'GLP', '312', '590', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (100, 'Guam', 'GU', 'GUM', '316', '671', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (101, 'Guatemala', 'GT', 'GTM', '320', '502', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (102, 'Guinea', 'GN', 'GIN', '324', '224', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (103, 'Guinea-Bissau', 'GW', 'GNB', '624', '245', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (104, 'Guyana', 'GY', 'GUY', '328', '592', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (105, 'Haiti', 'HT', 'HTI', '332', '509', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (106, 'Honduras', 'HN', 'HND', '340', '504', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (107, 'Iceland', 'IS', 'ISL', '352', '354', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (108, 'India', 'IN', 'IND', '356', '091', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (109, 'Indonesia', 'ID', 'IDN', '360', '062', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (110, 'Iran', 'IR', 'IRN', '364', '098', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (111, 'Iraq', 'IQ', 'IRQ', '368', '964', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (112, 'Ireland', 'IE', 'IRL', '372', '353', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (113, 'Ivory Coast', 'CI', 'CIV', '384', '225', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (114, 'Jamaica', 'JM', 'JAM', '388', '876', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (115, 'Jordan', 'JO', 'JOR', '400', '962', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (116, 'Kazakhstan', 'KZ', 'KAZ', '398', '007', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (117, 'Kenya', 'KE', 'KEN', '404', '254', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (118, 'Kiribati', 'KI', 'KIR', '408', '686', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (119, 'Kuwait', 'KW', 'KWT', '414', '965', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (120, 'North Korea', 'KP', 'PRK', '408', '850', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (121, 'Kyrgyzstan', 'KG', 'KGZ', '471', '996', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (122, 'Laos', 'LA', 'LAO', '418', '856', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (123, 'Latvia', 'LV', 'LVA', '428', '371', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (124, 'Lebanon', 'LB', 'LBN', '422', '961', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (125, 'Lesotho', 'LS', 'LSO', '426', '266', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (126, 'Liberia', 'LR', 'LBR', '430', '231', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (127, 'Libya', 'LY', 'LBY', '434', '218', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (128, 'Liechtenstein', 'LI', 'LIE', '438', '423', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (129, 'Lithuania', 'LT', 'LTU', '440', '370', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (130, 'Luxembourg', 'LU', 'LUX', '442', '352', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (131, 'Macau', 'MO', 'MAC', '446', '853', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (132, 'Macedonia', 'MK', 'MKD', '807', '389', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (133, 'Madagascar', 'MG', 'MDG', '450', '261', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (134, 'Malawi', 'MW', 'MWI', '454', '265', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (135, 'Malaysia', 'MY', 'MYS', '458', '060', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (136, 'Maldives', 'MV', 'MDV', '462', '960', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (137, 'Mali', 'ML', 'MLI', '466', '223', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (138, 'Malta', 'MT', 'MLT', '470', '356', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (139, 'Marshall Islands', 'MH', 'MHL', '584', '692', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (140, 'Martinique', 'MQ', 'MTQ', '474', '596', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (141, 'Mauritania', 'MR', 'MRT', '478', '222', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (142, 'Mauritius', 'MU', 'MUS', '480', '230', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (143, 'Mayotte Island', 'YT', 'MYT', '175', '269', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (144, 'Mexico', 'MX', 'MEX', '484', '052', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (145, 'Micronesia', 'FM', 'FSM', '583', '691', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (146, 'Moldova', 'MD', 'MDA', '498', '373', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (147, 'Monaco', 'MC', 'MCO', '492', '377', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (148, 'Mongolia', 'MN', 'MNG', '496', '976', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (149, 'Montserrat', 'MS', 'MSR', '500', '664', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (150, 'Morocco', 'MA', 'MAR', '504', '212', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (151, 'Mozambique', 'MZ', 'MOZ', '508', '258', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (152, 'Myanmar (Burma)', 'MM', 'MMR', '104', '095', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (153, 'Namibia', 'NA', 'NAM', '516', '264', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (154, 'Nauru', 'NR', 'NRU', '520', '674', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (155, 'Nepal', 'NP', 'NPL', '524', '977', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (156, 'Netherlands Antilles', 'AN', 'ANT', '530', '599', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (157, 'New Caledonia', 'NC', 'NCL', '540', '687', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (158, 'New Zealand', 'NZ', 'NZL', '554', '064', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (159, 'Nicaragua', 'NE', 'NER', '558', '505', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (160, 'Niger', 'NE', 'NER', '562', '227', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (161, 'Nigeria', 'NG', 'NGA', '566', '234', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (162, 'Niue', 'NU', 'NIU', '570', '683', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (163, 'Norfolk Island', 'NF', 'NFK', '574', '672', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (164, 'Norway', 'NO', 'NOR', '578', '047', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (165, 'Oman', 'OM', 'OMN', '512', '968', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (166, 'Pakistan', 'PK', 'PAK', '586', '092', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (167, 'Palau', 'PW', 'PLW', '585', '680', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (168, 'Palestine', 'PS', 'PSE', '275', '970', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (169, 'Panama', 'PA', 'PAN', '591', '507', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (170, 'Papua New Guinea', 'PG', 'PNG', '598', '675', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (171, 'Paraguay', 'PY', 'PRY', '600', '595', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (172, 'Peru', 'PE', 'PER', '604', '051', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (173, 'Philippines', 'PH', 'PHL', '608', '063', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (174, 'Poland', 'PL', 'POL', '616', '048', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (175, 'Puerto Rico', 'PR', 'PRI', '630', '787', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (176, 'Qatar', 'QA', 'QAT', '634', '974', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (177, 'Reunion Island', 'RE', 'REU', '638', '262', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (178, 'Romania', 'RO', 'ROU', '642', '040', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (179, 'Rwanda', 'RW', 'RWA', '646', '250', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (180, 'St. Helena', 'SH', 'SHN', '654', '290', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (181, 'St. Kitts', 'KN', 'KNA', '659', '869', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (182, 'St. Lucia', 'LC', 'LCA', '662', '758', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (183, 'St. Pierre & Miquelon', 'PM', 'SPM', '666', '508', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (184, 'St. Vincent', 'VC', 'VCT', '670', '784', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (185, 'San Marino', 'SM', 'SMR', '674', '378', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (186, 'Sao Tome & Principe', 'ST', 'STP', '678', '239', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (187, 'Saudi Arabia', 'SA', 'SAU', '682', '966', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (188, 'Senegal', 'SN', 'SEN', '686', '221', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (189, 'Serbia', 'CS', 'SCG', '891', '381', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (190, 'Seychelles', 'SC', 'SYC', '690', '248', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (191, 'Sierra Leone', 'SL', 'SLE', '694', '249', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (192, 'Slovakia', 'SK', 'SVK', '703', '421', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (193, 'Slovenia', 'SI', 'SVN', '705', '386', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (194, 'Solomon Islands', 'SB', 'SLB', '90', '677', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (195, 'Somalia', 'SO', 'SOM', '706', '252', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (196, 'South Africa', 'ZA', 'ZAF', '710', '027', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (197, 'Sri Lanka', 'LK', 'LKA', '144', '094', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (198, 'Sudan', 'SD', 'SDN', '736', '095', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (199, 'Suriname', 'SR', 'SUR', '740', '597', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (200, 'Swaziland', 'SZ', 'SWZ', '748', '268', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (201, 'Sweden', 'SE', 'SWE', '752', '046', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (202, 'Switzerland', 'CH', 'CHE', '756', '041', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (203, 'Syria', 'SY', 'SYR', '760', '963', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (204, 'Taiwan', 'TW', 'TWN', '158', '886', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (205, 'Tajikistan', 'TJ', 'TJK', '762', '992', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (206, 'Tanzania', 'TZ', 'TZA', '834', '255', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (207, 'Thailand', 'TH', 'THA', '764', '066', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (208, 'Togo', 'TG', 'TGO', '768', '228', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (209, 'Tonga', 'TO', 'TON', '776', '676', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (210, 'Trinidad & Tobago', 'TT', 'TTO', '780', '868', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (211, 'Tunisia', 'TN', 'TUN', '788', '216', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (212, 'Turkmenistan', 'TM', 'TKM', '795', '993', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (213, 'Turks & Caicos', 'TC', 'TCA', '796', '649', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (214, 'Tuvalu', 'TV', 'TUV', '798', '688', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (215, 'Uganda', 'UG', 'UGA', '800', '256', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (216, 'Ukraine', 'UA', 'UKR', '804', '380', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (217, 'United Arab Emirates', 'AE', 'ARE', '784', '971', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (218, 'Uruguay', 'UY', 'URY', '858', '598', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (219, 'Uzbekistan', 'UZ', 'UZB', '860', '998', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (220, 'Vanuatu', 'VU', 'VUT', '548', '678', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (221, 'Vatican City', 'VA', 'VAT', '336', '039', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (222, 'Venezuela', 'VE', 'VEN', '862', '058', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (223, 'Wallis & Futuna', 'WF', 'WLF', '876', '681', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (224, 'Western Samoa', 'EH', 'ESH', '732', '685', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (225, 'Yemen', 'YE', 'YEM', '887', '967', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (226, 'Yugoslavia', 'MK', 'MKD', '446', '381', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (227, 'Zambia', 'ZM', 'ZMB', '894', '260', 1);
insert into YKT_PORTAL.Country (countryId, name, a2, a3, number_, idd_, active_) values (228, 'Zimbabwe', 'ZW', 'ZWE', '716', '263', 1);

insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (1, 19, 'AL', 'Alabama', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (2, 19, 'AK', 'Alaska', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (3, 19, 'AZ', 'Arizona', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (4, 19, 'AR', 'Arkansas', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (5, 19, 'CA', 'California', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (6, 19, 'CO', 'Colorado', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (7, 19, 'CT', 'Connecticut', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (8, 19, 'DC', 'District of Columbia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (9, 19, 'DE', 'Delaware', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (10, 19, 'FL', 'Florida', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (11, 19, 'GA', 'Georgia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (12, 19, 'HI', 'Hawaii', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (13, 19, 'ID', 'Idaho', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (14, 19, 'IL', 'Illinois', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (15, 19, 'IN', 'Indiana', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (16, 19, 'IA', 'Iowa', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (17, 19, 'KS', 'Kansas', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (18, 19, 'KY', 'Kentucky ', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (19, 19, 'LA', 'Louisiana ', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (20, 19, 'ME', 'Maine', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (21, 19, 'MD', 'Maryland', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (22, 19, 'MA', 'Massachusetts', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (23, 19, 'MI', 'Michigan', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (24, 19, 'MN', 'Minnesota', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (25, 19, 'MS', 'Mississippi', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (26, 19, 'MO', 'Missouri', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (27, 19, 'MT', 'Montana', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (28, 19, 'NE', 'Nebraska', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (29, 19, 'NV', 'Nevada', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (30, 19, 'NH', 'New Hampshire', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (31, 19, 'NJ', 'New Jersey', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (32, 19, 'NM', 'New Mexico', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (33, 19, 'NY', 'New York', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (34, 19, 'NC', 'North Carolina', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (35, 19, 'ND', 'North Dakota', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (36, 19, 'OH', 'Ohio', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (37, 19, 'OK', 'Oklahoma ', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (38, 19, 'OR', 'Oregon', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (39, 19, 'PA', 'Pennsylvania', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (40, 19, 'PR', 'Puerto Rico', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (41, 19, 'RI', 'Rhode Island', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (42, 19, 'SC', 'South Carolina', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (43, 19, 'SD', 'South Dakota', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (44, 19, 'TN', 'Tennessee', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (45, 19, 'TX', 'Texas', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (46, 19, 'UT', 'Utah', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (47, 19, 'VT', 'Vermont', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (48, 19, 'VA', 'Virginia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (49, 19, 'WA', 'Washington', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (50, 19, 'WV', 'West Virginia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (51, 19, 'WI', 'Wisconsin', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (52, 19, 'WY', 'Wyoming', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (53, 1, 'AL', 'Alberta', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (54, 1, 'BC', 'British Columbia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (55, 1, 'MB', 'Manitoba', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (56, 1, 'NB', 'New Brunswick', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (57, 1, 'NL', 'Newfoundland and Labrador', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (58, 1, 'NT', 'Northwest Territories', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (59, 1, 'NS', 'Nova Scotia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (60, 1, 'NU', 'Nunavut', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (61, 1, 'ON', 'Ontario', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (62, 1, 'PE', 'Prince Edward Island', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (63, 1, 'QC', 'Quebec', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (64, 1, 'SK', 'Saskatchewan', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (65, 1, 'YT', 'Yukon', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (66, 15, 'AN', 'Andalusia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (67, 15, 'AR', 'Aragon', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (68, 15, 'AS', 'Asturias', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (69, 15, 'IB', 'Balearic Islands', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (70, 15, 'PV', 'Basque Country', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (71, 15, 'CN', 'Canary Islands', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (72, 15, 'CB', 'Cantabria', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (73, 15, 'CL', 'Castile and Leon', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (74, 15, 'CM', 'Castile-La Mancha', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (75, 15, 'CT', 'Catalonia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (76, 15, 'CE', 'Ceuta', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (77, 15, 'EX', 'Extremadura', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (78, 15, 'GA', 'Galicia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (79, 15, 'LO', 'La Rioja', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (80, 15, 'M', 'Madrid', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (81, 15, 'ML', 'Melilla', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (82, 15, 'MU', 'Murcia', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (83, 15, 'NA', 'Navarra', 1);
insert into YKT_PORTAL.Region (regionId, countryId, regionCode, name, active_) values (84, 15, 'VC', 'Valencia', 1);

--
-- List types for accounts
--

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10000, 'Billing', 'com.liferay.portal.model.Account.address');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10001, 'Other', 'com.liferay.portal.model.Account.address');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10002, 'P.O. Box', 'com.liferay.portal.model.Account.address');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10003, 'Shipping', 'com.liferay.portal.model.Account.address');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10004, 'E-mail', 'com.liferay.portal.model.Account.emailAddress');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10005, 'E-mail 2', 'com.liferay.portal.model.Account.emailAddress');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10006, 'E-mail 3', 'com.liferay.portal.model.Account.emailAddress');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10007, 'Fax', 'com.liferay.portal.model.Account.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10008, 'Local', 'com.liferay.portal.model.Account.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10009, 'Other', 'com.liferay.portal.model.Account.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10010, 'Toll-Free', 'com.liferay.portal.model.Account.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10011, 'TTY', 'com.liferay.portal.model.Account.phone');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10012, 'Intranet', 'com.liferay.portal.model.Account.website');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (10013, 'Public', 'com.liferay.portal.model.Account.website');

--
-- List types for contacts
--

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11000, 'Business', 'com.liferay.portal.model.Contact.address');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11001, 'Other', 'com.liferay.portal.model.Contact.address');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11002, 'Personal', 'com.liferay.portal.model.Contact.address');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11003, 'E-mail', 'com.liferay.portal.model.Contact.emailAddress');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11004, 'E-mail 2', 'com.liferay.portal.model.Contact.emailAddress');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11005, 'E-mail 3', 'com.liferay.portal.model.Contact.emailAddress');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11006, 'Business', 'com.liferay.portal.model.Contact.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11007, 'Business Fax', 'com.liferay.portal.model.Contact.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11008, 'Mobile', 'com.liferay.portal.model.Contact.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11009, 'Other', 'com.liferay.portal.model.Contact.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11010, 'Pager', 'com.liferay.portal.model.Contact.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11011, 'Personal', 'com.liferay.portal.model.Contact.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11012, 'Personal Fax', 'com.liferay.portal.model.Contact.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11013, 'TTY', 'com.liferay.portal.model.Contact.phone');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11014, 'Dr.', 'com.liferay.portal.model.Contact.prefix');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11015, 'Mr.', 'com.liferay.portal.model.Contact.prefix');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11016, 'Mrs.', 'com.liferay.portal.model.Contact.prefix');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11017, 'Ms.', 'com.liferay.portal.model.Contact.prefix');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11020, 'II', 'com.liferay.portal.model.Contact.suffix');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11021, 'III', 'com.liferay.portal.model.Contact.suffix');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11022, 'IV', 'com.liferay.portal.model.Contact.suffix');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11023, 'Jr.', 'com.liferay.portal.model.Contact.suffix');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11024, 'PhD.', 'com.liferay.portal.model.Contact.suffix');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11025, 'Sr.', 'com.liferay.portal.model.Contact.suffix');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11026, 'Blog', 'com.liferay.portal.model.Contact.website');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11027, 'Business', 'com.liferay.portal.model.Contact.website');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11028, 'Other', 'com.liferay.portal.model.Contact.website');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (11029, 'Personal', 'com.liferay.portal.model.Contact.website');

--
-- List types for organizations
--

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12000, 'Billing', 'com.liferay.portal.model.Organization.address');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12001, 'Other', 'com.liferay.portal.model.Organization.address');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12002, 'P.O. Box', 'com.liferay.portal.model.Organization.address');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12003, 'Shipping', 'com.liferay.portal.model.Organization.address');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12004, 'E-mail', 'com.liferay.portal.model.Organization.emailAddress');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12005, 'E-mail 2', 'com.liferay.portal.model.Organization.emailAddress');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12006, 'E-mail 3', 'com.liferay.portal.model.Organization.emailAddress');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12007, 'Fax', 'com.liferay.portal.model.Organization.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12008, 'Local', 'com.liferay.portal.model.Organization.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12009, 'Other', 'com.liferay.portal.model.Organization.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12010, 'Toll-Free', 'com.liferay.portal.model.Organization.phone');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12011, 'TTY', 'com.liferay.portal.model.Organization.phone');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12012, 'Administrative', 'com.liferay.portal.model.Organization.service');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12013, 'Contracts', 'com.liferay.portal.model.Organization.service');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12014, 'Donation', 'com.liferay.portal.model.Organization.service');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12015, 'Retail', 'com.liferay.portal.model.Organization.service');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12016, 'Training', 'com.liferay.portal.model.Organization.service');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12017, 'Full Member', 'com.liferay.portal.model.Organization.status');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12018, 'Provisional Member', 'com.liferay.portal.model.Organization.status');

insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12019, 'Intranet', 'com.liferay.portal.model.Organization.website');
insert into YKT_PORTAL.ListType (listTypeId, name, type_) values (12020, 'Public', 'com.liferay.portal.model.Organization.website');


insert into YKT_PORTAL.Counter values ('com.liferay.counter.model.Counter', 10000);



insert into YKT_PORTAL.Company (companyId, accountId, webId, virtualHost, mx) values (1, 7, 'kingstargroup.com', 'localhost', 'kingstargroup.com');
insert into YKT_PORTAL.Account_ (accountId, companyId, userId, userName, createDate, modifiedDate, parentAccountId, name, legalName, legalId, legalType, sicCode, tickerSymbol, industry, type_, size_) values (7, 1, 5, '', sysdate, sysdate, 0, 'Liferay', 'Liferay, Inc.', '', '', '', '', '', '', '');


insert into YKT_PORTAL.ClassName_ (classNameId, value) values (8, 'com.liferay.portal.model.Organization');
insert into YKT_PORTAL.ClassName_ (classNameId, value) values (9, 'com.liferay.portal.model.User');


insert into YKT_PORTAL.Role_ (roleId, companyId, classNameId, classPK, name, description, type_) values (10, 1, 0, 0, 'Administrator', '', 1);
insert into YKT_PORTAL.Role_ (roleId, companyId, classNameId, classPK, name, description, type_) values (11, 1, 0, 0, 'Guest', '', 1);
insert into YKT_PORTAL.Role_ (roleId, companyId, classNameId, classPK, name, description, type_) values (12, 1, 0, 0, 'Power User', '', 1);
insert into YKT_PORTAL.Role_ (roleId, companyId, classNameId, classPK, name, description, type_) values (13, 1, 0, 0, 'User', '', 1);


insert into YKT_PORTAL.Group_ (groupId, companyId, creatorUserId, classNameId, classPK, parentGroupId, liveGroupId, name, friendlyURL, active_) values (14, 1, 5, 0, 0, 0, 0, 'Guest', '/guest', 1);
insert into YKT_PORTAL.LayoutSet (layoutSetId, companyId, groupId, privateLayout, logo, themeId, colorSchemeId, pageCount) values (15, 1, 14, 1, 0, 'brochure', '01', 2);
insert into YKT_PORTAL.LayoutSet (layoutSetId, companyId, groupId, privateLayout, logo, themeId, colorSchemeId, pageCount) values (16, 1, 14, 0, 0, 'brochure', '01', 8);


insert into YKT_PORTAL.Organization_ (organizationId, companyId, parentOrganizationId, name, location, recursable, regionId, countryId, statusId, comments) values (17, 1, 0, 'Kingstar, Inc.', 0, 1, 5, 19, 12017, '');

insert into YKT_PORTAL.User_ (userId, companyId, createDate, modifiedDate, defaultUser, contactId, password_, passwordEncrypted, passwordReset, screenName, emailAddress,languageid,timezoneid, greeting, loginDate, failedLoginAttempts, agreedToTermsOfUse, active_) values (5, 1, sysdate, sysdate, 1, 6, 'password', 0, 0, '5', 'default@kingstargroup.com', 'zh_CN','CTT','Welcome!', sysdate, 0, 1, 1);
insert into YKT_PORTAL.Contact_ (contactId, companyId, userId, userName, createDate, modifiedDate, accountId, parentContactId, firstName, middleName, lastName, male, birthday) values (6, 1, 5, '', sysdate, sysdate, 7, 0, '', '', '', 1, to_date('1970-01-01 00:00:00','YYYY-MM-DD HH24:MI:SS'));

insert into YKT_PORTAL.User_ (userId, companyId, createDate, modifiedDate, defaultUser, contactId, password_, passwordEncrypted, passwordReset, screenName, emailAddress,languageid,timezoneid, greeting, loginDate, failedLoginAttempts, agreedToTermsOfUse, active_) values (2, 1, sysdate, sysdate, 0, 3, 'test', 0, 0, 'admin', 'admin@kingstargroup.com', 'zh_CN','CTT','Welcome Administrator!', sysdate, 0, 1, 1);
insert into YKT_PORTAL.Contact_ (contactId, companyId, userId, userName, createDate, modifiedDate, accountId, parentContactId, firstName, middleName, lastName, male, birthday) values (3, 1, 2, 'Admininistrator', sysdate, sysdate, 7, 0, '', '', 'Admin', 1, to_date('1970-01-01 00:00:00','YYYY-MM-DD HH24:MI:SS'));

insert into YKT_PORTAL.Group_ (groupId, companyId, creatorUserId, classNameId, classPK, parentGroupId, liveGroupId, name, friendlyURL, active_) values (83, 1, 2, 9, 2, 0, 0, '83', '', 1);
insert into YKT_PORTAL.LayoutSet (layoutSetId, companyId, groupId, privateLayout, logo, themeId, colorSchemeId, pageCount) values (84, 1, 83, 1, 0, 'adminbrochure', '01', 2);
insert into YKT_PORTAL.LayoutSet (layoutSetId, companyId, groupId, privateLayout, logo, themeId, colorSchemeId, pageCount) values (85, 1, 83, 0, 0, 'adminbrochure', '01', 8);
--insert into YKT_PORTAL.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, name, type_, typeSettings, hidden_, friendlyURL, priority) values (86, 83, 1, 1, 1, 0, '<?xml version="1.0"?>'||CHR(10)||''||CHR(10)||'<root>'||CHR(10)||'  <name>Home</name>'||CHR(10)||'</root>', 'portlet', 'column-1=71_INSTANCE_OY0d,82,23,61,65,'||CHR(10)||'column-2=9,79,29,8,19,'||CHR(10)||'layout-template-id=2_columns_ii'||CHR(10)||'', 0, '/home', 0);
--insert into YKT_PORTAL.Layout (plid, groupId, companyId, privateLayout, layoutId, parentLayoutId, name, type_, typeSettings, hidden_, friendlyURL, priority) values (87, 83, 1, 1, 2, 0, '<?xml version="1.0"?>'||CHR(10)||''||CHR(10)||'<root>'||CHR(10)||'  <name>Plugins</name>'||CHR(10)||'</root>', 'portlet', 'column-1='||CHR(10)||'column-2=111,'||CHR(10)||'layout-template-id=2_columns_ii'||CHR(10)||'', 0, '/plugins', 1);

insert into YKT_PORTAL.Users_Groups values (2, 14);

--insert into YKT_PORTAL.Users_Orgs (userId, organizationId) values (2, 17);
--insert into YKT_PORTAL.Users_Orgs (userId, organizationId) values (2, 43);

insert into YKT_PORTAL.Users_Roles values (2, 10);
insert into YKT_PORTAL.Users_Roles values (2, 12);
insert into YKT_PORTAL.Users_Roles values (2, 13);


insert into YKT_PORTAL.IGFolder (folderId, groupId, companyId, userId, createDate, modifiedDate, parentFolderId, name) values (3073, 14, 1, 2, sysdate, sysdate, 0, 'Web Images');

insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3074, 10092, 2, sysdate, sysdate, 3073, 'Download Icon', 1502, 1503);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3075, 10092, 2, sysdate, sysdate, 3073, 'A bullet for ul items.', 1504, 1505);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3076, 10092, 2, sysdate, sysdate, 3073, 'service-background.png', 1533, 1534);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3077, 1, 2, sysdate, sysdate, 3073, 'Background image for three-points-icons template and structure.', 1726, 1727);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3078, 1, 2, sysdate, sysdate, 3073, 'add-plugin-to-catalog-2_1.png', 1754, 1755);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3079, 1, 2, sysdate, sysdate, 3073, 'add-plugin-to-catalog-3_1.png', 1756, 1757);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3080, 1, 2, sysdate, sysdate, 3073, 'add-plugin-to-catalog-3_1.png', 1758, 1759);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3081, 1, 2, sysdate, sysdate, 3073, 'add-plugin-to-catalog-5.png', 1760, 1761);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3082, 1, 2, sysdate, sysdate, 3073, 'RSS Feed Icon', 1763, 1764);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3083, 1, 2, sysdate, sysdate, 3073, 'Header Bullet for Read More Template', 1783, 1784);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3084, 1, 2, sysdate, sysdate, 3073, 'Banner for Downloads', 1785, 1786);
insert into YKT_PORTAL.IGImage (imageId, companyId, userId, createDate, modifiedDate, folderId, description, smallImageId, largeImageId) values (3085, 1, 2, sysdate, sysdate, 3073, 'ge_gallery.png', 1787, 1788);

update YKT_PORTAL.LayoutSet set themeId = 'brochure', pageCount = 8 where groupId = 14 and privateLayout = 0;

insert into YKT_PORTAL.Release_ (releaseId, createDate, modifiedDate, buildNumber, verified) values (1, sysdate, sysdate, 4401, 0);


commit;


create index YKT_PORTAL.IX_125EE7A4 on YKT_PORTAL.ActivityTracker (classNameId, classPK);
create index YKT_PORTAL.IX_57B7CA39 on YKT_PORTAL.ActivityTracker (companyId);
create index YKT_PORTAL.IX_8EEF8AFB on YKT_PORTAL.ActivityTracker (groupId);
create index YKT_PORTAL.IX_A9E541D8 on YKT_PORTAL.ActivityTracker (receiverUserId);
create index YKT_PORTAL.IX_B57EB3C9 on YKT_PORTAL.ActivityTracker (userId);

create index YKT_PORTAL.IX_93D5AD4E on YKT_PORTAL.Address (companyId);
create index YKT_PORTAL.IX_ABD7DAC0 on YKT_PORTAL.Address (companyId, classNameId);
create index YKT_PORTAL.IX_71CB1123 on YKT_PORTAL.Address (companyId, classNameId, classPK);
create index YKT_PORTAL.IX_923BD178 on YKT_PORTAL.Address (companyId, classNameId, classPK, mailing);
create index YKT_PORTAL.IX_9226DBB4 on YKT_PORTAL.Address (companyId, classNameId, classPK, primary_);
create index YKT_PORTAL.IX_5BC8B0D4 on YKT_PORTAL.Address (userId);

create index YKT_PORTAL.IX_72EF6041 on YKT_PORTAL.BlogsEntry (companyId);
create index YKT_PORTAL.IX_8CACE77B on YKT_PORTAL.BlogsEntry (companyId, userId);
create index YKT_PORTAL.IX_81A50303 on YKT_PORTAL.BlogsEntry (groupId);
create index YKT_PORTAL.IX_DB780A20 on YKT_PORTAL.BlogsEntry (groupId, urlTitle);
create index YKT_PORTAL.IX_C07CA83D on YKT_PORTAL.BlogsEntry (groupId, userId);
create index YKT_PORTAL.IX_69157A4D on YKT_PORTAL.BlogsEntry (uuid_);
create index YKT_PORTAL.IX_1B1040FD on YKT_PORTAL.BlogsEntry (uuid_, groupId);

create index YKT_PORTAL.IX_90CDA39A on YKT_PORTAL.BlogsStatsUser (companyId, entryCount);
create index YKT_PORTAL.IX_43840EEB on YKT_PORTAL.BlogsStatsUser (groupId);
create index YKT_PORTAL.IX_28C78D5C on YKT_PORTAL.BlogsStatsUser (groupId, entryCount);
create index YKT_PORTAL.IX_82254C25 on YKT_PORTAL.BlogsStatsUser (groupId, userId);
create index YKT_PORTAL.IX_BB51F1D9 on YKT_PORTAL.BlogsStatsUser (userId);

create index YKT_PORTAL.IX_443BDC38 on YKT_PORTAL.BookmarksEntry (folderId);
create index YKT_PORTAL.IX_B670BA39 on YKT_PORTAL.BookmarksEntry (uuid_);

create index YKT_PORTAL.IX_2ABA25D7 on YKT_PORTAL.BookmarksFolder (companyId);
create index YKT_PORTAL.IX_7F703619 on YKT_PORTAL.BookmarksFolder (groupId);
create index YKT_PORTAL.IX_967799C0 on YKT_PORTAL.BookmarksFolder (groupId, parentFolderId);
create index YKT_PORTAL.IX_451E7AE3 on YKT_PORTAL.BookmarksFolder (uuid_);
create index YKT_PORTAL.IX_DC2F8927 on YKT_PORTAL.BookmarksFolder (uuid_, groupId);

create index YKT_PORTAL.IX_12EE4898 on YKT_PORTAL.CalEvent (groupId);
create index YKT_PORTAL.IX_4FDDD2BF on YKT_PORTAL.CalEvent (groupId, repeating);
create index YKT_PORTAL.IX_FCD7C63D on YKT_PORTAL.CalEvent (groupId, type_);
create index YKT_PORTAL.IX_C1AD2122 on YKT_PORTAL.CalEvent (uuid_);
create index YKT_PORTAL.IX_5CCE79C8 on YKT_PORTAL.CalEvent (uuid_, groupId);

create index YKT_PORTAL.IX_B27A301F on YKT_PORTAL.ClassName_ (value);

create index YKT_PORTAL.IX_38EFE3FD on YKT_PORTAL.Company (logoId);
create index YKT_PORTAL.IX_12566EC2 on YKT_PORTAL.Company (mx);
create index YKT_PORTAL.IX_975996C0 on YKT_PORTAL.Company (virtualHost);
create index YKT_PORTAL.IX_EC00543C on YKT_PORTAL.Company (webId);

create index YKT_PORTAL.IX_66D496A3 on YKT_PORTAL.Contact_ (companyId);

create index YKT_PORTAL.IX_25D734CD on YKT_PORTAL.Country (active_);

create index YKT_PORTAL.IX_4CB1B2B4 on YKT_PORTAL.DLFileEntry (companyId);
create index YKT_PORTAL.IX_24A846D1 on YKT_PORTAL.DLFileEntry (folderId);
create index YKT_PORTAL.IX_8F6C75D0 on YKT_PORTAL.DLFileEntry (folderId, name);
create index YKT_PORTAL.IX_A9951F17 on YKT_PORTAL.DLFileEntry (folderId, title);
create index YKT_PORTAL.IX_64F0FE40 on YKT_PORTAL.DLFileEntry (uuid_);

create index YKT_PORTAL.IX_CE705D48 on YKT_PORTAL.DLFileRank (companyId, userId, folderId, name);
create index YKT_PORTAL.IX_40B56512 on YKT_PORTAL.DLFileRank (folderId, name);
create index YKT_PORTAL.IX_EED06670 on YKT_PORTAL.DLFileRank (userId);

create index YKT_PORTAL.IX_E56EC6AD on YKT_PORTAL.DLFileShortcut (folderId);
create index YKT_PORTAL.IX_CA2708A2 on YKT_PORTAL.DLFileShortcut (toFolderId, toName);
create index YKT_PORTAL.IX_4831EBE4 on YKT_PORTAL.DLFileShortcut (uuid_);

create index YKT_PORTAL.IX_9CD91DB6 on YKT_PORTAL.DLFileVersion (folderId, name);
create index YKT_PORTAL.IX_6C5E6512 on YKT_PORTAL.DLFileVersion (folderId, name, version);

create index YKT_PORTAL.IX_A74DB14C on YKT_PORTAL.DLFolder (companyId);
create index YKT_PORTAL.IX_F2EA1ACE on YKT_PORTAL.DLFolder (groupId);
create index YKT_PORTAL.IX_49C37475 on YKT_PORTAL.DLFolder (groupId, parentFolderId);
create index YKT_PORTAL.IX_902FD874 on YKT_PORTAL.DLFolder (groupId, parentFolderId, name);
create index YKT_PORTAL.IX_51556082 on YKT_PORTAL.DLFolder (parentFolderId, name);
create index YKT_PORTAL.IX_CBC408D8 on YKT_PORTAL.DLFolder (uuid_);
create index YKT_PORTAL.IX_3CC1DED2 on YKT_PORTAL.DLFolder (uuid_, groupId);

create index YKT_PORTAL.IX_1BB072CA on YKT_PORTAL.EmailAddress (companyId);
create index YKT_PORTAL.IX_49D2DEC4 on YKT_PORTAL.EmailAddress (companyId, classNameId);
create index YKT_PORTAL.IX_551A519F on YKT_PORTAL.EmailAddress (companyId, classNameId, classPK);
create index YKT_PORTAL.IX_2A2CB130 on YKT_PORTAL.EmailAddress (companyId, classNameId, classPK, primary_);
create index YKT_PORTAL.IX_7B43CD8 on YKT_PORTAL.EmailAddress (userId);

create index YKT_PORTAL.IX_D0D5E397 on YKT_PORTAL.Group_ (companyId, classNameId, classPK);
create index YKT_PORTAL.IX_5BDDB872 on YKT_PORTAL.Group_ (companyId, friendlyURL);
create index YKT_PORTAL.IX_5AA68501 on YKT_PORTAL.Group_ (companyId, name);
create index YKT_PORTAL.IX_16218A38 on YKT_PORTAL.Group_ (liveGroupId);

create index YKT_PORTAL.LIFERAY_001 on YKT_PORTAL.Groups_Permissions (permissionId);

create index YKT_PORTAL.IX_60214CF6 on YKT_PORTAL.IGFolder (companyId);
create index YKT_PORTAL.IX_206498F8 on YKT_PORTAL.IGFolder (groupId);
create index YKT_PORTAL.IX_1A605E9F on YKT_PORTAL.IGFolder (groupId, parentFolderId);
create index YKT_PORTAL.IX_F73C0982 on YKT_PORTAL.IGFolder (uuid_);
create index YKT_PORTAL.IX_B10EFD68 on YKT_PORTAL.IGFolder (uuid_, groupId);

create index YKT_PORTAL.IX_4438CA80 on YKT_PORTAL.IGImage (folderId);
create index YKT_PORTAL.IX_64F0B572 on YKT_PORTAL.IGImage (largeImageId);
create index YKT_PORTAL.IX_D3D32126 on YKT_PORTAL.IGImage (smallImageId);
create index YKT_PORTAL.IX_265BB0F1 on YKT_PORTAL.IGImage (uuid_);

create index YKT_PORTAL.IX_6A925A4D on YKT_PORTAL.Image (size_);

create index YKT_PORTAL.IX_DFF98523 on YKT_PORTAL.JournalArticle (companyId);
create index YKT_PORTAL.IX_9356F865 on YKT_PORTAL.JournalArticle (groupId);
create index YKT_PORTAL.IX_68C0F69C on YKT_PORTAL.JournalArticle (groupId, articleId);
create index YKT_PORTAL.IX_8DBF1387 on YKT_PORTAL.JournalArticle (groupId, articleId, approved);
create index YKT_PORTAL.IX_85C52EEC on YKT_PORTAL.JournalArticle (groupId, articleId, version);
create index YKT_PORTAL.IX_2E207659 on YKT_PORTAL.JournalArticle (groupId, structureId);
create index YKT_PORTAL.IX_8DEAE14E on YKT_PORTAL.JournalArticle (groupId, templateId);
create index YKT_PORTAL.IX_EF9B7028 on YKT_PORTAL.JournalArticle (smallImageId);
create index YKT_PORTAL.IX_F029602F on YKT_PORTAL.JournalArticle (uuid_);
create index YKT_PORTAL.IX_3463D95B on YKT_PORTAL.JournalArticle (uuid_, groupId);

create index YKT_PORTAL.IX_3B51BB68 on YKT_PORTAL.JournalArticleImage (groupId);
create index YKT_PORTAL.IX_158B526F on YKT_PORTAL.JournalArticleImage (groupId, articleId, version);
create index YKT_PORTAL.IX_D67292FC on YKT_PORTAL.JournalArticleImage (groupId, articleId, version, elName, languageId);
create index YKT_PORTAL.IX_D4121315 on YKT_PORTAL.JournalArticleImage (tempImage);

create index YKT_PORTAL.IX_F8433677 on YKT_PORTAL.JournalArticleResource (groupId);
create index YKT_PORTAL.IX_88DF994A on YKT_PORTAL.JournalArticleResource (groupId, articleId);

create index YKT_PORTAL.IX_6838E427 on YKT_PORTAL.JournalContentSearch (groupId, articleId);
create index YKT_PORTAL.IX_20962903 on YKT_PORTAL.JournalContentSearch (groupId, privateLayout);
create index YKT_PORTAL.IX_7CC7D73E on YKT_PORTAL.JournalContentSearch (groupId, privateLayout, articleId);
create index YKT_PORTAL.IX_B3B318DC on YKT_PORTAL.JournalContentSearch (groupId, privateLayout, layoutId);
create index YKT_PORTAL.IX_7ACC74C9 on YKT_PORTAL.JournalContentSearch (groupId, privateLayout, layoutId, portletId);
create index YKT_PORTAL.IX_C3AA93B8 on YKT_PORTAL.JournalContentSearch (groupId, privateLayout, layoutId, portletId, articleId);

create index YKT_PORTAL.IX_35A2DB2F on YKT_PORTAL.JournalFeed (groupId);
create index YKT_PORTAL.IX_65576CBC on YKT_PORTAL.JournalFeed (groupId, feedId);
create index YKT_PORTAL.IX_50C36D79 on YKT_PORTAL.JournalFeed (uuid_);
create index YKT_PORTAL.IX_39031F51 on YKT_PORTAL.JournalFeed (uuid_, groupId);

create index YKT_PORTAL.IX_B97F5608 on YKT_PORTAL.JournalStructure (groupId);
create index YKT_PORTAL.IX_AB6E9996 on YKT_PORTAL.JournalStructure (groupId, structureId);
create index YKT_PORTAL.IX_8831E4FC on YKT_PORTAL.JournalStructure (structureId);
create index YKT_PORTAL.IX_6702CA92 on YKT_PORTAL.JournalStructure (uuid_);
create index YKT_PORTAL.IX_42E86E58 on YKT_PORTAL.JournalStructure (uuid_, groupId);

create index YKT_PORTAL.IX_77923653 on YKT_PORTAL.JournalTemplate (groupId);
create index YKT_PORTAL.IX_1701CB2B on YKT_PORTAL.JournalTemplate (groupId, structureId);
create index YKT_PORTAL.IX_E802AA3C on YKT_PORTAL.JournalTemplate (groupId, templateId);
create index YKT_PORTAL.IX_25FFB6FA on YKT_PORTAL.JournalTemplate (smallImageId);
create index YKT_PORTAL.IX_1B12CA20 on YKT_PORTAL.JournalTemplate (templateId);
create index YKT_PORTAL.IX_2857419D on YKT_PORTAL.JournalTemplate (uuid_);
create index YKT_PORTAL.IX_62D1B3AD on YKT_PORTAL.JournalTemplate (uuid_, groupId);

create index YKT_PORTAL.IX_C7FBC998 on YKT_PORTAL.Layout (companyId);
create index YKT_PORTAL.IX_FAD05595 on YKT_PORTAL.Layout (dlFolderId);
create index YKT_PORTAL.IX_C099D61A on YKT_PORTAL.Layout (groupId);
create index YKT_PORTAL.IX_705F5AA3 on YKT_PORTAL.Layout (groupId, privateLayout);
create index YKT_PORTAL.IX_BC2C4231 on YKT_PORTAL.Layout (groupId, privateLayout, friendlyURL);
create index YKT_PORTAL.IX_7162C27C on YKT_PORTAL.Layout (groupId, privateLayout, layoutId);
create index YKT_PORTAL.IX_6DE88B06 on YKT_PORTAL.Layout (groupId, privateLayout, parentLayoutId);
create index YKT_PORTAL.IX_23922F7D on YKT_PORTAL.Layout (iconImageId);

create index YKT_PORTAL.IX_A40B8BEC on YKT_PORTAL.LayoutSet (groupId);
create index YKT_PORTAL.IX_48550691 on YKT_PORTAL.LayoutSet (groupId, privateLayout);
create index YKT_PORTAL.IX_5ABC2905 on YKT_PORTAL.LayoutSet (virtualHost);

create index YKT_PORTAL.IX_2932DD37 on YKT_PORTAL.ListType (type_);

create index YKT_PORTAL.IX_69951A25 on YKT_PORTAL.MBBan (banUserId);
create index YKT_PORTAL.IX_5C3FF12A on YKT_PORTAL.MBBan (groupId);
create index YKT_PORTAL.IX_8ABC4E3B on YKT_PORTAL.MBBan (groupId, banUserId);
create index YKT_PORTAL.IX_48814BBA on YKT_PORTAL.MBBan (userId);

create index YKT_PORTAL.IX_BC735DCF on YKT_PORTAL.MBCategory (companyId);
create index YKT_PORTAL.IX_BB870C11 on YKT_PORTAL.MBCategory (groupId);
create index YKT_PORTAL.IX_ED292508 on YKT_PORTAL.MBCategory (groupId, parentCategoryId);
create index YKT_PORTAL.IX_C2626EDB on YKT_PORTAL.MBCategory (uuid_);
create index YKT_PORTAL.IX_F7D28C2F on YKT_PORTAL.MBCategory (uuid_, groupId);

create index YKT_PORTAL.IX_33A4DE38 on YKT_PORTAL.MBDiscussion(classNameId, classPK);

create index YKT_PORTAL.IX_3C865EE5 on YKT_PORTAL.MBMessage (categoryId);
create index YKT_PORTAL.IX_138C7F1E on YKT_PORTAL.MBMessage (categoryId, threadId);
create index YKT_PORTAL.IX_B1432D30 on YKT_PORTAL.MBMessage (companyId);
create index YKT_PORTAL.IX_75B95071 on YKT_PORTAL.MBMessage (threadId);
create index YKT_PORTAL.IX_A7038CD7 on YKT_PORTAL.MBMessage (threadId, parentMessageId);
create index YKT_PORTAL.IX_C57B16BC on YKT_PORTAL.MBMessage (uuid_);

create index YKT_PORTAL.IX_D180D4AE on YKT_PORTAL.MBMessageFlag (messageId);
create index YKT_PORTAL.IX_7B2917BE on YKT_PORTAL.MBMessageFlag (userId);
create index YKT_PORTAL.IX_94A83834 on YKT_PORTAL.MBMessageFlag (userId, messageId);

create index YKT_PORTAL.IX_A00A898F on YKT_PORTAL.MBStatsUser (groupId);
create index YKT_PORTAL.IX_FAB5A88B on YKT_PORTAL.MBStatsUser (groupId, messageCount);
create index YKT_PORTAL.IX_9168E2C9 on YKT_PORTAL.MBStatsUser (groupId, userId);
create index YKT_PORTAL.IX_847F92B5 on YKT_PORTAL.MBStatsUser (userId);

create index YKT_PORTAL.IX_CB854772 on YKT_PORTAL.MBThread (categoryId);

create index YKT_PORTAL.IX_8A1CC4B on YKT_PORTAL.MembershipRequest (groupId);
create index YKT_PORTAL.IX_C28C72EC on YKT_PORTAL.MembershipRequest (groupId, statusId);
create index YKT_PORTAL.IX_66D70879 on YKT_PORTAL.MembershipRequest (userId);

create index YKT_PORTAL.IX_A425F71A on YKT_PORTAL.OrgGroupPermission(groupId);
create index YKT_PORTAL.IX_6C53DA4E on YKT_PORTAL.OrgGroupPermission(permissionId);

create index YKT_PORTAL.IX_4A527DD3 on YKT_PORTAL.OrgGroupRole (groupId);
create index YKT_PORTAL.IX_AB044D1C on YKT_PORTAL.OrgGroupRole (roleId);

create index YKT_PORTAL.IX_6AF0D434 on YKT_PORTAL.OrgLabor (organizationId);

create index YKT_PORTAL.IX_834BCEB6 on YKT_PORTAL.Organization_ (companyId);
create index YKT_PORTAL.IX_E301BDF5 on YKT_PORTAL.Organization_ (companyId, name);
create index YKT_PORTAL.IX_418E4522 on YKT_PORTAL.Organization_ (companyId, parentOrganizationId);

create index YKT_PORTAL.IX_2C1142E on YKT_PORTAL.PasswordPolicy (companyId, defaultPolicy);
create index YKT_PORTAL.IX_3FBFA9F4 on YKT_PORTAL.PasswordPolicy (companyId, name);

create index YKT_PORTAL.IX_C3A17327 on YKT_PORTAL.PasswordPolicyRel (classNameId, classPK);
create index YKT_PORTAL.IX_ED7CF243 on YKT_PORTAL.PasswordPolicyRel (passwordPolicyId, classNameId, classPK);

create index YKT_PORTAL.IX_326F75BD on YKT_PORTAL.PasswordTracker (userId);

create index YKT_PORTAL.IX_4D19C2B8 on YKT_PORTAL.Permission_ (actionId, resourceId);
create index YKT_PORTAL.IX_F090C113 on YKT_PORTAL.Permission_ (resourceId);

create index YKT_PORTAL.IX_9F704A14 on YKT_PORTAL.Phone (companyId);
create index YKT_PORTAL.IX_A2E4AFBA on YKT_PORTAL.Phone (companyId, classNameId);
create index YKT_PORTAL.IX_9A53569 on YKT_PORTAL.Phone (companyId, classNameId, classPK);
create index YKT_PORTAL.IX_812CE07A on YKT_PORTAL.Phone (companyId, classNameId, classPK, primary_);
create index YKT_PORTAL.IX_F202B9CE on YKT_PORTAL.Phone (userId);

create index YKT_PORTAL.IX_B9746445 on YKT_PORTAL.PluginSetting (companyId);
create index YKT_PORTAL.IX_7171B2E8 on YKT_PORTAL.PluginSetting (companyId, pluginId, pluginType);

create index YKT_PORTAL.IX_EC370F10 on YKT_PORTAL.PollsChoice (questionId);
create index YKT_PORTAL.IX_D76DD2CF on YKT_PORTAL.PollsChoice (questionId, name);
create index YKT_PORTAL.IX_6660B399 on YKT_PORTAL.PollsChoice (uuid_);

create index YKT_PORTAL.IX_9FF342EA on YKT_PORTAL.PollsQuestion(groupId);
create index YKT_PORTAL.IX_51F087F4 on YKT_PORTAL.PollsQuestion(uuid_);
create index YKT_PORTAL.IX_F3C9F36 on YKT_PORTAL.PollsQuestion(uuid_, groupId);

create index YKT_PORTAL.IX_D5DF7B54 on YKT_PORTAL.PollsVote (choiceId);
create index YKT_PORTAL.IX_12112599 on YKT_PORTAL.PollsVote (questionId);
create index YKT_PORTAL.IX_1BBFD4D3 on YKT_PORTAL.PollsVote (questionId, userId);

create index YKT_PORTAL.IX_80CC9508 on YKT_PORTAL.Portlet (companyId);
create index YKT_PORTAL.IX_12B5E51D on YKT_PORTAL.Portlet (companyId, portletId);

create index YKT_PORTAL.IX_E4F13E6E on YKT_PORTAL.PortletPreferences (ownerId, ownerType, plid);
create index YKT_PORTAL.IX_C7057FF7 on YKT_PORTAL.PortletPreferences (ownerId, ownerType, plid, portletId);
create index YKT_PORTAL.IX_F15C1C4F on YKT_PORTAL.PortletPreferences (plid);
create index YKT_PORTAL.IX_D340DB76 on YKT_PORTAL.PortletPreferences (plid, portletId);

create index YKT_PORTAL.IX_16184D57 on YKT_PORTAL.RatingsEntry (classNameId, classPK);
create index YKT_PORTAL.IX_B47E3C11 on YKT_PORTAL.RatingsEntry (userId, classNameId, classPK);

create index YKT_PORTAL.IX_A6E99284 on YKT_PORTAL.RatingsStats (classNameId, classPK);

create index YKT_PORTAL.IX_2D9A426F on YKT_PORTAL.Region(active_);
create index YKT_PORTAL.IX_16D87CA7 on YKT_PORTAL.Region(countryId);
create index YKT_PORTAL.IX_11FB3E42 on YKT_PORTAL.Region(countryId, active_);

create index YKT_PORTAL.IX_717FDD47 on YKT_PORTAL.ResourceCode (companyId);
create index YKT_PORTAL.IX_A32C097E on YKT_PORTAL.ResourceCode (companyId, name, scope);
create index YKT_PORTAL.IX_AACAFF40 on YKT_PORTAL.ResourceCode (name);

create index YKT_PORTAL.IX_2578FBD3 on YKT_PORTAL.Resource_ (codeId);
create index YKT_PORTAL.IX_67DE7856 on YKT_PORTAL.Resource_ (codeId, primKey);

create index YKT_PORTAL.IX_449A10B9 on YKT_PORTAL.Role_ (companyId);
create index YKT_PORTAL.IX_A88E424E on YKT_PORTAL.Role_ (companyId, classNameId, classPK);
create index YKT_PORTAL.IX_EBC931B8 on YKT_PORTAL.Role_ (companyId, name);

create index YKT_PORTAL.LIFERAY_002 on YKT_PORTAL.Roles_Permissions (permissionId);

create index YKT_PORTAL.IX_C98C0D78 on YKT_PORTAL.SCFrameworkVersion(companyId);
create index YKT_PORTAL.IX_272991FA on YKT_PORTAL.SCFrameworkVersion(groupId);
create index YKT_PORTAL.IX_6E1764F on YKT_PORTAL.SCFrameworkVersion(groupId, active_);

create index YKT_PORTAL.IX_1C841592 on YKT_PORTAL.SCLicense (active_);
create index YKT_PORTAL.IX_5327BB79 on YKT_PORTAL.SCLicense (active_, recommended);

create index YKT_PORTAL.IX_5D25244F on YKT_PORTAL.SCProductEntry (companyId);
create index YKT_PORTAL.IX_72F87291 on YKT_PORTAL.SCProductEntry (groupId);
create index YKT_PORTAL.IX_98E6A9CB on YKT_PORTAL.SCProductEntry (groupId, userId);
create index YKT_PORTAL.IX_7311E812 on YKT_PORTAL.SCProductEntry (repoGroupId, repoArtifactId);

create index YKT_PORTAL.IX_AE8224CC on YKT_PORTAL.SCProductScreenshot (fullImageId);
create index YKT_PORTAL.IX_467956FD on YKT_PORTAL.SCProductScreenshot (productEntryId);
create index YKT_PORTAL.IX_DA913A55 on YKT_PORTAL.SCProductScreenshot (productEntryId, priority);
create index YKT_PORTAL.IX_6C572DAC on YKT_PORTAL.SCProductScreenshot (thumbnailId);

create index YKT_PORTAL.IX_7020130F on YKT_PORTAL.SCProductVersion(directDownloadURL);
create index YKT_PORTAL.IX_8377A211 on YKT_PORTAL.SCProductVersion(productEntryId);

create index YKT_PORTAL.IX_7338606F on YKT_PORTAL.ServiceComponent (buildNamespace);
create index YKT_PORTAL.IX_4F0315B8 on YKT_PORTAL.ServiceComponent (buildNamespace, buildNumber);

create index YKT_PORTAL.IX_C28B41DC on YKT_PORTAL.ShoppingCart (groupId);
create index YKT_PORTAL.IX_FC46FE16 on YKT_PORTAL.ShoppingCart (groupId, userId);
create index YKT_PORTAL.IX_54101CC8 on YKT_PORTAL.ShoppingCart (userId);

create index YKT_PORTAL.IX_5F615D3E on YKT_PORTAL.ShoppingCategory (groupId);
create index YKT_PORTAL.IX_1E6464F5 on YKT_PORTAL.ShoppingCategory (groupId, parentCategoryId);

create index YKT_PORTAL.IX_DC60CFAE on YKT_PORTAL.ShoppingCoupon(code_);
create index YKT_PORTAL.IX_3251AF16 on YKT_PORTAL.ShoppingCoupon(groupId);

create index YKT_PORTAL.IX_C8EACF2E on YKT_PORTAL.ShoppingItem (categoryId);
create index YKT_PORTAL.IX_1C717CA6 on YKT_PORTAL.ShoppingItem (companyId, sku);
create index YKT_PORTAL.IX_903DC750 on YKT_PORTAL.ShoppingItem (largeImageId);
create index YKT_PORTAL.IX_D217AB30 on YKT_PORTAL.ShoppingItem (mediumImageId);
create index YKT_PORTAL.IX_FF203304 on YKT_PORTAL.ShoppingItem (smallImageId);

create index YKT_PORTAL.IX_6D5F9B87 on YKT_PORTAL.ShoppingItemField (itemId);

create index YKT_PORTAL.IX_EA6FD516 on YKT_PORTAL.ShoppingItemPrice (itemId);

create index YKT_PORTAL.IX_1D15553E on YKT_PORTAL.ShoppingOrder (groupId);
create index YKT_PORTAL.IX_119B5630 on YKT_PORTAL.ShoppingOrder (groupId, userId, ppPaymentStatus);
create index YKT_PORTAL.IX_D7D6E87A on YKT_PORTAL.ShoppingOrder (number_);

create index YKT_PORTAL.IX_B5F82C7A on YKT_PORTAL.ShoppingOrderItem (orderId);

create index YKT_PORTAL.IX_786D171A on YKT_PORTAL.Subscription(companyId, classNameId, classPK);
create index YKT_PORTAL.IX_2E1A92D4 on YKT_PORTAL.Subscription(companyId, userId, classNameId, classPK);
create index YKT_PORTAL.IX_54243AFD on YKT_PORTAL.Subscription(userId);

create index YKT_PORTAL.IX_1AB6D6D2 on YKT_PORTAL.TagsAsset (classNameId, classPK);
create index YKT_PORTAL.IX_AB3D8BCB on YKT_PORTAL.TagsAsset (companyId);

create index YKT_PORTAL.IX_10563688 on YKT_PORTAL.TagsEntry (companyId, name);

create index YKT_PORTAL.IX_C134234 on YKT_PORTAL.TagsProperty (companyId);
create index YKT_PORTAL.IX_EB974D08 on YKT_PORTAL.TagsProperty (companyId, key_);
create index YKT_PORTAL.IX_5200A629 on YKT_PORTAL.TagsProperty (entryId);
create index YKT_PORTAL.IX_F505253D on YKT_PORTAL.TagsProperty (entryId, key_);

create index YKT_PORTAL.IX_524FEFCE on YKT_PORTAL.UserGroup (companyId);
create index YKT_PORTAL.IX_23EAD0D on YKT_PORTAL.UserGroup (companyId, name);
create index YKT_PORTAL.IX_69771487 on YKT_PORTAL.UserGroup (companyId, parentUserGroupId);

create index YKT_PORTAL.IX_1B988D7A on YKT_PORTAL.UserGroupRole (groupId);
create index YKT_PORTAL.IX_871412DF on YKT_PORTAL.UserGroupRole (groupId, roleId);
create index YKT_PORTAL.IX_887A2C95 on YKT_PORTAL.UserGroupRole (roleId);
create index YKT_PORTAL.IX_887BE56A on YKT_PORTAL.UserGroupRole (userId);
create index YKT_PORTAL.IX_4D040680 on YKT_PORTAL.UserGroupRole (userId, groupId);

create index YKT_PORTAL.IX_41A32E0D on YKT_PORTAL.UserIdMapper (type_, externalUserId);
create index YKT_PORTAL.IX_E60EA987 on YKT_PORTAL.UserIdMapper (userId);
create index YKT_PORTAL.IX_D1C44A6E on YKT_PORTAL.UserIdMapper (userId, type_);

create index YKT_PORTAL.IX_29BA1CF5 on YKT_PORTAL.UserTracker (companyId);
create index YKT_PORTAL.IX_46B0AE8E on YKT_PORTAL.UserTracker (sessionId);
create index YKT_PORTAL.IX_E4EFBA8D on YKT_PORTAL.UserTracker (userId);

create index YKT_PORTAL.IX_14D8BCC0 on YKT_PORTAL.UserTrackerPath (userTrackerId);

create index YKT_PORTAL.IX_3A1E834E on YKT_PORTAL.User_ (companyId);
create index YKT_PORTAL.IX_6EF03E4E on YKT_PORTAL.User_ (companyId, defaultUser);
create index YKT_PORTAL.IX_615E9F7A on YKT_PORTAL.User_ (companyId, emailAddress);
create index YKT_PORTAL.IX_765A87C6 on YKT_PORTAL.User_ (companyId, password_);
create index YKT_PORTAL.IX_C5806019 on YKT_PORTAL.User_ (companyId, screenName);
create index YKT_PORTAL.IX_9782AD88 on YKT_PORTAL.User_ (companyId, userId);
create index YKT_PORTAL.IX_5ADBE171 on YKT_PORTAL.User_ (contactId);
create index YKT_PORTAL.IX_A18034A4 on YKT_PORTAL.User_ (portraitId);
create index YKT_PORTAL.IX_E0422BDA on YKT_PORTAL.User_ (uuid_);

create index YKT_PORTAL.LIFERAY_003 on YKT_PORTAL.Users_Permissions (permissionId);

create index YKT_PORTAL.IX_97DFA146 on YKT_PORTAL.WebDAVProps (classNameId, classPK);

create index YKT_PORTAL.IX_96F07007 on YKT_PORTAL.Website (companyId);
create index YKT_PORTAL.IX_4F0F0CA7 on YKT_PORTAL.Website (companyId, classNameId);
create index YKT_PORTAL.IX_F960131C on YKT_PORTAL.Website (companyId, classNameId, classPK);
create index YKT_PORTAL.IX_1AA07A6D on YKT_PORTAL.Website (companyId, classNameId, classPK, primary_);
create index YKT_PORTAL.IX_F75690BB on YKT_PORTAL.Website (userId);

create index YKT_PORTAL.IX_5D6FE3F0 on YKT_PORTAL.WikiNode (companyId);
create index YKT_PORTAL.IX_B480A672 on YKT_PORTAL.WikiNode (groupId);
create index YKT_PORTAL.IX_6C112D7C on YKT_PORTAL.WikiNode (uuid_);
create index YKT_PORTAL.IX_7609B2AE on YKT_PORTAL.WikiNode (uuid_, groupId);

create index YKT_PORTAL.IX_C8A9C476 on YKT_PORTAL.WikiPage (nodeId);
create index YKT_PORTAL.IX_E7F635CA on YKT_PORTAL.WikiPage (nodeId, head);
create index YKT_PORTAL.IX_997EEDD2 on YKT_PORTAL.WikiPage (nodeId, title);
create index YKT_PORTAL.IX_E745EA26 on YKT_PORTAL.WikiPage (nodeId, title, head);
create index YKT_PORTAL.IX_3D4AF476 on YKT_PORTAL.WikiPage (nodeId, title, version);
create index YKT_PORTAL.IX_9C0E478F on YKT_PORTAL.WikiPage (uuid_);

create index YKT_PORTAL.IX_21277664 on YKT_PORTAL.WikiPageResource (nodeId, title);

create table ykt_portal.T_JOBLOG
(
  ERRCODE    NUMBER,
  ERRCONTENT VARCHAR2(255),
  ERRDATE    VARCHAR2(20)
)

CREATE OR REPLACE PROCEDURE YKT_PORTAL."ANALYSIZE_SPECIALSTU_STATDATA" is
   currDay  varchar2(8);
   v_error_code NUMBER;
   v_error_message VARCHAR2(255);
 begin
   select to_char(sysdate, 'yyyymmdd') into currDay from dual;
   delete from ykt_portal.T_RCSTATDATA where tx_date = currDay;
   commit;
	 insert into ykt_portal.T_RCSTATDATA
			select cardno,meal,transdate,sum(amount) as amount
			from
      (   select t.transdate,
              trim(to_char(to_date(SUBSTR(t.transdate,1,4)||'-'||SUBSTR(t.transdate,5,2)||'-'||SUBSTR(t.transdate,7,2),'yyyy-mm-dd'),'day','nls_date_language=American')) as week,
              (case when transtime <'093000' then 'bk'
                    when (transtime >='093000' and transtime<'150000') then 'lun'
                    else 'sup' end) as meal,
              t.cardno,t.devphyid,t.AMOUNT,t.transcode
          from ykt_cur.t_posdtl t
          where status='3' and t.amount>0 and transdate = currDay
      )
      where week in ('monday','tuesday','wednesday','thursday','friday')
      group by cardno,meal,transdate;
  commit;

  delete from ykt_portal.t_rpttermledger where accdate = currDay;
  commit;

  insert into ykt_portal.t_rpttermledger(accdate,termid,subjno,accno,transtype,summary,transcnt,dramt,cramt)
    select accdate,termid,subjno,accno,transtype,summary,count(summary),sum((2-dcflag)*amount) dramt,
    sum((dcflag-1)*amount) cramt from ykt_cur.v_accdtl  where accdate=currDay and subjno='2004'
    group by accdate,termid,subjno,accno,transtype,summary;
  commit;

  delete from ykt_portal.t_rptdeptledger where accdate = currDay;
  commit;

  insert into ykt_portal.t_rptdeptledger(accdate,deptcode,subjno,transtype,summary,transcnt,dramt,cramt)
    select accdate,deptcode,subjno,transtype,summary,count(summary),sum(dramt) dramt,sum(cramt) cramt
    from (select a.accdate,a.subjno,(2-dcflag)*a.amount dramt,(dcflag-1)*amount cramt,a.transtype,a.summary,c.deptcode
    from ykt_cur.v_accdtl a,ykt_cur.t_card b,ykt_cur.t_customer c
    where a.accdate=currDay and a.accno=b.accno and b.custid=c.custid and c.deptcode is not null )
    group by accdate,deptcode,subjno,transtype,summary;

  commit;
EXCEPTION
  when OTHERS THEN
     null;
   v_error_code := SQLCODE;
   v_error_message := SQLERRM;
   INSERT INTO YKT_PORTAL.t_joblog( errcode,errcontent,errdate) VALUES ( v_error_code, v_error_message,to_char(sysdate, 'yyyymmdd hh24miss'));
   commit;
end;

CREATE OR REPLACE PROCEDURE ANALYSIZE_SPECIALSTU_his (d1 in varchar2,
                                                     d2 in varchar2) is
   currDay  varchar2(8);
   v_error_code NUMBER;
   v_error_message VARCHAR2(255);
 begin
   select to_char(sysdate, 'yyyymmdd') into currDay from dual;
   delete from ykt_portal.T_RCSTATDATA where tx_date >= d1 and tx_date<=d2;
   commit;
	 insert into ykt_portal.T_RCSTATDATA
			select cardno,meal,transdate,sum(amount) amount
			from
      (   select t.transdate,
              trim(to_char(to_date(SUBSTR(t.transdate,1,4)||'-'||SUBSTR(t.transdate,5,2)||'-'||SUBSTR(t.transdate,7,2),'yyyy-mm-dd'),'day','nls_date_language=American')) as week,
              (case when transtime <'093000' then 'bk'
                    when (transtime >='093000' and transtime<'150000') then 'lun'
                    else 'sup' end) as meal,
              t.cardno,t.devphyid,t.AMOUNT,t.transcode
          from ykt_cur.t_posdtl t
          where status='3' and t.amount>0 and transdate >= d1 and transdate <= d2
      )
      where week in ('monday','tuesday','wednesday','thursday','friday')
      group by cardno,meal,transdate;
  commit;

  delete from ykt_portal.t_rpttermledger where accdate >= d1 and accdate <= d2;
  commit;

  insert into ykt_portal.t_rpttermledger(accdate,termid,subjno,accno,transtype,summary,transcnt,dramt,cramt)
    select accdate,termid,subjno,accno,transtype,summary,count(summary),sum((2-dcflag)*amount) dramt,
    sum((dcflag-1)*amount) cramt from ykt_cur.v_accdtl  where accdate>= d1 and accdate <= d2 and subjno='2004'
    group by accdate,termid,subjno,accno,transtype,summary;
  commit;

  delete from ykt_portal.t_rptdeptledger where accdate>= d1 and accdate <= d2;
  commit;

  insert into ykt_portal.t_rptdeptledger(accdate,deptcode,subjno,transtype,summary,transcnt,dramt,cramt)
    select accdate,deptcode,subjno,transtype,summary,count(summary),sum(dramt) dramt,sum(cramt) cramt
    from (select a.accdate,a.subjno,(2-dcflag)*a.amount dramt,(dcflag-1)*amount cramt,a.transtype,a.summary,c.deptcode
    from ykt_cur.v_accdtl a,ykt_cur.t_card b,ykt_cur.t_customer c
    where a.accdate>= d1 and a.accdate <= d2 and a.accno=b.accno and b.custid=c.custid and c.deptcode is not null )
    group by accdate,deptcode,subjno,transtype,summary;

  commit;
EXCEPTION
  when OTHERS THEN
     null;
   v_error_code := SQLCODE;
   v_error_message := SQLERRM;
   INSERT INTO YKT_PORTAL.t_joblog( errcode,errcontent,errdate) VALUES ( v_error_code, v_error_message,to_char(sysdate, 'yyyymmdd hh24miss'));
   commit;
end;



--以下脚本需要在ykt_portal用户下的command windows执行
--variable job number
--begin
--  sys.dbms_job.submit(job => :job,
--                      what => 'ANALYSIZE_SPECIALSTU_STATDATA;',
--                      next_date => to_date('22-11-2010 23:55:00', 'dd-mm-yyyy hh24:mi:ss'),
--                      interval => 'TRUNC(SYSDATE + 1) + (23*60+55)/(24*60)');
--  commit;
--end;
--/