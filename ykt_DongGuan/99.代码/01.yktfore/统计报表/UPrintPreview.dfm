object frmPrintPreview: TfrmPrintPreview
  Left = 212
  Top = 155
  Width = 696
  Height = 480
  Caption = '打印预览'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PreviewPanel: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 436
    Align = alClient
    BevelOuter = bvNone
    FullRepaint = False
    TabOrder = 0
    object GSMenuBar1: TGSMenuBar
      Left = 0
      Top = 0
      Width = 688
      Height = 22
      BorderWidth = 1
      ButtonHeight = 19
      ButtonWidth = 60
      Caption = 'PreviewBar'
      EdgeBorders = [ebLeft, ebTop, ebRight]
      TabOrder = 0
      object BPPrev: TToolButton
        Left = 0
        Top = 0
        AutoSize = True
        Caption = '上一页'
        OnClick = BPPrevClick
      end
      object BPNext: TToolButton
        Left = 47
        Top = 0
        AutoSize = True
        Caption = '下一页'
        OnClick = BPNextClick
      end
      object BPZoom: TToolButton
        Left = 94
        Top = 0
        AutoSize = True
        Caption = '缩    放'
        OnClick = APZoomExecute
      end
      object btnAPClose: TToolButton
        Left = 141
        Top = 0
        Hint = 'Print'
        AutoSize = True
        Caption = '打    印'
        ImageIndex = 62
        OnClick = btnAPCloseClick
      end
      object BPPageSetup: TToolButton
        Left = 193
        Top = 0
        Hint = 'Page Setup'
        AutoSize = True
        Caption = '打印设置'
        OnClick = BPPageSetupClick
      end
      object BPClose: TToolButton
        Left = 252
        Top = 0
        AutoSize = True
        Caption = '关    闭'
        OnClick = BPCloseClick
      end
    end
    object Preview: TXLPreview
      Left = 0
      Top = 22
      Width = 688
      Height = 414
      HorzScrollBar.Range = 301
      VertScrollBar.Range = 400
      Align = alClient
      Color = clAppWorkSpace
      ParentColor = False
      TabOrder = 1
      OnPageChanged = PreviewPageChanged
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 436
    Width = 688
    Height = 17
    Panels = <
      item
        Width = 200
      end
      item
        Alignment = taCenter
        Width = 50
      end
      item
        Alignment = taCenter
        Width = 80
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
end
