inherited faqhPASMCard: TfaqhPASMCard
  Width = 626
  Height = 416
  inherited UIPanel1: TUIPanel
    Top = 365
    Width = 626
    Height = 51
    inherited btnQuery: TBitBtn
      Left = 526
      Top = 35
      Width = 94
      Hint = '������Ȩ��'
      Caption = '������Ȩ��'
      TabOrder = 1
      Visible = False
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 352
      Top = 43
      TabOrder = 2
      Visible = False
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 30
      Width = 626
      Height = 21
      AutoStyle = False
      BorderColor = clWindow
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      Color = 16184303
      FlatColor = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 626
        Height = 21
        FrameStyle = fsStatus
        Align = alClient
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 626
    inherited Image1: TImage
      Width = 626
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 626
    Height = 347
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object grp1: TGroupBox
      Left = 184
      Top = 72
      Width = 401
      Height = 161
      Caption = 'PSAM����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label2: TLabel
        Left = 295
        Top = 96
        Width = 84
        Height = 14
        Caption = '��ʽyyyymmdd'
        Font.Charset = GB2312_CHARSET
        Font.Color = clMaroon
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object RzStatusPane2: TRzStatusPane
        Left = 13
        Top = 58
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��������'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 90
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��Ч����'
      end
      object lbl1: TLabel
        Left = 295
        Top = 64
        Width = 84
        Height = 14
        Caption = '��ʽyyyymmdd'
        Font.Charset = GB2312_CHARSET
        Font.Color = clMaroon
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object rzstspn1: TRzStatusPane
        Left = 13
        Top = 26
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'PSAM������'
      end
      object rzstspn3: TRzStatusPane
        Left = 13
        Top = 122
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�豸ʹ�÷�'
      end
      object edtLimitDate: TRzEdit
        Left = 136
        Top = 91
        Width = 153
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        MaxLength = 8
        ParentFont = False
        TabOrder = 2
      end
      object edtBeginDate: TRzEdit
        Left = 136
        Top = 59
        Width = 153
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        MaxLength = 8
        ParentFont = False
        TabOrder = 1
      end
      object cbbUser: TWVComboBox
        Left = 136
        Top = 124
        Width = 155
        Height = 22
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 14
        TabOrder = 3
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '152'
      end
      object cbbCardType: TWVComboBox
        Left = 136
        Top = 28
        Width = 155
        Height = 22
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 14
        TabOrder = 0
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*150'
      end
    end
    object btnPubAuth: TBitBtn
      Left = 491
      Top = 251
      Width = 94
      Height = 25
      Hint = '������Ȩ��'
      Caption = 'PSAM������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnPubAuthClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 624
    Top = 416
    Width = 76
    Height = 22
    Align = alNone
    TabOrder = 3
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      DataSource = nil
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '���׿���'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Caption = '����Ա��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Caption = '��Ч��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '��Ȩ��λ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Caption = '������Կ'
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
        Name = '��Ч����'
        Caption = '��Ч����'
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
        Name = '�豸ʹ�÷�'
        Caption = '�豸ʹ�÷�'
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
        Name = '������־'
        Caption = '������־'
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
        Name = 'pasm����'
        Caption = 'pasm����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'Lvol0'
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
        DataField = 'lvol5'
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
        DataField = 'Sserial0'
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
        DataField = 'lsafe_level'
      end
      item
        Name = '���з���ʶ'
        Caption = '���з���ʶ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sholder_ac_no'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|����Ա��|������|��Ȩ��Ȩ��|ҵ�����Ա|��Ч��|'
      end>
    Left = 52
    Top = 55
  end
  inherited MainRequest: TWVRequest
    ID = 'PASM������'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��Ч����'
        FieldName = '��Ч����'
      end
      item
        ParamName = '�豸ʹ�÷�'
        FieldName = '�豸ʹ�÷�'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = 'pasm����'
        FieldName = 'pasm����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdBiDirection
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '���з���ʶ'
        FieldName = '���з���ʶ'
        Direction = bdParam2Field
      end>
    Left = 88
    Top = 56
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 88
    Top = 96
  end
  inherited DataSource: TDataSource
    Left = 128
    Top = 96
  end
end
