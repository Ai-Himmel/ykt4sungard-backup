inherited faqhCardLibDestory: TfaqhCardLibDestory
  Width = 779
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 405
    Width = 779
    Height = 84
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 602
      Top = 35
      Width = 81
      Enabled = False
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 689
      Top = 35
      Width = 81
      TabOrder = 2
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 569
      Height = 65
      Align = alLeft
      Caption = '��������Ϣ'
      TabOrder = 0
      object Label2: TLabel
        Left = 16
        Top = 18
        Width = 58
        Height = 13
        AutoSize = False
        Caption = '�� �� ��'
      end
      object lblTransTo: TLabel
        Left = 210
        Top = 42
        Width = 38
        Height = 13
        AutoSize = False
        Caption = '����Ա'
      end
      object lblBNo: TLabel
        Left = 16
        Top = 41
        Width = 58
        Height = 13
        AutoSize = False
        Caption = '��Ƭ���'
      end
      object cbbCardType: TWVComboBox
        Left = 72
        Top = 13
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 0
        WorkView = WVCardDestory
        FieldName = '������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-56'
      end
      object cbbOperTrans: TWVComboBox
        Left = 253
        Top = 37
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 6
        WorkView = WVCardDestory
        FieldName = 'ת�����Ա'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-30'
      end
      object edtBNo: TEdit
        Left = 72
        Top = 37
        Width = 105
        Height = 20
        MaxLength = 10
        TabOrder = 5
      end
      object chkReadCard: TCheckBox
        Left = 210
        Top = 14
        Width = 73
        Height = 17
        Caption = '��������'
        TabOrder = 1
      end
      object chkInfo: TCheckBox
        Left = 296
        Top = 14
        Width = 73
        Height = 17
        Caption = '��ʾ��Ϣ'
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
      object btnDestory: TBitBtn
        Left = 366
        Top = 34
        Width = 83
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '��Ƭ����(&D)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnDestoryClick
      end
      object btnCelDestory: TBitBtn
        Left = 462
        Top = 34
        Width = 83
        Height = 25
        Anchors = [akTop, akRight]
        Caption = 'ȡ������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = btnCelDestoryClick
      end
    end
    object RzStatusBar1: TRzStatusBar
      Left = 0
      Top = 65
      Width = 779
      Height = 19
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      TabOrder = 3
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 725
        Height = 19
        Align = alLeft
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 779
    inherited Image1: TImage
      Width = 779
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 779
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 54
      Top = 9
      Width = 36
      Height = 12
      Caption = '������'
    end
    object lbl1: TLabel
      Left = 30
      Top = 33
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object Label7: TLabel
      Left = 238
      Top = 33
      Width = 60
      Height = 12
      Caption = 'ת������Ա'
    end
    object Label5: TLabel
      Left = 262
      Top = 9
      Width = 36
      Height = 12
      Caption = '����Ա'
    end
    object Label6: TLabel
      Left = 470
      Top = 33
      Width = 24
      Height = 12
      Caption = '״̬'
    end
    object Label4: TLabel
      Left = 446
      Top = 9
      Width = 48
      Height = 12
      Caption = '��ʾ����'
    end
    object WVComboBox3: TWVComboBox
      Left = 96
      Top = 4
      Width = 131
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-56'
    end
    object edtPatchNo: TWVEdit
      Left = 96
      Top = 28
      Width = 131
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<�������κ�>'
      WorkView = WorkView
      FieldName = '�������κ�'
    end
    object WVComboBox4: TWVComboBox
      Left = 304
      Top = 28
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 4
      WorkView = WorkView
      FieldName = 'ת������Ա'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox1: TWVComboBox
      Left = 304
      Top = 4
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 1
      WorkView = WorkView
      FieldName = 'ת�����Ա'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox2: TWVComboBox
      Left = 504
      Top = 28
      Width = 123
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 5
      WorkView = WorkView
      FieldName = '״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*127'
    end
    object edtShowCardNo: TWVEdit
      Left = 504
      Top = 4
      Width = 123
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<��ʾ����>'
      WorkView = WorkView
      FieldName = '��ʾ����'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 779
    Height = 332
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 779
      Height = 332
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʾ����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա'
          Width = 70
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
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʹ������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '״̬'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ת������Ա'
          Width = 70
          Visible = True
        end>
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
        GetPrevChar = '*'
      end
      item
        Name = 'ת�����Ա'
        Caption = 'ת�����Ա'
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
        Name = '״̬'
        Caption = '״̬'
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
        Name = 'ת������Ա'
        Caption = 'ת������Ա'
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
        MonitorValueChangedFields = '|������|��ʼ���|��ֹ���|����Ա��|ת�����Ա|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 412
    Top = 143
  end
  inherited MainRequest: TWVRequest
    ID = '��Ƭ��Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = 'ת�����Ա'
        FieldName = 'ת�����Ա'
      end
      item
        ParamName = '��ʾ����'
        FieldName = '��ʾ����'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = 'ת������Ա'
        FieldName = 'ת������Ա'
      end>
    Left = 448
    Top = 144
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'semp'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lvol0'
        DataPresentType = 'idobjects'
        DataPresentParam = '-56'
      end
      item
        FieldName = 'semp_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '127'
      end>
    Left = 480
    Top = 144
  end
  inherited DataSource: TDataSource
    Left = 520
    Top = 144
  end
  object WVCardDestory: TWorkView
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
        Name = '������'
        Caption = '������'
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
        Name = '��ʼ���'
        Caption = '��ʼ���'
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
        Name = 'ת�����Ա'
        Caption = 'ת�����Ա'
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
        Name = '���ϱ�־'
        Caption = '���ϱ�־'
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
        MonitorValueChangedFields = '|������|��ʼ���|��ֹ���|����Ա��|ת�����Ա|'
      end>
    Left = 412
    Top = 183
  end
  object WVRCardDestory: TWVRequest
    WorkView = WVCardDestory
    ID = '��Ƭ����'
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
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��ʼ���'
        FieldName = '��ʼ���'
      end
      item
        ParamName = 'ת�����Ա'
        FieldName = 'ת�����Ա'
      end
      item
        ParamName = '���ϱ�־'
        FieldName = '���ϱ�־'
      end>
    AfterExec = MainRequestAfterExec
    Left = 448
    Top = 184
  end
end
