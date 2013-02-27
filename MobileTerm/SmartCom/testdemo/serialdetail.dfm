object frmDetail: TfrmDetail
  Left = 417
  Top = 208
  Width = 307
  Height = 370
  Caption = '流水详细信息'
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object lvDetail: TListView
    Left = 8
    Top = 8
    Width = 281
    Height = 281
    Columns = <
      item
        Caption = '参数'
        Width = 95
      end
      item
        Caption = '值'
        Width = 180
      end>
    FlatScrollBars = True
    HideSelection = False
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object btnClose: TButton
    Left = 216
    Top = 302
    Width = 75
    Height = 25
    Caption = '关闭'
    ModalResult = 2
    TabOrder = 1
  end
  object btnEndSerial: TButton
    Left = 107
    Top = 302
    Width = 97
    Height = 25
    Caption = '结束上传流水'
    ModalResult = 6
    TabOrder = 2
  end
  object btnSaveDetail: TButton
    Left = 10
    Top = 302
    Width = 86
    Height = 25
    Caption = '保存流水'
    TabOrder = 3
    OnClick = btnSaveDetailClick
  end
end
