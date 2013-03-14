unit KSClientConsts;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSClientConsts
   <What>前台框架程序中使用到的常量
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses LogFile, DataTypes, Graphics, Messages,Classes;

const

  // 1、框架级别的常量定义 **********************************************

  SUIClassFactoryCategory = 'UIClassFactory';

  SUIShareObjList = 'UIShareObjList'; //(IN TRADER)

  // Common Action ID
  caPrint = 1;
  caAdjustGrid = 2;
  caSearchData = 3;
  caNextSearchData = 4;
  caFocusGrid = 5;
  //　wsn 20041013单独定义追加查询
  caSmartSearchData = 6;

  caDebugDataSource = 100;
  caDebugDataset = 101;
  caDebugWorkView = 102;
  caDebugUI = 103;

  // 系统通知消息
  snPrinterChanged = 1;
  snDateUpdated = 2;

  KS_ShareBase = $A000; //(IN TRADER)
  KS_AskMainFrame = KS_ShareBase + 1; //(IN TRADER)
  KS_AnswerMainFrame = KS_ShareBase + 2; //(IN TRADER)

  KS_AddListView = KS_ShareBase + 3; //(IN TRADER)发送给MainFrame，完成填充

  KS_AskHandle = KS_ShareBase + 4; //(IN TRADER)由MainForm寻找界面Handle
  KS_AnswerHandle = KS_ShareBase + 5; //(IN TRADER)由MainForm找到Handle，返回
  KS_DoHandle = KS_ShareBase + 6; //(IN TRADER)当Handle找到后，处理相应的信息
  KS_DeleteEntrust = KS_ShareBase + 7; //(IN TRADER)申请创建撤单界面
  KS_DoDeleteEntrust = KS_ShareBase + 8; //(IN TRADER)执行撤单
  KS_DoAddCust = KS_ShareBase + 9; //(IN TRADER)执行添加客户号列表
  KS_Entrust = KS_ShareBase + 10; //(IN TRADER)根据行情下单
  KS_SelectHQ = KS_ShareBase + 11; //(IN TRADER)根据下单选择行情
  //  KS_DelAllQryUIs = KS_ShareBase + 12;   //(IN TRADER)交易员系统查询客户号后，所有查询界面要释放掉。
  KS_KillHold = KS_ShareBase + 13; //(IN TRADER)根据持仓下单

  KS_SetCustPara = KS_ShareBase + 15; //(IN MANAGER) 设置客户参数
  //rding,20040608
  KS_GetDeleteEntrust = KS_ShareBase + 16;
    //根据委托号获取该委托号对应的单的信息，如果委托号为空，则返回所有
  //rding,20040608,end
  //交易员系统MainFrame里面的其他模块的Handle列表的索引
  TraderEntrustHdle = 1; //(IN TRADER)
  Pre_EntrustHdle = 2; //(IN TRADER)
  DeleteEntrustHdle = 3; //(IN TRADER)

  // 数据字典条目(DataEntry)
  deNotUsed = -100; // 不用的
  deSystemParams = -101; // 系统参数
  deDictionaryCategory = -102; // 数据字典条目
  deBoolean = -103; // Boolean类型（0否，1是）
  deBusinessFlag = -104; // 业务标志

  deExchangeKind = -25; //全部品种
  deExchangeSeat = -23; //全部席位
  deBank = -3; // 银行
  deDepart = -8; // 营业部

  deStandardFirst = 1000;
  deStandardLast = 1900;
  deAccountStatus = 1000; //帐户状态
  deCheckType = 1011; //校验方式
  deAccountType = 1012; //帐号类别: 客户号,沪A股东代码
  deAgentType = 1020; //代理方式
  deBusinessCtrl = 1021; //业务控制
  deWithDrawType = 1022; //提款方式
  deCustomerProp = 1023; //客户标志
  deSex = 1030; //性别
  deEducation = 1031; //学历
  dePaymentMonthly = 1032; //月收入
  deNation = 1040; //国籍地区
  deCertType = 1041; //证件类别
  deCenterCustomerType = 1042; //总部统计类别
  deDepartCustomerType = 1043; //营业部客户类别
  deCustomerGroup = 1044; //客户组别
  deDestroyCondition = 1060; //销户条件
  deAwardProp = 1062; //奖惩指标
  deAwardSource = 1063; //奖惩来源
  deUnionType = 1064; //联合类型
  deOperationType = 1065; //操作类型
  deMethodNo = 1066; //方法编号
  deJoin = 1067; //连接关系
  deCompare = 1068; //比较操作符
  deMethod = 1069; //方法内容
  deAwardType = 1070; //奖惩类别
  deClassify = 1071; //分类类别
  deType = 1072; //类型标志
  deSum = 1073; //统计方式
  deCurrency = 1101; //货币类型
  deCheckStatus = 1102; //支票状态
  deTransferStatus = 1103; //转帐状态
  deGetType = 1104; //支取类型
  deReserveStatus = 1105; //预约使用状态
  de1106 = 1106; //融资方式
  de1107 = 1107; //融资状态
  de1108 = 1108; //贷款类别
  deEntrustMethod = 1201; //委托方式
  deBusinessType = 1202; //业务类别
  de1202 = deBusinessType;
  deEntrustStatus = 1203; //委托状态
  de1203 = deEntrustStatus;
  deBuySell = 1204; //买卖方向
  de1205 = 1205; //委托属性
  deSecuritiesType = 1206; //证券类别
  de1207 = 1207; //申报级别
  deAccountKind = 1208; //帐户类别
  de1209 = 1209; //代码级别
  de1210 = 1210; //股东权限
  de1211 = 1211; //股东限制
  de1212 = 1212; //成交类型
  de1213 = 1213; //成交状态
  de1214 = 1214; //委托种类
  de1215 = 1215; //代理配股类型
  de1216 = 1216; //转股回售
  de1217 = 1217; //国债回购
  de1218 = 1218; //预埋指标类别
  de1219 = 1219; //预埋比较操作符
  de1220 = 1220; //预埋连接关系符
  de1221 = 1221; //代理新股类型
  de1222 = 1222; //委托价格类别
  de1223 = 1223; //委托标志
  de1224 = 1224; //资金清算方式
  de1225 = 1225; //股票清算方式
  de1250 = 1250; //抵押状态
  de1251 = 1251; //申报方向
  de1252 = 1252; //资金方向
  de1253 = 1253; //证券方向
  de1254 = 1254; //资金冻结方式
  de1255 = 1255; //资金实时回转标志
  de1256 = 1256; //证券实时回转标志
  de1257 = 1257; //配对方式
  de1258 = 1258; //缺省价格类型
  de1259 = 1259; //限价类型
  de1260 = 1260; //基价类型
  de1261 = 1261; //计算方向
  de1262 = 1262; //计算类型
  de1263 = 1263; //证券级别
  de1264 = 1264; //能否修改
  de1265 = 1265; //停牌标志
  de1266 = 1266; //固定价格标志
  de1267 = 1267; //固定数量标志
  de1268 = 1268; //计算市值标志
  de1269 = 1269; //托管标志
  de1270 = 1270; //记库存标志
  de1271 = 1271; //买卖标志
  de1272 = 1272; //除权除息标志
  de1273 = 1273; //交易状态
  de1274 = 1274; //行业种类
  de1275 = 1275; //流通类型
  de1276 = 1276; //证券统计类别
  deProcMode = 1280; //委托处理模式

  deMarket = 1301; //市场代码
  de1302 = 1302; //行情模式
  de1303 = 1303; //申报模式
  de1304 = 1304; //回报模式
  deCustomerTemplate = 1305; //客户模板
  de1306 = 1306; //业务科目
  de1307 = 1307; //业务进行状态
  de1308 = 1308; //系统状态
  de1330 = 1330; //交易状态
  de1350 = 1350; //已开通交易类别
  de1351 = 1351; //时间种类
  de1352 = 1352; //撤单是否允许
  de1353 = 1353; //卡的种类
  de1354 = 1354; //席位连通允许
  de1355 = 1355; //存取级别
  de1356 = 1356; //数据类型
  de1357 = 1357; //变动类别
  deWorkStatus = 1360; // 营业部状态/职工工作状态
  deFrontFree = 1401; //前台收费
  de2FeeCode = 1402; //二级费用代码
  de1402 = de2FeeCode;
  de1FeeCode = 1403; //一级费用代码
  de1403 = de1FeeCode;
  de1404 = 1404; //清算模式
  deStation = 1501; //岗位
  de1502 = 1502; //柜员权限
  de1504 = 1504; //柜员类型
  de1505 = 1505; //柜员操作类型
  de1506 = 1506; //缺省营业部岗位
  de1507 = 1507; //缺省客户类别
  de1508 = 1508; //缺省客户组别
  de1509 = 1509; //缺省客户模板
  deBankCode = 1601; //银行代码
  de1602 = 1602; //请求类别
  de1603 = 1603; //银行帐户类别
  de1604 = 1604; //银行发送业务标志
  de1605 = 1605; //银行资金方式
  de1606 = 1606; //银行帐户限制
  de1607 = 1607; //银行帐户权限
  de1608 = 1608; //银行委托状态
  de1609 = 1609; //发起方代码
  de1610 = 1610; //特殊控制
  de1611 = 1611; //日终清算方式
  de1612 = 1612; //文件类型
  de1613 = 1613; //处理模式
  de1614 = 1614; //处理标志
  de1615 = 1615; //文件子类
  deBankType = 1616; //银行类别
  de1617 = 1617; //开户连通标志
  deAera = 1620; //地区代码
  de1701 = 1701; //经纪人权限
  de1702 = 1702; //经纪人操作角色
  de1703 = 1703; //经纪人授权角色
  de1704 = 1704; //经纪人委托方式
  de1705 = 1705; //经纪人类别
  de1801 = 1801; //前台费用代码
  de1802 = 1802; //费用分成标志
  de1803 = 1803; //分笔计算标志
  de1804 = 1804; //经纪提成标志
  de1806 = 1806; //按分支分成
  de1807 = 1807; //分段计算标志
  de1808 = 1808; //分资金帐号计算标志
  de1809 = 1809; //提成触发方式
  de1810 = 1810; //指标类别
  de1811 = 1811; //平均标志
  de1812 = 1812; //买卖类别
  de1813 = 1813; //合并标志
  de1814 = 1814; //费用类型
  de1815 = 1815; //计算方式
  de1816 = 1816; //折扣方式
  de1819 = 1819; //收费方式
  de1820 = 1820; //收费档次
  de1282 = 1282; //扣款标志
  de1283 = 1283; //返款标志
  de1284 = 1284; //协议密码类型
  de1285 = 1285; //券商收费模式
  de1286 = 1286; //配售协议状态

  deLO_FLAG = 1901; //开平仓标志
  deSH_FLAG = 1902; //投保标记

  deTxStation = 1005; //交易所代码

  de0001 = 0001;
  de0002 = 0002;
  de0003 = 0003;
  de0004 = 0004;
  de0005 = 0005;
  de0006 = 0006;
  de0007 = 0007;
  de0008 = 0008;
  de0009 = 0009;
  de0010 = 0010;
  de0011 = 0011;
  de0012 = 0012;
  de0013 = 0013;
  de0014 = 0014;
  de0015 = 0015;
  de0016 = 0016;
  de0017 = 0017;
  de0018 = 0018;
  de0019 = 0019;
  de0020 = 0020;
  de0021 = 0021;
  de0022 = 0022;
  de0023 = 0023;
  de0024 = 0024;
  de0025 = 0025;
  de0026 = 0026;
  de0027 = 0027;
  de0028 = 0028;
  de0029 = 0029;
  de0030 = 0030;
  de0031 = 0031;
  de0032 = 0032;
  de0033 = 0033;
  de0034 = 0034;
  de0035 = 0035;
  de0036 = 0036;
  de0037 = 0037;
  de0038 = 0038;
  de0039 = 0039;

  de1001 = 1001;
  de1002 = 1002;
  de1003 = 1003;
  de1004 = 1004;
  de1005 = 1005;
  de1006 = 1006;
  de1007 = 1007;
  de1008 = 1008;
  de1009 = 1009;
  de1010 = 1010;
  de1011 = 1011;
  de1012 = 1012;
  de1013 = 1013;
  de1014 = 1014;
  de1015 = 1015;
  de1016 = 1016;
  de1017 = 1017;
  de1018 = 1018;
  de1019 = 1019;
  de1020 = 1020;
  de1021 = 1021;
  de1022 = 1022;
  de1023 = 1023;
  de1024 = 1024;
  de1025 = 1025;

  //一些需要动态确定内容的数据字典
  deExchange = -21;
  deOperator_CustNO = -1000;
  deExchange_Kind = -1001;
  deExchange_Seat = deExchange_Kind - 100;

  // 总部营业部代码
  CenterDepartNo = '000';
  // 表示所有营业部的代码
  AllDepartsNo = '';
  // 表示所有/不选
  EmptyIdObjectCode = '';
  EmptyIdObjectName = '';
  // deBoolean       = -103
  IdForFalse = '0';
  IdForTrue = '1';
  NameForFalse = '否';
  NameForTrue = '是';

  // Log Category
  lcRegisterUI = 9;
  lcKSClient = lcAppLogStart + 10;
  lcKSClientStart = lcKSClient + 1;
  lcKSClientShutDown = lcKSClient + 2;
  lcKSClientLoadPackage = lcKSClient + 3;
  lcKSClientUnLoadPackage = lcKSClient + 4;
  lcKsClientPreQuery = lcKSClient + 5;

  // 系统变量名称，属于Context
