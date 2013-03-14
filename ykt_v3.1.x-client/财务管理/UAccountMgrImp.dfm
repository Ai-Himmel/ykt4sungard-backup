inherited cmAccountMgrImp: TcmAccountMgrImp
  OldCreateOrder = True
  Left = 285
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
  object conFB: TZConnection
    Protocol = 'sqlite-3'
    AutoCommit = False
    Left = 368
    Top = 65
  end
  object KCWAccountByMan: TKCWVQuery
    ID = '凭证科目查询'
    InputBindings = <
      item
        ParamName = '账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
        DefaultValue = ''
      end
      item
        ParamName = '标志'
        FieldName = 'lvol1'
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
      end
      item
        ParamName = '名称'
        FieldName = 'sbankname'
      end>
    RequestType = 847150
    Left = 22
    Top = 10
  end
  object kcVoucherAdd: TKCWVQuery
    ID = '凭证科目录入'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
        DefaultValue = ''
      end
      item
        ParamName = '标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '分录总条数'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '凭证类型'
        FieldName = 'lsafe_level'
        DefaultValue = 0
      end
      item
        ParamName = '凭证日期'
        FieldName = 'sorder0'
      end
      item
        ParamName = '单据数'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '行号1'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '摘要1'
        FieldName = 'snote'
      end
      item
        ParamName = '科目代码1'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '借方金额1'
        FieldName = 'damt1'
        DefaultValue = 0
      end
      item
        ParamName = '贷方金额1'
        FieldName = 'damt2'
        DefaultValue = 0
      end
      item
        ParamName = '行号2'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '摘要2'
        FieldName = 'snote2'
      end
      item
        ParamName = '科目代码2'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '借方金额2'
        FieldName = 'damt3'
        DefaultValue = 0
      end
      item
        ParamName = '贷方金额2'
        FieldName = 'damt4'
        DefaultValue = 0
      end
      item
        ParamName = '行号3'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '摘要3'
        FieldName = 'sbankname'
      end
      item
        ParamName = '科目代码3'
        FieldName = 'sphone'
      end
      item
        ParamName = '借方金额3'
        FieldName = 'damt5'
        DefaultValue = 0
      end
      item
        ParamName = '贷方金额3'
        FieldName = 'damt6'
        DefaultValue = 0
      end
      item
        ParamName = '行号4'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '摘要4'
        FieldName = 'sbankname2'
      end
      item
        ParamName = '科目代码4'
        FieldName = 'sphone2'
      end
      item
        ParamName = '借方金额4'
        FieldName = 'damt7'
        DefaultValue = 0
      end
      item
        ParamName = '贷方金额4'
        FieldName = 'damt8'
        DefaultValue = 0
      end
      item
        ParamName = '年'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '月'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '凭证号'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '结算号码'
        FieldName = 'sname2'
      end
      item
        ParamName = '结算方式'
        FieldName = 'lvol9'
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
    RequestType = 850050
    Left = 22
    Top = 58
  end
  object cqVoucherMgr: TKCWVQuery
    ID = '凭证处理.查询'
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
        ParamName = '会计期间(年)'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '会计期间(月)'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '凭证日期'
        FieldName = 'sorder0'
      end
      item
        ParamName = '凭证类型'
        FieldName = 'lsafe_level'
        DefaultValue = 0
      end
      item
        ParamName = '凭证号'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '科目代码'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '是否手工账凭证'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '入账状态'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '查询类型'
        FieldName = 'lvol9'
        DefaultValue = 0
      end
      item
        ParamName = 'ID'
        FieldName = 'lserial1'
        DefaultValue = 0
      end
      item
        ParamName = '凭证结束日期'
        FieldName = 'sorder1'
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
    RequestType = 850050
    Left = 24
    Top = 106
  end
  object kcVOper: TKCWVQuery
    ID = '凭证处理'
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
        ParamName = '会计期间(年)'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '会计期间(月)'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '凭证类型'
        FieldName = 'lsafe_level'
        DefaultValue = 0
      end
      item
        ParamName = '凭证号'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '凭证ID'
        FieldName = 'lserial1'
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
    RequestType = 850050
    Left = 24
    Top = 154
  end
  object kcOperPermissionQ: TKCWVQuery
    ID = '财务权限管理查询'
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
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '权限类别'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '操作员名称'
        FieldName = 'sall_name'
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
    RequestType = 850040
    Left = 24
    Top = 202
  end
  object kcOperPermission: TKCWVQuery
    ID = '财务权限管理'
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
        ParamName = '操作员号'
        FieldName = 'semp_no'
      end
      item
        ParamName = '权限类别'
        FieldName = 'lvol1'
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
    RequestType = 850040
    Left = 24
    Top = 250
  end
  object kcAccountRptQ: TKCWVQuery
    ID = '会计账簿查询'
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
        ParamName = '账簿类型'
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
    RequestType = 850060
    Left = 24
    Top = 298
  end
  object kc850061: TKCWVQuery
    ID = '总分类账查询'
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
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '结束日期'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '科目号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '包含未入账'
        FieldName = 'lcert_code'
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
    RequestType = 850061
    Left = 96
    Top = 34
  end
  object kc850062: TKCWVQuery
    ID = '日记账查询'
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
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '结束日期'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '科目号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '包含未入账'
        FieldName = 'lcert_code'
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
    RequestType = 850062
    Left = 96
    Top = 82
  end
  object kc850063: TKCWVQuery
    ID = '明细分类帐查询'
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
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '结束日期'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '科目号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '包含未入账'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '查询方式'
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
    RequestType = 850063
    Left = 96
    Top = 130
  end
  object kc850065: TKCWVQuery
    ID = '科目汇总报表'
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
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '结束日期'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '科目级别'
        FieldName = 'lvol1'
      end
      item
        ParamName = '包含未入账'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '查询方式'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '显示未交易'
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
    RequestType = 850065
    Left = 96
    Top = 178
  end
  object kc850070: TKCWVQuery
    ID = '结算汇总报表'
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
        ParamName = '年'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '月'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '日期'
        FieldName = 'sorder0'
      end
      item
        ParamName = '类型'
        FieldName = 'lvol1'
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
    RequestType = 850070
    Left = 96
    Top = 226
  end
  object kc850071: TKCWVQuery
    ID = '日终结转'
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
    RequestType = 850071
    Left = 96
    Top = 274
  end
  object kc850072: TKCWVQuery
    ID = '期末结转'
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
    RequestType = 850072
    Left = 96
    Top = 322
  end
  object kcQSubject: TKCWVQuery
    ID = '科目信息查询'
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
        ParamName = '序列号'
        FieldName = 'Lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '科目代码'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '助记码'
        FieldName = 'sname'
      end
      item
        ParamName = '科目级别'
        FieldName = 'Lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '科目类别'
        FieldName = 'Lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '科目性质'
        FieldName = 'Lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '余额方向'
        FieldName = 'Lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '标志'
        FieldName = 'sstatus0'
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
    RequestType = 850035
    Left = 152
    Top = 10
  end
  object cpSetSubject: TKCWVProcessor
    ID = '科目信息设置'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '上级科目'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '科目代码'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '科目名称'
        FieldName = 'sallname'
      end
      item
        ParamName = '助记码'
        FieldName = 'sname'
      end
      item
        ParamName = '科目类别'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '科目性质'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '余额方向'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '是否末级'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '现金科目'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '银行科目'
        FieldName = 'lvol7'
        DefaultValue = 0
      end
      item
        ParamName = '一卡通科目'
        FieldName = 'lvol8'
        DefaultValue = 0
      end
      item
        ParamName = '序列号'
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
      end>
    RequestType = 850035
    KCDataset = Dataset
    Left = 152
    Top = 56
  end
end
