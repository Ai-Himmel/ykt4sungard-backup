inherited faqhSmartTermSetParam: TfaqhSmartTermSetParam
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
    end
  end
  inherited Grid: TDBGrid
    Top = 121
    Width = 700
    Height = 338
    OnDrawColumnCell = GridDrawColumnCell
    Columns = <
      item
        Expanded = False
        FieldName = 'lvol0'
        PickList.Strings = ()
        Title.Caption = '�豸��ʶ'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ID    sbank_pwd2'
        PickList.Strings = ()
        Title.Caption = '�豸���'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        PickList.Strings = ()
        Title.Caption = '����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sbank_code'
        PickList.Strings = ()
        Title.Caption = '���ʹ���'
        Visible = True
      end>
end
  object Panel2: TPanel [2]
    Left = 0
    Top = 0
    Width = 700
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label12: TLabel
      Left = 34
      Top = 5
      Width = 176
      Height = 16
      Caption = '�ֳֻ���ˮ�ɼ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 25
    Width = 700
    Height = 155
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left    = 42
      Top     = 9
      Width   = 48
      Height  = 12
      Caption = '�豸����'
    end
    object Label2: TLabel
      Left    = 206
      Top     = 9
      Width   = 84
      Height  = 12
      Caption = '�����豸ע���'
    end
    object Label3: TLabel
      Left    = 448
      Top     = 9
      Width   = 42
      Height  = 12
      Caption = '�豸���'
    end
    object Label4: TLabel
      Left    = 66
      Top     = 49
      Width   = 24
      Height  = 12
      Caption = '����'
    end
    object Label5: TLabel
      Left    = 242
      Top     = 49
      Width   = 48
      Height  = 12
      Caption = '���ʹ���'
    end
    object Label6: TLabel
      Left    = 424
      Top     = 49
      Width   = 66
      Height  = 12
      Caption = '�ϼ��豸���'
    end
    object Label7: TLabel
      Left    = 42
      Top     = 89
      Width   = 48
      Height  = 12
      Caption = '�豸״̬'
    end
    object Label8: TLabel
      Left    = 218
      Top     = 89
      Width   = 72
      Height  = 12
      Caption = '�豸�����ͺ�'
    end
    object Label9: TLabel
      Left    = 430
      Top     = 89
      Width   = 60
      Height  = 12
      Caption = '������ϵͳ'
    end
    object Label10: TLabel
      Left    = 18
      Top     = 129
      Width   = 72
      Height  = 12
      Caption = '�豸��������'
    end
    object Label11: TLabel
      Left    = 218
      Top     = 129
      Width   = 72
      Height  = 12
      Caption = '������Ա����'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = ''
      WorkView = WorkView
      FieldName = '�豸����'
    end
    object WVEdit2: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = ''
      WorkView = WorkView
      FieldName = '�����豸ע���'
    end
    object WVEdit3: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = ''
      WorkView = WorkView
      FieldName = '�豸���'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 45
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = ''
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit5: TWVEdit
      Left = 300
      Top = 45
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = ''
      WorkView = WorkView
      FieldName = '���ʹ���'
    end
    object WVEdit6: TWVEdit
      Left = 500
      Top = 45
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = ''
      WorkView = WorkView
      FieldName = '�ϼ��豸���'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 85
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 6
      Text = ''
      WorkView = WorkView
      FieldName = '�豸״̬'
    end
    object WVEdit8: TWVEdit
      Left = 300
      Top = 85
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
      Text = ''
      WorkView = WorkView
      FieldName = '�豸�����ͺ�'
    end
    object WVEdit9: TWVEdit
      Left = 500
      Top = 85
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 8
      Text = ''
      WorkView = WorkView
      FieldName = '������ϵͳ'
    end
    object WVEdit10: TWVEdit
      Left = 100
      Top = 125
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = ''
      WorkView = WorkView
      FieldName = '�豸��������'
    end
    object WVEdit11: TWVEdit
      Left = 300
      Top = 125
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = ''
      WorkView = WorkView
      FieldName = '������Ա����'
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
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '�����豸ע���'
        Caption = '�����豸ע���'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '�ϼ��豸���'
        Caption = '�ϼ��豸���'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '�豸״̬'
        Caption = '�豸״̬'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '�豸��������'
        Caption = '�豸��������'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '������Ա����'
        Caption = '������Ա����'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�ֳֻ���ˮ�ɼ�'
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
        ParamName = '�豸���'
        FieldName = '�豸���'
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
        ParamName = '�ϼ��豸���'
        FieldName = '�ϼ��豸���'
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
        ParamName = '������Ա����'
        FieldName = '������Ա����'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
>
    Left = 328
    Top = 240
  end
  inherited DataSource: TDataSource
    Left = 376
    Top = 288
  end
end
