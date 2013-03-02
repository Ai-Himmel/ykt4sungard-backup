package org.king.yangong.dormitorymanage.service.impl;

import java.sql.Types;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;
import org.hibernate.HibernateException;
import org.king.classmanage.domain.ClassDorm;
import org.king.classmanage.domain.Department;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.web.help.StudentWithAllInfo;
import org.king.dormitorymanage.dao.DormitorymodelDAO;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.dormitorymanage.exception.DormitoryNotEnoughException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.dormitorymanage.web.help.DormitoryWithAllInfo;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.dao.YxGraduateDAO;
import org.king.yangong.dormitorymanage.domain.YxGraduate;
import org.king.yangong.dormitorymanage.service.YxGraduateService;
import org.king.yangong.dormitorymanage.web.help.CanReqTJ;
import org.king.yangong.dormitorymanage.web.help.CollegeBindingInfo;
import org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount;
import org.king.yangong.dormitorymanage.web.help.SxTJ;
import org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo;

import com.ibm.icu.text.CollationKey;
import com.ibm.icu.text.Collator;


public class YxGraduateServiceImpl implements YxGraduateService {
	private YxGraduateDAO yxGraduateDAO;

	private DormitorymodelDAO dormitorymodelDAO;

	public void setDormitorymodelDAO(DormitorymodelDAO dormitorymodelDAO) {
		this.dormitorymodelDAO = dormitorymodelDAO;
	}

	public void setYxGraduateDAO(YxGraduateDAO yxGraduateDAO) {
		this.yxGraduateDAO = yxGraduateDAO;
	}

	public List getStudentTypeList() {
		List ret = null;
		ret = yxGraduateDAO.getStudentTypeList();
		return ret;
	}

	public List getStyleList() {
		List ret = null;
		ret = yxGraduateDAO.getStyleList();
		return ret;
	}

	public List getCollegeList() {
		List ret = null;
		ret = yxGraduateDAO.getCollegeList();
		return ret;
	}

	public List getCollegeListFromGraduateTable() {
		List ret = null;
		ret = yxGraduateDAO.getCollegeListFromGraduateTable();
		Comparator comp2 = new Comparator() {
			public int compare(Object o1, Object o2) {
				Department m1 = (Department) o1;
				Department m2 = (Department) o2;
				Collator col = Collator.getInstance(Locale.CHINA);
				String stuName1 = (String) m1.getDeptName();
				String stuName2 = (String) m2.getDeptName();
				CollationKey c1 = col.getCollationKey(stuName1);
				CollationKey c2 = col.getCollationKey(stuName2);
				return c1.compareTo(c2);
			}
		};
		Collections.sort(ret, comp2);
		return ret;
	}

	public List getCollegeListFromGraduateTableLimit(String stuemp_no) {
		List ret = null;
		ret = yxGraduateDAO
				.find("select distinct a from Department a,YxGraduate b,TabSsManager c "
						+ "where a.deptCode=b.curCollege and b.distriction=c.tabSsDept.id "
						+ "and c.stuNo='"
						+ stuemp_no
						+ "' and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and b.requestAvailable='1' and b.residentNeed='1' order by a.gsort");
		return ret;
	}	
	
	public List getMajorListFromGraduateTable() {
		List ret = null;
		ret = yxGraduateDAO.getMajorListFromGraduateTable();
		return ret;
	}

