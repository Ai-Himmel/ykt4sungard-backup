inherited dmDayClearAccImp: TdmDayClearAccImp
  OldCreateOrder = True
  Left = 220
  Top = 208
  Height = 502
  object cqDayAccount: TKCWVQuery
    ID = '�ֶ�����'
    InputBindings = <
      item
        ParamName = '����Ա����'
        FieldName = 'scust_no'
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
    RequestType = 900088
    Left = 24
    Top = 58
  end
  object cqconsumeBalance: TKCWVQuery
    ID = '���ѽ���'
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
        ParamName = '����Ա��'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '�̻��˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '���'
        FieldName = 'damt1'
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
    RequestType = 847222
    Left = 24
    Top = 210
  end
  object cqreConsumeBalance: TKCWVQuery
    ID = '���ѽ������'
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
        ParamName = '����Ա��'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '������ˮ��'
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
    RequestType = 847223
    Left = 24
    Top = 258
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 333
    Top = 48
  end
  object cpfillTrans: TKCWVProcessor
    ID = '��ֵ���'
    InputBindings = <
      item
        ParamName = '����Ա��'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = 'ʳ���˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '���'
        FieldName = 'damt1'
      end
      item
        ParamName = '��ע'
        FieldName = 'scert_addr'
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
    RequestType = 847220
    KCDataset = Dataset
    Left = 24
    Top = 106
  end
  object cqTradeLogDetailed: TKCWVQuery
    ID = '������ˮ��ϸ��Ϣ��ѯ������'
    InputBindings = <
      item
        ParamName = '�ɼ���ʼ����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�ɼ���ʼʱ��'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '�ɼ���������'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '�ɼ�����ʱ��'
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ϴ�����ˮ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�ϴ�����վ��ʶ'
        FieldName = 'lvol4'
      end
      item
        ParamName = '���׷����豸��ʶ'
        FieldName = 'lvol5'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�ͻ���ʶ'
        FieldName = 'lvol9'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'sserial2'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�豸����ID'
        FieldName = 'semp_no'
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
    RequestType = 847171
    Timeout = 60000
    Left = 24
    Top = 302
  end
  object cpfillReTrans: TKCWVProcessor
    ID = '��ֵ������'
    InputBindings = <
      item
        ParamName = '����Ա��'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '������ˮ��'
        FieldName = 'lvol1'
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
      end
      item
        ParamName = '��������ˮ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�������'
        FieldName = 'damt1'
      end
      item
        ParamName = '�����˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�˻����'
        FieldName = 'damt2'
      end>
    RequestType = 847221
    KCDataset = Dataset
    Left = 24
    Top = 154
  end
end
