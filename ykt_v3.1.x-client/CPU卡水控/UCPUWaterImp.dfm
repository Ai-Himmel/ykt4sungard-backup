inherited cmCPUWaterImp: TcmCPUWaterImp
  OldCreateOrder = True
  Left = 285
  object cpRollBack: TKCWVProcessor
    ID = 'ʧ����Ϣ_water'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�����'
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
    RequestType = 847302
    KCDataset = Dataset
    Left = 32
    Top = 112
  end
  object cpWaterTrans: TKCWVProcessor
    ID = 'ˮ��ת��_water'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˺�'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�����'
        FieldName = 'saddr'
      end
      item
        ParamName = '��������'
        FieldName = 'sstation1'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol7'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = 'СǮ�����'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = 'ת�˽��'
        FieldName = 'lvol5'
      end
      item
        ParamName = '֧������'
        FieldName = 'lcert_code'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lbank_acc_type'
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
        ParamName = '�ն���ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�ۿ���'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��д���'
        FieldName = 'lvol9'
      end
      item
        ParamName = 'СǮ�����'
        FieldName = 'lsafe_level'
      end>
    RequestType = 850010
    KCDataset = Dataset
    Left = 32
    Top = 64
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
  object cpTradeCode: TKCWVProcessor
    ID = '���ײο���_water'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˺�'
        FieldName = 'lwithdraw_flag'
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
      end
      item
        ParamName = '���ײο���'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�����'
        FieldName = 'saddr'
      end>
    RequestType = 850000
    KCDataset = Dataset
    Left = 32
    Top = 8
  end
  object cqQueryGlobeParaByKey: TKCWVQuery
    ID = 'ȫ�ֲ���������ѯ_water'
    InputBindings = <
      item
        ParamName = '������־'
        FieldName = 'lvol0'
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
        ParamName = '��Կ'
        FieldName = 'scard0'
      end>
    RequestType = 820404
    Left = 32
    Top = 162
  end
  object cpSaveFeeType: TKCWVProcessor
    ID = '����������ÿ�'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��־'
        FieldName = 'sstation0'
      end
      item
        ParamName = '���ʱ��'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'semail'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lwithdraw_flag'
        DefaultValue = 0
      end
      item
        ParamName = '�Ʒѵ�λ'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'sname'
      end
      item
        ParamName = '���ʸ���'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '����ʱ��1'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '���ʽ��1'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '���ʷ���1'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '����ʱ��2'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '���ʽ��2'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '���ʷ���2'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '����ʱ��3'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '���ʽ��3'
        FieldName = 'lvol8'
        DefaultValue = 0
      end
      item
        ParamName = '���ʷ���3'
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
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '���ʱ��'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end>
    RequestType = 846405
    KCDataset = Dataset
    Left = 32
    Top = 208
  end
  object kcFeeTypeQ: TKCWVQuery
    ID = '�������ÿ���ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��������'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '��־'
        FieldName = 'sstation0'
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
    RequestType = 846405
    Left = 32
    Top = 258
  end
  object kcFeeTypeDel: TKCWVQuery
    ID = '�������ÿ�ɾ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��������'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '��־'
        FieldName = 'sstation0'
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
    RequestType = 846405
    Left = 32
    Top = 306
  end
  object kcSmlTradeSerial: TKCWVQuery
    ID = 'СǮ����ˮ��ѯ'
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
        ParamName = '���ױ�־'
        FieldName = 'lvol5'
        DefaultValue = 0
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
    RequestType = 850012
    Left = 96
    Top = 26
  end
  object KCsmlSerialRcv: TKCWVQuery
    ID = 'СǮ����ˮ����'
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
        ParamName = '�ն���ˮ��'
        FieldName = 'lserial1'
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
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '���׽��'
        FieldName = 'damt0'
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
        ParamName = 'СǮ�����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end>
    RequestType = 847128
    Left = 96
    Top = 74
  end
end
