inherited dmReportImp: TdmReportImp
  OldCreateOrder = True
  Left = 452
  Top = 190
  Height = 546
  Width = 734
  object cqUnsuitReport: TKCWVQuery
    ID = '个人对帐不平清单表'
    InputBindings = <
      item
        ParamName = '开始日期'
        FieldName = 'sorder1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sorder2'
      end
      item
        ParamName = '操作员代码'
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
    RequestType = 900130
    Left = 16
    Top = 10
  end
  object cqTransfer: TKCWVQuery
    ID = '转帐对帐表'
    InputBindings = <
      item
        ParamName = '开始日期'
        FieldName = 'sorder1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sorder2'
      end
      item
        ParamName = '操作员代码'
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
    RequestType = 900210
    Left = 19
    Top = 59
  end
  object cqEquip: TKCWVQuery
    ID = '设备充值表'
    InputBindings = <
      item
        ParamName = '开始日期'
        FieldName = 'sorder1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sorder2'
      end
      item
        ParamName = '操作员代码'
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
    RequestType = 900240
    Left = 14
    Top = 149
  end
  object cqticketMoneyReport: TKCWVQuery
    ID = '支票经费本充值报表'
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
        ParamName = '开始日期'
        FieldName = 'sorder1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sorder2'
      end
      item
        ParamName = '交易类型'
        FieldName = 'LVOL3'
      end
      item
        ParamName = '充值类型'
        FieldName = 'LVOL2'
      end
      item
        ParamName = '票据号码'
        FieldName = 'SALL_NAME'
      end
      item
        ParamName = '操作员组号'
        FieldName = 'sserial0'
      end
      item
        ParamName = '操作员号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'LVOL1'
      end
      item
        ParamName = '类型'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '流水号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sorder0'
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
    RequestType = 900320
    Left = 80
    Top = 34
  end
  object cqSetOperator: TKCWVQuery
    ID = '操作员查询一'
    InputBindings = <>
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
    RequestType = 820302
    Left = 80
    Top = 82
  end
  object cqOperGroupManager: TKCWVQuery
    ID = '操作员组查询一'
    InputBindings = <
      item
        ParamName = '组编号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '组名称'
        FieldName = 'sbankname'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '操作员号'
        FieldName = 'scust_limit'
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
    RequestType = 820355
    Left = 80
    Top = 130
  end
  object KCTradeSubject: TKCWVQuery
    ID = '交易科目情况表'
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
        ParamName = '开始日期'
        FieldName = 'sorder1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sorder2'
      end
      item
        ParamName = '操作员代码'
        FieldName = 'scust_no'
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
    RequestType = 900122
    Left = 160
    Top = 202
  end
  object KCTotSubject: TKCWVQuery
    ID = '科目总账表'
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
        ParamName = '会计科目'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
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
    RequestType = 846705
    Left = 160
    Top = 154
  end
  object KCWSubBalanceRep: TKCWVQuery
    ID = '科目余额表'
    InputBindings = <
      item
        ParamName = '科目号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
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
    RequestType = 846701
    Left = 244
    Top = 32
  end
  object KCWSystemRunStat: TKCWVQuery
    ID = '系统运行情况'
    InputBindings = <
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
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
    RequestType = 846702
    Left = 244
    Top = 80
  end
  object KCWBusiReport: TKCWVQuery
    ID = '商户结算表'
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
        ParamName = '商户帐号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '显示级别'
        FieldName = 'lsafe_level'
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
    RequestType = 846706
    Timeout = 5000
    Left = 248
    Top = 226
  end
  object cqCardUsedInfo_R: TKCWVQuery
    ID = '卡片使用情况汇总_R'
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
        ParamName = '网点号'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
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
    RequestType = 846704
    Timeout = 5000
    Left = 248
    Top = 130
  end
  object kcTicketCashRpt_R: TKCWVQuery
    ID = '票据现金报表_R'
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
        ParamName = '网点号'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '科目类型'
        FieldName = 'lvol1'
      end
      item
        ParamName = '交易类型'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
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
    RequestType = 846703
    Timeout = 5000
    Left = 248
    Top = 178
  end
  object KCWBusiReportPOS: TKCWVQuery
    ID = '商户结算表POS'
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
        ParamName = '商户帐号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '级别'
        FieldName = 'lsafe_level'
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
    RequestType = 846707
    Timeout = 5000
    Left = 248
    Top = 274
  end
  object KCWBusiReportFC: TKCWVQuery
    ID = '商户结算表FC'
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
        ParamName = '商户帐号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '级别'
        FieldName = 'lsafe_level'
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
    RequestType = 846708
    Timeout = 5000
    Left = 248
    Top = 322
  end
  object KCWBusiReportDay: TKCWVQuery
    ID = '商户当日结算表'
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
        ParamName = '商户帐号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '级别'
        FieldName = 'lsafe_level'
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
    RequestType = 846110
    Timeout = 5000
    Left = 320
    Top = 10
  end
  object KCWBusiPayIn: TKCWVQuery
    ID = '商户解款余额查询'
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
        ParamName = '商户号'
        FieldName = 'lvol3'
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
    RequestType = 846720
    Timeout = 5000
    Left = 320
    Top = 58
  end
  object cqfillBusiPayIn: TKCWVProcessor
    ID = '商户解款'
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
        ParamName = '商户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '解款金额'
        FieldName = 'damt0'
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
    RequestType = 846721
    KCDataset = Dataset
    Left = 320
    Top = 106
  end
  object KCWPayInQuery: TKCWVQuery
    ID = '商户解款查询'
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
        ParamName = '商户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
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
    RequestType = 846722
    Timeout = 5000
    Left = 320
    Top = 154
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 440
    Top = 16
  end
  object kcBusiGatherRep: TKCWVQuery
    ID = '商户汇总结算表'
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
        ParamName = '商户帐号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '级别'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '商户类型'
        FieldName = 'lvol1'
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
    RequestType = 846709
    Timeout = 5000
    Left = 320
    Top = 202
  end
  object kcSubject: TKCWVQuery
    ID = '科目表查询'
    InputBindings = <
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
    RequestType = 846112
    Left = 19
    Top = 195
  end
  object conFB: TZConnection
    Protocol = 'firebird-2.0'
    User = 'sysdba'
    Password = 'masterkey'
    AutoCommit = False
    Left = 440
    Top = 65
  end
  object cqCardUsedInfo: TKCWVQuery
    ID = '卡片使用情况汇总'
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
        ParamName = '网点号'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
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
    RequestType = 846108
    Timeout = 5000
    Left = 320
    Top = 250
  end
  object kcTicketCashReport: TKCWVQuery
    ID = '票据现金报表'
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
        ParamName = '网点号'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '餐次'
        FieldName = 'lbank_acc_type'
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
    RequestType = 846109
    Timeout = 5000
    Left = 320
    Top = 298
  end
  object kcBusiStatFC: TKCWVQuery
    ID = '商户汇总结算表FC'
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
        ParamName = '商户帐号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '级别'
        FieldName = 'lsafe_level'
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
    RequestType = 846710
    Timeout = 5000
    Left = 248
    Top = 370
  end
  object kcBusiRunStatRpt: TKCWVQuery
    ID = '商户营业情况表'
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
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '级别'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '商户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '商户类型'
        FieldName = 'lvol1'
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
    RequestType = 846714
    Timeout = 5000
    Left = 16
    Top = 242
  end
  object kcQBusiByKey: TKCWVQuery
    ID = '商户信息主键Q'
    InputBindings = <
      item
        ParamName = '商户标识'
        FieldName = 'lvol3'
      end
      item
        ParamName = '操作标志'
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
    RequestType = 843335
    Left = 16
    Top = 106
  end
  object kcOperRpt: TKCWVQuery
    ID = '操作员业务报表'
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
        ParamName = '网点号'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
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
    RequestType = 846715
    Timeout = 5000
    Left = 160
    Top = 250
  end
  object kcBusiFeeRpt: TKCWVQuery
    ID = '商户搭伙费报表'
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
        ParamName = '商户帐号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '显示级别'
        FieldName = 'lsafe_level'
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
    RequestType = 846712
    Timeout = 5000
    Left = 168
    Top = 298
  end
  object kcCardDestoryRpt: TKCWVQuery
    ID = '销户现金报表'
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
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
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
    RequestType = 846713
    Timeout = 5000
    Left = 160
    Top = 346
  end
  object kcSysAccount: TKCWVQuery
    ID = '系统对账'
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
        ParamName = '对账日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '对账类型'
        FieldName = 'lsafe_level2'
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
    RequestType = 950997
    Timeout = 5000
    Left = 16
    Top = 290
  end
  object kcSysAccQuery: TKCWVQuery
    ID = '系统对账查询'
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
        ParamName = '开始日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '对账类型'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '查询类别'
        FieldName = 'lsafe_level'
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
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end
      item
        ParamName = '银行次数'
        FieldName = 'lvol2'
      end
      item
        ParamName = '一卡通次数'
        FieldName = 'lvol3'
      end>
    RequestType = 240023
    Timeout = 5000
    Left = 16
    Top = 338
  end
  object kcOperCashTot: TKCWVQuery
    ID = '操作员现金汇总报表'
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
        ParamName = '网点号'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '科目类型'
        FieldName = 'lvol1'
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
    RequestType = 846716
    Timeout = 5000
    Left = 80
    Top = 178
  end
  object conSLite: TZConnection
    Protocol = 'sqlite-3'
    AutoCommit = False
    Left = 440
    Top = 113
  end
  object KCDealBankAccQ: TKCWVQuery
    ID = '银行对账查询'
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
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '银行编号'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '对账状态'
        FieldName = 'sorder0'
      end
      item
        ParamName = '处理状态'
        FieldName = 'sorder1'
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
    RequestType = 240031
    Timeout = 0
    Left = 384
    Top = 34
  end
  object KCDealBankAcc: TKCWVQuery
    ID = '银行对账处理'
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
        ParamName = '账单日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '银行编号'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '处理状态'
        FieldName = 'sorder1'
      end
      item
        ParamName = '备注'
        FieldName = 'vsvarstr0'
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
    RequestType = 240032
    Timeout = 0
    Left = 384
    Top = 82
  end
  object KCDealBankAccDtlQ: TKCWVQuery
    ID = '银行对账明细查询'
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
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '银行编号'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '对账状态'
        FieldName = 'sorder0'
      end
      item
        ParamName = '处理状态'
        FieldName = 'sorder1'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
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
    RequestType = 240033
    Timeout = 0
    Left = 384
    Top = 130
  end
  object KCDealBankAccDtl: TKCWVQuery
    ID = '银行对账明细处理'
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
        ParamName = '账单日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '银行编号'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '处理状态'
        FieldName = 'sorder1'
      end
      item
        ParamName = '备注'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '记录号'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
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
    RequestType = 240034
    Timeout = 0
    Left = 384
    Top = 178
  end
  object KCBalanceRpt: TKCWVQuery
    ID = '收支平衡表'
    InputBindings = <
      item
        ParamName = '开始日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate1'
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
    RequestType = 846727
    Left = 388
    Top = 224
  end
  object KCBusiPayIn_nju: TKCWVQuery
    ID = '商户解款查询_nju'
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
        ParamName = '商户帐号'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '月份'
        FieldName = 'lvol4'
        DefaultValue = 0
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
    RequestType = 846729
    Timeout = 5000
    Left = 384
    Top = 274
  end
  object kcBusiPay_nju: TKCWVProcessor
    ID = '商户解款_nju'
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
        ParamName = '商户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '解款金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '月份'
        FieldName = 'lvol4'
      end
      item
        ParamName = '摘要'
        FieldName = 'snote'
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
    RequestType = 846727
    KCDataset = Dataset
    Left = 384
    Top = 322
  end
  object KCBusiPayInQ_nju: TKCWVQuery
    ID = '商户解款信息查询_nju'
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
        ParamName = '商户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '解款年份'
        FieldName = 'lvol4'
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
    RequestType = 846728
    Timeout = 5000
    Left = 384
    Top = 370
  end
end
