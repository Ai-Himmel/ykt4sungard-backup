inherited faqhGateTimeWeekManager: TfaqhGateTimeWeekManager
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 435
    end
    inherited btnPrint: TBitBtn
      Left = 610
      TabOrder = 2
    end
    object btnDelete: TBitBtn
      Left = 523
      Top = 3
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '&D ɾ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnDeleteClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label2: TLabel
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '���������'
    end
    object Label3: TLabel
      Left = 230
      Top = 9
      Width = 60
      Height = 12
      Caption = '����������'
    end
    object Label7: TLabel
      Left = 442
      Top = 9
      Width = 48
      Height = 12
      Caption = '�豸����'
    end
    object Label10: TLabel
      Left = 230
      Top = 33
      Width = 60
      Height = 12
      Caption = 'ʱ��������'
    end
    object Label12: TLabel
      Left = 54
      Top = 34
      Width = 36
      Height = 12
      Caption = '��ϵͳ'
    end
    object WVEdit2: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<���������>'
      WorkView = WorkView
      FieldName = '���������'
    end
    object WVEdit3: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<����������>'
      WorkView = WorkView
      FieldName = '����������'
    end
    object WVEdit10: TWVEdit
      Left = 300
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<ʱ��������>'
      WorkView = WorkView
      FieldName = 'ʱ��������'
    end
    object WVComboBox7: TWVComboBox
      Left = 100
      Top = 28
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '��ϵͳ'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-32'
    end
    object cbbScode: TWVComboBox
      Left = 500
      Top = 4
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '�豸����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*47'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 700
    Height = 386
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 386
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '���������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Caption = '����������'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '�豸���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'saddr'
          PickList.Strings = ()
          Title.Caption = '�豸����'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Caption = 'ʱ���ܱ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'saddr2'
          PickList.Strings = ()
          Title.Caption = 'ʱ��������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Caption = '�豸����'
          Width = 90
          Visible = True
        end>
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
        Name = '�������'
        Caption = '�������'
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
      end
      item
        Name = '���������'
        Caption = '���������'
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
      end
      item
        Name = '����������'
        Caption = '����������'
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
      end
      item
        Name = '�豸������'
        Caption = '�豸������'
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
      end
      item
        Name = '�豸����'
        Caption = '�豸����'
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
      end
      item
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
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
      end
      item
        Name = '�豸����'
        Caption = '�豸����'
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
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ʱ���ܱ��'
        Caption = 'ʱ���ܱ��'
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
      end
      item
        Name = 'ʱ��������'
        Caption = 'ʱ��������'
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
      end
      item
        Name = '��ϵͳ'
        Caption = '��ϵͳ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
          '|�������|���������|����������|�豸������|�豸����|�豸������' +
          '��|�豸����|��������|ʱ���ܱ��|ʱ��������|��ϵͳ|'
      end>
    Left = 156
    Top = 239
  end
  inherited MainRequest: TWVRequest
    ID = '�Ž�ʱ���ܹ���'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'ʱ���ܱ��'
      end
      item
        ParamName = 'ʱ��������'
        FieldName = 'ʱ��������'
      end
      item
        ParamName = '��ϵͳ'
        FieldName = '��ϵͳ'
      end>
    Left = 192
    Top = 240
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'spost_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '47'
      end>
    Left = 224
    Top = 240
  end
  inherited DataSource: TDataSource
    Left = 256
    Top = 240
  end
  object WorkView1: TWorkView
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
        DataField = '@Return'
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
      end
      item
        Name = '�������'
        Caption = '�������'
        FieldType = wftUndefined
        DataType = kdtString
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
        Name = '���������'
        Caption = '���������'
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
        Name = '�豸���'
        Caption = '�豸���'
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
        Name = 'ʱ���ܱ��'
        Caption = 'ʱ���ܱ��'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�������|���������|����������|�豸������|�豸����|�豸������' +
          '��|�豸����|��������|ʱ���ܱ��|ʱ��������|��ϵͳ|'
      end>
    Left = 156
    Top = 311
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�Ž�ʱ����ɾ��'
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
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'ʱ���ܱ��'
      end>
    AfterExec = MainRequestAfterExec
    Left = 192
    Top = 312
  end
end
