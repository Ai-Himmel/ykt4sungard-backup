inherited faqhSetUnitInfo: TfaqhSetUnitInfo
  Width = 773
  Height = 465
  Caption = '��λ��Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 773
    Height = 465
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      object Splitter1: TSplitter [0]
        Left = 185
        Top = 36
        Width = 5
        Height = 370
        Cursor = crHSplit
      end
      inherited UIPanel1: TUIPanel
        Top = 406
        Width = 769
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 521
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 604
          Top = 5
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 437
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 688
          Top = 5
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 10
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 10
          Checked = False
          State = cbUnchecked
          Visible = False
        end
        inherited RBtnAddBrother: TRzRadioButton
          Top = 10
          Anchors = [akLeft, akBottom]
        end
        inherited RbtnAddChild: TRzRadioButton
          Top = 10
          Anchors = [akLeft, akBottom]
        end
      end
      inherited TreeView: TRzTreeView
        Top = 36
        Width = 185
        Height = 370
        Align = alLeft
        DisabledColor = clCaptionText
        Enabled = False
        FrameColor = clCaptionText
        FrameHotColor = clInactiveCaption
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Left = 190
        Top = 36
        Width = 579
        Height = 370
        Align = alClient
        TabOrder = 2
        OnCellClick = GridCellClick
        DisabledColor = clHighlightText
        Columns = <
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���Ŵ���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ԭ���ű���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 132
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����ȫ��'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ϼ�����'
            Width = 142
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ӣ������'
            Width = 157
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 769
        Height = 36
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 34
          Top = 12
          Width = 48
          Height = 12
          Caption = '���Ŵ���'
        end
        object WVLabel2: TWVLabel
          Left = 208
          Top = 12
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object WVLabel4: TWVLabel
          Left = 440
          Top = 12
          Width = 48
          Height = 12
          Caption = '�ϼ�����'
        end
        object WVEdit1: TWVEdit
          Left = 92
          Top = 9
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.��λ����>'
          WorkView = WorkView
          FieldName = '��ѯ.��λ����'
        end
        object WVEdit3: TWVEdit
          Left = 268
          Top = 9
          Width = 157
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.��λ����>'
          WorkView = WorkView
          FieldName = '��ѯ.��λ����'
        end
        object WVEdit6: TWVEdit
          Left = 496
          Top = 9
          Width = 97
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.�ϼ���λ>'
          WorkView = WorkView
          FieldName = '��ѯ.�ϼ���λ'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 58
        Top = 45
        Width = 48
        Height = 12
        Caption = '���Ŵ���'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel [1]
        Left = 52
        Top = 125
        Width = 54
        Height = 12
        Caption = '��������*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel [2]
        Left = 58
        Top = 245
        Width = 48
        Height = 12
        Caption = 'Ӣ������'
      end
      object Label6: TLabel [3]
        Left = 452
        Top = 388
        Width = 48
        Height = 12
        Caption = '�ϼ���λ'
        Visible = False
      end
      object lbl1: TLabel [4]
        Left = 452
        Top = 356
        Width = 48
        Height = 12
        Caption = '�ϼ���λ'
        Visible = False
      end
      object Label3: TLabel [5]
        Left = 58
        Top = 204
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label7: TLabel [6]
        Left = 46
        Top = 85
        Width = 60
        Height = 12
        Caption = 'ԭ���Ŵ���'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel [7]
        Left = 59
        Top = 165
        Width = 48
        Height = 12
        Caption = '����ȫ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 406
        Width = 769
        TabOrder = 9
        inherited btnOK: TBitBtn
          Left = 597
          Top = 5
          TabOrder = 0
        end
        inherited btnCancel: TBitBtn
          Left = 679
          Top = 5
          TabOrder = 1
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 2
        end
      end
      object edtDeptNO: TWVEdit
        Left = 119
        Top = 40
        Width = 250
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 0
        Text = '<��λ����>'
        WorkView = WorkView
        FieldName = '��λ����'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Left = 119
        Top = 120
        Width = 250
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<��λ����>'
        WorkView = WorkView
        FieldName = '��λ����'
        SynchronizeWhenExit = True
      end
      object WVEdit5: TWVEdit
        Left = 119
        Top = 240
        Width = 250
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<Ӣ������>'
        WorkView = WorkView
        FieldName = 'Ӣ������'
        SynchronizeWhenExit = True
      end
      object WVComboBox3: TWVComboBox
        Left = 511
        Top = 384
        Width = 250
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 8
        Visible = False
        WorkView = WorkView
        FieldName = '�ϼ���λ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object edtDeptNo11: TWVEdit
        Left = 512
        Top = 352
        Width = 73
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 6
        Text = '<�ϼ���λ>'
        Visible = False
        WorkView = WorkView
        FieldName = '�ϼ���λ'
        SynchronizeWhenExit = True
      end
      object edtdeptName: TWVEdit
        Left = 584
        Top = 352
        Width = 177
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 7
        Text = '<��λ����>'
        Visible = False
        WorkView = WorkView
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 119
        Top = 200
        Width = 250
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-27'
      end
      object WVEdit2: TWVEdit
        Left = 119
        Top = 80
        Width = 250
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<�ɲ��Ŵ���>'
        WorkView = WorkView
        FieldName = '�ɲ��Ŵ���'
        SynchronizeWhenExit = True
      end
      object WVEdit7: TWVEdit
        Left = 119
        Top = 160
        Width = 250
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<����ȫ��>'
        WorkView = WorkView
        FieldName = '����ȫ��'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 604
    Top = 327
  end
  inherited QueryRequest: TWVRequest
    ID = '��λ��Ϣ��ѯһ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��λ����'
        FieldName = '��ѯ.��λ����'
      end
      item
        ParamName = '��λ����'
        FieldName = '��ѯ.��λ����'
      end
      item
        ParamName = '�ϼ���λ'
        FieldName = '��ѯ.�ϼ���λ'
      end
      item
        ParamName = 'Ӣ������'
        FieldName = '��ѯ.Ӣ������'
      end
      item
        ParamName = '�������'
        FieldName = '��ѯ.�������'
      end>
    Left = 704
    Top = 288
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'semail2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end>
    Left = 572
    Top = 327
  end
  inherited AddRequest: TWVRequest
    ID = '��λ��Ϣ����'
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
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = 'Ӣ������'
        FieldName = 'Ӣ������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�ϼ���λ'
        FieldName = '�ϼ���λ'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '�ɲ��Ŵ���'
        FieldName = '�ɲ��Ŵ���'
      end>
    Left = 608
    Top = 288
  end
  inherited DeleteRequest: TWVRequest
    ID = '��λ��Ϣ����'
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
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = 'Ӣ������'
        FieldName = 'Ӣ������'
      end
      item
        ParamName = '�ϼ���λ'
        FieldName = '�ϼ���λ'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 640
    Top = 288
  end
  inherited ChangeRequest: TWVRequest
    ID = '��λ��Ϣ����'
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
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = 'Ӣ������'
        FieldName = 'Ӣ������'
      end
      item
        ParamName = '�ϼ���λ'
        FieldName = '�ϼ���λ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '�ɲ��Ŵ���'
        FieldName = '�ɲ��Ŵ���'
      end>
    Left = 672
    Top = 288
  end
  inherited WVDataSource: TWVDataSource
    Left = 676
    Top = 327
  end
  inherited alDatasetActions: TActionList
    Left = 636
    Top = 324
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
        Name = '��ѯ�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��ѯ.��λ����'
        Caption = '��ѯ.��λ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��λ����'
        Caption = '��ѯ.��λ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.Ӣ������'
        Caption = '��ѯ.Ӣ������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�ϼ���λ'
        Caption = '��ѯ.�ϼ���λ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�������'
        Caption = '��ѯ.�������'
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
        Name = '��λ����'
        Caption = '��λ����'
        FieldType = wftUndefined
        DomainName = '�ǿ�'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = 'Ӣ������'
        Caption = 'Ӣ������'
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
        DataField = 'ssectypes'
      end
      item
        Name = '��λ����'
        Caption = '��λ����'
        FieldType = wftUndefined
        DomainName = '�ǿ�'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scusttypes'
      end
      item
        Name = '�ϼ���λ'
        Caption = '�ϼ���λ'
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
        DataField = 'semail2'
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
        GroupIndex = 1
        DataField = 'sbranch_code0'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        Name = '�ɲ��Ŵ���'
        Caption = '�ɲ��Ŵ���'
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
        DataField = 'scert_no2'
      end
      item
        Name = '����ȫ��'
        Caption = '����ȫ��'
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
        DataField = 'vsvarstr0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.��λ����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValidChangedFields = '|��λ����|��λ����|�Ƿ�Ժϵ|'
      end>
    Left = 564
    Top = 288
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��λ����'
        Caption = '��λ����'
        FieldType = wftUndefined
        DomainName = '�ǿ�'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.��λ����|'
      end
      item
        MonitorValidChangedFields = '|��λ����|��λ����|�Ƿ�Ժϵ|'
      end>
    Left = 396
    Top = 192
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '��λ��Ϣ������ѯһ'
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
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end>
    AfterExec = CheckReturnData
    Left = 432
    Top = 192
  end
end
