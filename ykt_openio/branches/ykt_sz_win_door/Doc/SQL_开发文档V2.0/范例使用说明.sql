--�汾˵�� 
--V2.0 2009-12-17 
--  ���� ������ѯ
--   sqlRegisterLostCardWithoutNewCard.sql ֻ��ʧ���� �����¿� 
--   sqlReleaseLostCard ���  
--  ���ӷ���ֵ: 105 �˿����û���ӵ���µĿ���, ���ܽ��

--
--��һ�����з���ʱ, ��ִ��������ѯ
--sqlNewConsumer.sql  ---������û�
--sqlDeleteConsumer.sql  --ɾ��ָ�����ŵ��û�
--sqlRegisterLostCard.sql --��ʧ��
--sqlEditConsumerNameAndGroupName.sql  --�޸��û���������������
--sqlRegisterLostCardWithoutNewCard.sql --��ʧ�������¿�[������ԭ����]
--sqlReleaseLostCard  --��ҿ�[������ԭ����]

--����
DECLARE @ret_code INT
--sqlNewConsumer.sql  ����û�
--��ӿ���:��91234, ����: ��С��  ����:
--EXEC @ret_code=sp_wg_NewConsumer 91234,'��С��',NULL
--PRINT @ret_code

--��ӿ���:��91235, ����: ��С  ����: ������
--EXEC @ret_code=sp_wg_NewConsumer 91235,'��С','������'   --���벿��(�������Ҫ�����һ��"������")
--PRINT @ret_code

--sqlDeleteConsumer.sql ɾ���û�
--EXEC @ret_code=sp_wg_DeleteConsumer 91235   --ɾ������Ϊ91235���û�
--PRINT @ret_code

--sqlEditConsumerNameAndGroupName.sql  �޸��û������������ڲ���
--EXEC @ret_code=sp_wg_EditConsumerNameAndGroupName 91234,'��С��2','������'
--PRINT @ret_code

--sqlRegisterLostCard.sql ��ʧ���� 
--91234Ϊ�ɿ���, 91235Ϊ�¿���
--EXEC @ret_code=sp_wg_RegisterLostCard 91234,91235
--PRINT @ret_code

--sqlRegisterLostCardWithoutNewCard.sql ֻ��ʧ���� �����¿� 
--91234Ϊ�ɿ���
--EXEC @ret_code=sp_wg_RegisterLostCardWithoutNewCard 91234
--PRINT @ret_code

--sqlReleaseLostCard ���  
--91234Ϊ�ɿ���
--EXEC @ret_code=sp_wg_ReleaseLostCard 91234
--PRINT @ret_code

PRINT @ret_code
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


GO