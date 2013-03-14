inherited cmPublishCardDef: TcmPublishCardDef
  OldCreateOrder = True
  Left = 454
  Top = 138
  object cqPubCardTrunk: TWVCommandTypeInfo
    ID = '发行卡trunk'
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
        ParamName = '操作员'
        ParamType = ptInputOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '显示卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '客户号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '票据号码'
      end
      item
        ParamName = '收费方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '客户类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '学工号'
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
        ParamName = '到期日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '卡号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡密码'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
        ParamDataType = kdtInteger
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
        ParamName = '是否不记名卡'
      end
      item
        ParamName = '终端编号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '单次限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '日限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '证件类型'
        ParamType = ptOutput
      end
      item
        ParamName = '发行方标识'
        ParamType = ptOutput
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end
      item
        ParamName = '充值次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '卡物理类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '卡内部编码'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '版本号'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 2
  end
  object cqStuChangeCardTrunk: TWVCommandTypeInfo
    ID = '新生换卡确认trunk'
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
        ParamName = '操作类型'
      end
      item
        ParamName = '原物理编号'
      end
      item
        ParamName = '原卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '原卡余额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '原卡交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '新卡物理编号'
      end
      item
        ParamName = '显示卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '到期日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '流水号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '终端编号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '学工号'
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
        ParamName = '卡号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡密码'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易次数'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '补助批次号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '单次限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '日限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end
      item
        ParamName = '证件类型'
        ParamType = ptOutput
      end
      item
        ParamName = '发行方标识'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '客户号'
        ParamType = ptOutput
      end
      item
        ParamName = '卡物理类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '卡内部编码'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '版本号'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 50
  end
  object cqRenewCardtrunk: TWVCommandTypeInfo
    ID = '补办卡trunk'
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
        ParamName = '操作员'
        ParamType = ptInputOutput
      end
      item
        ParamName = '显示卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '客户号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费方式'
      end
      item
        ParamName = '票据号码'
      end
      item
        ParamName = '收费金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '客户类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收卡成本费'
      end
      item
        ParamName = '客户姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '学工号'
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
        ParamName = '到期日期'
        ParamType = ptOutput
      end
      item
        ParamName = '卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡密码'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
        ParamDataType = kdtInteger
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
        ParamName = '终端编号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '单次限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '日限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '证件类型'
        ParamType = ptOutput
      end
      item
        ParamName = '发行方标识'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end
      item
        ParamName = '充值次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '卡物理类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '卡内部编码'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '版本号'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 98
  end
  object cqCardReRelease: TWVCommandTypeInfo
    ID = '回收再发行trunk'
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
        ParamName = '卡余额'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理编号'
      end
      item
        ParamName = '充值次数'
      end
      item
        ParamName = '交易次数'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
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
        ParamName = '收费类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡密码'
        ParamType = ptOutput
      end
      item
        ParamName = '有效期'
        ParamType = ptOutput
      end
      item
        ParamName = '单次限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '日限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务时间'
        ParamType = ptOutput
      end
      item
        ParamName = '终端编号'
        ParamType = ptOutput
      end
      item
        ParamName = '版本号'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 146
  end
  object WVWaterPriceQ: TWVCommandTypeInfo
    ID = '发卡水价查询'
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
        ParamName = '收费类别'
      end>
    Left = 24
    Top = 194
  end
end
