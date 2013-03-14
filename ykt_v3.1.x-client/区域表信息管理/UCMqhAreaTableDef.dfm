inherited dmAreaTableDef: TdmAreaTableDef
  OldCreateOrder = True
  Left = 263
  Top = 159
  Height = 479
  Width = 741
  object cqQueryAreaTable: TWVCommandTypeInfo
    ID = '区域信息非主键查询'
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
        ParamName = '区域号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '父区域号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '区域名称'
      end
      item
        ParamName = '区域级别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '详细地址'
      end>
    Left = 88
    Top = 26
  end
  object cpAddAreaTableInfo: TWVCommandTypeInfo
    ID = '区域信息设置.增加'
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
        ParamName = '父区域号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '区域名称'
      end
      item
        ParamName = '区域级别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '详细地址'
      end
      item
        ParamName = '备注'
      end>
    Left = 88
    Top = 106
  end
  object cpChangeAreaTableInfo: TWVCommandTypeInfo
    ID = '区域信息设置.修改'
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
        ParamName = '区域号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '父区域号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '区域名称'
      end
      item
        ParamName = '区域级别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '详细地址'
      end
      item
        ParamName = '备注'
      end>
    Left = 224
    Top = 122
  end
  object cpDelAreaTableInfo: TWVCommandTypeInfo
    ID = '区域信息设置.删除'
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
        ParamName = '区域号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '父区域号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '区域名称'
      end
      item
        ParamName = '区域级别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '详细地址'
      end
      item
        ParamName = '备注'
      end>
    Left = 352
    Top = 114
  end
end
