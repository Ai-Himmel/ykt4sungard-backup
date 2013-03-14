inherited dmAreaTableImp: TdmAreaTableImp
  OldCreateOrder = True
  Left = 285
  object cqQueryAreaTableByKey: TKCWVQuery
    ID = '区域信息非主键查询'
    InputBindings = <
      item
        ParamName = '区域号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '父区域号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '区域名称'
        FieldName = 'scard0'
      end
      item
        ParamName = '区域级别'
        FieldName = 'lvol2'
      end
      item
        ParamName = '详细地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 820114
    Left = 88
    Top = 40
  end
  object cpAddAreaTableInfo: TKCWVProcessor
    ID = '区域信息设置.增加'
    InputBindings = <
      item
        ParamName = '父区域号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '区域名称'
        FieldName = 'scard0'
      end
      item
        ParamName = '区域级别'
        FieldName = 'lvol2'
      end
      item
        ParamName = '详细地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '备注'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 820111
    KCDataset = Dataset
    Left = 88
    Top = 120
  end
  object cpChangeAreaTableInfo: TKCWVProcessor
    ID = '区域信息设置.修改'
    InputBindings = <
      item
        ParamName = '区域号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '父区域号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '区域名称'
        FieldName = 'scard0'
      end
      item
        ParamName = '区域级别'
        FieldName = 'lvol2'
      end
      item
        ParamName = '详细地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '备注'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 820112
    KCDataset = Dataset
    Left = 216
    Top = 120
  end
  object cpDelAreaTableInfo: TKCWVProcessor
    ID = '区域信息设置.删除'
    InputBindings = <
      item
        ParamName = '区域号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '父区域号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '区域名称'
        FieldName = 'scard0'
      end
      item
        ParamName = '区域级别'
        FieldName = 'lvol2'
      end
      item
        ParamName = '详细地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '备注'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
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
