inherited dmCardDef: TdmCardDef
  OldCreateOrder = True
  Left = 410
  Top = 153
  Height = 495
  Width = 626
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
      end
      item
        ParamName = 'psam卡号'
      end
      item
        ParamName = '本机流水号'
      end
      item
        ParamName = '本机日期'
      end
      item
        ParamName = '本机时间'
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end
      item
        ParamName = '卡号1'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 26
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
    Left = 24
    Top = 74
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
    Left = 24
    Top = 120
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
    Left = 24
    Top = 170
  end
  object cqAccountQ: TWVCommandTypeInfo
    ID = '账户信息查询'
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
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '发卡部门'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '卡物理编号'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '制卡日期'
      end
      item
        ParamName = '卡序列号'
      end
      item
        ParamName = '卡状态'
      end
      item
        ParamName = '查询类别'
      end>
    Left = 88
    Top = 50
  end
  object cqCardSericalQ: TWVCommandTypeInfo
    ID = '交易流水查询'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '发卡部门'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '卡物理编号'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '操作员'
      end>
    Left = 88
    Top = 98
  end
  object cqCardInfoQ: TWVCommandTypeInfo
    ID = '已发卡信息查询'
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
        ParamName = '发卡部门'
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '序列号'
      end
      item
        ParamName = '卡号'
      end>
    Left = 88
    Top = 154
  end
  object WVLoss_UN: TWVCommandTypeInfo
    ID = '挂失解挂'
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
        ParamName = '客户号'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '版本号'
        ParamType = ptOutput
      end
      item
        ParamName = 'psam卡号'
      end
      item
        ParamName = '本机流水号'
      end
      item
        ParamName = '本机日期'
      end
      item
        ParamName = '本机时间'
      end
      item
        ParamName = '卡类别'
        ParamType = ptOutput
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end>
    Left = 88
    Top = 202
  end
  object cqReturnMoney: TWVCommandTypeInfo
    ID = '充值查询'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '卡物理编号'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '交易码'
      end>
    Left = 88
    Top = 250
  end
  object WVRtnMoney: TWVCommandTypeInfo
    ID = '充值回退'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '应用序列号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '卡物理编号'
      end
      item
        ParamName = '交易前充值次数'
      end
      item
        ParamName = '交易前消费次数'
      end
      item
        ParamName = '卡余额'
        ParamType = ptInputOutput
      end
      item
        ParamName = '上笔sam终端号'
      end
      item
        ParamName = '上笔类型'
      end
      item
        ParamName = '上笔金额'
      end
      item
        ParamName = '上笔日期'
      end
      item
        ParamName = '上笔时间'
      end
      item
        ParamName = '操作员编号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '操作员流水'
        ParamType = ptInputOutput
      end
      item
        ParamName = '主机日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '主机时间'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类别'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end
      item
        ParamName = '参考号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '记账日期'
      end
      item
        ParamName = '备注'
      end>
    Left = 88
    Top = 298
  end
  object WVChangeCardA: TWVCommandTypeInfo
    ID = '换卡申请'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '换卡原因'
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '申请单号'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 34
  end
  object WVReNewApp: TWVCommandTypeInfo
    ID = '补办申请'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '换卡原因'
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 82
  end
  object WVDestoryApp: TWVCommandTypeInfo
    ID = '销户申请'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '销户原因'
      end
      item
        ParamName = '充值次数'
      end
      item
        ParamName = '消费次数'
      end
      item
        ParamName = '卡余额'
      end
      item
        ParamName = '上笔sam终端'
      end
      item
        ParamName = '上笔类型'
      end
      item
        ParamName = '上笔金额'
      end
      item
        ParamName = '上笔日期'
      end
      item
        ParamName = '上笔时间'
      end
      item
        ParamName = '主机日期'
        ParamType = ptOutput
      end
      item
        ParamName = '主机时间'
        ParamType = ptOutput
      end
      item
        ParamName = '终端号'
        ParamType = ptOutput
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 130
  end
  object WVReNewOper: TWVCommandTypeInfo
    ID = '补办操作'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '充值次数'
      end
      item
        ParamName = '消费次数'
      end
      item
        ParamName = '卡余额'
      end
      item
        ParamName = '终端号'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
      end
      item
        ParamName = '主机日期'
        ParamType = ptOutput
      end
      item
        ParamName = '主机时间'
        ParamType = ptOutput
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类别'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 178
  end
  object WVChangeCardOper: TWVCommandTypeInfo
    ID = '换卡操作'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '充值次数'
      end
      item
        ParamName = '消费次数'
      end
      item
        ParamName = '卡余额'
      end
      item
        ParamName = '终端号'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
      end
      item
        ParamName = '主机日期'
        ParamType = ptOutput
      end
      item
        ParamName = '主机时间'
        ParamType = ptOutput
      end
      item
        ParamName = '旧应用序列号'
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 226
  end
  object WVDestoryOper: TWVCommandTypeInfo
    ID = '销户操作'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end
      item
        ParamName = '退卡余额'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 274
  end
  object cqappDeal: TWVCommandTypeInfo
    ID = '申请单处理'
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
        ParamName = '申请日期'
      end
      item
        ParamName = '处理日期'
      end
      item
        ParamName = '申请单号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '申请类型'
      end
      item
        ParamName = '申请状态'
      end>
    Left = 208
    Top = 18
  end
  object WVCancelApp: TWVCommandTypeInfo
    ID = '申请单取消'
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
        ParamName = '申请单号'
      end>
    Left = 208
    Top = 66
  end
  object WVMakeAnonCNo: TWVCommandTypeInfo
    ID = '不记名卡号生成'
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
        ParamName = '发卡单位'
      end
      item
        ParamName = '卡类别'
      end
      item
        ParamName = '卡数量'
      end
      item
        ParamName = '批次号'
        ParamType = ptOutput
      end
      item
        ParamName = '开始卡号'
        ParamType = ptOutput
      end
      item
        ParamName = '结束卡号'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 114
  end
  object WVNonCardChange: TWVCommandTypeInfo
    ID = '非记名换卡操作'
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
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = '申请单号'
      end
      item
        ParamName = '原卡号'
      end
      item
        ParamName = '应用序列号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '充值次数'
      end
      item
        ParamName = '消费次数'
      end
      item
        ParamName = '卡余额'
      end
      item
        ParamName = '终端号'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
      end
      item
        ParamName = '主机日期'
        ParamType = ptOutput
      end
      item
        ParamName = '主机时间'
        ParamType = ptOutput
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end
      item
        ParamName = '卡号'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 162
  end
  object WVTradeCancel: TWVCommandTypeInfo
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
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = '记账日期'
      end
      item
        ParamName = '交易参考号'
      end
      item
        ParamName = '冲正操作员'
      end
      item
        ParamName = '冲正金额'
      end>
    Left = 208
    Top = 210
  end
  object cqSetPOSInfo: TWVCommandTypeInfo
    ID = '设备信息维护查询'
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
        ParamName = '设备终端号'
      end>
    Left = 24
    Top = 218
  end
  object WVMachineConsume: TWVCommandTypeInfo
    ID = '读卡器消费'
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
        ParamName = '交易标志'
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = 'sam流水号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '充值次数'
      end
      item
        ParamName = '消费次数'
      end
      item
        ParamName = '消费金额'
      end
      item
        ParamName = '卡余额'
      end
      item
        ParamName = '记账日期'
        ParamType = ptOutput
      end
      item
        ParamName = '交易参考号'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end
      item
        ParamName = '记账时间'
        ParamType = ptOutput
      end
      item
        ParamName = '卡号'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 258
  end
  object WVConsumeOk: TWVCommandTypeInfo
    ID = '读卡器消费确认'
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
        ParamName = '交易标志'
      end
      item
        ParamName = '交易日期'
      end
      item
        ParamName = '交易时间'
      end
      item
        ParamName = 'sam终端号'
      end
      item
        ParamName = 'sam流水号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '记账日期'
      end
      item
        ParamName = '交易参考号'
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
      end
      item
        ParamName = 'TAC码'
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '手机'
        ParamType = ptOutput
      end
      item
        ParamName = '记账时间'
        ParamType = ptOutput
      end
      item
        ParamName = '卡号'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 306
  end
  object WVConsumeSerial: TWVCommandTypeInfo
    ID = '消费流水查询'
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
        ParamName = '结束日期'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '卡物理编号'
      end
      item
        ParamName = '卡类型'
      end
      item
        ParamName = '交易码'
      end
      item
        ParamName = '商户号'
      end>
    Left = 280
    Top = 34
  end
end
