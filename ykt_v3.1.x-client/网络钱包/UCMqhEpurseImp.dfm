inherited dmEpurseRegImp: TdmEpurseRegImp
  OldCreateOrder = True
  Left = 285
  Width = 574
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 304
    Top = 8
  end
  object cqEpurseReg: TKCWVProcessor
    ID = '电子钱包开户'
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
        ParamName = '帐户密码'
        FieldName = 'snote2'
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
    RequestType = 846331
    KCDataset = Dataset
    Left = 24
    Top = 10
  end
  object KCWEPurseDestory: TKCWVQuery
    ID = '销户查询'
    InputBindings = <
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
        ParamName = '所属区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '所在部门'
        FieldName = 'scert_no'
      end
      item
        ParamName = '证件号码'
        FieldName = 'semail2'
      end
      item
        ParamName = '止付状态'
        FieldName = 'scust_type'
      end
      item
        ParamName = '开户日期'
        FieldName = 'sdate1'
      end
      item
        ParamName = '帐号'
        FieldName = 'sbank_acc'
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
    RequestType = 846603
    Left = 24
    Top = 58
  end
  object cqEPurseDestory: TKCWVProcessor
    ID = '电子钱包销户'
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
        ParamName = '帐户密码'
        FieldName = 'snote2'
      end
      item
        ParamName = '帐号'
        FieldName = 'sbank_acc'
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
    RequestType = 846332
    KCDataset = Dataset
    Left = 24
    Top = 106
  end
  object cqEPurseIn: TKCWVProcessor
    ID = '电子钱包充值'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '帐号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '充值方式'
        FieldName = 'lvol9'
      end
      item
        ParamName = '凭证号码'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '充值金额'
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
    RequestType = 846333
    KCDataset = Dataset
    Left = 24
    Top = 154
  end
  object cqEPurseOut1: TKCWVProcessor
    ID = '电子钱包支取'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '帐号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '取款密码'
        FieldName = 'snote2'
      end
      item
        ParamName = '取款金额'
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
    RequestType = 846334
    KCDataset = Dataset
    Left = 24
    Top = 202
  end
  object cqFreeze: TKCWVProcessor
    ID = '钱包止付解付'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '帐号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '客户号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '标志'
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
    RequestType = 846335
    KCDataset = Dataset
    Left = 24
    Top = 250
  end
  object cqEPurseTrans: TKCWVProcessor
    ID = '电子钱包转账'
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
        ParamName = '物理卡号'
        FieldName = 'sstation0'
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
        ParamName = '充值金额'
        FieldName = 'damt0'
      end
      item
        ParamName = '转账方向'
        FieldName = 'lvol3'
      end
      item
        ParamName = '帐户密码'
        FieldName = 'snote2'
      end
      item
        ParamName = '卡密码'
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
      end
      item
        ParamName = '卡号'
        FieldName = 'Lvol0'
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
      end
      item
        ParamName = '终端编号'
        FieldName = 'lwithdraw_flag'
      end>
    RequestType = 846336
    KCDataset = Dataset
    Left = 22
    Top = 304
  end
  object cqchangepwd: TKCWVProcessor
    ID = '钱包密码修改'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '帐号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '旧密码'
        FieldName = 'snote'
      end
      item
        ParamName = '新密码'
        FieldName = 'snote2'
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
    RequestType = 846337
    KCDataset = Dataset
    Left = 88
    Top = 26
  end
  object cqresetpwd: TKCWVProcessor
    ID = '钱包密码重置'
    InputBindings = <
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '帐号'
        FieldName = 'sbank_acc'
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
        ParamName = '新密码'
        FieldName = 'snote2'
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
    RequestType = 846338
    KCDataset = Dataset
    Left = 88
    Top = 74
  end
end
