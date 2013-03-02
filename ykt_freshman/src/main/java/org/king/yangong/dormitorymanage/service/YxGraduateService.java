package org.king.yangong.dormitorymanage.service;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.dormitorymanage.exception.DormitoryNotEnoughException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.framework.exception.BusinessException;
import org.king.yangong.dormitorymanage.domain.YxGraduate;


/**
	* File name: YxGraduateService.java<br>
	* Description: <br>
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青(jackey)
	* @version 
	* @since 1.0
	*/
public interface YxGraduateService {

	/**
		* Method name: getStudentTypeList<br>
		* Description: 学生类型列表<br>
		* Return: @return<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getStudentTypeList();
	
	/**
		* Method name: getStyleList<br>
		* Description: 培养方式列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getStyleList();
	
	/**
		* Method name: getCollegeList<br>
		* Description: 录取院系列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getCollegeList();
	
	/**
		* Method name: getCollegeListFromGraduateTable<br>
		* Description: 从研究生表中获得学院信息列表<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getCollegeListFromGraduateTable();
	
	
	/**
			* Method name: getCollegeListFromGraduateTableLimit<br>
			* Description: <br>
			* Return: List<br>
			* Args: @param stuemp_no
			* Args: @return
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    2007-7-2  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	public List getCollegeListFromGraduateTableLimit(String stuemp_no);
		
	/**
	* Method name: getMajorListFromGraduateTable<br>
	* Description: 列表<br>
	* Return: List<br>
	* Args: @return
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      罗帆    2007-6-8  <br>
	* @author   罗帆
	* @version 
	* @since 1.0
	*/
	public List getMajorListFromGraduateTable();
	/**
		* Method name: getCollegeBindingList<br>
		* Description: 需要邦定的学院信息列表<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getCollegeBindingList(String stuemp_no);
	
	/**
		* Method name: getQuarterBindingList<br>
		* Description: 宿舍资源列表<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getDormitoryList(String stuemp_no);
	
	/**
		* Method name: getBindedDormitoryList<br>
		* Description: 已绑定的宿舍资源列表<br>
		* Return: List<br>
		* Args: @param stuemp_no
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-11  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getBindedDormitoryList(String stuemp_no);
	/**
		* Method name: getSpecialityList<br>
		* Description: 专业列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	
	public List getSpecialityList();
	
	/**
		* Method name: getTypeList<br>
		* Description: 研究生类型列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getTypeList();
	

	/**
		* Method name: getGraduatesList<br>
		* Description: 研究生基本信息列表<br>
		* Return: List<br>
		* Args: @param graduate 查询参数的YxGraduate对象
		* Args: @param args args[0]:学号规则从第几个开始 args[1]:列表所在第几页
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getGraduatesList(YxGraduate graduate,String[] args);
	
	public Integer getGraduatesListCount(YxGraduate graduate,String[] args);

	/**
		* Method name: getGraduateResidentsList<br>
		* Description: 研究生住宿申请名单筛选列表<br>
		* Return: List<br>
		* Args: @param graduate 查询参数的YxGraduate对象
		* Args: @param args args[0]:学号规则从第几个开始 args[1]:列表所在第几页
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getGraduateResidentsList(YxGraduate graduate,String[] args);
	
	public Integer getGraduateResidentsListCount(YxGraduate graduate,String[] args);
	/**
		* Method name: updateGraduates<br>
		* Description: 更新研究生基本信息<br>
		* Return: boolean<br>
		* Args: @param graduateNo 更新的研究生学号列表
		* Args: @param args args[0]:新住宿类型 args[1]:新学制
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public boolean updateGraduates(String[] graduateNo,String[] args);
	
	/**
		* Method name: updateGraduateResidents<br>
		* Description: 更新研究生住宿信息<br>
		* Return: boolean<br>
		* Args: @param graduateNo 更新的研究生学号列表
		* Args: @param args args[0]:新区域 args[1]:是否可以申请
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public boolean updateGraduateResidents(String[] graduateNo,String[] args,HttpServletRequest request);
	
	/**
		* Method name: getTabssdeptList<br>
		* Description: 获得管理部门<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-18  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getTabssdeptList(String stuemp_no);
	
	/**
		* Method name: getDistrictionList<br>
		* Description: 获得宿舍区域列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getDistrictionList();
	
	/**
		* Method name: getRequestavailableList<br>
		* Description: 是否可以申请宿舍字典表  1是  2否<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getRequestavailableList();
	
	/**
		* Method name: getSexList<br>
		* Description: 获得学生性别列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getSexList();
	
	/**
		* Method name: getSectionList<br>
		* Description: 获得宿舍校区列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getSectionList();
	
	/**
		* Method name: getBuildingList<br>
		* Description: 获得宿舍楼号列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getBuildingList();
	
	/**
		* Method name: getLayerList<br>
		* Description: 获得宿舍层列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getLayerList();
	
	
	/**
		* Method name: getCellList<br>
		* Description: 单元号列表<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getCellList();
	
	public boolean updateDormitory(String[] temp, String[] untemp,String stuemp_no)
	throws DormitoryHasStuException,Exception;
	
	/**
		* Method name: saveDormDistribution<br>
		* Description: 学生分配宿舍<br>
		* Return: void<br>
		* Args: @throws DormitoryNotEnoughException
		* Args: @throws StudentAlreadyInDormException
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-13  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public void saveDormDistribution(String stuemp_no) throws DormitoryNotEnoughException,
	StudentAlreadyInDormException,Exception;
	
	/**
		* Method name: getCollegeStudentCount<br>
		* Description: 学院需要入住学生的统计信息<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-13  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getCollegeStudentCount(String stuemp_no);
	
	/**
		* Method name: getCollegeDormitoryStatistic<br>
		* Description: 学院宿舍的绑定情况统计信息<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-13  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getCollegeDormitoryStatistic(String stuemp_no);
	
	/**
		* Method name: getGraduateCount<br>
		* Description: 宿舍分配的人数统计<br>
		* Return: String<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-14  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public String getGraduateCount(String stuemp_no);
	
	
	public List getGraduateResidentsExport(YxGraduate graduate, String[] args)
	throws BusinessException ;

	public List getGraduateListByDorm(String operator);

	public List getSxList(String stuemp_no);

	public List getCanreqList(String stuemp_no);
	public List getGzListByDorm(String operator);
}
