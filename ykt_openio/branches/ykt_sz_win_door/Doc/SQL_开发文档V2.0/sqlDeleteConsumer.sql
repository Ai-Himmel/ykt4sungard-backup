--. 删除指定卡号的用户[必须有卡号]
--值 含义 
--0 成功执行。 
--101 卡号不能为空 
--102 卡号必须大于100, 小于 4294967295
--103 卡号已被其他人使用
--104 卡号不存在
--201 用户姓名不能为空 
--301 部门班组名必须是已存在的
--9 SQL Server errors

CREATE PROCEDURE sp_wg_DeleteConsumer
@CardNO bigint
AS
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


--查找卡对应的用户
SELECT @consumerID= f_ConsumerID from [t_b_IDCard] where [f_CardNO]= @CardNO
IF @consumerID IS NULL

	RETURN(104)

BEGIN TRANSACTION
--先删除权限
DELETE FROM [t_d_Privilege]
WHERE [f_ConsumerID]= @consumerID


--再删除卡号
DELETE FROM [t_b_IDCard] 
WHERE [f_ConsumerID]= @consumerID

--最后删除用户
DELETE FROM [t_b_Consumer] 
WHERE [f_ConsumerID]= @consumerID

COMMIT TRANSACTION
                                
RETURN(0)

GO

