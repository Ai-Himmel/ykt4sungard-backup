inherited faqhPatchPay: TfaqhPatchPay
  Width = 754
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 447
    Width = 754
    Height = 42
    object Label2: TLabel [0]
      Left = 69
      Top = 10
      Width = 28
      Height = 12
      AutoSize = False
      Caption = '����'
    end
    inherited btnQuery: TBitBtn
      Left = 577
    end
    inherited btnPrint: TBitBtn
      Left = 664
      Hint = '��������'
      Caption = '��������'
      Enabled = True
      Glyph.Data = {00000000}
    end
    object edtTipInfo: TEdit
      Left = 96
      Top = 5
      Width = 337
      Height = 20
      TabOrder = 2
    end
    object pbStatues: TProgressBar
      Left = 0
      Top = 32
      Width = 754
      Height = 10
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 3
    end
    object chkSelectAll: TCheckBox
      Left = 16
      Top = 8
      Width = 49
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 4
      OnClick = chkSelectAllClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 754
    inherited Image1: TImage
      Width = 754
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 754
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object WVLabel1: TWVLabel
      Left = 26
      Top = 8
      Width = 36
      Height = 12
      Caption = '�̻���'
    end
    object WVLabel2: TWVLabel
      Left = 152
      Top = 8
      Width = 48
      Height = 12
      Caption = '�̻�����'
    end
    object edtBusiId: TWVEdit
      Left = 64
      Top = 4
      Width = 81
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<�̻���>'
      WorkView = WorkView
      FieldName = '�̻���'
    end
    object edtBusiname: TWVEdit
      Left = 208
      Top = 4
      Width = 217
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 1
      Text = '<�̻�����>'
      WorkView = WorkView
      FieldName = '�̻�����'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 754
    Height = 398
    inherited Grid: TRzDBGrid
      Width = 754
      Height = 398
      Columns = <
        item
          Expanded = False
          FieldName = 'snote2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���κ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӧ�����к�'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ч��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 100
          Visible = True
        end>
    end
    object lvData: TRzListView
      Left = 0
      Top = 0
      Width = 754
      Height = 398
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '�̻���'
          Width = 80
        end
        item
          Caption = '�̻�����'
          Width = 200
        end
        item
          Caption = '�̻����'
          Width = 80
        end
        item
          Caption = '�������'
          Width = 373
        end>
      GridLines = True
      TabOrder = 1
      ViewStyle = vsReport
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
      end
      item
        Name = '�̻�����'
        Caption = '�̻�����'
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
        Name = '�̻���'
        Caption = '�̻���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|���κ�|'
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�̻�����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
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
        ParamName = '�̻���'
        FieldName = '�̻���'
        DefaultValue = 0
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sroom_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '210'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-5'
      end
      item
        FieldName = 'sroom_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '201'
      end>
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 200
    Top = 256
  end
  object WorkView1: TWorkView
    WorkFields = <
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
      end
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
        Name = '������Ϣ'
        Caption = '������Ϣ'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�̻�1'
        Caption = '�̻�1'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�̻�2'
        Caption = '�̻�2'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�̻�0'
        Caption = '�̻�0'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�̻�3'
        Caption = '�̻�3'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|���κ�|'
      end>
    Left = 92
    Top = 295
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�̻���������'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
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
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�̻�0'
        FieldName = '�̻�0'
      end
      item
        ParamName = '�̻�1'
        FieldName = '�̻�1'
      end
      item
        ParamName = '�̻�2'
        FieldName = '�̻�2'
      end
      item
        ParamName = '�̻�3'
        FieldName = '�̻�3'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 296
  end
end
