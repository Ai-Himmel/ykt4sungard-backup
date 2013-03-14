inherited dmSubsidyImp: TdmSubsidyImp
  OldCreateOrder = True
  Left = 284
  Top = 199
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 312
    Top = 40
  end
  object cqimportSublidyList: TKCWVProcessor
    ID = '补助信息导入'
    InputBindings = <
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '补助批次号'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '顺序号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '补助金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '截止日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '操作员'
        FieldName = 'scust_no'
      end
      item
        ParamName = '导入标志'
        FieldName = 'scust_type'
      end
      item
        ParamName = '客户号'
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
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end>
    RequestType = 847130
    KCDataset = Dataset
    Left = 40
    Top = 10
  end
  object cqSublidySend: TKCWVProcessor
    ID = '下发'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '摘要'
        FieldName = 'semail'
      end
      item
        ParamName = '付款方式'
        FieldName = 'lvol9'
      end
      item
        ParamName = '票据号码'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '补助总人数'
        FieldName = 'lvol3'
      end
      item
        ParamName = '补助总金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '经办人身份证号'
        FieldName = 'sname'
      end
      item
        ParamName = '经办人姓名'
        FieldName = 'semail2'
      end
      item
        ParamName = '补助标志'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '密码'
        FieldName = 'scust_limit2'
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
    RequestType = 847132
    KCDataset = Dataset
    Left = 40
    Top = 58
  end
  object cqsetSubsidyInfo: TKCWVQuery
    ID = '补助信息查询'
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
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '补助批次号'
        FieldName = 'lvol10'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol11'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '部门'
        FieldName = 'scert_no'
      end
      item
        ParamName = '审核状态'
        FieldName = 'sstatus4'
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
    RequestType = 847131
    Left = 40
    Top = 114
  end
  object cpsetSubsidyInfo: TKCWVProcessor
    ID = '补助信息管理'
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
        ParamName = '交易类型'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '顺序号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol11'
      end
      item
        ParamName = '发生额'
        FieldName = 'damt0'
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
    RequestType = 847131
    KCDataset = Dataset
    Left = 40
    Top = 162
  end
  object cpPatchdel: TKCWVProcessor
    ID = '补助批量删除'
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
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus1'
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
    RequestType = 847131
    KCDataset = Dataset
    Left = 40
    Top = 206
  end
  object cpCheck: TKCWVProcessor
    ID = '审核'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '密码'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '顺序号'
        FieldName = 'lvol1'
        DefaultValue = 0
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
    RequestType = 847131
    KCDataset = Dataset
    Left = 40
    Top = 250
  end
  object kcSubsidyRcv: TKCWVProcessor
    ID = '补助撤销'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '顺序号'
        FieldName = 'lvol1'
        DefaultValue = 0
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
    RequestType = 847129
    KCDataset = Dataset
    Left = 40
    Top = 298
  end
end
