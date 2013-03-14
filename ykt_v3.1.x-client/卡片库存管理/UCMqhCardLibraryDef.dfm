inherited dmCardLibrarytDef: TdmCardLibrarytDef
  OldCreateOrder = True
  Left = 285
  object WVQsetCardType: TWVCommandTypeInfo
    ID = '卡类别查询'
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
        ParamName = '交易类型'
      end>
    Left = 24
    Top = 18
  end
  object WVCsetCardType: TWVCommandTypeInfo
    ID = '卡类别设置'
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
        ParamName = '交易类型'
      end
      item
        ParamName = '卡类别'
      end
      item
        ParamName = '卡成本费'
      end
      item
        ParamName = '卡类别名称'
      end
      item
        ParamName = '用途'
      end
      item
        ParamName = '能否重用'
      end
      item
        ParamName = '能否补办'
      end
      item
        ParamName = '能否挂失'
      end
      item
        ParamName = '是否支持多钱包'
      end
      item
        ParamName = '使用状态'
      end
      item
        ParamName = '有效天数'
      end
      item
        ParamName = '可用的收费类别'
      end
      item
        ParamName = '默认收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否匿名卡'
      end
      item
        ParamName = '卡物理类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 24
    Top = 66
  end
  object cqcardInfoQuery: TWVCommandTypeInfo
    ID = '卡片信息查询'
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
        ParamName = '卡类型'
      end
      item
        ParamName = '转入操作员'
      end
      item
        ParamName = '显示卡号'
      end
      item
        ParamName = '领入批次号'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '转交操作员'
      end>
    Left = 24
    Top = 114
  end
  object WVCardIn: TWVCommandTypeInfo
    ID = '卡片领入'
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
        ParamName = '卡类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '转入操作员'
      end
      item
        ParamName = '起始编号'
      end
      item
        ParamName = '截至编号'
      end>
    Left = 24
    Top = 170
  end
  object WVCardOut: TWVCommandTypeInfo
    ID = '卡片上交'
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
        ParamName = '卡类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '转入操作员'
      end
      item
        ParamName = '起始编号'
      end
      item
        ParamName = '截至编号'
      end>
    Left = 24
    Top = 218
  end
  object WVCardTrans: TWVCommandTypeInfo
    ID = '卡片转交'
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
        ParamName = '卡类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '转入操作员'
      end
      item
        ParamName = '起始编号'
      end
      item
        ParamName = '截至编号'
      end
      item
        ParamName = '转入密码'
      end>
    Left = 24
    Top = 266
  end
  object WVCardDestory: TWVCommandTypeInfo
    ID = '卡片作废'
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
        ParamName = '卡类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '起始编号'
      end
      item
        ParamName = '转入操作员'
      end
      item
        ParamName = '作废标志'
      end>
    Left = 24
    Top = 314
  end
  object cqsetMoneyInfo: TWVCommandTypeInfo
    ID = '钱包查询'
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
        ParamName = '交易类型'
      end>
    Left = 96
    Top = 82
  end
  object cpsetMoneyInfo: TWVCommandTypeInfo
    ID = '钱包管理'
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
        ParamName = '交易类型'
      end
      item
        ParamName = '钱包名称'
      end
      item
        ParamName = '钱包号'
      end
      item
        ParamName = '最大充值额'
      end
      item
        ParamName = '是否使用'
      end>
    Left = 96
    Top = 34
  end
end
