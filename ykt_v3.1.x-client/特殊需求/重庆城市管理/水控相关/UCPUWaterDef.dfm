inherited cmCPUWaterDef: TcmCPUWaterDef
  OldCreateOrder = True
  Left = 285
  object ctRollBack: TWVCommandTypeInfo
    ID = '失败信息_cqcsgl'
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
    ID = '水控转账_cqcsgl'
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
      end>
    Left = 16
    Top = 58
  end
  object cqTradeCode: TWVCommandTypeInfo
    ID = '交易参考号_cqcsgl'
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
end
