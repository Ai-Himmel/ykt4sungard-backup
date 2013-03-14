inherited dmCustomerImp: TdmCustomerImp
  OldCreateOrder = True
  Left = 267
  Top = 215
  Height = 467
  Width = 727
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 40
    Top = 8
  end
  object cqQueryCustomer: TKCWVQuery
    ID = '客户信息查询'
    InputBindings = <
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '客户名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '客户状态'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '客户类别'
        FieldName = 'lvol3'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '联系人单位号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '联系人性别'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '联系人学工号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '联系人民族'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '客户所在区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '注册日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '班级'
        FieldName = 'scard1'
      end
      item
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '电子钱包'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '专业'
        FieldName = 'scust_no2'
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
    RequestType = 841601
    Left = 40
    Top = 58
  end
  object cqsetCustInfo: TKCWVProcessor
    ID = '客户信息设置'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '联系地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '客户所在区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '预计注销时间'
        FieldName = 'sdate2'
      end
      item
        ParamName = '联系人班级或部门名称'
        FieldName = 'scard1'
      end
      item
        ParamName = '联系人班级或部门号'
        FieldName = 'scert_no'
      end
      item
        ParamName = '备注'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '客户名称'
        FieldName = 'sall_name'
      end
      item
        ParamName = '客户类别'
        FieldName = 'lvol3'
      end
      item
        ParamName = '联系人姓名'
        FieldName = 'sname2'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '联系人民族'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '联系人性别'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '联系人学号或员工号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '联系电话'
        FieldName = 'sphone'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '专业'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '入学日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '邮编'
        FieldName = 'spost_code'
      end
      item
        ParamName = '电子邮箱'
        FieldName = 'semail'
      end
      item
        ParamName = '手机'
        FieldName = 'sphone2'
      end
      item
        ParamName = '国籍'
        FieldName = 'snation_code'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '交易类型'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '批量标志'
        FieldName = 'sstatus4'
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
    RequestType = 841601
    KCDataset = Dataset
    Left = 40
    Top = 106
  end
  object kcQryCustKind: TKCWVQuery
    ID = '客户类别查询'
    InputBindings = <
      item
        ParamName = '客户类别代码'
        FieldName = 'lvol0'
      end
      item
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
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
    RequestType = 843373
    Left = 128
    Top = 26
  end
  object cpSetCustKindInfo: TKCWVProcessor
    ID = '客户类别信息设置'
    InputBindings = <
      item
        ParamName = '客户类别代码'
        FieldName = 'lvol0'
      end
      item
        ParamName = '客户类别名称'
        FieldName = 'scard0'
      end
      item
        ParamName = '默认收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '交易类型'
        FieldName = 'Sstatus0'
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
    RequestType = 843373
    KCDataset = Dataset
    Left = 128
    Top = 74
  end
  object cpImpCustInfo: TKCWVProcessor
    ID = '客户信息导入'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '序号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '是否传送完毕'
        FieldName = 'scust_type'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
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
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '校区'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '所属部门'
        FieldName = 'scert_no'
      end
      item
        ParamName = '专业'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '班级'
        FieldName = 'scard1'
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
        ParamName = '性别'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '国籍'
        FieldName = 'snation_code'
      end
      item
        ParamName = '民族'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '电子邮箱'
        FieldName = 'semail'
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
        ParamName = '地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '邮编'
        FieldName = 'spost_code'
      end
      item
        ParamName = '入校日期'
        FieldName = 'Sdate1'
      end
      item
        ParamName = '预计离校日期'
        FieldName = 'sdate2'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end>
    RequestType = 841605
    KCDataset = Dataset
    Left = 40
    Top = 154
  end
  object cpSHlImpCustInfo: TKCWVProcessor
    ID = '客户导入信息设置.审核'
    InputBindings = <
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '导入顺序号'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '操作标志'
        FieldName = 'Sstatus0'
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
    RequestType = 841605
    KCDataset = Dataset
    Left = 216
    Top = 146
  end
  object cqimpCustOper: TKCWVQuery
    ID = '导入客户信息查询'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '导入日期'
        FieldName = 'Sdate0'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '导入顺序号'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '导入操作员'
        FieldName = 'Semp_no'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '客户类型'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '区域代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '部门代码'
        FieldName = 'scert_no'
      end
      item
        ParamName = '专业代码'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '班级'
        FieldName = 'scard1'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
      end
      item
        ParamName = '性别'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '国籍'
        FieldName = 'snation_code'
      end
      item
        ParamName = '民族'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '电子邮箱'
        FieldName = 'semail'
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
        ParamName = '地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '邮政编码'
        FieldName = 'spost_code'
      end
      item
        ParamName = '入校日期'
        FieldName = 'Sdate1'
      end
      item
        ParamName = '预计离校日期'
        FieldName = 'sdate2'
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
    RequestType = 841605
    Left = 216
    Top = 50
  end
  object cpimpCustOper: TKCWVProcessor
    ID = '导入客户管理'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '导入日期'
        FieldName = 'Sdate0'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '导入顺序号'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '导入操作员'
        FieldName = 'Semp_no'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '客户类型'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '收费类别'
        FieldName = 'lvol5'
      end
      item
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '区域代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '部门代码'
        FieldName = 'scert_no'
      end
      item
        ParamName = '专业代码'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '班级'
        FieldName = 'scard1'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
      end
      item
        ParamName = '性别'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '国籍'
        FieldName = 'snation_code'
      end
      item
        ParamName = '民族'
        FieldName = 'scust_type2'
      end
      item
        ParamName = '电子邮箱'
        FieldName = 'semail'
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
        ParamName = '地址'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '邮政编码'
        FieldName = 'spost_code'
      end
      item
        ParamName = '入校日期'
        FieldName = 'Sdate1'
      end
      item
        ParamName = '预计离校日期'
        FieldName = 'sdate2'
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
    RequestType = 841605
    KCDataset = Dataset
    Left = 216
    Top = 98
  end
  object cpImpBankCard: TKCWVProcessor
    ID = '银行卡导入'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '序号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '是否传送完毕'
        FieldName = 'scust_type'
      end
      item
        ParamName = '操作标志'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '客户号'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '校区'
        FieldName = 'sbranch_code0'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end>
    RequestType = 841602
    KCDataset = Dataset
    Left = 40
    Top = 202
  end
  object cpBankCardManger: TKCWVProcessor
    ID = '导入银行卡管理'
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
        FieldName = 'sstatus0'
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
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '新银行卡号'
        FieldName = 'scard1'
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
    RequestType = 841602
    KCDataset = Dataset
    Left = 40
    Top = 250
  end
  object KCWVQuery1: TKCWVQuery
    ID = '银行卡绑定查询'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '绑定状态'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '绑定日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '客户号'
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
    RequestType = 841602
    Left = 128
    Top = 122
  end
  object cpPatchdel: TKCWVProcessor
    ID = '银行卡批量删除'
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
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '批量标志'
        FieldName = 'lwithdraw_flag'
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
    RequestType = 841602
    KCDataset = Dataset
    Left = 216
    Top = 198
  end
  object cpCustPatchDel: TKCWVProcessor
    ID = '客户批量删除'
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
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '批量标志'
        FieldName = 'lwithdraw_flag'
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
    RequestType = 841605
    KCDataset = Dataset
    Left = 128
    Top = 174
  end
  object cpPhotoQuery: TKCWVProcessor
    ID = '照片查询'
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
        FieldName = 'lvol1'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '文件名'
        FieldName = 'vsvarstr1'
      end>
    RequestType = 841600
    KCDataset = Dataset
    Left = 216
    Top = 246
  end
  object cpBatchEditStuNo: TKCWVProcessor
    ID = '批量修改学工号'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '批量标志'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '新学工号'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '原学工号'
        FieldName = 'scert_no'
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
    RequestType = 841601
    KCDataset = Dataset
    Left = 128
    Top = 218
  end
  object cpImpNewstu: TKCWVProcessor
    ID = '新生换卡导入'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '序号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '是否传送完毕'
        FieldName = 'scust_type'
      end
      item
        ParamName = '操作标志'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '新卡显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '卡有效期'
        FieldName = 'sdate0'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end>
    RequestType = 846130
    KCDataset = Dataset
    Left = 128
    Top = 266
  end
  object cpImpNewStuManage: TKCWVProcessor
    ID = '新生换卡名单管理'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '新卡卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '批量标志'
        FieldName = 'lserial1'
        DefaultValue = 0
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '卡有效期'
        FieldName = 'sdate0'
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
    RequestType = 846130
    KCDataset = Dataset
    Left = 40
    Top = 298
  end
  object kcImpNewStuQ: TKCWVQuery
    ID = '新生换卡导入查询'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '绑定状态'
        FieldName = 'sserial0'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '新卡显示卡号'
        FieldName = 'sorder0'
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
    RequestType = 846130
    Left = 128
    Top = 314
  end
  object cpImpBankCardLink: TKCWVProcessor
    ID = '银行卡导入联机'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '序号'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '是否传送完毕'
        FieldName = 'scust_type'
      end
      item
        ParamName = '操作标志'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '客户号'
        FieldName = 'Lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '校区'
        FieldName = 'sbranch_code0'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end>
    RequestType = 841603
    KCDataset = Dataset
    Left = 288
    Top = 26
  end
  object kcImpBankCardLinkQ: TKCWVQuery
    ID = '银行卡绑定查询联机'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '绑定状态'
        FieldName = 'lsafe_level2'
        DefaultValue = 0
      end
      item
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '银行代码'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '银行卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '绑定日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '客户号'
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
    RequestType = 841603
    Left = 288
    Top = 74
  end
  object cpImpBankMangLink: TKCWVProcessor
    ID = '导入银行卡管理联机'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '记录号'
        FieldName = 'sname2'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '银行卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '批次号'
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
    RequestType = 841603
    KCDataset = Dataset
    Left = 288
    Top = 122
  end
  object cpPatchDelLink: TKCWVProcessor
    ID = '银行卡批量删除联机'
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
        ParamName = '批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '操作标志'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '批量标志'
        FieldName = 'lsafe_level2'
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
    RequestType = 841603
    KCDataset = Dataset
    Left = 288
    Top = 166
  end
  object cpLinkBinding: TKCWVProcessor
    ID = '银行卡联机绑定'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '记录号'
        FieldName = 'Sname2'
      end
      item
        ParamName = '类型'
        FieldName = 'sstatus1'
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
    RequestType = 841603
    KCDataset = Dataset
    Left = 288
    Top = 214
  end
  object cqBankLinkQuery: TKCWVQuery
    ID = '银行卡联机查询'
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
        ParamName = '学号'
        FieldName = 'spager'
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
    RequestType = 841603
    Left = 288
    Top = 266
  end
  object cqBankBingdingQuery: TKCWVQuery
    ID = '银行卡绑定流水查询'
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
        ParamName = '交易参考号'
        FieldName = 'sphone3'
      end
      item
        ParamName = '导入批次号'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '交易开始日期'
        FieldName = 'stime1'
      end
      item
        ParamName = '交易结束日期'
        FieldName = 'stime2'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '学号'
        FieldName = 'Spager'
      end
      item
        ParamName = '银行卡号'
        FieldName = 'scard0'
      end
      item
        ParamName = '操作类型'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '增删标志'
        FieldName = 'lvol9'
      end
      item
        ParamName = '错误码'
        FieldName = 'lsafe_level'
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
    RequestType = 841604
    Left = 288
    Top = 314
  end
end
