inherited faqhSetGridShowModle: TfaqhSetGridShowModle
  Width = 681
  Height = 477
  Caption = '���ģ����ʾ����'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 3
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
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 78
        Width = 677
        Height = 346
        Columns = <
          item
            Expanded = False
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Caption = 'ģ����'
            Visible = True
          end
          item
            Expanded = False
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ģ������'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ע'
            Width = 200
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 60
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label2: TLabel
          Left = 42
          Top = 5
          Width = 128
          Height = 16
          Caption = '�����ʾģ���ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label1: TLabel
          Left = 42
          Top = 34
          Width = 48
          Height = 12
          Caption = 'ģ������'
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 2
          MaxIntLen = 10
          ParentColor = False
          TabOrder = 0
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '�շ����'
          SynchronizeByValue = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label3: TLabel [0]
        Left = 42
        Top = 5
        Width = 128
        Height = 16
        Caption = '�����ʾģ������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        inherited btnOK: TBitBtn
          Left = 505
        end
        inherited btnCancel: TBitBtn
          Left = 593
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 412
    Top = 159
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
        Name = '��ѯ.�շ����'
        Caption = '��ѯ.�շ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Lvol0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�շ����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 312
    Top = 120
  end
  inherited QueryRequest: TWVRequest
    ID = '���ģ����ʾ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�շ����'
        FieldName = '��ѯ.�շ����'
      end>
    Left = 440
    Top = 120
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 372
    Top = 159
  end
  inherited AddRequest: TWVRequest
    ID = '���ģ����ʾ����'
    Bindings = <
      item
        ParamName = '�շ����'
        FieldName = '�շ����.����'
      end>
    Left = 344
    Top = 120
  end
  inherited DeleteRequest: TWVRequest
    ID = '���ģ����ʾ����'
    Bindings = <
      item
        ParamName = '�շ����'
        FieldName = '�շ����.ɾ��'
      end>
    Left = 376
    Top = 120
  end
  inherited ChangeRequest: TWVRequest
    ID = '���ģ����ʾ����'
    Bindings = <
      item
        ParamName = '�շ����'
        FieldName = '�շ����.�޸�'
      end>
    Left = 408
    Top = 120
  end
  inherited WVDataSource: TWVDataSource
    Left = 476
    Top = 119
  end
  inherited alDatasetActions: TActionList
    Left = 452
    Top = 156
  end
end