//  svDeviceSign        = ''
  svDepartNoName = '#营业部代码'; //wsn　等同于子系统标志号
  svDepartNoType = kdtInteger;
  svDepartNameName = '#营业部名称';
  svDepartNameType = kdtString;
  svOperatorNoName = '#职工代码';
  svOperatorNoType = kdtString;
  svOperatorNameName = '#职工姓名';
  svOperatorNameType = kdtString;
  svOperatorPasswordName = '#职工密码';
  svOperatorPasswordType = kdtString;
  svOperatorMenuAuthName = '#职工菜单权限';
  svOperatorMenuAuthType = kdtString;
  svLoginStatusName = '#登录状态';
  svLoginStatusType = kdtBoolean;
  svMACAddressName = '#网卡地址'; //wsn 等同于动态密钥
  svMACAddressType = kdtString;
  svSystemDateName = '#系统日期';
  svSystemDateType = kdtString;
  svWorkDateName = '#工作日期';
  svWorkDateType = kdtString;
  svReportDateName = '#报表日期';
  svReportDateType = kdtString;
  svProhibitMarketsName = '#禁止市场集合';
  svProhibitMarketsType = kdtString;
  svProhibitMoneyName = '#禁止币种集合';
  svProhibitMoneyType = kdtString;
  svCompanyNameName = '#公司名称';
  svCompanyNameType = kdtString;

  //ADD BY ZKJ 2003-11-30
  svSeatNoName = '#席位号'; //(IN REPORT)
  svSeatNoType = kdtString; //(IN REPORT)

  //ADD BY ZKJ 2003-12-03
  svBatchNoName = '#批次号'; //(IN REPORT)
  svBatchNoType = kdtInteger; //(IN REPORT)

  svFuncNoName = '#主功能号'; //(IN REPORT)
  svFuncNoType = kdtInteger; //(IN REPORT)

  //rding,20040602,增加“系统时间”
  svSystemTimeName = '#系统时差';
  svSystemTimeType = kdtInteger;

  // 标准命令对象的参数
  cpReturnCodeParamName = '返回码';
  cpReturnMessageParamName = '返回信息';
  cpReturnEmptyDataSet = '查询结果为空';

  // DirKey(关于本地目录的设置)
  dkStart = 0;
  dkBase = 1;
  dkLocalBase = 2;
  dkConfig = 3;
  dkReadOnlyConfig = 4;
  dkSavedConfig = 5;
  dkOutput = 6;
  dkReport = 7;
  dkHelp = 8;
  dkUser = 9;

  // 文件路径
  BinPath = 'bin\';
  ConfigPath = 'configs\'; // 配置文件路径
  HelpPath = 'help\'; // 帮助文件路径
  OutputPath = 'output\'; // 输出文件路径
  ReportPath = 'report\'; // 报表、回单格式文件路径
  UserPath = 'user\';

  AppFolder = 'KSClient'; // 应用程序目录名称

  ConfigFileName = 'SmartCardClient.in' {'ksclient.ini'}; // 配置文件
  ConfigSourceFileName = 'SmartCardClient.ini';
  AllUsersFileName = 'allusers.ini'; // 所有使用用户的配置文件
  StartIniFileName = 'Start.ini'; // 启动文件
  RunNotesFileName = 'NotesForRun.txt';

  //MenuFile = 'menus.mns';
  //FavoritesFile = 'favorites.mns';
  HelpIDsFile = 'HelpIDs.txt';
  GuideFile = 'intro.html';
  TutorialFile = 'Tutorial.htm';
  MenuInfoFileName = 'menus.mnt'; // 菜单文件
  MenuInfoDataFileName = 'menus.mnt'; // 菜单文件
  MainAppName = 'KSClient50.exe';
  SelfServAppName = 'KSSelfServ50.exe';

  CustMenuInfoDataFileName = 'custmenus.mn'; //wlj 客户权限菜单文件
  // 有关grid显示的配置后缀
  GridInfoFilePostfix = '.grid';

  // System Objects
  SODatabase = 'Database';

  GridInvisibleColor = clSilver;

  // Data Present Type
  dptIdObjects = 'IdObjects';

  // 字符串格式化
  // IdObject 文本格式转换
  IdObjectTextFormat = '%s-%s';
  IdObjectTextFormat2 = '%1:s';
  // 数字和日期的格式
  CurrencyFormat = '#,##0.00';
  NumberFormat = '#,##0';
  FeeRateFormat = '#0.00000000';
  NormalDateTimeFormat = 'yyyymmdd';
  FullDateFormat = 'yyyy''年''mm''月''dd''日''';
  FullReportDateFormat = 'yyyy''年''mm''月''dd''日''hh''时''mm''分''ss''秒';

  //wsn 20041206
  FullSepDateFormat = 'yymmdd';
  SepTimeFormat = 'hhnnss';
  CardNomalDateFormat = 'yyyy''-''mm''-''dd';

  //rding,20040602
  NormalTimeFormat = 'hh:nn:ss';

  // 警告 <=
  WarningReturnCode = 0;
  InforReturnCode = 1234; //wlj 20040105 后台sp返回的提示信息,如没有查询结果
  // Acount Type
  // 0客户号，1沪A，2深A，3沪B，4深B，#-银行代码，*磁卡号，a-证件
  atCustomerNo = '0';
  atSHA = '1';
  atSZA = '2';
  atSHB = '3';
  atSZB = '4';
  atST = '5';
  atBankNo = '#';
  atCard = '*';
  atCert = 'a';

  // Password Type
  ptTransactionPassword = 1;
  ptFundPassword = 2;
  ptAllPassword = 3;

  // Password Caption
  STransactionPassword = '交易密码';
  SFundPassword = '资金密码';
  SAllPassword = '交易/资金密码';

  CustomerNoInputMethodChar = atCustomerNo;
  SHAInputMethodChar = atSHA;
  SZAInputMethodChar = atSZA;
  SHBInputMethodChar = atSHB;
  SZBInputMethodChar = atSZB;
  SSTInputMethodChar = atST;
  BankAccountInputMethodChar = atBankNo;
  CardInputMethodChar = atCard;

  // Cert Type
  //
  ctIDCard = 0;
  ctPassport = 9;
  ctLicense = 1;
  ctOther = 7;

  // 最大预览页数
  MaxPreviewPageCount = 100;

  // StyleItem的名字
  StatusBarStyleItemName = '状态条';
  WorkAreaStyleItemName = '操作界面';
  OutWorkAreaStyleItemName = '操作界面的外围背景';
  TreeRootStyleItemName = '向导树.根';
  TreeLeaveStyleItemName = '向导树.叶';
  WarningStyleItemName = '警告文字';
  GridStyleItemName = '表格';
  GridTitleStyleItemName = '表格标题';

  // 分割符
  IdObjectSeparateChar = ',';

  MaxCustomerPasswordLength = 8;

  // 2、和交易市场相关的参数

