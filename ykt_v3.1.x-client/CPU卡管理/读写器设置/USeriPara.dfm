inherited faMachinePara: TfaMachinePara
  Width = 773
  Height = 629
  inherited UIPanel1: TUIPanel
    Top = 18
    Width = 773
    Height = 611
    Align = alClient
    Color = 16184303
    TabOrder = 1
    object WVLabel1: TWVLabel [0]
      Left = 101
      Top = 54
      Width = 70
      Height = 14
      Caption = '�豸������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object lblOper: TLabel [1]
      Left = 16
      Top = 1000
      Width = 42
      Height = 12
      Caption = 'lblOper'
      Visible = False
    end
    object WVLabel2: TWVLabel [2]
      Left = 101
      Top = 26
      Width = 70
      Height = 14
      Caption = '������汾'
      Font.Charset = GB2312_CHARSET
      Font.Color = clNavy
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object lblVer: TWVLabel [3]
      Left = 181
      Top = 26
      Width = 484
      Height = 14
      AutoSize = False
      Caption = 'ver'
      Font.Charset = GB2312_CHARSET
      Font.Color = clNavy
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object WVLabel3: TWVLabel [4]
      Left = 301
      Top = 54
      Width = 60
      Height = 14
      AutoSize = False
      Caption = 'PSAM����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    inherited btnOK: TBitBtn
      Left = 24
      Top = 1000
      TabOrder = 8
      Visible = False
    end
    inherited btnCancel: TBitBtn
      Left = 35
      Top = 1000
      TabOrder = 9
      Visible = False
    end
    object rgcom: TRadioGroup
      Left = 96
      Top = 74
      Width = 569
      Height = 37
      Caption = '����ѡ��'
      Columns = 5
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '����1'
        '����2'
        '����3'
        '����4'
        'USB��')
      ParentFont = False
      TabOrder = 3
    end
    object grpCardInfo: TGroupBox
      Left = 96
      Top = 166
      Width = 281
      Height = 363
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      object rzstspn2: TRzStatusPane
        Left = 8
        Top = 17
        Width = 96
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
      object RzStatusPane1: TRzStatusPane
        Left = 8
        Top = 45
        Width = 96
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
      object RzStatusPane2: TRzStatusPane
        Left = 8
        Top = 74
        Width = 96
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
      object RzStatusPane16: TRzStatusPane
        Left = 8
        Top = 102
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���汾��'
      end
      object RzStatusPane17: TRzStatusPane
        Left = 8
        Top = 131
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�� ״ ̬'
      end
      object RzStatusPane18: TRzStatusPane
        Left = 8
        Top = 188
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'Ǯ�����'
      end
      object RzStatusPane20: TRzStatusPane
        Left = 8
        Top = 216
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ֵ����'
      end
      object RzStatusPane23: TRzStatusPane
        Left = 8
        Top = 245
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���Ѵ���'
      end
      object RzStatusPane7: TRzStatusPane
        Left = 8
        Top = 274
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�����޶�'
      end
      object RzStatusPane8: TRzStatusPane
        Left = 8
        Top = 302
        Width = 96
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
      object rzstspn6: TRzStatusPane
        Left = 8
        Top = 159
        Width = 96
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
      object RzStatusPane21: TRzStatusPane
        Left = 8
        Top = 330
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���������'
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
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtCardNo: TRzEdit
        Left = 112
        Top = 46
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtShowNo: TRzEdit
        Left = 112
        Top = 75
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtVerNo: TRzEdit
        Left = 112
        Top = 103
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtBalack: TRzEdit
        Left = 112
        Top = 132
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
        Left = 112
        Top = 189
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
      object edtTreadeNum: TRzEdit
        Left = 112
        Top = 217
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 7
      end
      object edtPayCnt: TRzEdit
        Left = 112
        Top = 246
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 8
      end
      object edtMaxPerCount: TRzEdit
        Left = 112
        Top = 275
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 9
      end
      object edtmaxPerDay: TRzEdit
        Left = 112
        Top = 303
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 10
      end
      object edtCardType: TRzEdit
        Left = 112
        Top = 160
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtTradeDate: TRzEdit
        Left = 112
        Top = 331
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 11
      end
    end
    object cbbBit: TRzComboBox
      Left = 181
      Top = 50
      Width = 100
      Height = 20
      Ctl3D = False
      FrameVisible = True
      ItemHeight = 12
      ParentCtl3D = False
      TabOrder = 1
      Items.Strings = (
        '19200'
        '600'
        '1200'
        '2400'
        '4800'
        '9600'
        '14400'
        '57600')
    end
    object stat1: TRzStatusBar
      Left = 0
      Top = 592
      Width = 773
      Height = 19
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      TabOrder = 7
      object rzstspn1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 1000
        Height = 19
        Align = alLeft
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object grpOper: TGroupBox
      Left = 96
      Top = 113
      Width = 569
      Height = 52
      Caption = '��������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      object btnOpen: TBitBtn
        Left = 9
        Top = 20
        Width = 120
        Height = 25
        Hint = '�ֶ���ʼ������д�豸'
        Caption = '�򿪴���(&O)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
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
      object btnClose: TBitBtn
        Left = 434
        Top = 20
        Width = 120
        Height = 25
        Hint = '�ֶ��رն�д������'
        Caption = '�رմ���(&C)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
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
        Left = 153
        Top = 20
        Width = 120
        Height = 25
        Hint = '��ȡ����Ϣ'
        Caption = '��ȡ����Ϣ(&R)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
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
      object btnKey: TBitBtn
        Left = 297
        Top = 19
        Width = 113
        Height = 25
        Hint = '������Ȩ��'
        Caption = '��ȡ��Կ��(&A)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnKeyClick
      end
    end
    object grpCustInfo: TGroupBox
      Left = 384
      Top = 166
      Width = 280
      Height = 363
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      object RzStatusPane14: TRzStatusPane
        Left = 8
        Top = 245
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�շ����'
      end
      object RzStatusPane13: TRzStatusPane
        Left = 8
        Top = 273
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�ͻ����'
      end
      object RzStatusPane12: TRzStatusPane
        Left = 8
        Top = 216
        Width = 96
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
      object RzStatusPane10: TRzStatusPane
        Left = 8
        Top = 188
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '֤������'
      end
      object RzStatusPane6: TRzStatusPane
        Left = 8
        Top = 131
        Width = 96
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
      object RzStatusPane5: TRzStatusPane
        Left = 8
        Top = 103
        Width = 96
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
      object RzStatusPane4: TRzStatusPane
        Left = 8
        Top = 74
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ѧ/�� ��'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 8
        Top = 17
        Width = 96
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
      object RzStatusPane15: TRzStatusPane
        Left = 8
        Top = 330
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ֹ����'
      end
      object rzstspn3: TRzStatusPane
        Left = 8
        Top = 160
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '֤������'
      end
      object rzstspn5: TRzStatusPane
        Left = 8
        Top = 46
        Width = 96
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
      object rzstspn7: TRzStatusPane
        Left = 8
        Top = 302
        Width = 96
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
      object edtStuempNo: TRzEdit
        Left = 112
        Top = 74
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtName: TRzEdit
        Left = 112
        Top = 103
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtSex: TRzEdit
        Left = 112
        Top = 131
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtIDCard: TRzEdit
        Left = 112
        Top = 188
        Width = 154
        Height = 22
        Text = '999999999999999999999'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
      object edtFeeType: TRzEdit
        Left = 112
        Top = 245
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 8
      end
      object edtDept: TRzEdit
        Left = 112
        Top = 217
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 7
      end
      object edtCustType: TRzEdit
        Left = 112
        Top = 274
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 9
      end
      object edtEndDate: TRzEdit
        Left = 112
        Top = 330
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 11
      end
      object edtPatchNo: TRzEdit
        Left = 112
        Top = 17
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtCertType: TRzEdit
        Left = 112
        Top = 160
        Width = 154
        Height = 22
        Text = '999999999999999999999'
        CharCase = ecUpperCase
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
      object edtCustId: TRzEdit
        Left = 112
        Top = 46
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
      object edtStartDate: TRzEdit
        Left = 112
        Top = 302
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 10
      end
    end
    object cbbpasmSeat: TComboBox
      Left = 360
      Top = 50
      Width = 105
      Height = 22
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 14
      ParentFont = False
      TabOrder = 2
      Items.Strings = (
        'SAM1'
        'SAM2'
        'SAM3')
    end
    object btnSetPasm: TBitBtn
      Left = 474
      Top = 48
      Width = 103
      Height = 25
      Hint = '���ÿ���'
      Caption = '����PSAM����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnSetPasmClick
    end
    object grp1: TGroupBox
      Left = 96
      Top = 528
      Width = 569
      Height = 41
      TabOrder = 10
      object RzStatusPane9: TRzStatusPane
        Left = 8
        Top = 10
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ϵͳ��״̬'
      end
      object RzStatusPane11: TRzStatusPane
        Left = 296
        Top = 10
        Width = 96
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ϵͳ�����'
      end
      object edtLibStat: TRzEdit
        Left = 112
        Top = 11
        Width = 154
        Height = 22
        CharCase = ecUpperCase
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
      object edtAccMoney: TRzEdit
        Left = 400
        Top = 10
        Width = 154
        Height = 22
        Text = '08AHGD2134'
        CharCase = ecUpperCase
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
  end
  object UIPnlQueryCount: TUIPanel [1]
    Left = 0
    Top = 0
    Width = 773
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
      end
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '����Ա����'
        Caption = '����Ա����'
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
        Name = '������'
        Caption = '������'
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
        Name = '״̬'
        Caption = '״̬'
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
        MonitorValueChangedFields = '|���׿���|����Ա����|������|״̬|'
      end>
    Left = 612
    Top = 23
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '��Ȩ������'
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
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end>
    AfterExec = MainRequestAfterExec
    Left = 648
    Top = 24
  end
  object WorkView2: TWorkView
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
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = '@Dataset'
      end
      item
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        GetPrevChar = '*'
      end
      item
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
        Name = '����'
        Caption = '����'
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
        Name = '֤������'
        Caption = '֤������'
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
        Name = '֤������'
        Caption = '֤������'
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
        Name = '�ͻ����'
        Caption = '�ͻ����'
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
        Name = '�շ����'
        Caption = '�շ����'
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
        Name = '��ʾ����'
        Caption = '��ʾ����'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        Name = 'ע������'
        Caption = 'ע������'
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
        Name = '����'
        Caption = '����'
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
      end
      item
        Name = 'Ǯ����'
        Caption = 'Ǯ����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol3'
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
      end
      item
        Name = '��״̬'
        Caption = '��״̬'
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
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
      end>
    Left = 404
    Top = 31
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�ѿ����ͻ���Ϣ��ѯ'
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
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = 'ע������'
        FieldName = 'ע������'
      end
      item
        ParamName = '��ʾ����'
        FieldName = '��ʾ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��״̬'
        FieldName = '��״̬'
      end>
    AfterExec = MainRequestAfterExec
    Left = 440
    Top = 32
  end
end
