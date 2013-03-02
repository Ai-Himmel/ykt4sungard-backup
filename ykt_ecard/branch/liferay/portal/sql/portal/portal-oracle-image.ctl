load data
infile 'portal-oracle-image.csv'
into table Image
fields terminated by "," optionally enclosed by '\''
(imageId,
 modifiedDate Date 'YYYYMMDD',
 text_ char(1000000),
 type_,
 height,
 width,
 size_)