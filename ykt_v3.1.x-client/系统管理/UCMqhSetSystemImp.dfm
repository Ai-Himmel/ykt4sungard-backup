inherited dmSetSystemImp: TdmSetSystemImp
  OldCreateOrder = True
  Left = 326
  Width = 848
  object cqSetGridShowModle: TKCWVQuery
    ID = '���ģ����ʾ��ѯ'
    InputBindings = <>
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
    RequestType = 999999
    Left = 24
    Top = 10
  end
  object cpSetGridShowModle: TKCWVProcessor
    ID = '���ģ����ʾ����'
    InputBindings = <>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 1000000
    KCDataset = Dataset
    Left = 24
    Top = 58
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 560
    Top = 8
  end
  object cqSetGridShow: TKCWVQuery
    ID = '�����ʾ����'
    InputBindings = <>
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
    RequestType = 88888
    Left = 24
    Top = 106
  end
  object ctSetGridShowModle: TWVCommandTypeInfo
    ID = '���ģ����ʾ��ѯ'
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
      end>
    Left = 96
    Top = 34
  end
  object ckSetGridShowModle: TWVCommandTypeInfo
    ID = '���ģ����ʾ����'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end>
    Left = 96
    Top = 82
  end
  object ckSetGridShow: TWVCommandTypeInfo
    ID = '�����ʾ����'
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
      end>
    Left = 96
    Top = 130
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
    Left = 176
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
    Left = 176
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
    Left = 240
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
    Left = 240
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
    Left = 176
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
    Left = 240
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
    Left = 176
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
    Left = 176
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
    Left = 240
    Top = 186
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
    Left = 240
    Top = 234
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
    Left = 320
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
    Left = 320
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
    Left = 376
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
      end>
    Left = 376
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
    Left = 24
    Top = 154
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
    Left = 24
    Top = 202
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
    Left = 96
    Top = 178
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
    Left = 96
    Top = 226
  end
  object cqposSerialManager: TKCWVQuery
    ID = 'POS��ˮ��ѯ'
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
        FieldName = 'sdate0'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sname'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '���ױ��'
        FieldName = 'lvol11'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�������'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
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
    RequestType = 846402
    Left = 24
    Top = 250
  end
  object cpposSerialManager: TKCWVProcessor
    ID = 'POS��ˮ����'
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
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sname'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lvol3'
      end
      item
        ParamName = '������ǰ���'
        FieldName = 'Damt3'
      end
      item
        ParamName = '�����׺����'
        FieldName = 'Damt4'
      end
      item
        ParamName = '������'
        FieldName = 'damt0'
      end
      item
        ParamName = '�����'
        FieldName = 'damt1'
      end
      item
        ParamName = '���ױ��'
        FieldName = 'lvol11'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
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
    RequestType = 846402
    KCDataset = Dataset
    Left = 24
    Top = 298
  end
  object WVposSerialManager: TWVCommandTypeInfo
    ID = 'POS��ˮ��ѯ'
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
        ParamName = '�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '���ױ��'
      end
      item
        ParamName = '�������κ�'
      end
      item
        ParamName = '�������'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ˮ״̬'
      end
      item
        ParamName = '������־'
      end>
    Left = 96
    Top = 274
  end
  object WVposSerialManager1: TWVCommandTypeInfo
    ID = 'POS��ˮ����'
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
        ParamName = '����'
      end
      item
        ParamName = '�����״���'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = 'Ǯ����'
      end
      item
        ParamName = '������ǰ���'
      end
      item
        ParamName = '�����׺����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '���ױ��'
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '�������κ�'
      end>
    Left = 96
    Top = 322
  end
  object cqPosSerialImport: TKCWVProcessor
    ID = 'Pos��ˮ����'
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
        ParamName = '���'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '�Ƿ������'
        FieldName = 'scust_type'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sname'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�����״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '������ǰ���'
        FieldName = 'Damt3'
      end
      item
        ParamName = '�����׺����'
        FieldName = 'Damt4'
      end
      item
        ParamName = '������'
        FieldName = 'damt0'
      end
      item
        ParamName = '�����'
        FieldName = 'damt1'
      end
      item
        ParamName = '���ױ��'
        FieldName = 'lvol11'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end>
    RequestType = 846401
    KCDataset = Dataset
    Left = 176
    Top = 266
  end
  object WVPosSerialImport: TWVCommandTypeInfo
    ID = 'Pos��ˮ����'
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
        ParamType = ptInputOutput
      end
      item
        ParamName = '���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�Ƿ������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�̻�����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
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
        ParamName = '�����״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������ǰ���'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '�����׺����'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '������'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '�����'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '���ױ��'
        ParamDataType = kdtInteger
      end>
    Left = 240
    Top = 282
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
    Left = 320
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
    Left = 376
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
    Left = 320
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
    Left = 376
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
    Left = 376
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
    Left = 320
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
    Left = 320
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
    Left = 376
    Top = 274
  end
  object cpposSerManager: TKCWVProcessor
    ID = 'POS�쳣��ˮ����'
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
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sname2'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lvol3'
      end
      item
        ParamName = '������ǰ���'
        FieldName = 'Damt3'
      end
      item
        ParamName = '�����׺����'
        FieldName = 'Damt4'
      end
      item
        ParamName = '������'
        FieldName = 'damt0'
      end
      item
        ParamName = '�����'
        FieldName = 'damt1'
      end
      item
        ParamName = '���ױ��'
        FieldName = 'lvol11'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '���豸������'
        FieldName = 'sname'
      end
      item
        ParamName = '���豸��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = 'sstatus1'
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
    RequestType = 846404
    KCDataset = Dataset
    Left = 176
    Top = 314
  end
  object WVposSeManager1: TWVCommandTypeInfo
    ID = 'POS�쳣��ˮ����'
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
        ParamName = '����'
      end
      item
        ParamName = '�����״���'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = 'Ǯ����'
      end
      item
        ParamName = '������ǰ���'
      end
      item
        ParamName = '�����׺����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '���ױ��'
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '�������κ�'
      end
      item
        ParamName = '����������'
      end
      item
        ParamName = '���豸������'
      end
      item
        ParamName = '���豸��ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ˮ״̬'
      end>
    Left = 240
    Top = 330
  end
  object cqposSerManager: TKCWVQuery
    ID = 'POS�쳣��ˮ��ѯ'
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
        ParamName = '���׽�������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sname'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '���ױ��'
        FieldName = 'lvol11'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�������'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '���׿�ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lwithdraw_flag'
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
    RequestType = 846404
    Left = 320
    Top = 306
  end
  object WVposSeManager: TWVCommandTypeInfo
    ID = 'POS�쳣��ˮ��ѯ'
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
        ParamName = '���׿�ʼ����'
      end
      item
        ParamName = '�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '���ױ��'
      end
      item
        ParamName = '�������κ�'
      end
      item
        ParamName = '�������'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ˮ״̬'
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '���׽�������'
      end
      item
        ParamName = '�豸���'
      end>
    Left = 376
    Top = 322
  end
  object cqPatchDel: TWVCommandTypeInfo
    ID = 'pos��ˮ����ɾ��'
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
        ParamName = '������־'
      end
      item
        ParamName = '������־'
        ParamDataType = kdtInteger
      end>
    Left = 488
    Top = 34
  end
  object cpPatchdel: TKCWVProcessor
    ID = 'pos��ˮ����ɾ��'
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
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '������־'
        FieldName = 'lwithdraw_flag'
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
    RequestType = 846402
    KCDataset = Dataset
    Left = 432
    Top = 18
  end
  object cqSetWaterPrice: TKCWVQuery
    ID = '���ˮ�����ò�ѯ'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
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
    RequestType = 846206
    Left = 432
    Top = 66
  end
  object cpSetWaterPrice: TKCWVProcessor
    ID = '���ˮ������'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = 'ˮ��1'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = 'ˮ��2'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = 'ˮ��3'
        FieldName = 'lvol2'
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
    RequestType = 846206
    KCDataset = Dataset
    Left = 432
    Top = 114
  end
  object WVSetWaterPrice: TWVCommandTypeInfo
    ID = '���ˮ������'
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
        ParamName = 'ˮ��1'
      end
      item
        ParamName = 'ˮ��2'
      end
      item
        ParamName = 'ˮ��3'
      end>
    Left = 488
    Top = 130
  end
  object WVSetWaterPriceQ: TWVCommandTypeInfo
    ID = '���ˮ�����ò�ѯ'
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
      end>
    Left = 488
    Top = 82
  end
end
