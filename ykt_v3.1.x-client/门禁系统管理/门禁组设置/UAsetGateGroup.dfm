inherited faqhsetGateGroup: TfaqhsetGateGroup
  Width = 681
  Height = 477
  Caption = '�Ž�������'
  object Label3: TLabel [0]
    Left = 166
    Top = 178
    Width = 60
    Height = 12
    Caption = '�Ž�������'
  end
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
          Left = 416
          Top = 6
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Top = 6
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
          Top = 6
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 6
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
          Top = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Top = 11
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        Align = alNone
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 677
        Height = 385
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '�Ž�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ž�������'
            Width = 200
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 30
          Top = 10
          Width = 60
          Height = 12
          Caption = '�Ž�����'
        end
        object Label2: TLabel
          Left = 230
          Top = 10
          Width = 60
          Height = 12
          Caption = '�Ž�������'
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 100
          Top = 6
          Width = 100
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 0
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '��ѯ.�Ž�����'
          SynchronizeByValue = True
        end
        object WVEdit2: TWVEdit
          Left = 300
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�Ž�������>'
          WorkView = WorkView
          FieldName = '��ѯ.�Ž�������'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label4: TLabel [0]
        Left = 166
        Top = 124
        Width = 70
        Height = 14
        Caption = '�Ž�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel [1]
        Left = 42
        Top = 5
        Width = 80
        Height = 16
        Caption = '�Ž�������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel [2]
        Left = 166
        Top = 171
        Width = 70
        Height = 14
        Caption = '�Ž�������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 1
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
      object edtNo: TWVDigitalEdit
        Left = 244
        Top = 120
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�Ž�����'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 244
        Top = 165
        Width = 229
        Height = 22
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        ReadOnly = False
        TabOrder = 2
        Text = '<�Ž�������>'
        WorkView = WorkView
        FieldName = '�Ž�������'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 396
    Top = 79
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
        Name = '��ѯ.�Ž�����'
        Caption = '��ѯ.�Ž�����'
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
        Name = '��ѯ.�Ž�������'
        Caption = '��ѯ.�Ž�������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
        Name = '�Ž�����'
        Caption = '�Ž�����'
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
        Name = '�Ž�������'
        Caption = '�Ž�������'
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
        GroupIndex = 1
        DataField = 'semail'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�Ž�����|��ѯ.�Ž�������|��ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�Ž�����|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 328
    Top = 40
  end
  inherited QueryRequest: TWVRequest
    ID = '�Ž����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�Ž�����'
        FieldName = '��ѯ.�Ž�����'
      end
      item
        ParamName = '�Ž�������'
        FieldName = '��ѯ.�Ž�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 456
    Top = 40
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 364
    Top = 79
  end
  inherited AddRequest: TWVRequest
    ID = '�Ž�������'
    Bindings = <
      item
        ParamName = '�Ž�����'
        FieldName = '�Ž�����'
      end
      item
        ParamName = '�Ž�������'
        FieldName = '�Ž�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 360
    Top = 40
  end
  inherited DeleteRequest: TWVRequest
    ID = '�Ž�������'
    Bindings = <
      item
        ParamName = '�Ž�����'
        FieldName = '�Ž�����'
      end
      item
        ParamName = '�Ž�������'
        FieldName = '�Ž�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 392
    Top = 40
  end
  inherited ChangeRequest: TWVRequest
    ID = '�Ž�������'
    Bindings = <
      item
        ParamName = '�Ž�����'
        FieldName = '�Ž�����'
      end
      item
        ParamName = '�Ž�������'
        FieldName = '�Ž�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 424
    Top = 40
  end
  inherited WVDataSource: TWVDataSource
    Left = 460
    Top = 79
  end
  inherited alDatasetActions: TActionList
    Left = 428
    Top = 76
  end
end
