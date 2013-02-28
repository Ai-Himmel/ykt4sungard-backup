inherited dmSubSystemImp: TdmSubSystemImp
  OldCreateOrder = True
  Left = 444
  Top = 169
  Height = 581
  Width = 645
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 88
    Top = 16
  end
  object cqSetPOSInfo: TKCWVQuery
    ID = 'POS信息维护查询'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '设备编号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '所属商户号'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '设备终端号'
        FieldName = 'sname'
      end
      item
        ParamName = '终端序列号'
        FieldName = 'sname2'
      end
      item
        ParamName = '设备型号'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '设备类型'
        FieldName = 'spost_code'
      end
      item
        ParamName = '设备名称'
        FieldName = 'sbankname'
      end
      item
        ParamName = '用途'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '设备状态'
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
    RequestType = 2005
    Left = 24
    Top = 18
  end
  object cpSetPOSInfo: TKCWVProcessor
    ID = 'POS信息维护'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '设备机编号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '所属商户号'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '设备终端号'
        FieldName = 'sname'
      end
      item
        ParamName = '终端序列号'
        FieldName = 'sname2'
      end
      item
        ParamName = '设备型号'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '设备类型'
        FieldName = 'spost_code'
      end
      item
        ParamName = '设备名称'
        FieldName = 'sbankname'
      end
      item
        ParamName = '用途'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '设备状态'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '启用日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '注册日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '删除日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '最后更新时间'
        FieldName = 'scard0'
      end
      item
        ParamName = '备注'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '地区编码'
        FieldName = 'sstock_code'
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
    RequestType = 2005
    KCDataset = Dataset
    Left = 24
    Top = 66
  end
  object cqDevRepair: TKCWVQuery
    ID = '设备维修'
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
        ParamName = '设备编号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '设备状态'
        FieldName = 'sstat_type'
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
    RequestType = 2012
    Left = 24
    Top = 114
  end
  object KCDevBusiBind: TKCWVProcessor
    ID = '设备商户绑定'
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
        ParamName = '操作类型'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '商户编号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '设备编号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '序列号'
        FieldName = 'scust_auth'
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
    RequestType = 2011
    KCDataset = Dataset
    Left = 24
    Top = 162
  end
  object KCDevBusiQ: TKCWVQuery
    ID = '设备商户查询'
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
        ParamName = '设备编号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '商户编号'
        FieldName = 'lvol0'
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
    RequestType = 2013
    Left = 24
    Top = 210
  end
  object cqSetBusiInfo: TKCWVQuery
    ID = '商户信息维护QQ'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '商户编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '中心商户号'
        FieldName = 'sname'
      end
      item
        ParamName = '省商户编号'
        FieldName = 'sname2'
      end
      item
        ParamName = '商户状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '商户名'
        FieldName = 'snote'
      end
      item
        ParamName = '商户英文名称'
        FieldName = 'snote2'
      end
      item
        ParamName = '商户简称'
        FieldName = 'semail'
      end
      item
        ParamName = '商户类型'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '行业类型'
        FieldName = 'sbranch_code1'
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
    RequestType = 2004
    Left = 24
    Top = 258
  end
end
