inherited faqhPASMCardOper: TfaqhPASMCardOper
  Width = 761
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 424
    Width = 761
    Height = 65
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 584
      Top = 13
      Width = 82
      TabOrder = 3
    end
    inherited btnPrint: TBitBtn
      Left = 543
      Top = 67
      TabOrder = 6
      Visible = False
    end
    object btnpasmEdit: TBitBtn
      Left = 392
      Top = 13
      Width = 82
      Height = 25
      Hint = 'PASM���޸�'
      Anchors = [akTop, akRight]
      Caption = 'PSAM���޸�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Visible = False
      OnClick = btnpasmEditClick
    end
    object btnReturn: TBitBtn
      Left = 672
      Top = 13
      Width = 82
      Height = 25
      Hint = 'PASM������'
      Anchors = [akTop, akRight]
      Caption = 'PSAM������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnReturnClick
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 44
      Width = 761
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
      TabOrder = 5
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 761
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
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 321
      Height = 44
      Align = alLeft
      Caption = '�޸���Ϣ'
      TabOrder = 0
      Visible = False
      object lbl1: TLabel
        Left = 8
        Top = 21
        Width = 42
        Height = 12
        AutoSize = False
        Caption = '��״̬'
      end
      object lbl2: TLabel
        Left = 152
        Top = 21
        Width = 57
        Height = 12
        AutoSize = False
        Caption = '��Ч����'
      end
      object cbbStatus: TWVComboBox
        Left = 50
        Top = 17
        Width = 97
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView2
        FieldName = '״̬'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*64'
      end
      object edtLimitDate: TEdit
        Left = 206
        Top = 16
        Width = 103
        Height = 20
        MaxLength = 8
        TabOrder = 0
      end
    end
    object btnReadCard: TBitBtn
      Left = 495
      Top = 13
      Width = 82
      Height = 25
      Hint = 'PASM������'
      Anchors = [akTop, akRight]
      Caption = '������ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnReadCardClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 761
    inherited Image1: TImage
      Width = 761
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 761
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 18
      Top = 9
      Width = 48
      Height = 12
      Caption = 'PSAM����'
    end
    object Label2: TLabel
      Left = 178
      Top = 9
      Width = 36
      Height = 12
      Caption = '������'
    end
    object Label3: TLabel
      Left = 18
      Top = 33
      Width = 48
      Height = 12
      Caption = '��Ч����'
    end
    object Label4: TLabel
      Left = 178
      Top = 33
      Width = 36
      Height = 12
      Caption = '��״̬'
    end
    object lbl3: TLabel
      Left = 342
      Top = 12
      Width = 60
      Height = 12
      Caption = 'ʹ�÷���ʶ'
    end
    object edtCardNo: TWVEdit
      Left = 68
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit3: TWVEdit
      Left = 68
      Top = 29
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<��Ч��>'
      WorkView = WorkView
      FieldName = '��Ч��'
    end
    object WVComboBox3: TWVComboBox
      Left = 216
      Top = 5
      Width = 105
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*150'
    end
    object WVComboBox1: TWVComboBox
      Left = 216
      Top = 28
      Width = 105
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '��״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*140'
    end
    object cbbUser: TWVComboBox
      Left = 408
      Top = 5
      Width = 105
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = 'ʹ�÷�'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*151'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 761
    Height = 351
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 761
      Height = 351
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'PSAM����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sholder_ac_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʹ�÷���ʶ'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ն˱��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸��ʱ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Կ������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ч����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�޸�ʱ��'
          Width = 80
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
        Name = '����'
        Caption = '����'
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
        Name = 'ʹ�÷�'
        Caption = 'ʹ�÷�'
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
        Name = '��Ч��'
        Caption = '��Ч��'
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
        Name = '��״̬'
        Caption = '��״̬'
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
        MonitorValueChangedFields = '|���׿���|����Ա����|������|״̬|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = 'PASM����ѯ'
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
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��״̬'
        FieldName = '��״̬'
      end
      item
        ParamName = 'ʹ�÷�'
        FieldName = 'ʹ�÷�'
      end
      item
        ParamName = '��Ч��'
        FieldName = '��Ч��'
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
        DataPresentParam = '140'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '150'
      end
      item
        FieldName = 'sholder_ac_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '152'
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
        Name = '�ն˱��'
        Caption = '�ն˱��'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|���׿���|����Ա����|������|״̬|'
      end>
    Left = 164
    Top = 287
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'PASM������'
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
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 288
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = 'PASM���޸�'
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
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��Կ������'
        FieldName = '��Կ������'
      end
      item
        ParamName = 'ʹ�÷���ʶ'
        FieldName = 'ʹ�÷���ʶ'
      end
      item
        ParamName = '��Ч����'
        FieldName = '��Ч����'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 256
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '״̬'
        Caption = '״̬'
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
        Name = '��Ч����'
        Caption = '��Ч����'
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
        Name = '��Կ������'
        Caption = '��Կ������'
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
        Name = 'ʹ�÷���ʶ'
        Caption = 'ʹ�÷���ʶ'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|���׿���|����Ա����|������|״̬|'
      end>
    Left = 164
    Top = 255
  end
end
