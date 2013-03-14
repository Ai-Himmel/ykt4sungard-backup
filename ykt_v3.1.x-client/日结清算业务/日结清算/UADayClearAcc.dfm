inherited faDayClearAcc: TfaDayClearAcc
  inherited UIPanel1: TUIPanel
    inherited btnOK: TBitBtn
      Left = 379
      Caption = '手动结算'
    end
    inherited btnCancel: TBitBtn
      Left = 219
      Visible = False
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = '@Dataset'
      end
      item
        Name = '操作员代码'
        Caption = '操作员代码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scust_no'
      end>
    Left = 40
  end
  inherited MainRequest: TWVRequest
    ID = '手动结账'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员代码'
        FieldName = '操作员代码'
      end>
    Left = 72
  end
end
