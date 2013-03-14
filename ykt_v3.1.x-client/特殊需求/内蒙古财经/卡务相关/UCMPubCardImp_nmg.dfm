inherited cmPubCardImp_nmg: TcmPubCardImp_nmg
  OldCreateOrder = True
  Left = 285
  object cpPubCard_nmg: TKCWVProcessor
    ID = '发行卡nmg'
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
      end>
    RequestType = 846301
    KCDataset = Dataset
    Left = 14
    Top = 8
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 160
    Top = 8
  end
  object cqcashOperCancel: TKCWVProcessor
    ID = '充值支取冲正nmg'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '流水号'
        FieldName = 'lserial1'
      end
      item
        ParamName = '业务日期'
        FieldName = 'sdate3'
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
    RequestType = 846324
    KCDataset = Dataset
    Left = 14
    Top = 104
  end
  object cpSetSmlMoney: TKCWVProcessor
    ID = '小钱包充值nmg'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '物理卡号'
        FieldName = 'sstation1'
      end
      item
        ParamName = '入卡金额'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '交易次数'
        FieldName = 'lvol6'
      end
      item
        ParamName = '金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '卡号'
        FieldName = 'lvol0'
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
        ParamName = '出卡金额'
        FieldName = 'lvol8'
      end>
    RequestType = 846323
    KCDataset = Dataset
    Left = 14
    Top = 56
  end
end
