object QueryWorkerNum: TQueryWorkerNum
  Left = 276
  Top = 165
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Ա����Ϣ��ѯ'
  ClientHeight = 334
  ClientWidth = 591
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 12
    Width = 41
    Height = 13
    AutoSize = False
    Caption = 'Ա����'
  end
  object Label2: TLabel
    Left = 168
    Top = 12
    Width = 33
    Height = 13
    AutoSize = False
    Caption = '����'
  end
  object Label3: TLabel
    Left = 304
    Top = 12
    Width = 57
    Height = 13
    AutoSize = False
    Caption = '���֤��'
  end
  object WVEdit1: TWVEdit
    Left = 56
    Top = 8
    Width = 89
    Height = 21
    Color = clWhite
    ReadOnly = False
    TabOrder = 0
    Text = '<Ա����>'
    WorkView = WorkView2
    FieldName = 'Ա����'
  end
  object WVEdit2: TWVEdit
    Left = 208
    Top = 8
    Width = 81
    Height = 21
    Color = clWhite
    ReadOnly = False
    TabOrder = 1
    Text = '<����>'
    WorkView = WorkView2
    FieldName = '����'
  end
  object WVEdit3: TWVEdit
    Left = 368
    Top = 8
    Width = 121
    Height = 21
    Color = clWhite
    ReadOnly = False
    TabOrder = 2
    Text = '<���֤��>'
    WorkView = WorkView2
    FieldName = '���֤��'
  end
  object btnQuery: TBitBtn
    Left = 503
    Top = 7
    Width = 75
    Height = 25
    Hint = '��ѯ/ˢ������'
    Anchors = [akTop, akRight]
    Caption = '&Q ��ѯ'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = btnQueryClick
  end
  object WorkerDBGrid: TRzDBGrid
    Left = 0
    Top = 40
    Width = 591
    Height = 294
    Align = alBottom
    DataSource = DataSource2
    FixedColor = 15458000
    TabOrder = 4
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDblClick = WorkerDBGridDblClick
    FrameColor = 12164479
    FrameVisible = True
    FixedLineColor = 12164479
    LineColor = clInactiveCaption
    Columns = <
      item
        Expanded = False
        FieldName = 'sname2'
        Title.Alignment = taCenter
        Title.Caption = '����'
        Width = 71
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        Title.Alignment = taCenter
        Title.Caption = '����'
        Width = 68
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'smarket_code'
        Title.Alignment = taCenter
        Title.Caption = '�Ա�'
        Width = 40
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_no'
        Title.Alignment = taCenter
        Title.Caption = '��λ'
        Width = 109
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol4'
        Title.Alignment = taCenter
        Title.Caption = '���'
        Width = 67
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        Title.Alignment = taCenter
        Title.Caption = 'ְ��'
        Width = 87
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol3'
        Title.Alignment = taCenter
        Title.Caption = '������ò'
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol2'
        Title.Alignment = taCenter
        Title.Caption = '����'
        Width = 53
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol0'
        Title.Alignment = taCenter
        Title.Caption = '״̬'
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth'
        Title.Alignment = taCenter
        Title.Caption = '���֤��'
        Width = 158
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sphone3'
        Title.Alignment = taCenter
        Title.Caption = 'ע��ʱ��'
        Width = 109
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth2'
        Title.Alignment = taCenter
        Title.Caption = '��ϵ�绰'
        Width = 115
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scusttypes'
        Title.Alignment = taCenter
        Title.Caption = '��ϵ��ַ'
        Width = 288
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ssectypes'
        Title.Alignment = taCenter
        Title.Caption = '��ע'
        Width = 359
        Visible = True
      end>
  end
  object DataSource2: TDataSource
    Left = 156
    Top = 271
  end
  object WVDBBinder2: TWVDBBinder
    DataSource = DataSource2
    WorkView = WorkView2
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2002'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2004'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'lvol0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '11'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '33'
      end>
    HideUnbindingFields = False
    Left = 124
    Top = 271
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
    Left = 92
    Top = 271
  end
  object WorkView2: TWorkView
    WorkFields = <
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
    Left = 60
    Top = 271
  end
end
