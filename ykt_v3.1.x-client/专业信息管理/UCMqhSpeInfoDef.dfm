inherited dmSpeInfoDef: TdmSpeInfoDef
  OldCreateOrder = True
  Left = 227
  Top = 113
  object cqQuerySpeInfoByKey: TWVCommandTypeInfo
    ID = 'רҵ��Ϣ������ѯ'
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
        ParamName = 'רҵ����'
      end
      item
        ParamName = '�������'
      end>
    Left = 24
    Top = 10
  end
  object cqQuerySpeInfoByOther: TWVCommandTypeInfo
    ID = 'רҵ��Ϣ��������ѯ'
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
        ParamName = 'רҵ����'
      end
      item
        ParamName = 'רҵ����'
      end
      item
        ParamName = '�������'
      end>
    Left = 24
    Top = 58
  end
  object cpSetSpeInfo: TWVCommandTypeInfo
    ID = 'רҵ��Ϣ����'
    Params = <
      item
        ParamName = '�������'
      end
      item
        ParamName = 'רҵ����'
      end
      item
        ParamName = 'רҵ����'
      end
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 106
  end
  object KCQuerySpeInfoByKey: TKCWVQuery
    ID = 'רҵ��Ϣ������ѯ'
    InputBindings = <
      item
        ParamName = 'רҵ����'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '�������'
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
    RequestType = 842501
    Left = 96
    Top = 26
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 384
    Top = 272
  end
  object KCQuerySpeInfoByOther: TKCWVQuery
    ID = 'רҵ��Ϣ��������ѯ'
    InputBindings = <
      item
        ParamName = 'רҵ����'
        FieldName = 'scert_no2'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '�������'
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
    RequestType = 842501
    Left = 96
    Top = 82
  end
  object KCSetSpeInfo: TKCWVProcessor
    ID = 'רҵ��Ϣ����'
    InputBindings = <
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'scert_no2'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'ssectypes'
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
    RequestType = 842501
    KCDataset = Dataset
    Left = 96
    Top = 130
  end
end
