inherited frmPersonStat: TfrmPersonStat
  Width = 821
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 447
    Width = 821
    Height = 42
    object Label2: TLabel [0]
      Left = 13
      Top = 9
      Width = 48
      Height = 12
      AutoSize = False
      Caption = '����Ŀ¼'
    end
    inherited btnQuery: TBitBtn
      Left = 644
    end
    inherited btnPrint: TBitBtn
      Left = 731
      Hint = '����ͳ���б�'
      Caption = '����Excel'
      Enabled = True
      Glyph.Data = {00000000}
    end
    object edtFilePath: TEdit
      Left = 64
      Top = 4
      Width = 297
      Height = 20
      TabOrder = 2
      Text = 'C:\����ҵ��ͳ��'
    end
    object pbStatues: TProgressBar
      Left = 0
      Top = 32
      Width = 821
      Height = 10
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 3
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 821
    inherited Image1: TImage
      Width = 821
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 821
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 302
      Top = 9
      Width = 36
      Height = 12
      Caption = '������'
    end
    object lbl1: TLabel
      Left = 474
      Top = 8
      Width = 24
      Height = 12
      Caption = '����'
    end
    object WVLabel1: TWVLabel
      Left = 10
      Top = 8
      Width = 48
      Height = 12
      Caption = '��ʼ�·�'
    end
    object WVLabel2: TWVLabel
      Left = 152
      Top = 8
      Width = 48
      Height = 12
      Caption = '�����·�'
    end
    object Label3: TLabel
      Left = 602
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ֻ���'
    end
    object cbbNetInfo: TWVComboBox
      Left = 339
      Top = 5
      Width = 118
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      DropDownCount = 20
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '�����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-1'
    end
    object edtBeginDate: TWVEdit
      Left = 64
      Top = 4
      Width = 81
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 1
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 208
      Top = 4
      Width = 89
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 2
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object edt1: TWVEdit
      Left = 504
      Top = 4
      Width = 89
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 3
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit1: TWVEdit
      Left = 640
      Top = 4
      Width = 89
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 4
      Text = '<�ֻ���>'
      WorkView = WorkView
      FieldName = '�ֻ���'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 821
    Height = 398
    inherited Grid: TRzDBGrid
      Width = 821
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
      Width = 821
      Height = 398
      Align = alClient
      Columns = <
        item
          Caption = '�ֻ�ͨ������'
          Width = 120
        end
        item
          Caption = '�ֻ���'
          Width = 80
        end
        item
          Caption = '����'
          Width = 80
        end
        item
          Caption = '������'
          Width = 100
        end
        item
          Alignment = taCenter
          Caption = '��ֵ����'
          Width = 80
        end
        item
          Alignment = taCenter
          Caption = '��ֵ���'
          Width = 100
        end
        item
          Alignment = taCenter
          Caption = '���Ѵ���'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = '���ѽ��'
          Width = 150
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
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
      end
      item
        Name = '������'
        Caption = '������'
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
        Name = '����'
        Caption = '����'
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
        Name = '�ֻ���'
        Caption = '�ֻ���'
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
        MonitorValueChangedFields = '|���κ�|'
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '����ҵ��ͳ��'
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
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�ֻ���'
        FieldName = '�ֻ���'
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
end
