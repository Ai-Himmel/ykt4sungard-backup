inherited dmSysSetDef: TdmSysSetDef
  OldCreateOrder = True
  Left = 296
  Top = 224
  object cqSetDict: TWVCommandTypeInfo
    ID = '查询数据字典'
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
        ParamName = '名称'
      end
      item
        ParamName = '大类代码'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '小类代码'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 96
    Top = 146
  end
  object cpSetDict: TWVCommandTypeInfo
    ID = '设置数据字典'
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
        ParamName = '条目名称（字典大类）'
      end
      item
        ParamName = '子项代码（字典单元代码）'
      end
      item
        ParamName = '子项名称（字典单元内容）'
      end
      item
        ParamName = '大类名称'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 32
    Top = 210
  end
  object cqSetStation: TWVCommandTypeInfo
    ID = '站点信息查询'
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
        ParamName = '站点号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作类别'
      end>
    Left = 96
    Top = 50
  end
  object cpSetStation: TWVCommandTypeInfo
    ID = '设置站点'
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
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ip地址'
      end
      item
        ParamName = '网卡物理地址'
      end
      item
        ParamName = '机器名称'
      end
      item
        ParamName = '备注'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 32
    Top = 66
  end
  object cpResetOperPwd: TWVCommandTypeInfo
    ID = '重置密码'
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
      end
      item
        ParamName = '新密码'
      end>
    Left = 96
    Top = 194
  end
  object cqSetOperator: TWVCommandTypeInfo
    ID = '操作员查询'
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
        ParamName = '操作员代码'
      end
      item
        ParamName = '操作类别'
      end
      item
        ParamName = '状态'
      end>
    Left = 96
    Top = 242
  end
  object cpSetOperator: TWVCommandTypeInfo
    ID = '设置操作员'
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
        ParamName = '操作员代码'
      end
      item
        ParamName = '操作员姓名'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '地址'
      end
      item
        ParamName = '邮编'
      end
      item
        ParamName = '电子邮件'
      end
      item
        ParamName = '是否限制访问站点'
      end
      item
        ParamName = '操作员状态'
      end
      item
        ParamName = '操作员密码'
      end
      item
        ParamName = '功能权限'
      end
      item
        ParamName = '操作类别'
      end
      item
        ParamName = '菜单权限1'
      end
      item
        ParamName = '菜单权限2'
      end
      item
        ParamName = '菜单权限3'
      end
      item
        ParamName = '菜单权限4'
      end
      item
        ParamName = '网点号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '充值限额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '操作员类型'
      end>
    Left = 32
    Top = 18
  end
  object cqSetModuleAuth: TWVCommandTypeInfo
    ID = '权限模板查询'
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
        ParamName = '操作员'
      end
      item
        ParamName = '模板代码'
      end
      item
        ParamName = '操作类别'
        DefaultValue = 'R'
      end>
    Left = 160
    Top = 18
  end
  object cpSetModuleAuth: TWVCommandTypeInfo
    ID = '设置权限模板'
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
        ParamName = '模板代码'
      end
      item
        ParamName = '模板名称'
      end
      item
        ParamName = '功能权限'
      end
      item
        ParamName = '菜单权限1'
      end
      item
        ParamName = '菜单权限2'
      end
      item
        ParamName = '菜单权限3'
      end
      item
        ParamName = '菜单权限4'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 32
    Top = 114
  end
  object cqSetOperStation: TWVCommandTypeInfo
    ID = '操作员登录站点查询'
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
        ParamName = '操作员'
      end
      item
        ParamName = '站点号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作类别'
      end>
    Left = 160
    Top = 66
  end
  object cpSetOperStation: TWVCommandTypeInfo
    ID = '允许操作员登录站点'
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
      end
      item
        ParamName = '站点号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作类别'
      end>
    Left = 32
    Top = 162
  end
  object cpUpdOperPwd: TWVCommandTypeInfo
    ID = '修改密码'
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
        ParamName = '操作员代码'
      end
      item
        ParamName = '旧密码'
      end
      item
        ParamName = '新密码'
      end>
    Left = 96
    Top = 98
  end
  object cqSetSaveOper: TWVCommandTypeInfo
    ID = '设置充值操作员'
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
      end
      item
        ParamName = '操作员权限'
      end
      item
        ParamName = '密码'
      end>
    Left = 160
    Top = 112
  end
  object cqQOperCardBind: TWVCommandTypeInfo
    ID = '充值操作员卡绑定Q'
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
        ParamName = '交易类型'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '授权操作员'
      end
      item
        ParamName = '授权密码'
      end>
    Left = 160
    Top = 160
  end
  object cqOperCardBind: TWVCommandTypeInfo
    ID = '充值操作员卡绑定'
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
        ParamName = '交易类型'
      end
      item
        ParamName = '操作员号'
      end
      item
        ParamName = '卡号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '授权操作员'
      end
      item
        ParamName = '授权密码'
      end>
    Left = 160
    Top = 208
  end
  object cqCardInfoQuery: TWVCommandTypeInfo
    ID = '已开卡信息查询'
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
    Left = 160
    Top = 256
  end
end
