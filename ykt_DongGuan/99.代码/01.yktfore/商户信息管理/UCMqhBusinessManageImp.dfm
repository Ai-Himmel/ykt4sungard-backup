inherited dmBusinessManageImp: TdmBusinessManageImp
  OldCreateOrder = True
  Left = 280
  Top = 110
  Height = 527
  Width = 679
  object cqQueryBusinessByOther: TKCWVQuery
    ID = '�̻���Ϣ��������ѯ'
    InputBindings = <
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = 'lvol3'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�̻����'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�Ƿ�Ϊ��������'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '�Ƿ�ΪҶ�ڵ�'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '����������'
        FieldName = 'sname'
      end
      item
        ParamName = '���������֤��'
        FieldName = 'semail2'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��������'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '�մ���'
        FieldName = 'scust_type'
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
    Left = 40
    Top = 66
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 456
    Top = 24
  end
  object cqQueryBusinessByKey: TKCWVQuery
    ID = '�̻���Ϣ������ѯ'
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
    Left = 40
    Top = 18
  end
  object cqsetBusiFate: TKCWVQuery
    ID = '�������ʲ�ѯ'
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
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '���'
        FieldName = 'lserial0'
      end
      item
        ParamName = 'Ӫҵ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ۿ۱���'
        FieldName = 'damt1'
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
    RequestType = 843342
    Left = 120
    Top = 178
  end
  object cpsetBusiFate: TKCWVProcessor
    ID = '������������'
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
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '���'
        FieldName = 'lserial0'
      end
      item
        ParamName = 'Ӫҵ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ۿ۱���'
        FieldName = 'damt1'
      end
      item
        ParamName = '��ע'
        FieldName = 'ssectypes'
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
    RequestType = 843342
    KCDataset = Dataset
    Left = 120
    Top = 226
  end
  object cqfillBusiSaveMoney: TKCWVProcessor
    ID = '��ֵ�̻����'
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
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����'
        FieldName = 'damt0'
      end
      item
        ParamName = '��ֵ����'
        FieldName = 'lvol9'
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
        ParamName = '��������'
        FieldName = 'sorder0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'semp'
      end
      item
        ParamName = '��̨��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '�̻���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����'
        FieldName = 'damt0'
      end
      item
        ParamName = '��ɽ��'
        FieldName = 'damt1'
      end
      item
        ParamName = '�ʻ����'
        FieldName = 'damt2'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'vsvarstr0'
      end>
    RequestType = 843351
    KCDataset = Dataset
    Left = 288
    Top = 122
  end
  object cqsetFillBusiEquInfo: TKCWVQuery
    ID = '��ֵ�̻��豸��ѯ'
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
        FieldName = 'lvol0'
      end
      item
        ParamName = '�豸���'
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
    RequestType = 843357
    Left = 208
    Top = 2
  end
  object cpsetFillBusiEquInfo: TKCWVProcessor
    ID = '��ֵ�̻��豸��Ϣ��������'
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
        FieldName = 'lvol0'
      end
      item
        ParamName = '�豸���'
        FieldName = 'vsvarstr1'
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
    RequestType = 843355
    KCDataset = Dataset
    Left = 208
    Top = 50
  end
  object cpsetFillBusiEquInfoDel: TKCWVProcessor
    ID = '��ֵ�̻��豸��Ϣ����ɾ��'
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
        FieldName = 'lvol0'
      end
      item
        ParamName = '�豸���'
        FieldName = 'vsvarstr1'
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
    RequestType = 843356
    KCDataset = Dataset
    Left = 208
    Top = 98
  end
  object cqsetFillEquOperInfo: TKCWVQuery
    ID = '�豸����Ա��ѯ'
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
        ParamName = '�豸���'
        FieldName = 'saddr'
      end
      item
        ParamName = '��ֵ����Ա��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '״̬'
        FieldName = 'sstatus1'
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
    RequestType = 843361
    Left = 208
    Top = 146
  end
  object cpsetFillEquOperInfo: TKCWVProcessor
    ID = '��ֵ�豸����Ա�������'
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
        ParamName = '�豸���'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '��ֵ����Ա��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = 'ÿ������ֵ���'
        FieldName = 'damt0'
      end
      item
        ParamName = '�Ƿ�ָ���豸'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '�Ƿ��ֵ�̻�����Ա'
        FieldName = 'sstatus3'
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
    RequestType = 843358
    KCDataset = Dataset
    Left = 208
    Top = 194
  end
  object cpsetFillEquOperInfoEdit: TKCWVProcessor
    ID = '��ֵ�豸����Ա�����޸�'
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
        ParamName = '�豸���'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '��ֵ����Ա��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = 'ÿ������ֵ���'
        FieldName = 'damt0'
      end
      item
        ParamName = '�Ƿ�ָ���豸'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '�Ƿ��ֵ�̻�����Ա'
        FieldName = 'sstatus3'
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
    RequestType = 843359
    KCDataset = Dataset
    Left = 208
    Top = 240
  end
  object cpsetFillEquOperInfoDel: TKCWVProcessor
    ID = '��ֵ�豸����Ա����ɾ��'
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
        ParamName = '�豸���'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '��ֵ����Ա��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '�Ƿ�ָ���豸'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '�Ƿ��ֵ�̻�����Ա'
        FieldName = 'sstatus3'
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
    RequestType = 843360
    KCDataset = Dataset
    Left = 208
    Top = 290
  end
  object cqfillOperEquBanding: TKCWVQuery
    ID = '����Ա�豸��ѯ'
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
        ParamName = '�豸���'
        FieldName = 'saddr'
      end
      item
        ParamName = '��ֵ����Ա��'
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
    RequestType = 843364
    Left = 120
    Top = 34
  end
  object cpfillOperEquBanding: TKCWVProcessor
    ID = '��ֵ����Ա�豸��'
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
        ParamName = '��ֵ����Ա��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�豸���'
        FieldName = 'vsvarstr1'
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
    RequestType = 843362
    KCDataset = Dataset
    Left = 120
    Top = 82
  end
  object cpfillOperEquBandingDel: TKCWVProcessor
    ID = '��ֵ����Ա�豸��ɾ��'
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
        ParamName = '��ֵ����Ա��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�豸���'
        FieldName = 'vsvarstr1'
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
    RequestType = 843363
    KCDataset = Dataset
    Left = 120
    Top = 130
  end
  object cpSetBusinessInfo: TKCWVProcessor
    ID = '�̻���Ϣ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = 'lvol3'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '����'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'lvol7'
      end
      item
        ParamName = '��������'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '��ϵ��'
        FieldName = 'sname'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
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
        ParamName = '��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '�ʱ�'
        FieldName = 'spost_code'
      end
      item
        ParamName = 'Ӷ������'
        FieldName = 'smarket_code'
      end
      item
        ParamName = 'Ӷ�����'
        FieldName = 'drate0'
      end
      item
        ParamName = '�����ɱ���'
        FieldName = 'drate1'
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�����ʺ�'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = 'sbankname2'
      end
      item
        ParamName = 'ĩ���̻�'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '�Ƿ��մ���'
        FieldName = 'scust_type'
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
    RequestType = 843335
    KCDataset = Dataset
    Left = 40
    Top = 114
  end
  object cqSetBusiFee: TKCWVQuery
    ID = '�̻����Ѳ�ѯ'
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
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '�̻���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
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
    RequestType = 846205
    Left = 288
    Top = 26
  end
  object cpBusiFee: TKCWVProcessor
    ID = '�̻���������'
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
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '�̻���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '����'
        FieldName = 'drate0'
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
    RequestType = 846205
    KCDataset = Dataset
    Left = 288
    Top = 74
  end
  object cqBusiSubjectLink: TKCWVQuery
    ID = '�̻���Ŀӳ���ѯ'
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
      end
      item
        ParamName = '�̻���'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '��Ӧ��Ŀ����'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��������'
        FieldName = 'sbankname'
      end
      item
        ParamName = '�����˺�'
        FieldName = 'sbank_acc'
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
    RequestType = 850041
    Left = 288
    Top = 170
  end
  object cpBusiSubjectLink: TKCWVProcessor
    ID = '�̻���Ŀӳ��'
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
        DefaultValue = 0
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '��Ӧ��Ŀ��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��Ӧ��Ŀ����'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '��������'
        FieldName = 'sbankname'
      end
      item
        ParamName = '�����˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '��־'
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
    RequestType = 850041
    KCDataset = Dataset
    Left = 288
    Top = 218
  end
  object kcQBusiStruct: TKCWVQuery
    ID = '�̻���֯�ṹ��ѯ'
    InputBindings = <
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = 'lvol3'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�̻����'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�Ƿ�Ϊ��������'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '�Ƿ�ΪҶ�ڵ�'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '����������'
        FieldName = 'sname'
      end
      item
        ParamName = '���������֤��'
        FieldName = 'semail2'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��������'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '�մ���'
        FieldName = 'scust_type'
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
    RequestType = 850036
    Left = 40
    Top = 162
  end
  object cpSetBusiStruct: TKCWVProcessor
    ID = '�̻���֯�ṹ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = 'lvol3'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '����'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'lvol7'
      end
      item
        ParamName = '��������'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '��ϵ��'
        FieldName = 'sname'
      end
      item
        ParamName = '֤������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
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
        ParamName = '��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '�ʱ�'
        FieldName = 'spost_code'
      end
      item
        ParamName = 'Ӷ������'
        FieldName = 'smarket_code'
      end
      item
        ParamName = 'Ӷ�����'
        FieldName = 'drate0'
      end
      item
        ParamName = '�����ɱ���'
        FieldName = 'drate1'
      end
      item
        ParamName = '���д���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�����ʺ�'
        FieldName = 'sbank_acc2'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = 'sbankname2'
      end
      item
        ParamName = 'ĩ���̻�'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = '�Ƿ��մ���'
        FieldName = 'scust_type'
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
    RequestType = 850036
    KCDataset = Dataset
    Left = 40
    Top = 210
  end
  object cqSetBusiInfo: TKCWVQuery
    ID = '�̻���Ϣά����ѯ'
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
        ParamName = '�̻����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����̻���'
        FieldName = 'sname'
      end
      item
        ParamName = 'ʡ�̻����'
        FieldName = 'sname2'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '�̻���'
        FieldName = 'snote'
      end
      item
        ParamName = '�̻�Ӣ������'
        FieldName = 'snote2'
      end
      item
        ParamName = '�̻����'
        FieldName = 'semail'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '��ҵ����'
        FieldName = 'sbranch_code1'
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
    RequestType = 2004
    Left = 368
    Top = 10
  end
  object cpSetBusiInfo: TKCWVProcessor
    ID = '�̻���Ϣά��'
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
        ParamName = '�̻����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����̻���'
        FieldName = 'sname'
      end
      item
        ParamName = 'ʡ�̻����'
        FieldName = 'sname2'
      end
      item
        ParamName = '�̻���'
        FieldName = 'snote'
      end
      item
        ParamName = '�̻�Ӣ������'
        FieldName = 'snote2'
      end
      item
        ParamName = '�̻����'
        FieldName = 'semail'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '��ҵ����'
        FieldName = 'sbranch_code1'
      end
      item
        ParamName = '��ϵ��'
        FieldName = 'sbankname'
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
        FieldName = 'semail2'
      end
      item
        ParamName = '����'
        FieldName = 'sphone3'
      end
      item
        ParamName = 'Ӫҵ��ַ'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '��������'
        FieldName = 'spost_code'
      end
      item
        ParamName = '�������'
        FieldName = 'damt0'
      end
      item
        ParamName = '��������'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = '�����˺�'
        FieldName = 'spager'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = 'sbankname2'
      end
      item
        ParamName = '���к�'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�̻�״̬'
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
    RequestType = 2004
    KCDataset = Dataset
    Left = 368
    Top = 58
  end
  object cqSetBusiDev: TKCWVQuery
    ID = '�̻��豸�����ѯ'
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
        ParamName = '�̻���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '�豸�ն����к�'
        FieldName = 'scust_auth'
      end
      item
        ParamName = 'ʡ�豸�ն����к�'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sstock_code'
      end
      item
        ParamName = '״̬'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = 'ע������'
        FieldName = 'snote'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = 'ͣ������'
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
    RequestType = 2020
    Left = 368
    Top = 106
  end
  object cpSetBusiDev: TKCWVProcessor
    ID = '�̻��豸����'
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
        FieldName = 'lvol0'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�豸�ն����к�'
        FieldName = 'scust_auth'
      end
      item
        ParamName = 'ʡ�豸�ն����к�'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sstock_code'
      end
      item
        ParamName = '״̬'
        FieldName = 'scurrency_type'
      end
      item
        ParamName = 'ע������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = 'ͣ������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '���豸���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��ע'
        FieldName = 'snote2'
      end
      item
        ParamName = '������ʱ��'
        FieldName = 'scust_limit2'
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
    RequestType = 2020
    KCDataset = Dataset
    Left = 368
    Top = 154
  end
end
