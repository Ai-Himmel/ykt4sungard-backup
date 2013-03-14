inherited faMachinePara: TfaMachinePara
  Width = 758
  Height = 587
  inherited UIPanel1: TUIPanel
    Top = 18
    Width = 758
    Height = 569
    Align = alClient
    Color = 16184303
    TabOrder = 1
    object WVLabel1: TWVLabel [0]
      Left = 101
      Top = 86
      Width = 70
      Height = 14
      Caption = '设备波特率'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblOper: TLabel [1]
      Left = 16
      Top = 528
      Width = 42
      Height = 12
      Caption = 'lblOper'
      Visible = False
    end
    object WVLabel2: TWVLabel [2]
      Left = 101
      Top = 45
      Width = 70
      Height = 14
      Caption = '读卡库版本'
      Font.Charset = GB2312_CHARSET
      Font.Color = clNavy
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblVer: TWVLabel [3]
      Left = 181
      Top = 45
      Width = 484
      Height = 14
      AutoSize = False
      Caption = 'ver'
      Font.Charset = GB2312_CHARSET
      Font.Color = clNavy
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    inherited btnOK: TBitBtn
      Left = 9
      Top = 1000
      TabOrder = 6
      Visible = False
    end
    inherited btnCancel: TBitBtn
      Left = 12
      Top = 1000
      TabOrder = 7
      Visible = False
    end
    object rgcom: TRadioGroup
      Left = 296
      Top = 69
      Width = 369
      Height = 38
      Caption = '串口选择'
      Columns = 4
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '串口1'
        '串口2'
        '串口3'
        '串口4')
      ParentFont = False
      TabOrder = 0
    end
    object grpCardInfo: TGroupBox
      Left = 96
      Top = 182
      Width = 281
      Height = 355
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      object rzstspn2: TRzStatusPane
        Left = 16
        Top = 17
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '物理卡号'
      end
      object RzStatusPane1: TRzStatusPane
        Left = 16
        Top = 48
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '卡    号'
      end
      object RzStatusPane2: TRzStatusPane
        Left = 16
        Top = 79
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '显示卡号'
      end
      object RzStatusPane16: TRzStatusPane
        Left = 16
        Top = 109
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '卡版本号'
      end
      object RzStatusPane17: TRzStatusPane
        Left = 16
        Top = 140
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '是否黑卡'
      end
      object RzStatusPane18: TRzStatusPane
        Left = 16
        Top = 171
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '钱包余额'
      end
      object RzStatusPane20: TRzStatusPane
        Left = 16
        Top = 202
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '总交易次数'
      end
      object RzStatusPane23: TRzStatusPane
        Left = 16
        Top = 296
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '卡 密 码'
      end
      object RzStatusPane7: TRzStatusPane
        Left = 16
        Top = 234
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '单次限额'
      end
      object RzStatusPane8: TRzStatusPane
        Left = 16
        Top = 266
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '日限额'
      end
      object RzStatusPane9: TRzStatusPane
        Left = 16
        Top = 325
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '卡 状 态'
      end
      object edtPhyID: TRzEdit
        Left = 112
        Top = 18
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtCardNo: TRzEdit
        Left = 112
        Top = 49
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtShowNo: TRzEdit
        Left = 112
        Top = 80
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtVerNo: TRzEdit
        Left = 112
        Top = 110
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtBalack: TRzEdit
        Left = 112
        Top = 141
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object edtMoney: TRzEdit
        Left = 112
        Top = 172
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
      object edtTreadeNum: TRzEdit
        Left = 112
        Top = 203
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
      object edtPwd: TRzEdit
        Left = 112
        Top = 297
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        PasswordChar = '*'
        ReadOnly = True
        TabOrder = 9
      end
      object edtMaxPerCount: TRzEdit
        Left = 112
        Top = 235
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 7
      end
      object edtmaxPerDay: TRzEdit
        Left = 112
        Top = 267
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 8
      end
      object edtCardStatus: TRzEdit
        Left = 112
        Top = 326
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 10
      end
    end
    object cbbBit: TRzComboBox
      Left = 181
      Top = 82
      Width = 100
      Height = 20
      Ctl3D = False
      FrameVisible = True
      ItemHeight = 12
      ParentCtl3D = False
      TabOrder = 1
      Items.Strings = (
        '19200'
        '9600'
        '14400'
        '57600')
    end
    object stat1: TRzStatusBar
      Left = 0
      Top = 550
      Width = 758
      Height = 19
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      TabOrder = 5
      object rzstspn1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 1000
        Height = 19
        Align = alLeft
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object grpOper: TGroupBox
      Left = 96
      Top = 117
      Width = 569
      Height = 55
      Caption = '基本操作'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      object btnOpen: TBitBtn
        Left = 17
        Top = 20
        Width = 120
        Height = 25
        Hint = '手动初始化卡读写设备'
        Caption = '打开串口(&O)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnOpenClick
        Glyph.Data = {
          36040000424D3604000000000000360000002800000010000000100000000100
          2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF0031ADDE0031ADDE0031ADDE0031ADDE00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF0031ADDE00BDF7FF0094F7FF0084EFFF004AC6E7004AC6E7004AC6E70031AD
          DE0031ADDE0021ADDE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00BD848400BD8C
          8C00BD8C8C00BD8C8400BD8C8400BD8C8400BD8484009CFFFF0094F7FF008CEF
          FF007BE7F7004AC6E7004AC6E700FFFFFF00FFFFFF00FFFFFF00C6948C00EFD6
          BD00F7DEBD00EFCEAD00EFCE9C00EFCE9400E7BD94008CF7FF008CF7FF0094F7
          FF0094F7FF0094F7FF006BD6EF0031ADDE00FFFFFF00FFFFFF00CEA59400F7E7
          D600FFEFD600F7DEBD008CAD6B0073A563004A944200008C1000088C10000073
          080073DEDE008CF7FF0073D6EF0031ADDE00FFFFFF00FFFFFF00D6B59C00F7EF
          DE00FFEFDE00F7E7CE00F7DEBD00F7DEAD00EFC69C008C9C6300189C2100088C
          1000007308008CF7FF0073D6EF0084EFFF0031ADDE00FFFFFF00E7BDA500FFEF
          EF00FFF7F700FFEFDE00F7E7CE00F7E7BD00BDBD84009CB573002194290018AD
          29000073080063CEBD005AC6CE008CF7FF005AD6EF00FFFFFF00EFCEAD00FFF7
          EF00FFFFFF00FFF7EF00FFEFDE00FFEFD600297B2100188C210039BD5A0039C6
          5A0018A529000884100039A57B0094F7FF0094F7FF0031B5DE00F7CEAD00FFF7
          EF00FFFFFF00FFFFFF00FFEFE700DEBDB5009C8C7B00187B180042C66B0052E7
          8400189C2900006B000094DEEF00A5EFF700B5F7FF0052C6E700EFCEAD00FFF7
          F700FFFFFF00FFFFFF00F7EFF700C68C7B00D6AD9C00CED6B500218C290039BD
          5A000873080029ADD60031ADDE0031ADD60039B5DE0031ADDE00E7B59400EFCE
          B500EFD6C600EFD6C600E7C6B500DEB59C00FFFFFF00FFF7EF00A5C69400429C
          4200A59C840031ADDE0031ADDE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF0031ADDE00F7CEAD00FFFFFF00FFFFFF00FFFFFF00EFDEDE00BD8C
          8400B5848400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00EFBDA500FFF7F700FFF7F700FFFFF700E7CED600C68C
          7300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00DEAD8C00E7B59C00E7B59C00E7BD9C00DEB59400FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
      end
      object btnAuth: TBitBtn
        Left = 156
        Top = 20
        Width = 120
        Height = 25
        Hint = '读写器授权'
        Caption = '读写器授权(&A)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btnAuthClick
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
      object btnClose: TBitBtn
        Left = 433
        Top = 20
        Width = 120
        Height = 25
        Hint = '手动关闭读写器串口'
        Caption = '关闭串口(&C)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnCloseClick
        Glyph.Data = {
          36040000424D3604000000000000360000002800000010000000100000000100
          2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B
          7B00000000000000000000000000000000007B7B7B00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B000000
          000000000000000000000000000000000000000000007B7B7B00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000007B7B
          7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B7B00000000007B7B7B00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000FF0000007B00FFFF
          FF00FFFFFF000000FF000000FF000000FF000000FF0000007B00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000FF000000
          7B000000FF000000FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
          FF000000FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000
          FF000000FF000000FF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
          FF000000FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF000000
          0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000FF000000
          FF0000007B000000FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFF
          FF0000000000FFFFFF00FFFFFF000000FF000000FF000000FF000000FF000000
          7B00FFFFFF00FFFFFF000000FF000000FF000000FF0000007B00FFFFFF00FFFF
          FF007B7B7B00000000007B7B7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF007B7B7B00000000007B7B7B007B7B7B00FFFFFF00FFFFFF00FFFF
          FF007B7B7B0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF007B7B7B00000000000000000000000000000000000000
          0000000000007B7B7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
          FF00FFFFFF00FFFFFF00FFFFFF007B7B7B000000000000000000000000000000
          00007B7B7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
      end
      object btnReadCard: TBitBtn
        Left = 294
        Top = 20
        Width = 120
        Height = 25
        Hint = '读取卡信息'
        Caption = '读取卡信息(&R)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnReadCardClick
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
    end
    object grpCustInfo: TGroupBox
      Left = 384
      Top = 182
      Width = 280
      Height = 355
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      object RzStatusPane14: TRzStatusPane
        Left = 15
        Top = 234
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '收费类别'
      end
      object RzStatusPane13: TRzStatusPane
        Left = 15
        Top = 265
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '客户类别'
      end
      object RzStatusPane12: TRzStatusPane
        Left = 15
        Top = 203
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '所属部门'
      end
      object RzStatusPane10: TRzStatusPane
        Left = 15
        Top = 173
        Width = 90
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
      object RzStatusPane6: TRzStatusPane
        Left = 15
        Top = 142
        Width = 90
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
        Left = 15
        Top = 111
        Width = 90
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
      object RzStatusPane4: TRzStatusPane
        Left = 15
        Top = 80
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '学/工 号'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 15
        Top = 49
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '批 次 号'
      end
      object RzStatusPane15: TRzStatusPane
        Left = 16
        Top = 294
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '截止日期'
      end
      object RzStatusPane21: TRzStatusPane
        Left = 16
        Top = 17
        Width = 90
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '交易日期'
      end
      object edtStuempNo: TRzEdit
        Left = 112
        Top = 81
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtName: TRzEdit
        Left = 112
        Top = 112
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtSex: TRzEdit
        Left = 112
        Top = 143
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object edtIDCard: TRzEdit
        Left = 112
        Top = 174
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
      object edtFeeType: TRzEdit
        Left = 112
        Top = 235
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 7
      end
      object edtDept: TRzEdit
        Left = 112
        Top = 204
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
      object edtCustType: TRzEdit
        Left = 112
        Top = 266
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 8
      end
      object edtEndDate: TRzEdit
        Left = 112
        Top = 295
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 9
      end
      object edtPatchNo: TRzEdit
        Left = 112
        Top = 49
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtTradeDate: TRzEdit
        Left = 112
        Top = 18
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
    end
  end
  object UIPnlQueryCount: TUIPanel [1]
    Left = 0
    Top = 0
    Width = 758
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
    end
  end
  inherited WorkView: TWorkView
    Left = 520
    Top = 24
  end
  inherited MainRequest: TWVRequest
    Left = 552
    Top = 24
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '返回码'
        Caption = '返回码'
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
        Name = '返回信息'
        Caption = '返回信息'
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
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '交易卡号'
        Caption = '交易卡号'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '操作员代码'
        Caption = '操作员代码'
        FieldType = wftUndefined
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
        Name = '物理卡号'
        Caption = '物理卡号'
        FieldType = wftUndefined
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
        Name = '状态'
        Caption = '状态'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|交易卡号|操作员代码|物理卡号|状态|'
      end>
    Left = 596
    Top = 23
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '授权卡操作'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '操作员代码'
        FieldName = '操作员代码'
      end
      item
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end>
    AfterExec = MainRequestAfterExec
    Left = 648
    Top = 24
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '帐户信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '注销日期'
        FieldName = '注销日期'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '卡状态'
        FieldName = '卡状态'
      end>
    AfterExec = MainRequestAfterExec
    Left = 560
    Top = 64
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '客户号'
        Caption = '客户号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '学工号'
        Caption = '学工号'
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
        Name = '客户姓名'
        Caption = '客户姓名'
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
        Name = '部门'
        Caption = '部门'
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
        Name = '证件类型'
        Caption = '证件类型'
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
        Name = '证件号码'
        Caption = '证件号码'
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
        Name = '客户类别'
        Caption = '客户类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
      end
      item
        Name = '所属区域'
        Caption = '所属区域'
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
        Name = '显示卡号'
        Caption = '显示卡号'
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
        Name = '导入批次号'
        Caption = '导入批次号'
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
        Name = '注销日期'
        Caption = '注销日期'
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
        Name = '卡号'
        Caption = '卡号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
      end
      item
        Name = '钱包号'
        Caption = '钱包号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
      end
      item
        Name = '物理卡号'
        Caption = '物理卡号'
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
        Name = '卡状态'
        Caption = '卡状态'
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
        MonitorValueChangedFields = '|客户号|学工号|卡号|姓名|身份证号|'
      end>
    Left = 524
    Top = 63
  end
end
