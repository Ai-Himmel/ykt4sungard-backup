inherited faqhBusPosManage: TfaqhBusPosManage
  Width = 807
  Height = 650
  inherited UIPanel1: TUIPanel
    Top = 647
    Width = 807
    Height = 3
    TabOrder = 4
    inherited btnQuery: TBitBtn
      Left = 624
      Top = 5
      Hint = ''
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 717
      Top = 5
      Hint = ''
      Enabled = True
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 807
    Height = 16
    TabOrder = 0
    inherited Image1: TImage
      Width = 807
      Height = 16
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 16
    Width = 807
    Height = 0
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label2: TLabel
      Left = 531
      Top = 58
      Width = 72
      Height = 12
      Caption = '�Ƿ񽻴���'
      Visible = False
    end
    object WVLabel1: TWVLabel
      Left = 40
      Top = 58
      Width = 108
      Height = 12
      Caption = '��һ����ȡ���ɱ���'
      Visible = False
    end
    object WVLabel2: TWVLabel
      Left = 295
      Top = 58
      Width = 84
      Height = 12
      Caption = '�Ƿ��˿��ɱ���'
      Visible = False
    end
    object WVComboBox1: TWVComboBox
      Left = 615
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      Visible = False
      WorkView = WorkView
      FieldName = '�Ƿ񽻴���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox2: TWVComboBox
      Left = 159
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      Visible = False
      WorkView = WorkView
      FieldName = '��һ���Ƿ���ȡ���ɱ���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox3: TWVComboBox
      Left = 391
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      Visible = False
      WorkView = WorkView
      FieldName = '�Ƿ��˿��ɱ���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 16
    Width = 807
    Height = 631
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 807
      Height = 631
    end
  end
  object Panel2: TPanel [4]
    Left = 0
    Top = 16
    Width = 807
    Height = 631
    Align = alClient
    BevelOuter = bvNone
    Color = 16184303
    TabOrder = 1
    object GroupBox2: TGroupBox
      Left = 64
      Top = 29
      Width = 666
      Height = 99
      Caption = '���Ѳ�������'
      TabOrder = 1
      object Label5: TLabel
        Left = 53
        Top = 20
        Width = 72
        Height = 12
        Caption = '���Ѳ����汾'
      end
      object Label6: TLabel
        Left = 398
        Top = 20
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label7: TLabel
        Left = 614
        Top = 20
        Width = 12
        Height = 12
        Caption = 'Ԫ'
      end
      object Label8: TLabel
        Left = 29
        Top = 48
        Width = 96
        Height = 12
        Caption = '�ɼ���ˮʱ����'
      end
      object Label9: TLabel
        Left = 277
        Top = 48
        Width = 12
        Height = 12
        Caption = '��'
      end
      object Label10: TLabel
        Left = 350
        Top = 48
        Width = 96
        Height = 12
        Caption = '����ˢ��ʱ����'
      end
      object Label11: TLabel
        Left = 614
        Top = 48
        Width = 12
        Height = 12
        Caption = '��'
      end
      object edtConParaVer: TWVEdit
        Left = 128
        Top = 16
        Width = 140
        Height = 20
        ReadOnly = True
        TabOrder = 0
        Text = 'WVEdit1'
      end
      object edtBaseFee: TWVEdit
        Left = 449
        Top = 16
        Width = 161
        Height = 20
        ReadOnly = False
        TabOrder = 1
        Text = 'WVEdit1'
      end
      object edtTimeSplit: TWVEdit
        Left = 128
        Top = 44
        Width = 140
        Height = 20
        ReadOnly = False
        TabOrder = 2
        Text = 'WVEdit1'
      end
      object edtCardTimeSpace: TWVEdit
        Left = 449
        Top = 44
        Width = 161
        Height = 20
        ReadOnly = False
        TabOrder = 3
        Text = 'WVEdit1'
      end
      object btnCreateFile: TImageButton
        Left = 528
        Top = 70
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '�����Ѳ���'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = btnCreateFileClick
      end
      object CheckBox1: TCheckBox
        Left = 408
        Top = 73
        Width = 112
        Height = 17
        Caption = '�ϴ��ֳֻ��ļ�'
        Checked = True
        State = cbChecked
        TabOrder = 5
        Visible = False
      end
    end
    object grpWelcome: TGroupBox
      Left = 64
      Top = 1000
      Width = 666
      Height = 53
      Caption = '��ӭ��Ϣ����'
      TabOrder = 5
      Visible = False
      object Label13: TLabel
        Left = 40
        Top = 26
        Width = 48
        Height = 12
        Caption = '��ӭ��Ϣ'
      end
      object edtWelcome: TWVEdit
        Left = 93
        Top = 22
        Width = 284
        Height = 20
        ReadOnly = False
        TabOrder = 1
        Text = 'WVEdit1'
      end
      object ImageButton2: TImageButton
        Left = 552
        Top = 21
        Width = 76
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '�����ļ�'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = ImageButton2Click
      end
      object CheckBox2: TCheckBox
        Left = 408
        Top = 24
        Width = 112
        Height = 17
        Caption = '�ϴ��ֳֻ��ļ�'
        TabOrder = 2
      end
    end
    object grpBlackList: TGroupBox
      Left = 64
      Top = 564
      Width = 666
      Height = 43
      Caption = '����������'
      TabOrder = 4
      object btnBala: TImageButton
        Left = 528
        Top = 14
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '��������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnBalaClick
      end
      object CheckBox3: TCheckBox
        Left = 408
        Top = 19
        Width = 112
        Height = 17
        Caption = '�ϴ��ֳֻ��ļ�'
        Checked = True
        State = cbChecked
        TabOrder = 1
        Visible = False
      end
    end
    object GroupBox5: TGroupBox
      Left = 64
      Top = 133
      Width = 666
      Height = 228
      Caption = '��Ȩ������'
      TabOrder = 2
      object Label15: TLabel
        Left = 64
        Top = 19
        Width = 60
        Height = 12
        Caption = '��Ȩ�ް汾'
      end
      object Label4: TLabel
        Left = 232
        Top = 203
        Width = 48
        Height = 12
        Caption = '���ʱ���'
      end
      object edtCardLimit: TWVEdit
        Left = 128
        Top = 15
        Width = 141
        Height = 20
        ReadOnly = True
        TabOrder = 1
        Text = 'WVEdit1'
      end
      object btnSetLimit: TImageButton
        Left = 528
        Top = 14
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '����Ȩ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnSetLimitClick
      end
      object CheckBox4: TCheckBox
        Left = 408
        Top = 17
        Width = 112
        Height = 17
        Caption = '�ϴ��ֳֻ��ļ�'
        Checked = True
        State = cbChecked
        TabOrder = 2
        Visible = False
      end
      object ListView1: TListView
        Left = 6
        Top = 40
        Width = 652
        Height = 153
        BiDiMode = bdLeftToRight
        Checkboxes = True
        Columns = <
          item
            Caption = '�շ����'
            Width = 100
          end
          item
            Caption = '�շ�����'
            Width = 100
          end
          item
            Caption = '���ʱ���'
            Width = 100
          end>
        ColumnClick = False
        MultiSelect = True
        ReadOnly = True
        RowSelect = True
        ParentBiDiMode = False
        TabOrder = 3
        ViewStyle = vsReport
        OnClick = ListView1Click
      end
      object edtFeeBal: TEdit
        Left = 285
        Top = 199
        Width = 121
        Height = 20
        TabOrder = 5
        OnKeyPress = edtFeeBalKeyPress
      end
      object CheckBox5: TCheckBox
        Left = 31
        Top = 201
        Width = 97
        Height = 17
        Caption = 'ȫѡ/ȫ��ѡ'
        TabOrder = 6
        OnClick = CheckBox5Click
      end
      object btnLimitEdit: TImageButton
        Left = 528
        Top = 198
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '�� ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = btnLimitEditClick
      end
    end
    object btnTime: TImageButton
      Left = 592
      Top = 6
      Width = 100
      Height = 23
      Caption = 'ͬ��ʱ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnTimeClick
    end
    object GroupBox1: TGroupBox
      Left = 64
      Top = 364
      Width = 666
      Height = 174
      Caption = '��������'
      TabOrder = 3
      object lbl2: TLabel
        Left = 213
        Top = 146
        Width = 76
        Height = 12
        AutoSize = False
        Caption = '�����������'
      end
      object lblFeeType: TLabel
        Left = 7
        Top = 146
        Width = 180
        Height = 12
        AutoSize = False
        Caption = '�����������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object btnSoundSet: TImageButton
        Left = 528
        Top = 142
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '����������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnSoundSetClick
      end
      object CheckBox6: TCheckBox
        Left = 408
        Top = 19
        Width = 112
        Height = 17
        Caption = '�ϴ��ֳֻ��ļ�'
        Checked = True
        State = cbChecked
        TabOrder = 1
        Visible = False
      end
      object lvSound: TListView
        Left = 6
        Top = 16
        Width = 652
        Height = 121
        BiDiMode = bdLeftToRight
        Columns = <
          item
            Caption = '�շ����'
            Width = 100
          end
          item
            Caption = '�շ�����'
            Width = 100
          end
          item
            Caption = '�����������'
            Width = 100
          end
          item
            Caption = '������������'
            Width = 100
          end>
        ColumnClick = False
        MultiSelect = True
        ReadOnly = True
        RowSelect = True
        ParentBiDiMode = False
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lvSoundClick
      end
      object cbbSound: TRzComboBox
        Left = 288
        Top = 143
        Width = 121
        Height = 20
        Style = csDropDownList
        ItemHeight = 12
        TabOrder = 3
        Text = '0-Ĭ�����'
        OnChange = cbbSoundChange
        Items.Strings = (
          '0-Ĭ�����'
          '1-��ʦ��'
          '2-ѧ����'
          '3-ְ����'
          '4-��ʱ��')
        ItemIndex = 0
      end
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
        Name = '�ͻ��������'
        Caption = '�ͻ��������'
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
        Name = '�Ƿ񽻴���'
        Caption = '�Ƿ񽻴���'
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
        Name = '���ѷ���'
        Caption = '���ѷ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ʽ����Ч��'
        Caption = '��ʽ����Ч��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'Ѻ����'
        Caption = 'Ѻ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '���ɱ���'
        Caption = '���ɱ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�������'
        Caption = '�������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��һ���Ƿ���ȡ���ɱ���'
        Caption = '��һ���Ƿ���ȡ���ɱ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�Ƿ��˿��ɱ���'
        Caption = '�Ƿ��˿��ɱ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�˻�������'
        Caption = '�˻�������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end>
    Left = 356
    Top = 207
  end
  inherited MainRequest: TWVRequest
    ID = '�ͻ�����������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ��������'
        FieldName = '�ͻ��������'
      end
      item
        ParamName = '�Ƿ񽻴���'
        FieldName = '�Ƿ񽻴���'
      end
      item
        ParamName = '���ѷ���'
        FieldName = '���ѷ���'
      end
      item
        ParamName = '��ʽ����Ч��'
        FieldName = '��ʽ����Ч��'
      end
      item
        ParamName = 'Ѻ����'
        FieldName = 'Ѻ����'
      end
      item
        ParamName = '���ɱ���'
        FieldName = '���ɱ���'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��һ���Ƿ���ȡ���ɱ���'
        FieldName = '��һ���Ƿ���ȡ���ɱ���'
      end
      item
        ParamName = '�Ƿ��˿��ɱ���'
        FieldName = '�Ƿ��˿��ɱ���'
      end
      item
        ParamName = '�˻�������'
        FieldName = '�˻�������'
      end>
    Left = 392
    Top = 208
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end>
    Left = 424
    Top = 208
  end
  inherited DataSource: TDataSource
    Left = 456
    Top = 208
  end
  object SaveDialog1: TSaveDialog
    Left = 488
    Top = 212
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
        Name = '�������ݼ�'
        Caption = '�������ݼ�'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 352
    Top = 240
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '��ȡ������'
    Bindings = <
      item
        ParamName = '�������ݼ�'
        FieldName = '�������ݼ�'
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
        Direction = bdParam2Field
      end>
    Left = 416
    Top = 240
  end
  object DataSource1: TDataSource
    Left = 448
    Top = 240
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView1
    FieldName = '�������ݼ�'
    Bindings = <>
    HideUnbindingFields = False
    Left = 384
    Top = 240
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
        Name = '�������ݼ�'
        Caption = '�������ݼ�'
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
        Name = '�ֵ���'
        Caption = '�ֵ���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 'R'
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 352
    Top = 296
  end
  object WVDBBinder2: TWVDBBinder
    DataSource = DataSource2
    WorkView = WorkView2
    FieldName = '�������ݼ�'
    Bindings = <>
    HideUnbindingFields = False
    Left = 384
    Top = 296
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '��ȡ������'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '�������ݼ�'
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
        Direction = bdParam2Field
      end
      item
        ParamName = '������־'
        FieldName = '�ֵ���'
        DefaultValue = 'R'
      end>
    Left = 416
    Top = 296
  end
  object DataSource2: TDataSource
    Left = 448
    Top = 296
  end
end
