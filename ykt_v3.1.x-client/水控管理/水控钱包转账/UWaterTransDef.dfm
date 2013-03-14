inherited cmWaterTransDef: TcmWaterTransDef
  OldCreateOrder = True
  object cqwaterTrans: TWVCommandTypeInfo
    ID = '水控转账11'
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
        ParamName = '交易卡号'
      end
      item
        ParamName = '充值金额'
        ParamType = ptInputOutput
      end
      item
        ParamName = '操作员代码'
      end
      item
        ParamName = '大钱包金额'
        ParamType = ptInputOutput
      end
      item
        ParamName = '大钱包次数'
        ParamType = ptInputOutput
      end
      item
        ParamName = '小钱包次数'
        ParamType = ptInputOutput
      end
      item
        ParamName = '小钱包金额'
        ParamType = ptInputOutput
      end
      item
        ParamName = '购水后台流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '后台流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end>
    Left = 16
    Top = 10
  end
  object ctRollBack: TWVCommandTypeInfo
    ID = '失败信息'
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
        ParamName = '充值流水'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '消费流水'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '失败标志'
        ParamDataType = kdtInteger
      end>
    Left = 16
    Top = 56
  end
end