const
  KnownMarketMin = 1;
  KnownMarketMax = 4;

type
  KnownMarkets = KnownMarketMin..KnownMarketMax;

const
  KnownSecurityLengths: array[KnownMarkets] of Integer
  = (6, 6, 6, 6);

  KnownSecurityPatterns: array[KnownMarkets] of string
  = ('600000', '000000', '900900', '200000');

  KnownAccountLengths: array[KnownMarkets] of Integer
  = (10, 10, 10, 10);

  KnownAccountPatterns: array[KnownMarkets] of string
  = ('A000000000', '0000000000', 'C000000000', '2000000000');

const
  // 3、主程序实现需要的常量定义 **********************************************

  //wsn 20041113 根据后台设计，用变量代替
  CurrentSetListUnit = '大学';
  CurrentBalanceState = '平衡'; {运行情况总表的平衡状态}
  CurrentNoBalanceState = '不平衡'; {运行情况总表的不平衡状态}

  // 影响界面的外观
  Separator = '>';
  MinGuideWidth = 100;

  // 有关帮助系统
  HIDIndex = '#Index';
  HIDNotImp = '#NotImp';
  HIDNoHelp = '#Index';

  // UICode
  UIGuide = '#Guide';
  UISearch = '#Search';
  GuideCaption = '向导';
  SearchCaption = '搜索';

  // 启动文件里面的配置
  ccStart = 'Start';
  ckBase = 'Base';
  ckMode = 'Mode';

  // 标准配置文件里面的配置
  //配置信息类别(config category)
  ccServer = 'Server';
  cchqserver = 'hqserver';
  // server keys
  ckIP = 'IP';
  ckIP2 = 'IP2';
  cdIP = '';

  ckPort = 'Port';
  ckPort2 = 'Port2';
  cdPort = 2000;

  ckEncode = 'Encode';
  cdEncode = 0;

  ckDestNo = 'DestNo';
  cdDestNo = 0;

  ckNodeID = 'Node_ID';
  cdNodeID = '0';

  ckFuncNo = 'FuncNo';
  cdFuncNo = 800;

  ckTimeOut = 'TimeOut';
  cdTimeOut = 30 * 1000;

  ckPrior = 'Prior';
  cdPrior = 2;

  ckDelayShowMessage = 'DelayShowMessage';
  cdDelayShowMessage = False;

  ckDelaySeconds = 'DelaySeconds';
  cdDelaySeconds = 3;
  MinDelaySeconds = 1;

  // 营业部
  ccDepartment = 'Department';
  ckDepartmentID = 'ID';
  ckDepartmentName = 'Name';
  //公司名称  wlj 20040331 add
  ckCompanyName = 'CompanyName';

  //wsn 20050119 复旦一卡通的子系统信息
  ckSubSystemNo = 'SubSystemNo';
  ckCurrentSubSystemRegedit = 'CurrentSubSystemRegedit';
  ccSmartcard = 'SmartCard';
  ckInitialKey = 'InitialKey';

  // 装载的程序包(config category)
  ccPackages = 'Packages';
  ccSelfServPackages = 'SelfServPackages';
  ckPackageCount = 'Count';

  // 主程序(config category)
  ccMain = 'Main';
  ccTrader = 'Trader'; //(IN TRADER)

  ckMaxUICount = 'MaxUICount';
  cdMaxUICount = 5;
  MinMaxUICount = 2;

  ckNestedMenu = 'NestedMenu';
  cdNestedMenu = False;

  ckShowMenuIcon = 'ShowMenuIcon';
  cdShowMenuIcon = True;

  ckShowGroupChar = 'ShowGroupChar';
  cdShowGroupChar = False;

  ckConfirmClose = 'ConfirmClose';
  cdConfirmClose = False;

  ckStartUI = 'Start';
  cdStartUI = '';

  ckUseThread = 'UseThread';
  cdUseThread = False;

  ckShowTutorial = 'ShowTutorial'; // 显示向导
  cdShowTutorial = False;

  ckAutoLockSeconds = 'AutoLockSeconds'; // 自动锁定
  cdAutoLockSeconds = 600;
  MinAutoLogoutSeconds = 30;

  ckAutoFitSize = 'AutoFitSize'; // 自动调整界面大小
  cdAutoFitSize = True;

  ckMultiQuery = 'MultiQuery'; // 可以同时打开多个相同的查询界面
  cdMultiQuery = True;

  ccMultiQuery = 'MultiQueryInterface';
    // 该组里面每个UICode=Boolean，确定是否可以同时打开多个相同的操作界面

  {
  ccMenuFile = 'Menu';
  cdMenuFile = 'menus.mns';

  ccFavoriteFile = 'Favorites';
  cdFavoriteFile = 'favorites.mns';
  }

  // 日志(config category)
  ccLog = 'Log';

  ckObjectLife = 'ObjectLife'; // lcConstuct_Desdroy
  cdObjectLife = False;

  ckDataset = 'Dataset'; // lcDBAIntfHelper lcDataset lcRender
  cdDataset = False;

  ckDataPack = 'DataPack'; // lcKCPack
  cdDataPack = False;

  ckCommand = 'Command'; // lcCommand
  cdCommand = False;

  ckApplication = 'Application'; // lcKSClient...
  cdApplication = True;

  ckDebug = 'Debug'; // lcDebug
  cdDebug = False;

  ckKCDataset = 'KCDataset';
  cdKCDataset = False;

  ckKsClientPreQuery = 'KsClientPreQuery';
  cdKsClientPreQuery = False;
  // 输入方式
  ccInput = 'Input';
  ckBarInput = 'BarInput';
  ckCustomerNo = 'CustomerNo';
  cdCustomerNo = '';
  ckCustomerNoLength1 = 'CustomerNoLength1';
  cdCustomerNoLength1 = 8;
  ckCustomerNoLength2 = 'CustomerNoLength2';
  cdCustomerNoLength2 = 10;
  ckInputSequence = 'Sequence';
  cdInputSequence = '';
  ckOperatorNo = 'OperatorNo';
  cdOperatorNo = '';
  ckDefaultMethod = 'DefaultMethod';
  cdDefaultMethod = '0';
  ckBrokerNo = 'BrokerNo';
  cdBrokerNo = '';
  ckMaxEntrustVol = 'MaxEntrustVol';
  cdMaxEntrustVol = 999999;
  ckMaxCashSum = 'MaxCashSum';
  cdMaxCashSum = 5000000;
  ckMaxBankBookCheckSum = 'MaxBankBookCheckSum';
  cdMaxBankBookCheckSum = 1000000000;

  ckSecurityLength = 'SecurityLength.%s';
  cdSecurityLength = 6;
  ckSecurityPattern = 'SecurityPattern.%s';
  cdSecurityPattern = '000000';
  ckAccountLength = 'AccountLength.%s';
  cdAccountLength = 0;
  ckAccountPattern = 'AccountPattern.%s';
  cdAccountPattern = '';

  ckOtherInputAccount = 'OtherInputAccount';
  cdOtherInputAccount = '';

  //吴乐俭 20031219 华斯要求价格为4位,缺省价格为整数
  ckPriceFormat = 'PriceFormat';
  cdPriceFormat = '#,##0';

  ckPircePrecision = 'PricePrecision'; //价格的小数位数
  cdPricePrecision = 0;

  //清算过账相关

 { //一卡通上传流水工作站以及设备号  20050106
  SmartCardSubSystemCata ='SmartCard';
  SmartCardSubSystemName ='SubSystemNo';
  SmartCardSubSystemNo = 0;     }
