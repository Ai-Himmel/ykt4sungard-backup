inherited faqhphoneTransferDeal: TfaqhphoneTransferDeal
  Width = 753
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 448
    Width = 753
    Height = 41
    TabOrder = 4
    inherited btnQuery: TBitBtn
      Left = 488
      Top = 8
      Enabled = False
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 575
      Top = 8
      TabOrder = 2
    end
    object chkSelectAll: TCheckBox
      Left = 16
      Top = 13
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 4
      OnClick = chkSelectAllClick
    end
    object btnDeal: TImageButton
      Left = 664
      Top = 8
      Width = 75
      Height = 25
      Hint = '���˴���'
      Anchors = [akTop, akRight]
      Caption = '���˴���'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnDealClick
    end
    object GroupBox1: TGroupBox
      Left = 96
      Top = -3
      Width = 305
      Height = 41
      TabOrder = 0
      object Label8: TLabel
        Left = 10
        Top = 18
        Width = 84
        Height = 12
        Caption = '�ֹ��������ڣ�'
      end
      object dtpDate: TDateTimePicker
        Left = 96
        Top = 13
        Width = 105
        Height = 20
        CalAlignment = dtaLeft
        Date = 39373.412233588
        Time = 39373.412233588
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkDate
        ParseInput = False
        TabOrder = 1
      end
      object btnTrans: TImageButton
        Left = 208
        Top = 11
        Width = 75
        Height = 25
        Hint = '�ֹ�����'
        Anchors = [akTop, akRight]
        Caption = '�ֹ�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnTransClick
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 753
    inherited Image1: TImage
      Width = 753
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 753
    Height = 54
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 42
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label2: TLabel
      Left = 222
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label3: TLabel
      Left = 418
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label4: TLabel
      Left = 42
      Top = 33
      Width = 48
      Height = 12
      Caption = '�ֻ�����'
    end
    object Label5: TLabel
      Left = 234
      Top = 33
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label6: TLabel
      Left = 394
      Top = 33
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object Label7: TLabel
      Left = 570
      Top = 33
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object edtCustNo: TWVEdit
      Left = 268
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object edtCardNo: TWVEdit
      Left = 452
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 2
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 5
      Text = '<�ֻ�����>'
      WorkView = WorkView
      FieldName = '�ֻ�����'
    end
    object WVEdit5: TWVEdit
      Left = 268
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 6
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object cbbCustType: TWVComboBox
      Left = 452
      Top = 28
      Width = 102
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '�Ϲ�ƴ�����뷨'
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '����״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*93'
    end
    object WVComboBox1: TWVComboBox
      Left = 629
      Top = 28
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '�Ϲ�ƴ�����뷨'
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '����״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*94'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 72
    Width = 753
    Height = 376
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 753
      Height = 376
      Columns = <
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ˮ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׽��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֻ�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������Ա'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 80
          Visible = True
        end>
    end
  end
  object lvSerial: TRzListView [4]
    Left = 0
    Top = 72
    Width = 753
    Height = 376
    Align = alClient
    Checkboxes = True
    Columns = <
      item
        Caption = '��ˮ��'
        Width = 80
      end
      item
        Caption = '�ͻ���'
        Width = 80
      end
      item
        Caption = '����'
        Width = 80
      end
      item
        Caption = '�ͻ�����'
        Width = 80
      end
      item
        Caption = '��������'
        Width = 80
      end
      item
        Caption = '����ʱ��'
        Width = 80
      end
      item
        Caption = '���׽��'
        Width = 80
      end
      item
        Caption = '�ֻ�����'
        Width = 100
      end
      item
        Caption = '����״̬'
        Width = 80
      end
      item
        Caption = '����״̬'
        Width = 80
      end
      item
        Caption = '�������Ա'
        Width = 100
      end
      item
        Caption = '��������'
        Width = 80
      end
      item
        Caption = '����ʱ��'
        Width = 80
      end>
    ColumnClick = False
    FlatScrollBars = True
    GridLines = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
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
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        DomainName = '����У��'
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
      end
      item
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
      end
      item
        Name = '����'
        Caption = '����'
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
      end
      item
        Name = '�ֻ�����'
        Caption = '�ֻ�����'
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
      end
      item
        Name = '����'
        Caption = '����'
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
      end
      item
        Name = '����״̬'
        Caption = '����״̬'
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
      end
      item
        Name = '����״̬'
        Caption = '����״̬'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�ֻ�����|����|����״̬|����״̬|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�ƶ���ֵ���˲�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�ֻ�����'
        FieldName = '�ֻ�����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '93'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'idobjects'
        DataPresentParam = '94'
      end>
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 224
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        Name = '������ˮ��'
        Caption = '������ˮ��'
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
        Name = '����'
        Caption = '����'
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
        Name = '����Ա'
        Caption = '����Ա'
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
        MonitorValueChangedFields = '|'
      end>
    Left = 164
    Top = 103
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�ƶ���ֵ���˴���'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������ˮ��'
        FieldName = '������ˮ��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 104
  end
  object WorkView2: TWorkView
    WorkFields = <
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
        MonitorValueChangedFields = '|'
      end>
    Left = 164
    Top = 143
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�ֹ�����'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 144
  end
end
