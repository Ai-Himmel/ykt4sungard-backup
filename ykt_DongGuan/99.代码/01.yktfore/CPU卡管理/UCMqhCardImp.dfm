inherited dmCardImp: TdmCardImp
  OldCreateOrder = True
  Left = 375
  Top = 251
  Height = 433
  Width = 509
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 88
  end
  object cqMoneyIn: TKCWVProcessor
    ID = '����ֵ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����'
        FieldName = 'sphone3'
      end
      item
        ParamName = '������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�뿨���'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol5'
      end
      item
        ParamName = '���Ѵ���'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'Lvol9'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '��ֵ���'
        FieldName = 'damt0'
      end
      item
        ParamName = 'psam����'
        FieldName = 'snote'
      end
      item
        ParamName = '������ˮ��'
        FieldName = 'sphone'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime0'
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
        ParamName = '����'
        FieldName = 'sphone3'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '����1'
        FieldName = 'lvol0'
      end>
    RequestType = 846312
    KCDataset = Dataset
    Left = 22
    Top = 24
  end
  object cqMoneyOut: TKCWVProcessor
    ID = '��֧ȡ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�뿨���'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '֧ȡ���'
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
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'stime3'
      end>
    RequestType = 846314
    KCDataset = Dataset
    Left = 22
    Top = 72
  end
  object cqRefreshCard: TKCWVProcessor
    ID = '���¿���Ϣ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '������'
        FieldName = 'sstation1'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '����������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�����'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�뵥���޶�'
        FieldName = 'damt11'
      end
      item
        ParamName = '�����޶�'
        FieldName = 'damt12'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol5'
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
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
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
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
      end
      item
        ParamName = '�Ա�'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '����������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol8'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'lvol4'
      end
      item
        ParamName = '������'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '�����޶�'
        FieldName = 'lvol11'
      end
      item
        ParamName = '���޶�'
        FieldName = 'lvol12'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime3'
      end>
    RequestType = 846320
    KCDataset = Dataset
    Left = 22
    Top = 120
  end
  object cpSetMoney: TKCWVProcessor
    ID = '���������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������'
        FieldName = 'sstation1'
      end
      item
        ParamName = '�뿨���'
        FieldName = 'Lvol7'
        DefaultValue = 0
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '�������'
        FieldName = 'damt0'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'scard0'
      end
      item
        ParamName = '��֤����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '��֤����'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '�ն˱��'
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
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol8'
      end>
    RequestType = 846322
    KCDataset = Dataset
    Left = 22
    Top = 168
  end
  object cqAccountQ: TKCWVQuery
    ID = '�˻���Ϣ��ѯ'
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
        FieldName = 'sroom_no2'
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
        FieldName = 'scard0'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ƿ�����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�����к�'
        FieldName = 'sphone3'
      end
      item
        ParamName = '��״̬'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '��ѯ���'
        FieldName = 'sstat_type'
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
    RequestType = 2006
    Left = 88
    Top = 42
  end
  object cqCardSericalQ: TKCWVQuery
    ID = '������ˮ��ѯ'
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
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
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
        FieldName = 'sroom_no2'
      end
      item
        ParamName = '�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'sphone3'
      end
      item
        ParamName = '����'
        FieldName = 'scard0'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '������'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '������'
        FieldName = 'spost_code'
      end
      item
        ParamName = '����Ա'
        FieldName = 'semp_no'
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
    RequestType = 2007
    Left = 88
    Top = 90
  end
  object cqCardInfoQ: TKCWVQuery
    ID = '�ѷ�����Ϣ��ѯ'
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
        ParamName = '��������'
        FieldName = 'sroom_no2'
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
        ParamName = '���к�'
        FieldName = 'sphone3'
      end
      item
        ParamName = '����'
        FieldName = 'scard0'
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
    RequestType = 2002
    Left = 88
    Top = 138
  end
  object KCLoss_UN: TKCWVProcessor
    ID = '��ʧ���'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '����'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'psam����'
        FieldName = 'snote'
      end
      item
        ParamName = '������ˮ��'
        FieldName = 'sphone'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime0'
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
        ParamName = '�汾��'
        FieldName = 'semail'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�����'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end>
    RequestType = 2008
    KCDataset = Dataset
    Left = 86
    Top = 184
  end
  object cqReturnMoney: TKCWVQuery
    ID = '��ֵ��ѯ'
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
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '������'
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
    RequestType = 3001
    Left = 88
    Top = 234
  end
  object KCRtnMoney: TKCWVQuery
    ID = '��ֵ����'
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
        FieldName = 'sdate0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����ǰ��ֵ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '����ǰ���Ѵ���'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '�����'
        FieldName = 'lvol7'
        DefaultValue = 0
      end
      item
        ParamName = '�ϱ�sam�ն˺�'
        FieldName = 'sserial0'
      end
      item
        ParamName = '�ϱ�����'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '�ϱʽ��'
        FieldName = 'lvol8'
        DefaultValue = 0
      end
      item
        ParamName = '�ϱ�����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '�ϱ�ʱ��'
        FieldName = 'sorder1'
      end
      item
        ParamName = '����Ա���'
        FieldName = 'lbank_acc_type2'
        DefaultValue = 0
      end
      item
        ParamName = '����Ա��ˮ'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�ο���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '��ע'
        FieldName = 'snote'
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
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol9'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = '����Ա��ˮ'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�����'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '�ο���'
        FieldName = 'scert_no'
      end>
    RequestType = 2021
    Left = 88
    Top = 282
  end
  object KCChangeCardA: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '����ԭ��'
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
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '���뵥��'
        FieldName = 'lvol1'
      end>
    RequestType = 2022
    KCDataset = Dataset
    Left = 150
    Top = 24
  end
  object KCReNewApp: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '����ԭ��'
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
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end>
    RequestType = 2023
    KCDataset = Dataset
    Left = 150
    Top = 72
  end
  object KCDestoryApp: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '����ԭ��'
        FieldName = 'snote'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '���Ѵ���'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '�����'
        FieldName = 'lvol7'
        DefaultValue = 0
      end
      item
        ParamName = '�ϱ�sam�ն�'
        FieldName = 'sserial0'
      end
      item
        ParamName = '�ϱ�����'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '�ϱʽ��'
        FieldName = 'lvol8'
        DefaultValue = 0
      end
      item
        ParamName = '�ϱ�����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '�ϱ�ʱ��'
        FieldName = 'sorder1'
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
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end>
    RequestType = 2024
    KCDataset = Dataset
    Left = 150
    Top = 120
  end
  object KCRenewOper: TKCWVProcessor
    ID = '�������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '���Ѵ���'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '�����'
        FieldName = 'lvol7'
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
      end
      item
        ParamName = '�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol9'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end>
    RequestType = 2026
    KCDataset = Dataset
    Left = 150
    Top = 168
  end
  object KCChangeCardOper: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = '��Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard1'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '���Ѵ���'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '�����'
        FieldName = 'lvol7'
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
      end
      item
        ParamName = '�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol9'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end>
    RequestType = 2025
    KCDataset = Dataset
    Left = 150
    Top = 216
  end
  object KCDestoryOper: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
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
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '�˿����'
        FieldName = 'lvol8'
      end>
    RequestType = 2027
    KCDataset = Dataset
    Left = 150
    Top = 264
  end
  object cqappDeal: TKCWVQuery
    ID = '���뵥����'
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
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '���뵥��'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '��������'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '����״̬'
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
    RequestType = 2018
    Left = 216
    Top = 10
  end
  object KCCancelApp: TKCWVProcessor
    ID = '���뵥ȡ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���뵥��'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '������־'
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
    RequestType = 2018
    KCDataset = Dataset
    Left = 214
    Top = 56
  end
  object KCMakeAnon: TKCWVProcessor
    ID = '��������������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '�����'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '������λ'
        FieldName = 'lvol0'
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
      end
      item
        ParamName = '��������'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end>
    RequestType = 2019
    KCDataset = Dataset
    Left = 214
    Top = 104
  end
  object KCNonCardchange: TKCWVProcessor
    ID = '�Ǽ�����������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '���뵥��'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ԭ����'
        FieldName = 'scard1'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '���Ѵ���'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '�����'
        FieldName = 'lvol7'
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
      end
      item
        ParamName = '�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol9'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'scert_no'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end>
    RequestType = 2031
    KCDataset = Dataset
    Left = 214
    Top = 152
  end
  object KCTradeCancel: TKCWVProcessor
    ID = '���׳���'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��������Ա'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '�������'
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
    RequestType = 2035
    KCDataset = Dataset
    Left = 214
    Top = 200
  end
  object cqSetPOSInfo: TKCWVQuery
    ID = '�豸��Ϣά����ѯ'
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
        ParamName = '�豸�ն˺�'
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
    RequestType = 2005
    Left = 24
    Top = 218
  end
  object KCMachineConsume: TKCWVProcessor
    ID = '����������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���ױ�־'
        FieldName = 'sstat_type'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'sam��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '���Ѵ���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '���ѽ��'
        FieldName = 'damt0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol7'
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
        ParamName = '��������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol9'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end>
    RequestType = 2036
    KCDataset = Dataset
    Left = 214
    Top = 248
  end
  object KCConsumeOk: TKCWVProcessor
    ID = '����������ȷ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���ױ�־'
        FieldName = 'sstat_type'
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
        ParamName = 'sam�ն˺�'
        FieldName = 'sserial1'
      end
      item
        ParamName = 'sam��ˮ��'
        FieldName = 'lserial0'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'scert_no'
      end
      item
        ParamName = 'TAC��'
        FieldName = 'sserial4'
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
        ParamName = '��������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol9'
      end
      item
        ParamName = '������'
        FieldName = 'sname2'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ֻ�'
        FieldName = 'sphone'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end>
    RequestType = 2036
    KCDataset = Dataset
    Left = 214
    Top = 296
  end
  object KCConsumeSerial: TKCWVQuery
    ID = '������ˮ��ѯ'
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
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'scard0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '������'
        FieldName = 'spost_code'
      end
      item
        ParamName = '�̻���'
        FieldName = 'lvol3'
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
    RequestType = 3002
    Left = 280
    Top = 26
  end
end
