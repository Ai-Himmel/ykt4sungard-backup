inherited faqhacceptSmartTermList: TfaqhacceptSmartTermList
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 432
    Width = 700
    Height = 57
    inherited btnQuery: TBitBtn
      Left = 283
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 362
      Visible = False
    end
    object ibnUpLoadSerial: TBitBtn
      Left = 595
      Top = 7
      Width = 91
      Height = 25
      Hint = '�ɼ�������ˮ'
      Anchors = [akTop, akRight]
      Caption = '&U �ɼ���ˮ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = ibnUpLoadSerialClick
    end
    object sbInfo: TStatusBar
      Left = 0
      Top = 38
      Width = 700
      Height = 19
      Font.Charset = GB2312_CHARSET
      Font.Color = clTeal
      Font.Height = -15
      Font.Name = '����'
      Font.Style = []
      Panels = <
        item
          Width = 400
        end
        item
          Width = 50
        end>
      SimplePanel = False
      UseSystemFont = False
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
    Height = 6
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
  end
  inherited UIPanel2: TUIPanel
    Top = 24
    Width = 700
    Height = 408
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 408
      Columns = <
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Caption = '������'
          Visible = True
        end>
    end
  end
  object lvSerial: TRzListView [4]
    Left = 0
    Top = 24
    Width = 700
    Height = 408
    Align = alClient
    Color = 16184303
    Columns = <
      item
        Caption = '���'
        Width = 40
      end
      item
        Caption = '�豸����ID'
        Width = 90
      end
      item
        Caption = '��ˮ��'
        Width = 60
      end
      item
        Caption = '�汾��'
        Width = 70
      end
      item
        Caption = '����ʱ��'
        Width = 120
      end
      item
        Caption = '����'
      end
      item
        Caption = '���ױ��'
        Width = 70
      end
      item
        Caption = '����ԭ��'
        Width = 70
      end
      item
        Caption = 'CRC'
        Width = 130
      end>
    ColumnClick = False
    FillLastColumn = False
    FlatScrollBars = True
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '����'
    Font.Style = []
    FrameColor = 16184303
    FrameHotColor = 16184303
    FrameHotStyle = fsFlat
    FrameVisible = True
    GridLines = True
    ParentFont = False
    ParentShowHint = False
    RowSelect = True
    ShowHint = True
    TabOrder = 4
    ViewStyle = vsReport
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
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
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
        Name = '������ˮ��'
        Caption = '������ˮ��'
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = '���ױ��'
        Caption = '���ױ��'
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
        Name = 'ͨ�Ű汾��'
        Caption = 'ͨ�Ű汾��'
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
        Name = 'CRC'
        Caption = 'CRC'
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
        Name = '����ͨ������ԭ��'
        Caption = '����ͨ������ԭ��'
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
        Name = '����ֵ'
        Caption = '����ֵ'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|������|�豸���|����Ա��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�ɼ��ֳֻ���֤��ˮ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'CRC'
        FieldName = 'CRC'
      end
      item
        ParamName = '���ױ��'
        FieldName = '���ױ��'
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '������ˮ��'
        FieldName = '������ˮ��'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '����ͨ������ԭ��'
        FieldName = '����ͨ������ԭ��'
      end
      item
        ParamName = 'ͨ�Ű汾��'
        FieldName = 'ͨ�Ű汾��'
      end
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '������'
        FieldName = '����ֵ'
        Direction = bdParam2Field
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 224
  end
end
