load data
infile 'portal-oracle-journalstructure.csv'
into table JournalStructure
fields terminated by "," optionally enclosed by '\''
(id_,
 groupId,
 companyId,
 userId,
 userName,
 createDate date 'YYYYMMDD',
 modifiedDate date 'YYYYMMDD',
 structureId,
 name,
 description char(4000),
 xsd char(10000000))