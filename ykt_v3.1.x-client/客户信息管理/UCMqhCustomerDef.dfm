inherited dmCustomerDef: TdmCustomerDef
  OldCreateOrder = True
  Left = 246
  Top = 152
  Height = 457
  Width = 628
  object cqQueryCustomer: TWVCommandTypeInfo
    ID = '客户信息查询'
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
        ParamName = '客户所在区域'
      end
      item
        ParamName = '联系人单位号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户名称'
      end
      item
        ParamName = '客户状态'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '联系人身份证号'
      end
      item
        ParamName = '联系人民族'
      end
      item
        ParamName = '联系人性别'
      end
      item
        ParamName = '联系人学工号'
      end
      item
        ParamName = '注册日期'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '班级'
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '电子钱包'
      end
      item
        ParamName = '专业'
      end>
    Left = 32
    Top = 18
  end
  object WVsetCustInfo: TWVCommandTypeInfo
    ID = '客户信息设置'
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
        ParamName = '联系地址'
      end
      item
        ParamName = '客户所在区域'
      end
      item
        ParamName = '预计注销时间'
      end
      item
        ParamName = '联系人班级或部门名称'
      end
      item
        ParamName = '联系人班级或部门号'
      end
      item
        ParamName = '备注'
      end
      item
        ParamName = '客户名称'
      end
      item
        ParamName = '客户类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '联系人姓名'
      end
      item
        ParamName = '联系人身份证号'
      end
      item
        ParamName = '联系人民族'
      end
      item
        ParamName = '联系人性别'
      end
      item
        ParamName = '联系人学号或员工号'
      end
      item
        ParamName = '联系电话'
      end
      item
        ParamName = '收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '专业'
      end
      item
        ParamName = '国籍'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '电子邮箱'
      end
      item
        ParamName = '邮编'
      end
      item
        ParamName = '入学日期'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易类型'
      end
      item
        ParamName = '批量标志'
      end>
    Left = 32
    Top = 66
  end
  object cqQueryCustomerKind: TWVCommandTypeInfo
    ID = '客户类别查询'
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
        ParamName = '客户类别代码'
      end
      item
        ParamName = '交易类型'
      end>
    Left = 120
    Top = 34
  end
  object cpSetCustomerKindInfo: TWVCommandTypeInfo
    ID = '客户类别信息设置'
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
        ParamName = '客户类别代码'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户类别名称'
      end
      item
        ParamName = '默认收费类别'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易类型'
      end>
    Left = 120
    Top = 82
  end
  object cpImportCustomerInfo: TWVCommandTypeInfo
    ID = '客户信息导入'
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
        ParamName = '批次号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '序号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否传送完毕'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '学工号'
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
        ParamName = '姓名'
      end
      item
        ParamName = '校区'
      end
      item
        ParamName = '所属部门'
      end
      item
        ParamName = '专业'
      end
      item
        ParamName = '班级'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '性别'
      end
      item
        ParamName = '国籍'
      end
      item
        ParamName = '民族'
      end
      item
        ParamName = '电子邮箱'
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
        ParamName = '入校日期'
      end
      item
        ParamName = '预计离校日期'
      end>
    Left = 32
    Top = 114
  end
  object cpShImportCustomerInfo: TWVCommandTypeInfo
    ID = '客户导入信息设置.审核'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '导入顺序号'
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end
      item
        ParamName = '操作标志'
      end>
    Left = 208
    Top = 114
  end
  object cqimpCustOper: TWVCommandTypeInfo
    ID = '导入客户信息查询'
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
        ParamName = '导入日期'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '导入顺序号'
      end
      item
        ParamName = '导入操作员'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户类型'
      end
      item
        ParamName = '收费类别'
      end
      item
        ParamName = '客户姓名'
      end
      item
        ParamName = '区域代码'
      end
      item
        ParamName = '部门代码'
      end
      item
        ParamName = '专业代码'
      end
      item
        ParamName = '班级'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '性别'
      end
      item
        ParamName = '国籍'
      end
      item
        ParamName = '民族'
      end
      item
        ParamName = '电子邮箱'
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
        ParamName = '邮政编码'
      end
      item
        ParamName = '入校日期'
      end
      item
        ParamName = '预计离校日期'
      end>
    Left = 208
    Top = 18
  end
  object cpimpCustOper: TWVCommandTypeInfo
    ID = '导入客户管理'
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
        ParamName = '导入日期'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '导入顺序号'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '导入操作员'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户类型'
      end
      item
        ParamName = '收费类别'
      end
      item
        ParamName = '客户姓名'
      end
      item
        ParamName = '区域代码'
      end
      item
        ParamName = '部门代码'
      end
      item
        ParamName = '专业代码'
      end
      item
        ParamName = '班级'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '性别'
      end
      item
        ParamName = '国籍'
      end
      item
        ParamName = '民族'
      end
      item
        ParamName = '电子邮箱'
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
        ParamName = '邮政编码'
      end
      item
        ParamName = '入校日期'
      end
      item
        ParamName = '预计离校日期'
      end>
    Left = 208
    Top = 66
  end
  object WVCImportBankCard: TWVCommandTypeInfo
    ID = '银行卡导入'
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
        ParamName = '批次号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '序号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否传送完毕'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行卡号'
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '校区'
      end>
    Left = 32
    Top = 162
  end
  object WVCIMPBankCardManger: TWVCommandTypeInfo
    ID = '导入银行卡管理'
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
        ParamName = '客户号'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行卡号'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '区域'
      end
      item
        ParamName = '新银行卡号'
      end>
    Left = 32
    Top = 210
  end
  object WVCIMPBankCardQuery: TWVCommandTypeInfo
    ID = '银行卡绑定查询'
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
        ParamName = '绑定状态'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '客户姓名'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行卡号'
      end
      item
        ParamName = '绑定日期'
      end
      item
        ParamName = '客户号'
      end>
    Left = 120
    Top = 130
  end
  object cqPatchDel: TWVCommandTypeInfo
    ID = '银行卡批量删除'
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
        ParamName = '批次号'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '批量标志'
        ParamDataType = kdtInteger
      end>
    Left = 208
    Top = 166
  end
  object cqcustPatchDel: TWVCommandTypeInfo
    ID = '客户批量删除'
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
        ParamName = '批次号'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '批量标志'
        ParamDataType = kdtInteger
      end>
    Left = 120
    Top = 174
  end
  object cqPhotoQuery: TWVCommandTypeInfo
    ID = '照片查询'
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
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '文件名'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 214
  end
  object cqBatchEditStuNo: TWVCommandTypeInfo
    ID = '批量修改学工号'
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
        ParamName = '批量标志'
      end
      item
        ParamName = '原学工号'
      end
      item
        ParamName = '新学工号'
      end>
    Left = 120
    Top = 218
  end
  object cqImpNewStu: TWVCommandTypeInfo
    ID = '新生换卡导入'
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
        ParamName = '批次号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '序号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '是否传送完毕'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '新卡显示卡号'
      end
      item
        ParamName = '卡有效期'
      end>
    Left = 32
    Top = 266
  end
  object cqImpNewStuManage: TWVCommandTypeInfo
    ID = '新生换卡名单管理'
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
        ParamName = '学工号'
      end
      item
        ParamName = '新卡卡号'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '批量标志'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '卡有效期'
      end>
    Left = 120
    Top = 266
  end
  object cqImpNewStuQ: TWVCommandTypeInfo
    ID = '新生换卡导入查询'
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
        ParamName = '绑定状态'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '新卡显示卡号'
      end>
    Left = 208
    Top = 266
  end
  object cqImpBankCardLink: TWVCommandTypeInfo
    ID = '银行卡导入联机'
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
        ParamName = '批次号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '序号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '是否传送完毕'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行卡号'
      end
      item
        ParamName = '姓名'
      end
      item
        ParamName = '校区'
      end>
    Left = 280
    Top = 42
  end
  object cqBankImpLinkQ: TWVCommandTypeInfo
    ID = '银行卡绑定查询联机'
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
        ParamName = '绑定状态'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '客户姓名'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '银行代码'
      end
      item
        ParamName = '银行卡号'
      end
      item
        ParamName = '绑定日期'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 280
    Top = 90
  end
  object cqImpBankCardMangLink: TWVCommandTypeInfo
    ID = '导入银行卡管理联机'
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
        ParamName = '记录号'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '银行卡号'
      end
      item
        ParamName = '批次号'
      end>
    Left = 280
    Top = 138
  end
  object cqbankPatchDel: TWVCommandTypeInfo
    ID = '银行卡批量删除联机'
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
        ParamName = '批次号'
      end
      item
        ParamName = '操作标志'
      end
      item
        ParamName = '批量标志'
        ParamDataType = kdtInteger
      end>
    Left = 280
    Top = 182
  end
  object cqLinkBinding: TWVCommandTypeInfo
    ID = '银行卡联机绑定'
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
        ParamName = '记录号'
      end
      item
        ParamName = '类型'
      end>
    Left = 280
    Top = 230
  end
  object cqBankLinkQuery: TWVCommandTypeInfo
    ID = '银行卡联机查询'
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
        ParamName = '学号'
      end>
    Left = 280
    Top = 274
  end
  object cqBankBingdingQuery: TWVCommandTypeInfo
    ID = '银行卡绑定流水查询'
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
        ParamName = '交易参考号'
      end
      item
        ParamName = '导入批次号'
      end
      item
        ParamName = '交易开始日期'
      end
      item
        ParamName = '交易结束日期'
      end
      item
        ParamName = '客户号'
      end
      item
        ParamName = '学号'
      end
      item
        ParamName = '银行卡号'
      end
      item
        ParamName = '操作类型'
      end
      item
        ParamName = '增删标志'
      end
      item
        ParamName = '错误码'
      end>
    Left = 280
    Top = 322
  end
end
