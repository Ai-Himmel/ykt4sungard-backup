inherited faqhqueryTimeGroupDetail: TfaqhqueryTimeGroupDetail
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
    end
  end
  inherited Grid: TRzDBGrid
    Top = 78
    Width = 700
    Height = 381
    Columns = <
      item
        Expanded = False
        FieldName = 'lvol0'
        PickList.Strings = ()
        Title.Caption = 'ʱ�������'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol2'
        PickList.Strings = ()
        Title.Caption = 'ʱ��α��'
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'semail'
        PickList.Strings = ()
        Title.Caption = 'ʱ�������'
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'semail2'
        PickList.Strings = ()
        Title.Caption = 'ʱ�������'
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sdate1'
        PickList.Strings = ()
        Title.Caption = '��ʼʱ��'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sdate2'
        PickList.Strings = ()
        Title.Caption = '����ʱ��'
        Width = 80
        Visible = True
      end>
  end
  object Panel2: TPanel [2]
    Left = 0
    Top = 0
    Width = 700
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 4
    object Label2: TLabel
      Left = 34
      Top = 5
      Width = 160
      Height = 16
      Caption = 'ʱ�������ϸ�����ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 43
    Width = 700
    Height = 35
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 18
      Top = 11
      Width = 72
      Height = 12
      Caption = 'ʱ�������'
    end
    object edtNo: TWVDigitalEdit
      Left = 92
      Top = 7
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
      FieldName = 'ʱ�������'
      SynchronizeByValue = True
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Top = 25
    Width = 700
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
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        Name = '����'
        Caption = '����'
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
        MonitorValueChangedFields = '|ʱ�������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = 'ʱ�������ϸ�����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'ʱ�������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
end
