inherited faqhQueryGlobeParaByOther: TfaqhQueryGlobeParaByOther
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 521
      Top = 6
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 612
      Top = 6
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
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label2: TLabel
      Left = 34
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label3: TLabel
      Left = 228
      Top = 9
      Width = 36
      Height = 12
      Caption = '����ֵ'
    end
    object Label6: TLabel
      Left = 418
      Top = 9
      Width = 48
      Height = 12
      Caption = '������λ'
    end
    object WVLabel1: TWVLabel
      Left = 32
      Top = 48
      Width = 48
      Height = 12
      Caption = '��Чʱ��'
      Visible = False
    end
    object WVLabel2: TWVLabel
      Left = 232
      Top = 48
      Width = 144
      Height = 12
      Caption = '��ʽ����λ����λ����λ��'
      Visible = False
    end
    object WVEdit2: TWVEdit
      Left = 84
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object WVEdit3: TWVEdit
      Left = 267
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<����ֵ>'
      WorkView = WorkView
      FieldName = '����ֵ'
    end
    object WVEdit6: TWVEdit
      Left = 468
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<������λ>'
      WorkView = WorkView
      FieldName = '������λ'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 40
      Width = 101
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<��Чʱ��>'
      Visible = False
      WorkView = WorkView
      FieldName = '��Чʱ��'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 700
    Height = 404
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 404
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '������ʶ'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Caption = '��������'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Caption = '����ֵ'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Caption = '������λ'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Caption = '��ע'
          Width = 300
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
        DataField = '@Return'
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
        DataField = 'vsmess'
      end
      item
        Name = '������ʶ'
        Caption = '������ʶ'
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
        DataField = 'lvol0'
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
        GroupIndex = 1
        DataField = 'scust_auth'
      end
      item
        Name = '����ֵ'
        Caption = '����ֵ'
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
        DataField = 'scard0'
      end
      item
        Name = '��Чʱ��'
        Caption = '��Чʱ��'
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
        DataField = 'spager'
      end
      item
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        DataField = 'sphone'
      end
      item
        Name = '������λ'
        Caption = '������λ'
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
        DataField = 'scust_no'
      end
      item
        Name = '��ע'
        Caption = '��ע'
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
        DataField = 'scusttypes'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|������־|��������|����ֵ|��Чʱ��|����ʱ��|������λ|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = 'ȫ�ֲ����ǹؼ��ֲ�ѯ'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����ֵ'
        FieldName = '����ֵ'
      end
      item
        ParamName = '������λ'
        FieldName = '������λ'
      end
      item
        ParamName = '��Чʱ��'
        FieldName = '��Чʱ��'
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
    Left = 328
    Top = 240
  end
  inherited DataSource: TDataSource
    Left = 376
    Top = 288
  end
end
