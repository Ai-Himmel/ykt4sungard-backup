inherited dmCustomerImp: TdmCustomerImp
  OldCreateOrder = True
  Left = 267
  Top = 215
  Height = 467
  Width = 727
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 40
    Top = 8
  end
  object cqQueryCustomer: TKCWVQuery
    ID = '�ͻ���Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ͻ�״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��ϵ�˵�λ��'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '��ϵ��ѧ����'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '��ϵ������'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = 'ע������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�༶'
        FieldName = 'scard1'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����Ǯ��'
        FieldName = 'sstat_type'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'scust_no2'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841601
    Left = 40
    Top = 58
  end
  object cqsetCustInfo: TKCWVProcessor
    ID = '�ͻ���Ϣ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = 'Ԥ��ע��ʱ��'
        FieldName = 'sdate2'
      end
      item
        ParamName = '��ϵ�˰༶��������'
        FieldName = 'scard1'
      end
      item
        ParamName = '��ϵ�˰༶���ź�'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��ע'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lvol3'
      end
      item
        ParamName = '��ϵ������'
        FieldName = 'sname2'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ϵ������'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '��ϵ��ѧ�Ż�Ա����'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '��ѧ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�ʱ�'
        FieldName = 'spost_code'
      end
      item
        ParamName = '��������'
        FieldName = 'semail'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone2'
      end
      item
        ParamName = '����'
        FieldName = 'snation_code'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus4'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841601
    KCDataset = Dataset
    Left = 40
    Top = 106
  end
  object kcQryCustKind: TKCWVQuery
    ID = '�ͻ�����ѯ'
    InputBindings = <
      item
        ParamName = '�ͻ�������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 843373
    Left = 128
    Top = 26
  end
  object cpSetCustKindInfo: TKCWVProcessor
    ID = '�ͻ������Ϣ����'
    InputBindings = <
      item
        ParamName = '�ͻ�������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ͻ��������'
        FieldName = 'scard0'
      end
      item
        ParamName = 'Ĭ���շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 843373
    KCDataset = Dataset
    Left = 128
    Top = 74
  end
  object cpImpCustInfo: TKCWVProcessor
    ID = '�ͻ���Ϣ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�Ƿ������'
        FieldName = 'scust_type'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'У��'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '��������'
        FieldName = 'scert_no'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '�༶'
        FieldName = 'scard1'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
      end
      item
        ParamName = '�Ա�'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '����'
        FieldName = 'snation_code'
      end
      item
        ParamName = '����'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '��������'
        FieldName = 'semail'
      end
      item
        ParamName = '�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone2'
      end
      item
        ParamName = '��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '�ʱ�'
        FieldName = 'spost_code'
      end
      item
        ParamName = '��У����'
        FieldName = 'Sdate1'
      end
      item
        ParamName = 'Ԥ����У����'
        FieldName = 'sdate2'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end>
    RequestType = 841605
    KCDataset = Dataset
    Left = 40
    Top = 154
  end
  object cpSHlImpCustInfo: TKCWVProcessor
    ID = '�ͻ�������Ϣ����.���'
    InputBindings = <
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����˳���'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'Sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841605
    KCDataset = Dataset
    Left = 216
    Top = 146
  end
  object cqimpCustOper: TKCWVQuery
    ID = '����ͻ���Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sdate0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����˳���'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '�������Ա'
        FieldName = 'Semp_no'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = 'scert_no'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '�༶'
        FieldName = 'scard1'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
      end
      item
        ParamName = '�Ա�'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '����'
        FieldName = 'snation_code'
      end
      item
        ParamName = '����'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '��������'
        FieldName = 'semail'
      end
      item
        ParamName = '�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone2'
      end
      item
        ParamName = '��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��������'
        FieldName = 'spost_code'
      end
      item
        ParamName = '��У����'
        FieldName = 'Sdate1'
      end
      item
        ParamName = 'Ԥ����У����'
        FieldName = 'sdate2'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841605
    Left = 216
    Top = 50
  end
  object cpimpCustOper: TKCWVProcessor
    ID = '����ͻ�����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sdate0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����˳���'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '�������Ա'
        FieldName = 'Semp_no'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = 'scert_no'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '�༶'
        FieldName = 'scard1'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
      end
      item
        ParamName = '�Ա�'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '����'
        FieldName = 'snation_code'
      end
      item
        ParamName = '����'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '��������'
        FieldName = 'semail'
      end
      item
        ParamName = '�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone2'
      end
      item
        ParamName = '��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��������'
        FieldName = 'spost_code'
      end
      item
        ParamName = '��У����'
        FieldName = 'Sdate1'
      end
      item
        ParamName = 'Ԥ����У����'
        FieldName = 'sdate2'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841605
    KCDataset = Dataset
    Left = 216
    Top = 98
  end
  object cpImpBankCard: TKCWVProcessor
    ID = '���п�����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�Ƿ������'
        FieldName = 'scust_type'
      end
      item
        ParamName = '������־'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '���п���'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'У��'
        FieldName = 'sbranch_code0'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end>
    RequestType = 841602
    KCDataset = Dataset
    Left = 40
    Top = 202
  end
  object cpBankCardManger: TKCWVProcessor
    ID = '�������п�����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '���п���'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '�����п���'
        FieldName = 'scard1'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841602
    KCDataset = Dataset
    Left = 40
    Top = 250
  end
  object KCWVQuery1: TKCWVQuery
    ID = '���п��󶨲�ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��״̬'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '���п���'
        FieldName = 'scard0'
      end
      item
        ParamName = '������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841602
    Left = 128
    Top = 122
  end
  object cpPatchdel: TKCWVProcessor
    ID = '���п�����ɾ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '������־'
        FieldName = 'lwithdraw_flag'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841602
    KCDataset = Dataset
    Left = 216
    Top = 198
  end
  object cpCustPatchDel: TKCWVProcessor
    ID = '�ͻ�����ɾ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '������־'
        FieldName = 'lwithdraw_flag'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841605
    KCDataset = Dataset
    Left = 128
    Top = 174
  end
  object cpPhotoQuery: TKCWVProcessor
    ID = '��Ƭ��ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '�ļ���'
        FieldName = 'vsvarstr1'
      end>
    RequestType = 841600
    KCDataset = Dataset
    Left = 216
    Top = 246
  end
  object cpBatchEditStuNo: TKCWVProcessor
    ID = '�����޸�ѧ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '������־'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '��ѧ����'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = 'ԭѧ����'
        FieldName = 'scert_no'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841601
    KCDataset = Dataset
    Left = 128
    Top = 218
  end
  object cpImpNewstu: TKCWVProcessor
    ID = '������������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�Ƿ������'
        FieldName = 'scust_type'
      end
      item
        ParamName = '������־'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�¿���ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '����Ч��'
        FieldName = 'sdate0'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end>
    RequestType = 846130
    KCDataset = Dataset
    Left = 128
    Top = 266
  end
  object cpImpNewStuManage: TKCWVProcessor
    ID = '����������������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�¿�����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '������־'
        FieldName = 'lserial1'
        DefaultValue = 0
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����Ч��'
        FieldName = 'sdate0'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846130
    KCDataset = Dataset
    Left = 40
    Top = 298
  end
  object kcImpNewStuQ: TKCWVQuery
    ID = '�������������ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��״̬'
        FieldName = 'sserial0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�¿���ʾ����'
        FieldName = 'sorder0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846130
    Left = 128
    Top = 314
  end
  object cpImpBankCardLink: TKCWVProcessor
    ID = '���п���������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '�Ƿ������'
        FieldName = 'scust_type'
      end
      item
        ParamName = '������־'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'Lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '���п���'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'У��'
        FieldName = 'sbranch_code0'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end>
    RequestType = 841603
    KCDataset = Dataset
    Left = 288
    Top = 26
  end
  object kcImpBankCardLinkQ: TKCWVQuery
    ID = '���п��󶨲�ѯ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��״̬'
        FieldName = 'lsafe_level2'
        DefaultValue = 0
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '���п���'
        FieldName = 'scard0'
      end
      item
        ParamName = '������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841603
    Left = 288
    Top = 74
  end
  object cpImpBankMangLink: TKCWVProcessor
    ID = '�������п���������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��¼��'
        FieldName = 'sname2'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '���п���'
        FieldName = 'scard0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841603
    KCDataset = Dataset
    Left = 288
    Top = 122
  end
  object cpPatchDelLink: TKCWVProcessor
    ID = '���п�����ɾ������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '������־'
        FieldName = 'lsafe_level2'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841603
    KCDataset = Dataset
    Left = 288
    Top = 166
  end
  object cpLinkBinding: TKCWVProcessor
    ID = '���п�������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��¼��'
        FieldName = 'Sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sstatus1'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841603
    KCDataset = Dataset
    Left = 288
    Top = 214
  end
  object cqBankLinkQuery: TKCWVQuery
    ID = '���п�������ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = 'ѧ��'
        FieldName = 'spager'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841603
    Left = 288
    Top = 266
  end
  object cqBankBingdingQuery: TKCWVQuery
    ID = '���п�����ˮ��ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���׿�ʼ����'
        FieldName = 'stime1'
      end
      item
        ParamName = '���׽�������'
        FieldName = 'stime2'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ѧ��'
        FieldName = 'Spager'
      end
      item
        ParamName = '���п���'
        FieldName = 'scard0'
      end
      item
        ParamName = '��������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '��ɾ��־'
        FieldName = 'lvol9'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 841604
    Left = 288
    Top = 314
  end
end
