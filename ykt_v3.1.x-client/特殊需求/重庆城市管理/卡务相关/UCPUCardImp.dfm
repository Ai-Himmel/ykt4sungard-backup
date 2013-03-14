inherited cmCPUCardImp: TcmCPUCardImp
  OldCreateOrder = True
  object cppubCardcqcsgl: TKCWVProcessor
    ID = '发行卡cqcsgl'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '收费方式'
        FieldName = 'lvol9'
      end
      item
        ParamName = '收费金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '票据号码'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '到期日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '是否不记名卡'
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
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
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
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '部门代码'
        FieldName = 'scert_no'
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
        ParamName = '到期日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡密码'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol8'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '单次限额'
        FieldName = 'lvol11'
      end
      item
        ParamName = '日限额'
        FieldName = 'lvol12'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '发行方标识'
        FieldName = 'sholder_ac_no'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end>
    RequestType = 846301
    KCDataset = Dataset
    Left = 22
    Top = 8
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 120
    Top = 8
  end
  object cpStuChangeCard: TKCWVProcessor
    ID = '新生换卡确认cqcsgl'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '操作类型'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '原物理编号'
        FieldName = 'scust_no'
      end
      item
        ParamName = '原卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '原卡余额'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '原卡交易次数'
        FieldName = 'Lvol6'
      end
      item
        ParamName = '新卡物理编号'
        FieldName = 'Scust_no2'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '到期日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '补助批次号'
        FieldName = 'lvol4'
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
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '到期日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
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
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '部门代码'
        FieldName = 'scert_no'
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
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡密码'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol8'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '补助批次号'
        FieldName = 'lvol4'
      end
      item
        ParamName = '单次限额'
        FieldName = 'lvol11'
      end
      item
        ParamName = '日限额'
        FieldName = 'lvol12'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '发行方标识'
        FieldName = 'sholder_ac_no'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end>
    RequestType = 846325
    Timeout = 2000
    KCDataset = Dataset
    Left = 22
    Top = 56
  end
  object cpRenewCard: TKCWVProcessor
    ID = '补办卡cqcsgl'
    InputBindings = <
      item
        ParamName = '操作员'
        FieldName = 'semp'
      end
      item
        ParamName = '显示卡号'
        FieldName = 'sorder0'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '收费方式'
        FieldName = 'Lvol9'
      end
      item
        ParamName = '收费金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '收卡成本费'
        FieldName = 'lvol4'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '票据号码'
        FieldName = 'scust_auth2'
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
        ParamName = '显示卡号'
        FieldName = 'sorder0'
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
        ParamName = '客户姓名'
        FieldName = 'sall_name'
      end
      item
        ParamName = '学工号'
        FieldName = 'spager'
      end
      item
        ParamName = '部门代码'
        FieldName = 'scert_no'
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
        ParamName = '到期日期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '卡密码'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '出卡值'
        FieldName = 'lvol8'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '操作员'
        FieldName = 'semp'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '单次限额'
        FieldName = 'lvol11'
      end
      item
        ParamName = '日限额'
        FieldName = 'lvol12'
      end
      item
        ParamName = '证件类型'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '发行方标识'
        FieldName = 'sholder_ac_no'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '卡类型'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end>
    RequestType = 846305
    KCDataset = Dataset
    Left = 22
    Top = 104
  end
  object cpCardReRelease: TKCWVProcessor
    ID = '回收再发行cqcsgl'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '物理编号'
        FieldName = 'sstation0'
      end
      item
        ParamName = '卡余额'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '充值次数'
        FieldName = 'lvol5'
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
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '卡余额'
        FieldName = 'lvol8'
      end
      item
        ParamName = '收费类别'
        FieldName = 'Lvol5'
      end
      item
        ParamName = '卡密码'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '有效期'
        FieldName = 'sdate0'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '单次限额'
        FieldName = 'lvol11'
      end
      item
        ParamName = '日限额'
        FieldName = 'lvol12'
      end
      item
        ParamName = '业务时间'
        FieldName = 'stime3'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end>
    RequestType = 846310
    KCDataset = Dataset
    Left = 22
    Top = 152
  end
end
