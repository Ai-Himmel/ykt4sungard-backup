inherited faqhBusiPayIn_nju: TfaqhBusiPayIn_nju
  Width = 716
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 716
    TabOrder = 3
    object lbl1: TLabel [0]
      Left = 256
      Top = 8
      Width = 36
      Height = 12
      Caption = 'ժҪ��'
    end
    object lbl2: TLabel [1]
      Left = 8
      Top = 8
      Width = 84
      Height = 12
      AutoSize = False
      Caption = 'Ҫ�����̻���'
    end
    object lblBusiName: TLabel [2]
      Left = 88
      Top = 8
      Width = 169
      Height = 12
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 539
    end
    inherited btnPrint: TBitBtn
      Left = 626
      Top = 1000
      TabOrder = 2
      Visible = False
    end
    object btnPayIn: TBitBtn
      Left = 627
      Top = 3
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '�� ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnPayInClick
    end
    object edtNote: TWVEdit
      Left = 289
      Top = 4
      Width = 224
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<ժҪ>'
      WorkView = WorkView1
      FieldName = 'ժҪ'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 716
    TabOrder = 2
    inherited Image1: TImage
      Width = 716
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 716
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 8
      Width = 48
      Height = 12
      Caption = '����·�'
    end
    object lblCustname: TLabel
      Left = 216
      Top = 6
      Width = 77
      Height = 14
      Caption = 'lblCustname'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object edtMonth: TWVEdit
      Left = 81
      Top = 4
      Width = 96
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 0
      Text = '<�·�>'
      WorkView = WorkView
      FieldName = '�·�'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 43
    Width = 716
    Height = 416
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 507
      Height = 416
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻���'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����·�'
          Width = 80
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 80
          Visible = True
        end>
    end
    inherited RzSizePanel1: TRzSizePanel
      Height = 416
      inherited tvTree: TRzTreeView
        Height = 416
        OnClick = tvCustClick
      end
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
        Name = '�̻���'
        Caption = '�̻���'
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
        Name = '�·�'
        Caption = '�·�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�����|����Ա��|������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 244
    Top = 135
  end
  inherited MainRequest: TWVRequest
    ID = '�̻�����ѯ_nju'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻��ʺ�'
        FieldName = '�̻���'
      end
      item
        ParamName = '�·�'
        FieldName = '�·�'
        DefaultValue = 0
      end>
    Left = 280
    Top = 136
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'damt3'
        DataPresentType = '����'
      end>
    Left = 312
    Top = 136
  end
  inherited DataSource: TDataSource
    Left = 344
    Top = 136
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
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
        Name = '�̻���'
        Caption = '�̻���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�����'
        Caption = '�����'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�·�'
        Caption = '�·�'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = 'ժҪ'
        Caption = 'ժҪ'
        FieldType = wftUndefined
        DataType = kdtString
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
        MonitorValueChangedFields = '|�����|����Ա��|������|'
      end>
    Left = 244
    Top = 175
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�̻����_nju'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
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
        ParamName = 'ժҪ'
        FieldName = 'ժҪ'
      end
      item
        ParamName = '�·�'
        FieldName = '�·�'
      end>
    AfterExec = MainRequestAfterExec
    Left = 280
    Top = 176
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
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
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
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
        MonitorValueChangedFields = '|�̻���ʶ|'
      end>
    Left = 244
    Top = 215
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�̻���Ϣ������ѯ2'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end>
    Left = 280
    Top = 216
  end
end
