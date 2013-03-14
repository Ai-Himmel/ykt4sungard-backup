unit KSClientConsts;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSClientConsts
   <What>ǰ̨��ܳ�����ʹ�õ��ĳ���
   <Written By> Huang YanLai (������)
   <History>
**********************************************}

interface

uses LogFile, DataTypes, Graphics, Messages,Classes;

const

  // 1����ܼ���ĳ������� **********************************************

  SUIClassFactoryCategory = 'UIClassFactory';

  SUIShareObjList = 'UIShareObjList'; //(IN TRADER)

  // Common Action ID
  caPrint = 1;
  caAdjustGrid = 2;
  caSearchData = 3;
  caNextSearchData = 4;
  caFocusGrid = 5;
  //��wsn 20041013��������׷�Ӳ�ѯ
  caSmartSearchData = 6;

  caDebugDataSource = 100;
  caDebugDataset = 101;
  caDebugWorkView = 102;
  caDebugUI = 103;

  // ϵͳ֪ͨ��Ϣ
  snPrinterChanged = 1;
  snDateUpdated = 2;

  KS_ShareBase = $A000; //(IN TRADER)
  KS_AskMainFrame = KS_ShareBase + 1; //(IN TRADER)
  KS_AnswerMainFrame = KS_ShareBase + 2; //(IN TRADER)

  KS_AddListView = KS_ShareBase + 3; //(IN TRADER)���͸�MainFrame��������

  KS_AskHandle = KS_ShareBase + 4; //(IN TRADER)��MainFormѰ�ҽ���Handle
  KS_AnswerHandle = KS_ShareBase + 5; //(IN TRADER)��MainForm�ҵ�Handle������
  KS_DoHandle = KS_ShareBase + 6; //(IN TRADER)��Handle�ҵ��󣬴�����Ӧ����Ϣ
  KS_DeleteEntrust = KS_ShareBase + 7; //(IN TRADER)���봴����������
  KS_DoDeleteEntrust = KS_ShareBase + 8; //(IN TRADER)ִ�г���
  KS_DoAddCust = KS_ShareBase + 9; //(IN TRADER)ִ����ӿͻ����б�
  KS_Entrust = KS_ShareBase + 10; //(IN TRADER)���������µ�
  KS_SelectHQ = KS_ShareBase + 11; //(IN TRADER)�����µ�ѡ������
  //  KS_DelAllQryUIs = KS_ShareBase + 12;   //(IN TRADER)����Աϵͳ��ѯ�ͻ��ź����в�ѯ����Ҫ�ͷŵ���
  KS_KillHold = KS_ShareBase + 13; //(IN TRADER)���ݳֲ��µ�

  KS_SetCustPara = KS_ShareBase + 15; //(IN MANAGER) ���ÿͻ�����
  //rding,20040608
  KS_GetDeleteEntrust = KS_ShareBase + 16;
    //����ί�кŻ�ȡ��ί�кŶ�Ӧ�ĵ�����Ϣ�����ί�к�Ϊ�գ��򷵻�����
  //rding,20040608,end
  //����ԱϵͳMainFrame���������ģ���Handle�б������
  TraderEntrustHdle = 1; //(IN TRADER)
  Pre_EntrustHdle = 2; //(IN TRADER)
  DeleteEntrustHdle = 3; //(IN TRADER)

  // �����ֵ���Ŀ(DataEntry)
  deNotUsed = -100; // ���õ�
  deSystemParams = -101; // ϵͳ����
  deDictionaryCategory = -102; // �����ֵ���Ŀ
  deBoolean = -103; // Boolean���ͣ�0��1�ǣ�
  deBusinessFlag = -104; // ҵ���־

  deExchangeKind = -25; //ȫ��Ʒ��
  deExchangeSeat = -23; //ȫ��ϯλ
  deBank = -3; // ����
  deDepart = -8; // Ӫҵ��

  deStandardFirst = 1000;
  deStandardLast = 1900;
  deAccountStatus = 1000; //�ʻ�״̬
  deCheckType = 1011; //У�鷽ʽ
  deAccountType = 1012; //�ʺ����: �ͻ���,��A�ɶ�����
  deAgentType = 1020; //����ʽ
  deBusinessCtrl = 1021; //ҵ�����
  deWithDrawType = 1022; //��ʽ
  deCustomerProp = 1023; //�ͻ���־
  deSex = 1030; //�Ա�
  deEducation = 1031; //ѧ��
  dePaymentMonthly = 1032; //������
  deNation = 1040; //��������
  deCertType = 1041; //֤�����
  deCenterCustomerType = 1042; //�ܲ�ͳ�����
  deDepartCustomerType = 1043; //Ӫҵ���ͻ����
  deCustomerGroup = 1044; //�ͻ����
  deDestroyCondition = 1060; //��������
  deAwardProp = 1062; //����ָ��
  deAwardSource = 1063; //������Դ
  deUnionType = 1064; //��������
  deOperationType = 1065; //��������
  deMethodNo = 1066; //�������
  deJoin = 1067; //���ӹ�ϵ
  deCompare = 1068; //�Ƚϲ�����
  deMethod = 1069; //��������
  deAwardType = 1070; //�������
  deClassify = 1071; //�������
  deType = 1072; //���ͱ�־
  deSum = 1073; //ͳ�Ʒ�ʽ
  deCurrency = 1101; //��������
  deCheckStatus = 1102; //֧Ʊ״̬
  deTransferStatus = 1103; //ת��״̬
  deGetType = 1104; //֧ȡ����
  deReserveStatus = 1105; //ԤԼʹ��״̬
  de1106 = 1106; //���ʷ�ʽ
  de1107 = 1107; //����״̬
  de1108 = 1108; //�������
  deEntrustMethod = 1201; //ί�з�ʽ
  deBusinessType = 1202; //ҵ�����
  de1202 = deBusinessType;
  deEntrustStatus = 1203; //ί��״̬
  de1203 = deEntrustStatus;
  deBuySell = 1204; //��������
  de1205 = 1205; //ί������
  deSecuritiesType = 1206; //֤ȯ���
  de1207 = 1207; //�걨����
  deAccountKind = 1208; //�ʻ����
  de1209 = 1209; //���뼶��
  de1210 = 1210; //�ɶ�Ȩ��
  de1211 = 1211; //�ɶ�����
  de1212 = 1212; //�ɽ�����
  de1213 = 1213; //�ɽ�״̬
  de1214 = 1214; //ί������
  de1215 = 1215; //�����������
  de1216 = 1216; //ת�ɻ���
  de1217 = 1217; //��ծ�ع�
  de1218 = 1218; //Ԥ��ָ�����
  de1219 = 1219; //Ԥ��Ƚϲ�����
  de1220 = 1220; //Ԥ�����ӹ�ϵ��
  de1221 = 1221; //�����¹�����
  de1222 = 1222; //ί�м۸����
  de1223 = 1223; //ί�б�־
  de1224 = 1224; //�ʽ����㷽ʽ
  de1225 = 1225; //��Ʊ���㷽ʽ
  de1250 = 1250; //��Ѻ״̬
  de1251 = 1251; //�걨����
  de1252 = 1252; //�ʽ���
  de1253 = 1253; //֤ȯ����
  de1254 = 1254; //�ʽ𶳽᷽ʽ
  de1255 = 1255; //�ʽ�ʵʱ��ת��־
  de1256 = 1256; //֤ȯʵʱ��ת��־
  de1257 = 1257; //��Է�ʽ
  de1258 = 1258; //ȱʡ�۸�����
  de1259 = 1259; //�޼�����
  de1260 = 1260; //��������
  de1261 = 1261; //���㷽��
  de1262 = 1262; //��������
  de1263 = 1263; //֤ȯ����
  de1264 = 1264; //�ܷ��޸�
  de1265 = 1265; //ͣ�Ʊ�־
  de1266 = 1266; //�̶��۸��־
  de1267 = 1267; //�̶�������־
  de1268 = 1268; //������ֵ��־
  de1269 = 1269; //�йܱ�־
  de1270 = 1270; //�ǿ���־
  de1271 = 1271; //������־
  de1272 = 1272; //��Ȩ��Ϣ��־
  de1273 = 1273; //����״̬
  de1274 = 1274; //��ҵ����
  de1275 = 1275; //��ͨ����
  de1276 = 1276; //֤ȯͳ�����
  deProcMode = 1280; //ί�д���ģʽ

  deMarket = 1301; //�г�����
  de1302 = 1302; //����ģʽ
  de1303 = 1303; //�걨ģʽ
  de1304 = 1304; //�ر�ģʽ
  deCustomerTemplate = 1305; //�ͻ�ģ��
  de1306 = 1306; //ҵ���Ŀ
  de1307 = 1307; //ҵ�����״̬
  de1308 = 1308; //ϵͳ״̬
  de1330 = 1330; //����״̬
  de1350 = 1350; //�ѿ�ͨ�������
  de1351 = 1351; //ʱ������
  de1352 = 1352; //�����Ƿ�����
  de1353 = 1353; //��������
  de1354 = 1354; //ϯλ��ͨ����
  de1355 = 1355; //��ȡ����
  de1356 = 1356; //��������
  de1357 = 1357; //�䶯���
  deWorkStatus = 1360; // Ӫҵ��״̬/ְ������״̬
  deFrontFree = 1401; //ǰ̨�շ�
  de2FeeCode = 1402; //�������ô���
  de1402 = de2FeeCode;
  de1FeeCode = 1403; //һ�����ô���
  de1403 = de1FeeCode;
  de1404 = 1404; //����ģʽ
  deStation = 1501; //��λ
  de1502 = 1502; //��ԱȨ��
  de1504 = 1504; //��Ա����
  de1505 = 1505; //��Ա��������
  de1506 = 1506; //ȱʡӪҵ����λ
  de1507 = 1507; //ȱʡ�ͻ����
  de1508 = 1508; //ȱʡ�ͻ����
  de1509 = 1509; //ȱʡ�ͻ�ģ��
  deBankCode = 1601; //���д���
  de1602 = 1602; //�������
  de1603 = 1603; //�����ʻ����
  de1604 = 1604; //���з���ҵ���־
  de1605 = 1605; //�����ʽ�ʽ
  de1606 = 1606; //�����ʻ�����
  de1607 = 1607; //�����ʻ�Ȩ��
  de1608 = 1608; //����ί��״̬
  de1609 = 1609; //���𷽴���
  de1610 = 1610; //�������
  de1611 = 1611; //�������㷽ʽ
  de1612 = 1612; //�ļ�����
  de1613 = 1613; //����ģʽ
  de1614 = 1614; //�����־
  de1615 = 1615; //�ļ�����
  deBankType = 1616; //�������
  de1617 = 1617; //������ͨ��־
  deAera = 1620; //��������
  de1701 = 1701; //������Ȩ��
  de1702 = 1702; //�����˲�����ɫ
  de1703 = 1703; //��������Ȩ��ɫ
  de1704 = 1704; //������ί�з�ʽ
  de1705 = 1705; //���������
  de1801 = 1801; //ǰ̨���ô���
  de1802 = 1802; //���÷ֳɱ�־
  de1803 = 1803; //�ֱʼ����־
  de1804 = 1804; //������ɱ�־
  de1806 = 1806; //����֧�ֳ�
  de1807 = 1807; //�ֶμ����־
  de1808 = 1808; //���ʽ��ʺż����־
  de1809 = 1809; //��ɴ�����ʽ
  de1810 = 1810; //ָ�����
  de1811 = 1811; //ƽ����־
  de1812 = 1812; //�������
  de1813 = 1813; //�ϲ���־
  de1814 = 1814; //��������
  de1815 = 1815; //���㷽ʽ
  de1816 = 1816; //�ۿ۷�ʽ
  de1819 = 1819; //�շѷ�ʽ
  de1820 = 1820; //�շѵ���
  de1282 = 1282; //�ۿ��־
  de1283 = 1283; //�����־
  de1284 = 1284; //Э����������
  de1285 = 1285; //ȯ���շ�ģʽ
  de1286 = 1286; //����Э��״̬

  deLO_FLAG = 1901; //��ƽ�ֱ�־
  deSH_FLAG = 1902; //Ͷ�����

  deTxStation = 1005; //����������

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

  //һЩ��Ҫ��̬ȷ�����ݵ������ֵ�
  deExchange = -21;
  deOperator_CustNO = -1000;
  deExchange_Kind = -1001;
  deExchange_Seat = deExchange_Kind - 100;

  // �ܲ�Ӫҵ������
  CenterDepartNo = '000';
  // ��ʾ����Ӫҵ���Ĵ���
  AllDepartsNo = '';
  // ��ʾ����/��ѡ
  EmptyIdObjectCode = '';
  EmptyIdObjectName = '';
  // deBoolean       = -103
  IdForFalse = '0';
  IdForTrue = '1';
  NameForFalse = '��';
  NameForTrue = '��';

  // Log Category
  lcRegisterUI = 9;
  lcKSClient = lcAppLogStart + 10;
  lcKSClientStart = lcKSClient + 1;
  lcKSClientShutDown = lcKSClient + 2;
  lcKSClientLoadPackage = lcKSClient + 3;
  lcKSClientUnLoadPackage = lcKSClient + 4;
  lcKsClientPreQuery = lcKSClient + 5;

  // ϵͳ�������ƣ�����Context
