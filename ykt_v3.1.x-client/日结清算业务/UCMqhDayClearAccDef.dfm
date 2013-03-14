inherited dmDayClearAccDef: TdmDayClearAccDef
  OldCreateOrder = True
  Left = 231
  Top = 156
  Width = 572
  object cqDayAccount: TWVCommandTypeInfo
    ID = '手动结账'
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
      end>
    Left = 25
    Top = 58
  end
  object cqfillTrans: TWVCommandTypeInfo
    ID = '充值解款'
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
        ParamName = '操作员号'
      end
      item
        ParamName = '密码'
      end
      item
        ParamName = '食堂账号'
      end
      item
        ParamName = '金额'
      end
      item
        ParamName = '备注'
      end>
    Left = 24
    Top = 106
  end
  object cqfillReTrans: TWVCommandTypeInfo
    ID = '充值解款冲正'
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
        ParamName = '操作员号'
      end
      item
        ParamName = '密码'
      end
      item
        ParamName = '交易流水号'
      end
      item
        ParamName = '被冲正流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '冲正金额'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '被冲账号'
        ParamType = ptOutput
      end
      item
        ParamName = '账户余额'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end>
    Left = 24
    Top = 154
  end
  object cqconsumeBalance: TWVCommandTypeInfo
    ID = '消费结算'
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
        ParamName = '操作员号'
      end
      item
        ParamName = '密码'
      end
      item
        ParamName = '商户账号'
      end
      item
        ParamName = '金额'
      end>
    Left = 24
    Top = 202
  end
  object cqreConsumeBalance: TWVCommandTypeInfo
    ID = '消费结算冲正'
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
        ParamName = '操作员号'
      end
      item
        ParamName = '密码'
      end
      item
        ParamName = '交易流水号'
      end>
    Left = 24
    Top = 250
  end
  object cqTradeLogDetailed: TWVCommandTypeInfo
    ID = '交易流水详细信息查询解款冲正'
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
        ParamName = '采集开始日期'
      end
      item
        ParamName = '采集开始时间'
      end
      item
        ParamName = '采集结束日期'
      end
      item
        ParamName = '采集结束时间'
      end
      item
        ParamName = '流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '上传端流水号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易代码'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '流水状态'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '上传工作站标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易发生设备标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易卡号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户标识'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '操作员代码'
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '设备物理ID'
      end>
    Left = 24
    Top = 301
  end
end
