inherited faqhSmartTermUpSerial: TfaqhSmartTermUpSerial
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 426
    Width = 700
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 379
      Top = 6
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 466
      Top = 6
      Visible = False
    end
    object ibnUpLoadSerial: TBitBtn
      Left = 603
      Top = 6
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
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel2: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 15
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
  end
  inherited UIPanel2: TUIPanel
    Top = 33
    Width = 700
    Height = 393
    inherited Grid: TRzDBGrid
      Align = alNone
      Visible = False
    end
  end
  object lvSerial: TRzListView [4]
    Left = 0
    Top = 33
    Width = 700
    Height = 393
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
        Caption = 'ͨ�Ű汾'
        Width = 70
      end
      item
        Caption = '����ԭ��'
        Width = 70
      end
      item
        Caption = '��������'
        Width = 90
      end
      item
        Caption = '����'
      end
      item
        Caption = '��ʹ�ô���'
        Width = 100
      end
      item
        Caption = '�뿨ֵ'
        Width = 60
      end
      item
        Caption = '����ֵ'
        Width = 60
      end
      item
        Caption = '���׽��'
        Width = 70
      end
      item
        Caption = '���ױ��'
        Width = 70
      end
      item
        Caption = 'CRC'
        Width = 20
      end>
    ColumnClick = False
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
    ParentColor = True
    ParentFont = False
    RowSelect = True
    ShowWorkAreas = True
    TabOrder = 4
    ViewStyle = vsReport
  end
  object sbInfo: TStatusBar [5]
    Left = 0
    Top = 462
    Width = 700
    Height = 27
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
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸�ɣ�'
        Caption = '�ն��豸�ɣ�'
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'Ǯ����'
        Caption = 'Ǯ����'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = '�ۼ�ʹ�ô���'
        Caption = '�ۼ�ʹ�ô���'
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
        Name = '�������ѽ��'
        Caption = '�������ѽ��'
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
        Name = '�뿨���'
        Caption = '�뿨���'
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
        Name = '�������'
        Caption = '�������'
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
        Name = '���ױ��'
        Caption = '���ױ��'
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
        Name = 'ͨ�Ű汾��'
        Caption = 'ͨ�Ű汾��'
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
        Name = '����ͨ������ԭ��'
        Caption = '����ͨ������ԭ��'
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
        Name = 'CRC'
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
        Name = '����ֵ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '-1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�ն��豸�ɣ�|������ˮ��|���׿���|Ǯ����|��������|����ʱ��|�ۼ�' +
          'ʹ�ô���|�������ѽ��|�뿨���|�������|���ױ��|ͨ�Ű汾��|����' +
          'ͨ������ԭ��||'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 20
    Top = 207
  end
  inherited MainRequest: TWVRequest
    ID = '�ֳֻ���ˮ�ɼ�'
    Bindings = <
      item
        ParamName = '�ն��豸�ɣ�'
        FieldName = '�ն��豸�ɣ�'
      end
      item
        ParamName = '������ˮ��'
        FieldName = '������ˮ��'
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
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
        ParamName = '�ۼ�ʹ�ô���'
        FieldName = '�ۼ�ʹ�ô���'
      end
      item
        ParamName = '�������ѽ��'
        FieldName = '�������ѽ��'
      end
      item
        ParamName = '�뿨���'
        FieldName = '�뿨���'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���ױ��'
        FieldName = '���ױ��'
      end
      item
        ParamName = 'ͨ�Ű汾��'
        FieldName = 'ͨ�Ű汾��'
      end
      item
        ParamName = '����ͨ������ԭ��'
        FieldName = '����ͨ������ԭ��'
      end
      item
        ParamName = 'CRC'
        FieldName = 'CRC'
      end
      item
        ParamName = '������'
        FieldName = '����ֵ'
        Direction = bdParam2Field
      end>
    Left = 56
    Top = 208
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 88
    Top = 208
  end
  inherited DataSource: TDataSource
    Left = 120
    Top = 208
  end
end
