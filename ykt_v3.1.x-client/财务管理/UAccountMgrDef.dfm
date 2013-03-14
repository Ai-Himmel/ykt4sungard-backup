inherited cmAccountMgrDef: TcmAccountMgrDef
  OldCreateOrder = True
  Left = 285
  object ctinAccountByMan: TWVCommandTypeInfo
    ID = '凭证科目查询'
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
      end
      item
        ParamName = '标志'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 24
    Top = 10
  end
  object cqVoucherAdd: TWVCommandTypeInfo
    ID = '凭证科目录入'
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
        ParamName = '标志'
      end
      item
        ParamName = '分录总条数'
        ParamType = ptOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '凭证类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '凭证日期'
      end
      item
        ParamName = '单据数'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '行号1'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '摘要1'
      end
      item
        ParamName = '科目代码1'
      end
      item
        ParamName = '借方金额1'
        ParamDataType = kdtFloat
        DefaultValue = 0
      end
      item
        ParamName = '贷方金额1'
        ParamDataType = kdtFloat
        DefaultValue = 0
      end
      item
        ParamName = '行号2'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '摘要2'
      end
      item
        ParamName = '科目代码2'
      end
      item
        ParamName = '借方金额2'
        ParamDataType = kdtFloat
        DefaultValue = 0
      end
      item
        ParamName = '贷方金额2'
        ParamDataType = kdtFloat
        DefaultValue = 0
      end
      item
        ParamName = '行号3'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '摘要3'
      end
      item
        ParamName = '科目代码3'
      end
      item
        ParamName = '借方金额3'
        ParamDataType = kdtFloat
        DefaultValue = 0
      end
      item
        ParamName = '贷方金额3'
        ParamDataType = kdtFloat
        DefaultValue = 0
      end
      item
        ParamName = '行号4'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '摘要4'
      end
      item
        ParamName = '科目代码4'
      end
      item
        ParamName = '借方金额4'
        ParamDataType = kdtFloat
        DefaultValue = 0
      end
      item
        ParamName = '贷方金额4'
        ParamDataType = kdtFloat
        DefaultValue = 0
      end
      item
        ParamName = '年'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '月'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '凭证号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '结算方式'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '结算号码'
      end>
    Left = 24
    Top = 58
  end
  object cqVoucherMgr: TWVCommandTypeInfo
    ID = '凭证处理.查询'
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
        ParamName = '标志'
      end
      item
        ParamName = '会计期间(年)'
        DefaultValue = 0
      end
      item
        ParamName = '会计期间(月)'
        DefaultValue = 0
      end
      item
        ParamName = '凭证日期'
      end
      item
        ParamName = '凭证类型'
        DefaultValue = 0
      end
      item
        ParamName = '凭证号'
        DefaultValue = 0
      end
      item
        ParamName = '科目代码'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '是否手工账凭证'
      end
      item
        ParamName = '入账状态'
      end
      item
        ParamName = '查询类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'ID'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '凭证结束日期'
      end>
    Left = 24
    Top = 106
  end
  object cqVOper: TWVCommandTypeInfo
    ID = '凭证处理'
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
        ParamName = '标志'
      end
      item
        ParamName = '会计期间(年)'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '会计期间(月)'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '凭证类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '凭证号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '凭证ID'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 24
    Top = 154
  end
  object cqOperPermissionQ: TWVCommandTypeInfo
    ID = '财务权限管理查询'
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
        ParamName = '标志'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '权限类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '操作员名称'
      end>
    Left = 24
    Top = 202
  end
  object cqOperPermission: TWVCommandTypeInfo
    ID = '财务权限管理'
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
        ParamName = '标志'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '权限类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 24
    Top = 250
  end
  object cqAccountRptQ: TWVCommandTypeInfo
    ID = '会计账簿查询'
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
        ParamName = '账簿类型'
      end>
    Left = 24
    Top = 298
  end
  object cq850061: TWVCommandTypeInfo
    ID = '总分类账查询'
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
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '结束日期'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目号'
      end
      item
        ParamName = '包含未入账'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 96
    Top = 34
  end
  object cq850062: TWVCommandTypeInfo
    ID = '日记账查询'
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
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '结束日期'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目号'
      end
      item
        ParamName = '包含未入账'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 96
    Top = 82
  end
  object cq850063: TWVCommandTypeInfo
    ID = '明细分类帐查询'
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
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '结束日期'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目号'
      end
      item
        ParamName = '包含未入账'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '查询方式'
      end>
    Left = 96
    Top = 130
  end
  object cq850065: TWVCommandTypeInfo
    ID = '科目汇总报表'
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
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '结束日期'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目级别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '包含未入账'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '查询方式'
      end
      item
        ParamName = '显示未交易'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 96
    Top = 178
  end
  object cq850070: TWVCommandTypeInfo
    ID = '结算汇总报表'
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
        ParamName = '年'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '月'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '日期'
      end
      item
        ParamName = '类型'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 96
    Top = 226
  end
  object cq850071: TWVCommandTypeInfo
    ID = '日终结转'
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
      end>
    Left = 96
    Top = 274
  end
  object cq850072: TWVCommandTypeInfo
    ID = '期末结转'
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
      end>
    Left = 96
    Top = 322
  end
  object cqQSubject: TWVCommandTypeInfo
    ID = '科目信息查询'
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
        ParamName = '序列号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目代码'
      end
      item
        ParamName = '助记码'
      end
      item
        ParamName = '科目级别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目性质'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '余额方向'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '标志'
      end>
    Left = 152
    Top = 10
  end
  object cqSetSubject: TWVCommandTypeInfo
    ID = '科目信息设置'
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
        ParamName = '标志'
      end
      item
        ParamName = '序列号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目代码'
      end
      item
        ParamName = '科目名称'
      end
      item
        ParamName = '助记码'
      end
      item
        ParamName = '科目类别'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '科目性质'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '余额方向'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '是否末级'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '现金科目'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '银行科目'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '一卡通科目'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '上级科目'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 152
    Top = 58
  end
end
