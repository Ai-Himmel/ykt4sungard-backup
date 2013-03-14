inherited dmBusPosManage: TdmBusPosManage
  OldCreateOrder = True
  Left = 285
  object wvgetworkkey: TWVCommandTypeInfo
    ID = '取得工作密钥'
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
        ParamDataType = kdtObject
      end
      item
        ParamName = '参数标志'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end>
    Left = 32
    Top = 24
  end
  object kcworkkey: TKCWVQuery
    ID = '取得工作密钥'
    InputBindings = <
      item
        ParamName = '参数标志'
        FieldName = 'lvol0'
        DefaultValue = '0'
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
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 820404
    Left = 88
    Top = 40
  end
  object WVgetblacklist: TWVCommandTypeInfo
    ID = '读取黑名单'
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
        ParamName = '返回数据集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end>
    Left = 30
    Top = 120
  end
  object kcwgetblacklist: TKCWVQuery
    ID = '读取黑名单'
    InputBindings = <>
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
        ParamName = '返回数据集'
        FieldName = '@Dataset'
      end>
    RequestType = 950996
    Left = 89
    Top = 136
  end
  object getcardtypeinfo: TWVCommandTypeInfo
    ID = '读取卡类型'
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
        ParamDataType = kdtObject
      end
      item
        ParamName = '参数标志'
        DefaultValue = 'R'
      end>
    Left = 32
    Top = 72
  end
  object kcgetcardtypeinfo: TKCWVQuery
    ID = '读取卡类型'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '参数标志'
        FieldName = 'sstatus0'
        DefaultValue = 'R'
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
      end>
    RequestType = 847198
    Left = 88
    Top = 88
  end
  object uploadwater: TWVCommandTypeInfo
    ID = '上传流水'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
        DefaultValue = '0'
      end
      item
        ParamName = '流水号'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '物理ID'
        DefaultValue = '0'
      end
      item
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '工作站标示'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '入卡金额'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '出卡金额'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '消费金额'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '钱包'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '消费次数'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '交易标志'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = 'CRC校验码'
        DefaultValue = '0'
      end
      item
        ParamName = '发生日期'
      end
      item
        ParamName = '发生时间'
      end
      item
        ParamName = '物理编号2'
      end>
    Left = 32
    Top = 168
  end
  object kcupload: TKCWVQuery
    ID = '上传流水'
    InputBindings = <
      item
        ParamName = '流水号'
        FieldName = 'lvol4'
        DefaultValue = '0'
      end
      item
        ParamName = '物理ID'
        FieldName = 'sdate1'
        DefaultValue = '0'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol5'
        DefaultValue = '0'
      end
      item
        ParamName = '工作站标示'
        FieldName = 'lcert_code'
        DefaultValue = '0'
      end
      item
        ParamName = '入卡金额'
        FieldName = 'lvol9'
        DefaultValue = '0'
      end
      item
        ParamName = '出卡金额'
        FieldName = 'lvol10'
        DefaultValue = '0'
      end
      item
        ParamName = '消费金额'
        FieldName = 'lvol8'
        DefaultValue = '0'
      end
      item
        ParamName = '钱包'
        FieldName = 'lvol6'
        DefaultValue = '0'
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol7'
        DefaultValue = '0'
      end
      item
        ParamName = '交易标志'
        FieldName = 'lvol12'
        DefaultValue = '0'
      end
      item
        ParamName = 'CRC校验码'
        FieldName = 'sbank_code2'
        DefaultValue = '0'
      end
      item
        ParamName = '发生日期'
        FieldName = 'spost_code'
      end
      item
        ParamName = '发生时间'
        FieldName = 'spost_code2'
      end
      item
        ParamName = '物理编号2'
        FieldName = 'sphone3'
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
    RequestType = 940031
    Left = 88
    Top = 184
  end
  object kcBusPosSerialQ: TKCWVQuery
    ID = '车载机流水查询'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '部门'
        FieldName = 'scert_no'
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
        ParamName = '开始时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime1'
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
        ParamName = '返回数据集'
        FieldName = '@Dataset'
      end>
    RequestType = 846723
    Left = 88
    Top = 232
  end
  object cqBusPosSerialQ: TWVCommandTypeInfo
    ID = '车载机流水查询'
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
        ParamName = '返回数据集'
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
        ParamName = '部门'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '结束时间'
      end>
    Left = 32
    Top = 216
  end
  object cqBusPosSerStat: TWVCommandTypeInfo
    ID = '车载机流水统计'
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
        ParamName = '返回数据集'
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
        ParamName = '部门'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 32
    Top = 264
  end
  object kcBusPosSerStat: TKCWVQuery
    ID = '车载机流水统计'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '部门'
        FieldName = 'scert_no'
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
        ParamName = '类别'
        FieldName = 'lvol0'
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
        ParamName = '返回数据集'
        FieldName = '@Dataset'
      end>
    RequestType = 846724
    Left = 88
    Top = 280
  end
  object cq1BusPosserial: TWVCommandTypeInfo
    ID = '单Pos流水查询'
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
        ParamName = '返回数据集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '设备编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '结束时间'
      end>
    Left = 32
    Top = 312
  end
  object kc1BusPosSerial: TKCWVQuery
    ID = '单Pos流水查询'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '设备名称'
        FieldName = 'snote'
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
        ParamName = '开始时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime1'
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
        ParamName = '返回数据集'
        FieldName = '@Dataset'
      end>
    RequestType = 846725
    Left = 88
    Top = 328
  end
  object cq1BusPosStat: TWVCommandTypeInfo
    ID = '单Pos流水统计'
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
        ParamName = '返回数据集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '设备编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '结束时间'
      end>
    Left = 152
    Top = 16
  end
  object kcBusPosStat: TKCWVQuery
    ID = '单Pos流水统计'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '设备名称'
        FieldName = 'snote'
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
        ParamName = '开始时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime1'
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
        ParamName = '返回数据集'
        FieldName = '@Dataset'
      end>
    RequestType = 846726
    Left = 208
    Top = 32
  end
end
