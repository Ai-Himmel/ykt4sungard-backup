inherited dmSubSystemImp: TdmSubSystemImp
  OldCreateOrder = True
  Left = 468
  Top = 97
  Height = 581
  Width = 588
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 424
    Top = 8
  end
  object cqQuerySubSystemByOther: TKCWVQuery
    ID = '子系统非主键查询'
    InputBindings = <
      item
        ParamName = '子系统名称'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '子系统类别'
        FieldName = 'lvol1'
      end
      item
        ParamName = '子系统状态'
        FieldName = 'lvol2'
      end
      item
        ParamName = '子系统所在区域'
        FieldName = 'lvol3'
      end
      item
        ParamName = '网络地址'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = 'sname'
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
    RequestType = 820005
    Left = 320
    Top = 215
  end
  object cpAddSubSystemInfo: TKCWVProcessor
    ID = '子系统设置.增加'
    InputBindings = <
      item
        ParamName = '子系统名称'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '子系统类别'
        FieldName = 'lvol1'
      end
      item
        ParamName = '子系统所在区域'
        FieldName = 'lvol3'
      end
      item
        ParamName = '工作站'
        FieldName = 'lvol4'
      end
      item
        ParamName = '网络地址'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = 'sname'
      end
      item
        ParamName = '子系统版本号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '负责人员工号'
        FieldName = 'sname2'
      end
      item
        ParamName = '联系电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '联系地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '备注'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '端口号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '加密方式'
        FieldName = 'lvol7'
      end
      item
        ParamName = '功能列表'
        FieldName = 'vsvarstr0'
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
    RequestType = 820001
    KCDataset = Dataset
    Left = 320
    Top = 26
  end
  object cpChangeSubSystemInfo: TKCWVProcessor
    ID = '子系统设置.修改'
    InputBindings = <
      item
        ParamName = '子系统标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '子系统名称'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '子系统类别'
        FieldName = 'lvol1'
      end
      item
        ParamName = '子系统状态'
        FieldName = 'lvol2'
      end
      item
        ParamName = '子系统所在区域'
        FieldName = 'lvol3'
      end
      item
        ParamName = '工作站'
        FieldName = 'lvol4'
      end
      item
        ParamName = '网络地址'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = 'sname'
      end
      item
        ParamName = '前次时钟同步时间'
        FieldName = 'spager'
      end
      item
        ParamName = '子系统版本号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '负责人员工号'
        FieldName = 'sname2'
      end
      item
        ParamName = '联系电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '联系地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '备注'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '端口号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '加密方式'
        FieldName = 'lvol7'
      end
      item
        ParamName = '功能列表'
        FieldName = 'vsvarstr0'
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
    RequestType = 820002
    KCDataset = Dataset
    Left = 320
    Top = 74
  end
  object cpDelSubSystemInfo: TKCWVProcessor
    ID = '子系统设置.删除'
    InputBindings = <
      item
        ParamName = '子系统标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '子系统名称'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '子系统类别'
        FieldName = 'lvol1'
      end
      item
        ParamName = '子系统状态'
        FieldName = 'lvol2'
      end
      item
        ParamName = '子系统所在区域'
        FieldName = 'lvol3'
      end
      item
        ParamName = '工作站'
        FieldName = 'lvol4'
      end
      item
        ParamName = '网络地址'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = 'sname'
      end
      item
        ParamName = '前次时钟同步时间'
        FieldName = 'spager'
      end
      item
        ParamName = '子系统版本号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '负责人员工号'
        FieldName = 'sname2'
      end
      item
        ParamName = '联系电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '联系地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '备注'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '端口号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '加密方式'
        FieldName = 'lvol7'
      end
      item
        ParamName = '功能列表'
        FieldName = 'vsvarstr0'
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
    RequestType = 820003
    KCDataset = Dataset
    Left = 320
    Top = 122
  end
  object cqQuerySubSystemByKey: TKCWVQuery
    ID = '子系统主键查询'
    InputBindings = <
      item
        ParamName = '子系统标识'
        FieldName = 'lvol0'
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
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 820005
    Left = 320
    Top = 168
  end
  object cqQueryEquipmentByKey: TKCWVQuery
    ID = '设备关键字查询'
    InputBindings = <
      item
        ParamName = '设备标识'
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
    RequestType = 820105
    Left = 224
    Top = 197
  end
  object cqQueryEquipmentByOther: TKCWVQuery
    ID = '设备非关键字查询'
    InputBindings = <
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '三九设备注册号'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '设备物理ID'
        FieldName = 'sphone3'
      end
      item
        ParamName = '机号'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '机型代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '上级设备物理ID'
        FieldName = 'sphone2'
      end
      item
        ParamName = '设备状态'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '设备物理型号'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '设备所在区域'
        FieldName = 'lserial1'
        DefaultValue = 0
      end
      item
        ParamName = '设备标识'
        FieldName = 'sserial0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_auth'
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
    Left = 224
    Top = 149
  end
  object cpAddEquipmentInfo: TKCWVProcessor
    ID = '设备信息设置.增加'
    InputBindings = <
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备物理型号'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '机型代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '设备用途'
        FieldName = 'damt5'
      end
      item
        ParamName = '上级设备物理号'
        FieldName = 'damt6'
      end
      item
        ParamName = '设备物理号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '设备所在区域'
        FieldName = 'lserial1'
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
      end
      item
        ParamName = '通信地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '是否支持科目收费'
        FieldName = 'damt4'
      end
      item
        ParamName = '服务器端口号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '服务器端口总数'
        FieldName = 'lvol2'
      end
      item
        ParamName = '机号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '通讯类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '通讯端口'
        FieldName = 'sbank_code2'
      end
      item
        ParamName = '卡片结构'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
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
    RequestType = 820101
    KCDataset = Dataset
    Left = 224
    Top = 5
  end
  object cpChangeEquipmenInfo: TKCWVProcessor
    ID = '设备信息设置.修改'
    InputBindings = <
      item
        ParamName = '设备标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备物理型号'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '机型代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '设备用途'
        FieldName = 'damt5'
      end
      item
        ParamName = '上级设备物理号'
        FieldName = 'damt6'
      end
      item
        ParamName = '设备物理号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '设备所在区域'
        FieldName = 'lserial1'
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
      end
      item
        ParamName = '通信地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '是否支持科目收费'
        FieldName = 'damt4'
      end
      item
        ParamName = '服务器端口号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '服务器端口总数'
        FieldName = 'lvol2'
      end
      item
        ParamName = '机号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '通讯类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '通讯端口'
        FieldName = 'sbank_code2'
      end
      item
        ParamName = '卡片结构'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
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
    RequestType = 820102
    KCDataset = Dataset
    Left = 224
    Top = 53
  end
  object cpDelEquipmentInfo: TKCWVProcessor
    ID = '设备信息设置.删除'
    InputBindings = <
      item
        ParamName = '设备标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备物理型号'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '机型代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '设备用途'
        FieldName = 'damt5'
      end
      item
        ParamName = '上级设备物理号'
        FieldName = 'damt6'
      end
      item
        ParamName = '设备物理号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '设备所在区域'
        FieldName = 'lserial1'
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
      end
      item
        ParamName = '通信地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '是否支持科目收费'
        FieldName = 'damt4'
      end
      item
        ParamName = '服务器端口号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '服务器端口总数'
        FieldName = 'lvol2'
      end
      item
        ParamName = '机号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '通讯端口'
        FieldName = 'sbank_code2'
      end
      item
        ParamName = '通讯类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '卡片结构'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
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
    RequestType = 820103
    KCDataset = Dataset
    Left = 224
    Top = 101
  end
  object cpDownMagFeePortion: TKCWVProcessor
    ID = '下传搭伙费比率'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sdate0'
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
    RequestType = 950041
    KCDataset = Dataset
    Left = 40
    Top = 104
  end
  object cpDownConsumeLimit: TKCWVProcessor
    ID = '下传大额消费限额'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '大额消费限额'
        FieldName = 'lvol4'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
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
        ParamName = '错误信息'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930010
    KCDataset = Dataset
    Left = 40
    Top = 152
  end
  object cpDownEquipClock: TKCWVProcessor
    ID = '下传设备时钟'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
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
        ParamName = '下传时钟'
        FieldName = 'sserial0'
      end
      item
        ParamName = '错误信息'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930001
    KCDataset = Dataset
    Left = 40
    Top = 296
  end
  object cpUpEquipClock: TKCWVProcessor
    ID = '上传设备时钟'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '上传时钟'
        FieldName = 'sserial0'
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
        ParamName = '错误信息'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930002
    KCDataset = Dataset
    Left = 40
    Top = 344
  end
  object cqQueryEquipmentCanEdit: TKCWVQuery
    ID = '可编辑设备查询'
    InputBindings = <
      item
        ParamName = '机型代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '设备物理型号'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
      end
      item
        ParamName = '设备所在区域'
        FieldName = 'lserial1'
      end
      item
        ParamName = '设备状态'
        FieldName = 'lvol4'
      end
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备物理ID'
        FieldName = 'sphone3'
      end
      item
        ParamName = '上级设备物理ID'
        FieldName = 'sphone2'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '设备标识'
        FieldName = 'sserial0'
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
    Left = 224
    Top = 245
  end
  object cpCollectConsumeSer: TKCWVProcessor
    ID = '采集历史消费流水'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '收数起始流水号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '收数结束流水号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
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
    RequestType = 930016
    KCDataset = Dataset
    Left = 40
    Top = 248
  end
  object cpCollectAddMoneySer: TKCWVProcessor
    ID = '采集现金充值流水'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '收数起始流水号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '收数结束流水号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
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
    RequestType = 930018
    KCDataset = Dataset
    Left = 40
    Top = 200
  end
  object cpEquipCompellOut: TKCWVProcessor
    ID = '强制前置机和设备签退'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
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
        ParamName = '错误信息'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930060
    KCDataset = Dataset
    Left = 40
    Top = 392
  end
  object cpSetHisSumMoney: TKCWVProcessor
    ID = '设置消费累计限额'
    InputBindings = <
      item
        ParamName = '终端设备ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '累计消费限额'
        FieldName = 'lvol4'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
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
        ParamName = '错误信息'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930061
    KCDataset = Dataset
    Left = 40
    Top = 8
  end
  object cqQueryEquipmentTree: TKCWVQuery
    ID = '可编辑设备查询2'
    InputBindings = <
      item
        ParamName = '机型代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '设备物理型号'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
      end
      item
        ParamName = '设备所在区域'
        FieldName = 'lserial1'
      end
      item
        ParamName = '设备状态'
        FieldName = 'lvol4'
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
    RequestType = 820108
    Left = 224
    Top = 293
  end
  object cqsubSendListQuery: TKCWVQuery
    ID = '子系统名单发送情况'
    InputBindings = <
      item
        ParamName = '子系统'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '学工号'
        FieldName = 'sname'
      end
      item
        ParamName = '名单类型'
        FieldName = 'lvol2'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '状态'
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
    RequestType = 940005
    Left = 320
    Top = 258
  end
  object cqsetEquipPara2: TKCWVQuery
    ID = '设备查询'
    InputBindings = <
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '上级设备'
        FieldName = 'sphone2'
      end
      item
        ParamName = '设备机型'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '子系统'
        FieldName = 'lserial0'
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
    Top = 170
  end
  object cpCustomerKindByKey: TKCWVQuery
    ID = 'querycustomerkind'
    InputBindings = <
      item
        ParamName = 'lcert_code'
        FieldName = 'lcert_code'
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
    RequestType = 820502
    Left = 128
    Top = 26
  end
  object cpEquGroup: TKCWVProcessor
    ID = 'EquGroup'
    InputBindings = <
      item
        ParamName = '分组权限'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
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
        ParamName = '错误信息'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 950040
    KCDataset = Dataset
    Left = 40
    Top = 440
  end
  object cqsetCommCfParam: TKCWVQuery
    ID = '通用前置参数查询'
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
        ParamName = '标志'
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
    RequestType = 847232
    Left = 128
    Top = 74
  end
  object cpsetCommCfParam: TKCWVProcessor
    ID = '通用前置参数设置'
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
        ParamName = '前置编号'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '前置机名'
        FieldName = 'semail'
      end
      item
        ParamName = '心跳时间间隔'
        FieldName = 'lvol0'
      end
      item
        ParamName = '心跳接阀值'
        FieldName = 'lvol1'
      end
      item
        ParamName = '心跳应答功能号'
        FieldName = 'lvol2'
      end
      item
        ParamName = '指令调度队列号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '指令应答功能号'
        FieldName = 'lvol9'
      end
      item
        ParamName = '指令执行超时时间'
        FieldName = 'lvol4'
      end
      item
        ParamName = '指令获取时间间隔'
        FieldName = 'lvol8'
      end
      item
        ParamName = '设备种类标志'
        FieldName = 'sdate0'
      end
      item
        ParamName = '设备档案请求功能号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '设备联机模式'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '流水采集频率'
        FieldName = 'lvol5'
      end
      item
        ParamName = '指令队列上限'
        FieldName = 'lvol7'
      end
      item
        ParamName = '工作密钥'
        FieldName = 'sname2'
      end
      item
        ParamName = '标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '节点号'
        FieldName = 'lvol10'
      end
      item
        ParamName = '平台IP'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '端口'
        FieldName = 'lvol12'
      end
      item
        ParamName = '功能号'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '轮询间隔时间'
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
    RequestType = 847232
    KCDataset = Dataset
    Left = 128
    Top = 122
  end
  object KCPGateOpen: TKCWVProcessor
    ID = '门禁常开设置'
    InputBindings = <
      item
        ParamName = '设备编号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '终端设备ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '标志'
        FieldName = 'lvol0'
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
    RequestType = 950004
    KCDataset = Dataset
    Left = 40
    Top = 56
  end
  object cqDevInfoImp: TKCWVProcessor
    ID = '设备信息导入'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '序号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '是否传送完毕'
        FieldName = 'scust_type'
      end
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备类型'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '设备机型'
        FieldName = 'sserial1'
      end
      item
        ParamName = '设备用途'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '所在区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '上级设备'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
      end
      item
        ParamName = '支持科目收费'
        FieldName = 'Lvol6'
      end
      item
        ParamName = '卡片结构'
        FieldName = 'saddr'
      end
      item
        ParamName = '服务器端口号'
        FieldName = 'Lvol8'
      end
      item
        ParamName = '设备机号'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'IP地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '通讯类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '服务器端口数'
        FieldName = 'lvol2'
      end
      item
        ParamName = '通讯端口'
        FieldName = 'lvol3'
      end
      item
        ParamName = '操作标志'
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
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end>
    RequestType = 820110
    KCDataset = Dataset
    Left = 128
    Top = 221
  end
  object cqdevImpManage: TKCWVQuery
    ID = '设备信息查询'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '操作标志'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '设备类型'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '设备机型'
        FieldName = 'sserial1'
      end
      item
        ParamName = '设备用途'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
      end
      item
        ParamName = '所在区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '卡片结构'
        FieldName = 'saddr'
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
    RequestType = 820110
    Left = 128
    Top = 266
  end
  object cpdevImpManage: TKCWVProcessor
    ID = '设备导入管理'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '导入顺序号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '设备名称'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '设备类型'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '设备机型'
        FieldName = 'sserial1'
      end
      item
        ParamName = '设备用途'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '所属子系统'
        FieldName = 'lserial0'
      end
      item
        ParamName = '上级设备编号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '所在区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '卡片结构'
        FieldName = 'saddr'
      end
      item
        ParamName = '服务器端口号'
        FieldName = 'lvol8'
      end
      item
        ParamName = '服务器端口总数'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '是否支持科目收费'
        FieldName = 'Lvol6'
      end
      item
        ParamName = '设备机号'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'IP地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '通讯方式'
        FieldName = 'lvol5'
      end
      item
        ParamName = '通讯端口号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '操作标志'
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
    RequestType = 820110
    KCDataset = Dataset
    Left = 128
    Top = 314
  end
  object cqDevBusiImpCheck: TKCWVProcessor
    ID = '设备导入审核'
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
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '导入顺序号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '操作标志'
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
    RequestType = 820110
    KCDataset = Dataset
    Left = 128
    Top = 362
  end
  object cpPatchdel: TKCWVProcessor
    ID = '设备批量删除'
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
    RequestType = 820110
    KCDataset = Dataset
    Left = 224
    Top = 346
  end
  object cpFeeType: TKCWVProcessor
    ID = '下传费率设置'
    InputBindings = <
      item
        ParamName = '设备编号'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '标志'
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
    RequestType = 950044
    KCDataset = Dataset
    Left = 128
    Top = 408
  end
  object KCChange: TKCWVProcessor
    ID = '更换设备'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '老设备'
        FieldName = 'lvol3'
      end
      item
        ParamName = '新设备'
        FieldName = 'lvol4'
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
    RequestType = 950107
    KCDataset = Dataset
    Left = 320
    Top = 306
  end
end
