inherited dmEPurseReg: TdmEPurseReg
  OldCreateOrder = True
  Left = 285
  object cqEpurseReg: TWVCommandTypeInfo
    ID = '电子钱包开户'
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
        ParamName = '帐户密码'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end>
    Left = 48
    Top = 10
  end
  object WVEPurseDestory: TWVCommandTypeInfo
    ID = '销户查询'
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
        ParamDataType = kdtInteger
      end
      item
        ParamName = '学工号'
      end
      item
        ParamName = '客户姓名'
      end
      item
        ParamName = '所属区域'
      end
      item
        ParamName = '所在部门'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '止付状态'
      end
      item
        ParamName = '开户日期'
      end
      item
        ParamName = '帐号'
      end>
    Left = 48
    Top = 58
  end
  object cqEPurseDestory: TWVCommandTypeInfo
    ID = '电子钱包销户'
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
        ParamName = '帐户密码'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '帐号'
      end>
    Left = 48
    Top = 106
  end
  object WVEPurseIn: TWVCommandTypeInfo
    ID = '电子钱包充值'
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
        ParamName = '帐号'
      end
      item
        ParamName = '充值方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '凭证号码'
      end
      item
        ParamName = '充值金额'
        ParamDataType = kdtFloat
      end>
    Left = 48
    Top = 154
  end
  object WVEPurseOut: TWVCommandTypeInfo
    ID = '电子钱包支取'
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
        ParamName = '帐号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '取款密码'
      end
      item
        ParamName = '取款金额'
        ParamDataType = kdtFloat
      end>
    Left = 48
    Top = 202
  end
  object WVFreeze: TWVCommandTypeInfo
    ID = '钱包止付解付'
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
        ParamName = '帐号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '标志'
      end>
    Left = 48
    Top = 250
  end
  object WVEpurseTrans: TWVCommandTypeInfo
    ID = '电子钱包转账'
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
        ParamName = '卡号'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '入卡金额'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '交易次数'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '充值金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '转账方向'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '帐户密码'
      end
      item
        ParamName = '卡密码'
      end
      item
        ParamName = '流水号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '业务日期'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡金额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '终端编号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end>
    Left = 48
    Top = 298
  end
  object WVchangepwd: TWVCommandTypeInfo
    ID = '钱包密码修改'
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
        ParamName = '帐号'
      end
      item
        ParamName = '旧密码'
      end
      item
        ParamName = '新密码'
      end>
    Left = 128
    Top = 26
  end
  object WVresetpwd: TWVCommandTypeInfo
    ID = '钱包密码重置'
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
        ParamName = '帐号'
      end
      item
        ParamName = '证件类型'
      end
      item
        ParamName = '证件号码'
      end
      item
        ParamName = '新密码'
      end>
    Left = 128
    Top = 74
  end
end
