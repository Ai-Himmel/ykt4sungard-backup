inherited dmCardImp: TdmCardImp
  OldCreateOrder = True
  Left = 319
  Top = 94
  Height = 621
  Width = 557
  object cpChangeCardPwd: TKCWVProcessor
    ID = '�޸Ŀ�����'
    InputBindings = <
      item
        ParamName = '����ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'scust_no'
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
    RequestType = 847111
    KCDataset = Dataset
    Left = 118
    Top = 24
  end
  object cqTradeBusiQuery: TKCWVQuery
    ID = 'δ���˽����̻���ѯ'
    InputBindings = <
      item
        ParamName = '�ն˻��豸����ID'
        FieldName = 'sbank_pwd2'
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
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 847182
    Left = 118
    Top = 120
  end
  object cqManualTrade: TKCWVProcessor
    ID = '������ˮ�ֹ�����'
    InputBindings = <
      item
        ParamName = '��������'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ն˻�����ID'
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '�ն˻���ˮ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�̻�ID'
        FieldName = 'lvol12'
      end
      item
        ParamName = '���ϵͳ��ʶ'
        FieldName = 'lvol11'
      end
      item
        ParamName = '����Ա'
        FieldName = 'sdate1'
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
    RequestType = 847181
    KCDataset = Dataset
    Left = 118
    Top = 74
  end
  object cpLossCard: TKCWVProcessor
    ID = '��ʧ���'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������־'
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
      end
      item
        ParamName = '���汾��'
        FieldName = 'sserial0'
      end>
    RequestType = 846307
    KCDataset = Dataset
    Left = 38
    Top = 144
  end
  object cpCardDestory: TKCWVProcessor
    ID = 'һ��ͨ����'
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
        ParamName = '�Ƿ��п�'
        FieldName = 'lvol4'
      end
      item
        ParamName = '��������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�����'
        FieldName = 'Lvol8'
      end
      item
        ParamName = '���״���'
        FieldName = 'Lvol6'
      end
      item
        ParamName = '�Ƿ���Ѻ��'
        FieldName = 'Lvol5'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'lvol10'
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
        ParamName = '�˿���'
        FieldName = 'damt0'
      end>
    RequestType = 846303
    KCDataset = Dataset
    Left = 342
    Top = 96
  end
  object KCWPatchAccQuery: TKCWVQuery
    ID = '���ʽ��ײ�ѯ'
    InputBindings = <
      item
        ParamName = '���׿���'
        FieldName = 'lvol1'
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
        ParamName = '�����˺�'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '״̬'
        FieldName = 'lvol2'
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
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 847185
    Left = 40
    Top = 2
  end
  object cqPatchAcc: TKCWVProcessor
    ID = '���ʽ���'
    InputBindings = <
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�뿨ֵ'
        FieldName = 'damt0'
      end
      item
        ParamName = '����վ��'
        FieldName = 'lvol6'
      end
      item
        ParamName = '��ǰ�����״���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '����Ա'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�������'
        FieldName = 'damt1'
      end
      item
        ParamName = '����Ա'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = '��ˮ��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = 'ԭ��ˮ��'
        FieldName = 'lserial0'
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
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'damt4'
      end
      item
        ParamName = '����'
        FieldName = 'damt3'
      end
      item
        ParamName = '��ֵ���'
        FieldName = 'damt2'
      end>
    RequestType = 240157
    KCDataset = Dataset
    Left = 40
    Top = 50
  end
  object cpinAccountByMan: TKCWVProcessor
    ID = '����ֹ�����'
    InputBindings = <
      item
        ParamName = '�跽�˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�����˺�'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '�������'
        FieldName = 'damt0'
      end
      item
        ParamName = '����վ��'
        FieldName = 'lvol6'
      end
      item
        ParamName = '���˲���Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = '���˲���Ա����'
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
    RequestType = 847127
    KCDataset = Dataset
    Left = 190
  end
  object KCWAccountByMan: TKCWVQuery
    ID = '����ֹ����ʲ�ѯ'
    InputBindings = <
      item
        ParamName = '�˺�'
        FieldName = 'sbank_acc'
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
      end
      item
        ParamName = '����'
        FieldName = 'sbankname'
      end>
    RequestType = 847150
    Left = 190
    Top = 50
  end
  object KCWManualTradeQ: TKCWVQuery
    ID = 'δ������ˮ��ѯ'
    InputBindings = <
      item
        ParamName = '��������'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '������ʼʱ��'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '������ֹʱ��'
        FieldName = 'sbank_code2'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ն˻�����ID'
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '�ն˻���ˮ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '״̬'
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
    RequestType = 847180
    Left = 190
    Top = 146
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 32
    Top = 336
  end
  object cqPubAuthCard1: TKCWVProcessor
    ID = '������Ȩ��'
    InputBindings = <
      item
        ParamName = '����Ա��'
        FieldName = 'sname2'
      end
      item
        ParamName = '������'
        FieldName = 'sname'
      end
      item
        ParamName = '��Ȩ��Ȩ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ҵ�����Ա'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '��Ч��'
        FieldName = 'sdate2'
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
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '��Ч��'
        FieldName = 'sdate2'
      end
      item
        ParamName = '��Ȩ��Ȩ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '������Կ'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_limit2'
      end>
    RequestType = 847226
    KCDataset = Dataset
    Left = 278
    Top = 24
  end
  object cqauthCardOper: TKCWVQuery
    ID = '��Ȩ������'
    InputBindings = <
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '������'
        FieldName = 'sname'
      end
      item
        ParamName = '״̬'
        FieldName = 'lvol1'
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
    RequestType = 847231
    Left = 278
    Top = 66
  end
  object cqmodifyAuthCard: TKCWVQuery
    ID = '�޸���Ȩ������'
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
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������Ч��'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��Ȩ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ҵ�����Ա��'
        FieldName = 'scust_limit'
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
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������Ч��'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��Ȩ��'
        FieldName = 'lvol1'
      end>
    RequestType = 847228
    Left = 278
    Top = 114
  end
  object cqReturnCardAuth: TKCWVProcessor
    ID = '��Ȩ������'
    InputBindings = <
      item
        ParamName = '������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�޿�����'
        FieldName = 'lvol1'
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
    RequestType = 847227
    KCDataset = Dataset
    Left = 278
    Top = 160
  end
  object cqLoseAuthCard: TKCWVProcessor
    ID = '��Ȩ����ʧ'
    InputBindings = <
      item
        ParamName = '����Ա����'
        FieldName = 'sname'
      end
      item
        ParamName = 'ҵ�����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
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
    RequestType = 847229
    KCDataset = Dataset
    Left = 278
    Top = 208
  end
  object cqRLoseAuthCard: TKCWVProcessor
    ID = '��Ȩ�����'
    InputBindings = <
      item
        ParamName = '����Ա����'
        FieldName = 'semp_pwd'
      end
      item
        ParamName = 'ҵ�����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
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
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�������汾'
        FieldName = 'sserial0'
      end>
    RequestType = 847230
    KCDataset = Dataset
    Left = 278
    Top = 256
  end
  object KCWCardCustInfoQuery: TKCWVQuery
    ID = '�����ͻ���Ϣ��ѯ'
    InputBindings = <
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
        ParamName = 'רҵ'
        FieldName = 'scert_no2'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = 'ע������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�༶'
        FieldName = 'scard1'
      end
      item
        ParamName = '�������'
        FieldName = 'lsafe_level'
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
    RequestType = 846600
    Left = 278
    Top = 304
  end
  object cqFeeQuery: TKCWVProcessor
    ID = '�����շѲ�ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���ܺ�'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�Ƿ񲻼�����'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
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
        ParamName = '�շ���Ϣ'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '�ܷ���'
        FieldName = 'damt0'
      end
      item
        ParamName = '����Ч��'
        FieldName = 'sdate0'
      end>
    RequestType = 846601
    KCDataset = Dataset
    Left = 278
    Top = 352
  end
  object cqReleaseCard: TKCWVProcessor
    ID = '���п�'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = 'lvol9'
      end
      item
        ParamName = '�շѽ��'
        FieldName = 'damt0'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�Ƿ񲻼�����'
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
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
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
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol8'
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
        ParamName = '����Ա'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '�����޶�'
        FieldName = 'lvol11'
      end
      item
        ParamName = '���޶�'
        FieldName = 'lvol12'
      end>
    RequestType = 846301
    KCDataset = Dataset
    Left = 278
    Top = 400
  end
  object cqRelCardOk: TKCWVProcessor
    ID = '����ȷ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��������Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '�ն˱��'
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
    RequestType = 846302
    KCDataset = Dataset
    Left = 278
    Top = 448
  end
  object cqRenewCard: TKCWVProcessor
    ID = '���쿨'
    InputBindings = <
      item
        ParamName = '����Ա'
        FieldName = 'semp'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = 'Lvol9'
      end
      item
        ParamName = '�շѽ��'
        FieldName = 'damt0'
      end
      item
        ParamName = '�տ��ɱ���'
        FieldName = 'lvol4'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'scust_auth2'
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
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
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
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol8'
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
        ParamName = '����Ա'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '�����޶�'
        FieldName = 'lvol11'
      end
      item
        ParamName = '���޶�'
        FieldName = 'lvol12'
      end>
    RequestType = 846305
    KCDataset = Dataset
    Left = 342
  end
  object KCWCardInfoQuery: TKCWVQuery
    ID = '�ѿ����ͻ���Ϣ��ѯ'
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
    Left = 342
    Top = 48
  end
  object cqFreezeCard: TKCWVProcessor
    ID = '����ⶳ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus1'
      end
      item
        ParamName = 'ժҪ'
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
      end
      item
        ParamName = '���汾��'
        FieldName = 'sserial0'
      end>
    RequestType = 846308
    KCDataset = Dataset
    Left = 38
    Top = 192
  end
  object cqCardReRelease: TKCWVProcessor
    ID = '�����ٷ���'
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
        ParamName = '�����'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
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
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�շ����'
        FieldName = 'Lvol5'
      end
      item
        ParamName = '������'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '��Ч��'
        FieldName = 'sdate0'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�����޶�'
        FieldName = 'lvol11'
      end
      item
        ParamName = '���޶�'
        FieldName = 'lvol12'
      end>
    RequestType = 846310
    KCDataset = Dataset
    Left = 342
    Top = 144
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
        ParamName = '���״���'
        FieldName = 'lvol6'
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
      end>
    RequestType = 846312
    KCDataset = Dataset
    Left = 38
    Top = 96
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
      end>
    RequestType = 846314
    KCDataset = Dataset
    Left = 118
    Top = 168
  end
  object cqcashOperCancel: TKCWVProcessor
    ID = '��ֵ֧ȡ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
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
    RequestType = 846315
    KCDataset = Dataset
    Left = 342
    Top = 192
  end
  object KCWAccountQuery: TKCWVQuery
    ID = '�ʻ���Ϣ��ѯ'
    InputBindings = <
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
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    Left = 342
    Top = 240
  end
  object cqcardTradeQuery: TKCWVQuery
    ID = '��������ˮ��ѯ'
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
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��ֹ����'
        FieldName = 'sdate2'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '�ն���ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ѧ/����'
        FieldName = 'spager'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
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
        ParamName = '��ˮ״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '��ѯ����'
        FieldName = 'sstatus4'
      end
      item
        ParamName = '���׿�ʼ����'
        FieldName = 'stime1'
      end
      item
        ParamName = '���׽�������'
        FieldName = 'stime2'
      end
      item
        ParamName = '����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '����״̬'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'sorder1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'sorder2'
      end
      item
        ParamName = '�ⲿ����'
        FieldName = 'lsafe_level'
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
    RequestType = 846605
    Left = 40
    Top = 242
  end
  object cqTradeReserse: TKCWVProcessor
    ID = '���׳���'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus3'
      end
      item
        ParamName = '�Ƿ���Ȩ'
        FieldName = 'Sstatus2'
      end
      item
        ParamName = '����Ա����'
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
    RequestType = 846315
    KCDataset = Dataset
    Left = 38
    Top = 288
  end
  object cqReverseOpenCard: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '��֤����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�Ƿ���Ȩ'
        FieldName = 'sstatus2'
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
        ParamName = '������'
        FieldName = 'sstation0'
      end>
    RequestType = 846302
    KCDataset = Dataset
    Left = 342
    Top = 288
  end
  object cqaccountTradeQuery: TKCWVQuery
    ID = '�ʻ�������ϸ��ѯ'
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
        ParamName = '���˿�ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '���˽�ֹ����'
        FieldName = 'sdate2'
      end
      item
        ParamName = '���׿�ʼ����'
        FieldName = 'stime1'
      end
      item
        ParamName = '���׽�ֹ����'
        FieldName = 'stime2'
      end
      item
        ParamName = '��Ŀ��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '�ʻ���'
        FieldName = 'sbankname'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '�ն���ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'scard1'
      end
      item
        ParamName = '�̻���'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'Ǯ����'
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
    RequestType = 846606
    Left = 120
    Top = 210
  end
  object cqRevSaveMoney: TKCWVProcessor
    ID = '��ֵ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_limit'
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
        ParamName = '�뿨ֵ'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '�����״���'
        FieldName = 'lvol6'
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
        ParamName = '����ֵ'
        FieldName = 'lvol8'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end>
    RequestType = 846316
    KCDataset = Dataset
    Left = 342
    Top = 336
  end
  object cqRevConsume: TKCWVProcessor
    ID = '���ѳ���'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_limit'
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
        ParamName = '�뿨ֵ'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '�����״���'
        FieldName = 'lvol6'
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
        ParamName = '����ֵ'
        FieldName = 'lvol8'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end>
    RequestType = 846317
    KCDataset = Dataset
    Left = 342
    Top = 384
  end
  object cpbadCardManage: TKCWVProcessor
    ID = '�����Ǽ�'
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
        ParamName = '��ԭ��'
        FieldName = 'sstatus1'
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
    RequestType = 846309
    KCDataset = Dataset
    Left = 120
    Top = 258
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
      end>
    RequestType = 846320
    KCDataset = Dataset
    Left = 190
    Top = 96
  end
  object cpStuChangeCard: TKCWVProcessor
    ID = '��������ȷ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = 'ԭ������'
        FieldName = 'scust_no'
      end
      item
        ParamName = 'ԭ����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = 'ԭ�����'
        FieldName = 'Lvol7'
      end
      item
        ParamName = 'ԭ�����״���'
        FieldName = 'Lvol6'
      end
      item
        ParamName = '�¿�������'
        FieldName = 'Scust_no2'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
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
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'lvol4'
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
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
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
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
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
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
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
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '����ֵ'
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
        ParamName = '�����޶�'
        FieldName = 'lvol11'
      end
      item
        ParamName = '���޶�'
        FieldName = 'lvol12'
      end>
    RequestType = 846321
    Timeout = 2000
    KCDataset = Dataset
    Left = 190
    Top = 192
  end
  object cqcardLibNotBalance: TKCWVQuery
    ID = '���ⲻƽ�����ѯ'
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
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '���ⲻƽ����'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '��ƽ��ֵ'
        FieldName = 'lvol10'
      end
      item
        ParamName = 'ͳ������'
        FieldName = 'sdate0'
      end
      item
        ParamName = 'ƽ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = 'ƽ�˲���Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = 'ƽ��״̬'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
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
    RequestType = 846115
    Left = 120
    Top = 306
  end
  object cpCardLibBal: TKCWVProcessor
    ID = '���ⲻƽ����'
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
        ParamName = 'ͳ������'
        FieldName = 'sdate0'
      end
      item
        ParamName = 'ƽ�˷�ʽ'
        FieldName = 'Sstatus2'
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
    RequestType = 846116
    KCDataset = Dataset
    Left = 120
    Top = 354
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
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�������'
        FieldName = 'damt0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
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
      end>
    RequestType = 846322
    KCDataset = Dataset
    Left = 38
    Top = 384
  end
end
