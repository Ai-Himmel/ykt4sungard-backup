inherited dmSetSystemImp: TdmSetSystemImp
  OldCreateOrder = True
  Left = 285
  Width = 848
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 560
    Top = 8
  end
  object cqsetPlanTask: TKCWVQuery
    ID = '计划任务查询'
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
    RequestType = 846202
    Left = 160
    Top = 10
  end
  object cpsetPlanTask: TKCWVProcessor
    ID = '计划任务管理'
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
        ParamName = '任务编号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '任务说明'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '程序名'
        FieldName = 'snote'
      end
      item
        ParamName = '程序路径'
        FieldName = 'Vsvarstr1'
      end
      item
        ParamName = '命令行参数'
        FieldName = 'Vsvarstr2'
      end
      item
        ParamName = '每天一次'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '每星期一次'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '每月一次'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '运行开始时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '运行结束时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '是否启用'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
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
    RequestType = 846202
    KCDataset = Dataset
    Left = 160
    Top = 58
  end
  object WVQueryPlanTask: TWVCommandTypeInfo
    ID = '计划任务查询'
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
        ParamName = '任务说明'
      end
      item
        ParamName = '程序名'
      end
      item
        ParamName = '程序路径'
      end
      item
        ParamName = '命令行参数'
      end
      item
        ParamName = '每天一次'
      end
      item
        ParamName = '每星期一次'
      end
      item
        ParamName = '每月一次'
      end
      item
        ParamName = '运行开始时间'
      end
      item
        ParamName = '运行结束时间'
      end
      item
        ParamName = '是否启用'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 224
    Top = 34
  end
  object WVSetPlanTask: TWVCommandTypeInfo
    ID = '计划任务管理'
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
        ParamName = '任务编号'
      end
      item
        ParamName = '任务说明'
      end
      item
        ParamName = '程序名'
      end
      item
        ParamName = '程序路径'
      end
      item
        ParamName = '命令行参数'
      end
      item
        ParamName = '每天一次'
      end
      item
        ParamName = '每星期一次'
      end
      item
        ParamName = '每月一次'
      end
      item
        ParamName = '运行开始时间'
      end
      item
        ParamName = '运行结束时间'
      end
      item
        ParamName = '是否启用'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 224
    Top = 82
  end
  object cqqueryPlanTask: TKCWVQuery
    ID = '计划任务日志查询'
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
    RequestType = 846203
    Left = 160
    Top = 114
  end
  object WVQueryPlanTaskInfo: TWVCommandTypeInfo
    ID = '计划任务日志查询'
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
        ParamName = '交易类型'
      end>
    Left = 224
    Top = 130
  end
  object cqsetMesList: TKCWVQuery
    ID = '消息队列查询'
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
        ParamName = '消息编号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '交易码'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '消息状态'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '消息级别'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '子系统编号'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '设备编号'
        FieldName = 'Lvol5'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
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
    RequestType = 846204
    Left = 160
    Top = 170
  end
  object cpsetMesList: TKCWVProcessor
    ID = '消息队列管理'
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
        ParamName = '消息编号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '消息状态'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '最大发送次数'
        FieldName = 'Lvol9'
      end
      item
        ParamName = '交易类型'
        FieldName = 'sstatus0'
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
    RequestType = 846204
    KCDataset = Dataset
    Left = 160
    Top = 218
  end
  object WVQueryMesList: TWVCommandTypeInfo
    ID = '消息队列查询'
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
        ParamName = '交易类型'
      end
      item
        ParamName = '消息编号'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '消息状态'
      end
      item
        ParamName = '消息级别'
      end
      item
        ParamName = '子系统编号'
      end
      item
        ParamName = '设备编号'
      end
      item
        ParamName = '交易日期'
      end>
    Left = 224
    Top = 178
  end
  object WVSetMesList: TWVCommandTypeInfo
    ID = '消息队列管理'
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
        ParamName = '消息编号'
      end
      item
        ParamName = '消息状态'
      end
      item
        ParamName = '最大发送次数'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 224
    Top = 226
  end
  object cqsetNetInfo: TKCWVQuery
    ID = '网点信息查询'
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
        ParamName = '所在区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '站点号'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '交易类型'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '网点名称'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '网点类型'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '银行帐户名'
        FieldName = 'sbankname'
      end
      item
        ParamName = '联系人'
        FieldName = 'sall_name'
      end
      item
        ParamName = '电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone2'
      end
      item
        ParamName = '传真'
        FieldName = 'sphone3'
      end
      item
        ParamName = '地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '邮政编码'
        FieldName = 'spost_code'
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
    RequestType = 846501
    Left = 304
    Top = 18
  end
  object cpsetNetInfo: TKCWVProcessor
    ID = '网点信息管理'
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
        ParamName = '所在区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '站点号'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '交易类型'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '网点名称'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '网点类型'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '银行帐户名'
        FieldName = 'sbankname'
      end
      item
        ParamName = '联系人'
        FieldName = 'sall_name'
      end
      item
        ParamName = '电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone2'
      end
      item
        ParamName = '传真'
        FieldName = 'sphone3'
      end
      item
        ParamName = '地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '邮政编码'
        FieldName = 'spost_code'
      end
      item
        ParamName = '镇区'
        FieldName = 'snote2'
      end
      item
        ParamName = '渠道编码'
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
    RequestType = 846501
    KCDataset = Dataset
    Left = 304
    Top = 66
  end
  object WVNetInfoQuery: TWVCommandTypeInfo
    ID = '网点信息查询'
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
        ParamName = '所在区域'
      end
      item
        ParamName = '站点号'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '网点名称'
      end
      item
        ParamName = '网点类型'
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行账号'
      end
      item
        ParamName = '银行帐户名'
      end
      item
        ParamName = '联系人'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '传真'
      end
      item
        ParamName = '地址'
      end
      item
        ParamName = '邮政编码'
      end>
    Left = 360
    Top = 34
  end
  object WVSetNetInfo: TWVCommandTypeInfo
    ID = '网点信息管理'
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
        ParamName = '所在区域'
      end
      item
        ParamName = '站点号'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '网点名称'
      end
      item
        ParamName = '网点类型'
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行账号'
      end
      item
        ParamName = '银行帐户名'
      end
      item
        ParamName = '联系人'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '传真'
      end
      item
        ParamName = '地址'
      end
      item
        ParamName = '邮政编码'
      end
      item
        ParamName = '镇区'
      end
      item
        ParamName = '渠道编码'
      end>
    Left = 360
    Top = 82
  end
  object cqsetTradeFee: TKCWVQuery
    ID = '交易收费查询'
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
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '交易码'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '交易类型'
        FieldName = 'lvol1'
      end
      item
        ParamName = '收费方式'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '收费金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '收费顺序'
        FieldName = 'Lvol3'
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
    RequestType = 846502
    Left = 16
    Top = 18
  end
  object cpsetTradeFee: TKCWVProcessor
    ID = '交易收费配置'
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
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '交易码'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '交易类型'
        FieldName = 'lvol1'
      end
      item
        ParamName = '收费方式'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '收费金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '收费顺序'
        FieldName = 'Lvol3'
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
    RequestType = 846502
    KCDataset = Dataset
    Left = 16
    Top = 66
  end
  object WVQTradeFee: TWVCommandTypeInfo
    ID = '交易收费查询'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '收费类别'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '收费方式'
      end
      item
        ParamName = '收费金额'
      end
      item
        ParamName = '收费顺序'
      end>
    Left = 80
    Top = 42
  end
  object WVSetTradeFee: TWVCommandTypeInfo
    ID = '交易收费配置'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '收费类别'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '收费方式'
      end
      item
        ParamName = '收费金额'
      end
      item
        ParamName = '收费顺序'
      end>
    Left = 80
    Top = 90
  end
  object cqCheck: TKCWVProcessor
    ID = 'Pos流水审核1'
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
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '钱包号'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '交易次数'
        FieldName = 'Lvol6'
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
    RequestType = 846403
    KCDataset = Dataset
    Left = 304
    Top = 114
  end
  object WVCheck: TWVCommandTypeInfo
    ID = 'Pos流水审核1'
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
        ParamName = '批次号'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '钱包号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易次数'
        ParamDataType = kdtInteger
      end>
    Left = 360
    Top = 130
  end
  object cqqueryOperLog: TKCWVQuery
    ID = '操作日志查询'
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
        ParamName = '站点号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '站点流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '操作员'
        FieldName = 'Semp_no'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '流水状态'
        FieldName = 'Sstatus1'
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
    RequestType = 820302
    Left = 304
    Top = 162
  end
  object WVQueryOperLog: TWVCommandTypeInfo
    ID = '操作日志查询'
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
        ParamName = '站点号'
      end
      item
        ParamName = '站点流水号'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '流水状态'
      end
      item
        ParamName = '结束日期'
      end>
    Left = 360
    Top = 178
  end
  object cqCardFee: TWVCommandTypeInfo
    ID = '发卡收费配置查询'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '收费类别'
      end>
    Left = 360
    Top = 226
  end
  object KCWcardFee: TKCWVQuery
    ID = '发卡收费配置查询'
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
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
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
    RequestType = 846111
    Left = 304
    Top = 210
  end
  object cpCardFee: TKCWVProcessor
    ID = '发卡收费配置'
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
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '卡类型'
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
      end>
    RequestType = 846111
    KCDataset = Dataset
    Left = 304
    Top = 258
  end
  object cqCardFeeSet: TWVCommandTypeInfo
    ID = '发卡收费配置'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '收费类别'
      end>
    Left = 360
    Top = 274
  end
  object WVCsetCardType: TWVCommandTypeInfo
    ID = '卡类别设置'
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
        ParamName = '交易类型'
      end
      item
        ParamName = '卡类别'
      end
      item
        ParamName = '卡成本费'
      end
      item
        ParamName = '卡类别名称'
      end
      item
        ParamName = '用途'
      end
      item
        ParamName = '能否重用'
      end
      item
        ParamName = '能否补办'
      end
      item
        ParamName = '能否挂失'
      end
      item
        ParamName = '是否支持多钱包'
      end
      item
        ParamName = '使用状态'
      end
      item
        ParamName = '有效天数'
      end
      item
        ParamName = '可用的收费类别'
      end
      item
        ParamName = '默认收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否匿名卡'
      end
      item
        ParamName = '卡物理类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '预存金额'
      end
      item
        ParamName = '单笔限额'
      end
      item
        ParamName = '卡限额'
      end>
    Left = 80
    Top = 186
  end
  object WVQsetCardType: TWVCommandTypeInfo
    ID = '卡类别查询'
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
        ParamName = '交易类型'
      end
      item
        ParamName = '卡类别'
      end>
    Left = 80
    Top = 138
  end
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
      end
      item
        ParamName = '卡类别'
        FieldName = 'lvol0'
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
    RequestType = 846101
    Left = 16
    Top = 114
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
      end
      item
        ParamName = '预存金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '单笔限额'
        FieldName = 'damt1'
        DefaultValue = 0
      end
      item
        ParamName = '卡限额'
        FieldName = 'damt2'
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
    Left = 16
    Top = 162
  end
  object KCPKGQuery: TKCWVQuery
    ID = '包裹查询'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '处理状态'
        FieldName = 'sstock_code'
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
    RequestType = 2029
    Left = 16
    Top = 210
  end
  object WVPKGQuery: TWVCommandTypeInfo
    ID = '包裹查询'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '处理状态'
      end>
    Left = 80
    Top = 234
  end
  object KCPKGOper: TKCWVProcessor
    ID = '包裹操作'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '处理状态'
        FieldName = 'sstock_code'
      end
      item
        ParamName = '包裹编号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '备注'
        FieldName = 'vsvarstr1'
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
    RequestType = 2029
    KCDataset = Dataset
    Left = 16
    Top = 258
  end
  object WVPKGOper: TWVCommandTypeInfo
    ID = '包裹操作'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '处理状态'
      end
      item
        ParamName = '包裹编号'
      end
      item
        ParamName = '备注'
      end>
    Left = 80
    Top = 282
  end
  object KCFileQ: TKCWVQuery
    ID = '文件查询'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '包裹编号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '处理状态'
        FieldName = 'sstock_code'
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
    RequestType = 2030
    Left = 160
    Top = 266
  end
  object WVFielQ: TWVCommandTypeInfo
    ID = '文件查询'
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
        ParamName = '包裹编号'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '处理状态'
      end>
    Left = 224
    Top = 274
  end
  object KCFileOper: TKCWVProcessor
    ID = '文件操作'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '处理状态'
        FieldName = 'sstock_code'
      end
      item
        ParamName = '包裹编号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '备注'
        FieldName = 'vsvarstr1'
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
    RequestType = 2030
    KCDataset = Dataset
    Left = 160
    Top = 314
  end
  object WVFileOper: TWVCommandTypeInfo
    ID = '文件操作'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '处理状态'
      end
      item
        ParamName = '包裹编号'
      end
      item
        ParamName = '备注'
      end>
    Left = 224
    Top = 322
  end
end
