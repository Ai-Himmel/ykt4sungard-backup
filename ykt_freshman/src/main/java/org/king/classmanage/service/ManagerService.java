/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ManagerService.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-26     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.service;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Schoolmanager;
import org.king.classmanage.exception.ManagerInClassException;
import org.king.classmanage.exception.ManagerInCollegeException;
import org.king.classmanage.exception.ManagerInSchoolException;
import org.king.framework.service.Service;

public interface ManagerService extends Service {

	/**
	 * Description: ������Ա�Ļ�����Ϣ
	 * 
	 * @param managerNo
	 * @return
	 * @return Modify History: 2006-5-29 jackey create
	 */
	public List findManagerInfo(String managerNo);
	
/**
 * ������Ա�༭ҳ����Ҫ�Ĳ���
 * @param request
 */	
	public void initForm(HttpServletRequest request);

	/**
	 * Description: ��������ѯ������Ա
	 * 
	 * @param args
	 * @return Modify History: 2006-4-28 jackey create
	 */
	
	public Managermodel findManager(String manageId);
	
	public List findManager(String[] args,String schoolId);
	
	public List findManagerExport(String[] args,String schoolId);

	/**
	 * Description: ��������ѯ������Ա����
	 * 
	 * @param args
	 * @return
	 * @return Modify History: 2006-5-29 jackey create
	 */
	public Integer findManagerCount(String[] args,String schoolId);

	/**
	 * Description: ��ѯ������Ա�Ľ�ɫ
	 * 
	 * @param managerId
	 * @return
	 * @return Modify History: 2006-4-29 jackey create
	 */
	public List findManagerRole(String managerId);

	/**
	 * Description: �������Ա
	 * 
	 * @param managermodel
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveManager(Managermodel managermodel);
	public void updateManager(Managermodel managermodel);
	
	/**
	 * ����ѧԺ��Ӹ���Ա
	 * @param managermodel
	 * @param list
	 */
	public void saveManagerandRole_hlxy(Managermodel managermodel, List list) ;

	/**
	 * Description: ͬʱ���������Ա�ͽ�ɫ��Ϣ
	 * 
	 * @param managermodel
	 * @param list
	 * @return Modify History: 2006-4-28 jackey create
	 */
	public void saveManagerandRole(Managermodel managermodel, List list);

	/**
	 * Description: ͬʱ���¹�����Ա�ͽ�ɫ��Ϣ
	 * 
	 * @param managermodel
	 * @param list
	 * @return Modify History: 2006-4-28 jackey create
	 */
	public void updateManagerandRole(Managermodel managermodel, List list,
			String roleStr)throws ManagerInClassException, ManagerInCollegeException,
			ManagerInSchoolException;

	/**
	 * Description: ��ѯ���й���Ա
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getManager();

	/**
	 * Description: ��ѯ��Ժѧ�����鳤
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getCollegeManager();
	
	public List getCollegeManager(boolean bool);

	/**
	 * Description: ͨ����Ժ��ѧ�����鳤
	 * 
	 * @param collegeId
	 * @return Modify History: 2006-4-27 jackey create
	 */
	public List getCollegeManager(String collegeId);

	/**
	 * Description: ������Ժ����Ա��ϵ
	 * 
	 * @param collegemanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveCollegeManager(Collegemanager collegemanager);

	/**
	 * Description: ɾ����Ժ����Ա��ϵ
	 * 
	 * @param collegemanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteCollegeManager(String collegeId);

	/**
	 * Description: ��ѯѧԺ����Ա
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getSchoolManager();
	
	public List getSchoolManager(boolean bool);

	/**
	 * Description: ͨ��ѧԺ�����Ա
	 * 
	 * @param schoolId
	 * @return Modify History: 2006-4-27 jackey create
	 */
	public List getSchoolManager(String schoolId);

