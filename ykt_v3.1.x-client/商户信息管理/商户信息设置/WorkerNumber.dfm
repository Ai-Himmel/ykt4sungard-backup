object QueryWorkerNumber: TQueryWorkerNumber
  Left = 183
  Top = 215
  Width = 650
  Height = 339
  Caption = 'Ա����Ϣ��ѯ'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object WorkerDBGrid: TDBGrid
    Left = 0
    Top = 50
    Width = 642
    Height = 255
    Align = alClient
    FixedColor = 15458000
    ImeName = ''
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnCellClick = WorkerDBGridCellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'sname2'
        Title.Alignment = taCenter
        Title.Caption = 'Ա����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        Title.Alignment = taCenter
        Title.Caption = '����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol0'
        Title.Alignment = taCenter
        Title.Caption = 'Ա��״̬'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_no'
        Title.Alignment = taCenter
        Title.Caption = '��λ����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth'
        Title.Alignment = taCenter
        Title.Caption = '���֤��'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        Title.Alignment = taCenter
        Title.Caption = 'ְ�ƴ���'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol3'
        Title.Alignment = taCenter
        Title.Caption = '������ò'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'smarket_code'
        Title.Alignment = taCenter
        Title.Caption = '�Ա�'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth2'
        Title.Alignment = taCenter
        Title.Caption = '��ϵ�绰'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol4'
        Title.Alignment = taCenter
        Title.Caption = 'Ա�����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scusttypes'
        Title.Alignment = taCenter
        Title.Caption = '��ϵ��ַ'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ssectypes'
        Title.Alignment = taCenter
        Title.Caption = '��ע'
        Visible = True
      end>
  end
  object UIPanel1: TUIPanel
    Left = 0
    Top = 0
    Width = 642
    Height = 50
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    Color = 16119543
    TabOrder = 1
    object Label1: TLabel
      Left = 14
      Top = 19
      Width = 39
      Height = 13
      AutoSize = False
      Caption = 'Ա����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 162
      Top = 19
      Width = 28
      Height = 13
      AutoSize = False
      Caption = '����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 284
      Top = 19
      Width = 50
      Height = 13
      AutoSize = False
      Caption = '���֤��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object WVEdit1: TWVEdit
      Left = 56
      Top = 16
      Width = 89
      Height = 21
      ImeName = ''
      ReadOnly = False
      TabOrder = 0
    end
    object WVEdit2: TWVEdit
      Left = 192
      Top = 16
      Width = 81
      Height = 21
      ImeName = ''
      ReadOnly = False
      TabOrder = 1
    end
    object WVEdit3: TWVEdit
      Left = 336
      Top = 16
      Width = 121
      Height = 21
      ImeName = ''
      ReadOnly = False
      TabOrder = 2
    end
    object Button1: TButton
      Left = 468
      Top = 16
      Width = 75
      Height = 25
      Caption = '�� ��'
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 552
      Top = 16
      Width = 73
      Height = 25
      Cancel = True
      Caption = 'ȡ��'
      ModalResult = 2
      TabOrder = 4
    end
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '��ϵ��ַ'
        Caption = '��ϵ��ַ'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scusttypes'
      end
      item
        Name = '��λ����'
        Caption = '��λ����'
        FieldType = wftUndefined
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
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sname'
      end
      item
        Name = 'Ա��״̬'
        Caption = 'Ա��״̬'
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
        Name = 'Ա����'
        Caption = 'Ա����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sname2'
      end
      item
        Name = '���֤��'
        Caption = '���֤��'
        FieldType = wftUndefined
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
        Name = 'ְ�ƴ���'
        Caption = 'ְ�ƴ���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
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
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = '������ò'
        Caption = '������ò'
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
        Name = '�Ա�'
        Caption = '�Ա�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'smarket_code'
      end
      item
        Name = '��ϵ�绰'
        Caption = '��ϵ�绰'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_auth2'
      end
      item
        Name = 'Ա�����'
        Caption = 'Ա�����'
        FieldType = wftUndefined
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
        DataField = '@Dataset'
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 292
    Top = 143
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = 'Ա����Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = '��ϵ��ַ'
      end
      item
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ա��״̬'
        FieldName = 'Ա��״̬'
      end
      item
        ParamName = 'Ա����'
        FieldName = 'Ա����'
      end
      item
        ParamName = '���֤��'
        FieldName = '���֤��'
      end
      item
        ParamName = 'ְ�ƴ���'
        FieldName = 'ְ�ƴ���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '������ò'
        FieldName = '������ò'
      end
      item
        ParamName = '�Ա�'
        FieldName = '�Ա�'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = '��ϵ�绰'
      end
      item
        ParamName = 'Ա�����'
        FieldName = 'Ա�����'
      end>
    Left = 332
    Top = 143
  end
end
