/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegeService.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-25     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.service;

import java.util.List;

import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Collegemodel;
import org.king.framework.service.Service;


public interface CollegeService extends Service {
	
	/** 
	* Description: ������Ժ��Ϣ
	* @param collegemodel
	* Modify History: 2006-4-25   jackey    create
	*/
	public void saveCollege(Collegemodel collegemodel);	
	
	/** 
	* Description: �����Ա�����Ժ��ѧ�����鳤��Ϣ
	* @param collegemodel
	* @param collegeleader
	* @param collegemanager 
	* Modify History: 2006-4-27   jackey    create
	*/
	public void saveCollegeAndLeader(Collegemodel collegemodel,String collegeleader,Collegemanager collegemanager);
	
	/** 
	* Description: �����Ը�����Ժ��ѧ�����鳤��Ϣ
	* @param collegemodel
	* @param collegeleader
	* @param collegemanager 
	* Modify History: 2006-4-27   jackey    create
	*/
	public void updateCollegeAndLeader(Collegemodel collegemodel,String collegeleader,Collegemanager collegemanager);
	
	/** 
	* Description: ͨ����Ժid��ѯѧԺ��Ϣ
	* @param collegeId
	* @return Collegemodel
	* Modify History: 2006-4-25   jackey    create
	*/
	public Collegemodel getCollege(String collegeId);
	
	/**
	* Description: ͨ����Ժ��Ų�ѯѧԺ��Ϣ
	*@param collegeNo
	*@return
	* @return Modify History: 2006-5-30 jackey create
	*/
	public List getCollegebyNo(String collegeNo);
	
	/**
	* Description: ͨ����Ժ���Ʋ�ѯѧԺ��Ϣ
	*@param collegeName
	*@return
	* @return Modify History: 2006-6-5 jackey create
	*/
	public List getCollegebyName(String collegeName);
	
	/** 
	* Description: ��ѯ������Ժ��Ϣ
	* @return List
	* Modify History: 2006-4-25   jackey    create
	*/
	public List getAllCollege();
	
	/** 
	* Description: ��ѯ����ѧԺ������Ժ��Ϣ
	* @return List
	* Modify History: 2006-4-25   jackey    create
	*/	
	public List getAllCollegeByfdxy();
	/** 
	* Description: ɾ����Ժ��Ϣ
	* @param collegeId 
	* Modify History: 2006-4-25   jackey    create
	*/
	
	public void deleteCollege(String collegeId);
	
	/** 
	* Description: ����Ժ����༶
	* @param collegeId
	* @param classId 
	* Modify History: 2006-4-25   jackey    create
	*/
	public void distributeClass(String collegeId,List classId);

}
