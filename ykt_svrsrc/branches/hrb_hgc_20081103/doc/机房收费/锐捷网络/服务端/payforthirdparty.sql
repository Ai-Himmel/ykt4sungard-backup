
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_pay_for_thirdparty]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
	drop procedure [dbo].[sp_pay_for_thirdparty]
GO

CREATE PROCEDURE [dbo].[sp_pay_for_thirdparty]
(
	@userid		VARCHAR(32),
	@fee		NUMERIC(8,2),
	@manager	VARCHAR(32),
	@type		NUMERIC(2),	--1表示普通付费,2表示预付待扣款付费.
	@status		NUMERIC(1) OUTPUT --1表示成功,0表示失败
)
with encryption
AS
	DECLARE @payid		NUMERIC(18, 0)
	DECLARE @flowid		NUMERIC(18, 0)
	DECLARE @nowtime	DATETIME
	DECLARE @time_str   VARCHAR(16)
	DECLARE @pay_flowid_len INT
	DECLARE @acctflow_flowid_len INT
	DECLARE @seqMultiplicator NUMERIC(18,0)
	DECLARE @errCode INT
BEGIN
	SET NOCOUNT ON

	SET @errCode = 0
	SET @status = 0

	--查询缴费记录表FLOWID字段长度
	SELECT @pay_flowid_len=c.xprec
		FROM syscolumns c INNER JOIN sysobjects o on c.id=o.id
		WHERE o.name='T_PAY' AND c.name='FLOWID'

	IF @@error <> 0
		RETURN

	--查询账务流水表FLOWID字段长度
	SELECT @acctflow_flowid_len=c.xprec
		FROM syscolumns c INNER JOIN sysobjects o on c.id=o.id
		WHERE o.name='T_ACCTFLOW' AND c.name='FLOWID'

	IF @@error <> 0
		RETURN

	SET @nowtime = GETDATE()
	SET @time_str = '99' + CONVERT(VARCHAR(16), @nowtime, 12)  --格式: 99yyMMdd，避免和SAM管理系统生成的序号重复

	BEGIN TRANSACTION 

	--生成帐务流水序号
	UPDATE T_TABLESEQ SET SEQ = SEQ + 1 WHERE NAME = 'FLOWID'

	SET @errCode = @@error
	IF @errCode <> 0
		GOTO errorHandle

	SELECT @flowid = SEQ - 1 FROM T_TABLESEQ WHERE NAME = 'FLOWID'

	SET @errCode = @@error
	IF @errCode <> 0
		GOTO errorHandle

	--根据FLOWID字段长度判断序号长度
	IF @acctflow_flowid_len > 12
		SET @seqMultiplicator = 1000000
	ELSE
		SET @seqMultiplicator = 10000

	--如果超出序号最大值，返回错误
	IF @flowid >= @seqMultiplicator
	BEGIN
		SET @errCode = 0
		GOTO errorHandle
	END

	--生成帐务流水号
	SET @flowid = CONVERT(NUMERIC(18,0), @time_str) * @seqMultiplicator + @flowid
        
	--生成缴费记录序号
	UPDATE T_TABLESEQ SET SEQ = SEQ + 1 WHERE NAME = 'PAYID'

	SET @errCode = @@error
	IF @errCode <> 0
		GOTO errorHandle

	SELECT @payid = SEQ - 1 FROM T_TABLESEQ WHERE NAME = 'PAYID'

	SET @errCode = @@error
	IF @errCode <> 0
		GOTO errorHandle

	--根据FLOWID字段长度判断序号长度
	IF @pay_flowid_len > 12
		SET @seqMultiplicator = 1000000
	ELSE
		SET @seqMultiplicator = 10000

	--如果超出序号最大值，返回错误
	IF @payid >= @seqMultiplicator
	BEGIN
		SET @errCode = 0
		GOTO errorHandle
	END

	--生成缴费记录号
	SET @payid = CONVERT(NUMERIC(18,0), @time_str) * @seqMultiplicator + @payid

    --写帐务流水
	INSERT INTO T_ACCTFLOW(FLOWID,ACCTTIME,MANAGERID,FEETYPE,FEE) VALUES(@flowid,GETDATE(),@manager,0,@fee)

	SET @errCode = @@error
	IF @errCode <> 0
		GOTO errorHandle

    --写缴费记录
	INSERT INTO T_PAY(FLOWID,PAYTYPE,USERID,PAYTIME,MANAGERID,FEE) VALUES(@payid,0,@userid,GETDATE(),@manager,@fee)

	SET @errCode = @@error
	IF @errCode <> 0
		GOTO errorHandle
        
	--更新用户余额或者预付待扣款
	IF(@type = 1)
		UPDATE T_USER SET LEFTFEE=LEFTFEE + @fee WHERE USERID = @userid
	ELSE
		UPDATE T_USER SET PREFEE=PREFEE + @fee WHERE USERID = @userid

	SET @errCode = @@error
	IF @errCode <> 0
		GOTO errorHandle

	COMMIT TRANSACTION
	SET @status = 1
	RETURN

    -- 出现错误，需要回滚事务
