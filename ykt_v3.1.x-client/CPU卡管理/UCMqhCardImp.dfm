inherited dmCardImp: TdmCardImp
  OldCreateOrder = True
  Left = 320
  Top = 119
  Height = 621
  Width = 724
  object cpChangeCardPwd: TKCWVProcessor
    ID = '修改卡密码'
    InputBindings = <
      item
        ParamName = '卡标识'
        FieldName = 'lvol0'
      end
      item
        ParamName = '新密码'
        FieldName = 'scust_no'
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
    RequestType = 847111
    KCDataset = Dataset
    Left = 118
    Top = 24
  end
  object cqTradeBusiQuery: TKCWVQuery
    ID = '未入账交易商户查询'
    InputBindings = <
      item
        ParamName = '终端机设备物理ID'
        FieldName = 'sbank_pwd2'
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
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 847182
    Left = 118
    Top = 120
  end
  object cqManualTrade: TKCWVProcessor
    ID = '交易流水手工入账'
    InputBindings = <
      item
        ParamName = '发生日期'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '发生时间'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '终端机物理ID'
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '终端机流水号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '商户ID'
        FieldName = 'lvol12'
      end
      item
        ParamName = '外接系统标识'
        FieldName = 'lvol11'
      end
      item
        ParamName = '操作员'
        FieldName = 'sdate1'
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
    RequestType = 847181
    KCDataset = Dataset
    Left = 118
    Top = 74
  end
  object cpLossCard: TKCWVProcessor
    ID = '挂失解挂'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作标志'
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
      end
      item
        ParamName = '卡版本号'
        FieldName = 'sserial0'
      end>
    RequestType = 846307
    KCDataset = Dataset
    Left = 38
    Top = 144
  end
  object cpCardDestory: TKCWVProcessor
    ID = '一卡通销户'
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
        ParamName = '是否有卡'
        FieldName = 'lvol4'
      end
      item
        ParamName = '卡物理编号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '卡余额'
        FieldName = 'Lvol8'
      end
      item
        ParamName = '交易次数'
        FieldName = 'Lvol6'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
      end
      item
        ParamName = '金额精度'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '补助批次号'
        FieldName = 'lvol10'
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
        ParamName = '退款金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end>
    RequestType = 846303
    KCDataset = Dataset
    Left = 342
    Top = 96
  end
  object KCWPatchAccQuery: TKCWVQuery
    ID = '补帐交易查询'
    InputBindings = <
      item
        ParamName = '交易卡号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '银行账号'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '状态'
        FieldName = 'lvol2'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
        DefaultValue = ''
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
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
    RequestType = 847185
    Left = 40
    Top = 2
  end
  object cqPatchAcc: TKCWVProcessor
    ID = '补帐交易'
    InputBindings = <
      item
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '入卡值'
        FieldName = 'damt0'
      end
      item
        ParamName = '工作站号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '当前卡交易次数'
        FieldName = 'lvol1'
      end
      item
        ParamName = '操作员'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '发生金额'
        FieldName = 'damt1'
      end
      item
        ParamName = '复核员'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '复核员密码'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '流水发生日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '原流水号'
        FieldName = 'lserial0'
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
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '出卡值'
        FieldName = 'damt4'
      end
      item
        ParamName = '搭伙费'
        FieldName = 'damt3'
      end
      item
        ParamName = '充值金额'
        FieldName = 'damt2'
      end>
    RequestType = 240157
    KCDataset = Dataset
    Left = 40
    Top = 50
  end
  object cpinAccountByMan: TKCWVProcessor
    ID = '金额手工入帐'
    InputBindings = <
      item
        ParamName = '借方账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '贷方账号'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '发生金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '工作站号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '错账操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '错账操作员密码'
        FieldName = 'scust_limit'
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
    RequestType = 847127
    KCDataset = Dataset
    Left = 190
  end
  object KCWAccountByMan: TKCWVQuery
    ID = '金额手工入帐查询'
    InputBindings = <
      item
        ParamName = '账号'
        FieldName = 'sbank_acc'
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
        ParamName = '名称'
        FieldName = 'sbankname'
      end>
    RequestType = 847150
    Left = 190
    Top = 50
  end
  object KCWManualTradeQ: TKCWVQuery
    ID = '未入账流水查询'
    InputBindings = <
      item
        ParamName = '发生日期'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '发生起始时间'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '发生截止时间'
        FieldName = 'sbank_code2'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '终端机物理ID'
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '终端机流水号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol2'
      end
      item
        ParamName = '状态'
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
    RequestType = 847180
    Left = 190
    Top = 146
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 32
    Top = 336
  end
  object cqPubAuthCard1: TKCWVProcessor
    ID = '发行授权卡'
    InputBindings = <
      item
        ParamName = '操作员号'
        FieldName = 'sname2'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sname'
      end
      item
        ParamName = '授权卡权限'
        FieldName = 'lvol0'
      end
      item
        ParamName = '业务操作员'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '有效期'
        FieldName = 'sdate2'
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
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作员号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '有效期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '授权卡权限'
        FieldName = 'lvol1'
      end
      item
        ParamName = '工作密钥'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '操作员名称'
        FieldName = 'scust_limit2'
      end>
    RequestType = 847226
    KCDataset = Dataset
    Left = 278
    Top = 24
  end
  object cqauthCardOper: TKCWVQuery
    ID = '授权卡操作'
    InputBindings = <
      item
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作员代码'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sname'
      end
      item
        ParamName = '状态'
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
    RequestType = 847231
    Left = 278
    Top = 66
  end
  object cqmodifyAuthCard: TKCWVQuery
    ID = '修改授权卡参数'
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
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '更新有效期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '卡权限'
        FieldName = 'lvol1'
      end
      item
        ParamName = '业务操作员号'
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
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '更新有效期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '卡权限'
        FieldName = 'lvol1'
      end>
    RequestType = 847228
    Left = 278
    Top = 114
  end
  object cqReturnCardAuth: TKCWVProcessor
    ID = '授权卡回收'
    InputBindings = <
      item
        ParamName = '物理卡号'
        FieldName = 'sdate0'
      end
      item
        ParamName = '操作员代码'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '无卡回收'
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
    RequestType = 847227
    KCDataset = Dataset
    Left = 278
    Top = 160
  end
  object cqLoseAuthCard: TKCWVProcessor
    ID = '授权卡挂失'
    InputBindings = <
      item
        ParamName = '操作员代码'
        FieldName = 'sname'
      end
      item
        ParamName = '业务操作员号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '交易卡号'
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
      end>
    RequestType = 847229
    KCDataset = Dataset
    Left = 278
    Top = 208
  end
  object cqRLoseAuthCard: TKCWVProcessor
    ID = '授权卡解挂'
    InputBindings = <
      item
        ParamName = '操作员密码'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '业务操作员号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '交易卡号'
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
        ParamName = '交易卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '黑名单版本'
        FieldName = 'sserial0'
      end>
    RequestType = 847230
    KCDataset = Dataset
    Left = 278
    Top = 256
  end
  object KCWCardCustInfoQuery: TKCWVQuery
    ID = '发卡客户信息查询'
    InputBindings = <
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '部门'
        FieldName = 'scert_no'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
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
        ParamName = '所属区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '专业'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '注销日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '班级'
        FieldName = 'scard1'
      end
      item
        ParamName = '发卡类别'
        FieldName = 'lsafe_level'
        DefaultValue = 0
      end
      item
        ParamName = '卡类型'
        FieldName = 'lserial0'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 846600
    Left = 278
    Top = 304
  end
  object cqFeeQuery: TKCWVProcessor
    ID = '发卡收费查询'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '功能号'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '是否不记名卡'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
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
        ParamName = '收费信息'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '总费用'
        FieldName = 'damt0'
      end
      item
        ParamName = '卡有效期'
        FieldName = 'sdate0'
      end>
    RequestType = 846601
    KCDataset = Dataset
    Left = 278
    Top = 352
  end
  object cqRelCardOk: TKCWVProcessor
    ID = '发卡确认'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '开户操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '终端编号'
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
    RequestType = 846302
    KCDataset = Dataset
    Left = 278
    Top = 400
  end
  object KCWCardInfoQuery: TKCWVQuery
    ID = '已开卡客户信息查询'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '部门'
        FieldName = 'scert_no'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
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
        ParamName = '所属区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '注销日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation1'
      end
      item
        ParamName = '卡状态'
        FieldName = 'sserial0'
      end
      item
        ParamName = '补办标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '损坏原因'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lserial0'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 846602
    Left = 342
    Top = 48
  end
  object cqFreezeCard: TKCWVProcessor
    ID = '冻结解冻'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作标志'
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
      end
      item
        ParamName = '卡版本号'
        FieldName = 'sserial0'
      end>
    RequestType = 846308
    KCDataset = Dataset
    Left = 38
    Top = 192
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
        FieldName = 'lvol0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '入卡金额'
        FieldName = 'lvol7'
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
        FieldName = 'lvol9'
      end
      item
        ParamName = '票据号码'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '充值金额'
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
    RequestType = 846312
    KCDataset = Dataset
    Left = 38
    Top = 96
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
    Left = 118
    Top = 168
  end
  object cqcashOperCancel: TKCWVProcessor
    ID = '充值支取冲正'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
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
    RequestType = 846315
    KCDataset = Dataset
    Left = 342
    Top = 192
  end
  object KCWAccountQuery: TKCWVQuery
    ID = '帐户信息查询'
    InputBindings = <
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '部门'
        FieldName = 'scert_no'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
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
        ParamName = '所属区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '注销日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation1'
      end
      item
        ParamName = '卡状态'
        FieldName = 'sserial0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lserial0'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 846602
    Left = 342
    Top = 240
  end
  object cqcardTradeQuery: TKCWVQuery
    ID = '卡交易流水查询'
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
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '截止日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '终端流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '凭证号码'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '学/工号'
        FieldName = 'spager'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '流水状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '查询类型'
        FieldName = 'sstatus4'
      end
      item
        ParamName = '交易开始日期'
        FieldName = 'stime1'
      end
      item
        ParamName = '交易结束日期'
        FieldName = 'stime2'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '联机状态'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '开始时间'
        FieldName = 'sorder1'
      end
      item
        ParamName = '结束时间'
        FieldName = 'sorder2'
      end
      item
        ParamName = '交易标志'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '外部类型'
        FieldName = 'lsafe_level'
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
    RequestType = 846605
    Left = 40
    Top = 242
  end
  object cqTradeReserse: TKCWVProcessor
    ID = '交易冲正'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '冲正类型'
        FieldName = 'Sstatus3'
      end
      item
        ParamName = '是否授权'
        FieldName = 'Sstatus2'
      end
      item
        ParamName = '操作员密码'
        FieldName = 'scust_limit'
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
    RequestType = 846315
    KCDataset = Dataset
    Left = 38
    Top = 288
  end
  object cqReverseOpenCard: TKCWVProcessor
    ID = '开户冲正'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '验证操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '操作员密码'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '是否授权'
        FieldName = 'sstatus2'
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
        ParamName = '物理卡号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end>
    RequestType = 846302
    KCDataset = Dataset
    Left = 342
    Top = 288
  end
  object cqaccountTradeQuery: TKCWVQuery
    ID = '帐户交易明细查询'
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
        ParamName = '记账开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '记账截止日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '交易开始日期'
        FieldName = 'stime1'
      end
      item
        ParamName = '交易截止日期'
        FieldName = 'stime2'
      end
      item
        ParamName = '科目号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '帐户名'
        FieldName = 'sbankname'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '终端流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '交易码'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '凭证号码'
        FieldName = 'scard1'
      end
      item
        ParamName = '商户号'
        FieldName = 'lvol2'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
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
    RequestType = 846606
    Left = 120
    Top = 210
  end
  object cqRevSaveMoney: TKCWVProcessor
    ID = '充值冲正'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '操作员密码'
        FieldName = 'scust_limit'
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
        ParamName = '入卡值'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '卡交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
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
        ParamName = '出卡值'
        FieldName = 'lvol8'
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end>
    RequestType = 846316
    KCDataset = Dataset
    Left = 342
    Top = 336
  end
  object cqRevConsume: TKCWVProcessor
    ID = '消费冲正'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '操作员密码'
        FieldName = 'scust_limit'
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
        ParamName = '入卡值'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '卡交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
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
        ParamName = '出卡值'
        FieldName = 'lvol8'
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end>
    RequestType = 846317
    KCDataset = Dataset
    Left = 342
    Top = 384
  end
  object cpbadCardManage: TKCWVProcessor
    ID = '坏卡登记'
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
        ParamName = '损坏原因'
        FieldName = 'sstatus1'
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
    RequestType = 846309
    KCDataset = Dataset
    Left = 120
    Top = 258
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
    Left = 190
    Top = 96
  end
  object cqcardLibNotBalance: TKCWVQuery
    ID = '卡库不平处理查询'
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
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '客户号'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '卡库不平类型'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '不平金额阀值'
        FieldName = 'Lvol10'
      end
      item
        ParamName = '统计日期'
        FieldName = 'Sdate0'
      end
      item
        ParamName = '平账日期'
        FieldName = 'Sdate3'
      end
      item
        ParamName = '平账操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '平账状态'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '所属区域'
        FieldName = 'sbranch_code0'
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
    RequestType = 846115
    Left = 120
    Top = 306
  end
  object cpCardLibBal: TKCWVProcessor
    ID = '卡库不平处理'
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
        ParamName = '统计日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '平账方式'
        FieldName = 'Sstatus2'
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
    RequestType = 846116
    KCDataset = Dataset
    Left = 120
    Top = 354
  end
  object cppubPASMCard: TKCWVProcessor
    ID = 'PASM卡发行'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '启用日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '有效日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '设备使用方'
        FieldName = 'sholder_ac_no2'
      end
      item
        ParamName = '操作标志'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '终端编号'
        FieldName = 'sserial0'
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
        ParamName = 'pasm卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol5'
      end
      item
        ParamName = '终端编号'
        FieldName = 'Sserial0'
      end
      item
        ParamName = '索引号'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '发行方标识'
        FieldName = 'sholder_ac_no'
      end>
    RequestType = 845001
    KCDataset = Dataset
    Left = 414
    Top = 24
  end
  object cpPASMEdit: TKCWVProcessor
    ID = 'PASM卡修改'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '密钥索引号'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '使用方标识'
        FieldName = 'sholder_ac_no2'
      end
      item
        ParamName = '有效日期'
        FieldName = 'Sdate2'
      end
      item
        ParamName = '状态'
        FieldName = 'Sstatus1'
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
    RequestType = 845001
    KCDataset = Dataset
    Left = 414
    Top = 72
  end
  object cpPASMDel: TKCWVProcessor
    ID = 'PASM卡回收'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '终端编号'
        FieldName = 'Sserial0'
      end
      item
        ParamName = '操作标志'
        FieldName = 'Sstatus0'
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
    RequestType = 845001
    KCDataset = Dataset
    Left = 414
    Top = 120
  end
  object kcPASMQuery: TKCWVQuery
    ID = 'PASM卡查询'
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
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lvol5'
      end
      item
        ParamName = '使用方'
        FieldName = 'sholder_ac_no2'
      end
      item
        ParamName = '有效期'
        FieldName = 'Sdate0'
      end
      item
        ParamName = '卡状态'
        FieldName = 'sstatus1'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end>
    RequestType = 845001
    Left = 414
    Top = 168
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
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '调整金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
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
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end>
    RequestType = 846322
    KCDataset = Dataset
    Left = 38
    Top = 384
  end
  object cpCollSerial_CPU: TKCWVProcessor
    ID = 'CPU卡流水采集'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '站点号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易标志'
        FieldName = 'lvol2'
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol6'
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
        ParamName = '交易前余额'
        FieldName = 'lvol7'
      end
      item
        ParamName = '交易金额'
        FieldName = 'lvol8'
      end
      item
        ParamName = '搭伙费'
        FieldName = 'lvol9'
      end
      item
        ParamName = '补写金额'
        FieldName = 'lvol10'
      end
      item
        ParamName = '商户号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '终端编号'
        FieldName = 'sserial0'
      end
      item
        ParamName = '交易序号'
        FieldName = 'lserial0'
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
    RequestType = 860001
    KCDataset = Dataset
    Left = 416
    Top = 218
  end
  object cpsmlpacket: TKCWVProcessor
    ID = '小钱包操作'
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
        ParamName = '小钱包号'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '转出卡号'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '转入卡号'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '小钱包金额'
        FieldName = 'damt0'
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
        ParamName = '小钱包号'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '小钱包金额'
        FieldName = 'damt0'
        DefaultValue = 0
      end>
    RequestType = 847401
    KCDataset = Dataset
    Left = 416
    Top = 264
  end
  object cpReturnSml: TKCWVProcessor
    ID = '退小钱包操作'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '终端号'
        FieldName = 'lwithdraw_flag'
        DefaultValue = 0
      end
      item
        ParamName = '有无卡标志'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation1'
        DefaultValue = 0
      end
      item
        ParamName = '钱包号'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '小钱包消费次数'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '小钱包余额'
        FieldName = 'lsafe_level'
        DefaultValue = 0
      end
      item
        ParamName = '主钱包充值次数'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '主钱包消费次数'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '主钱包余额'
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
        ParamName = 'r主钱包余额'
        FieldName = 'lvol9'
        DefaultValue = 0
      end
      item
        ParamName = 'r记账日期'
        FieldName = 'sdate3'
        DefaultValue = 0
      end
      item
        ParamName = 'r记账时间'
        FieldName = 'stime3'
        DefaultValue = 0
      end
      item
        ParamName = 'r卡号'
        FieldName = 'lvol0'
      end>
    RequestType = 850020
    KCDataset = Dataset
    Left = 416
    Top = 312
  end
  object cpFeeCardLock: TKCWVProcessor
    ID = '后付费解锁'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '入卡金额'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '锁卡设备'
        FieldName = 'sphone'
      end
      item
        ParamName = '锁卡日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '锁卡时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '锁卡次数'
        FieldName = 'lvol3'
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
        ParamName = '出卡金额'
        FieldName = 'lvol5'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '扣款金额'
        FieldName = 'lvol4'
        DefaultValue = 0
      end>
    RequestType = 850011
    KCDataset = Dataset
    Left = 414
    Top = 360
  end
end
