inherited dmCustomerImp: TdmCustomerImp
  OldCreateOrder = True
  Left = 555
  Top = 181
  Height = 467
  Width = 636
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 368
  end
  object cqSetCustInfo: TKCWVQuery
    ID = '客户信息维护查询'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '发卡部门'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '申请状态'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '姓名'
        FieldName = 'snote'
      end
      item
        ParamName = '证件类型'
        FieldName = 'sroom_no'
      end
      item
        ParamName = '证件号码'
        FieldName = 'spager'
      end
      item
        ParamName = '出生日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '性别'
        FieldName = 'scust_type'
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
        ParamName = '电子信箱'
        FieldName = 'semail'
      end
      item
        ParamName = '卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'sphone3'
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
    RequestType = 2001
    Left = 32
    Top = 26
  end
  object cpSetCustInfo: TKCWVProcessor
    ID = '客户信息维护'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '发卡部门'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '申请有效期限(月)'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '申请日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '申请状态'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '预交款'
        FieldName = 'damt0'
        DefaultValue = 0
      end
      item
        ParamName = '姓名'
        FieldName = 'snote'
      end
      item
        ParamName = '证件类型'
        FieldName = 'sroom_no'
      end
      item
        ParamName = '证件号码'
        FieldName = 'spager'
      end
      item
        ParamName = '出生日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '身高'
        FieldName = 'lvol2'
      end
      item
        ParamName = '性别'
        FieldName = 'scust_type'
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
        ParamName = '电子信箱'
        FieldName = 'semail'
      end
      item
        ParamName = '单位名称'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '婚姻状态'
        FieldName = 'sorder0'
      end
      item
        ParamName = '文化程度'
        FieldName = 'sorder1'
      end
      item
        ParamName = '政治面貌'
        FieldName = 'sorder2'
      end
      item
        ParamName = '经济来源'
        FieldName = 'sserial0'
      end
      item
        ParamName = '国籍'
        FieldName = 'snation_code'
      end
      item
        ParamName = '民族'
        FieldName = 'sserial1'
      end
      item
        ParamName = '籍贯'
        FieldName = 'scert_addr'
      end
      item
        ParamName = '户口所在地类型'
        FieldName = 'sserial2'
      end
      item
        ParamName = '户口所在地'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '居住是由'
        FieldName = 'sserial3'
      end
      item
        ParamName = '居住地址'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '居住日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '首次到达本市日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '更新时间'
        FieldName = 'sname'
      end
      item
        ParamName = '是否删除'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '发卡类别'
        FieldName = 'semp_no'
      end
      item
        ParamName = '集团服务号'
        FieldName = 'semail2'
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
    RequestType = 2001
    KCDataset = Dataset
    Left = 32
    Top = 74
  end
  object cqCustPay: TKCWVQuery
    ID = '缴费领卡'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '预交款'
        FieldName = 'damt0'
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡序列号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '本机流水号'
        FieldName = 'sphone'
      end
      item
        ParamName = 'psam卡号'
        FieldName = 'snote'
      end
      item
        ParamName = '本机日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '本机时间'
        FieldName = 'stime0'
      end
      item
        ParamName = '卡物理编号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '网点号'
        FieldName = 'sphone2'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '消费次数'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol4'
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
        ParamName = '交易流水'
        FieldName = 'lserial0'
      end
      item
        ParamName = '卡类型'
        FieldName = 'sname2'
      end>
    RequestType = 2001
    Left = 32
    Top = 122
  end
  object KCMakeCardCQ: TKCWVQuery
    ID = '制卡审核查询'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '开始日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '发卡部门'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '发卡类别'
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
    RequestType = 2010
    Left = 32
    Top = 170
  end
  object KCMakeCardCheck: TKCWVQuery
    ID = '制卡审核'
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
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '批次号'
        FieldName = 'snote'
      end
      item
        ParamName = '卡序列号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '应用类型'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '厂家'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '城市编码'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '卡商'
        FieldName = 'sname'
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
    RequestType = 2014
    Left = 32
    Top = 218
  end
  object KCFeeQuery: TKCWVQuery
    ID = '缴费查询'
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
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '卡类别'
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
        ParamName = '预交金额'
        FieldName = 'damt0'
        DefaultValue = 0
      end
      item
        ParamName = '缴费信息'
        FieldName = 'snote'
      end>
    RequestType = 2009
    Left = 32
    Top = 266
  end
  object cqExpMakeCardList: TKCWVQuery
    ID = '制卡名单导出'
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
        ParamName = '批次号'
        FieldName = 'snote'
      end
      item
        ParamName = '卡类别'
        FieldName = 'lvol2'
      end
      item
        ParamName = '发卡部门'
        FieldName = 'sroom_no2'
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
    RequestType = 2015
    Left = 112
    Top = 10
  end
  object KCFeePay: TKCWVQuery
    ID = '缴费'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '预交款'
        FieldName = 'damt0'
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
    RequestType = 2001
    Left = 112
    Top = 58
  end
  object KCSavePhoto: TKCWVQuery
    ID = '保存照片'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '文件名'
        FieldName = 'saddr'
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
    RequestType = 2016
    Left = 112
    Top = 106
  end
  object KCImpCardInfo: TKCWVQuery
    ID = '卡厂数据导入'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '业务编号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '资源号'
        FieldName = 'sphone'
      end
      item
        ParamName = '应用序列号'
        FieldName = 'sphone2'
      end
      item
        ParamName = 'UCID'
        FieldName = 'sphone3'
      end
      item
        ParamName = '激活码'
        FieldName = 'spager'
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
    RequestType = 2017
    Left = 112
    Top = 154
  end
  object KCTwoCheckQ: TKCWVQuery
    ID = '二次制卡查询'
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
        ParamName = '批次号'
        FieldName = 'sphone'
      end
      item
        ParamName = '序列号'
        FieldName = 'scard0'
      end
      item
        ParamName = '物理编号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '发卡部门'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '发卡类别'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol1'
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
    RequestType = 2032
    Left = 112
    Top = 202
  end
  object KCTwoCheck: TKCWVQuery
    ID = '二次审核'
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
        ParamName = '批次号'
        FieldName = 'sphone'
      end
      item
        ParamName = '卡编号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '顺序号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '结束标志'
        FieldName = 'lvol2'
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
    RequestType = 2033
    Left = 112
    Top = 250
  end
  object KCMakeCard2Q: TKCWVQuery
    ID = '二次制卡结果查询'
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
        ParamName = '制卡状态'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '二次制卡批次号'
        FieldName = 'sphone'
      end
      item
        ParamName = '审核结束日期'
        FieldName = 'sdate2'
      end
      item
        ParamName = '审核开始日期'
        FieldName = 'sdate1'
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
    RequestType = 2034
    Left = 112
    Top = 298
  end
  object KCImpPhoneNo: TKCWVQuery
    ID = '手机号码导入'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '手机通宝卡号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '手机号'
        FieldName = 'sphone'
      end
      item
        ParamName = '时间戳'
        FieldName = 'scust_auth'
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
    RequestType = 2037
    Left = 184
    Top = 26
  end
  object cqSetPhoneNo: TKCWVQuery
    ID = '手机卡信息维护Q'
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
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '手机通宝卡号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '手机号'
        FieldName = 'sphone'
      end
      item
        ParamName = '更新时间'
        FieldName = 'scust_auth'
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
    RequestType = 2038
    Left = 184
    Top = 74
  end
  object KCSet: TKCWVQuery
    ID = '手机卡信息维护'
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
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '手机通宝卡号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '手机号'
        FieldName = 'sphone'
      end
      item
        ParamName = '更新时间'
        FieldName = 'scust_auth'
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
    RequestType = 2038
    Left = 184
    Top = 122
  end
end
