--������û�[Լ��: ���ź��û���������Ϊ��, ���ſ���Ϊ��; ���Ų����ظ�] 

--ֵ ���� 
--0 �ɹ�ִ�С� 
--101 ���Ų���Ϊ�� 
--102 ���ű������100, С�� 4294967295
--103 �����ѱ�������ʹ��
--104 ���Ų�����
--201 �û���������Ϊ�� 
--301 ���Ű������������Ѵ��ڵ�
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
--���������� ��С��4294967295, ����100
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

--�˿�������������ʹ��
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
--����û���t_b_Consumer [���� ����]
INSERT INTO [t_b_Consumer]([f_ConsumerNO], [f_ConsumerName], [f_GroupID], 
            [f_AttendEnabled], [f_DoorEnabled], [f_BeginYMD], [f_EndYMD],[f_Password], [f_WorkNo])
            VALUES(@consumerNO,          
                @consumerName,
                @groupID,
                1 ,1 , CONVERT( datetime, '2000-01-01'), CONVERT( datetime, '2020-12-31'), '123456', NULL)     

--�ҵ���Ӧ�û�ID��
SELECT @consumerID= f_ConsumerID from [t_b_Consumer] where f_ConsumerNo = @consumerNO
IF @consumerID IS NULL
	RETURN(9)

--��ӿ��ŵ�t_b_IDCard  [����  �û�ID��]
Insert Into [t_b_IDCard] ([f_Cardno], [f_ConsumerID], [f_CardStatusDesc]) 
values (CONVERT(nvarchar(50), @CardNO), 
				@consumerID, 
				'0')

--���������ʹ���˴˿� 2007-8-8 17:31:36
Delete from [t_b_IDCard] 
WHERE [f_CardNo]=@CardNO  AND [f_ConsumerID]<> @consumerID

COMMIT TRANSACTION
                                
RETURN(0)

GO

