inherited cmCPUWaterImp: TcmCPUWaterImp
  OldCreateOrder = True
  Left = 285
  object cpRollBack: TKCWVProcessor
    ID = '失败信息_cqcsgl'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易参考号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '随机数'
        FieldName = 'saddr'
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
    RequestType = 847302
    KCDataset = Dataset
    Left = 32
    Top = 112
  end
  object cpWaterTrans: TKCWVProcessor
    ID = '水控转账_cqcsgl'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '终端号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '交易参考号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '随机数'
        FieldName = 'saddr'
      end
      item
        ParamName = '卡物理编号'
        FieldName = 'sstation1'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol7'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '小钱包余额'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '转账金额'
        FieldName = 'lvol5'
      end
      item
        ParamName = '支付代码'
        FieldName = 'lcert_code'
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
        ParamName = '终端流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '记账日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '记账时间'
        FieldName = 'stime3'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol8'
      end
      item
        ParamName = '扣款金额'
        FieldName = 'lvol5'
      end
      item
        ParamName = '补写金额'
        FieldName = 'lvol9'
      end
      item
        ParamName = '小钱包余额'
        FieldName = 'lsafe_level'
      end>
    RequestType = 850010
    KCDataset = Dataset
    Left = 32
    Top = 64
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
  object cpTradeCode: TKCWVProcessor
    ID = '交易参考号_cqcsgl'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '终端号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '时间戳'
        FieldName = 'scust_auth'
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
        ParamName = '交易参考号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '随机数'
        FieldName = 'saddr'
      end>
    RequestType = 850000
    KCDataset = Dataset
    Left = 32
    Top = 8
  end
end
