inherited dmDeviceSuperviseDef: TdmDeviceSuperviseDef
  OldCreateOrder = True
  Left = 217
  Top = 186
  object cpSmartTermUpSerial: TWVCommandTypeInfo
    ID = '手持机流水采集'
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
        ParamName = '终端设备ＩＤ'
      end
      item
        ParamName = '交易流水号'
      end
      item
        ParamName = '交易卡号'
      end
      item
        ParamName = '钱包号'
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = '累计使用次数'
      end
      item
        ParamName = '本次消费金额'
      end
      item
        ParamName = '入卡金额'
      end
      item
        ParamName = '出卡金额'
      end
      item
        ParamName = '交易标记'
      end
      item
        ParamName = '通信版本号'
      end
      item
        ParamName = '数据通信启动原因'
      end
      item
        ParamName = 'CRC'
      end>
    Left = 56
    Top = 74
  end
  object cqSmartTermSetParam: TWVCommandTypeInfo
    ID = '手持机参数设置'
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
        ParamName = '设备物理ID'
      end>
    Left = 56
    Top = 128
  end
  object cqGetSysWorkKey: TWVCommandTypeInfo
    ID = '读取工作密钥'
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
        ParamName = '参数标志'
        ParamDataType = kdtInteger
      end>
    Left = 56
    Top = 184
  end
  object cqSmartTermDownBlkCard: TWVCommandTypeInfo
    ID = '下传手持机黑白名单'
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
        ParamName = '设备物理ID'
      end>
    Left = 56
    Top = 242
  end
  object cpUpdateVersion: TWVCommandTypeInfo
    ID = '更新手持机名单版本'
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
        ParamName = '设备物理ID'
      end
      item
        ParamName = '版本号'
      end>
    Left = 56
    Top = 298
  end
  object cqsendSmartTermList: TWVCommandTypeInfo
    ID = '下发手持机名单查询'
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
        ParamName = '学工号'
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备编号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属校区'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '发送状态'
      end>
    Left = 232
    Top = 130
  end
  object cqacceptSmartTermList: TWVCommandTypeInfo
    ID = '采集手持机认证流水'
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
        ParamName = '终端设备ID'
      end
      item
        ParamName = '交易流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = '交易标记'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通信版本号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'CRC'
      end
      item
        ParamName = '数据通信启动原因'
        ParamDataType = kdtInteger
      end>
    Left = 232
    Top = 66
  end
  object cqSmartTermQueryList: TWVCommandTypeInfo
    ID = '手持机名单分配查询'
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
        ParamName = '学工号'
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '院系'
      end
      item
        ParamName = '专业'
      end
      item
        ParamName = '班级'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属校区'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '手持机编号'
      end>
    Left = 56
    Top = 10
  end
  object WVCommandTypeInfo1: TWVCommandTypeInfo
    ID = '手持机名单下传'
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
        ParamName = '设备编号'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '学工号'
      end>
    Left = 232
    Top = 10
  end
  object KCWVProcessor1: TKCWVProcessor
    ID = '手持机流水采集'
    InputBindings = <
      item
        ParamName = '终端设备ＩＤ'
        FieldName = 'sdate1'
      end
      item
        ParamName = '交易流水号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '交易日期'
        FieldName = 'spost_code'
      end
      item
        ParamName = '交易时间'
        FieldName = 'spost_code2'
      end
      item
        ParamName = '累计使用次数'
        FieldName = 'lvol7'
      end
      item
        ParamName = '本次消费金额'
        FieldName = 'lvol8'
      end
      item
        ParamName = '入卡金额'
        FieldName = 'lvol9'
      end
      item
        ParamName = '出卡金额'
        FieldName = 'lvol10'
      end
      item
        ParamName = '交易标记'
        FieldName = 'lvol12'
      end
      item
        ParamName = '通信版本号'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '数据通信启动原因'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = 'CRC'
        FieldName = 'sbank_code2'
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
    RequestType = 930031
    KCDataset = Dataset
    Left = 128
    Top = 98
  end
  object KCWVQuery1: TKCWVQuery
    ID = '手持机参数设置'
    InputBindings = <
      item
        ParamName = '设备物理ID'
        FieldName = 'sbank_pwd2'
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
    RequestType = 820105
    Left = 128
    Top = 154
  end
  object KCWVQuery2: TKCWVQuery
    ID = '读取工作密钥'
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
    RequestType = 820404
    Left = 128
    Top = 210
  end
  object KCWVQuery3: TKCWVQuery
    ID = '下传手持机黑白名单'
    InputBindings = <
      item
        ParamName = '设备物理ID'
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
    RequestType = 930039
    Left = 128
    Top = 266
  end
  object KCWVProcessor2: TKCWVProcessor
    ID = '更新手持机名单版本'
    InputBindings = <
      item
        ParamName = '设备物理ID'
        FieldName = 'sdate1'
      end
      item
        ParamName = '版本号'
        FieldName = 'sserial0'
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
    RequestType = 930046
    KCDataset = Dataset
    Left = 128
    Top = 322
  end
  object KCWVQuery4: TKCWVQuery
    ID = '下发手持机名单查询'
    InputBindings = <
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '姓名'
        FieldName = 'semail'
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '客户类别'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '收费类别'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '设备编号'
        FieldName = 'Sname'
      end
      item
        ParamName = '客户号'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '所属校区'
        FieldName = 'lvol5'
      end
      item
        ParamName = '发送状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '状态'
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
    RequestType = 848023
    Left = 304
    Top = 146
  end
  object kcSmartTermQueryList: TKCWVQuery
    ID = '手持机名单分配查询'
    InputBindings = <
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '姓名'
        FieldName = 'semail'
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '客户类别'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '卡类型'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol6'
      end
      item
        ParamName = '院系'
        FieldName = 'sstation0'
      end
      item
        ParamName = '专业'
        FieldName = 'sstation1'
      end
      item
        ParamName = '班级'
        FieldName = 'sorder0'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '所属校区'
        FieldName = 'lvol7'
      end
      item
        ParamName = '手持机编号'
        FieldName = 'sname'
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
    RequestType = 848004
    Left = 128
    Top = 34
  end
  object KCWVProcessor3: TKCWVProcessor
    ID = '手持机名单下传'
    InputBindings = <
      item
        ParamName = '设备编号'
        FieldName = 'sname'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '操作员号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '学工号'
        FieldName = 'semail'
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
    RequestType = 848006
    KCDataset = Dataset
    Left = 304
    Top = 26
  end
  object KCacceptSmartTermList: TKCWVProcessor
    ID = '采集手持机认证流水'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'Sdate0'
      end
      item
        ParamName = '交易流水号'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol7'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '交易时间'
        FieldName = 'spost_code2'
      end
      item
        ParamName = '交易标记'
        FieldName = 'lvol11'
      end
      item
        ParamName = '通信版本号'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '数据通信启动原因'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = 'CRC'
        FieldName = 'sbank_code2'
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
    RequestType = 930101
    KCDataset = Dataset
    Left = 304
    Top = 82
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 480
    Top = 24
  end
  object ckDeleteList: TKCWVProcessor
    ID = '手持机名单删除'
    InputBindings = <
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '设备编号'
        FieldName = 'sname'
      end
      item
        ParamName = '姓名'
        FieldName = 'semail'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol1'
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
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 848008
    KCDataset = Dataset
    Left = 304
    Top = 202
  end
  object cqDeleteList: TWVCommandTypeInfo
    ID = '手持机名单删除'
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
        ParamName = '学工号'
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '设备编号'
      end>
    Left = 232
    Top = 186
  end
  object WVCommandTypeInfo2: TWVCommandTypeInfo
    ID = '手持机名单成功'
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
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备号'
      end>
    Left = 232
    Top = 242
  end
  object KCWVProcessor4: TKCWVProcessor
    ID = '手持机名单成功'
    InputBindings = <
      item
        ParamName = '设备号'
        FieldName = 'sname'
      end
      item
        ParamName = '卡号'
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
    RequestType = 848024
    KCDataset = Dataset
    Left = 304
    Top = 258
  end
  object WVAttendSerial: TWVCommandTypeInfo
    ID = '手持机考勤流水采集'
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
        ParamName = '物理卡号'
      end
      item
        ParamName = '考勤时间'
      end>
    Left = 232
    Top = 298
  end
  object kcAttendSerial: TKCWVProcessor
    ID = '手持机考勤流水采集'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '考勤时间'
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
    RequestType = 930032
    KCDataset = Dataset
    Left = 304
    Top = 306
  end
end
