inherited faqhSetGlobeParaInfo: TfaqhSetGlobeParaInfo
  Width = 708
  Height = 477
  Caption = 'ȫ�ֲ�������'
  inherited pcPages: TRzPageControl
    Width = 708
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 704
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 346
          Enabled = False
          TabOrder = 0
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 610
          Top = 6
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 525
          Top = 6
          TabOrder = 3
        end
        inherited btnDelete: TBitBtn
          Left = 391
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 6
          TabOrder = 2
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 11
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 704
        Height = 385
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '������ʶ'
            Width = 80
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
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Caption = '������λ'
            Width = 80
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
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 704
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 42
          Top = 13
          Width = 48
          Height = 12
          Caption = '������ʶ'
        end
        object WVEdit1: TWVEdit
          Left = 104
          Top = 8
          Width = 105
          Height = 20
          Color = clInfoBk
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.������־>'
          WorkView = WorkView
          FieldName = '��ѯ.������־'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 42
        Top = 44
        Width = 48
        Height = 12
        Caption = '������ʶ'
      end
      object Label3: TLabel [1]
        Left = 42
        Top = 84
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label4: TLabel [2]
        Left = 54
        Top = 164
        Width = 36
        Height = 12
        Caption = '����ֵ'
      end
      object Label7: TLabel [3]
        Left = 42
        Top = 124
        Width = 48
        Height = 12
        Caption = '������λ'
      end
      object WVLabel2: TWVLabel [4]
        Left = 66
        Top = 203
        Width = 24
        Height = 12
        Caption = '��ע'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 704
        TabOrder = 5
        inherited btnOK: TBitBtn
          Left = 532
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 620
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtName: TWVEdit
        Left = 99
        Top = 80
        Width = 152
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Left = 99
        Top = 160
        Width = 152
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<����ֵ>'
        WorkView = WorkView
        FieldName = '����ֵ'
        SynchronizeWhenExit = True
      end
      object edtUnit: TWVEdit
        Left = 99
        Top = 120
        Width = 152
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<������λ>'
        WorkView = WorkView
        FieldName = '������λ'
        SynchronizeWhenExit = True
      end
      object WVEdit5: TWVEdit
        Left = 99
        Top = 200
        Width = 369
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<��ע>'
        WorkView = WorkView
        FieldName = '��ע'
      end
      object edtId: TWVEdit
        Left = 99
        Top = 40
        Width = 152
        Height = 20
        MaxLength = 22
        ParentColor = True
        ReadOnly = True
        TabOrder = 0
        Text = '<������ʶ>'
        WorkView = WorkView
        FieldName = '������ʶ'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 260
    Top = 383
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
        GroupIndex = 1
      end
      item
        Name = '�������.����'
        Caption = '�������.����'
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
      end
      item
        Name = '�������.ɾ��'
        Caption = '�������.ɾ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '�������.�޸�'
        Caption = '�������.�޸�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '��ѯ.������־'
        Caption = '��ѯ.������־'
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
        DataField = 'lvol5'
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
        Checker.MinLength = 14
        Checker.MaxLength = 14
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'spager'
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
        MonitorValueChangedFields = '|��ѯ.������־|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|������־|��������|����ֵ|��Чʱ��|����ʱ��|������λ|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = 'ȫ�ֲ����ؼ��ֲ�ѯ'
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
        FieldName = '��ѯ.������־'
      end>
    Left = 168
    Top = 304
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 104
    Top = 344
  end
  inherited AddRequest: TWVRequest
    ID = 'ȫ�ֲ�������.����'
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
        ParamName = '������ʶ'
        FieldName = '������ʶ'
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
        ParamName = '��Чʱ��'
        FieldName = '��Чʱ��'
      end
      item
        ParamName = '������λ'
        FieldName = '������λ'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 72
    Top = 304
  end
  inherited DeleteRequest: TWVRequest
    ID = 'ȫ�ֲ�������.ɾ��'
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
        ParamName = '������ʶ'
        FieldName = '������ʶ'
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
        ParamName = '��Чʱ��'
        FieldName = '��Чʱ��'
      end
      item
        ParamName = '������λ'
        FieldName = '������λ'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 104
    Top = 304
  end
  inherited ChangeRequest: TWVRequest
    ID = 'ȫ�ֲ�������.�޸�'
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
        ParamName = '������ʶ'
        FieldName = '������ʶ'
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
        ParamName = '��Чʱ��'
        FieldName = '��Чʱ��'
      end
      item
        ParamName = '������λ'
        FieldName = '������λ'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 136
    Top = 304
  end
  inherited WVDataSource: TWVDataSource
    Left = 168
    Top = 343
  end
  inherited alDatasetActions: TActionList
    Left = 135
    Top = 344
  end
end
