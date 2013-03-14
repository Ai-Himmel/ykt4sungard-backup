inherited dmSubSystemDef: TdmSubSystemDef
  OldCreateOrder = True
  Left = 317
  Top = 100
  Height = 606
  Width = 635
  object cqQuerySubSystemByOther: TWVCommandTypeInfo
    ID = '子系统非主键查询'
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
        ParamName = '子系统名称'
      end
      item
        ParamName = '子系统类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统状态'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '网络地址'
      end
      item
        ParamName = '网卡物理地址'
      end
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end>
    Left = 312
    Top = 220
  end
  object cpAddSubSystemInfo: TWVCommandTypeInfo
    ID = '子系统设置.增加'
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
        ParamName = '子系统名称'
      end
      item
        ParamName = '子系统类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '工作站'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '网络地址'
      end
      item
        ParamName = '网卡物理地址'
      end
      item
        ParamName = '子系统版本号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '负责人员工号'
      end
      item
        ParamName = '联系电话'
      end
      item
        ParamName = '联系地址'
      end
      item
        ParamName = '备注'
      end
      item
        ParamName = '端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '加密方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '功能列表'
      end>
    Left = 312
    Top = 28
  end
  object cpChangeSubSystemInfo: TWVCommandTypeInfo
    ID = '子系统设置.修改'
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
        ParamName = '子系统标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统名称'
      end
      item
        ParamName = '子系统类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统状态'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '工作站'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '网络地址'
      end
      item
        ParamName = '网卡物理地址'
      end
      item
        ParamName = '前次时钟同步时间'
      end
      item
        ParamName = '子系统版本号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '负责人员工号'
      end
      item
        ParamName = '联系电话'
      end
      item
        ParamName = '联系地址'
      end
      item
        ParamName = '备注'
      end
      item
        ParamName = '加密方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '功能列表'
      end>
    Left = 312
    Top = 76
  end
  object cqQuerySubSystemByKey: TWVCommandTypeInfo
    ID = '子系统主键查询'
    Params = <
      item
        ParamName = '子系统标识'
        ParamDataType = kdtInteger
      end
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
    Left = 312
    Top = 170
  end
  object cqQueryEquipmentByKey: TWVCommandTypeInfo
    ID = '设备关键字查询'
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
        ParamName = '设备标识'
        ParamDataType = kdtInteger
      end>
    Left = 208
    Top = 196
  end
  object cpAddEquipmentInfo: TWVCommandTypeInfo
    ID = '设备信息设置.增加'
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
        ParamName = '设备名称'
      end
      item
        ParamName = '设备物理型号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '机型代码'
      end
      item
        ParamName = '设备用途'
      end
      item
        ParamName = '上级设备物理号'
      end
      item
        ParamName = '设备物理号'
      end
      item
        ParamName = '设备所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通信地址'
      end
      item
        ParamName = '是否支持科目收费'
      end
      item
        ParamName = '服务器端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '服务器端口总数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '机号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通讯类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通讯端口'
      end
      item
        ParamName = '卡片结构'
      end
      item
        ParamName = '备注'
      end>
    Left = 208
    Top = 4
  end
  object cpChangeEquipmentInfo: TWVCommandTypeInfo
    ID = '设备信息设置.修改'
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
        ParamName = '设备标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '设备物理型号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '机型代码'
      end
      item
        ParamName = '设备用途'
      end
      item
        ParamName = '上级设备物理号'
      end
      item
        ParamName = '设备物理号'
      end
      item
        ParamName = '设备所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通信地址'
      end
      item
        ParamName = '是否支持科目收费'
      end
      item
        ParamName = '服务器端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '服务器端口总数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '机号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通讯端口'
      end
      item
        ParamName = '通讯类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡片结构'
      end
      item
        ParamName = '备注'
      end>
    Left = 208
    Top = 52
  end
  object cpDelEquipmentInfo: TWVCommandTypeInfo
    ID = '设备信息设置.删除'
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
        ParamName = '设备标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '设备物理型号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '机型代码'
      end
      item
        ParamName = '设备用途'
      end
      item
        ParamName = '上级设备物理号'
      end
      item
        ParamName = '设备物理号'
      end
      item
        ParamName = '设备所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通信地址'
      end
      item
        ParamName = '是否支持科目收费'
      end
      item
        ParamName = '服务器端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '服务器端口总数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '机号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通讯端口'
      end
      item
        ParamName = '通讯类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡片结构'
      end
      item
        ParamName = '备注'
      end>
    Left = 208
    Top = 100
  end
  object cqQueryEquipmentByOther: TWVCommandTypeInfo
    ID = '设备非关键字查询'
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
        ParamName = '设备名称'
      end
      item
        ParamName = '三九设备注册号'
      end
      item
        ParamName = '设备物理ID'
      end
      item
        ParamName = '机号'
      end
      item
        ParamName = '机型代码'
      end
      item
        ParamName = '上级设备物理ID'
      end
      item
        ParamName = '设备状态'
      end
      item
        ParamName = '设备物理型号'
      end
      item
        ParamName = '所属子系统'
      end
      item
        ParamName = '设备所在区域'
      end
      item
        ParamName = '设备标识'
      end
      item
        ParamName = '导入批次号'
      end>
    Left = 208
    Top = 148
  end
  object cqDownMagFeePortion: TWVCommandTypeInfo
    ID = '下传搭伙费比率'
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
        ParamName = '终端设备ID'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备物理编号'
      end>
    Left = 40
    Top = 106
  end
  object cqDownConsumeLimit: TWVCommandTypeInfo
    ID = '下传大额消费限额'
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
        ParamName = '终端设备ID'
      end
      item
        ParamName = '大额消费限额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '错误信息'
        ParamType = ptOutput
      end
      item
        ParamName = '设备编号'
      end>
    Left = 40
    Top = 154
  end
  object cpDelSubSystemInfo: TWVCommandTypeInfo
    ID = '子系统设置.删除'
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
        ParamName = '子系统标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统名称'
      end
      item
        ParamName = '子系统类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统状态'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '子系统所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '工作站'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '网络地址'
      end
      item
        ParamName = '网卡物理地址'
      end
      item
        ParamName = '前次时钟同步时间'
      end
      item
        ParamName = '子系统版本号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '负责人员工号'
      end
      item
        ParamName = '联系电话'
      end
      item
        ParamName = '联系地址'
      end
      item
        ParamName = '备注'
      end
      item
        ParamName = '端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '加密方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '功能列表'
      end>
    Left = 312
    Top = 122
  end
  object cpDownEquipClock: TWVCommandTypeInfo
    ID = '下传设备时钟'
    Params = <
      item
        ParamName = '终端设备ID'
      end
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
        ParamName = '下传时钟'
        ParamType = ptOutput
      end
      item
        ParamName = '错误信息'
        ParamType = ptOutput
      end
      item
        ParamName = '设备编号'
      end>
    Left = 41
    Top = 344
  end
  object cpUpEquipClock: TWVCommandTypeInfo
    ID = '上传设备时钟'
    Params = <
      item
        ParamName = '终端设备ID'
      end
      item
        ParamName = '上传时钟'
        ParamType = ptOutput
      end
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
        ParamName = '错误信息'
        ParamType = ptOutput
      end
      item
        ParamName = '设备编号'
      end>
    Left = 42
    Top = 392
  end
  object cqQueryEquipmentCanEdit: TWVCommandTypeInfo
    ID = '可编辑设备查询'
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
        ParamName = '机型代码'
      end
      item
        ParamName = '设备物理型号'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '设备所在区域'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '设备状态'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '收费方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '设备物理ID'
      end
      item
        ParamName = '上级设备物理ID'
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '设备标识'
      end>
    Left = 208
    Top = 244
  end
  object cpCollectConsumeSer: TWVCommandTypeInfo
    ID = '采集历史消费流水'
    Params = <
      item
        ParamName = '终端设备ID'
      end
      item
        ParamName = '收数起始流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收数结束流水号'
        ParamDataType = kdtInteger
      end
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
        ParamName = '设备编号'
      end>
    Left = 40
    Top = 248
  end
  object cpCollectAddMoneySer: TWVCommandTypeInfo
    ID = '采集现金充值流水'
    Params = <
      item
        ParamName = '终端设备ID'
      end
      item
        ParamName = '收数起始流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收数结束流水号'
        ParamDataType = kdtInteger
      end
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
        ParamName = '设备编号'
      end>
    Left = 40
    Top = 200
  end
  object cpEquipCompellOut: TWVCommandTypeInfo
    ID = '强制前置机和设备签退'
    Params = <
      item
        ParamName = '终端设备ID'
      end
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
        ParamName = '错误信息'
        ParamType = ptOutput
      end
      item
        ParamName = '设备编号'
      end>
    Left = 40
    Top = 296
  end
  object cpSetHisSumMoney: TWVCommandTypeInfo
    ID = '设置消费累计限额'
    Params = <
      item
        ParamName = '终端设备ID'
      end
      item
        ParamName = '累计消费限额'
        ParamDataType = kdtInteger
      end
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
        ParamName = '错误信息'
        ParamType = ptOutput
      end
      item
        ParamName = '设备编号'
      end>
    Left = 40
    Top = 8
  end
  object cqQueryEquipmentTree: TWVCommandTypeInfo
    ID = '可编辑设备查询2'
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
        ParamName = '机型代码'
      end
      item
        ParamName = '设备物理型号'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '设备所在区域'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '设备状态'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '收费方式'
        ParamDataType = kdtInteger
      end>
    Left = 208
    Top = 292
  end
  object cqsubSendListQuery: TWVCommandTypeInfo
    ID = '子系统名单发送情况'
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
        ParamName = '子系统'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '名单类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '状态'
        ParamDataType = kdtInteger
      end>
    Left = 312
    Top = 266
  end
  object cqsetEquipPara2: TWVCommandTypeInfo
    ID = '设备查询'
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
        ParamName = '设备物理编号'
      end
      item
        ParamName = '上级设备'
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '设备机型'
      end
      item
        ParamName = '子系统'
        ParamDataType = kdtInteger
      end>
    Left = 120
    Top = 170
  end
  object cqCustomerKindByKey: TWVCommandTypeInfo
    ID = 'querycustomerkind'
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
        ParamName = 'lcert_code'
      end>
    Left = 120
    Top = 26
  end
  object cqEquGroup: TWVCommandTypeInfo
    ID = 'EquGroup'
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
        ParamName = '分组权限'
      end
      item
        ParamName = '错误信息'
        ParamType = ptOutput
      end
      item
        ParamName = '设备编号'
        ParamDataType = kdtInteger
      end>
    Left = 41
    Top = 442
  end
  object cqsetCommCfParam: TWVCommandTypeInfo
    ID = '通用前置参数查询'
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
        ParamName = '前置编号'
      end
      item
        ParamName = '心跳时间间隔'
      end
      item
        ParamName = '心跳接阀值'
      end
      item
        ParamName = '心跳应答功能号'
      end
      item
        ParamName = '指令调度队列号'
      end
      item
        ParamName = '指令应答功能号'
      end
      item
        ParamName = '指令执行超时时间'
      end
      item
        ParamName = '指令获取时间间隔'
      end
      item
        ParamName = '设备种类标志'
      end
      item
        ParamName = '设备档案请求功能号'
      end
      item
        ParamName = '设备联机模式'
      end
      item
        ParamName = '流水采集频率'
      end
      item
        ParamName = '指令队列上限'
      end
      item
        ParamName = '工作密钥'
      end
      item
        ParamName = '标志'
      end>
    Left = 120
    Top = 74
  end
  object cpsetCommCfParam: TWVCommandTypeInfo
    ID = '通用前置参数设置'
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
        ParamName = '前置编号'
      end
      item
        ParamName = '前置机名'
      end
      item
        ParamName = '心跳时间间隔'
      end
      item
        ParamName = '心跳接阀值'
      end
      item
        ParamName = '心跳应答功能号'
      end
      item
        ParamName = '指令调度队列号'
      end
      item
        ParamName = '指令应答功能号'
      end
      item
        ParamName = '指令执行超时时间'
      end
      item
        ParamName = '指令获取时间间隔'
      end
      item
        ParamName = '设备种类标志'
      end
      item
        ParamName = '设备档案请求功能号'
      end
      item
        ParamName = '设备联机模式'
      end
      item
        ParamName = '流水采集频率'
      end
      item
        ParamName = '指令队列上限'
      end
      item
        ParamName = '工作密钥'
      end
      item
        ParamName = '标志'
      end
      item
        ParamName = '节点号'
      end
      item
        ParamName = '平台IP'
      end
      item
        ParamName = '端口'
      end
      item
        ParamName = '功能号'
      end
      item
        ParamName = '轮询间隔时间'
      end>
    Left = 120
    Top = 122
  end
  object WVGateOpen: TWVCommandTypeInfo
    ID = '门禁常开设置'
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
        ParamName = '终端设备ID'
      end
      item
        ParamName = '设备编号'
      end
      item
        ParamName = '标志'
        ParamDataType = kdtInteger
      end>
    Left = 40
    Top = 58
  end
  object WVDevInfoImp: TWVCommandTypeInfo
    ID = '设备信息导入'
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
        DefaultValue = '0'
      end
      item
        ParamName = '是否传送完毕'
        DefaultValue = '0'
      end
      item
        ParamName = '设备名称'
        DefaultValue = '0'
      end
      item
        ParamName = '设备类型'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '设备机型'
      end
      item
        ParamName = '设备用途'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '所在区域'
      end
      item
        ParamName = '上级设备'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '支持科目收费'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡片结构'
      end
      item
        ParamName = '服务器端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备机号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'IP地址'
      end
      item
        ParamName = '通讯类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '服务器端口数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通讯端口'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作标志'
      end>
    Left = 120
    Top = 220
  end
  object cqdevImpManage: TWVCommandTypeInfo
    ID = '设备信息查询'
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
        ParamName = '批次号'
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备机型'
      end
      item
        ParamName = '设备用途'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所在区域'
      end
      item
        ParamName = '卡片结构'
      end>
    Left = 120
    Top = 266
  end
  object cpdevImpManage: TWVCommandTypeInfo
    ID = '设备导入管理'
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
        ParamName = '导入顺序号'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备机型'
      end
      item
        ParamName = '设备用途'
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '上级设备编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所在区域'
      end
      item
        ParamName = '卡片结构'
      end
      item
        ParamName = '服务器端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '服务器端口总数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否支持科目收费'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备机号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'IP地址'
      end
      item
        ParamName = '通讯方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '通讯端口号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作标志'
      end>
    Left = 120
    Top = 314
  end
  object WVdevBusiImpCheck: TWVCommandTypeInfo
    ID = '设备导入审核'
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
        ParamName = '导入批次号'
      end
      item
        ParamName = '导入顺序号'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 120
    Top = 362
  end
  object cqPatchDel: TWVCommandTypeInfo
    ID = '设备批量删除'
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
    Left = 208
    Top = 338
  end
  object cqFeeType: TWVCommandTypeInfo
    ID = '下传费率设置'
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
        ParamName = '设备编号'
      end
      item
        ParamName = '标志'
        ParamDataType = kdtInteger
      end>
    Left = 120
    Top = 410
  end
  object WVchange: TWVCommandTypeInfo
    ID = '更换设备'
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
        ParamName = '老设备'
      end
      item
        ParamName = '新设备'
      end>
    Left = 312
    Top = 314
  end
end
