--��ʧ��[������ԭ����, �¿���]
--����ֵ ���� 
--0 �ɹ�ִ�С� 
--101 ���Ų���Ϊ�� 
--102 ���ű������100, С�� 4294967295
--103 �����ѱ�������ʹ��
--104 ���Ų�����
--201 �û���������Ϊ�� 
--301 ���Ű������������Ѵ��ڵ�
--9 SQL Server errors

CREATE PROCEDURE sp_wg_RegisterLostCard
@CardNO bigint,
@NewCardNO bigint
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
--���������� ��С��4294967295, ����100
IF (@CardNO <= 100 OR @CardNO >= 4294967295 )
	RETURN(102)
END

IF @NewCardNO IS NULL
BEGIN
   PRINT 'ERROR: You must specify a NewCardNO value.'
   RETURN(101)
END
ELSE
BEGIN
--���������� ��С��4294967295, ����100
IF (@NewCardNO <= 100 OR @NewCardNO >= 4294967295 )
	RETURN(102)
END


--���ҿ���Ӧ���û�
SELECT @consumerID= f_ConsumerID from [t_b_IDCard] where [f_CardNO]= @CardNO
IF @consumerID IS NULL
	RETURN(104)

--���¿����Ƿ�����
SELECT @reccount=count(*) FROM t_b_IDCard 
WHERE f_CardStatusDesc='0' 
   AND f_CardNO= @NewCardNO 

IF @reccount >0
	--�¿�������ʹ��, ��������ʧ���� 
   RETURN(103)

BEGIN TRANSACTION

--��ʧԭ�п�
Update [t_b_IDCard]
SET [f_CardStatusDesc]= '�ѹ�ʧ'
WHERE [f_CardNo]= @CardNO 

--�ֿ���ԭ���еĿ�ȫ����ʧ
Update [t_b_IDCard]
SET [f_CardStatusDesc]= '�ѹ�ʧ'
WHERE [f_ConsumerID]= @consumerID


--��ָ�����¿�
DELETE FROM [t_b_IDCard]
WHERE  [f_CardNo]=@NewCardNO

--����¿�
Insert Into [t_b_IDCard] ([f_Cardno], [f_ConsumerID], [f_CardStatusDesc])
values (@NewCardNO, @consumerID, '0')

COMMIT TRANSACTION
                                
RETURN(0)

GO

