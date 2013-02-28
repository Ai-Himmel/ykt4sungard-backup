inherited dmSubSystemDef: TdmSubSystemDef
  OldCreateOrder = True
  Left = 317
  Top = 100
  Height = 606
  Width = 698
  object cqSetPOSInfo: TWVCommandTypeInfo
    ID = 'POS信息维护查询'
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
        ParamName = '所属商户号'
      end
      item
        ParamName = '设备终端号'
      end
      item
        ParamName = '终端序列号'
      end
      item
        ParamName = '设备型号'
      end
      item
        ParamName = '设备类型'
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '用途'
      end
      item
        ParamName = '设备状态'
      end>
    Left = 32
    Top = 18
  end
  object cpSetPOSInfo: TWVCommandTypeInfo
    ID = 'POS信息维护'
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
        ParamName = '设备机编号'
      end
      item
        ParamName = '所属商户号'
      end
      item
        ParamName = '设备终端号'
      end
      item
        ParamName = '终端序列号'
      end
      item
        ParamName = '设备型号'
      end
      item
        ParamName = '设备类型'
      end
      item
        ParamName = '设备名称'
      end
      item
        ParamName = '用途'
      end
      item
        ParamName = '设备状态'
      end
      item
        ParamName = '启用日期'
      end
      item
        ParamName = '注册日期'
      end
      item
        ParamName = '删除日期'
      end
      item
        ParamName = '最后更新时间'
      end
      item
        ParamName = '备注'
      end
      item
        ParamName = '地区编码'
      end>
    Left = 32
    Top = 66
  end
  object cqDevRepair: TWVCommandTypeInfo
    ID = '设备维修'
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
        ParamName = '设备状态'
      end>
    Left = 32
    Top = 114
  end
  object WVDevBusiBind: TWVCommandTypeInfo
    ID = '设备商户绑定'
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
        ParamName = '商户编号'
      end
      item
        ParamName = '操作类型'
      end
      item
        ParamName = '序列号'
      end>
    Left = 32
    Top = 162
  end
  object WVDevBusiQ: TWVCommandTypeInfo
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
        ParamName = '设备编号'
      end
      item
        ParamName = '商户编号'
      end>
    Left = 32
    Top = 210
  end
  object cqSetBusiInfo: TWVCommandTypeInfo
    ID = '商户信息维护QQ'
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
        ParamName = '商户编号'
      end
      item
        ParamName = '中心商户号'
      end
      item
        ParamName = '省商户编号'
      end
      item
        ParamName = '商户状态'
      end
      item
        ParamName = '商户名'
      end
      item
        ParamName = '商户英文名称'
      end
      item
        ParamName = '商户简称'
      end
      item
        ParamName = '商户类型'
      end
      item
        ParamName = '行业类型'
      end>
    Left = 32
    Top = 258
  end
end
