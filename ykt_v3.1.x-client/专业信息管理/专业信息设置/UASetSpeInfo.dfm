inherited faqhSetSpeInfo: TfaqhSetSpeInfo
  Width = 681
  Height = 477
  Caption = 'רҵ��Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 416
          Top = 5
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Top = 5
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 5
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Top = 10
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 369
        Columns = <
          item
            Expanded = False
            FieldName = 'scert_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'רҵ����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'רҵ����'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������ʱ��'
            Width = 300
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 34
          Top = 8
          Width = 48
          Height = 12
          Caption = 'רҵ����'
        end
        object WVLabel1: TWVLabel
          Left = 232
          Top = 8
          Width = 48
          Height = 12
          Caption = 'רҵ����'
        end
        object WVEdit4: TWVEdit
          Left = 90
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.רҵ����>'
          WorkView = WorkView
          FieldName = '��ѯ.רҵ����'
        end
        object WVEdit5: TWVEdit
          Left = 289
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.רҵ����>'
          WorkView = WorkView
          FieldName = '��ѯ.רҵ����'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 36
        Top = 45
        Width = 60
        Height = 12
        Caption = 'רҵ���� *'
      end
      object Label3: TLabel [1]
        Left = 36
        Top = 85
        Width = 60
        Height = 12
        Caption = 'רҵ���� *'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 504
          Top = 5
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 587
          Top = 5
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Top = 5
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVEdit3: TWVEdit
        Left = 110
        Top = 80
        Width = 339
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<רҵ����>'
        WorkView = WorkView
        FieldName = 'רҵ����'
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 110
        Top = 40
        Width = 339
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<רҵ����>'
        WorkView = WorkView
        FieldName = 'רҵ����'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 204
    Top = 335
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
        DataField = '@Return'
      end
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '��ѯ.רҵ����'
        Caption = '��ѯ.רҵ����'
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
        Name = '��ѯ.רҵ����'
        Caption = '��ѯ.רҵ����'
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
        Name = '�������'
        Caption = '�������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
        GroupIndex = 1
      end
      item
        Name = 'רҵ����'
        Caption = 'רҵ����'
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
        DataField = 'scert_no2'
      end
      item
        Name = 'רҵ����'
        Caption = 'רҵ����'
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
        DataField = 'ssectypes'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.רҵ����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|רҵ����|רҵ����|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 71
    Top = 336
  end
  inherited QueryRequest: TWVRequest
    ID = 'רҵ��Ϣ��������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'רҵ����'
        FieldName = '��ѯ.רҵ����'
      end
      item
        ParamName = 'רҵ����'
        FieldName = '��ѯ.רҵ����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 168
    Top = 296
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 104
    Top = 335
  end
  inherited AddRequest: TWVRequest
    ID = 'רҵ��Ϣ����'
    Bindings = <
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
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
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 72
    Top = 296
  end
  inherited DeleteRequest: TWVRequest
    ID = 'רҵ��Ϣ����'
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
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end>
    Left = 104
    Top = 296
  end
  inherited ChangeRequest: TWVRequest
    ID = 'רҵ��Ϣ����'
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
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end>
    Left = 136
    Top = 296
  end
  inherited WVDataSource: TWVDataSource
    Left = 168
    Top = 335
  end
  inherited alDatasetActions: TActionList
    Left = 136
    Top = 335
  end
end
