inherited faqhSetPhoneNo: TfaqhSetPhoneNo
  Width = 763
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 456
    Width = 763
    Height = 33
    object Label1: TLabel [0]
      Left = 162
      Top = 9
      Width = 72
      Height = 12
      Caption = '�ֻ�ͨ������'
    end
    object Label6: TLabel [1]
      Left = 342
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ֻ���'
    end
    object Label7: TLabel [2]
      Left = 18
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    inherited btnQuery: TBitBtn
      Left = 498
    end
    inherited btnPrint: TBitBtn
      Left = 673
    end
    object edtTNo: TWVEdit
      Left = 236
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<�ֻ�ͨ������>'
      WorkView = WVSet
      FieldName = '�ֻ�ͨ������'
    end
    object edtPhone: TWVEdit
      Left = 380
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<�ֻ���>'
      WorkView = WVSet
      FieldName = '�ֻ���'
    end
    object edtCardNo: TWVEdit
      Left = 44
      Top = 5
      Width = 100
      Height = 20
      MaxLength = 22
      ParentColor = True
      ReadOnly = True
      TabOrder = 4
      Text = '<����>'
      WorkView = WVSet
      FieldName = '����'
    end
    object btnEdit: TBitBtn
      Left = 586
      Top = 3
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '�޸�(&E)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnEditClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 763
    inherited Image1: TImage
      Width = 763
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 763
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label2: TLabel
      Left = 26
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label3: TLabel
      Left = 170
      Top = 9
      Width = 72
      Height = 12
      Caption = '�ֻ�ͨ������'
    end
    object Label4: TLabel
      Left = 350
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ֻ���'
    end
    object Label5: TLabel
      Left = 498
      Top = 9
      Width = 48
      Height = 12
      Caption = '����ʱ��'
    end
    object edtCardNoQ: TWVEdit
      Left = 60
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit3: TWVEdit
      Left = 244
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 1
      Text = '<�ֻ�ͨ������>'
      WorkView = WorkView
      FieldName = '�ֻ�ͨ������'
    end
    object WVEdit4: TWVEdit
      Left = 388
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<�ֻ���>'
      WorkView = WorkView
      FieldName = '�ֻ���'
    end
    object WVEdit5: TWVEdit
      Left = 556
      Top = 5
      Width = 133
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<����ʱ��>'
      WorkView = WorkView
      FieldName = '����ʱ��'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 763
    Height = 407
    inherited Grid: TRzDBGrid
      Width = 763
      Height = 407
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֻ�ͨ������'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֻ���'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 150
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
        Name = '������־'
        Caption = '������־'
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
        Name = '�ֻ�ͨ������'
        Caption = '�ֻ�ͨ������'
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
        Name = '�ֻ���'
        Caption = '�ֻ���'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        MonitorValueChangedFields = '|������־|����|�ֻ�ͨ������|�ֻ���|����ʱ��|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�ֻ�����Ϣά��Q'
    Bindings = <
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
        DefaultValue = 0
      end
      item
        ParamName = '�ֻ�ͨ������'
        FieldName = '�ֻ�ͨ������'
      end
      item
        ParamName = '�ֻ���'
        FieldName = '�ֻ���'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
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
  object WVSet: TWorkView
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
        Name = '�ֻ�ͨ������'
        Caption = '�ֻ�ͨ������'
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
        Name = '�ֻ���'
        Caption = '�ֻ���'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        MonitorValueChangedFields = '|������־|����|�ֻ�ͨ������|�ֻ���|����ʱ��|'
      end>
    Left = 164
    Top = 263
  end
  object WVRequest1: TWVRequest
    WorkView = WVSet
    ID = '�ֻ�����Ϣά��'
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
        ParamName = '�ֻ�ͨ������'
        FieldName = '�ֻ�ͨ������'
      end
      item
        ParamName = '�ֻ���'
        FieldName = '�ֻ���'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 264
  end
end
