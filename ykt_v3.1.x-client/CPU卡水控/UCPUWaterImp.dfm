inherited cmCPUWaterImp: TcmCPUWaterImp
  OldCreateOrder = True
  Left = 285
  object cpRollBack: TKCWVProcessor
    ID = '失败信息_water'
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
    ID = '水控转账_water'
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
      end
      item
        ParamName = '钱包号'
        FieldName = 'lbank_acc_type'
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
    ID = '交易参考号_water'
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
  object cqQueryGlobeParaByKey: TKCWVQuery
    ID = '全局参数主键查询_water'
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
      end
      item
        ParamName = '密钥'
        FieldName = 'scard0'
      end>
    RequestType = 820404
    Left = 32
    Top = 162
  end
  object cpSaveFeeType: TKCWVProcessor
    ID = '保存费率设置卡'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '标志'
        FieldName = 'sstation0'
      end
      item
        ParamName = '费率编号'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '费率名称'
        FieldName = 'semail'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lwithdraw_flag'
        DefaultValue = 0
      end
      item
        ParamName = '计费单位'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '费率类型'
        FieldName = 'sname'
      end
      item
        ParamName = '费率个数'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '数量'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '费率时间1'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '费率金额1'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '费率分钟1'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '费率时间2'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '费率金额2'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '费率分钟2'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '费率时间3'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '费率金额3'
        FieldName = 'lvol8'
        DefaultValue = 0
      end
      item
        ParamName = '费率分钟3'
        FieldName = 'lvol7'
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
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end
      item
        ParamName = '费率编号'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end>
    RequestType = 846405
    KCDataset = Dataset
    Left = 32
    Top = 208
  end
  object kcFeeTypeQ: TKCWVQuery
    ID = '费率设置卡查询'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '费率名称'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '标志'
        FieldName = 'sstation0'
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
    RequestType = 846405
    Left = 32
    Top = 258
  end
  object kcFeeTypeDel: TKCWVQuery
    ID = '费率设置卡删除'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '费率名称'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '标志'
        FieldName = 'sstation0'
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
    RequestType = 846405
    Left = 32
    Top = 306
  end
  object kcSmlTradeSerial: TKCWVQuery
    ID = '小钱包流水查询'
    InputBindings = <
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
        ParamName = '截止日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '终端流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '凭证号码'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '学/工号'
        FieldName = 'spager'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '流水状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '查询类型'
        FieldName = 'sstatus4'
      end
      item
        ParamName = '交易开始日期'
        FieldName = 'stime1'
      end
      item
        ParamName = '交易结束日期'
        FieldName = 'stime2'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '联机状态'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '开始时间'
        FieldName = 'sorder1'
      end
      item
        ParamName = '结束时间'
        FieldName = 'sorder2'
      end
      item
        ParamName = '交易标志'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '外部类型'
        FieldName = 'lsafe_level'
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
    RequestType = 850012
    Left = 96
    Top = 26
  end
  object KCsmlSerialRcv: TKCWVQuery
    ID = '小钱包流水冲正'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '终端流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易金额'
        FieldName = 'damt0'
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
      end
      item
        ParamName = '小钱包余额'
        FieldName = 'lvol2'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end>
    RequestType = 847128
    Left = 96
    Top = 74
  end
end
