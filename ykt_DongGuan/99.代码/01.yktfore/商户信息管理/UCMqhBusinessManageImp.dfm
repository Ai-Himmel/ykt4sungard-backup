inherited dmBusinessManageImp: TdmBusinessManageImp
  OldCreateOrder = True
  Left = 280
  Top = 110
  Height = 527
  Width = 679
  object cqQueryBusinessByOther: TKCWVQuery
    ID = '商户信息非主键查询'
    InputBindings = <
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
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
        FieldName = 'sall_name'
      end
      item
        ParamName = '商户类别'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '是否为独立核算'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '是否为叶节点'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '负责人姓名'
        FieldName = 'sname'
      end
      item
        ParamName = '负责人身份证号'
        FieldName = 'semail2'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '费率类型'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '收搭伙费'
        FieldName = 'scust_type'
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
    Left = 40
    Top = 66
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 456
    Top = 24
  end
  object cqQueryBusinessByKey: TKCWVQuery
    ID = '商户信息主键查询'
    InputBindings = <
      item
        ParamName = '商户标识'
        FieldName = 'lvol3'
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
    RequestType = 843335
    Left = 40
    Top = 18
  end
  object cqsetBusiFate: TKCWVQuery
    ID = '浮动费率查询'
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
        ParamName = '标志'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '编号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '营业额'
        FieldName = 'lvol1'
      end
      item
        ParamName = '折扣比例'
        FieldName = 'damt1'
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
    RequestType = 843342
    Left = 120
    Top = 178
  end
  object cpsetBusiFate: TKCWVProcessor
    ID = '浮动费率设置'
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
        ParamName = '标志'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '编号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '营业额'
        FieldName = 'lvol1'
      end
      item
        ParamName = '折扣比例'
        FieldName = 'damt1'
      end
      item
        ParamName = '备注'
        FieldName = 'ssectypes'
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
    RequestType = 843342
    KCDataset = Dataset
    Left = 120
    Top = 226
  end
  object cqfillBusiSaveMoney: TKCWVProcessor
    ID = '充值商户存款'
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
        ParamName = '商户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '存款金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '充值类型'
        FieldName = 'lvol9'
      end
      item
        ParamName = '票据号码'
        FieldName = 'scust_auth2'
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
        ParamName = '交易日期'
        FieldName = 'sorder0'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp'
      end
      item
        ParamName = '后台流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '商户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '存款金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '提成金额'
        FieldName = 'damt1'
      end
      item
        ParamName = '帐户余额'
        FieldName = 'damt2'
      end
      item
        ParamName = '商户名称'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 843351
    KCDataset = Dataset
    Left = 288
    Top = 122
  end
  object cqsetFillBusiEquInfo: TKCWVQuery
    ID = '充值商户设备查询'
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
        ParamName = '商户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '设备编号'
        FieldName = 'saddr'
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
    RequestType = 843357
    Left = 208
    Top = 2
  end
  object cpsetFillBusiEquInfo: TKCWVProcessor
    ID = '充值商户设备信息设置增加'
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
        ParamName = '商户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '设备编号'
        FieldName = 'vsvarstr1'
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
    RequestType = 843355
    KCDataset = Dataset
    Left = 208
    Top = 50
  end
  object cpsetFillBusiEquInfoDel: TKCWVProcessor
    ID = '充值商户设备信息设置删除'
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
        ParamName = '商户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '设备编号'
        FieldName = 'vsvarstr1'
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
    RequestType = 843356
    KCDataset = Dataset
    Left = 208
    Top = 98
  end
  object cqsetFillEquOperInfo: TKCWVQuery
    ID = '设备操作员查询'
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
        ParamName = '设备编号'
        FieldName = 'saddr'
      end
      item
        ParamName = '充值操作员号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus1'
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
    RequestType = 843361
    Left = 208
    Top = 146
  end
  object cpsetFillEquOperInfo: TKCWVProcessor
    ID = '充值设备操作员设置添加'
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
        ParamName = '设备编号'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '充值操作员号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '每日最大充值金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '是否指定设备'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '是否充值商户操作员'
        FieldName = 'sstatus3'
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
    RequestType = 843358
    KCDataset = Dataset
    Left = 208
    Top = 194
  end
  object cpsetFillEquOperInfoEdit: TKCWVProcessor
    ID = '充值设备操作员设置修改'
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
        ParamName = '设备编号'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '充值操作员号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '每日最大充值金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '是否指定设备'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '是否充值商户操作员'
        FieldName = 'sstatus3'
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
    RequestType = 843359
    KCDataset = Dataset
    Left = 208
    Top = 240
  end
  object cpsetFillEquOperInfoDel: TKCWVProcessor
    ID = '充值设备操作员设置删除'
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
        ParamName = '设备编号'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '充值操作员号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '是否指定设备'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '是否充值商户操作员'
        FieldName = 'sstatus3'
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
    RequestType = 843360
    KCDataset = Dataset
    Left = 208
    Top = 290
  end
  object cqfillOperEquBanding: TKCWVQuery
    ID = '操作员设备查询'
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
        ParamName = '设备编号'
        FieldName = 'saddr'
      end
      item
        ParamName = '充值操作员号'
        FieldName = 'scust_auth'
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
    RequestType = 843364
    Left = 120
    Top = 34
  end
  object cpfillOperEquBanding: TKCWVProcessor
    ID = '充值操作员设备绑定'
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
        ParamName = '充值操作员号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '设备编号'
        FieldName = 'vsvarstr1'
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
    RequestType = 843362
    KCDataset = Dataset
    Left = 120
    Top = 82
  end
  object cpfillOperEquBandingDel: TKCWVProcessor
    ID = '充值操作员设备绑定删除'
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
        ParamName = '充值操作员号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '设备编号'
        FieldName = 'vsvarstr1'
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
    RequestType = 843363
    KCDataset = Dataset
    Left = 120
    Top = 130
  end
  object cpSetBusinessInfo: TKCWVProcessor
    ID = '商户信息设置'
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
        ParamName = '商户标识'
        FieldName = 'lvol3'
      end
      item
        ParamName = '父商户标识'
        FieldName = 'lvol1'
      end
      item
        ParamName = '商户名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '部门'
        FieldName = 'scert_no'
      end
      item
        ParamName = '商户类型'
        FieldName = 'lvol7'
      end
      item
        ParamName = '独立核算'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '联系人'
        FieldName = 'sname'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
      end
      item
        ParamName = '电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone2'
      end
      item
        ParamName = '电子邮箱'
        FieldName = 'semail'
      end
      item
        ParamName = '地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '邮编'
        FieldName = 'spost_code'
      end
      item
        ParamName = '佣金类型'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '佣金费率'
        FieldName = 'drate0'
      end
      item
        ParamName = '存款提成比率'
        FieldName = 'drate1'
      end
      item
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行帐号'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '银行帐户名'
        FieldName = 'sbankname2'
      end
      item
        ParamName = '末级商户'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = 'scust_type'
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
    RequestType = 843335
    KCDataset = Dataset
    Left = 40
    Top = 114
  end
  object cqSetBusiFee: TKCWVQuery
    ID = '商户搭伙费查询'
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
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '商户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
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
    RequestType = 846205
    Left = 288
    Top = 26
  end
  object cpBusiFee: TKCWVProcessor
    ID = '商户搭伙费设置'
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
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '商户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '费率'
        FieldName = 'drate0'
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
    RequestType = 846205
    KCDataset = Dataset
    Left = 288
    Top = 74
  end
  object cqBusiSubjectLink: TKCWVQuery
    ID = '商户科目映射查询'
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
        ParamName = '标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '商户号'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '对应科目名称'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '开户银行'
        FieldName = 'sbankname'
      end
      item
        ParamName = '银行账号'
        FieldName = 'sbank_acc'
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
    RequestType = 850041
    Left = 288
    Top = 170
  end
  object cpBusiSubjectLink: TKCWVProcessor
    ID = '商户科目映射'
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
        ParamName = '商户号'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '商户名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '对应科目号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '对应科目名称'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '开户银行'
        FieldName = 'sbankname'
      end
      item
        ParamName = '银行账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '标志'
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
    RequestType = 850041
    KCDataset = Dataset
    Left = 288
    Top = 218
  end
  object kcQBusiStruct: TKCWVQuery
    ID = '商户组织结构查询'
    InputBindings = <
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
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
        FieldName = 'sall_name'
      end
      item
        ParamName = '商户类别'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '是否为独立核算'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '是否为叶节点'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '负责人姓名'
        FieldName = 'sname'
      end
      item
        ParamName = '负责人身份证号'
        FieldName = 'semail2'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '费率类型'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '收搭伙费'
        FieldName = 'scust_type'
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
    RequestType = 850036
    Left = 40
    Top = 162
  end
  object cpSetBusiStruct: TKCWVProcessor
    ID = '商户组织结构设置'
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
        ParamName = '商户标识'
        FieldName = 'lvol3'
      end
      item
        ParamName = '父商户标识'
        FieldName = 'lvol1'
      end
      item
        ParamName = '商户名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '部门'
        FieldName = 'scert_no'
      end
      item
        ParamName = '商户类型'
        FieldName = 'lvol7'
      end
      item
        ParamName = '独立核算'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '联系人'
        FieldName = 'sname'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
      end
      item
        ParamName = '电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone2'
      end
      item
        ParamName = '电子邮箱'
        FieldName = 'semail'
      end
      item
        ParamName = '地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '邮编'
        FieldName = 'spost_code'
      end
      item
        ParamName = '佣金类型'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '佣金费率'
        FieldName = 'drate0'
      end
      item
        ParamName = '存款提成比率'
        FieldName = 'drate1'
      end
      item
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行帐号'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '银行帐户名'
        FieldName = 'sbankname2'
      end
      item
        ParamName = '末级商户'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = 'scust_type'
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
    RequestType = 850036
    KCDataset = Dataset
    Left = 40
    Top = 210
  end
  object cqSetBusiInfo: TKCWVQuery
    ID = '商户信息维护查询'
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
    Left = 368
    Top = 10
  end
  object cpSetBusiInfo: TKCWVProcessor
    ID = '商户信息维护'
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
      end
      item
        ParamName = '联系人'
        FieldName = 'sbankname'
      end
      item
        ParamName = '电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone2'
      end
      item
        ParamName = '电子信箱'
        FieldName = 'semail2'
      end
      item
        ParamName = '传真'
        FieldName = 'sphone3'
      end
      item
        ParamName = '营业地址'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '邮政编码'
        FieldName = 'spost_code'
      end
      item
        ParamName = '结算费率'
        FieldName = 'damt0'
      end
      item
        ParamName = '开户银行'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '银行账号'
        FieldName = 'spager'
      end
      item
        ParamName = '银行帐户名'
        FieldName = 'sbankname2'
      end
      item
        ParamName = '联行号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '开户日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '销户日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '销户状态'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '商户状态'
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
    RequestType = 2004
    KCDataset = Dataset
    Left = 368
    Top = 58
  end
  object cqSetBusiDev: TKCWVQuery
    ID = '商户设备管理查询'
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
        ParamName = '商户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '设备终端序列号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '省设备终端序列号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '设备类型'
        FieldName = 'sstock_code'
      end
      item
        ParamName = '状态'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '注册日期'
        FieldName = 'snote'
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
    RequestType = 2020
    Left = 368
    Top = 106
  end
  object cpSetBusiDev: TKCWVProcessor
    ID = '商户设备管理'
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
        ParamName = '商户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '商户名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '设备终端序列号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '省设备终端序列号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '设备类型'
        FieldName = 'sstock_code'
      end
      item
        ParamName = '状态'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '注册日期'
        FieldName = 'sdate0'
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
        ParamName = '绑定设备编号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '备注'
        FieldName = 'snote2'
      end
      item
        ParamName = '最后更新时间'
        FieldName = 'scust_limit2'
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
    RequestType = 2020
    KCDataset = Dataset
    Left = 368
    Top = 154
  end
end
