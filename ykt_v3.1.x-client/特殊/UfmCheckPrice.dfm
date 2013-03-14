object fmCheckPrice: TfmCheckPrice
  Left = 336
  Top = 196
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = '确认价格手数：'
  ClientHeight = 142
  ClientWidth = 277
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
  object Label1: TLabel
    Left = 30
    Top = 27
    Width = 60
    Height = 13
    Caption = '申报价格：'
  end
  object Label2: TLabel
    Left = 30
    Top = 65
    Width = 60
    Height = 13
    Caption = '申报手数：'
  end
  object btnOK: TBitBtn
    Left = 26
    Top = 104
    Width = 75
    Height = 25
    Action = acOK
    TabOrder = 2
  end
  object btnCancel: TBitBtn
    Left = 173
    Top = 104
    Width = 75
    Height = 25
    Action = acCancel
    TabOrder = 3
  end
  object edtPrice: TWVDigitalEdit
    Left = 116
    Top = 25
    Width = 119
    Height = 17
    Color = clInfoBk
    ParentColor = False
    TabOrder = 0
    TabStop = True
    Text = '0'
    WorkView = WorkView
    FieldName = 'wvPrice'
  end
  object edtNum: TWVDigitalEdit
    Left = 116
    Top = 63
    Width = 119
    Height = 17
    Color = clInfoBk
    ParentColor = False
    TabOrder = 1
    TabStop = True
    Text = '0'
    WorkView = WorkView
    FieldName = 'wvNum'
  end
  object WorkView: TWorkView
    WorkFields = <
      item
        Name = 'wvPrice'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = 'wvNum'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 1
        Checker.Max = 1E100
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValidChangedFields = '|WVPRICE|WVNUM|'
        OnValidChanged = WorkViewFieldsMonitors0ValidChanged
      end>
    Left = 80
    Top = 8
  end
  object ActionList: TActionList
    Left = 16
    Top = 8
    object acOK: TAction
      Caption = '确认(&O)'
      OnExecute = acOKExecute
    end
    object acCancel: TAction
      Caption = '取消(&C)'
      ShortCut = 27
      OnExecute = acCancelExecute
    end
  end
end
