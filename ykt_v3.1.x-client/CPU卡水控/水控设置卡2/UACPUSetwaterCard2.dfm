inherited faqhUACPUSetwaterCard: TfaqhUACPUSetwaterCard
  Width = 787
  Height = 580
  inherited UIPanel1: TUIPanel
    Top = 544
    Width = 787
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 130
      Top = 1000
      TabOrder = 5
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 105
      Top = 1000
      Enabled = True
      TabOrder = 4
      Visible = False
    end
    object btnRateSet: TBitBtn
      Left = 545
      Top = 6
      Width = 129
      Height = 25
      Hint = '���з������ÿ�'
      Anchors = [akTop, akRight]
      Caption = '���з������ÿ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnRateSetClick
    end
    object btnConCard: TBitBtn
      Left = 687
      Top = 6
      Width = 89
      Height = 25
      Hint = '�������ÿ�'
      Anchors = [akTop, akRight]
      Caption = '�������ÿ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnConCardClick
    end
    object btnClear: TBitBtn
      Left = 346
      Top = 6
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '�������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnClearClick
    end
    object btnSave2Db: TBitBtn
      Left = 432
      Top = 6
      Width = 101
      Height = 25
      Hint = '����������õ����ݿ�'
      Anchors = [akTop, akRight]
      Caption = '���浽���ݿ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnSave2DbClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 787
    inherited Image1: TImage
      Width = 787
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 787
    Height = 526
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object lbl1: TLabel
      Left = 86
      Top = 80
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
      Left = 72
      Top = 137
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
      Left = 86
      Top = 163
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
      Left = 86
      Top = 255
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
    object Label35: TLabel
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
      Left = 86
      Top = 109
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
    object Label6: TLabel
      Left = 86
      Top = 215
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
      Left = 86
      Top = 190
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
    object lbl2: TLabel
      Left = 86
      Top = 52
      Width = 70
      Height = 14
      Caption = '�������ƣ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object cbbFeeType: TWVComboBox
      Left = 156
      Top = 75
      Width = 157
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 10
      ItemHeight = 12
      TabOrder = 2
      OnChange = cbbFeeTypeChange
      OnExit = cbbFeeTypeExit
      WorkView = WorkView
      FieldName = '��ѯ.�շ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '-43'
    end
    object edtNo: TRzSpinEdit
      Left = 156
      Top = 134
      Width = 157
      Height = 20
      AllowKeyEdit = True
      Max = 10
      TabOrder = 4
    end
    object edtRateNum: TRzSpinEdit
      Left = 156
      Top = 160
      Width = 157
      Height = 20
      BlankValue = 1
      AllowKeyEdit = True
      Max = 3
      Min = 1
      Value = 1
      TabOrder = 6
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
      TabOrder = 0
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
      object Label30: TLabel
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
      TabOrder = 11
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
      TabOrder = 12
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
      object Label4: TLabel
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
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rgUse: TRzRadioGroup
      Left = 157
      Top = 94
      Width = 156
      Height = 38
      Caption = ' '
      Color = 16184303
      Columns = 2
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ItemFrameColor = 8409372
      ItemHotTrack = True
      ItemHighlightColor = 2203937
      ItemHotTrackColor = 3983359
      ItemHotTrackColorType = htctActual
      ItemIndex = 0
      Items.Strings = (
        '����'
        '������')
      ParentFont = False
      TabOrder = 3
    end
    object rgFeeType: TRzRadioGroup
      Left = 156
      Top = 249
      Width = 157
      Height = 110
      Caption = ' '
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ItemFrameColor = 8409372
      ItemHotTrack = True
      ItemHighlightColor = 2203937
      ItemHotTrackColor = 3983359
      ItemHotTrackColorType = htctActual
      ItemIndex = 0
      Items.Strings = (
        '�������ÿ�'
        '�������ÿ�'
        'Ԥ�۷ѿ�'
        '�ѻ�ˮ�ؿ�')
      ParentFont = False
      TabOrder = 10
    end
    object rgFeeUnit: TRzRadioGroup
      Left = 156
      Top = 208
      Width = 157
      Height = 39
      Caption = ' '
      Color = 16184303
      Columns = 2
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ItemFrameColor = 8409372
      ItemHotTrack = True
      ItemHighlightColor = 2203937
      ItemHotTrackColor = 3983359
      ItemHotTrackColorType = htctActual
      ItemIndex = 0
      Items.Strings = (
        'ʱ��'
        '����')
      ParentFont = False
      TabOrder = 8
      OnClick = rgFeeUnitClick
    end
    object cbbWorkView: TComboBox
      Left = 157
      Top = 187
      Width = 156
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 7
      Items.Strings = (
        '��Ԣģʽ'
        '��ԡ��ģʽ')
    end
    object edtFeeName: TWVEdit
      Left = 156
      Top = 47
      Width = 157
      Height = 22
      Color = clBtnHighlight
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      MaxLength = 22
      ParentFont = False
      ReadOnly = False
      TabOrder = 1
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 752
    Top = 576
    Width = 35
    Height = 29
    Align = alNone
    TabOrder = 3
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '������־'
        Caption = '������־'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ʼ����|��������|'
      end>
    Left = 548
    Top = 15
  end
  inherited MainRequest: TWVRequest
    ID = 'ȫ�ֲ���������ѯ_water'
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
        ParamName = '��Կ'
        FieldName = '��Կ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 584
    Top = 16
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 624
    Top = 16
  end
  inherited DataSource: TDataSource
    Left = 656
    Top = 16
  end
  object wvrSaveFeeType: TWVRequest
    WorkView = wvSaveFeeType
    ID = '����������ÿ�'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '���ʱ��'
        FieldName = '���ʱ��'
        Direction = bdBiDirection
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end
      item
        ParamName = '�Ʒѵ�λ'
        FieldName = '�Ʒѵ�λ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���ʸ���'
        FieldName = '���ʸ���'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����ʱ��1'
        FieldName = '����ʱ��1'
      end
      item
        ParamName = '���ʽ��1'
        FieldName = '���ʽ��1'
      end
      item
        ParamName = '���ʷ���1'
        FieldName = '���ʷ���1'
      end
      item
        ParamName = '����ʱ��2'
        FieldName = '����ʱ��2'
      end
      item
        ParamName = '���ʽ��2'
        FieldName = '���ʽ��2'
      end
      item
        ParamName = '���ʷ���2'
        FieldName = '���ʷ���2'
      end
      item
        ParamName = '����ʱ��3'
        FieldName = '����ʱ��3'
      end
      item
        ParamName = '���ʽ��3'
        FieldName = '���ʽ��3'
      end
      item
        ParamName = '���ʷ���3'
        FieldName = '���ʷ���3'
      end>
    AfterExec = MainRequestAfterExec
    Left = 584
    Top = 56
  end
  object wvSaveFeeType: TWorkView
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
        Name = '��־'
        Caption = '��־'
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
        Name = '���ʱ��'
        Caption = '���ʱ��'
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
        Name = '��������'
        Caption = '��������'
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
        Name = 'Ǯ����'
        Caption = 'Ǯ����'
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
        Name = '�Ʒѵ�λ'
        Caption = '�Ʒѵ�λ'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '���ʸ���'
        Caption = '���ʸ���'
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
        Name = '�շ����'
        Caption = '�շ����'
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
        Name = '����'
        Caption = '����'
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
        Name = '����ʱ��1'
        Caption = '����ʱ��1'
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
        Name = '���ʽ��1'
        Caption = '���ʽ��1'
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
        Name = '���ʷ���1'
        Caption = '���ʷ���1'
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
        Name = '����ʱ��2'
        Caption = '����ʱ��2'
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
        Name = '���ʽ��2'
        Caption = '���ʽ��2'
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
        Name = '���ʷ���2'
        Caption = '���ʷ���2'
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
        Name = '����ʱ��3'
        Caption = '����ʱ��3'
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
        Name = '���ʽ��3'
        Caption = '���ʽ��3'
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
        Name = '���ʷ���3'
        Caption = '���ʷ���3'
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
        MonitorValueChangedFields = '|��ʼ����|��������|'
      end>
    Left = 548
    Top = 55
  end
end
