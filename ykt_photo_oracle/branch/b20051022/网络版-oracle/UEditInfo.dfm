object FrmEditInfo: TFrmEditInfo
  Left = 181
  Top = 203
  Width = 626
  Height = 244
  Caption = '个人信息修改'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 40
    Top = 69
    Width = 40
    Height = 13
    Caption = '姓  名'
  end
  object Label4: TLabel
    Left = 40
    Top = 36
    Width = 46
    Height = 13
    Caption = '学工号 '
  end
  object Label5: TLabel
    Left = 40
    Top = 100
    Width = 39
    Height = 13
    Caption = '学　院'
  end
  object Label16: TLabel
    Left = 40
    Top = 132
    Width = 47
    Height = 13
    Caption = '专  业 '
  end
  object Label6: TLabel
    Left = 312
    Top = 100
    Width = 40
    Height = 13
    Caption = '类  别'
  end
  object Label23: TLabel
    Left = 312
    Top = 36
    Width = 39
    Height = 13
    Caption = '身份证'
  end
  object Label1: TLabel
    Left = 336
    Top = 195
    Width = 52
    Height = 13
    Caption = '入学年级'
    Visible = False
  end
  object Label2: TLabel
    Left = 312
    Top = 67
    Width = 52
    Height = 13
    Caption = '现在年级'
  end
  object Edit1: TDBEdit
    Left = 96
    Top = 32
    Width = 193
    Height = 21
    DataField = 'STUEMP_NO'
    DataSource = DataSource1
    Enabled = False
    ImeName = '拼音加加集合版'
    TabOrder = 0
  end
  object Edit2: TDBEdit
    Left = 96
    Top = 64
    Width = 193
    Height = 21
    DataField = 'STUEMP_NAME'
    DataSource = DataSource1
    ImeName = '拼音加加集合版'
    TabOrder = 1
  end
  object Edit6: TDBEdit
    Left = 368
    Top = 32
    Width = 193
    Height = 21
    DataField = 'ID2'
    DataSource = DataSource1
    ImeName = '拼音加加集合版'
    TabOrder = 2
  end
  object Button1: TButton
    Left = 336
    Top = 160
    Width = 75
    Height = 25
    Cancel = True
    Caption = '关  闭'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 224
    Top = 160
    Width = 75
    Height = 25
    Caption = '保存修改'
    TabOrder = 4
    OnClick = Button2Click
  end
  object ComboBox1: TDBComboBox
    Left = 96
    Top = 96
    Width = 193
    Height = 21
    DataField = 'DEPT_NAME'
    DataSource = DataSource1
    ImeName = '拼音加加集合版'
    ItemHeight = 13
    TabOrder = 5
    OnChange = ComboBox1Change
  end
  object ComboBox2: TDBComboBox
    Left = 96
    Top = 128
    Width = 193
    Height = 21
    DataField = 'S_CODE'
    DataSource = DataSource1
    ImeName = '拼音加加集合版'
    ItemHeight = 13
    TabOrder = 6
    OnChange = ComboBox2Change
  end
  object ComboBox4: TDBComboBox
    Left = 128
    Top = 184
    Width = 193
    Height = 21
    ImeName = '拼音加加集合版'
    ItemHeight = 13
    TabOrder = 7
    Visible = False
  end
  object ComboBox5: TDBComboBox
    Left = 40
    Top = 184
    Width = 193
    Height = 21
    ImeName = '拼音加加集合版'
    ItemHeight = 13
    TabOrder = 8
    Visible = False
  end
  object Edit4: TDBEdit
    Left = 392
    Top = 192
    Width = 193
    Height = 21
    ImeName = '拼音加加集合版'
    TabOrder = 9
    Visible = False
  end
  object DBEdit1: TDBEdit
    Left = 368
    Top = 64
    Width = 193
    Height = 21
    DataField = 'C_GRADE'
    DataSource = DataSource1
    ImeName = '拼音加加集合版'
    TabOrder = 10
  end
  object dbcbbtype: TDBComboBox
    Left = 368
    Top = 96
    Width = 193
    Height = 21
    DataField = 'cut_type'
    DataSource = DataSource1
    ImeName = '拼音加加集合版'
    ItemHeight = 13
    TabOrder = 11
    OnChange = ComboBox1Change
  end
  object ADOQuery1: TADOQuery
    Connection = dm.ConnectPhoto
    LockType = ltUnspecified
    Parameters = <>
    Left = 432
    Top = 137
  end
  object ADOQuery2: TADOQuery
    Connection = dm.ConnectPhoto
    LockType = ltUnspecified
    Parameters = <>
    Left = 472
    Top = 137
  end
  object ADOQueryEdit: TADOQuery
    Connection = dm.ConnectPhoto
    CursorType = ctStatic
    MarshalOptions = moMarshalModifiedOnly
    Parameters = <>
    SQL.Strings = (
      'select * from t_cif_photo')
    Left = 336
    Top = 136
  end
  object DataSource1: TDataSource
    DataSet = ADOQueryEdit
    Left = 376
    Top = 136
  end
end