	public List getDormitoryList(String stuemp_no) {
		List entitys = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo("
						+ "a.dormitoryId,a.area,'',a.location,'',a.dormitory,'',a.level,'',a.unit,''"
						+ ",a.direction,'',a.roomNumber,a.gender,'',a.emptyNum,'','') "
						+ "from Dormitorymodel a ,TabSsManager b,Dictionary d1,Dictionary d2 where a.curDormDept=b.tabSsDept.id "
						+ "and a.location=d1.id.dictValue and d1.id.dictNo=20 and a.dormitory=d2.id.dictValue and d2.id.dictNo=21 and b.stuNo='" + stuemp_no + "' and a.emptyNum>0 "
						+" order by a.area,d1.dictSort,d2.dictSort,a.level,a.unit,a.roomNumber");
		HashMap Hash_section = new HashMap();
		List Temp_section = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 17 ");
		for (int i = 0; i < Temp_section.size(); i++) {
			HashMap temp = (HashMap) Temp_section.get(i);
			Hash_section.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_distriction = new HashMap();
		List Temp_distriction = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 20 ");
		for (int i = 0; i < Temp_distriction.size(); i++) {
			HashMap temp = (HashMap) Temp_distriction.get(i);
			Hash_distriction
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_dormitory = new HashMap();
		List Temp_dormitory = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 21 ");
		for (int i = 0; i < Temp_dormitory.size(); i++) {
			HashMap temp = (HashMap) Temp_dormitory.get(i);
			Hash_dormitory.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_level = new HashMap();
		List Temp_level = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 22 ");
		for (int i = 0; i < Temp_level.size(); i++) {
			HashMap temp = (HashMap) Temp_level.get(i);
			Hash_level.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_unit = new HashMap();
		List Temp_unit = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 21 ");
		for (int i = 0; i < Temp_unit.size(); i++) {
			HashMap temp = (HashMap) Temp_unit.get(i);
			Hash_unit.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_direct = new HashMap();
		List Temp_direct = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 24 ");
		for (int i = 0; i < Temp_direct.size(); i++) {
			HashMap temp = (HashMap) Temp_direct.get(i);
			Hash_direct.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		for (int i = 0; i < entitys.size(); i++) {
			YangongDormitoryBindInfo yangongDormitorybindinfo = (YangongDormitoryBindInfo) entitys
					.get(i);
			String sectionCode = "";
			String sectionStr = "";
			if (!"".equals(yangongDormitorybindinfo.getLocation())) {// 校区
				if (sectionCode.equals(yangongDormitorybindinfo.getLocation())) {
					yangongDormitorybindinfo.setAreaStr(sectionStr);
				} else {
					sectionCode = yangongDormitorybindinfo.getArea();
					if (Hash_section.get(sectionCode) != null) {
						sectionStr = Hash_section.get(sectionCode).toString();
						yangongDormitorybindinfo.setAreaStr(sectionStr);
					} else {
						yangongDormitorybindinfo.setLocationStr("");
					}
				}

			}

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(yangongDormitorybindinfo.getLocation())) {// 区域
				if (locationCode.equals(yangongDormitorybindinfo.getLocation())) {
					yangongDormitorybindinfo.setLocationStr(locationStr);
				} else {
					locationCode = yangongDormitorybindinfo.getLocation();
					if (Hash_distriction.get(locationCode) != null) {
						locationStr = Hash_distriction.get(locationCode)
								.toString();
						yangongDormitorybindinfo.setLocationStr(locationStr);
					} else {
						yangongDormitorybindinfo.setLocationStr("");
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(yangongDormitorybindinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(yangongDormitorybindinfo
						.getDormitory())) {
					yangongDormitorybindinfo.setDormitoryStr(dormitoryStr);
				} else {
					dormitoryCode = yangongDormitorybindinfo.getDormitory();
					if (Hash_dormitory.get(dormitoryCode) != null) {
						dormitoryStr = Hash_dormitory.get(dormitoryCode)
								.toString();
						yangongDormitorybindinfo.setDormitoryStr(dormitoryStr);
					} else {
						yangongDormitorybindinfo.setDormitoryStr("");
					}
				}
			}
			String directionCode = "";
			String directionStr = "";
			if (!"".equals(yangongDormitorybindinfo.getDirection())) {// 朝向
				if (directionCode.equals(yangongDormitorybindinfo
						.getDirection())) {
					yangongDormitorybindinfo.setDirectionStr(directionStr);
				} else {
					directionCode = yangongDormitorybindinfo.getDirection();
					if (Hash_direct.get(directionCode) != null) {
						directionStr = Hash_direct.get(directionCode)
								.toString();
						yangongDormitorybindinfo.setDirectionStr(directionStr);
					} else {
						yangongDormitorybindinfo.setDirectionStr("");
					}
				}
			}
			

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(yangongDormitorybindinfo.getGender())) {// 性别
				if (genderCode.equals(yangongDormitorybindinfo.getGender())) {
					yangongDormitorybindinfo.setGenderStr(genderStr);
				} else {
					genderCode = yangongDormitorybindinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						yangongDormitorybindinfo.setGenderStr(genderStr);
					} else {
						yangongDormitorybindinfo.setGenderStr("");
					}
				}

			}

		}
		return entitys;

	}

	public List getBindedDormitoryList(String stuemp_no) {
		List entitys = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo("
						+ "a.dormitoryId,a.area,'',a.location,'',a.dormitory,'',a.level,'',a.unit,''"
						+ ",a.direction,'',a.roomNumber,a.gender,'',b.distributeNum,b.studentType,b.classId) "
						+ "from Dormitorymodel a,ClassDorm b,TabSsManager c,Dictionary d1,Dictionary d2 "
						+ "where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
						+ "and a.location=d1.id.dictValue and d1.id.dictNo=20 and a.dormitory=d2.id.dictValue and d2.id.dictNo=21 and c.stuNo='"
						+ stuemp_no
						+ "' and b.curYear='"
						+ DateUtil.getNow("yyyy") + "' order by a.area,d1.dictSort,d2.dictSort,a.level,a.unit,a.roomNumber");

		HashMap Hash_section = new HashMap();
		List Temp_section = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 17 ");
		for (int i = 0; i < Temp_section.size(); i++) {
			HashMap temp = (HashMap) Temp_section.get(i);
			Hash_section.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_distriction = new HashMap();
		List Temp_distriction = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 20 ");
		for (int i = 0; i < Temp_distriction.size(); i++) {
			HashMap temp = (HashMap) Temp_distriction.get(i);
			Hash_distriction
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_dormitory = new HashMap();
		List Temp_dormitory = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 21 ");
		for (int i = 0; i < Temp_dormitory.size(); i++) {
			HashMap temp = (HashMap) Temp_dormitory.get(i);
			Hash_dormitory.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_level = new HashMap();
		List Temp_level = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 22 ");
		for (int i = 0; i < Temp_level.size(); i++) {
			HashMap temp = (HashMap) Temp_level.get(i);
			Hash_level.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_unit = new HashMap();
		List Temp_unit = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 21 ");
		for (int i = 0; i < Temp_unit.size(); i++) {
			HashMap temp = (HashMap) Temp_unit.get(i);
			Hash_unit.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_direct = new HashMap();
		List Temp_direct = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 24 ");
		for (int i = 0; i < Temp_direct.size(); i++) {
			HashMap temp = (HashMap) Temp_direct.get(i);
			Hash_direct.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_gender = new HashMap();
		List Temp_gender = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		for (int i = 0; i < entitys.size(); i++) {
			YangongDormitoryBindInfo yangongDormitorybindinfo = (YangongDormitoryBindInfo) entitys
					.get(i);
			String sectionCode = "";
			String sectionStr = "";
			if (!"".equals(yangongDormitorybindinfo.getLocation())) {// 校区
				if (sectionCode.equals(yangongDormitorybindinfo.getLocation())) {
					yangongDormitorybindinfo.setAreaStr(sectionStr);
				} else {
					sectionCode = yangongDormitorybindinfo.getArea();
					if (Hash_section.get(sectionCode) != null) {
						sectionStr = Hash_section.get(sectionCode).toString();
						yangongDormitorybindinfo.setAreaStr(sectionStr);
					} else {
						yangongDormitorybindinfo.setLocationStr("");
					}
				}

			}

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(yangongDormitorybindinfo.getLocation())) {// 区域
				if (locationCode.equals(yangongDormitorybindinfo.getLocation())) {
					yangongDormitorybindinfo.setLocationStr(locationStr);
				} else {
					locationCode = yangongDormitorybindinfo.getLocation();
					if (Hash_distriction.get(locationCode) != null) {
						locationStr = Hash_distriction.get(locationCode)
								.toString();
						yangongDormitorybindinfo.setLocationStr(locationStr);
					} else {
						yangongDormitorybindinfo.setLocationStr("");
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(yangongDormitorybindinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(yangongDormitorybindinfo
						.getDormitory())) {
					yangongDormitorybindinfo.setDormitoryStr(dormitoryStr);
				} else {
					dormitoryCode = yangongDormitorybindinfo.getDormitory();
					if (Hash_dormitory.get(dormitoryCode) != null) {
						dormitoryStr = Hash_dormitory.get(dormitoryCode)
								.toString();
						yangongDormitorybindinfo.setDormitoryStr(dormitoryStr);
					} else {
						yangongDormitorybindinfo.setDormitoryStr("");
					}
				}
			}
			
			String directionCode = "";
			String directionStr = "";
			if (!"".equals(yangongDormitorybindinfo.getDirection())) {// 朝向
				if (directionCode.equals(yangongDormitorybindinfo
						.getDirection())) {
					yangongDormitorybindinfo.setDirectionStr(directionStr);
				} else {
					directionCode = yangongDormitorybindinfo.getDirection();
					if (Hash_direct.get(directionCode) != null) {
						directionStr = Hash_direct.get(directionCode)
								.toString();
						yangongDormitorybindinfo.setDirectionStr(directionStr);
					} else {
						yangongDormitorybindinfo.setDirectionStr("");
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(yangongDormitorybindinfo.getGender())) {// 性别
				if (genderCode.equals(yangongDormitorybindinfo.getGender())) {
					yangongDormitorybindinfo.setGenderStr(genderStr);
				} else {
					genderCode = yangongDormitorybindinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						yangongDormitorybindinfo.setGenderStr(genderStr);
					} else {
						yangongDormitorybindinfo.setGenderStr("");
					}
				}

			}

		}
		return entitys;

	}

	public List getCollegeBindingList(String stuemp_no) {
		List entitys = null;
		String allHql = "select distinct new org.king.yangong.dormitorymanage.web.help.CollegeBindingInfo("
				+ "a.curCollege,'',a.studentType,'',a.sex,'',count(*) as count) "
				+ "from YxGraduate a"
				+ ",TabSsManager b where a.distriction=b.tabSsDept.id "
				+ "and b.stuNo='"
				+ stuemp_no
				+ "' and a.enrollYear='"
				+ DateUtil.getNow("yyyy")
				+ "' and a.requestAvailable='1' and a.residentNeed='1' "
				+ " group by a.curCollege,a.studentType,a.sex order by a.curCollege,a.studentType,a.sex";
		entitys = yxGraduateDAO.find(allHql);
		HashMap Hash_curCollege = new HashMap();
		List Temp_curCollege = yxGraduateDAO
				.find("select new map(a.deptCode as deptCode,a.deptName as deptName) "
						+ "from Department a ");
		for (int i = 0; i < Temp_curCollege.size(); i++) {
			HashMap temp = (HashMap) Temp_curCollege.get(i);
			Hash_curCollege.put(temp.get("deptCode"), temp.get("deptName"));
		}

		HashMap Hash_studentType = new HashMap();
		List Temp_studentType = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 15 ");
		for (int i = 0; i < Temp_studentType.size(); i++) {
			HashMap temp = (HashMap) Temp_studentType.get(i);
			Hash_studentType
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_sex = new HashMap();
		List Temp_sex = yxGraduateDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_sex.size(); i++) {
			HashMap temp = (HashMap) Temp_sex.get(i);
			Hash_sex.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		for (int i = 0; i < entitys.size(); i++) {
			CollegeBindingInfo collegeBindingInfo = (CollegeBindingInfo) entitys
					.get(i);
			String curCollegeCode = "";
			String curCollegeStr = "";
			if (!"".equals(collegeBindingInfo.getCurCollege())) {// 院系
				if (curCollegeCode.equals(collegeBindingInfo.getCurCollege())) {
					collegeBindingInfo.setCurCollegeStr((curCollegeStr));
				} else {
					curCollegeCode = collegeBindingInfo.getCurCollege();
					if (Hash_curCollege.get(curCollegeCode) != null) {
						curCollegeStr = Hash_curCollege.get(curCollegeCode)
								.toString();
						collegeBindingInfo.setCurCollegeStr(curCollegeStr);
					} else {
						collegeBindingInfo.setCurCollegeStr("");
					}
				}

			}

			String studentTypeCode = "";
			String studentTypeStr = "";
			String curstudentType=collegeBindingInfo.getStudentType();
			if(curstudentType!=null)
				curstudentType=curstudentType.trim();
			if (!"".equals(curstudentType)) {// 学生类型
				if (studentTypeCode.equals(curstudentType)) {
					collegeBindingInfo.setStudentTypeStr(studentTypeStr);
					collegeBindingInfo.setStudentType(curstudentType);
				} else {
					studentTypeCode = curstudentType;
					if (Hash_studentType.get(studentTypeCode) != null) {
						studentTypeStr = Hash_studentType.get(studentTypeCode)
								.toString();
						collegeBindingInfo.setStudentTypeStr(studentTypeStr);
						collegeBindingInfo.setStudentType(curstudentType);
					} else {
						collegeBindingInfo.setStudentTypeStr("");
					}
				}

			}
			String sexCode = "";
			String sexStr = "";
			if (!"".equals(collegeBindingInfo.getSex())) {// 性别
				if (sexCode.equals(collegeBindingInfo.getSex())) {
					collegeBindingInfo.setSexStr(sexStr);
				} else {
					sexCode = collegeBindingInfo.getSex();
					if (Hash_sex.get(sexCode) != null) {
						sexStr = Hash_sex.get(sexCode).toString();
						collegeBindingInfo.setSexStr(sexStr);
					} else {
						collegeBindingInfo.setSexStr("");
					}
				}
			}

		}
		return entitys;
	}

	public List getSpecialityList() {
		List ret = null;
		ret = yxGraduateDAO.getSpecialityList();
		Comparator comp2 = new Comparator() {
			public int compare(Object o1, Object o2) {
				Dictionary m1 = (Dictionary) o1;
				Dictionary m2 = (Dictionary) o2;
				Collator col = Collator.getInstance(Locale.CHINA);
				String stuName1 = (String) m1.getDictCaption();
				String stuName2 = (String) m2.getDictCaption();
				CollationKey c1 = col.getCollationKey(stuName1);
				CollationKey c2 = col.getCollationKey(stuName2);
				return c1.compareTo(c2);
			}
		};
		Collections.sort(ret, comp2);	
		return ret;
	}

	public List getTypeList() {
		List ret = null;
		ret = yxGraduateDAO.getTypeList();
		return ret;
	}

	public List getGraduatesList(YxGraduate graduate, String[] args) {
		String graduateNo = graduate.getGraduateNo();
		String graduateName = graduate.getGraduateName();
		String sex = graduate.getSex();
		String matriculateType = graduate.getMatriculateType();
		String studentType = graduate.getStudentType();
		String curCollege = graduate.getCurCollege();
		String speciality = graduate.getSpeciality();
		String lengthofschool = args[4];
		String graduateType = graduate.getGraduateType();

		String startfrom = args[0];
		String page = args[1];
		String stuemp_no = args[5];
		String graduateNoSearch1 = args[2];
		String graduateNoSearch2 = args[3];	

		// String datebuf = sdf1.format(new Date());//查询当前年份的班级

		List entitys = null;

//		String hqlStr = "select a from YxGraduate a where "
//		+"a.enrollYear='"+ DateUtil.getNow("yyyy") + "' ";
		
		String hqlStr = "select distinct a from YxGraduate a ,TabSsManager c where "
				+ "(a.distriction=c.tabSsDept.id and c.stuNo='"
				+ stuemp_no
				+ "' or a.distriction is null or a.distriction='') and  "
				+"a.enrollYear='"+ DateUtil.getNow("yyyy") + "' ";
		
		MyQuery myQuery = new MyQuery();
		if (startfrom != null && !"".equals(startfrom)) {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		} else {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		}		
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch1) ? " and a.graduateNo >= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch2) ? " and a.graduateNo <= ?"
				: "");			

		hqlStr += (StringUtils.isNotEmpty(graduateName) ? " and a.graduateName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(sex) ? " and a.sex = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(matriculateType) ? " and a.matriculateType = ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(studentType) ? " and a.studentType = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(curCollege) ? " and a.curCollege = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(speciality) ? " and a.speciality = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(lengthofschool) ? " and a.lengthofschool = ?" : "");		
		
		if(graduateType!=null&&!"".equals(graduateType)){
			if(graduateType.equals("NULL")){
				hqlStr +=" and a.graduateType = ''";
			}else{
				hqlStr +=" and a.graduateType = ?";
			}
		}

		if (startfrom != null && !"".equals(startfrom)) {
			int start = Integer.parseInt(startfrom);
			String prix = "";
			for (int i = 1; i < start; i++) {
				prix += "_";
			}
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara(prix + graduateNo + "%", Types.VARCHAR);
			}
		} else {
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara("%" + graduateNo + "%", Types.VARCHAR);
			}
		}
		
		if (StringUtils.isNotEmpty(graduateNoSearch1)) {
			myQuery.addPara(graduateNoSearch1, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(graduateNoSearch2)) {
			myQuery.addPara(graduateNoSearch2, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(graduateName)) {
			myQuery.addPara("%" + graduateName + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(sex)) {
			myQuery.addPara(sex, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(matriculateType)) {
			myQuery.addPara(matriculateType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentType)) {
			myQuery.addPara(studentType, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(curCollege)) {
			myQuery.addPara(curCollege, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(speciality)) {
			myQuery.addPara(speciality, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(lengthofschool)) {
			myQuery.addPara(lengthofschool,Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(graduateType)&&!"NULL".equals(graduateType)&&!"".equals(graduateType)) {
			myQuery.addPara(graduateType,Types.VARCHAR);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setPageSize(100);
		myQuery.setOrderby(" order by a.graduateNo ");
		myQuery.setQueryString(hqlStr);
		myQuery.setOffset(true);
		entitys = yxGraduateDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			YxGraduate yxgraduate = (YxGraduate) entitys.get(i);
			if (yxgraduate.getSex() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getSex()
								+ "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setSex(Cap);
				}
			}
			if (yxgraduate.getStudentType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 15 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getStudentType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setStudentType(Cap);
				}
			}
			if (yxgraduate.getMatriculateType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 16 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getMatriculateType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setMatriculateType(Cap);
				}
			}

			if (yxgraduate.getCurCollege() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.deptName from Department a where a.deptCode= '"
								+ yxgraduate.getCurCollege() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setCurCollege(Cap);
				}
			}
			if (yxgraduate.getSpeciality() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 28 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getSpeciality() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setSpeciality(Cap);
				}
			}
			if (yxgraduate.getGraduateType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.graduateType from GraduateType a where "
								+ "a.id='" + yxgraduate.getGraduateType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setGraduateType(Cap);
				}
			}
		}
		return entitys;

	}

	public Integer getGraduatesListCount(YxGraduate graduate, String[] args) {
		String graduateNo = graduate.getGraduateNo();
		String graduateName = graduate.getGraduateName();
		String matriculateType = graduate.getMatriculateType();
		String studentType = graduate.getStudentType();
		String curCollege = graduate.getCurCollege();
		String speciality = graduate.getSpeciality();
		String lengthofschool = args[4];
		String graduateType = graduate.getGraduateType();
		String stuemp_no = args[5];
		String startfrom = args[0];
		String page = args[1];
		String sex = graduate.getSex();
		String graduateNoSearch1 = args[2];
		String graduateNoSearch2 = args[3];	

		// String datebuf = sdf1.format(new Date());//查询当前年份的班级

		List entitys = null;

		String hqlStr = " select count(distinct a) from YxGraduate a,TabSsManager c where"
		+ "(a.distriction=c.tabSsDept.id and c.stuNo='"
		+ stuemp_no
		+ "' or a.distriction is null or a.distriction = '') and  "
		+"a.enrollYear='"+ DateUtil.getNow("yyyy") + "' ";
		MyQuery myQuery = new MyQuery();
		
		if (startfrom != null && !"".equals(startfrom)) {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		} else {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		}
		
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch1) ? " and a.graduateNo >= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch2) ? " and a.graduateNo <= ?"
				: "");			
		hqlStr += (StringUtils.isNotEmpty(graduateName) ? " and a.graduateName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(sex) ? " and a.sex = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(matriculateType) ? " and a.matriculateType = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(studentType) ? " and a.studentType = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(curCollege) ? " and a.curCollege = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(speciality) ? " and a.speciality = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(lengthofschool) ? " and a.lengthofschool = ?" : "");
		
		if(graduateType!=null&&!graduateType.equals("")){
			if(graduateType.equals("NULL")){
				hqlStr +=" and a.graduateType = ''";
			}else{
				hqlStr +=" and a.graduateType = ?";
			}
		}

		
		if (startfrom != null && !"".equals(startfrom)) {
			int start = Integer.parseInt(startfrom);
			String prix = "";
			for (int i = 1; i < start; i++) {
				prix += "_";
			}
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara(prix + graduateNo + "%", Types.VARCHAR);
			}
		} else {
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara("%" + graduateNo + "%", Types.VARCHAR);
			}
		}
		
		if (StringUtils.isNotEmpty(graduateNoSearch1)) {
			myQuery.addPara(graduateNoSearch1, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(graduateNoSearch2)) {
			myQuery.addPara(graduateNoSearch2, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(graduateName)) {
			myQuery.addPara("%" + graduateName + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(sex)) {
			myQuery.addPara(sex, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(matriculateType)) {
			myQuery.addPara(matriculateType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentType)) {
			myQuery.addPara(studentType, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(curCollege)) {
			myQuery.addPara(curCollege, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(speciality)) {
			myQuery.addPara(speciality, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(lengthofschool)) {
			myQuery.addPara(lengthofschool,Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(graduateType)&&!"NULL".equals(graduateType)&&!"".equals(graduateType)) {
			myQuery.addPara(graduateType,Types.VARCHAR);
		}
		myQuery.setQueryString(hqlStr.toString());
		entitys = yxGraduateDAO.find(myQuery);

		Integer entitysCount = new Integer("0");
		if (entitys != null) {
			entitysCount = (Integer) entitys.get(0);
		}
		return entitysCount;

	}

	public boolean updateGraduates(String[] deleteX, String[] args) {
		String newGraduateType = args[0];
		String newlengthofschool = args[1];
		int n = 0;
		if (deleteX != null) {
			for (int i = 0; i < deleteX.length; i++) {
				YxGraduate yxGraduate = yxGraduateDAO.get(deleteX[i]);
				if (newGraduateType != null) {
					yxGraduate.setGraduateType(newGraduateType);
					n++;
				}
				if (newlengthofschool != null && !"".equals(newlengthofschool)) {
					yxGraduate.setLengthofschool(Double
							.parseDouble(newlengthofschool));
					n++;
				}
				if(n>0){
					yxGraduate.setUpdateDate(DateUtil.getNow("yyyyMMdd"));
					yxGraduate.setUpdateTime(DateUtil.getNow("HHmmss"));
					yxGraduateDAO.update(yxGraduate);
				}
			}
		}
		return true;
	}

	public List getGraduateResidentsList(YxGraduate graduate, String[] args) {
		String graduateNo = graduate.getGraduateNo();
		String graduateName = graduate.getGraduateName();
		String matriculateType = graduate.getMatriculateType();
		String studentType = graduate.getStudentType();
		String curCollege = graduate.getCurCollege();
		String speciality = graduate.getSpeciality();
		String distriction = graduate.getDistriction();
		String graduateType = graduate.getGraduateType();
		String requestAvailable = graduate.getRequestAvailable();		
		String sex = graduate.getSex();
		String startfrom = args[0];
		String page = args[1];
		String stuemp_no = args[2];
		String graduateNoSearch1 = args[3];
		String graduateNoSearch2 = args[4];	
		String lengthofschool1 = args[5];		
		// String datebuf = sdf1.format(new Date());//查询当前年份的班级
		List entitys = null;

		String hqlStr = "select distinct a from YxGraduate a,TabSsManager c where "
				+ "(a.distriction=c.tabSsDept.id and c.stuNo='"
				+ stuemp_no
				+ "' or a.distriction is null or a.distriction='') and  a.enrollYear='"
				+ DateUtil.getNow("yyyy") + "' ";
		
		MyQuery myQuery = new MyQuery();
		if (startfrom != null && !"".equals(startfrom)) {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		} else {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		}
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch1) ? " and a.graduateNo >= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch2) ? " and a.graduateNo <= ?"
				: "");		
		hqlStr += (StringUtils.isNotEmpty(graduateName) ? " and a.graduateName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(sex) ? " and a.sex = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(matriculateType) ? " and a.matriculateType = ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(studentType) ? " and a.studentType = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(curCollege) ? " and a.curCollege = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(speciality) ? " and a.speciality = ?"
				: "");
//		hqlStr += (lengthofschool > 0 ? " and a.lengthofschool = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(lengthofschool1) ? " and a.lengthofschool = ?"
				: "");		
		if(graduateType!=null&&!graduateType.equals("")){
			if(graduateType.equals("NULL")){
				hqlStr +=" and a.graduateType = ''";
			}else{
				hqlStr +=" and a.graduateType = ?";
			}
		}
		hqlStr += (StringUtils.isNotEmpty(distriction) ? " and a.distriction = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(requestAvailable) ? " and a.requestAvailable = ?"
				: "");		

		if (startfrom != null && !"".equals(startfrom)) {
			int start = Integer.parseInt(startfrom);
			String prix = "";
			for (int i = 1; i < start; i++) {
				prix += "_";
			}
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara(prix + graduateNo + "%", Types.VARCHAR);
			}
		} else {
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara("%" + graduateNo + "%", Types.VARCHAR);
			}
		}
		
		if (StringUtils.isNotEmpty(graduateNoSearch1)) {
			myQuery.addPara(graduateNoSearch1, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(graduateNoSearch2)) {
			myQuery.addPara(graduateNoSearch2, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(graduateName)) {
			myQuery.addPara("%" + graduateName + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(sex)) {
			myQuery.addPara(sex, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(matriculateType)) {
			myQuery.addPara(matriculateType, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(studentType)) {
			myQuery.addPara(studentType, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(curCollege)) {
			myQuery.addPara(curCollege, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(speciality)) {
			myQuery.addPara(speciality, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(lengthofschool1)) {
			myQuery.addPara(new Double(Double.parseDouble(lengthofschool1)), Types.DOUBLE);
		}
//		if (lengthofschool > 0) {
//			myQuery.addPara(Double.valueOf(String.valueOf(lengthofschool)),
//					Types.DOUBLE);
//		}
		if (StringUtils.isNotEmpty(graduateType)&&!"NULL".equals(graduateType)&&!"".equals(graduateType)) {
			myQuery.addPara(graduateType,Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(distriction)) {
			myQuery.addPara(distriction, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(requestAvailable)) {
			myQuery.addPara(requestAvailable, Types.VARCHAR);
		}
		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setPageSize(100);
		myQuery.setOrderby(" order by a.graduateNo ");
		myQuery.setQueryString(hqlStr);
		myQuery.setOffset(true);
		entitys = yxGraduateDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			YxGraduate yxgraduate = (YxGraduate) entitys.get(i);
			if (yxgraduate.getSex() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getSex()
								+ "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setSex(Cap);
				}
			}
			if (yxgraduate.getStudentType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 15 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getStudentType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setStudentType(Cap);
				}
			}
			if (yxgraduate.getMatriculateType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 16 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getMatriculateType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setMatriculateType(Cap);
				}
			}

			if (yxgraduate.getCurCollege() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.deptName from Department a where a.deptCode= '"
								+ yxgraduate.getCurCollege() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setCurCollege(Cap);
				}
			}

			if (yxgraduate.getSpeciality() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 28 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getSpeciality() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setSpeciality(Cap);
				}
			}
			if (yxgraduate.getGraduateType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.graduateType from GraduateType a where "
								+ "a.id='" + yxgraduate.getGraduateType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setGraduateType(Cap);
				}
			}

			if (yxgraduate.getDistriction() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.name from TabSsDept a where a.id='"
								+ yxgraduate.getDistriction() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setDistriction(Cap);
				}
			}

			if (yxgraduate.getRequestAvailable() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 19 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getRequestAvailable() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setRequestAvailable(Cap);
				}
			}
		}

		return entitys;

	}
	
	public List getGraduateResidentsExport(YxGraduate graduate, String[] args)
	throws BusinessException {
		String graduateNo = graduate.getGraduateNo();
		String graduateName = graduate.getGraduateName();
		String matriculateType = graduate.getMatriculateType();
		String studentType = graduate.getStudentType();
		String curCollege = graduate.getCurCollege();
		String speciality = graduate.getSpeciality();
		String distriction = graduate.getDistriction();
		String graduateType = graduate.getGraduateType();
		String requestAvailable = graduate.getRequestAvailable();		
		String sex = graduate.getSex();
		String startfrom = args[0];
		String stuemp_no = args[2];
		String graduateNoSearch1 = args[3];
		String graduateNoSearch2 = args[4];		
		String lengthofschool1 = args[5];	
		// String datebuf = sdf1.format(new Date());//查询当前年份的班级
		List entitys = null;

		String hqlStr = "select distinct a from YxGraduate a,TabSsManager c where "
				+ "(a.distriction=c.tabSsDept.id and c.stuNo='"
				+ stuemp_no
				+ "' or a.distriction is null or a.distriction='') and  a.enrollYear='"
				+ DateUtil.getNow("yyyy") + "' ";
		
		MyQuery myQuery = new MyQuery();
		if (startfrom != null && !"".equals(startfrom)) {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		} else {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		}
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch1) ? " and a.graduateNo >= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch2) ? " and a.graduateNo <= ?"
				: "");		
		hqlStr += (StringUtils.isNotEmpty(graduateName) ? " and a.graduateName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(sex) ? " and a.sex = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(matriculateType) ? " and a.matriculateType = ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(studentType) ? " and a.studentType = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(curCollege) ? " and a.curCollege = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(speciality) ? " and a.speciality = ?"
				: "");
//		hqlStr += (lengthofschool > 0 ? " and a.lengthofschool = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(lengthofschool1) ? " and a.lengthofschool = ?"
				: "");		
		if(graduateType!=null&&!graduateType.equals("")){
			if(graduateType.equals("NULL")){
				hqlStr +=" and a.graduateType = ''";
			}else{
				hqlStr +=" and a.graduateType = ?";
			}
		}
		hqlStr += (StringUtils.isNotEmpty(distriction) ? " and a.distriction = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(requestAvailable) ? " and a.requestAvailable = ?"
				: "");	

		if (startfrom != null && !"".equals(startfrom)) {
			int start = Integer.parseInt(startfrom);
			String prix = "";
			for (int i = 1; i < start; i++) {
				prix += "_";
			}
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara(prix + graduateNo + "%", Types.VARCHAR);
			}
		} else {
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara("%" + graduateNo + "%", Types.VARCHAR);
			}
		}
		
		if (StringUtils.isNotEmpty(graduateNoSearch1)) {
			myQuery.addPara(graduateNoSearch1, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(graduateNoSearch2)) {
			myQuery.addPara(graduateNoSearch2, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(graduateName)) {
			myQuery.addPara("%" + graduateName + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(sex)) {
			myQuery.addPara(sex, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(matriculateType)) {
			myQuery.addPara(matriculateType, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(studentType)) {
			myQuery.addPara(studentType, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(curCollege)) {
			myQuery.addPara(curCollege, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(speciality)) {
			myQuery.addPara(speciality, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(lengthofschool1)) {
			myQuery.addPara(new Double(Double.parseDouble(lengthofschool1)), Types.DOUBLE);
		}
//		if (lengthofschool > 0) {
//			myQuery.addPara(Double.valueOf(String.valueOf(lengthofschool)),
//					Types.DOUBLE);
//		}
		if (StringUtils.isNotEmpty(graduateType)&&!"NULL".equals(graduateType)&&!"".equals(graduateType)) {
			myQuery.addPara(graduateType,Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(distriction)) {
			myQuery.addPara(distriction, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(requestAvailable)) {
			myQuery.addPara(requestAvailable, Types.VARCHAR);
		}

//		if (StringUtils.isNumeric(page)) {
//			myQuery.setPageStartNo(Integer.parseInt(page));
//		} else {
//			myQuery.setPageStartNo(0);
//		}
		myQuery.setPageStartNo(0);
//		myQuery.setPageSize(100);
		myQuery.setOrderby(" order by a.graduateNo ");
		myQuery.setQueryString(hqlStr);
//		myQuery.setOffset(true);
		entitys = yxGraduateDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			YxGraduate yxgraduate = (YxGraduate) entitys.get(i);
			if (yxgraduate.getSex() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getSex()
								+ "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setSex(Cap);
				}
			}
			if (yxgraduate.getStudentType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 15 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getStudentType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setStudentType(Cap);
				}
			}
			if (yxgraduate.getMatriculateType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 16 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getMatriculateType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setMatriculateType(Cap);
				}
			}

			if (yxgraduate.getCurCollege() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.deptName from Department a where a.deptCode= '"
								+ yxgraduate.getCurCollege() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setCurCollege(Cap);
				}
			}

			if (yxgraduate.getSpeciality() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 28 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getSpeciality() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setSpeciality(Cap);
				}
			}
			if (yxgraduate.getGraduateType() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.graduateType from GraduateType a where "
								+ "a.id='" + yxgraduate.getGraduateType() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setGraduateType(Cap);
				}
			}

			if (yxgraduate.getDistriction() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.name from TabSsDept a where a.id='"
								+ yxgraduate.getDistriction() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setDistriction(Cap);
				}
			}

			if (yxgraduate.getRequestAvailable() != null) {
				List cap_list = yxGraduateDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 19 "
								+ "and a.id.dictValue='"
								+ yxgraduate.getRequestAvailable() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					yxgraduate.setRequestAvailable(Cap);
				}
			}
		}

		return entitys;
		}

	public Integer getGraduateResidentsListCount(YxGraduate graduate,
			String[] args) {
		String graduateNo = graduate.getGraduateNo();
		String graduateName = graduate.getGraduateName();
		String matriculateType = graduate.getMatriculateType();
		String studentType = graduate.getStudentType();
		String curCollege = graduate.getCurCollege();
		String speciality = graduate.getSpeciality();
		String distriction = graduate.getDistriction();
//		double lengthofschool = graduate.getLengthofschool();
		String graduateType = graduate.getGraduateType();
		String requestAvailable = graduate.getRequestAvailable();				

		String startfrom = args[0];
		String sex = graduate.getSex();
		String stuemp_no = args[2];
		String graduateNoSearch1 = args[3];
		String graduateNoSearch2 = args[4];	
		String lengthofschool1 = args[5];	

		// String datebuf = sdf1.format(new Date());//查询当前年份的班级

		List entitys = null;

		String hqlStr = "select count(distinct a) from YxGraduate a,TabSsManager c where "
				+ "(a.distriction=c.tabSsDept.id and c.stuNo='"
				+ stuemp_no
				+ "' or a.distriction is null or a.distriction = '') and  a.enrollYear='"
				+ DateUtil.getNow("yyyy") + "' ";

		MyQuery myQuery = new MyQuery();
		if (startfrom != null && !"".equals(startfrom)) {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		} else {
			hqlStr += (StringUtils.isNotEmpty(graduateNo) ? " and a.graduateNo like ?"
					: "");
		}
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch1) ? " and a.graduateNo >= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(graduateNoSearch2) ? " and a.graduateNo <= ?"
				: "");		
		hqlStr += (StringUtils.isNotEmpty(graduateName) ? " and a.graduateName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(sex) ? " and a.sex = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(matriculateType) ? " and a.matriculateType = ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(studentType) ? " and a.studentType = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(curCollege) ? " and a.curCollege = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(speciality) ? " and a.speciality = ?"
				: "");
//		hqlStr += (lengthofschool > 0 ? " and a.lengthofschool = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(lengthofschool1) ? " and a.lengthofschool = ?"
				: "");		
		if(graduateType!=null&&!graduateType.equals("")){
			if(graduateType.equals("NULL")){
				hqlStr +=" and a.graduateType = ''";
			}else{
				hqlStr +=" and a.graduateType = ?";
			}
		}
		hqlStr += (StringUtils.isNotEmpty(distriction) ? " and a.distriction = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(requestAvailable) ? " and a.requestAvailable = ?"
				: "");	
		if (startfrom != null && !"".equals(startfrom)) {
			int start = Integer.parseInt(startfrom);
			String prix = "";
			for (int i = 1; i < start; i++) {
				prix += "_";
			}
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara(prix + graduateNo + "%", Types.VARCHAR);
			}
		} else {
			if (StringUtils.isNotEmpty(graduateNo)) {
				myQuery.addPara("%" + graduateNo + "%", Types.VARCHAR);
			}
		}
		
		if (StringUtils.isNotEmpty(graduateNoSearch1)) {
			myQuery.addPara(graduateNoSearch1, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(graduateNoSearch2)) {
			myQuery.addPara(graduateNoSearch2, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(graduateName)) {
			myQuery.addPara("%" + graduateName + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(sex)) {
			myQuery.addPara(sex, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(matriculateType)) {
			myQuery.addPara(matriculateType, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(studentType)) {
			myQuery.addPara(studentType, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(curCollege)) {
			myQuery.addPara(curCollege, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(speciality)) {
			myQuery.addPara(speciality, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(lengthofschool1)) {
			myQuery.addPara(new Double(Double.parseDouble(lengthofschool1)), Types.DOUBLE);
		}
//		if (lengthofschool > 0) {
//			myQuery.addPara(Double.valueOf(String.valueOf(lengthofschool)),
//					Types.DOUBLE);
//		}
		if (StringUtils.isNotEmpty(graduateType)&&!"NULL".equals(graduateType)&&!"".equals(graduateType)) {
			myQuery.addPara(graduateType,Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(distriction)) {
			myQuery.addPara(distriction, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(requestAvailable)) {
			myQuery.addPara(requestAvailable, Types.VARCHAR);
		}
//		if (lengthofschool > 0) {
//			myQuery.addPara(Double.valueOf(String.valueOf(lengthofschool)),
//					Types.DOUBLE);
//		}

		myQuery.setQueryString(hqlStr);
		entitys = yxGraduateDAO.find(myQuery);

		Integer entitysCount = new Integer("0");
		if (entitys != null) {
			entitysCount = (Integer) entitys.get(0);
		}

		return entitysCount;

	}

	public boolean updateGraduateResidents(String[] deleteX, String[] args,HttpServletRequest request) {
		String newdistriction = args[0];
		String newrequestavailable = args[1];
		if (deleteX != null) {
			String alertShow = "";

			for (int i = 0; i < deleteX.length; i++) {
				
				YxGraduate yx = yxGraduateDAO.get(deleteX[i]);
			
				if(yx.getResidentNeed()==null||yx.getResidentNeed().equals("2")){
					yx.setDistriction(newdistriction);
					if(!newrequestavailable.equals("")){
						yx.setRequestAvailable(newrequestavailable);				
					}
					yx.setRegisterTime(DateUtil.getNow("yyyy-MM-dd HH:mm"));
					yxGraduateDAO.update(yx);
				}else{
					alertShow+=yx.getGraduateName()+",";
				}
				
				
			}
			if(alertShow.length()>0)
			    request.setAttribute("alertShow", alertShow.substring(0, alertShow.length()-1));
		}

		return true;
	}

	public List getTabssdeptList(String stuemp_no) {
		List ret = null;
		ret = yxGraduateDAO.getTabssdeptList(stuemp_no);
		return ret;
	}

	public List getDistrictionList() {
		List ret = null;
		ret = yxGraduateDAO.getDistrictionList();
		return ret;
	}

	public List getRequestavailableList() {
		List ret = null;
		ret = yxGraduateDAO.getRequestavailableList();
		return ret;
	}

	public List getSexList() {
		List ret = null;
		ret = yxGraduateDAO.getSexList();
		return ret;
	}

	public List getSectionList() {
		List ret = null;
		ret = yxGraduateDAO.getSectionList();
		return ret;
	}

	public List getBuildingList() {
		List ret = null;
		ret = yxGraduateDAO.getBuildingList();
		return ret;
	}

	public List getLayerList() {
		List ret = null;
		ret = yxGraduateDAO.getLayerList();
		return ret;
	}

	public List getCellList() {
		List ret = null;
		ret = yxGraduateDAO.getCellList();
		return ret;
	}

	public boolean updateDormitory(String[] temp, String[] untemp,
			String stuemp_no) throws DormitoryHasStuException, Exception {

		try {
			List list = yxGraduateDAO
					.find("select a.dormitoryId from YxGraduate a"
							+ ",TabSsManager b where a.distriction=b.tabSsDept.id "
							+ "and b.stuNo='"
							+ stuemp_no
							+ "' and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and a.requestAvailable='1' and a.residentNeed='1'"
							+ "and a.dormitoryId<>'' and a.dormitoryId is not null ");
			String dromStr = "";
			for (int i = 0; i < list.size(); i++) {
				dromStr += list.get(i).toString() + ",";
			}
			String dormitoryId = "";
			String classId = "";
			String disturbuteNum = "0";
			List area_list = yxGraduateDAO
					.find("from Dictionary a where a.id.dictNo= 17 ");
			List location_list = yxGraduateDAO
					.find("from Dictionary a where a.id.dictNo= 20 ");
			List dormitory_list = yxGraduateDAO
					.find("from Dictionary a where a.id.dictNo= 21 ");

			List dormitorymodels = dormitorymodelDAO
					.find("select a from Dormitorymodel a,TabSsManager c "
							+ "where a.curDormDept=c.tabSsDept.id "
							+ "and c.stuNo='" + stuemp_no
							+ "' and a.distributeNum>0 ");

			if (null != untemp) {
				for (int i = 0; i < untemp.length; i++) {
					if (i % 11 == 0) {
						// dormitoryId
						dormitoryId = untemp[i];
						if ("".equals(dormitoryId)) {
							i = i + 10;
							continue;
						}
						if (dromStr.indexOf(dormitoryId) != -1) {
							// 宿舍有学生
							Dormitorymodel dormm = dormitorymodelDAO
									.get(dormitoryId);

							if (!"".equals(dormm.getArea())) {// 校区
								String area = "";
								String Cap = "";
								for (int k = 0; k < area_list.size(); k++) {
									Dictionary dictionary = (Dictionary) area_list
											.get(k);
									area = dictionary.getId().getDictValue();
									if (area.equals(dormm.getArea())) {
										Cap = dictionary.getDictCaption();
										break;
									}
								}
								dormm.setArea(Cap);

							}

							if (!"".equals(dormm.getLocation())) {// 区域
								String location = "";
								String Cap = "";
								for (int k = 0; k < location_list.size(); k++) {
									Dictionary dictionary = (Dictionary) location_list
											.get(k);
									location = dictionary.getId()
											.getDictValue();
									if (location.equals(dormm.getLocation())) {
										Cap = dictionary.getDictCaption();
										break;
									}
								}
								dormm.setLocation(Cap);

							}

							if (!"".equals(dormm.getDormitory())) {// 楼号
								String dormitory = "";
								String Cap = "";
								for (int k = 0; k < dormitory_list.size(); k++) {
									Dictionary dictionary = (Dictionary) dormitory_list
											.get(k);
									dormitory = dictionary.getId()
											.getDictValue();
									if (dormitory.equals(dormm.getDormitory())) {
										Cap = dictionary.getDictCaption();
										break;
									}
								}
								dormm.setDormitory(Cap);
							}

							throw new DormitoryHasStuException(dormm.getArea()
									+ dormm.getLocation()
									+ dormm.getDormitory()
									+ dormm.getRoomNumber());
						}
						// 删除这个宿舍的绑定记录
						// ClassDorm classdorm = new ClassDorm();
						// classdorm.setDormId(dormitoryId);
						// yxGraduateDAO.deleteClassDorm(classdorm);
					}
				}
			}
			// 全删
			List delclassdorm = dormitorymodelDAO
					.find("select a from ClassDorm a,Dormitorymodel b,TabSsManager c "
							+ "where a.dormId=b.dormitoryId and b.curDormDept=c.tabSsDept.id "
							+ "and c.stuNo='"
							+ stuemp_no
							+ "' and a.sex is not null and a.studentType is not null and a.curYear='"
							+ DateUtil.getNow("yyyy") + "'");
			for (int j = 0; j < delclassdorm.size(); j++) {
				yxGraduateDAO.deleteClassDorm((ClassDorm) delclassdorm.get(j));
			}

			for (int i = 0; i < dormitorymodels.size(); i++) {
				Dormitorymodel model = (Dormitorymodel) dormitorymodels.get(i);
				model.setEmptyNum(model.getDistributeNum());
				dormitorymodelDAO.update(model);
			}

			if (null != temp) {
				for (int i = 0; i < temp.length; i++) {
					if (i % 11 == 0) {
						// dormitoryId
						dormitoryId = temp[i];
						if ("".equals(dormitoryId)) {
							i = i + 10;
							continue;
						}
						disturbuteNum = temp[i + 5];
						classId = temp[i + 8];
						i = i + 8;
						// ClassDorm classdormtodel = new ClassDorm();
						// classdormtodel.setDormId(dormitoryId);
						// yxGraduateDAO.deleteClassDorm(classdormtodel);

						ClassDorm classdorm = new ClassDorm();
						classdorm.setClassId(classId.substring(0, classId
								.indexOf("-")));
						classdorm.setDormId(dormitoryId);
						classdorm.setDistributeNum(Integer
								.valueOf(disturbuteNum));
						classdorm.setStudentType(classId.substring(classId
								.lastIndexOf("-") + 1));
						classdorm.setSex(classId.substring(
								classId.indexOf("-") + 1, classId
										.lastIndexOf("-")));
						classdorm.setCurYear(DateUtil.getNow("yyyy"));
						yxGraduateDAO.saveClassDorm(classdorm);
						Dormitorymodel dormitorymodel = (Dormitorymodel) dormitorymodelDAO
								.get(dormitoryId);
						dormitorymodel.setEmptyNum(dormitorymodel.getEmptyNum()
								- Integer.parseInt(disturbuteNum));
						dormitorymodelDAO.update(dormitorymodel);
					}
				}
			}
		} catch (HibernateException e) {
			// TODO: handle exception
			e.printStackTrace();
			throw new Exception(e.getMessage());
		}

		return true;
	}

	public void saveDormDistribution(String stuemp_no)
			throws DormitoryNotEnoughException, StudentAlreadyInDormException,
			Exception {
		
		List managerdeptList=yxGraduateDAO.find("select a.tabSsDept.id from TabSsManager a where a.stuNo='"+stuemp_no+"' and a.inOffice=1 ");
		
	    String curDept="";
	        
	    if(managerdeptList!=null&&managerdeptList.size()>0)
	        curDept=(String)managerdeptList.get(0);
	    else{
	    	throw new Exception("no right");
	    }
	    
	    int ageline=32;
		int curyear=Integer.parseInt(DateUtil.getNow("yyyy"));
		
		List agelineli=yxGraduateDAO.find(" select a.id.dictValue from Dictionary a where a.id.dictNo=30 ");
		if(agelineli!=null&&agelineli.size()>0){
			ageline=Integer.parseInt((String)agelineli.get(0));
		}
		
		String birthdayline=String.valueOf(curyear-ageline);
		
		List noList = yxGraduateDAO
				.find("from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ " and a.requestAvailable='1' and a.residentNeed='1' and a.dormitoryId<>'' and a.dormitoryId is not null");
		if (noList != null && noList.size() > 0) {
			throw new StudentAlreadyInDormException(
					"student already in dormitory");
		}
		List collegeList = yxGraduateDAO
				.find("select distinct a.curCollege from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' or a.residentNeed='1'");

		for (int i = 0; i < collegeList.size(); i++) {
			String curCollege = collegeList.get(i).toString();
			List MBoyStudent = yxGraduateDAO
					.find("select a.id from YxGraduate a,TabSsManager b where a.distriction=b.tabSsDept.id "
							+ "and b.stuNo='"
							+ stuemp_no
							+ "' and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ " and a.sex='1' and a.curCollege='"
							+ curCollege
							+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.studentType='M' "
							+ "order by a.speciality,a.lengthofschool,a.graduateNo");

			List MGirlStudent = yxGraduateDAO
					.find("select a.id from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
							+ "and b.stuNo='"
							+ stuemp_no
							+ "' and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.sex='2' and a.curCollege='"
							+ curCollege
							+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.studentType='M' "
							+ "order by a.speciality,a.lengthofschool,a.graduateNo");
            
			List DBoyStudent =new ArrayList();
			List DGirlStudent=new ArrayList();
			
			if(curDept.equals("8a708026132402840113240ad4710003")){//西苑				
				
			    List DBoyStudentold = yxGraduateDAO
					.find("select a.id from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
							+ "and b.stuNo='"
							+ stuemp_no
							+ "' and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.sex='1' and a.curCollege='"
							+ curCollege
							+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.studentType='D' and a.birthday<'"+birthdayline+"' "
							+ " order by a.lengthofschool,a.graduateNo");
			    
			    List DBoyStudentyoung = yxGraduateDAO
				.find("select a.id from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.sex='1' and a.curCollege='"
						+ curCollege
						+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.studentType='D' and (a.birthday is null or a.birthday='' or a.birthday>'"+birthdayline+"') "
						+ " order by a.lengthofschool,a.graduateNo");
			    
			    if(DBoyStudentold!=null&&DBoyStudentold.size()>0){
			    	for(int k=0;k<DBoyStudentold.size();k++){
			    		String oldid=(String)DBoyStudentold.get(k);
			    		DBoyStudent.add(oldid);
			    	}
			    }
			    if(DBoyStudentyoung!=null&&DBoyStudentyoung.size()>0){
			    	for(int k=0;k<DBoyStudentyoung.size();k++){
			    		String youngid=(String)DBoyStudentyoung.get(k);
			    		DBoyStudent.add(youngid);		    		
			    	}
			    }

			    List DGirlStudentold = yxGraduateDAO
					.find("select a.id from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
							+ "and b.stuNo='"
							+ stuemp_no
							+ "' and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.sex='2' and a.curCollege='"
							+ curCollege
							+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.studentType='D' and a.birthday<'"+birthdayline+"' "
							+ "order by a.lengthofschool,a.graduateNo");
			    
			    List DGirlStudentyoung = yxGraduateDAO
				.find("select a.id from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.sex='2' and a.curCollege='"
						+ curCollege
						+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.studentType='D' and (a.birthday is null or a.birthday='' or a.birthday>'"+birthdayline+"') "
						+ "order by a.lengthofschool,a.graduateNo");
			    
			    if(DGirlStudentold!=null&&DGirlStudentold.size()>0){
			    	for(int k=0;k<DGirlStudentold.size();k++){
			    		String oldid=(String)DGirlStudentold.get(k);
			    		DGirlStudent.add(oldid);
			    	}
			    }
			    if(DGirlStudentyoung!=null&&DGirlStudentyoung.size()>0){
			    	for(int k=0;k<DGirlStudentyoung.size();k++){
			    		String youngid=(String)DGirlStudentyoung.get(k);
			    		DGirlStudent.add(youngid);
			    	}
			    }
			    
			}
			else{//北区等
				DBoyStudent = yxGraduateDAO
				.find("select a.id from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.sex='1' and a.curCollege='"
						+ curCollege
						+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.studentType='D' "
						+ "order by a.speciality,a.lengthofschool,a.graduateNo");

		       DGirlStudent = yxGraduateDAO
				.find("select a.id from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.sex='2' and a.curCollege='"
						+ curCollege
						+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.studentType='D' "
						+ "order by a.speciality,a.lengthofschool,a.graduateNo");
			}
			
			List MBoyDorm = yxGraduateDAO
					.find("select new org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo("
							+ "a.dormitoryId,'','','','','','','','','','','',''"
							+ ",'',a.gender,'',b.distributeNum,'',b.classId) "
							+ "from Dormitorymodel a,ClassDorm b,TabSsManager c"
							+ " where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
							+ "and c.stuNo='"
							+ stuemp_no
							+ "' and b.curYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and b.sex='1' and b.classId='"
							+ curCollege
							+ "' and b.studentType='M' ");

			List MGirlDorm = yxGraduateDAO
					.find("select new org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo("
							+ "a.dormitoryId,'','','','','','','','','','','',''"
							+ ",'',a.gender,'',b.distributeNum,'',b.classId) "
							+ "from Dormitorymodel a,ClassDorm b ,TabSsManager c"
							+ " where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
							+ "and c.stuNo='"
							+ stuemp_no
							+ "' and b.curYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and b.sex='2' and b.classId='"
							+ curCollege
							+ "' and b.studentType='M' ");
			List DBoyDorm = yxGraduateDAO
					.find("select new org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo("
							+ "a.dormitoryId,'','','','','','','','','','','',''"
							+ ",'',a.gender,'',b.distributeNum,'',b.classId) "
							+ "from Dormitorymodel a,ClassDorm b ,TabSsManager c"
							+ " where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
							+ "and c.stuNo='"
							+ stuemp_no
							+ "' and b.curYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and b.sex='1' and b.classId='"
							+ curCollege
							+ "' and b.studentType='D' ");

			List DGirlDorm = yxGraduateDAO
					.find("select new org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo("
							+ "a.dormitoryId,'','','','','','','','','','','',''"
							+ ",'',a.gender,'',b.distributeNum,'',b.classId) "
							+ "from Dormitorymodel a,ClassDorm b ,TabSsManager c"
							+ " where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
							+ "and c.stuNo='"
							+ stuemp_no
							+ "' and b.curYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and b.sex='2' and b.classId='"
							+ curCollege
							+ "' and b.studentType='D' ");
			String MboyIds = "";
			String MgirlIds = "";
			if (MBoyStudent.size() > 0) {
				int boyCount = MBoyStudent.size();
				for (int j = 0; j < boyCount; j++) {
					if (j == boyCount - 1) {
						MboyIds += MBoyStudent.get(j).toString();
					} else {
						MboyIds += MBoyStudent.get(j).toString() + ",";
					}
				}
				try {
					DistributionTest(MboyIds, MBoyDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}

			}
			if (MGirlStudent.size() > 0) {
				int girlCount = MGirlStudent.size();
				for (int j = 0; j < girlCount; j++) {
					if (j == girlCount - 1) {
						MgirlIds += MGirlStudent.get(j).toString();
					} else {
						MgirlIds += MGirlStudent.get(j).toString() + ",";
					}
				}
				try {
					DistributionTest(MgirlIds, MGirlDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}

			}
			String DboyIds = "";
			String DgirlIds = "";
			if (DBoyStudent.size() > 0) {
				int boyCount = DBoyStudent.size();
				for (int j = 0; j < boyCount; j++) {
					if (j == boyCount - 1) {
						DboyIds += DBoyStudent.get(j).toString();
					} else {
						DboyIds += DBoyStudent.get(j).toString() + ",";
					}
				}
				try {
					DistributionTest(DboyIds, DBoyDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}

			}
			if (DGirlStudent.size() > 0) {
				int girlCount = DGirlStudent.size();
				for (int j = 0; j < girlCount; j++) {
					if (j == girlCount - 1) {
						DgirlIds += DGirlStudent.get(j).toString();
					} else {
						DgirlIds += DGirlStudent.get(j).toString() + ",";
					}
				}
				try {
					DistributionTest(DgirlIds, DGirlDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}

			}

			if (MBoyStudent.size() > 0) {

				try {
					Distribution(MboyIds, MBoyDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}
			}

			if (MGirlStudent.size() > 0) {
				try {
					Distribution(MgirlIds, MGirlDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}
			}

			if (DBoyStudent.size() > 0) {
				try {
					Distribution(DboyIds, DBoyDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}
			}

			if (DGirlStudent.size() > 0) {
				try {
					Distribution(DgirlIds, DGirlDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}
			}

		}

	}

	private void Distribution(String StudentIds, List dorms)
			throws DormitoryNotEnoughException, Exception {

		String[][] dormitoryArr = new String[dorms.size()][10];
		int[] distributeNum = new int[dorms.size()];
		String[] studentArr = StudentIds.split(",");

		for (int l = 0; l < dorms.size(); l++) {
			YangongDormitoryBindInfo yangongDormitoryBindInfo = (YangongDormitoryBindInfo) dorms
					.get(l);
			dormitoryArr[l][0] = yangongDormitoryBindInfo.getDormitoryId();
			for (int m = 1; m < dormitoryArr[l].length; m++) {
				dormitoryArr[l][m] = "";
			}
			distributeNum[l] = yangongDormitoryBindInfo.getEmptyNum();
		}

		int stu_index = 0;
		for (int i = 0; i < dormitoryArr.length; i++) {
			for (int j = 1; j <= distributeNum[i]; j++) {
				if (stu_index >= studentArr.length) {
					break;
				}
				dormitoryArr[i][j] = studentArr[stu_index];
				stu_index++;
			}
		}
		if (stu_index < studentArr.length) {
			throw new DormitoryNotEnoughException("dormitory maybe not enough!");
		}

		// 更新数据到数据库
		// 保存分宿舍结果
		String dormitoryId = "";
		for (int l = 0; l < dormitoryArr.length; l++) {
			dormitoryId = dormitoryArr[l][0];
			for (int m = 1; m < dormitoryArr[l].length; m++) {
				if (!"".equals(dormitoryArr[l][m])) {
					YxGraduate yxgraduate = yxGraduateDAO
							.get(dormitoryArr[l][m]);
					if (null != yxgraduate) {
						yxgraduate.setDormitoryId(dormitoryId);
						yxGraduateDAO.update(yxgraduate);
					}
				}

			}
		}

	}

	private void DistributionTest(String StudentIds, List dorms)
			throws DormitoryNotEnoughException, Exception {

		String[][] dormitoryArr = new String[dorms.size()][10];
		int[] distributeNum = new int[dorms.size()];
		String[] studentArr = StudentIds.split(",");

		for (int l = 0; l < dorms.size(); l++) {
			YangongDormitoryBindInfo yangongDormitoryBindInfo = (YangongDormitoryBindInfo) dorms
					.get(l);
			dormitoryArr[l][0] = yangongDormitoryBindInfo.getDormitoryId();
			for (int m = 1; m < dormitoryArr[l].length; m++) {
				dormitoryArr[l][m] = "";
			}
			distributeNum[l] = yangongDormitoryBindInfo.getEmptyNum();
		}

		int stu_index = 0;
		for (int i = 0; i < dormitoryArr.length; i++) {
			for (int j = 1; j <= distributeNum[i]; j++) {
				if (stu_index >= studentArr.length) {
					break;
				}
				dormitoryArr[i][j] = studentArr[stu_index];
				stu_index++;
			}
		}
		if (stu_index < studentArr.length) {
			throw new DormitoryNotEnoughException("dormitory maybe not enough!");
		}
	}

	public List getCollegeStudentCount(String stuemp_no) {
		List list = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"
						+ "(a.curCollege,'',count(a.graduateNo),0,0,0,0) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' "
						+ "group by a.curCollege ");
		List mmaleList = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"
						+ "(a.curCollege,a.studentType,0,count(a.graduateNo),0,0,0) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' and a.sex='1' and a.studentType='M' "
						+ "group by a.curCollege,a.studentType ");
		List mfemaleList = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"
						+ "(a.curCollege,a.studentType,0,0,count(a.graduateNo),0,0) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' and a.sex='2' and a.studentType='M' "
						+ "group by a.curCollege,a.studentType ");

		List dmaleList = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"
						+ "(a.curCollege,a.studentType,0,0,0,count(a.graduateNo),0) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' and a.sex='1' and a.studentType='D' "
						+ "group by a.curCollege,a.studentType ");
		List dfemaleList = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"
						+ "(a.curCollege,a.studentType,0,0,0,0,count(a.graduateNo)) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' and a.sex='2' and a.studentType='D' "
						+ "group by a.curCollege,a.studentType ");
		int MMale = 0;
		int MFemale = 0;
		int DMale = 0;
		int DFemale = 0;
		int allSum = 0;
		for (int i = 0; i < list.size(); i++) {
			CollegeWithStuCount collegeWithStuCount = (CollegeWithStuCount) list
					.get(i);
			for (int j = 0; j < mmaleList.size(); j++) {
				CollegeWithStuCount male = (CollegeWithStuCount) mmaleList
						.get(j);
				String majorinmale = male.getCollegeCode();
				if (majorinmale.equals(collegeWithStuCount.getCollegeCode())) {
					collegeWithStuCount.setYjsMaleCount(male.getYjsMaleCount());
					mmaleList.remove(j);
					break;
				}
			}
			for (int k = 0; k < mfemaleList.size(); k++) {
				CollegeWithStuCount female = (CollegeWithStuCount) mfemaleList
						.get(k);
				String majorinfemale = female.getCollegeCode();
				if (majorinfemale.equals(collegeWithStuCount.getCollegeCode())) {
					collegeWithStuCount.setYjsFemaleCount(female
							.getYjsFemaleCount());
					mfemaleList.remove(k);
					break;
				}
			}

			for (int j = 0; j < dmaleList.size(); j++) {
				CollegeWithStuCount male = (CollegeWithStuCount) dmaleList
						.get(j);
				String majorinmale = male.getCollegeCode();
				if (majorinmale.equals(collegeWithStuCount.getCollegeCode())) {
					collegeWithStuCount.setBsMaleCount(male.getBsMaleCount());
					dmaleList.remove(j);
					break;
				}
			}
			for (int k = 0; k < dfemaleList.size(); k++) {
				CollegeWithStuCount female = (CollegeWithStuCount) dfemaleList
						.get(k);
				String majorinfemale = female.getCollegeCode();
				if (majorinfemale.equals(collegeWithStuCount.getCollegeCode())) {
					collegeWithStuCount.setBsFemaleCount(female
							.getBsFemaleCount());
					dfemaleList.remove(k);
					break;
				}

			}

			MMale += collegeWithStuCount.getYjsMaleCount();
			MFemale += collegeWithStuCount.getYjsFemaleCount();
			DMale += collegeWithStuCount.getBsMaleCount();
			DFemale += collegeWithStuCount.getBsFemaleCount();
			allSum += collegeWithStuCount.getStuCount();
			if (i == list.size() - 1) {
				CollegeWithStuCount addstu = new CollegeWithStuCount(
						"allCount", "all", 0, 0, 0, 0, 0);
				addstu.setStuCount(allSum);
				addstu.setBsFemaleCount(DFemale);
				addstu.setBsMaleCount(DMale);
				addstu.setYjsFemaleCount(MFemale);
				addstu.setYjsMaleCount(MMale);
				list.add(i + 1, addstu);
				break;
			}
		}
		return list;
	}

	public List getCollegeDormitoryStatistic(String stuemp_no) {
		List list_all = dormitorymodelDAO
				.find("select new map(tt.id.curCollege as collegeId,sum(tt.id.distributeNum) as accomodation, '10' as flag) "
						+ " from collegedormss tt,TabSsManager b where tt.id.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and tt.id.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' " + "group by tt.id.curCollege");
		List list_mmale = dormitorymodelDAO
				.find("select new map(tt.id.curCollege as collegeId,sum(tt.id.distributeNum) as accomodation, '11' as flag) "
						+ "from collegedormss tt ,TabSsManager b where tt.id.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and tt.id.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and tt.id.studentType='M' and tt.id.sex='1' "
						+ " group by tt.id.curCollege");
		List list_mfemale = dormitorymodelDAO
				.find("select new map(tt.id.curCollege as collegeId,sum(tt.id.distributeNum) as accomodation, '12' as flag) "
						+ "from collegedormss tt ,TabSsManager b where tt.id.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and tt.id.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and tt.id.studentType='M' and tt.id.sex='2' "
						+ " group by tt.id.curCollege");

		List list_dmale = dormitorymodelDAO
				.find("select new map(tt.id.curCollege as collegeId,sum(tt.id.distributeNum) as accomodation, '13' as flag) "
						+ "from collegedormss tt ,TabSsManager b where tt.id.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and tt.id.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and tt.id.studentType='D' and tt.id.sex='1' "
						+ " group by tt.id.curCollege");
		List list_dfemale = dormitorymodelDAO
				.find("select new map(tt.id.curCollege as collegeId,sum(tt.id.distributeNum) as accomodation, '14' as flag) "
						+ "from collegedormss tt,TabSsManager b where tt.id.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and tt.id.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and tt.id.studentType='D' and tt.id.sex='2' "
						+ " group by tt.id.curCollege");
		int MMale = 0;
		int MFemale = 0;
		int DMale = 0;
		int DFemale = 0;
		int allSum = 0;
		for (int i = 0; i < list_mmale.size(); i++) {
			Map dormWithStuCount = (Map) list_mmale.get(i);
			MMale+=Integer.parseInt(dormWithStuCount.get("accomodation").toString());
		}
		for (int i = 0; i < list_mfemale.size(); i++) {
			Map dormWithStuCount = (Map) list_mfemale.get(i);
			MFemale+=Integer.parseInt(dormWithStuCount.get("accomodation").toString());
		}
		for (int i = 0; i < list_dmale.size(); i++) {
			Map dormWithStuCount = (Map) list_dmale.get(i);
			DMale+=Integer.parseInt(dormWithStuCount.get("accomodation").toString());
		}
		for (int i = 0; i < list_dfemale.size(); i++) {
			Map dormWithStuCount = (Map) list_dfemale.get(i);
			DFemale+=Integer.parseInt(dormWithStuCount.get("accomodation").toString());
		}
		for (int i = 0; i < list_all.size(); i++) {
			Map dormWithStuCount = (Map) list_all.get(i);
			allSum+=Integer.parseInt(dormWithStuCount.get("accomodation").toString());
		}
		HashMap allmap = new HashMap();
		allmap.put("collegeId", "dormallCount");
		allmap.put("accomodation", String.valueOf(allSum));
		allmap.put("flag", "10");
		HashMap MMaleMap =  new HashMap();
		MMaleMap.put("collegeId", "dormallCount");
		MMaleMap.put("accomodation", String.valueOf(MMale));
		MMaleMap.put("flag", "11");
		HashMap MFemaleMap =  new HashMap();
		MFemaleMap.put("collegeId", "dormallCount");
		MFemaleMap.put("accomodation", String.valueOf(MFemale));
		MFemaleMap.put("flag", "12");
		HashMap DMaleMap =  new HashMap();
		DMaleMap.put("collegeId", "dormallCount");
		DMaleMap.put("accomodation", String.valueOf(DMale));
		DMaleMap.put("flag", "13");
		HashMap DFemaleMap =  new HashMap();
		DFemaleMap.put("collegeId", "dormallCount");
		DFemaleMap.put("accomodation", String.valueOf(DFemale));
		DFemaleMap.put("flag", "14");
		list_all.add(allmap);
		list_all.add(MMaleMap);
		list_all.add(MFemaleMap);
		list_all.add(DMaleMap);
		list_all.add(DFemaleMap);
		
		if (list_all.size() > 0) {
			if (list_mmale.size() > 0) {
				list_all.addAll(list_mmale);
			}
			if (list_mfemale.size() > 0) {
				list_all.addAll(list_mfemale);
			}
			if (list_dmale.size() > 0) {
				list_all.addAll(list_dmale);
			}
			if (list_dfemale.size() > 0) {
				list_all.addAll(list_dfemale);
			}
		}
		return list_all;
	}

	public String getGraduateCount(String stuemp_no) {
		List list = yxGraduateDAO
				.find("select count(a.graduateNo) from YxGraduate a,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and a.requestAvailable='1' and a.residentNeed='1' and a.dormitoryId<>'' and a.dormitoryId is not null ");
		return list.get(0).toString();
	}

	public List getGraduateListByDorm(String operator) {
		// TODO Auto-generated method stub
		return (List)yxGraduateDAO.find("select distinct a from YxGraduate a,TabSsManager b " +
				"where b.tabSsDept.id=a.distriction and b.stuNo='"+operator+"' and a.dormitoryId is not null and a.dormitoryId<>'' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "'");
	}
	public List getGzListByDorm(String operator) {
		// TODO Auto-generated method stub
		return (List)yxGraduateDAO.find("select distinct a from Studentmodel a " +
				"where a.dormId is not null and a.dormId<>'' and a.majorin='623' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "'");
	}
	public List getSxList(String stuemp_no) {
		String curYear = DateUtil.getNow("yyyy");
		List templist = yxGraduateDAO.find(" select new Map(a.requestAvailable as requestAvailable, " +
				"a.studentType as studentType, " +
				"a.sex as sex, " +
				"count(a.graduateNo) as graduateCount) " +
				"from YxGraduate a,TabSsManager b " +
				"where a.distriction=b.tabSsDept.id " +
				"and b.stuNo='"+stuemp_no+"' "+
				"and a.enrollYear='"+curYear+"' "+
				"and a.requestAvailable='1' " +
				"group by a.requestAvailable,a.studentType,a.sex " +
				"order by a.requestAvailable,a.studentType,a.sex ");
		List sxlist = new ArrayList();
		SxTJ sxtj = new SxTJ();
		sxtj.setState("可申请");
		sxtj.setType("");
		for(int i=0;i<templist.size();i++){
			((Map)templist.get(i)).put("studentType", ((Map)templist.get(i)).get("studentType").toString().trim());
			if("D".equals(((Map)templist.get(i)).get("studentType"))){
				if("1".equals(((Map)templist.get(i)).get("sex"))){
					if((((Map)templist.get(i)).get("graduateCount")).toString()!=null)					
						sxtj.setDmale((((Map)templist.get(i)).get("graduateCount")).toString());
					else
						sxtj.setDmale("0");
				}else{
					if((((Map)templist.get(i)).get("graduateCount")).toString()!=null)
						sxtj.setDfemale((((Map)templist.get(i)).get("graduateCount")).toString());
					else
						sxtj.setDfemale("0");
				}
			}else{
				if("1".equals(((Map)templist.get(i)).get("sex"))){
					if((((Map)templist.get(i)).get("graduateCount")).toString()!=null)					
						sxtj.setMmale((((Map)templist.get(i)).get("graduateCount")).toString());
					else
						sxtj.setMmale("0");
				}else{
					if((((Map)templist.get(i)).get("graduateCount")).toString()!=null)
						sxtj.setMfemale((((Map)templist.get(i)).get("graduateCount")).toString());
					else
						sxtj.setMfemale("0");
				}
			}
		}
		sxlist.add(sxtj);
		int i = 0;
		List countlist = yxGraduateDAO.find(" select " +
				"distinct a.graduateType " +
				"from YxGraduate a " +
				"where " +
				"a.requestAvailable='2' " +
				"and a.enrollYear='"+curYear+"' ");
		SxTJ[] sxTJs = new SxTJ[countlist.size()]; 
		for(int m=0;m<countlist.size();m++){
			sxTJs[m] = new SxTJ();
		}
		templist = yxGraduateDAO.find(" select new Map(a.requestAvailable as requestAvailable, " +
				"a.graduateType as graduateType, " +
				"a.studentType as studentType, " +
				"a.sex as sex, " +
				"count(a.graduateNo) as graduateCount) " +
				"from YxGraduate a " +
				"where " +
				"a.requestAvailable='2' " +
				"and a.enrollYear='"+curYear+"' "+
				"group by a.requestAvailable,a.graduateType,a.studentType,a.sex " +
				"order by a.requestAvailable,a.graduateType,a.studentType,a.sex ");
		for(int k1=0;k1<templist.size();k1++){
			
			((Map)templist.get(k1)).put("requestAvailable", "不可申请");		
			
			if ((((Map)templist.get(k1)).get("graduateType"))!= null&&
					!"".equals((((Map)templist.get(k1)).get("graduateType")).toString())) {
				List cap_list = yxGraduateDAO
						.find("select a.graduateType from GraduateType a where a.ifdeleted='1' and a.id='"
								+ (((Map)templist.get(k1)).get("graduateType")).toString() + "'");
				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					((Map)templist.get(k1)).put("graduateType", Cap);
				}
			}
		}
		if(templist!=null&&templist.size()>0){
			((Map)templist.get(0)).put("studentType", ((Map)templist.get(0)).get("studentType").toString().trim());
			sxTJs[i].setState((((Map)templist.get(0)).get("requestAvailable")).toString());
			if(((Map)templist.get(0)).get("graduateType")!=null){
				sxTJs[i].setType((((Map)templist.get(0)).get("graduateType")).toString());
			}
			if("D".equals(((Map)templist.get(0)).get("studentType"))){
				if("1".equals(((Map)templist.get(0)).get("sex"))){
					if((((Map)templist.get(0)).get("graduateCount")).toString()!=null)					
						sxTJs[i].setDmale((((Map)templist.get(0)).get("graduateCount")).toString());
					else
						sxTJs[i].setDmale("0");
				}else{
					if((((Map)templist.get(0)).get("graduateCount")).toString()!=null)
						sxTJs[i].setDfemale((((Map)templist.get(0)).get("graduateCount")).toString());
					else
						sxTJs[i].setDfemale("0");
				}
			}else{
				if("1".equals(((Map)templist.get(0)).get("sex"))){
					if((((Map)templist.get(0)).get("graduateCount")).toString()!=null)					
						sxTJs[i].setMmale((((Map)templist.get(0)).get("graduateCount")).toString());
					else
						sxTJs[i].setMmale("0");
				}else{
					if((((Map)templist.get(0)).get("graduateCount")).toString()!=null)
						sxTJs[i].setMfemale((((Map)templist.get(0)).get("graduateCount")).toString());
					else
						sxTJs[i].setMfemale("0");
				}
			}
		}
		for(int k=1;k<templist.size();k++){
			((Map)templist.get(k)).put("studentType", ((Map)templist.get(k)).get("studentType").toString().trim());
			if(!(sxTJs[i].getType()).equals((((Map)templist.get(k)).get("graduateType")))){
				i++;
			}
			sxTJs[i].setState((((Map)templist.get(k)).get("requestAvailable")).toString());
			if(((Map)templist.get(k)).get("graduateType")!=null){
				sxTJs[i].setType((((Map)templist.get(k)).get("graduateType")).toString());
			}

		
			if("D".equals(((Map)templist.get(k)).get("studentType"))){
				if("1".equals(((Map)templist.get(k)).get("sex"))){
					if((((Map)templist.get(k)).get("graduateCount")).toString()!=null)					
						sxTJs[i].setDmale((((Map)templist.get(k)).get("graduateCount")).toString());
					else
						sxTJs[i].setDmale("0");
				}else{
					if((((Map)templist.get(k)).get("graduateCount")).toString()!=null)
						sxTJs[i].setDfemale((((Map)templist.get(k)).get("graduateCount")).toString());
					else
						sxTJs[i].setDfemale("0");
				}
			}else{
				if("1".equals(((Map)templist.get(k)).get("sex"))){
					if((((Map)templist.get(k)).get("graduateCount")).toString()!=null)					
						sxTJs[i].setMmale((((Map)templist.get(k)).get("graduateCount")).toString());
					else
						sxTJs[i].setMmale("0");
				}else{
					if((((Map)templist.get(k)).get("graduateCount")).toString()!=null)
						sxTJs[i].setMfemale((((Map)templist.get(k)).get("graduateCount")).toString());
					else
						sxTJs[i].setMfemale("0");
				}
			}
	}
		for(int n=0;n<sxTJs.length;n++){
			sxlist.add(sxTJs[n]);
		}
		return sxlist;
	}

	public List getCanreqList(String stuemp_no) {
		List canreqlist = new ArrayList();
		List collegeList = getCollegeListFromGraduateTable();
		int i = 0;
		List countlist = yxGraduateDAO.find(" select " +
				"distinct new Map(a.distriction,a.curCollege) " +
				"from YxGraduate a,TabSsManager b " +
				"where a.distriction=b.tabSsDept.id " +
				"and b.stuNo='"+stuemp_no+"' "+
				"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' and a.requestAvailable='1' ");
		
		CanReqTJ[] canreqtjs = new CanReqTJ[countlist.size()];
		for(int m=0;m<countlist.size();m++){
			canreqtjs[m] = new CanReqTJ();
		}
		List templist = yxGraduateDAO.find(" select new Map(a.requestAvailable as requestAvailable,a.distriction as distriction,a.curCollege as curCollege," +
				"a.studentType as studentType, " +
				"a.sex as sex, " +
				"count(a.graduateNo) as graduateCount,c.gsort) " +
				"from YxGraduate a,TabSsManager b,Department c " +
				"where a.distriction=b.tabSsDept.id " +
				"and b.stuNo='"+stuemp_no+"' "+
				"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' and a.requestAvailable='1' " +
				"and a.curCollege=c.deptCode " +
				"group by a.requestAvailable,a.distriction,a.curCollege,a.studentType,a.sex,c.gsort " +
				"order by c.gsort ");
		
		for(int k1=0;k1<templist.size();k1++){
			if ((((Map)templist.get(k1)).get("distriction")).toString()!= null) {
				List cap_list = yxGraduateDAO
						.find("select a.name from TabSsDept a where a.id='"
								+ (((Map)templist.get(k1)).get("distriction")).toString() + "'");
				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					((Map)templist.get(k1)).put("distriction", Cap);						
				}
			}
			if ((((Map)templist.get(k1)).get("curCollege")).toString()!= null) {
				List cap_list = yxGraduateDAO
						.find("select a.deptName from Department a where a.deptCode= '"
								+ (((Map)templist.get(k1)).get("curCollege")).toString() + "'");
				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					((Map)templist.get(k1)).put("curCollege", Cap);
				}
			}
		}
		
		if(templist!=null&&templist.size()>0){
			canreqtjs[i].setDistrict((((Map)templist.get(0)).get("distriction")).toString());
			
			canreqtjs[i].setCurCollege((((Map)templist.get(0)).get("curCollege")).toString());
			
			((Map)templist.get(0)).put("studentType", ((Map)templist.get(0)).get("studentType").toString().trim());
			
			if("D".equals(((Map)templist.get(0)).get("studentType"))){
				if("1".equals(((Map)templist.get(0)).get("sex"))){
					if((((Map)templist.get(0)).get("graduateCount")).toString()!=null)					
						canreqtjs[i].setDmale((((Map)templist.get(0)).get("graduateCount")).toString());
					else
						canreqtjs[i].setDmale("0");
				}else{
					if((((Map)templist.get(0)).get("graduateCount")).toString()!=null)
						canreqtjs[i].setDfemale((((Map)templist.get(0)).get("graduateCount")).toString());
					else
						canreqtjs[i].setDfemale("0");
				}
			}else{
				if("1".equals(((Map)templist.get(0)).get("sex"))){
					if((((Map)templist.get(0)).get("graduateCount")).toString()!=null)					
						canreqtjs[i].setMmale((((Map)templist.get(0)).get("graduateCount")).toString());
					else
						canreqtjs[i].setMmale("0");
				}else{
					if((((Map)templist.get(0)).get("graduateCount")).toString()!=null)
						canreqtjs[i].setMfemale((((Map)templist.get(0)).get("graduateCount")).toString());
					else
						canreqtjs[i].setMfemale("0");
				}
			}
		}
		for(int k=1;k<templist.size();k++){
			((Map)templist.get(k)).put("studentType", ((Map)templist.get(k)).get("studentType").toString().trim());
				if(!(canreqtjs[i].getDistrict()).equals((((Map)templist.get(k)).get("distriction")).toString())||
						!(canreqtjs[i].getCurCollege()).equals((((Map)templist.get(k)).get("curCollege")).toString())){
					i++;
				}

				canreqtjs[i].setDistrict((((Map)templist.get(k)).get("distriction")).toString());

				canreqtjs[i].setCurCollege((((Map)templist.get(k)).get("curCollege")).toString());
			
				if("D".equals(((Map)templist.get(k)).get("studentType"))){
					if("1".equals(((Map)templist.get(k)).get("sex"))){
						if((((Map)templist.get(k)).get("graduateCount")).toString()!=null)					
							canreqtjs[i].setDmale((((Map)templist.get(k)).get("graduateCount")).toString());
						else
							canreqtjs[i].setDmale("0");
					}else{
						if((((Map)templist.get(k)).get("graduateCount")).toString()!=null)
							canreqtjs[i].setDfemale((((Map)templist.get(k)).get("graduateCount")).toString());
						else
							canreqtjs[i].setDfemale("0");
					}
				}else{
					if("1".equals(((Map)templist.get(k)).get("sex"))){
						if((((Map)templist.get(k)).get("graduateCount")).toString()!=null)					
							canreqtjs[i].setMmale((((Map)templist.get(k)).get("graduateCount")).toString());
						else
							canreqtjs[i].setMmale("0");
					}else{
						if((((Map)templist.get(k)).get("graduateCount")).toString()!=null)
							canreqtjs[i].setMfemale((((Map)templist.get(k)).get("graduateCount")).toString());
						else
							canreqtjs[i].setMfemale("0");
					}
				}
		}
		for(int n=0;n<canreqtjs.length;n++){
			canreqlist.add(canreqtjs[n]);
		}
		return canreqlist;
	}

}
