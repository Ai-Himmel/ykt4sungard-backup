inherited dmBusinessEquipImp: TdmBusinessEquipImp
  OldCreateOrder = True
  Left = 356
  Top = 166
  Height = 505
  Width = 547
  object cqQueryBusinessEquipByOther: TKCWVQuery
    ID = '�豸�̻���Ϣ��������ѯ'
    InputBindings = <
      item
        ParamName = '�豸��ʶ'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'ʹ�ÿ�ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = 'ʹ�ý�������'
        FieldName = 'sdate2'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'stime2'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sbankname'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�̻����'
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
    RequestType = 843371
    Left = 152
    Top = 90
  end
  object cpSetBusinessEquipInfo: TKCWVProcessor
    ID = '�豸�̻���Ϣ����'
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
        ParamName = '���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'stime2'
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
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '���'
        FieldName = 'lvol0'
      end>
    RequestType = 843371
    KCDataset = Dataset
    Left = 48
    Top = 218
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 328
    Top = 32
  end
  object cqSetBusinessEquipInfo: TKCWVQuery
    ID = '�豸�̻���Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '�豸���'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '������'
        FieldName = 'sname'
      end
      item
        ParamName = '�̻����'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'sstatus1'
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
    RequestType = 843371
    Left = 48
    Top = 74
  end
  object cqQueryEquipmentByKey3: TKCWVQuery
    ID = '�豸�ؼ��ֲ�ѯ3'
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
    RequestType = 847166
    Left = 152
    Top = 138
  end
  object cqQueryBusinessByKey2: TKCWVQuery
    ID = '�̻���Ϣ������ѯ2'
    InputBindings = <
      item
        ParamName = '�̻���ʶ'
        FieldName = 'lvol3'
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
    Left = 48
    Top = 122
  end
  object cqQueryBusinessByOther2: TKCWVQuery
    ID = '�̻���Ϣ��������ѯ2'
    InputBindings = <
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
        FieldName = 'scard1'
      end
      item
        ParamName = '�̻����'
        FieldName = 'lvol7'
      end
      item
        ParamName = '�Ƿ�Ϊ��������'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '�Ƿ�ΪҶ�ڵ�'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '����������'
        FieldName = 'sname'
      end
      item
        ParamName = '���������֤��'
        FieldName = 'sname2'
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
    Left = 48
    Top = 170
  end
  object cqQueryEquipmentByOther2: TKCWVQuery
    ID = '�豸�ǹؼ��ֲ�ѯ2'
    InputBindings = <
      item
        ParamName = '�豸����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�����豸ע���'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '�豸����ID'
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '���ʹ���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�豸״̬'
        FieldName = 'lvol4'
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
        ParamName = '������Ա����'
        FieldName = 'sname2'
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
    RequestType = 847166
    Left = 152
    Top = 45
  end
  object cqsetMealOrder: TKCWVQuery
    ID = '�ʹ���Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '�ʹ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime2'
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
    RequestType = 843340
    Left = 240
    Top = 66
  end
  object cpsetMealOrder: TKCWVProcessor
    ID = '�ʹ���Ϣ����'
    InputBindings = <
      item
        ParamName = '���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ʹ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime2'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��ע'
        FieldName = 'scusttypes'
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
    RequestType = 843340
    KCDataset = Dataset
    Left = 240
    Top = 18
  end
  object cqImpDevCustInfo: TKCWVProcessor
    ID = '�豸�̻���Ϣ����'
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
        ParamName = '�̻����'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�豸���'
        FieldName = 'Lvol5'
      end
      item
        ParamName = 'ͣ��ʱ��'
        FieldName = 'stime2'
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
    RequestType = 843370
    KCDataset = Dataset
    Left = 48
    Top = 266
  end
  object cqdevBusiImpManage: TKCWVQuery
    ID = '�豸�̻���ѯ'
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
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sname'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sbankname'
      end
      item
        ParamName = '�̻����'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sall_name'
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
    RequestType = 843370
    Left = 152
    Top = 186
  end
  object cpdevBusiImpManage: TKCWVProcessor
    ID = '�豸�̻��������'
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
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����˳���'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sbankname'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime2'
      end
      item
        ParamName = '��������'
        FieldName = 'Sdate1'
      end
      item
        ParamName = 'ͣ������'
        FieldName = 'Sdate2'
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
    RequestType = 843370
    KCDataset = Dataset
    Left = 152
    Top = 234
  end
  object cqDevBusiImpCheck: TKCWVProcessor
    ID = '�豸�̻��������'
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
    RequestType = 843370
    KCDataset = Dataset
    Left = 152
    Top = 282
  end
  object cpPatchdel: TKCWVProcessor
    ID = '�̻��豸����ɾ��'
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
    RequestType = 843370
    KCDataset = Dataset
    Left = 240
    Top = 118
  end
  object cqsetBusiCC: TKCWVQuery
    ID = '�̻��ʹ���Ϣ��ѯ'
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
        ParamName = '�̻����'
        FieldName = 'lvol0'
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
    RequestType = 843341
    Left = 240
    Top = 210
  end
  object cpsetBusiCC: TKCWVProcessor
    ID = '�̻��ʹ���Ϣ����'
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
        ParamName = '�̻����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = 'stime2'
      end
      item
        ParamName = '��ͽ���ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '�������'
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
    RequestType = 843341
    KCDataset = Dataset
    Left = 240
    Top = 162
  end
end
