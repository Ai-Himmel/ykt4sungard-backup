inherited dmGlobeParaDef: TdmGlobeParaDef
  OldCreateOrder = True
  Left = 285
  object cpAddGlobeParaInfo: TWVCommandTypeInfo
    ID = '全局参数设置.增加'
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
        ParamName = '参数标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '参数名称'
      end
      item
        ParamName = '参数值'
      end
      item
        ParamName = '生效时间'
      end
      item
        ParamName = '参数单位'
      end
      item
        ParamName = '备注'
      end>
    Left = 192
    Top = 82
  end
  object cpChangeGlobeParaInfo: TWVCommandTypeInfo
    ID = '全局参数设置.修改'
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
        ParamName = '参数标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '参数名称'
      end
      item
        ParamName = '参数值'
      end
      item
        ParamName = '生效时间'
      end
      item
        ParamName = '参数单位'
      end
      item
        ParamName = '备注'
      end>
    Left = 192
    Top = 128
  end
  object cpDelGlobeParaInfo: TWVCommandTypeInfo
    ID = '全局参数设置.删除'
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
        ParamName = '参数标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '参数名称'
      end
      item
        ParamName = '参数值'
      end
      item
        ParamName = '生效时间'
      end
      item
        ParamName = '参数单位'
      end
      item
        ParamName = '备注'
      end>
    Left = 192
    Top = 176
  end
  object cqQueryGlobeParaByOther: TWVCommandTypeInfo
    ID = '全局参数非关键字查询'
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
        ParamName = '参数名称'
      end
      item
        ParamName = '参数值'
      end
      item
        ParamName = '参数单位'
      end
      item
        ParamName = '生效时间'
      end
      item
        ParamName = '设置时间'
      end>
    Left = 288
    Top = 26
  end
  object cqQueryGlobeParaByKey: TWVCommandTypeInfo
    ID = '全局参数关键字查询'
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
        ParamName = '参数标志'
        ParamDataType = kdtInteger
      end>
    Left = 56
    Top = 106
  end
  object cpAddSetChargePara: TWVCommandTypeInfo
    ID = '收费参数设置.增加'
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
        ParamName = '单位名称'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end>
    Left = 192
    Top = 234
  end
  object cpChargeSetChargePara: TWVCommandTypeInfo
    ID = '收费参数设置.修改'
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
        ParamName = '单位名称'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end>
    Left = 192
    Top = 290
  end
  object cpDelSetChargePara: TWVCommandTypeInfo
    ID = '收费参数设置.删除'
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
        ParamName = '单位名称'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end>
    Left = 192
    Top = 346
  end
  object cqSetChargePara: TWVCommandTypeInfo
    ID = '收费参数查询'
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
        ParamName = '单位名称'
      end>
    Left = 64
    Top = 234
  end
  object cqSetChargeType: TWVCommandTypeInfo
    ID = '收费类别设置'
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
        ParamName = '收费类别'
      end
      item
        ParamName = '是否收搭伙费'
      end
      item
        ParamName = '标志'
      end
      item
        ParamName = '类别标志'
        ParamDataType = kdtInteger
      end>
    Left = 64
    Top = 290
  end
end
