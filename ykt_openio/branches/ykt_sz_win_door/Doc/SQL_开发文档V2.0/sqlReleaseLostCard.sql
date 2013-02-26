--解挂卡[必须有原卡号]
--返回值 含义 
--0 成功执行。 
--101 卡号不能为空 
--102 卡号必须大于100, 小于 4294967295
--103 卡号已被其他人使用
--104 卡号不存在
--105 此卡的用户已拥有新的卡号, 不能解挂
--201 用户姓名不能为空 
--301 部门班组名必须是已存在的
--9 SQL Server errors

CREATE PROCEDURE sp_wg_ReleaseLostCard
@CardNO bigint
AS
DECLARE @reccount as int
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

--查找用户是否持有新的卡
SELECT @reccount= count(*) from [t_b_IDCard] where [f_ConsumerID]= @consumerID AND [f_CardStatusDesc]='0'
IF @reccount > 0
	RETURN(105)

--解挂原有卡
Update [t_b_IDCard]
SET [f_CardStatusDesc]= '0'
WHERE [f_CardNo]= @CardNO 
                                
RETURN(0)

GO

