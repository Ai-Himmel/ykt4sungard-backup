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
	 * Description:通过班级编号检索宿舍ffindDormPeoples
	 * 
	 * @param classId
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormByClass(String classId);

	/**
	 * 根据唯一的id检索宿舍
	 * 
	 * @param dormId
	 * @return
	 */
	public Dormitorymodel getDormByDormId(Serializable dormId);

	/**
	 * 通过宿舍楼号检索宿舍
	 * 
	 * @param dormitoryId
	 * @return dormitory
	 */
	public Dormitorymodel[] getDormByDorm(String dormitory);

	/**
	 * 删除班级宿舍绑定关系
	 * 
	 * @param classId
	 * @return
	 */
	public boolean deleteConnection(String classId);

	// /**
	// * 学生分配宿舍
	// *
	// * @param studentId
	// * @param classId
	// * @throws DormitoryNotEnoughException
	// * @throws BusinessException
	// */
	// public void saveDistribution(String[] classId)
	// throws DormitoryNotEnoughException, StudentAlreadyInDormException;

	/**
	 * Description: 学生分配宿舍第一步保存
	 * 
	 * @param deleteX
	 * @return Modify History: 2006-6-27 jackey create
	 */
	public void saveCollegeDistribution(String[][] deleteX, List collegeList) 
	throws StudentAlreadyInDormException ;

	/**
	 * Description: 学生分配宿舍最后一步分配
	 * 
	 * @return Modify History: 2006-6-27 jackey create
	 */
	public void saveLastDistribution() throws DormitoryNotEnoughException,
			StudentAlreadyInDormException;

	/**
	 * 添加宿舍
	 * 
	 * @param dorm
	 */
	public void addDorm(Dormitorymodel dorm);

	/**
	 * 转换存储内容并加入宿舍表
	 * 
	 * @param args
	 */
	public void addConvertDorm(List dormList) throws LocationNotExistException,
			DormitoryNotExistException, GenderNotExistException,
			StudentAlreadyInDormException;

	/**
	 * Description: 获取所有的宿舍信息
	 * 
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getAllDorm();

	/**
	 * 根据条件查询宿舍
	 * 
	 * @param param
	 * @return
	 */
	public List getDormitory(List param);

	/**
	 * 更新宿舍
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
	 * Description: 批量更新
	 * 
	 * @return Modify History: 2006-6-21 jackey create
	 */
	public void updateBatchDorm(String operater);

	/**
	 * 删除宿舍资源
	 * 
	 * @param dorm
	 */
	public void deleteDorm(Dormitorymodel dorm);

	/**
	 * Description: 批量删除
	 * 
	 * @param dorm
	 * @return Modify History: 2006-6-19 jackey create
	 */
	public void deleteDorm(String[] deleteX) throws DormitoryHasStuException;

	/**
	 * 根据宿舍号查询宿舍
	 * 
	 * @param roomNumber
	 * @return
	 */
	public Dormitorymodel[] getDormByRoom(String roomNumber);

	/**
	 * 根据楼号和宿舍号查询宿舍
	 * 
	 * @param dormitory
	 * @param roomNumber
	 * @return
	 */
	public Dormitorymodel[] getOneDorm(String dormitory, String roomNumber);

	/**
	 * 根据条件查询宿舍信息
	 * 
	 * @param args
	 * @return
	 */
	public List findDormitorys(String[] args, String schoolId)
			throws BusinessException;

	/**
	 * Description: 根据条件查询宿舍信息导出
	 * 
	 * @param args
	 * @return
	 * @throws BusinessException
	 * @return Modify History: 2006-6-26 jackey create
	 */
	public List findDormitorysExport(String[] args, String schoolId)
			throws BusinessException;

	/**
	 * Description:根据条件查询宿舍信息 辅导员
	 * 
	 * @param args
	 * @param classId
	 * @return
	 * @return Modify History: 2006-6-22 jackey create
	 */
	public List findfdyDormitorys(String[] args, String classId);

	/**
	 * Description: 根据条件查询宿舍信息 辅导员导出
	 * 
	 * @param args
	 * @param classId
	 * @return
	 * @return Modify History: 2006-6-26 jackey create
	 */
	public List findfdyDormitorysExport(String[] args, String classId);

	/**
	 * 根据位置及楼号，宿舍号查询宿舍信息
	 */
	public List findDormInfo(String[] args) throws BusinessException;

	public Integer getDormInfoCount(String[] args);

	/**
	 * 获得查询宿舍信息的总条数
	 * 
	 * @param args
	 * @return
	 */
	public Integer getDormitoryCount(String[] args, String schoolId);

	/**
	 * Description: 获得查询宿舍信息的总条数 辅导员
	 * 
	 * @param args
	 * @param classId
	 * @return
	 * @return Modify History: 2006-6-22 jackey create
	 */
	public Integer getfdyDormitoryCount(String[] args, String classId);

	/**
	 * 根据条件查询待调宿舍的学生信息
	 * 
	 * @param args
	 * @return
	 * @throws BusinessException
	 */
	public List findFreshmens(String[] args) throws BusinessException;

	/**
	 * 根据条件查询待调宿舍的学生数目
	 * 
	 * @param args
	 * @return
	 */
	public Integer getFreshmenCount(String[] args);

	/**
	 * 根据学号更改学生宿舍信息
	 * 
	 * @param stuNo
	 * @param dorm
	 * @param room
	 */
	public boolean updateAlert(String stuId, String dorm, String room,
			String location, String operator);

	/**
	 * 回收学生宿舍
	 * 
	 * @param stuNo
	 */
	public void withdrawDis(String stuId, String operator)
			throws BusinessException;

	/**
	 * 查询修改历史记录
	 * 
	 * @param args
	 */
	public List searchAlertHis(String[] args, HttpServletRequest request,
			String schoolId);

	/**
	 * Description: 查询修改历史记录导出
	 * 
	 * @param args
	 * @return
	 * @return Modify History: 2006-6-26 jackey create
	 */
	public List searchAlertHisExport(String[] args, HttpServletRequest request,
			String schoolId);

	/**
	 * 获得查询出的历史记录总条数
	 * 
	 * @param args
	 * @return
	 */
	public Integer getHisCount(String[] args);

	/**
	 * Description: 获得所有已经分配了班级的宿舍列表
	 * 
	 * @return
	 * @return Modify History: 2006-5-10 jackey create
	 */
	public List getBindedDorm(HttpServletRequest request);

	/**
	 * Description: 获得某个区域的楼列表
	 * 
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormbyLocation(String location);

	/**
	 * Description: 获得所有的楼列表
	 * 
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormmitoryList();

	/**
	 * Description: 获得所有没有分配的宿舍列表
	 * 
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormNoClass(HttpServletRequest request);

	/**
	 * Description: 获得某宿舍楼还没有绑定的宿舍列表
	 * 
	 * @param dormitory
	 * @return
	 * @return Modify History: 2006-5-11 jackey create
	 */
	public List getDormByDormNoBinded(String dormitory);

	/**
	 * 获得宿舍楼资源数据
	 * 
	 * @return
	 */
	public List getDormStat(HttpServletRequest request);

	public Integer getDormStatCount(HttpServletRequest request);
	
	public List getNotcheckinDormStat(HttpServletRequest request);

	/**
	 * 获得宿舍资源
	 * 
	 * @param dormId
	 * @param location
	 * @return
	 */
	public List getDormStat(String dormId, String location,HttpServletRequest request);

	public Integer getDormStatCount(String dormId, String location,HttpServletRequest request);

	public List getNotCheckinDormStat(String dormId, String location,HttpServletRequest request);
	
	public String getDormInfo(String dorm, String location);

	// 获得所有的楼号
	public List getAllDormUnique();

	// 获取所有的区域
	public List getAllLocation();

	/**
	 * Description: 检索宿舍号的重复性
	 * 
	 * @return
	 * @return Modify History: 2006-6-6 jackey create
	 */
	public int getDormbylocdormandnum(String location, String dormitory,
			String roomNumber);

	/**
	 * Description: 有没有改动？
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
	 * Description: 宿舍数
	 * 
	 * @return
	 * @return Modify History: 2006-6-10 jackey create
	 */
	public String getXmlMenuTree();

	/**
	 * Description: 专业数
	 * 
	 * @return
	 * @return Modify History: 2006-6-11 jackey create
	 */
	public String getMajorinXmlMenuTree();

	/**
	 * 调整宿舍
	 * 
	 */

	public void updateDormitoryfm(String oldLocation, String oldDormitory,
			String oldRoom, String[] oldStudent, String newLocation,
			String newDormitory, String newRoom, String[] newStudent,
			String operator);

	public List findAdjustFreshmens(String[] args) throws BusinessException;

	/**
	 * Description:没有宿舍人员查询
	 * 
	 * @param args
	 * @return
	 * @return Modify History: 2006-6-16 jackey create
	 */
	public List findAdjustPeoples(String[] args, String schoolId);

	/**
	 * Description: 某个宿舍的人员列表
	 * 
	 * @param args
	 * @return
	 * @return Modify History: 2006-6-16 jackey create
	 */
	public List findDormPeoples(String[] args, String schoolId,
			HttpServletRequest request);

	/**
	 * Description: 保存人员宿舍修改
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
	 * Description: 查询宿舍
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
	 * Description: 两个宿舍对调保存
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
	 * Description: 获得所有已经分配了班级的宿舍列表
	 * 
	 * @return
	 * @return Modify History: 2006-5-10 jackey create
	 */
	public List getBindedDorm(String curDept);

	/**
	 * Description: 获得所有还可以分配给班级的宿舍列表
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
	 * Description: 护理学院宿舍分配 saveGzDormDistribution
	 * 
	 * @param stuemp_no
	 *            Modify History: 2007-6-26 jackey create
	 */
	public void saveGzDormDistribution(String stuemp_no)
			throws DormitoryNotEnoughException, StudentAlreadyInDormException,
			Exception;
	
	/**
	* Description: 宿舍统计
	* getGzClassDormitoryStatistic
	* @param stuemp_no
	* @return
	* Modify History: 2007-6-26 jackey create
	*/
	public List getGzClassDormitoryStatistic(String stuemp_no);
	
	public List getGzClassStudentCount();
/**
 * 用于护理学院辅导员调换宿舍时查询
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