	/**
	 * Description: ����ѧԺ����Ա��ϵ
	 * 
	 * @param schoolmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveSchoolManager(Schoolmanager schoolmanager);

	/**
	 * Description: ɾ��ѧԺ����Ա��ϵ
	 * 
	 * @param schoolmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteSchoolManager(String schoolId);

	/**
	 * Description: ��ѯ���а༶����Ա
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getClassAssitant();
	
	public List getClassAssitant(boolean bool);

	/**
	 * Description: ��ѯ����Ա�Ƿ����ڰ༶
	 * 
	 * @param managerId
	 * @return
	 * @return Modify History: 2006-5-27 jackey create
	 */
	public List getClassAssistantByManagerId(String managerId);

	/**
	 * Description: ��ѯ����Ա�Ƿ�������Ժ
	 * 
	 * @param managerId
	 * @return
	 */
	public List getCollegeAssistantByManagerId(String managerId);

	/**
	 * Description: ͨ����Ų鸨��Ա
	 * 
	 * @param classId
	 * @return Modify History: 2006-4-27 jackey create
	 */
	public List getClassAssitant(String classId);

	/**
	 * Description: ����༶����Ա��ϵ
	 * 
	 * @param classmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveClassAssitant(Classmanager classmanager);

	/**
	 * Description: ɾ���༶����Ա��ϵ
	 * 
	 * @param classmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteClassAssitant(String classId);

	/**
	 * Description: ��ѯ�༶��ʦ
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getClassTutor();
	
	public List getClassTutor(boolean bool);

	/**
	 * Description: ͨ����Ų鵼ʦ
	 * 
	 * @param classId
	 * @return Modify History: 2006-4-27 jackey create
	 */
	public List getClassTutor(String classId);
	
	/**
	* Description: ͨ����Ų�רҵ��ʦ
	*@param classId
	*@return
	* @return Modify History: 2006-7-6 jackey create
	*/
	public List getClassSpeTutor(String classId);
	

	/**
	 * Description: ����༶��ʦ��ϵ
	 * 
	 * @param classmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveClassTutor(Classmanager classmanager);

	/**
	 * Description: ɾ���༶��ʦ��ϵ
	 * 
	 * @param classmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteClassTutor(String classId);

	/**
	 * Description: id��ѯ����Ա
	 * 
	 * @param manageId
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public Managermodel getManager(String manageId);

	/**
	 * Description: ѧ���Ų�ѯ����Ա
	 * 
	 * @param managerNo
	 * @return
	 * @return Modify History: 2006-5-29 jackey create
	 */
	public List getManagerByNo(String managerNo);

	/**
	 * Description: ɾ������Ա
	 * 
	 * @param managerId
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteManager(String managerId);
	
	/**
	 * �޸Ĺ���Ա�������
	 * @param deleteX
	 */
	public void modifyManager_Available(String[] deleteX);

	/**
	 * Description: ͬʱɾ������Ա�ͽ�ɫ��Ϣ
	 * 
	 * @param managerId
	 * @return Modify History: 2006-4-28 jackey create
	 */
	public boolean deleteManagerandRole(String managerId) throws ManagerInClassException,ManagerInCollegeException,ManagerInSchoolException;

	public boolean inRole(String managerId, String role);
	
	/**
	* Description: TODO
	*@param managerNo
	*@return�༶id
	* @return Modify History: 2006-6-21 jackey create
	*/
	public String findManagerclass(String managerId);
	
	
	/**
	* Description: ͨ����ɫ����ɫ���в���id
	*@param roleName
	*@return
	* @return Modify History: 2006-6-28 jackey create
	*/
	public String getRoleidByName(String roleName);
	
	/**
	* Description: ͨ��ѧ���Ų���accountid
	*@param roleName
	*@return
	* @return Modify History: 2006-6-28 jackey create
	*/
	public String getAccountidByNo(String managerNo);
	
/**
 * ����ѧԺ���ڲ��Ұ༶����Ա�ȵ�
 * @return
 */	
	public List getClassAssitant_hlxy();
	
	public List getClassAssitant_hlxy(boolean bool);
	
	public List getClassTutor_hlxy();
	
	public List getClassTutor_hlxy(boolean bool);
	
	public List getClassAssitant_hlxy(String classId);
	
	public List getClassTutor_hlxy(String classId) ;
	
	public List getClassSpeTutor_hlxy(String classId) ;
	
	public List findManagerclass_hlxy(String managerId);
	
	

	
}
