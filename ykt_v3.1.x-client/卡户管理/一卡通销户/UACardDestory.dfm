inherited faqhCardDestory: TfaqhCardDestory
  Width = 781
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 433
    Width = 781
    Height = 56
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 596
      Top = 4
      Width = 81
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 294
      Top = 42
      Height = 22
      TabOrder = 4
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 35
      Width = 781
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
      TabOrder = 3
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 781
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
    object btnRenewCard: TBitBtn
      Left = 687
      Top = 4
      Width = 81
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '����(&D)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnRenewCardClick
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
    object btnReadCardNo: TBitBtn
      Left = 507
      Top = 4
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '������ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnReadCardNoClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 781
    inherited Image1: TImage
      Width = 781
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 781
    Height = 103
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 44
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label2: TLabel
      Left = 255
      Top = 9
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label3: TLabel
      Left = 249
      Top = 33
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object WVLabel5: TWVLabel
      Left = 470
      Top = 57
      Width = 48
      Height = 12
      Caption = '�ͻ����'
    end
    object WVLabel6: TWVLabel
      Left = 32
      Top = 33
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object WVLabel2: TWVLabel
      Left = 32
      Top = 56
      Width = 48
      Height = 12
      Caption = '�շ����'
    end
    object Label7: TLabel
      Left = 470
      Top = 33
      Width = 48
      Height = 12
      Caption = '�ͻ�����'
    end
    object WVLabel9: TWVLabel
      Left = 32
      Top = 80
      Width = 48
      Height = 12
      Caption = '��ʾ����'
    end
    object WVLabel1: TWVLabel
      Left = 249
      Top = 56
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object WVLabel8: TWVLabel
      Left = 470
      Top = 81
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label5: TLabel
      Left = 249
      Top = 80
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label4: TLabel
      Left = 493
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object WVEdit1: TWVEdit
      Left = 88
      Top = 5
      Width = 125
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
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
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
    object WVComboBox6: TWVComboBox
      Left = 526
      Top = 53
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '�ͻ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVComboBox1: TWVComboBox
      Left = 88
      Top = 28
      Width = 125
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
      Width = 125
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
    object WVEdit8: TWVEdit
      Left = 526
      Top = 29
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<�ͻ�����>'
      WorkView = WorkView
      FieldName = '�ͻ�����'
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
    object WVComboBox5: TWVComboBox
      Left = 526
      Top = 77
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVEdit5: TWVEdit
      Left = 304
      Top = 76
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = '<ע������>'
      WorkView = WorkView
      FieldName = 'ע������'
    end
    object edtCardNo: TWVEdit
      Left = 526
      Top = 5
      Width = 125
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 2
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit4: TWVEdit
      Left = 88
      Top = 77
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<��ʾ����>'
      WorkView = WorkView
      FieldName = '��ʾ����'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 121
    Width = 781
    Height = 312
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 781
      Height = 312
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'sbranch_code0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ/����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�շ����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Caption = '��״̬'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʧ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ʻ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ʻ��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ʻ��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ȡ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ѻ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt5'
          PickList.Strings = ()
          Title.Caption = '�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Caption = '�����������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ȫ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��У����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ҵ����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʾ����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ʺ�'
          Visible = False
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '��ʾ����'
        Caption = '��ʾ����'
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
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        Features.Strings = ()
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
      end
      item
        Name = 'Ǯ����'
        Caption = 'Ǯ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol3'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 132
    Top = 183
  end
  inherited MainRequest: TWVRequest
    ID = '�ѿ����ͻ���Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
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
        ParamName = '��ʾ����'
        FieldName = '��ʾ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end>
    Left = 168
    Top = 184
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'scert_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '89'
      end
      item
        FieldName = 'scust_type2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'sserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '17'
      end
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-56'
      end>
    Left = 200
    Top = 184
  end
  inherited DataSource: TDataSource
    Left = 240
    Top = 184
  end
  object WVRCardDestory: TWVRequest
    WorkView = WVCardDestory
    ID = 'һ��ͨ����'
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
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�Ƿ��п�'
        FieldName = '�Ƿ��п�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���״���'
        FieldName = '���״���'
      end
      item
        ParamName = '�Ƿ���Ѻ��'
        FieldName = '�Ƿ���Ѻ��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�˿���'
        FieldName = '�˿���'
        Direction = bdParam2Field
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end>
    AfterExec = MainRequestAfterExec
    Left = 168
    Top = 240
  end
  object WVCardDestory: TWorkView
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
        DataField = 'vsmess'
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
        Name = '�Ƿ��п�'
        Caption = '�Ƿ��п�'
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
        Name = '�����'
        Caption = '�����'
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
        Name = '�Ƿ���Ѻ��'
        Caption = '�Ƿ���Ѻ��'
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
        Name = '����'
        Caption = '����'
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
        Name = '�˿���'
        Caption = '�˿���'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
    Left = 132
    Top = 239
  end
end
