inherited dmUnitInfoDef: TdmUnitInfoDef
  OldCreateOrder = True
  Left = 198
  Top = 139
  object cqQueryUnitInfoByKey: TWVCommandTypeInfo
    ID = '��λ��Ϣ������ѯһ'
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
        ParamName = '��λ����'
      end>
    Left = 48
    Top = 10
  end
  object cqQueryUnitInfoByOther: TWVCommandTypeInfo
    ID = '��λ��Ϣ��ѯһ'
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
        ParamName = '��λ����'
      end
      item
        ParamName = '��λ����'
      end
      item
        ParamName = 'Ӣ������'
      end
      item
        ParamName = '�ϼ���λ'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�������'
      end>
    Left = 48
    Top = 106
  end
  object cpSetUnitInfo: TWVCommandTypeInfo
    ID = '��λ��Ϣ����'
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
        ParamName = '��λ����'
      end
      item
        ParamName = '��λ����'
      end
      item
        ParamName = 'Ӣ������'
      end
      item
        ParamName = '�ϼ���λ'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�������'
      end
      item
        ParamName = '�ɲ��Ŵ���'
      end>
    Left = 48
    Top = 58
  end
  object KCQueryUnitInfoByKey: TKCWVQuery
    ID = '��λ��Ϣ������ѯһ'
    InputBindings = <
      item
        ParamName = '��λ����'
        FieldName = 'scert_no'
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
    RequestType = 842001
    Left = 128
    Top = 26
  end
  object KCQueryUnitInfoByOther: TKCWVQuery
    ID = '��λ��Ϣ��ѯһ'
    InputBindings = <
      item
        ParamName = '��λ����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��λ����'
        FieldName = 'scusttypes'
      end
      item
        ParamName = 'Ӣ������'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '�ϼ���λ'
        FieldName = 'semail2'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
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
    RequestType = 842001
    Left = 128
    Top = 122
  end
  object KCSetUnitInfo: TKCWVProcessor
    ID = '��λ��Ϣ����'
    InputBindings = <
      item
        ParamName = '��λ����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��λ����'
        FieldName = 'scusttypes'
      end
      item
        ParamName = 'Ӣ������'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '�ϼ���λ'
        FieldName = 'semail2'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ɲ��Ŵ���'
        FieldName = 'scert_no2'
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
    RequestType = 842001
    KCDataset = Dataset
    Left = 128
    Top = 74
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 392
    Top = 32
  end
end
