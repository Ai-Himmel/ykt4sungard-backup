inherited faqhSetSpeInfoByKey: TfaqhSetSpeInfoByKey
  Width = 681
  Height = 477
  Caption = 'רҵ��Ϣ����'
  inherited pcPages: TPageControl
    Width = 681
    Height = 477
    inherited tsQuery: TTabSheet
      inherited UIPanel1: TUIPanel
        Top = 420
        Width = 673
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 415
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 503
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 322
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
          TabOrder = 2
        end
      end
      inherited Grid: TDBGrid
        Left = 0
        Top = 97
        Width = 673
        Height = 323
        Align = alClient
        TabOrder = 2
        OnDrawColumnCell = GridDrawColumnCell
        Columns = <
      item
        Expanded = False
        FieldName = 'sstation0'
        PickList.Strings = ()
        Title.Caption = 'רҵ����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        PickList.Strings = ()
        Title.Caption = 'רҵ����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'usset2'
        PickList.Strings = ()
        Title.Caption = '��ע'
        Visible = True
      end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 673
        Height = 60
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label4: TLabel
          Left = 42
          Top = 5
          Width = 128
          Height = 16
          Caption = 'רҵ��Ϣ��ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
    object Label1: TLabel
      Left    = 42
      Top     = 34
      Width   = 48
      Height  = 12
      Caption = 'רҵ����'
    end
    object WVComboBox1: TWVComboBox
      Left = 100
      Top = 30
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '��ѯ.רҵ����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '10'
    end
      end
    end
    inherited tsEdit: TTabSheet
    object Label2: TLabel [0]
      Left    = 42
      Top     = 44
      Width   = 48
      Height  = 12
      Caption = 'רҵ����'
    end
    object Label3: TLabel [1]
      Left    = 292
      Top     = 44
      Width   = 48
      Height  = 12
      Caption = 'רҵ����'
    end
      object Label5: TLabel [2]
        Left = 42
        Top = 5
        Width = 128
        Height = 16
        Caption = 'רҵ��Ϣ����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 414
        Width = 673
        inherited btnOK: TBitBtn
          Left = 501
        end
        inherited btnCancel: TBitBtn
          Left = 589
        end
        inherited DBNavigator: TDBNavigator
          Hints.Strings = ()
        end
      end
    object WVEdit2: TWVEdit
      Left = 100
      Top = 40
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = ''
      WorkView = WorkView
      FieldName = 'רҵ����'
	  SynchronizeWhenExit = True
    end
    object WVEdit3: TWVEdit
      Left = 350
      Top = 40
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = ''
      WorkView = WorkView
      FieldName = 'רҵ����'
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
        Name = '��ѯ.רҵ����'
        Caption = '��ѯ.רҵ����'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 20
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = 'רҵ����'
        Caption = 'רҵ����'
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
		GroupIndex = 1
        DataField = 'sstation0'
		GetPrevChar = '*'
      end
      item
        Name = 'רҵ����'
        Caption = 'רҵ����'
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
		GroupIndex = 1
        DataField = 'sname'
		GetPrevChar = '*'
      end
      item
        Name = '��ע'
        Caption = '��ע'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GroupIndex = 1
        DataField = 'usset2'
		GetPrevChar = '*'
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
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = 'רҵ��Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'רҵ����'
        FieldName = '��ѯ.רҵ����'
      end>
    Left = 472
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
>
    Left = 164
    Top = 383
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
        ParamName = '��ע'
        FieldName = '��ע.����'
      end>
    Top = 360
  end
  inherited DeleteRequest: TWVRequest
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
        ParamName = '��ע'
        FieldName = '��ע.ɾ��'
      end>
    Left = 216
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
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
        ParamName = '��ע'
        FieldName = '��ע.�޸�'
      end>
    Left = 384
    Top = 336
  end
  inherited WVDataSource: TWVDataSource
    Left = 540
    Top = 375
  end
  inherited alDatasetActions: TActionList
    Left = 332
    Top = 396
  end
end