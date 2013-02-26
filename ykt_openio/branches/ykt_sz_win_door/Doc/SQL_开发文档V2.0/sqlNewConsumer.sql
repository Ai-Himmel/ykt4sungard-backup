--添加新用户[约束: 卡号和用户姓名不能为空, 部门可以为空; 卡号不能重复] 

--值 含义 
--0 成功执行。 
--101 卡号不能为空 
--102 卡号必须大于100, 小于 4294967295
--103 卡号已被其他人使用
--104 卡号不存在
--201 用户姓名不能为空 
--301 部门班组名必须是已存在的
--9 SQL Server errors

CREATE PROCEDURE sp_wg_NewConsumer
@CardNO bigint,
@ConsumerName nvarchar(100),
@GroupName nvarchar(100)=NULL
AS
DECLARE @reccount as int
DECLARE @groupID  as int  
DECLARE @consumerNO  as int  
DECLARE @consumerID  as int  
-- Validate parameter.
IF @CardNO IS NULL
BEGIN
   PRINT 'ERROR: You must specify a CardNO value.'
   RETURN(101)
END
ELSE
BEGIN
--必须是整数 且小于4294967295, 大于100
IF (@CardNO <= 100 OR @CardNO >= 4294967295 )
	RETURN(102)
END

IF @ConsumerName IS NULL
BEGIN
   PRINT 'ERROR: You must specify a ConsumerName value.'
   RETURN(201)
END
ELSE
BEGIN
   IF @ConsumerName = ''
   BEGIN
    PRINT 'ERROR: You must specify a ConsumerName value.'
    RETURN(201)
   END
END


IF @GroupName IS NULL
  SET @groupID=NULL
ELSE
BEGIN
IF @GroupName = ''
  SET @groupID=NULL
ELSE
  BEGIN
   -- Make sure the GroupName is valid.
   SELECT @groupID=f_GroupID FROM t_b_Group WHERE f_GroupName = @GroupName 
   IF @groupID IS NULL
      RETURN(301)
  END
END

--此卡不能由其他人使用
SET @reccount =0
SELECT @reccount=count(*) FROM t_b_IDCard 
WHERE f_CardStatusDesc='0' AND f_CardNO= CONVERT(nvarchar(50), @CardNO) 

IF @reccount >0
      RETURN(103)   

SELECT  @consumerNO=max([f_ConsumerNO]) FROM [t_b_Consumer]
IF @consumerNO IS NULL
	SET @consumerNO =1
ELSE
	SET @consumerNO = @consumerNO+1	

BEGIN TRANSACTION
--添加用户到t_b_Consumer [姓名 部门]
INSERT INTO [t_b_Consumer]([f_ConsumerNO], [f_ConsumerName], [f_GroupID], 
            [f_AttendEnabled], [f_DoorEnabled], [f_BeginYMD], [f_EndYMD],[f_Password], [f_WorkNo])
            VALUES(@consumerNO,          
                @consumerName,
                @groupID,
                1 ,1 , CONVERT( datetime, '2000-01-01'), CONVERT( datetime, '2020-12-31'), '123456', NULL)     

--找到相应用户ID号
SELECT @consumerID= f_ConsumerID from [t_b_Consumer] where f_ConsumerNo = @consumerNO
IF @consumerID IS NULL
	RETURN(9)

--添加卡号到t_b_IDCard  [卡号  用户ID号]
Insert Into [t_b_IDCard] ([f_Cardno], [f_ConsumerID], [f_CardStatusDesc]) 
values (CONVERT(nvarchar(50), @CardNO), 
				@consumerID, 
				'0')

--清除其他人使用了此卡 2007-8-8 17:31:36
Delete from [t_b_IDCard] 
WHERE [f_CardNo]=@CardNO  AND [f_ConsumerID]<> @consumerID

COMMIT TRANSACTION
                                
RETURN(0)

GO

