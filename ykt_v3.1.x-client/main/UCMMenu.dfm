object dmMenu: TdmMenu
  OldCreateOrder = True
  OnCreate = DataModuleCreate
  OnDestroy = DataModuleDestroy
  Left = 567
  Top = 65526
  Height = 479
  Width = 741
  object ctQueryMenu: TWVCommandTypeInfo
    ID = '��ѯ�˵�'
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
        ParamName = '�˵����'
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end>
    Left = 48
    Top = 56
  end
  object cpQueryMenu: TKCWVQuery
    ID = '��ѯ�˵�'
    InputBindings = <
      item
        ParamName = '�˵����'
        FieldName = 'sname'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
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
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 300123
    Left = 176
    Top = 64
  end
  object ctQueryMenuStructure: TWVCommandTypeInfo
    ID = '��ѯ�˵��ṹ'
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
        ParamName = '�˵����'
      end>
    Left = 64
    Top = 136
  end
  object cpQueryMenuStructure: TKCWVQuery
    ID = '��ѯ�˵��ṹ'
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
        ParamName = '�˵����'
        FieldName = 'sname'
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
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 300125
    Left = 176
    Top = 128
  end
  object cpGetFunction: TKCWVQuery
    ID = '��ѯ������'
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
        ParamName = '���ܱ��'
        FieldName = 'lcert_code'
        DefaultValue = 0
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
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 300128
    Left = 176
    Top = 200
  end
  object ctGetFunction: TWVCommandTypeInfo
    ID = '��ѯ������'
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
        ParamName = '���ܱ��'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 64
    Top = 200
  end
  object ctGetQhFunction: TWVCommandTypeInfo
    ID = '��ѯ�ڻ�������'
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
        ParamName = '��ѯ��־'
        DefaultValue = 0
      end>
    Left = 64
    Top = 264
  end
  object cpGetQhFunction: TKCWVQuery
    ID = '��ѯ�ڻ�������'
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
        ParamName = '��ѯ��־'
        FieldName = 'sstatus0'
        DefaultValue = 1
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
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 820521
    Left = 184
    Top = 264
  end
end
