inherited dmCardLibrarytImp: TdmCardLibrarytImp
  OldCreateOrder = True
  Left = 245
  Top = 190
  Width = 590
  object cqsetCardType: TKCWVQuery
    ID = '卡类别查询'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
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
    RequestType = 846101
    Left = 40
    Top = 10
  end
  object cpsetCardType: TKCWVProcessor
    ID = '卡类别设置'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '卡类别'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡成本费'
        FieldName = 'lvol1'
      end
      item
        ParamName = '卡类别名称'
        FieldName = 'sname'
      end
      item
        ParamName = '用途'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '能否重用'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '能否补办'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '能否挂失'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '是否支持多钱包'
        FieldName = 'sstatus4'
      end
      item
        ParamName = '使用状态'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '有效天数'
        FieldName = 'lvol2'
      end
      item
        ParamName = '可用的收费类别'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '默认收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '是否匿名卡'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '卡物理类别'
        FieldName = 'lvol3'
        DefaultValue = 0
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
    RequestType = 846101
    KCDataset = Dataset
    Left = 40
    Top = 58
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 296
    Top = 8
  end
  object cqcardInfoQuery: TKCWVQuery
    ID = '卡片信息查询'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol0'
      end
      item
        ParamName = '转入操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '领入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '状态'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '转交操作员'
        FieldName = 'semp_no2'
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
    RequestType = 846106
    Left = 40
    Top = 106
  end
  object cqCardIn: TKCWVProcessor
    ID = '卡片领入'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol0'
      end
      item
        ParamName = '起始编号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '截至编号'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '转入操作员'
        FieldName = 'scust_limit2'
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
    RequestType = 846102
    KCDataset = Dataset
    Left = 40
    Top = 154
  end
  object cqCardOut: TKCWVProcessor
    ID = '卡片上交'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol0'
      end
      item
        ParamName = '起始编号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '截至编号'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '转入操作员'
        FieldName = 'scust_limit2'
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
    RequestType = 846103
    KCDataset = Dataset
    Left = 40
    Top = 202
  end
  object cqCardTrans: TKCWVProcessor
    ID = '卡片转交'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol0'
      end
      item
        ParamName = '起始编号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '截至编号'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '转入操作员'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '转入密码'
        FieldName = 'scust_limit'
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
    RequestType = 846104
    KCDataset = Dataset
    Left = 40
    Top = 250
  end
  object cqCardDestory: TKCWVProcessor
    ID = '卡片作废'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol0'
      end
      item
        ParamName = '起始编号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '转入操作员'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '作废标志'
        FieldName = 'sstatus3'
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
    RequestType = 846105
    KCDataset = Dataset
    Left = 40
    Top = 298
  end
  object cqsetMoneyInfo: TKCWVQuery
    ID = '钱包查询'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
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
    RequestType = 846201
    Left = 160
    Top = 58
  end
  object cpsetMoneyInfo: TKCWVProcessor
    ID = '钱包管理'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '钱包名称'
        FieldName = 'sname'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '最大充值额'
        FieldName = 'lvol1'
      end
      item
        ParamName = '是否使用'
        FieldName = 'sstatus1'
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
    RequestType = 846201
    KCDataset = Dataset
    Left = 160
    Top = 10
  end
end
