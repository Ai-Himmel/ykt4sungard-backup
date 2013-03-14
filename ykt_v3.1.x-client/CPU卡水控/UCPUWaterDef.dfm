inherited cmCPUWaterDef: TcmCPUWaterDef
  OldCreateOrder = True
  Left = 486
  Top = 165
  object ctRollBack: TWVCommandTypeInfo
    ID = '失败信息_water'
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
        ParamName = '交易参考号'
      end
      item
        ParamName = '随机数'
      end>
    Left = 16
    Top = 104
  end
  object cqwaterTrans: TWVCommandTypeInfo
    ID = '水控转账_water'
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
        ParamName = '终端号'
      end
      item
        ParamName = '交易参考号'
      end
      item
        ParamName = '随机数'
      end
      item
        ParamName = '卡物理编号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '卡余额'
      end
      item
        ParamName = '交易次数'
      end
      item
        ParamName = '小钱包余额'
      end
      item
        ParamName = '转账金额'
      end
      item
        ParamName = '支付代码'
      end
      item
        ParamName = '终端流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '记账日期'
        ParamType = ptOutput
      end
      item
        ParamName = '记账时间'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
      end
      item
        ParamName = '扣款金额'
        ParamType = ptOutput
      end
      item
        ParamName = '补写金额'
        ParamType = ptOutput
      end
      item
        ParamName = '小钱包余额'
        ParamType = ptOutput
      end
      item
        ParamName = '钱包号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 16
    Top = 58
  end
  object cqTradeCode: TWVCommandTypeInfo
    ID = '交易参考号_water'
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
        ParamName = '终端号'
      end
      item
        ParamName = '时间戳'
      end
      item
        ParamName = '交易参考号'
        ParamType = ptOutput
      end
      item
        ParamName = '随机数'
        ParamType = ptOutput
      end>
    Left = 16
    Top = 10
  end
  object WVQueryGlobeParaByKey: TWVCommandTypeInfo
    ID = '全局参数主键查询_water'
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
      end
      item
        ParamName = '密钥'
        ParamType = ptOutput
      end>
    Left = 16
    Top = 154
  end
  object cqSaveFeeType: TWVCommandTypeInfo
    ID = '保存费率设置卡'
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
        ParamName = '标志'
      end
      item
        ParamName = '费率编号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率名称'
      end
      item
        ParamName = '钱包号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '计费单位'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率类型'
      end
      item
        ParamName = '费率个数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '数量'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率时间1'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率金额1'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率分钟1'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率时间2'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率金额2'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率分钟2'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率时间3'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率金额3'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '费率分钟3'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 16
    Top = 202
  end
  object cqFeeTypeQ: TWVCommandTypeInfo
    ID = '费率设置卡查询'
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
        ParamName = '标志'
      end
      item
        ParamName = '费率名称'
      end>
    Left = 16
    Top = 250
  end
  object cqFeeTypeDel: TWVCommandTypeInfo
    ID = '费率设置卡删除'
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
        ParamName = '标志'
      end
      item
        ParamName = '费率名称'
      end>
    Left = 16
    Top = 298
  end
  object cqSmlTradeSerial: TWVCommandTypeInfo
    ID = '小钱包流水查询'
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
        ParamName = '开始日期'
      end
      item
        ParamName = '截止日期'
      end
      item
        ParamName = '终端编号'
      end
      item
        ParamName = '终端流水号'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '凭证号码'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '学/工号'
      end
      item
        ParamName = '显示卡号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '钱包号'
      end
      item
        ParamName = '流水状态'
      end
      item
        ParamName = '查询类型'
      end
      item
        ParamName = '交易开始日期'
      end
      item
        ParamName = '交易结束日期'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '联机状态'
      end
      item
        ParamName = '结束时间'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '交易标志'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '外部类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 80
    Top = 26
  end
  object WVsmlSerialRcv: TWVCommandTypeInfo
    ID = '小钱包流水冲正'
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
        ParamName = '终端编号'
      end
      item
        ParamName = '终端流水号'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = '交易金额'
      end
      item
        ParamName = '小钱包余额'
        ParamType = ptOutput
      end>
    Left = 80
    Top = 74
  end
end
