inherited faqhSmartTermSetParam: TfaqhSmartTermSetParam
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
  end
  inherited UIPanel2: TUIPanel
    Left = 664
    Top = 432
    Width = 36
    Height = 27
    Align = alNone
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Visible = False
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '…Ë±∏±Í ∂'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ID    sbank_pwd2'
          PickList.Strings = ()
          Title.Caption = '…Ë±∏ŒÔ¿'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = 'ª˙∫≈'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Caption = 'ª˙–Õ¥˙¬Î'
          Visible = True
        end>
    end
  end
  object ibnSetWorkKey: TBitBtn [3]
    Left = 251
    Top = 203
    Width = 158
    Height = 25
    Hint = '…Ë÷√…Ë±∏π§◊˜√‹‘ø'
    Anchors = [akTop, akRight]
    Caption = '…Ë÷√…Ë±∏π§◊˜√‹‘ø'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'ÀŒÃÂ'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = ibnSetWorkKeyClick
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '≤È—ØΩ·π˚ºØ'
        Caption = '≤È—ØΩ·π˚ºØ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '∑µªÿ¬Î'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '…Ë±∏√˚≥∆'
        Caption = '…Ë±∏√˚≥∆'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '»˝æ≈…Ë±∏◊¢≤·∫≈'
        Caption = '»˝æ≈…Ë±∏◊¢≤·∫≈'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '…Ë±∏ŒÔ¿ÌID'
        Caption = '…Ë±∏ŒÔ¿ÌID'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ª˙∫≈'
        Caption = 'ª˙∫≈'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ª˙–Õ¥˙¬Î'
        Caption = 'ª˙–Õ¥˙¬Î'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '…œº∂…Ë±∏ŒÔ¿ÌID'
        Caption = '…œº∂…Ë±∏ŒÔ¿ÌID'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '…Ë±∏◊¥Ã¨'
        Caption = '…Ë±∏◊¥Ã¨'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '…Ë±∏ŒÔ¿Ì–Õ∫≈'
        Caption = '…Ë±∏ŒÔ¿Ì–Õ∫≈'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'À˘ Ù◊”œµÕ≥'
        Caption = 'À˘ Ù◊”œµÕ≥'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '…Ë±∏À˘‘⁄«¯”Ú'
        Caption = '…Ë±∏À˘‘⁄«¯”Ú'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '∏∫‘»À‘±π§∫≈'
        Caption = '∏∫‘»À‘±π§∫≈'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|…Ë±∏√˚≥∆|»˝æ≈…Ë±∏◊¢≤·∫≈|…Ë±∏ŒÔ¿|ª˙∫≈|ª˙–Õ¥˙¬Î|…œº∂…Ë±∏ŒÔ¿|…Ë±∏' +
          '◊¥Ã¨|…Ë±∏ŒÔ¿Ì–Õ∫≈|À˘ Ù◊”œµÕ≥|…Ë±∏À˘‘⁄«¯”Ú|∏∫‘»À‘±π§∫≈|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 28
    Top = 47
  end
  inherited MainRequest: TWVRequest
    ID = ' ÷≥÷ª˙≤Œ ˝…Ë÷√'
    Bindings = <
      item
        ParamName = '≤È—ØΩ·π˚ºØ'
        FieldName = '≤È—ØΩ·π˚ºØ'
        Direction = bdParam2Field
      end
      item
        ParamName = '…Ë±∏√˚≥∆'
        FieldName = '…Ë±∏√˚≥∆'
      end
      item
        ParamName = '»˝æ≈…Ë±∏◊¢≤·∫≈'
        FieldName = '»˝æ≈…Ë±∏◊¢≤·∫≈'
      end
      item
        ParamName = '…Ë±∏ŒÔ¿ÌID'
        FieldName = '…Ë±∏ŒÔ¿ÌID'
      end
      item
        ParamName = 'ª˙∫≈'
        FieldName = 'ª˙∫≈'
      end
      item
        ParamName = 'ª˙–Õ¥˙¬Î'
        FieldName = 'ª˙–Õ¥˙¬Î'
      end
      item
        ParamName = '…œº∂…Ë±∏ŒÔ¿ÌID'
        FieldName = '…œº∂…Ë±∏ŒÔ¿ÌID'
      end
      item
        ParamName = '…Ë±∏◊¥Ã¨'
        FieldName = '…Ë±∏◊¥Ã¨'
      end
      item
        ParamName = '…Ë±∏ŒÔ¿Ì–Õ∫≈'
        FieldName = '…Ë±∏ŒÔ¿Ì–Õ∫≈'
      end
      item
        ParamName = 'À˘ Ù◊”œµÕ≥'
        FieldName = 'À˘ Ù◊”œµÕ≥'
      end
      item
        ParamName = '…Ë±∏À˘‘⁄«¯”Ú'
        FieldName = '…Ë±∏À˘‘⁄«¯”Ú'
      end
      item
        ParamName = '∏∫‘»À‘±π§∫≈'
        FieldName = '∏∫‘»À‘±π§∫≈'
      end
      item
        ParamName = '∑µªÿ¬Î'
        FieldName = '∑µªÿ¬Î'
        Direction = bdParam2Field
      end>
    Left = 64
    Top = 48
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '≤È—ØΩ·π˚ºØ'
    Left = 96
    Top = 48
  end
  inherited DataSource: TDataSource
    Left = 136
    Top = 48
  end
  object wvGetSysParam: TWorkView
    WorkFields = <
      item
        Name = '≤È—ØΩ·π˚ºØ'
        Caption = '≤È—ØΩ·π˚ºØ'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '≤Œ ˝±Í ∂'
        Caption = '≤Œ ˝±Í ∂'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '∑µªÿ¬Î'
        Caption = '∑µªÿ¬Î'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|…Ë±∏√˚≥∆|»˝æ≈…Ë±∏◊¢≤·∫≈|…Ë±∏ŒÔ¿|ª˙∫≈|ª˙–Õ¥˙¬Î|…œº∂…Ë±∏ŒÔ¿|…Ë±∏' +
          '◊¥Ã¨|…Ë±∏ŒÔ¿Ì–Õ∫≈|À˘ Ù◊”œµÕ≥|…Ë±∏À˘‘⁄«¯”Ú|∏∫‘»À‘±π§∫≈|'
      end>
    Left = 28
    Top = 207
  end
  object wvrGetSysParam: TWVRequest
    WorkView = wvGetSysParam
    ID = '∂¡»°π§◊˜√‹‘ø'
    Bindings = <
      item
        ParamName = '≤È—ØΩ·π˚ºØ'
        FieldName = '≤È—ØΩ·π˚ºØ'
        Direction = bdParam2Field
      end
      item
        ParamName = '∑µªÿ¬Î'
        FieldName = '∑µªÿ¬Î'
        Direction = bdParam2Field
      end
      item
        ParamName = '≤Œ ˝±Í÷æ'
        FieldName = '≤Œ ˝±Í ∂'
      end>
    AfterExec = MainRequestAfterExec
    Left = 72
    Top = 208
  end
end
