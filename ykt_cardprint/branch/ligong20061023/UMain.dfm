object Form1: TForm1
  Left = 288
  Top = 257
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '��Ƭ��ӡ'
  ClientHeight = 185
  ClientWidth = 342
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object btnTeacher: TButton
    Left = 104
    Top = 16
    Width = 121
    Height = 25
    Caption = '��ʦ֤����ӡ'
    TabOrder = 0
    OnClick = btnTeacherClick
  end
  object btnStudent: TButton
    Left = 104
    Top = 48
    Width = 121
    Height = 25
    Caption = 'ѧ��֤����ӡ'
    TabOrder = 1
    OnClick = btnStudentClick
  end
  object btnExit: TButton
    Left = 104
    Top = 120
    Width = 121
    Height = 25
    Caption = '��  ��'
    TabOrder = 2
    OnClick = btnExitClick
  end
  object btnU: TButton
    Left = 104
    Top = 80
    Width = 121
    Height = 25
    Caption = '��Ƭ��ӡ'
    TabOrder = 3
    OnClick = btnUClick
  end
end
