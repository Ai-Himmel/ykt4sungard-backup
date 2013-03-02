/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.Constants.java
 * �������ڣ� 2006-6-20 21:26:09
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-20 21:26:09      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.check;

/**
 * <p> Constants.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="Constants.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-20
 * 
 *
 */
public class Constants {

	public static String SELECTED_PERSON = "selectedPerson";
	public static String DBNAME = "ORACLE";//DB2,ORACLE
	public static String LINKADD = "http://www.ecardapp.fudan.edu.cn:8090/check";
	public static String PUBREST = "'1','8','9'";//���¼� 
	public static String NOCUSTID="�޴���ʦ��ѧ����:";
	
	public static String EXCEL_IMPSUCCESS="";
	
	public static final String OPRATER_EQUAL = "=";

    public static final String OPRATER_UNEQUAL = "<>";

    public static final String OPRATER_GREATER_AND_EQUAL = ">=";

    public static final String OPRATER_LESS_AND_EQUAL = "<=";

    public static final String OPRATER_GREATER = ">";

    public static final String OPRATER_LESS = "<";

    public static final String OPRATER_CONTAINS = "%|%";

    public static final String OPRATER_NOT_CONTAINS = "%||%";

    public static final String OPRATER_LEFT_CONTAINS = "|%";

    public static final String OPRATER_RIGHT_CONTAINS = "%|";

    public static final String OPRATER_BETWEEN = "between";

    public static final String OPRATER_ISNULL = "is null";

    public static final String OPRATER_ISNOTNULL = "is not null";

    public static final String OPRATER_AND = "and";

    public static final String OPRATER_OR = "or";

    //��ɫ����--��������Ա
    public static final String ROLE_TYPE_SYS_ADMIN = "0";

    //��ɫ����--У������Ա
    public static final String ROLE_TYPE_AREA_ADMIN = "1";

    //��ɫ����--Ժϵ����Ա
    public static final String ROLE_TYPE_FACULTY_ADMIN = "2";

    //��ɫ����--����Ա
    public static final String ROLE_TYPE_ASSISTANT = "3";

    //��ɫ����--�ο���ʦ
    public static final String ROLE_TYPE_TEACHER = "4";

    //��ɫ����--һ���ɫ
    public static final String ROLE_TYPE_NORMAL = "5";

    //ϵͳͬ�����ɵ�δ��˿γ̼ƻ���Ϣ
    public static final String AUTO_COURSEPLAN = "1";

    //�˹�Ԥ����ʱ���ɵ�δ��˿γ̼ƻ���Ϣ
    public static final String MANUAL_COURSEPLAN = "2";

    //δͨ����˵���ʷ�γ̼ƻ���Ϣ
    public static final String UNACCEPTED_COURSEPLAN = "0";
	
}
