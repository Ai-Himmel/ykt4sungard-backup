object frmMain: TfrmMain
  Left = 267
  Top = 280
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #25293#29031'/'#21046#21345#31649#29702#31995#32479
  ClientHeight = 691
  ClientWidth = 1014
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mm1
  OldCreateOrder = False
  Position = poDefault
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnlPhotoInfo: TPanel
    Left = 0
    Top = 0
    Width = 241
    Height = 691
    Align = alLeft
    BevelOuter = bvNone
    Caption = 'pnlPhotoInfo'
    TabOrder = 0
    object pnlPhoto: TPanel
      Left = 0
      Top = 301
      Width = 241
      Height = 320
      Align = alBottom
      BevelInner = bvRaised
      BevelOuter = bvLowered
      Caption = #26174#31034#29031#29255
      Color = 16053492
      TabOrder = 1
      object imgPhoto: TImage
        Left = 2
        Top = 2
        Width = 237
        Height = 316
        Align = alClient
        Stretch = True
      end
    end
    object pnlOperator: TPanel
      Left = 0
      Top = 621
      Width = 241
      Height = 70
      Align = alBottom
      BevelOuter = bvNone
      Color = 16053492
      TabOrder = 2
      object grp1: TGroupBox
        Left = 0
        Top = 2
        Width = 241
        Height = 57
        Color = 16053492
        ParentColor = False
        TabOrder = 0
        object btnEditInfo: TButton
          Left = 128
          Top = 19
          Width = 73
          Height = 24
          Caption = #20462#25913#20449#24687
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = btnEditInfoClick
        end
        object btnDelPhoto: TButton
          Left = 36
          Top = 19
          Width = 73
          Height = 24
          Caption = #21024#38500#29031#29255
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = btnDelPhotoClick
        end
      end
    end
    object grp2: TGroupBox
      Left = 0
      Top = 0
      Width = 241
      Height = 301
      Align = alClient
      Caption = #22522#26412#20449#24687
      Color = 16053492
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      TabOrder = 0
      object Label13: TLabel
        Left = 18
        Top = 32
        Width = 54
        Height = 15
        AutoSize = False
        Caption = #23458#25143#21495#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblCustNo: TLabel
        Left = 72
        Top = 32
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblStuEmpNo: TLabel
        Left = 72
        Top = 56
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 10
        Top = 56
        Width = 62
        Height = 15
        AutoSize = False
        Caption = #23398'/'#24037#21495#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lbl1: TLabel
        Left = 33
        Top = 80
        Width = 39
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblName: TLabel
        Left = 72
        Top = 80
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblType: TLabel
        Left = 72
        Top = 104
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 3
        Top = 104
        Width = 66
        Height = 15
        AutoSize = False
        Caption = #23458#25143#31867#21035#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 33
        Top = 128
        Width = 39
        Height = 15
        AutoSize = False
        Caption = #26657#21306#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblArea: TLabel
        Left = 72
        Top = 128
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblDept: TLabel
        Left = 72
        Top = 152
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 33
        Top = 152
        Width = 39
        Height = 15
        AutoSize = False
        Caption = #37096#38376#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 33
        Top = 176
        Width = 39
        Height = 15
        AutoSize = False
        Caption = #19987#19994#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblSpec: TLabel
        Left = 72
        Top = 176
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblState: TLabel
        Left = 72
        Top = 200
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 33
        Top = 200
        Width = 39
        Height = 15
        AutoSize = False
        Caption = #29366#24577#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel
        Left = 3
        Top = 224
        Width = 69
        Height = 15
        AutoSize = False
        Caption = #27880#20876#26085#26399#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblRegDate: TLabel
        Left = 72
        Top = 224
        Width = 164
        Height = 15
        AutoSize = False
        Caption = #22995#21517#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblCardId: TLabel
        Left = 72
        Top = 248
        Width = 164
        Height = 15
        AutoSize = False
        Caption = '123456789123456789'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        WordWrap = True
      end
      object Label8: TLabel
        Left = 3
        Top = 248
        Width = 69
        Height = 15
        AutoSize = False
        Caption = #36523#20221#35777#21495#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object bvl1: TBevel
        Left = 69
        Top = 244
        Width = 168
        Height = 21
      end
      object Bevel1: TBevel
        Left = 69
        Top = 220
        Width = 168
        Height = 21
      end
      object Bevel2: TBevel
        Left = 69
        Top = 196
        Width = 168
        Height = 21
      end
      object Bevel3: TBevel
        Left = 69
        Top = 172
        Width = 168
        Height = 21
      end
      object Bevel4: TBevel
        Left = 69
        Top = 148
        Width = 168
        Height = 21
      end
      object Bevel5: TBevel
        Left = 69
        Top = 125
        Width = 168
        Height = 21
      end
      object Bevel6: TBevel
        Left = 69
        Top = 101
        Width = 168
        Height = 21
      end
      object Bevel7: TBevel
        Left = 69
        Top = 77
        Width = 168
        Height = 21
      end
      object Bevel8: TBevel
        Left = 69
        Top = 53
        Width = 168
        Height = 21
      end
      object bvlCustId: TBevel
        Left = 69
        Top = 29
        Width = 168
        Height = 21
      end
    end
  end
  object pnlRight: TPanel
    Left = 610
    Top = 0
    Width = 404
    Height = 691
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object pnl3: TPanel
      Left = 0
      Top = 97
      Width = 404
      Height = 477
      Align = alClient
      BevelOuter = bvNone
      Color = clSkyBlue
      TabOrder = 1
      object imgCanon: TImage
        Left = 0
        Top = 0
        Width = 404
        Height = 152
        Align = alTop
        Stretch = True
      end
      object shpSelect: TShape
        Left = 0
        Top = 0
        Width = 89
        Height = 105
        Cursor = crSizeAll
        Brush.Color = clWindow
        Pen.Color = clRed
        Pen.Mode = pmMask
        Pen.Style = psDashDotDot
        OnMouseDown = shpSelectMouseDown
        OnMouseMove = shpSelectMouseMove
        OnMouseUp = shpSelectMouseUp
      end
      object shpL: TShape
        Left = 32
        Top = 24
        Width = 1
        Height = 65
        Pen.Color = clLime
      end
      object shpT: TShape
        Left = 48
        Top = 16
        Width = 65
        Height = 1
        Pen.Color = clLime
      end
      object shpR: TShape
        Left = 120
        Top = 24
        Width = 1
        Height = 65
        Pen.Color = clLime
      end
      object shpB: TShape
        Left = 56
        Top = 24
        Width = 65
        Height = 1
        Pen.Color = clLime
      end
      object shpA: TShape
        Left = 64
        Top = 32
        Width = 65
        Height = 1
        Pen.Color = clLime
      end
      object imgSrc: TImageEnVideoView
        Left = -207
        Top = 407
        Width = 209
        Height = 121
        ParentCtl3D = False
        BorderStyle = bsNone
        MouseInteract = [miSelect]
        AutoFit = True
        ImageEnVersion = '3.0.2'
        EnableInteractionHints = True
        TabOrder = 2
      end
      object imgCam: TImageEnView
        Left = 0
        Top = 152
        Width = 404
        Height = 169
        ParentCtl3D = False
        BorderStyle = bsNone
        OnViewChange = imgCamViewChange
        SelectionOptions = [iesoAnimated, iesoSizeable, iesoMoveable]
        MouseInteract = [miSelect]
        AutoFit = True
        ImageEnVersion = '3.0.2'
        EnableInteractionHints = True
        Align = alTop
        Visible = False
        TabOrder = 0
      end
      object grpPhotoSet: TGroupBox
        Left = 16
        Top = 336
        Width = 377
        Height = 121
        Caption = #30456#26426#21442#25968#35843#25972
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object Label14: TLabel
          Left = 8
          Top = 24
          Width = 65
          Height = 13
          AutoSize = False
          Caption = #22270#20687#22823#23567#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object Label15: TLabel
          Left = 180
          Top = 48
          Width = 73
          Height = 13
          AutoSize = False
          Caption = 'ISO'#24863#20809#24230#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object Label16: TLabel
          Left = 201
          Top = 72
          Width = 52
          Height = 13
          AutoSize = False
          Caption = #38378#20809#28783#65306
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object Label17: TLabel
          Left = 8
          Top = 72
          Width = 65
          Height = 13
          AutoSize = False
          Caption = #29031#29255#25928#26524#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object Label18: TLabel
          Left = 21
          Top = 48
          Width = 52
          Height = 13
          AutoSize = False
          Caption = #30333#24179#34913#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object Label19: TLabel
          Left = 188
          Top = 24
          Width = 65
          Height = 13
          AutoSize = False
          Caption = #28966#28857#35843#25972#65306
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
        end
        object cbbImageSize: TComboBox
          Left = 72
          Top = 18
          Width = 105
          Height = 21
          Style = csDropDownList
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          TabOrder = 1
          Text = #22823'/'#26497#31934#32454
          Items.Strings = (
            #22823'/'#26497#31934#32454
            #22823'/'#31934#32454
            #22823'/'#19968#33324
            #20013'1/'#26497#31934#32454
            #20013'1/'#31934#32454
            #20013'1/'#19968#33324
            #20013'2/'#26497#31934#32454
            #20013'2/'#31934#32454
            #20013'2/'#19968#33324
            #23567'/'#26497#31934#32454
            #23567'/'#31934#32454
            #23567'/'#19968#33324)
        end
        object cbbISO: TComboBox
          Left = 248
          Top = 42
          Width = 105
          Height = 21
          Style = csDropDownList
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          TabOrder = 3
          Text = '50'
          Items.Strings = (
            '50'
            '100'
            '200'
            '400'
            #33258#21160)
        end
        object cbbFlash: TComboBox
          Left = 248
          Top = 66
          Width = 105
          Height = 21
          Style = csDropDownList
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          TabOrder = 5
          Text = #20851
          Items.Strings = (
            #20851
            #33258#21160
            #24320
            #33258#21160'('#32418#30524')'
            #24320'('#32418#30524')')
        end
        object cbbPhotoEffect: TComboBox
          Left = 72
          Top = 66
          Width = 105
          Height = 21
          Style = csDropDownList
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          TabOrder = 4
          Text = #25928#26524#20851
          Items.Strings = (
            #25928#26524#20851
            #40092#33395#27169#24335
            #20013#24615#27169#24335
            #26580#21644#27169#24335
            #26087#29031#29255#27169#24335
            #40657#30333#27169#24335)
        end
        object cbbWhiteBalance: TComboBox
          Left = 72
          Top = 42
          Width = 105
          Height = 21
          Style = csDropDownList
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #23435#20307
          Font.Style = []
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          TabOrder = 2
          Text = #33258#21160
          Items.Strings = (
            #33258#21160
            #26085#20809
            #38452#22825
            #30333#28861#28783
            #33639#20809#28783
            #33639#20809#28783'H'
            #33258#23450#20041)
        end
        object trckbr1: TTrackBar
          Left = 248
          Top = 17
          Width = 110
          Height = 17
          PageSize = 1
          TabOrder = 0
          ThumbLength = 10
          OnChange = trckbr1Change
        end
        object pb: TProgressBar
          Left = 8
          Top = 91
          Width = 169
          Height = 16
          TabOrder = 6
        end
        object btnSetParam: TButton
          Left = 288
          Top = 92
          Width = 65
          Height = 24
          Caption = #35774' '#32622
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
          OnClick = btnSetParamClick
        end
      end
    end
    object grp4: TGroupBox
      Left = 0
      Top = 0
      Width = 404
      Height = 97
      Align = alTop
      Color = 16053492
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      TabOrder = 0
      object btn1: TButton
        Left = 8
        Top = 66
        Width = 153
        Height = 25
        Caption = #30456#26426#21462#26223#26694#35774#32622#39044#35272
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btn1Click
      end
      object cbbMenu: TComboBox
        Left = 24
        Top = 16
        Width = 145
        Height = 22
        ItemHeight = 14
        TabOrder = 0
        Visible = False
      end
    end
    object pnl2: TPanel
      Left = 0
      Top = 574
      Width = 404
      Height = 117
      Align = alBottom
      BevelOuter = bvNone
      Color = 16053492
      TabOrder = 2
      object grpCam: TGroupBox
        Left = 0
        Top = 8
        Width = 406
        Height = 50
        Caption = #25668#20687#22836#25805#20316
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object btnConnCam: TButton
          Left = 14
          Top = 18
          Width = 81
          Height = 24
          Caption = #36830#25509#25668#20687#22836
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = btnConnCamClick
        end
        object btnCamFormat: TButton
          Left = 112
          Top = 18
          Width = 81
          Height = 24
          Caption = #25668#20687#22836#26684#24335
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = btnCamFormatClick
        end
        object btnSetCam: TButton
          Left = 210
          Top = 18
          Width = 81
          Height = 24
          Caption = #25668#20687#22836#35774#32622
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = btnSetCamClick
        end
        object btnCamClose: TButton
          Left = 308
          Top = 18
          Width = 81
          Height = 24
          Caption = #20851#38381#25668#20687#22836
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = btnCamCloseClick
        end
      end
      object grpCanon: TGroupBox
        Left = 0
        Top = 59
        Width = 406
        Height = 47
        Caption = #25968#30721#30456#26426#25805#20316
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object btnConnectCan: TButton
          Left = 13
          Top = 17
          Width = 81
          Height = 24
          Caption = #36830#25509#29031#30456#26426
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = btnConnectCanClick
        end
        object btnPhotoShow: TButton
          Left = 111
          Top = 17
          Width = 81
          Height = 24
          Caption = #26174#31034#22270#20687
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = btnPhotoShowClick
        end
        object btnPhotoClose: TButton
          Left = 210
          Top = 17
          Width = 81
          Height = 24
          Caption = #20851#38381#22270#20687
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = btnPhotoCloseClick
        end
        object btnCloseCanon: TButton
          Left = 308
          Top = 17
          Width = 81
          Height = 24
          Caption = #20851#38381#29031#30456#26426
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = btnCloseCanonClick
        end
      end
    end
  end
  object pnlLeft: TPanel
    Left = 241
    Top = 0
    Width = 369
    Height = 691
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    object pnlPhotoMain: TPanel
      Left = 0
      Top = 97
      Width = 369
      Height = 476
      Align = alClient
      BevelInner = bvRaised
      BevelOuter = bvLowered
      Color = 16053492
      TabOrder = 1
      object imgShow: TImageEnVect
        Left = 2
        Top = 2
        Width = 365
        Height = 472
        ParentCtl3D = False
        BorderStyle = bsNone
        AutoFit = True
        ImageEnVersion = '3.0.2'
        EnableInteractionHints = True
        Align = alClient
        TabOrder = 0
      end
    end
    object grp3: TGroupBox
      Left = 0
      Top = 0
      Width = 369
      Height = 97
      Align = alTop
      Caption = #26597#35810#26465#20214
      Color = 16053492
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      TabOrder = 0
      object Label10: TLabel
        Left = 184
        Top = 18
        Width = 49
        Height = 14
        AutoSize = False
        Caption = #23398'/'#24037#21495
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel
        Left = 8
        Top = 18
        Width = 56
        Height = 14
        AutoSize = False
        Caption = #25152#23646#21306#22495
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lbl2: TLabel
        Left = 8
        Top = 74
        Width = 81
        Height = 14
        AutoSize = False
        Caption = #24635#25293#29031#20154#25968#65306
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object lblPhotoNum: TLabel
        Left = 88
        Top = 74
        Width = 89
        Height = 14
        AutoSize = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object edtStuempNo: TEdit
        Left = 184
        Top = 37
        Width = 153
        Height = 23
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnKeyDown = edtStuempNoKeyDown
      end
      object btnQuery: TBitBtn
        Left = 184
        Top = 65
        Width = 65
        Height = 27
        Caption = '&Q'#26597' '#35810
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = btnQueryClick
      end
      object btnCustQuery: TBitBtn
        Left = 256
        Top = 65
        Width = 81
        Height = 27
        Caption = #35814#32454#26597#35810
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = N6Click
      end
      object cbbArea: TComboBox
        Left = 8
        Top = 37
        Width = 169
        Height = 23
        Style = csDropDownList
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = #23435#20307
        Font.Style = []
        ItemHeight = 15
        ParentFont = False
        TabOrder = 0
        Items.Strings = (
          'sdfjakdj'
          'sdfadf'
          'sfda'
          'asfd'
          'asdf'
          'asfd'
          'asfd'
          'sdfadfa')
      end
    end
    object pnl1: TPanel
      Left = 0
      Top = 573
      Width = 369
      Height = 118
      Align = alBottom
      BevelOuter = bvNone
      Color = 16053492
      TabOrder = 2
      object grpPhoto: TGroupBox
        Left = 0
        Top = 7
        Width = 369
        Height = 100
        Caption = #29031#29255#25805#20316
        Color = 16053492
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 0
        object btnPhoto: TBitBtn
          Left = 42
          Top = 24
          Width = 65
          Height = 58
          Caption = #29031#29255#25293#25668
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = btnPhotoClick
          Glyph.Data = {
            36100000424D3610000000000000360000002800000020000000200000000100
            2000000000000010000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF007F7F7F000000
            0000000000000000000000000000000000007F7F7F00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00BFBFBF00BFBFBF00000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000007F7F7F00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF007F7F7F0000000000000000000000
            0000000000000000000000000000BFBFBF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00BFBFBF00BFBFBF00000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000007F7F7F00000000007F7F7F0000000000BFBFBF00BFBFBF000000
            000000000000000000000000000000000000BFBFBF00BFBFBF00000000007F7F
            7F00000000007F7F7F000000000000000000FFFFFF00FFFFFF00FFFFFF00BFBF
            BF00BFBFBF000000000000000000000000007F7F7F00000000007F7F7F000000
            00007F7F7F00000000007F7F7F0000000000BFBFBF007F7F7F00000000007F7F
            00007F7F00007F7F00007F7F00007F7F0000000000007F7F7F00BFBFBF000000
            00007F7F7F00000000007F7F7F007F7F7F0000000000FFFFFF00BFBFBF00BFBF
            BF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000007F7F7F00000000007F7F7F00BFBFBF00000000007F7F00007F7F
            00007F7F00007F7F0000FFFF00007F7F00007F7F000000000000BFBFBF007F7F
            7F00000000007F7F7F00000000007F7F7F0000000000FFFFFF00BFBFBF00BFBF
            BF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            00007F7F7F000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F00007F7F0000FFFF00007F7F00007F7F000000000000BFBF
            BF0000000000000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F00007F7F0000FFFF00007F7F00007F7F000000000000BFBF
            BF00000000007F7F7F00000000007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            0000000000000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F00007F7F0000FFFFFF00FFFF00007F7F000000000000BFBF
            BF0000000000000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F0000FFFF0000FFFFFF007F7F00007F7F000000000000BFBF
            BF00000000007F7F7F00000000007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            0000000000000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F0000FFFFFF00FFFF00007F7F00007F7F000000000000BFBF
            BF0000000000000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F000000000000000000000000007F7F7F00BFBFBF00000000007F7F00007F7F
            0000FFFF0000FFFFFF00FFFF00007F7F00007F7F000000000000BFBFBF007F7F
            7F00000000007F7F7F00000000007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            000000000000000000007F7F7F0000000000BFBFBF007F7F7F00000000007F7F
            00007F7F00007F7F00007F7F00007F7F0000000000007F7F7F00BFBFBF000000
            00007F7F7F00000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000007F7F7F00000000007F7F7F007F7F7F00BFBFBF00BFBFBF000000
            000000000000000000000000000000000000BFBFBF00BFBFBF00000000007F7F
            7F00000000007F7F7F00000000007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            00007F7F7F00000000007F7F7F007F7F7F00BFBFBF00FFFFFF00FFFFFF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF007F7F7F00000000007F7F7F000000
            00007F7F7F00000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000BFBFBF00BFBFBF00BFBFBF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF007F7F7F000000000000000000000000000000
            00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
            FF0000000000000000007F7F7F00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF000000000000000000FFFFFF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF000000000000000000BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F007F7F7F00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF0000000000000000000000
            00000000000000000000BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F007F7F7F00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F00BFBFBF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
            FF0000000000BFBFBF00BFBFBF007F7F7F000000000000000000000000000000
            000000000000BFBFBF007F7F7F00000000007F7F7F007F7F7F007F7F7F007F7F
            7F007F7F7F007F7F7F0000000000BFBFBF00BFBFBF007F7F7F00000000000000
            000000000000BFBFBF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF000000000000000000000000007F7F7F00FFFFFF00FFFFFF00FFFF
            FF0000000000000000000000000000000000BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00000000000000000000000000000000007F7F7F00FFFF
            FF000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF007F7F7F000000000000000000000000000000
            0000FFFFFF00FFFFFF00000000007F7F7F0000000000BFBFBF00BFBFBF00BFBF
            BF00BFBFBF0000000000FFFFFF00FFFFFF00FFFFFF007F7F7F00000000000000
            0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00000000007F7F7F00FFFFFF00FFFFFF00FFFF
            FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
            0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
          Layout = blGlyphTop
        end
        object btnSavePhoto: TBitBtn
          Left = 138
          Top = 23
          Width = 65
          Height = 59
          Caption = #20445#23384#29031#29255
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = btnSavePhotoClick
          Glyph.Data = {
            36100000424D3610000000000000360000002800000020000000200000000100
            2000000000000010000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF006666660066666600666666006666660066666600666666006666
            6600666666006666660066666600666666006666660066666600666666006666
            6600666666006666660066666600666666006666660066666600666666006666
            66006666660066666600666666006666660066666600FFFFFF00FFFFFF00AA99
            9900332222000000000000000000000000005555550077888800887788008888
            8800778888008888880088888800887788008888880077888800887788008888
            8800778888008888880088888800887788008888880077888800887788007744
            55005555550000000000000000000000000066666600FFFFFF00FFFFFF00DDCC
            DD003322220033222200331122007744550066555500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007744
            5500AA99880000000000000011000000000066666600FFFFFF00FFFFFF00DDDD
            CC004422220044222200332222006655550077445500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF006655
            4400AA99990011001100001100000000000066666600FFFFFF00FFFFFF00DDDD
            CC004422220044222200332222006655440077445500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF006655
            4400AA99990011000000111100000000000066666600FFFFFF00FFFFFF00DDCC
            DD003322220033222200442233007744550066555500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007744
            5500AA99880000110000110011000000000066666600FFFFFF00FFFFFF00DDDD
            DD003322220033222200442233006644550066555500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007744
            5500AA99880011111100110011000000000066666600FFFFFF00FFFFFF00DDDD
            CC004422330044222200443322006655440077445500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF006655
            4400AA99990011001100111100000000000066666600FFFFFF0044DDDD00DDDD
            CC005522330044223300443322006655550077445500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF006655
            4400AA99990022111100111100000000000066666600FFFFFF0000FFFF00BBDD
            DD004433330044223300442233006644550066555500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007744
            5500AA99880011111100110011000000000066666600FFFFFF0011EEEE0000EE
            FF0000DDDD0044333300442233007744550066555500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007744
            5500AA99880011111100110011000000000066666600FFFFFF0000FFFF0000FF
            FF0000FFFF0033666600443322006655550077445500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF006655
            4400AA99990022111100111111000000000066666600FFFFFF0000FFEE0011FF
            EE0000FFFF0000FFFF0000FFEE006655550077445500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EEFFFF0099FFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF006655
            4400AA99990022111100221111000000000066666600FFFFFF0066BBBB0000EE
            FF0000EEEE0000FFEE0000EEFF003399AA0066555500FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00DDFFFF0088FFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007744
            5500AA99880011111100221122000000000066666600FFFFFF00FFFFFF00CCDD
            DD003366660000FFFF0000EEFF0000FFFF0000FFFF00DDFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00BBFFFF0055FFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00DDAABB007744
            5500AA99880022111100221122000000000066666600FFFFFF00FFFFFF00DDDD
            CC00553333002299990000FFEE0000FFEE0000FFFF0044EEEE00DDFFEE00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00AAFFFF0033FFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00DDAABB00665544006655
            4400AA99990022111100222211000000000066666600FFFFFF00FFFFFF00DDDD
            CC005533330055333300553333000088770011EEEE0000FFFF0000FFFF005577
            770077445500774455006655440066555500774455004499AA0011EEEE006655
            440077445500774455006655440066555500774455007744550066555500AAAA
            AA003311220033112200222211000000000066666600FFFFFF00FFFFFF00DDDD
            DD00553333005533330055333300552244000044330000FFFF0000FFFF0000DD
            EE0000554400000000000000000000000000000000000099880000EEEE000000
            0000000000000000000000000000000000000000000000333300001122003311
            22002222110022112200221122000000000066666600FFFFFF00FFFFFF00DDCC
            DD005533330055333300552244005522330044333300443333004455660000EE
            FF0000FFFF001199990044224400442233003322220011BBBB0000EEFF004422
            3300332222003322220033113300334455001199990033222200331122003311
            22002222220022221100331122000000000066666600FFFFFF00FFFFFF00DDDD
            CC00663344006633440055333300553333005533330055333300553333002299
            990000EEFF0000FFFF0011BBAA00443322004422330011CCCC0000FFFF004422
            220044222200442222003333220011AAAA003333440033222200332222003322
            11003311220033112200222211000000000066666600FFFFFF00FFFFFF00DDDD
            CC0066334400663344005533330000000000AA999900AA999900AA998800AAAA
            8800AA99990066BBBB0000FFEE0033DDDD0099AA990022EEEE0000FFFF00AAAA
            8800AA99990022EEEE0055DDCC00AA998800AA99990033222200332222003322
            22003322220033112200332211000000000066666600FFFFFF00FFFFFF00DDCC
            DD00553344005533330055334400AAAAAA002222220022222200331122003311
            220022222200222222002244550000FFFF0000EEDD0000EEEE0000FFFF003322
            3300119999001166660066445500774455006655550033222200332222003311
            22003322220022222200331122000000000066666600FFFFFF00FFFFFF00DDDD
            DD00554444005533440066334400FFFFFF00BB999900BBAAAA00CCAABB00DDBB
            CC00CCCCCC00CCCCCC00CCCCCC00BBCCDD0044EEEE0000FFFF0000FFFF0022FF
            FF0088DDDD002233330066556600665566006655550033222200332233003322
            22003322220033222200331122000000000066666600FFFFFF00FFFFFF00DDDD
            CC0066334400555555004488770077FFFF0066CCCC0044DDDD0044EEDD0033FF
            EE0022EEFF0022EEFF0011FFEE0000FFEE0011FFFF0000FFFF0000FFFF0000FF
            FF0011FFFF0011EEEE0000FFEE0011EEDD0011DDEE0011CCCC0011CCBB0011AA
            99002299990022667700227766000000000066666600FFFFFF00FFFFFF00DDDD
            CC00663344006633440066443300FFFFFF00AA888800BB999900BBAA9900BBAA
            AA00CCAABB00DDBBCC00DDCCCC0077EEDD0011FFFF0011FFFF0000FFFF0011FF
            FF0066DDEE003311220066554400665555007744550044223300443322003322
            22004422220044222200332222000000000066666600FFFFFF00FFFFFF00DDDD
            DD00664444006633440066334400FFFFFF00AA888800AA998800BB889900BB99
            AA00BBAAAA00CCBBBB00CCBBCC0011EEFF0055EEEE0000EEEE0000FFFF00AAFF
            FF0011FFEE002244440077445500664455006655550033222200442233004422
            33003322220033222200332222000000000066666600FFFFFF00FFFFFF00DDCC
            DD00664444006644440066334400FFFFFF00BBAA9900AA888800AA888800BB88
            9900BB99990033EEDD0044DDEE00DDBBCC00CCCCBB0011DDDD0000FFFF00FFFF
            FF00CCCCCC001188880011DDEE00774455006655550044222200442233004422
            33003322220033222200442233000000000066666600FFFFFF00FFFFFF00DDDD
            CC00773344006633440066443300FFFFFF00CCAABB00BB999900AA998800AA99
            880099AAAA0055DDDD00BBBBAA00CCBBBB00DDBBCC0022CCDD0000FFFF00FFFF
            FF00DDBBBB00332222005577770033AA99007755550044223300443322004422
            22004422330044223300332222000000000066666600FFFFFF00FFFFFF00DDDD
            CC00774444007733440066444400FFFFFF00DDCCCC00CCAAAA00BBAA990044DD
            CC0099999900BB999900BBAA9900BBAAAA00CCAABB0000AAAA0000FFEE005555
            5500CCAAAA003311220066554400665555005588880044445500443322004433
            2200442233004422220044332200FFFFFF00FFFFFF00FFFFFF00FFFFFF00DDCC
            DD00664444006644440066334400FFFFFF00DDDDCC00CCBBBB0088CCCC00AA99
            AA00AA888800AA998800BB889900BB99AA00BBAAAA0055DDDD0011EEFF00BB99
            AA00BBAAAA002222220077445500774455006655550022999900335566004422
            3300442222003322220000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0055CCBB0011DDEE00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
          Layout = blGlyphTop
        end
        object btnSaveAs: TBitBtn
          Left = 226
          Top = 22
          Width = 95
          Height = 24
          Caption = #29031#29255#21478#23384
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = btnSaveAsClick
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000FFFFFF00FFFFFF000000
            00007FFFFF007FFFFF0000000000000000000000000000000000000000000000
            000000FFFF0000FFFF00000000007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF007FFFFF0000000000000000000000000000000000000000000000
            000000FFFF0000FFFF00000000007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF007FFFFF0000000000000000000000000000000000000000000000
            000000FFFF0000FFFF00000000007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF007FFFFF0000000000000000000000000000000000000000000000
            00000000000000000000000000007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF007FFFFF007FFFFF007FFFFF007FFFFF007FFFFF007FFFFF007FFF
            FF007FFFFF007FFFFF007FFFFF007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF007FFFFF0000000000000000000000000000000000000000000000
            000000000000000000007FFFFF007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00000000007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00000000007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00000000007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00000000007FFFFF0000000000FFFFFF00FFFFFF000000
            00007FFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00000000000000000000000000FFFFFF00FFFFFF000000
            00007FFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFFFF000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
        end
        object btnOpenPictrue: TBitBtn
          Left = 226
          Top = 58
          Width = 95
          Height = 24
          Caption = #25171#24320#29031#29255
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = btnOpenPictrueClick
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
            FF00009090000090900000909000009090000090900000909000009090000090
            9000009090000090900000909000009090000000000000000000FFFFFF00FFFF
            FF0000909000F0F0F00090CFFF0090FFFF0090CFFF0090FFFF0090CFFF0090CF
            FF0090CFFF0090CFFF0060CFCF00009090000000000000000000FFFFFF000090
            9000F0F0F00090FFFF0090FFFF0090CFFF0090FFFF0090CFFF0090FFFF0090CF
            FF0090CFFF0090CFFF0060CFCF00000000000090900000000000FFFFFF000090
            9000F0F0F00090FFFF0090FFFF0090FFFF0090FFFF0090FFFF0090CFFF0090FF
            FF0090CFFF0090CFFF000090900000000000009090000000000000909000F0F0
            F00090FFFF0090FFFF0090FFFF0090FFFF0090CFFF0090FFFF0090FFFF0090CF
            FF0090FFFF0060CFCF00000000000000000060CFCF000000000000909000F0F0
            F00090FFFF0090FFFF0090FFFF0090FFFF0090FFFF0090FFFF0090CFFF0090FF
            FF0090CFFF0060CFCF0000000000FFFFFF000000000000000000009090000090
            9000009090000090900000909000009090000090900000909000009090000090
            90000090900000909000FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF000090
            9000F0F0F00090FFFF0000000000FFFFFF00FFFFFF007F7F0000FFFFFF007F7F
            0000FFFFFF007F7F0000FFFFFF00FFFFFF000000000000000000FFFFFF000090
            9000F0F0F00090FFFF0090FFFF0000000000FFFFFF00FFFFFF007F7F0000FFFF
            FF007F7F0000FFFFFF00FFFFFF000000000060CFCF0000000000FFFFFF000090
            9000F0F0F00090FFFF0090FFFF0090FFFF0000000000FFFFFF00FFFFFF007F7F
            0000FFFFFF00FFFFFF00000000000090900000909000FFFFFF00FFFFFF00FFFF
            FF0000909000F0F0F000F0F0F000F0F0F000F0F0F00000000000FFFFFF00FFFF
            FF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00009090000090900000909000009090000090900000000000FFFF
            FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
            0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
        end
        object btnGetPhoto: TBitBtn
          Left = 42
          Top = 24
          Width = 65
          Height = 58
          Caption = #21462#29031#29255
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = btnGetPhotoClick
          Glyph.Data = {
            36100000424D3610000000000000360000002800000020000000200000000100
            2000000000000010000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF007F7F7F000000
            0000000000000000000000000000000000007F7F7F00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00BFBFBF00BFBFBF00000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000007F7F7F00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF007F7F7F0000000000000000000000
            0000000000000000000000000000BFBFBF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00BFBFBF00BFBFBF00000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000007F7F7F00000000007F7F7F0000000000BFBFBF00BFBFBF000000
            000000000000000000000000000000000000BFBFBF00BFBFBF00000000007F7F
            7F00000000007F7F7F000000000000000000FFFFFF00FFFFFF00FFFFFF00BFBF
            BF00BFBFBF000000000000000000000000007F7F7F00000000007F7F7F000000
            00007F7F7F00000000007F7F7F0000000000BFBFBF007F7F7F00000000007F7F
            00007F7F00007F7F00007F7F00007F7F0000000000007F7F7F00BFBFBF000000
            00007F7F7F00000000007F7F7F007F7F7F0000000000FFFFFF00BFBFBF00BFBF
            BF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000007F7F7F00000000007F7F7F00BFBFBF00000000007F7F00007F7F
            00007F7F00007F7F0000FFFF00007F7F00007F7F000000000000BFBFBF007F7F
            7F00000000007F7F7F00000000007F7F7F0000000000FFFFFF00BFBFBF00BFBF
            BF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            00007F7F7F000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F00007F7F0000FFFF00007F7F00007F7F000000000000BFBF
            BF0000000000000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F00007F7F0000FFFF00007F7F00007F7F000000000000BFBF
            BF00000000007F7F7F00000000007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            0000000000000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F00007F7F0000FFFFFF00FFFF00007F7F000000000000BFBF
            BF0000000000000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F0000FFFF0000FFFFFF007F7F00007F7F000000000000BFBF
            BF00000000007F7F7F00000000007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            0000000000000000000000000000BFBFBF00000000007F7F00007F7F00007F7F
            00007F7F00007F7F0000FFFFFF00FFFF00007F7F00007F7F000000000000BFBF
            BF0000000000000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F000000000000000000000000007F7F7F00BFBFBF00000000007F7F00007F7F
            0000FFFF0000FFFFFF00FFFF00007F7F00007F7F000000000000BFBFBF007F7F
            7F00000000007F7F7F00000000007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            000000000000000000007F7F7F0000000000BFBFBF007F7F7F00000000007F7F
            00007F7F00007F7F00007F7F00007F7F0000000000007F7F7F00BFBFBF000000
            00007F7F7F00000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF000000000000000000000000007F7F7F00000000007F7F7F00000000007F7F
            7F00000000007F7F7F00000000007F7F7F007F7F7F00BFBFBF00BFBFBF000000
            000000000000000000000000000000000000BFBFBF00BFBFBF00000000007F7F
            7F00000000007F7F7F00000000007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F0000000000000000007F7F7F00000000007F7F7F000000
            00007F7F7F00000000007F7F7F007F7F7F00BFBFBF00FFFFFF00FFFFFF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF007F7F7F00000000007F7F7F000000
            00007F7F7F00000000007F7F7F007F7F7F0000000000FFFFFF00FFFFFF00FFFF
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000BFBFBF00BFBFBF00BFBFBF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF007F7F7F000000000000000000000000000000
            00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
            FF0000000000000000007F7F7F00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF000000000000000000FFFFFF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF000000000000000000BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F007F7F7F00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF0000000000000000000000
            00000000000000000000BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F007F7F7F00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00BFBFBF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
            FF00000000007F7F7F00BFBFBF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
            FF0000000000BFBFBF00BFBFBF007F7F7F000000000000000000000000000000
            000000000000BFBFBF007F7F7F00000000007F7F7F007F7F7F007F7F7F007F7F
            7F007F7F7F007F7F7F0000000000BFBFBF00BFBFBF007F7F7F00000000000000
            000000000000BFBFBF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF000000000000000000000000007F7F7F00FFFFFF00FFFFFF00FFFF
            FF0000000000000000000000000000000000BFBFBF00BFBFBF00BFBFBF00BFBF
            BF00BFBFBF00BFBFBF00000000000000000000000000000000007F7F7F00FFFF
            FF000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF007F7F7F000000000000000000000000000000
            0000FFFFFF00FFFFFF00000000007F7F7F0000000000BFBFBF00BFBFBF00BFBF
            BF00BFBFBF0000000000FFFFFF00FFFFFF00FFFFFF007F7F7F00000000000000
            0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00000000007F7F7F00FFFFFF00FFFFFF00FFFF
            FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
            0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
          Layout = blGlyphTop
        end
      end
    end
  end
  object mm1: TMainMenu
    Left = 360
    Top = 352
    object N1: TMenuItem
      Caption = #31995#32479#31649#29702
      object N3: TMenuItem
        Caption = #26435#38480#25511#21046
        OnClick = N3Click
      end
      object N21: TMenuItem
        Caption = #20462#25913#23494#30721
        OnClick = N21Click
      end
      object N23: TMenuItem
        Caption = #25293#29031#35774#32622
        OnClick = N23Click
      end
      object N15: TMenuItem
        Caption = #36864#20986
        OnClick = N15Click
      end
    end
    object N4: TMenuItem
      Caption = #32479#35745#25253#34920
      object N5: TMenuItem
        Caption = #25293#29031#32479#35745
        OnClick = N5Click
      end
      object N6: TMenuItem
        Caption = #25293#29031#20449#24687#26597#35810
        OnClick = N6Click
      end
    end
    object N7: TMenuItem
      Caption = #25968#25454#25805#20316
      object N9: TMenuItem
        Caption = #29031#29255#23548#20986
        OnClick = N9Click
      end
      object N8: TMenuItem
        Caption = #29031#29255#23548#20837
        OnClick = N8Click
      end
      object N22: TMenuItem
        Caption = #20154#21592#20449#24687#23548#20837
        Visible = False
        OnClick = N22Click
      end
      object N16: TMenuItem
        Caption = #28155#21152#20154#21592#20449#24687
        OnClick = N16Click
      end
      object N17: TMenuItem
        Caption = #20462#25913#20154#21592#20449#24687
        OnClick = btnEditInfoClick
      end
    end
    object N10: TMenuItem
      Caption = #21046#21345#31649#29702
      object N11: TMenuItem
        Caption = #25209#37327#25171#21360
        OnClick = N11Click
      end
    end
    object NPrint_W: TMenuItem
      Caption = #30333#21345#25171#21360
      OnClick = NPrint_WClick
    end
    object N2: TMenuItem
      Caption = #22270#20687#22788#29702
      object N18: TMenuItem
        Caption = #39068#33394#35843#25972
        OnClick = N18Click
      end
      object N19: TMenuItem
        Caption = #22270#20687#25928#26524
        OnClick = N19Click
      end
      object N20: TMenuItem
        Caption = #21435#38500#32418#30524
        OnClick = N20Click
      end
    end
    object N13: TMenuItem
      Caption = #20851#20110
      object N14: TMenuItem
        Caption = #20851#20110#25293#29031#25171#21345#31995#32479
        OnClick = N14Click
      end
    end
  end
  object qryPhoto: TADOQuery
    Connection = frmdm.conn
    Parameters = <>
    Left = 407
    Top = 354
  end
  object ImageEnIO1: TImageEnIO
    Background = clBtnFace
    PreviewFont.Charset = DEFAULT_CHARSET
    PreviewFont.Color = clWindowText
    PreviewFont.Height = -11
    PreviewFont.Name = 'MS Sans Serif'
    PreviewFont.Style = []
    Left = 520
    Top = 352
  end
  object opnmgndlg: TOpenImageEnDialog
    Filter = 
      'All graphics|*.jpg;*.jpeg;*.gif;*.tif;*.tiff;*.pcx;*.png;*.bmp;*' +
      '.wmf;*.emf;*.ico;*.cur;*.avi|JPEG Bitmap (JPG;JPEG)|*.jpg;*.jpeg' +
      '|CompuServe Bitmap (GIF)|*.gif|TIFF Bitmap (TIF;TIFF)|*.tif;*.ti' +
      'ff|PaintBrush (PCX)|*.pcx|Portable Network Graphics (PNG)|*.png|' +
      'Windows Bitmap (BMP)|*.bmp|OS/2 Bitmap (BMP)|*.bmp|Enhanced Wind' +
      'ows Metafile (EMF)|*.emf|Windows Metafile (WMF)|*.wmf|Icon resou' +
      'rce (ICO)|*.ico|Cursor Resource (CUR)|*.cur|Video for Windows (A' +
      'VI)|*.avi'
    PreviewBorderStyle = iepsCropShadow
    Left = 432
    Top = 352
  end
  object svmgndlg1: TSaveImageEnDialog
    Filter = 
      'JPEG Bitmap (JPG)|*.jpg|CompuServe Bitmap (GIF)|*.gif|TIFF Bitma' +
      'p (TIF)|*.tif|PaintBrush (PCX)|*.pcx|Portable Network Graphics (' +
      'PNG)|*.png|Windows Bitmap (BMP)|*.bmp|OS/2 Bitmap (BMP)|*.bmp|Ta' +
      'rga Bitmap (TGA)|*.tga|Portable PixMap (PXM)|*.pxm|Portable PixM' +
      'ap (PPM)|*.ppm|Portable GreyMap (PGM)|*.pgm|Portable Bitmap (PBM' +
      ')|*.pbm|JPEG2000 (JP2)|*.jp2|JPEG2000 Code Stream (J2K)|*.j2k|Mu' +
      'ltipage PCX (DCX)|*.dcx'
    ExOptions = [sdShowPreview, sdShowAdvanced]
    Left = 435
    Top = 383
  end
  object ImageEnProc1: TImageEnProc
    AttachedImageEn = imgCam
    Background = clBtnFace
    PreviewsParams = [prppShowResetButton, prppHardReset]
    PreviewFont.Charset = DEFAULT_CHARSET
    PreviewFont.Color = clWindowText
    PreviewFont.Height = -11
    PreviewFont.Name = 'MS Sans Serif'
    PreviewFont.Style = []
    Left = 482
    Top = 355
  end
  object ImageEnProc2: TImageEnProc
    AttachedImageEn = imgSrc
    Background = clBtnFace
    PreviewsParams = [prppDefaultLockPreview]
    PreviewFont.Charset = DEFAULT_CHARSET
    PreviewFont.Color = clWindowText
    PreviewFont.Height = -11
    PreviewFont.Name = 'MS Sans Serif'
    PreviewFont.Style = []
    Left = 483
    Top = 320
  end
end
