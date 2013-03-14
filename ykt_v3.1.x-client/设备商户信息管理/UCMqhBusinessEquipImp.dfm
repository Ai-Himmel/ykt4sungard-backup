inherited dmBusinessEquipImp: TdmBusinessEquipImp
  OldCreateOrder = True
  Left = 356
  Top = 166
  Height = 505
  Width = 547
  object cqQueryBusinessEquipByOther: TKCWVQuery
    ID = '设备商户信息非主键查询'
    InputBindings = <
      item
        ParamName = '设备标识'
        FieldName = 'lvol5'
      end
      item
        ParamName = '使用开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '使用状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '使用结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '使用结束时间'
        FieldName = 'stime2'
      end
      item
        ParamName = '商户名称'
        FieldName = 'sbankname'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '商户编号'
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
    RequestType = 843371
    Left = 152
    Top = 90
  end
  object cpSetBusinessEquipInfo: TKCWVProcessor
    ID = '设备商户信息设置'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '商户标识'
        FieldName = 'lvol3'
      end
      item
        ParamName = '设备标识'
        FieldName = 'lvol5'
      end
      item
        ParamName = '使用结束时间'
        FieldName = 'stime2'
      end
      item
        ParamName = '启用日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '停用日期'
        FieldName = 'sdate2'
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
        ParamName = '编号'
        FieldName = 'lvol0'
      end>
    RequestType = 843371
    KCDataset = Dataset
    Left = 48
    Top = 218
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 328
    Top = 32
  end
  object cqSetBusinessEquipInfo: TKCWVQuery
    ID = '设备商户信息查询'
    InputBindings = <
      item
        ParamName = '编号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '设备编号'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '物理编号'
        FieldName = 'sname'
      end
      item
        ParamName = '商户编号'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '使用状态'
        FieldName = 'sstatus1'
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
    RequestType = 843371
    Left = 48
    Top = 74
  end
  object cqQueryEquipmentByKey3: TKCWVQuery
    ID = '设备关键字查询3'
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
    RequestType = 847166
    Left = 152
    Top = 138
  end
  object cqQueryBusinessByKey2: TKCWVQuery
    ID = '商户信息主键查询2'
    InputBindings = <
      item
        ParamName = '商户标识'
        FieldName = 'lvol3'
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
    RequestType = 843335
    Left = 48
    Top = 122
  end
  object cqQueryBusinessByOther2: TKCWVQuery
    ID = '商户信息非主键查询2'
    InputBindings = <
      item
        ParamName = '商户标识'
        FieldName = 'lvol3'
      end
      item
        ParamName = '父商户标识'
        FieldName = 'lvol1'
      end
      item
        ParamName = '商户名称'
        FieldName = 'scard1'
      end
      item
        ParamName = '商户类别'
        FieldName = 'lvol7'
      end
      item
        ParamName = '是否为独立核算'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '是否为叶节点'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '负责人姓名'
        FieldName = 'sname'
      end
      item
        ParamName = '负责人身份证号'
        FieldName = 'sname2'
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
    RequestType = 843335
    Left = 48
    Top = 170
  end
  object cqQueryEquipmentByOther2: TKCWVQuery
    ID = '设备非关键字查询2'
    InputBindings = <
      item
        ParamName = '设备名称'
        FieldName = 'scust_auth'
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
    RequestType = 847166
    Left = 152
    Top = 45
  end
  object cqsetMealOrder: TKCWVQuery
    ID = '餐次信息查询'
    InputBindings = <
      item
        ParamName = '餐次名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '开始时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime2'
      end
      item
        ParamName = '操作标志'
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
    RequestType = 843340
    Left = 240
    Top = 66
  end
  object cpsetMealOrder: TKCWVProcessor
    ID = '餐次信息设置'
    InputBindings = <
      item
        ParamName = '序号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '餐次名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '开始时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime2'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '备注'
        FieldName = 'scusttypes'
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
    RequestType = 843340
    KCDataset = Dataset
    Left = 240
    Top = 18
  end
  object cqImpDevCustInfo: TKCWVProcessor
    ID = '设备商户信息导入'
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
        ParamName = '商户编号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '设备编号'
        FieldName = 'Lvol5'
      end
      item
        ParamName = '停用时间'
        FieldName = 'stime2'
      end
      item
        ParamName = '启用日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '停用日期'
        FieldName = 'sdate2'
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
    RequestType = 843370
    KCDataset = Dataset
    Left = 48
    Top = 266
  end
  object cqdevBusiImpManage: TKCWVQuery
    ID = '设备商户查询'
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
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '设备编号'
        FieldName = 'lvol5'
      end
      item
        ParamName = '设备物理编号'
        FieldName = 'sname'
      end
      item
        ParamName = '设备名称'
        FieldName = 'sbankname'
      end
      item
        ParamName = '商户编号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '商户名称'
        FieldName = 'sall_name'
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
    RequestType = 843370
    Left = 152
    Top = 186
  end
  object cpdevBusiImpManage: TKCWVProcessor
    ID = '设备商户导入管理'
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
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '导入顺序号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '设备名称'
        FieldName = 'sbankname'
      end
      item
        ParamName = '商户名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '结束时间'
        FieldName = 'stime2'
      end
      item
        ParamName = '启用日期'
        FieldName = 'Sdate1'
      end
      item
        ParamName = '停用日期'
        FieldName = 'Sdate2'
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
    RequestType = 843370
    KCDataset = Dataset
    Left = 152
    Top = 234
  end
  object cqDevBusiImpCheck: TKCWVProcessor
    ID = '设备商户导入审核'
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
    RequestType = 843370
    KCDataset = Dataset
    Left = 152
    Top = 282
  end
  object cpPatchdel: TKCWVProcessor
    ID = '商户设备批量删除'
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
    RequestType = 843370
    KCDataset = Dataset
    Left = 240
    Top = 118
  end
  object cqsetBusiCC: TKCWVQuery
    ID = '商户餐次信息查询'
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
        ParamName = '商户编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作类别'
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
    RequestType = 843341
    Left = 240
    Top = 210
  end
  object cpsetBusiCC: TKCWVProcessor
    ID = '商户餐次信息设置'
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
        ParamName = '商户编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '早餐结束时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '午餐结束时间'
        FieldName = 'stime2'
      end
      item
        ParamName = '晚餐结束时间'
        FieldName = 'stime3'
      end
      item
        ParamName = '操作类别'
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
    RequestType = 843341
    KCDataset = Dataset
    Left = 240
    Top = 162
  end
end
