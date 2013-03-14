inherited dmBusinessManageDef: TdmBusinessManageDef
  OldCreateOrder = True
  Left = 264
  Top = 149
  Height = 491
  Width = 711
  object cqQueryBusinessByOther: TWVCommandTypeInfo
    ID = '商户信息非主键查询'
    Params = <
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
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
        ParamName = '商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '父商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '商户名称'
      end
      item
        ParamName = '商户类别'
      end
      item
        ParamName = '是否为独立核算'
      end
      item
        ParamName = '是否为叶节点'
      end
      item
        ParamName = '负责人姓名'
      end
      item
        ParamName = '负责人身份证号'
      end
      item
        ParamName = '费率类型'
      end
      item
        ParamName = '收搭伙费'
      end>
    Left = 32
    Top = 58
  end
  object cqQueryBusinessByKey: TWVCommandTypeInfo
    ID = '商户信息主键查询'
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
        ParamName = '商户标识'
      end
      item
        ParamName = '操作标志'
      end>
    Left = 32
    Top = 10
  end
  object cqsetBusiFate: TWVCommandTypeInfo
    ID = '浮动费率查询'
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
        ParamName = '编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '营业额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '折扣比例'
        ParamDataType = kdtFloat
      end>
    Left = 128
    Top = 178
  end
  object cpsetBusiFate: TWVCommandTypeInfo
    ID = '浮动费率设置'
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
        ParamName = '标志'
      end
      item
        ParamName = '编号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '营业额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '折扣比例'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '备注'
      end>
    Left = 128
    Top = 226
  end
  object cqfillBusiSaveMoney: TWVCommandTypeInfo
    ID = '充值商户存款'
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
        ParamName = '商户号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '存款金额'
        ParamType = ptInputOutput
      end
      item
        ParamName = '交易日期'
        ParamType = ptOutput
      end
      item
        ParamName = '操作员号'
        ParamType = ptOutput
      end
      item
        ParamName = '后台流水号'
        ParamType = ptOutput
      end
      item
        ParamName = '提成金额'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '帐户余额'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '商户名称'
        ParamType = ptOutput
      end
      item
        ParamName = '充值类型'
      end
      item
        ParamName = '票据号码'
      end>
    Left = 320
    Top = 122
  end
  object cqsetFillBusiEquInfo: TWVCommandTypeInfo
    ID = '充值商户设备查询'
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
        ParamName = '商户号'
      end
      item
        ParamName = '设备编号'
      end>
    Left = 224
    Top = 2
  end
  object cpsetFillBusiEquInfo: TWVCommandTypeInfo
    ID = '充值商户设备信息设置增加'
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
        ParamName = '商户号'
      end
      item
        ParamName = '设备编号'
      end>
    Left = 224
    Top = 50
  end
  object cpsetFillBusiEquInfoDel: TWVCommandTypeInfo
    ID = '充值商户设备信息设置删除'
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
        ParamName = '商户号'
      end
      item
        ParamName = '设备编号'
      end>
    Left = 224
    Top = 98
  end
  object cqsetFillEquOperInfo: TWVCommandTypeInfo
    ID = '设备操作员查询'
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
        ParamName = '设备编号'
      end
      item
        ParamName = '充值操作员号'
      end
      item
        ParamName = '状态'
      end>
    Left = 224
    Top = 146
  end
  object cpsetFillEquOperInfo: TWVCommandTypeInfo
    ID = '充值设备操作员设置添加'
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
        ParamName = '设备编号'
      end
      item
        ParamName = '充值操作员号'
      end
      item
        ParamName = '每日最大充值金额'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '是否指定设备'
      end
      item
        ParamName = '是否充值商户操作员'
      end>
    Left = 224
    Top = 194
  end
  object cpsetFillEquOperInfoEdit: TWVCommandTypeInfo
    ID = '充值设备操作员设置修改'
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
        ParamName = '设备编号'
      end
      item
        ParamName = '充值操作员号'
      end
      item
        ParamName = '每日最大充值金额'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '是否指定设备'
      end
      item
        ParamName = '是否充值商户操作员'
      end>
    Left = 224
    Top = 242
  end
  object cpsetFillEquOperInfoDel: TWVCommandTypeInfo
    ID = '充值设备操作员设置删除'
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
        ParamName = '设备编号'
      end
      item
        ParamName = '充值操作员号'
      end
      item
        ParamName = '状态'
      end
      item
        ParamName = '是否指定设备'
      end
      item
        ParamName = '是否充值商户操作员'
      end>
    Left = 224
    Top = 290
  end
  object cqfillOperEquBanding: TWVCommandTypeInfo
    ID = '操作员设备查询'
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
        ParamName = '设备编号'
      end
      item
        ParamName = '充值操作员号'
      end>
    Left = 128
    Top = 26
  end
  object cpfillOperEquBanding: TWVCommandTypeInfo
    ID = '充值操作员设备绑定'
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
        ParamName = '充值操作员号'
      end
      item
        ParamName = '设备编号'
      end>
    Left = 128
    Top = 74
  end
  object cpfillOperEquBandingDel: TWVCommandTypeInfo
    ID = '充值操作员设备绑定删除'
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
        ParamName = '充值操作员号'
      end
      item
        ParamName = '设备编号'
      end>
    Left = 128
    Top = 122
  end
  object cpSetBusinessInfo: TWVCommandTypeInfo
    ID = '商户信息设置'
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
        ParamName = '商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '父商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '商户名称'
      end
      item
        ParamName = '区域'
      end
      item
        ParamName = '部门'
      end
      item
        ParamName = '商户类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '独立核算'
      end
      item
        ParamName = '联系人'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '电子邮箱'
      end
      item
        ParamName = '地址'
      end
      item
        ParamName = '邮编'
      end
      item
        ParamName = '佣金类型'
      end
      item
        ParamName = '佣金费率'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '存款提成比率'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行帐号'
      end
      item
        ParamName = '银行帐户名'
      end
      item
        ParamName = '末级商户'
      end
      item
        ParamName = '是否收搭伙费'
      end>
    Left = 32
    Top = 106
  end
  object cqSetBusiFee: TWVCommandTypeInfo
    ID = '商户搭伙费查询'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end>
    Left = 320
    Top = 26
  end
  object cpSetBusiFee: TWVCommandTypeInfo
    ID = '商户搭伙费设置'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '费率'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '学校费率'
        ParamDataType = kdtFloat
      end>
    Left = 320
    Top = 74
  end
  object cqBusiSubjectLink: TWVCommandTypeInfo
    ID = '商户科目映射查询'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '对应科目名称'
      end
      item
        ParamName = '开户银行'
      end
      item
        ParamName = '银行账号'
      end>
    Left = 320
    Top = 170
  end
  object cpBusiSubjectLink: TWVCommandTypeInfo
    ID = '商户科目映射'
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
        ParamName = '商户号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '商户名称'
      end
      item
        ParamName = '对应科目号'
      end
      item
        ParamName = '对应科目名称'
      end
      item
        ParamName = '开户银行'
      end
      item
        ParamName = '银行账号'
      end
      item
        ParamName = '标志'
      end>
    Left = 320
    Top = 218
  end
  object cqSetBusiStruct: TWVCommandTypeInfo
    ID = '商户组织结构设置'
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
        ParamName = '商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '父商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '商户名称'
      end
      item
        ParamName = '区域'
      end
      item
        ParamName = '部门'
      end
      item
        ParamName = '商户类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '独立核算'
      end
      item
        ParamName = '联系人'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '电子邮箱'
      end
      item
        ParamName = '地址'
      end
      item
        ParamName = '邮编'
      end
      item
        ParamName = '佣金类型'
      end
      item
        ParamName = '佣金费率'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '存款提成比率'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行帐号'
      end
      item
        ParamName = '银行帐户名'
      end
      item
        ParamName = '末级商户'
      end
      item
        ParamName = '是否收搭伙费'
      end>
    Left = 32
    Top = 154
  end
  object cqQBusiStruct: TWVCommandTypeInfo
    ID = '商户组织结构查询'
    Params = <
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
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
        ParamName = '商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '父商户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '商户名称'
      end
      item
        ParamName = '商户类别'
      end
      item
        ParamName = '是否为独立核算'
      end
      item
        ParamName = '是否为叶节点'
      end
      item
        ParamName = '负责人姓名'
      end
      item
        ParamName = '负责人身份证号'
      end
      item
        ParamName = '费率类型'
      end
      item
        ParamName = '收搭伙费'
      end>
    Left = 32
    Top = 202
  end
end
