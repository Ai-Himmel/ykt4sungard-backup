--修改用户姓名和所属部门[必须有卡号]--不改卡号, 卡号和用户姓名不能为空, 部门可以为空
--返回值 含义 
--0 成功执行。 
--101 卡号不能为空 
--102 卡号必须大于100, 小于 4294967295
--103 卡号已被其他人使用
--104 卡号不存在
--201 用户姓名不能为空 
--301 部门班组名必须是已存在的
--9 SQL Server errors

CREATE PROCEDURE sp_wg_EditConsumerNameAndGroupName
@CardNO bigint,
@ConsumerName nvarchar(100),
@GroupName nvarchar(100)=NULL
AS
DECLARE @groupID  as int  
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

--查找卡对应的用户
SELECT @consumerID= f_ConsumerID from [t_b_IDCard] where [f_CardNO]= @CardNO
IF @consumerID IS NULL
	RETURN(104)

--更新用户到t_b_Consumer [姓名 部门]
UPDATE [t_b_Consumer] 
SET [f_ConsumerName] = @consumerName, 
    [f_GroupID]      = @groupID
WHERE [f_ConsumerID]= @consumerID
                                
RETURN(0)

GO

