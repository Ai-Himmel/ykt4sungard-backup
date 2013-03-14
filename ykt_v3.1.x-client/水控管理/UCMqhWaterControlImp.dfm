inherited WaterControlImp: TWaterControlImp
  OldCreateOrder = True
  Left = 264
  Top = 195
  Height = 541
  Width = 767
  object cqQueryGlobeParaByKey: TKCWVQuery
    ID = '全局参数主键查询'
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
      end
      item
        ParamName = '密钥'
        FieldName = 'scard0'
      end>
    RequestType = 820404
    Left = 32
    Top = 58
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
  object WVQueryGlobeParaByKey: TWVCommandTypeInfo
    ID = '全局参数主键查询'
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
      end
      item
        ParamName = '密钥'
        ParamType = ptOutput
      end>
    Left = 112
    Top = 82
  end
  object cqwaterCardPatch: TKCWVQuery
    ID = '补写水控卡信息'
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
        ParamName = '物理卡号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '交易代码'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '入卡值'
        FieldName = 'Damt1'
      end
      item
        ParamName = '操作员代码'
        FieldName = 'Scust_limit'
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
    RequestType = 847119
    Left = 32
    Top = 106
  end
  object WVwaterCardPatch: TWVCommandTypeInfo
    ID = '补写水控卡信息'
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
        ParamName = '交易卡号'
      end
      item
        ParamName = '交易代码'
      end
      item
        ParamName = '入卡值'
      end
      item
        ParamName = '操作员代码'
      end>
    Left = 112
    Top = 130
  end
  object cpReCreCardOK: TKCWVProcessor
    ID = '补写水控信息确认'
    InputBindings = <
      item
        ParamName = '卡标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易码'
        FieldName = 'lserial0'
      end
      item
        ParamName = '交易流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '钱包号'
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
    RequestType = 847120
    KCDataset = Dataset
    Left = 32
    Top = 152
  end
  object cpPatchCard: TKCWVProcessor
    ID = '补写水控信息'
    InputBindings = <
      item
        ParamName = '卡标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '入卡值'
        FieldName = 'damt1'
      end
      item
        ParamName = '操作员号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '工作站号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '设备号'
        FieldName = 'lvol7'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol8'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol4'
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
        ParamName = '后台交易流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '出卡值'
        FieldName = 'damt2'
      end
      item
        ParamName = '搭伙费'
        FieldName = 'damt3'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '卡密码'
        FieldName = 'sopen_emp'
      end
      item
        ParamName = '客户类型'
        FieldName = 'lvol1'
      end
      item
        ParamName = '收费类型'
        FieldName = 'lvol5'
      end
      item
        ParamName = '截至日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '图书证号'
        FieldName = 'sname2'
      end
      item
        ParamName = '身份证号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '部门代码'
        FieldName = 'Scust_no2'
      end
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '性别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '客户名称'
        FieldName = 'sname'
      end>
    RequestType = 847119
    KCDataset = Dataset
    Left = 32
    Top = 200
  end
  object cpModifyWaterState: TKCWVProcessor
    ID = '修改水控状态'
    InputBindings = <
      item
        ParamName = '卡标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '后台交易流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '交易码'
        FieldName = 'lvol2'
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
    RequestType = 847108
    KCDataset = Dataset
    Left = 32
    Top = 248
  end
  object cqQCIByPatchCard: TKCWVQuery
    ID = '补写水控信息查询'
    InputBindings = <
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '姓名'
        FieldName = 'sname'
      end
      item
        ParamName = '身份证号'
        FieldName = 'sname2'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'scust_no'
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
    RequestType = 847162
    Left = 216
    Top = 10
  end
  object ctQCIByPathCard: TWVCommandTypeInfo
    ID = '补写水控信息查询'
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
        ParamName = '身份证号'
      end
      item
        ParamName = '显示卡号'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end>
    Left = 288
    Top = 26
  end
  object ctPatchCard: TWVCommandTypeInfo
    ID = '补写水控信息'
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
        ParamName = '后台交易流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '搭伙费'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '交易卡号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '显示卡号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡密码'
        ParamType = ptOutput
      end
      item
        ParamName = '收费类型'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户类型'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '截至日期'
        ParamType = ptOutput
      end
      item
        ParamName = '身份证号'
        ParamType = ptOutput
      end
      item
        ParamName = '部门代码'
        ParamType = ptOutput
      end
      item
        ParamName = '图书证号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '入卡值'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '工作站号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '设备号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户名称'
        ParamType = ptOutput
      end
      item
        ParamName = '学工号'
        ParamType = ptOutput
      end
      item
        ParamName = '性别'
        ParamType = ptOutput
      end
      item
        ParamName = '交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '钱包号'
        ParamDataType = kdtInteger
      end>
    Left = 112
    Top = 224
  end
  object ctModifyWaterState: TWVCommandTypeInfo
    ID = '修改水控状态'
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
        ParamName = '卡标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '后台交易流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易码'
        ParamDataType = kdtInteger
      end>
    Left = 112
    Top = 264
  end
  object ctReCreCardOK: TWVCommandTypeInfo
    ID = '补写水控信息确认'
    Params = <
      item
        ParamName = '卡标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易码'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易流水号'
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
        ParamName = '钱包号'
        ParamDataType = kdtInteger
      end>
    Left = 112
    Top = 176
  end
  object ctCollectionWaterTrade: TWVCommandTypeInfo
    ID = '水控流水采集'
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
        ParamName = '设备号'
      end
      item
        ParamName = '金额'
      end
      item
        ParamName = '失败码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员代码'
      end>
    Left = 288
    Top = 74
  end
  object cqCollectionWaterTrade: TKCWVProcessor
    ID = '水控流水采集'
    InputBindings = <
      item
        ParamName = '设备号'
        FieldName = 'sdate0'
      end
      item
        ParamName = '金额'
        FieldName = 'damt1'
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
        ParamName = '操作员代码'
        FieldName = 'scust_no'
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
        ParamName = '失败码'
        FieldName = 'lvol0'
      end>
    RequestType = 847306
    KCDataset = Dataset
    Left = 216
    Top = 56
  end
end
