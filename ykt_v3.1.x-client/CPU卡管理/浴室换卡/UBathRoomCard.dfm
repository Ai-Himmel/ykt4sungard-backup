inherited faBathRoomCard: TfaBathRoomCard
  Width = 836
  Height = 473
  inherited UIPanel1: TUIPanel
    Top = 18
    Width = 836
    Height = 455
    Align = alClient
    Color = 16184303
    TabOrder = 1
    object TipInfo: TRzStatusPane [0]
      Left = 0
      Top = 434
      Width = 836
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
      Left = 193
      Top = 1000
      Enabled = False
      TabOrder = 6
      Visible = False
    end
    inherited btnCancel: TBitBtn
      Left = 113
      Top = 1000
      TabOrder = 5
      Visible = False
    end
    object btnLock: TBitBtn
      Left = 184
      Top = 299
      Width = 113
      Height = 25
      Hint = '��ȡ����Ϣ'
      Caption = '�� �� ��(L)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnLockClick
    end
    object btnUnlock: TBitBtn
      Left = 308
      Top = 299
      Width = 108
      Height = 25
      Hint = 'У԰�����֧ȡ'
      Caption = '����/�ۿ�(K)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnUnlockClick
    end
    object grpCardInfo: TGroupBox
      Left = 72
      Top = 72
      Width = 345
      Height = 209
      Caption = '�ֻ�����Ϣ'
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
      object RzStatusPane7: TRzStatusPane
        Left = 13
        Top = 178
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
      object WVLabel1: TWVLabel
        Left = 300
        Top = 183
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
      object RzStatusPane2: TRzStatusPane
        Left = 13
        Top = 148
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
      object WVLabel2: TWVLabel
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
      object edtBeforeMoney: TRzEdit
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
      object edtmoney: TWVDigitalEdit
        Left = 133
        Top = 179
        Width = 160
        Height = 22
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 9
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 5
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '֧ȡ���'
        SynchronizeByValue = True
      end
      object edtAfterMoney: TRzEdit
        Left = 132
        Top = 149
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
    end
    object grp2: TGroupBox
      Left = 448
      Top = 72
      Width = 313
      Height = 209
      Caption = 'ϴԡ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object RzStatusPane8: TRzStatusPane
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
        Caption = '������'
      end
      object RzStatusPane9: TRzStatusPane
        Left = 13
        Top = 88
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
        Caption = '�� �� ��'
      end
      object RzStatusPane10: TRzStatusPane
        Left = 13
        Top = 120
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
        Caption = '���ý��'
      end
      object RzStatusPane11: TRzStatusPane
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
        Caption = '��    ��'
      end
      object edtBathCardPhyId: TRzEdit
        Left = 128
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
      object edtBathCardMoney: TRzEdit
        Left = 128
        Top = 89
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
      object edtSetMoney: TRzEdit
        Left = 128
        Top = 121
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
      object edtBathCardNO: TRzEdit
        Left = 128
        Top = 59
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
    end
    object btnSetMoney: TBitBtn
      Left = 632
      Top = 299
      Width = 128
      Height = 25
      Hint = 'У԰�����֧ȡ'
      Caption = '����/���ý��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnSetMoneyClick
    end
  end
  object UIPnlQueryCount: TUIPanel [1]
    Left = 0
    Top = 0
    Width = 836
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
        Name = '���״���'
        Caption = '���״���'
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
        Name = '��ֵ����'
        Caption = '��ֵ����'
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
        Name = '֧ȡ���'
        Caption = '֧ȡ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        Name = '�ն˱��'
        Caption = '�ն˱��'
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
      end>
    Left = 536
    Top = 32
  end
  inherited MainRequest: TWVRequest
    ID = '��֧ȡ'
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
        ParamName = '�뿨���'
        FieldName = '�뿨���'
      end
      item
        ParamName = '���״���'
        FieldName = '���״���'
      end
      item
        ParamName = '֧ȡ���'
        FieldName = '֧ȡ���'
      end
      item
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
        Direction = bdBiDirection
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'ҵ��ʱ��'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ֵ����'
        FieldName = '��ֵ����'
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
end
