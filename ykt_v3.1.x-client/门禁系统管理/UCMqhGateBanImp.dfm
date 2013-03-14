inherited dmGateBanImp: TdmGateBanImp
  OldCreateOrder = True
  Left = 348
  Top = 126
  Height = 565
  Width = 696
  object cqsetGateHoliday: TKCWVQuery
    ID = '节假日查询'
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
        ParamName = '节假日编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '节假日名'
        FieldName = 'semail'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848255
    Left = 24
    Top = 66
  end
  object cpsetGateHoliday: TKCWVProcessor
    ID = '节假日设置'
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
        ParamName = '节假日编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '节假日名'
        FieldName = 'semail'
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
      end
      item
        ParamName = '节假日编号'
        FieldName = 'lvol0'
      end>
    RequestType = 848255
    KCDataset = Dataset
    Left = 24
    Top = 114
  end
  object cqsetGateTime: TKCWVQuery
    ID = '时间段参数查询'
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
        ParamName = '时间段名称'
        FieldName = 'semail'
      end
      item
        ParamName = '开始时间'
        FieldName = 'sdate0'
      end
      item
        ParamName = '结束时间'
        FieldName = 'sdate1'
      end
      item
        ParamName = '标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848250
    Left = 24
    Top = 354
  end
  object cpsetGateTime: TKCWVProcessor
    ID = '时间段参数设置'
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
        ParamName = '时间段名称'
        FieldName = 'semail'
      end
      item
        ParamName = '开始时间'
        FieldName = 'sdate0'
      end
      item
        ParamName = '结束时间'
        FieldName = 'sdate1'
      end
      item
        ParamName = '标识'
        FieldName = 'lvol0'
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
    RequestType = 848250
    KCDataset = Dataset
    Left = 24
    Top = 402
  end
  object cqsetDayTimeGroup: TKCWVQuery
    ID = '时间段组每日设置'
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
        ParamName = '时间段组编号'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '时间段'
        FieldName = 'lvol0'
      end
      item
        ParamName = '时间段一'
        FieldName = 'lvol1'
      end
      item
        ParamName = '时间段二'
        FieldName = 'lvol2'
      end
      item
        ParamName = '时间段三'
        FieldName = 'lvol3'
      end
      item
        ParamName = '时间段四'
        FieldName = 'lvol4'
      end
      item
        ParamName = '时间段五'
        FieldName = 'lvol5'
      end
      item
        ParamName = '时间段六'
        FieldName = 'lvol6'
      end
      item
        ParamName = '时间段七'
        FieldName = 'lvol7'
      end
      item
        ParamName = '时间段八'
        FieldName = 'lvol8'
      end
      item
        ParamName = '结束标志'
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
    RequestType = 848252
    Left = 104
    Top = 338
  end
  object cqsetTimeGroup: TKCWVQuery
    ID = '时间段组查询'
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
        ParamName = '时间段名称'
        FieldName = 'semail'
      end
      item
        ParamName = '标识'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848252
    Left = 24
    Top = 258
  end
  object cpsetTimeGroup: TKCWVProcessor
    ID = '时间段组设置'
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
        ParamName = '时间段名称'
        FieldName = 'semail'
      end
      item
        ParamName = '标识'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '交易类型'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '时间段一'
        FieldName = 'lvol1'
      end
      item
        ParamName = '时间段二'
        FieldName = 'lvol2'
      end
      item
        ParamName = '时间段三'
        FieldName = 'lvol3'
      end
      item
        ParamName = '时间段四'
        FieldName = 'lvol4'
      end
      item
        ParamName = '时间段五'
        FieldName = 'lvol5'
      end
      item
        ParamName = '时间段六'
        FieldName = 'lvol6'
      end
      item
        ParamName = '时间段七'
        FieldName = 'lvol7'
      end
      item
        ParamName = '时间段八'
        FieldName = 'lvol8'
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
        ParamName = '标识'
        FieldName = 'lvol0'
      end>
    RequestType = 848252
    KCDataset = Dataset
    Left = 24
    Top = 306
  end
  object cqqueryTimeGroupDetail: TKCWVQuery
    ID = '时间段组详细情况查询'
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
        ParamName = '时间段组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '星期'
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
    RequestType = 848254
    Left = 104
    Top = 386
  end
  object cqsetGateHolidayDetail: TKCWVQuery
    ID = '节假日详细设置'
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
        ParamName = '节假日编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '节假日日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '时间段组编号'
        FieldName = 'lvol1'
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
    RequestType = 848256
    Left = 104
    Top = 434
  end
  object cqsetGateGroup: TKCWVQuery
    ID = '门禁组查询'
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
        ParamName = '门禁组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '门禁组名称'
        FieldName = 'semail'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848257
    Left = 24
    Top = 162
  end
  object cpsetGateGroup: TKCWVProcessor
    ID = '门禁组设置'
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
        ParamName = '门禁组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '门禁组名称'
        FieldName = 'semail'
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
    RequestType = 848257
    KCDataset = Dataset
    Left = 24
    Top = 210
  end
  object cqsetGateGroupForGate: TKCWVQuery
    ID = '门禁组门禁机查询'
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
        ParamName = '门禁组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '门禁机编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848258
    Left = 104
    Top = 146
  end
  object cpsetGateGroupForGate: TKCWVProcessor
    ID = '门禁组门禁机设置'
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
        ParamName = '门禁组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '门禁机编号'
        FieldName = 'lvol1'
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
    RequestType = 848258
    KCDataset = Dataset
    Left = 104
    Top = 194
  end
  object cqsetGateOperLimit: TKCWVQuery
    ID = '门禁机操作员权限查询'
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
        ParamName = '门禁机编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作员号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848259
    Left = 104
    Top = 242
  end
  object cpsetGateOperLimit: TKCWVProcessor
    ID = '门禁机操作员权限设置'
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
        ParamName = '门禁机编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作员号'
        FieldName = 'scust_limit'
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
    RequestType = 848259
    KCDataset = Dataset
    Left = 104
    Top = 290
  end
  object cqsetGateGroupOperLimit: TKCWVQuery
    ID = '门禁组操作员权限查询'
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
        ParamName = '门禁组名称'
        FieldName = 'semail'
      end
      item
        ParamName = '操作员号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848260
    Left = 104
    Top = 50
  end
  object cpsetGateGroupOperLimit: TKCWVProcessor
    ID = '门禁组操作员权限设置'
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
        ParamName = '门禁组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作员号'
        FieldName = 'scust_limit'
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
    RequestType = 848260
    KCDataset = Dataset
    Left = 104
    Top = 98
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 448
    Top = 64
  end
  object cqQueryEquipmentByOther: TKCWVQuery
    ID = '设备查询门禁系统'
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
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '机号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '机型代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '上级设备物理ID'
        FieldName = 'sdate1'
      end
      item
        ParamName = '设备状态'
        FieldName = 'lvol4'
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
        ParamName = '负责人员工号'
        FieldName = 'sname2'
      end
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
    RequestType = 848264
    Left = 192
    Top = 69
  end
  object KCHolidayQuery: TKCWVQuery
    ID = '节假日详细查询'
    InputBindings = <
      item
        ParamName = '节假日编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '节假日名称'
        FieldName = 'semail'
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
    RequestType = 848266
    Left = 192
    Top = 117
  end
  object cqsetWeekTimeGroup: TKCWVQuery
    ID = '周时间段查询'
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
        ParamName = '时间段组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '时间段组名称'
        FieldName = 'semail'
      end
      item
        ParamName = '周一组编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '周二组编号'
        FieldName = 'lvol2'
      end
      item
        ParamName = '周三组编号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '周四组编号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '周五组编号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '周六组编号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '周日组编号'
        FieldName = 'lvol7'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848251
    Left = 192
    Top = 162
  end
  object cpsetWeekTimeGroup: TKCWVProcessor
    ID = '周时间段参数设置'
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
        ParamName = '时间段组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '时间段组名'
        FieldName = 'semail'
      end
      item
        ParamName = '交易类型'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '周一组编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '周二组编号'
        FieldName = 'lvol2'
      end
      item
        ParamName = '周三组编号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '周四组编号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '周五组编号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '周六组编号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '周日组编号'
        FieldName = 'lvol7'
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
    RequestType = 848251
    KCDataset = Dataset
    Left = 192
    Top = 210
  end
  object KCallotCustGate: TKCWVProcessor
    ID = '门禁人员名单分配'
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
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '门禁编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '周时间段'
        FieldName = 'lvol3'
      end
      item
        ParamName = '节假日'
        FieldName = 'lvol4'
      end
      item
        ParamName = '标志'
        FieldName = 'lvol5'
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
        ParamName = '返回标志'
        FieldName = 'lvol0'
      end>
    RequestType = 848267
    KCDataset = Dataset
    Left = 192
    Top = 258
  end
  object cqGateListQuery: TKCWVQuery
    ID = '门禁人员名单查询'
    InputBindings = <
      item
        ParamName = '门禁机名称'
        FieldName = 'semail2'
      end
      item
        ParamName = '门禁设备编号'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '姓名'
        FieldName = 'semail'
      end
      item
        ParamName = '院系代码'
        FieldName = 'scert_no'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol2'
        DefaultValue = Null
      end
      item
        ParamName = '客户类型'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '收费类型'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '名单类型'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '班级'
        FieldName = 'sstation1'
      end
      item
        ParamName = '专业代码'
        FieldName = 'sorder0'
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '操作员'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '增删标志'
        FieldName = 'lvol8'
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
    RequestType = 848269
    Left = 192
    Top = 306
  end
  object cqGateListDelete: TKCWVQuery
    ID = '门禁人员名单删除'
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
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '门禁编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '时间周'
        FieldName = 'lvol2'
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
    RequestType = 848268
    Left = 192
    Top = 354
  end
  object KCGateGroupOper: TKCWVQuery
    ID = '门禁组操作员查询'
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
        ParamName = '门禁组编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '门禁组名称'
        FieldName = 'semail'
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
    RequestType = 848265
    Left = 192
    Top = 402
  end
  object cqgateSerialDetailQuery: TKCWVQuery
    ID = '门禁流水查询'
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
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sname'
      end
      item
        ParamName = '起始日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '起始时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '设备标识'
        FieldName = 'lvol2'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sall_name'
      end
      item
        ParamName = '部门'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '事件'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '姓名'
        FieldName = 'semail'
      end
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '客户类别'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '设备机型'
        FieldName = 'scust_limit'
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
    RequestType = 848270
    Left = 280
    Top = 18
  end
  object cqattendDetailQuery: TKCWVQuery
    ID = '考勤流水查询'
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
        ParamName = '部门名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '学工号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '姓名'
        FieldName = 'sname'
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
        ParamName = '开始时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime2'
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
    RequestType = 847233
    Left = 280
    Top = 138
  end
  object cqattendDetailstat: TKCWVQuery
    ID = '考勤信息统计'
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
        ParamName = '部门名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '学工号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '姓名'
        FieldName = 'sname'
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
        ParamName = '开始时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime2'
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
    RequestType = 847234
    Left = 280
    Top = 82
  end
  object cqQueryGateOpenAlong: TKCWVQuery
    ID = '常开时间段查询'
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
        ParamName = '门禁机编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '时间周编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '交易类型'
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
    RequestType = 848273
    Left = 280
    Top = 186
  end
  object cqSetGateOpenAlong: TKCWVProcessor
    ID = '常开时间段设置'
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
        ParamName = '门禁机编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '时间周编号'
        FieldName = 'lvol1'
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
    RequestType = 848273
    KCDataset = Dataset
    Left = 280
    Top = 234
  end
  object cqsetgatebaninfo: TKCWVProcessor
    ID = '门禁对接参数设置'
    InputBindings = <
      item
        ParamName = '操作码'
        FieldName = 'sstatus0'
      end
      item
        ParamName = 'oper.大楼名称'
        FieldName = 'scusttypes'
      end
      item
        ParamName = 'oper.大楼编号'
        FieldName = 'scert_no'
      end
      item
        ParamName = 'oper.门禁组'
        FieldName = 'lvol0'
        DefaultValue = '0'
      end
      item
        ParamName = 'oper.备注'
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
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 888180
    KCDataset = Dataset
    Left = 280
    Top = 282
  end
  object cpSetGateTimeWeek: TKCWVProcessor
    ID = '门禁时间周设置'
    InputBindings = <
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lvol2'
      end
      item
        ParamName = '控制器编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '时间周编号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '机型代码'
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
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 848021
    KCDataset = Dataset
    Left = 280
    Top = 330
  end
  object cqGateTimeWeekManager: TKCWVQuery
    ID = '门禁时间周管理'
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
        ParamName = '操作类别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '控制器编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '控制器名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sholder_type'
      end
      item
        ParamName = '设备名称'
        FieldName = 'sholder_type2'
      end
      item
        ParamName = '设备物理型号'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '设备机型'
        FieldName = 'spost_code'
      end
      item
        ParamName = '所属区域'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '时间周编号'
        FieldName = 'lserial1'
        DefaultValue = 0
      end
      item
        ParamName = '时间周名称'
        FieldName = 'saddr2'
      end
      item
        ParamName = '子系统'
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
    RequestType = 848021
    Left = 280
    Top = 378
  end
  object kcGateTimeWeekDel: TKCWVQuery
    ID = '门禁时间周删除'
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
        ParamName = '操作类别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '控制器编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lvol2'
      end
      item
        ParamName = '时间周编号'
        FieldName = 'lvol3'
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
    RequestType = 848021
    Left = 280
    Top = 426
  end
  object cqQueryCustomerByOther: TKCWVQuery
    ID = '门禁客户信息查询'
    InputBindings = <
      item
        ParamName = '联系地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '客户所在区域'
        FieldName = 'lvol0'
      end
      item
        ParamName = '联系人单位名称'
        FieldName = 'scard1'
      end
      item
        ParamName = '联系人单位号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '客户名称'
        FieldName = 'sname'
      end
      item
        ParamName = '客户状态'
        FieldName = 'lvol2'
      end
      item
        ParamName = '客户类别'
        FieldName = 'lvol3'
      end
      item
        ParamName = '联系人姓名'
        FieldName = 'sname2'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '联系人民族'
        FieldName = 'lvol4'
      end
      item
        ParamName = '联系人性别'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '联系人学工号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '联系电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '班级'
        FieldName = 'sorder0'
      end
      item
        ParamName = '结束学工号'
        FieldName = 'sphone2'
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
    RequestType = 848022
    Left = 376
    Top = 34
  end
  object kcSetGateOpenMgr: TKCWVQuery
    ID = '管理卡常开卡设置'
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
        ParamName = '设备号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '卡用途'
        FieldName = 'lvol1'
      end
      item
        ParamName = '操作类别'
        FieldName = 'lvol2'
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
    RequestType = 950106
    Left = 376
    Top = 82
  end
  object kcQgateMgrOpen: TKCWVQuery
    ID = '管理卡常开卡查询'
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
        ParamName = '设备号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '卡用途'
        FieldName = 'lvol1'
      end
      item
        ParamName = '操作类别'
        FieldName = 'lvol2'
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
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 950106
    Left = 376
    Top = 130
  end
end
