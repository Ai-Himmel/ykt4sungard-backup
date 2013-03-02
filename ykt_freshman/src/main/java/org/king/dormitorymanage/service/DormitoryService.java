package org.king.dormitorymanage.service;

import java.io.Serializable;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.DynaActionForm;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.dormitorymanage.exception.AccomodationNotEnoughException;
import org.king.dormitorymanage.exception.AccomodationNotRightException;
import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.dormitorymanage.exception.DormitoryHasnotbindedException;
import org.king.dormitorymanage.exception.DormitoryNotEnoughException;
import org.king.dormitorymanage.exception.DormitoryNotExistException;
import org.king.dormitorymanage.exception.GenderNotExistException;
import org.king.dormitorymanage.exception.GenderNotMatchException;
import org.king.dormitorymanage.exception.LocationNotExistException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.framework.exception.BusinessException;

public interface DormitoryService {

	/**
	 * Description:ͨ���༶��ż�������ffindDormPeoples
	 * 
	 * @param classId
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormByClass(String classId);

	/**
	 * ����Ψһ��id��������
	 * 
	 * @param dormId
	 * @return
	 */
	public Dormitorymodel getDormByDormId(Serializable dormId);

	/**
	 * ͨ������¥�ż�������
	 * 
	 * @param dormitoryId
	 * @return dormitory
	 */
	public Dormitorymodel[] getDormByDorm(String dormitory);

	/**
	 * ɾ���༶����󶨹�ϵ
	 * 
	 * @param classId
	 * @return
	 */
	public boolean deleteConnection(String classId);

	// /**
	// * ѧ����������
	// *
	// * @param studentId
	// * @param classId
	// * @throws DormitoryNotEnoughException
	// * @throws BusinessException
	// */
	// public void saveDistribution(String[] classId)
	// throws DormitoryNotEnoughException, StudentAlreadyInDormException;

	/**
	 * Description: ѧ�����������һ������
	 * 
	 * @param deleteX
	 * @return Modify History: 2006-6-27 jackey create
	 */
	public void saveCollegeDistribution(String[][] deleteX, List collegeList) 
	throws StudentAlreadyInDormException ;

	/**
	 * Description: ѧ�������������һ������
	 * 
	 * @return Modify History: 2006-6-27 jackey create
	 */
	public void saveLastDistribution() throws DormitoryNotEnoughException,
			StudentAlreadyInDormException;

	/**
	 * �������
	 * 
	 * @param dorm
	 */
	public void addDorm(Dormitorymodel dorm);

	/**
	 * ת���洢���ݲ����������
	 * 
	 * @param args
	 */
	public void addConvertDorm(List dormList) throws LocationNotExistException,
			DormitoryNotExistException, GenderNotExistException,
			StudentAlreadyInDormException;

	/**
	 * Description: ��ȡ���е�������Ϣ
	 * 
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getAllDorm();

	/**
	 * ����������ѯ����
	 * 
	 * @param param
	 * @return
	 */
	public List getDormitory(List param);

	/**
	 * ��������
	 * 
	 * @param dorm
	 */
	public void updateDormitory(Dormitorymodel dorm)
			throws AccomodationNotRightException;

	/**
	 * Description: TODO
	 * 
	 * @param temp
	 * @param untemp
	 * @throws DormitoryHasStuException
	 * @return Modify History: 2006-6-16 jackey create
	 */
	public boolean updateDormitory(String[] temp, String[] untemp)
			throws DormitoryHasStuException;

	/**
	 * Description: ��������
	 * 
	 * @return Modify History: 2006-6-21 jackey create
	 */
	public void updateBatchDorm(String operater);

	/**
	 * ɾ��������Դ
	 * 
	 * @param dorm
	 */
	public void deleteDorm(Dormitorymodel dorm);

	/**
	 * Description: ����ɾ��
	 * 
	 * @param dorm
	 * @return Modify History: 2006-6-19 jackey create
	 */
	public void deleteDorm(String[] deleteX) throws DormitoryHasStuException;

	/**
	 * ��������Ų�ѯ����
	 * 
	 * @param roomNumber
	 * @return
	 */
	public Dormitorymodel[] getDormByRoom(String roomNumber);

	/**
	 * ����¥�ź�����Ų�ѯ����
	 * 
	 * @param dormitory
	 * @param roomNumber
	 * @return
	 */
	public Dormitorymodel[] getOneDorm(String dormitory, String roomNumber);

	/**
	 * ����������ѯ������Ϣ
	 * 
	 * @param args
	 * @return
	 */
	public List findDormitorys(String[] args, String schoolId)
			throws BusinessException;

	/**
	 * Description: ����������ѯ������Ϣ����
	 * 
	 * @param args
	 * @return
	 * @throws BusinessException
	 * @return Modify History: 2006-6-26 jackey create
	 */
	public List findDormitorysExport(String[] args, String schoolId)
			throws BusinessException;

