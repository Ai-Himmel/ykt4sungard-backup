inherited dmSpeInfoDef: TdmSpeInfoDef
  OldCreateOrder = True
  Left = 227
  Top = 113
  object cqQuerySpeInfoByKey: TWVCommandTypeInfo
    ID = '专业信息主键查询'
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
        ParamName = '专业代码'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 24
    Top = 10
  end
  object cqQuerySpeInfoByOther: TWVCommandTypeInfo
    ID = '专业信息非主键查询'
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
        ParamName = '专业代码'
      end
      item
        ParamName = '专业名称'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 24
    Top = 58
  end
  object cpSetSpeInfo: TWVCommandTypeInfo
    ID = '专业信息设置'
    Params = <
      item
        ParamName = '操作类别'
      end
      item
        ParamName = '专业代码'
      end
      item
        ParamName = '专业名称'
      end
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 106
  end
  object KCQuerySpeInfoByKey: TKCWVQuery
    ID = '专业信息主键查询'
    InputBindings = <
      item
        ParamName = '专业代码'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
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
    ID = '专业信息非主键查询'
    InputBindings = <
      item
        ParamName = '专业代码'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '专业名称'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
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
    RequestType = 842501
    Left = 96
    Top = 82
  end
  object KCSetSpeInfo: TKCWVProcessor
    ID = '专业信息设置'
    InputBindings = <
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '专业代码'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '专业名称'
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
    RequestType = 842501
    KCDataset = Dataset
    Left = 96
    Top = 130
  end
end
