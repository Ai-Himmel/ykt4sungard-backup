inherited faqhCollectionWaterTrade: TfaqhCollectionWaterTrade
  Width = 739
  Height = 526
  inherited UIPanel1: TUIPanel
    Top = 469
    Width = 739
    Height = 57
    inherited btnQuery: TBitBtn
      Left = 462
      Caption = '��ȡ��ˮ'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 121
      Top = 1
      Visible = False
    end
    object btnUpLoad: TBitBtn
      Left = 553
      Top = 3
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '�ϴ���ˮ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnUpLoadClick
    end
    object pb1: TProgressBar
      Left = 0
      Top = 3
      Width = 337
      Height = 22
      Min = 0
      Max = 100
      TabOrder = 3
    end
    object stat1: TStatusBar
      Left = 0
      Top = 32
      Width = 739
      Height = 25
      Color = 15458000
      Panels = <
        item
          Width = 500
        end>
      SimplePanel = False
    end
    object btnClear: TBitBtn
      Left = 640
      Top = 3
      Width = 89
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '��ղɼ���'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnClearClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 739
    inherited Image1: TImage
      Width = 739
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 739
    Height = 451
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object lvSerial: TRzListView
      Left = 0
      Top = 0
      Width = 739
      Height = 451
      Align = alClient
      Columns = <
        item
          Caption = '���'
        end
        item
          Alignment = taCenter
          Caption = 'ˮ���豸��'
          Width = 200
        end
        item
          Alignment = taRightJustify
          Caption = '���'
          Width = 469
        end>
      FlatScrollBars = True
      GridLines = True
      SortType = stData
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 240
    Top = 0
    Width = 65
    Height = 17
    Align = alNone
    Visible = False
    inherited Grid: TRzDBGrid
      Left = 152
      Top = 112
      Width = 97
      Height = 18
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'Lserial1'
          PickList.Strings = ()
          Title.Caption = '��̨��ˮ��'
          Visible = True
        end>
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        Name = '�豸��'
        Caption = '�豸��'
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
        Name = '���'
        Caption = '���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        Name = 'ʧ����'
        Caption = 'ʧ����'
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
        Name = '����Ա����'
        Caption = '����Ա����'
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
        MonitorValueChangedFields = '|�豸��|���|'
      end>
    Left = 156
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = 'ˮ����ˮ�ɼ�'
    Bindings = <
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
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸��'
        FieldName = '�豸��'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = 'ʧ����'
        FieldName = 'ʧ����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end>
    Left = 192
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 224
  end
end
