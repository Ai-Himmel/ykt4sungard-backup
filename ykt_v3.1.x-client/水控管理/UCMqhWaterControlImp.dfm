inherited WaterControlImp: TWaterControlImp
  OldCreateOrder = True
  Left = 264
  Top = 195
  Height = 541
  Width = 767
  object cqQueryGlobeParaByKey: TKCWVQuery
    ID = 'ȫ�ֲ���������ѯ'
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
      end
      item
        ParamName = '��Կ'
        FieldName = 'scard0'
      end>
    RequestType = 820404
    Left = 32
    Top = 58
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
  object WVQueryGlobeParaByKey: TWVCommandTypeInfo
    ID = 'ȫ�ֲ���������ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '������־'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��Կ'
        ParamType = ptOutput
      end>
    Left = 112
    Top = 82
  end
  object cqwaterCardPatch: TKCWVQuery
    ID = '��дˮ�ؿ���Ϣ'
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
        ParamName = '������'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '���׿���'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '���״���'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '�뿨ֵ'
        FieldName = 'Damt1'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'Scust_limit'
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
    RequestType = 847119
    Left = 32
    Top = 106
  end
  object WVwaterCardPatch: TWVCommandTypeInfo
    ID = '��дˮ�ؿ���Ϣ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '���׿���'
      end
      item
        ParamName = '���״���'
      end
      item
        ParamName = '�뿨ֵ'
      end
      item
        ParamName = '����Ա����'
      end>
    Left = 112
    Top = 130
  end
  object cpReCreCardOK: TKCWVProcessor
    ID = '��дˮ����Ϣȷ��'
    InputBindings = <
      item
        ParamName = '����ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'lserial0'
      end
      item
        ParamName = '������ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'Ǯ����'
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
    RequestType = 847120
    KCDataset = Dataset
    Left = 32
    Top = 152
  end
  object cpPatchCard: TKCWVProcessor
    ID = '��дˮ����Ϣ'
    InputBindings = <
      item
        ParamName = '����ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�뿨ֵ'
        FieldName = 'damt1'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����վ��'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�豸��'
        FieldName = 'lvol7'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol8'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lvol4'
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
        ParamName = '��̨������ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'damt2'
      end
      item
        ParamName = '����'
        FieldName = 'damt3'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '������'
        FieldName = 'sopen_emp'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�շ�����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = 'ͼ��֤��'
        FieldName = 'sname2'
      end
      item
        ParamName = '���֤��'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = 'Scust_no2'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�Ա�'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sname'
      end>
    RequestType = 847119
    KCDataset = Dataset
    Left = 32
    Top = 200
  end
  object cpModifyWaterState: TKCWVProcessor
    ID = '�޸�ˮ��״̬'
    InputBindings = <
      item
        ParamName = '����ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��̨������ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '������'
        FieldName = 'lvol2'
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
    RequestType = 847108
    KCDataset = Dataset
    Left = 32
    Top = 248
  end
  object cqQCIByPatchCard: TKCWVQuery
    ID = '��дˮ����Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����'
        FieldName = 'sname'
      end
      item
        ParamName = '���֤��'
        FieldName = 'sname2'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
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
    RequestType = 847162
    Left = 216
    Top = 10
  end
  object ctQCIByPathCard: TWVCommandTypeInfo
    ID = '��дˮ����Ϣ��ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = 'ѧ����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '���֤��'
      end
      item
        ParamName = '��ʾ����'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end>
    Left = 288
    Top = 26
  end
  object ctPatchCard: TWVCommandTypeInfo
    ID = '��дˮ����Ϣ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��̨������ˮ��'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����ֵ'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '����'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '���׿���'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ʾ����'
        ParamType = ptOutput
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '�շ�����'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ͻ�����'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��������'
        ParamType = ptOutput
      end
      item
        ParamName = '���֤��'
        ParamType = ptOutput
      end
      item
        ParamName = '���Ŵ���'
        ParamType = ptOutput
      end
      item
        ParamName = 'ͼ��֤��'
        ParamType = ptOutput
      end
      item
        ParamName = '����ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�뿨ֵ'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '����Ա��'
      end
      item
        ParamName = '����վ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�豸��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ͻ�����'
        ParamType = ptOutput
      end
      item
        ParamName = 'ѧ����'
        ParamType = ptOutput
      end
      item
        ParamName = '�Ա�'
        ParamType = ptOutput
      end
      item
        ParamName = '���״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
      end>
    Left = 112
    Top = 224
  end
  object ctModifyWaterState: TWVCommandTypeInfo
    ID = '�޸�ˮ��״̬'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '����ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��̨������ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
      end>
    Left = 112
    Top = 264
  end
  object ctReCreCardOK: TWVCommandTypeInfo
    ID = '��дˮ����Ϣȷ��'
    Params = <
      item
        ParamName = '����ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
      end>
    Left = 112
    Top = 176
  end
  object ctCollectionWaterTrade: TWVCommandTypeInfo
    ID = 'ˮ����ˮ�ɼ�'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '�豸��'
      end
      item
        ParamName = '���'
      end
      item
        ParamName = 'ʧ����'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա����'
      end>
    Left = 288
    Top = 74
  end
  object cqCollectionWaterTrade: TKCWVProcessor
    ID = 'ˮ����ˮ�ɼ�'
    InputBindings = <
      item
        ParamName = '�豸��'
        FieldName = 'sdate0'
      end
      item
        ParamName = '���'
        FieldName = 'damt1'
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
        ParamName = '����Ա����'
        FieldName = 'scust_no'
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
        ParamName = 'ʧ����'
        FieldName = 'lvol0'
      end>
    RequestType = 847306
    KCDataset = Dataset
    Left = 216
    Top = 56
  end
end
