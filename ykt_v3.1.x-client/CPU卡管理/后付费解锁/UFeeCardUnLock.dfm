inherited faFeeCardUnlock: TfaFeeCardUnlock
  Width = 731
  Height = 473
  inherited UIPanel1: TUIPanel
    Top = 18
    Width = 731
    Height = 455
    Align = alClient
    Color = 16184303
    TabOrder = 1
    object RzStatusPane2: TRzStatusPane [0]
      Left = 0
      Top = 434
      Width = 731
      Height = 21
      FrameStyle = fsStatus
      Align = alBottom
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    inherited btnOK: TBitBtn
      Left = 88
      Top = 1000
      Enabled = False
      TabOrder = 4
      Visible = False
    end
    inherited btnCancel: TBitBtn
      Left = 8
      Top = 1000
      TabOrder = 3
      Visible = False
    end
    object btnReadCardInfo: TBitBtn
      Left = 352
      Top = 307
      Width = 113
      Height = 25
      Hint = '��ȡ����Ϣ'
      Caption = '������Ϣ(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnReadCardInfoClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FF000000FFFFFF00FFFFFF007B7B
        7B007B7B7B007B7B7B00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FFFFFF00FFFFFF00FFFFFF007B7B
        7B007B7B7B007B7B7B007B7B7B00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FF000000FFFFFF00FFFFFF007B7B
        7B007B7B7B007B7B7B00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FFFFFF00FFFFFF00FFFFFF007B7B
        7B007B7B7B00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FF000000FF000000FFFFFF007B7B
        7B007B7B7B007B7B7B00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00000000000000000000000000FFFFFF00FFFFFF00FFFFFF000000
        00000000000000000000FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
        7B007B7B7B007B7B7B007B7B7B007B7B7B0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    object btnMoneyOut: TBitBtn
      Left = 476
      Top = 307
      Width = 108
      Height = 25
      Hint = 'У԰�����֧ȡ'
      Caption = '�� ��(&O)'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnMoneyOutClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B0000000000000000000000
        0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00BDBDBD00BDBDBD00BDBD
        BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD0000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00BDBDBD0000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFFFFF00BDBDBD007B7B
        7B007B7B7B007B7B7B007B7B7B00FFFFFF00BDBDBD00000000007B7B7B000000
        0000000000000000000000000000000000007B7B7B00FFFFFF0000007B00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00BDBDBD00000000007B7B7B00BDBD
        BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD007B7B7B00FFFFFF0000007B000000
        7B00BDBDBD007B7B7B007B7B7B00FFFFFF00BDBDBD00000000007B7B7B00FFFF
        FF00FFFFFF0000007B0000007B0000007B0000007B0000007B0000007B000000
        7B0000007B00FFFFFF00FFFFFF00FFFFFF00BDBDBD00000000007B7B7B00FFFF
        FF007B7B7B0000007B0000007B0000007B0000007B0000007B0000007B000000
        7B0000007B00FFFFFF00FFFFFF00FFFFFF00BDBDBD00000000007B7B7B00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFFFFF0000007B000000
        7B00FFFFFF00FFFFFF00000000000000000000000000000000007B7B7B00FFFF
        FF007B7B7B007B7B7B007B7B7B00FFFFFF007B7B7B00FFFFFF0000007B00BDBD
        BD007B7B7B00FFFFFF007B7B7B00FFFFFF0000000000FFFFFF007B7B7B00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF007B7B7B0000000000FFFFFF00FFFFFF007B7B7B00FFFF
        FF007B7B7B007B7B7B007B7B7B00FFFFFF007B7B7B007B7B7B007B7B7B007B7B
        7B007B7B7B007B7B7B007B7B7B00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
        0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFFF
        FF007B7B7B007B7B7B007B7B7B00FFFFFF007B7B7B00FFFFFF0000000000FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B0000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B007B7B
        7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    object grp1: TGroupBox
      Left = 184
      Top = 72
      Width = 401
      Height = 217
      Caption = '����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object WVLabel5: TWVLabel
        Left = 300
        Top = 120
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object WVLabel10: TWVLabel
        Left = 300
        Top = 152
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object RzStatusPane1: TRzStatusPane
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
        Caption = '��    ��'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 56
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
        Caption = '���׿���'
      end
      object RzStatusPane4: TRzStatusPane
        Left = 13
        Top = 86
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
        Caption = 'ѧ/����'
      end
      object RzStatusPane5: TRzStatusPane
        Left = 13
        Top = 116
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
        Caption = '�ۿ�ǰ���'
      end
      object RzStatusPane6: TRzStatusPane
        Left = 13
        Top = 146
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
        Caption = '�ۿ�����'
      end
      object RzStatusPane7: TRzStatusPane
        Left = 13
        Top = 177
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
        Caption = '�ۿ���'
      end
      object lbl1: TWVLabel
        Left = 300
        Top = 184
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtName: TRzEdit
        Left = 132
        Top = 27
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtCardNo: TRzEdit
        Left = 132
        Top = 57
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtStuempNo: TRzEdit
        Left = 132
        Top = 87
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edtCardMoney: TRzEdit
        Left = 132
        Top = 117
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object edtAfterMoney: TRzEdit
        Left = 132
        Top = 147
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object edtMoney: TRzEdit
        Left = 132
        Top = 179
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
    end
  end
  object UIPnlQueryCount: TUIPanel [1]
    Left = 0
    Top = 0
    Width = 731
    Height = 18
    Align = alTop
    BevelOuter = bvNone
    Color = 15458000
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '����'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    StyleItemName = '�����������Χ����'
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
        Name = '�뿨���'
        Caption = '�뿨���'
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
        Name = '�����豸'
        Caption = '�����豸'
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
      end
      item
        Name = 'ҵ������'
        Caption = 'ҵ������'
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
        Name = 'ҵ��ʱ��'
        Caption = 'ҵ��ʱ��'
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
        Name = '�ۿ���'
        Caption = '�ۿ���'
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    Left = 536
    Top = 32
  end
  inherited MainRequest: TWVRequest
    ID = '�󸶷ѽ���'
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
        ParamName = '����'
        FieldName = '����'
        Direction = bdBiDirection
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '���Ѵ���'
        FieldName = '���Ѵ���'
      end
      item
        ParamName = '�뿨���'
        FieldName = '�뿨���'
      end
      item
        ParamName = '�����豸'
        FieldName = '�����豸'
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
        ParamName = '�������'
        FieldName = '�������'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'ҵ��ʱ��'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ۿ���'
        FieldName = '�ۿ���'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 584
    Top = 32
  end
  object DataSource1: TDataSource
    Left = 664
    Top = 32
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView
    FieldName = '��ѯ�����'
    Bindings = <>
    HideUnbindingFields = False
    Left = 624
    Top = 32
  end
  object WVcashOperCancel: TWorkView
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
        DataField = 'vsmess'
      end
      item
        Name = 'ҵ������'
        Caption = 'ҵ������'
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
      end
      item
        Name = '�ն˱��'
        Caption = '�ն˱��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 584
    Top = 72
  end
  object WVRcashOperCancel: TWVRequest
    WorkView = WVcashOperCancel
    ID = '��ֵ֧ȡ����'
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
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
      end>
    AfterExec = MainRequestAfterExec
    Left = 624
    Top = 72
  end
end
