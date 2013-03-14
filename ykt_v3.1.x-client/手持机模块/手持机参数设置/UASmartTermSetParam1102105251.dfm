inherited faqhSmartTermSetParam: TfaqhSmartTermSetParam
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
    end
  end
  inherited Grid: TDBGrid
    Top = 121
    Width = 700
    Height = 338
    OnDrawColumnCell = GridDrawColumnCell
    Columns = <
      item
        Expanded = False
        FieldName = 'lvol0'
        PickList.Strings = ()
        Title.Caption = 'Éè±¸±êÊ¶'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ID    sbank_pwd2'
        PickList.Strings = ()
        Title.Caption = 'Éè±¸ÎïÀ'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        PickList.Strings = ()
        Title.Caption = '»úºÅ'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sbank_code'
        PickList.Strings = ()
        Title.Caption = '»úÐÍ´úÂë'
        Visible = True
      end>
end
  object Panel2: TPanel [2]
    Left = 0
    Top = 0
    Width = 700
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label12: TLabel
      Left = 34
      Top = 5
      Width = 176
      Height = 16
      Caption = 'ÊÖ³Ö»úÁ÷Ë®²É¼¯'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'ºÚÌå'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 25
    Width = 700
    Height = 155
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left    = 42
      Top     = 9
      Width   = 48
      Height  = 12
      Caption = 'Éè±¸Ãû³Æ'
    end
    object Label2: TLabel
      Left    = 206
      Top     = 9
      Width   = 84
      Height  = 12
      Caption = 'Èý¾ÅÉè±¸×¢²áºÅ'
    end
    object Label3: TLabel
      Left    = 448
      Top     = 9
      Width   = 42
      Height  = 12
      Caption = 'Éè±¸ÎïÀ'
    end
    object Label4: TLabel
      Left    = 66
      Top     = 49
      Width   = 24
      Height  = 12
      Caption = '»úºÅ'
    end
    object Label5: TLabel
      Left    = 242
      Top     = 49
      Width   = 48
      Height  = 12
      Caption = '»úÐÍ´úÂë'
    end
    object Label6: TLabel
      Left    = 424
      Top     = 49
      Width   = 66
      Height  = 12
      Caption = 'ÉÏ¼¶Éè±¸ÎïÀ'
    end
    object Label7: TLabel
      Left    = 42
      Top     = 89
      Width   = 48
      Height  = 12
      Caption = 'Éè±¸×´Ì¬'
    end
    object Label8: TLabel
      Left    = 218
      Top     = 89
      Width   = 72
      Height  = 12
      Caption = 'Éè±¸ÎïÀíÐÍºÅ'
    end
    object Label9: TLabel
      Left    = 430
      Top     = 89
      Width   = 60
      Height  = 12
      Caption = 'ËùÊô×ÓÏµÍ³'
    end
    object Label10: TLabel
      Left    = 18
      Top     = 129
      Width   = 72
      Height  = 12
      Caption = 'Éè±¸ËùÔÚÇøÓò'
    end
    object Label11: TLabel
      Left    = 218
      Top     = 129
      Width   = 72
      Height  = 12
      Caption = '¸ºÔðÈËÔ±¹¤ºÅ'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = ''
      WorkView = WorkView
      FieldName = 'Éè±¸Ãû³Æ'
    end
    object WVEdit2: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = ''
      WorkView = WorkView
      FieldName = 'Èý¾ÅÉè±¸×¢²áºÅ'
    end
    object WVEdit3: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = ''
      WorkView = WorkView
      FieldName = 'Éè±¸ÎïÀ'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 45
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = ''
      WorkView = WorkView
      FieldName = '»úºÅ'
    end
    object WVEdit5: TWVEdit
      Left = 300
      Top = 45
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = ''
      WorkView = WorkView
      FieldName = '»úÐÍ´úÂë'
    end
    object WVEdit6: TWVEdit
      Left = 500
      Top = 45
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = ''
      WorkView = WorkView
      FieldName = 'ÉÏ¼¶Éè±¸ÎïÀ'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 85
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 6
      Text = ''
      WorkView = WorkView
      FieldName = 'Éè±¸×´Ì¬'
    end
    object WVEdit8: TWVEdit
      Left = 300
      Top = 85
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
      Text = ''
      WorkView = WorkView
      FieldName = 'Éè±¸ÎïÀíÐÍºÅ'
    end
    object WVEdit9: TWVEdit
      Left = 500
      Top = 85
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 8
      Text = ''
      WorkView = WorkView
      FieldName = 'ËùÊô×ÓÏµÍ³'
    end
    object WVEdit10: TWVEdit
      Left = 100
      Top = 125
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = ''
      WorkView = WorkView
      FieldName = 'Éè±¸ËùÔÚÇøÓò'
    end
    object WVEdit11: TWVEdit
      Left = 300
      Top = 125
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = ''
      WorkView = WorkView
      FieldName = '¸ºÔðÈËÔ±¹¤ºÅ'
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '²éÑ¯½á¹û¼¯'
        Caption = '²éÑ¯½á¹û¼¯'
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
        Name = 'Éè±¸Ãû³Æ'
        Caption = 'Éè±¸Ãû³Æ'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = 'Èý¾ÅÉè±¸×¢²áºÅ'
        Caption = 'Èý¾ÅÉè±¸×¢²áºÅ'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = 'Éè±¸ÎïÀ'
        Caption = 'Éè±¸ÎïÀ'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '»úºÅ'
        Caption = '»úºÅ'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '»úÐÍ´úÂë'
        Caption = '»úÐÍ´úÂë'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = 'ÉÏ¼¶Éè±¸ÎïÀ'
        Caption = 'ÉÏ¼¶Éè±¸ÎïÀ'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = 'Éè±¸×´Ì¬'
        Caption = 'Éè±¸×´Ì¬'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = 'Éè±¸ÎïÀíÐÍºÅ'
        Caption = 'Éè±¸ÎïÀíÐÍºÅ'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = 'ËùÊô×ÓÏµÍ³'
        Caption = 'ËùÊô×ÓÏµÍ³'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = 'Éè±¸ËùÔÚÇøÓò'
        Caption = 'Éè±¸ËùÔÚÇøÓò'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '¸ºÔðÈËÔ±¹¤ºÅ'
        Caption = '¸ºÔðÈËÔ±¹¤ºÅ'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|Éè±¸Ãû³Æ|Èý¾ÅÉè±¸×¢²áºÅ|Éè±¸ÎïÀ|»úºÅ|»úÐÍ´úÂë|ÉÏ¼¶Éè±¸ÎïÀ|Éè±¸×´Ì¬|Éè±¸ÎïÀíÐÍºÅ|ËùÊô×ÓÏµÍ³|Éè±¸ËùÔÚÇøÓò|¸ºÔðÈËÔ±¹¤ºÅ|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = 'ÊÖ³Ö»úÁ÷Ë®²É¼¯'
    Bindings = <
      item
        ParamName = '²éÑ¯½á¹û¼¯'
        FieldName = '²éÑ¯½á¹û¼¯'
        Direction = bdParam2Field
      end
      item
        ParamName = 'Éè±¸Ãû³Æ'
        FieldName = 'Éè±¸Ãû³Æ'
      end
      item
        ParamName = 'Èý¾ÅÉè±¸×¢²áºÅ'
        FieldName = 'Èý¾ÅÉè±¸×¢²áºÅ'
      end
      item
        ParamName = 'Éè±¸ÎïÀ'
        FieldName = 'Éè±¸ÎïÀ'
      end
      item
        ParamName = '»úºÅ'
        FieldName = '»úºÅ'
      end
      item
        ParamName = '»úÐÍ´úÂë'
        FieldName = '»úÐÍ´úÂë'
      end
      item
        ParamName = 'ÉÏ¼¶Éè±¸ÎïÀ'
        FieldName = 'ÉÏ¼¶Éè±¸ÎïÀ'
      end
      item
        ParamName = 'Éè±¸×´Ì¬'
        FieldName = 'Éè±¸×´Ì¬'
      end
      item
        ParamName = 'Éè±¸ÎïÀíÐÍºÅ'
        FieldName = 'Éè±¸ÎïÀíÐÍºÅ'
      end
      item
        ParamName = 'ËùÊô×ÓÏµÍ³'
        FieldName = 'ËùÊô×ÓÏµÍ³'
      end
      item
        ParamName = 'Éè±¸ËùÔÚÇøÓò'
        FieldName = 'Éè±¸ËùÔÚÇøÓò'
      end
      item
        ParamName = '¸ºÔðÈËÔ±¹¤ºÅ'
        FieldName = '¸ºÔðÈËÔ±¹¤ºÅ'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '²éÑ¯½á¹û¼¯'
    Bindings = <
>
    Left = 328
    Top = 240
  end
  inherited DataSource: TDataSource
    Left = 376
    Top = 288
  end
end