errorHandle:
	BEGIN
		ROLLBACK TRANSACTION
		SET @status = 0
		RETURN
	END
END

GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_add_thirdparty_pay_dbuser]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_add_thirdparty_pay_dbuser]
GO


-- =============================================
-- Author:		杨科
-- Create date: 2008-05-21
-- Description:	添加第三方付费接口使用的数据库账号
-- 参数：
-- 		username	添加的账号
-- 		password	密码
-- 		defaultDb	添加的账号的默认数据库
-- =============================================
CREATE PROCEDURE dbo.sp_add_thirdparty_pay_dbuser 
(
	@username nvarchar(32),
	@password varchar(32),
	@defaultDb varchar(32)
)
AS
BEGIN
	SET NOCOUNT ON;

	declare @debug smallint
	set @debug=0

	--添加用户

	if not exists(select * from master.dbo.syslogins where loginname=@username)
		exec sp_addlogin @username, @password, @defaultDb

	if not exists(select * from sysusers where name = @username)
		exec sp_adduser @username

	--添加用户权限

	declare @grant_sql nvarchar(512)

	set @grant_sql = N'GRANT SELECT,UPDATE ON '
		+ N'T_USER (ACCTSTATE,ENDTIME,LASTUPDATETIME,LEFTFEE,LEFTTIME,LEFTTRAFFIC,MONTHLYACCTTIME,PREFEE,ATNAME,LASTBILLTIME) TO '
		+ @username

	execute sp_executesql @grant_sql


	set @grant_sql = N'GRANT SELECT,UPDATE ON T_TABLESEQ TO ' + @username
	execute sp_executesql @grant_sql

	set @grant_sql = N'GRANT SELECT ON T_USER (FIRSTLOGIN,USERGROUPID,USERID,USERTYPE) TO ' + @username
	execute sp_executesql @grant_sql

	set @grant_sql = N'GRANT SELECT ON T_USERGROUP (ATNAME,USERGROUPID) TO ' + @username
	execute sp_executesql @grant_sql

	set @grant_sql = N'GRANT SELECT ON T_ACCTTEMPLATE (ATNAME,POLICYNAME) TO ' + @username
	execute sp_executesql @grant_sql

	set @grant_sql = N'GRANT SELECT ON T_POLICY TO ' + @username
	execute sp_executesql @grant_sql

	set @grant_sql = N'GRANT SELECT ON T_POLICYPROPERTY TO ' + @username
	execute sp_executesql @grant_sql

	set @grant_sql = N'GRANT INSERT ON T_ACCTFLOW TO ' + @username
	execute sp_executesql @grant_sql

	set @grant_sql = N'GRANT INSERT ON T_PAY TO ' + @username
	execute sp_executesql @grant_sql
	
	set @grant_sql = N'GRANT EXECUTE ON dbo.sp_pay_for_thirdparty TO ' + @username
	execute sp_executesql @grant_sql


	declare @owner_name nvarchar(32)

	select @owner_name=u.name
		from sysusers u inner join sysobjects o on u.uid=o.uid
		where o.xtype='P' and o.name='sp_activate_user'

	set @grant_sql = N'GRANT EXECUTE ON ' + @owner_name + N'.sp_activate_user TO ' + @username
	execute sp_executesql @grant_sql
END

GO
