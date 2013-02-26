--. ɾ��ָ�����ŵ��û�[�����п���]
--ֵ ���� 
--0 �ɹ�ִ�С� 
--101 ���Ų���Ϊ�� 
--102 ���ű������100, С�� 4294967295
--103 �����ѱ�������ʹ��
--104 ���Ų�����
--201 �û���������Ϊ�� 
--301 ���Ű������������Ѵ��ڵ�
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
--���������� ��С��4294967295, ����100
IF (@CardNO <= 100 OR @CardNO >= 4294967295 )
	RETURN(102)
END


--���ҿ���Ӧ���û�
SELECT @consumerID= f_ConsumerID from [t_b_IDCard] where [f_CardNO]= @CardNO
IF @consumerID IS NULL

	RETURN(104)

BEGIN TRANSACTION
--��ɾ��Ȩ��
DELETE FROM [t_d_Privilege]
WHERE [f_ConsumerID]= @consumerID


--��ɾ������
DELETE FROM [t_b_IDCard] 
WHERE [f_ConsumerID]= @consumerID

--���ɾ���û�
DELETE FROM [t_b_Consumer] 
WHERE [f_ConsumerID]= @consumerID

COMMIT TRANSACTION
                                
RETURN(0)

GO

