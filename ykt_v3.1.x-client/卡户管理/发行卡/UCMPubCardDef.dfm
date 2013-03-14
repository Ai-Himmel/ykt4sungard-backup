inherited cmPubCardDef: TcmPubCardDef
  OldCreateOrder = True
  object cqPubCard_trunk: TWVCommandTypeInfo
    ID = '发行卡trunk'
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
        ParamName = '操作员'
        ParamType = ptInputOutput
      end
      item
        ParamName = '卡类型'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '显示卡号'
        ParamType = ptInputOutput
      end
      item
        ParamName = '物理卡号'
      end
      item
        ParamName = '客户号'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '票据号码'
      end
      item
        ParamName = '收费方式'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费金额'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '客户类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '收费类别'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '客户姓名'
        ParamType = ptOutput
      end
      item
        ParamName = '学工号'
        ParamType = ptOutput
      end
      item
        ParamName = '部门代码'
        ParamType = ptOutput
      end
      item
        ParamName = '证件号码'
        ParamType = ptOutput
      end
      item
        ParamName = '性别'
        ParamType = ptOutput
      end
      item
        ParamName = '到期日期'
        ParamType = ptInputOutput
      end
      item
        ParamName = '卡号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '卡密码'
        ParamType = ptOutput
      end
      item
        ParamName = '出卡值'
        ParamType = ptOutput
        ParamDataType = kdtInteger
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
        ParamName = '是否不记名卡'
      end
      item
        ParamName = '终端编号'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '单次限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '日限额'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end>
    Left = 24
    Top = 10
  end
end
