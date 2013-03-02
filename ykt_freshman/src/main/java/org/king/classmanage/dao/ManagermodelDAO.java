/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ManagermodelDAO.java
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
package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Managermanagerrole;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Schoolmanager;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface ManagermodelDAO extends DAO {

	/** 
	* Description: ������ѯ
	* @param myQuery
	* @return 
	* Modify History: 2006-4-26   jackey    create
	*/
	public List find(MyQuery myQuery);

	/** 
	* Description: HQL����ѯ
	* @param query
	* @return 
	* Modify History: 2006-4-26   jackey    create
	*/
	public List find(String query);

	/** 
	* Description: id��ѯ
	* @param id
	* @return 
	* Modify History: 2006-4-26   jackey    create
	*/
	public Managermodel get(Serializable id);

	/** 
	* Description: ȫ����ѯ
	* @return 
	* Modify History: 2006-4-26   jackey    create
	*/
	public List getAll();

	/** 
	* Description: ���������Ա
	* @param transientInstance 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void save(Managermodel transientInstance);
	
	/**
	* Description: ���������Ա��ɫ��Ϣ
	*@param transientInstance
	* @return Modify History: 2006-4-28 jackey create
	*/
	public void saveDuties(Managermanagerrole transientInstance);

	/** 
	* Description: ���¼�¼
	* @param transientInstance 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void update(Managermodel transientInstance);

	/** 
	* Description: ɾ��������Ա��¼
	* @param persistentInstance 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void delete(Managermodel persistentInstance);
	
	
	/**
	* Description:ɾ��������Ա��ɫ
	*@param persistentInstance
	* @return Modify History: 2006-4-28 jackey create
	*/
	public void deleteManagermanagerRole(Managermanagerrole persistentInstance);
	

	/** 
	* Description: ���Ӳ�ѯ
	* @param Obj  ѧԺ������school ��Ժ������college �༶����Ա������class_ass �༶��ʦ������class_tu רҵ��ʦ����: class_spetu
	* @param id   id ���Ϊ<br>  "GET_ALL"  </br>���ʾ��ѯ����  schoolId ��ʾ����Ժϵ
	* @return 
	* Modify History: 2006-4-27   jackey    create
	*/
	public List findSpecial(String Obj,String id,String schoolId);
	

	/** 
	* Description: ���Ӳ�ѯ
	* @param Obj  ѧԺ������school ��Ժ������college �༶����Ա������class_ass �༶��ʦ������class_tu 
	* @param id   id ���Ϊ<br>  "GET_ALL"  </br>���ʾ��ѯ����  
	* @param check True ��ʾֱ�Ӳ�ѯ��û�з������Ա
	* @return Modify History: 2006-7-4 jackey create
	*/

	public List findSpecial(String Obj, String id, boolean check,String schoolId);
	
	
	/** 
	* Description: ������Ժ����Ա��ϵ
	* @param collegemanager 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void saveCollegeManager(Collegemanager collegemanager);
	
	/** 
	* Description: ɾ����Ժ����Ա��ϵ
	* @param collegeId 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void deleteCollegeManager(String collegeId);
	
	
	/**
	* Description:  ɾ����Ժ����Ա
	*@param collegemanager
	* @return Modify History: 2006-5-29 jackey create
	*/
	public void deleteCollegeManager(Collegemanager collegemanager);
	
	/** 
	* Description: ����ѧԺ����Ա��ϵ
	* @param schoolmanager 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void saveSchoolManager(Schoolmanager schoolmanager);
	
	/** 
	* Description: ɾ��ѧԺ����Ա��ϵ
	* @param schoolId 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void deleteSchoolManager(String schoolId);
	
	/**
	* Description: ɾ��ѧԺ����Ա
	*@param schoolmanager
	* @return Modify History: 2006-5-29 jackey create
	*/
	public void deleteSchoolManager(Schoolmanager schoolmanager);
	
	/** 
	* Description: ����༶����Ա��ϵ
	* @param classmanager 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void saveClassManager(Classmanager classmanager);
	
	/** 
	* Description: ɾ���༶����Ա��ϵ
	* @param classId 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void deleteClassAssitant(String classId);
	
	/**
	* Description: ɾ���༶����ԭ
	*@param classmanager
	* @return Modify History: 2006-5-29 jackey create
	*/
	public void deleteClassmanager(Classmanager classmanager);
	
	
	/** 
	* Description: ����༶��ʦ��ϵ
	* @param classId 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void deleteClassTutor(String classId);
	

}
