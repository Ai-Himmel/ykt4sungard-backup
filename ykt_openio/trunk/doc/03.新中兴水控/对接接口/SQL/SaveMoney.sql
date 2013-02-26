use newks
go

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TPE_Account_SaveMoney]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[TPE_Account_SaveMoney]
go

Create  PROCEDURE [dbo].[TPE_Account_SaveMoney]
(@Result int output,@accountno int,@Save_Money money,@station_no int,@oper_no int) AS
begin
 declare @pd_money money,@name varchar(16),@now_money money,@branch_no varchar(9),@pid_no int,@accountId varchar(10),@lock_flag tinyint,@gdc6_accountno int
 declare @mac float
 
 select top 1 @pd_money=save_pd,@name=b.ÐÕÃû,@now_money=b.now_money,@branch_no=b.branch_no,@pid_no=b.pid_no,@accountId=b.accountId,@lock_flag=b.lock_flag,@gdc6_accountno=b.gdc6_accountno from pid_mes a,emmployee b where a.pid_no=b.pid_no and b.accountno=@accountno
 if @@rowcount<=0 begin
	set @Result = 1
	return  
 end
 begin tran
  update emmployee set now_money=now_money+@Save_Money,lock_flag=0,mac=dbo.get_mac(now_money+@save_money,cardfee,prefee,save_money) where accountno=@accountno

  select @mac=dbo.get_mac(@now_money+@save_money,@save_money,0,@pd_money+@now_money)
  insert into operate_water(operate_kindno,Operate_time,Accountno,ÐÕÃû,accountid,branch_no,pid_no,now_money,save_money,pd_money,old_nowmoney,Oper_no,Õ¾ºÅ,gdc6_Accountno,mac)
   values(6,getdate(),@accountno,@name,@accountId,@branch_no,@pid_no,@now_money+@save_money,@save_money,@pd_money,@now_money,@oper_no,@station_no,@gdc6_Accountno,@mac) 
  
  update daily_rec set total_savemoney=total_savemoney+@save_money
 commit tran
 set @Result = 0
 return
end

