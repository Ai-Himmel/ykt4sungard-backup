inherited faqhSetGateTimeWeek: TfaqhSetGateTimeWeek
  Width = 751
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 751
    TabOrder = 5
    inherited btnQuery: TBitBtn
      Left = 662
      Caption = '�� ��'
    end
    inherited btnPrint: TBitBtn
      Left = 661
      Top = 400
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 751
    inherited Image1: TImage
      Width = 751
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 436
    Width = 751
    Height = 23
    Align = alBottom
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 4
    object chkGateUnAllot: TRzCheckBox
      Left = 5
      Top = 6
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 0
      OnClick = chkGateUnAllotClick
    end
    object chkDevSelectAll: TRzCheckBox
      Left = 325
      Top = 6
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 1
      OnClick = chkDevSelectAllClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 324
    Width = 427
    Height = 418
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Align = alNone
    end
  end
  object RzSizePanel1: TRzSizePanel [4]
    Left = 0
    Top = 18
    Width = 324
    Height = 418
    Color = 16184303
    GradientColorAdjustment = 40
    HotSpotSizePercent = 100
    HotSpotVisible = True
    SizeBarWidth = 5
    TabOrder = 1
    UseGradients = True
    object rzpnl2: TRzPanel
      Left = 0
      Top = 0
      Width = 318
      Height = 105
      Align = alTop
      BorderOuter = fsNone
      Color = 16184303
      TabOrder = 0
      object Label19: TLabel
        Left = 6
        Top = 58
        Width = 72
        Height = 12
        Caption = '��ʱ�������'
      end
      object WVEdit8: TWVEdit
        Left = 85
        Top = 54
        Width = 124
        Height = 20
        Color = clInfoBk
        MaxLength = 9
        ReadOnly = False
        TabOrder = 1
        Text = '<��ѯ.ʱ���������>'
        WorkView = WorkView5
        FieldName = '��ѯ.ʱ���������'
      end
      object btnWeekQuery: TBitBtn
        Left = 236
        Top = 51
        Width = 75
        Height = 25
        Hint = 'ȷ�ϲ���'
        Caption = '�ܲ�ѯ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnWeekQueryClick
      end
    end
    object lvWeek: TRzListView
      Left = 0
      Top = 105
      Width = 318
      Height = 313
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '��ʱ��α��'
          Width = 100
        end
        item
          Caption = '��ʱ�������'
          Width = 197
        end>
      ColumnClick = False
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
    end
  end
  object RzPanel1: TRzPanel [5]
    Left = 324
    Top = 18
    Width = 427
    Height = 418
    Align = alClient
    BorderOuter = fsNone
    Color = 16184303
    TabOrder = 3
    object rzpnl1: TRzPanel
      Left = 0
      Top = 0
      Width = 427
      Height = 105
      Align = alTop
      BorderOuter = fsNone
      BorderShadow = 16184303
      Color = 16184303
      TabOrder = 0
      object Label7: TLabel
        Left = 10
        Top = 9
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label12: TLabel
        Left = 22
        Top = 34
        Width = 36
        Height = 12
        Caption = '��ϵͳ'
      end
      object Label11: TLabel
        Left = 10
        Top = 56
        Width = 48
        Height = 12
        Caption = '�豸״̬'
        Visible = False
      end
      object Label18: TLabel
        Left = 214
        Top = 9
        Width = 60
        Height = 12
        Caption = '�豸����ID'
      end
      object Label15: TLabel
        Left = 202
        Top = 32
        Width = 72
        Height = 12
        Caption = '�豸�����ͺ�'
      end
      object Label16: TLabel
        Left = 10
        Top = 56
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label14: TLabel
        Left = 202
        Top = 55
        Width = 72
        Height = 12
        Caption = '�豸��������'
      end
      object WVEdit3: TWVEdit
        Left = 64
        Top = 5
        Width = 132
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<�豸����>'
        WorkView = WorkView1
        FieldName = '�豸����'
      end
      object WVComboBox7: TWVComboBox
        Left = 64
        Top = 28
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView1
        FieldName = '������ϵͳ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-32'
      end
      object WVComboBox5: TWVComboBox
        Left = 64
        Top = 52
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 6
        Visible = False
        FieldName = '�豸״̬'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*5'
      end
      object WVEdit6: TWVEdit
        Left = 282
        Top = 5
        Width = 132
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<�豸����ID>'
        WorkView = WorkView1
        FieldName = '�豸����ID'
      end
      object WVComboBox8: TWVComboBox
        Left = 282
        Top = 28
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView1
        FieldName = '�豸�����ͺ�'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-35'
      end
      object WVComboBox9: TWVComboBox
        Left = 282
        Top = 51
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView1
        FieldName = '�豸��������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-28'
      end
      object cbbScode: TWVComboBox
        Left = 64
        Top = 52
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView1
        FieldName = '���ʹ���'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*47'
      end
      object btnDevquery: TBitBtn
        Left = 338
        Top = 74
        Width = 75
        Height = 25
        Hint = 'ȷ�ϲ���'
        Caption = '�豸��ѯ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 7
        OnClick = btnDevqueryClick
      end
    end
    object lvGate: TRzListView
      Left = 0
      Top = 105
      Width = 427
      Height = 313
      Align = alClient
      AlphaSortAll = True
      Checkboxes = True
      Columns = <
        item
          Caption = '�Ž����'
          Width = 80
        end
        item
          Caption = '�Ž�����'
          Width = 200
        end
        item
          Caption = '���������'
          Width = 175
        end
        item
          Caption = '����������'
          Width = 60
        end
        item
          Caption = '���ͱ��'
        end
        item
          Caption = '��������'
          Width = 70
        end>
      ColumnClick = False
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
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
        Name = '������־'
        Caption = '������־'
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
        Name = '�豸���'
        Caption = '�豸���'
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
        Name = '���������'
        Caption = '���������'
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
        Name = 'ʱ���ܱ��'
        Caption = 'ʱ���ܱ��'
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
        Name = '���ʹ���'
        Caption = '���ʹ���'
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
        MonitorValueChangedFields = 
          '|�ͻ���|���׿���|������|��ʼ����|��ʼʱ��|��������|����ʱ��|��' +
          '����ʶ|�豸������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�Ž�ʱ��������'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'ʱ���ܱ��'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
  object WVRequest5: TWVRequest
    WorkView = WorkView5
    ID = '��ʱ��β�ѯ'
    Bindings = <
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
        ParamName = 'ʱ���������'
        FieldName = '��ѯ.ʱ���������'
      end
      item
        ParamName = '��һ����'
        FieldName = '��ѯ.��һ����'
      end
      item
        ParamName = '�ܶ�����'
        FieldName = '��ѯ.�ܶ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    Left = 200
    Top = 288
  end
  object WorkView5: TWorkView
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
        Name = '��ѯ.ʱ���������'
        Caption = '��ѯ.ʱ���������'
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
        Name = '��ѯ.��һ����'
        Caption = '��ѯ.��һ����'
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
        Name = '��ѯ.�ܶ�����'
        Caption = '��ѯ.�ܶ�����'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        GroupIndex = 1
        DataField = 'semail'
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
        Name = '��һ����'
        Caption = '��һ����'
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
        DataField = 'lvol1'
      end
      item
        Name = '�ܶ�����'
        Caption = '�ܶ�����'
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
        DataField = 'lvol2'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol3'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol4'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol5'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol6'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol7'
      end
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
          '|��ѯ.ʱ�������|��ѯ.ʱ���������|��ѯ.��һ����|��ѯ.�ܶ���' +
          '���|��ѯ.��������|��ѯ.��������|��ѯ.��������|��ѯ.������' +
          '���|��ѯ.��������|��ѯ.��־|'
      end
      item
        MonitorValueChangedFields = 
          '|ʱ�������|ʱ�������|��־|��һ����|�ܶ�����|��������|' +
          '��������|��������|��������|��������|'
      end>
    Left = 168
    Top = 288
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
        DataType = kdtInteger
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
        Name = '�豸����'
        Caption = '�豸����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '�����豸ע���'
        Caption = '�����豸ע���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd'
      end
      item
        Name = '�豸����ID'
        Caption = '�豸����ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sbank_pwd2'
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
        DataField = 'lvol1'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '�ϼ��豸����ID'
        Caption = '�ϼ��豸����ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '�豸״̬'
        Caption = '�豸״̬'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '�豸��������'
        Caption = '�豸��������'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 164
    Top = 255
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�豸�ǹؼ��ֲ�ѯ'
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
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�����豸ע���'
        FieldName = '�����豸ע���'
      end
      item
        ParamName = '�豸����ID'
        FieldName = '�豸����ID'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = '�ϼ��豸����ID'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '�豸״̬'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�豸��������'
        FieldName = '�豸��������'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 256
  end
end
