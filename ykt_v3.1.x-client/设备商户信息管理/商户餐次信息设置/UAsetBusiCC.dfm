inherited faqhsetBusiCC: TfaqhsetBusiCC
  Width = 681
  Height = 477
  Caption = '�̻��ʹ���Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 503
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 255
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Width = 161
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 375
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ͽ���ʱ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ͽ���ʱ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ͽ���ʱ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ҹ������ʱ��'
            Width = 80
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
        TabOrder = 1
        object Label1: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '�̻����'
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 76
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
          FieldName = '��ѯ.�̻����'
          SynchronizeByValue = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object lbl1: TLabel [0]
        Left = 232
        Top = 16
        Width = 72
        Height = 12
        AutoSize = False
        Caption = '��ǰѡ���̻�'
      end
      object lblBusi: TLabel [1]
        Left = 312
        Top = 16
        Width = 353
        Height = 12
        AutoSize = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clRed
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 505
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 593
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object pnl1: TPanel
        Left = 0
        Top = 0
        Width = 209
        Height = 418
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 0
        object pnl2: TPanel
          Left = 0
          Top = 0
          Width = 209
          Height = 41
          Align = alTop
          BevelOuter = bvNone
          Color = 14999516
          TabOrder = 0
        end
        object tvCust: TRzTreeView
          Left = 0
          Top = 41
          Width = 225
          Height = 377
          SelectionPen.Color = clBtnShadow
          Align = alLeft
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          Indent = 19
          ParentFont = False
          TabOrder = 1
          OnClick = tvCustClick
        end
      end
      object grp1: TGroupBox
        Left = 232
        Top = 40
        Width = 289
        Height = 153
        Caption = '�ʹ���Ϣ'
        TabOrder = 1
        object Label7: TLabel
          Left = 28
          Top = 28
          Width = 72
          Height = 12
          Caption = '��ͽ���ʱ��'
        end
        object Label8: TLabel
          Left = 28
          Top = 68
          Width = 72
          Height = 12
          Caption = '��ͽ���ʱ��'
        end
        object Label9: TLabel
          Left = 28
          Top = 108
          Width = 72
          Height = 12
          Caption = '��ͽ���ʱ��'
        end
        object edtTime1: TWVEdit
          Left = 109
          Top = 24
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<��ͽ���ʱ��>'
          WorkView = WorkView
          FieldName = '��ͽ���ʱ��'
          SynchronizeWhenExit = True
        end
        object edtTime2: TWVEdit
          Left = 109
          Top = 64
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<��ͽ���ʱ��>'
          WorkView = WorkView
          FieldName = '��ͽ���ʱ��'
          SynchronizeWhenExit = True
        end
        object edtTime3: TWVEdit
          Left = 109
          Top = 104
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<��ͽ���ʱ��>'
          WorkView = WorkView
          FieldName = '��ͽ���ʱ��'
          SynchronizeWhenExit = True
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 108
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
        Name = '��ѯ.�̻����'
        Caption = '��ѯ.�̻����'
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
        Name = '�̻����'
        Caption = '�̻����'
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
        Name = '��ͽ���ʱ��'
        Caption = '��ͽ���ʱ��'
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
        Name = '��ͽ���ʱ��'
        Caption = '��ͽ���ʱ��'
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
        DataField = 'stime2'
      end
      item
        Name = '��ͽ���ʱ��'
        Caption = '��ͽ���ʱ��'
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
        DataField = 'stime3'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.�̻����|��ѯ.��ͽ���ʱ��|��ѯ.��ͽ���ʱ��|��ѯ.��ͽ���' +
          'ʱ��|��ѯ.ҹ������ʱ��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�̻����|��ͽ���ʱ��|��ͽ���ʱ��|��ͽ���ʱ��|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 40
    Top = 128
  end
  inherited QueryRequest: TWVRequest
    ID = '�̻��ʹ���Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻����'
        FieldName = '��ѯ.�̻����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 168
    Top = 128
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 76
    Top = 159
  end
  inherited AddRequest: TWVRequest
    ID = '�̻��ʹ���Ϣ����'
    Bindings = <
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 72
    Top = 128
  end
  inherited DeleteRequest: TWVRequest
    ID = '�̻��ʹ���Ϣ����'
    Bindings = <
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 104
    Top = 128
  end
  inherited ChangeRequest: TWVRequest
    ID = '�̻��ʹ���Ϣ����'
    Bindings = <
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = '��ͽ���ʱ��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 136
    Top = 128
  end
  inherited WVDataSource: TWVDataSource
    Left = 172
    Top = 159
  end
  inherited alDatasetActions: TActionList
    Left = 140
    Top = 156
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�̻���Ϣ������ѯ2'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end>
    Left = 80
    Top = 88
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�̻���ʶ|'
      end>
    Left = 36
    Top = 87
  end
end
