object PhotoSystem: TPhotoSystem
  Left = 433
  Top = -7
  Width = 575
  Height = 738
  Align = alLeft
  BorderIcons = []
  Caption = '���ո���ϵͳ'
  Color = clInfoBk
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClick = FormClick
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnMouseDown = FormMouseDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 567
    Height = 57
    Align = alTop
    Color = clInfoBk
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 16
      Width = 193
      Height = 32
      AutoSize = False
      Caption = '���ո���ϵͳ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label18: TLabel
      Left = 464
      Top = 24
      Width = 89
      Height = 13
      AutoSize = False
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label19: TLabel
      Left = 296
      Top = 24
      Width = 161
      Height = 13
      AutoSize = False
      Caption = '���Ĺ���Ƭ��ѧ�������ǣ�'
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 57
    Width = 567
    Height = 49
    Align = alTop
    Color = clInfoBk
    TabOrder = 1
    object Label2: TLabel
      Left = 96
      Top = 17
      Width = 100
      Height = 13
      AutoSize = False
      Caption = '������ѧ���� ��'
    end
    object Edit1: TEdit
      Left = 200
      Top = 12
      Width = 113
      Height = 21
      ImeName = '���� (����) - ΢��ƴ��'
      TabOrder = 0
      OnKeyUp = Edit1KeyUp
    end
    object Button1: TButton
      Left = 336
      Top = 8
      Width = 75
      Height = 25
      Caption = '�� ѯ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button1Click
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 106
    Width = 217
    Height = 578
    Align = alLeft
    Color = clInfoBk
    Enabled = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '����'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label3: TLabel
      Left = 8
      Top = 64
      Width = 70
      Height = 14
      AutoSize = False
      Caption = '��    ����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 40
      Width = 70
      Height = 14
      AutoSize = False
      Caption = 'ѧ�Ź��ţ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 8
      Top = 88
      Width = 70
      Height = 14
      AutoSize = False
      Caption = 'һ����λ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 8
      Top = 136
      Width = 70
      Height = 14
      AutoSize = False
      Caption = '��Ա���'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label10: TLabel
      Left = 7
      Top = 8
      Width = 112
      Height = 16
      Caption = '[���˻�����Ϣ]'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 24
      Top = 496
      Width = 89
      Height = 13
      AutoSize = False
      Caption = 'ԭʼ��Ƭ���ڣ�'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 72
      Top = 64
      Width = 137
      Height = 14
      AutoSize = False
      Caption = 'xm'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label13: TLabel
      Left = 72
      Top = 40
      Width = 137
      Height = 14
      AutoSize = False
      Caption = 'xgh'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label14: TLabel
      Left = 72
      Top = 88
      Width = 137
      Height = 14
      AutoSize = False
      Caption = 'yx'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label15: TLabel
      Left = 72
      Top = 136
      Width = 137
      Height = 14
      AutoSize = False
      Caption = 'zy'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label16: TLabel
      Left = 8
      Top = 112
      Width = 70
      Height = 14
      AutoSize = False
      Caption = '������λ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label17: TLabel
      Left = 72
      Top = 112
      Width = 137
      Height = 14
      AutoSize = False
      Caption = 'lb'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label20: TLabel
      Left = 128
      Top = 497
      Width = 73
      Height = 12
      AutoSize = False
      Caption = 'L'
    end
    object Label21: TLabel
      Left = 16
      Top = 560
      Width = 42
      Height = 12
      Caption = 'Label21'
      Visible = False
    end
    object Label23: TLabel
      Left = 8
      Top = 160
      Width = 70
      Height = 14
      AutoSize = False
      Caption = '���֤�ţ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label24: TLabel
      Left = 40
      Top = 184
      Width = 169
      Height = 14
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label25: TLabel
      Left = 40
      Top = 320
      Width = 48
      Height = 12
      AutoSize = False
      Caption = '��Ƭλ��'
      Visible = False
    end
    object LPicture: TLabel
      Left = 96
      Top = 320
      Width = 49
      Height = 12
      AutoSize = False
      Caption = 'pic'
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object Panel6: TPanel
      Left = 16
      Top = 240
      Width = 182
      Height = 242
      Caption = 'ԭʼ��Ƭ'
      Color = clInactiveCaption
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Image2: TImage
        Left = 1
        Top = 1
        Width = 180
        Height = 240
        Align = alClient
        Stretch = True
      end
    end
    object DBEdit1: TDBEdit
      Left = 40
      Top = 344
      Width = 137
      Height = 28
      DataSource = DataSource1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '���� (����) - ΢��ƴ��'
      ParentFont = False
      TabOrder = 1
      Visible = False
    end
    object DBEdit2: TDBEdit
      Left = 40
      Top = 344
      Width = 129
      Height = 28
      DataSource = DataSource1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '���� (����) - ΢��ƴ��'
      ParentFont = False
      TabOrder = 2
      Visible = False
    end
    object Edit5: TEdit
      Left = 40
      Top = 344
      Width = 129
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '���� (����) - ΢��ƴ��'
      ParentFont = False
      TabOrder = 3
      Text = 'Edit5'
      Visible = False
    end
    object DBEdit4: TDBEdit
      Left = 40
      Top = 348
      Width = 129
      Height = 28
      DataSource = DataSource1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '���� (����) - ΢��ƴ��'
      ParentFont = False
      TabOrder = 4
      Visible = False
    end
    object BitBtn1: TBitBtn
      Left = 56
      Top = 520
      Width = 89
      Height = 25
      Caption = '�޸Ļ�����Ϣ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnClick = BitBtn1Click
    end
    object Edit6: TEdit
      Left = 40
      Top = 352
      Width = 129
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '���� (����) - ΢��ƴ��'
      ParentFont = False
      TabOrder = 6
      Text = 'Edit6'
      Visible = False
    end
    object btnDelPic: TButton
      Left = 56
      Top = 200
      Width = 75
      Height = 25
      Caption = 'ɾ����Ƭ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      OnClick = btnDelPicClick
    end
  end
  object Panel4: TPanel
    Left = 217
    Top = 106
    Width = 350
    Height = 578
    Align = alClient
    Color = clInfoBk
    TabOrder = 3
    object Label8: TLabel
      Left = 0
      Top = 492
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'ԭ�ļ�����'
    end
    object Label9: TLabel
      Left = 161
      Top = 492
      Width = 80
      Height = 13
      AutoSize = False
      Caption = '�����ļ�����'
    end
    object Label7: TLabel
      Left = -56
      Top = 380
      Width = 72
      Height = 13
      Caption = '���˳��ţ�'
      Visible = False
    end
    object Label22: TLabel
      Left = -72
      Top = 340
      Width = 84
      Height = 13
      Caption = '��Ƭ����λ�ã�'
      Visible = False
    end
    object Edit2: TEdit
      Left = 72
      Top = 488
      Width = 86
      Height = 21
      ImeName = '���� (����) - ΢��ƴ��'
      TabOrder = 0
    end
    object Edit3: TEdit
      Left = 240
      Top = 488
      Width = 97
      Height = 21
      ImeName = '���� (����) - ΢��ƴ��'
      TabOrder = 1
    end
    object Edit4: TEdit
      Left = -112
      Top = 392
      Width = 121
      Height = 21
      ImeName = '���� (����) - ΢��ƴ��'
      TabOrder = 2
      Text = '00001'
      Visible = False
    end
    object Button5: TButton
      Left = -96
      Top = 88
      Width = 105
      Height = 33
      Caption = '�޸����˳���'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      Visible = False
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = -40
      Top = 128
      Width = 49
      Height = 33
      Caption = 'ȷ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = -40
      Top = 200
      Width = 49
      Height = 33
      Caption = 'ȡ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = -64
      Top = 240
      Width = 75
      Height = 33
      Caption = '�༭��Ƭ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      Visible = False
      OnClick = Button8Click
    end
    object Edit7: TEdit
      Left = -240
      Top = 280
      Width = 249
      Height = 21
      ImeName = '���� (����) - ΢��ƴ��'
      TabOrder = 7
      Visible = False
    end
    object pnlHandlePic: TPanel
      Left = 1
      Top = 1
      Width = 348
      Height = 576
      Align = alClient
      Color = clInfoBk
      Enabled = False
      TabOrder = 8
      object sbZI: TSpeedButton
        Left = 23
        Top = 53
        Width = 50
        Height = 22
        Caption = '�Ŵ�'
        OnClick = sbZIClick
      end
      object sbZO: TSpeedButton
        Left = 87
        Top = 53
        Width = 50
        Height = 22
        Caption = '��С'
        OnClick = sbZOClick
      end
      object sbRL: TSpeedButton
        Left = 23
        Top = 88
        Width = 50
        Height = 22
        Caption = '��ת'
        OnClick = sbRLClick
      end
      object sbRR: TSpeedButton
        Left = 87
        Top = 88
        Width = 50
        Height = 22
        Caption = '��ת'
        OnClick = sbRRClick
      end
      object sbUp: TSpeedButton
        Left = 215
        Top = 53
        Width = 50
        Height = 22
        Caption = '����'
        OnClick = sbUpClick
      end
      object sbLeft: TSpeedButton
        Left = 159
        Top = 70
        Width = 50
        Height = 22
        Caption = '����'
        OnClick = sbLeftClick
      end
      object sbRight: TSpeedButton
        Left = 271
        Top = 70
        Width = 50
        Height = 22
        Caption = '����'
        OnClick = sbRightClick
      end
      object sbDown: TSpeedButton
        Left = 215
        Top = 88
        Width = 50
        Height = 22
        Caption = '����'
        OnClick = sbDownClick
      end
      object pnlPic: TPanel
        Left = 21
        Top = 121
        Width = 300
        Height = 400
        Caption = '��         Ƭ'
        Color = clSilver
        FullRepaint = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clYellow
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsItalic]
        ParentFont = False
        TabOrder = 0
        object imgPic: TImage
          Left = 0
          Top = 0
          Width = 300
          Height = 400
          Center = True
          IncrementalDisplay = True
          Stretch = True
        end
        object PicFrame: TShape
          Left = 30
          Top = 40
          Width = 240
          Height = 320
          Brush.Style = bsClear
          Pen.Color = clAqua
        end
        object shpTop: TShape
          Left = 110
          Top = 80
          Width = 80
          Height = 2
          Brush.Style = bsClear
          Pen.Color = clLime
          Pen.Style = psDot
        end
        object shpLeft: TShape
          Left = 70
          Top = 150
          Width = 2
          Height = 60
          Brush.Style = bsClear
          Pen.Color = clLime
          Pen.Style = psDot
        end
        object shpRight: TShape
          Left = 230
          Top = 150
          Width = 2
          Height = 60
          Brush.Style = bsClear
          Pen.Color = clLime
          Pen.Style = psDot
        end
        object shpCenter: TShape
          Left = 150
          Top = 200
          Width = 2
          Height = 2
          Brush.Style = bsClear
          Pen.Color = clLime
          Pen.Style = psDot
        end
        object Shape1: TShape
          Left = 150
          Top = 160
          Width = 2
          Height = 2
          Brush.Style = bsClear
          Pen.Color = clLime
          Pen.Style = psDot
        end
        object Shape2: TShape
          Left = 150
          Top = 240
          Width = 2
          Height = 2
          Brush.Style = bsClear
          Pen.Color = clLime
          Pen.Style = psDot
        end
      end
      object Button2: TButton
        Left = 24
        Top = 16
        Width = 73
        Height = 25
        Caption = 'ȡ��Ƭ'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 24
        Top = 533
        Width = 65
        Height = 25
        Caption = 'ȷ ��'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 104
        Top = 533
        Width = 73
        Height = 25
        Caption = 'ȡ ��'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = Button4Click
      end
    end
  end
  object btnExit: TButton
    Left = 462
    Top = 639
    Width = 75
    Height = 25
    Caption = '�� ��'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = btnExitClick
  end
  object DataSource1: TDataSource
    Left = 344
    Top = 1
  end
  object ADOQuery4: TADOQuery
    Connection = dm.ConnectPhoto
    LockType = ltUnspecified
    Parameters = <>
    Left = 313
    Top = 1
  end
  object MainMenu1: TMainMenu
    Left = 184
    Top = 1
    object file1: TMenuItem
      Caption = '��������'
      object N2: TMenuItem
        Caption = '�����ѡ��'
        OnClick = N2Click
      end
      object N6: TMenuItem
        Caption = '����Ա����'
        OnClick = N6Click
      end
    end
    object count1: TMenuItem
      Caption = 'ͳ�Ʊ���'
      object N1: TMenuItem
        Caption = 'ͳ��'
        OnClick = N1Click
      end
      object N7: TMenuItem
        Caption = '��ѯ'
        OnClick = N7Click
      end
    end
    object N3: TMenuItem
      Caption = '���ݲ���'
      object N12: TMenuItem
        Caption = '�ƿ�'
        OnClick = N12Click
      end
      object N4: TMenuItem
        Caption = '������Ƭ'
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = '����'
        OnClick = N5Click
        object N8: TMenuItem
          Caption = '������Ƭ'
          OnClick = N8Click
        end
        object N9: TMenuItem
          Caption = '���������Ϣ'
          OnClick = N9Click
        end
      end
      object N11: TMenuItem
        Caption = 'ɾ��������Ϣ'
        OnClick = N11Click
      end
      object N10: TMenuItem
        Caption = '�ƿ�����'
        OnClick = N10Click
      end
      object N13: TMenuItem
        Caption = '�����Ա��Ϣ'
        OnClick = N13Click
      end
    end
  end
  object ADOQuery1: TADOQuery
    AutoCalcFields = False
    Connection = dm.ConnectPhoto
    CursorType = ctUnspecified
    MarshalOptions = moMarshalModifiedOnly
    OnEditError = ADOQuery1EditError
    OnPostError = ADOQuery1PostError
    EnableBCD = False
    ParamCheck = False
    Parameters = <>
    Left = 216
    Top = 1
  end
  object ADOQuery2: TADOQuery
    AutoCalcFields = False
    Connection = dm.ConnectPhoto
    CursorType = ctDynamic
    MarshalOptions = moMarshalModifiedOnly
    Parameters = <>
    Left = 248
  end
end
