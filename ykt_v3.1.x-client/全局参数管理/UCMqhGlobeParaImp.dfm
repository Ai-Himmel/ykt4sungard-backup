inherited dmGlobeParaImp: TdmGlobeParaImp
  OldCreateOrder = True
  Left = 270
  Top = 210
  object cpAddGlobeParaInfo: TKCWVProcessor
    ID = 'ȫ�ֲ�������.����'
    InputBindings = <
      item
        ParamName = '������ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'scard0'
      end
      item
        ParamName = '��Чʱ��'
        FieldName = 'spager'
      end
      item
        ParamName = '������λ'
        FieldName = 'scust_no'
      end
      item
        ParamName = '��ע'
        FieldName = 'scusttypes'
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
    RequestType = 820401
    KCDataset = Dataset
    Left = 200
    Top = 74
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 312
    Top = 136
  end
  object cpChangeGlobeParaInfo: TKCWVProcessor
    ID = 'ȫ�ֲ�������.�޸�'
    InputBindings = <
      item
        ParamName = '������ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'scard0'
      end
      item
        ParamName = '��Чʱ��'
        FieldName = 'spager'
      end
      item
        ParamName = '������λ'
        FieldName = 'scust_no'
      end
      item
        ParamName = '��ע'
        FieldName = 'scusttypes'
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
    RequestType = 820402
    KCDataset = Dataset
    Left = 200
    Top = 128
  end
  object cpDelGlobeParaInfo: TKCWVProcessor
    ID = 'ȫ�ֲ�������.ɾ��'
    InputBindings = <
      item
        ParamName = '������ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'scard0'
      end
      item
        ParamName = '��Чʱ��'
        FieldName = 'spager'
      end
      item
        ParamName = '������λ'
        FieldName = 'scust_no'
      end
      item
        ParamName = '��ע'
        FieldName = 'scusttypes'
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
    RequestType = 820403
    KCDataset = Dataset
    Left = 200
    Top = 184
  end
  object cqQueryGlobeParaByOther: TKCWVQuery
    ID = 'ȫ�ֲ����ǹؼ��ֲ�ѯ'
    InputBindings = <
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'scard0'
      end
      item
        ParamName = '��Чʱ��'
        FieldName = 'spager'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'sphone'
      end
      item
        ParamName = '������λ'
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
    RequestType = 820405
    Left = 200
    Top = 18
  end
  object cqQueryGlobeParaByKey: TKCWVQuery
    ID = 'ȫ�ֲ����ؼ��ֲ�ѯ'
    InputBindings = <
      item
        ParamName = '������־'
        FieldName = 'lvol0'
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
    RequestType = 820405
    Left = 48
    Top = 122
  end
  object cpAddSetChargePara: TKCWVProcessor
    ID = '�շѲ�������.����'
    InputBindings = <
      item
        ParamName = '��λ����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�շ����'
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
      end>
    RequestType = 847190
    KCDataset = Dataset
    Left = 200
    Top = 242
  end
  object cpChargeSetChargePara: TKCWVProcessor
    ID = '�շѲ�������.�޸�'
    InputBindings = <
      item
        ParamName = '��λ����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�շ����'
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
      end>
    RequestType = 847191
    KCDataset = Dataset
    Left = 200
    Top = 298
  end
  object cpDelSetChargePara: TKCWVProcessor
    ID = '�շѲ�������.ɾ��'
    InputBindings = <
      item
        ParamName = '��λ����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�շ����'
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
      end>
    RequestType = 847192
    KCDataset = Dataset
    Left = 200
    Top = 346
  end
  object cqSetChargePara: TKCWVQuery
    ID = '�շѲ�����ѯ'
    InputBindings = <
      item
        ParamName = '��λ����'
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
    RequestType = 847193
    Left = 48
    Top = 290
  end
  object cqSetChargeType: TKCWVQuery
    ID = '�շ��������'
    InputBindings = <
      item
        ParamName = '�շ����'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '�Ƿ��մ���'
        FieldName = 'sname'
      end
      item
        ParamName = '����־'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��־'
        FieldName = 'sstatus0'
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
    RequestType = 847198
    Left = 48
    Top = 346
  end
end
