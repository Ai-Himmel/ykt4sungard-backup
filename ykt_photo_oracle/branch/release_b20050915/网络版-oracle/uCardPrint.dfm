object frmCardPrint: TfrmCardPrint
  Left = 342
  Top = 181
  BorderStyle = bsDialog
  Caption = '��Ƭ��ӡ'
  ClientHeight = 232
  ClientWidth = 418
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 418
    Height = 232
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object pnl2: TPanel
      Left = 0
      Top = 0
      Width = 418
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object lbl1: TLabel
        Left = 8
        Top = 16
        Width = 64
        Height = 13
        Caption = 'ѧ/���ţ�'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object edtNo: TEdit
        Left = 72
        Top = 10
        Width = 105
        Height = 21
        TabOrder = 0
        OnKeyDown = edtNoKeyDown
      end
      object btnQuery: TButton
        Left = 192
        Top = 8
        Width = 65
        Height = 25
        Caption = '(&Q)��ѯ'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = btnQueryClick
      end
      object btnPreview: TButton
        Left = 264
        Top = 8
        Width = 65
        Height = 25
        Caption = '(&P)��ӡ'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = btnPreviewClick
      end
      object btnExit: TButton
        Left = 336
        Top = 8
        Width = 65
        Height = 25
        Caption = '(&X)�˳�'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = btnExitClick
      end
    end
    object pnl3: TPanel
      Left = 0
      Top = 41
      Width = 418
      Height = 191
      Align = alClient
      BevelOuter = bvNone
      Color = 15002349
      TabOrder = 1
      object lbl2: TLabel
        Left = 176
        Top = 112
        Width = 201
        Height = 57
        AutoSize = False
        Caption = 
          'ע�����'#13#10'1���������ޱ�����У��ʹ��'#13#10'2�������Ʊ��ܣ���ʧ������' +
          '��ʧ'#13#10'3�������뵽У԰�����İ���'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        WordWrap = True
      end
      object lblNo: TLabel
        Left = 176
        Top = 40
        Width = 209
        Height = 13
        AutoSize = False
        Caption = 'ѧ�ţ�123456'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblName: TLabel
        Left = 176
        Top = 64
        Width = 209
        Height = 13
        AutoSize = False
        Caption = '����������ΰ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblCardStatus: TLabel
        Left = 58
        Top = 144
        Width = 49
        Height = 13
        AutoSize = False
        Caption = '���ƿ�'
        Font.Charset = GB2312_CHARSET
        Font.Color = clRed
        Font.Height = -14
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblmaketime: TLabel
        Left = 16
        Top = 160
        Width = 145
        Height = 12
        AutoSize = False
        Caption = '�ƿ����ڣ�2005-08-02'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object pnlPictrue: TPanel
        Left = 40
        Top = 32
        Width = 81
        Height = 107
        BevelInner = bvLowered
        Color = clCaptionText
        TabOrder = 0
        object imgPicture: TImage
          Left = 2
          Top = 2
          Width = 77
          Height = 103
          Align = alClient
          Stretch = True
        end
      end
      object QuickRep1: TQuickRep
        Left = 42
        Top = 280
        Width = 325
        Height = 204
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        Functions.Strings = (
          'PAGENUMBER'
          'COLUMNNUMBER'
          'REPORTTITLE')
        Functions.DATA = (
          '0'
          '0'
          #39#39)
        Options = [FirstPageHeader, LastPageFooter]
        Page.Columns = 1
        Page.Orientation = poPortrait
        Page.PaperSize = Custom
        Page.Values = (
          0
          540
          0
          860
          0
          0
          0)
        PrinterSettings.Copies = 1
        PrinterSettings.Duplex = False
        PrinterSettings.FirstPage = 0
        PrinterSettings.LastPage = 0
        PrinterSettings.OutputBin = Auto
        PrintIfEmpty = True
        SnapToGrid = True
        Units = MM
        Zoom = 100
        object DetailBand1: TQRBand
          Left = 0
          Top = 0
          Width = 325
          Height = 204
          Frame.Color = clBlack
          Frame.DrawTop = False
          Frame.DrawBottom = False
          Frame.DrawLeft = False
          Frame.DrawRight = False
          AlignToBottom = False
          Color = clWhite
          ForceNewColumn = False
          ForceNewPage = False
          Size.Values = (
            539.75
            859.895833333333)
          BandType = rbDetail
          object QRImage1: TQRImage
            Left = 33
            Top = 34
            Width = 80
            Height = 102
            Frame.Color = clBlack
            Frame.DrawTop = False
            Frame.DrawBottom = False
            Frame.DrawLeft = False
            Frame.DrawRight = False
            Size.Values = (
              270
              88
              90
              212)
            Stretch = True
          end
          object QRNo: TQRLabel
            Left = 170
            Top = 38
            Width = 151
            Height = 16
            Frame.Color = clBlack
            Frame.DrawTop = False
            Frame.DrawBottom = False
            Frame.DrawLeft = False
            Frame.DrawRight = False
            Size.Values = (
              42.3333333333333
              449.791666666667
              100.541666666667
              399.520833333333)
            Alignment = taLeftJustify
            AlignToBand = False
            AutoSize = False
            AutoStretch = False
            Caption = 'ѧ����'
            Color = clWhite
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = '����'
            Font.Style = [fsBold]
            ParentFont = False
            Transparent = False
            WordWrap = True
            FontSize = 9
          end
          object QRName: TQRLabel
            Left = 170
            Top = 62
            Width = 151
            Height = 16
            Frame.Color = clBlack
            Frame.DrawTop = False
            Frame.DrawBottom = False
            Frame.DrawLeft = False
            Frame.DrawRight = False
            Size.Values = (
              42.3333333333333
              449.791666666667
              164.041666666667
              399.520833333333)
            Alignment = taLeftJustify
            AlignToBand = False
            AutoSize = False
            AutoStretch = False
            Caption = '����'
            Color = clWhite
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = '����'
            Font.Style = [fsBold]
            ParentFont = False
            Transparent = False
            WordWrap = True
            FontSize = 9
          end
        end
      end
    end
  end
  object qryQuery: TADOQuery
    Connection = dm.ConnectPhoto
    Parameters = <>
    Left = 120
    Top = 209
  end
end
