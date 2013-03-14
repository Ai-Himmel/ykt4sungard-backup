inherited dmReportDef: TdmReportDef
  OldCreateOrder = True
  Left = 372
  Top = 136
  Height = 527
  Width = 763
  object cqUnsuitReport: TWVCommandTypeInfo
    ID = '个人对帐不平清单表'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '操作员代码'
      end>
    Left = 16
    Top = 10
  end
  object cqTransfer: TWVCommandTypeInfo
    ID = '转帐对帐表'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '操作员代码'
      end>
    Left = 17
    Top = 58
  end
  object cqUnEqip: TWVCommandTypeInfo
    ID = '设备充值表'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '操作员代码'
      end>
    Left = 15
    Top = 148
  end
  object cqticketMoneyReport: TWVCommandTypeInfo
    ID = '支票经费本充值报表'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '充值类型'
      end
      item
        ParamName = '票据号码'
      end
      item
        ParamName = '操作员组号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '交易卡号'
      end
      item
        ParamName = '类型'
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '流水号'
        ParamDataType = kdtInteger
      end>
    Left = 88
    Top = 26
  end
  object cqSetOperator: TWVCommandTypeInfo
    ID = '操作员查询一'
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
      end>
    Left = 88
    Top = 74
  end
  object WVOperGroupManager: TWVCommandTypeInfo
    ID = '操作员组查询一'
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
        ParamName = '组编号'
      end
      item
        ParamName = '组名称'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '操作员号'
      end>
    Left = 88
    Top = 122
  end
  object cqTotSubject: TWVCommandTypeInfo
    ID = '科目总账表'
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
        ParamName = '会计科目'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end>
    Left = 168
    Top = 146
  end
  object cqtradeSubject: TWVCommandTypeInfo
    ID = '交易科目情况表'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '操作员代码'
      end>
    Left = 168
    Top = 194
  end
  object WVSubBalanceRep: TWVCommandTypeInfo
    ID = '科目余额表'
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
        ParamName = '科目号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end>
    Left = 250
    Top = 26
  end
  object WVSystemRunStat: TWVCommandTypeInfo
    ID = '系统运行情况'
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
        ParamName = '结束日期'
      end>
    Left = 250
    Top = 74
  end
  object cqCardUsedInfo_R: TWVCommandTypeInfo
    ID = '卡片使用情况汇总_R'
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
        ParamName = '网点号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end>
    Left = 248
    Top = 122
  end
  object WVBusiReport: TWVCommandTypeInfo
    ID = '商户结算表'
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
        ParamName = '商户帐号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '显示级别'
      end>
    Left = 248
    Top = 218
  end
  object cqTicketCashRpt_R: TWVCommandTypeInfo
    ID = '票据现金报表_R'
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
        ParamName = '网点号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '科目类型'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 248
    Top = 170
  end
  object WVBusiReportPOS: TWVCommandTypeInfo
    ID = '商户结算表POS'
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
        ParamName = '商户帐号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '级别'
      end>
    Left = 248
    Top = 266
  end
  object WVBusiReportFC: TWVCommandTypeInfo
    ID = '商户结算表FC'
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
        ParamName = '商户帐号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '级别'
        ParamDataType = kdtInteger
      end>
    Left = 248
    Top = 314
  end
  object WVBusiReportDay: TWVCommandTypeInfo
    ID = '商户当日结算表'
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
        ParamName = '商户帐号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '级别'
      end>
    Left = 328
    Top = 2
  end
  object WVBusiPayInQ: TWVCommandTypeInfo
    ID = '商户解款余额查询'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
      end>
    Left = 328
    Top = 50
  end
  object WVBusiPayIn: TWVCommandTypeInfo
    ID = '商户解款'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '解款金额'
        ParamDataType = kdtFloat
      end>
    Left = 328
    Top = 98
  end
  object WVPayInQuery: TWVCommandTypeInfo
    ID = '商户解款查询'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end>
    Left = 328
    Top = 146
  end
  object cqBusiGatherRep: TWVCommandTypeInfo
    ID = '商户汇总结算表'
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
        ParamName = '商户帐号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '级别'
      end
      item
        ParamName = '商户类型'
      end>
    Left = 328
    Top = 194
  end
  object cqSubject: TWVCommandTypeInfo
    ID = '科目表查询'
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
      end>
    Left = 17
    Top = 194
  end
  object cqCardUsedInfo: TWVCommandTypeInfo
    ID = '卡片使用情况汇总'
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
        ParamName = '网点号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '卡类型'
      end>
    Left = 328
    Top = 242
  end
  object cqTicketCashRpt: TWVCommandTypeInfo
    ID = '票据现金报表'
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
        ParamName = '网点号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '餐次'
        ParamDataType = kdtInteger
      end>
    Left = 328
    Top = 290
  end
  object cqBusiStatFC: TWVCommandTypeInfo
    ID = '商户汇总结算表FC'
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
        ParamName = '商户帐号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '级别'
        ParamDataType = kdtInteger
      end>
    Left = 328
    Top = 338
  end
  object cqBusiRunStatRpt: TWVCommandTypeInfo
    ID = '商户营业情况表'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '级别'
      end
      item
        ParamName = '商户号'
      end
      item
        ParamName = '商户类型'
      end>
    Left = 16
    Top = 242
  end
  object cqQueryBusinessByKey: TWVCommandTypeInfo
    ID = '商户信息主键Q'
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
        ParamName = '商户标识'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 16
    Top = 106
  end
  object cqOperRpt: TWVCommandTypeInfo
    ID = '操作员业务报表'
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
        ParamName = '网点号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end>
    Left = 168
    Top = 242
  end
  object cqBusiFeeRpt: TWVCommandTypeInfo
    ID = '商户搭伙费报表'
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
        ParamName = '商户帐号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '显示级别'
      end>
    Left = 168
    Top = 290
  end
  object cqCardDestoryRpt: TWVCommandTypeInfo
    ID = '销户现金报表'
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
        ParamName = '操作员号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end>
    Left = 168
    Top = 338
  end
  object cqSysAccount: TWVCommandTypeInfo
    ID = '系统对账'
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
        ParamName = '对账日期'
      end
      item
        ParamName = '对账类型'
      end>
    Left = 16
    Top = 290
  end
  object cqSysAccQuery: TWVCommandTypeInfo
    ID = '系统对账查询'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '对账类型'
      end
      item
        ParamName = '查询类别'
      end
      item
        ParamName = '银行次数'
        ParamType = ptOutput
      end
      item
        ParamName = '一卡通次数'
        ParamType = ptOutput
      end>
    Left = 16
    Top = 338
  end
  object cqOperCashTot: TWVCommandTypeInfo
    ID = '操作员现金汇总报表'
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
        ParamName = '网点号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '科目类型'
      end>
    Left = 88
    Top = 170
  end
  object WVDealBankAccQ: TWVCommandTypeInfo
    ID = '银行对账查询'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '银行编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '对账状态'
      end
      item
        ParamName = '处理状态'
      end>
    Left = 400
    Top = 26
  end
  object WVDealBankAcc: TWVCommandTypeInfo
    ID = '银行对账处理'
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
        ParamName = '账单日期'
      end
      item
        ParamName = '银行编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '处理状态'
      end
      item
        ParamName = '备注'
      end>
    Left = 400
    Top = 74
  end
  object WVDealBankAccDtlQ: TWVCommandTypeInfo
    ID = '银行对账明细查询'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '银行编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '对账状态'
      end
      item
        ParamName = '处理状态'
      end
      item
        ParamName = '学工号'
      end>
    Left = 400
    Top = 122
  end
  object WVDealBankAccDtl: TWVCommandTypeInfo
    ID = '银行对账明细处理'
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
        ParamName = '账单日期'
      end
      item
        ParamName = '银行编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '处理状态'
      end
      item
        ParamName = '备注'
      end
      item
        ParamName = '记录号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '学工号'
      end>
    Left = 400
    Top = 170
  end
  object WVBalanceRpt: TWVCommandTypeInfo
    ID = '收支平衡表'
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
        ParamName = '结束日期'
      end>
    Left = 402
    Top = 218
  end
  object WVBusiPayIn_nju: TWVCommandTypeInfo
    ID = '商户解款查询_nju'
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
        ParamName = '商户帐号'
      end
      item
        ParamName = '月份'
      end>
    Left = 400
    Top = 266
  end
  object WVbusiPayIn_njuE: TWVCommandTypeInfo
    ID = '商户解款_nju'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '解款金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '月份'
      end
      item
        ParamName = '摘要'
      end>
    Left = 400
    Top = 314
  end
  object WVbusipayinQ_nju: TWVCommandTypeInfo
    ID = '商户解款信息查询_nju'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '解款年份'
      end>
    Left = 400
    Top = 362
  end
end
