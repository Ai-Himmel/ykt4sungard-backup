--��ҿ�[������ԭ����]
--����ֵ ���� 
--0 �ɹ�ִ�С� 
--101 ���Ų���Ϊ�� 
--102 ���ű������100, С�� 4294967295
--103 �����ѱ�������ʹ��
--104 ���Ų�����
--105 �˿����û���ӵ���µĿ���, ���ܽ��
--201 �û���������Ϊ�� 
--301 ���Ű������������Ѵ��ڵ�
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
--���������� ��С��4294967295, ����100
IF (@CardNO <= 100 OR @CardNO >= 4294967295 )
	RETURN(102)
END

--���ҿ���Ӧ���û�
SELECT @consumerID= f_ConsumerID from [t_b_IDCard] where [f_CardNO]= @CardNO
IF @consumerID IS NULL
	RETURN(104)

--�����û��Ƿ�����µĿ�
SELECT @reccount= count(*) from [t_b_IDCard] where [f_ConsumerID]= @consumerID AND [f_CardStatusDesc]='0'
IF @reccount > 0
	RETURN(105)

--���ԭ�п�
Update [t_b_IDCard]
SET [f_CardStatusDesc]= '0'
WHERE [f_CardNo]= @CardNO 
                                
RETURN(0)

GO

