inherited faqhreturnWaterManageCard: TfaqhreturnWaterManageCard
  Width = 780
  Height = 654
  inherited UIPanel1: TUIPanel
    Top = 624
    Width = 780
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 603
      Caption = '������Ϣ'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 98
      Top = 1000
      Enabled = True
      TabOrder = 2
      Visible = False
    end
    object btnModify: TImageButton
      Left = 691
      Top = 3
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '�޸Ŀ���Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnModifyClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 780
    inherited Image1: TImage
      Width = 780
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 780
    Height = 606
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object lbl1: TLabel
      Left = 94
      Top = 40
      Width = 70
      Height = 14
      Caption = '�շ����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 80
      Top = 99
      Width = 84
      Height = 14
      Caption = 'ˮ��Ǯ���ţ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 94
      Top = 125
      Width = 70
      Height = 14
      Caption = '���ʸ�����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 94
      Top = 216
      Width = 70
      Height = 14
      Caption = '�������ͣ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object bvl1: TBevel
      Left = 352
      Top = 39
      Width = 6
      Height = 498
    end
    object Label4: TLabel
      Left = 44
      Top = 528
      Width = 70
      Height = 14
      Caption = '�շ����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object Label3: TLabel
      Left = 94
      Top = 71
      Width = 70
      Height = 14
      Caption = '�Ƿ���ã�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label36: TLabel
      Left = 94
      Top = 187
      Width = 70
      Height = 14
      Caption = '�Ʒѵ�λ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 94
      Top = 152
      Width = 70
      Height = 14
      Caption = '����ģʽ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object cbbFeeType: TWVComboBox
      Left = 164
      Top = 37
      Width = 157
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 10
      ItemHeight = 12
      TabOrder = 0
      OnChange = cbbFeeTypeChange
      OnExit = cbbFeeTypeExit
      WorkView = WorkView
      FieldName = '��ѯ.�շ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '-43'
    end
    object edtNo: TRzSpinEdit
      Left = 164
      Top = 96
      Width = 157
      Height = 20
      AllowKeyEdit = True
      Max = 10
      Min = 1
      Value = 1
      TabOrder = 3
    end
    object edtRateNum: TRzSpinEdit
      Left = 164
      Top = 122
      Width = 157
      Height = 20
      BlankValue = 1
      AllowKeyEdit = True
      Max = 3
      Min = 1
      Value = 1
      TabOrder = 4
      OnChange = edtRateNumChange
    end
    object rb1: TRzGroupBox
      Tag = 1
      Left = 384
      Top = 40
      Width = 329
      Height = 89
      Caption = '����һ'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 1
      ThemeAware = False
      Visible = False
      object lblUnitName1: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '�۷�ʱ�䵥λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit1: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '����Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '�۷ѽ�λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '�Է�Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label29: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '�ӵ�N���ӿ�ʼ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label31: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '�Է���Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit1: TRzSpinEdit
        Tag = 1
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney1: TRzSpinEdit
        Tag = 1
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN1: TRzSpinEdit
        Tag = 1
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rb2: TRzGroupBox
      Tag = 2
      Left = 384
      Top = 136
      Width = 329
      Height = 89
      Caption = '���ʶ�'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 5
      ThemeAware = False
      Visible = False
      object lblUnitName2: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '�۷�ʱ�䵥λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit2: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '����Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label12: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '�۷ѽ�λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label13: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '�Է�Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label28: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '�ӵ�N���ӿ�ʼ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label32: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '�Է���Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit2: TRzSpinEdit
        Tag = 2
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney2: TRzSpinEdit
        Tag = 2
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN2: TRzSpinEdit
        Tag = 2
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Min = 1
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rb3: TRzGroupBox
      Tag = 3
      Left = 384
      Top = 232
      Width = 329
      Height = 89
      Caption = '������'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 9
      ThemeAware = False
      Visible = False
      object lblUnitName3: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '�۷�ʱ�䵥λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit3: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '����Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label16: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '�۷ѽ�λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label17: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '�Է�Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label27: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '�ӵ�N���ӿ�ʼ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label33: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '�Է���Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit3: TRzSpinEdit
        Tag = 3
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney3: TRzSpinEdit
        Tag = 3
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN3: TRzSpinEdit
        Tag = 3
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Min = 1
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rb4: TRzGroupBox
      Tag = 4
      Left = 384
      Top = 328
      Width = 329
      Height = 89
      Caption = '������'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 10
      ThemeAware = False
      Visible = False
      object lblUnitName4: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '�۷�ʱ�䵥λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit4: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '����Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label20: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '�۷ѽ�λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label21: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '�Է�Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label26: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '�ӵ�N���ӿ�ʼ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label34: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '�Է���Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit4: TRzSpinEdit
        Tag = 4
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney4: TRzSpinEdit
        Tag = 4
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN4: TRzSpinEdit
        Tag = 4
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Min = 1
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rb5: TRzGroupBox
      Tag = 5
      Left = 384
      Top = 422
      Width = 329
      Height = 91
      Caption = '������'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 11
      ThemeAware = False
      Visible = False
      object lblUnitName5: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '�۷�ʱ�䵥λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit5: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '����Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label24: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '�۷ѽ�λ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label25: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '�Է�Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label30: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '�ӵ�N���ӿ�ʼ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label35: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '�Է���Ϊ��λ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit5: TRzSpinEdit
        Tag = 5
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney5: TRzSpinEdit
        Tag = 5
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN5: TRzSpinEdit
        Tag = 5
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Min = 1
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rgUse: TRadioGroup
      Left = 165
      Top = 56
      Width = 156
      Height = 36
      Columns = 2
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '����'
        '������')
      ParentFont = False
      TabOrder = 2
    end
    object rgFeeUnit: TRadioGroup
      Left = 164
      Top = 173
      Width = 157
      Height = 36
      Columns = 2
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        'ʱ��'
        '����')
      ParentFont = False
      TabOrder = 7
      OnClick = rgFeeUnitClick
    end
    object rgFeeType: TRadioGroup
      Left = 164
      Top = 209
      Width = 157
      Height = 101
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '�������ÿ�'
        '�������ÿ�'
        'Ԥ�۷ѿ�'
        '�ѻ�ˮ�ؿ�')
      ParentFont = False
      TabOrder = 8
    end
    object cbbWorkView: TComboBox
      Left = 165
      Top = 149
      Width = 156
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 6
      Items.Strings = (
        '��Ԣģʽ'
        '��ԡ��ģʽ')
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 780
    Height = 606
    Visible = False
    inherited Grid: TRzDBGrid
      Left = 40
      Top = 152
      Align = alNone
      DataSource = nil
      Visible = False
      Columns = <
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Caption = '��������'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SORDER1'
          PickList.Strings = ()
          Title.Caption = '����ʱ��'
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        Name = '��Կ'
        Caption = '��Կ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ʼ����|��������|'
      end>
    Left = 492
    Top = 15
  end
  inherited MainRequest: TWVRequest
    ID = 'ȫ�ֲ���������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��Կ'
        FieldName = '��Կ'
        Direction = bdParam2Field
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
      end>
    Left = 528
    Top = 16
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 560
    Top = 16
  end
  inherited DataSource: TDataSource
    Left = 592
    Top = 16
  end
end
