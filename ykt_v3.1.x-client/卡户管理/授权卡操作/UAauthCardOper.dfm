inherited faqhauthCardOper: TfaqhauthCardOper
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 437
    Width = 700
    Height = 52
    TabOrder = 3
    object Label6: TLabel [0]
      Left = 114
      Top = 10
      Width = 84
      Height = 12
      Caption = '��Ҳ���Ա����'
    end
    inherited btnQuery: TBitBtn
      Left = 347
      Top = 2
      Width = 82
    end
    inherited btnPrint: TBitBtn
      Left = 482
      TabOrder = 4
      Visible = False
    end
    object cbxNoCard: TRzCheckBox
      Left = 16
      Top = 9
      Width = 73
      Height = 17
      Caption = '�޿�����'
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 6
    end
    object btnLose: TBitBtn
      Left = 435
      Top = 2
      Width = 82
      Height = 25
      Hint = '��ʧ��Ȩ��'
      Anchors = [akTop, akRight]
      Caption = '��ʧ��Ȩ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnLoseClick
    end
    object btnRLose: TBitBtn
      Left = 523
      Top = 2
      Width = 82
      Height = 25
      Hint = '��ʧ��Ȩ��'
      Anchors = [akTop, akRight]
      Caption = '�����Ȩ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnRLoseClick
    end
    object btnReturn: TBitBtn
      Left = 611
      Top = 2
      Width = 82
      Height = 25
      Hint = '��ʧ��Ȩ��'
      Anchors = [akTop, akRight]
      Caption = '&R ����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnReturnClick
    end
    object WVEdit2: TWVEdit
      Left = 204
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      PasswordChar = '*'
      ReadOnly = False
      TabOrder = 5
      Text = '<����Ա����>'
      WorkView = WorkView3
      FieldName = '����Ա����'
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 31
      Width = 700
      Height = 21
      AutoStyle = False
      BorderColor = clWindow
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      Color = 16184303
      FlatColor = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 700
        Height = 21
        FrameStyle = fsStatus
        Align = alClient
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 18
      Top = 9
      Width = 48
      Height = 12
      Caption = '���׿���'
    end
    object Label2: TLabel
      Left = 182
      Top = 9
      Width = 60
      Height = 12
      Caption = '����Ա����'
    end
    object Label3: TLabel
      Left = 386
      Top = 9
      Width = 48
      Height = 12
      Caption = '������'
    end
    object Label4: TLabel
      Left = 562
      Top = 9
      Width = 24
      Height = 12
      Caption = '״̬'
    end
    object WVEdit1: TWVEdit
      Left = 68
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<���׿���>'
      WorkView = WorkView
      FieldName = '���׿���'
    end
    object WVEdit3: TWVEdit
      Left = 444
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<������>'
      WorkView = WorkView
      FieldName = '������'
    end
    object WVComboBox3: TWVComboBox
      Left = 248
      Top = 5
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '����Ա����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox1: TWVComboBox
      Left = 592
      Top = 4
      Width = 97
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*83'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 48
    Width = 700
    Height = 389
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 389
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׿���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ч��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��״̬'
          Width = 60
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
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʧ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ע������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Caption = '����ʱ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Caption = '��Ȩ��'
          Width = 400
          Visible = True
        end>
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '����Ա����'
        Caption = '����Ա����'
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
      end
      item
        Name = '״̬'
        Caption = '״̬'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|���׿���|����Ա����|������|״̬|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '��Ȩ������'
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
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sserial0'
        DataPresentType = 'idobjects'
        DataPresentParam = '83'
      end>
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
  object WorkView1: TWorkView
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '����Ա����'
        Caption = '����Ա����'
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
        Name = '�޿�����'
        Caption = '�޿�����'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|���׿���|����Ա����|������|״̬|'
      end>
    Left = 164
    Top = 271
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '��Ȩ������'
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
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�޿�����'
        FieldName = '�޿�����'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 272
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '��Ȩ����ʧ'
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
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = 'ҵ�����Ա��'
        FieldName = 'ҵ�����Ա��'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 312
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '����Ա����'
        Caption = '����Ա����'
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
        Name = 'ҵ�����Ա��'
        Caption = 'ҵ�����Ա��'
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
        MonitorValueChangedFields = '|���׿���|����Ա����|������|״̬|'
      end>
    Left = 164
    Top = 311
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
      end
      item
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '����Ա����'
        Caption = '����Ա����'
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
        Name = 'ҵ�����Ա��'
        Caption = 'ҵ�����Ա��'
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
        Name = '�������汾'
        Caption = '�������汾'
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
        MonitorValueChangedFields = '|���׿���|����Ա����|������|״̬|'
      end>
    Left = 164
    Top = 351
  end
  object WVRequest3: TWVRequest
    WorkView = WorkView3
    ID = '��Ȩ�����'
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
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = 'ҵ�����Ա��'
        FieldName = 'ҵ�����Ա��'
      end
      item
        ParamName = '�������汾'
        FieldName = '�������汾'
        Direction = bdParam2Field
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 352
  end
end