const
  bsetdate = 210;
  bqscl = 300;
  bqycl = 400;
  bgzlxcl = 450;
  bcheck = 500;
  bpayint = 605;
  bpayfine = 606;
  bbackbef = 610;
  bpost = 630;
  bbackaft = 655;
  bstat001 = 911;
  bd4ck = 912;
  bstat003 = 950;
  bstat005 = 960;
  bstat002 = 970;
  bstat010 = 980;
  bstat015 = 990;
  binit = 100;
  bqdlv = 840;
  bdpdlv = 905;
  brstbef = 633;
  bdpost = 631;
  brstaft = 632;
  bpayrest = 971;
  bAfterCheck = 850;

  StartUp = 1; //启动
  Kill = 2; //终止
  Query = 3; //查询状态

  // 监控查询参数
  ccMonitor = 'Monitor';
  ckFundAlertVal = '资金存取监控阀值';
  cdFundAlertVal = 500000;
  ckEntrustAlertVol = '委托买卖监控阀值';
  cdEntrustAlertVol = 300000;
  ckDoneAlertVol = '成交回报监控阀值';
  cdDoneAlertVol = 300000;
  ckRefreshInterval = '刷新时间间隔';
  cdRefreshInterval = 10;

  // 是否出现对话框确认用户的操作
  ccConfirm = 'Confirm';
  cdConfirm = 0;

  // 选择分支机构管理树(单，复选)
  ccSelectTree = 'SelectTree';
  cdSelectTree = 0; //表示单选

  // 是否打印回单
  ccPrintReceipt = 'PrintReceipt';
  cdPrintReceipt = 1;

  ckPreview = 'Preview';
  cdPreview = True;

  // 是否单机双柜员复核
  ccDoubleCheck = 'DoubleCheck';
  cdDoubleCheck = False;

  // 运行时候的环境配置
  ccRunEnvir = 'RunEnvir';
  ckHTML = 'HTML';
  ckNoHTMLHint = 'NoHTMLHint';

  NoHTMLSwitch = 'nohtml';

  // 缺省职工，
  DefaultSystemOperatorNO = 'SYSTEM';
  DefaultSystemOperatorName = '系统';

  // 菜单相关
  FavoritesCaption = '常用菜单';
  // 根菜单ID
  DepartMenuRootID = '营业部菜单';
  //DepartMenuRootID = '总部菜单';
  CenterMenuRootID = '总部菜单';

  DepartFavoritesMenuRootID = '营业部常用菜单';
  //DepartFavoritesMenuRootID = '总部常用菜单';
  CenterFavoritesMenuRootID = '总部常用菜单';
  EmptyFavoritesMenuRootID = '空白常用菜单';
  UserMenuRootID = '个人菜单';
  UserMenuRootCaption = UserMenuRootID;
  FavoritesIDPart = '常用';
  CenterRootIDPart = '总部';

  // 所有用户的配置
  AllUsersCategories = '|AllUsers|Device|AllUserSet|';

  ccAllUsers = 'AllUsers';
  ckUser = 'User.%s';
  cdUser = '';

  ccDevice = 'Device';
  ccAllUserSet = 'AllUserSet'; //wlj 20040331 增加，所有客户共同的设置放在此处

  // 密码小键盘
  ckPwdComNo = 'PwdComNo'; // 使用密码小键盘的串口号
  cdPwdComNo = 1;
  ckPwdTimeOut = 'PwdTimeOut';
  cdPwdTimeOut = 10;

  // 每个用户自己的配置
  // wlj 20040331 增加  CustConf|FileDone
  UserCategories = '|User|UserMenus|UserSet|FileDone|';
  UserFileNameFormat = '%s.ini';

  ccUser = 'User';
  ckRoot = 'RootMenu';
  cdRoot = '';

  ccUserMenus = 'UserMenus';
  ckUserMenuCount = 'Count';
  cdUserMenuCount = 0;
  //wlj 20040331 增加此定义
  ccUserSet = 'UserSet'; //wlj 20040331 增加；客户特殊的设置放在此处
  ccUserFileDone = 'FileDone';
    //wlj 20040331 增加；客户成交回报文件的设置放在此处

  // 3. 自动化系统Robot使用
  MaxSavedDataItemCount = 10;

  // Data Category Name
  DCCustomer = '客户号';
  DCDate = '日期';
  DCSequenceNo = '流水号';
  DCContractNo = '合同号';
  DCAccount = '股东代码';
  DCBrokerNo = '经纪人号';
  DCSecurity = '证券代码';
  DCOperator = '操作员';
  DCBankAccount = '银行帐号';

  // Command Param Name
  CPCustomerNo = '客户号';
  CPDate = '日期';
  CPSequenceNo = '流水号';
  CPContractNo1 = '合同号';
  CPContractNo2 = '批号';
  CPAccount1 = '股东代码';
  CPAccount2 = '股东帐号';
  CPBrokerNo1 = '经纪人号';
  CPBrokerNo2 = '经纪人代码';
  CPSecurity = '证券代码';
  CPOperator1 = '工号';
  CPOperator2 = '职工代码';
  CPBankAccount1 = '银行帐号';
  CPBankAccount2 = '银行账号';

  // 4.
  //为域"证券代码EX"使用
  //为域"经纪人号EX"使用
  //为域"职工代码EX"使用
  SecNameParam = '证券名称';
  AllowSecTypeParam = '允许类别';
  NotAllowSecErrorParam = '不允许的类别错误';
  RequiredSecParam = '必输';
  SecObjParam = '证券对象';
  BroketNameParam = '经纪人名称';
  BroketObjParam = '经纪人对象';
  RequiredOperatorNo = '必输';
  CheckOperatorExits = '验证存在性';
  OperatorName = '职工姓名';

  // 5.打印
  PrintFullDateField = '#系统日期2';
  PrintFullDepartmentNameField = '#营业部名称2';

