 /*********************************************
 **	    HT IO Control extended functions     **
 **		Heading File For HT2800              **
 *********************************************/

#ifndef __IOCTRL

    extern unsigned int GetIOsts(void)
    /*
    1.��ȡIO�������룯���״̬���ã�HT2800��Ч��
    ��������
    ���ز�����
    ����ֵ:  �� ����Ӧ11�ţ�����BITS�����壩
           1�����룬0�����
    */

    extern void SetIOsts(unsigned int status)
    /*
    2.����IO�������룯���״̬��HT2800��Ч��
    ������ �� ����Ӧ11�ţ�����BITS�����壩
         1�����룬0�����
    ���ز����� ��
    */

    extern unsigned int ReadIOPort(void)
    /*
    3.��IO���ڶ�ȡ���ݣ�HT2800��Ч��
    ��������
    ���ز�����
    ����ֵ:  �� ����Ӧ11�ţ�����BITS�����壩
    */

    extern void SetIOPort(unsigned int value)
    /*
    4.��IO���������ݣ�HT2800��Ч��
    ������ �� ����Ӧ11�ţ�����BITS�����壩
    ���ز����� ��
    */

    extern void NormalIOsts(void)
    /*
    5.�˳�IO�������룯���״̬��HT2800��Ч��
    ��������
    ���ز����� ��
    */

#endif
