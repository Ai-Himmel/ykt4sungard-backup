inherited dmSubSystemImp: TdmSubSystemImp
  OldCreateOrder = True
  Left = 468
  Top = 97
  Height = 581
  Width = 588
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 424
    Top = 8
  end
  object cqQuerySubSystemByOther: TKCWVQuery
    ID = '��ϵͳ��������ѯ'
    InputBindings = <
      item
        ParamName = '��ϵͳ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ϵͳ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��ϵͳ״̬'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ϵͳ��������'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�����ַ'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '���������ַ'
        FieldName = 'sname'
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
    RequestType = 820005
    Left = 320
    Top = 215
  end
  object cpAddSubSystemInfo: TKCWVProcessor
    ID = '��ϵͳ����.����'
    InputBindings = <
      item
        ParamName = '��ϵͳ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ϵͳ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��ϵͳ��������'
        FieldName = 'lvol3'
      end
      item
        ParamName = '����վ'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�����ַ'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '���������ַ'
        FieldName = 'sname'
      end
      item
        ParamName = '��ϵͳ�汾��'
        FieldName = 'lvol5'
      end
      item
        ParamName = '������Ա����'
        FieldName = 'sname2'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��ע'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '�˿ں�'
        FieldName = 'lvol6'
      end
      item
        ParamName = '���ܷ�ʽ'
        FieldName = 'lvol7'
      end
      item
        ParamName = '�����б�'
        FieldName = 'vsvarstr0'
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
    RequestType = 820001
    KCDataset = Dataset
    Left = 320
    Top = 26
  end
  object cpChangeSubSystemInfo: TKCWVProcessor
    ID = '��ϵͳ����.�޸�'
    InputBindings = <
      item
        ParamName = '��ϵͳ��ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ϵͳ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ϵͳ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��ϵͳ״̬'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ϵͳ��������'
        FieldName = 'lvol3'
      end
      item
        ParamName = '����վ'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�����ַ'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '���������ַ'
        FieldName = 'sname'
      end
      item
        ParamName = 'ǰ��ʱ��ͬ��ʱ��'
        FieldName = 'spager'
      end
      item
        ParamName = '��ϵͳ�汾��'
        FieldName = 'lvol5'
      end
      item
        ParamName = '������Ա����'
        FieldName = 'sname2'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��ע'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '�˿ں�'
        FieldName = 'lvol6'
      end
      item
        ParamName = '���ܷ�ʽ'
        FieldName = 'lvol7'
      end
      item
        ParamName = '�����б�'
        FieldName = 'vsvarstr0'
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
    RequestType = 820002
    KCDataset = Dataset
    Left = 320
    Top = 74
  end
  object cpDelSubSystemInfo: TKCWVProcessor
    ID = '��ϵͳ����.ɾ��'
    InputBindings = <
      item
        ParamName = '��ϵͳ��ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ϵͳ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ϵͳ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��ϵͳ״̬'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��ϵͳ��������'
        FieldName = 'lvol3'
      end
      item
        ParamName = '����վ'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�����ַ'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '���������ַ'
        FieldName = 'sname'
      end
      item
        ParamName = 'ǰ��ʱ��ͬ��ʱ��'
        FieldName = 'spager'
      end
      item
        ParamName = '��ϵͳ�汾��'
        FieldName = 'lvol5'
      end
      item
        ParamName = '������Ա����'
        FieldName = 'sname2'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��ע'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '�˿ں�'
        FieldName = 'lvol6'
      end
      item
        ParamName = '���ܷ�ʽ'
        FieldName = 'lvol7'
      end
      item
        ParamName = '�����б�'
        FieldName = 'vsvarstr0'
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
    RequestType = 820003
    KCDataset = Dataset
    Left = 320
    Top = 122
  end
  object cqQuerySubSystemByKey: TKCWVQuery
    ID = '��ϵͳ������ѯ'
    InputBindings = <
      item
        ParamName = '��ϵͳ��ʶ'
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
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 820005
    Left = 320
    Top = 168
  end
  object cqQueryEquipmentByKey: TKCWVQuery
    ID = '�豸�ؼ��ֲ�ѯ'
    InputBindings = <
      item
        ParamName = '�豸��ʶ'
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
    RequestType = 820105
    Left = 224
    Top = 197
  end
  object cqQueryEquipmentByOther: TKCWVQuery
    ID = '�豸�ǹؼ��ֲ�ѯ'
    InputBindings = <
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�����豸ע���'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '�豸����ID'
        FieldName = 'sphone3'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '���ʹ���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = 'sphone2'
      end
      item
        ParamName = '�豸״̬'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '�豸��������'
        FieldName = 'lserial1'
        DefaultValue = 0
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = 'sserial0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�������κ�'
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
    RequestType = 820105
    Left = 224
    Top = 149
  end
  object cpAddEquipmentInfo: TKCWVProcessor
    ID = '�豸��Ϣ����.����'
    InputBindings = <
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '���ʹ���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�豸��;'
        FieldName = 'damt5'
      end
      item
        ParamName = '�ϼ��豸�����'
        FieldName = 'damt6'
      end
      item
        ParamName = '�豸�����'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�豸��������'
        FieldName = 'lserial1'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = 'ͨ�ŵ�ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = 'damt4'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�������˿�����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ͨѶ���'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'ͨѶ�˿�'
        FieldName = 'sbank_code2'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820101
    KCDataset = Dataset
    Left = 224
    Top = 5
  end
  object cpChangeEquipmenInfo: TKCWVProcessor
    ID = '�豸��Ϣ����.�޸�'
    InputBindings = <
      item
        ParamName = '�豸��ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '���ʹ���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�豸��;'
        FieldName = 'damt5'
      end
      item
        ParamName = '�ϼ��豸�����'
        FieldName = 'damt6'
      end
      item
        ParamName = '�豸�����'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�豸��������'
        FieldName = 'lserial1'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = 'ͨ�ŵ�ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = 'damt4'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�������˿�����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ͨѶ���'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'ͨѶ�˿�'
        FieldName = 'sbank_code2'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820102
    KCDataset = Dataset
    Left = 224
    Top = 53
  end
  object cpDelEquipmentInfo: TKCWVProcessor
    ID = '�豸��Ϣ����.ɾ��'
    InputBindings = <
      item
        ParamName = '�豸��ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '���ʹ���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�豸��;'
        FieldName = 'damt5'
      end
      item
        ParamName = '�ϼ��豸�����'
        FieldName = 'damt6'
      end
      item
        ParamName = '�豸�����'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�豸��������'
        FieldName = 'lserial1'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = 'ͨ�ŵ�ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = 'damt4'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�������˿�����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ͨѶ�˿�'
        FieldName = 'sbank_code2'
      end
      item
        ParamName = 'ͨѶ���'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
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
    RequestType = 820103
    KCDataset = Dataset
    Left = 224
    Top = 101
  end
  object cpDownMagFeePortion: TKCWVProcessor
    ID = '�´����ѱ���'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sdate0'
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
    RequestType = 950041
    KCDataset = Dataset
    Left = 40
    Top = 104
  end
  object cpDownConsumeLimit: TKCWVProcessor
    ID = '�´���������޶�'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������޶�'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
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
        ParamName = '������Ϣ'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930010
    KCDataset = Dataset
    Left = 40
    Top = 152
  end
  object cpDownEquipClock: TKCWVProcessor
    ID = '�´��豸ʱ��'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
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
        ParamName = '�´�ʱ��'
        FieldName = 'sserial0'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930001
    KCDataset = Dataset
    Left = 40
    Top = 296
  end
  object cpUpEquipClock: TKCWVProcessor
    ID = '�ϴ��豸ʱ��'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '�ϴ�ʱ��'
        FieldName = 'sserial0'
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
        ParamName = '������Ϣ'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930002
    KCDataset = Dataset
    Left = 40
    Top = 344
  end
  object cqQueryEquipmentCanEdit: TKCWVQuery
    ID = '�ɱ༭�豸��ѯ'
    InputBindings = <
      item
        ParamName = '���ʹ���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�豸��������'
        FieldName = 'lserial1'
      end
      item
        ParamName = '�豸״̬'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸����ID'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = 'sphone2'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = 'sserial0'
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
    Left = 224
    Top = 245
  end
  object cpCollectConsumeSer: TKCWVProcessor
    ID = '�ɼ���ʷ������ˮ'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '������ʼ��ˮ��'
        FieldName = 'lvol5'
      end
      item
        ParamName = '����������ˮ��'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
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
    RequestType = 930016
    KCDataset = Dataset
    Left = 40
    Top = 248
  end
  object cpCollectAddMoneySer: TKCWVProcessor
    ID = '�ɼ��ֽ��ֵ��ˮ'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '������ʼ��ˮ��'
        FieldName = 'lvol5'
      end
      item
        ParamName = '����������ˮ��'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
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
    RequestType = 930018
    KCDataset = Dataset
    Left = 40
    Top = 200
  end
  object cpEquipCompellOut: TKCWVProcessor
    ID = 'ǿ��ǰ�û����豸ǩ��'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
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
        ParamName = '������Ϣ'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930060
    KCDataset = Dataset
    Left = 40
    Top = 392
  end
  object cpSetHisSumMoney: TKCWVProcessor
    ID = '���������ۼ��޶�'
    InputBindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�ۼ������޶�'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
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
        ParamName = '������Ϣ'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 930061
    KCDataset = Dataset
    Left = 40
    Top = 8
  end
  object cqQueryEquipmentTree: TKCWVQuery
    ID = '�ɱ༭�豸��ѯ2'
    InputBindings = <
      item
        ParamName = '���ʹ���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�豸��������'
        FieldName = 'lserial1'
      end
      item
        ParamName = '�豸״̬'
        FieldName = 'lvol4'
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
    RequestType = 820108
    Left = 224
    Top = 293
  end
  object cqsubSendListQuery: TKCWVQuery
    ID = '��ϵͳ�����������'
    InputBindings = <
      item
        ParamName = '��ϵͳ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'sname'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol2'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '״̬'
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
    RequestType = 940005
    Left = 320
    Top = 258
  end
  object cqsetEquipPara2: TKCWVQuery
    ID = '�豸��ѯ'
    InputBindings = <
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�ϼ��豸'
        FieldName = 'sphone2'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '��ϵͳ'
        FieldName = 'lserial0'
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
    Top = 170
  end
  object cpCustomerKindByKey: TKCWVQuery
    ID = 'querycustomerkind'
    InputBindings = <
      item
        ParamName = 'lcert_code'
        FieldName = 'lcert_code'
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
    RequestType = 820502
    Left = 128
    Top = 26
  end
  object cpEquGroup: TKCWVProcessor
    ID = 'EquGroup'
    InputBindings = <
      item
        ParamName = '����Ȩ��'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
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
        ParamName = '������Ϣ'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 950040
    KCDataset = Dataset
    Left = 40
    Top = 440
  end
  object cqsetCommCfParam: TKCWVQuery
    ID = 'ͨ��ǰ�ò�����ѯ'
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
        ParamName = '��־'
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
    RequestType = 847232
    Left = 128
    Top = 74
  end
  object cpsetCommCfParam: TKCWVProcessor
    ID = 'ͨ��ǰ�ò�������'
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
        ParamName = 'ǰ�ñ��'
        FieldName = 'lcert_code'
      end
      item
        ParamName = 'ǰ�û���'
        FieldName = 'semail'
      end
      item
        ParamName = '����ʱ����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����ӷ�ֵ'
        FieldName = 'lvol1'
      end
      item
        ParamName = '����Ӧ���ܺ�'
        FieldName = 'lvol2'
      end
      item
        ParamName = 'ָ����ȶ��к�'
        FieldName = 'lvol3'
      end
      item
        ParamName = 'ָ��Ӧ���ܺ�'
        FieldName = 'lvol9'
      end
      item
        ParamName = 'ָ��ִ�г�ʱʱ��'
        FieldName = 'lvol4'
      end
      item
        ParamName = 'ָ���ȡʱ����'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�豸�����־'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�豸���������ܺ�'
        FieldName = 'lvol6'
      end
      item
        ParamName = '�豸����ģʽ'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '��ˮ�ɼ�Ƶ��'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'ָ���������'
        FieldName = 'lvol7'
      end
      item
        ParamName = '������Կ'
        FieldName = 'sname2'
      end
      item
        ParamName = '��־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�ڵ��'
        FieldName = 'lvol10'
      end
      item
        ParamName = 'ƽ̨IP'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�˿�'
        FieldName = 'lvol12'
      end
      item
        ParamName = '���ܺ�'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '��ѯ���ʱ��'
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
    RequestType = 847232
    KCDataset = Dataset
    Left = 128
    Top = 122
  end
  object KCPGateOpen: TKCWVProcessor
    ID = '�Ž���������'
    InputBindings = <
      item
        ParamName = '�豸���'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�ն��豸ID'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��־'
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
    RequestType = 950004
    KCDataset = Dataset
    Left = 40
    Top = 56
  end
  object cqDevInfoImp: TKCWVProcessor
    ID = '�豸��Ϣ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�Ƿ������'
        FieldName = 'scust_type'
      end
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸����'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sserial1'
      end
      item
        ParamName = '�豸��;'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sphone3'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '�ϼ��豸'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = '֧�ֿ�Ŀ�շ�'
        FieldName = 'Lvol6'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = 'saddr'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = 'Lvol8'
      end
      item
        ParamName = '�豸����'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'IP��ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ͨѶ���'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�������˿���'
        FieldName = 'lvol2'
      end
      item
        ParamName = 'ͨѶ�˿�'
        FieldName = 'lvol3'
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
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end>
    RequestType = 820110
    KCDataset = Dataset
    Left = 128
    Top = 221
  end
  object cqdevImpManage: TKCWVQuery
    ID = '�豸��Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�豸����'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sserial1'
      end
      item
        ParamName = '�豸��;'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = 'saddr'
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
    RequestType = 820110
    Left = 128
    Top = 266
  end
  object cpdevImpManage: TKCWVProcessor
    ID = '�豸�������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '����˳���'
        FieldName = 'lvol4'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�豸����'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sserial1'
      end
      item
        ParamName = '�豸��;'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�ϼ��豸���'
        FieldName = 'Lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = 'saddr'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�������˿�����'
        FieldName = 'Lvol2'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = 'Lvol6'
      end
      item
        ParamName = '�豸����'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'IP��ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ͨѶ��ʽ'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'ͨѶ�˿ں�'
        FieldName = 'lvol3'
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
    RequestType = 820110
    KCDataset = Dataset
    Left = 128
    Top = 314
  end
  object cqDevBusiImpCheck: TKCWVProcessor
    ID = '�豸�������'
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
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����˳���'
        FieldName = 'lvol4'
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
    RequestType = 820110
    KCDataset = Dataset
    Left = 128
    Top = 362
  end
  object cpPatchdel: TKCWVProcessor
    ID = '�豸����ɾ��'
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
    RequestType = 820110
    KCDataset = Dataset
    Left = 224
    Top = 346
  end
  object cpFeeType: TKCWVProcessor
    ID = '�´���������'
    InputBindings = <
      item
        ParamName = '�豸���'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '��־'
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
    RequestType = 950044
    KCDataset = Dataset
    Left = 128
    Top = 408
  end
  object KCChange: TKCWVProcessor
    ID = '�����豸'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���豸'
        FieldName = 'lvol3'
      end
      item
        ParamName = '���豸'
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
      end>
    RequestType = 950107
    KCDataset = Dataset
    Left = 320
    Top = 306
  end
end