const //一些预查询结果存放的StringList的名字。
  SLName_Exchange_Seat = '交易所席位';
  SLName_Exchange_Kind = '交易所品种';
  SLName_Cust_Class = '客户类';
  SLName_Enturst_Exchange_Seat = '交易所/席位号对应列表';
  SLName_Compact_Money = '可交易合约/币种对应列表';
  SLName_CustNO_MulTraderNO = '多交易编号客户列表';
  SLName_CustNO_CanTrade = '可交易客户号列表';
  SLName_QueryParm = '查询参数传递列表';
  SLName_CustNO_Transfer = '客户号传递列表';
  SLName_EntrustParam = '下单参数传递列表';
  SLName_PreEntrust = '预埋参数传递列表';
  SLName_WithDrawEntrust = '撤单参数传递列表';
  SLName_SetCustPara = '设置参数的客户传递列表';

  //rding,20040602,增加“席位时间差”
  SLName_Seat_TimeDelta = '席位/时间差对应列表';

resourcestring
  // 资源字符串，用于文字描述
  SWaitingQuery = '正在查询...';
  SNotFound = '没有找到匹配的数据条目';
  SWaitingOperation = '向服务器发送请求...';
  SAllDepartments = 'A-所有营业部';
  SCancelPrompt = '按ESC键或者鼠标双击这里终止等待';
  SDataDictionaryIsNull = '数据字典查询内容为空';
  //wsn 20050325
  SWaitingPubCard = '正在发行校园卡...';

  SAdd = '增加';
  SDelete = '删除';
  SChange = '修改';
  SViewDetail = '细节';
  SSet = '增删改';

  SShowConfirm = '请确认操作';
  SShowWarning = '操作警告';
  SShowError = '提示信息';
  SShowMessage = '操作信息';
  SShowSuccess = '操作成功';
  SPrintReceiptPrompt = '是否需要打印回单？';
  SWaitForSum = '正在合计';

  SApplicationShortName = '校园一卡通系统';
  SSelfServApplicationShortName = '自助交割';

  SSimpleFieldError = '输入的%s不正确';
  SFullFieldError = '输入的%s%s';
  SFieldErrorFormat = '%s,正确的数据格式应该是：'#13#10 + '%s';
  SInvalidReinput = '与第一次输入数据的不相同';
  SInvalidAccount = '格式不正确';
  SInvalidSmallData = '应该大于等于%s';
  SInvalidBigData = '应该小于等于%s';
  SNotExist = '不存在';
  SFormatError = '格式不正确';
  SNotEmpty = '不能为空';
  SCannotRefreshDates = '不能更新系统日期，继续操作？';

  //SMenuError = '菜单数据被损坏，请和管理员联系，重新安装菜单数据。';
  SMenuError = '无法读取菜单数据';
  SSyetemDateFormat = '系统工作日期 %s';
  SLocalDateFormat = '''您的电脑日期 ''yyyy''年''mm''月''dd''日''';

  SOutOfDate = '%s 过期';

  SNoRegisterUI = '没有实现的功能 %s';

  SNoInstallHTML = '因为没有安装IE浏览器4.0以上版本';
  SProhibitHTML = '因为运行参数禁止在程序中使用IE浏览器';
  SNoOnlineHelp = '不能使用在线帮助，';
  SNoGuide = '不能使用向导，';

  SReportCancelled =
    '报表输出被终止或者取消。如果希望输出完整报表，请重新查询数据。';

  SConfirmIgnoreError = '%s'#13#10'是否继续?';

  SPrinterError = '打印机错误，可能是没有安装缺省打印机。';
  SNoPrinter = '没有安装打印机';
  SEndPageTooSmall = '结束页码应该大于开始页码';

  SRootMetaMenuCaption = '校园一卡通管理系统';
  //////////////////////////////////////////////////
  //SRootMetaMenuCaption = '集中交易系统'; (IN TRADER)
  //////////////////////////////////////////////////
  SInputPassword = '请输入密码';
  SPassword = '密码';
  yktVersion = 'ykt_3.1.081'; //固定长度为11位，不能改变,包含手机卡

