inherited faqhPatchCardIssue: TfaqhPatchCardIssue
  Width = 746
  Height = 481
  inherited UIPanel1: TUIPanel
    Top = 396
    Width = 746
    Height = 85
    TabOrder = 4
    object WVLabel4: TWVLabel [0]
      Left = 271
      Top = 12
      Width = 24
      Height = 12
      Caption = '���'
    end
    object WVLabel5: TWVLabel [1]
      Left = 373
      Top = 12
      Width = 12
      Height = 12
      Caption = 'Ԫ'
    end
    object WVLabel8: TWVLabel [2]
      Left = 552
      Top = 24
      Width = 7
      Height = 14
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object WVLabel2: TWVLabel [3]
      Left = 48
      Top = 35
      Width = 7
      Height = 14
      Font.Charset = GB2312_CHARSET
      Font.Color = clNavy
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object WVLabel10: TWVLabel [4]
      Left = 8
      Top = 8
      Width = 6
      Height = 12
    end
    object WVLabel12: TWVLabel [5]
      Left = 64
      Top = 11
      Width = 48
      Height = 12
      Caption = '��ֵ��ʽ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel [6]
      Left = 63
      Top = 36
      Width = 48
      Height = 12
      Caption = 'Ʊ�ݺ���'
    end
    object lbl1: TLabel [7]
      Left = 224
      Top = 36
      Width = 72
      Height = 12
      Caption = '������ˮ���'
    end
    object lbl2: TLabel [8]
      Left = 373
      Top = 36
      Width = 12
      Height = 12
      Caption = 'Ԫ'
    end
    inherited btnQuery: TBitBtn
      Left = 573
      Top = 5
      Width = 81
    end
    inherited btnPrint: TBitBtn
      Left = 664
      Top = 107
      TabOrder = 10
      Visible = False
    end
    object btnReleaseCard: TBitBtn
      Left = 659
      Top = 5
      Width = 81
      Height = 25
      Hint = '���п�'
      Anchors = [akTop, akRight]
      Caption = '���п�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = btnReleaseCardClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000000000
        0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000000063FFFF0063FF
        FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00000000000000000029FFFF0063FFFF0094FFFF00000000000000
        000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
        00000000000029FFFF0063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FF
        FF0094FFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000000000
        000063FFFF0063FFFF0063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FF
        FF0094FFFF00CEFFFF0000000000FFFFFF00FFFFFF00FFFFFF000000000063FF
        FF0063FFFF0063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FFFF0094FF
        FF00CEFFFF00CEFFFF00CEFFFF0000000000FFFFFF00FFFFFF000000000063FF
        FF0063FFFF0063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FFFF0094FF
        FF00CEFFFF00C6D6EF00BDBDBD009494940000000000FFFFFF00FFFFFF000000
        000063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FFFF0094FFFF00CEFF
        FF00C6D6EF0084848400949494009494940063949400FFFFFF00FFFFFF00FFFF
        FF000000000063FFFF0063FFFF0094FFFF0094FFFF0094FFFF00CEFFFF00C6D6
        EF0073737300313131005A5A5A009494940084848400BDBDBD00FFFFFF00FFFF
        FF00FFFFFF000000000063FFFF0094FFFF0094FFFF0094FFFF00CEFFFF007373
        73006363290063630000632900006329290052525200ADADAD00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000000063FFFF0094FFFF0094FFFF0094CEFF006363
        2900CECE630094630000946300006363000052525200FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000000063FFFF0094FFFF00CEFFFF00C6D6EF007373
        730063632900CE9429009463000063290000BDBDBD00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000000063FFFF00CEFFFF0000000000BDBD
        BD00313131009463000029290000ADADAD00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000000063FFFF0000000000FFFFFF00BDBD
        BD000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF000000
        0000CECE2900FFFF9400FFFF63000000000000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00000000000000000000000000FFFFFF00FFFFFF00FFFFFF00}
    end
    object cbbType: TWVComboBox
      Left = 117
      Top = 7
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      OnChange = cbbTypeChange
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*63'
    end
    object edtTicketNo: TWVEdit
      Left = 117
      Top = 31
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
    end
    object chkSelect: TWVCheckBox
      Left = 8
      Top = 9
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 4
      OnClick = chkSelectClick
      DefaultChecked = False
      PresentType = cdpEqual
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 64
      Width = 746
      Height = 21
      AutoStyle = False
      BorderColor = clWindow
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      Color = 16184303
      FlatColor = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 746
        Height = 21
        FrameStyle = fsStatus
        Align = alClient
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object chkSaveM: TWVCheckBox
      Left = 392
      Top = 9
      Width = 73
      Height = 17
      Caption = '�������'
      Checked = True
      State = cbChecked
      TabOrder = 5
      OnClick = chkSelectClick
      DefaultChecked = False
      PresentType = cdpEqual
    end
    object edtmoney: TWVDigitalEdit
      Left = 300
      Top = 8
      Width = 69
      Height = 19
      AllowPoint = True
      Precision = 2
      MaxIntLen = 12
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 3
      TabStop = True
      Text = '0'
      WorkView = WVReleaseCard
      FieldName = '�շѽ��'
      SynchronizeByValue = True
    end
    object edtsmlMoney: TWVDigitalEdit
      Left = 300
      Top = 30
      Width = 69
      Height = 19
      AllowPoint = True
      Precision = 2
      MaxIntLen = 12
      Value = 20
      Color = clWindow
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 6
      TabStop = True
      Text = '20'
      SynchronizeByValue = True
    end
    object pb1: TProgressBar
      Left = 0
      Top = 53
      Width = 746
      Height = 11
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 8
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 746
    inherited Image1: TImage
      Width = 746
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 746
    Height = 143
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 88
      Top = 125
      Width = 617
      Height = 12
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 44
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label3: TLabel
      Left = 255
      Top = 9
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label7: TLabel
      Left = 470
      Top = 9
      Width = 48
      Height = 12
      Caption = '�ͻ�����'
    end
    object WVLabel1: TWVLabel
      Left = 470
      Top = 33
      Width = 48
      Height = 12
      Caption = '�ͻ����'
    end
    object Label5: TLabel
      Left = 249
      Top = 33
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object WVLabel6: TWVLabel
      Left = 32
      Top = 33
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object WVLabel7: TWVLabel
      Left = 32
      Top = 56
      Width = 48
      Height = 12
      Caption = '�շ����'
    end
    object WVLabel9: TWVLabel
      Left = 56
      Top = 80
      Width = 24
      Height = 12
      Caption = 'רҵ'
    end
    object Label6: TLabel
      Left = 249
      Top = 80
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object WVLabel11: TWVLabel
      Left = 249
      Top = 56
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label8: TLabel
      Left = 262
      Top = 105
      Width = 36
      Height = 12
      Caption = '���κ�'
    end
    object WVLabel13: TWVLabel
      Left = 470
      Top = 57
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label9: TLabel
      Left = 57
      Top = 104
      Width = 24
      Height = 12
      Caption = '�༶'
    end
    object WVLabel3: TWVLabel
      Left = 470
      Top = 82
      Width = 48
      Height = 12
      Caption = '�������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object WVEdit1: TWVEdit
      Left = 88
      Top = 5
      Width = 126
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object WVEdit2: TWVEdit
      Left = 304
      Top = 5
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
    end
    object WVEdit8: TWVEdit
      Left = 527
      Top = 5
      Width = 127
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<�ͻ�����>'
      WorkView = WorkView
      FieldName = '�ͻ�����'
    end
    object WVComboBox6: TWVComboBox
      Left = 527
      Top = 29
      Width = 127
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '�ͻ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVEdit3: TWVEdit
      Left = 304
      Top = 29
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<֤������>'
      WorkView = WorkView
      FieldName = '֤������'
    end
    object WVComboBox1: TWVComboBox
      Left = 88
      Top = 28
      Width = 126
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '֤������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*87'
    end
    object WVComboBox3: TWVComboBox
      Left = 88
      Top = 51
      Width = 126
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '�շ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object cbbSpec: TWVComboBox
      Left = 88
      Top = 75
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 25
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = 'רҵ'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-23'
    end
    object WVComboBox2: TWVComboBox
      Left = 304
      Top = 52
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
    object WVEdit5: TWVEdit
      Left = 304
      Top = 76
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<ע������>'
      WorkView = WorkView
      FieldName = 'ע������'
    end
    object cbbDept: TWVComboBox
      Left = 527
      Top = 53
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 25
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVEdit6: TWVEdit
      Left = 304
      Top = 101
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 15
      Text = '<�������κ�>'
      WorkView = WorkView
      FieldName = '�������κ�'
    end
    object WVEdit4: TWVEdit
      Left = 88
      Top = 100
      Width = 126
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 14
      Text = '<�༶>'
      WorkView = WorkView
      FieldName = '�༶'
    end
    object cbbCardType: TWVComboBox
      Left = 527
      Top = 78
      Width = 127
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 13
      WorkView = WorkView
      FieldName = '�������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '-5'
    end
    object cbb1: TKSFilterComboBox
      Left = 527
      Top = 52
      Width = 127
      Height = 22
      ListFont.Charset = GB2312_CHARSET
      ListFont.Color = clWindowText
      ListFont.Height = -12
      ListFont.Name = '����'
      ListFont.Style = []
      OnFilterItems = cbb1FilterItems
      TabOrder = 8
    end
    object cbb2: TKSFilterComboBox
      Left = 88
      Top = 74
      Width = 126
      Height = 22
      ListFont.Charset = GB2312_CHARSET
      ListFont.Color = clWindowText
      ListFont.Height = -12
      ListFont.Name = '����'
      ListFont.Style = []
      OnFilterItems = cbb2FilterItems
      TabOrder = 10
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 161
    Width = 746
    Height = 235
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 746
      Height = 235
      DataSource = nil
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      DisabledColor = clHighlightText
      Columns = <
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Width = 56
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ����'
          Width = 77
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 79
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ����'
          Width = 93
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'רҵ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ժϵ'
          Width = 140
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���֤��'
          Width = 131
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ע��ʱ��'
          Width = 106
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵ�绰'
          Width = 114
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�꼶'
          Visible = True
        end>
    end
  end
  object RzListView1: TRzListView [4]
    Left = 0
    Top = 161
    Width = 746
    Height = 235
    Align = alClient
    AlphaSortAll = True
    Checkboxes = True
    Columns = <
      item
        Caption = '��������'
        Width = 70
      end
      item
        Caption = '�ͻ���'
        Width = 60
      end
      item
        Alignment = taCenter
        Caption = 'ѧ/����'
        Width = 80
      end
      item
        Alignment = taCenter
        Caption = '����'
        Width = 80
      end
      item
        Alignment = taCenter
        Caption = '�ͻ����'
        Width = 100
      end
      item
        Caption = '�շ�������'
        Width = 0
      end
      item
        Alignment = taCenter
        Caption = '�շ����'
        Width = 100
      end
      item
        Alignment = taCenter
        Caption = '����'
        Width = 100
      end
      item
        Alignment = taCenter
        Caption = 'רҵ'
        Width = 100
      end
      item
        Alignment = taCenter
        Caption = '��������'
        Width = 70
      end
      item
        Caption = '���κ�'
        Width = 80
      end
      item
        Alignment = taCenter
        Caption = '֤������'
        Width = 70
      end
      item
        Caption = '֤������'
        Width = 349
      end
      item
        Width = 10
      end>
    FlatScrollBars = True
    FrameColor = clInactiveCaption
    FrameHotTrack = True
    FrameVisible = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    SmallImages = ImageList1
    SortType = stBoth
    TabOrder = 2
    ViewStyle = vsReport
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
      end
      item
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
      end
      item
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
      end
      item
        Name = '����'
        Caption = '����'
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
      end
      item
        Name = '֤������'
        Caption = '֤������'
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
      end
      item
        Name = '֤������'
        Caption = '֤������'
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
        Name = '�ͻ����'
        Caption = '�ͻ����'
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
        Name = '�շ����'
        Caption = '�շ����'
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
      end
      item
        Name = 'רҵ'
        Caption = 'רҵ'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        Name = 'ע������'
        Caption = 'ע������'
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
        Name = '�༶'
        Caption = '�༶'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�ͻ���|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Top = 199
  end
  inherited MainRequest: TWVRequest
    ID = '�����ͻ���Ϣ��ѯ'
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
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = 'ע������'
        FieldName = 'ע������'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'רҵ'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 104
    Top = 200
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'lvol0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'scust_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end>
    Left = 152
    Top = 200
  end
  inherited DataSource: TDataSource
    Left = 240
    Top = 200
  end
  object WVRFeeQuery: TWVRequest
    WorkView = WVFeeQuery
    ID = '�����շѲ�ѯ'
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
        ParamName = '�շ���Ϣ'
        FieldName = '�շ���Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ܷ���'
        FieldName = '�ܷ���'
        Direction = bdParam2Field
      end
      item
        ParamName = '���ܺ�'
        FieldName = '���ܺ�'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '�Ƿ񲻼�����'
        FieldName = '�Ƿ񲻼�����'
      end
      item
        ParamName = '����Ч��'
        FieldName = '����Ч��'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end>
    AfterExec = MainRequestAfterExec
    Left = 104
    Top = 240
  end
  object WVFeeQuery: TWorkView
    WorkFields = <
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
        Name = '���ܺ�'
        Caption = '���ܺ�'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
        Name = '�շ���Ϣ'
        Caption = '�շ���Ϣ'
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
        Name = '�ܷ���'
        Caption = '�ܷ���'
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
        Name = '�Ƿ񲻼�����'
        Caption = '�Ƿ񲻼�����'
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
        Name = '����Ч��'
        Caption = '����Ч��'
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
      end>
    Left = 68
    Top = 239
  end
  object WVRReleaseCard: TWVRequest
    WorkView = WVReleaseCard
    ID = '���п�nmg'
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
        ParamName = '����Ա'
        FieldName = '����Ա'
        Direction = bdBiDirection
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��ʾ����'
        FieldName = '��ʾ����'
        Direction = bdBiDirection
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'Ʊ�ݺ���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
        Direction = bdBiDirection
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = '�շѷ�ʽ'
      end
      item
        ParamName = '�շѽ��'
        FieldName = '�շѽ��'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���Ŵ���'
        FieldName = '���Ŵ���'
        Direction = bdParam2Field
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�Ա�'
        FieldName = '�Ա�'
        Direction = bdParam2Field
      end
      item
        ParamName = '����'
        FieldName = '����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '����ֵ'
        FieldName = '����ֵ'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�Ƿ񲻼�����'
        FieldName = '�Ƿ񲻼�����'
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
        Direction = bdParam2Field
      end
      item
        ParamName = '���޶�'
        FieldName = '���޶�'
        Direction = bdParam2Field
      end
      item
        ParamName = '�����޶�'
        FieldName = '�����޶�'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 104
    Top = 280
  end
  object WVReleaseCard: TWorkView
    WorkFields = <
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
        Name = '����Ա'
        Caption = '����Ա'
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
        Name = '��ʾ����'
        Caption = '��ʾ����'
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
        Name = '������'
        Caption = '������'
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
        Name = 'Ʊ�ݺ���'
        Caption = 'Ʊ�ݺ���'
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        Name = '�շѷ�ʽ'
        Caption = '�շѷ�ʽ'
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
        Name = '�շѽ��'
        Caption = '�շѽ��'
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
        Name = '�ͻ����'
        Caption = '�ͻ����'
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
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '���Ŵ���'
        Caption = '���Ŵ���'
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
        Name = '֤������'
        Caption = '֤������'
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
        Name = '�Ա�'
        Caption = '�Ա�'
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
        Name = '������'
        Caption = '������'
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
        Name = '����ֵ'
        Caption = '����ֵ'
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
        Name = '��ˮ��'
        Caption = '��ˮ��'
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
        Name = 'ҵ������'
        Caption = 'ҵ������'
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
        Name = '�Ƿ񲻼�����'
        Caption = '�Ƿ񲻼�����'
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
        Name = '�ն˱��'
        Caption = '�ն˱��'
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
        Name = '�����޶�'
        Caption = '�����޶�'
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
        Name = '���޶�'
        Caption = '���޶�'
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
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
      end>
    Left = 68
    Top = 279
  end
  object WVRelCardOk: TWorkView
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
        DataField = 'vsmess'
      end
      item
        Name = '�ն˱��'
        Caption = '�ն˱��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��ˮ��'
        Caption = '��ˮ��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end
      item
        Name = 'ҵ������'
        Caption = 'ҵ������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��������Ա'
        Caption = '��������Ա'
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
    FieldsMonitors = <>
    Left = 72
    Top = 312
  end
  object WVRRelCardOk: TWVRequest
    WorkView = WVRelCardOk
    ID = '����ȷ��'
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
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
      end
      item
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
      end
      item
        ParamName = '��������Ա'
        FieldName = '��������Ա'
      end>
    Left = 104
    Top = 312
  end
  object ImageList1: TImageList
    Left = 440
    Top = 240
  end
  object WorkView1: TWorkView
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
        DataField = 'vsmess'
      end
      item
        Name = '������'
        Caption = '������'
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
        Name = '�뿨���'
        Caption = '�뿨���'
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
        Name = '���״���'
        Caption = '���״���'
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
        Name = '���'
        Caption = '���'
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
        Name = '��ˮ��'
        Caption = '��ˮ��'
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
        Name = 'ҵ������'
        Caption = 'ҵ������'
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
        Name = '�������'
        Caption = '�������'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
      end>
    Left = 332
    Top = 183
  end
  object WVcashOperCancel: TWorkView
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
        DataField = 'vsmess'
      end
      item
        Name = 'ҵ������'
        Caption = 'ҵ������'
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
        Name = '��ˮ��'
        Caption = '��ˮ��'
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
        Name = '�ն˱��'
        Caption = '�ն˱��'
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
    FieldsMonitors = <>
    Left = 336
    Top = 224
  end
  object WVRcashOperCancel: TWVRequest
    WorkView = WVcashOperCancel
    ID = '��ֵ֧ȡ����nmg'
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
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
      end>
    AfterExec = MainRequestAfterExec
    Left = 376
    Top = 224
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'СǮ����ֵnmg'
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
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�뿨���'
        FieldName = '�뿨���'
      end
      item
        ParamName = '���״���'
        FieldName = '���״���'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        Direction = bdParam2Field
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    AfterExec = MainRequestAfterExec
    Left = 368
    Top = 184
  end
end
