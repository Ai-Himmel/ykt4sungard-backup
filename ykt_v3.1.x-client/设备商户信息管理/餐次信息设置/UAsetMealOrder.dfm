inherited faqhsetMealOrder: TfaqhsetMealOrder
  Width = 681
  Height = 477
  Caption = '�ʹ���Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 267
          Top = 6
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 595
          Top = 6
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 506
          Top = 6
          TabOrder = 3
        end
        inherited btnDelete: TBitBtn
          Left = 348
          Top = 6
          Enabled = False
          TabOrder = 2
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
          Top = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 12
          Width = 177
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 41
        Width = 677
        Height = 377
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Caption = '�ʹ�����'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Caption = '��ʼʱ��'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime2'
            PickList.Strings = ()
            Title.Caption = '����ʱ��'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '��ע'
            Width = 100
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 23
        Align = alTop
        ParentColor = True
        TabOrder = 1
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label4: TLabel [0]
        Left = 194
        Top = 76
        Width = 24
        Height = 12
        Caption = '���'
        Visible = False
      end
      object Label5: TLabel [1]
        Left = 170
        Top = 116
        Width = 48
        Height = 12
        Caption = '�ʹ�����'
      end
      object Label6: TLabel [2]
        Left = 172
        Top = 156
        Width = 48
        Height = 12
        Caption = '��ʼʱ��'
      end
      object Label8: TLabel [3]
        Left = 42
        Top = 5
        Width = 96
        Height = 16
        Caption = '�ʹ���Ϣ����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel [4]
        Left = 172
        Top = 196
        Width = 48
        Height = 12
        Caption = '����ʱ��'
      end
      object Label10: TLabel [5]
        Left = 332
        Top = 156
        Width = 96
        Height = 12
        Caption = 'ʱ���ʽ(hhmmss)'
      end
      object Label11: TLabel [6]
        Left = 332
        Top = 196
        Width = 96
        Height = 12
        Caption = 'ʱ���ʽ(hhmmss)'
      end
      object Label12: TLabel [7]
        Left = 196
        Top = 228
        Width = 24
        Height = 12
        Caption = '��ע'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 5
        inherited btnOK: TBitBtn
          Left = 501
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 589
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVDigitalEdit4: TWVDigitalEdit
        Left = 228
        Top = 72
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '���'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 228
        Top = 112
        Width = 277
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<�ʹ�����>'
        WorkView = WorkView
        FieldName = '�ʹ�����'
        SynchronizeWhenExit = True
      end
      object edtBegin: TWVEdit
        Left = 230
        Top = 152
        Width = 100
        Height = 20
        Color = clInfoBk
        MaxLength = 6
        ReadOnly = False
        TabOrder = 2
        Text = '<��ʼʱ��>'
        WorkView = WorkView
        FieldName = '��ʼʱ��'
        SynchronizeWhenExit = True
      end
      object edtEnd: TWVEdit
        Left = 230
        Top = 192
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 6
        ReadOnly = False
        TabOrder = 3
        Text = '<����ʱ��>'
        WorkView = WorkView
        FieldName = '����ʱ��'
        SynchronizeWhenExit = True
      end
      object edtMemo: TWVEdit
        Left = 230
        Top = 224
        Width = 275
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<��ע>'
        WorkView = WorkView
        FieldName = '��ע'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 156
    Top = 295
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '���'
        Caption = '���'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '�ʹ�����'
        Caption = '�ʹ�����'
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
        GroupIndex = 1
        DataField = 'sall_name'
      end
      item
        Name = '��ʼʱ��'
        Caption = '��ʼʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'stime1'
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
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'stime2'
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
        DataField = 'sstatus0'
      end
      item
        Name = '����Ա��'
        Caption = '����Ա��'
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
        Name = '��ѯ.�ʹ�����'
        Caption = '��ѯ.�ʹ�����'
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
        Name = '��ѯ.��ʼʱ��'
        Caption = '��ѯ.��ʼʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.����ʱ��'
        Caption = '��ѯ.����ʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
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
        MonitorValueChangedFields = '|��ѯ.�ʹ�����|��ѯ.��ʼʱ��|��ѯ.����ʱ��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|���|�ʹ�����|��ʼʱ��|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 344
    Top = 48
  end
  inherited QueryRequest: TWVRequest
    ID = '�ʹ���Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ʹ�����'
        FieldName = '��ѯ.�ʹ�����'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = '��ѯ.��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '��ѯ.����ʱ��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 504
    Top = 48
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 108
    Top = 295
  end
  inherited AddRequest: TWVRequest
    ID = '�ʹ���Ϣ����'
    Bindings = <
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�ʹ�����'
        FieldName = '�ʹ�����'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 384
    Top = 48
  end
  inherited DeleteRequest: TWVRequest
    ID = '�ʹ���Ϣ����'
    Bindings = <
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�ʹ�����'
        FieldName = '�ʹ�����'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 424
    Top = 48
  end
  inherited ChangeRequest: TWVRequest
    ID = '�ʹ���Ϣ����'
    Bindings = <
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�ʹ�����'
        FieldName = '�ʹ�����'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 464
    Top = 48
  end
  inherited WVDataSource: TWVDataSource
    Left = 260
    Top = 311
  end
  inherited alDatasetActions: TActionList
    Left = 220
    Top = 308
  end
end
