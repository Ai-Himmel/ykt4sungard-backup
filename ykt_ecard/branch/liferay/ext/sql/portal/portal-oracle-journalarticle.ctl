load data
infile 'portal-oracle-journalarticle.csv'
into table JournalArticle
fields terminated by "," optionally enclosed by '\''
(id_,
 resourcePrimKey,
 groupId,
 companyId,
 userId,
 userName,
 createDate date 'YYYYMMDD',
 modifiedDate date 'YYYYMMDD',
 articleId,
 version,
 title,
 description char(4000),
 content char(10000000),
 type_,
 structureId,
 templateId,
 displayDate Date 'YYYYMMDD',
 approved,
 approvedByUserId,
 approvedByUserName,
 expired,
 indexable)