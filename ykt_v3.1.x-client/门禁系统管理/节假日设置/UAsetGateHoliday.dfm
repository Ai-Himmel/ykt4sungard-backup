inherited faqhsetGateHoliday: TfaqhsetGateHoliday
  Width = 760
  Height = 591
  Caption = '�ڼ�������'
  inherited pcPages: TRzPageControl
    Width = 760
    Height = 591
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 532
        Width = 756
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 495
          Top = 5
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 581
          Top = 5
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 409
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 667
          Top = 5
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 10
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 756
        Align = alNone
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 756
        Height = 499
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '�ڼ��ձ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ڼ�����'
            Width = 200
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 756
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 30
          Top = 10
          Width = 60
          Height = 12
          Caption = '�ڼ��ձ��'
        end
        object Label2: TLabel
          Left = 218
          Top = 10
          Width = 48
          Height = 12
          Caption = '�ڼ�����'
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 100
          Top = 6
          Width = 100
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
          FieldName = '��ѯ.�ڼ��ձ��'
          SynchronizeByValue = True
        end
        object WVEdit2: TWVEdit
          Left = 276
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�ڼ�����>'
          WorkView = WorkView
          FieldName = '��ѯ.�ڼ�����'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label4: TLabel [0]
        Left = 118
        Top = 68
        Width = 70
        Height = 14
        Caption = '�ڼ��ձ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel [1]
        Left = 42
        Top = 5
        Width = 80
        Height = 16
        Caption = '�ڼ�������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel [2]
        Left = 132
        Top = 97
        Width = 56
        Height = 14
        Caption = '�ڼ�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel [3]
        Left = 118
        Top = 125
        Width = 70
        Height = 14
        Caption = '�ڼ�������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel [4]
        Left = 132
        Top = 154
        Width = 56
        Height = 14
        Caption = 'ʱ�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object lblTime: TLabel [5]
        Left = 196
        Top = 171
        Width = 48
        Height = 12
        Caption = 'ʱ�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object btn1: TSpeedButton [6]
        Left = 296
        Top = 148
        Width = 21
        Height = 21
        Caption = '>>>'
        Flat = True
        OnClick = btn1Click
      end
      object lblNo: TLabel [7]
        Left = 118
        Top = 36
        Width = 70
        Height = 14
        Caption = '�ڼ��ձ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object Label8: TLabel [8]
        Left = 298
        Top = 124
        Width = 14
        Height = 14
        Caption = '��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 532
        Width = 756
        TabOrder = 1
        inherited btnOK: TBitBtn
          Left = 584
          Caption = '��������'
        end
        inherited btnCancel: TBitBtn
          Left = 672
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
        object btnDelDate: TBitBtn
          Left = 458
          Top = 8
          Width = 75
          Height = 25
          Hint = '��ѯ/ˢ������'
          Anchors = [akTop, akRight]
          Caption = 'ɾ������'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = btnDelDateClick
        end
        object btnSet: TBitBtn
          Left = 370
          Top = 8
          Width = 75
          Height = 25
          Hint = '��ѯ/ˢ������'
          Anchors = [akTop, akRight]
          Caption = '��������'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = btnSetClick
        end
      end
      object edtNo: TWVDigitalEdit
        Left = 196
        Top = 64
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�ڼ��ձ��'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 196
        Top = 92
        Width = 221
        Height = 22
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        ReadOnly = False
        TabOrder = 2
        Text = '<�ڼ�����>'
        WorkView = WorkView
        FieldName = '�ڼ�����'
      end
      object edtTime: TWVEdit
        Left = 196
        Top = 149
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 3
        Text = '0'
        OnChange = edtTimeChange
      end
      object dtpTime: TDateTimePicker
        Left = 196
        Top = 120
        Width = 100
        Height = 20
        CalAlignment = dtaLeft
        Date = 39177.4242927083
        Time = 39177.4242927083
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkDate
        ParseInput = False
        TabOrder = 4
        OnChange = dtpTimeChange
      end
      object lvTime: TRzListView
        Left = 120
        Top = 192
        Width = 297
        Height = 305
        Columns = <
          item
            Caption = '�ڼ�������'
            Width = 100
          end
          item
            Caption = 'ʱ�������'
            Width = 177
          end>
        ColumnClick = False
        FlatScrollBars = True
        GridLines = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 5
        ViewStyle = vsReport
        OnClick = lvTimeClick
        OnCustomDrawItem = lvTimeCustomDrawItem
      end
      object dtpETime: TDateTimePicker
        Left = 316
        Top = 120
        Width = 100
        Height = 20
        CalAlignment = dtaLeft
        Date = 39177.4242927083
        Time = 39177.4242927083
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkDate
        ParseInput = False
        TabOrder = 6
      end
      object pnlQuery: TPanel
        Left = 318
        Top = 149
        Width = 401
        Height = 385
        Color = 15458000
        TabOrder = 7
        Visible = False
        object Label16: TLabel
          Left = 6
          Top = 18
          Width = 24
          Height = 12
          Caption = '��ʶ'
        end
        object Label18: TLabel
          Left = 145
          Top = 18
          Width = 72
          Height = 12
          Caption = 'ʱ���������'
        end
        object WVEdit1: TWVEdit
          Left = 36
          Top = 14
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.��ʶ>'
          WorkView = WorkView2
          FieldName = '��ѯ.��ʶ'
        end
        object WVEdit4: TWVEdit
          Left = 220
          Top = 14
          Width = 157
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.ʱ�������>'
          WorkView = WorkView2
          FieldName = '��ѯ.ʱ�������'
        end
        object pnl1: TPanel
          Left = 1
          Top = 352
          Width = 399
          Height = 32
          Align = alBottom
          BevelOuter = bvNone
          Color = 15458000
          TabOrder = 2
          object btnTimeQuery: TBitBtn
            Left = 144
            Top = 4
            Width = 75
            Height = 25
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = '�顡ѯ'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            OnClick = btnTimeQueryClick
          end
          object btnSelect: TBitBtn
            Left = 232
            Top = 4
            Width = 75
            Height = 25
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = 'ѡ����'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
            OnClick = btnSelectClick
          end
          object btnCancle: TBitBtn
            Left = 320
            Top = 4
            Width = 75
            Height = 25
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = 'ȡ����'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
            OnClick = btnCancleClick
          end
        end
        object dbgrd1: TDBGrid
          Left = 1
          Top = 40
          Width = 399
          Height = 312
          Align = alBottom
          DataSource = DataSource1
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ReadOnly = True
          TabOrder = 3
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -12
          TitleFont.Name = '����'
          TitleFont.Style = []
          OnDblClick = dbgrd1DblClick
          Columns = <
            item
              Expanded = False
              FieldName = 'lcert_code'
              Title.Caption = '��ʶ'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail'
              Title.Caption = 'ʱ���������'
              Width = 200
              Visible = True
            end>
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 492
    Top = 71
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
        Name = '��ѯ.�ڼ��ձ��'
        Caption = '��ѯ.�ڼ��ձ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '��ѯ.�ڼ�����'
        Caption = '��ѯ.�ڼ�����'
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
        Name = '�ڼ��ձ��'
        Caption = '�ڼ��ձ��'
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
        Name = '�ڼ�����'
        Caption = '�ڼ�����'
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
        GroupIndex = 1
        DataField = 'semail'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�ڼ��ձ��|��ѯ.�ڼ�����|��ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�ڼ��ձ��|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 376
    Top = 32
  end
  inherited QueryRequest: TWVRequest
    ID = '�ڼ��ղ�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ڼ��ձ��'
        FieldName = '��ѯ.�ڼ��ձ��'
      end
      item
        ParamName = '�ڼ�����'
        FieldName = '��ѯ.�ڼ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 520
    Top = 32
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 452
    Top = 71
  end
  inherited AddRequest: TWVRequest
    ID = '�ڼ�������'
    Bindings = <
      item
        ParamName = '�ڼ��ձ��'
        FieldName = '�ڼ��ձ��'
        Direction = bdBiDirection
      end
      item
        ParamName = '�ڼ�����'
        FieldName = '�ڼ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 408
    Top = 32
  end
  inherited DeleteRequest: TWVRequest
    ID = '�ڼ�������'
    Bindings = <
      item
        ParamName = '�ڼ��ձ��'
        FieldName = '�ڼ��ձ��'
      end
      item
        ParamName = '�ڼ�����'
        FieldName = '�ڼ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 448
    Top = 32
  end
  inherited ChangeRequest: TWVRequest
    ID = '�ڼ�������'
    Bindings = <
      item
        ParamName = '�ڼ��ձ��'
        FieldName = '�ڼ��ձ��'
        Direction = bdBiDirection
      end
      item
        ParamName = '�ڼ�����'
        FieldName = '�ڼ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 488
    Top = 32
  end
  inherited WVDataSource: TWVDataSource
    Left = 524
    Top = 71
  end
  inherited alDatasetActions: TActionList
    Left = 532
    Top = 108
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
        Name = '�ڼ��ձ��'
        Caption = '�ڼ��ձ��'
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
        Name = '�ڼ�������'
        Caption = '�ڼ�������'
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
      end
      item
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        Name = '��־'
        Caption = '��־'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�ڼ��ձ��|��ѯ.�ڼ�����|��ѯ.��������|'
      end
      item
        MonitorValueChangedFields = '|�ڼ��ձ��|'
      end>
    Left = 424
    Top = 144
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�ڼ�����ϸ����'
    Bindings = <
      item
        ParamName = 'ʱ�������'
        FieldName = 'ʱ�������'
      end
      item
        ParamName = '�ڼ��ձ��'
        FieldName = '�ڼ��ձ��'
      end
      item
        ParamName = '�ڼ�������'
        FieldName = '�ڼ�������'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end>
    AfterExec = CheckReturnData
    Left = 464
    Top = 144
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView2
    FieldName = '��ѯ�����'
    Bindings = <>
    HideUnbindingFields = False
    Left = 412
    Top = 279
  end
  object DataSource1: TDataSource
    OnStateChange = DataSourceStateChange
    OnDataChange = DataSourceDataChange
    Left = 444
    Top = 279
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = 'ʱ������ѯ'
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
        ParamName = 'ʱ�������'
        FieldName = '��ѯ.ʱ�������'
      end
      item
        ParamName = '��ʶ'
        FieldName = '��ѯ.��ʶ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    AfterExec = CheckReturnData
    Left = 480
    Top = 280
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
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
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
        Name = '��ѯ.ʱ�������'
        Caption = '��ѯ.ʱ�������'
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
        Name = '��ѯ.��ʶ'
        Caption = '��ѯ.��ʶ'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.ʱ�������|��ѯ.��ʶ|��ѯ.��������|'
      end
      item
        MonitorValueChangedFields = '|ʱ�������|'
      end>
    Left = 376
    Top = 280
  end
  object WVRequest3: TWVRequest
    WorkView = WorkView3
    ID = '�ڼ�����ϸ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ڼ��ձ��'
        FieldName = '�ڼ��ձ��'
      end
      item
        ParamName = '�ڼ�������'
        FieldName = '�ڼ�������'
      end>
    AfterExec = CheckReturnData
    Left = 176
    Top = 360
  end
  object WorkView3: TWorkView
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
        Name = '�ڼ��ձ��'
        Caption = '�ڼ��ձ��'
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
        Name = '�ڼ�������'
        Caption = '�ڼ�������'
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
        MonitorValueChangedFields = '|��ѯ.�ڼ��ձ��|��ѯ.�ڼ�����|��ѯ.��������|'
      end
      item
        MonitorValueChangedFields = '|�ڼ��ձ��|'
      end>
    Left = 144
    Top = 360
  end
end
