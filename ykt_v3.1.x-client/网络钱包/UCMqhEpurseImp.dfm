inherited dmEpurseRegImp: TdmEpurseRegImp
  OldCreateOrder = True
  Left = 285
  Width = 574
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 304
    Top = 8
  end
  object cqEpurseReg: TKCWVProcessor
    ID = '����Ǯ������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ʻ�����'
        FieldName = 'snote2'
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
    RequestType = 846331
    KCDataset = Dataset
    Left = 24
    Top = 10
  end
  object KCWEPurseDestory: TKCWVQuery
    ID = '������ѯ'
    InputBindings = <
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '���ڲ���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
      end
      item
        ParamName = 'ֹ��״̬'
        FieldName = 'scust_type'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�ʺ�'
        FieldName = 'sbank_acc'
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
    RequestType = 846603
    Left = 24
    Top = 58
  end
  object cqEPurseDestory: TKCWVProcessor
    ID = '����Ǯ������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ʻ�����'
        FieldName = 'snote2'
      end
      item
        ParamName = '�ʺ�'
        FieldName = 'sbank_acc'
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
    RequestType = 846332
    KCDataset = Dataset
    Left = 24
    Top = 106
  end
  object cqEPurseIn: TKCWVProcessor
    ID = '����Ǯ����ֵ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ʺ�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '��ֵ��ʽ'
        FieldName = 'lvol9'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '��ֵ���'
        FieldName = 'damt0'
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
    RequestType = 846333
    KCDataset = Dataset
    Left = 24
    Top = 154
  end
  object cqEPurseOut1: TKCWVProcessor
    ID = '����Ǯ��֧ȡ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ʺ�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ȡ������'
        FieldName = 'snote2'
      end
      item
        ParamName = 'ȡ����'
        FieldName = 'damt0'
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
    RequestType = 846334
    KCDataset = Dataset
    Left = 24
    Top = 202
  end
  object cqFreeze: TKCWVProcessor
    ID = 'Ǯ��ֹ���⸶'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ʺ�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��־'
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
    RequestType = 846335
    KCDataset = Dataset
    Left = 24
    Top = 250
  end
  object cqEPurseTrans: TKCWVProcessor
    ID = '����Ǯ��ת��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�뿨���'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '��ֵ���'
        FieldName = 'damt0'
      end
      item
        ParamName = 'ת�˷���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�ʻ�����'
        FieldName = 'snote2'
      end
      item
        ParamName = '������'
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
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end>
    RequestType = 846336
    KCDataset = Dataset
    Left = 22
    Top = 304
  end
  object cqchangepwd: TKCWVProcessor
    ID = 'Ǯ�������޸�'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ʺ�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '������'
        FieldName = 'snote'
      end
      item
        ParamName = '������'
        FieldName = 'snote2'
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
    RequestType = 846337
    KCDataset = Dataset
    Left = 88
    Top = 26
  end
  object cqresetpwd: TKCWVProcessor
    ID = 'Ǯ����������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ʺ�'
        FieldName = 'sbank_acc'
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
        ParamName = '������'
        FieldName = 'snote2'
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
    RequestType = 846338
    KCDataset = Dataset
    Left = 88
    Top = 74
  end
end
