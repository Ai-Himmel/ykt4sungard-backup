inherited faqhfillTrans: TfaqhfillTrans
  Width = 667
  Height = 491
  inherited UIPanel1: TUIPanel
    Top = 455
    Width = 667
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 496
      Top = 6
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 281
      Visible = False
    end
    object btnTrans: TBitBtn
      Left = 585
      Top = 6
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '��ֵ���'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnQueryClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 667
    inherited Image1: TImage
      Width = 667
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 667
    Height = 437
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 250
      Top = 193
      Width = 56
      Height = 14
      Caption = '����Ա��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 278
      Top = 225
      Width = 28
      Height = 14
      Caption = '����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 250
      Top = 161
      Width = 56
      Height = 14
      Caption = '�����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 278
      Top = 257
      Width = 28
      Height = 14
      Caption = '��ע'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 250
      Top = 129
      Width = 56
      Height = 14
      Caption = '����˺�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object edtOperCode: TWVEdit
      Left = 316
      Top = 189
      Width = 187
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      ReadOnly = False
      TabOrder = 0
      Text = '<����Ա��>'
      WorkView = WorkView
      FieldName = '����Ա��'
    end
    object WVEdit2: TWVEdit
      Left = 316
      Top = 221
      Width = 187
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      MaxLength = 6
      ParentFont = False
      PasswordChar = '*'
      ReadOnly = False
      TabOrder = 1
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit5: TWVEdit
      Left = 316
      Top = 253
      Width = 187
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      ReadOnly = False
      TabOrder = 2
      Text = '<��ע>'
      WorkView = WorkView
      FieldName = '��ע'
    end
    object WVEdit4: TWVEdit
      Left = 316
      Top = 157
      Width = 187
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      MaxLength = 22
      ParentFont = False
      ReadOnly = False
      TabOrder = 3
      Text = '<���>'
      WorkView = WorkView
      FieldName = '���'
    end
    object WVComboBox3: TWVComboBox
      Left = 316
      Top = 127
      Width = 188
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      MaxLength = 8
      TabOrder = 4
      WorkView = WorkView
      FieldName = 'ʳ���˺�'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-49'
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 616
    Top = 408
    Width = 51
    Height = 50
    Align = alNone
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Caption = 'ʣ����'
          Visible = True
        end>
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
      end
      item
        Name = '����Ա��'
        Caption = '����Ա��'
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
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ʳ���˺�'
        Caption = 'ʳ���˺�'
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
        Name = '���'
        Caption = '���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        Name = '��ע'
        Caption = '��ע'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|����Ա��|����|ʳ���˺�|���|��ע|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 12
    Top = 311
  end
  inherited MainRequest: TWVRequest
    ID = '��ֵ���'
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
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ʳ���˺�'
        FieldName = 'ʳ���˺�'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 48
    Top = 312
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 88
    Top = 312
  end
  inherited DataSource: TDataSource
    Left = 128
    Top = 312
  end
end
