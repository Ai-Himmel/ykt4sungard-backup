--版本说明 
--V2.0 2009-12-17 
--  增加 两个查询
--   sqlRegisterLostCardWithoutNewCard.sql 只挂失卡号 不补新卡 
--   sqlReleaseLostCard 解挂  
--  增加返回值: 105 此卡的用户已拥有新的卡号, 不能解挂

--
--第一次运行范例时, 先执行六个查询
--sqlNewConsumer.sql  ---添加新用户
--sqlDeleteConsumer.sql  --删除指定卡号的用户
--sqlRegisterLostCard.sql --挂失卡
--sqlEditConsumerNameAndGroupName.sql  --修改用户姓名和所属部门
--sqlRegisterLostCardWithoutNewCard.sql --挂失卡不补新卡[必须有原卡号]
--sqlReleaseLostCard  --解挂卡[必须有原卡号]

--范例
DECLARE @ret_code INT
--sqlNewConsumer.sql  添加用户
--添加卡号:　91234, 姓名: 张小三  部门:
--EXEC @ret_code=sp_wg_NewConsumer 91234,'张小三',NULL
--PRINT @ret_code

--添加卡号:　91235, 姓名: 张小  部门: 开发部
--EXEC @ret_code=sp_wg_NewConsumer 91235,'张小','开发部'   --加入部门(在软件中要先添加一个"开发部")
--PRINT @ret_code

--sqlDeleteConsumer.sql 删除用户
--EXEC @ret_code=sp_wg_DeleteConsumer 91235   --删除卡号为91235的用户
--PRINT @ret_code

--sqlEditConsumerNameAndGroupName.sql  修改用户的姓名和所在部门
--EXEC @ret_code=sp_wg_EditConsumerNameAndGroupName 91234,'张小三2','开发部'
--PRINT @ret_code

--sqlRegisterLostCard.sql 挂失卡号 
--91234为旧卡号, 91235为新卡号
--EXEC @ret_code=sp_wg_RegisterLostCard 91234,91235
--PRINT @ret_code

--sqlRegisterLostCardWithoutNewCard.sql 只挂失卡号 不补新卡 
--91234为旧卡号
--EXEC @ret_code=sp_wg_RegisterLostCardWithoutNewCard 91234
--PRINT @ret_code

--sqlReleaseLostCard 解挂  
--91234为旧卡号
--EXEC @ret_code=sp_wg_ReleaseLostCard 91234
--PRINT @ret_code

PRINT @ret_code
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


GO