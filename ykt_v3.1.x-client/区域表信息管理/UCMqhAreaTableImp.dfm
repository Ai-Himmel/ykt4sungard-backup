inherited dmAreaTableImp: TdmAreaTableImp
  OldCreateOrder = True
  Left = 285
  object cqQueryAreaTableByKey: TKCWVQuery
    ID = '������Ϣ��������ѯ'
    InputBindings = <
      item
        ParamName = '�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'scard0'
      end
      item
        ParamName = '���򼶱�'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ϸ��ַ'
        FieldName = 'scusttypes'
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
    RequestType = 820114
    Left = 88
    Top = 40
  end
  object cpAddAreaTableInfo: TKCWVProcessor
    ID = '������Ϣ����.����'
    InputBindings = <
      item
        ParamName = '�������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'scard0'
      end
      item
        ParamName = '���򼶱�'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ϸ��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��ע'
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
    RequestType = 820111
    KCDataset = Dataset
    Left = 88
    Top = 120
  end
  object cpChangeAreaTableInfo: TKCWVProcessor
    ID = '������Ϣ����.�޸�'
    InputBindings = <
      item
        ParamName = '�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'scard0'
      end
      item
        ParamName = '���򼶱�'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ϸ��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��ע'
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
    RequestType = 820112
    KCDataset = Dataset
    Left = 216
    Top = 120
  end
  object cpDelAreaTableInfo: TKCWVProcessor
    ID = '������Ϣ����.ɾ��'
    InputBindings = <
      item
        ParamName = '�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'scard0'
      end
      item
        ParamName = '���򼶱�'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ϸ��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��ע'
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
    RequestType = 820113
    KCDataset = Dataset
    Left = 344
    Top = 120
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 336
    Top = 40
  end
end
