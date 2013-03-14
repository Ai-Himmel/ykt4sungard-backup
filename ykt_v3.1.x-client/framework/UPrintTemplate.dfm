object fmPrintTemplate: TfmPrintTemplate
  Left = 229
  Top = 218
  Width = 748
  Height = 347
  VertScrollBar.Position = 743
  Caption = '打印模板'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object RDReport1: TRDReport
    Left = -11
    Top = -727
    Width = 718
    Height = 1047
    PrintSize.PrintHeight = 2770.1875
    PrintSize.PrintWidth = 1899.70837402344
    PrintSize.PrintLeft = -29.1041660308838
    PrintSize.PrintTop = -1923.52087402344
    LineStyles = <
      item
      end
      item
        Pen.Width = 2
      end
      item
        Pen.Style = psDot
      end>
    PaperWidth = 2100
    PaperHeight = 2970
    ReportName = 'sdfdsdsad'
    Margin.Left = 100
    Margin.Right = 100
    Margin.Top = 100
    Margin.Bottom = 100
    PaperSize = A4
    Orientation = poPortrait
    Arranged = False
    Color = clWhite
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '宋体'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    object HeaderBand: TRDSimpleBand
      Left = 0
      Top = 0
      Width = 718
      Height = 25
      PrintSize.PrintHeight = 66.1458358764648
      PrintSize.PrintWidth = 1899.70837402344
      BandKind = sbkHeader
      IsAlignBottom = False
      BandIndex = 0
      object lbSysDate: TRDLabel
        Left = 512
        Top = 0
        Width = 161
        Height = 23
        Link.Style = lsLeftToRight
        PrintSize.PrintHeight = 60
        PrintSize.PrintWidth = 425.979156494141
        PrintSize.PrintLeft = 1354.66662597656
        PrintSize.PrintRightDistance = 119.0625
        Anchors = [akLeft, akTop, akRight]
        HAlign = haRight
        VAlign = vaCenter
        TextFormatType = tfNormal
        Caption = '2001年12月31日'
      end
      object lbHeaderTitle: TRDLabel
        Left = 28
        Top = 0
        Width = 333
        Height = 23
        PrintSize.PrintHeight = 60
        PrintSize.PrintWidth = 881.0625
        PrintSize.PrintLeft = 74.0833358764648
        HAlign = haLeft
        VAlign = vaCenter
      end
    end
    object TitleBand: TRDSimpleBand
      Left = 0
      Top = 25
      Width = 718
      Height = 71
      PrintSize.PrintHeight = 187.85417175293
      PrintSize.PrintWidth = 1899.70837402344
      PrintSize.PrintTop = 66.1458358764648
      IsAlignBottom = False
      BandIndex = 1
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RDGroupBand1: TRDGroupBand
      Left = 0
      Top = 96
      Width = 718
      Height = 45
      PrintSize.PrintHeight = 119.0625
      PrintSize.PrintWidth = 1899.70837402344
      PrintSize.PrintTop = 254
      BandIndex = 2
      Arranged = False
      Color = clWhite
      ParentColor = False
      object colHeaderBand: TRDSimpleBand
        Left = 0
        Top = 0
        Width = 718
        Height = 23
        PrintSize.PrintHeight = 60
        PrintSize.PrintWidth = 1899.70837402344
        BandKind = sbkHeader
        IsAlignBottom = False
        BandIndex = 0
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object RDRepeatBand1: TRDRepeatBand
        Left = 0
        Top = 23
        Width = 718
        Height = 22
        PrintSize.PrintHeight = 58.2083320617676
        PrintSize.PrintWidth = 1899.70837402344
        PrintSize.PrintTop = 60.8541679382324
        ControllerName = 'DataSet'
        BandIndex = 1
        Arranged = False
        Color = clWhite
        ParentColor = False
        object DataBand: TRDSimpleBand
          Left = 0
          Top = 0
          Width = 718
          Height = 22
          PrintSize.PrintHeight = 58.2083320617676
          PrintSize.PrintWidth = 1899.70837402344
          IsAlignBottom = False
          BandIndex = 0
        end
      end
    end
    object FootBand: TRDSimpleBand
      Left = 0
      Top = 1019
      Width = 718
      Height = 28
      PrintSize.PrintHeight = 74.0833358764648
      PrintSize.PrintWidth = 1899.70837402344
      PrintSize.PrintTop = 2696.10424804688
      BandKind = sbkFooter
      IsAlignBottom = False
      BandIndex = 3
      object L_0152C910: TRDLabel
        Left = 555
        Top = 2000
        Width = 55
        Height = 19
        Link.Style = lsLeftToRight
        PrintSize.PrintHeight = 50
        PrintSize.PrintWidth = 145.52082824707
        PrintSize.PrintLeft = 1468.4375
        PrintSize.PrintTop = 5291.66650390625
        PrintSize.PrintRightDistance = 285.75
        Anchors = [akLeft, akTop, akRight]
        FieldName = '#Page'
        HAlign = haCenter
        VAlign = vaCenter
        TextFormatType = tfNormal
        TextFormat = '第%d页'
        Caption = '第100页'
      end
      object L_00DE3BB8: TRDLabel
        Left = 619
        Top = 2000
        Width = 65
        Height = 19
        Options = '#PrintOnLastPage'
        PrintSize.PrintHeight = 50.2708320617676
        PrintSize.PrintWidth = 171.97917175293
        PrintSize.PrintLeft = 1637.77087402344
        PrintSize.PrintTop = 5291.66650390625
        PrintSize.PrintRightDistance = 89.9583358764648
        Anchors = [akLeft, akTop, akRight]
        FieldName = '#Page'
        HAlign = haLeft
        VAlign = vaCenter
        TextFormatType = tfNormal
        TextFormat = '共%d页'
        Caption = '共100页'
      end
      object RDLabel1: TRDLabel
        Left = 56
        Top = 5
        Width = 52
        Height = 19
        Options = '#PrintOnLastPage'
        PrintSize.PrintHeight = 50.2708320617676
        PrintSize.PrintWidth = 137.58332824707
        PrintSize.PrintLeft = 148.16667175293
        PrintSize.PrintTop = 13.2291669845581
        HAlign = haLeft
        VAlign = vaCenter
        Caption = '制表人：'
      end
      object lbEmp: TRDLabel
        Left = 105
        Top = 5
        Width = 177
        Height = 19
        Options = '#PrintOnLastPage'
        PrintSize.PrintHeight = 50.2708320617676
        PrintSize.PrintWidth = 468.3125
        PrintSize.PrintLeft = 277.8125
        PrintSize.PrintTop = 13.2291669845581
        HAlign = haLeft
        VAlign = vaCenter
      end
    end
  end
  object ReportProcessor1: TReportProcessor
    DesignedReport = RDReport1
    DateFormat = 'yyyy/mm/dd'
    TimeFormat = 'hh:nn:ss'
    Left = 40
    Top = 231
  end
  object RPDBDataset1: TRPDBDataset
    DatasetName = 'DataSet'
    Environment = RPDataEnvironment1
    Left = 72
    Top = 232
  end
  object RPDatasetController1: TRPDatasetController
    Dataset = RPDBDataset1
    ControllerName = 'DataSet'
    Environment = RPDataEnvironment1
    Left = 191
    Top = 226
  end
  object RPDataEnvironment1: TRPDataEnvironment
    Left = 112
    Top = 232
  end
  object RPEasyReport1: TRPEasyReport
    Environment = RPDataEnvironment1
    Left = 152
    Top = 233
  end
end
