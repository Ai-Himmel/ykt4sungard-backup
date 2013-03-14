inherited dmCardDef: TdmCardDef
  OldCreateOrder = True
  Left = 319
  Top = 124
  Height = 577
  Width = 800
  object ctLossCard: TWVCommandTypeInfo
    ID = '挂失解挂'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '卡版本号'
        ParamType = ptOutput
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end>
    Left = 40
    Top = 148
  end
  object ctChangeCardPwd: TWVCommandTypeInfo
    ID = '修改卡密码'
    Params = <
      item
        ParamName = '卡标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '新密码'
      end
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end>
    Left = 120
    Top = 24
  end
  object WVMoneyIn: TWVCommandTypeInfo
    ID = '卡充值'
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
        ParamName = '卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '入卡金额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '充值类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '票据号码'
      end
      item
        ParamName = '充值金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡金额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '终端编号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end>
    Left = 40
    Top = 98
  end
  object ctTradeBusiInfo: TWVCommandTypeInfo
    ID = '未入账交易商户查询'
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
        ParamName = '终端机设备物理ID'
      end>
    Left = 120
    Top = 124
  end
  object cqManualTradeQ: TWVCommandTypeInfo
    ID = '未入账流水查询'
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
        ParamName = '发生日期'
      end
      item
        ParamName = '发生起始时间'
      end
      item
        ParamName = '发生截止时间'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '终端机物理ID'
      end
      item
        ParamName = '终端机流水号'
      end
      item
        ParamName = '钱包号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '状态'
      end>
    Left = 192
    Top = 140
  end
  object cpManualTrade: TWVCommandTypeInfo
    ID = '交易流水手工入账'
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
        ParamName = '发生日期'
      end
      item
        ParamName = '发生时间'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '终端机物理ID'
      end
      item
        ParamName = '终端机流水号'
      end
      item
        ParamName = '钱包号'
      end
      item
        ParamName = '入卡金额'
      end
      item
        ParamName = '出卡金额'
      end
      item
        ParamName = '交易金额'
      end
      item
        ParamName = '当前卡交易累计次数'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '交易标记'
      end
      item
        ParamName = '通信版本号'
      end
      item
        ParamName = '启动原因'
      end
      item
        ParamName = '商户ID'
      end
      item
        ParamName = '终端设备授权号'
      end
      item
        ParamName = '外接系统标识'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '采集时间戳'
      end
      item
        ParamName = '处理日期'
      end
      item
        ParamName = '处理时间'
      end>
    Left = 120
    Top = 76
  end
  object ctCardDestory: TWVCommandTypeInfo
    ID = '一卡通销户'
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
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否有卡'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡物理编号'
      end
      item
        ParamName = '卡余额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否退押金'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '金额精度'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '退款金额'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '补助批次号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
        ParamType = ptOutput
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end
      item
        ParamName = '充值次数'
      end>
    Left = 344
    Top = 98
  end
  object cqPatchAccount: TWVCommandTypeInfo
    ID = '补帐交易'
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
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '入卡值'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '工作站号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '当前卡交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '发生金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '复核员'
      end
      item
        ParamName = '复核员密码'
      end
      item
        ParamName = '搭伙费'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '充值金额'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '流水发生日期'
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '原流水号'
        ParamDataType = kdtInteger
      end>
    Left = 40
    Top = 50
  end
  object cqPatchAccQuery: TWVCommandTypeInfo
    ID = '补帐交易查询'
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
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '银行账号'
      end
      item
        ParamName = '状态'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '学工号'
      end>
    Left = 40
    Top = 2
  end
  object cqinAccountByMan: TWVCommandTypeInfo
    ID = '金额手工入帐'
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
        ParamName = '借方账号'
      end
      item
        ParamName = '贷方账号'
      end
      item
        ParamName = '发生金额'
      end
      item
        ParamName = '工作站号'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '错账操作员号'
      end
      item
        ParamName = '错账操作员密码'
      end>
    Left = 192
    Top = 2
  end
  object ctinAccountByMan: TWVCommandTypeInfo
    ID = '金额手工入帐查询'
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
        ParamName = '账号'
      end
      item
        ParamName = '名称'
        ParamType = ptOutput
      end>
    Left = 192
    Top = 50
  end
  object cpPubAuthCard: TWVCommandTypeInfo
    ID = '发行授权卡'
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
        ParamName = '操作员号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '授权卡权限'
        ParamType = ptInputOutput
      end
      item
        ParamName = '业务操作员'
      end
      item
        ParamName = '有效期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '交易卡号'
        ParamType = ptOutput
      end
      item
        ParamName = '工作密钥'
        ParamType = ptOutput
      end
      item
        ParamName = '操作员名称'
        ParamType = ptOutput
      end>
    Left = 280
    Top = 26
  end
  object cpauthCardOper: TWVCommandTypeInfo
    ID = '授权卡操作'
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
        ParamName = '交易卡号'
      end
      item
        ParamName = '操作员代码'
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '状态'
      end>
    Left = 280
    Top = 74
  end
  object cpmodifyAuthCard: TWVCommandTypeInfo
    ID = '修改授权卡参数'
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
        ParamName = '交易卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '更新有效期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '卡权限'
        ParamType = ptInputOutput
      end
      item
        ParamName = '业务操作员号'
      end>
    Left = 280
    Top = 122
  end
  object cpReturnAuthCard: TWVCommandTypeInfo
    ID = '授权卡回收'
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
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员代码'
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '无卡回收'
      end>
    Left = 280
    Top = 170
  end
  object cpLoseAuthCard: TWVCommandTypeInfo
    ID = '授权卡挂失'
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
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员代码'
      end
      item
        ParamName = '业务操作员号'
      end>
    Left = 280
    Top = 218
  end
  object cpRLoseAuthCard: TWVCommandTypeInfo
    ID = '授权卡解挂'
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
        ParamName = '交易卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员密码'
      end
      item
        ParamName = '业务操作员号'
      end
      item
        ParamName = '黑名单版本'
        ParamType = ptOutput
      end>
    Left = 280
    Top = 266
  end
  object WVCardCustInfoQuery: TWVCommandTypeInfo
    ID = '发卡客户信息查询'
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
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户姓名'
      end
      item
        ParamName = '部门'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属区域'
      end
      item
        ParamName = '专业'
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '注销日期'
      end
      item
        ParamName = '班级'
      end
      item
        ParamName = '发卡类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '卡类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 280
    Top = 312
  end
  object WVFeeQuery: TWVCommandTypeInfo
    ID = '发卡收费查询'
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
        ParamName = '功能号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费信息'
        ParamType = ptOutput
      end
      item
        ParamName = '总费用'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '是否不记名卡'
      end
      item
        ParamName = '卡有效期'
        ParamType = ptOutput
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 280
    Top = 354
  end
  object WVRelCardOk: TWVCommandTypeInfo
    ID = '发卡确认'
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
        ParamName = '终端编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
      end
      item
        ParamName = '开户操作员'
      end>
    Left = 280
    Top = 400
  end
  object WVCardInfoQuery: TWVCommandTypeInfo
    ID = '已开卡客户信息查询'
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
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户姓名'
      end
      item
        ParamName = '部门'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属区域'
      end
      item
        ParamName = '显示卡号'
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '注销日期'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '钱包号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '卡状态'
      end
      item
        ParamName = '补办标志'
      end
      item
        ParamName = '损坏原因'
      end
      item
        ParamName = '卡类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 344
    Top = 48
  end
  object ctFreezeCard: TWVCommandTypeInfo
    ID = '冻结解冻'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '卡版本号'
        ParamType = ptOutput
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end>
    Left = 40
    Top = 196
  end
  object WVMoneyOut: TWVCommandTypeInfo
    ID = '卡支取'
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
        ParamName = '卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '入卡金额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '充值次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '支取金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '出卡金额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '终端编号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end>
    Left = 120
    Top = 170
  end
  object WVcashOperCancel: TWVCommandTypeInfo
    ID = '充值支取冲正'
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
        ParamName = '流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
      end
      item
        ParamName = '终端编号'
        ParamDataType = kdtInteger
      end>
    Left = 344
    Top = 194
  end
  object WVAccountQuery: TWVCommandTypeInfo
    ID = '帐户信息查询'
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
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户姓名'
      end
      item
        ParamName = '部门'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '所属区域'
      end
      item
        ParamName = '显示卡号'
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '注销日期'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '钱包号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '卡状态'
      end
      item
        ParamName = '卡类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 344
    Top = 240
  end
  object cqcardTradeQuery: TWVCommandTypeInfo
    ID = '卡交易流水查询'
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
        ParamName = '开始日期'
      end
      item
        ParamName = '截止日期'
      end
      item
        ParamName = '终端编号'
      end
      item
        ParamName = '终端流水号'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '凭证号码'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '学/工号'
      end
      item
        ParamName = '显示卡号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '钱包号'
      end
      item
        ParamName = '流水状态'
      end
      item
        ParamName = '查询类型'
      end
      item
        ParamName = '交易开始日期'
      end
      item
        ParamName = '交易结束日期'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '联机状态'
      end
      item
        ParamName = '结束时间'
      end
      item
        ParamName = '开始时间'
      end
      item
        ParamName = '交易标志'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '外部类型'
        DefaultValue = 0
      end>
    Left = 40
    Top = 242
  end
  object WVTradeReserse: TWVCommandTypeInfo
    ID = '交易冲正'
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
        ParamName = '终端编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '操作员密码'
      end
      item
        ParamName = '冲正类型'
      end
      item
        ParamName = '是否授权'
      end>
    Left = 40
    Top = 288
  end
  object WVReverseOpenCard: TWVCommandTypeInfo
    ID = '开户冲正'
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
        ParamName = '终端编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '物理卡号'
        ParamType = ptOutput
      end
      item
        ParamName = '交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '验证操作员'
      end
      item
        ParamName = '操作员密码'
      end
      item
        ParamName = '是否授权'
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end>
    Left = 344
    Top = 288
  end
  object cqaccountTradeQuery: TWVCommandTypeInfo
    ID = '帐户交易明细查询'
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
        ParamName = '记账开始日期'
      end
      item
        ParamName = '记账截止日期'
      end
      item
        ParamName = '交易开始日期'
      end
      item
        ParamName = '交易截止日期'
      end
      item
        ParamName = '科目号'
      end
      item
        ParamName = '账号'
      end
      item
        ParamName = '帐户名'
      end
      item
        ParamName = '终端编号'
      end
      item
        ParamName = '终端流水号'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '凭证号码'
      end
      item
        ParamName = '商户号'
      end
      item
        ParamName = '显示卡号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '学工号'
      end>
    Left = 120
    Top = 218
  end
  object WVRevSaveMoney: TWVCommandTypeInfo
    ID = '充值冲正'
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
        ParamName = '业务日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '终端编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '操作员密码'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '卡交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '入卡值'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务时间'
        ParamType = ptInputOutput
      end
      item
        ParamName = '充值次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 344
    Top = 336
  end
  object WVRevConsume: TWVCommandTypeInfo
    ID = '消费冲正'
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
        ParamName = '业务日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '终端编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员'
      end
      item
        ParamName = '操作员密码'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '卡交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '入卡值'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end
      item
        ParamName = '充值次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 344
    Top = 384
  end
  object cpbadCardManage: TWVCommandTypeInfo
    ID = '坏卡登记'
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
        ParamName = '卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '损坏原因'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 120
    Top = 266
  end
  object WVRefreshCard: TWVCommandTypeInfo
    ID = '更新卡信息'
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
        ParamName = '卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '更新类型'
      end
      item
        ParamName = '显示卡号'
        ParamType = ptOutput
      end
      item
        ParamName = '客户类别'
        ParamType = ptOutput
      end
      item
        ParamName = '收费类别'
        ParamType = ptOutput
      end
      item
        ParamName = '学工号'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '部门代码'
        ParamType = ptOutput
      end
      item
        ParamName = '证件号码'
        ParamType = ptOutput
      end
      item
        ParamName = '性别'
        ParamType = ptOutput
      end
      item
        ParamName = '卡到期日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '卡余额'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易次数'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '补助批次号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡密码'
        ParamType = ptOutput
      end
      item
        ParamName = '单次限额'
        ParamType = ptOutput
      end
      item
        ParamName = '日限额'
        ParamType = ptOutput
      end
      item
        ParamName = '入单次限额'
      end
      item
        ParamName = '入日限额'
      end
      item
        ParamName = '证件类型'
        ParamType = ptOutput
      end
      item
        ParamName = '交易日期'
        ParamType = ptOutput
      end
      item
        ParamName = '交易时间'
        ParamType = ptOutput
      end
      item
        ParamName = '充值次数'
      end>
    Left = 192
    Top = 96
  end
  object cqcardLibNotBalance: TWVCommandTypeInfo
    ID = '卡库不平处理查询'
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
        ParamName = '卡号'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '卡库不平类型'
      end
      item
        ParamName = '不平金额阀值'
      end
      item
        ParamName = '统计日期'
      end
      item
        ParamName = '平账日期'
      end
      item
        ParamName = '平账操作员'
      end
      item
        ParamName = '平账状态'
      end
      item
        ParamName = '所属区域'
      end>
    Left = 120
    Top = 314
  end
  object cqcqcardLibNotBal: TWVCommandTypeInfo
    ID = '卡库不平处理'
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
        ParamName = '卡号'
      end
      item
        ParamName = '统计日期'
      end
      item
        ParamName = '平账方式'
      end>
    Left = 120
    Top = 362
  end
  object cqPubPASMCard: TWVCommandTypeInfo
    ID = 'PASM卡发行'
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
        ParamName = '启用日期'
      end
      item
        ParamName = '有效日期'
      end
      item
        ParamName = '设备使用方'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = 'pasm卡号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptInputOutput
      end
      item
        ParamName = '终端编号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '索引号'
        ParamType = ptOutput
      end
      item
        ParamName = '发行方标识'
        ParamType = ptOutput
      end>
    Left = 416
    Top = 16
  end
  object cqPASMEdit: TWVCommandTypeInfo
    ID = 'PASM卡修改'
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
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '密钥索引号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '使用方标识'
      end
      item
        ParamName = '有效日期'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 416
    Top = 64
  end
  object cqPASMDel: TWVCommandTypeInfo
    ID = 'PASM卡回收'
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
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '终端编号'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 416
    Top = 112
  end
  object cqPASMQuery: TWVCommandTypeInfo
    ID = 'PASM卡查询'
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
        ParamName = '卡号'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '使用方'
      end
      item
        ParamName = '有效期'
      end
      item
        ParamName = '卡状态'
      end>
    Left = 416
    Top = 160
  end
  object cqSetMoney: TWVCommandTypeInfo
    ID = '卡余额设置'
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
        ParamName = '物理卡号'
      end
      item
        ParamName = '入卡金额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '调整金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
        ParamType = ptOutput
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡金额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '终端编号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '验证操作员'
      end
      item
        ParamName = '验证密码'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '方向'
      end
      item
        ParamName = '充值次数'
      end>
    Left = 40
    Top = 338
  end
  object cqCollSerial_CPU: TWVCommandTypeInfo
    ID = 'CPU卡流水采集'
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
        ParamName = '站点号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '交易标志'
      end
      item
        ParamName = '消费次数'
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = '交易前余额'
      end
      item
        ParamName = '交易金额'
      end
      item
        ParamName = '搭伙费'
      end
      item
        ParamName = '补写金额'
      end
      item
        ParamName = '商户号'
      end
      item
        ParamName = '终端编号'
      end
      item
        ParamName = '交易序号'
      end>
    Left = 416
    Top = 210
  end
  object cqsmlPacket: TWVCommandTypeInfo
    ID = '小钱包操作'
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
        ParamName = '返回数据集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '小钱包号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '客户号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '转出卡号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '转入卡号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '小钱包金额'
        ParamType = ptInputOutput
        ParamDataType = kdtFloat
        DefaultValue = 0
      end>
    Left = 416
    Top = 264
  end
  object cqReturnSml: TWVCommandTypeInfo
    ID = '退小钱包操作'
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
        ParamName = '返回数据集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '终端号'
      end
      item
        ParamName = '有无卡标志'
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '钱包号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '小钱包消费次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '小钱包余额'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '主钱包充值次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '主钱包消费次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '主钱包余额'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'r主钱包余额'
        ParamType = ptOutput
      end
      item
        ParamName = 'r记账日期'
        ParamType = ptOutput
      end
      item
        ParamName = 'r记账时间'
        ParamType = ptOutput
      end
      item
        ParamName = 'r卡号'
        ParamType = ptOutput
      end>
    Left = 416
    Top = 312
  end
  object cqFeeCardLock: TWVCommandTypeInfo
    ID = '后付费解锁'
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
        ParamName = '卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '消费次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '入卡金额'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '锁卡设备'
      end
      item
        ParamName = '锁卡日期'
      end
      item
        ParamName = '锁卡时间'
      end
      item
        ParamName = '出卡金额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end
      item
        ParamName = '业务日期'
        ParamType = ptOutput
      end
      item
        ParamName = '扣款金额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '锁卡次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 416
    Top = 354
  end
end
