object datemngfrm: Tdatemngfrm
  Left = 219
  Top = 175
  Caption = 'VIP'#29992#25143#31649#29702
  ClientHeight = 555
  ClientWidth = 984
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 984
    Height = 555
    Align = alClient
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 982
      Height = 32
      Align = alTop
      TabOrder = 0
      object Label1: TLabel
        Left = 398
        Top = 4
        Width = 132
        Height = 23
        Caption = #32479#35745#25253#34920#26597#35810
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -21
        Font.Name = #21326#25991#23435#20307
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 33
      Width = 982
      Height = 435
      Align = alClient
      TabOrder = 1
      object Panel5: TPanel
        Left = 1
        Top = 1
        Width = 980
        Height = 433
        Align = alClient
        Caption = 'Panel5'
        TabOrder = 0
        object DBGrid1: TDBGrid
          Left = 1
          Top = 1
          Width = 978
          Height = 431
          Align = alClient
          DataSource = DataSource1
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
          ReadOnly = True
          TabOrder = 0
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -16
          TitleFont.Name = #23435#20307
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'BALANCE_DATE'
              Title.Caption = #32479#35745#26085#26399
              Width = 102
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'FEE_NUM'
              Title.Caption = #25910#36153#27425#25968
              Width = 99
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'AMT'
              Title.Caption = #24635#37329#39069
              Width = 94
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'FREE_NUM'
              Title.Caption = #20813#36153#27425#25968
              Width = 103
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'VIP_NUM'
              Title.Caption = 'VIP'#27425#25968
              Width = 95
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'CARD_NUM'
              Title.Caption = #36827#39302#20154#25968
              Width = 129
              Visible = True
            end>
        end
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 468
      Width = 982
      Height = 86
      Align = alBottom
      TabOrder = 2
      object Label2: TLabel
        Left = 10
        Top = 36
        Width = 80
        Height = 16
        Caption = #24320#22987#26085#26399#65306
      end
      object Label3: TLabel
        Left = 202
        Top = 36
        Width = 80
        Height = 16
        Caption = #32467#26463#26085#26399#65306
      end
      object datequery: TButton
        Left = 400
        Top = 31
        Width = 89
        Height = 25
        Caption = #26597#35810#25253#34920
        TabOrder = 0
        OnClick = datequeryClick
      end
      object printf: TButton
        Left = 504
        Top = 32
        Width = 105
        Height = 25
        Caption = #25171#21360#25253#34920
        TabOrder = 1
        OnClick = printfClick
      end
      object oldbegdate: TDateTimePicker
        Left = 83
        Top = 33
        Width = 110
        Height = 24
        Date = 40100.000000000000000000
        Time = 40100.000000000000000000
        DateFormat = dfLong
        TabOrder = 2
      end
      object oldenddate: TDateTimePicker
        Left = 283
        Top = 32
        Width = 104
        Height = 24
        Date = 40100.000000000000000000
        Time = 40100.000000000000000000
        DateFormat = dfLong
        TabOrder = 3
      end
    end
  end
  object DataSource1: TDataSource
    Left = 169
    Top = 113
  end
  object frReport1: TfrxReport
    Tag = 1
    Version = '4.9.31'
    DotMatrixReport = False
    EngineOptions.DoublePass = True
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator]
    PreviewOptions.OutlineWidth = 180
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 37871.995398692100000000
    ReportOptions.Description.Strings = (
      'Demonstrates how to create simple list report.')
    ReportOptions.LastChange = 40583.730886712960000000
    ReportOptions.VersionMajor = '12'
    ReportOptions.VersionMinor = '13'
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    OnGetValue = frReport1GetValue
    Left = 410
    Top = 186
    Datasets = <
      item
        DataSet = frxDBDataset1
        DataSetName = 'frxDBDataset1'
      end>
    Variables = <>
    Style = <>
    object Page1: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 9
      LeftMargin = 5.000000000000000000
      RightMargin = 5.000000000000000000
      TopMargin = 5.000000000000000000
      BottomMargin = 5.000000000000000000
      Columns = 1
      ColumnWidth = 210.000000000000000000
      ColumnPositions.Strings = (
        '0')
      PrintOnPreviousPage = True
      object Band1: TfrxReportTitle
        Height = 26.456710000000000000
        Top = 18.897650000000000000
        Width = 755.906000000000000000
        object Memo1: TfrxMemoView
          Align = baWidth
          Top = 3.779530000000000000
          Width = 755.906000000000000000
          Height = 22.677180000000000000
          ShowHint = False
          Color = clTeal
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haCenter
          Memo.UTF8W = (
            #20307#32946#22330#39302#28040#36153#25253#34920)
          ParentFont = False
          VAlign = vaCenter
        end
      end
      object Band2: TfrxPageHeader
        Height = 37.795300000000000000
        Top = 68.031540000000000000
        Width = 755.906000000000000000
        object Memo5: TfrxMemoView
          Left = 15.118120000000000000
          Top = 7.559060000000000000
          Width = 75.590551181102400000
          Height = 18.897650000000000000
          ShowHint = False
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #32479#35745#26085#26399)
          ParentFont = False
        end
        object Memo6: TfrxMemoView
          Left = 113.385900000000000000
          Top = 9.448825000000000000
          Width = 71.811070000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #25910#36153#27425#25968)
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          Left = 207.874150000000000000
          Top = 9.448825000000000000
          Width = 68.031540000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #37329#39069)
          ParentFont = False
        end
        object Memo8: TfrxMemoView
          Left = 294.803340000000000000
          Top = 9.448825000000000000
          Width = 83.149660000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #20813#36153#27425#25968)
          ParentFont = False
        end
        object Memo9: TfrxMemoView
          Left = 404.409710000000000000
          Top = 9.448825000000000000
          Width = 83.149660000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            'VIP'#27425#25968)
          ParentFont = False
        end
        object Memo10: TfrxMemoView
          Left = 510.236550000000000000
          Top = 9.448825000000000000
          Width = 83.149660000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #28040#36153#20154#25968)
          ParentFont = False
        end
      end
      object Band3: TfrxPageFooter
        Height = 22.677180000000000000
        Top = 298.582870000000000000
        Width = 755.906000000000000000
        object Memo2: TfrxMemoView
          Left = 3.779530000000000000
          Top = 3.779530000000000000
          Width = 710.551640000000000000
          Height = 15.118120000000000000
          ShowHint = False
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftTop]
          Frame.Width = 2.000000000000000000
          HAlign = haRight
          Memo.UTF8W = (
            'Page [Page] of [TotalPages]')
          ParentFont = False
        end
      end
      object Band4: TfrxMasterData
        Height = 26.456710000000000000
        Top = 166.299320000000000000
        Width = 755.906000000000000000
        AllowSplit = True
        Columns = 1
        ColumnWidth = 200.000000000000000000
        ColumnGap = 20.000000000000000000
        DataSet = frxDBDataset1
        DataSetName = 'frxDBDataset1'
        RowCount = 0
        object BALANCE_DATE: TfrxMemoView
          Left = 15.118110240000000000
          Width = 75.590551181102400000
          Height = 18.897650000000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Memo.UTF8W = (
            '[frxDBDataset1."BALANCE_DATE"]')
        end
        object FEE_NUM: TfrxMemoView
          Left = 113.385900000000000000
          Top = 3.779530000000000000
          Width = 68.031540000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DataField = 'FEE_NUM'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Memo.UTF8W = (
            '[frxDBDataset1."FEE_NUM"]')
        end
        object AMT: TfrxMemoView
          Left = 207.874150000000000000
          Top = 3.779530000000000000
          Width = 64.252010000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DataField = 'AMT'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Memo.UTF8W = (
            '[frxDBDataset1."AMT"]')
        end
        object FREE_NUM: TfrxMemoView
          Left = 294.803340000000000000
          Top = 3.779530000000000000
          Width = 68.031540000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DataField = 'FREE_NUM'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Memo.UTF8W = (
            '[frxDBDataset1."FREE_NUM"]')
        end
        object VIP_NUM: TfrxMemoView
          Left = 404.409710000000000000
          Top = 3.779530000000000000
          Width = 83.149660000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DataField = 'VIP_NUM'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Memo.UTF8W = (
            '[frxDBDataset1."VIP_NUM"]')
        end
        object CARD_NUM: TfrxMemoView
          Left = 510.236550000000000000
          Top = 3.779530000000000000
          Width = 83.149660000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DataField = 'CARD_NUM'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Memo.UTF8W = (
            '[frxDBDataset1."CARD_NUM"]')
        end
      end
      object ReportSummary1: TfrxReportSummary
        Height = 22.677180000000000000
        Top = 253.228510000000000000
        Width = 755.906000000000000000
        object Memo3: TfrxMemoView
          Left = 15.118110240000000000
          Top = 1.889765000000000000
          Width = 75.590551181102400000
          Height = 18.897650000000000000
          ShowHint = False
          Memo.UTF8W = (
            #21512#35745)
        end
        object Memo4: TfrxMemoView
          Left = 113.385900000000000000
          Top = 1.889765000000000000
          Width = 69.472480000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Memo.UTF8W = (
            '[SUM(<frxDBDataset1."FEE_NUM">,Band4)]')
        end
        object Memo11: TfrxMemoView
          Left = 207.874150000000000000
          Top = 1.889765000000000000
          Width = 67.472480000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Memo.UTF8W = (
            '[SUM(<frxDBDataset1."AMT">,Band4)]')
        end
        object Memo12: TfrxMemoView
          Left = 294.803340000000000000
          Top = 1.389765000000000000
          Width = 71.472480000000000000
          Height = 19.897650000000000000
          ShowHint = False
          Memo.UTF8W = (
            '[SUM(<frxDBDataset1."FREE_NUM">,Band4)]')
        end
        object Memo13: TfrxMemoView
          Left = 404.409710000000000000
          Top = 1.889765000000000000
          Width = 77.811070000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Memo.UTF8W = (
            '[SUM(<frxDBDataset1."VIP_NUM">,Band4)]')
        end
        object Memo14: TfrxMemoView
          Left = 510.236550000000000000
          Top = 1.889765000000000000
          Width = 79.370130000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Memo.UTF8W = (
            '[SUM(<frxDBDataset1."CARD_NUM">,Band4)]')
        end
      end
    end
  end
  object frxDBDataset1: TfrxDBDataset
    UserName = 'frxDBDataset1'
    CloseDataSource = True
    DataSource = DataSource1
    BCDToCurrency = False
    Left = 298
    Top = 178
  end
end
