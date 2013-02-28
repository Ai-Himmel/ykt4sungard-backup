inherited dmCardImp: TdmCardImp
  OldCreateOrder = True
  Left = 375
  Top = 251
  Height = 433
  Width = 509
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 88
  end
  object cqMoneyIn: TKCWVProcessor
    ID = '卡充值'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '入卡金额'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol5'
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '充值类型'
        FieldName = 'Lvol9'
      end
      item
        ParamName = '票据号码'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '充值金额'
        FieldName = 'damt0'
      end
      item
        ParamName = 'psam卡号'
        FieldName = 'snote'
      end
      item
        ParamName = '本机流水号'
        FieldName = 'sphone'
      end
      item
        ParamName = '本机日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '本机时间'
        FieldName = 'stime0'
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
        ParamName = '卡号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '出卡金额'
        FieldName = 'lvol8'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end
      item
        ParamName = '卡号1'
        FieldName = 'lvol0'
      end>
    RequestType = 846312
    KCDataset = Dataset
    Left = 22
    Top = 24
  end
  object cqMoneyOut: TKCWVProcessor
    ID = '卡支取'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '入卡金额'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '支取金额'
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
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '出卡金额'
        FieldName = 'lvol8'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end>
    RequestType = 846314
    KCDataset = Dataset
    Left = 22
    Top = 72
  end
  object cqRefreshCard: TKCWVProcessor
    ID = '更新卡信息'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation1'
      end
      item
        ParamName = '更新类型'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '卡到期日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '卡余额'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '入单次限额'
        FieldName = 'damt11'
      end
      item
        ParamName = '入日限额'
        FieldName = 'damt12'
      end
      item
        ParamName = '充值次数'
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
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '客户类别'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '部门代码'
        FieldName = 'scert_no'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
      end
      item
        ParamName = '性别'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '卡到期日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol8'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '补助批次号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '卡密码'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '单次限额'
        FieldName = 'lvol11'
      end
      item
        ParamName = '日限额'
        FieldName = 'lvol12'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime3'
      end>
    RequestType = 846320
    KCDataset = Dataset
    Left = 22
    Top = 120
  end
  object cpSetMoney: TKCWVProcessor
    ID = '卡余额设置'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation1'
      end
      item
        ParamName = '入卡金额'
        FieldName = 'Lvol7'
        DefaultValue = 0
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '调整金额'
        FieldName = 'damt0'
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '验证操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '验证密码'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '方向'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '终端编号'
        FieldName = 'snote'
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
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end
      item
        ParamName = '出卡金额'
        FieldName = 'lvol8'
      end>
    RequestType = 846322
    KCDataset = Dataset
    Left = 22
    Top = 168
  end
  object cqAccountQ: TKCWVQuery
    ID = '账户信息查询'
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
        ParamName = '姓名'
        FieldName = 'snote'
      end
      item
        ParamName = '证件类型'
        FieldName = 'sroom_no'
      end
      item
        ParamName = '证件号码'
        FieldName = 'spager'
      end
      item
        ParamName = '发卡部门'
        FieldName = 'sroom_no2'
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
        ParamName = '卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡物理编号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol1'
      end
      item
        ParamName = '制卡日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '卡序列号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '卡状态'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '查询类别'
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
    RequestType = 2006
    Left = 88
    Top = 42
  end
  object cqCardSericalQ: TKCWVQuery
    ID = '交易流水查询'
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
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '姓名'
        FieldName = 'snote'
      end
      item
        ParamName = '证件类型'
        FieldName = 'sroom_no'
      end
      item
        ParamName = '证件号码'
        FieldName = 'spager'
      end
      item
        ParamName = '发卡部门'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡物理编号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '交易码'
        FieldName = 'spost_code'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
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
    RequestType = 2007
    Left = 88
    Top = 90
  end
  object cqCardInfoQ: TKCWVQuery
    ID = '已发卡信息查询'
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
        ParamName = '发卡部门'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '姓名'
        FieldName = 'snote'
      end
      item
        ParamName = '证件类型'
        FieldName = 'sroom_no'
      end
      item
        ParamName = '证件号码'
        FieldName = 'spager'
      end
      item
        ParamName = '序列号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '卡号'
        FieldName = 'scard0'
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
    RequestType = 2002
    Left = 88
    Top = 138
  end
  object KCLoss_UN: TKCWVProcessor
    ID = '挂失解挂'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '卡号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'psam卡号'
        FieldName = 'snote'
      end
      item
        ParamName = '本机流水号'
        FieldName = 'sphone'
      end
      item
        ParamName = '本机日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '本机时间'
        FieldName = 'stime0'
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
        ParamName = '版本号'
        FieldName = 'semail'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡类别'
        FieldName = 'sname2'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end>
    RequestType = 2008
    KCDataset = Dataset
    Left = 86
    Top = 184
  end
  object cqReturnMoney: TKCWVQuery
    ID = '充值查询'
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
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡物理编号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '交易码'
        FieldName = 'spost_code'
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
    RequestType = 3001
    Left = 88
    Top = 234
  end
  object KCRtnMoney: TKCWVQuery
    ID = '充值回退'
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
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡物理编号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '交易前充值次数'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '交易前消费次数'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol7'
        DefaultValue = 0
      end
      item
        ParamName = '上笔sam终端号'
        FieldName = 'sserial0'
      end
      item
        ParamName = '上笔类型'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '上笔金额'
        FieldName = 'lvol8'
        DefaultValue = 0
      end
      item
        ParamName = '上笔日期'
        FieldName = 'sorder0'
      end
      item
        ParamName = '上笔时间'
        FieldName = 'sorder1'
      end
      item
        ParamName = '操作员编号'
        FieldName = 'lbank_acc_type2'
        DefaultValue = 0
      end
      item
        ParamName = '操作员流水'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '主机日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '参考号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '记账日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '备注'
        FieldName = 'snote'
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
        ParamName = '主机时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '主机日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol9'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '操作员流水'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡类别'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end
      item
        ParamName = '参考号'
        FieldName = 'scert_no'
      end>
    RequestType = 2021
    Left = 88
    Top = 282
  end
  object KCChangeCardA: TKCWVProcessor
    ID = '换卡申请'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '换卡原因'
        FieldName = 'snote'
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
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end
      item
        ParamName = '申请单号'
        FieldName = 'lvol1'
      end>
    RequestType = 2022
    KCDataset = Dataset
    Left = 150
    Top = 24
  end
  object KCReNewApp: TKCWVProcessor
    ID = '补办申请'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '换卡原因'
        FieldName = 'snote'
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
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end>
    RequestType = 2023
    KCDataset = Dataset
    Left = 150
    Top = 72
  end
  object KCDestoryApp: TKCWVProcessor
    ID = '销户申请'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '销户原因'
        FieldName = 'snote'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol7'
        DefaultValue = 0
      end
      item
        ParamName = '上笔sam终端'
        FieldName = 'sserial0'
      end
      item
        ParamName = '上笔类型'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '上笔金额'
        FieldName = 'lvol8'
        DefaultValue = 0
      end
      item
        ParamName = '上笔日期'
        FieldName = 'sorder0'
      end
      item
        ParamName = '上笔时间'
        FieldName = 'sorder1'
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
        ParamName = '主机日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '主机时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end>
    RequestType = 2024
    KCDataset = Dataset
    Left = 150
    Top = 120
  end
  object KCRenewOper: TKCWVProcessor
    ID = '补办操作'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '物理卡号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol7'
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
      end
      item
        ParamName = '终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol9'
      end
      item
        ParamName = '主机日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '主机时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡类别'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end>
    RequestType = 2026
    KCDataset = Dataset
    Left = 150
    Top = 168
  end
  object KCChangeCardOper: TKCWVProcessor
    ID = '换卡操作'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '旧应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard1'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '物理卡号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol7'
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
      end
      item
        ParamName = '终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol9'
      end
      item
        ParamName = '主机日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '主机时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end>
    RequestType = 2025
    KCDataset = Dataset
    Left = 150
    Top = 216
  end
  object KCDestoryOper: TKCWVProcessor
    ID = '销户操作'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
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
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end
      item
        ParamName = '退卡余额'
        FieldName = 'lvol8'
      end>
    RequestType = 2027
    KCDataset = Dataset
    Left = 150
    Top = 264
  end
  object cqappDeal: TKCWVQuery
    ID = '申请单处理'
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
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '申请日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '处理日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '申请单号'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '申请类型'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '申请状态'
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
    RequestType = 2018
    Left = 216
    Top = 10
  end
  object KCCancelApp: TKCWVProcessor
    ID = '申请单取消'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '申请单号'
        FieldName = 'lvol1'
        DefaultValue = 0
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
    RequestType = 2018
    KCDataset = Dataset
    Left = 214
    Top = 56
  end
  object KCMakeAnon: TKCWVProcessor
    ID = '不记名卡号生成'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡数量'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '卡类别'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '发卡单位'
        FieldName = 'lvol0'
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
      end
      item
        ParamName = '结束卡号'
        FieldName = 'lvol2'
      end
      item
        ParamName = '开始卡号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end>
    RequestType = 2019
    KCDataset = Dataset
    Left = 214
    Top = 104
  end
  object KCNonCardchange: TKCWVProcessor
    ID = '非记名换卡操作'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '申请单号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '原卡号'
        FieldName = 'scard1'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol7'
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
      end
      item
        ParamName = '终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol9'
      end
      item
        ParamName = '主机日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '主机时间'
        FieldName = 'stime1'
      end
      item
        ParamName = '流水号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end>
    RequestType = 2031
    KCDataset = Dataset
    Left = 214
    Top = 152
  end
  object KCTradeCancel: TKCWVProcessor
    ID = '交易冲正'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = '记账日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '交易参考号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '冲正操作员'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '冲正金额'
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
    RequestType = 2035
    KCDataset = Dataset
    Left = 214
    Top = 200
  end
  object cqSetPOSInfo: TKCWVQuery
    ID = '设备信息维护查询'
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
        ParamName = '设备终端号'
        FieldName = 'sname'
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
    Top = 218
  end
  object KCMachineConsume: TKCWVProcessor
    ID = '读卡器消费'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'sam流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '消费金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '卡余额'
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
      end
      item
        ParamName = '记账日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '交易参考号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol9'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end
      item
        ParamName = '记账时间'
        FieldName = 'stime3'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end>
    RequestType = 2036
    KCDataset = Dataset
    Left = 214
    Top = 248
  end
  object KCConsumeOk: TKCWVProcessor
    ID = '读卡器消费确认'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '交易日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易时间'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam终端号'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'sam流水号'
        FieldName = 'lserial0'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '记账日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '交易参考号'
        FieldName = 'scert_no'
      end
      item
        ParamName = 'TAC码'
        FieldName = 'sserial4'
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
        ParamName = '记账日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '交易参考号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol9'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone'
      end
      item
        ParamName = '记账时间'
        FieldName = 'stime3'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end>
    RequestType = 2036
    KCDataset = Dataset
    Left = 214
    Top = 296
  end
  object KCConsumeSerial: TKCWVQuery
    ID = '消费流水查询'
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
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡物理编号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '交易码'
        FieldName = 'spost_code'
      end
      item
        ParamName = '商户号'
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
    RequestType = 3002
    Left = 280
    Top = 26
  end
end