//  svDeviceSign        = ''
  svDepartNoName = '#Ӫҵ������'; //wsn����ͬ����ϵͳ��־��
  svDepartNoType = kdtInteger;
  svDepartNameName = '#Ӫҵ������';
  svDepartNameType = kdtString;
  svOperatorNoName = '#ְ������';
  svOperatorNoType = kdtString;
  svOperatorNameName = '#ְ������';
  svOperatorNameType = kdtString;
  svOperatorPasswordName = '#ְ������';
  svOperatorPasswordType = kdtString;
  svOperatorMenuAuthName = '#ְ���˵�Ȩ��';
  svOperatorMenuAuthType = kdtString;
  svLoginStatusName = '#��¼״̬';
  svLoginStatusType = kdtBoolean;
  svMACAddressName = '#������ַ'; //wsn ��ͬ�ڶ�̬��Կ
  svMACAddressType = kdtString;
  svSystemDateName = '#ϵͳ����';
  svSystemDateType = kdtString;
  svWorkDateName = '#��������';
  svWorkDateType = kdtString;
  svReportDateName = '#��������';
  svReportDateType = kdtString;
  svProhibitMarketsName = '#��ֹ�г�����';
  svProhibitMarketsType = kdtString;
  svProhibitMoneyName = '#��ֹ���ּ���';
  svProhibitMoneyType = kdtString;
  svCompanyNameName = '#��˾����';
  svCompanyNameType = kdtString;

  //ADD BY ZKJ 2003-11-30
  svSeatNoName = '#ϯλ��'; //(IN REPORT)
  svSeatNoType = kdtString; //(IN REPORT)

  //ADD BY ZKJ 2003-12-03
  svBatchNoName = '#���κ�'; //(IN REPORT)
  svBatchNoType = kdtInteger; //(IN REPORT)

  svFuncNoName = '#�����ܺ�'; //(IN REPORT)
  svFuncNoType = kdtInteger; //(IN REPORT)

  //rding,20040602,���ӡ�ϵͳʱ�䡱
  svSystemTimeName = '#ϵͳʱ��';
  svSystemTimeType = kdtInteger;

  // ��׼�������Ĳ���
  cpReturnCodeParamName = '������';
  cpReturnMessageParamName = '������Ϣ';
  cpReturnEmptyDataSet = '��ѯ���Ϊ��';

  // DirKey(���ڱ���Ŀ¼������)
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

  // �ļ�·��
  BinPath = 'bin\';
  ConfigPath = 'configs\'; // �����ļ�·��
  HelpPath = 'help\'; // �����ļ�·��
  OutputPath = 'output\'; // ����ļ�·��
  ReportPath = 'report\'; // �����ص���ʽ�ļ�·��
  UserPath = 'user\';

  AppFolder = 'KSClient'; // Ӧ�ó���Ŀ¼����

  ConfigFileName = 'SmartCardClient.in' {'ksclient.ini'}; // �����ļ�
  ConfigSourceFileName = 'SmartCardClient.ini';
  AllUsersFileName = 'allusers.ini'; // ����ʹ���û��������ļ�
  StartIniFileName = 'Start.ini'; // �����ļ�
  RunNotesFileName = 'NotesForRun.txt';

  //MenuFile = 'menus.mns';
  //FavoritesFile = 'favorites.mns';
  HelpIDsFile = 'HelpIDs.txt';
  GuideFile = 'intro.html';
  TutorialFile = 'Tutorial.htm';
  MenuInfoFileName = 'menus.mnt'; // �˵��ļ�
  MenuInfoDataFileName = 'menus.mnt'; // �˵��ļ�
  MainAppName = 'KSClient50.exe';
  SelfServAppName = 'KSSelfServ50.exe';

  CustMenuInfoDataFileName = 'custmenus.mn'; //wlj �ͻ�Ȩ�޲˵��ļ�
  // �й�grid��ʾ�����ú�׺
  GridInfoFilePostfix = '.grid';

  // System Objects
  SODatabase = 'Database';

  GridInvisibleColor = clSilver;

  // Data Present Type
  dptIdObjects = 'IdObjects';

  // �ַ�����ʽ��
  // IdObject �ı���ʽת��
  IdObjectTextFormat = '%s-%s';
  IdObjectTextFormat2 = '%1:s';
  // ���ֺ����ڵĸ�ʽ
  CurrencyFormat = '#,##0.00';
  NumberFormat = '#,##0';
  FeeRateFormat = '#0.00000000';
  NormalDateTimeFormat = 'yyyymmdd';
  FullDateFormat = 'yyyy''��''mm''��''dd''��''';
  FullReportDateFormat = 'yyyy''��''mm''��''dd''��''hh''ʱ''mm''��''ss''��';

  //wsn 20041206
  FullSepDateFormat = 'yymmdd';
  SepTimeFormat = 'hhnnss';
  CardNomalDateFormat = 'yyyy''-''mm''-''dd';

  //rding,20040602
  NormalTimeFormat = 'hh:nn:ss';

  // ���� <=
  WarningReturnCode = 0;
  InforReturnCode = 1234; //wlj 20040105 ��̨sp���ص���ʾ��Ϣ,��û�в�ѯ���
  // Acount Type
  // 0�ͻ��ţ�1��A��2��A��3��B��4��B��#-���д��룬*�ſ��ţ�a-֤��
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
  STransactionPassword = '��������';
  SFundPassword = '�ʽ�����';
  SAllPassword = '����/�ʽ�����';

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

  // ���Ԥ��ҳ��
  MaxPreviewPageCount = 100;

  // StyleItem������
  StatusBarStyleItemName = '״̬��';
  WorkAreaStyleItemName = '��������';
  OutWorkAreaStyleItemName = '�����������Χ����';
  TreeRootStyleItemName = '����.��';
  TreeLeaveStyleItemName = '����.Ҷ';
  WarningStyleItemName = '��������';
  GridStyleItemName = '���';
  GridTitleStyleItemName = '������';

  // �ָ��
  IdObjectSeparateChar = ',';

  MaxCustomerPasswordLength = 8;

  // 2���ͽ����г���صĲ���

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
  // 3��������ʵ����Ҫ�ĳ������� **********************************************

  //wsn 20041113 ���ݺ�̨��ƣ��ñ�������
  CurrentSetListUnit = '��ѧ';
  CurrentBalanceState = 'ƽ��'; {��������ܱ��ƽ��״̬}
  CurrentNoBalanceState = '��ƽ��'; {��������ܱ�Ĳ�ƽ��״̬}

  // Ӱ���������
  Separator = '>';
  MinGuideWidth = 100;

  // �йذ���ϵͳ
  HIDIndex = '#Index';
  HIDNotImp = '#NotImp';
  HIDNoHelp = '#Index';

  // UICode
  UIGuide = '#Guide';
  UISearch = '#Search';
  GuideCaption = '��';
  SearchCaption = '����';

  // �����ļ����������
  ccStart = 'Start';
  ckBase = 'Base';
  ckMode = 'Mode';

  // ��׼�����ļ����������
  //������Ϣ���(config category)
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

  // Ӫҵ��
  ccDepartment = 'Department';
  ckDepartmentID = 'ID';
  ckDepartmentName = 'Name';
  //��˾����  wlj 20040331 add
  ckCompanyName = 'CompanyName';

  //wsn 20050119 ����һ��ͨ����ϵͳ��Ϣ
  ckSubSystemNo = 'SubSystemNo';
  ckCurrentSubSystemRegedit = 'CurrentSubSystemRegedit';
  ccSmartcard = 'SmartCard';
  ckInitialKey = 'InitialKey';

  // װ�صĳ����(config category)
  ccPackages = 'Packages';
  ccSelfServPackages = 'SelfServPackages';
  ckPackageCount = 'Count';

  // ������(config category)
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

  ckShowTutorial = 'ShowTutorial'; // ��ʾ��
  cdShowTutorial = False;

  ckAutoLockSeconds = 'AutoLockSeconds'; // �Զ�����
  cdAutoLockSeconds = 600;
  MinAutoLogoutSeconds = 30;

  ckAutoFitSize = 'AutoFitSize'; // �Զ����������С
  cdAutoFitSize = True;

  ckMultiQuery = 'MultiQuery'; // ����ͬʱ�򿪶����ͬ�Ĳ�ѯ����
  cdMultiQuery = True;

  ccMultiQuery = 'MultiQueryInterface';
    // ��������ÿ��UICode=Boolean��ȷ���Ƿ����ͬʱ�򿪶����ͬ�Ĳ�������

  {
  ccMenuFile = 'Menu';
  cdMenuFile = 'menus.mns';

  ccFavoriteFile = 'Favorites';
  cdFavoriteFile = 'favorites.mns';
  }

  // ��־(config category)
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
  // ���뷽ʽ
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

  //���ּ� 20031219 ��˹Ҫ��۸�Ϊ4λ,ȱʡ�۸�Ϊ����
  ckPriceFormat = 'PriceFormat';
  cdPriceFormat = '#,##0';

  ckPircePrecision = 'PricePrecision'; //�۸��С��λ��
  cdPricePrecision = 0;

  //����������

 { //һ��ͨ�ϴ���ˮ����վ�Լ��豸��  20050106
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

  StartUp = 1; //����
  Kill = 2; //��ֹ
  Query = 3; //��ѯ״̬

  // ��ز�ѯ����
  ccMonitor = 'Monitor';
  ckFundAlertVal = '�ʽ��ȡ��ط�ֵ';
  cdFundAlertVal = 500000;
  ckEntrustAlertVol = 'ί��������ط�ֵ';
  cdEntrustAlertVol = 300000;
  ckDoneAlertVol = '�ɽ��ر���ط�ֵ';
  cdDoneAlertVol = 300000;
  ckRefreshInterval = 'ˢ��ʱ����';
  cdRefreshInterval = 10;

  // �Ƿ���ֶԻ���ȷ���û��Ĳ���
  ccConfirm = 'Confirm';
  cdConfirm = 0;

  // ѡ���֧����������(������ѡ)
  ccSelectTree = 'SelectTree';
  cdSelectTree = 0; //��ʾ��ѡ

  // �Ƿ��ӡ�ص�
  ccPrintReceipt = 'PrintReceipt';
  cdPrintReceipt = 1;

  ckPreview = 'Preview';
  cdPreview = True;

  // �Ƿ񵥻�˫��Ա����
  ccDoubleCheck = 'DoubleCheck';
  cdDoubleCheck = False;

  // ����ʱ��Ļ�������
  ccRunEnvir = 'RunEnvir';
  ckHTML = 'HTML';
  ckNoHTMLHint = 'NoHTMLHint';

  NoHTMLSwitch = 'nohtml';

  // ȱʡְ����
  DefaultSystemOperatorNO = 'SYSTEM';
  DefaultSystemOperatorName = 'ϵͳ';

  // �˵����
  FavoritesCaption = '���ò˵�';
  // ���˵�ID
  DepartMenuRootID = 'Ӫҵ���˵�';
  //DepartMenuRootID = '�ܲ��˵�';
  CenterMenuRootID = '�ܲ��˵�';

  DepartFavoritesMenuRootID = 'Ӫҵ�����ò˵�';
  //DepartFavoritesMenuRootID = '�ܲ����ò˵�';
  CenterFavoritesMenuRootID = '�ܲ����ò˵�';
  EmptyFavoritesMenuRootID = '�հ׳��ò˵�';
  UserMenuRootID = '���˲˵�';
  UserMenuRootCaption = UserMenuRootID;
  FavoritesIDPart = '����';
  CenterRootIDPart = '�ܲ�';

  // �����û�������
  AllUsersCategories = '|AllUsers|Device|AllUserSet|';

  ccAllUsers = 'AllUsers';
  ckUser = 'User.%s';
  cdUser = '';

  ccDevice = 'Device';
  ccAllUserSet = 'AllUserSet'; //wlj 20040331 ���ӣ����пͻ���ͬ�����÷��ڴ˴�

  // ����С����
  ckPwdComNo = 'PwdComNo'; // ʹ������С���̵Ĵ��ں�
  cdPwdComNo = 1;
  ckPwdTimeOut = 'PwdTimeOut';
  cdPwdTimeOut = 10;

  // ÿ���û��Լ�������
  // wlj 20040331 ����  CustConf|FileDone
  UserCategories = '|User|UserMenus|UserSet|FileDone|';
  UserFileNameFormat = '%s.ini';

  ccUser = 'User';
  ckRoot = 'RootMenu';
  cdRoot = '';

  ccUserMenus = 'UserMenus';
  ckUserMenuCount = 'Count';
  cdUserMenuCount = 0;
  //wlj 20040331 ���Ӵ˶���
  ccUserSet = 'UserSet'; //wlj 20040331 ���ӣ��ͻ���������÷��ڴ˴�
  ccUserFileDone = 'FileDone';
    //wlj 20040331 ���ӣ��ͻ��ɽ��ر��ļ������÷��ڴ˴�

  // 3. �Զ���ϵͳRobotʹ��
  MaxSavedDataItemCount = 10;

  // Data Category Name
  DCCustomer = '�ͻ���';
  DCDate = '����';
  DCSequenceNo = '��ˮ��';
  DCContractNo = '��ͬ��';
  DCAccount = '�ɶ�����';
  DCBrokerNo = '�����˺�';
  DCSecurity = '֤ȯ����';
  DCOperator = '����Ա';
  DCBankAccount = '�����ʺ�';

  // Command Param Name
  CPCustomerNo = '�ͻ���';
  CPDate = '����';
  CPSequenceNo = '��ˮ��';
  CPContractNo1 = '��ͬ��';
  CPContractNo2 = '����';
  CPAccount1 = '�ɶ�����';
  CPAccount2 = '�ɶ��ʺ�';
  CPBrokerNo1 = '�����˺�';
  CPBrokerNo2 = '�����˴���';
  CPSecurity = '֤ȯ����';
  CPOperator1 = '����';
  CPOperator2 = 'ְ������';
  CPBankAccount1 = '�����ʺ�';
  CPBankAccount2 = '�����˺�';

  // 4.
  //Ϊ��"֤ȯ����EX"ʹ��
  //Ϊ��"�����˺�EX"ʹ��
  //Ϊ��"ְ������EX"ʹ��
  SecNameParam = '֤ȯ����';
  AllowSecTypeParam = '�������';
  NotAllowSecErrorParam = '�������������';
  RequiredSecParam = '����';
  SecObjParam = '֤ȯ����';
  BroketNameParam = '����������';
  BroketObjParam = '�����˶���';
  RequiredOperatorNo = '����';
  CheckOperatorExits = '��֤������';
  OperatorName = 'ְ������';

  // 5.��ӡ
  PrintFullDateField = '#ϵͳ����2';
  PrintFullDepartmentNameField = '#Ӫҵ������2';

const //һЩԤ��ѯ�����ŵ�StringList�����֡�
  SLName_Exchange_Seat = '������ϯλ';
  SLName_Exchange_Kind = '������Ʒ��';
  SLName_Cust_Class = '�ͻ���';
  SLName_Enturst_Exchange_Seat = '������/ϯλ�Ŷ�Ӧ�б�';
  SLName_Compact_Money = '�ɽ��׺�Լ/���ֶ�Ӧ�б�';
  SLName_CustNO_MulTraderNO = '�ཻ�ױ�ſͻ��б�';
  SLName_CustNO_CanTrade = '�ɽ��׿ͻ����б�';
  SLName_QueryParm = '��ѯ���������б�';
  SLName_CustNO_Transfer = '�ͻ��Ŵ����б�';
  SLName_EntrustParam = '�µ����������б�';
  SLName_PreEntrust = 'Ԥ����������б�';
  SLName_WithDrawEntrust = '�������������б�';
  SLName_SetCustPara = '���ò����Ŀͻ������б�';

  //rding,20040602,���ӡ�ϯλʱ��
  SLName_Seat_TimeDelta = 'ϯλ/ʱ����Ӧ�б�';

resourcestring
  // ��Դ�ַ�����������������
  SWaitingQuery = '���ڲ�ѯ...';
  SNotFound = 'û���ҵ�ƥ���������Ŀ';
  SWaitingOperation = '���������������...';
  SAllDepartments = 'A-����Ӫҵ��';
  SCancelPrompt = '��ESC���������˫��������ֹ�ȴ�';
  SDataDictionaryIsNull = '�����ֵ��ѯ����Ϊ��';
  //wsn 20050325
  SWaitingPubCard = '���ڷ���У԰��...';

  SAdd = '����';
  SDelete = 'ɾ��';
  SChange = '�޸�';
  SViewDetail = 'ϸ��';
  SSet = '��ɾ��';

  SShowConfirm = '��ȷ�ϲ���';
  SShowWarning = '��������';
  SShowError = '��ʾ��Ϣ';
  SShowMessage = '������Ϣ';
  SShowSuccess = '�����ɹ�';
  SPrintReceiptPrompt = '�Ƿ���Ҫ��ӡ�ص���';
  SWaitForSum = '���ںϼ�';

  SApplicationShortName = 'У԰һ��ͨϵͳ';
  SSelfServApplicationShortName = '��������';

  SSimpleFieldError = '�����%s����ȷ';
  SFullFieldError = '�����%s%s';
  SFieldErrorFormat = '%s,��ȷ�����ݸ�ʽӦ���ǣ�'#13#10 + '%s';
  SInvalidReinput = '���һ���������ݵĲ���ͬ';
  SInvalidAccount = '��ʽ����ȷ';
  SInvalidSmallData = 'Ӧ�ô��ڵ���%s';
  SInvalidBigData = 'Ӧ��С�ڵ���%s';
  SNotExist = '������';
  SFormatError = '��ʽ����ȷ';
  SNotEmpty = '����Ϊ��';
  SCannotRefreshDates = '���ܸ���ϵͳ���ڣ�����������';

  //SMenuError = '�˵����ݱ��𻵣���͹���Ա��ϵ�����°�װ�˵����ݡ�';
  SMenuError = '�޷���ȡ�˵�����';
  SSyetemDateFormat = 'ϵͳ�������� %s';
  SLocalDateFormat = '''���ĵ������� ''yyyy''��''mm''��''dd''��''';

  SOutOfDate = '%s ����';

  SNoRegisterUI = 'û��ʵ�ֵĹ��� %s';

  SNoInstallHTML = '��Ϊû�а�װIE�����4.0���ϰ汾';
  SProhibitHTML = '��Ϊ���в�����ֹ�ڳ�����ʹ��IE�����';
  SNoOnlineHelp = '����ʹ�����߰�����';
  SNoGuide = '����ʹ���򵼣�';

  SReportCancelled =
    '�����������ֹ����ȡ�������ϣ������������������²�ѯ���ݡ�';

  SConfirmIgnoreError = '%s'#13#10'�Ƿ����?';

  SPrinterError = '��ӡ�����󣬿�����û�а�װȱʡ��ӡ����';
  SNoPrinter = 'û�а�װ��ӡ��';
  SEndPageTooSmall = '����ҳ��Ӧ�ô��ڿ�ʼҳ��';

  SRootMetaMenuCaption = 'У԰һ��ͨ����ϵͳ';
  //////////////////////////////////////////////////
  //SRootMetaMenuCaption = '���н���ϵͳ'; (IN TRADER)
  //////////////////////////////////////////////////
  SInputPassword = '����������';
  SPassword = '����';
  yktVersion = 'ykt_3.1.081'; //�̶�����Ϊ11λ�����ܸı�,�����ֻ���

var
  IdObjectDisplayFormat: string = IdObjectTextFormat2;
  //wsn 20050106 һ��ͨϵͳ�ϴ���ˮ�������ϵͳ��
  SmartCardSubSystemNo: integer;
  SmartCardSubSystemDynamicKey : string;
  SmartCardSubSystemCata: string = 'SmartCard';         
  SmartCardSubSystemName: string = 'SubSystemNo';

  backVer:string;//��̨����汾��

  appPath:string;//����·��
  ifDebug:Integer;//�Ƿ����ģʽ
  yktMenu:string; //һ��ͨ�˵�

  SmartCardSystemDate: string; //��������

  sysDate:string;//ϵͳ����
  accountDate:string;//��������
  bAccountDate:string;//����ǰһ����
  accountTime:string;//ϵͳʱ��
  eaccountDate:string;//�����һ����
  SmartCardPortStatus: Boolean;
  SmartCardAuthStatus: Boolean;
  smartCardPwd:string;  //��Կ
  scMacID:string;   //��½ʱȡ�ñ�����mac��ַ
  scSiteNo:string;  //վ��ţ���½ʱȡ��
  scOperNo:string;    //����Ա�ţ���½�ɹ��󱣴�
  

  //Ĭ��pasm����
  pasmSeat:Integer;
  //�������������
  bjopen:Integer;//������������1�򿪣�0�ر�
  bjcomport:Integer;//�������˿ں�
  maxPer:Integer;//�޶��Ƿ��

  rptTitle:string;    //����ı�ͷ��ʾ
  rptOper:string;     //������
  
  //�Ƿ���ʾ��Ƭ,1��ʾ��0����ʾ
  showphoto:Integer;

  //��½�󱣴�IP��Port��FuncNo
  scIP : string;
  scPORT : Integer;
  scFUNCNO : Integer;
  
  //ϵͳ����·��,·����/��β
  sAppPath:string;
  //ϵͳ����·�����ϼ�·��,
  sPreAppPath:string;

  //ˮ�����
  //ˮ�ؼ�¼
  waterStrings:TStringList;
  //�Ƿ���ʾˮ��Ԥ��ֵ
  waterIfDef:Integer;
  //ˮ��Ԥ��ֵ���
  waterDefMoney:Real;
  //СǮ����ֵ��Ч��
  waterExpiredate:Integer;

  //�°汾�Ƿ���ʾ
  verIfTip:Integer;
  //�°汾��Ϣhttp·��
  verHttpPath:string;
  //��̨��Ͱ汾,���ڸð汾ҵ������
  buSmlVer:string;
  //��̨��ǰ�汾,����ʾ�û�������̨
  buCurrVer:string;

  cpuWaterPrice1:Integer;
  cpuWaterPrice2:Integer;
  cpuWaterPrice3:Integer;

implementation

end.
