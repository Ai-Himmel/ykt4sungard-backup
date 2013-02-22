object frmMain: TfrmMain
  Left = 204
  Top = 147
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #19978#20256#26356#26032
  ClientHeight = 432
  ClientWidth = 767
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 767
    Height = 413
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object pnl2: TPanel
      Left = 0
      Top = 0
      Width = 305
      Height = 413
      Align = alLeft
      TabOrder = 0
      object splleft: TSplitter
        Left = 1
        Top = 98
        Width = 303
        Height = 3
        Cursor = crVSplit
        Align = alTop
      end
      object lstDir: TListBox
        Left = 1
        Top = 1
        Width = 303
        Height = 97
        Align = alTop
        ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
        ItemHeight = 13
        TabOrder = 0
        OnClick = lstDirClick
      end
      object lstList: TListBox
        Left = 1
        Top = 101
        Width = 303
        Height = 311
        Align = alClient
        ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
        ItemHeight = 13
        TabOrder = 1
      end
    end
    object pnlright: TPanel
      Left = 305
      Top = 0
      Width = 462
      Height = 413
      Align = alClient
      TabOrder = 1
      object lblProgress: TLabel
        Left = 3
        Top = 306
        Width = 66
        Height = 12
        Caption = 'lblProgress'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object btnCreate: TButton
        Left = 10
        Top = 264
        Width = 89
        Height = 25
        Caption = #29983#25104#21152#23494#25991#20214
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        OnClick = btnCreateClick
      end
      object btnNew: TButton
        Left = 114
        Top = 264
        Width = 89
        Height = 25
        Caption = #26816#27979#26356#26032
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = btnNewClick
      end
      object btnUpLode: TButton
        Left = 216
        Top = 264
        Width = 89
        Height = 25
        Caption = #19978#20256#26356#26032
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = btnUpLodeClick
      end
      object btnExit: TButton
        Left = 363
        Top = 264
        Width = 89
        Height = 25
        Caption = #36864#20986#31995#32479
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = btnExitClick
      end
      object pnltop: TPanel
        Left = 1
        Top = 1
        Width = 460
        Height = 112
        Align = alTop
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 4
        object lbl1: TLabel
          Left = 13
          Top = 8
          Width = 153
          Height = 15
          AutoSize = False
          Caption = #26032#21152#23494#25991#20214#23384#25918#20301#32622
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlue
          Font.Height = -15
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
        end
        object lbl2: TLabel
          Left = 13
          Top = 56
          Width = 153
          Height = 15
          AutoSize = False
          Caption = #26087#21152#23494#25991#20214#23384#25918#20301#32622
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlue
          Font.Height = -15
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
        end
        object edtMd5: TEdit
          Left = 13
          Top = 32
          Width = 332
          Height = 19
          Ctl3D = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 0
        end
        object edtOldMd5: TEdit
          Left = 13
          Top = 80
          Width = 332
          Height = 19
          Ctl3D = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 1
        end
      end
      object lststatus: TListBox
        Left = 1
        Top = 344
        Width = 460
        Height = 68
        Align = alBottom
        ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
        ItemHeight = 13
        TabOrder = 5
      end
      object grpservice: TGroupBox
        Left = 1
        Top = 113
        Width = 460
        Height = 144
        Align = alTop
        Caption = #36830#25509'FTP'#26381#21153#22120
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        object lbl3: TLabel
          Left = 16
          Top = 24
          Width = 49
          Height = 13
          AutoSize = False
          Caption = #22320'  '#22336#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object lbl4: TLabel
          Left = 16
          Top = 72
          Width = 49
          Height = 13
          AutoSize = False
          Caption = #29992#25143#21517#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object lbl5: TLabel
          Left = 16
          Top = 96
          Width = 49
          Height = 13
          AutoSize = False
          Caption = #23494'  '#30721#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object lbl6: TLabel
          Left = 16
          Top = 48
          Width = 49
          Height = 13
          AutoSize = False
          Caption = #31471'  '#21475#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object Label6: TLabel
          Left = 16
          Top = 120
          Width = 53
          Height = 13
          Caption = #30446'  '#24405#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object SpeedButton2: TSpeedButton
          Left = 215
          Top = 115
          Width = 23
          Height = 22
          Hint = #25171#24320#30446#24405
          Flat = True
          Glyph.Data = {
            F6040000424DF604000000000000360000002800000015000000130000000100
            180000000000C0040000C40E0000C40E00000000000000000000CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
            D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
            D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
            D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D60000000000000000000000000000000000000000000000000000000000
            00000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D60000000000000086840086840086840086840086840086840086840086
            84008684000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D600000000FFFF0000000086840086840086840086840086840086840086
            84008684008684000000CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6000000FFFFFF00FFFF0000000086840086840086840086840086840086
            84008684008684008684000000CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D600000000FFFFFFFFFF00FFFF0000000086840086840086840086840086
            84008684008684008684008684000000CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6000000FFFFFF00FFFFFFFFFF00FFFF0000000000000000000000000000
            00000000000000000000000000000000000000CED3D6CED3D600CED3D6CED3D6
            CED3D600000000FFFFFFFFFF00FFFFFFFFFF00FFFFFFFFFF00FFFFFFFFFF00FF
            FF000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6000000FFFFFF00FFFFFFFFFF00FFFFFFFFFF00FFFFFFFFFF00FFFFFFFF
            FF000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D600000000FFFFFFFFFF00FFFF0000000000000000000000000000000000
            00000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6000000000000000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3
            D6CED3D6CED3D6000000000000000000CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
            D6CED3D6CED3D6CED3D6000000000000CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6000000CED3
            D6CED3D6CED3D6000000CED3D6000000CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D60000
            00000000000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
            D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
            D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
            CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
            D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600}
          ParentShowHint = False
          ShowHint = True
          OnClick = SpeedButton2Click
        end
        object edtip: TEdit
          Left = 69
          Top = 20
          Width = 169
          Height = 19
          Ctl3D = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 0
        end
        object edtuser: TEdit
          Left = 69
          Top = 68
          Width = 169
          Height = 19
          Ctl3D = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 1
        end
        object edtpass: TEdit
          Left = 69
          Top = 92
          Width = 169
          Height = 19
          Ctl3D = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
          ParentCtl3D = False
          ParentFont = False
          PasswordChar = '*'
          TabOrder = 2
        end
        object edtport: TEdit
          Left = 69
          Top = 44
          Width = 60
          Height = 19
          Ctl3D = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 3
        end
        object btnconnect: TButton
          Left = 250
          Top = 79
          Width = 55
          Height = 25
          Caption = #36830' '#25509
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = btnconnectClick
        end
        object btndisconn: TButton
          Left = 250
          Top = 111
          Width = 55
          Height = 25
          Caption = #26029' '#24320
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          OnClick = btndisconnClick
        end
        object edtSerDir: TEdit
          Left = 69
          Top = 116
          Width = 143
          Height = 19
          Ctl3D = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 6
          Text = '/'
        end
        object lstSerDir: TListBox
          Left = 323
          Top = 15
          Width = 135
          Height = 127
          Align = alRight
          ImeName = #20013#25991' ('#31616#20307') - '#25340#38899#21152#21152'3.11'
          ItemHeight = 13
          Sorted = True
          TabOrder = 7
        end
      end
      object ProgressBar1: TProgressBar
        Left = 1
        Top = 328
        Width = 460
        Height = 16
        Align = alBottom
        Smooth = True
        TabOrder = 7
      end
    end
  end
  object status: TStatusBar
    Left = 0
    Top = 413
    Width = 767
    Height = 19
    Panels = <
      item
        Width = 100
      end>
  end
  object idFtp: TIdFTP
    OnStatus = idFtpStatus
    Intercept = idLogDebug
    MaxLineAction = maException
    ReadTimeout = 0
    OnDisconnected = idFtpDisconnected
    OnWork = idFtpWork
    OnWorkBegin = idFtpWorkBegin
    OnWorkEnd = idFtpWorkEnd
    ProxySettings.ProxyType = fpcmNone
    ProxySettings.Port = 0
    Left = 20
    Top = 56
  end
  object idAntiFreeze: TIdAntiFreeze
    Left = 56
    Top = 56
  end
  object idLogDebug: TIdLogDebug
    Left = 96
    Top = 56
  end
end