	/**
	 * Description:����������ѯ������Ϣ ����Ա
	 * 
	 * @param args
	 * @param classId
	 * @return
	 * @return Modify History: 2006-6-22 jackey create
	 */
	public List findfdyDormitorys(String[] args, String classId);

	/**
	 * Description: ����������ѯ������Ϣ ����Ա����
	 * 
	 * @param args
	 * @param classId
	 * @return
	 * @return Modify History: 2006-6-26 jackey create
	 */
	public List findfdyDormitorysExport(String[] args, String classId);

	/**
	 * ����λ�ü�¥�ţ�����Ų�ѯ������Ϣ
	 */
	public List findDormInfo(String[] args) throws BusinessException;

	public Integer getDormInfoCount(String[] args);

	/**
	 * ��ò�ѯ������Ϣ��������
	 * 
	 * @param args
	 * @return
	 */
	public Integer getDormitoryCount(String[] args, String schoolId);

	/**
	 * Description: ��ò�ѯ������Ϣ�������� ����Ա
	 * 
	 * @param args
	 * @param classId
	 * @return
	 * @return Modify History: 2006-6-22 jackey create
	 */
	public Integer getfdyDormitoryCount(String[] args, String classId);

	/**
	 * ����������ѯ���������ѧ����Ϣ
	 * 
	 * @param args
	 * @return
	 * @throws BusinessException
	 */
	public List findFreshmens(String[] args) throws BusinessException;

	/**
	 * ����������ѯ���������ѧ����Ŀ
	 * 
	 * @param args
	 * @return
	 */
	public Integer getFreshmenCount(String[] args);

	/**
	 * ����ѧ�Ÿ���ѧ��������Ϣ
	 * 
	 * @param stuNo
	 * @param dorm
	 * @param room
	 */
	public boolean updateAlert(String stuId, String dorm, String room,
			String location, String operator);

	/**
	 * ����ѧ������
	 * 
	 * @param stuNo
	 */
	public void withdrawDis(String stuId, String operator)
			throws BusinessException;

	/**
	 * ��ѯ�޸���ʷ��¼
	 * 
	 * @param args
	 */
	public List searchAlertHis(String[] args, HttpServletRequest request,
			String schoolId);

	/**
	 * Description: ��ѯ�޸���ʷ��¼����
	 * 
	 * @param args
	 * @return
	 * @return Modify History: 2006-6-26 jackey create
	 */
	public List searchAlertHisExport(String[] args, HttpServletRequest request,
			String schoolId);

	/**
	 * ��ò�ѯ������ʷ��¼������
	 * 
	 * @param args
	 * @return
	 */
	public Integer getHisCount(String[] args);

	/**
	 * Description: ��������Ѿ������˰༶�������б�
	 * 
	 * @return
	 * @return Modify History: 2006-5-10 jackey create
	 */
	public List getBindedDorm(HttpServletRequest request);

	/**
	 * Description: ���ĳ�������¥�б�
	 * 
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormbyLocation(String location);

	/**
	 * Description: ������е�¥�б�
	 * 
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormmitoryList();

	/**
	 * Description: �������û�з���������б�
	 * 
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormNoClass(HttpServletRequest request);

	/**
	 * Description: ���ĳ����¥��û�а󶨵������б�
	 * 
	 * @param dormitory
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormByDormNoBinded(String dormitory);

	/**
	 * �������¥��Դ����
	 * 
	 * @return
	 */
	public List getDormStat(HttpServletRequest request);

	public Integer getDormStatCount(HttpServletRequest request);
	
	public List getNotcheckinDormStat(HttpServletRequest request);

	/**
	 * ���������Դ
	 * 
	 * @param dormId
	 * @param location
	 * @return
	 */
	public List getDormStat(String dormId, String location,HttpServletRequest request);

	public Integer getDormStatCount(String dormId, String location,HttpServletRequest request);

	public List getNotCheckinDormStat(String dormId, String location,HttpServletRequest request);
	
	public String getDormInfo(String dorm, String location);

	// ������е�¥��
	public List getAllDormUnique();

	// ��ȡ���е�����
	public List getAllLocation();

	/**
	 * Description: ��������ŵ��ظ���
	 * 
	 * @return
	 * @return Modify History: 2006-6-6 jackey create
	 */
	public int getDormbylocdormandnum(String location, String dormitory,
			String roomNumber);

	/**
	 * Description: ��û�иĶ���
	 * 
	 * @param location
	 * @param dormitory
	 * @param roomNumber
	 * @param dormitoryId
	 * @return
	 * @return Modify History: 2006-6-13 jackey create
	 */
	public boolean getCheckdup(String location, String dormitory,
			String roomNumber, String dormitoryId);

	/**
	 * Description: ������
	 * 
	 * @return
	 * @return Modify History: 2006-6-10 jackey create
	 */
	public String getXmlMenuTree();

	/**
	 * Description: רҵ��
	 * 
	 * @return
	 * @return Modify History: 2006-6-11 jackey create
	 */
	public String getMajorinXmlMenuTree();

	/**
	 * ��������
	 * 
	 */

