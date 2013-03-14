inherited faChangeCardPwd: TfaChangeCardPwd
  Width = 648
  Height = 459
  inherited UIPanel1: TUIPanel
    Top = 18
    Width = 648
    Height = 441
    Align = alClient
    Color = 16184303
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
    inherited btnOK: TBitBtn
      Left = 16
      Top = 352
      Width = 73
      Height = 20
      Hint = '修改密码'
      Caption = '修改卡密码'
      Enabled = False
      Visible = False
    end
    inherited btnCancel: TBitBtn
      Left = 14
      Top = 381
      TabOrder = 5
      Visible = False
    end
    object GroupBox1: TGroupBox
      Left = 184
      Top = 72
      Width = 377
      Height = 153
      Caption = '卡信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object RzStatusPane4: TRzStatusPane
        Left = 13
        Top = 22
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '交易卡号'
      end
      object RzStatusPane1: TRzStatusPane
        Left = 13
        Top = 54
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '姓    名'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 86
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '性    别'
      end
      object RzStatusPane5: TRzStatusPane
        Left = 13
        Top = 118
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '证件号码'
      end
      object edtName: TRzEdit
        Left = 136
        Top = 55
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtCardNo: TRzEdit
        Left = 136
        Top = 23
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtSex: TRzEdit
        Left = 136
        Top = 87
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edtCert: TRzEdit
        Left = 136
        Top = 119
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
    end
    object GroupBox2: TGroupBox
      Left = 184
      Top = 240
      Width = 377
      Height = 121
      Caption = '修改密码'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      object RzStatusPane6: TRzStatusPane
        Left = 13
        Top = 25
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '旧密码*'
      end
      object RzStatusPane7: TRzStatusPane
        Left = 13
        Top = 57
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '新密码*'
      end
      object RzStatusPane8: TRzStatusPane
        Left = 13
        Top = 89
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '确认新密码*'
      end
      object edtOldPwd: TRzEdit
        Left = 136
        Top = 26
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        MaxLength = 6
        ParentFont = False
        PasswordChar = '*'
        TabOrder = 0
      end
      object edtNewPwd: TRzEdit
        Left = 136
        Top = 58
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        MaxLength = 6
        ParentFont = False
        PasswordChar = '*'
        TabOrder = 1
      end
      object edtVertPwd: TRzEdit
        Left = 136
        Top = 90
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        MaxLength = 6
        ParentFont = False
        PasswordChar = '*'
        TabOrder = 2
      end
    end
    object btnReadCardInfo: TBitBtn
      Left = 320
      Top = 371
      Width = 113
      Height = 25
      Hint = '读取卡信息'
      Caption = '读卡信息(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
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
    object btnEdPwd: TBitBtn
      Left = 448
      Top = 371
      Width = 112
      Height = 25
      Hint = '修改密码'
      Caption = '修改卡密码'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnEdPwdClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B7B7B007B7B7B0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF007B7B7B00FFF7FF00DEDEDE007B7B7B0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000737B0000000000FFFFFF00FFFF
        FF00FFFFFF007B7B7B00ADADAD007B7B7B0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0000737B0000F7FF0000000000FFFFFF00FFFF
        FF007B7B7B00FFF7FF00DEDEDE007B7B7B0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0000737B0000F7FF0000737B0000000000FFFFFF00FFFF
        FF00FFFFFF007B7B7B00BDB5BD006B6B6B0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF0000737B0000F7FF0000737B0000C6CE0000000000FFFFFF00FFFF
        FF007B7B7B00FFF7FF00DED6DE007B7B7B0000000000FFFFFF00FFFFFF00FFFF
        FF0000737B0000F7FF0000737B0000C6CE0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B7B7B00BDB5BD007B7B7B000000000000737B0000737B000073
        7B0000F7FF0000737B0000C6CE0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
        FF007B7B7B00DEDEDE00BDB5BD0000000000FFF7FF00FFF7FF00FFF7FF00FFF7
        FF0000737B0000C6CE0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B
        7B00DEDEDE00BDB5BD0000737B00FFF7FF0000F7FF0000C6CE0000C6CE00BDB5
        BD0000C6CE0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFF7
        FF00BDB5BD006B6B6B0000737B00FFF7FF00BDB5BD00BDB5BD0000F7FF0000C6
        CE0000737B0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFF7
        FF00DEDEDE007B7B7B007B7B7B00000000007B7B7B0000000000BDB5BD00BDB5
        BD0000737B0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFF7
        FF00DEDEDE00BDB5BD000000000000737B00FFF7FF0000737B0000C6CE0000C6
        CE0000737B0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B
        7B00FFF7FF00FFF7FF0000000000FFF7FF007B7B7B0000737B0000737B000073
        7B0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF007B7B7B007B7B7B00000000007B7B7B007B7B7B007B7B7B00000000000000
        0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
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
    TabOrder = 1
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
