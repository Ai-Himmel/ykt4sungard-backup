inherited dmCustomerDef: TdmCustomerDef
  OldCreateOrder = True
  Left = 472
  Top = 238
  Height = 457
  Width = 628
  object cpSetCustInfo: TWVCommandTypeInfo
    ID = '客户信息维护'
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
        ParamName = '客户号'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '发卡部门'
      end
      item
        ParamName = '申请有效期限(月)'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '申请日期'
      end
      item
        ParamName = '申请状态'
      end
      item
        ParamName = '预交款'
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
        ParamName = '出生日期'
      end
      item
        ParamName = '身高'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '性别'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '电子信箱'
      end
      item
        ParamName = '单位名称'
      end
      item
        ParamName = '婚姻状态'
      end
      item
        ParamName = '文化程度'
      end
      item
        ParamName = '政治面貌'
      end
      item
        ParamName = '经济来源'
      end
      item
        ParamName = '国籍'
      end
      item
        ParamName = '民族'
      end
      item
        ParamName = '籍贯'
      end
      item
        ParamName = '户口所在地类型'
      end
      item
        ParamName = '户口所在地'
      end
      item
        ParamName = '居住是由'
      end
      item
        ParamName = '居住地址'
      end
      item
        ParamName = '居住日期'
      end
      item
        ParamName = '首次到达本市日期'
      end
      item
        ParamName = '更新时间'
      end
      item
        ParamName = '是否删除'
      end
      item
        ParamName = '发卡类别'
      end
      item
        ParamName = '集团服务号'
      end>
    Left = 24
    Top = 82
  end
  object cqSetCustInfo: TWVCommandTypeInfo
    ID = '客户信息维护查询'
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
        ParamName = '申请状态'
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
        ParamName = '出生日期'
      end
      item
        ParamName = '性别'
      end
      item
        ParamName = '电话'
      end
      item
        ParamName = '手机'
      end
      item
        ParamName = '电子信箱'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '应用序列号'
      end>
    Left = 24
    Top = 34
  end
  object cqCustPay: TWVCommandTypeInfo
    ID = '缴费领卡'
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
        ParamName = '预交款'
      end
      item
        ParamName = '卡号'
      end
      item
        ParamName = '卡序列号'
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
        ParamName = '卡物理编号'
      end
      item
        ParamName = '网点号'
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
        ParamName = '交易流水'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类型'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 130
  end
  object WVMakeCardCQ: TWVCommandTypeInfo
    ID = '制卡审核查询'
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
        ParamName = '开始日期'
      end
      item
        ParamName = '结束日期'
      end
      item
        ParamName = '发卡部门'
      end
      item
        ParamName = '发卡类别'
      end>
    Left = 24
    Top = 178
  end
  object WVMakeCardCheck: TWVCommandTypeInfo
    ID = '制卡审核'
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
        ParamName = '客户号'
      end
      item
        ParamName = '批次号'
      end
      item
        ParamName = '卡序列号'
      end
      item
        ParamName = '应用类型'
      end
      item
        ParamName = '厂家'
      end
      item
        ParamName = '城市编码'
      end
      item
        ParamName = '卡商'
      end>
    Left = 24
    Top = 226
  end
  object WVFeeQuery: TWVCommandTypeInfo
    ID = '缴费查询'
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
        ParamName = '卡号'
      end
      item
        ParamName = '预交金额'
        ParamType = ptOutput
      end
      item
        ParamName = '缴费信息'
        ParamType = ptOutput
      end
      item
        ParamName = '卡类别'
      end>
    Left = 24
    Top = 274
  end
  object cqExpMakeCardList: TWVCommandTypeInfo
    ID = '制卡名单导出'
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
        ParamName = '批次号'
      end
      item
        ParamName = '发卡部门'
      end
      item
        ParamName = '卡类别'
      end>
    Left = 104
    Top = 10
  end
  object WVFeePay: TWVCommandTypeInfo
    ID = '缴费'
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
        ParamName = '预交款'
      end>
    Left = 104
    Top = 58
  end
  object WVSavePhoto: TWVCommandTypeInfo
    ID = '保存照片'
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
        ParamName = '文件名'
      end>
    Left = 104
    Top = 106
  end
  object WVImpCardInfo: TWVCommandTypeInfo
    ID = '卡厂数据导入'
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
        ParamName = '业务编号'
      end
      item
        ParamName = '资源号'
      end
      item
        ParamName = '应用序列号'
      end
      item
        ParamName = 'UCID'
      end
      item
        ParamName = '激活码'
      end>
    Left = 104
    Top = 154
  end
  object WVtwoCheckQ: TWVCommandTypeInfo
    ID = '二次制卡查询'
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
        ParamName = '批次号'
      end
      item
        ParamName = '序列号'
      end
      item
        ParamName = '物理编号'
      end
      item
        ParamName = '发卡部门'
      end
      item
        ParamName = '发卡类别'
      end
      item
        ParamName = '卡号'
      end>
    Left = 104
    Top = 202
  end
  object WVTwoCheck: TWVCommandTypeInfo
    ID = '二次审核'
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
        ParamName = '批次号'
      end
      item
        ParamName = '卡编号'
      end
      item
        ParamName = '顺序号'
      end
      item
        ParamName = '结束标志'
      end>
    Left = 104
    Top = 250
  end
  object WVMakeCard2Q: TWVCommandTypeInfo
    ID = '二次制卡结果查询'
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
        ParamName = '审核开始日期'
      end
      item
        ParamName = '审核结束日期'
      end
      item
        ParamName = '二次制卡批次号'
      end
      item
        ParamName = '制卡状态'
      end>
    Left = 104
    Top = 298
  end
  object WVImpPhoneNo: TWVCommandTypeInfo
    ID = '手机号码导入'
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
        ParamName = '手机通宝卡号'
      end
      item
        ParamName = '手机号'
      end
      item
        ParamName = '时间戳'
      end>
    Left = 184
    Top = 34
  end
  object cqSetPhoneNo: TWVCommandTypeInfo
    ID = '手机卡信息维护Q'
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
        ParamName = '手机通宝卡号'
      end
      item
        ParamName = '手机号'
      end
      item
        ParamName = '更新时间'
      end>
    Left = 184
    Top = 82
  end
  object WVSet: TWVCommandTypeInfo
    ID = '手机卡信息维护'
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
        ParamName = '手机通宝卡号'
      end
      item
        ParamName = '手机号'
      end
      item
        ParamName = '更新时间'
      end>
    Left = 184
    Top = 130
  end
end
