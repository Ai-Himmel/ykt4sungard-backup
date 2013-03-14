inherited dmBusinessEquipDef: TdmBusinessEquipDef
  OldCreateOrder = True
  Left = 435
  Top = 180
  Height = 543
  Width = 628
  object cqQueryBusinessEquipByOther: TWVCommandTypeInfo
    ID = '设备商户信息非主键查询'
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
        ParamName = '使用状态'
      end
      item
        ParamName = '设备标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '商户名称'
      end
      item
        ParamName = '使用开始日期'
      end
      item
        ParamName = '使用结束日期'
      end
      item
        ParamName = '使用结束时间'
      end
      item
        ParamName = '商户编号'
        ParamDataType = kdtInteger
      end>
    Left = 144
    Top = 74
  end
  object cpSetBusinessEquipInfo: TWVCommandTypeInfo
    ID = '设备商户信息设置'
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
        ParamName = '编号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '使用结束时间'
      end
      item
        ParamName = '启用日期'
      end
      item
        ParamName = '停用日期'
      end>
    Left = 40
    Top = 202
  end
  object cqSetBusinessEquipInfo: TWVCommandTypeInfo
    ID = '设备商户信息查询'
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
        ParamName = '编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '设备编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '物理编号'
      end
      item
        ParamName = '商户编号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '使用状态'
      end>
    Left = 40
    Top = 58
  end
  object cqQueryEquipmentByKey3: TWVCommandTypeInfo
    ID = '设备关键字查询3'
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
    Left = 144
    Top = 124
  end
  object cqQueryBusinessByKey2: TWVCommandTypeInfo
    ID = '商户信息主键查询2'
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
        ParamName = '商户标识'
      end>
    Left = 40
    Top = 106
  end
  object cqQueryBusinessByOther2: TWVCommandTypeInfo
    ID = '商户信息非主键查询2'
    Params = <
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
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
        ParamName = '商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '父商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '商户名称'
      end
      item
        ParamName = '商户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否为独立核算'
      end
      item
        ParamName = '是否为叶节点'
      end
      item
        ParamName = '负责人姓名'
      end
      item
        ParamName = '负责人身份证号'
      end>
    Left = 40
    Top = 154
  end
  object cqQueryEquipmentByOther2: TWVCommandTypeInfo
    ID = '设备非关键字查询2'
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
    Left = 144
    Top = 28
  end
  object cqsetMealOrder: TWVCommandTypeInfo
    ID = '餐次信息查询'
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
        ParamName = '餐次名称'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '结束时间'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 232
    Top = 10
  end
  object cpsetMealOrder: TWVCommandTypeInfo
    ID = '餐次信息设置'
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
        ParamName = '序号'
      end
      item
        ParamName = '餐次名称'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '结束时间'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '备注'
      end>
    Left = 232
    Top = 58
  end
  object WVDevBusiImp: TWVCommandTypeInfo
    ID = '设备商户信息导入'
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
        ParamName = '商户编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '停用时间'
      end
      item
        ParamName = '启用日期'
      end
      item
        ParamName = '停用日期'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 40
    Top = 250
  end
  object cqdevBusiImpManage: TWVCommandTypeInfo
    ID = '设备商户查询'
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
        ParamName = '导入批次号'
      end
      item
        ParamName = '设备编号'
      end
      item
        ParamName = '设备物理编号'
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '商户编号'
      end
      item
        ParamName = '商户名称'
      end>
    Left = 144
    Top = 170
  end
  object cpdevBusiImpManage: TWVCommandTypeInfo
    ID = '设备商户导入管理'
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
        ParamName = '设备名称'
      end
      item
        ParamName = '商户名称'
      end
      item
        ParamName = '结束时间'
      end
      item
        ParamName = '启用日期'
      end
      item
        ParamName = '停用日期'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 144
    Top = 218
  end
  object WVdevBusiImpCheck: TWVCommandTypeInfo
    ID = '设备商户导入审核'
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
    Left = 144
    Top = 266
  end
  object cqPatchDel: TWVCommandTypeInfo
    ID = '商户设备批量删除'
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
    Left = 232
    Top = 206
  end
  object cqsetBusiCC: TWVCommandTypeInfo
    ID = '商户餐次信息查询'
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
        ParamName = '商户编号'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 232
    Top = 306
  end
  object cpsetBusiCC: TWVCommandTypeInfo
    ID = '商户餐次信息设置'
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
        ParamName = '商户编号'
      end
      item
        ParamName = '早餐结束时间'
      end
      item
        ParamName = '午餐结束时间'
      end
      item
        ParamName = '晚餐结束时间'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 232
    Top = 258
  end
end
