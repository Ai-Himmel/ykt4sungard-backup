inherited dmSetSystemImp: TdmSetSystemImp
  OldCreateOrder = True
  Left = 285
  Width = 848
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 560
    Top = 8
  end
  object cqsetPlanTask: TKCWVQuery
    ID = '�ƻ������ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846202
    Left = 160
    Top = 10
  end
  object cpsetPlanTask: TKCWVProcessor
    ID = '�ƻ��������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '����˵��'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '������'
        FieldName = 'snote'
      end
      item
        ParamName = '����·��'
        FieldName = 'Vsvarstr1'
      end
      item
        ParamName = '�����в���'
        FieldName = 'Vsvarstr2'
      end
      item
        ParamName = 'ÿ��һ��'
        FieldName = 'Lvol1'
      end
      item
        ParamName = 'ÿ����һ��'
        FieldName = 'Lvol2'
      end
      item
        ParamName = 'ÿ��һ��'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '���п�ʼʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = '���н���ʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '�Ƿ�����'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846202
    KCDataset = Dataset
    Left = 160
    Top = 58
  end
  object WVQueryPlanTask: TWVCommandTypeInfo
    ID = '�ƻ������ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '����˵��'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '����·��'
      end
      item
        ParamName = '�����в���'
      end
      item
        ParamName = 'ÿ��һ��'
      end
      item
        ParamName = 'ÿ����һ��'
      end
      item
        ParamName = 'ÿ��һ��'
      end
      item
        ParamName = '���п�ʼʱ��'
      end
      item
        ParamName = '���н���ʱ��'
      end
      item
        ParamName = '�Ƿ�����'
      end
      item
        ParamName = '��������'
      end>
    Left = 224
    Top = 34
  end
  object WVSetPlanTask: TWVCommandTypeInfo
    ID = '�ƻ��������'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '����˵��'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '����·��'
      end
      item
        ParamName = '�����в���'
      end
      item
        ParamName = 'ÿ��һ��'
      end
      item
        ParamName = 'ÿ����һ��'
      end
      item
        ParamName = 'ÿ��һ��'
      end
      item
        ParamName = '���п�ʼʱ��'
      end
      item
        ParamName = '���н���ʱ��'
      end
      item
        ParamName = '�Ƿ�����'
      end
      item
        ParamName = '��������'
      end>
    Left = 224
    Top = 82
  end
  object cqqueryPlanTask: TKCWVQuery
    ID = '�ƻ�������־��ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846203
    Left = 160
    Top = 114
  end
  object WVQueryPlanTaskInfo: TWVCommandTypeInfo
    ID = '�ƻ�������־��ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '��������'
      end>
    Left = 224
    Top = 130
  end
  object cqsetMesList: TKCWVQuery
    ID = '��Ϣ���в�ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '��Ϣ���'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '��Ϣ״̬'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '��Ϣ����'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '��ϵͳ���'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '�豸���'
        FieldName = 'Lvol5'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846204
    Left = 160
    Top = 170
  end
  object cpsetMesList: TKCWVProcessor
    ID = '��Ϣ���й���'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��Ϣ���'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '��Ϣ״̬'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '����ʹ���'
        FieldName = 'Lvol9'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846204
    KCDataset = Dataset
    Left = 160
    Top = 218
  end
  object WVQueryMesList: TWVCommandTypeInfo
    ID = '��Ϣ���в�ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��Ϣ���'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��Ϣ״̬'
      end
      item
        ParamName = '��Ϣ����'
      end
      item
        ParamName = '��ϵͳ���'
      end
      item
        ParamName = '�豸���'
      end
      item
        ParamName = '��������'
      end>
    Left = 224
    Top = 178
  end
  object WVSetMesList: TWVCommandTypeInfo
    ID = '��Ϣ���й���'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��Ϣ���'
      end
      item
        ParamName = '��Ϣ״̬'
      end
      item
        ParamName = '����ʹ���'
      end
      item
        ParamName = '��������'
      end>
    Left = 224
    Top = 226
  end
  object cqsetNetInfo: TKCWVQuery
    ID = '������Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = 'վ���'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��������'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�����˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = 'sbankname'
      end
      item
        ParamName = '��ϵ��'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone2'
      end
      item
        ParamName = '����'
        FieldName = 'sphone3'
      end
      item
        ParamName = '��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��������'
        FieldName = 'spost_code'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846501
    Left = 304
    Top = 18
  end
  object cpsetNetInfo: TKCWVProcessor
    ID = '������Ϣ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = 'վ���'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��������'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�����˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = 'sbankname'
      end
      item
        ParamName = '��ϵ��'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone2'
      end
      item
        ParamName = '����'
        FieldName = 'sphone3'
      end
      item
        ParamName = '��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��������'
        FieldName = 'spost_code'
      end
      item
        ParamName = '����'
        FieldName = 'snote2'
      end
      item
        ParamName = '��������'
        FieldName = 'snote'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846501
    KCDataset = Dataset
    Left = 304
    Top = 66
  end
  object WVNetInfoQuery: TWVCommandTypeInfo
    ID = '������Ϣ��ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = 'վ���'
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '���д���'
      end
      item
        ParamName = '�����˺�'
      end
      item
        ParamName = '�����ʻ���'
      end
      item
        ParamName = '��ϵ��'
      end
      item
        ParamName = '�绰'
      end
      item
        ParamName = '�ֻ�'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��ַ'
      end
      item
        ParamName = '��������'
      end>
    Left = 360
    Top = 34
  end
  object WVSetNetInfo: TWVCommandTypeInfo
    ID = '������Ϣ����'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = 'վ���'
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '���д���'
      end
      item
        ParamName = '�����˺�'
      end
      item
        ParamName = '�����ʻ���'
      end
      item
        ParamName = '��ϵ��'
      end
      item
        ParamName = '�绰'
      end
      item
        ParamName = '�ֻ�'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��ַ'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��������'
      end>
    Left = 360
    Top = 82
  end
  object cqsetTradeFee: TKCWVQuery
    ID = '�����շѲ�ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '�շѽ��'
        FieldName = 'damt0'
      end
      item
        ParamName = '�շ�˳��'
        FieldName = 'Lvol3'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846502
    Left = 16
    Top = 18
  end
  object cpsetTradeFee: TKCWVProcessor
    ID = '�����շ�����'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '�շѽ��'
        FieldName = 'damt0'
      end
      item
        ParamName = '�շ�˳��'
        FieldName = 'Lvol3'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846502
    KCDataset = Dataset
    Left = 16
    Top = 66
  end
  object WVQTradeFee: TWVCommandTypeInfo
    ID = '�����շѲ�ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '�շ����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�շѷ�ʽ'
      end
      item
        ParamName = '�շѽ��'
      end
      item
        ParamName = '�շ�˳��'
      end>
    Left = 80
    Top = 42
  end
  object WVSetTradeFee: TWVCommandTypeInfo
    ID = '�����շ�����'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '�շ����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�շѷ�ʽ'
      end
      item
        ParamName = '�շѽ��'
      end
      item
        ParamName = '�շ�˳��'
      end>
    Left = 80
    Top = 90
  end
  object cqCheck: TKCWVProcessor
    ID = 'Pos��ˮ���1'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '���״���'
        FieldName = 'Lvol6'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846403
    KCDataset = Dataset
    Left = 304
    Top = 114
  end
  object WVCheck: TWVCommandTypeInfo
    ID = 'Pos��ˮ���1'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '���κ�'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '���״���'
        ParamDataType = kdtInteger
      end>
    Left = 360
    Top = 130
  end
  object cqqueryOperLog: TKCWVQuery
    ID = '������־��ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'վ���'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = 'վ����ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '����Ա'
        FieldName = 'Semp_no'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 820302
    Left = 304
    Top = 162
  end
  object WVQueryOperLog: TWVCommandTypeInfo
    ID = '������־��ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = 'վ���'
      end
      item
        ParamName = 'վ����ˮ��'
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '��ʼ����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��ˮ״̬'
      end
      item
        ParamName = '��������'
      end>
    Left = 360
    Top = 178
  end
  object cqCardFee: TWVCommandTypeInfo
    ID = '�����շ����ò�ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�շ����'
      end>
    Left = 360
    Top = 226
  end
  object KCWcardFee: TKCWVQuery
    ID = '�����շ����ò�ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846111
    Left = 304
    Top = 210
  end
  object cpCardFee: TKCWVProcessor
    ID = '�����շ�����'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846111
    KCDataset = Dataset
    Left = 304
    Top = 258
  end
  object cqCardFeeSet: TWVCommandTypeInfo
    ID = '�����շ�����'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�շ����'
      end>
    Left = 360
    Top = 274
  end
  object WVCsetCardType: TWVCommandTypeInfo
    ID = '���������'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '���ɱ���'
      end
      item
        ParamName = '���������'
      end
      item
        ParamName = '��;'
      end
      item
        ParamName = '�ܷ�����'
      end
      item
        ParamName = '�ܷ񲹰�'
      end
      item
        ParamName = '�ܷ��ʧ'
      end
      item
        ParamName = '�Ƿ�֧�ֶ�Ǯ��'
      end
      item
        ParamName = 'ʹ��״̬'
      end
      item
        ParamName = '��Ч����'
      end
      item
        ParamName = '���õ��շ����'
      end
      item
        ParamName = 'Ĭ���շ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�Ƿ�������'
      end
      item
        ParamName = '���������'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'Ԥ����'
      end
      item
        ParamName = '�����޶�'
      end
      item
        ParamName = '���޶�'
      end>
    Left = 80
    Top = 186
  end
  object WVQsetCardType: TWVCommandTypeInfo
    ID = '������ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�����'
      end>
    Left = 80
    Top = 138
  end
  object cqsetCardType: TKCWVQuery
    ID = '������ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846101
    Left = 16
    Top = 114
  end
  object cpsetCardType: TKCWVProcessor
    ID = '���������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '���ɱ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '���������'
        FieldName = 'sname'
      end
      item
        ParamName = '��;'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '�ܷ�����'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '�ܷ񲹰�'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '�ܷ��ʧ'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '�Ƿ�֧�ֶ�Ǯ��'
        FieldName = 'sstatus4'
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '��Ч����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '���õ��շ����'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = 'Ĭ���շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�Ƿ�������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '���������'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'damt0'
      end
      item
        ParamName = '�����޶�'
        FieldName = 'damt1'
        DefaultValue = 0
      end
      item
        ParamName = '���޶�'
        FieldName = 'damt2'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846101
    KCDataset = Dataset
    Left = 16
    Top = 162
  end
  object KCPKGQuery: TKCWVQuery
    ID = '������ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstock_code'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 2029
    Left = 16
    Top = 210
  end
  object WVPKGQuery: TWVCommandTypeInfo
    ID = '������ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '��ʼ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '����״̬'
      end>
    Left = 80
    Top = 234
  end
  object KCPKGOper: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstock_code'
      end
      item
        ParamName = '�������'
        FieldName = 'scust_no'
      end
      item
        ParamName = '��ע'
        FieldName = 'vsvarstr1'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 2029
    KCDataset = Dataset
    Left = 16
    Top = 258
  end
  object WVPKGOper: TWVCommandTypeInfo
    ID = '��������'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '����״̬'
      end
      item
        ParamName = '�������'
      end
      item
        ParamName = '��ע'
      end>
    Left = 80
    Top = 282
  end
  object KCFileQ: TKCWVQuery
    ID = '�ļ���ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�������'
        FieldName = 'scust_no'
      end
      item
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstock_code'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 2030
    Left = 160
    Top = 266
  end
  object WVFielQ: TWVCommandTypeInfo
    ID = '�ļ���ѯ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '�������'
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '����״̬'
      end>
    Left = 224
    Top = 274
  end
  object KCFileOper: TKCWVProcessor
    ID = '�ļ�����'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstock_code'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '��ע'
        FieldName = 'vsvarstr1'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 2030
    KCDataset = Dataset
    Left = 160
    Top = 314
  end
  object WVFileOper: TWVCommandTypeInfo
    ID = '�ļ�����'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '����״̬'
      end
      item
        ParamName = '�������'
      end
      item
        ParamName = '��ע'
      end>
    Left = 224
    Top = 322
  end
end
