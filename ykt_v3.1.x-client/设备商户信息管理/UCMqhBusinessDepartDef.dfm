inherited dmBusinessDepartDef: TdmBusinessDepartDef
  OldCreateOrder = True
  object cqQueryBusinessDepartByOther: TWVCommandTypeInfo
    ID = '设备商户信息非主键查询'
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
        ParamName = '前端机标识'
      end
      item
        ParamName = '商户标识'
      end
      item
        ParamName = '使用开始日期'
      end
      item
        ParamName = '使用开始时间'
      end
      item
        ParamName = '使用结束时间'
      end
      item
        ParamName = '使用结束日期'
      end
      item
        ParamName = '备注'
      end>
    Left = 240
    Top = 42
  end
  object cqQueryBusinessDepartByKey: TWVCommandTypeInfo
    ID = '设备商户信息主键查询'
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
        ParamName = '设备商户标识'
      end>
    Left = 88
    Top = 42
  end
  object cqSetBusinessDepartInfo: TWVCommandTypeInfo
    ID = '设备商户信息查询'
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
        ParamName = '设备商户标识'
      end>
    Left = 240
    Top = 154
  end
  object cpSetBusinessDepartInfo: TWVCommandTypeInfo
    ID = '设备商户信息设置'
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
        ParamName = '编号'
      end
      item
        ParamName = '前端机标识'
      end
      item
        ParamName = '商户标识'
      end
      item
        ParamName = '使用开始日期'
      end
      item
        ParamName = '使用开始时间'
      end
      item
        ParamName = '使用结束时间'
      end
      item
        ParamName = '使用结束日期'
      end
      item
        ParamName = '备注'
      end>
    Left = 80
    Top = 154
  end
end
