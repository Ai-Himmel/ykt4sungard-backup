inherited dmGateBanDef: TdmGateBanDef
  OldCreateOrder = True
  Left = 380
  Top = 122
  Height = 554
  Width = 639
  object cqsetGateHoliday: TWVCommandTypeInfo
    ID = '节假日查询'
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
        ParamName = '节假日编号'
      end
      item
        ParamName = '节假日名'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 32
    Top = 50
  end
  object cpsetGateHoliday: TWVCommandTypeInfo
    ID = '节假日设置'
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
        ParamName = '节假日编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '节假日名'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 32
    Top = 98
  end
  object cqsetGateTime: TWVCommandTypeInfo
    ID = '时间段参数查询'
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
        ParamName = '时间段名称'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '结束时间'
      end
      item
        ParamName = '标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易类型'
      end>
    Left = 32
    Top = 338
  end
  object cpsetGateTime: TWVCommandTypeInfo
    ID = '时间段参数设置'
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
        ParamName = '时间段名称'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '结束时间'
      end
      item
        ParamName = '标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易类型'
      end>
    Left = 32
    Top = 386
  end
  object cqsetDayTimeGroup: TWVCommandTypeInfo
    ID = '时间段组每日设置'
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
        ParamName = '时间段组编号'
      end
      item
        ParamName = '时间段'
      end
      item
        ParamName = '时间段一'
      end
      item
        ParamName = '时间段二'
      end
      item
        ParamName = '时间段三'
      end
      item
        ParamName = '时间段四'
      end
      item
        ParamName = '时间段五'
      end
      item
        ParamName = '时间段六'
      end
      item
        ParamName = '时间段七'
      end
      item
        ParamName = '时间段八'
      end
      item
        ParamName = '结束标志'
      end>
    Left = 112
    Top = 322
  end
  object cqsetTimeGroup: TWVCommandTypeInfo
    ID = '时间段组查询'
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
        ParamName = '时间段名称'
      end
      item
        ParamName = '标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易类型'
      end>
    Left = 32
    Top = 242
  end
  object cpsetTimeGroup: TWVCommandTypeInfo
    ID = '时间段组设置'
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
        ParamName = '时间段名称'
      end
      item
        ParamName = '标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '时间段一'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '时间段二'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '时间段三'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '时间段四'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '时间段五'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '时间段六'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '时间段七'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '时间段八'
        ParamDataType = kdtInteger
      end>
    Left = 32
    Top = 290
  end
  object cqqueryTimeGroupDetail: TWVCommandTypeInfo
    ID = '时间段组详细情况查询'
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
        ParamName = '时间段组编号'
      end
      item
        ParamName = '星期'
        ParamDataType = kdtInteger
      end>
    Left = 112
    Top = 370
  end
  object WVholidayDetailSet: TWVCommandTypeInfo
    ID = '节假日详细设置'
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
        ParamName = '节假日编号'
      end
      item
        ParamName = '节假日日期'
      end
      item
        ParamName = '时间段组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '标志'
      end>
    Left = 112
    Top = 418
  end
  object cqsetGateGroup: TWVCommandTypeInfo
    ID = '门禁组查询'
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
        ParamName = '门禁组编号'
      end
      item
        ParamName = '门禁组名称'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 32
    Top = 146
  end
  object cpsetGateGroup: TWVCommandTypeInfo
    ID = '门禁组设置'
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
        ParamName = '门禁组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '门禁组名称'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 32
    Top = 194
  end
  object cqsetGateGroupForGate: TWVCommandTypeInfo
    ID = '门禁组门禁机查询'
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
        ParamName = '门禁组编号'
      end
      item
        ParamName = '门禁机编号'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 112
    Top = 130
  end
  object cpsetGateGroupForGate: TWVCommandTypeInfo
    ID = '门禁组门禁机设置'
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
        ParamName = '门禁组编号'
      end
      item
        ParamName = '门禁机编号'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 112
    Top = 178
  end
  object cqsetGateOperLimit: TWVCommandTypeInfo
    ID = '门禁机操作员权限查询'
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
        ParamName = '门禁机编号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 112
    Top = 226
  end
  object cpsetGateOperLimit: TWVCommandTypeInfo
    ID = '门禁机操作员权限设置'
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
        ParamName = '门禁机编号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 112
    Top = 274
  end
  object cqsetGateGroupOperLimit: TWVCommandTypeInfo
    ID = '门禁组操作员权限查询'
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
        ParamName = '门禁组名称'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 112
    Top = 34
  end
  object cpsetGateGroupOperLimit: TWVCommandTypeInfo
    ID = '门禁组操作员权限设置'
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
        ParamName = '门禁组编号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 112
    Top = 82
  end
  object cqQueryEquipmentByOther: TWVCommandTypeInfo
    ID = '设备查询门禁系统'
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
        ParamDataType = kdtInteger
      end
      item
        ParamName = '机型代码'
      end
      item
        ParamName = '上级设备物理ID'
      end
      item
        ParamName = '设备状态'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备物理型号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属子系统'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '负责人员工号'
      end>
    Left = 208
    Top = 52
  end
  object WVHolidayQuery: TWVCommandTypeInfo
    ID = '节假日详细查询'
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
        ParamName = '节假日编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '节假日名称'
      end>
    Left = 208
    Top = 100
  end
  object cqsetWeekTimeGroup: TWVCommandTypeInfo
    ID = '周时间段查询'
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
        ParamName = '时间段组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '时间段组名称'
      end
      item
        ParamName = '周一组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '周二组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '周三组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '周四组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '周五组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '周六组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '周日组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易类型'
      end>
    Left = 208
    Top = 154
  end
  object cpsetWeekTimeGroup: TWVCommandTypeInfo
    ID = '周时间段参数设置'
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
        ParamName = '时间段组编号'
      end
      item
        ParamName = '时间段组名'
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '周一组编号'
      end
      item
        ParamName = '周二组编号'
      end
      item
        ParamName = '周三组编号'
      end
      item
        ParamName = '周四组编号'
      end
      item
        ParamName = '周五组编号'
      end
      item
        ParamName = '周六组编号'
      end
      item
        ParamName = '周日组编号'
      end>
    Left = 208
    Top = 202
  end
  object cqallotCustGate: TWVCommandTypeInfo
    ID = '门禁人员名单分配'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回标志'
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
        ParamName = '周时间段'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '节假日'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '门禁编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '标志'
        ParamDataType = kdtInteger
      end>
    Left = 208
    Top = 250
  end
  object cqGateListQuery: TWVCommandTypeInfo
    ID = '门禁人员名单查询'
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
        ParamName = '门禁机名称'
      end
      item
        ParamName = '门禁设备编号'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '院系代码'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '客户类型'
      end
      item
        ParamName = '收费类型'
      end
      item
        ParamName = '名单类型'
      end
      item
        ParamName = '班级'
      end
      item
        ParamName = '专业代码'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '增删标志'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 208
    Top = 298
  end
  object cqGateListDelete: TWVCommandTypeInfo
    ID = '门禁人员名单删除'
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
        ParamName = '客户号'
      end
      item
        ParamName = '门禁编号'
      end
      item
        ParamName = '时间周'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 208
    Top = 346
  end
  object WVGateGroupOper: TWVCommandTypeInfo
    ID = '门禁组操作员查询'
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
        ParamName = '门禁组编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '门禁组名称'
      end>
    Left = 208
    Top = 394
  end
  object cqgateSerialDetailQuery: TWVCommandTypeInfo
    ID = '门禁流水查询'
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
        ParamName = '客户号'
      end
      item
        ParamName = '交易卡号'
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '起始日期'
      end
      item
        ParamName = '起始时间'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '结束时间'
      end
      item
        ParamName = '设备标识'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '部门'
      end
      item
        ParamName = '事件'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '设备机型'
      end>
    Left = 304
    Top = 10
  end
  object cqattendDetailQuery: TWVCommandTypeInfo
    ID = '考勤流水查询'
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
        ParamName = '部门名称'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '姓名'
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
    Left = 304
    Top = 114
  end
  object cqattendDetailstat: TWVCommandTypeInfo
    ID = '考勤信息统计'
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
        ParamName = '部门名称'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '姓名'
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
    Left = 304
    Top = 66
  end
  object cqSetGateOpenAlong: TWVCommandTypeInfo
    ID = '常开时间段设置'
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
        ParamName = '门禁机编号'
      end
      item
        ParamName = '时间周编号'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 304
    Top = 170
  end
  object cqQueryGateOpenAlong: TWVCommandTypeInfo
    ID = '常开时间段查询'
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
        ParamName = '门禁机编号'
      end
      item
        ParamName = '时间周编号'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 304
    Top = 218
  end
  object cqgatebansetinfo: TWVCommandTypeInfo
    ID = '门禁对接参数设置'
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
        ParamName = '操作码'
      end
      item
        ParamName = 'oper.大楼编号'
      end
      item
        ParamName = 'oper.大楼名称'
      end
      item
        ParamName = 'oper.门禁组'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = 'oper.备注'
      end>
    Left = 304
    Top = 266
  end
  object cqSetGateTimeWeek: TWVCommandTypeInfo
    ID = '门禁时间周设置'
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
        ParamName = '设备编号'
      end
      item
        ParamName = '控制器编号'
      end
      item
        ParamName = '时间周编号'
      end
      item
        ParamName = '机型代码'
      end>
    Left = 304
    Top = 314
  end
  object cqGateTimeWeekManager: TWVCommandTypeInfo
    ID = '门禁时间周管理'
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
        ParamName = '操作类别'
      end
      item
        ParamName = '控制器编号'
      end
      item
        ParamName = '控制器名称'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '设备物理型号'
      end
      item
        ParamName = '设备机型'
      end
      item
        ParamName = '所属区域'
      end
      item
        ParamName = '时间周编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '时间周名称'
      end
      item
        ParamName = '子系统'
      end>
    Left = 304
    Top = 362
  end
  object cqGateTimeWeekDel: TWVCommandTypeInfo
    ID = '门禁时间周删除'
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
        ParamName = '操作类别'
      end
      item
        ParamName = '控制器编号'
      end
      item
        ParamName = '设备编号'
      end
      item
        ParamName = '时间周编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 304
    Top = 410
  end
  object cqQueryCustomerByOther: TWVCommandTypeInfo
    ID = '门禁客户信息查询'
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
        ParamName = '联系地址'
      end
      item
        ParamName = '客户所在区域'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '联系人单位名称'
      end
      item
        ParamName = '联系人单位号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户名称'
      end
      item
        ParamName = '客户状态'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '联系人姓名'
      end
      item
        ParamName = '联系人身份证号'
      end
      item
        ParamName = '联系人民族'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '联系人性别'
      end
      item
        ParamName = '联系人学工号'
      end
      item
        ParamName = '联系电话'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '班级'
      end
      item
        ParamName = '结束学工号'
      end>
    Left = 392
    Top = 26
  end
  object cqSetGateMgrOpen: TWVCommandTypeInfo
    ID = '管理卡常开卡设置'
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
        ParamName = '设备号'
      end
      item
        ParamName = '卡用途'
      end
      item
        ParamName = '操作类别'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 392
    Top = 74
  end
  object cqQGateMgrOpen: TWVCommandTypeInfo
    ID = '管理卡常开卡查询'
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
      end
      item
        ParamName = '设备号'
      end
      item
        ParamName = '卡用途'
      end
      item
        ParamName = '操作类别'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 392
    Top = 122
  end
end
