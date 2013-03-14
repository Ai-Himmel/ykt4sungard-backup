inherited dmDayClearAccImp: TdmDayClearAccImp
  OldCreateOrder = True
  Left = 220
  Top = 208
  Height = 502
  object cqDayAccount: TKCWVQuery
    ID = '手动结账'
    InputBindings = <
      item
        ParamName = '操作员代码'
        FieldName = 'scust_no'
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
    RequestType = 900088
    Left = 24
    Top = 58
  end
  object cqconsumeBalance: TKCWVQuery
    ID = '消费结算'
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
        ParamName = '操作员号'
        FieldName = 'scard0'
      end
      item
        ParamName = '密码'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '商户账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '金额'
        FieldName = 'damt1'
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
    RequestType = 847222
    Left = 24
    Top = 210
  end
  object cqreConsumeBalance: TKCWVQuery
    ID = '消费结算冲正'
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
        ParamName = '操作员号'
        FieldName = 'scard0'
      end
      item
        ParamName = '密码'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '交易流水号'
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
    RequestType = 847223
    Left = 24
    Top = 258
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 333
    Top = 48
  end
  object cpfillTrans: TKCWVProcessor
    ID = '充值解款'
    InputBindings = <
      item
        ParamName = '操作员号'
        FieldName = 'scard0'
      end
      item
        ParamName = '密码'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '食堂账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '金额'
        FieldName = 'damt1'
      end
      item
        ParamName = '备注'
        FieldName = 'scert_addr'
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
    RequestType = 847220
    KCDataset = Dataset
    Left = 24
    Top = 106
  end
  object cqTradeLogDetailed: TKCWVQuery
    ID = '交易流水详细信息查询解款冲正'
    InputBindings = <
      item
        ParamName = '采集开始日期'
        FieldName = 'scust_no'
      end
      item
        ParamName = '采集开始时间'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '采集结束日期'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '采集结束时间'
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '流水号'
        FieldName = 'lvol0'
      end
      item
        ParamName = '上传端流水号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '交易代码'
        FieldName = 'lvol2'
      end
      item
        ParamName = '流水状态'
        FieldName = 'lvol3'
      end
      item
        ParamName = '上传工作站标识'
        FieldName = 'lvol4'
      end
      item
        ParamName = '交易发生设备标识'
        FieldName = 'lvol5'
      end
      item
        ParamName = '交易卡号'
        FieldName = 'lvol6'
      end
      item
        ParamName = '客户标识'
        FieldName = 'lvol9'
      end
      item
        ParamName = '操作员代码'
        FieldName = 'sserial2'
      end
      item
        ParamName = '学工号'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '设备物理ID'
        FieldName = 'semp_no'
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
    RequestType = 847171
    Timeout = 60000
    Left = 24
    Top = 302
  end
  object cpfillReTrans: TKCWVProcessor
    ID = '充值解款冲正'
    InputBindings = <
      item
        ParamName = '操作员号'
        FieldName = 'scard0'
      end
      item
        ParamName = '密码'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '交易流水号'
        FieldName = 'lvol1'
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
      end
      item
        ParamName = '被冲正流水号'
        FieldName = 'lvol1'
      end
      item
        ParamName = '冲正金额'
        FieldName = 'damt1'
      end
      item
        ParamName = '被冲账号'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '账户余额'
        FieldName = 'damt2'
      end>
    RequestType = 847221
    KCDataset = Dataset
    Left = 24
    Top = 154
  end
end
