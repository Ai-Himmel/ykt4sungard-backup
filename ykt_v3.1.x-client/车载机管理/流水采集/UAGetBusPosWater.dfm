inherited faqhGetBusPosWater: TfaqhGetBusPosWater
  Width = 828
  Height = 504
  inherited UIPanel1: TUIPanel
    Top = 504
    Width = 828
    Height = 0
    TabOrder = 4
    object Label4: TLabel [0]
      Left = 13
      Top = 11
      Width = 9
      Height = 16
      Font.Charset = GB2312_CHARSET
      Font.Color = clRed
      Font.Height = -16
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 641
      Top = 5
      Hint = ''
    end
    inherited btnPrint: TBitBtn
      Left = 726
      Top = 5
      Hint = ''
      Enabled = True
    end
    object ImageButton1: TImageButton
      Left = 752
      Top = 11
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'ȷ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = ImageButton1Click
      CommandName = '��ѯ'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 828
    Height = 16
    TabOrder = 0
    inherited Image1: TImage
      Width = 828
      Height = 16
    end
    inherited LabRecordCount: TLabel
      Left = 12
      Width = 481
      Font.Color = clBlue
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 16
    Width = 828
    Height = 0
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label2: TLabel
      Left = 531
      Top = 58
      Width = 72
      Height = 12
      Caption = '�Ƿ񽻴���'
      Visible = False
    end
    object WVLabel1: TWVLabel
      Left = 40
      Top = 58
      Width = 108
      Height = 12
      Caption = '��һ����ȡ���ɱ���'
      Visible = False
    end
    object WVLabel2: TWVLabel
      Left = 295
      Top = 58
      Width = 84
      Height = 12
      Caption = '�Ƿ��˿��ɱ���'
      Visible = False
    end
    object WVComboBox1: TWVComboBox
      Left = 615
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      Visible = False
      WorkView = WorkView
      FieldName = '�Ƿ񽻴���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox2: TWVComboBox
      Left = 159
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      Visible = False
      WorkView = WorkView
      FieldName = '��һ���Ƿ���ȡ���ɱ���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox3: TWVComboBox
      Left = 391
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      Visible = False
      WorkView = WorkView
      FieldName = '�Ƿ��˿��ɱ���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 16
    Width = 828
    Height = 488
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 828
      Height = 488
    end
  end
  object Panel2: TPanel [4]
    Left = 0
    Top = 16
    Width = 828
    Height = 488
    Align = alClient
    Color = 16184303
    TabOrder = 1
    object Panel4: TPanel
      Left = 1
      Top = 434
      Width = 826
      Height = 53
      Align = alBottom
      Color = 16184303
      TabOrder = 1
      object Label3: TLabel
        Left = 8
        Top = 14
        Width = 84
        Height = 14
        Caption = 'ѡ����ˮ�ļ�'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtFile: TEdit
        Left = 96
        Top = 10
        Width = 369
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object btnOpenfile: TImageButton
        Left = 571
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '���ļ�'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btnOpenfileClick
      end
      object btnAnaSerial: TImageButton
        Left = 655
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '������ˮ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnAnaSerialClick
      end
      object btngetSerial: TImageButton
        Left = 488
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '��ȡ��ˮ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btngetSerialClick
      end
      object btnTrans: TImageButton
        Left = 738
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '�ϴ���ˮ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnTransClick
      end
    end
    object ListView1: TListView
      Left = 1
      Top = 1
      Width = 826
      Height = 433
      Align = alClient
      Columns = <
        item
          Caption = '����ID��'
          Width = 80
        end
        item
          Caption = '��ˮ��'
          Width = 56
        end
        item
          Caption = '���׿���'
          Width = 100
        end
        item
          Alignment = taRightJustify
          Caption = '�뿨���'
          Width = 60
        end
        item
          Alignment = taRightJustify
          Caption = '���׽��'
          Width = 60
        end
        item
          Alignment = taRightJustify
          Caption = '�������'
          Width = 61
        end
        item
          Caption = '���н��״���'
          Width = 100
        end
        item
          Caption = '��������'
          Width = 80
        end
        item
          Caption = '����ʱ��'
          Width = 80
        end
        item
          Caption = '���ױ�־'
          Width = 100
        end
        item
          Caption = '��������'
          Width = 60
        end
        item
          Caption = 'Ǯ����'
          Width = 51
        end
        item
          Caption = 'CRC'
          Width = 60
        end>
      GridLines = True
      RowSelect = True
      TabOrder = 0
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
        Name = '�ͻ��������'
        Caption = '�ͻ��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�Ƿ񽻴���'
        Caption = '�Ƿ񽻴���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '���ѷ���'
        Caption = '���ѷ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ʽ����Ч��'
        Caption = '��ʽ����Ч��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'Ѻ����'
        Caption = 'Ѻ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '���ɱ���'
        Caption = '���ɱ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
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
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��һ���Ƿ���ȡ���ɱ���'
        Caption = '��һ���Ƿ���ȡ���ɱ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�Ƿ��˿��ɱ���'
        Caption = '�Ƿ��˿��ɱ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�˻�������'
        Caption = '�˻�������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end>
    Left = 108
    Top = 487
  end
  inherited MainRequest: TWVRequest
    ID = '�ͻ�����������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ��������'
        FieldName = '�ͻ��������'
      end
      item
        ParamName = '�Ƿ񽻴���'
        FieldName = '�Ƿ񽻴���'
      end
      item
        ParamName = '���ѷ���'
        FieldName = '���ѷ���'
      end
      item
        ParamName = '��ʽ����Ч��'
        FieldName = '��ʽ����Ч��'
      end
      item
        ParamName = 'Ѻ����'
        FieldName = 'Ѻ����'
      end
      item
        ParamName = '���ɱ���'
        FieldName = '���ɱ���'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��һ���Ƿ���ȡ���ɱ���'
        FieldName = '��һ���Ƿ���ȡ���ɱ���'
      end
      item
        ParamName = '�Ƿ��˿��ɱ���'
        FieldName = '�Ƿ��˿��ɱ���'
      end
      item
        ParamName = '�˻�������'
        FieldName = '�˻�������'
      end>
    Left = 152
    Top = 496
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end>
    Left = 200
    Top = 496
  end
  inherited DataSource: TDataSource
    Left = 336
    Top = 496
  end
  object SaveDialog1: TSaveDialog
    Filter = '�ı��ļ�|*.txt'
    Title = '��Ч��ˮ����'
    Left = 272
    Top = 496
  end
  object OpenDialog1: TOpenDialog
    Filter = '���ػ���ˮ�ļ�(*.bps)|*.bps'
    Left = 272
    Top = 368
  end
  object upwaterdata: TWorkView
    WorkFields = <
      item
        Name = '��ˮ��'
        Caption = '��ˮ��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '���׿���'
        Caption = '���׿���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '����վ��ʾ'
        Caption = '����վ��ʾ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '�뿨���'
        Caption = '�뿨���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '�������'
        Caption = '�������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '���ѽ��'
        Caption = '���ѽ��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = 'Ǯ��'
        Caption = 'Ǯ��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '���Ѵ���'
        Caption = '���Ѵ���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '���ױ�־'
        Caption = '���ױ�־'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
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
        DefaultValue = '0'
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
        Name = 'CRCУ����'
        Caption = 'CRCУ����'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = '������2'
        Caption = '������2'
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
        MonitorValueChangedFields = '|'
      end>
    Left = 236
    Top = 327
  end
  object WVRequest1: TWVRequest
    WorkView = upwaterdata
    ID = '�ϴ���ˮ'
    Bindings = <
      item
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
        DefaultValue = '0'
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
        DefaultValue = '0'
      end
      item
        ParamName = '����ID'
        FieldName = '������'
        DefaultValue = '0'
      end
      item
        ParamName = '����վ��ʾ'
        FieldName = '����վ��ʾ'
        DefaultValue = '0'
      end
      item
        ParamName = '�뿨���'
        FieldName = '�뿨���'
        DefaultValue = '0'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        DefaultValue = '0'
      end
      item
        ParamName = '���ѽ��'
        FieldName = '���ѽ��'
        DefaultValue = '0'
      end
      item
        ParamName = 'Ǯ��'
        FieldName = 'Ǯ��'
        DefaultValue = '0'
      end
      item
        ParamName = '���Ѵ���'
        FieldName = '���Ѵ���'
        DefaultValue = '0'
      end
      item
        ParamName = '���ױ�־'
        FieldName = '���ױ�־'
        DefaultValue = '0'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
        DefaultValue = '0'
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
        DefaultValue = '0'
      end
      item
        ParamName = 'CRCУ����'
        FieldName = 'CRCУ����'
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
        ParamName = '������2'
        FieldName = '������2'
      end>
    AfterExec = MainRequestAfterExec
    Left = 272
    Top = 328
  end
end