var
  IdObjectDisplayFormat: string = IdObjectTextFormat2;
  //wsn 20050106 一卡通系统上传流水必须的子系统号
  SmartCardSubSystemNo: integer;
  SmartCardSubSystemDynamicKey : string;
  SmartCardSubSystemCata: string = 'SmartCard';         
  SmartCardSubSystemName: string = 'SubSystemNo';

  backVer:string;//后台编译版本号

  appPath:string;//程序路径
  ifDebug:Integer;//是否调试模式
  yktMenu:string; //一卡通菜单

  SmartCardSystemDate: string; //结算日期

  sysDate:string;//系统日期
  accountDate:string;//结算日期
  bAccountDate:string;//结算前一日期
  accountTime:string;//系统时间
  eaccountDate:string;//结算后一日期
  SmartCardPortStatus: Boolean;
  SmartCardAuthStatus: Boolean;
  smartCardPwd:string;  //密钥
  scMacID:string;   //登陆时取得本机的mac地址
  scSiteNo:string;  //站点号，登陆时取得
  scOperNo:string;    //操作员号，登陆成功后保存
  

  //默认pasm卡座
  pasmSeat:Integer;
  //语音报价器相关
  bjopen:Integer;//语音报价器，1打开，0关闭
  bjcomport:Integer;//报价器端口号
  maxPer:Integer;//限额是否打开

  rptTitle:string;    //报表的表头显示
  rptOper:string;     //报表人
  
  //是否显示照片,1显示，0不显示
  showphoto:Integer;

  //登陆后保存IP，Port，FuncNo
  scIP : string;
  scPORT : Integer;
  scFUNCNO : Integer;
  
  //系统运行路径,路径以/结尾
  sAppPath:string;
  //系统运行路径的上级路径,
  sPreAppPath:string;

  //水控相关
  //水控记录
  waterStrings:TStringList;
  //是否显示水控预充值
  waterIfDef:Integer;
  //水控预充值金额
  waterDefMoney:Real;
  //小钱包充值有效期
  waterExpiredate:Integer;

  //新版本是否提示
  verIfTip:Integer;
  //新版本信息http路径
  verHttpPath:string;
  //后台最低版本,低于该版本业务会出错
  buSmlVer:string;
  //后台当前版本,会提示用户升级后台
  buCurrVer:string;

  cpuWaterPrice1:Integer;
  cpuWaterPrice2:Integer;
  cpuWaterPrice3:Integer;

implementation

end.
