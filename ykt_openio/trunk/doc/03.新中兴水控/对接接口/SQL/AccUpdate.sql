use newks
go

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[JSD_Account_Update]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[JSD_Account_Update]
go

Create   procedure [dbo].[JSD_Account_Update]
	( @Result int output,@Accountno int,@Name varchar(16),@Gdc6_Pid_no int,@Card_no int,
	 @Old_Card_no int, @Work_mes int,@UpdateTime varchar(20)) 
AS
BEGIN
	declare @tmpDate datetime
	set @tmpDate = CONVERT (datetime , @UpdateTime)
	if(@tmpDate<'2007-01-01')
	begin
		set @tmpDate = Getdate()
	end
/*	insert into Table1(UpdateTime) values(@tmpDate) 
	set @Result = 0
return*/
 	DECLARE @branch1_no char(3),@branch2_no char(6),@branch_no char(9),@pid_no int

 	select top 1 @pid_no=pid_no from pid_mes where gdc6_pid_no=@gdc6_pid_no
 	if @@rowcount<=0 
 	Begin
   		set @Result=1
   		return --身份不正确,不能导入
 	end
	set @branch1_no = '001'
	set @branch2_no = '001001'
	set @branch_no = '001001001'

  	begin tran
 		update emmployee set card_no=@card_no,old_card_no=@old_card_no,branch1_no=@branch1_no,
			branch2_no=@branch2_no,branch_no=@branch_no,work_mes=@work_mes,pid_no=@pid_no,
			gdc6_accountno=@accountno,姓名=@name,account_date=@tmpDate 
	  		where accountno=@accountno
 	if @@rowcount<=0
 	Begin
  		insert into emmployee(accountno,accountid,姓名,card_no,old_card_no,branch1_no,branch2_no,branch_no,
			pid_no,cardfee,prefee, work_mes,Now_money, save_money,  gdc6_accountno,account_date,站号)
	 		values(@accountno,'',@name,@card_no,@old_card_no,@branch1_no,@branch2_no,@branch_no,@pid_no,0,0,
			@work_mes,0,0,@accountno,@tmpDate,0)
	  	if @@error>0 begin
	   		rollback tran
	   		set @Result=4
	   		return
  		end
		update daily_rec set account_num=account_num+1 
   		if @@error>0 begin
   			rollback tran
   			return  4
   		end

/*	  	select * from month_cost where Accountno=@accountno
	  	if @@rowcount=0
	  	begin
	    	insert into month_cost values(@accountno,0,0,0,0,0,0,0,0,0,0,0)
	    	if @@error>0 begin
	     		rollback tran    
	     		set @Result=4
	     		return 4 
	    	end
	  	end*/
 	end
 	commit tran
 	set @Result=0 
 	return 
end
--delete emmployee where accountno=100001
--select * from emmployee where accountno=100001
--update emmployee set card_no= 11111 where accountno=100001