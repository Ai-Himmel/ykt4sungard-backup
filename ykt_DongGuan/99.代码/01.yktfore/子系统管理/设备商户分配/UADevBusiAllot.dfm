inherited faqhDevBusiAllot: TfaqhDevBusiAllot
  Width = 1038
  Height = 489
  inherited UIPnlQueryCount: TUIPanel [0]
    Width = 1038
    TabOrder = 2
    inherited Image1: TImage
      Width = 1038
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
      Visible = False
    end
  end
  inherited UIPanel1: TUIPanel [1]
    Top = 456
    Width = 1038
    Height = 33
    TabOrder = 3
    object lblBusi: TLabel [0]
      Left = 16
      Top = 8
      Width = 497
      Height = 12
      AutoSize = False
      Caption = 'lblBusi'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 853
      Caption = '�� ��'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 476
      Top = 200
      TabOrder = 2
    end
    object btnDel: TBitBtn
      Left = 949
      Top = 3
      Width = 79
      Height = 25
      Hint = 'ɾ��'
      Anchors = [akTop, akRight]
      Caption = '�����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnDelClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 524
    Width = 514
    Height = 438
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Left = 96
      Top = 240
      Width = 270
      Height = 142
      Align = alNone
      DataSource = nil
      TabOrder = 2
      Columns = <
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸��ʶ'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����'
          Width = 87
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����ID'
          Width = 71
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ʹ���'
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������˿�����'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ϼ��豸'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scurrency_type'
          PickList.Strings = ()
          Title.Caption = '��Ƭ�ṹ'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������˿ں�'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸״̬'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ͨѶ�˿ں�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'IP��ַ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ϵͳ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt5'
          PickList.Strings = ()
          Title.Caption = '�豸��;'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = 'ͨѶ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������汾'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Caption = '��ע'
          Width = 120
          Visible = True
        end>
    end
    object lvDev: TRzListView
      Left = 0
      Top = 85
      Width = 514
      Height = 156
      Align = alClient
      Columns = <
        item
          Caption = '��������'
          Width = 100
        end
        item
          Caption = '�豸���'
          Width = 70
        end
        item
          Caption = '�豸����'
          Width = 120
        end
        item
          Caption = '�豸�ն˺�'
          Width = 80
        end
        item
          Caption = '�豸���к�'
          Width = 100
        end
        item
          Caption = '�豸�ͺ�'
          Width = 80
        end
        item
          Caption = '�豸����'
          Width = 80
        end
        item
          Caption = '�豸��;'
          Width = 80
        end
        item
          Caption = '�豸״̬'
          Width = 80
        end
        item
          Caption = '��������'
          Width = 80
        end>
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnClick = lvDevClick
    end
    object rzszpnl1: TRzSizePanel
      Left = 0
      Top = 241
      Width = 514
      Height = 197
      Align = alBottom
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 1
      UseGradients = True
      object lvAllotDev: TRzListView
        Left = 0
        Top = 33
        Width = 514
        Height = 164
        Align = alClient
        Checkboxes = True
        Columns = <
          item
            Caption = '�豸���'
            Width = 70
          end
          item
            Caption = '�豸����'
            Width = 100
          end
          item
            Caption = '�豸�ն����к�'
            Width = 100
          end
          item
            Caption = '�̻����'
            Width = 70
          end
          item
            Caption = '�̻�����'
            Width = 90
          end
          item
            Caption = '��Ʒ���'
            Width = 80
          end
          item
            Caption = '�豸�ն˺�'
            Width = 80
          end
          item
            Caption = '�豸�ͺ�'
            Width = 80
          end
          item
            Caption = '�豸����'
            Width = 80
          end
          item
            Caption = '�����̻���'
            Width = 80
          end
          item
            Caption = 'ʡ�̻���'
            Width = 80
          end
          item
            Caption = '�̻�����'
            Width = 80
          end>
        FlatScrollBars = True
        GridLines = True
        RowSelect = True
        TabOrder = 1
        ViewStyle = vsReport
      end
      object pnlAllot: TPanel
        Left = 0
        Top = 8
        Width = 514
        Height = 25
        Align = alTop
        BevelOuter = bvNone
        Caption = '�̻��ѷ����豸'
        Font.Charset = GB2312_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object lblShowAllot: TRzURLLabel
          Left = 8
          Top = 7
          Width = 84
          Height = 13
          AutoSize = False
          Caption = '��ʾ�ѷ����豸'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clHighlight
          Font.Height = -11
          Font.Name = 'Verdana'
          Font.Style = [fsUnderline]
          ParentFont = False
          OnClick = lblShowAllotClick
          Rotation = roFlat
        end
      end
    end
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 514
      Height = 85
      Align = alTop
      ParentColor = True
      TabOrder = 3
      object Label2: TLabel
        Left = 18
        Top = 10
        Width = 48
        Height = 12
        Caption = '�豸���'
      end
      object Label4: TLabel
        Left = 346
        Top = 10
        Width = 60
        Height = 12
        Caption = '�豸�ն˺�'
      end
      object Label5: TLabel
        Left = 6
        Top = 34
        Width = 60
        Height = 12
        Caption = '�ն����к�'
      end
      object Label6: TLabel
        Left = 178
        Top = 34
        Width = 48
        Height = 12
        Caption = '�豸�ͺ�'
      end
      object Label7: TLabel
        Left = 358
        Top = 34
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label8: TLabel
        Left = 178
        Top = 10
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label10: TLabel
        Left = 18
        Top = 58
        Width = 48
        Height = 12
        Caption = '�豸״̬'
      end
      object lblDev: TLabel
        Left = 181
        Top = 60
        Width = 236
        Height = 12
        AutoSize = False
        Caption = 'lblBusi'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object WVEdit4: TWVEdit
        Left = 409
        Top = 6
        Width = 106
        Height = 20
        ReadOnly = False
        TabOrder = 2
        Text = '<��ѯ.�豸�ն˺�>'
        WorkView = WorkView1
        FieldName = '��ѯ.�豸�ն˺�'
      end
      object WVEdit5: TWVEdit
        Left = 68
        Top = 30
        Width = 104
        Height = 20
        ReadOnly = False
        TabOrder = 3
        Text = '<��ѯ.�ն����к�>'
        WorkView = WorkView1
        FieldName = '��ѯ.�ն����к�'
      end
      object WVEdit8: TWVEdit
        Left = 228
        Top = 6
        Width = 116
        Height = 20
        ReadOnly = False
        TabOrder = 1
        Text = '<��ѯ.�豸����>'
        WorkView = WorkView1
        FieldName = '��ѯ.�豸����'
      end
      object WVComboBox3: TWVComboBox
        Left = 228
        Top = 30
        Width = 116
        Height = 20
        Style = csDropDownList
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView1
        FieldName = '��ѯ.�豸�ͺ�'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*223'
      end
      object WVComboBox1: TWVComboBox
        Left = 68
        Top = 54
        Width = 104
        Height = 20
        Style = csDropDownList
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView1
        FieldName = '��ѯ.�豸״̬'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*220'
      end
      object WVComboBox2: TWVComboBox
        Left = 409
        Top = 30
        Width = 106
        Height = 20
        Style = csDropDownList
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView1
        FieldName = '��ѯ.�豸����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*221'
      end
      object edtPosIdQ: TWVEdit
        Left = 68
        Top = 6
        Width = 104
        Height = 20
        ReadOnly = False
        TabOrder = 0
        Text = '<��ѯ.�豸���>'
        WorkView = WorkView1
        FieldName = '��ѯ.�豸���'
      end
      object btnDevQ: TBitBtn
        Left = 436
        Top = 54
        Width = 79
        Height = 25
        Hint = '����'
        Caption = '�豸��ѯ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 7
        OnClick = btnDevQClick
      end
    end
  end
  object RzSizePanel1: TRzSizePanel [3]
    Left = 0
    Top = 18
    Width = 524
    Height = 438
    HotSpotVisible = True
    SizeBarWidth = 7
    TabOrder = 0
    UseGradients = True
    object Panel2: TPanel
      Left = 0
      Top = 0
      Width = 516
      Height = 87
      Align = alTop
      ParentColor = True
      TabOrder = 0
      object Label3: TLabel
        Left = 22
        Top = 10
        Width = 84
        Height = 12
        Caption = '�豸�ն����к�'
      end
      object Label1: TLabel
        Left = 10
        Top = 34
        Width = 96
        Height = 12
        Caption = 'ʡ�豸�ն����к�'
      end
      object Label9: TLabel
        Left = 282
        Top = 10
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label11: TLabel
        Left = 306
        Top = 34
        Width = 24
        Height = 12
        Caption = '״̬'
      end
      object btnBusiQ: TBitBtn
        Left = 401
        Top = 54
        Width = 79
        Height = 25
        Hint = '����'
        Caption = '�̻���ѯ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnBusiQClick
      end
      object WVEdit1: TWVEdit
        Left = 116
        Top = 30
        Width = 133
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 1
        Text = '<��ѯ.ʡ�豸�ն����к�>'
        WorkView = WorkView3
        FieldName = '��ѯ.ʡ�豸�ն����к�'
      end
      object WVEdit3: TWVEdit
        Left = 116
        Top = 6
        Width = 133
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 2
        Text = '<��ѯ.�豸�ն����к�>'
        WorkView = WorkView3
        FieldName = '��ѯ.�豸�ն����к�'
      end
      object WVComboBox4: TWVComboBox
        Left = 340
        Top = 27
        Width = 141
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView3
        FieldName = '��ѯ.״̬'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*239'
      end
      object WVComboBox5: TWVComboBox
        Left = 340
        Top = 3
        Width = 141
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView3
        FieldName = '��ѯ.�豸����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*221'
      end
    end
    object lvBusi: TRzListView
      Left = 0
      Top = 87
      Width = 516
      Height = 351
      Align = alClient
      Columns = <
        item
          Caption = '�̻����'
          Width = 70
        end
        item
          Caption = '�̻�����'
          Width = 120
        end
        item
          Caption = '�豸�ն����к�'
          Width = 100
        end
        item
          Caption = '�豸����'
          Width = 100
        end
        item
          Caption = '״̬'
          Width = 100
        end
        item
          Caption = '���豸���'
          Width = 5
        end>
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
      OnClick = lvBusiClick
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
        Name = '�̻���'
        Caption = '�̻���'
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
        Name = '�豸���'
        Caption = '�豸���'
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
        Name = '���к�'
        Caption = '���к�'
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
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 76
    Top = 295
  end
  inherited MainRequest: TWVRequest
    ID = '�豸�̻���'
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
        ParamName = '�̻����'
        FieldName = '�̻���'
        DefaultValue = 0
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���к�'
        FieldName = '���к�'
      end>
    Left = 112
    Top = 296
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = nil
    FieldName = '��ѯ�����'
    Left = 144
    Top = 336
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 336
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'POS��Ϣά����ѯ'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�豸���'
        FieldName = '��ѯ.�豸���'
      end
      item
        ParamName = '�����̻���'
        FieldName = '��ѯ.�����̻���'
      end
      item
        ParamName = '�豸�ն˺�'
        FieldName = '��ѯ.�豸�ն˺�'
      end
      item
        ParamName = '�ն����к�'
        FieldName = '��ѯ.�ն����к�'
      end
      item
        ParamName = '�豸�ͺ�'
        FieldName = '��ѯ.�豸�ͺ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '��;'
        FieldName = '��ѯ.��;'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '��ѯ.�豸״̬'
      end>
    Left = 112
    Top = 376
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
        Name = '��ѯ.�豸���'
        Caption = '��ѯ.�豸���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
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
        Name = '��ѯ.�����̻���'
        Caption = '��ѯ.�����̻���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
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
        Name = '��ѯ.�豸�ն˺�'
        Caption = '��ѯ.�豸�ն˺�'
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
        Name = '��ѯ.�ն����к�'
        Caption = '��ѯ.�ն����к�'
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
        Name = '��ѯ.�豸�ͺ�'
        Caption = '��ѯ.�豸�ͺ�'
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
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
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
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
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
        Name = '��ѯ.��;'
        Caption = '��ѯ.��;'
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
        Name = '��ѯ.�豸״̬'
        Caption = '��ѯ.�豸״̬'
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
        Name = '������־'
        Caption = '������־'
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
        DataField = 'sstat_type'
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    InvalidColor = clWindow
    Left = 80
    Top = 376
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
        Name = '�̻���'
        Caption = '�̻���'
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
        Name = '�豸���'
        Caption = '�豸���'
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
        MonitorValueChangedFields = 
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 76
    Top = 407
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�豸�̻���ѯ'
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
        ParamName = '�̻����'
        FieldName = '�̻���'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end>
    AfterExec = MainRequestAfterExec
    Left = 112
    Top = 408
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView3
    ID = '�̻��豸�����ѯ'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�̻���'
        FieldName = '��ѯ.�̻���'
        DefaultValue = 0
      end
      item
        ParamName = '�豸�ն����к�'
        FieldName = '��ѯ.�豸�ն����к�'
      end
      item
        ParamName = 'ʡ�豸�ն����к�'
        FieldName = '��ѯ.ʡ�豸�ն����к�'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end
      item
        ParamName = 'ע������'
        FieldName = '��ѯ.ע������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = 'ͣ������'
        FieldName = '��ѯ.ͣ������'
      end>
    Left = 112
    Top = 336
  end
  object WorkView3: TWorkView
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
        Name = '������־'
        Caption = '������־'
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
        Name = '��ѯ.�̻���'
        Caption = '��ѯ.�̻���'
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
        Name = '��ѯ.�豸�ն����к�'
        Caption = '��ѯ.�豸�ն����к�'
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
        Name = '��ѯ.ʡ�豸�ն����к�'
        Caption = '��ѯ.ʡ�豸�ն����к�'
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
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
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
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
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
        Name = '��ѯ.ע������'
        Caption = '��ѯ.ע������'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.ͣ������'
        Caption = '��ѯ.ͣ������'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�̻���|��ѯ.�豸�ն����к�|��ѯ.ʡ�豸�ն���' +
          '�к�|��ѯ.�豸����|��ѯ.״̬|��ѯ.ע������|��ѯ.��������|��ѯ.ͣ' +
          '������|'
      end
      item
        MonitorValueChangedFields = 
          '|�̻���|�̻�����|�豸�ն����к�|�|�豸����|״̬|ע������|������' +
          '��|ͣ������|���豸���|��ע|'
      end>
    InvalidColor = clBtnHighlight
    Left = 72
    Top = 336
  end
end
