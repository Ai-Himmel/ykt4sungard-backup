inherited faqhsetPlanTask: TfaqhsetPlanTask
  Width = 681
  Height = 477
  Caption = '�ƻ��������'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 414
        Width = 677
        Height = 40
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Top = 7
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 499
          Top = 7
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 322
          Top = 7
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 7
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
          Top = 7
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Top = 12
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 41
        Width = 677
        Height = 373
        Columns = <
          item
            Expanded = False
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����˵��'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����·��'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Vsvarstr2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����в���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ÿ��һ��'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ÿ��һ��'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ÿ��һ��'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ʼʱ��'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����ʱ��'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ƿ�����'
            Width = 50
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 23
        Align = alTop
        ParentColor = True
        TabOrder = 0
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label12: TLabel [0]
        Left = 44
        Top = 60
        Width = 48
        Height = 12
        Caption = '������'
      end
      object Label13: TLabel [1]
        Left = 292
        Top = 60
        Width = 48
        Height = 12
        Caption = '����˵��'
      end
      object Label14: TLabel [2]
        Left = 56
        Top = 100
        Width = 36
        Height = 12
        Caption = '������'
      end
      object Label15: TLabel [3]
        Left = 292
        Top = 100
        Width = 48
        Height = 12
        Caption = '����·��'
      end
      object Label16: TLabel [4]
        Left = 32
        Top = 140
        Width = 60
        Height = 12
        Caption = '�����в���'
      end
      object Label17: TLabel [5]
        Left = 292
        Top = 140
        Width = 48
        Height = 12
        Caption = 'ÿ��һ��'
      end
      object Label18: TLabel [6]
        Left = 42
        Top = 180
        Width = 48
        Height = 12
        Caption = 'ÿ��һ��'
      end
      object Label19: TLabel [7]
        Left = 292
        Top = 180
        Width = 48
        Height = 12
        Caption = 'ÿ��һ��'
      end
      object Label20: TLabel [8]
        Left = 44
        Top = 220
        Width = 48
        Height = 12
        Caption = '��ʼʱ��'
      end
      object Label21: TLabel [9]
        Left = 292
        Top = 220
        Width = 48
        Height = 12
        Caption = '����ʱ��'
      end
      object Label23: TLabel [10]
        Left = 42
        Top = 5
        Width = 96
        Height = 16
        Caption = '�ƻ��������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel [11]
        Left = 196
        Top = 220
        Width = 72
        Height = 12
        Caption = '��ʽ��hhmmss'
      end
      object Label2: TLabel [12]
        Left = 460
        Top = 220
        Width = 72
        Height = 12
        Caption = '��ʽ��hhmmss'
      end
      object Label3: TLabel [13]
        Left = 156
        Top = 60
        Width = 48
        Height = 12
        Caption = '�Ƿ�����'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 7
        inherited btnOK: TBitBtn
          Left = 505
        end
        inherited btnCancel: TBitBtn
          Left = 593
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtTaskId: TWVDigitalEdit
        Left = 100
        Top = 56
        Width = 45
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '������'
        SynchronizeByValue = True
      end
      object WVEdit13: TWVEdit
        Left = 350
        Top = 56
        Width = 197
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<����˵��>'
        WorkView = WorkView
        FieldName = '����˵��'
        SynchronizeWhenExit = True
      end
      object WVEdit14: TWVEdit
        Left = 100
        Top = 96
        Width = 173
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<������>'
        WorkView = WorkView
        FieldName = '������'
        SynchronizeWhenExit = True
      end
      object WVEdit15: TWVEdit
        Left = 350
        Top = 96
        Width = 197
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 3
        Text = '<����·��>'
        WorkView = WorkView
        FieldName = '����·��'
        SynchronizeWhenExit = True
      end
      object WVEdit16: TWVEdit
        Left = 100
        Top = 136
        Width = 171
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 4
        Text = '<�����в���>'
        WorkView = WorkView
        FieldName = '�����в���'
        SynchronizeWhenExit = True
      end
      object WVEdit20: TWVEdit
        Left = 100
        Top = 216
        Width = 93
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 5
        Text = '<���п�ʼʱ��>'
        WorkView = WorkView
        FieldName = '���п�ʼʱ��'
        SynchronizeWhenExit = True
      end
      object WVEdit21: TWVEdit
        Left = 350
        Top = 216
        Width = 100
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 6
        Text = '<���н���ʱ��>'
        WorkView = WorkView
        FieldName = '���н���ʱ��'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 350
        Top = 136
        Width = 196
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        MaxLength = 8
        TabOrder = 8
        WorkView = WorkView
        FieldName = 'ÿ��һ��'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*100'
      end
      object WVComboBox2: TWVComboBox
        Left = 100
        Top = 176
        Width = 172
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        MaxLength = 8
        TabOrder = 9
        WorkView = WorkView
        FieldName = 'ÿ����һ��'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*101'
      end
      object WVComboBox3: TWVComboBox
        Left = 350
        Top = 176
        Width = 196
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        MaxLength = 8
        TabOrder = 10
        WorkView = WorkView
        FieldName = 'ÿ��һ��'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*102'
      end
      object WVComboBox4: TWVComboBox
        Left = 214
        Top = 56
        Width = 59
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        MaxLength = 8
        TabOrder = 11
        WorkView = WorkView
        FieldName = '�Ƿ�����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*64'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 508
    Top = 199
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end
      item
        Name = '�������.ɾ��'
        Caption = '�������.ɾ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '�������.�޸�'
        Caption = '�������.�޸�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Lvol0'
      end
      item
        Name = '����˵��'
        Caption = '����˵��'
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
        GroupIndex = 1
        DataField = 'vsvarstr0'
      end
      item
        Name = '������'
        Caption = '������'
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
        GroupIndex = 1
        DataField = 'snote'
      end
      item
        Name = '����·��'
        Caption = '����·��'
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
        GroupIndex = 1
        DataField = 'Vsvarstr1'
      end
      item
        Name = '�����в���'
        Caption = '�����в���'
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
        GroupIndex = 1
        DataField = 'Vsvarstr2'
      end
      item
        Name = 'ÿ��һ��'
        Caption = 'ÿ��һ��'
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
        GroupIndex = 1
        DataField = 'Lvol1'
      end
      item
        Name = 'ÿ����һ��'
        Caption = 'ÿ����һ��'
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
        GroupIndex = 1
        DataField = 'Lvol2'
      end
      item
        Name = 'ÿ��һ��'
        Caption = 'ÿ��һ��'
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
        GroupIndex = 1
        DataField = 'Lvol3'
      end
      item
        Name = '���п�ʼʱ��'
        Caption = '���п�ʼʱ��'
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
        GroupIndex = 1
        DataField = 'stime0'
      end
      item
        Name = '���н���ʱ��'
        Caption = '���н���ʱ��'
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
        GroupIndex = 1
        DataField = 'stime1'
      end
      item
        Name = '�Ƿ�����'
        Caption = '�Ƿ�����'
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
        GroupIndex = 1
        DataField = 'sstatus1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.����˵��|��ѯ.������|��ѯ.����·��|��ѯ.�����в���|��ѯ.ÿ' +
          '��һ��|��ѯ.ÿ����һ��|��ѯ.ÿ��һ��|��ѯ.���п�ʼʱ��|��ѯ.����' +
          '����ʱ��|��ѯ.�Ƿ�����|��ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|������|����˵��|������|����·��|�����в���|ÿ��һ��|ÿ����һ' +
          '��|ÿ��һ��|���п�ʼʱ��|���н���ʱ��|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 424
    Top = 160
  end
  inherited QueryRequest: TWVRequest
    ID = '�ƻ������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 560
    Top = 160
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '100'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '101'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '102'
      end
      item
        FieldName = 'sstatus1'
        WVFieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '64'
      end>
    Left = 468
    Top = 199
  end
  inherited AddRequest: TWVRequest
    ID = '�ƻ��������'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����˵��'
        FieldName = '����˵��'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����·��'
        FieldName = '����·��'
      end
      item
        ParamName = '�����в���'
        FieldName = '�����в���'
      end
      item
        ParamName = 'ÿ��һ��'
        FieldName = 'ÿ��һ��'
      end
      item
        ParamName = 'ÿ����һ��'
        FieldName = 'ÿ����һ��'
      end
      item
        ParamName = 'ÿ��һ��'
        FieldName = 'ÿ��һ��'
      end
      item
        ParamName = '���п�ʼʱ��'
        FieldName = '���п�ʼʱ��'
      end
      item
        ParamName = '���н���ʱ��'
        FieldName = '���н���ʱ��'
      end
      item
        ParamName = '�Ƿ�����'
        FieldName = '�Ƿ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 464
    Top = 160
  end
  inherited DeleteRequest: TWVRequest
    ID = '�ƻ��������'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����˵��'
        FieldName = '����˵��'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����·��'
        FieldName = '����·��'
      end
      item
        ParamName = '�����в���'
        FieldName = '�����в���'
      end
      item
        ParamName = 'ÿ��һ��'
        FieldName = 'ÿ��һ��'
      end
      item
        ParamName = 'ÿ����һ��'
        FieldName = 'ÿ����һ��'
      end
      item
        ParamName = 'ÿ��һ��'
        FieldName = 'ÿ��һ��'
      end
      item
        ParamName = '���п�ʼʱ��'
        FieldName = '���п�ʼʱ��'
      end
      item
        ParamName = '���н���ʱ��'
        FieldName = '���н���ʱ��'
      end
      item
        ParamName = '�Ƿ�����'
        FieldName = '�Ƿ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 496
    Top = 160
  end
  inherited ChangeRequest: TWVRequest
    ID = '�ƻ��������'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����˵��'
        FieldName = '����˵��'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����·��'
        FieldName = '����·��'
      end
      item
        ParamName = '�����в���'
        FieldName = '�����в���'
      end
      item
        ParamName = 'ÿ��һ��'
        FieldName = 'ÿ��һ��'
      end
      item
        ParamName = 'ÿ����һ��'
        FieldName = 'ÿ����һ��'
      end
      item
        ParamName = 'ÿ��һ��'
        FieldName = 'ÿ��һ��'
      end
      item
        ParamName = '���п�ʼʱ��'
        FieldName = '���п�ʼʱ��'
      end
      item
        ParamName = '���н���ʱ��'
        FieldName = '���н���ʱ��'
      end
      item
        ParamName = '�Ƿ�����'
        FieldName = '�Ƿ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 528
    Top = 160
  end
  inherited WVDataSource: TWVDataSource
    Left = 580
    Top = 199
  end
  inherited alDatasetActions: TActionList
    Left = 540
    Top = 196
  end
end
