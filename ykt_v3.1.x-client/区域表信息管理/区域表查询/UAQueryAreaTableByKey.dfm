inherited faQueryAreaTable: TfaQueryAreaTable
  Width = 709
  Height = 453
  object WVLabel4: TWVLabel [0]
    Left = 160
    Top = 144
    Width = 48
    Height = 12
    Caption = 'WVLabel4'
  end
  inherited UIPanel1: TUIPanel
    Top = 417
    Width = 709
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 533
      Top = 5
    end
    inherited btnPrint: TBitBtn
      Left = 623
      Top = 5
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 709
    inherited Image1: TImage
      Width = 709
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 709
    Height = 399
    inherited Grid: TRzDBGrid
      Width = 709
      Height = 399
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 74
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 79
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���򼶱�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϸ��ַ'
          Width = 124
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Width = 130
          Visible = True
        end>
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = '@Return'
      end
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'vsmess'
      end
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
        Name = '�����'
        Caption = '�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '�������'
        Caption = '�������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scard0'
      end
      item
        Name = '���򼶱�'
        Caption = '���򼶱�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = '��ϸ��ַ'
        Caption = '��ϸ��ַ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scusttypes'
      end>
    Top = 183
  end
  inherited MainRequest: TWVRequest
    ID = '������Ϣ��������ѯ'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���򼶱�'
        FieldName = '���򼶱�'
      end
      item
        ParamName = '��ϸ��ַ'
        FieldName = '��ϸ��ַ'
      end>
    Left = 104
    Top = 184
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '37'
      end>
    Left = 144
    Top = 184
  end
  inherited DataSource: TDataSource
    Left = 184
    Top = 184
  end
end
