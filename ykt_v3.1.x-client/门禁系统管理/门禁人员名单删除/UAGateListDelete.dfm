inherited faqhGateListDelete: TfaqhGateListDelete
  Width = 880
  Height = 578
  inherited UIPanel1: TUIPanel
    Top = 542
    Width = 880
    Height = 36
    TabOrder = 5
    object Label14: TLabel [0]
      Left = 70
      Top = 14
      Width = 60
      Height = 12
      Caption = '�����ƣ�'
    end
    inherited btnQuery: TBitBtn
      Left = 709
      Top = 6
      Enabled = False
      TabOrder = 4
    end
    inherited btnPrint: TBitBtn
      Left = 246
      Top = 1000
      TabOrder = 9
      Visible = False
    end
    object btnDelete: TBitBtn
      Left = 791
      Top = 6
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = 'ɾ��(&D)'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnDeleteClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFF
        FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF000000FF0000FFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF000000FF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFF
        FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B000000
        FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B000000
        FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFF
        FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF000000FF0000FFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF007B7B7B000000FF007B7B7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    object chkCustUnAllot: TRzCheckBox
      Left = 13
      Top = 12
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      FrameColor = 8409372
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      ParentFont = False
      State = cbUnchecked
      TabOrder = 8
      OnClick = chkCustUnAllotClick
    end
    object btnInfo: TBitBtn
      Left = 631
      Top = 6
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = 'ɾ����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnInfoClick
    end
    object edtTable: TWVEdit
      Left = 132
      Top = 9
      Width = 85
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 7
      Text = 'sheet1'
    end
    object btnOpen: TBitBtn
      Left = 227
      Top = 6
      Width = 75
      Height = 25
      Hint = '��Excel�ĵ�'
      Caption = '��Excel'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnOpenClick
    end
    object btnIMPQuery: TBitBtn
      Left = 307
      Top = 6
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Caption = '&Q ��ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnIMPQueryClick
    end
    object btnCloseConn: TBitBtn
      Left = 386
      Top = 6
      Width = 75
      Height = 25
      Hint = '�Ͽ�����'
      Caption = '�Ͽ�����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnPrintClick
    end
    object btnDelList: TBitBtn
      Left = 550
      Top = 7
      Width = 75
      Height = 25
      Hint = '�Ͽ�����'
      Anchors = [akTop, akRight]
      Caption = '����б�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = btnDelListClick
    end
    object btnErrInfo: TBitBtn
      Left = 466
      Top = 6
      Width = 75
      Height = 25
      Hint = '�Ͽ�����'
      Caption = 'ʧ����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 10
      OnClick = btnErrInfoClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 880
    TabOrder = 4
    inherited Image1: TImage
      Width = 880
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 880
    Height = 127
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label1: TLabel
      Left = 41
      Top = 9
      Width = 48
      Height = 12
      Caption = '�Ž�����'
    end
    object Label4: TLabel
      Left = 66
      Top = 33
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label7: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '�ͻ����'
    end
    object Label10: TLabel
      Left = 66
      Top = 81
      Width = 24
      Height = 12
      Caption = '�༶'
    end
    object Label11: TLabel
      Left = 266
      Top = 81
      Width = 24
      Height = 12
      Caption = 'רҵ'
    end
    object Label2: TLabel
      Left = 242
      Top = 9
      Width = 48
      Height = 12
      Caption = '�Ž����'
    end
    object Label5: TLabel
      Left = 266
      Top = 33
      Width = 24
      Height = 12
      Caption = 'Ժϵ'
    end
    object Label8: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '�շ����'
    end
    object Label12: TLabel
      Left = 490
      Top = 57
      Width = 24
      Height = 12
      Caption = '״̬'
    end
    object Label9: TLabel
      Left = 466
      Top = 80
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label6: TLabel
      Left = 478
      Top = 33
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label3: TLabel
      Left = 470
      Top = 9
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label13: TLabel
      Left = 42
      Top = 105
      Width = 48
      Height = 12
      Caption = '��ɾ��־'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<�Ž�������>'
      WorkView = WorkView1
      FieldName = '�Ž�������'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 29
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<����>'
      WorkView = WorkView1
      FieldName = '����'
    end
    object cbbCustType: TWVComboBox
      Left = 100
      Top = 53
      Width = 117
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView1
      FieldName = '�շ�����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVEdit10: TWVEdit
      Left = 100
      Top = 77
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 9
      Text = '<�༶>'
      WorkView = WorkView1
      FieldName = '�༶'
    end
    object WVComboBox6: TWVComboBox
      Left = 300
      Top = 78
      Width = 141
      Height = 18
      Style = csOwnerDrawFixed
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView1
      FieldName = 'רҵ����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '-23'
    end
    object cbbFeeType: TWVComboBox
      Left = 300
      Top = 53
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView1
      FieldName = '�շ�����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object cbbDep: TWVComboBox
      Left = 300
      Top = 28
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView1
      FieldName = 'Ժϵ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVEdit2: TWVEdit
      Left = 300
      Top = 5
      Width = 141
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<�Ž��豸���>'
      WorkView = WorkView1
      FieldName = '�Ž��豸���'
    end
    object WVEdit3: TWVEdit
      Left = 524
      Top = 5
      Width = 139
      Height = 20
      CharCase = ecUpperCase
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<ѧ����>'
      WorkView = WorkView1
      FieldName = 'ѧ����'
    end
    object WVEdit6: TWVEdit
      Left = 524
      Top = 29
      Width = 139
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
      Text = '<�ͻ���>'
      WorkView = WorkView1
      FieldName = '�ͻ���'
    end
    object WVComboBox1: TWVComboBox
      Left = 524
      Top = 77
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 10
      WorkView = WorkView1
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*133'
    end
    object WVComboBox2: TWVComboBox
      Left = 524
      Top = 53
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView1
      FieldName = '״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*84'
    end
    object WVComboBox3: TWVComboBox
      Left = 100
      Top = 100
      Width = 117
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 12
      WorkView = WorkView1
      FieldName = '��ɾ��־'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*44'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 145
    Width = 880
    Height = 397
    inherited Grid: TRzDBGrid
      Align = alNone
      DataSource = nil
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '�Ž��豸���'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Caption = '�Ž�������'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '�ͻ���'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Caption = '�ͻ�����'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Caption = '�շ�����'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = 'ҽԺ�շѷ�ʽ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Caption = 'ѧ��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '����'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '��״̬'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Caption = '���κ�'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Caption = 'Ժϵ����'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation1'
          PickList.Strings = ()
          Title.Caption = 'רҵ����'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Caption = '�༶'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol7'
          PickList.Strings = ()
          Title.Caption = '״̬'
          Visible = True
        end>
    end
  end
  object lv1: TRzListView [4]
    Left = 0
    Top = 145
    Width = 880
    Height = 397
    Align = alClient
    Checkboxes = True
    Columns = <
      item
        Caption = '�Ž����'
        Width = 60
      end
      item
        Caption = '�Ž�����'
        Width = 150
      end
      item
        Caption = '�ͻ���'
      end
      item
        Caption = 'ѧ/����'
        Width = 80
      end
      item
        Caption = '����'
        Width = 80
      end
      item
        Caption = '״̬��'
        Width = 1
      end
      item
        Caption = '״̬'
        Width = 60
      end
      item
        Caption = '��ɾ��־��'
        Width = 1
      end
      item
        Caption = '��ɾ��־'
        Width = 60
      end
      item
        Caption = 'ʱ����'
        Width = 60
      end
      item
        Caption = '�ͻ����'
        Width = 80
      end
      item
        Caption = '�շ����'
        Width = 80
      end
      item
        Caption = 'Ժϵ'
        Width = 100
      end
      item
        Caption = 'רҵ'
        Width = 57
      end>
    ColumnClick = False
    FlatScrollBars = True
    GridLines = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
  end
  object pnl1: TPanel [5]
    Left = 252
    Top = 265
    Width = 437
    Height = 281
    Anchors = [akRight, akBottom]
    BevelOuter = bvNone
    Color = 16184303
    TabOrder = 3
    Visible = False
    object btn1: TSpeedButton
      Left = 376
      Top = 256
      Width = 57
      Height = 22
      Caption = '�� ��'
      Flat = True
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      OnClick = btn1Click
    end
    object SpeedButton1: TSpeedButton
      Left = 300
      Top = 256
      Width = 57
      Height = 22
      Caption = '�����Ϣ'
      Flat = True
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      OnClick = SpeedButton1Click
    end
    object mmo1: TRzMemo
      Left = 0
      Top = 0
      Width = 437
      Height = 249
      Align = alTop
      ScrollBars = ssBoth
      TabOrder = 0
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        Name = '�Ž����'
        Caption = '�Ž����'
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
        Name = 'ʱ����'
        Caption = 'ʱ����'
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
        MonitorValueChangedFields = 
          '|�Ž�������|�Ž��豸���|ѧ����|����|Ժϵ����|�ͻ���|�ͻ�����|��' +
          '������|ҽԺ�շѷ�ʽ|�༶|רҵ����|״̬|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�Ž���Ա����ɾ��'
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
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�Ž����'
        FieldName = '�Ž����'
      end
      item
        ParamName = 'ʱ����'
        FieldName = 'ʱ����'
        DefaultValue = 0
      end>
    Left = 120
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
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
        Name = '�Ž�������'
        Caption = '�Ž�������'
        FieldType = wftUndefined
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
        Name = '�Ž��豸���'
        Caption = '�Ž��豸���'
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
        FieldType = wftUndefined
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
        Name = 'Ժϵ����'
        Caption = 'Ժϵ����'
        FieldType = wftUndefined
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
        Name = '�շ�����'
        Caption = '�շ�����'
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
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
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
        Name = '�༶'
        Caption = '�༶'
        FieldType = wftUndefined
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
        Name = 'רҵ����'
        Caption = 'רҵ����'
        FieldType = wftUndefined
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
        Name = '״̬'
        Caption = '״̬'
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
        Name = '���κ�'
        Caption = '���κ�'
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
        Name = '��ɾ��־'
        Caption = '��ɾ��־'
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
          '|�Ž�������|�Ž��豸���|ѧ����|����|Ժϵ����|�ͻ���|�ͻ�����|��' +
          '������|ҽԺ�շѷ�ʽ|�༶|רҵ����|״̬|'
      end>
    Left = 84
    Top = 295
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�Ž���Ա������ѯ'
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
        ParamName = '�Ž�������'
        FieldName = '�Ž�������'
      end
      item
        ParamName = '�Ž��豸���'
        FieldName = '�Ž��豸���'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ժϵ����'
        FieldName = 'Ժϵ����'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�շ�����'
        FieldName = '�շ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '��ɾ��־'
        FieldName = '��ɾ��־'
      end>
    AfterExec = MainRequestAfterExec
    Left = 120
    Top = 296
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\����\�½� Microsoft Office Access Ӧ�ó���.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 88
    Top = 336
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 128
    Top = 336
  end
  object dlgOpen: TOpenDialog
    Left = 216
    Top = 336
  end
end
