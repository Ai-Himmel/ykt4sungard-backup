object OperatorForm: TOperatorForm
  Left = 192
  Top = 107
  Width = 683
  Height = 479
  Caption = '操作员设置'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 224
    Top = 40
    Width = 78
    Height = 13
    AutoSize = False
    Caption = '操作员代码：'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 224
    Top = 64
    Width = 78
    Height = 13
    AutoSize = False
    Caption = '操作员名称：'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 675
    Height = 445
    Align = alClient
    BevelOuter = bvNone
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 224
      Top = 32
      Width = 78
      Height = 13
      AutoSize = False
      Caption = '*操作员代码：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 224
      Top = 64
      Width = 78
      Height = 13
      AutoSize = False
      Caption = '*操作员名称：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 232
      Top = 96
      Width = 78
      Height = 13
      AutoSize = False
      Caption = '操作员电话：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 232
      Top = 128
      Width = 78
      Height = 13
      AutoSize = False
      Caption = '操作员手机：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 232
      Top = 160
      Width = 78
      Height = 13
      AutoSize = False
      Caption = 'EMail：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 232
      Top = 192
      Width = 78
      Height = 13
      AutoSize = False
      Caption = '生效时间：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 232
      Top = 224
      Width = 78
      Height = 13
      AutoSize = False
      Caption = '失效时间：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 232
      Top = 256
      Width = 78
      Height = 13
      AutoSize = False
      Caption = '登陆密码：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label13: TLabel
      Left = 232
      Top = 288
      Width = 78
      Height = 13
      AutoSize = False
      Caption = '复核密码：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object DBGrid1: TDBGrid
      Left = 0
      Top = 0
      Width = 193
      Height = 445
      Align = alLeft
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -14
      TitleFont.Name = '宋体'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'OPER_CODE'
          Title.Alignment = taCenter
          Title.Caption = '代码'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'OPER_NAME'
          Title.Alignment = taCenter
          Title.Caption = '名称'
          Width = 90
          Visible = True
        end>
    end
    object DBEdit1: TDBEdit
      Left = 320
      Top = 24
      Width = 185
      Height = 22
      DataField = 'OPER_CODE'
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      TabOrder = 1
    end
    object DBEdit2: TDBEdit
      Left = 320
      Top = 56
      Width = 185
      Height = 22
      DataField = 'OPER_NAME'
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      TabOrder = 2
    end
    object DBEdit3: TDBEdit
      Left = 320
      Top = 88
      Width = 185
      Height = 22
      DataField = 'PHONE'
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      TabOrder = 3
    end
    object DBEdit4: TDBEdit
      Left = 320
      Top = 120
      Width = 185
      Height = 22
      DataField = 'MOBILE'
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      TabOrder = 4
    end
    object DBEdit5: TDBEdit
      Left = 320
      Top = 152
      Width = 185
      Height = 22
      DataField = 'EMAIL'
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      TabOrder = 5
    end
    object DBEdit6: TDBEdit
      Left = 320
      Top = 184
      Width = 185
      Height = 22
      Hint = '格式：YYYYMMDDHHMMSS'
      DataField = 'LOGIN_TIME'
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
    end
    object DBEdit7: TDBEdit
      Left = 320
      Top = 216
      Width = 185
      Height = 22
      Hint = '格式：YYYYMMDDHHMMSS'
      DataField = 'LOGOUT_TIME'
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
    end
    object btnADd: TButton
      Left = 224
      Top = 408
      Width = 75
      Height = 25
      Caption = '添  加'
      TabOrder = 8
      OnClick = btnADdClick
    end
    object btnDelete: TButton
      Left = 312
      Top = 408
      Width = 75
      Height = 25
      Caption = '删  除'
      TabOrder = 9
      OnClick = btnDeleteClick
    end
    object btnSave: TButton
      Left = 400
      Top = 408
      Width = 75
      Height = 25
      Caption = '保  存'
      TabOrder = 10
      OnClick = btnSaveClick
    end
    object btnExit: TButton
      Left = 560
      Top = 408
      Width = 75
      Height = 25
      Caption = '退  出'
      TabOrder = 11
      OnClick = btnExitClick
    end
    object edtrepwd: TEdit
      Left = 320
      Top = 280
      Width = 185
      Height = 22
      ImeName = '拼音加加集合版'
      PasswordChar = '*'
      TabOrder = 12
    end
    object edtpwd: TDBEdit
      Left = 320
      Top = 248
      Width = 185
      Height = 22
      DataField = 'PWD'
      DataSource = DataSource1
      ImeName = '拼音加加集合版'
      PasswordChar = '*'
      TabOrder = 13
    end
    object chkuse: TCheckBox
      Left = 232
      Top = 312
      Width = 73
      Height = 17
      Caption = '是否可用'
      TabOrder = 14
      OnClick = chkuseClick
    end
    object cbQuery: TCheckBox
      Left = 528
      Top = 312
      Width = 57
      Height = 17
      Caption = '查询'
      TabOrder = 15
    end
    object cbEditData: TCheckBox
      Left = 408
      Top = 312
      Width = 113
      Height = 17
      Caption = '修改基本信息'
      TabOrder = 16
    end
    object cbLoadPic: TCheckBox
      Left = 320
      Top = 312
      Width = 57
      Height = 17
      Caption = '取照片'
      TabOrder = 17
    end
    object cbExpData: TCheckBox
      Left = 408
      Top = 384
      Width = 113
      Height = 17
      Caption = '导出基本信息'
      TabOrder = 18
    end
    object cbExpPic: TCheckBox
      Left = 320
      Top = 384
      Width = 73
      Height = 17
      Caption = '导出照片'
      TabOrder = 19
    end
    object cbPrint: TCheckBox
      Left = 528
      Top = 336
      Width = 57
      Height = 17
      Caption = '打印'
      TabOrder = 20
    end
    object cbImpPic: TCheckBox
      Left = 320
      Top = 360
      Width = 73
      Height = 17
      Caption = '导入照片'
      TabOrder = 21
    end
    object cbImpData: TCheckBox
      Left = 408
      Top = 360
      Width = 113
      Height = 17
      Caption = '导入基本信息'
      TabOrder = 22
    end
    object cbMakeCard: TCheckBox
      Left = 320
      Top = 336
      Width = 97
      Height = 17
      Caption = '制卡管理'
      TabOrder = 23
    end
    object cbDelData: TCheckBox
      Left = 408
      Top = 336
      Width = 105
      Height = 17
      Caption = '删除基本信息'
      TabOrder = 24
    end
    object chkMakeCard: TCheckBox
      Left = 528
      Top = 360
      Width = 57
      Height = 17
      Caption = '制卡'
      TabOrder = 25
    end
    object chkPersonAdd: TCheckBox
      Left = 528
      Top = 384
      Width = 81
      Height = 17
      Caption = '人员添加'
      TabOrder = 26
    end
  end
  object DataSource1: TDataSource
    DataSet = ADOTable1
    Left = 72
    Top = 64
  end
  object ADOTable1: TADOTable
    Connection = dm.ConnectPhoto
    CursorType = ctStatic
    AfterScroll = ADOTable1AfterScroll
    TableName = 'photo.T_PIF_OPERATOR'
    Left = 112
    Top = 64
  end
  object ADOQuery1: TADOQuery
    Connection = dm.ConnectPhoto
    Parameters = <>
    Left = 72
    Top = 104
  end
end
