inherited faqhDevBusiAllot: TfaqhDevBusiAllot
  Width = 847
  Height = 489
  inherited UIPnlQueryCount: TUIPanel [0]
    Width = 847
    TabOrder = 2
    inherited Image1: TImage
      Width = 847
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
    end
  end
  inherited UIPanel1: TUIPanel [1]
    Top = 424
    Width = 847
    Height = 65
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 494
      Top = 35
      Caption = '�豸��ѯ'
      Enabled = False
      TabOrder = 1
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 285
      Top = 200
      TabOrder = 5
    end
    object btnAdd: TBitBtn
      Left = 582
      Top = 35
      Width = 79
      Height = 25
      Hint = '����'
      Anchors = [akTop, akRight]
      Caption = '��  ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnAddClick
    end
    object btnDel: TBitBtn
      Left = 758
      Top = 35
      Width = 79
      Height = 25
      Hint = 'ɾ��'
      Anchors = [akTop, akRight]
      Caption = 'ɾ  ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnDelClick
    end
    object btnChange: TBitBtn
      Left = 670
      Top = 35
      Width = 79
      Height = 25
      Hint = '�޸�'
      Anchors = [akTop, akRight]
      Caption = '��  ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnChangeClick
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 385
      Height = 65
      Align = alLeft
      TabOrder = 0
      object lblBusiName: TLabel
        Left = 12
        Top = 18
        Width = 189
        Height = 14
        AutoSize = False
        Caption = '�̻�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label12: TLabel
        Left = 12
        Top = 42
        Width = 72
        Height = 12
        Caption = '�豸��������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel
        Left = 204
        Top = 43
        Width = 72
        Height = 12
        Caption = '�豸ͣ������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel
        Left = 204
        Top = 20
        Width = 72
        Height = 12
        Caption = 'ʹ�ý���ʱ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtStartDate: TWVEdit
        Left = 92
        Top = 38
        Width = 85
        Height = 20
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        MaxLength = 8
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
        Text = '<��������>'
        WorkView = WorkView1
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object edtEndTime: TWVEdit
        Left = 284
        Top = 13
        Width = 85
        Height = 20
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        MaxLength = 6
        ParentFont = False
        ReadOnly = False
        TabOrder = 0
        Text = '<ʹ�ý���ʱ��>'
        WorkView = WorkView1
        FieldName = 'ʹ�ý���ʱ��'
        SynchronizeWhenExit = True
      end
      object edtStopDate: TWVEdit
        Left = 284
        Top = 38
        Width = 85
        Height = 20
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        MaxLength = 8
        ParentFont = False
        ReadOnly = False
        TabOrder = 2
        Text = '<ͣ������>'
        WorkView = WorkView1
        FieldName = 'ͣ������'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 267
    Width = 580
    Height = 406
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Left = 96
      Top = 240
      Width = 270
      Height = 142
      Align = alNone
      DataSource = nil
      TabOrder = 3
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
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 580
      Height = 108
      Align = alTop
      BevelOuter = bvNone
      Color = 16119543
      TabOrder = 0
      object Label1: TLabel
        Left = 18
        Top = 9
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label3: TLabel
        Left = 376
        Top = 9
        Width = 60
        Height = 12
        Caption = '�豸����ID'
      end
      object Label4: TLabel
        Left = 42
        Top = 35
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label5: TLabel
        Left = 194
        Top = 11
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label6: TLabel
        Left = 352
        Top = 35
        Width = 84
        Height = 12
        Caption = '�ϼ��豸����ID'
      end
      object Label8: TLabel
        Left = 194
        Top = 35
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label9: TLabel
        Left = 6
        Top = 62
        Width = 60
        Height = 12
        Caption = '������ϵͳ'
      end
      object Label10: TLabel
        Left = 194
        Top = 61
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label2: TLabel
        Left = 376
        Top = 61
        Width = 60
        Height = 12
        Caption = '�������κ�'
      end
      object Label13: TLabel
        Left = 18
        Top = 87
        Width = 48
        Height = 12
        Caption = '�豸��ʶ'
      end
      object WVEdit1: TWVEdit
        Left = 68
        Top = 5
        Width = 112
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<�豸����>'
        WorkView = WorkView
        FieldName = '�豸����'
      end
      object WVEdit3: TWVEdit
        Left = 444
        Top = 5
        Width = 100
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<�豸����ID>'
        WorkView = WorkView
        FieldName = '�豸����ID'
      end
      object WVEdit6: TWVEdit
        Left = 444
        Top = 31
        Width = 100
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<�ϼ��豸����ID>'
        WorkView = WorkView
        FieldName = '�ϼ��豸����ID'
      end
      object WVComboBox2: TWVComboBox
        Left = 244
        Top = 57
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '�豸��������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-28'
      end
      object WVComboBox3: TWVComboBox
        Left = 68
        Top = 58
        Width = 112
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '������ϵͳ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-32'
      end
      object WVComboBox5: TWVComboBox
        Left = 244
        Top = 31
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '�豸�����ͺ�'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-35'
      end
      object WVComboBox6: TWVComboBox
        Left = 244
        Top = 5
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '���ʹ���'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*47'
      end
      object edtMachineNo: TWVEdit
        Left = 68
        Top = 32
        Width = 112
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 5
        Text = '<����>'
        WorkView = WorkView
        FieldName = '����'
      end
      object WVEdit2: TWVEdit
        Left = 444
        Top = 57
        Width = 100
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 7
        Text = '<�������κ�>'
        WorkView = WorkView
        FieldName = '�������κ�'
      end
      object WVEdit4: TWVEdit
        Left = 68
        Top = 84
        Width = 112
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 9
        Text = '<�豸��ʶ>'
        WorkView = WorkView
        FieldName = '�豸��ʶ'
      end
    end
    object lvDev: TRzListView
      Left = 0
      Top = 108
      Width = 580
      Height = 101
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '��������'
          Width = 100
        end
        item
          Caption = '�豸��ʶ'
          Width = 70
        end
        item
          Caption = '�豸����'
          Width = 120
        end
        item
          Caption = '�豸����ID'
          Width = 80
        end
        item
          Caption = '���ʹ���'
          Width = 100
        end
        item
          Caption = '������ϵͳ'
          Width = 100
        end
        item
          Caption = '�豸��;'
          Width = 23
        end>
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
    end
    object rzszpnl1: TRzSizePanel
      Left = 0
      Top = 209
      Width = 580
      Height = 197
      Align = alBottom
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 2
      UseGradients = True
      object lvAllotDev: TRzListView
        Left = 0
        Top = 33
        Width = 580
        Height = 164
        Align = alClient
        Checkboxes = True
        Columns = <
          item
            Width = 25
          end
          item
            Caption = '���'
            Width = 70
          end
          item
            Caption = '�豸����'
            Width = 120
          end
          item
            Caption = '�̻�����'
            Width = 100
          end
          item
            Caption = 'ʹ�ÿ�ʼʱ��'
            Width = 100
          end
          item
            Caption = 'ʹ�ý���ʱ��'
            Width = 100
          end
          item
            Caption = '�豸��������'
            Width = 100
          end
          item
            Caption = '�豸ͣ������'
            Width = 100
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
        Width = 580
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
  end
  object RzSizePanel1: TRzSizePanel [3]
    Left = 0
    Top = 18
    Width = 267
    Height = 406
    HotSpotVisible = True
    SizeBarWidth = 7
    TabOrder = 0
    UseGradients = True
    object tvBusiness: TRzTreeView
      Left = 0
      Top = 0
      Width = 259
      Height = 406
      SelectionPen.Color = clBtnShadow
      Align = alClient
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      Indent = 19
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      OnClick = tvBusinessClick
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
        Name = '�豸����'
        Caption = '�豸����'
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
        DataField = 'scert_no'
      end
      item
        Name = '�����豸ע���'
        Caption = '�����豸ע���'
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
        DataField = 'sbank_pwd'
      end
      item
        Name = '�豸����ID'
        Caption = '�豸����ID'
        FieldType = wftUndefined
        Features.Strings = ()
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
        GroupIndex = 1
        DataField = 'lvol1'
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
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '�ϼ��豸����ID'
        Caption = '�ϼ��豸����ID'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
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
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
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
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�豸�ǹؼ��ֲ�ѯ'
    Bindings = <
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
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
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
    Left = 208
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
        Name = '���'
        Caption = '���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = 'ʹ�ý���ʱ��'
        Caption = 'ʹ�ý���ʱ��'
        FieldType = wftUndefined
        DomainName = 'ʱ���ʽ'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'stime2'
      end
      item
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = 'ͣ������'
        Caption = 'ͣ������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate2'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�豸�̻���ʶ|'
      end
      item
        MonitorValueChangedFields = 
          '|���|ǰ�˻���ʶ|�̻���ʶ|ʹ�ÿ�ʼ����|ʹ�ÿ�ʼʱ��|ʹ�ý���ʱ��' +
          '|ʹ�ý�������|'
      end>
    Left = 80
    Top = 296
  end
  object AddRequest: TWVRequest
    WorkView = WorkView1
    ID = '�豸�̻���Ϣ����'
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
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ͣ������'
        FieldName = 'ͣ������'
      end>
    Left = 112
    Top = 296
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�̻���Ϣ������ѯ2'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end>
    Left = 112
    Top = 336
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
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�̻���ʶ|'
      end>
    Left = 76
    Top = 335
  end
  object WorkView3: TWorkView
    WorkFields = <
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
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
        FieldType = wftUndefined
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
        Name = 'ʹ�ÿ�ʼ����'
        Caption = 'ʹ�ÿ�ʼ����'
        FieldType = wftUndefined
        DomainName = '����У��'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = 'ʹ�ý�������'
        Caption = 'ʹ�ý�������'
        FieldType = wftUndefined
        DomainName = '����У��'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�̻�����'
        Caption = '�̻�����'
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
        Name = 'ʹ��״̬'
        Caption = 'ʹ��״̬'
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
        Name = 'ʹ�ý���ʱ��'
        Caption = 'ʹ�ý���ʱ��'
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
        Name = '�̻����'
        Caption = '�̻����'
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
        MonitorValueChangedFields = '|'
      end>
    Left = 84
    Top = 207
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView3
    ID = '�豸�̻���Ϣ��������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʹ�ÿ�ʼ����'
        FieldName = 'ʹ�ÿ�ʼ����'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = 'ʹ�ý�������'
        FieldName = 'ʹ�ý�������'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'ʹ��״̬'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end>
    AfterExec = MainRequestAfterExec
    Left = 120
    Top = 208
  end
end
