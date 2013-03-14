inherited faRecycleCard: TfaRecycleCard
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
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    object lbl1: TLabel [1]
      Left = 184
      Top = 72
      Width = 196
      Height = 42
      Caption = '提示：'#13#10#13#10'该功能是把卡片回收成出厂状态'
      Font.Charset = GB2312_CHARSET
      Font.Color = clRed
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    inherited btnOK: TBitBtn
      Left = 96
      Top = 1000
      Width = 73
      Height = 20
      Hint = '修改密码'
      Caption = '修改卡密码'
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
      Top = 207
      Width = 111
      Height = 25
      Caption = '卡片回收(&C)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnRecycleClick
    end
    object chkTip: TCheckBox
      Left = 184
      Top = 128
      Width = 97
      Height = 17
      Caption = '回收前提示'
      Checked = True
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 0
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
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    StyleItemName = '操作界面的外围背景'
    object LabRecordCount: TLabel
      Left = 16
      Top = 4
      Width = 393
      Height = 12
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '卡标识'
        Caption = '卡标识'
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
        Name = '新密码'
        Caption = '新密码'
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
        Name = '返回码'
        Caption = '返回码'
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
        Name = '返回信息'
        Caption = '返回信息'
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
    ID = '修改卡密码'
    Bindings = <
      item
        ParamName = '卡标识'
        FieldName = '卡标识'
      end
      item
        ParamName = '新密码'
        FieldName = '新密码'
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end>
    Left = 48
    Top = 272
  end
end
