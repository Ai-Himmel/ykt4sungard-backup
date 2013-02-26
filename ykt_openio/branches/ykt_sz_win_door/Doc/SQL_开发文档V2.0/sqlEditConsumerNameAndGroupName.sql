--�޸��û���������������[�����п���]--���Ŀ���, ���ź��û���������Ϊ��, ���ſ���Ϊ��
--����ֵ ���� 
--0 �ɹ�ִ�С� 
--101 ���Ų���Ϊ�� 
--102 ���ű������100, С�� 4294967295
--103 �����ѱ�������ʹ��
--104 ���Ų�����
--201 �û���������Ϊ�� 
--301 ���Ű������������Ѵ��ڵ�
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

--���ҿ���Ӧ���û�
SELECT @consumerID= f_ConsumerID from [t_b_IDCard] where [f_CardNO]= @CardNO
IF @consumerID IS NULL
	RETURN(104)

--�����û���t_b_Consumer [���� ����]
UPDATE [t_b_Consumer] 
SET [f_ConsumerName] = @consumerName, 
    [f_GroupID]      = @groupID
WHERE [f_ConsumerID]= @consumerID
                                
RETURN(0)

GO

