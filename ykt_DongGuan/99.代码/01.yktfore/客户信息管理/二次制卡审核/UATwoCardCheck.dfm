inherited faqhTwoCardCheck: TfaqhTwoCardCheck
  Width = 674
  Height = 427
  inherited UIPanel1: TUIPanel
    Top = 359
    Width = 674
    Height = 68
    inherited btnQuery: TBitBtn
      Left = 409
      Top = 5
    end
    inherited btnPrint: TBitBtn
      Left = 584
      Top = 5
      Caption = '����Excel'
      Enabled = True
      Glyph.Data = {00000000}
    end
    object btnCheck: TBitBtn
      Left = 497
      Top = 5
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '���ͨ��'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnCheckClick
    end
    object chkSelect: TCheckBox
      Left = 8
      Top = 8
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 3
      OnClick = chkSelectClick
    end
    object btnClear: TBitBtn
      Left = 233
      Top = 5
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '����б�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnClearClick
    end
    object stat1: TStatusBar
      Left = 0
      Top = 45
      Width = 674
      Height = 23
      Panels = <
        item
          Width = 1000
        end>
      SimplePanel = False
    end
    object pbStatues: TProgressBar
      Left = 0
      Top = 35
      Width = 674
      Height = 10
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 6
    end
    object btnReadCardQ: TBitBtn
      Left = 321
      Top = 5
      Width = 79
      Height = 25
      Hint = '������ѯ����'
      Anchors = [akTop, akRight]
      Caption = '������ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
      OnClick = btnReadCardQClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 674
    inherited Image1: TImage
      Width = 674
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 674
    Height = 63
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label4: TLabel
      Left = 18
      Top = 18
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label9: TLabel
      Left = 412
      Top = 18
      Width = 60
      Height = 12
      Caption = '�ƿ����κ�'
    end
    object Label10: TLabel
      Left = 238
      Top = 18
      Width = 36
      Height = 12
      Caption = '�����'
    end
    object Label11: TLabel
      Left = 6
      Top = 42
      Width = 60
      Height = 12
      Caption = 'Ӧ�����к�'
    end
    object Label6: TLabel
      Left = 226
      Top = 42
      Width = 48
      Height = 12
      Caption = '������'
    end
    object Label1: TLabel
      Left = 448
      Top = 42
      Width = 24
      Height = 12
      Caption = '����'
    end
    object cbbDept: TWVComboBox
      Left = 73
      Top = 14
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView1
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*210'
    end
    object edtBeginDate: TWVEdit
      Left = 476
      Top = 14
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<���κ�>'
      WorkView = WorkView1
      FieldName = '���κ�'
    end
    object cbbIDType: TWVComboBox
      Left = 281
      Top = 14
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView1
      FieldName = '�������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-1'
    end
    object edtAppNo: TWVEdit
      Left = 73
      Top = 38
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<���к�>'
      WorkView = WorkView1
      FieldName = '���к�'
    end
    object WVEdit1: TWVEdit
      Left = 281
      Top = 38
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<������>'
      WorkView = WorkView1
      FieldName = '������'
    end
    object edtCardNo: TWVEdit
      Left = 476
      Top = 38
      Width = 120
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
      Text = '<����>'
      WorkView = WorkView1
      FieldName = '����'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 81
    Width = 674
    Height = 278
    inherited Grid: TRzDBGrid
      Width = 674
      Height = 278
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������Ч����(��)'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ԥ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�绰'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֻ�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��λ����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ļ��̶�'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ò'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������Դ'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ʩ'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snation_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_addr'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������ڵ�����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������ڵ�'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס��ַ'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�״ε��ﱾ������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ƿ�ɾ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ɾ������'
          Width = 60
          Visible = True
        end>
    end
    object lvInfo: TRzListView
      Left = 0
      Top = 0
      Width = 674
      Height = 278
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '��������'
          Width = 120
        end
        item
          Alignment = taCenter
          Caption = '����'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = 'Ӧ�����к�'
          Width = 120
        end
        item
          Alignment = taCenter
          Caption = '������'
          Width = 80
        end
        item
          Alignment = taCenter
          Caption = '�����'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = '����'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = '�״��ƿ����κ�'
          Width = 154
        end
        item
          Caption = '��ID'
          Width = 11
        end>
      FlatScrollBars = True
      FrameVisible = True
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
        Name = '�����'
        Caption = '�����'
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
        Name = '���κ�'
        Caption = '���κ�'
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
        Name = '˳���'
        Caption = '˳���'
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
        Name = '������־'
        Caption = '������־'
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
        MonitorValueChangedFields = '|������־|�ͻ���|Ԥ����|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�������'
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
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '˳���'
        FieldName = '˳���'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = WorkView1
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sroom_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '201'
      end
      item
        FieldName = 'sstatus0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '200'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '202'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '203'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '204'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '205'
      end
      item
        FieldName = 'sstatus4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '206'
      end
      item
        FieldName = 'sserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '207'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '208'
      end
      item
        FieldName = 'sserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '209'
      end
      item
        FieldName = 'sserial2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '211'
      end
      item
        FieldName = 'sserial3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '212'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '213'
      end
      item
        FieldName = 'sroom_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '210'
      end>
    Left = 240
    Top = 280
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 280
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '�����ƿ���ѯ'
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
        ParamName = '���κ�'
        FieldName = '���κ�'
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
        ParamName = '���к�'
        FieldName = '���к�'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 208
    Top = 280
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
        Name = '���κ�'
        Caption = '���κ�'
        FieldType = wftUndefined
        DataType = kdtString
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
        Name = '���к�'
        Caption = '���к�'
        FieldType = wftUndefined
        DataType = kdtString
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
        Name = '������'
        Caption = '������'
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
      end
      item
        Name = '�������'
        Caption = '�������'
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
        Name = '����'
        Caption = '����'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 168
    Top = 280
  end
  object dlgSave1: TSaveDialog
    Title = '���ʧ����Ϣ'
    Left = 216
    Top = 313
  end
end
