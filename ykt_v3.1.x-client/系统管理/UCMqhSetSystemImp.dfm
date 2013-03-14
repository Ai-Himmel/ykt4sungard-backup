inherited dmSetSystemImp: TdmSetSystemImp
  OldCreateOrder = True
  Left = 326
  Width = 848
  object cqSetGridShowModle: TKCWVQuery
    ID = '表格模板显示查询'
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
    RequestType = 999999
    Left = 24
    Top = 10
  end
  object cpSetGridShowModle: TKCWVProcessor
    ID = '表格模板显示设置'
    InputBindings = <>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 1000000
    KCDataset = Dataset
    Left = 24
    Top = 58
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 560
    Top = 8
  end
  object cqSetGridShow: TKCWVQuery
    ID = '表格显示设置'
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
    RequestType = 88888
    Left = 24
    Top = 106
  end
  object ctSetGridShowModle: TWVCommandTypeInfo
    ID = '表格模板显示查询'
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
    Left = 96
    Top = 34
  end
  object ckSetGridShowModle: TWVCommandTypeInfo
    ID = '表格模板显示设置'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end>
    Left = 96
    Top = 82
  end
  object ckSetGridShow: TWVCommandTypeInfo
    ID = '表格显示设置'
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
    Left = 96
    Top = 130
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
    Left = 176
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
    Left = 176
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
    Left = 240
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
    Left = 240
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
    Left = 176
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
    Left = 240
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
    Left = 176
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
    Left = 176
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
    Left = 240
    Top = 186
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
    Left = 240
    Top = 234
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
    Left = 320
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
    Left = 320
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
    Left = 376
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
      end>
    Left = 376
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
    Left = 24
    Top = 154
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
    Left = 24
    Top = 202
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
    Left = 96
    Top = 178
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
    Left = 96
    Top = 226
  end
  object cqposSerialManager: TKCWVQuery
    ID = 'POS流水查询'
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
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sname'
      end
      item
        ParamName = '设备流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '商户卡号'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易标记'
        FieldName = 'lvol11'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '导入序号'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '流水状态'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
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
    RequestType = 846402
    Left = 24
    Top = 250
  end
  object cpposSerialManager: TKCWVProcessor
    ID = 'POS流水管理'
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
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡交易次数'
        FieldName = 'lvol6'
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
        ParamName = '设备物理编号'
        FieldName = 'sname'
      end
      item
        ParamName = '设备流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '商户卡号'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '卡交易前余额'
        FieldName = 'Damt3'
      end
      item
        ParamName = '卡交易后余额'
        FieldName = 'Damt4'
      end
      item
        ParamName = '发生额'
        FieldName = 'damt0'
      end
      item
        ParamName = '管理费'
        FieldName = 'damt1'
      end
      item
        ParamName = '交易标记'
        FieldName = 'lvol11'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '导入批次号'
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
    RequestType = 846402
    KCDataset = Dataset
    Left = 24
    Top = 298
  end
  object WVposSerialManager: TWVCommandTypeInfo
    ID = 'POS流水查询'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备流水号'
      end
      item
        ParamName = '商户卡号'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '交易标记'
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '导入序号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '流水状态'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 96
    Top = 274
  end
  object WVposSerialManager1: TWVCommandTypeInfo
    ID = 'POS流水管理'
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
        ParamName = '卡号'
      end
      item
        ParamName = '卡交易次数'
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备流水号'
      end
      item
        ParamName = '商户卡号'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '钱包号'
      end
      item
        ParamName = '卡交易前余额'
      end
      item
        ParamName = '卡交易后余额'
      end
      item
        ParamName = '发生额'
      end
      item
        ParamName = '管理费'
      end
      item
        ParamName = '交易标记'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '导入批次号'
      end>
    Left = 96
    Top = 322
  end
  object cqPosSerialImport: TKCWVProcessor
    ID = 'Pos流水导入'
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
        ParamName = '序号'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '是否传送完毕'
        FieldName = 'scust_type'
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
        ParamName = '设备物理编号'
        FieldName = 'sname'
      end
      item
        ParamName = '设备流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '商户卡号'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
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
        ParamName = '卡交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '卡交易前余额'
        FieldName = 'Damt3'
      end
      item
        ParamName = '卡交易后余额'
        FieldName = 'Damt4'
      end
      item
        ParamName = '发生额'
        FieldName = 'damt0'
      end
      item
        ParamName = '管理费'
        FieldName = 'damt1'
      end
      item
        ParamName = '交易标记'
        FieldName = 'lvol11'
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
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end>
    RequestType = 846401
    KCDataset = Dataset
    Left = 176
    Top = 266
  end
  object WVPosSerialImport: TWVCommandTypeInfo
    ID = 'Pos流水导入'
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
        ParamType = ptInputOutput
      end
      item
        ParamName = '序号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否传送完毕'
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '商户卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易码'
        ParamDataType = kdtInteger
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
        ParamName = '卡交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡交易前余额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '卡交易后余额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '发生额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '管理费'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '交易标记'
        ParamDataType = kdtInteger
      end>
    Left = 240
    Top = 282
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
    Left = 320
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
    Left = 376
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
    Left = 320
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
    Left = 376
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
    Left = 376
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
    Left = 320
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
    Left = 320
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
    Left = 376
    Top = 274
  end
  object cpposSerManager: TKCWVProcessor
    ID = 'POS异常流水管理'
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
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sname2'
      end
      item
        ParamName = '设备流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '商户卡号'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '卡交易前余额'
        FieldName = 'Damt3'
      end
      item
        ParamName = '卡交易后余额'
        FieldName = 'Damt4'
      end
      item
        ParamName = '发生额'
        FieldName = 'damt0'
      end
      item
        ParamName = '管理费'
        FieldName = 'damt1'
      end
      item
        ParamName = '交易标记'
        FieldName = 'lvol11'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '主交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '主设备物理编号'
        FieldName = 'sname'
      end
      item
        ParamName = '主设备流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '流水状态'
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
    RequestType = 846404
    KCDataset = Dataset
    Left = 176
    Top = 314
  end
  object WVposSeManager1: TWVCommandTypeInfo
    ID = 'POS异常流水管理'
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
        ParamName = '卡号'
      end
      item
        ParamName = '卡交易次数'
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备流水号'
      end
      item
        ParamName = '商户卡号'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '钱包号'
      end
      item
        ParamName = '卡交易前余额'
      end
      item
        ParamName = '卡交易后余额'
      end
      item
        ParamName = '发生额'
      end
      item
        ParamName = '管理费'
      end
      item
        ParamName = '交易标记'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '主交易日期'
      end
      item
        ParamName = '主设备物理编号'
      end
      item
        ParamName = '主设备流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '流水状态'
      end>
    Left = 240
    Top = 330
  end
  object cqposSerManager: TKCWVQuery
    ID = 'POS异常流水查询'
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
        ParamName = '交易结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sname'
      end
      item
        ParamName = '设备流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '商户卡号'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易标记'
        FieldName = 'lvol11'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '导入序号'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '流水状态'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '交易开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lwithdraw_flag'
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
    RequestType = 846404
    Left = 320
    Top = 306
  end
  object WVposSeManager: TWVCommandTypeInfo
    ID = 'POS异常流水查询'
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
        ParamName = '交易开始日期'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备流水号'
      end
      item
        ParamName = '商户卡号'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '交易标记'
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '导入序号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '流水状态'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '交易结束日期'
      end
      item
        ParamName = '设备编号'
      end>
    Left = 376
    Top = 322
  end
  object cqPatchDel: TWVCommandTypeInfo
    ID = 'pos流水批量删除'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '批量标志'
        ParamDataType = kdtInteger
      end>
    Left = 488
    Top = 34
  end
  object cpPatchdel: TKCWVProcessor
    ID = 'pos流水批量删除'
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
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '批量标志'
        FieldName = 'lwithdraw_flag'
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
    RequestType = 846402
    KCDataset = Dataset
    Left = 432
    Top = 18
  end
  object cqSetWaterPrice: TKCWVQuery
    ID = '汇多水价设置查询'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
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
    RequestType = 846206
    Left = 432
    Top = 66
  end
  object cpSetWaterPrice: TKCWVProcessor
    ID = '汇多水价设置'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '水价1'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '水价2'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '水价3'
        FieldName = 'lvol2'
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
    RequestType = 846206
    KCDataset = Dataset
    Left = 432
    Top = 114
  end
  object WVSetWaterPrice: TWVCommandTypeInfo
    ID = '汇多水价设置'
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
        ParamName = '水价1'
      end
      item
        ParamName = '水价2'
      end
      item
        ParamName = '水价3'
      end>
    Left = 488
    Top = 130
  end
  object WVSetWaterPriceQ: TWVCommandTypeInfo
    ID = '汇多水价设置查询'
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
      end>
    Left = 488
    Top = 82
  end
end
