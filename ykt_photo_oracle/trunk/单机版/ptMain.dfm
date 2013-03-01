object fMain: TfMain
  Left = 520
  Top = 1
  Width = 462
  Height = 740
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = '拍照-单机版'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 14
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 454
    Height = 97
    Align = alTop
    Color = clInfoBk
    TabOrder = 0
    object lbl1: TLabel
      Left = 154
      Top = 23
      Width = 56
      Height = 14
      Caption = '学工号：'
    end
    object btnFetch: TButton
      Left = 36
      Top = 54
      Width = 75
      Height = 25
      Caption = '取照片 '
      TabOrder = 0
      OnClick = btnFetchClick
    end
    object btnSave: TButton
      Left = 243
      Top = 56
      Width = 75
      Height = 23
      Caption = '保存'
      Enabled = False
      TabOrder = 1
      OnClick = btnSaveClick
    end
    object edtPersonNo: TEdit
      Left = 238
      Top = 19
      Width = 171
      Height = 22
      TabOrder = 2
    end
    object btnQuery: TButton
      Left = 151
      Top = 54
      Width = 75
      Height = 25
      Caption = '查询'
      TabOrder = 3
      OnClick = btnQueryClick
    end
    object btnCancel: TButton
      Left = 334
      Top = 54
      Width = 75
      Height = 25
      Caption = '取消 '
      TabOrder = 4
      OnClick = btnCancelClick
    end
    object GroupBox1: TGroupBox
      Left = 130
      Top = 11
      Width = 3
      Height = 70
      TabOrder = 5
    end
  end
  object pnlHandlePic: TPanel
    Left = 0
    Top = 97
    Width = 454
    Height = 560
    Align = alTop
    Color = clInfoBk
    Enabled = False
    TabOrder = 1
    object sbZI: TSpeedButton
      Left = 63
      Top = 17
      Width = 50
      Height = 22
      Caption = '放大'
      OnClick = sbZIClick
    end
    object sbZO: TSpeedButton
      Left = 135
      Top = 17
      Width = 50
      Height = 22
      Caption = '缩小'
      OnClick = sbZOClick
    end
    object sbRL: TSpeedButton
      Left = 63
      Top = 52
      Width = 50
      Height = 22
      Caption = '左转'
      OnClick = sbRLClick
    end
    object sbRR: TSpeedButton
      Left = 135
      Top = 52
      Width = 50
      Height = 22
      Caption = '右转'
      OnClick = sbRRClick
    end
    object sbUp: TSpeedButton
      Left = 279
      Top = 17
      Width = 50
      Height = 22
      Caption = '上移'
      OnClick = sbUpClick
    end
    object sbLeft: TSpeedButton
      Left = 215
      Top = 34
      Width = 50
      Height = 22
      Caption = '左移'
      OnClick = sbLeftClick
    end
    object sbRight: TSpeedButton
      Left = 343
      Top = 34
      Width = 50
      Height = 22
      Caption = '右移'
      OnClick = sbRightClick
    end
    object sbDown: TSpeedButton
      Left = 279
      Top = 52
      Width = 50
      Height = 22
      Caption = '下移'
      OnClick = sbDownClick
    end
    object pnlPic: TPanel
      Left = 61
      Top = 93
      Width = 330
      Height = 440
      Caption = '照         片'
      Color = clSilver
      FullRepaint = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clYellow
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsItalic]
      ParentFont = False
      TabOrder = 0
      object imgPic: TImage
        Left = 0
        Top = 0
        Width = 330
        Height = 440
        Center = True
        IncrementalDisplay = True
        Stretch = True
      end
      object PicFrame: TShape
        Left = 30
        Top = 40
        Width = 270
        Height = 360
        Brush.Style = bsClear
        Pen.Color = clAqua
      end
      object shpTop: TShape
        Left = 125
        Top = 80
        Width = 80
        Height = 2
        Brush.Style = bsClear
        Pen.Color = clLime
        Pen.Style = psDot
      end
      object shpLeft: TShape
        Left = 80
        Top = 160
        Width = 2
        Height = 60
        Brush.Style = bsClear
        Pen.Color = clLime
        Pen.Style = psDot
      end
      object shpRight: TShape
        Left = 250
        Top = 160
        Width = 2
        Height = 60
        Brush.Style = bsClear
        Pen.Color = clLime
        Pen.Style = psDot
      end
      object shpCenter: TShape
        Left = 165
        Top = 220
        Width = 2
        Height = 2
        Brush.Style = bsClear
        Pen.Color = clLime
        Pen.Style = psDot
      end
      object Shape1: TShape
        Left = 165
        Top = 180
        Width = 2
        Height = 2
        Brush.Style = bsClear
        Pen.Color = clLime
        Pen.Style = psDot
      end
      object Shape2: TShape
        Left = 165
        Top = 260
        Width = 2
        Height = 2
        Brush.Style = bsClear
        Pen.Color = clLime
        Pen.Style = psDot
      end
    end
  end
  object btnConfig: TButton
    Left = 253
    Top = 671
    Width = 75
    Height = 25
    Caption = '配置'
    TabOrder = 2
    OnClick = btnConfigClick
  end
  object btnExit: TButton
    Left = 347
    Top = 671
    Width = 75
    Height = 25
    Caption = '退出'
    ModalResult = 2
    TabOrder = 3
    OnClick = btnExitClick
  end
end
