inherited dmGlobeParaImp: TdmGlobeParaImp
  OldCreateOrder = True
  Left = 270
  Top = 210
  object cpAddGlobeParaInfo: TKCWVProcessor
    ID = '全局参数设置.增加'
    InputBindings = <
      item
        ParamName = '参数标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '参数名称'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '参数值'
        FieldName = 'scard0'
      end
      item
        ParamName = '生效时间'
        FieldName = 'spager'
      end
      item
        ParamName = '参数单位'
        FieldName = 'scust_no'
      end
      item
        ParamName = '备注'
        FieldName = 'scusttypes'
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
    RequestType = 820401
    KCDataset = Dataset
    Left = 200
    Top = 74
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 312
    Top = 136
  end
  object cpChangeGlobeParaInfo: TKCWVProcessor
    ID = '全局参数设置.修改'
    InputBindings = <
      item
        ParamName = '参数标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '参数名称'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '参数值'
        FieldName = 'scard0'
      end
      item
        ParamName = '生效时间'
        FieldName = 'spager'
      end
      item
        ParamName = '参数单位'
        FieldName = 'scust_no'
      end
      item
        ParamName = '备注'
        FieldName = 'scusttypes'
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
    RequestType = 820402
    KCDataset = Dataset
    Left = 200
    Top = 128
  end
  object cpDelGlobeParaInfo: TKCWVProcessor
    ID = '全局参数设置.删除'
    InputBindings = <
      item
        ParamName = '参数标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '参数名称'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '参数值'
        FieldName = 'scard0'
      end
      item
        ParamName = '生效时间'
        FieldName = 'spager'
      end
      item
        ParamName = '参数单位'
        FieldName = 'scust_no'
      end
      item
        ParamName = '备注'
        FieldName = 'scusttypes'
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
    RequestType = 820403
    KCDataset = Dataset
    Left = 200
    Top = 184
  end
  object cqQueryGlobeParaByOther: TKCWVQuery
    ID = '全局参数非关键字查询'
    InputBindings = <
      item
        ParamName = '参数名称'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '参数值'
        FieldName = 'scard0'
      end
      item
        ParamName = '生效时间'
        FieldName = 'spager'
      end
      item
        ParamName = '设置时间'
        FieldName = 'sphone'
      end
      item
        ParamName = '参数单位'
        FieldName = 'scust_no'
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
    RequestType = 820405
    Left = 200
    Top = 18
  end
  object cqQueryGlobeParaByKey: TKCWVQuery
    ID = '全局参数关键字查询'
    InputBindings = <
      item
        ParamName = '参数标志'
        FieldName = 'lvol0'
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
    RequestType = 820405
    Left = 48
    Top = 122
  end
  object cpAddSetChargePara: TKCWVProcessor
    ID = '收费参数设置.增加'
    InputBindings = <
      item
        ParamName = '单位名称'
        FieldName = 'scust_no'
      end
      item
        ParamName = '客户类别'
        FieldName = 'lvol0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol1'
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
    RequestType = 847190
    KCDataset = Dataset
    Left = 200
    Top = 242
  end
  object cpChargeSetChargePara: TKCWVProcessor
    ID = '收费参数设置.修改'
    InputBindings = <
      item
        ParamName = '单位名称'
        FieldName = 'scust_no'
      end
      item
        ParamName = '客户类别'
        FieldName = 'lvol0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol1'
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
    RequestType = 847191
    KCDataset = Dataset
    Left = 200
    Top = 298
  end
  object cpDelSetChargePara: TKCWVProcessor
    ID = '收费参数设置.删除'
    InputBindings = <
      item
        ParamName = '单位名称'
        FieldName = 'scust_no'
      end
      item
        ParamName = '客户类别'
        FieldName = 'lvol0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol1'
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
    RequestType = 847192
    KCDataset = Dataset
    Left = 200
    Top = 346
  end
  object cqSetChargePara: TKCWVQuery
    ID = '收费参数查询'
    InputBindings = <
      item
        ParamName = '单位名称'
        FieldName = 'scust_no'
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
    RequestType = 847193
    Left = 48
    Top = 290
  end
  object cqSetChargeType: TKCWVQuery
    ID = '收费类别设置'
    InputBindings = <
      item
        ParamName = '收费类别'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = 'sname'
      end
      item
        ParamName = '类别标志'
        FieldName = 'lvol1'
      end
      item
        ParamName = '标志'
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
    RequestType = 847198
    Left = 48
    Top = 346
  end
end
