inherited faqhCardFreezeP: TfaqhCardFreezeP
  Width = 781
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 431
    Width = 781
    Height = 58
    TabOrder = 3
    object lbl1: TLabel [0]
      Left = 72
      Top = 14
      Width = 48
      Height = 12
      Caption = '������'
    end
    inherited btnQuery: TBitBtn
      Left = 517
      Top = 8
      Width = 81
      TabOrder = 3
    end
    inherited btnPrint: TBitBtn
      Left = 22
      Top = 50
      Height = 22
      TabOrder = 9
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 37
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
      TabOrder = 8
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
    object btnPatchOper: TBitBtn
      Left = 603
      Top = 8
      Width = 81
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '��������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnPatchOperClick
    end
    object chkSelect: TCheckBox
      Left = 8
      Top = 12
      Width = 49
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 7
      OnClick = chkSelectClick
    end
    object edtSheetName: TEdit
      Left = 128
      Top = 10
      Width = 73
      Height = 20
      TabOrder = 6
      Text = 'sheet1'
    end
    object btnSelectFile: TImageButton
      Left = 209
      Top = 8
      Width = 74
      Height = 25
      Hint = '����У԰��'
      Caption = 'ѡ���ļ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnSelectFileClick
    end
    object btnImportQuery: TImageButton
      Left = 287
      Top = 8
      Width = 70
      Height = 25
      Hint = '�����ѯ'
      Caption = '�����ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnImportQueryClick
    end
    object btnClear: TImageButton
      Left = 361
      Top = 8
      Width = 74
      Height = 25
      Hint = '�����ѯ'
      Caption = '����б�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnClearClick
    end
    object btnExprot: TBitBtn
      Left = 691
      Top = 8
      Width = 81
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '����Excel'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnExprotClick
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
    Height = 127
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 42
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
      Top = 33
      Width = 48
      Height = 12
      Caption = '�ͻ����'
    end
    object WVLabel6: TWVLabel
      Left = 261
      Top = 80
      Width = 36
      Height = 12
      Caption = '��״̬'
    end
    object WVLabel2: TWVLabel
      Left = 30
      Top = 57
      Width = 48
      Height = 12
      Caption = '�շ����'
    end
    object Label7: TLabel
      Left = 470
      Top = 9
      Width = 48
      Height = 12
      Caption = '�ͻ�����'
    end
    object WVLabel9: TWVLabel
      Left = 30
      Top = 81
      Width = 48
      Height = 12
      Caption = '��ʾ����'
    end
    object WVLabel1: TWVLabel
      Left = 249
      Top = 57
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object WVLabel8: TWVLabel
      Left = 470
      Top = 57
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label6: TLabel
      Left = 42
      Top = 105
      Width = 36
      Height = 12
      Caption = '���κ�'
    end
    object Label5: TLabel
      Left = 249
      Top = 104
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object WVLabel3: TWVLabel
      Left = 30
      Top = 33
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object WVEdit1: TWVEdit
      Left = 86
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
      Top = 29
      Width = 125
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
    object WVComboBox1: TWVComboBox
      Left = 304
      Top = 76
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '��״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*17'
    end
    object WVComboBox3: TWVComboBox
      Left = 86
      Top = 53
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
      Top = 5
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<�ͻ�����>'
      WorkView = WorkView
      FieldName = '�ͻ�����'
    end
    object WVComboBox2: TWVComboBox
      Left = 304
      Top = 53
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
      Top = 53
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVEdit6: TWVEdit
      Left = 86
      Top = 101
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<�������κ�>'
      WorkView = WorkView
      FieldName = '�������κ�'
    end
    object WVEdit5: TWVEdit
      Left = 304
      Top = 100
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 11
      Text = '<ע������>'
      WorkView = WorkView
      FieldName = 'ע������'
    end
    object WVEdit4: TWVEdit
      Left = 86
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
    object WVComboBox4: TWVComboBox
      Left = 86
      Top = 29
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
  end
  inherited UIPanel2: TUIPanel
    Top = 145
    Width = 781
    Height = 286
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 781
      Height = 286
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 1
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
          FieldName = 'stime3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
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
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʾ����'
          Width = 70
          Visible = True
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
    object lvCustUnAllot: TRzListView
      Left = 0
      Top = 0
      Width = 781
      Height = 286
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '��������'
          Width = 100
        end
        item
          Caption = '�ͻ���'
          Width = 60
        end
        item
          Caption = 'ѧ/����'
          Width = 100
        end
        item
          Caption = '����'
          Width = 80
        end
        item
          Caption = '����'
          Width = 60
        end
        item
          Caption = '�ͻ����'
          Width = 80
        end
        item
          Caption = '�շ����'
          Width = 70
        end
        item
          Caption = '����ȫ��'
          Width = 300
        end
        item
          Caption = '�����'
        end
        item
          Caption = '�ʻ����'
          Width = 70
        end>
      ColumnClick = False
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
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
      end
      item
        Name = '��״̬'
        Caption = '��״̬'
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
      end
      item
        ParamName = '��״̬'
        FieldName = '��״̬'
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
  object WVCardFreeze: TWorkView
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
        GroupIndex = 1
      end
      item
        Name = '������־'
        Caption = '������־'
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
        Name = '���汾��'
        Caption = '���汾��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 128
    Top = 224
  end
  object WVRCardFreeze: TWVRequest
    WorkView = WVCardFreeze
    ID = '����ⶳ'
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
        ParamName = '���汾��'
        FieldName = '���汾��'
        Direction = bdParam2Field
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 168
    Top = 224
  end
  object dlgOpen: TOpenDialog
    Left = 128
    Top = 272
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\����\�½� Microsoft Office Access Ӧ�ó���.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 176
    Top = 272
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 216
    Top = 272
  end
  object dlgSave1: TSaveDialog
    Filter = 'Excele�ļ�|*.xls'
    Left = 264
    Top = 273
  end
end
