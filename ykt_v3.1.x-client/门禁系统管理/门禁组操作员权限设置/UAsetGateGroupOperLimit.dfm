inherited faqhsetGateGroupOperLimit: TfaqhsetGateGroupOperLimit
  Width = 681
  Height = 477
  Caption = '�Ž������ԱȨ������'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 503
          Top = 6
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 327
          Top = 6
          Enabled = False
          TabOrder = 2
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
          Top = 6
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 6
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 246
          Top = 6
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
          Top = 11
          Width = 161
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        Align = alNone
        TabOrder = 2
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 677
        Height = 385
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '�Ž�����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Caption = '����Ա��'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����Ա��'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ž�����'
            Width = 250
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 30
          Top = 10
          Width = 60
          Height = 12
          Caption = '�Ž�������'
        end
        object Label2: TLabel
          Left = 258
          Top = 10
          Width = 48
          Height = 12
          Caption = '����Ա��'
        end
        object WVComboBox1: TWVComboBox
          Left = 309
          Top = 5
          Width = 156
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '��ѯ.����Ա��'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-30'
        end
        object edtName: TWVEdit
          Left = 92
          Top = 4
          Width = 149
          Height = 22
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          MaxLength = 9
          ParentFont = False
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.�Ž�������>'
          WorkView = WorkView
          FieldName = '��ѯ.�Ž�������'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        inherited btnOK: TBitBtn
          Left = 505
        end
        inherited btnCancel: TBitBtn
          Left = 593
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 671
          Hints.Strings = ()
        end
        object chkSelectAll: TRzCheckBox
          Left = 216
          Top = 11
          Width = 57
          Height = 17
          Caption = 'ȫѡ'
          FrameColor = 8409372
          HighlightColor = 2203937
          HotTrack = True
          HotTrackColor = 3983359
          HotTrackColorType = htctActual
          State = cbUnchecked
          TabOrder = 3
          OnClick = chkSelectAllClick
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 1
      end
      object lvGate: TRzListView
        Left = 209
        Top = 33
        Width = 468
        Height = 385
        Align = alClient
        Checkboxes = True
        Columns = <
          item
            Caption = '�Ž�����'
            Width = 100
          end
          item
            Caption = '�Ž�������'
            Width = 347
          end>
        ColumnClick = False
        GridLines = True
        MultiSelect = True
        ReadOnly = True
        RowSelect = True
        SortType = stBoth
        TabOrder = 3
        ViewStyle = vsReport
        OnCustomDrawItem = lvGateCustomDrawItem
      end
      object rzszpnl1: TRzSizePanel
        Left = 0
        Top = 33
        Width = 209
        Height = 385
        Color = 16119543
        HotSpotVisible = True
        SizeBarWidth = 7
        TabOrder = 2
        UseGradients = True
        object lst1: TRzCheckList
          Left = 0
          Top = 0
          Width = 201
          Height = 385
          Align = alClient
          ItemHeight = 17
          TabOrder = 0
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 148
    Top = 343
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
        Name = '��ѯ.�Ž�������'
        Caption = '��ѯ.�Ž�������'
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
        Name = '��ѯ.����Ա��'
        Caption = '��ѯ.����Ա��'
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
        Name = '�Ž�����'
        Caption = '�Ž�����'
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
        DataField = 'lvol0'
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
        GroupIndex = 1
        DataField = 'scust_limit'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.�Ž�����|��ѯ.����Ա��|��ѯ.�Ž�������|��ѯ.����Ա��|��' +
          'ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�Ž�����|�Ž�����|����Ա��|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 304
  end
  inherited QueryRequest: TWVRequest
    ID = '�Ž������ԱȨ�޲�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�Ž�������'
        FieldName = '��ѯ.�Ž�������'
      end
      item
        ParamName = '����Ա��'
        FieldName = '��ѯ.����Ա��'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 232
    Top = 304
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 108
    Top = 343
  end
  inherited AddRequest: TWVRequest
    ID = '�Ž������ԱȨ������'
    Bindings = <
      item
        ParamName = '�Ž�����'
        FieldName = '�Ž�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end>
    Left = 112
    Top = 304
  end
  inherited DeleteRequest: TWVRequest
    ID = '�Ž������ԱȨ������'
    Bindings = <
      item
        ParamName = '�Ž�����'
        FieldName = '�Ž�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end>
    Left = 152
    Top = 304
  end
  inherited ChangeRequest: TWVRequest
    ID = '�Ž������ԱȨ������'
    Bindings = <
      item
        ParamName = '�Ž�����'
        FieldName = '�Ž�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end>
    Left = 192
    Top = 304
  end
  inherited WVDataSource: TWVDataSource
    Left = 228
    Top = 343
  end
  inherited alDatasetActions: TActionList
    Left = 188
    Top = 340
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�Ž����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�Ž�����'
        FieldName = '�Ž�����'
      end
      item
        ParamName = '�Ž�������'
        FieldName = '�Ž�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    AfterExec = CheckReturnData
    Left = 112
    Top = 248
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
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
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
        Name = '�Ž�����'
        Caption = '�Ž�����'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '�Ž�������'
        Caption = '�Ž�������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'semail'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�Ž�����|��ѯ.�Ž�������|��ѯ.��������|'
      end
      item
        MonitorValueChangedFields = '|�Ž�����|'
      end>
    Left = 72
    Top = 248
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '����Ա��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 112
    Top = 200
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
        DataField = '@Dataset'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        MonitorValueChangedFields = '|��ʼ����|��������|����Ա����|'
      end>
    Left = 68
    Top = 199
  end
end
