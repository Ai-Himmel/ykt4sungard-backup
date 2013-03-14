object dmMenu: TdmMenu
  OldCreateOrder = True
  OnCreate = DataModuleCreate
  OnDestroy = DataModuleDestroy
  Left = 567
  Top = 65526
  Height = 479
  Width = 741
  object ctQueryMenu: TWVCommandTypeInfo
    ID = '查询菜单'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end
      item
        ParamName = '菜单编号'
      end
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end>
    Left = 48
    Top = 56
  end
  object cpQueryMenu: TKCWVQuery
    ID = '查询菜单'
    InputBindings = <
      item
        ParamName = '菜单编号'
        FieldName = 'sname'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 300123
    Left = 176
    Top = 64
  end
  object ctQueryMenuStructure: TWVCommandTypeInfo
    ID = '查询菜单结构'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '菜单编号'
      end>
    Left = 64
    Top = 136
  end
  object cpQueryMenuStructure: TKCWVQuery
    ID = '查询菜单结构'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '菜单编号'
        FieldName = 'sname'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 300125
    Left = 176
    Top = 128
  end
  object cpGetFunction: TKCWVQuery
    ID = '查询功能项'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '功能编号'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 300128
    Left = 176
    Top = 200
  end
  object ctGetFunction: TWVCommandTypeInfo
    ID = '查询功能项'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '功能编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 64
    Top = 200
  end
  object ctGetQhFunction: TWVCommandTypeInfo
    ID = '查询期货功能项'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '查询标志'
        DefaultValue = 0
      end>
    Left = 64
    Top = 264
  end
  object cpGetQhFunction: TKCWVQuery
    ID = '查询期货功能项'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '查询标志'
        FieldName = 'sstatus0'
        DefaultValue = 1
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 820521
    Left = 184
    Top = 264
  end
end
