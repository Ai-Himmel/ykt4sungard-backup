object EditNameForm: TEditNameForm
  Left = 317
  Top = 281
  BorderStyle = bsDialog
  Caption = '�޸�����'
  ClientHeight = 100
  ClientWidth = 270
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 48
    Top = 8
    Width = 70
    Height = 13
    Caption = '�޸�������'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object edtName: TEdit
    Left = 48
    Top = 24
    Width = 121
    Height = 21
    ImeName = '���� (����) - ƴ���Ӽ�'
    TabOrder = 0
  end
  object btnOk: TButton
    Left = 48
    Top = 56
    Width = 75
    Height = 25
    Caption = '&Oȷ ��'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancle: TButton
    Left = 144
    Top = 56
    Width = 75
    Height = 25
    Caption = '&Cȡ ��'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = btnCancleClick
  end
end
