inherited dmSysSetImp: TdmSysSetImp
  OldCreateOrder = True
  Left = 315
  Top = 164
  Height = 492
  Width = 649
  object DataSet: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 368
    Top = 32
  end
  object cqSetDict: TKCWVQuery
    ID = '查询数据字典'
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
        ParamName = '名称'
        FieldName = 'semail'
      end
      item
        ParamName = '大类代码'
        FieldName = 'lvol0'
      end
      item
        ParamName = '小类代码'
        FieldName = 'semail2'
      end
      item
        ParamName = '操作类别'
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
    RequestType = 820511
    Left = 96
    Top = 90
  end
  object cpSetDict: TKCWVProcessor
    ID = '设置数据字典'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'scust_no'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '条目名称（字典大类）'
        FieldName = 'lvol0'
      end
      item
        ParamName = '子项代码（字典单元代码）'
        FieldName = 'sorder0'
      end
      item
        ParamName = '子项名称（字典单元内容）'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '大类名称'
        FieldName = 'sbank_acc2'
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
    RequestType = 820511
    KCDataset = DataSet
    Left = 168
    Top = 26
  end
  object cqSetStation: TKCWVQuery
    ID = '站点信息查询'
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
        ParamName = '站点号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '操作类别'
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
    RequestType = 820341
    Left = 32
    Top = 26
  end
  object cpSetStation: TKCWVProcessor
    ID = '设置站点'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '站点号'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ip地址'
        FieldName = 'sphone'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = 'sphone2'
      end
      item
        ParamName = '机器名称'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '备注'
        FieldName = 'snote'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
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
    RequestType = 820341
    KCDataset = DataSet
    Left = 32
    Top = 218
  end
  object cpUpdOperPwd: TKCWVProcessor
    ID = '修改密码'
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
        ParamName = '操作员代码'
        FieldName = 'scust_no'
      end
      item
        ParamName = '旧密码'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '新密码'
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
    RequestType = 820331
    KCDataset = DataSet
    Left = 32
    Top = 74
  end
  object cqSetOperator: TKCWVQuery
    ID = '操作员查询'
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
        ParamName = '操作员代码'
        FieldName = 'scust_no'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '状态'
        FieldName = 'sstatus3'
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
    RequestType = 820301
    Left = 96
    Top = 42
  end
  object cpSetOperator: TKCWVProcessor
    ID = '设置操作员'
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
        ParamName = '操作类别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '操作员代码'
        FieldName = 'scust_no'
      end
      item
        ParamName = '操作员姓名'
        FieldName = 'sname'
      end
      item
        ParamName = '操作员类型'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '网点号'
        FieldName = 'lbank_acc_type2'
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
        ParamName = '电子邮件'
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
        ParamName = '是否限制访问站点'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '操作员状态'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '操作员密码'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '功能权限'
        FieldName = 'usset1'
      end
      item
        ParamName = '菜单权限1'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '菜单权限2'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '菜单权限3'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '菜单权限4'
        FieldName = 'vsvarstr3'
      end
      item
        ParamName = '充值限额'
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
    RequestType = 820301
    KCDataset = DataSet
    Left = 32
    Top = 122
  end
  object cqSetModuleAuth: TKCWVQuery
    ID = '权限模板查询'
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
        ParamName = '模板代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '操作类别'
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
    RequestType = 820311
    Left = 96
    Top = 186
  end
  object cpSetModuleAuth: TKCWVProcessor
    ID = '设置权限模板'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'scust_no'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '模板代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '模板名称'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '功能权限'
        FieldName = 'usset1'
      end
      item
        ParamName = '菜单权限1'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '菜单权限2'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '菜单权限3'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '菜单权限4'
        FieldName = 'vsvarstr3'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
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
    RequestType = 820311
    KCDataset = DataSet
    Left = 32
    Top = 170
  end
  object cqSetOperStation: TKCWVQuery
    ID = '操作员登录站点查询'
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
        ParamName = '操作员'
        FieldName = 'scust_no'
      end
      item
        ParamName = '站点号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '操作类别'
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
    RequestType = 820321
    Left = 96
    Top = 138
  end
  object cpSetOperStation: TKCWVProcessor
    ID = '允许操作员登录站点'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '操作员'
        FieldName = 'scust_no'
      end
      item
        ParamName = '站点号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
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
    RequestType = 820321
    KCDataset = DataSet
    Left = 96
    Top = 234
  end
  object cpResetOperPwd: TKCWVProcessor
    ID = '重置密码'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '操作员'
        FieldName = 'scust_no'
      end
      item
        ParamName = '新密码'
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
    RequestType = 820332
    KCDataset = DataSet
    Left = 168
    Top = 74
  end
  object cpSetSaveOper: TKCWVProcessor
    ID = '设置充值操作员'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'scust_no2'
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
        ParamName = '操作员'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '操作员权限'
        FieldName = 'lvol0'
      end
      item
        ParamName = '密码'
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
    RequestType = 820305
    KCDataset = DataSet
    Left = 168
    Top = 122
  end
  object cpOperCardBind: TKCWVProcessor
    ID = '充值操作员卡绑定'
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
        ParamName = '交易类型'
        FieldName = 'sstation0'
      end
      item
        ParamName = '操作员号'
        FieldName = 'sname'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '授权操作员'
        FieldName = 'semp_no'
      end
      item
        ParamName = '授权密码'
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
    RequestType = 846210
    KCDataset = DataSet
    Left = 168
    Top = 218
  end
  object kcQOperCardBind: TKCWVQuery
    ID = '充值操作员卡绑定Q'
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
        ParamName = '交易类型'
        FieldName = 'sstation0'
      end
      item
        ParamName = '操作员号'
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
    RequestType = 846210
    Left = 168
    Top = 170
  end
  object kcCardInfoQuery: TKCWVQuery
    ID = '已开卡信息查询'
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
    Left = 166
    Top = 264
  end
end
