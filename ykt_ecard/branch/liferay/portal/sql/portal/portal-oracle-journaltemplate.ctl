load data
infile 'portal-oracle-journaltemplate.csv'
into table JournalTemplate
fields terminated by "," optionally enclosed by '\''
(id_,
 groupId,
 companyId,
 userId,
 userName,
 createDate date 'YYYYMMDD',
 modifiedDate date 'YYYYMMDD',
 templateId,
 structureId,
 name,
 description char(4000),
 xsl char(10000000),
 langType,
 smallImage,
 smallImageId,
 smallImageURL)