object frmDetail: TfrmDetail
  Left = 417
  Top = 208
  Width = 307
  Height = 370
  Caption = '��ˮ��ϸ��Ϣ'
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = '����'
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
        Caption = '����'
        Width = 95
      end
      item
        Caption = 'ֵ'
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
    Caption = '�ر�'
    ModalResult = 2
    TabOrder = 1
  end
  object btnEndSerial: TButton
    Left = 107
    Top = 302
    Width = 97
    Height = 25
    Caption = '�����ϴ���ˮ'
    ModalResult = 6
    TabOrder = 2
  end
  object btnSaveDetail: TButton
    Left = 10
    Top = 302
    Width = 86
    Height = 25
    Caption = '������ˮ'
    TabOrder = 3
    OnClick = btnSaveDetailClick
  end
end
