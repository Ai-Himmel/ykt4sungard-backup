inherited faqhAttendSerialList: TfaqhAttendSerialList
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 432
    Width = 700
    Height = 57
    object lbl1: TLabel [0]
      Left = 8
      Top = 16
      Width = 84
      Height = 12
      Caption = '��ˮ���λ�ã�'
    end
    inherited btnQuery: TBitBtn
      Left = 283
      Top = 1000
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 362
      Top = 1000
      Visible = False
    end
    object ibnUpLoadSerial: TBitBtn
      Left = 499
      Top = 7
      Width = 91
      Height = 25
      Hint = '�ɼ�������ˮ'
      Anchors = [akTop, akRight]
      Caption = '�ɼ���ˮ(&G)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = ibnUpLoadSerialClick
    end
    object edtFileName: TEdit
      Left = 88
      Top = 12
      Width = 209
      Height = 20
      TabOrder = 3
      Text = 'C:\serial.txt'
    end
    object btnUpload: TBitBtn
      Left = 595
      Top = 7
      Width = 91
      Height = 25
      Hint = '�ϴ��Ѿ��ɼ�����ˮ'
      Anchors = [akTop, akRight]
      Caption = '�ϴ���ˮ(&U)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnUploadClick
    end
    object mmoList: TMemo
      Left = 304
      Top = 16
      Width = 185
      Height = 89
      Lines.Strings = (
        'mmoList')
      TabOrder = 5
      Visible = False
    end
    object pb1: TProgressBar
      Left = 0
      Top = 40
      Width = 700
      Height = 17
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 6
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
        Caption = '������'
        Width = 120
      end
      item
        Caption = '����ʱ��'
        Width = 150
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
        DataField = '@Return'
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
        DataField = 'vsmess'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|������|�豸���|����Ա��|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�ֳֻ�������ˮ�ɼ�'
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
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
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
  object dlgSave1: TSaveDialog
    Left = 312
    Top = 224
  end
end
