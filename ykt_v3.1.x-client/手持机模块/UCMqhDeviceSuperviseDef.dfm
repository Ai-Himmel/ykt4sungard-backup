inherited dmDeviceSuperviseDef: TdmDeviceSuperviseDef
  OldCreateOrder = True
  Left = 217
  Top = 186
  object cpSmartTermUpSerial: TWVCommandTypeInfo
    ID = '�ֳֻ���ˮ�ɼ�'
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
        ParamName = '�ն��豸�ɣ�'
      end
      item
        ParamName = '������ˮ��'
      end
      item
        ParamName = '���׿���'
      end
      item
        ParamName = 'Ǯ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '�ۼ�ʹ�ô���'
      end
      item
        ParamName = '�������ѽ��'
      end
      item
        ParamName = '�뿨���'
      end
      item
        ParamName = '�������'
      end
      item
        ParamName = '���ױ��'
      end
      item
        ParamName = 'ͨ�Ű汾��'
      end
      item
        ParamName = '����ͨ������ԭ��'
      end
      item
        ParamName = 'CRC'
      end>
    Left = 56
    Top = 74
  end
  object cqSmartTermSetParam: TWVCommandTypeInfo
    ID = '�ֳֻ���������'
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
        ParamName = '�豸����ID'
      end>
    Left = 56
    Top = 128
  end
  object cqGetSysWorkKey: TWVCommandTypeInfo
    ID = '��ȡ������Կ'
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
        ParamDataType = kdtInteger
      end>
    Left = 56
    Top = 184
  end
  object cqSmartTermDownBlkCard: TWVCommandTypeInfo
    ID = '�´��ֳֻ��ڰ�����'
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
        ParamName = '�豸����ID'
      end>
    Left = 56
    Top = 242
  end
  object cpUpdateVersion: TWVCommandTypeInfo
    ID = '�����ֳֻ������汾'
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
        ParamName = '�豸����ID'
      end
      item
        ParamName = '�汾��'
      end>
    Left = 56
    Top = 298
  end
  object cqsendSmartTermList: TWVCommandTypeInfo
    ID = '�·��ֳֻ�������ѯ'
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
        ParamName = 'ѧ����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ͻ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�豸���'
      end
      item
        ParamName = '�ͻ���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����У��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '״̬'
      end
      item
        ParamName = '����״̬'
      end>
    Left = 232
    Top = 130
  end
  object cqacceptSmartTermList: TWVCommandTypeInfo
    ID = '�ɼ��ֳֻ���֤��ˮ'
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
        ParamName = '�ն��豸ID'
      end
      item
        ParamName = '������ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '���׿���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '���ױ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ͨ�Ű汾��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'CRC'
      end
      item
        ParamName = '����ͨ������ԭ��'
        ParamDataType = kdtInteger
      end>
    Left = 232
    Top = 66
  end
  object cqSmartTermQueryList: TWVCommandTypeInfo
    ID = '�ֳֻ����������ѯ'
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
        ParamName = 'ѧ����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ͻ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'Ժϵ'
      end
      item
        ParamName = 'רҵ'
      end
      item
        ParamName = '�༶'
      end
      item
        ParamName = '�ͻ���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����У��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ֳֻ����'
      end>
    Left = 56
    Top = 10
  end
  object WVCommandTypeInfo1: TWVCommandTypeInfo
    ID = '�ֳֻ������´�'
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
        ParamName = '�豸���'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա��'
      end
      item
        ParamName = 'ѧ����'
      end>
    Left = 232
    Top = 10
  end
  object KCWVProcessor1: TKCWVProcessor
    ID = '�ֳֻ���ˮ�ɼ�'
    InputBindings = <
      item
        ParamName = '�ն��豸�ɣ�'
        FieldName = 'sdate1'
      end
      item
        ParamName = '������ˮ��'
        FieldName = 'lvol4'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lvol6'
      end
      item
        ParamName = '��������'
        FieldName = 'spost_code'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'spost_code2'
      end
      item
        ParamName = '�ۼ�ʹ�ô���'
        FieldName = 'lvol7'
      end
      item
        ParamName = '�������ѽ��'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�뿨���'
        FieldName = 'lvol9'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol10'
      end
      item
        ParamName = '���ױ��'
        FieldName = 'lvol12'
      end
      item
        ParamName = 'ͨ�Ű汾��'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '����ͨ������ԭ��'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = 'CRC'
        FieldName = 'sbank_code2'
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
    RequestType = 930031
    KCDataset = Dataset
    Left = 128
    Top = 98
  end
  object KCWVQuery1: TKCWVQuery
    ID = '�ֳֻ���������'
    InputBindings = <
      item
        ParamName = '�豸����ID'
        FieldName = 'sbank_pwd2'
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
    RequestType = 820105
    Left = 128
    Top = 154
  end
  object KCWVQuery2: TKCWVQuery
    ID = '��ȡ������Կ'
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
      end>
    RequestType = 820404
    Left = 128
    Top = 210
  end
  object KCWVQuery3: TKCWVQuery
    ID = '�´��ֳֻ��ڰ�����'
    InputBindings = <
      item
        ParamName = '�豸����ID'
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
    RequestType = 930039
    Left = 128
    Top = 266
  end
  object KCWVProcessor2: TKCWVProcessor
    ID = '�����ֳֻ������汾'
    InputBindings = <
      item
        ParamName = '�豸����ID'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�汾��'
        FieldName = 'sserial0'
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
    RequestType = 930046
    KCDataset = Dataset
    Left = 128
    Top = 322
  end
  object KCWVQuery4: TKCWVQuery
    ID = '�·��ֳֻ�������ѯ'
    InputBindings = <
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����'
        FieldName = 'semail'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '�շ����'
        FieldName = 'Lvol4'
      end
      item
        ParamName = '�豸���'
        FieldName = 'Sname'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '����У��'
        FieldName = 'lvol5'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstatus1'
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
    RequestType = 848023
    Left = 304
    Top = 146
  end
  object kcSmartTermQueryList: TKCWVQuery
    ID = '�ֳֻ����������ѯ'
    InputBindings = <
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����'
        FieldName = 'semail'
      end
      item
        ParamName = '����'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '������'
        FieldName = 'Lvol1'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol6'
      end
      item
        ParamName = 'Ժϵ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'sstation1'
      end
      item
        ParamName = '�༶'
        FieldName = 'sorder0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '����У��'
        FieldName = 'lvol7'
      end
      item
        ParamName = '�ֳֻ����'
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
    RequestType = 848004
    Left = 128
    Top = 34
  end
  object KCWVProcessor3: TKCWVProcessor
    ID = '�ֳֻ������´�'
    InputBindings = <
      item
        ParamName = '�豸���'
        FieldName = 'sname'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'semail'
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
    RequestType = 848006
    KCDataset = Dataset
    Left = 304
    Top = 26
  end
  object KCacceptSmartTermList: TKCWVProcessor
    ID = '�ɼ��ֳֻ���֤��ˮ'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'Sdate0'
      end
      item
        ParamName = '������ˮ��'
        FieldName = 'Lvol3'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol7'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'spost_code2'
      end
      item
        ParamName = '���ױ��'
        FieldName = 'lvol11'
      end
      item
        ParamName = 'ͨ�Ű汾��'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '����ͨ������ԭ��'
        FieldName = 'lbank_acc_type2'
      end
      item
        ParamName = 'CRC'
        FieldName = 'sbank_code2'
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
    RequestType = 930101
    KCDataset = Dataset
    Left = 304
    Top = 82
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 480
    Top = 24
  end
  object ckDeleteList: TKCWVProcessor
    ID = '�ֳֻ�����ɾ��'
    InputBindings = <
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�豸���'
        FieldName = 'sname'
      end
      item
        ParamName = '����'
        FieldName = 'semail'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
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
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848008
    KCDataset = Dataset
    Left = 304
    Top = 202
  end
  object cqDeleteList: TWVCommandTypeInfo
    ID = '�ֳֻ�����ɾ��'
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
        ParamName = 'ѧ����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա��'
      end
      item
        ParamName = '�豸���'
      end>
    Left = 232
    Top = 186
  end
  object WVCommandTypeInfo2: TWVCommandTypeInfo
    ID = '�ֳֻ������ɹ�'
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
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�豸��'
      end>
    Left = 232
    Top = 242
  end
  object KCWVProcessor4: TKCWVProcessor
    ID = '�ֳֻ������ɹ�'
    InputBindings = <
      item
        ParamName = '�豸��'
        FieldName = 'sname'
      end
      item
        ParamName = '����'
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
    RequestType = 848024
    KCDataset = Dataset
    Left = 304
    Top = 258
  end
  object WVAttendSerial: TWVCommandTypeInfo
    ID = '�ֳֻ�������ˮ�ɼ�'
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
        ParamName = '������'
      end
      item
        ParamName = '����ʱ��'
      end>
    Left = 232
    Top = 298
  end
  object kcAttendSerial: TKCWVProcessor
    ID = '�ֳֻ�������ˮ�ɼ�'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����ʱ��'
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
    RequestType = 930032
    KCDataset = Dataset
    Left = 304
    Top = 306
  end
end
