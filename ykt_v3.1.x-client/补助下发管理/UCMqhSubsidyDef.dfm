inherited dmSubsidyDef: TdmSubsidyDef
  OldCreateOrder = True
  Left = 587
  Top = 216
  Width = 495
  object cqSublidyImport: TWVCommandTypeInfo
    ID = '补助信息导入'
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
        ParamName = '补助批次号'
      end
      item
        ParamName = '导入批次号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '顺序号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '补助金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '截止日期'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '导入标志'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end>
    Left = 24
    Top = 26
  end
  object cqsendSublidyList: TWVCommandTypeInfo
    ID = '下发'
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
        ParamName = '导入批次号'
      end
      item
        ParamName = '摘要'
      end
      item
        ParamName = '付款方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '票据号码'
      end
      item
        ParamName = '补助总人数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '补助总金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '经办人身份证号'
      end
      item
        ParamName = '经办人姓名'
      end
      item
        ParamName = '补助标志'
      end
      item
        ParamName = '密码'
      end>
    Left = 24
    Top = 74
  end
  object cqsetSubsidyInfo: TWVCommandTypeInfo
    ID = '补助信息管理'
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
        ParamName = '交易类型'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '顺序号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '发生额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '记录状态'
      end>
    Left = 24
    Top = 170
  end
  object cpsetSubsidyInfo: TWVCommandTypeInfo
    ID = '补助信息查询'
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
        ParamName = '导入批次号'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '补助批次号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '部门'
      end
      item
        ParamName = '审核状态'
      end>
    Left = 24
    Top = 122
  end
  object cqPatchDel: TWVCommandTypeInfo
    ID = '补助批量删除'
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
      end
      item
        ParamName = '状态'
      end>
    Left = 24
    Top = 214
  end
  object cqCheck: TWVCommandTypeInfo
    ID = '审核'
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
        ParamName = '操作标志'
      end
      item
        ParamName = '密码'
      end
      item
        ParamName = '顺序号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 24
    Top = 266
  end
  object WVSubsidyRcv: TWVCommandTypeInfo
    ID = '补助撤销'
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
        ParamName = '顺序号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '金额'
      end>
    Left = 24
    Top = 314
  end
end
