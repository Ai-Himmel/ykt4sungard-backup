inherited dmReportImp: TdmReportImp
  OldCreateOrder = True
  Left = 452
  Top = 190
  Height = 546
  Width = 734
  object cqUnsuitReport: TKCWVQuery
    ID = '���˶��ʲ�ƽ�嵥��'
    InputBindings = <
      item
        ParamName = '��ʼ����'
        FieldName = 'sorder1'
      end
      item
        ParamName = '��������'
        FieldName = 'sorder2'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 900130
    Left = 16
    Top = 10
  end
  object cqTransfer: TKCWVQuery
    ID = 'ת�ʶ��ʱ�'
    InputBindings = <
      item
        ParamName = '��ʼ����'
        FieldName = 'sorder1'
      end
      item
        ParamName = '��������'
        FieldName = 'sorder2'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 900210
    Left = 19
    Top = 59
  end
  object cqEquip: TKCWVQuery
    ID = '�豸��ֵ��'
    InputBindings = <
      item
        ParamName = '��ʼ����'
        FieldName = 'sorder1'
      end
      item
        ParamName = '��������'
        FieldName = 'sorder2'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 900240
    Left = 14
    Top = 149
  end
  object cqticketMoneyReport: TKCWVQuery
    ID = '֧Ʊ���ѱ���ֵ����'
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
        FieldName = 'sorder1'
      end
      item
        ParamName = '��������'
        FieldName = 'sorder2'
      end
      item
        ParamName = '��������'
        FieldName = 'LVOL3'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'LVOL2'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'SALL_NAME'
      end
      item
        ParamName = '����Ա���'
        FieldName = 'sserial0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'sserial1'
      end
      item
        ParamName = '���׿���'
        FieldName = 'LVOL1'
      end
      item
        ParamName = '����'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'sorder0'
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
    RequestType = 900320
    Left = 80
    Top = 34
  end
  object cqSetOperator: TKCWVQuery
    ID = '����Ա��ѯһ'
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
    RequestType = 820302
    Left = 80
    Top = 82
  end
  object cqOperGroupManager: TKCWVQuery
    ID = '����Ա���ѯһ'
    InputBindings = <
      item
        ParamName = '����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '������'
        FieldName = 'sbankname'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820355
    Left = 80
    Top = 130
  end
  object KCTradeSubject: TKCWVQuery
    ID = '���׿�Ŀ�����'
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
        FieldName = 'sorder1'
      end
      item
        ParamName = '��������'
        FieldName = 'sorder2'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_no'
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
    RequestType = 900122
    Left = 160
    Top = 202
  end
  object KCTotSubject: TKCWVQuery
    ID = '��Ŀ���˱�'
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
        ParamName = '��ƿ�Ŀ'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
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
    RequestType = 846705
    Left = 160
    Top = 154
  end
  object KCWSubBalanceRep: TKCWVQuery
    ID = '��Ŀ����'
    InputBindings = <
      item
        ParamName = '��Ŀ��'
        FieldName = 'scust_auth'
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
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 846701
    Left = 244
    Top = 32
  end
  object KCWSystemRunStat: TKCWVQuery
    ID = 'ϵͳ�������'
    InputBindings = <
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 846702
    Left = 244
    Top = 80
  end
  object KCWBusiReport: TKCWVQuery
    ID = '�̻������'
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
        ParamName = '�̻��ʺ�'
        FieldName = 'lvol3'
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
        ParamName = '��ʾ����'
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
    RequestType = 846706
    Timeout = 5000
    Left = 248
    Top = 226
  end
  object cqCardUsedInfo_R: TKCWVQuery
    ID = '��Ƭʹ���������_R'
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
        ParamName = '�����'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
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
    RequestType = 846704
    Timeout = 5000
    Left = 248
    Top = 130
  end
  object kcTicketCashRpt_R: TKCWVQuery
    ID = 'Ʊ���ֽ𱨱�_R'
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
        ParamName = '�����'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp_no'
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
        ParamName = '��Ŀ����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'lbank_acc_type'
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
    RequestType = 846703
    Timeout = 5000
    Left = 248
    Top = 178
  end
  object KCWBusiReportPOS: TKCWVQuery
    ID = '�̻������POS'
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
        ParamName = '�̻��ʺ�'
        FieldName = 'lvol3'
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
        ParamName = '����'
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
    RequestType = 846707
    Timeout = 5000
    Left = 248
    Top = 274
  end
  object KCWBusiReportFC: TKCWVQuery
    ID = '�̻������FC'
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
        ParamName = '�̻��ʺ�'
        FieldName = 'lvol3'
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
        ParamName = '����'
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
    RequestType = 846708
    Timeout = 5000
    Left = 248
    Top = 322
  end
  object KCWBusiReportDay: TKCWVQuery
    ID = '�̻����ս����'
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
        ParamName = '�̻��ʺ�'
        FieldName = 'lvol3'
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
        ParamName = '����'
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
    RequestType = 846110
    Timeout = 5000
    Left = 320
    Top = 10
  end
  object KCWBusiPayIn: TKCWVQuery
    ID = '�̻��������ѯ'
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
    RequestType = 846720
    Timeout = 5000
    Left = 320
    Top = 58
  end
  object cqfillBusiPayIn: TKCWVProcessor
    ID = '�̻����'
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
        ParamName = '�̻���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�����'
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
    RequestType = 846721
    KCDataset = Dataset
    Left = 320
    Top = 106
  end
  object KCWPayInQuery: TKCWVQuery
    ID = '�̻�����ѯ'
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
        ParamName = '�̻���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
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
    RequestType = 846722
    Timeout = 5000
    Left = 320
    Top = 154
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 440
    Top = 16
  end
  object kcBusiGatherRep: TKCWVQuery
    ID = '�̻����ܽ����'
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
        ParamName = '�̻��ʺ�'
        FieldName = 'lvol3'
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
        ParamName = '����'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '�̻�����'
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
    RequestType = 846709
    Timeout = 5000
    Left = 320
    Top = 202
  end
  object kcSubject: TKCWVQuery
    ID = '��Ŀ���ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 846112
    Left = 19
    Top = 195
  end
  object conFB: TZConnection
    Protocol = 'firebird-2.0'
    User = 'sysdba'
    Password = 'masterkey'
    AutoCommit = False
    Left = 440
    Top = 65
  end
  object cqCardUsedInfo: TKCWVQuery
    ID = '��Ƭʹ���������'
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
        ParamName = '�����'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp_no'
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
    RequestType = 846108
    Timeout = 5000
    Left = 320
    Top = 250
  end
  object kcTicketCashReport: TKCWVQuery
    ID = 'Ʊ���ֽ𱨱�'
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
        ParamName = '�����'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = '�ʹ�'
        FieldName = 'lbank_acc_type'
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
    RequestType = 846109
    Timeout = 5000
    Left = 320
    Top = 298
  end
  object kcBusiStatFC: TKCWVQuery
    ID = '�̻����ܽ����FC'
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
        ParamName = '�̻��ʺ�'
        FieldName = 'lvol3'
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
        ParamName = '����'
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
    RequestType = 846710
    Timeout = 5000
    Left = 248
    Top = 370
  end
  object kcBusiRunStatRpt: TKCWVQuery
    ID = '�̻�Ӫҵ�����'
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
        ParamName = '����'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '�̻���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�̻�����'
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
    RequestType = 846714
    Timeout = 5000
    Left = 16
    Top = 242
  end
  object kcQBusiByKey: TKCWVQuery
    ID = '�̻���Ϣ����Q'
    InputBindings = <
      item
        ParamName = '�̻���ʶ'
        FieldName = 'lvol3'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 843335
    Left = 16
    Top = 106
  end
  object kcOperRpt: TKCWVQuery
    ID = '����Աҵ�񱨱�'
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
        ParamName = '�����'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
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
    RequestType = 846715
    Timeout = 5000
    Left = 160
    Top = 250
  end
  object kcBusiFeeRpt: TKCWVQuery
    ID = '�̻����ѱ���'
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
        ParamName = '�̻��ʺ�'
        FieldName = 'lvol3'
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
        ParamName = '��ʾ����'
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
    RequestType = 846712
    Timeout = 5000
    Left = 168
    Top = 298
  end
  object kcCardDestoryRpt: TKCWVQuery
    ID = '�����ֽ𱨱�'
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
        ParamName = '����Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
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
    RequestType = 846713
    Timeout = 5000
    Left = 160
    Top = 346
  end
  object kcSysAccount: TKCWVQuery
    ID = 'ϵͳ����'
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
        ParamName = '��������'
        FieldName = 'lsafe_level2'
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
    RequestType = 950997
    Timeout = 5000
    Left = 16
    Top = 290
  end
  object kcSysAccQuery: TKCWVQuery
    ID = 'ϵͳ���˲�ѯ'
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
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '��ѯ���'
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
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '���д���'
        FieldName = 'lvol2'
      end
      item
        ParamName = 'һ��ͨ����'
        FieldName = 'lvol3'
      end>
    RequestType = 240023
    Timeout = 5000
    Left = 16
    Top = 338
  end
  object kcOperCashTot: TKCWVQuery
    ID = '����Ա�ֽ���ܱ���'
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
        ParamName = '�����'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp_no'
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
        ParamName = '��Ŀ����'
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
    RequestType = 846716
    Timeout = 5000
    Left = 80
    Top = 178
  end
  object conSLite: TZConnection
    Protocol = 'sqlite-3'
    AutoCommit = False
    Left = 440
    Top = 113
  end
  object KCDealBankAccQ: TKCWVQuery
    ID = '���ж��˲�ѯ'
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
        ParamName = '���б��'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '����״̬'
        FieldName = 'sorder0'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sorder1'
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
    RequestType = 240031
    Timeout = 0
    Left = 384
    Top = 34
  end
  object KCDealBankAcc: TKCWVQuery
    ID = '���ж��˴���'
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
        ParamName = '�˵�����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '���б��'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '����״̬'
        FieldName = 'sorder1'
      end
      item
        ParamName = '��ע'
        FieldName = 'vsvarstr0'
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
    RequestType = 240032
    Timeout = 0
    Left = 384
    Top = 82
  end
  object KCDealBankAccDtlQ: TKCWVQuery
    ID = '���ж�����ϸ��ѯ'
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
        ParamName = '���б��'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '����״̬'
        FieldName = 'sorder0'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sorder1'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
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
    RequestType = 240033
    Timeout = 0
    Left = 384
    Top = 130
  end
  object KCDealBankAccDtl: TKCWVQuery
    ID = '���ж�����ϸ����'
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
        ParamName = '�˵�����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '���б��'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '����״̬'
        FieldName = 'sorder1'
      end
      item
        ParamName = '��ע'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '��¼��'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = 'ѧ����'
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
    RequestType = 240034
    Timeout = 0
    Left = 384
    Top = 178
  end
  object KCBalanceRpt: TKCWVQuery
    ID = '��֧ƽ���'
    InputBindings = <
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 846727
    Left = 388
    Top = 224
  end
  object KCBusiPayIn_nju: TKCWVQuery
    ID = '�̻�����ѯ_nju'
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
        ParamName = '�̻��ʺ�'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '�·�'
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
      end>
    RequestType = 846729
    Timeout = 5000
    Left = 384
    Top = 274
  end
  object kcBusiPay_nju: TKCWVProcessor
    ID = '�̻����_nju'
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
        ParamName = '�̻���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�����'
        FieldName = 'damt0'
      end
      item
        ParamName = '�·�'
        FieldName = 'lvol4'
      end
      item
        ParamName = 'ժҪ'
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
    RequestType = 846727
    KCDataset = Dataset
    Left = 384
    Top = 322
  end
  object KCBusiPayInQ_nju: TKCWVQuery
    ID = '�̻������Ϣ��ѯ_nju'
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
        ParamName = '�̻���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '������'
        FieldName = 'lvol4'
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
    RequestType = 846728
    Timeout = 5000
    Left = 384
    Top = 370
  end
end
