inherited dmCustomerImp: TdmCustomerImp
  OldCreateOrder = True
  Left = 555
  Top = 181
  Height = 467
  Width = 636
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 368
  end
  object cqSetCustInfo: TKCWVQuery
    ID = '�ͻ���Ϣά����ѯ'
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
        FieldName = 'sstat_type'
      end
      item
        ParamName = '��������'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '����'
        FieldName = 'snote'
      end
      item
        ParamName = '֤������'
        FieldName = 'sroom_no'
      end
      item
        ParamName = '֤������'
        FieldName = 'spager'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�Ա�'
        FieldName = 'scust_type'
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
        ParamName = '��������'
        FieldName = 'semail'
      end
      item
        ParamName = '����'
        FieldName = 'scard0'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'sphone3'
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
    RequestType = 2001
    Left = 32
    Top = 26
  end
  object cpSetCustInfo: TKCWVProcessor
    ID = '�ͻ���Ϣά��'
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
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'scard0'
      end
      item
        ParamName = '��������'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '������Ч����(��)'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstatus0'
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'damt0'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'snote'
      end
      item
        ParamName = '֤������'
        FieldName = 'sroom_no'
      end
      item
        ParamName = '֤������'
        FieldName = 'spager'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '���'
        FieldName = 'lvol2'
      end
      item
        ParamName = '�Ա�'
        FieldName = 'scust_type'
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
        ParamName = '��������'
        FieldName = 'semail'
      end
      item
        ParamName = '��λ����'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sorder0'
      end
      item
        ParamName = '�Ļ��̶�'
        FieldName = 'sorder1'
      end
      item
        ParamName = '������ò'
        FieldName = 'sorder2'
      end
      item
        ParamName = '������Դ'
        FieldName = 'sserial0'
      end
      item
        ParamName = '����'
        FieldName = 'snation_code'
      end
      item
        ParamName = '����'
        FieldName = 'sserial1'
      end
      item
        ParamName = '����'
        FieldName = 'scert_addr'
      end
      item
        ParamName = '�������ڵ�����'
        FieldName = 'sserial2'
      end
      item
        ParamName = '�������ڵ�'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '��ס����'
        FieldName = 'sserial3'
      end
      item
        ParamName = '��ס��ַ'
        FieldName = 'vsvarstr2'
      end
      item
        ParamName = '��ס����'
        FieldName = 'sdate2'
      end
      item
        ParamName = '�״ε��ﱾ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'sname'
      end
      item
        ParamName = '�Ƿ�ɾ��'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '�������'
        FieldName = 'semp_no'
      end
      item
        ParamName = '���ŷ����'
        FieldName = 'semail2'
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
    RequestType = 2001
    KCDataset = Dataset
    Left = 32
    Top = 74
  end
  object cqCustPay: TKCWVQuery
    ID = '�ɷ��쿨'
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
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'damt0'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'scard0'
      end
      item
        ParamName = '�����к�'
        FieldName = 'sphone3'
      end
      item
        ParamName = '������ˮ��'
        FieldName = 'sphone'
      end
      item
        ParamName = 'psam����'
        FieldName = 'snote'
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
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�����'
        FieldName = 'sphone2'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '���Ѵ���'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '�����'
        FieldName = 'lvol4'
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
      end
      item
        ParamName = '������ˮ'
        FieldName = 'lserial0'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end>
    RequestType = 2001
    Left = 32
    Top = 122
  end
  object KCMakeCardCQ: TKCWVQuery
    ID = '�ƿ���˲�ѯ'
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
        FieldName = 'sstat_type'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '��������'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol2'
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
    RequestType = 2010
    Left = 32
    Top = 170
  end
  object KCMakeCardCheck: TKCWVQuery
    ID = '�ƿ����'
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
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '���κ�'
        FieldName = 'snote'
      end
      item
        ParamName = '�����к�'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'Ӧ������'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '���б���'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'sname'
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
    RequestType = 2014
    Left = 32
    Top = 218
  end
  object KCFeeQuery: TKCWVQuery
    ID = '�ɷѲ�ѯ'
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
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'scard0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol1'
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
      end
      item
        ParamName = 'Ԥ�����'
        FieldName = 'damt0'
        DefaultValue = 0
      end
      item
        ParamName = '�ɷ���Ϣ'
        FieldName = 'snote'
      end>
    RequestType = 2009
    Left = 32
    Top = 266
  end
  object cqExpMakeCardList: TKCWVQuery
    ID = '�ƿ���������'
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
        FieldName = 'snote'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��������'
        FieldName = 'sroom_no2'
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
    RequestType = 2015
    Left = 112
    Top = 10
  end
  object KCFeePay: TKCWVQuery
    ID = '�ɷ�'
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
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'damt0'
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
    RequestType = 2001
    Left = 112
    Top = 58
  end
  object KCSavePhoto: TKCWVQuery
    ID = '������Ƭ'
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
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '�ļ���'
        FieldName = 'saddr'
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
    RequestType = 2016
    Left = 112
    Top = 106
  end
  object KCImpCardInfo: TKCWVQuery
    ID = '�������ݵ���'
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
        ParamName = '������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = 'ҵ����'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '��Դ��'
        FieldName = 'sphone'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'sphone2'
      end
      item
        ParamName = 'UCID'
        FieldName = 'sphone3'
      end
      item
        ParamName = '������'
        FieldName = 'spager'
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
    RequestType = 2017
    Left = 112
    Top = 154
  end
  object KCTwoCheckQ: TKCWVQuery
    ID = '�����ƿ���ѯ'
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
        FieldName = 'sphone'
      end
      item
        ParamName = '���к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��������'
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
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
    RequestType = 2032
    Left = 112
    Top = 202
  end
  object KCTwoCheck: TKCWVQuery
    ID = '�������'
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
        FieldName = 'sphone'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '˳���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '������־'
        FieldName = 'lvol2'
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
    RequestType = 2033
    Left = 112
    Top = 250
  end
  object KCMakeCard2Q: TKCWVQuery
    ID = '�����ƿ������ѯ'
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
        ParamName = '�ƿ�״̬'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�����ƿ����κ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '��˽�������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '��˿�ʼ����'
        FieldName = 'sdate1'
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
    RequestType = 2034
    Left = 112
    Top = 298
  end
  object KCImpPhoneNo: TKCWVQuery
    ID = '�ֻ����뵼��'
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
        ParamName = '�ֻ�ͨ������'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�ֻ���'
        FieldName = 'sphone'
      end
      item
        ParamName = 'ʱ���'
        FieldName = 'scust_auth'
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
    RequestType = 2037
    Left = 184
    Top = 26
  end
  object cqSetPhoneNo: TKCWVQuery
    ID = '�ֻ�����Ϣά��Q'
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
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ֻ�ͨ������'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�ֻ���'
        FieldName = 'sphone'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'scust_auth'
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
    RequestType = 2038
    Left = 184
    Top = 74
  end
  object KCSet: TKCWVQuery
    ID = '�ֻ�����Ϣά��'
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
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ֻ�ͨ������'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�ֻ���'
        FieldName = 'sphone'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'scust_auth'
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
    RequestType = 2038
    Left = 184
    Top = 122
  end
end
