object datemngfrm: Tdatemngfrm
  Left = 234
  Top = 78
  Caption = #25910#36153#26102#38388#27573#31649#29702
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
  OnShow = FormShow
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
        Width = 154
        Height = 23
        Caption = #25910#36153#26102#38388#27573#31649#29702
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
        Width = 479
        Height = 433
        Align = alClient
        Caption = 'Panel5'
        TabOrder = 0
        object DBGrid1: TDBGrid
          Left = 1
          Top = 1
          Width = 477
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
          OnCellClick = DBGrid1CellClick
          Columns = <
            item
              Expanded = False
              FieldName = 'DATA_ID'
              Title.Caption = #26085#26399'ID'
              Width = 53
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'FEE_DATA'
              Title.Caption = #25910#36153#26085#26399
              Width = 84
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'STAGE_VALUE'
              Title.Caption = #25910#36153#26102#38388#27573#27573
              Width = 187
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'OPERATOR'
              Title.Caption = #25805#20316#21592
              Width = 80
              Visible = True
            end>
        end
      end
      object Panel6: TPanel
        Left = 480
        Top = 1
        Width = 501
        Height = 433
        Align = alRight
        Caption = 'Panel6'
        TabOrder = 1
        object DBGrid2: TDBGrid
          Left = 1
          Top = 1
          Width = 499
          Height = 431
          Align = alClient
          DataSource = DataSource2
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
          ReadOnly = True
          TabOrder = 0
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -16
          TitleFont.Name = #23435#20307
          TitleFont.Style = []
          OnCellClick = DBGrid2CellClick
          OnDblClick = DBGrid2DblClick
          Columns = <
            item
              Expanded = False
              FieldName = 'STAGE_ID'
              Title.Caption = #26102#38388'ID'
              Width = 53
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'BEGIN_TIME'
              Title.Caption = #24320#22987#26102#38388
              Width = 116
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'END_TIME'
              Title.Caption = #32467#26463#26102#38388
              Width = 126
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'OPERATOR'
              Title.Caption = #25805#20316#21592
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'RESERVE'
              Title.Caption = #22791#27880
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
      object Label14: TLabel
        Left = 9
        Top = 50
        Width = 80
        Height = 16
        Caption = #25910#36153#26102#27573#65306
      end
      object stuno: TLabel
        Left = 503
        Top = 12
        Width = 80
        Height = 16
        Caption = #24320#22987#26102#38388#65306
      end
      object Label12: TLabel
        Left = 10
        Top = 12
        Width = 80
        Height = 16
        Caption = #24320#22987#26085#26399#65306
      end
      object Label13: TLabel
        Left = 202
        Top = 12
        Width = 80
        Height = 16
        Caption = #32467#26463#26085#26399#65306
      end
      object Label2: TLabel
        Left = 691
        Top = 12
        Width = 80
        Height = 16
        Caption = #32467#26463#26102#38388#65306
      end
      object datemod: TButton
        Left = 320
        Top = 50
        Width = 57
        Height = 25
        Caption = #20462#25913
        TabOrder = 0
        OnClick = datemodClick
      end
      object deldate: TButton
        Left = 386
        Top = 50
        Width = 55
        Height = 25
        Caption = #21024#38500
        TabOrder = 1
        OnClick = deldateClick
      end
      object datestr: TEdit
        Left = 84
        Top = 50
        Width = 157
        Height = 24
        TabOrder = 2
      end
      object bgtime: TEdit
        Left = 577
        Top = 12
        Width = 96
        Height = 24
        TabOrder = 3
      end
      object oldbegdate: TDateTimePicker
        Left = 83
        Top = 12
        Width = 110
        Height = 24
        Date = 40100.000000000000000000
        Time = 40100.000000000000000000
        DateFormat = dfLong
        TabOrder = 4
      end
      object oldenddate: TDateTimePicker
        Left = 281
        Top = 12
        Width = 104
        Height = 24
        Date = 40100.000000000000000000
        Time = 40100.000000000000000000
        DateFormat = dfLong
        TabOrder = 5
      end
      object dateadd: TButton
        Left = 254
        Top = 50
        Width = 58
        Height = 25
        Caption = #28155#21152
        TabOrder = 6
        OnClick = dateaddClick
      end
      object modtime: TButton
        Left = 595
        Top = 50
        Width = 78
        Height = 25
        Caption = #20462#25913#26102#38388
        TabOrder = 7
        OnClick = modtimeClick
      end
      object STAGETIMEADD: TButton
        Left = 506
        Top = 50
        Width = 79
        Height = 25
        Caption = #28155#21152#26102#38388
        TabOrder = 8
        OnClick = STAGETIMEADDClick
      end
      object deltime: TButton
        Left = 684
        Top = 50
        Width = 79
        Height = 25
        Caption = #21024#38500#26102#38388
        TabOrder = 9
        OnClick = deltimeClick
      end
      object edtime: TEdit
        Left = 769
        Top = 12
        Width = 96
        Height = 24
        TabOrder = 10
      end
    end
  end
  object DataSource1: TDataSource
    Left = 169
    Top = 113
  end
  object DataSource2: TDataSource
    Left = 569
    Top = 97
  end
end
