inherited dmSysSetImp: TdmSysSetImp
  OldCreateOrder = True
  Left = 315
  Top = 164
  Height = 492
  Width = 649
  object DataSet: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 368
    Top = 32
  end
  object cqSetDict: TKCWVQuery
    ID = '��ѯ�����ֵ�'
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
        FieldName = 'semail'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'С�����'
        FieldName = 'semail2'
      end
      item
        ParamName = '�������'
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
    RequestType = 820511
    Left = 96
    Top = 90
  end
  object cpSetDict: TKCWVProcessor
    ID = '���������ֵ�'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'scust_no'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��Ŀ���ƣ��ֵ���ࣩ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������루�ֵ䵥Ԫ���룩'
        FieldName = 'sorder0'
      end
      item
        ParamName = '�������ƣ��ֵ䵥Ԫ���ݣ�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��������'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820511
    KCDataset = DataSet
    Left = 168
    Top = 26
  end
  object cqSetStation: TKCWVQuery
    ID = 'վ����Ϣ��ѯ'
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
        FieldName = 'lvol1'
      end
      item
        ParamName = '�������'
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
    RequestType = 820341
    Left = 32
    Top = 26
  end
  object cpSetStation: TKCWVProcessor
    ID = '����վ��'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'վ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ip��ַ'
        FieldName = 'sphone'
      end
      item
        ParamName = '���������ַ'
        FieldName = 'sphone2'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '��ע'
        FieldName = 'snote'
      end
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820341
    KCDataset = DataSet
    Left = 32
    Top = 218
  end
  object cpUpdOperPwd: TKCWVProcessor
    ID = '�޸�����'
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
        ParamName = '����Ա����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '������'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '������'
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
    RequestType = 820331
    KCDataset = DataSet
    Left = 32
    Top = 74
  end
  object cqSetOperator: TKCWVQuery
    ID = '����Ա��ѯ'
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
        ParamName = '����Ա����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '״̬'
        FieldName = 'sstatus3'
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
    RequestType = 820301
    Left = 96
    Top = 42
  end
  object cpSetOperator: TKCWVProcessor
    ID = '���ò���Ա'
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
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'sname'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '�����'
        FieldName = 'lbank_acc_type2'
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
        ParamName = '�����ʼ�'
        FieldName = 'semail'
      end
      item
        ParamName = '��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '�ʱ�'
        FieldName = 'spost_code'
      end
      item
        ParamName = '�Ƿ����Ʒ���վ��'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '����Ա״̬'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����Ȩ��'
        FieldName = 'usset1'
      end
      item
        ParamName = '�˵�Ȩ��1'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '�˵�Ȩ��2'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '�˵�Ȩ��3'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '�˵�Ȩ��4'
        FieldName = 'vsvarstr3'
      end
      item
        ParamName = '��ֵ�޶�'
        FieldName = 'damt0'
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
    RequestType = 820301
    KCDataset = DataSet
    Left = 32
    Top = 122
  end
  object cqSetModuleAuth: TKCWVQuery
    ID = 'Ȩ��ģ���ѯ'
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
        ParamName = 'ģ�����'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�������'
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
    RequestType = 820311
    Left = 96
    Top = 186
  end
  object cpSetModuleAuth: TKCWVProcessor
    ID = '����Ȩ��ģ��'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'scust_no'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ģ�����'
        FieldName = 'sbank_code'
      end
      item
        ParamName = 'ģ������'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '����Ȩ��'
        FieldName = 'usset1'
      end
      item
        ParamName = '�˵�Ȩ��1'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '�˵�Ȩ��2'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '�˵�Ȩ��3'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '�˵�Ȩ��4'
        FieldName = 'vsvarstr3'
      end
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820311
    KCDataset = DataSet
    Left = 32
    Top = 170
  end
  object cqSetOperStation: TKCWVQuery
    ID = '����Ա��¼վ���ѯ'
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
        ParamName = '����Ա'
        FieldName = 'scust_no'
      end
      item
        ParamName = 'վ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�������'
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
    RequestType = 820321
    Left = 96
    Top = 138
  end
  object cpSetOperStation: TKCWVProcessor
    ID = '�������Ա��¼վ��'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '����Ա'
        FieldName = 'scust_no'
      end
      item
        ParamName = 'վ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820321
    KCDataset = DataSet
    Left = 96
    Top = 234
  end
  object cpResetOperPwd: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'scust_no2'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '����Ա'
        FieldName = 'scust_no'
      end
      item
        ParamName = '������'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820332
    KCDataset = DataSet
    Left = 168
    Top = 74
  end
  object cpSetSaveOper: TKCWVProcessor
    ID = '���ó�ֵ����Ա'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'scust_no2'
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
        ParamName = '����Ա'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '����ԱȨ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����'
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
    RequestType = 820305
    KCDataset = DataSet
    Left = 168
    Top = 122
  end
  object cpOperCardBind: TKCWVProcessor
    ID = '��ֵ����Ա����'
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
        ParamName = '��������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'sname'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '��Ȩ����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '��Ȩ����'
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
    RequestType = 846210
    KCDataset = DataSet
    Left = 168
    Top = 218
  end
  object kcQOperCardBind: TKCWVQuery
    ID = '��ֵ����Ա����Q'
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
        ParamName = '��������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'sname'
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
    RequestType = 846210
    Left = 168
    Top = 170
  end
  object kcCardInfoQuery: TKCWVQuery
    ID = '�ѿ�����Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = 'ע������'
        FieldName = 'sdate1'
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
        ParamName = '������'
        FieldName = 'sstation1'
      end
      item
        ParamName = '��״̬'
        FieldName = 'sserial0'
      end
      item
        ParamName = '�����־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '��ԭ��'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '������'
        FieldName = 'lserial0'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 846602
    Left = 166
    Top = 264
  end
end
