inherited faDayClearAcc: TfaDayClearAcc
  inherited UIPanel1: TUIPanel
    inherited btnOK: TBitBtn
      Left = 379
      Caption = '�ֶ�����'
    end
    inherited btnCancel: TBitBtn
      Left = 219
      Visible = False
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
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
        Name = '����Ա����'
        Caption = '����Ա����'
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
    ID = '�ֶ�����'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end>
    Left = 72
  end
end
