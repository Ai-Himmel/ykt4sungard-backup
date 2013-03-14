inherited cmWaterTransImp: TcmWaterTransImp
  OldCreateOrder = True
  Left = 285
  object cpRollBack: TKCWVProcessor
    ID = '失败信息'
    InputBindings = <
      item
        ParamName = '消费流水'
        FieldName = 'lvol1'
      end
      item
        ParamName = '充值流水'
        FieldName = 'lvol2'
      end
      item
        ParamName = '失败标志'
        FieldName = 'lvol3'
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
    RequestType = 847302
    KCDataset = Dataset
    Left = 32
    Top = 56
  end
  object cpWaterTrans: TKCWVProcessor
    ID = '水控转账11'
    InputBindings = <
      item
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '充值金额'
        FieldName = 'damt4'
      end
      item
        ParamName = '操作员代码'
        FieldName = 'scust_no'
      end
      item
        ParamName = '大钱包金额'
        FieldName = 'damt1'
      end
      item
        ParamName = '大钱包次数'
        FieldName = 'lvol4'
      end
      item
        ParamName = '小钱包次数'
        FieldName = 'lvol5'
      end
      item
        ParamName = '小钱包金额'
        FieldName = 'Damt3'
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
      end
      item
        ParamName = '后台流水号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '购水后台流水号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '充值金额'
        FieldName = 'damt1'
      end
      item
        ParamName = '大钱包次数'
        FieldName = 'Lvol9'
      end
      item
        ParamName = '大钱包金额'
        FieldName = 'Damt0'
      end
      item
        ParamName = '小钱包次数'
        FieldName = 'lvol5'
      end
      item
        ParamName = '小钱包金额'
        FieldName = 'Damt2'
      end>
    RequestType = 847301
    KCDataset = Dataset
    Left = 32
    Top = 8
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
end
