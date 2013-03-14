inherited faqhSetEquipmentInfo: TfaqhSetEquipmentInfo
  Width = 745
  Height = 435
  Caption = '设备信息设置'
  inherited pcPages: TRzPageControl
    Width = 745
    Height = 435
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 382
        Width = 741
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 488
        end
        inherited btnChange: TBitBtn [1]
          Left = 574
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 402
        end
        inherited btnDelete: TBitBtn
          Left = 660
          Caption = '&D 注销'
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 741
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 741
        Height = 285
        Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
        ReadOnly = True
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lserial1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '所在区域'
            Width = 77
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备标识'
            Width = 61
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备名称'
            Width = 142
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备物理ID'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '设备机号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备机型'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '服务器端口总数'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt6'
            PickList.Strings = ()
            Title.Caption = '上级设备'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scurrency_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡片结构'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '服务器端口号'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备状态'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '通讯端口号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备类型'
            Width = 98
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstation0'
            PickList.Strings = ()
            Title.Caption = 'IP地址'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '所属子系统'
            Width = 81
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '备注'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'damt5'
            PickList.Strings = ()
            Title.Caption = '设备用途'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt4'
            PickList.Strings = ()
            Title.Caption = '是否支持科目收费'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = '通讯类别'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入批次号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '备注'
            Width = 120
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 741
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 58
          Top = 34
          Width = 48
          Height = 12
          Caption = '所在区域'
        end
        object Label2: TLabel
          Left = 58
          Top = 10
          Width = 48
          Height = 12
          Caption = '设备机型'
        end
        object Label3: TLabel
          Left = 538
          Top = 10
          Width = 48
          Height = 12
          Caption = '设备类型'
        end
        object Label4: TLabel
          Left = 281
          Top = 10
          Width = 60
          Height = 12
          Caption = '所属子系统'
        end
        object WVLabel14: TWVLabel
          Left = 136
          Top = 74
          Width = 48
          Height = 12
          Caption = '设备状态'
          Visible = False
        end
        object Label5: TLabel
          Left = 346
          Top = 74
          Width = 48
          Height = 12
          Caption = '收费方式'
          Visible = False
        end
        object Label6: TLabel
          Left = 58
          Top = 58
          Width = 48
          Height = 12
          Caption = '设备名称'
        end
        object Label7: TLabel
          Left = 281
          Top = 34
          Width = 60
          Height = 12
          Caption = '设备物理ID'
        end
        object Label8: TLabel
          Left = 257
          Top = 58
          Width = 84
          Height = 12
          Caption = '上级设备物理ID'
        end
        object Label9: TLabel
          Left = 525
          Top = 34
          Width = 60
          Height = 12
          Caption = '导入批次号'
        end
        object Label10: TLabel
          Left = 536
          Top = 58
          Width = 48
          Height = 12
          Caption = '设备标识'
        end
        object WVComboBox18: TWVComboBox
          Left = 120
          Top = 6
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 0
          Text = '<查询.机型代码>'
          WorkView = WorkView
          FieldName = '查询.机型代码'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object WVComboBox1: TWVComboBox
          Left = 595
          Top = 6
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 2
          Text = '<查询.设备物理型号>'
          WorkView = WorkView
          FieldName = '查询.设备物理型号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-35'
        end
        object WVComboBox17: TWVComboBox
          Left = 351
          Top = 6
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 1
          Text = '<查询.所属子系统>'
          WorkView = WorkView
          FieldName = '查询.所属子系统'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVComboBox20: TWVComboBox
          Left = 120
          Top = 30
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 3
          Text = '<查询.所在区域>'
          WorkView = WorkView
          FieldName = '查询.所在区域'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-28'
        end
        object WVComboBox3: TWVComboBox
          Left = 200
          Top = 70
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 9
          Text = '<查询.设备状态>'
          Visible = False
          WorkView = WorkView
          FieldName = '查询.设备状态'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*5'
        end
        object WVComboBox19: TWVComboBox
          Left = 404
          Top = 70
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 10
          Text = '<查询.设备物理型号>'
          Visible = False
          WorkView = WorkView
          FieldName = '查询.设备物理型号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*53'
        end
        object WVEdit4: TWVEdit
          Left = 120
          Top = 54
          Width = 125
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 6
          Text = '<查询.设备名称>'
          WorkView = WorkView
          FieldName = '查询.设备名称'
        end
        object WVEdit5: TWVEdit
          Left = 351
          Top = 30
          Width = 125
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 4
          Text = '<查询.设备物理ID>'
          WorkView = WorkView
          FieldName = '查询.设备物理ID'
        end
        object WVEdit6: TWVEdit
          Left = 351
          Top = 54
          Width = 125
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 7
          Text = '<查询.上级设备物理ID>'
          WorkView = WorkView
          FieldName = '查询.上级设备物理ID'
        end
        object WVEdit2: TWVEdit
          Left = 595
          Top = 30
          Width = 125
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<查询.导入批次号>'
          WorkView = WorkView
          FieldName = '查询.导入批次号'
        end
        object WVEdit7: TWVEdit
          Left = 595
          Top = 54
          Width = 125
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 8
          Text = '<查询.设备标识>'
          WorkView = WorkView
          FieldName = '查询.设备标识'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object WVLabel11: TWVLabel [0]
        Left = 572
        Top = 552
        Width = 36
        Height = 12
        Caption = '卡类别'
        Visible = False
      end
      object WVLabel29: TWVLabel [1]
        Left = 280
        Top = 544
        Width = 120
        Height = 12
        Caption = '终端机适用用户卡类别'
        Visible = False
      end
      object WVLabel44: TWVLabel [2]
        Left = 112
        Top = 552
        Width = 48
        Height = 12
        Caption = '读卡密钥'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 376
        Width = 741
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 565
        end
        inherited btnCancel: TBitBtn
          Left = 653
          TabStop = True
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object RzPanel1: TRzPanel
        Left = 0
        Top = 33
        Width = 741
        Height = 343
        Align = alClient
        BorderOuter = fsNone
        Color = 16119543
        TabOrder = 1
        object WVLabel4: TWVLabel
          Left = 57
          Top = 36
          Width = 54
          Height = 12
          Caption = '设备名称*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel43: TWVLabel
          Left = 386
          Top = 110
          Width = 54
          Height = 12
          Caption = '所在区域*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblPhyNo: TWVLabel
          Left = 51
          Top = 110
          Width = 60
          Height = 12
          Caption = '设备物理ID'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblUEqu: TWVLabel
          Left = 57
          Top = 147
          Width = 54
          Height = 12
          Caption = '上级设备*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblSerPortNo: TWVLabel
          Left = 39
          Top = 182
          Width = 72
          Height = 12
          Caption = '服务器端口号'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblSerPortNum: TWVLabel
          Left = 27
          Top = 256
          Width = 84
          Height = 12
          Caption = '服务器端口总数'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblMachineNo: TWVLabel
          Left = 391
          Top = 224
          Width = 48
          Height = 12
          Caption = '设备机号'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel42: TWVLabel
          Left = 374
          Top = 147
          Width = 66
          Height = 12
          Caption = '所属子系统*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblMachineType: TWVLabel
          Left = 57
          Top = 73
          Width = 54
          Height = 12
          Caption = '设备机型*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lbl3: TWVLabel
          Left = 385
          Top = 73
          Width = 54
          Height = 12
          Caption = '设备用途*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel40: TWVLabel
          Left = 385
          Top = 36
          Width = 54
          Height = 12
          Caption = '设备类型*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel17: TWVLabel
          Left = 75
          Top = 218
          Width = 36
          Height = 12
          Caption = 'IP地址'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel2: TWVLabel
          Left = 391
          Top = 261
          Width = 48
          Height = 12
          Caption = '通讯类别'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblPort: TWVLabel
          Left = 51
          Top = 290
          Width = 60
          Height = 12
          Alignment = taRightJustify
          Caption = '通讯端口号'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object btnOpen: TSpeedButton
          Left = 287
          Top = 145
          Width = 19
          Height = 19
          Flat = True
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            00009C310000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE6300009C310000FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300CE9C
            6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C63009C31
            0000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E7009C31
            0000CE630000CE630000CE630000CE6300009C310000FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE630000CE630000CE630000CE630000CE6300009C310000CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E7009C31
            0000CE630000CE630000CE630000CE6300009C310000FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E7009C31
            0000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE6300009C310000FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E7009C31
            00009C310000CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7
            E700FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300CE9C
            6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C
            6300CE9C6300CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
          OnClick = btnOpenClick
        end
        object btnClose: TSpeedButton
          Left = 288
          Top = 144
          Width = 19
          Height = 19
          Flat = True
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF009C3100009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF009C310000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF009C310000CE630000CE6300009C310000CE9C6300CE9C6300CE9C
            6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300FFFFFF00FFFF
            FF009C310000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF009C31
            0000CE630000CE630000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C63009C310000CE63
            0000CE630000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF009C31
            0000CE630000CE630000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
            FF009C310000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF009C310000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF009C310000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C63009C3100009C310000E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00E7E7E700E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C
            6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300}
          Visible = False
          OnClick = btnCloseClick
        end
        object WVLabel3: TWVLabel
          Left = 391
          Top = 184
          Width = 48
          Height = 12
          Caption = '卡片结构'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel5: TWVLabel
          Left = 415
          Top = 290
          Width = 24
          Height = 12
          Alignment = taRightJustify
          Caption = '备注'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object edtEquName: TWVEdit
          Left = 121
          Top = 33
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          ReadOnly = False
          TabOrder = 1
          Text = '<设备名称>'
          WorkView = WorkView
          FieldName = '设备名称'
        end
        object edtPhyNo: TWVEdit
          Left = 121
          Top = 106
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          MaxLength = 30
          ParentFont = False
          ReadOnly = False
          TabOrder = 4
          Text = '<设备物理号>'
          WorkView = WorkView
          FieldName = '设备物理号'
        end
        object edtSerPortNo: TWVEdit
          Left = 120
          Top = 177
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          MaxLength = 22
          ParentFont = False
          ReadOnly = False
          TabOrder = 10
          Text = '<服务器端口号>'
          WorkView = WorkView
          FieldName = '服务器端口号'
        end
        object edtSerPortNum: TWVEdit
          Left = 120
          Top = 252
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          MaxLength = 22
          ParentFont = False
          ReadOnly = False
          TabOrder = 14
          Text = '<服务器端口总数>'
          WorkView = WorkView
          FieldName = '服务器端口总数'
        end
        object edtMachineNo: TWVEdit
          Left = 449
          Top = 218
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          MaxLength = 22
          ParentFont = False
          ReadOnly = False
          TabOrder = 13
          Text = '<机号>'
          WorkView = WorkView
          FieldName = '机号'
        end
        object cbbChildSys: TWVComboBox
          Left = 448
          Top = 143
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 7
          WorkView = WorkView
          FieldName = '所属子系统'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '-32'
        end
        object cbbMachineType: TWVComboBox
          Left = 121
          Top = 71
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 3
          WorkView = WorkView
          FieldName = '机型代码'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '47'
        end
        object cbbUseType: TWVComboBox
          Left = 448
          Top = 69
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 2
          WorkView = WorkView
          FieldName = '设备用途'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '81'
        end
        object cbbEquPhyType: TWVComboBox
          Left = 448
          Top = 31
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 0
          WorkView = WorkView
          FieldName = '设备物理型号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '-35'
        end
        object edtIP: TWVEdit
          Left = 121
          Top = 214
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          MaxLength = 15
          ParentFont = False
          ReadOnly = False
          TabOrder = 12
          Text = '<通信地址>'
          WorkView = WorkView
          FieldName = '通信地址'
        end
        object cbbComm: TWVComboBox
          Left = 449
          Top = 257
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 15
          OnChange = cbbCommChange
          WorkView = WorkView
          FieldName = '通讯类别'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*50'
        end
        object edtCommPortNo: TWVEdit
          Left = 120
          Top = 287
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          ReadOnly = False
          TabOrder = 16
          Text = '<通讯端口>'
          WorkView = WorkView
          FieldName = '通讯端口'
        end
        object cbbArea: TWVComboBox
          Left = 448
          Top = 107
          Width = 188
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '设备所在区域'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '-28'
        end
        object edtUEqu: TWVEdit
          Left = 120
          Top = 144
          Width = 41
          Height = 20
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          MaxLength = 22
          ParentColor = True
          ParentFont = False
          ReadOnly = True
          TabOrder = 8
          Text = '<上级设备物理号>'
          OnChange = edtUEquChange
          WorkView = WorkView
          FieldName = '上级设备物理号'
        end
        object edtParName: TEdit
          Left = 160
          Top = 144
          Width = 129
          Height = 20
          Color = 16119543
          Enabled = False
          ReadOnly = True
          TabOrder = 9
        end
        object WVComboBox4: TWVComboBox
          Left = 449
          Top = 179
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 11
          OnChange = cbbCommChange
          WorkView = WorkView
          FieldName = '卡片结构'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*48'
        end
        object WVEdit3: TWVEdit
          Left = 448
          Top = 287
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          ReadOnly = False
          TabOrder = 17
          Text = '<备注>'
          WorkView = WorkView
          FieldName = '备注'
        end
        object TreeView1: TTreeView
          Left = 305
          Top = 142
          Width = 56
          Height = 123
          Indent = 19
          TabOrder = 6
          Visible = False
          OnDblClick = btnCloseClick
          OnExit = TreeView1Exit
        end
      end
      object pnl1: TRzPanel
        Left = 0
        Top = 0
        Width = 741
        Height = 33
        Align = alTop
        BorderInner = fsGroove
        BorderOuter = fsNone
        Color = 16119543
        TabOrder = 0
        object WVLabel1: TWVLabel
          Left = 53
          Top = 13
          Width = 48
          Height = 12
          Caption = '设备标识'
          Visible = False
        end
        object WVEdit1: TWVEdit
          Left = 120
          Top = 8
          Width = 125
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<设备标识>'
          Visible = False
          WorkView = WorkView
          FieldName = '设备标识'
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 419
    Top = 55
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '返回码'
        Caption = '返回码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = '@Return'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'vsmess'
      end
      item
        Name = '操作类别.增加'
        Caption = '操作类别.增加'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end
      item
        Name = '操作类别.删除'
        Caption = '操作类别.删除'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '操作类别.修改'
        Caption = '操作类别.修改'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '查询.导入批次号'
        Caption = '查询.导入批次号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.机型代码'
        Caption = '查询.机型代码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sbank_code'
      end
      item
        Name = '查询.所在区域'
        Caption = '查询.所在区域'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lserial1'
      end
      item
        Name = '查询.设备物理型号'
        Caption = '查询.设备物理型号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lbank_acc_type'
      end
      item
        Name = '查询.所属子系统'
        Caption = '查询.所属子系统'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lserial0'
      end
      item
        Name = '查询.设备状态'
        Caption = '查询.设备状态'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol4'
      end
      item
        Name = '查询.收费方式'
        Caption = '查询.收费方式'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'damt0'
      end
      item
        Name = '查询.设备名称'
        Caption = '查询.设备名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.设备物理ID'
        Caption = '查询.设备物理ID'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.上级设备物理ID'
        Caption = '查询.上级设备物理ID'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.设备标识'
        Caption = '查询.设备标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '设备标识'
        Caption = '设备标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '设备名称'
        Caption = '设备名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '设备物理型号'
        Caption = '设备物理型号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '机型代码'
        Caption = '机型代码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '设备用途'
        Caption = '设备用途'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'damt5'
      end
      item
        Name = '上级设备物理号'
        Caption = '上级设备物理号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'damt6'
      end
      item
        Name = '设备物理号'
        Caption = '设备物理号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 30
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sphone3'
      end
      item
        Name = '设备所在区域'
        Caption = '设备所在区域'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lserial1'
      end
      item
        Name = '所属子系统'
        Caption = '所属子系统'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '通信地址'
        Caption = '通信地址'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 15
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sstation0'
      end
      item
        Name = '服务器端口号'
        Caption = '服务器端口号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '服务器端口总数'
        Caption = '服务器端口总数'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = '机号'
        Caption = '机号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '通讯类别'
        Caption = '通讯类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '通讯端口'
        Caption = '通讯端口'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code2'
      end
      item
        Name = '卡片结构'
        Caption = '卡片结构'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scurrency_type'
      end
      item
        Name = '是否支持科目收费'
        Caption = '是否支持科目收费'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '备注'
        Caption = '备注'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'vsvarstr0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|设备名称|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 355
    Top = 55
  end
  inherited QueryRequest: TWVRequest
    ID = '可编辑设备查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备所在区域'
        FieldName = '查询.所在区域'
      end
      item
        ParamName = '机型代码'
        FieldName = '查询.机型代码'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '查询.设备物理型号'
      end
      item
        ParamName = '所属子系统'
        FieldName = '查询.所属子系统'
      end
      item
        ParamName = '设备状态'
        FieldName = '查询.设备状态'
      end
      item
        ParamName = '收费方式'
        FieldName = '查询.收费方式'
      end
      item
        ParamName = '设备名称'
        FieldName = '查询.设备名称'
      end
      item
        ParamName = '设备物理ID'
        FieldName = '查询.设备物理ID'
      end
      item
        ParamName = '上级设备物理ID'
        FieldName = '查询.上级设备物理ID'
      end
      item
        ParamName = '导入批次号'
        FieldName = '查询.导入批次号'
      end
      item
        ParamName = '设备标识'
        FieldName = '查询.设备标识'
      end>
    Left = 448
    Top = 24
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end
      item
        FieldName = 'damt6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '5'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'damt5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '81'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '50'
      end>
    Left = 391
    Top = 55
  end
  inherited AddRequest: TWVRequest
    ID = '设备信息设置.增加'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '机型代码'
        FieldName = '机型代码'
      end
      item
        ParamName = '设备用途'
        FieldName = '设备用途'
      end
      item
        ParamName = '上级设备物理号'
        FieldName = '上级设备物理号'
      end
      item
        ParamName = '设备物理号'
        FieldName = '设备物理号'
      end
      item
        ParamName = '设备所在区域'
        FieldName = '设备所在区域'
      end
      item
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '通信地址'
        FieldName = '通信地址'
      end
      item
        ParamName = '是否支持科目收费'
        FieldName = '是否支持科目收费'
      end
      item
        ParamName = '服务器端口号'
        FieldName = '服务器端口号'
      end
      item
        ParamName = '服务器端口总数'
        FieldName = '服务器端口总数'
      end
      item
        ParamName = '机号'
        FieldName = '机号'
      end
      item
        ParamName = '通讯类别'
        FieldName = '通讯类别'
      end
      item
        ParamName = '通讯端口'
        FieldName = '通讯端口'
      end
      item
        ParamName = '卡片结构'
        FieldName = '卡片结构'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 364
    Top = 24
  end
  inherited DeleteRequest: TWVRequest
    ID = '设备信息设置.删除'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备标识'
        FieldName = '设备标识'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '机型代码'
        FieldName = '机型代码'
      end
      item
        ParamName = '设备用途'
        FieldName = '设备用途'
      end
      item
        ParamName = '上级设备物理号'
        FieldName = '上级设备物理号'
      end
      item
        ParamName = '设备物理号'
        FieldName = '设备物理号'
      end
      item
        ParamName = '设备所在区域'
        FieldName = '设备所在区域'
      end
      item
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '通信地址'
        FieldName = '通信地址'
      end
      item
        ParamName = '是否支持科目收费'
        FieldName = '是否支持科目收费'
      end
      item
        ParamName = '服务器端口号'
        FieldName = '服务器端口号'
      end
      item
        ParamName = '服务器端口总数'
        FieldName = '服务器端口总数'
      end
      item
        ParamName = '机号'
        FieldName = '机号'
      end
      item
        ParamName = '通讯类别'
        FieldName = '通讯类别'
      end
      item
        ParamName = '通讯端口'
        FieldName = '通讯端口'
      end
      item
        ParamName = '卡片结构'
        FieldName = '卡片结构'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 392
    Top = 24
  end
  inherited ChangeRequest: TWVRequest
    ID = '设备信息设置.修改'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备标识'
        FieldName = '设备标识'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '机型代码'
        FieldName = '机型代码'
      end
      item
        ParamName = '设备用途'
        FieldName = '设备用途'
      end
      item
        ParamName = '上级设备物理号'
        FieldName = '上级设备物理号'
      end
      item
        ParamName = '设备物理号'
        FieldName = '设备物理号'
      end
      item
        ParamName = '设备所在区域'
        FieldName = '设备所在区域'
      end
      item
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '通信地址'
        FieldName = '通信地址'
      end
      item
        ParamName = '是否支持科目收费'
        FieldName = '是否支持科目收费'
      end
      item
        ParamName = '服务器端口总数'
        FieldName = '服务器端口总数'
      end
      item
        ParamName = '服务器端口号'
        FieldName = '服务器端口号'
      end
      item
        ParamName = '机号'
        FieldName = '机号'
      end
      item
        ParamName = '通讯端口'
        FieldName = '通讯端口'
      end
      item
        ParamName = '通讯类别'
        FieldName = '通讯类别'
      end
      item
        ParamName = '卡片结构'
        FieldName = '卡片结构'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 420
    Top = 24
  end
  inherited WVDataSource: TWVDataSource
    Left = 475
    Top = 55
  end
  inherited alDatasetActions: TActionList
    Left = 447
    Top = 55
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView
    ID = '可编辑设备查询2'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备所在区域'
        FieldName = '查询.所在区域'
      end
      item
        ParamName = '机型代码'
        FieldName = '查询.机型代码'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '查询.设备物理型号'
      end
      item
        ParamName = '所属子系统'
        FieldName = '查询.所属子系统'
      end
      item
        ParamName = '设备状态'
        FieldName = '查询.设备状态'
      end
      item
        ParamName = '收费方式'
        FieldName = '查询.收费方式'
      end>
    AfterExec = CheckReturnData
    Left = 320
    Top = 56
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView1
    ID = '设备关键字查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备标识'
        FieldName = '设备标识'
      end>
    AfterExec = CheckReturnData
    Left = 256
    Top = 24
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '返回码'
        Caption = '返回码'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = '@Return'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'vsmess'
      end
      item
        Name = '设备标识'
        Caption = '设备标识'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end
      item
        MonitorValueChangedFields = '|设备名称|'
      end>
    Left = 299
    Top = 23
  end
end
