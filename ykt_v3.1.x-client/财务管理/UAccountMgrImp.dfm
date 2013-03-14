inherited cmAccountMgrImp: TcmAccountMgrImp
  OldCreateOrder = True
  Left = 285
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
  object conFB: TZConnection
    Protocol = 'sqlite-3'
    AutoCommit = False
    Left = 368
    Top = 65
  end
  object KCWAccountByMan: TKCWVQuery
    ID = 'ƾ֤��Ŀ��ѯ'
    InputBindings = <
      item
        ParamName = '�˺�'
        FieldName = 'sbank_acc'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
        DefaultValue = ''
      end
      item
        ParamName = '��־'
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
        ParamName = '����'
        FieldName = 'sbankname'
      end>
    RequestType = 847150
    Left = 22
    Top = 10
  end
  object kcVoucherAdd: TKCWVQuery
    ID = 'ƾ֤��Ŀ¼��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
        DefaultValue = ''
      end
      item
        ParamName = '��־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��¼������'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'lsafe_level'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '������'
        FieldName = 'lbank_acc_type'
        DefaultValue = 0
      end
      item
        ParamName = '�к�1'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = 'ժҪ1'
        FieldName = 'snote'
      end
      item
        ParamName = '��Ŀ����1'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�跽���1'
        FieldName = 'damt1'
        DefaultValue = 0
      end
      item
        ParamName = '�������1'
        FieldName = 'damt2'
        DefaultValue = 0
      end
      item
        ParamName = '�к�2'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = 'ժҪ2'
        FieldName = 'snote2'
      end
      item
        ParamName = '��Ŀ����2'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '�跽���2'
        FieldName = 'damt3'
        DefaultValue = 0
      end
      item
        ParamName = '�������2'
        FieldName = 'damt4'
        DefaultValue = 0
      end
      item
        ParamName = '�к�3'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = 'ժҪ3'
        FieldName = 'sbankname'
      end
      item
        ParamName = '��Ŀ����3'
        FieldName = 'sphone'
      end
      item
        ParamName = '�跽���3'
        FieldName = 'damt5'
        DefaultValue = 0
      end
      item
        ParamName = '�������3'
        FieldName = 'damt6'
        DefaultValue = 0
      end
      item
        ParamName = '�к�4'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = 'ժҪ4'
        FieldName = 'sbankname2'
      end
      item
        ParamName = '��Ŀ����4'
        FieldName = 'sphone2'
      end
      item
        ParamName = '�跽���4'
        FieldName = 'damt7'
        DefaultValue = 0
      end
      item
        ParamName = '�������4'
        FieldName = 'damt8'
        DefaultValue = 0
      end
      item
        ParamName = '��'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '��'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '�������'
        FieldName = 'sname2'
      end
      item
        ParamName = '���㷽ʽ'
        FieldName = 'lvol9'
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
    RequestType = 850050
    Left = 22
    Top = 58
  end
  object cqVoucherMgr: TKCWVQuery
    ID = 'ƾ֤����.��ѯ'
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
        ParamName = '����ڼ�(��)'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'sorder0'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'lsafe_level'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '�Ƿ��ֹ���ƾ֤'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '����״̬'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '��ѯ����'
        FieldName = 'lvol9'
        DefaultValue = 0
      end
      item
        ParamName = 'ID'
        FieldName = 'lserial1'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤��������'
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
    RequestType = 850050
    Left = 24
    Top = 106
  end
  object kcVOper: TKCWVQuery
    ID = 'ƾ֤����'
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
        ParamName = '����ڼ�(��)'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'lsafe_level'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = 'ƾ֤ID'
        FieldName = 'lserial1'
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
    RequestType = 850050
    Left = 24
    Top = 154
  end
  object kcOperPermissionQ: TKCWVQuery
    ID = '����Ȩ�޹����ѯ'
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
        ParamName = '����Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = 'Ȩ�����'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '����Ա����'
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
    RequestType = 850040
    Left = 24
    Top = 202
  end
  object kcOperPermission: TKCWVQuery
    ID = '����Ȩ�޹���'
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
        ParamName = '����Ա��'
        FieldName = 'semp_no'
      end
      item
        ParamName = 'Ȩ�����'
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
      end>
    RequestType = 850040
    Left = 24
    Top = 250
  end
  object kcAccountRptQ: TKCWVQuery
    ID = '����˲���ѯ'
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
        ParamName = '�˲�����'
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
    RequestType = 850060
    Left = 24
    Top = 298
  end
  object kc850061: TKCWVQuery
    ID = '�ܷ����˲�ѯ'
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
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����δ����'
        FieldName = 'lcert_code'
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
    RequestType = 850061
    Left = 96
    Top = 34
  end
  object kc850062: TKCWVQuery
    ID = '�ռ��˲�ѯ'
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
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����δ����'
        FieldName = 'lcert_code'
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
    RequestType = 850062
    Left = 96
    Top = 82
  end
  object kc850063: TKCWVQuery
    ID = '��ϸ�����ʲ�ѯ'
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
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����δ����'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '��ѯ��ʽ'
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
    RequestType = 850063
    Left = 96
    Top = 130
  end
  object kc850065: TKCWVQuery
    ID = '��Ŀ���ܱ���'
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
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'lvol12'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '����δ����'
        FieldName = 'lcert_code'
        DefaultValue = 0
      end
      item
        ParamName = '��ѯ��ʽ'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '��ʾδ����'
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
    RequestType = 850065
    Left = 96
    Top = 178
  end
  object kc850070: TKCWVQuery
    ID = '������ܱ���'
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
        ParamName = '��'
        FieldName = 'lvol10'
        DefaultValue = 0
      end
      item
        ParamName = '��'
        FieldName = 'lvol11'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '����'
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
      end>
    RequestType = 850070
    Left = 96
    Top = 226
  end
  object kc850071: TKCWVQuery
    ID = '���ս�ת'
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
    RequestType = 850071
    Left = 96
    Top = 274
  end
  object kc850072: TKCWVQuery
    ID = '��ĩ��ת'
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
    RequestType = 850072
    Left = 96
    Top = 322
  end
  object kcQSubject: TKCWVQuery
    ID = '��Ŀ��Ϣ��ѯ'
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
        ParamName = '���к�'
        FieldName = 'Lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '������'
        FieldName = 'sname'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = 'Lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ���'
        FieldName = 'Lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ����'
        FieldName = 'Lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'Lvol4'
        DefaultValue = 0
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
    RequestType = 850035
    Left = 152
    Top = 10
  end
  object cpSetSubject: TKCWVProcessor
    ID = '��Ŀ��Ϣ����'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�ϼ���Ŀ'
        FieldName = 'lserial0'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = 'sallname'
      end
      item
        ParamName = '������'
        FieldName = 'sname'
      end
      item
        ParamName = '��Ŀ���'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '��Ŀ����'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '�Ƿ�ĩ��'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '�ֽ��Ŀ'
        FieldName = 'lvol6'
        DefaultValue = 0
      end
      item
        ParamName = '���п�Ŀ'
        FieldName = 'lvol7'
        DefaultValue = 0
      end
      item
        ParamName = 'һ��ͨ��Ŀ'
        FieldName = 'lvol8'
        DefaultValue = 0
      end
      item
        ParamName = '���к�'
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
      end>
    RequestType = 850035
    KCDataset = Dataset
    Left = 152
    Top = 56
  end
end