	public void updateDormitoryfm(String oldLocation, String oldDormitory,
			String oldRoom, String[] oldStudent, String newLocation,
			String newDormitory, String newRoom, String[] newStudent,
			String operator);

	public List findAdjustFreshmens(String[] args) throws BusinessException;

	/**
	 * Description:û��������Ա��ѯ
	 * 
	 * @param args
	 * @return
	 * @return Modify History: 2006-6-16 jackey create
	 */
	public List findAdjustPeoples(String[] args, String schoolId);

	/**
	 * Description: ĳ���������Ա�б�
	 * 
	 * @param args
	 * @return
	 * @return Modify History: 2006-6-16 jackey create
	 */
	public List findDormPeoples(String[] args, String schoolId,
			HttpServletRequest request);

	/**
	 * Description: ������Ա�����޸�
	 * 
	 * @param temp
	 * @param untemp
	 * @return Modify History: 2006-6-19 jackey create
	 */
	public void updateDormitoryPeople(String[] temp, String[] untemp,
			String operator, String role)
			throws AccomodationNotEnoughException, GenderNotMatchException,
			DormitoryHasnotbindedException;

	/**
	 * Description: ��ѯ����
	 * 
	 * @param location
	 * @param dormitory
	 * @param roomNumber
	 * @return
	 * @return Modify History: 2006-6-19 jackey create
	 */
	public Dormitorymodel getDormitory(String area, String location,
			String dormitory, String union, String roomNumber,String operator);

	public Dormitorymodel getDormitory(String area, String location,
			String dormitory, String roomNumber);
	
	public Dormitorymodel getDormitory(String area, String location,
			String dormitory, String roomNumber,String operator);

	public Dormitorymodel getfdyDormitory(String location, String dormitory,
			String roomNumber, String classId);

	/**
	 * Description: ��������Ե�����
	 * 
	 * @param temp
	 * @param untemp
	 * @param operator
	 * @throws AccomodationNotEnoughException
	 * @throws GenderNotMatchException
	 * @return Modify History: 2006-6-20 jackey create
	 */
	public void updateTwoDormitory(String[] tempA, String[] tempB,
			String operator, String role)
			throws AccomodationNotEnoughException, GenderNotMatchException;

	public void initForm(HttpServletRequest request);

	public List getAreaList(String curDept);

	public List getLocationList(String curDept);

	public String[][] getALList(String curDept);

	public String[][] getLDList(String curDept);

	/**
	 * Description: ��������Ѿ������˰༶�������б�
	 * 
	 * @return
	 * @return Modify History: 2006-5-10 jackey create
	 */
	public List getBindedDorm(String curDept);

	/**
	 * Description: ������л����Է�����༶�������б�
	 * 
	 * @return
	 * @return Modify History: 2006-5-10 jackey create
	 */
	public List getUnBindedDorm(String curDept);

	public boolean updateDormitory(String[] temp, String[] untemp,
			String curDept) throws DormitoryHasStuException;

	public List find(String sqlstring);

	public List getDormStat(String dorm, String location, String area,HttpServletRequest request);

	public Integer getDormStatCount(String dorm, String location, String area,HttpServletRequest request);

	public String getDormInfo(String dorm, String location, String area);

	public List findDormitorysExport4yg(String[] args, String schoolId)
			throws BusinessException;

	public List getSingleDormInfo(String operator);

	public List findDormitorys4yg(String[] args, String schoolId);

	public Integer getDormitoryCount4yg(String[] args, String schoolId);

	/**
	 * Description: ����ѧԺ������� saveGzDormDistribution
	 * 
	 * @param stuemp_no
	 *            Modify History: 2007-6-26 jackey create
	 */
	public void saveGzDormDistribution(String stuemp_no)
			throws DormitoryNotEnoughException, StudentAlreadyInDormException,
			Exception;
	
	/**
	* Description: ����ͳ��
	* getGzClassDormitoryStatistic
	* @param stuemp_no
	* @return
	* Modify History: 2007-6-26 jackey create
	*/
	public List getGzClassDormitoryStatistic(String stuemp_no);
	
	public List getGzClassStudentCount();
/**
 * ���ڻ���ѧԺ����Ա��������ʱ��ѯ
 * @param area
 * @param location
 * @param dormitory
 * @param roomNumber
 * @param classlist
 * @return
 */	
	public List getfdyDormitory_hlxy(String area,String location, String dormitory,
			String roomNumber, List classlist);
	
	public void initForm_fdy(HttpServletRequest request);
	
	public Integer getfdyDormitoryCount_hlxy(String[] args, List classlist) ;
	
	public List findfdyDormitorysExport_hlxy(String[] args, List classlist);
	
	public List findfdyDormitorys_hlxy(String[] args, List classlist);

	public List getDormStatyg(String dorm, String location, String area, HttpServletRequest request);

	public Integer getDormStatCountyg(String dorm, String location, String area, HttpServletRequest request);
	
	public List findfdyDormPeoples_hlxy(String[] args, String schoolId,
			HttpServletRequest request) ;
}
