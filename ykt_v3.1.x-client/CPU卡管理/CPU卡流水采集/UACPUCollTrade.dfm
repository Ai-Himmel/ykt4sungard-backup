inherited faqhCPUCollTrade: TfaqhCPUCollTrade
  Width = 798
  Height = 526
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 798
    Height = 67
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 521
      Caption = '��ȡ��ˮ'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 180
      Top = 1000
      TabOrder = 6
      Visible = False
    end
    object btnUpLoad: TBitBtn
      Left = 612
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
      TabOrder = 1
      OnClick = btnUpLoadClick
    end
    object pb1: TProgressBar
      Left = 0
      Top = 33
      Width = 798
      Height = 9
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 4
    end
    object stat1: TStatusBar
      Left = 0
      Top = 42
      Width = 798
      Height = 25
      Color = 15458000
      Panels = <
        item
          Width = 500
        end>
      SimplePanel = False
    end
    object btnClear: TBitBtn
      Left = 699
      Top = 3
      Width = 89
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '��ռ�¼'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnClearClick
    end
    object chkSelectAll: TCheckBox
      Left = 8
      Top = 8
      Width = 49
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 3
      OnClick = chkSelectAllClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 798
    inherited Image1: TImage
      Width = 798
    end
    inherited LabRecordCount: TLabel
      Left = 0
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 798
    Height = 441
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object lvSerial: TRzListView
      Left = 0
      Top = 0
      Width = 798
      Height = 441
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '���'
        end
        item
          Alignment = taCenter
          Caption = '��������'
          Width = 80
        end
        item
          Alignment = taCenter
          Caption = '����ʱ��'
          Width = 80
        end
        item
          Caption = '���״���'
          Width = 60
        end
        item
          Alignment = taRightJustify
          Caption = '����ǰ���'
          Width = 90
        end
        item
          Alignment = taRightJustify
          Caption = '���׽��'
          Width = 70
        end
        item
          Alignment = taRightJustify
          Caption = '����'
        end
        item
          Alignment = taRightJustify
          Caption = '��д���'
          Width = 70
        end
        item
          Caption = '�̻���'
        end
        item
          Caption = '�ն˱��'
          Width = 60
        end
        item
          Caption = '�������'
          Width = 117
        end>
      FlatScrollBars = True
      GridLines = True
      MultiSelect = True
      SortType = stData
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 488
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
        Name = 'վ���'
        Caption = 'վ���'
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
      end
      item
        Name = '���ױ�־'
        Caption = '���ױ�־'
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
        Name = '���Ѵ���'
        Caption = '���Ѵ���'
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
        Name = '����ǰ���'
        Caption = '����ǰ���'
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
        Name = '���׽��'
        Caption = '���׽��'
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
      end
      item
        Name = '��д���'
        Caption = '��д���'
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
        Name = '�̻���'
        Caption = '�̻���'
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
        Name = '�ն˱��'
        Caption = '�ն˱��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sserial0'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        MonitorValueChangedFields = '|�豸��|���|'
      end>
    Left = 156
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = 'CPU����ˮ�ɼ�'
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
        ParamName = 'վ���'
        FieldName = 'վ���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '���ױ�־'
        FieldName = '���ױ�־'
      end
      item
        ParamName = '���Ѵ���'
        FieldName = '���Ѵ���'
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
        ParamName = '����ǰ���'
        FieldName = '����ǰ���'
      end
      item
        ParamName = '���׽��'
        FieldName = '���׽��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��д���'
        FieldName = '��д���'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
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
