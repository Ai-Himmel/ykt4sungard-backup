inherited cmCPUCardImp: TcmCPUCardImp
  OldCreateOrder = True
  object cppubCardcqcsgl: TKCWVProcessor
    ID = '���п�cqcsgl'
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
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
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
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '���з���ʶ'
        FieldName = 'sholder_ac_no'
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'stime3'
      end>
    RequestType = 846301
    KCDataset = Dataset
    Left = 22
    Top = 8
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 120
    Top = 8
  end
  object cpStuChangeCard: TKCWVProcessor
    ID = '��������ȷ��cqcsgl'
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
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '���з���ʶ'
        FieldName = 'sholder_ac_no'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end>
    RequestType = 846325
    Timeout = 2000
    KCDataset = Dataset
    Left = 22
    Top = 56
  end
  object cpRenewCard: TKCWVProcessor
    ID = '���쿨cqcsgl'
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
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '���з���ʶ'
        FieldName = 'sholder_ac_no'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'stime3'
      end>
    RequestType = 846305
    KCDataset = Dataset
    Left = 22
    Top = 104
  end
  object cpCardReRelease: TKCWVProcessor
    ID = '�����ٷ���cqcsgl'
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
      end
      item
        ParamName = 'ҵ��ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end>
    RequestType = 846310
    KCDataset = Dataset
    Left = 22
    Top = 152
  end
end
