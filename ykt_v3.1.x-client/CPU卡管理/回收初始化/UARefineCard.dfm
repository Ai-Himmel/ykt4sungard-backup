inherited faRefineCard: TfaRefineCard
  Width = 648
  Height = 459
  inherited UIPanel1: TUIPanel
    Top = 18
    Width = 648
    Height = 441
    Align = alClient
    Color = 16184303
    TabOrder = 1
    object RzStatusPane2: TRzStatusPane [0]
      Left = 0
      Top = 420
      Width = 648
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
      Left = 96
      Top = 1000
      Width = 73
      Height = 20
      Hint = '�޸�����'
      Caption = '�޸Ŀ�����'
      Enabled = False
      TabOrder = 3
      Visible = False
    end
    inherited btnCancel: TBitBtn
      Left = 14
      Top = 1000
      TabOrder = 2
      Visible = False
    end
    object btnRecycle: TButton
      Left = 432
      Top = 159
      Width = 111
      Height = 25
      Caption = '��Ƭ����(&C)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnRecycleClick
    end
    object grp1: TGroupBox
      Left = 184
      Top = 72
      Width = 361
      Height = 81
      Caption = '���տ���Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
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
        Caption = '��ʾ����'
      end
      object edtShowCardNo: TRzEdit
        Left = 136
        Top = 27
        Width = 153
        Height = 22
        BiDiMode = bdLeftToRight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        MaxLength = 20
        ParentBiDiMode = False
        ParentFont = False
        TabOrder = 0
      end
      object chkTip: TCheckBox
        Left = 136
        Top = 56
        Width = 169
        Height = 17
        Caption = '����ʱ��ʾ��ʾ��Ϣ'
        Checked = True
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        State = cbChecked
        TabOrder = 1
      end
    end
  end
  object UIPnlQueryCount: TUIPanel [1]
    Left = 0
    Top = 0
    Width = 648
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
    object LabRecordCount: TLabel
      Left = 16
      Top = 4
      Width = 393
      Height = 12
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '����ʶ'
        Caption = '����ʶ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no'
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
      end>
    Left = 16
    Top = 272
  end
  inherited MainRequest: TWVRequest
    ID = '�޸Ŀ�����'
    Bindings = <
      item
        ParamName = '����ʶ'
        FieldName = '����ʶ'
      end
      item
        ParamName = '������'
        FieldName = '������'
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
      end>
    Left = 48
    Top = 272
  end
end
