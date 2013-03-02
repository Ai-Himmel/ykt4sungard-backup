/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StudentServiceImpl.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-30     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.service.impl;

import java.io.IOException;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.sql.Types;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.king.checkinmanage.dao.StuCardfeeInfoDAO;
import org.king.checkinmanage.dao.StuCardfeeSubmitDAO;
import org.king.checkinmanage.dao.StuarchivesinfoDAO;
import org.king.checkinmanage.dao.StucheckininfoDAO;
import org.king.checkinmanage.dao.StuhealthinfoDAO;
import org.king.checkinmanage.domain.StuCardfeeInfo;
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.classmanage.dao.ClassmodelDAO;
import org.king.classmanage.dao.DepartmentDAO;
import org.king.classmanage.dao.StuAdddelhisDAO;
import org.king.classmanage.dao.StudentmodelDAO;
import org.king.classmanage.domain.ClassAlertHis;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Department;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.GzStuTemp;
import org.king.classmanage.domain.StuAdddelhis;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.exception.EnterenceNoNotExistException;
import org.king.classmanage.exception.FamilyAddressNotExistException;
import org.king.classmanage.exception.MakeStuNoFailException;
import org.king.classmanage.exception.StuNameNotExistException;
import org.king.classmanage.exception.TotalScoreNotExistException;
import org.king.classmanage.service.StudentService;
import org.king.classmanage.web.help.AbroadStuInfo;
import org.king.classmanage.web.help.ClassWithManager;
import org.king.classmanage.web.help.MajorinInfo;
import org.king.classmanage.web.help.MajorinWithStuCount;
import org.king.classmanage.web.help.StudentWithAllInfo;
import org.king.dormitorymanage.dao.DormitorymodelDAO;
import org.king.dormitorymanage.domain.DormAlerthis;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.dormitorymanage.exception.DormitoryNotExistException;
import org.king.dormitorymanage.exception.GenderNotExistException;
import org.king.dormitorymanage.exception.LocationNotExistException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.security.dao.AccountDAO;
import org.king.security.dao.RoleDAO;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.security.domain.Role;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.dao.YxGraduateDAO;
import org.king.yangong.dormitorymanage.domain.YxGraduate;
import org.springframework.jdbc.core.JdbcTemplate;

import com.ibm.icu.text.CollationKey;
import com.ibm.icu.text.Collator;

public class StudentServiceImpl extends BaseService implements StudentService {

	private StudentmodelDAO studentmodelDAO;

	private ClassmodelDAO classmodelDAO;

	private DormitorymodelDAO dormitorymodelDAO;

	private DepartmentDAO departmentDAO;

	private JdbcTemplate jdbcTemplate;
	
	private StuAdddelhisDAO stuAdddelhisDAO;
	private YxGraduateDAO yxGraduateDAO;
	
	private StucheckininfoDAO stucheckininfoDAO;
    private StuarchivesinfoDAO stuarchivesinfoDAO;
    private StuhealthinfoDAO stuhealthinfoDAO;
    private StuCardfeeInfoDAO stucardfeeinfoDAO;
    
    private AccountDAO accountDAO;
    private RoleDAO roleDAO;
    
	public static SimpleDateFormat sdf1 = new SimpleDateFormat("yyyy");

	/**
	 * @param accountDAO
	 *            The accountDAO to set.
	 */
	public void setYxGraduateDAO(YxGraduateDAO yxGraduateDAO) {
		this.yxGraduateDAO = yxGraduateDAO;
	}
	public void setAccountDAO(AccountDAO accountDAO) {
		this.accountDAO = accountDAO;
	}
	public void setRoleDAO(RoleDAO roleDAO) {
		this.roleDAO = roleDAO;
	}
    
    public void setStucheckininfoDAO(StucheckininfoDAO stucheckininfoDAO) {
		this.stucheckininfoDAO = stucheckininfoDAO;
	}
	
	public void setStuarchivesinfoDAO(StuarchivesinfoDAO stuarchivesinfoDAO) {
		this.stuarchivesinfoDAO = stuarchivesinfoDAO;
	}
	
	public void setStuhealthinfoDAO(StuhealthinfoDAO stuhealthinfoDAO) {
		this.stuhealthinfoDAO = stuhealthinfoDAO;
	}
	public void setStuCardfeeInfoDAO(StuCardfeeInfoDAO stucardfeeinfoDAO) {
		this.stucardfeeinfoDAO = stucardfeeinfoDAO;
	}

	/**
	 * @param departmentDAO
	 *            The departmentDAO to set.
	 */
	public void setDepartmentDAO(DepartmentDAO departmentDAO) {
		this.departmentDAO = departmentDAO;
	}

	/**
	 * @param jdbcTemplate
	 *            The jdbcTemplate to set.
	 */
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	/**
	 * @param dormitorymodelDAO
	 *            The dormitorymodelDAO to set.
	 */
	public void setDormitorymodelDAO(DormitorymodelDAO dormitorymodelDAO) {
		this.dormitorymodelDAO = dormitorymodelDAO;
	}

	/**
	 * @param studentmodelDAO
	 *            The studentmodelDAO to set.
	 */
	public void setStuAdddelhisDAO(StuAdddelhisDAO stuAdddelhisDAO) {
		this.stuAdddelhisDAO = stuAdddelhisDAO;
	}

	/**
	 * @param classmodelDAO
	 *            The classmodelDAO to set.
	 */
	public void setClassmodelDAO(ClassmodelDAO classmodelDAO) {
		this.classmodelDAO = classmodelDAO;
	}
	
	public void setStudentmodelDAO(StudentmodelDAO studentmodelDAO) {
		this.studentmodelDAO = studentmodelDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#saveStudent(org.king.classmanage.domain.Studentmodel)
	 */
	public void saveStudent(Studentmodel studentmodel) {
		// TODO Auto-generated method stub
		studentmodelDAO.save(studentmodel);
	}

	public void updateStudent(Studentmodel studentmodel) {
		studentmodelDAO.update(studentmodel);
	}

	public void updateStudentWithHis(Studentmodel studentmodel,
			ClassAlertHis classalerthis) {
		studentmodelDAO.update(studentmodel);
		studentmodelDAO.saveAlertHis(classalerthis);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#getStudent()
	 */
	public List getStudent() {
		// TODO Auto-generated method stub
//		return studentmodelDAO.getAll();
		String datebuf = sdf1.format(new Date());//当前年份
		String hql = "from org.king.classmanage.domain.Studentmodel a where a.enrollYear='"+datebuf+"' order by studentNo";
		List list = classmodelDAO.find(hql);
		return list;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#getAbroadStudent()
	 */
	public List getAbroadStudent() {
		return studentmodelDAO
				.find("select new map(a.studentId as studentId,a.studentNo as studentNo,"
						+ "a.stuName as stuName,c.dictCaption as gender,b.dictCaption as nationality,d.dictCaption as majorin) "
						+ "from Studentmodel a,Dictionary b,Dictionary c,Dictionary d "
						+ "where a.nationality=b.id.dictValue and a.gender=c.id.dictValue and a.majorin=d.id.dictValue "
						+ "and b.id.dictNo=12 and c.id.dictNo=1 and d.id.dictNo=11"
						+ " and a.nationality<>'CHN' ");
	}

	public List getAbroadStudent(String[] args) {
		String studentNo = args[0];
		String stuName = args[1];
		String nationality = args[2];
		String majorin = args[3];

		List entitys = null;

		String hqlStr = "select distinct new org.king.classmanage.web.help.AbroadStuInfo"
				+ "(a.studentId,a.studentNo,a.stuName,a.gender,a.nationality,a.majorin) "
				+ "from Studentmodel a where a.nationality<>'CHN' and (a.yxClass.classId is null or a.yxClass.classId='')";

		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nationality)) {
			myQuery.addPara(nationality, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}
		myQuery.setOrderby(" order by a.studentNo");
		myQuery.setQueryString(hqlStr);

		entitys = studentmodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			AbroadStuInfo abroadstuinfo = (AbroadStuInfo) entitys.get(i);

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(abroadstuinfo.getGender())) {// 性别
				if (genderCode.equals(abroadstuinfo.getGender())) {
					abroadstuinfo.setGender(genderStr);
				} else {
					genderCode = abroadstuinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ abroadstuinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						abroadstuinfo.setGender(genderStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(abroadstuinfo.getNationality())) {// 国籍
				if (nationalityCode.equals(abroadstuinfo.getNationality())) {
					abroadstuinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = abroadstuinfo.getNationality();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 12 "
									+ "and a.id.dictValue='"
									+ abroadstuinfo.getNationality() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationalityStr = Cap;
						abroadstuinfo.setNationality(nationalityStr);
					}
				}

			}

			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(abroadstuinfo.getMajorin())) {// 专业
				if (majorinCode.equals(abroadstuinfo.getMajorin())) {
					abroadstuinfo.setMajorin(majorinStr);
				} else {
					majorinCode = abroadstuinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ abroadstuinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						abroadstuinfo.setMajorin(majorinStr);
					}
				}

			}

		}
		return entitys;

	} /*
		 * (non-Javadoc)
		 * 
		 * @see org.king.classmanage.service.StudentService#getStudent(java.lang.String)
		 */

	public Studentmodel getStudent(String studentId) {
		return studentmodelDAO.get(studentId);
	}
	public List getStudentTempInfoByStudentNo(String studentNo) {
		return studentmodelDAO.find("select a from GzStuTemp a,Studentmodel b where " +
				"a.enterenceNo=b.enterenceNo and b.studentNo='"+studentNo+"'");
	}
	public List getStudentTempInfoByEnterenceNo(String enterenceNo) {
		return studentmodelDAO.find("from GzStuTemp where enterenceNo='"+enterenceNo+"'");		
	}
	public List getStudentbyClass(String classId) {
		return studentmodelDAO
				.find("from Studentmodel a where a.yxClass.classId='" + classId
						+ "'");

	}
	public List getStudentInfoByEnterenceNo(String enterenceNo) {
		return studentmodelDAO.find("from Studentmodel where enterenceNo='"+enterenceNo+"'");		
	}
	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#deleteStudent(java.lang.String)
	 */
	public void deleteStudent(String studentId) {
		Studentmodel studentmodel = getStudent(studentId);
		if (null != studentmodel) {
			studentmodelDAO.delete(getStudent(studentId));
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#getStudentNoDorm()
	 */
	public List getStudentNoDorm() {
		// TODO Auto-generated method stub
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#distributAbroadtoClass(java.util.List,
	 *      java.util.List)
	 */
	public void distributAbroadtoClass(String studentIds, String[] classIds) {
		// 根据studentIds得到所有学生list
		List stuList = studentmodelDAO
				.find("from Studentmodel a where a.studentId in (" + studentIds
						+ ") order by a.majorin");
		// 根据deleteX班级个数建立一个二维数组
		if (null != classIds) {
			String classIdArr[][] = new String[classIds.length][stuList.size() + 1];
			for (int i = 0; i < classIds.length; i++) {
				classIdArr[i][0] = classIds[i];
				for (int m = 1; m < classIdArr[i].length; m++) {
					classIdArr[i][m] = "";
				}
			}
			Studentmodel studentmodel_f = null;
			Studentmodel studentmodel_m = null;
			// 每个数据中依次放两个直到放完为止
			String majorin_f = "";
			String majorin_m = "";
			String majorin_l = "";
			int index = 1;
			int j = 0;
			while (j < stuList.size()) {
				for (int k = 0; k < classIdArr.length; k++) {
					if (j < stuList.size() - 1) {
						// 取两个学生
						studentmodel_f = (Studentmodel) stuList.get(j);
						studentmodel_m = (Studentmodel) stuList.get(j + 1);
						majorin_f = studentmodel_f.getMajorin() != null ? studentmodel_f
								.getMajorin()
								: "A";
						majorin_m = studentmodel_m.getMajorin() != null ? studentmodel_m
								.getMajorin()
								: "B";
						if (!majorin_f.equals(majorin_m)) {
							// 取得两个学生专业不同
							if (majorin_l.equals(majorin_f)) {
								// 与前面的相同 则加到前面班级中去
								for (int m = 0; m < classIdArr[k - 1].length; m++) {
									if ("".equals(classIdArr[k - 1][m])) {
										index = m;
										break;
									} else {
										continue;
									}
								}
								classIdArr[k - 1][index] = studentmodel_f
										.getStudentId();
								j++;
								// 记录上一次最后一个学生的专业
								majorin_l = studentmodel_f.getMajorin() != null ? studentmodel_f
										.getMajorin()
										: "C";
								continue;
							} else {
								// 与前面的不同 则自己加到一个班级中
								for (int m = 0; m < classIdArr[k].length; m++) {
									if ("".equals(classIdArr[k][m])) {
										index = m;
										break;
									} else {
										continue;
									}
								}
								classIdArr[k][index] = studentmodel_f
										.getStudentId();
								j++;
								majorin_l = studentmodel_f.getMajorin() != null ? studentmodel_f
										.getMajorin()
										: "C";
								continue;
							}
						} else {
							// 取得两个学生专业相同
							// 直接放到这个班级里去
							for (int m = 0; m < classIdArr[k].length; m++) {
								if ("".equals(classIdArr[k][m])) {
									index = m;
									break;
								} else {
									continue;
								}
							}
							classIdArr[k][index] = studentmodel_f
									.getStudentId();
							j++;
							classIdArr[k][index + 1] = studentmodel_m
									.getStudentId();
							j++;
							continue;
						}
					} else if (j == stuList.size() - 1) {
						// 只有一个学生
						studentmodel_f = (Studentmodel) stuList.get(j);
						if (majorin_l.equals(majorin_f) && (j != 0)) {
							// 与前面的相同 则加到前面班级中去
							for (int m = 0; m < classIdArr[k - 1].length; m++) {
								if ("".equals(classIdArr[k - 1][m])) {
									index = m;
									break;
								} else {
									continue;
								}
							}
							classIdArr[k - 1][index] = studentmodel_f
									.getStudentId();
							j++;
							majorin_l = studentmodel_f.getStudentId();
							break;
						} else {
							// 与前面的不同 则自己加到一个班级中
							for (int m = 0; m < classIdArr[k].length; m++) {
								if ("".equals(classIdArr[k][m])) {
									index = m;
									break;
								} else {
									continue;
								}
							}
							classIdArr[k][index] = studentmodel_f
									.getStudentId();
							j++;
							majorin_l = studentmodel_f.getMajorin() != null ? studentmodel_f
									.getMajorin()
									: "C";
							continue;
						}

					} else {
						// 没有学生了
						break;
					}
				}
			}
			String classId = "";
			// 更新到数据库中去
			for (int l = 0; l < classIdArr.length; l++) {
				classId = classIdArr[l][0];
				Classmodel classmodel = classmodelDAO.get(classId);
				for (int m = 1; m < classIdArr[l].length; m++) {
					if (!"".equals(classIdArr[l][m])) {
						Studentmodel studentmodel = studentmodelDAO
								.get(classIdArr[l][m]);
						if (null != studentmodel) {
							studentmodel.setYxClass(classmodel);
							studentmodelDAO.update(studentmodel);
						}
					}
				}
			}
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#deleteAbroadDistribution()
	 */
	public void deleteAbroadDistribution() {
		// TODO Auto-generated method stub

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#getDiction(java.lang.String)
	 */
	public List getDiction(String dicId) {
		return studentmodelDAO.find("from Dictionary a where a.id.dictNo="
				+ dicId + " order by a.id.dictValue");
	}

	public List getDepartment() {
		return departmentDAO.getAll();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#getDictionarybyParent(java.lang.String)
	 */
	public List getDictionarybyParent(String parent) {
		return studentmodelDAO
				.find("from Dictionary a where a.id.dictNo=7 and a.dictParent="
						+ parent);

	}
/**
 * 通过学生信息查院系列表
 */	
	public void findDepartments(HttpServletRequest request) {
		
		String hql = "select distinct new Map(b.deptCode as deptCode,b.deptName as deptName) " +
				"from Studentmodel a,Department b " +
				"where a.department=b.deptCode and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
		List list = studentmodelDAO.find(hql);
		request.setAttribute("departmentList", list);
		
	}
	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.StudentService#getStudent(java.lang.String[])
	 */
	public List getStudent(String[] args,String schoolId) {//查询学生基本信息
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];
		String college = args[6];
		String classes = args[7];
		String location = args[8];
		String dormitory = args[9];
		String roomnumber = args[10];
		String assistant = args[11];
		String majorin = args[12];
		String nationality = args[13];
		String page = args[14];
		String orderby = args[15];
		String odr = args[16];
		String department = args[17];
		String area = "";
		if(args.length>18){
			area = args[18];
		}
		
		String idType = "";
		String cultureMode = "";
		String studentChar = "";
		String checkornot = "";
		String schoolornot = "";	
		String enterenceNo = "";
		String idCard = "";
		if(args.length>19){
			idType = args[19];
			cultureMode = args[20];
			studentChar = args[21];
			checkornot = args[22];
			schoolornot = args[23];
			enterenceNo = args[24];
			idCard = args[25];
		}
		
//      <!-- 证件类型 -->
//      <property name="idType" type="string">
//      <!-- 培养层次 -->
//      <property name="cultureMode" type="string">
//      <!-- 学生性质 -->
//      <property name="studentChar" type="string">
//      <!-- 是否在籍 -->
//      <property name="checkornot" type="integer">
//      <!-- 是否在校 -->
//      <property name="schoolornot" type="integer">		
		boolean orderedCheck = true;
		List entitys = null;


		String hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
				+ "('',a.yxClass.classId,'','','','', "
				+ "a.studentId,a.studentNo, a.enterenceNo, ci.ifCheckedin,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
				+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
				+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
				+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,''," +
						"a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
				+ "from Studentmodel a,Stucheckininfo ci ";
		if (StringUtils.isNotEmpty(college) || StringUtils.isNotEmpty(classes)) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += ",Classmanager d,Managermodel e,Managermanagerrole f ";
		}
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)
				|| StringUtils.isNotEmpty(area)) {
			hqlStr += ",Dormitorymodel g ";
		}
		hqlStr += "where 1=1 and ci.studentNo=a.studentNo ";
//		hqlStr += "and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";	
		if(schoolId!=null&&!"".equals(schoolId)&&schoolId.equals("0002")){//护理学院
			//-------------------------------------------------
			hqlStr +=" and a.majorin='623' ";
		}else if(schoolId!=null&&!"".equals(schoolId)&&schoolId.equals("0001")){
			//-------------------------------------------------复旦学院
			hqlStr +=" and a.majorin<>'623' ";
		}
		
		hqlStr +=" and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";

		MyQuery myQuery = new MyQuery();
		
		if (StringUtils.isNotEmpty(idCard)) {
			hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?": "");
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(enterenceNo)) {

			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?": "");
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(studentNo)) {

			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?": "");
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(province)) {
			hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
					: "");
			myQuery.addPara(province, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(polity)) {
			hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");
			myQuery.addPara(polity, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?" : "");
			myQuery.addPara(department, Types.VARCHAR);
		}		
		
		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
			myQuery.addPara(majorin, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(nationality)) {
			hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
					: "");
			myQuery.addPara(nationality, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(college)) {
			myQuery.addPara(college, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(college) || StringUtils.isNotEmpty(classes)) {
			hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
			hqlStr += (StringUtils.isNotEmpty(college) ? " and c.collegeId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " and b.classId = ?"
					: "");
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}

		}


		if (StringUtils.isNotEmpty(assistant)) {
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += " and a.yxClass.classId=d.id.classId and d.id.managerId=e.managerId "
						+ " and e.managerId=f.id.managerId and f.id.roleId='21' ";
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.managerId = ?"
						: "");
			}
			myQuery.addPara(assistant, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(idType)) {
			hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
					: "");
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
					: "");
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}	
		
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)|| StringUtils.isNotEmpty(area)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(area) ? " and g.area = ? "
					: "");
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
		}	

		myQuery.setPageSize(100);

		if (orderby == null || orderby.length() == 0) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentNo ");
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("enterenceNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.enterenceNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("examNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by ci.ifCheckedin " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("gender")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.gender " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("majorin")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.majorin " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nation")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.nation " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nationality")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.nationality " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("province")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.fromProvince " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("polityBg")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.polityBg " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("birthday")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.birthday " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("homeTelephone")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.homeTelephone " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("tempecardNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.tempecardNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("department")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.department " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("idType")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.idType " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("cultureMode")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.cultureMode " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentChar")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentChar " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("checkornot")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.checkornot " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("schoolornot")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.schoolornot " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}


		else {
			orderedCheck = false;
			myQuery.setPageStartNo(0);
			myQuery.setOffset(false);
		}

		myQuery.setQueryString(hqlStr);
		entitys = studentmodelDAO.find(myQuery);
		List Temp_mng = classmodelDAO
				.find("select new map(b.id.classId as classId,c.managerName as managerName) from Classmodel a,Classmanager b,Managermodel c,Managermanagerrole d "
						+ "where a.classId=b.id.classId "
						+ "and b.id.managerId=c.managerId and c.managerId=d.id.managerId and d.id.roleId='21'");
		HashMap Hash_mng = new HashMap();
		for (int i = 0; i < Temp_mng.size(); i++) {
			HashMap temp = (HashMap) Temp_mng.get(i);
			Hash_mng.put(temp.get("classId"), temp.get("managerName"));
		}
		HashMap Hash_cls = new HashMap();
		List Temp_cls = classmodelDAO
				.find("select new map(a.classId as classId,a.classNo as classNo) from Classmodel a ");
		for (int i = 0; i < Temp_cls.size(); i++) {
			HashMap temp = (HashMap) Temp_cls.get(i);
			Hash_cls.put(temp.get("classId"), temp.get("classNo"));
		}
		HashMap Hash_col = new HashMap();
		List Temp_col = classmodelDAO
				.find("select new map(a.classId as classId,b.collegeName as collegeName) from Classmodel a,Collegemodel b"
						+ " where a.yxCollege.collegeId=b.collegeId ");
		for (int i = 0; i < Temp_col.size(); i++) {
			HashMap temp = (HashMap) Temp_col.get(i);
			Hash_col.put(temp.get("classId"), temp.get("collegeName"));
		}
		
		HashMap Hash_area = new HashMap();
		HashMap Hash_location = new HashMap();
		HashMap Hash_dormitory = new HashMap();
		HashMap Hash_roomNumber = new HashMap();

		HashMap Hash_yuanxi = new HashMap();
		List Temp_yuanxi = classmodelDAO
				.find("select new map(a.id.dictValue as majorin,b.deptName as yuanxi) from Dictionary a,Department b"
						+ " where a.id.dictNo=11 and a.dictParent=b.deptCode ");
		for (int i = 0; i < Temp_yuanxi.size(); i++) {
			HashMap temp = (HashMap) Temp_yuanxi.get(i);
			Hash_yuanxi.put(temp.get("majorin"), temp.get("yuanxi"));
		}
		
//-------------------------------------------			
		if(schoolId!=null&&schoolId.equals("0001")){			
			List list_dorm = dormitorymodelDAO
					.find("select new map(a.dormitoryId as dormitoryId,b.dictCaption as location,c.dictCaption as dormitory,a.roomNumber as roomNumber) from"
							+ " Dormitorymodel a,Dictionary b,Dictionary c where a.location=b.id.dictValue and b.id.dictNo=6 "
							+ "and a.dormitory=c.id.dictValue and c.id.dictNo=7 ");
			for (int i = 0; i < list_dorm.size(); i++) {
				HashMap temp = (HashMap) list_dorm.get(i);
				Hash_location.put(temp.get("dormitoryId"), temp.get("location"));
				Hash_dormitory.put(temp.get("dormitoryId"), temp.get("dormitory"));
				Hash_roomNumber
						.put(temp.get("dormitoryId"), temp.get("roomNumber"));
			}
		
		}else {
			List list_dorm = dormitorymodelDAO
			.find("select new map(a.dormitoryId as dormitoryId," +
					"b.dictCaption as location," +
					"c.dictCaption as dormitory," +
					"d.dictCaption as area," +
					"a.roomNumber as roomNumber) from"
					+ " Dormitorymodel a,Dictionary b,Dictionary c,Dictionary d where a.area=d.id.dictValue and d.id.dictNo=17 " +
							"and a.location=b.id.dictValue and b.id.dictNo=20 "
					+ "and a.dormitory=c.id.dictValue and c.id.dictNo=21 ");
			for (int i = 0; i < list_dorm.size(); i++) {
				HashMap temp = (HashMap) list_dorm.get(i);
				Hash_location.put(temp.get("dormitoryId"), temp.get("location"));
				Hash_dormitory.put(temp.get("dormitoryId"), temp.get("dormitory"));
				Hash_roomNumber
						.put(temp.get("dormitoryId"), temp.get("roomNumber"));
				Hash_area.put(temp.get("dormitoryId"), temp.get("area"));
			}			
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_fromprovince = new HashMap();
		List Temp_fromprovince = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 10 ");
		for (int i = 0; i < Temp_fromprovince.size(); i++) {
			HashMap temp = (HashMap) Temp_fromprovince.get(i);
			Hash_fromprovince.put(temp.get("dictValue"), temp
					.get("dictCaption"));
		}

		HashMap Hash_Nationality = new HashMap();
		List Temp_Nationality = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 12 ");
		for (int i = 0; i < Temp_Nationality.size(); i++) {
			HashMap temp = (HashMap) Temp_Nationality.get(i);
			Hash_Nationality
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_PolityBg = new HashMap();
		List Temp_PolityBg = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 4 ");
		for (int i = 0; i < Temp_PolityBg.size(); i++) {
			HashMap temp = (HashMap) Temp_PolityBg.get(i);
			Hash_PolityBg.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Majorin = new HashMap();
		List Temp_Majorin = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 11 ");
		for (int i = 0; i < Temp_Majorin.size(); i++) {
			HashMap temp = (HashMap) Temp_Majorin.get(i);
			Hash_Majorin.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Nation = new HashMap();
		List Temp_Nation = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 2 ");
		for (int i = 0; i < Temp_Nation.size(); i++) {
			HashMap temp = (HashMap) Temp_Nation.get(i);
			Hash_Nation.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Department = new HashMap();
		List Temp_Department = studentmodelDAO
				.find("select new map(a.deptCode as deptCode, a.deptName as deptName) from Department a ");
		for (int i = 0; i < Temp_Department.size(); i++) {
			HashMap temp = (HashMap) Temp_Department.get(i);
			Hash_Department.put(temp.get("deptCode"), temp.get("deptName"));
		}

		HashMap Hash_bathcardNo = new HashMap();
		List Temp_bathcardNo = studentmodelDAO
				.find("select new map(a.studentNo as studentNo,a.bathcardNo as bathcardNo)from StuCardfeeInfo a ");
		for (int i = 0; i < Temp_bathcardNo.size(); i++) {
			HashMap temp = (HashMap) Temp_bathcardNo.get(i);
			Hash_bathcardNo.put(temp.get("studentNo"), temp.get("bathcardNo"));
		}
	
		HashMap Hash_idType = new HashMap();
		List Temp_idType = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 29 ");
		for (int i = 0; i < Temp_idType.size(); i++) {
			HashMap temp = (HashMap) Temp_idType.get(i);
			Hash_idType.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_cultureMode = new HashMap();
		List Temp_cultureMode = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 26 ");
		for (int i = 0; i < Temp_cultureMode.size(); i++) {
			HashMap temp = (HashMap) Temp_cultureMode.get(i);
			Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_studentChar = new HashMap();
		List Temp_studentChar = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 27 ");
		for (int i = 0; i < Temp_studentChar.size(); i++) {
			HashMap temp = (HashMap) Temp_studentChar.get(i);
			Hash_studentChar.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
//      <!-- 证件类型 -->
//      <property name="idType" type="string">100
//      <!-- 培养层次 -->
//      <property name="cultureMode" type="string">26
//      <!-- 学生性质 -->
//      <property name="studentChar" type="string">27
//      <!-- 是否在籍 -->
//      <property name="checkornot" type="integer">
//      <!-- 是否在校 -->
//      <property name="schoolornot" type="integer">		

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			if (orderby != null
					&& orderby.length() > 0
					&& ("college".equals(orderby) || "name".equals(orderby) || "assistant"
							.equals(orderby))) {
				String clsssIdCode = "";
				String clsmanagerStr = "";
				String classIdStr = "";
				String collegeIdStr = "";
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}

			}

			if (orderby != null
					&& orderby.length() > 0
					&& ("location".equals(orderby)|| "area".equals(orderby)
							|| "dormitory".equals(orderby) || "roomNumber"
							.equals(orderby))) {
				String dromIdCode = "";
				String areaStr = "";				
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setArea(areaStr);
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
						if (Hash_area.get(dromIdCode) != null) {
							areaStr = Hash_area.get(dromIdCode)
									.toString();
							studentwithallinfo.setArea(areaStr);
						}						
					}
				}
			}

			String studentno = "";
			String deptname = "";
			if (!"".equals(studentwithallinfo.getStudentNo())) {// 淋浴卡
				studentno = studentwithallinfo.getStudentNo();
				if (Hash_bathcardNo.get(studentno) != null) {
					deptname = Hash_bathcardNo.get(studentno).toString();
					studentwithallinfo.setBathcardNo(deptname);
				}
			}

		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("college")) {
			// 书院排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0 && orderby.equals("name")) {
			// 班号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = "";
					String stuName2 = "";
					if(m1.getClassId()!=null){
						stuName1 = (String) m1.getClassId();
					}
					if(m2.getClassId()!=null){
						stuName2 = (String) m2.getClassId();
					}
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = "";
					String stuName2 = "";
					if(m1.getClassId()!=null){
						stuName1 = (String) m1.getClassId();
					}
					if(m2.getClassId()!=null){
						stuName2 = (String) m2.getClassId();
					}
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("assistant")) {
			// 辅导员排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("stuName")) {
			// 学生姓名排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}		
//----------------------------------------------------------------
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("area")) {
			// 大校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getArea();
					String stuName2 = (String) m2.getArea();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getArea();
					String stuName2 = (String) m2.getArea();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("location")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {					
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("dormitory")) {
			// 楼号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("roomNumber")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("bathcardNo")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		List subList = null;
		if (orderedCheck) {
			subList = entitys;
		} else {
			int startrow = 0;
			if (StringUtils.isNumeric(page)) {
				startrow = Integer.parseInt(page);
				if ((startrow + 100) < entitys.size()) {
					subList = entitys.subList(startrow, startrow + 100);
				} else {
					subList = entitys.subList(startrow, entitys.size());
				}
			} else {
				if ((startrow + 100) < entitys.size()) {
					subList = entitys.subList(0, 100);
				} else {
					subList = entitys.subList(0, entitys.size());
				}
			}
		}

		for (int i = 0; i < subList.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) subList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			String classIdStr = "";
			String collegeIdStr = "";
			if (!"college".equals(orderby) && !"name".equals(orderby)
					&& !"assistant".equals(orderby)) {
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}
			}
			if (!"area".equals(orderby) &&!"location".equals(orderby) && !"dormitory".equals(orderby)
					&& !"roomNumber".equals(orderby)) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				String areaStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
						studentwithallinfo.setArea(areaStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
						if (Hash_area.get(dromIdCode) != null) {
							areaStr = Hash_area.get(dromIdCode)
									.toString();
							studentwithallinfo.setArea(areaStr);
						}
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(studentwithallinfo.getGender())) {// 性别
				if (genderCode.equals(studentwithallinfo.getGender())) {
					studentwithallinfo.setGender(genderStr);
				} else {
					genderCode = studentwithallinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						studentwithallinfo.setGender(genderStr);
					}
				}

			}
			
			String idTypeCode = "";
			String idTypeStr = "";
			if (!"".equals(studentwithallinfo.getIdType())) {// 证件类型
				if (idTypeCode.equals(studentwithallinfo.getIdType())) {
					studentwithallinfo.setIdType(idTypeStr);
				} else {
					idTypeCode = studentwithallinfo.getIdType();
					if (Hash_idType.get(idTypeCode) != null) {
						idTypeStr = Hash_idType.get(idTypeCode).toString();
						studentwithallinfo.setIdType(idTypeStr);
					}
				}

			}	
			
			String cultureModeCode = "";
			String cultureModeStr = "";
			if (!"".equals(studentwithallinfo.getCultureMode())) {// 证件类型
				if (cultureModeCode.equals(studentwithallinfo.getCultureMode())) {
					studentwithallinfo.setCultureMode(cultureModeStr);
				} else {
					cultureModeCode = studentwithallinfo.getCultureMode();
					if (Hash_cultureMode.get(cultureModeCode) != null) {
						cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
						studentwithallinfo.setCultureMode(cultureModeStr);
					}
				}

			}
			
			String studentCharCode = "";
			String studentCharStr = "";
			if (!"".equals(studentwithallinfo.getStudentChar())) {// 证件类型
				if (studentCharCode.equals(studentwithallinfo.getStudentChar())) {
					studentwithallinfo.setStudentChar(studentCharStr);
				} else {
					studentCharCode = studentwithallinfo.getStudentChar();
					if (Hash_studentChar.get(studentCharCode) != null) {
						studentCharStr = Hash_studentChar.get(studentCharCode).toString();
						studentwithallinfo.setStudentChar(studentCharStr);
					}
				}

			}	
			

		
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(studentwithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(studentwithallinfo
						.getFromProvince())) {
					studentwithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = studentwithallinfo.getFromProvince();
					if (Hash_fromprovince.get(fromProvinceCode) != null) {
						fromProvinceStr = Hash_fromprovince.get(
								fromProvinceCode).toString();
						studentwithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(studentwithallinfo.getNationality())) {// 国籍
				if (nationalityCode.equals(studentwithallinfo.getNationality())) {
					studentwithallinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = studentwithallinfo.getNationality();
					if (Hash_Nationality.get(nationalityCode) != null) {
						nationalityStr = Hash_Nationality.get(nationalityCode)
								.toString();
						studentwithallinfo.setNationality(nationalityStr);
					}
				}

			}
			String politybgCode = "";
			String politybgStr = "";
			if (!"".equals(studentwithallinfo.getPolityBg())) {// 政治面貌
				if (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					studentwithallinfo.setPolityBg(politybgStr);
				} else {
					politybgCode = studentwithallinfo.getPolityBg();
					if (Hash_PolityBg.get(politybgCode) != null) {
						politybgStr = Hash_PolityBg.get(politybgCode)
								.toString();
						studentwithallinfo.setPolityBg(politybgStr);
					}
				}

			}
			String deptCode = "";
			String deptStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 所属院系
				if (deptCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setDepartment(deptStr);
				} else {
					deptCode = studentwithallinfo.getMajorin();
					if (Hash_yuanxi.get(deptCode) != null) {
						deptStr = Hash_yuanxi.get(deptCode).toString();
						studentwithallinfo.setDepartment(deptStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = studentwithallinfo.getMajorin();
					if (Hash_Majorin.get(majorinCode) != null) {
						majorinStr = Hash_Majorin.get(majorinCode).toString();
						studentwithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(studentwithallinfo.getNation())) {// 民族
				if (nationCode.equals(studentwithallinfo.getNation())) {
					studentwithallinfo.setNation(nationStr);
				} else {
					nationCode = studentwithallinfo.getNation();
					if (Hash_Nation.get(nationCode) != null) {
						nationStr = Hash_Nation.get(nationCode).toString();
						studentwithallinfo.setNation(nationStr);
					}
				}

			}

			// String deptCode = "";
			// String deptStr = "";
			// if (!"".equals(studentwithallinfo.getDepartment())) {// 所属院系
			// if (deptCode.equals(studentwithallinfo.getDepartment())) {
			// studentwithallinfo.setDepartment(deptStr);
			// } else {
			// deptCode = studentwithallinfo.getDepartment();
			// if (Hash_Department.get(deptCode) != null) {
			// deptStr = Hash_Department.get(deptCode).toString();
			// studentwithallinfo.setDepartment(deptStr);
			// }
			// }
			//
			// }

		}
		return subList;

	}

	public List getStudentExport(String[] args,String schoolId) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];
		String college = args[6];
		String classes = args[7];
		String location = args[8];
		String dormitory = args[9];
		String roomnumber = args[10];
		String assistant = args[11];
		String majorin = args[12];
		String nationality = args[13];
		String page = args[14];
		String orderby = args[15];
		String odr = args[16];
		String department = args[17];
		String area = "";
		if(args.length>18){
			area = args[18];
		}
		
		String idType = "";
		String cultureMode = "";
		String studentChar = "";
		String checkornot = "";
		String schoolornot = "";	
		String enterenceNo = "";	
		String idCard = "";			
		if(args.length>19){
			idType = args[19];
			cultureMode = args[20];
			studentChar = args[21];
			checkornot = args[22];
			schoolornot = args[23];	
			enterenceNo = args[24];		
			idCard = args[25];		
		}
		List entitys = null;
		
		String datebuf = sdf1.format(new Date());//当前年份

		String hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
				+ "('',a.yxClass.classId,'','','','', "
				+ "a.studentId,a.studentNo, a.enterenceNo,ci.ifCheckedin,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
				+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
				+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
				+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
				+ "from Studentmodel a,Stucheckininfo ci ";
		if (StringUtils.isNotEmpty(college) || StringUtils.isNotEmpty(classes)) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += ",Classmanager d,Managermodel e,Managermanagerrole f ";
		}
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)
				|| StringUtils.isNotEmpty(area)) {
			hqlStr += ",Dormitorymodel g ";
		}
//------------------------------------------------------------------------------------------
		hqlStr += "where 1=1 and ci.studentNo=a.studentNo " ;
		
		if(schoolId!=null&&!"".equals(schoolId)&&schoolId.equals("0002")){//护理学院
			//-------------------------------------------------
			hqlStr +=" and a.majorin='623' ";
		}else if(schoolId!=null&&!"".equals(schoolId)&&schoolId.equals("0001")){
			//-------------------------------------------------复旦学院
			hqlStr +=" and a.majorin<>'623' ";
		}
//------------------------------------------------------------------------------------------		
		
		hqlStr +=" and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";

		MyQuery myQuery = new MyQuery();
		
		if (StringUtils.isNotEmpty(idCard)) {
			hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?": "");
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(enterenceNo)) {

			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?": "");
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(studentNo)) {

			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?": "");
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(province)) {
			hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
					: "");
			myQuery.addPara(province, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(polity)) {
			hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");
			myQuery.addPara(polity, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?" : "");
			myQuery.addPara(department, Types.VARCHAR);
		}		
		
		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
			myQuery.addPara(majorin, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(nationality)) {
			hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
					: "");
			myQuery.addPara(nationality, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(college)) {
			myQuery.addPara(college, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(college) || StringUtils.isNotEmpty(classes)) {
			hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
			hqlStr += (StringUtils.isNotEmpty(college) ? " and c.collegeId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " and b.classId = ?"
					: "");
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}

		}


		if (StringUtils.isNotEmpty(assistant)) {
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += " and a.yxClass.classId=d.id.classId and d.id.managerId=e.managerId "
						+ " and e.managerId=f.id.managerId and f.id.roleId='21' ";
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.managerId = ?"
						: "");
			}
			myQuery.addPara(assistant, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(idType)) {
			hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
					: "");
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
					: "");
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}	
		
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)|| StringUtils.isNotEmpty(area)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(area) ? " and g.area = ? "
					: "");
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
		}	
		
		myQuery.setPageStartNo(0);

		if (orderby == null || orderby.length() == 0) {
			myQuery.setOrderby(" order by a.studentNo ");

		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentNo")) {
			myQuery.setOrderby(" order by a.studentNo " + odr);

		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("enterenceNo")) {
			myQuery.setOrderby(" order by a.enterenceNo " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("examNo")) {
			myQuery.setOrderby(" order by ci.ifCheckedin " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("gender")) {
			myQuery.setOrderby(" order by a.gender " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("majorin")) {
			myQuery.setOrderby(" order by a.majorin " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nation")) {
			myQuery.setOrderby(" order by a.nation " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nationality")) {
			myQuery.setOrderby(" order by a.nationality " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("province")) {
			myQuery.setOrderby(" order by a.fromProvince " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("polityBg")) {
			myQuery.setOrderby(" order by a.polityBg " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("birthday")) {
			myQuery.setOrderby(" order by a.birthday " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("homeTelephone")) {
			myQuery.setOrderby(" order by a.homeTelephone " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("tempecardNo")) {
			myQuery.setOrderby(" order by a.tempecardNo " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("department")) {
			myQuery.setOrderby(" order by a.department " + odr);
		}

		myQuery.setQueryString(hqlStr);
		entitys = studentmodelDAO.find(myQuery);
		List Temp_mng = classmodelDAO
				.find("select new map(b.id.classId as classId,c.managerName as managerName) from Classmodel a,Classmanager b,Managermodel c,Managermanagerrole d "
						+ "where a.classId=b.id.classId "
						+ "and b.id.managerId=c.managerId and c.managerId=d.id.managerId and d.id.roleId='21'");
		HashMap Hash_mng = new HashMap();
		for (int i = 0; i < Temp_mng.size(); i++) {
			HashMap temp = (HashMap) Temp_mng.get(i);
			Hash_mng.put(temp.get("classId"), temp.get("managerName"));
		}
		HashMap Hash_cls = new HashMap();
		List Temp_cls = classmodelDAO
				.find("select new map(a.classId as classId,a.classNo as classNo) from Classmodel a ");
		for (int i = 0; i < Temp_cls.size(); i++) {
			HashMap temp = (HashMap) Temp_cls.get(i);
			Hash_cls.put(temp.get("classId"), temp.get("classNo"));
		}
		HashMap Hash_col = new HashMap();
		List Temp_col = classmodelDAO
				.find("select new map(a.classId as classId,b.collegeName as collegeName) from Classmodel a,Collegemodel b"
						+ " where a.yxCollege.collegeId=b.collegeId ");
		for (int i = 0; i < Temp_col.size(); i++) {
			HashMap temp = (HashMap) Temp_col.get(i);
			Hash_col.put(temp.get("classId"), temp.get("collegeName"));
		}
		HashMap Hash_location = new HashMap();
		HashMap Hash_dormitory = new HashMap();
		HashMap Hash_roomNumber = new HashMap();
		HashMap Hash_area = new HashMap();
//		-------------------------------------------		
		if(schoolId!=null&&schoolId.equals("0001")){
		List list_dorm = dormitorymodelDAO
				.find("select new map(a.dormitoryId as dormitoryId,b.dictCaption as location,c.dictCaption as dormitory,a.roomNumber as roomNumber) from"
						+ " Dormitorymodel a,Dictionary b,Dictionary c where a.location=b.id.dictValue and b.id.dictNo=6 "
						+ "and a.dormitory=c.id.dictValue and c.id.dictNo=7 ");
		for (int i = 0; i < list_dorm.size(); i++) {
			HashMap temp = (HashMap) list_dorm.get(i);
			Hash_location.put(temp.get("dormitoryId"), temp.get("location"));
			Hash_dormitory.put(temp.get("dormitoryId"), temp.get("dormitory"));
			Hash_roomNumber
					.put(temp.get("dormitoryId"), temp.get("roomNumber"));
		}
		
		}else if(schoolId!=null&&schoolId.equals("0002")){
			List list_dorm = dormitorymodelDAO
			.find("select new map(a.dormitoryId as dormitoryId," +
					"b.dictCaption as location," +
					"c.dictCaption as dormitory," +
					"d.dictCaption as area," +
					"a.roomNumber as roomNumber) from"
					+ " Dormitorymodel a,Dictionary b,Dictionary c,Dictionary d where a.area=d.id.dictValue and d.id.dictNo=17 " +
							"and a.location=b.id.dictValue and b.id.dictNo=20 "
					+ "and a.dormitory=c.id.dictValue and c.id.dictNo=21 ");
			for (int i = 0; i < list_dorm.size(); i++) {
				HashMap temp = (HashMap) list_dorm.get(i);
				Hash_location.put(temp.get("dormitoryId"), temp.get("location"));
				Hash_dormitory.put(temp.get("dormitoryId"), temp.get("dormitory"));
				Hash_roomNumber
						.put(temp.get("dormitoryId"), temp.get("roomNumber"));
				Hash_area.put(temp.get("dormitoryId"), temp.get("area"));
			}			
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_fromprovince = new HashMap();
		List Temp_fromprovince = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 10 ");
		for (int i = 0; i < Temp_fromprovince.size(); i++) {
			HashMap temp = (HashMap) Temp_fromprovince.get(i);
			Hash_fromprovince.put(temp.get("dictValue"), temp
					.get("dictCaption"));
		}

		HashMap Hash_Nationality = new HashMap();
		List Temp_Nationality = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 12 ");
		for (int i = 0; i < Temp_Nationality.size(); i++) {
			HashMap temp = (HashMap) Temp_Nationality.get(i);
			Hash_Nationality
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_PolityBg = new HashMap();
		List Temp_PolityBg = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 4 ");
		for (int i = 0; i < Temp_PolityBg.size(); i++) {
			HashMap temp = (HashMap) Temp_PolityBg.get(i);
			Hash_PolityBg.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Majorin = new HashMap();
		List Temp_Majorin = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 11 ");
		for (int i = 0; i < Temp_Majorin.size(); i++) {
			HashMap temp = (HashMap) Temp_Majorin.get(i);
			Hash_Majorin.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Nation = new HashMap();
		List Temp_Nation = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 2 ");
		for (int i = 0; i < Temp_Nation.size(); i++) {
			HashMap temp = (HashMap) Temp_Nation.get(i);
			Hash_Nation.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Department = new HashMap();
		List Temp_Department = studentmodelDAO
				.find("select new map(a.deptCode as deptCode, a.deptName as deptName) from Department a ");
		for (int i = 0; i < Temp_Department.size(); i++) {
			HashMap temp = (HashMap) Temp_Department.get(i);
			Hash_Department.put(temp.get("deptCode"), temp.get("deptName"));
		}

		HashMap Hash_bathcardNo = new HashMap();
		List Temp_bathcardNo = studentmodelDAO
				.find("select new map(a.studentNo as studentNo,a.bathcardNo as bathcardNo)from StuCardfeeInfo a ");
		for (int i = 0; i < Temp_bathcardNo.size(); i++) {
			HashMap temp = (HashMap) Temp_bathcardNo.get(i);
			Hash_bathcardNo.put(temp.get("studentNo"), temp.get("bathcardNo"));
		}
		
		HashMap Hash_idType = new HashMap();
		List Temp_idType = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 29 ");
		for (int i = 0; i < Temp_idType.size(); i++) {
			HashMap temp = (HashMap) Temp_idType.get(i);
			Hash_idType.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_cultureMode = new HashMap();
		List Temp_cultureMode = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 26 ");
		for (int i = 0; i < Temp_cultureMode.size(); i++) {
			HashMap temp = (HashMap) Temp_cultureMode.get(i);
			Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_studentChar = new HashMap();
		List Temp_studentChar = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 27 ");
		for (int i = 0; i < Temp_studentChar.size(); i++) {
			HashMap temp = (HashMap) Temp_studentChar.get(i);
			Hash_studentChar.put(temp.get("dictValue"), temp.get("dictCaption"));
		}		

		HashMap Hash_yuanxi = new HashMap();
		List Temp_yuanxi = classmodelDAO
				.find("select new map(a.id.dictValue as majorin,b.deptName as yuanxi) from Dictionary a,Department b"
						+ " where a.id.dictNo=11 and a.dictParent=b.deptCode ");
		for (int i = 0; i < Temp_yuanxi.size(); i++) {
			HashMap temp = (HashMap) Temp_yuanxi.get(i);
			Hash_yuanxi.put(temp.get("majorin"), temp.get("yuanxi"));
		}

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			if (orderby != null
					&& orderby.length() > 0
					&& ("college".equals(orderby) || "name".equals(orderby) || "assistant"
							.equals(orderby))) {
				String clsssIdCode = "";
				String clsmanagerStr = "";
				String classIdStr = "";
				String collegeIdStr = "";
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}

			}

			if (orderby != null
					&& orderby.length() > 0
					&& ("location".equals(orderby)||"area".equals(orderby)
							|| "dormitory".equals(orderby) || "roomNumber"
							.equals(orderby))) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				String areaStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
						studentwithallinfo.setArea(areaStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
						if (Hash_area.get(dromIdCode) != null) {
							areaStr = Hash_area.get(dromIdCode)
									.toString();
							studentwithallinfo.setArea(areaStr);
						}						
					}
				}
			}

			String studentno = "";
			String deptname = "";
			if (!"".equals(studentwithallinfo.getStudentNo())) {// 淋浴卡
				studentno = studentwithallinfo.getStudentNo();
				if (Hash_bathcardNo.get(studentno) != null) {
					deptname = Hash_bathcardNo.get(studentno).toString();
					studentwithallinfo.setBathcardNo(deptname);
				}
			}

		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("college")) {
			// 书院排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0 && orderby.equals("name")) {
			// 班号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("assistant")) {
			// 辅导员排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("stuName")) {
			// 学生姓名排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

//------------------------------------------------大校区		
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("area")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getArea();
					String stuName2 = (String) m2.getArea();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getArea();
					String stuName2 = (String) m2.getArea();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("location")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("dormitory")) {
			// 楼号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("roomNumber")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("bathcardNo")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			String classIdStr = "";
			String collegeIdStr = "";
			if (!"college".equals(orderby) && !"name".equals(orderby)
					&& !"assistant".equals(orderby)) {
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}
			}
			if (!"location".equals(orderby) && !"dormitory".equals(orderby)&&!"area".equals(orderby)
					&& !"roomNumber".equals(orderby)) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				String areaStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
						studentwithallinfo.setArea(areaStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
						if (Hash_area.get(dromIdCode) != null) {
							areaStr = Hash_area.get(dromIdCode)
									.toString();
							studentwithallinfo.setArea(areaStr);
						}
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(studentwithallinfo.getGender())) {// 性别
				if (genderCode.equals(studentwithallinfo.getGender())) {
					studentwithallinfo.setGender(genderStr);
				} else {
					genderCode = studentwithallinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						studentwithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(studentwithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(studentwithallinfo
						.getFromProvince())) {
					studentwithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = studentwithallinfo.getFromProvince();
					if (Hash_fromprovince.get(fromProvinceCode) != null) {
						fromProvinceStr = Hash_fromprovince.get(
								fromProvinceCode).toString();
						studentwithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(studentwithallinfo.getNationality())) {// 国籍
				if (nationalityCode.equals(studentwithallinfo.getNationality())) {
					studentwithallinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = studentwithallinfo.getNationality();
					if (Hash_Nationality.get(nationalityCode) != null) {
						nationalityStr = Hash_Nationality.get(nationalityCode)
								.toString();
						studentwithallinfo.setNationality(nationalityStr);
					}
				}

			}
			String politybgCode = "";
			String politybgStr = "";
			if (!"".equals(studentwithallinfo.getPolityBg())) {// 政治面貌
				if (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					studentwithallinfo.setPolityBg(politybgStr);
				} else {
					politybgCode = studentwithallinfo.getPolityBg();
					if (Hash_PolityBg.get(politybgCode) != null) {
						politybgStr = Hash_PolityBg.get(politybgCode)
								.toString();
						studentwithallinfo.setPolityBg(politybgStr);
					}
				}

			}
			String deptCode = "";
			String deptStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 所属院系
				if (deptCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setDepartment(deptStr);
				} else {
					deptCode = studentwithallinfo.getMajorin();
					if (Hash_yuanxi.get(deptCode) != null) {
						deptStr = Hash_yuanxi.get(deptCode).toString();
						studentwithallinfo.setDepartment(deptStr);
					}
				}
			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = studentwithallinfo.getMajorin();
					if (Hash_Majorin.get(majorinCode) != null) {
						majorinStr = Hash_Majorin.get(majorinCode).toString();
						studentwithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(studentwithallinfo.getNation())) {// 民族
				if (nationCode.equals(studentwithallinfo.getNation())) {
					studentwithallinfo.setNation(nationStr);
				} else {
					nationCode = studentwithallinfo.getNation();
					if (Hash_Nation.get(nationCode) != null) {
						nationStr = Hash_Nation.get(nationCode).toString();
						studentwithallinfo.setNation(nationStr);
					}
				}

			}
			
			String idTypeCode = "";
			String idTypeStr = "";
			if (!"".equals(studentwithallinfo.getIdType())) {// 证件类型
				if (idTypeCode.equals(studentwithallinfo.getIdType())) {
					studentwithallinfo.setIdType(idTypeStr);
				} else {
					idTypeCode = studentwithallinfo.getIdType();
					if (Hash_idType.get(idTypeCode) != null) {
						idTypeStr = Hash_idType.get(idTypeCode).toString();
						studentwithallinfo.setIdType(idTypeStr);
					}
				}

			}	
			
			String cultureModeCode = "";
			String cultureModeStr = "";
			if (!"".equals(studentwithallinfo.getCultureMode())) {// 证件类型
				if (cultureModeCode.equals(studentwithallinfo.getCultureMode())) {
					studentwithallinfo.setCultureMode(cultureModeStr);
				} else {
					cultureModeCode = studentwithallinfo.getCultureMode();
					if (Hash_cultureMode.get(cultureModeCode) != null) {
						cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
						studentwithallinfo.setCultureMode(cultureModeStr);
					}
				}

			}
			
			String studentCharCode = "";
			String studentCharStr = "";
			if (!"".equals(studentwithallinfo.getStudentChar())) {// 证件类型
				if (studentCharCode.equals(studentwithallinfo.getStudentChar())) {
					studentwithallinfo.setStudentChar(studentCharStr);
				} else {
					studentCharCode = studentwithallinfo.getStudentChar();
					if (Hash_studentChar.get(studentCharCode) != null) {
						studentCharStr = Hash_studentChar.get(studentCharCode).toString();
						studentwithallinfo.setStudentChar(studentCharStr);
					}
				}

			}				

			// String deptCode = "";
			// String deptStr = "";
			// if (!"".equals(studentwithallinfo.getDepartment())) {// 所属院系
			// if (deptCode.equals(studentwithallinfo.getDepartment())) {
			// studentwithallinfo.setDepartment(deptStr);
			// } else {
			// deptCode = studentwithallinfo.getDepartment();
			// if (Hash_Department.get(deptCode) != null) {
			// deptStr = Hash_Department.get(deptCode).toString();
			// studentwithallinfo.setDepartment(deptStr);
			// }
			// }
			//
			// }

		}
		return entitys;

	}

	public List getfdyStudentExport(String[] args, String classId) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];
		String location = args[6];
		String dormitory = args[7];
		String roomnumber = args[8];
		String majorin = args[9];
		String nationality = args[10];
		String page = args[11];
		String orderby = args[12];
		String odr = args[13];

		String department = args[14];
		
		String idType = args[15];
		String cultureMode = args[16];
		String studentChar = args[17];
		String checkornot = args[18];
		String schoolornot = args[19];
		String enterenceNo = args[20];	
		String idCard = args[21];	
		List entitys = null;
		

		String hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
				+ "('',a.yxClass.classId,'','','','', "
				+ "a.studentId,a.studentNo, a.enterenceNo,ci.ifCheckedin,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
				+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
				+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
				+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
				+ "from Studentmodel a,Stucheckininfo ci ";
		if (StringUtils.isNotEmpty(classId)) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += ",Dormitorymodel g ";
		}

		MyQuery myQuery = new MyQuery();
		hqlStr += "where 1=1 and ci.studentNo=a.studentNo ";
		hqlStr +=" and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";	

		if (StringUtils.isNotEmpty(idCard)) {
			hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?"
					: "");			
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(studentNo)) {
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
					: "");			
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(enterenceNo)) {
			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?"
					: "");			
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}		

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");			
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");			
			myQuery.addPara(nation, Types.VARCHAR);
		}			

		if (StringUtils.isNotEmpty(province)) {
			hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
					: "");			
			myQuery.addPara(province, Types.VARCHAR);
		}		

		if (StringUtils.isNotEmpty(polity)) {
			hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");			
			myQuery.addPara(polity, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");			
			myQuery.addPara(majorin, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(nationality)) {
			hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
					: "");			
			myQuery.addPara(nationality, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?"
					: "");			
			myQuery.addPara(department, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(idType)) {
			hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
					: "");
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
					: "");	
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}
		
		if (StringUtils.isNotEmpty(classId)) {
			if (StringUtils.isNotEmpty(classId)) {
				hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
				hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?"
						: "");
			}			
			myQuery.addPara(classId, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
		}			

		
		myQuery.setPageStartNo(0);

		if (orderby == null || orderby.length() == 0) {
			myQuery.setOrderby(" order by a.studentNo ");

		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentNo")) {
			myQuery.setOrderby(" order by a.studentNo " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("enterenceNo")) {
			myQuery.setOrderby(" order by a.enterenceNo " + odr);
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("examNo")) {
			myQuery.setOrderby(" order by ci.ifCheckedin " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("gender")) {
			myQuery.setOrderby(" order by a.gender " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("majorin")) {
			myQuery.setOrderby(" order by a.majorin " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nation")) {
			myQuery.setOrderby(" order by a.nation " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nationality")) {
			myQuery.setOrderby(" order by a.nationality " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("province")) {
			myQuery.setOrderby(" order by a.fromProvince " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("polityBg")) {
			myQuery.setOrderby(" order by a.polityBg " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("birthday")) {
			myQuery.setOrderby(" order by a.birthday " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("homeTelephone")) {
			myQuery.setOrderby(" order by a.homeTelephone " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("tempecardNo")) {
			myQuery.setOrderby(" order by a.tempecardNo " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("department")) {
			myQuery.setOrderby(" order by a.department " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("idType")) {
			myQuery.setOrderby(" order by a.idType " + odr);
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("cultureMode")) {
			myQuery.setOrderby(" order by a.cultureMode " + odr);
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentChar")) {
			myQuery.setOrderby(" order by a.studentChar " + odr);
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("checkornot")) {
			myQuery.setOrderby(" order by a.checkornot " + odr);
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("schoolornot")) {
			myQuery.setOrderby(" order by a.schoolornot " + odr);
		}
		
		myQuery.setQueryString(hqlStr);
		entitys = studentmodelDAO.find(myQuery);
		List Temp_mng = classmodelDAO
				.find("select new map(b.id.classId as classId,c.managerName as managerName) from Classmodel a,Classmanager b,Managermodel c,Managermanagerrole d "
						+ "where a.classId=b.id.classId "
						+ "and b.id.managerId=c.managerId and c.managerId=d.id.managerId and d.id.roleId='21'");
		HashMap Hash_mng = new HashMap();
		for (int i = 0; i < Temp_mng.size(); i++) {
			HashMap temp = (HashMap) Temp_mng.get(i);
			Hash_mng.put(temp.get("classId"), temp.get("managerName"));
		}
		HashMap Hash_cls = new HashMap();
		List Temp_cls = classmodelDAO
				.find("select new map(a.classId as classId,a.classNo as classNo) from Classmodel a ");
		for (int i = 0; i < Temp_cls.size(); i++) {
			HashMap temp = (HashMap) Temp_cls.get(i);
			Hash_cls.put(temp.get("classId"), temp.get("classNo"));
		}
		HashMap Hash_col = new HashMap();
		List Temp_col = classmodelDAO
				.find("select new map(a.classId as classId,b.collegeName as collegeName) from Classmodel a,Collegemodel b"
						+ " where a.yxCollege.collegeId=b.collegeId ");
		for (int i = 0; i < Temp_col.size(); i++) {
			HashMap temp = (HashMap) Temp_col.get(i);
			Hash_col.put(temp.get("classId"), temp.get("collegeName"));
		}
		HashMap Hash_location = new HashMap();
		HashMap Hash_dormitory = new HashMap();
		HashMap Hash_roomNumber = new HashMap();

		List list_dorm = dormitorymodelDAO
				.find("select new map(a.dormitoryId as dormitoryId,b.dictCaption as location,c.dictCaption as dormitory,a.roomNumber as roomNumber) from"
						+ " Dormitorymodel a,Dictionary b,Dictionary c where a.location=b.id.dictValue and b.id.dictNo=6 "
						+ "and a.dormitory=c.id.dictValue and c.id.dictNo=7 ");
		for (int i = 0; i < list_dorm.size(); i++) {
			HashMap temp = (HashMap) list_dorm.get(i);
			Hash_location.put(temp.get("dormitoryId"), temp.get("location"));
			Hash_dormitory.put(temp.get("dormitoryId"), temp.get("dormitory"));
			Hash_roomNumber
					.put(temp.get("dormitoryId"), temp.get("roomNumber"));
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_fromprovince = new HashMap();
		List Temp_fromprovince = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 10 ");
		for (int i = 0; i < Temp_fromprovince.size(); i++) {
			HashMap temp = (HashMap) Temp_fromprovince.get(i);
			Hash_fromprovince.put(temp.get("dictValue"), temp
					.get("dictCaption"));
		}

		HashMap Hash_Nationality = new HashMap();
		List Temp_Nationality = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 12 ");
		for (int i = 0; i < Temp_Nationality.size(); i++) {
			HashMap temp = (HashMap) Temp_Nationality.get(i);
			Hash_Nationality
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_PolityBg = new HashMap();
		List Temp_PolityBg = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 4 ");
		for (int i = 0; i < Temp_PolityBg.size(); i++) {
			HashMap temp = (HashMap) Temp_PolityBg.get(i);
			Hash_PolityBg.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Majorin = new HashMap();
		List Temp_Majorin = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 11 ");
		for (int i = 0; i < Temp_Majorin.size(); i++) {
			HashMap temp = (HashMap) Temp_Majorin.get(i);
			Hash_Majorin.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Nation = new HashMap();
		List Temp_Nation = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 2 ");
		for (int i = 0; i < Temp_Nation.size(); i++) {
			HashMap temp = (HashMap) Temp_Nation.get(i);
			Hash_Nation.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Department = new HashMap();
		List Temp_Department = studentmodelDAO
				.find("select new map(a.deptCode as deptCode, a.deptName as deptName) from Department a ");
		for (int i = 0; i < Temp_Department.size(); i++) {
			HashMap temp = (HashMap) Temp_Department.get(i);
			Hash_Department.put(temp.get("deptCode"), temp.get("deptName"));
		}

		HashMap Hash_bathcardNo = new HashMap();
		List Temp_bathcardNo = studentmodelDAO
				.find("select new map(a.studentNo as studentNo,a.bathcardNo as bathcardNo)from StuCardfeeInfo a ");
		for (int i = 0; i < Temp_bathcardNo.size(); i++) {
			HashMap temp = (HashMap) Temp_bathcardNo.get(i);
			Hash_bathcardNo.put(temp.get("studentNo"), temp.get("bathcardNo"));
		}

		HashMap Hash_yuanxi = new HashMap();
		List Temp_yuanxi = classmodelDAO
				.find("select new map(a.id.dictValue as majorin,b.deptName as yuanxi) from Dictionary a,Department b"
						+ " where a.id.dictNo=11 and a.dictParent=b.deptCode ");
		for (int i = 0; i < Temp_yuanxi.size(); i++) {
			HashMap temp = (HashMap) Temp_yuanxi.get(i);
			Hash_yuanxi.put(temp.get("majorin"), temp.get("yuanxi"));
		}
		
		HashMap Hash_idType = new HashMap();
		List Temp_idType = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 29 ");
		for (int i = 0; i < Temp_idType.size(); i++) {
			HashMap temp = (HashMap) Temp_idType.get(i);
			Hash_idType.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_cultureMode = new HashMap();
		List Temp_cultureMode = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 26 ");
		for (int i = 0; i < Temp_cultureMode.size(); i++) {
			HashMap temp = (HashMap) Temp_cultureMode.get(i);
			Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_studentChar = new HashMap();
		List Temp_studentChar = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 27 ");
		for (int i = 0; i < Temp_studentChar.size(); i++) {
			HashMap temp = (HashMap) Temp_studentChar.get(i);
			Hash_studentChar.put(temp.get("dictValue"), temp.get("dictCaption"));
		}		

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			if (orderby != null
					&& orderby.length() > 0
					&& ("college".equals(orderby) || "name".equals(orderby) || "assistant"
							.equals(orderby))) {
				String clsssIdCode = "";
				String clsmanagerStr = "";
				String classIdStr = "";
				String collegeIdStr = "";
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}

			}

			if (orderby != null
					&& orderby.length() > 0
					&& ("location".equals(orderby)
							|| "dormitory".equals(orderby) || "roomNumber"
							.equals(orderby))) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
					}
				}
			}

			String studentno = "";
			String deptname = "";
			if (!"".equals(studentwithallinfo.getStudentNo())) {// 淋浴卡
				studentno = studentwithallinfo.getStudentNo();
				if (Hash_bathcardNo.get(studentno) != null) {
					deptname = Hash_bathcardNo.get(studentno).toString();
					studentwithallinfo.setBathcardNo(deptname);
				}
			}

		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("college")) {
			// 书院排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0 && orderby.equals("name")) {
			// 班号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("assistant")) {
			// 辅导员排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("stuName")) {
			// 学生姓名排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("location")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("dormitory")) {
			// 楼号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("roomNumber")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("bathcardNo")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			String classIdStr = "";
			String collegeIdStr = "";
			if (!"college".equals(orderby) && !"name".equals(orderby)
					&& !"assistant".equals(orderby)) {
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}
			}
			if (!"location".equals(orderby) && !"dormitory".equals(orderby)
					&& !"roomNumber".equals(orderby)) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(studentwithallinfo.getGender())) {// 性别
				if (genderCode.equals(studentwithallinfo.getGender())) {
					studentwithallinfo.setGender(genderStr);
				} else {
					genderCode = studentwithallinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						studentwithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(studentwithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(studentwithallinfo
						.getFromProvince())) {
					studentwithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = studentwithallinfo.getFromProvince();
					if (Hash_fromprovince.get(fromProvinceCode) != null) {
						fromProvinceStr = Hash_fromprovince.get(
								fromProvinceCode).toString();
						studentwithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(studentwithallinfo.getNationality())) {// 国籍
				if (nationalityCode.equals(studentwithallinfo.getNationality())) {
					studentwithallinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = studentwithallinfo.getNationality();
					if (Hash_Nationality.get(nationalityCode) != null) {
						nationalityStr = Hash_Nationality.get(nationalityCode)
								.toString();
						studentwithallinfo.setNationality(nationalityStr);
					}
				}

			}
			String politybgCode = "";
			String politybgStr = "";
			if (!"".equals(studentwithallinfo.getPolityBg())) {// 政治面貌
				if (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					studentwithallinfo.setPolityBg(politybgStr);
				} else {
					politybgCode = studentwithallinfo.getPolityBg();
					if (Hash_PolityBg.get(politybgCode) != null) {
						politybgStr = Hash_PolityBg.get(politybgCode)
								.toString();
						studentwithallinfo.setPolityBg(politybgStr);
					}
				}

			}
			String deptCode = "";
			String deptStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 所属院系
				if (deptCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setDepartment(deptStr);
				} else {
					deptCode = studentwithallinfo.getMajorin();
					if (Hash_yuanxi.get(deptCode) != null) {
						deptStr = Hash_yuanxi.get(deptCode).toString();
						studentwithallinfo.setDepartment(deptStr);
					}
				}
			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = studentwithallinfo.getMajorin();
					if (Hash_Majorin.get(majorinCode) != null) {
						majorinStr = Hash_Majorin.get(majorinCode).toString();
						studentwithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(studentwithallinfo.getNation())) {// 民族
				if (nationCode.equals(studentwithallinfo.getNation())) {
					studentwithallinfo.setNation(nationStr);
				} else {
					nationCode = studentwithallinfo.getNation();
					if (Hash_Nation.get(nationCode) != null) {
						nationStr = Hash_Nation.get(nationCode).toString();
						studentwithallinfo.setNation(nationStr);
					}
				}

			}
			
			String idTypeCode = "";
			String idTypeStr = "";
			if (!"".equals(studentwithallinfo.getIdType())) {// 证件类型
				if (idTypeCode.equals(studentwithallinfo.getIdType())) {
					studentwithallinfo.setIdType(idTypeStr);
				} else {
					idTypeCode = studentwithallinfo.getIdType();
					if (Hash_idType.get(idTypeCode) != null) {
						idTypeStr = Hash_idType.get(idTypeCode).toString();
						studentwithallinfo.setIdType(idTypeStr);
					}
				}

			}	
			
			String cultureModeCode = "";
			String cultureModeStr = "";
			if (!"".equals(studentwithallinfo.getCultureMode())) {// 证件类型
				if (cultureModeCode.equals(studentwithallinfo.getCultureMode())) {
					studentwithallinfo.setCultureMode(cultureModeStr);
				} else {
					cultureModeCode = studentwithallinfo.getCultureMode();
					if (Hash_cultureMode.get(cultureModeCode) != null) {
						cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
						studentwithallinfo.setCultureMode(cultureModeStr);
					}
				}

			}
			
			String studentCharCode = "";
			String studentCharStr = "";
			if (!"".equals(studentwithallinfo.getStudentChar())) {// 证件类型
				if (studentCharCode.equals(studentwithallinfo.getStudentChar())) {
					studentwithallinfo.setStudentChar(studentCharStr);
				} else {
					studentCharCode = studentwithallinfo.getStudentChar();
					if (Hash_studentChar.get(studentCharCode) != null) {
						studentCharStr = Hash_studentChar.get(studentCharCode).toString();
						studentwithallinfo.setStudentChar(studentCharStr);
					}
				}

			}				

			// String deptCode = "";
			// String deptStr = "";
			// if (!"".equals(studentwithallinfo.getDepartment())) {// 所属院系
			// if (deptCode.equals(studentwithallinfo.getDepartment())) {
			// studentwithallinfo.setDepartment(deptStr);
			// } else {
			// deptCode = studentwithallinfo.getDepartment();
			// if (Hash_Department.get(deptCode) != null) {
			// deptStr = Hash_Department.get(deptCode).toString();
			// studentwithallinfo.setDepartment(deptStr);
			// }
			// }
			//
			// }

		}
		return entitys;

	}

	public List getfdyStudentExport_hlxy(String[] args, List classlist) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];
		String location = args[6];
		String dormitory = args[7];
		String roomnumber = args[8];
		String majorin = args[9];
		String nationality = args[10];
		String orderby = args[12];
		String odr = args[13];
		String department = args[14];
		String area = args[15];
		
		String idType = args[16];
		String cultureMode = args[17];
		String studentChar = args[18];
		String checkornot = args[19];
		String schoolornot = args[20];
		
		String classIds = args[21];
		String enterenceNo = args[22];
		String idCard = args[23];		
		List entitys = null;

		String hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
				+ "('',a.yxClass.classId,'','','','', "
				+ "a.studentId,a.studentNo, a.enterenceNo, a.examNo,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
				+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
				+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
				+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
				+ "from Studentmodel a ";
		if (classlist!=null&&classlist.size()>0) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += ",Dormitorymodel g ";
		}

		hqlStr += "where 1=1 and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
		hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?"
				: "");		
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?"
				: "");		
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and a.yxClass.classId = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?"
				: "");	
		
		
		hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
				: "");			

		if (classlist!=null&&classlist.size()>0) {
			hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
			
			
			hqlStr += "and b.classId in(";
			if(classlist!=null&&classlist.size()>0){
				for(int i=0;i<classlist.size();i++){
					HashMap hashmap =  (HashMap)classlist.get(i);
					String classId = (String)hashmap.get("classId");
					hqlStr += "'"+classId + "',";
				}
				
			}
			hqlStr = hqlStr.substring(0,(hqlStr.length()-1));
			hqlStr += ") ";			
//			hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?"
//					: "");
		}
		
		if (StringUtils.isNotEmpty(area)
				||StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(area) ? " and g.area = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
		}

		MyQuery myQuery = new MyQuery();
		if (StringUtils.isNotEmpty(idCard)) {
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(enterenceNo)) {
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}
		
//		if (StringUtils.isNotEmpty(classIds)) {
//			myQuery.addPara(classIds, Types.VARCHAR);
//		}
	

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(province)) {
			myQuery.addPara(province, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(polity)) {
			myQuery.addPara(polity, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nationality)) {
			myQuery.addPara(nationality, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			myQuery.addPara(department, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(idType)) {
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}	
		
		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}
		
		myQuery.setPageStartNo(0);

		if (orderby == null || orderby.length() == 0) {
			myQuery.setOrderby(" order by a.studentNo ");

		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentNo")) {
			myQuery.setOrderby(" order by a.studentNo " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("enterenceNo")) {
			myQuery.setOrderby(" order by a.enterenceNo " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("gender")) {
			myQuery.setOrderby(" order by a.gender " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("majorin")) {
			myQuery.setOrderby(" order by a.majorin " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nation")) {
			myQuery.setOrderby(" order by a.nation " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nationality")) {
			myQuery.setOrderby(" order by a.nationality " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("province")) {
			myQuery.setOrderby(" order by a.fromProvince " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("polityBg")) {
			myQuery.setOrderby(" order by a.polityBg " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("birthday")) {
			myQuery.setOrderby(" order by a.birthday " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("homeTelephone")) {
			myQuery.setOrderby(" order by a.homeTelephone " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("tempecardNo")) {
			myQuery.setOrderby(" order by a.tempecardNo " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("department")) {
			myQuery.setOrderby(" order by a.department " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("idType")) {
			myQuery.setOrderby(" order by a.idType " + odr);
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("cultureMode")) {
			myQuery.setOrderby(" order by a.cultureMode " + odr);
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentChar")) {
			myQuery.setOrderby(" order by a.studentChar " + odr);
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("checkornot")) {
			myQuery.setOrderby(" order by a.checkornot " + odr);
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("schoolornot")) {
			myQuery.setOrderby(" order by a.schoolornot " + odr);
		}

		myQuery.setQueryString(hqlStr);
		entitys = studentmodelDAO.find(myQuery);
		List Temp_mng = classmodelDAO
				.find("select new map(b.id.classId as classId,c.managerName as managerName) from Classmodel a,Classmanager b,Managermodel c,Managermanagerrole d "
						+ "where a.classId=b.id.classId "
						+ "and b.id.managerId=c.managerId and c.managerId=d.id.managerId and d.id.roleId='21'");
		HashMap Hash_mng = new HashMap();
		for (int i = 0; i < Temp_mng.size(); i++) {
			HashMap temp = (HashMap) Temp_mng.get(i);
			Hash_mng.put(temp.get("classId"), temp.get("managerName"));
		}
		HashMap Hash_cls = new HashMap();
		List Temp_cls = classmodelDAO
				.find("select new map(a.classId as classId,a.classNo as classNo) from Classmodel a ");
		for (int i = 0; i < Temp_cls.size(); i++) {
			HashMap temp = (HashMap) Temp_cls.get(i);
			Hash_cls.put(temp.get("classId"), temp.get("classNo"));
		}
		HashMap Hash_col = new HashMap();
		List Temp_col = classmodelDAO
				.find("select new map(a.classId as classId,b.collegeName as collegeName) from Classmodel a,Collegemodel b"
						+ " where a.yxCollege.collegeId=b.collegeId ");
		for (int i = 0; i < Temp_col.size(); i++) {
			HashMap temp = (HashMap) Temp_col.get(i);
			Hash_col.put(temp.get("classId"), temp.get("collegeName"));
		}
		HashMap Hash_location = new HashMap();
		HashMap Hash_dormitory = new HashMap();
		HashMap Hash_roomNumber = new HashMap();
		HashMap Hash_area = new HashMap();
		
		List list_dorm = dormitorymodelDAO
				.find("select new map(a.dormitoryId as dormitoryId," +
						"b.dictCaption as location," +
						"c.dictCaption as dormitory," +
						"d.dictCaption as area," +
						"a.roomNumber as roomNumber) from"
						+ " Dormitorymodel a,Dictionary b,Dictionary c,Dictionary d " +
								"where a.location=b.id.dictValue and b.id.dictNo=20 "
						+ "and a.dormitory=c.id.dictValue and c.id.dictNo=21 " +
								"and a.area=d.id.dictValue and d.id.dictNo=17 ");
		for (int i = 0; i < list_dorm.size(); i++) {
			HashMap temp = (HashMap) list_dorm.get(i);
			Hash_area.put(temp.get("dormitoryId"), temp.get("area"));
			Hash_location.put(temp.get("dormitoryId"), temp.get("location"));
			Hash_dormitory.put(temp.get("dormitoryId"), temp.get("dormitory"));
			Hash_roomNumber
					.put(temp.get("dormitoryId"), temp.get("roomNumber"));
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_fromprovince = new HashMap();
		List Temp_fromprovince = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 10 ");
		for (int i = 0; i < Temp_fromprovince.size(); i++) {
			HashMap temp = (HashMap) Temp_fromprovince.get(i);
			Hash_fromprovince.put(temp.get("dictValue"), temp
					.get("dictCaption"));
		}

		HashMap Hash_Nationality = new HashMap();
		List Temp_Nationality = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 12 ");
		for (int i = 0; i < Temp_Nationality.size(); i++) {
			HashMap temp = (HashMap) Temp_Nationality.get(i);
			Hash_Nationality
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_PolityBg = new HashMap();
		List Temp_PolityBg = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 4 ");
		for (int i = 0; i < Temp_PolityBg.size(); i++) {
			HashMap temp = (HashMap) Temp_PolityBg.get(i);
			Hash_PolityBg.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Majorin = new HashMap();
		List Temp_Majorin = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 11 ");
		for (int i = 0; i < Temp_Majorin.size(); i++) {
			HashMap temp = (HashMap) Temp_Majorin.get(i);
			Hash_Majorin.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Nation = new HashMap();
		List Temp_Nation = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 2 ");
		for (int i = 0; i < Temp_Nation.size(); i++) {
			HashMap temp = (HashMap) Temp_Nation.get(i);
			Hash_Nation.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Department = new HashMap();
		List Temp_Department = studentmodelDAO
				.find("select new map(a.deptCode as deptCode, a.deptName as deptName) from Department a ");
		for (int i = 0; i < Temp_Department.size(); i++) {
			HashMap temp = (HashMap) Temp_Department.get(i);
			Hash_Department.put(temp.get("deptCode"), temp.get("deptName"));
		}

		HashMap Hash_bathcardNo = new HashMap();
		List Temp_bathcardNo = studentmodelDAO
				.find("select new map(a.studentNo as studentNo,a.bathcardNo as bathcardNo)from StuCardfeeInfo a ");
		for (int i = 0; i < Temp_bathcardNo.size(); i++) {
			HashMap temp = (HashMap) Temp_bathcardNo.get(i);
			Hash_bathcardNo.put(temp.get("studentNo"), temp.get("bathcardNo"));
		}

		HashMap Hash_yuanxi = new HashMap();
		List Temp_yuanxi = classmodelDAO
				.find("select new map(a.id.dictValue as majorin,b.deptName as yuanxi) from Dictionary a,Department b"
						+ " where a.id.dictNo=11 and a.dictParent=b.deptCode ");
		for (int i = 0; i < Temp_yuanxi.size(); i++) {
			HashMap temp = (HashMap) Temp_yuanxi.get(i);
			Hash_yuanxi.put(temp.get("majorin"), temp.get("yuanxi"));
		}
		
		HashMap Hash_idType = new HashMap();
		List Temp_idType = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 29 ");
		for (int i = 0; i < Temp_idType.size(); i++) {
			HashMap temp = (HashMap) Temp_idType.get(i);
			Hash_idType.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_cultureMode = new HashMap();
		List Temp_cultureMode = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 26 ");
		for (int i = 0; i < Temp_cultureMode.size(); i++) {
			HashMap temp = (HashMap) Temp_cultureMode.get(i);
			Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_studentChar = new HashMap();
		List Temp_studentChar = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 27 ");
		for (int i = 0; i < Temp_studentChar.size(); i++) {
			HashMap temp = (HashMap) Temp_studentChar.get(i);
			Hash_studentChar.put(temp.get("dictValue"), temp.get("dictCaption"));
		}		

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			if (orderby != null
					&& orderby.length() > 0
					&& ("college".equals(orderby) || "name".equals(orderby) || "assistant"
							.equals(orderby))) {
				String clsssIdCode = "";
				String clsmanagerStr = "";
				String classIdStr = "";
				String collegeIdStr = "";
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}

			}

			if (orderby != null
					&& orderby.length() > 0
					&& ("area".equals(orderby)
							||"location".equals(orderby)
							|| "dormitory".equals(orderby) || "roomNumber"
							.equals(orderby))) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				String areaStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setArea(areaStr);
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_area.get(dromIdCode) != null) {
							areaStr = Hash_area.get(dromIdCode)
									.toString();
							studentwithallinfo.setArea(areaStr);
						}
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
					}
				}
			}

			String studentno = "";
			String deptname = "";
			if (!"".equals(studentwithallinfo.getStudentNo())) {// 淋浴卡
				studentno = studentwithallinfo.getStudentNo();
				if (Hash_bathcardNo.get(studentno) != null) {
					deptname = Hash_bathcardNo.get(studentno).toString();
					studentwithallinfo.setBathcardNo(deptname);
				}
			}

		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("college")) {
			// 书院排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0 && orderby.equals("name")) {
			// 班号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("assistant")) {
			// 辅导员排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("stuName")) {
			// 学生姓名排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("area")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getArea();
					String stuName2 = (String) m2.getArea();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getArea();
					String stuName2 = (String) m2.getArea();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("location")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("dormitory")) {
			// 楼号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("roomNumber")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("bathcardNo")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			String classIdStr = "";
			String collegeIdStr = "";
			if (!"college".equals(orderby) && !"name".equals(orderby)
					&& !"assistant".equals(orderby)) {
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}
			}
			if (!"area".equals(orderby) &&!"location".equals(orderby) && !"dormitory".equals(orderby)
					&& !"roomNumber".equals(orderby)) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				String areaStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setArea(areaStr);
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_area.get(dromIdCode) != null) {
							areaStr = Hash_area.get(dromIdCode)
									.toString();
							studentwithallinfo.setArea(areaStr);
						}						
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(studentwithallinfo.getGender())) {// 性别
				if (genderCode.equals(studentwithallinfo.getGender())) {
					studentwithallinfo.setGender(genderStr);
				} else {
					genderCode = studentwithallinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						studentwithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(studentwithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(studentwithallinfo
						.getFromProvince())) {
					studentwithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = studentwithallinfo.getFromProvince();
					if (Hash_fromprovince.get(fromProvinceCode) != null) {
						fromProvinceStr = Hash_fromprovince.get(
								fromProvinceCode).toString();
						studentwithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(studentwithallinfo.getNationality())) {// 国籍
				if (nationalityCode.equals(studentwithallinfo.getNationality())) {
					studentwithallinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = studentwithallinfo.getNationality();
					if (Hash_Nationality.get(nationalityCode) != null) {
						nationalityStr = Hash_Nationality.get(nationalityCode)
								.toString();
						studentwithallinfo.setNationality(nationalityStr);
					}
				}

			}
			String politybgCode = "";
			String politybgStr = "";
			if (!"".equals(studentwithallinfo.getPolityBg())) {// 政治面貌
				if (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					studentwithallinfo.setPolityBg(politybgStr);
				} else {
					politybgCode = studentwithallinfo.getPolityBg();
					if (Hash_PolityBg.get(politybgCode) != null) {
						politybgStr = Hash_PolityBg.get(politybgCode)
								.toString();
						studentwithallinfo.setPolityBg(politybgStr);
					}
				}

			}
			String deptCode = "";
			String deptStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 所属院系
				if (deptCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setDepartment(deptStr);
				} else {
					deptCode = studentwithallinfo.getMajorin();
					if (Hash_yuanxi.get(deptCode) != null) {
						deptStr = Hash_yuanxi.get(deptCode).toString();
						studentwithallinfo.setDepartment(deptStr);
					}
				}
			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = studentwithallinfo.getMajorin();
					if (Hash_Majorin.get(majorinCode) != null) {
						majorinStr = Hash_Majorin.get(majorinCode).toString();
						studentwithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(studentwithallinfo.getNation())) {// 民族
				if (nationCode.equals(studentwithallinfo.getNation())) {
					studentwithallinfo.setNation(nationStr);
				} else {
					nationCode = studentwithallinfo.getNation();
					if (Hash_Nation.get(nationCode) != null) {
						nationStr = Hash_Nation.get(nationCode).toString();
						studentwithallinfo.setNation(nationStr);
					}
				}

			}
			
			String idTypeCode = "";
			String idTypeStr = "";
			if (!"".equals(studentwithallinfo.getIdCard())) {// 证件类型
				if (idTypeCode.equals(studentwithallinfo.getIdCard())) {
					studentwithallinfo.setIdType(idTypeStr);
				} else {
					idTypeCode = studentwithallinfo.getIdCard();
					if (Hash_idType.get(idTypeCode) != null) {
						idTypeStr = Hash_idType.get(idTypeCode).toString();
						studentwithallinfo.setIdType(idTypeStr);
					}
				}

			}	
			
			String cultureModeCode = "";
			String cultureModeStr = "";
			if (!"".equals(studentwithallinfo.getCultureMode())) {// 证件类型
				if (cultureModeCode.equals(studentwithallinfo.getCultureMode())) {
					studentwithallinfo.setCultureMode(cultureModeStr);
				} else {
					cultureModeCode = studentwithallinfo.getCultureMode();
					if (Hash_cultureMode.get(cultureModeCode) != null) {
						cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
						studentwithallinfo.setCultureMode(cultureModeStr);
					}
				}

			}
			
			String studentCharCode = "";
			String studentCharStr = "";
			if (!"".equals(studentwithallinfo.getStudentChar())) {// 证件类型
				if (studentCharCode.equals(studentwithallinfo.getStudentChar())) {
					studentwithallinfo.setStudentChar(studentCharStr);
				} else {
					studentCharCode = studentwithallinfo.getStudentChar();
					if (Hash_studentChar.get(studentCharCode) != null) {
						studentCharStr = Hash_studentChar.get(studentCharCode).toString();
						studentwithallinfo.setStudentChar(studentCharStr);
					}
				}

			}				

			// String deptCode = "";
			// String deptStr = "";
			// if (!"".equals(studentwithallinfo.getDepartment())) {// 所属院系
			// if (deptCode.equals(studentwithallinfo.getDepartment())) {
			// studentwithallinfo.setDepartment(deptStr);
			// } else {
			// deptCode = studentwithallinfo.getDepartment();
			// if (Hash_Department.get(deptCode) != null) {
			// deptStr = Hash_Department.get(deptCode).toString();
			// studentwithallinfo.setDepartment(deptStr);
			// }
			// }
			//
			// }

		}
		return entitys;

	}
	
	public List getfdyStudent(String[] args, String classId) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];
		String location = args[6];
		String dormitory = args[7];
		String roomnumber = args[8];
		String majorin = args[9];
		String nationality = args[10];
		String page = args[11];
		String orderby = args[12];
		String odr = args[13];

		String department = args[14];
		
		String idType = args[15];
		String cultureMode = args[16];
		String studentChar = args[17];
		String checkornot = args[18];
		String schoolornot = args[19];
		String enterenceNo = args[20];	
		String idCard = args[21];				
		boolean orderedCheck = true;
		List entitys = null;

		String datebuf = sdf1.format(new Date());//当前年份
		
		String hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
				+ "('',a.yxClass.classId,'','','','', "
				+ "a.studentId,a.studentNo, a.enterenceNo,ci.ifCheckedin,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
				+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
				+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
				+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
				+ "from Studentmodel a,Stucheckininfo ci ";
		if (StringUtils.isNotEmpty(classId)) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += ",Dormitorymodel g ";
		}
		
		MyQuery myQuery = new MyQuery();
		hqlStr += "where 1=1 and ci.studentNo=a.studentNo";
		hqlStr +=" and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";	
		
		if (StringUtils.isNotEmpty(idCard)) {
			hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?"
					: "");			
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(studentNo)) {
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
					: "");			
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(enterenceNo)) {
			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?"
					: "");			
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");			
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");			
			myQuery.addPara(nation, Types.VARCHAR);
		}			

		if (StringUtils.isNotEmpty(province)) {
			hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
					: "");			
			myQuery.addPara(province, Types.VARCHAR);
		}		

		if (StringUtils.isNotEmpty(polity)) {
			hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");			
			myQuery.addPara(polity, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");			
			myQuery.addPara(majorin, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(nationality)) {
			hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
					: "");			
			myQuery.addPara(nationality, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?"
					: "");			
			myQuery.addPara(department, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(idType)) {
			hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
					: "");
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
					: "");	
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}
		
		if (StringUtils.isNotEmpty(classId)) {
			if (StringUtils.isNotEmpty(classId)) {
				hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
				hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?"
						: "");
			}			
			myQuery.addPara(classId, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
		}			

		
		myQuery.setPageSize(100);

		if (orderby == null || orderby.length() == 0) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentNo ");
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("enterenceNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.enterenceNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("examNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by ci.ifCheckedin " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("gender")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.gender " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("majorin")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.majorin " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nation")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.nation " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nationality")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.nationality " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("province")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.fromProvince " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("polityBg")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.polityBg " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("birthday")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.birthday " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("homeTelephone")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.homeTelephone " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("tempecardNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.tempecardNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("department")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.department " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("idType")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.idType " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("cultureMode")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.cultureMode " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentChar")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentChar " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("checkornot")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.checkornot " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}else if (orderby != null && orderby.length() > 0
				&& orderby.equals("schoolornot")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.schoolornot " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}
		

		else {
			orderedCheck = false;
			myQuery.setPageStartNo(0);
			myQuery.setOffset(false);
		}

		myQuery.setQueryString(hqlStr);
		entitys = studentmodelDAO.find(myQuery);
		List Temp_mng = classmodelDAO
				.find("select new map(b.id.classId as classId,c.managerName as managerName) from Classmodel a,Classmanager b,Managermodel c,Managermanagerrole d "
						+ "where a.classId=b.id.classId "
						+ "and b.id.managerId=c.managerId and c.managerId=d.id.managerId and d.id.roleId='21'");
		HashMap Hash_mng = new HashMap();
		for (int i = 0; i < Temp_mng.size(); i++) {
			HashMap temp = (HashMap) Temp_mng.get(i);
			Hash_mng.put(temp.get("classId"), temp.get("managerName"));
		}
		HashMap Hash_cls = new HashMap();
		List Temp_cls = classmodelDAO
				.find("select new map(a.classId as classId,a.classNo as classNo) from Classmodel a ");
		for (int i = 0; i < Temp_cls.size(); i++) {
			HashMap temp = (HashMap) Temp_cls.get(i);
			Hash_cls.put(temp.get("classId"), temp.get("classNo"));
		}
		HashMap Hash_col = new HashMap();
		List Temp_col = classmodelDAO
				.find("select new map(a.classId as classId,b.collegeName as collegeName) from Classmodel a,Collegemodel b"
						+ " where a.yxCollege.collegeId=b.collegeId ");
		for (int i = 0; i < Temp_col.size(); i++) {
			HashMap temp = (HashMap) Temp_col.get(i);
			Hash_col.put(temp.get("classId"), temp.get("collegeName"));
		}
		HashMap Hash_location = new HashMap();
		HashMap Hash_dormitory = new HashMap();
		HashMap Hash_roomNumber = new HashMap();

		List list_dorm = dormitorymodelDAO
				.find("select new map(a.dormitoryId as dormitoryId,b.dictCaption as location,c.dictCaption as dormitory,a.roomNumber as roomNumber) from"
						+ " Dormitorymodel a,Dictionary b,Dictionary c where a.location=b.id.dictValue and b.id.dictNo=6 "
						+ "and a.dormitory=c.id.dictValue and c.id.dictNo=7 ");
		for (int i = 0; i < list_dorm.size(); i++) {
			HashMap temp = (HashMap) list_dorm.get(i);
			Hash_location.put(temp.get("dormitoryId"), temp.get("location"));
			Hash_dormitory.put(temp.get("dormitoryId"), temp.get("dormitory"));
			Hash_roomNumber
					.put(temp.get("dormitoryId"), temp.get("roomNumber"));
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_fromprovince = new HashMap();
		List Temp_fromprovince = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 10 ");
		for (int i = 0; i < Temp_fromprovince.size(); i++) {
			HashMap temp = (HashMap) Temp_fromprovince.get(i);
			Hash_fromprovince.put(temp.get("dictValue"), temp
					.get("dictCaption"));
		}

		HashMap Hash_Nationality = new HashMap();
		List Temp_Nationality = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 12 ");
		for (int i = 0; i < Temp_Nationality.size(); i++) {
			HashMap temp = (HashMap) Temp_Nationality.get(i);
			Hash_Nationality
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_PolityBg = new HashMap();
		List Temp_PolityBg = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 4 ");
		for (int i = 0; i < Temp_PolityBg.size(); i++) {
			HashMap temp = (HashMap) Temp_PolityBg.get(i);
			Hash_PolityBg.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Majorin = new HashMap();
		List Temp_Majorin = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 11 ");
		for (int i = 0; i < Temp_Majorin.size(); i++) {
			HashMap temp = (HashMap) Temp_Majorin.get(i);
			Hash_Majorin.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Nation = new HashMap();
		List Temp_Nation = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 2 ");
		for (int i = 0; i < Temp_Nation.size(); i++) {
			HashMap temp = (HashMap) Temp_Nation.get(i);
			Hash_Nation.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Department = new HashMap();
		List Temp_Department = studentmodelDAO
				.find("select new map(a.deptCode as deptCode, a.deptName as deptName) from Department a ");
		for (int i = 0; i < Temp_Department.size(); i++) {
			HashMap temp = (HashMap) Temp_Department.get(i);
			Hash_Department.put(temp.get("deptCode"), temp.get("deptName"));
		}

		HashMap Hash_bathcardNo = new HashMap();
		List Temp_bathcardNo = studentmodelDAO
				.find("select new map(a.studentNo as studentNo,a.bathcardNo as bathcardNo)from StuCardfeeInfo a ");
		for (int i = 0; i < Temp_bathcardNo.size(); i++) {
			HashMap temp = (HashMap) Temp_bathcardNo.get(i);
			Hash_bathcardNo.put(temp.get("studentNo"), temp.get("bathcardNo"));
		}

		HashMap Hash_yuanxi = new HashMap();
		List Temp_yuanxi = classmodelDAO
				.find("select new map(a.id.dictValue as majorin,b.deptName as yuanxi) from Dictionary a,Department b"
						+ " where a.id.dictNo=11 and a.dictParent=b.deptCode ");
		for (int i = 0; i < Temp_yuanxi.size(); i++) {
			HashMap temp = (HashMap) Temp_yuanxi.get(i);
			Hash_yuanxi.put(temp.get("majorin"), temp.get("yuanxi"));
		}
		
		HashMap Hash_idType = new HashMap();
		List Temp_idType = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 29 ");
		for (int i = 0; i < Temp_idType.size(); i++) {
			HashMap temp = (HashMap) Temp_idType.get(i);
			Hash_idType.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_cultureMode = new HashMap();
		List Temp_cultureMode = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 26 ");
		for (int i = 0; i < Temp_cultureMode.size(); i++) {
			HashMap temp = (HashMap) Temp_cultureMode.get(i);
			Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_studentChar = new HashMap();
		List Temp_studentChar = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 27 ");
		for (int i = 0; i < Temp_studentChar.size(); i++) {
			HashMap temp = (HashMap) Temp_studentChar.get(i);
			Hash_studentChar.put(temp.get("dictValue"), temp.get("dictCaption"));
		}		

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			if (orderby != null
					&& orderby.length() > 0
					&& ("college".equals(orderby) || "name".equals(orderby) || "assistant"
							.equals(orderby))) {
				String clsssIdCode = "";
				String clsmanagerStr = "";
				String classIdStr = "";
				String collegeIdStr = "";
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}

			}

			if (orderby != null
					&& orderby.length() > 0
					&& ("location".equals(orderby)
							|| "dormitory".equals(orderby) || "roomNumber"
							.equals(orderby))) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
					}
				}
			}

			String studentno = "";
			String deptname = "";
			if (!"".equals(studentwithallinfo.getStudentNo())) {// 淋浴卡
				studentno = studentwithallinfo.getStudentNo();
				if (Hash_bathcardNo.get(studentno) != null) {
					deptname = Hash_bathcardNo.get(studentno).toString();
					studentwithallinfo.setBathcardNo(deptname);
				}
			}

		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("college")) {
			// 书院排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0 && orderby.equals("name")) {
			// 班号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("assistant")) {
			// 辅导员排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("stuName")) {
			// 学生姓名排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("location")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("dormitory")) {
			// 楼号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("roomNumber")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("bathcardNo")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		List subList = null;
		if (orderedCheck) {
			subList = entitys;
		} else {
			int startrow = 0;
			if (StringUtils.isNumeric(page)) {
				startrow = Integer.parseInt(page);
				if ((startrow + 100) < entitys.size()) {
					subList = entitys.subList(startrow, startrow + 100);
				} else {
					subList = entitys.subList(startrow, entitys.size());
				}
			} else {
				if ((startrow + 100) < entitys.size()) {
					subList = entitys.subList(0, 100);
				} else {
					subList = entitys.subList(0, entitys.size());
				}
			}
		}

		for (int i = 0; i < subList.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) subList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			String classIdStr = "";
			String collegeIdStr = "";
			if (!"college".equals(orderby) && !"name".equals(orderby)
					&& !"assistant".equals(orderby)) {
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}
			}
			if (!"location".equals(orderby) && !"dormitory".equals(orderby)
					&& !"roomNumber".equals(orderby)) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(studentwithallinfo.getGender())) {// 性别
				if (genderCode.equals(studentwithallinfo.getGender())) {
					studentwithallinfo.setGender(genderStr);
				} else {
					genderCode = studentwithallinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						studentwithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(studentwithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(studentwithallinfo
						.getFromProvince())) {
					studentwithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = studentwithallinfo.getFromProvince();
					if (Hash_fromprovince.get(fromProvinceCode) != null) {
						fromProvinceStr = Hash_fromprovince.get(
								fromProvinceCode).toString();
						studentwithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(studentwithallinfo.getNationality())) {// 国籍
				if (nationalityCode.equals(studentwithallinfo.getNationality())) {
					studentwithallinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = studentwithallinfo.getNationality();
					if (Hash_Nationality.get(nationalityCode) != null) {
						nationalityStr = Hash_Nationality.get(nationalityCode)
								.toString();
						studentwithallinfo.setNationality(nationalityStr);
					}
				}

			}
			String politybgCode = "";
			String politybgStr = "";
			if (!"".equals(studentwithallinfo.getPolityBg())) {// 政治面貌
				if (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					studentwithallinfo.setPolityBg(politybgStr);
				} else {
					politybgCode = studentwithallinfo.getPolityBg();
					if (Hash_PolityBg.get(politybgCode) != null) {
						politybgStr = Hash_PolityBg.get(politybgCode)
								.toString();
						studentwithallinfo.setPolityBg(politybgStr);
					}
				}

			}
			String deptCode = "";
			String deptStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 所属院系
				if (deptCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setDepartment(deptStr);
				} else {
					deptCode = studentwithallinfo.getMajorin();
					if (Hash_yuanxi.get(deptCode) != null) {
						deptStr = Hash_yuanxi.get(deptCode).toString();
						studentwithallinfo.setDepartment(deptStr);
					}
				}
			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = studentwithallinfo.getMajorin();
					if (Hash_Majorin.get(majorinCode) != null) {
						majorinStr = Hash_Majorin.get(majorinCode).toString();
						studentwithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(studentwithallinfo.getNation())) {// 民族
				if (nationCode.equals(studentwithallinfo.getNation())) {
					studentwithallinfo.setNation(nationStr);
				} else {
					nationCode = studentwithallinfo.getNation();
					if (Hash_Nation.get(nationCode) != null) {
						nationStr = Hash_Nation.get(nationCode).toString();
						studentwithallinfo.setNation(nationStr);
					}
				}

			}
			
			String idTypeCode = "";
			String idTypeStr = "";
			if (!"".equals(studentwithallinfo.getIdType())) {// 证件类型
				if (idTypeCode.equals(studentwithallinfo.getIdType())) {
					studentwithallinfo.setIdType(idTypeStr);
				} else {
					idTypeCode = studentwithallinfo.getIdType();
					if (Hash_idType.get(idTypeCode) != null) {
						idTypeStr = Hash_idType.get(idTypeCode).toString();
						studentwithallinfo.setIdType(idTypeStr);
					}
				}

			}	
			
			String cultureModeCode = "";
			String cultureModeStr = "";
			if (!"".equals(studentwithallinfo.getCultureMode())) {// 证件类型
				if (cultureModeCode.equals(studentwithallinfo.getCultureMode())) {
					studentwithallinfo.setCultureMode(cultureModeStr);
				} else {
					cultureModeCode = studentwithallinfo.getCultureMode();
					if (Hash_cultureMode.get(cultureModeCode) != null) {
						cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
						studentwithallinfo.setCultureMode(cultureModeStr);
					}
				}

			}
			
			String studentCharCode = "";
			String studentCharStr = "";
			if (!"".equals(studentwithallinfo.getStudentChar())) {// 证件类型
				if (studentCharCode.equals(studentwithallinfo.getStudentChar())) {
					studentwithallinfo.setStudentChar(studentCharStr);
				} else {
					studentCharCode = studentwithallinfo.getStudentChar();
					if (Hash_studentChar.get(studentCharCode) != null) {
						studentCharStr = Hash_studentChar.get(studentCharCode).toString();
						studentwithallinfo.setStudentChar(studentCharStr);
					}
				}

			}				

			// String deptCode = "";
			// String deptStr = "";
			// if (!"".equals(studentwithallinfo.getDepartment())) {// 所属院系
			// if (deptCode.equals(studentwithallinfo.getDepartment())) {
			// studentwithallinfo.setDepartment(deptStr);
			// } else {
			// deptCode = studentwithallinfo.getDepartment();
			// if (Hash_Department.get(deptCode) != null) {
			// deptStr = Hash_Department.get(deptCode).toString();
			// studentwithallinfo.setDepartment(deptStr);
			// }
			// }
			//
			// }

		}
		return subList;

	}
	
	public List getfdyStudent_hlxy(String[] args, List classlist) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];
		String location = args[6];
		String dormitory = args[7];
		String roomnumber = args[8];
		String majorin = args[9];
		String nationality = args[10];
		String page = args[11];
		String orderby = args[12];
		String odr = args[13];

		String department = args[14];

		String area = args[15];
		
		String idType = args[16];
		String cultureMode = args[17];
		String studentChar = args[18];
		String checkornot = args[19];
		String schoolornot = args[20];
		
		String classIds = args[21];
		String enterenceNo = args[22];
		String idCard = args[23];		
		boolean orderedCheck = true;
		List entitys = null;
		
		String hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
				+ "('',a.yxClass.classId,'','','','', "
				+ "a.studentId,a.studentNo, a.enterenceNo, a.examNo,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
				+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
				+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
				+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
				+ "from Studentmodel a ";
		if (classlist!=null&&classlist.size()>0) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}
		if (StringUtils.isNotEmpty(area)
				||StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += ",Dormitorymodel g ";
		}

		hqlStr += "where 1=1 and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
		hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?"
				: "");		
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and a.yxClass.classId = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?"
				: "");	
		
		
		hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
				: "");			

		if (classlist!=null&&classlist.size()>0) {
			hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
			
			
			hqlStr += "and b.classId in(";
			if(classlist!=null&&classlist.size()>0){
				for(int i=0;i<classlist.size();i++){
					HashMap hashmap =  (HashMap)classlist.get(i);
					String classId = (String)hashmap.get("classId");
					hqlStr += "'"+classId + "',";
				}
				
			}
			hqlStr = hqlStr.substring(0,(hqlStr.length()-1));
			hqlStr += ") ";			
//			hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?"
//					: "");
		}
		
		if (StringUtils.isNotEmpty(area)
				||StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(area) ? " and g.area = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
		}

		MyQuery myQuery = new MyQuery();
		
		if (StringUtils.isNotEmpty(idCard)) {
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(enterenceNo)) {
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}
		
//		if (StringUtils.isNotEmpty(classIds)) {
//			myQuery.addPara(classIds, Types.VARCHAR);
//		}
	

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(province)) {
			myQuery.addPara(province, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(polity)) {
			myQuery.addPara(polity, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nationality)) {
			myQuery.addPara(nationality, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			myQuery.addPara(department, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(idType)) {
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}	
		
		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}
				

		myQuery.setPageSize(100);

		if (orderby == null || orderby.length() == 0) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentNo ");
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("enterenceNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.enterenceNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("gender")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.gender " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("majorin")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.majorin " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nation")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.nation " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("nationality")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.nationality " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("province")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.fromProvince " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("polityBg")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.polityBg " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("birthday")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.birthday " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("homeTelephone")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.homeTelephone " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("tempecardNo")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.tempecardNo " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("department")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.department " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("idType")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.idType " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("cultureMode")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.cultureMode " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("studentChar")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.studentChar " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("checkornot")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.checkornot " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		} else if (orderby != null && orderby.length() > 0
				&& orderby.equals("schoolornot")) {
			myQuery.setOffset(true);
			myQuery.setOrderby(" order by a.schoolornot " + odr);
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
		}

		else {
			orderedCheck = false;
			myQuery.setPageStartNo(0);
			myQuery.setOffset(false);
		}

		myQuery.setQueryString(hqlStr);
		entitys = studentmodelDAO.find(myQuery);
		List Temp_mng = classmodelDAO
				.find("select new map(b.id.classId as classId,c.managerName as managerName) from Classmodel a,Classmanager b,Managermodel c,Managermanagerrole d "
						+ "where a.classId=b.id.classId "
						+ "and b.id.managerId=c.managerId and c.managerId=d.id.managerId and d.id.roleId='21'");
		HashMap Hash_mng = new HashMap();
		for (int i = 0; i < Temp_mng.size(); i++) {
			HashMap temp = (HashMap) Temp_mng.get(i);
			Hash_mng.put(temp.get("classId"), temp.get("managerName"));
		}
		HashMap Hash_cls = new HashMap();
		List Temp_cls = classmodelDAO
				.find("select new map(a.classId as classId,a.classNo as classNo) from Classmodel a ");
		for (int i = 0; i < Temp_cls.size(); i++) {
			HashMap temp = (HashMap) Temp_cls.get(i);
			Hash_cls.put(temp.get("classId"), temp.get("classNo"));
		}
		HashMap Hash_col = new HashMap();
		List Temp_col = classmodelDAO
				.find("select new map(a.classId as classId,b.collegeName as collegeName) from Classmodel a,Collegemodel b"
						+ " where a.yxCollege.collegeId=b.collegeId ");
		for (int i = 0; i < Temp_col.size(); i++) {
			HashMap temp = (HashMap) Temp_col.get(i);
			Hash_col.put(temp.get("classId"), temp.get("collegeName"));
		}
		HashMap Hash_location = new HashMap();
		HashMap Hash_dormitory = new HashMap();
		HashMap Hash_roomNumber = new HashMap();
		HashMap Hash_area = new HashMap();

		List list_dorm = dormitorymodelDAO
				.find("select new map(a.dormitoryId as dormitoryId," +
						"b.dictCaption as location," +
						"c.dictCaption as dormitory," +
						"d.dictCaption as area," +
						"a.roomNumber as roomNumber) from"
						+ " Dormitorymodel a,Dictionary b,Dictionary c,Dictionary d " +
								"where a.location=b.id.dictValue and b.id.dictNo=20 "
						+ "and a.dormitory=c.id.dictValue and c.id.dictNo=21 " +
								"and a.area=d.id.dictValue and d.id.dictNo=17 ");
		for (int i = 0; i < list_dorm.size(); i++) {
			HashMap temp = (HashMap) list_dorm.get(i);
			Hash_location.put(temp.get("dormitoryId"), temp.get("location"));
			Hash_dormitory.put(temp.get("dormitoryId"), temp.get("dormitory"));
			Hash_area.put(temp.get("dormitoryId"), temp.get("area"));
			Hash_roomNumber
					.put(temp.get("dormitoryId"), temp.get("roomNumber"));
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_fromprovince = new HashMap();
		List Temp_fromprovince = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 10 ");
		for (int i = 0; i < Temp_fromprovince.size(); i++) {
			HashMap temp = (HashMap) Temp_fromprovince.get(i);
			Hash_fromprovince.put(temp.get("dictValue"), temp
					.get("dictCaption"));
		}

		HashMap Hash_Nationality = new HashMap();
		List Temp_Nationality = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 12 ");
		for (int i = 0; i < Temp_Nationality.size(); i++) {
			HashMap temp = (HashMap) Temp_Nationality.get(i);
			Hash_Nationality
					.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_PolityBg = new HashMap();
		List Temp_PolityBg = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 4 ");
		for (int i = 0; i < Temp_PolityBg.size(); i++) {
			HashMap temp = (HashMap) Temp_PolityBg.get(i);
			Hash_PolityBg.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Majorin = new HashMap();
		List Temp_Majorin = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 11 ");
		for (int i = 0; i < Temp_Majorin.size(); i++) {
			HashMap temp = (HashMap) Temp_Majorin.get(i);
			Hash_Majorin.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Nation = new HashMap();
		List Temp_Nation = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 2 ");
		for (int i = 0; i < Temp_Nation.size(); i++) {
			HashMap temp = (HashMap) Temp_Nation.get(i);
			Hash_Nation.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_Department = new HashMap();
		List Temp_Department = studentmodelDAO
				.find("select new map(a.deptCode as deptCode, a.deptName as deptName) from Department a ");
		for (int i = 0; i < Temp_Department.size(); i++) {
			HashMap temp = (HashMap) Temp_Department.get(i);
			Hash_Department.put(temp.get("deptCode"), temp.get("deptName"));
		}

		HashMap Hash_bathcardNo = new HashMap();
		List Temp_bathcardNo = studentmodelDAO
				.find("select new map(a.studentNo as studentNo,a.bathcardNo as bathcardNo)from StuCardfeeInfo a ");
		for (int i = 0; i < Temp_bathcardNo.size(); i++) {
			HashMap temp = (HashMap) Temp_bathcardNo.get(i);
			Hash_bathcardNo.put(temp.get("studentNo"), temp.get("bathcardNo"));
		}

		HashMap Hash_yuanxi = new HashMap();
		List Temp_yuanxi = classmodelDAO
				.find("select new map(a.id.dictValue as majorin,b.deptName as yuanxi) from Dictionary a,Department b"
						+ " where a.id.dictNo=11 and a.dictParent=b.deptCode ");
		for (int i = 0; i < Temp_yuanxi.size(); i++) {
			HashMap temp = (HashMap) Temp_yuanxi.get(i);
			Hash_yuanxi.put(temp.get("majorin"), temp.get("yuanxi"));
		}
		
		HashMap Hash_idType = new HashMap();
		List Temp_idType = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 29 ");
		for (int i = 0; i < Temp_idType.size(); i++) {
			HashMap temp = (HashMap) Temp_idType.get(i);
			Hash_idType.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_cultureMode = new HashMap();
		List Temp_cultureMode = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 26 ");
		for (int i = 0; i < Temp_cultureMode.size(); i++) {
			HashMap temp = (HashMap) Temp_cultureMode.get(i);
			Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		
		HashMap Hash_studentChar = new HashMap();
		List Temp_studentChar = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 27 ");
		for (int i = 0; i < Temp_studentChar.size(); i++) {
			HashMap temp = (HashMap) Temp_studentChar.get(i);
			Hash_studentChar.put(temp.get("dictValue"), temp.get("dictCaption"));
		}		

		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			if (orderby != null
					&& orderby.length() > 0
					&& ("college".equals(orderby) || "name".equals(orderby) || "assistant"
							.equals(orderby))) {
				String clsssIdCode = "";
				String clsmanagerStr = "";
				String classIdStr = "";
				String collegeIdStr = "";
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}

			}

			if (orderby != null
					&& orderby.length() > 0
					&& ("area".equals(orderby)
							||"location".equals(orderby)
							|| "dormitory".equals(orderby) || "roomNumber"
							.equals(orderby))) {
				String dromIdCode = "";
				String locationStr = "";
				String dormitoryStr = "";
				String areaStr = "";
				String roomNumberStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setArea(areaStr);
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_area.get(dromIdCode) != null) {
							areaStr = Hash_area.get(dromIdCode)
									.toString();
							studentwithallinfo.setArea(areaStr);
						}
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
					}
				}
			}

			String studentno = "";
			String deptname = "";
			if (!"".equals(studentwithallinfo.getStudentNo())) {// 淋浴卡
				studentno = studentwithallinfo.getStudentNo();
				if (Hash_bathcardNo.get(studentno) != null) {
					deptname = Hash_bathcardNo.get(studentno).toString();
					studentwithallinfo.setBathcardNo(deptname);
				}
			}

		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("college")) {
			// 书院排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getCollege();
					String stuName2 = (String) m2.getCollege();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0 && orderby.equals("name")) {
			// 班号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getClassId();
					String stuName2 = (String) m2.getClassId();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("assistant")) {
			// 辅导员排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getAssistant();
					String stuName2 = (String) m2.getAssistant();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("stuName")) {
			// 学生姓名排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getStuName();
					String stuName2 = (String) m2.getStuName();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("area")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getArea();
					String stuName2 = (String) m2.getArea();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getArea();
					String stuName2 = (String) m2.getArea();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}
		
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("location")) {
			// 校区排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getLocation();
					String stuName2 = (String) m2.getLocation();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};

			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("dormitory")) {
			// 楼号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getDormitory();
					String stuName2 = (String) m2.getDormitory();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("roomNumber")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getRoomnumber();
					String stuName2 = (String) m2.getRoomnumber();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("bathcardNo")) {
			// 宿舍号排序
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					StudentWithAllInfo m1 = (StudentWithAllInfo) o1;
					StudentWithAllInfo m2 = (StudentWithAllInfo) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.getBathcardNo();
					String stuName2 = (String) m2.getBathcardNo();
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c2.compareTo(c1);
				}
			};
			if ("desc".equals(odr)) {
				Collections.sort(entitys, comp1);
			} else if ("asc".equals(odr)) {
				Collections.sort(entitys, comp2);
			}
		}

		List subList = null;
		if (orderedCheck) {
			subList = entitys;
		} else {
			int startrow = 0;
			if (StringUtils.isNumeric(page)) {
				startrow = Integer.parseInt(page);
				if ((startrow + 100) < entitys.size()) {
					subList = entitys.subList(startrow, startrow + 100);
				} else {
					subList = entitys.subList(startrow, entitys.size());
				}
			} else {
				if ((startrow + 100) < entitys.size()) {
					subList = entitys.subList(0, 100);
				} else {
					subList = entitys.subList(0, entitys.size());
				}
			}
		}

		for (int i = 0; i < subList.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) subList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			String classIdStr = "";
			String collegeIdStr = "";
			if (!"college".equals(orderby) && !"name".equals(orderby)
					&& !"assistant".equals(orderby)) {
				if (!"".equals(studentwithallinfo.getClassId())
						&& studentwithallinfo.getClassId() != null) {
					if (clsssIdCode.equals(studentwithallinfo.getClassId())) {
						studentwithallinfo.setAssistant(clsmanagerStr);
						studentwithallinfo.setClassId(classIdStr);
						studentwithallinfo.setCollege(collegeIdStr);
					} else {
						clsssIdCode = studentwithallinfo.getClassId();
						if (Hash_mng.get(clsssIdCode) != null) {
							clsmanagerStr = Hash_mng.get(clsssIdCode)
									.toString();
							studentwithallinfo.setAssistant(clsmanagerStr);
						}
						if (Hash_cls.get(clsssIdCode) != null) {
							classIdStr = Hash_cls.get(clsssIdCode).toString();
							studentwithallinfo.setClassId(classIdStr);
						}
						if (Hash_col.get(clsssIdCode) != null) {
							collegeIdStr = Hash_col.get(clsssIdCode).toString();
							studentwithallinfo.setCollege(collegeIdStr);
						}
					}

				}
			}
			if (!"area".equals(orderby) &&!"location".equals(orderby) && !"dormitory".equals(orderby)
					&& !"roomNumber".equals(orderby)) {
				String dromIdCode = "";
				String areaStr = "";
				String locationStr = "";
				String dormitoryStr = "";
				String roomNumberStr = "";
				if (!"".equals(studentwithallinfo.getDormId())
						&& studentwithallinfo.getDormId() != null) {
					if (dromIdCode.equals(studentwithallinfo.getDormId())) {
						studentwithallinfo.setArea(areaStr);
						studentwithallinfo.setLocation(locationStr);
						studentwithallinfo.setDormitory(dormitoryStr);
						studentwithallinfo.setRoomnumber(roomNumberStr);
					} else {
						dromIdCode = studentwithallinfo.getDormId();
						if (Hash_area.get(dromIdCode) != null) {
							areaStr = Hash_area.get(dromIdCode)
									.toString();
							studentwithallinfo.setArea(areaStr);
						}
						if (Hash_location.get(dromIdCode) != null) {
							locationStr = Hash_location.get(dromIdCode)
									.toString();
							studentwithallinfo.setLocation(locationStr);
						}
						if (Hash_dormitory.get(dromIdCode) != null) {
							dormitoryStr = Hash_dormitory.get(dromIdCode)
									.toString();
							studentwithallinfo.setDormitory(dormitoryStr);
						}
						if (Hash_roomNumber.get(dromIdCode) != null) {
							roomNumberStr = Hash_roomNumber.get(dromIdCode)
									.toString();
							studentwithallinfo.setRoomnumber(roomNumberStr);
						}
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(studentwithallinfo.getGender())) {// 性别
				if (genderCode.equals(studentwithallinfo.getGender())) {
					studentwithallinfo.setGender(genderStr);
				} else {
					genderCode = studentwithallinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						studentwithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(studentwithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(studentwithallinfo
						.getFromProvince())) {
					studentwithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = studentwithallinfo.getFromProvince();
					if (Hash_fromprovince.get(fromProvinceCode) != null) {
						fromProvinceStr = Hash_fromprovince.get(
								fromProvinceCode).toString();
						studentwithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(studentwithallinfo.getNationality())) {// 国籍
				if (nationalityCode.equals(studentwithallinfo.getNationality())) {
					studentwithallinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = studentwithallinfo.getNationality();
					if (Hash_Nationality.get(nationalityCode) != null) {
						nationalityStr = Hash_Nationality.get(nationalityCode)
								.toString();
						studentwithallinfo.setNationality(nationalityStr);
					}
				}

			}
			String politybgCode = "";
			String politybgStr = "";
			if (!"".equals(studentwithallinfo.getPolityBg())) {// 政治面貌
				if (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					studentwithallinfo.setPolityBg(politybgStr);
				} else {
					politybgCode = studentwithallinfo.getPolityBg();
					if (Hash_PolityBg.get(politybgCode) != null) {
						politybgStr = Hash_PolityBg.get(politybgCode)
								.toString();
						studentwithallinfo.setPolityBg(politybgStr);
					}
				}

			}
			String deptCode = "";
			String deptStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 所属院系
				if (deptCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setDepartment(deptStr);
				} else {
					deptCode = studentwithallinfo.getMajorin();
					if (Hash_yuanxi.get(deptCode) != null) {
						deptStr = Hash_yuanxi.get(deptCode).toString();
						studentwithallinfo.setDepartment(deptStr);
					}
				}
			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = studentwithallinfo.getMajorin();
					if (Hash_Majorin.get(majorinCode) != null) {
						majorinStr = Hash_Majorin.get(majorinCode).toString();
						studentwithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(studentwithallinfo.getNation())) {// 民族
				if (nationCode.equals(studentwithallinfo.getNation())) {
					studentwithallinfo.setNation(nationStr);
				} else {
					nationCode = studentwithallinfo.getNation();
					if (Hash_Nation.get(nationCode) != null) {
						nationStr = Hash_Nation.get(nationCode).toString();
						studentwithallinfo.setNation(nationStr);
					}
				}

			}
			
			String idTypeCode = "";
			String idTypeStr = "";
			if (!"".equals(studentwithallinfo.getIdType())) {// 证件类型
				if (idTypeCode.equals(studentwithallinfo.getIdType())) {
					studentwithallinfo.setIdType(idTypeStr);
				} else {
					idTypeCode = studentwithallinfo.getIdType();
					if (Hash_idType.get(idTypeCode) != null) {
						idTypeStr = Hash_idType.get(idTypeCode).toString();
						studentwithallinfo.setIdType(idTypeStr);
					}
				}

			}	
			
			String cultureModeCode = "";
			String cultureModeStr = "";
			if (!"".equals(studentwithallinfo.getCultureMode())) {// 证件类型
				if (cultureModeCode.equals(studentwithallinfo.getCultureMode())) {
					studentwithallinfo.setCultureMode(cultureModeStr);
				} else {
					cultureModeCode = studentwithallinfo.getCultureMode();
					if (Hash_cultureMode.get(cultureModeCode) != null) {
						cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
						studentwithallinfo.setCultureMode(cultureModeStr);
					}
				}

			}
			
			String studentCharCode = "";
			String studentCharStr = "";
			if (!"".equals(studentwithallinfo.getStudentChar())) {// 证件类型
				if (studentCharCode.equals(studentwithallinfo.getStudentChar())) {
					studentwithallinfo.setStudentChar(studentCharStr);
				} else {
					studentCharCode = studentwithallinfo.getStudentChar();
					if (Hash_studentChar.get(studentCharCode) != null) {
						studentCharStr = Hash_studentChar.get(studentCharCode).toString();
						studentwithallinfo.setStudentChar(studentCharStr);
					}
				}

			}				

			// String deptCode = "";
			// String deptStr = "";
			// if (!"".equals(studentwithallinfo.getDepartment())) {// 所属院系
			// if (deptCode.equals(studentwithallinfo.getDepartment())) {
			// studentwithallinfo.setDepartment(deptStr);
			// } else {
			// deptCode = studentwithallinfo.getDepartment();
			// if (Hash_Department.get(deptCode) != null) {
			// deptStr = Hash_Department.get(deptCode).toString();
			// studentwithallinfo.setDepartment(deptStr);
			// }
			// }
			//
			// }

		}
		return subList;

	}

	public Integer getStudentCount(String[] args,String schoolId) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];

		String college = args[6];
		String classes = args[7];
		String location = args[8];
		String dormitory = args[9];
		String roomnumber = args[10];
		String assistant = args[11];
		String majorin = args[12];
		String nationality = args[13];
		
		String department = args[17];
		
		String area = args[18];
		
		String idType = args[19];
		String cultureMode = args[20];
		String studentChar = args[21];
		String checkornot = args[22];
		String schoolornot = args[23];	
		String enterenceNo = args[24];	
		String idCard = args[25];			
		
		Integer stuCount = new Integer("0");
		List entitys = null;
		
		String datebuf = sdf1.format(new Date());//当前年份

		String hqlStr = "select count(distinct a.studentId) "
				+ " from Studentmodel a ";
		if (StringUtils.isNotEmpty(college) || StringUtils.isNotEmpty(classes)) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += ",Classmanager d,Managermodel e,Managermanagerrole f ";
		}

		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)
				|| StringUtils.isNotEmpty(area)) {
			hqlStr += ",Dormitorymodel g ";
		}

		hqlStr += "where 1=1 ";
		if(schoolId!=null&&!"".equals(schoolId)&&schoolId.equals("0002")){//护理学院
			//-------------------------------------------------
			hqlStr +=" and a.majorin='623' ";
		}else if(schoolId!=null&&!"".equals(schoolId)&&schoolId.equals("0001")){
			//-------------------------------------------------复旦学院
			hqlStr +=" and a.majorin<>'623' ";
		}
		hqlStr +=" and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";

		MyQuery myQuery = new MyQuery();
		
		if (StringUtils.isNotEmpty(idCard)) {
			hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?": "");
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(enterenceNo)) {

			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?": "");
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(studentNo)) {

			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?": "");
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(province)) {
			hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
					: "");
			myQuery.addPara(province, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(polity)) {
			hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");
			myQuery.addPara(polity, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?" : "");
			myQuery.addPara(department, Types.VARCHAR);
		}		
		
		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
			myQuery.addPara(majorin, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(nationality)) {
			hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
					: "");
			myQuery.addPara(nationality, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(college)) {
			myQuery.addPara(college, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(college) || StringUtils.isNotEmpty(classes)) {
			hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
			hqlStr += (StringUtils.isNotEmpty(college) ? " and c.collegeId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " and b.classId = ?"
					: "");
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}

		}


		if (StringUtils.isNotEmpty(assistant)) {
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += " and a.yxClass.classId=d.id.classId and d.id.managerId=e.managerId "
						+ " and e.managerId=f.id.managerId and f.id.roleId='21' ";
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.managerId = ?"
						: "");
			}
			myQuery.addPara(assistant, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(idType)) {
			hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
					: "");
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
					: "");
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}	
		
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)|| StringUtils.isNotEmpty(area)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(area) ? " and g.area = ? "
					: "");
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
		}	

		myQuery.setQueryString(hqlStr);

		entitys = studentmodelDAO.find(myQuery);
		if (entitys != null) {
			stuCount = (Integer) entitys.get(0);
		}
		return stuCount;

	}

	public Integer getfdyStudentCount(String[] args, String classId) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];
		String location = args[6];
		String dormitory = args[7];
		String roomnumber = args[8];
		String majorin = args[9];
		String nationality = args[10];
		
		String department = args[14];	
		
		String idType = args[15];
		String cultureMode = args[16];
		String studentChar = args[17];
		String checkornot = args[18];
		String schoolornot = args[19];
		String enterenceNo = args[20];
		String idCard = args[21];
		
		Integer stuCount = new Integer("0");
		List entitys = null;

		String hqlStr = "select count(distinct a.studentId) "
				+ " from Studentmodel a ";
		if (StringUtils.isNotEmpty(classId)) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}

		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += ",Dormitorymodel g ";
		}

		hqlStr += "where 1=1 ";
		hqlStr +=" and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";	
		
		MyQuery myQuery = new MyQuery();
		if (StringUtils.isNotEmpty(idCard)) {
			hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?"
					: "");			
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(studentNo)) {
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
					: "");			
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(enterenceNo)) {
			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?"
					: "");			
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");			
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");			
			myQuery.addPara(nation, Types.VARCHAR);
		}			

		if (StringUtils.isNotEmpty(province)) {
			hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
					: "");			
			myQuery.addPara(province, Types.VARCHAR);
		}		

		if (StringUtils.isNotEmpty(polity)) {
			hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");			
			myQuery.addPara(polity, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");			
			myQuery.addPara(majorin, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(nationality)) {
			hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
					: "");			
			myQuery.addPara(nationality, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?"
					: "");			
			myQuery.addPara(department, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(idType)) {
			hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
					: "");
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
					: "");	
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}
		
		if (StringUtils.isNotEmpty(classId)) {
			if (StringUtils.isNotEmpty(classId)) {
				hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
				hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?"
						: "");
			}			
			myQuery.addPara(classId, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}

			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
		}			

		myQuery.setQueryString(hqlStr);

		entitys = studentmodelDAO.find(myQuery);
		if (entitys != null) {
			stuCount = (Integer) entitys.get(0);
		}
		return stuCount;

	}
	
	public Integer getfdyStudentCount_hlxy(String[] args, List classlist) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String polity = args[5];
		String location = args[6];
		String dormitory = args[7];
		String roomnumber = args[8];
		String majorin = args[9];
		String nationality = args[10];
		
		String department = args[14];		
		String area = args[15];
		
		String idType = args[16];
		String cultureMode = args[17];
		String studentChar = args[18];
		String checkornot = args[19];
		String schoolornot = args[20];	
		
		String classIds = args[21];
		String enterenceNo = args[22];
		String idCard = args[23];		
		Integer stuCount = new Integer("0");
		List entitys = null;

		String hqlStr = "select count(distinct a.studentId) "
				+ " from Studentmodel a ";
		if (classlist!=null&&classlist.size()>0) {
			hqlStr += ",Classmodel b,Collegemodel c ";
		}

		if (StringUtils.isNotEmpty(area)
				||StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += ",Dormitorymodel g ";
		}

		hqlStr += "where 1=1 and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
		hqlStr += (StringUtils.isNotEmpty(idCard) ? " and a.idCard like ?"
				: "");		
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and a.enterenceNo like ?"
				: "");		
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and a.yxClass.classId = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(polity) ? " and a.polityBg = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(department) ? " and a.department = ?"
				: "");	
		
		
		hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
				: "");			

		if (classlist!=null&&classlist.size()>0) {
			hqlStr += " and a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId ";
			
			
			hqlStr += "and b.classId in(";
			if(classlist!=null&&classlist.size()>0){
				for(int i=0;i<classlist.size();i++){
					HashMap hashmap =  (HashMap)classlist.get(i);
					String classId = (String)hashmap.get("classId");
					hqlStr += "'"+classId + "',";
				}
				
			}
			hqlStr = hqlStr.substring(0,(hqlStr.length()-1));
			hqlStr += ") ";			
//			hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?"
//					: "");
		}
		
		if (StringUtils.isNotEmpty(area)
				||StringUtils.isNotEmpty(location)
				|| StringUtils.isNotEmpty(dormitory)
				|| StringUtils.isNotEmpty(roomnumber)) {
			hqlStr += " and a.dormId=g.dormitoryId ";
			hqlStr += (StringUtils.isNotEmpty(area) ? " and g.area = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(location) ? " and g.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and g.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and g.roomNumber = ?"
					: "");
		}

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(idCard)) {
			myQuery.addPara("%" + idCard + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(enterenceNo)) {
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}
		
//		if (StringUtils.isNotEmpty(classIds)) {
//			myQuery.addPara(classIds, Types.VARCHAR);
//		}
	

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(province)) {
			myQuery.addPara(province, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(polity)) {
			myQuery.addPara(polity, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nationality)) {
			myQuery.addPara(nationality, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(department)) {
			myQuery.addPara(department, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(idType)) {
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}	
		
		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr);

		entitys = studentmodelDAO.find(myQuery);
		if (entitys != null) {
			stuCount = (Integer) entitys.get(0);
		}
		return stuCount;

	}

	public List findStudent(String[] args) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String majorin = args[5];
		String nationality = args[6];
		String collegeId = args[7];
		String classId = args[8];
		String page = args[9];

		String idType = "";
		String cultureMode = "";
		String studentChar = "";
		String checkornot = "";
		String schoolornot = "";

		if(args.length>10){
			idType = args[10];
			cultureMode = args[11];
			studentChar = args[12];
			checkornot = args[13];
			schoolornot = args[14];
		}
		List entitys = null;

		String hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
				+ "('',a.yxClass.classId,'','','','', "
				+ "a.studentId,a.studentNo, a.enterenceNo, a.examNo,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
				+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
				+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
				+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
				+ "from Studentmodel a ";
		if (StringUtils.isNotEmpty(collegeId)
				|| StringUtils.isNotEmpty(classId)) {
			hqlStr += ",Classmodel b ";
		}

		hqlStr += "where (a.dormId='' or a.dormId is null)  and a.majorin<>'623' ";
		if (StringUtils.isNotEmpty(collegeId)
				|| StringUtils.isNotEmpty(classId)) {
			hqlStr += " and a.yxClass.classId=b.classId  ";
		}
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(collegeId) ? " and b.yxCollege.collegeId = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?" : "");
		
		String datebuf = sdf1.format(new Date());//当前年份
	
		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.enrollYear = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
				: "");	
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(province)) {
			myQuery.addPara(province, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nationality)) {
			myQuery.addPara(nationality, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(collegeId)) {
			myQuery.addPara(collegeId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(idType)) {
			myQuery.addPara(idType, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(cultureMode)) {
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setOrderby(" order by a.studentNo");
		myQuery.setQueryString(hqlStr);
		myQuery.setPageSize(100);
		myQuery.setOffset(true);
		entitys = studentmodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			if (!"".equals(studentwithallinfo.getClassId())
					&& studentwithallinfo.getClassId() != null) {
				List list_mng = classmodelDAO
						.find("select c.managerName from Classmodel a,Classmanager b,Managermodel c,Managermanagerrole d "
								+ "where a.classId='"
								+ studentwithallinfo.getClassId()
								+ "' and a.classId=b.id.classId "
								+ "and b.id.managerId=c.managerId and c.managerId=d.id.managerId and d.id.roleId='21'");
				if (list_mng.size() > 0) {
					String clsmanager = list_mng.get(0).toString();
					studentwithallinfo.setAssistant(clsmanager);

				}
				List list_cls = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b"
								+ " where a.classId='"
								+ studentwithallinfo.getClassId()
								+ "' and a.yxCollege.collegeId=b.collegeId ");
				if (list_cls.size() > 0) {
					Object[] classmodel = (Object[]) list_cls.get(0);
					studentwithallinfo.setClassId(classmodel[0].toString());
					studentwithallinfo.setCollege(classmodel[1].toString());
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(studentwithallinfo.getGender())
					&& studentwithallinfo.getGender() != null) {// 性别
				if (genderCode.equals(studentwithallinfo.getGender())) {
					studentwithallinfo.setGender(genderStr);
				} else {
					genderCode = studentwithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						studentwithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(studentwithallinfo.getFromProvince())
					&& studentwithallinfo.getFromProvince() != null) {// 生源地
				if (fromProvinceCode.equals(studentwithallinfo
						.getFromProvince())) {
					studentwithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = studentwithallinfo.getFromProvince();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 10 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getFromProvince()
									+ "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						fromProvinceStr = Cap;
						studentwithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(studentwithallinfo.getNationality())
					&& studentwithallinfo.getNationality() != null) {// 国籍
				if (nationalityCode.equals(studentwithallinfo.getNationality())) {
					studentwithallinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = studentwithallinfo.getNationality();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 12 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getNationality() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationalityStr = Cap;
						studentwithallinfo.setNationality(nationalityStr);
					}
				}

			}
			String politybgCode = "";
			String politybgStr = "";
			if (!"".equals(studentwithallinfo.getPolityBg())
					&& studentwithallinfo.getPolityBg() != null) {// 政治面貌
				if (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					studentwithallinfo.setPolityBg(politybgStr);
				} else {
					politybgCode = studentwithallinfo.getPolityBg();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 4 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getPolityBg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						politybgStr = Cap;
						studentwithallinfo.setPolityBg(politybgStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())
					&& studentwithallinfo.getMajorin() != null) {// 专业
				if (majorinCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = studentwithallinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						studentwithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(studentwithallinfo.getNation())
					&& studentwithallinfo.getNation() != null) {// 民族
				if (nationCode.equals(studentwithallinfo.getNation())) {
					studentwithallinfo.setNation(nationStr);
				} else {
					nationCode = studentwithallinfo.getNation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 2 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getNation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationStr = Cap;
						studentwithallinfo.setNation(nationStr);
					}
				}

			}
			String deptCode = "";
			String deptStr = "";
			if (!"".equals(studentwithallinfo.getDepartment())) {// 所属院系
				if (deptCode.equals(studentwithallinfo.getDepartment())) {
					studentwithallinfo.setDepartment(deptStr);
				} else {
					deptCode = studentwithallinfo.getDepartment();
					List cap_list = studentmodelDAO
							.find("select a.deptName from Department a where a.deptCode='"
									+ studentwithallinfo.getDepartment() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						deptStr = Cap;
						studentwithallinfo.setDepartment(deptStr);
					}
				}

			}
			
//			HashMap Hash_idType = new HashMap();
//			List Temp_idType = studentmodelDAO
//					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
//							+ "from Dictionary a where a.id.dictNo= 29 ");
//			for (int i1 = 0; i < Temp_idType.size(); i1++) {
//				HashMap temp = (HashMap) Temp_idType.get(i);
//				Hash_idType.put(temp.get("dictValue"), temp.get("dictCaption"));
//			}
//			
//			HashMap Hash_cultureMode = new HashMap();
//			List Temp_cultureMode = studentmodelDAO
//					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
//							+ "from Dictionary a where a.id.dictNo= 26 ");
//			for (int i2 = 0; i < Temp_cultureMode.size(); i2++) {
//				HashMap temp = (HashMap) Temp_cultureMode.get(i);
//				Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
//			}
//			
//			HashMap Hash_studentChar = new HashMap();
//			List Temp_studentChar = studentmodelDAO
//					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
//							+ "from Dictionary a where a.id.dictNo= 27 ");
//			for (int i3 = 0; i < Temp_studentChar.size(); i3++) {
//				HashMap temp = (HashMap) Temp_studentChar.get(i);
//				Hash_studentChar.put(temp.get("dictValue"), temp.get("dictCaption"));
//			}			
//			
//			String idTypeCode = "";
//			String idTypeStr = "";
//			if (!"".equals(studentwithallinfo.getIdCard())) {// 证件类型
//				if (idTypeCode.equals(studentwithallinfo.getIdCard())) {
//					studentwithallinfo.setIdType(idTypeStr);
//				} else {
//					idTypeCode = studentwithallinfo.getIdCard();
//					if (Hash_idType.get(idTypeCode) != null) {
//						idTypeStr = Hash_idType.get(idTypeCode).toString();
//						studentwithallinfo.setIdType(idTypeStr);
//					}
//				}
//
//			}	
//			
//			String cultureModeCode = "";
//			String cultureModeStr = "";
//			if (!"".equals(studentwithallinfo.getCultureMode())) {// 证件类型
//				if (cultureModeCode.equals(studentwithallinfo.getCultureMode())) {
//					studentwithallinfo.setCultureMode(cultureModeStr);
//				} else {
//					cultureModeCode = studentwithallinfo.getCultureMode();
//					if (Hash_cultureMode.get(cultureModeCode) != null) {
//						cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
//						studentwithallinfo.setCultureMode(cultureModeStr);
//					}
//				}
//
//			}
//			
//			String studentCharCode = "";
//			String studentCharStr = "";
//			if (!"".equals(studentwithallinfo.getStudentChar())) {// 证件类型
//				if (studentCharCode.equals(studentwithallinfo.getStudentChar())) {
//					studentwithallinfo.setStudentChar(studentCharStr);
//				} else {
//					studentCharCode = studentwithallinfo.getStudentChar();
//					if (Hash_studentChar.get(studentCharCode) != null) {
//						studentCharStr = Hash_studentChar.get(studentCharCode).toString();
//						studentwithallinfo.setStudentChar(studentCharStr);
//					}
//				}
//
//			}	
			
			if (!"".equals(studentwithallinfo.getStudentNo())) {// 淋浴卡
				List cap_list = studentmodelDAO
						.find("select a.bathcardNo from StuCardfeeInfo a where a.studentNo='"
								+ studentwithallinfo.getStudentNo() + "'");

				if (cap_list.size() > 0) {
					if (cap_list.get(0) != null) {
						String Cap = cap_list.get(0).toString();
						studentwithallinfo.setBathcardNo(Cap);
					}
				}
			}
		}
		return entitys;
	}

	public List findStudentExport(String[] args) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String majorin = args[5];
		String nationality = args[6];
		String collegeId = args[7];
		String classId = args[8];
		String page = args[9];
		
		String idType = "";
		String cultureMode = "";
		String studentChar = "";
		String checkornot = "";
		String schoolornot = "";

		if(args.length>10){
			idType = args[10];
			cultureMode = args[11];
			studentChar = args[12];
			checkornot = args[13];
			schoolornot = args[14];
		}
		List entitys = null;
		
		String datebuf = sdf1.format(new Date());//当前年份	

		String hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
			+ "('',a.yxClass.classId,'','','','', "
			+ "a.studentId,a.studentNo, a.enterenceNo, a.examNo,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
			+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
			+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
			+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
			+ "from Studentmodel a ";
		if (StringUtils.isNotEmpty(collegeId)
				|| StringUtils.isNotEmpty(classId)) {
			hqlStr += ",Classmodel b ";
		}
	
		hqlStr += "where (a.dormId='' or a.dormId is null)  and a.majorin<>'623' ";
		if (StringUtils.isNotEmpty(collegeId)
				|| StringUtils.isNotEmpty(classId)) {
			hqlStr += " and a.yxClass.classId=b.classId  ";
		}
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(collegeId) ? " and b.yxCollege.collegeId = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?" : "");
		
//		String datebuf = sdf1.format(new Date());//当前年份
	
		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.enrollYear = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(idType) ? " and a.idType = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
				: "");	
		
		MyQuery myQuery = new MyQuery();
	
		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(province)) {
			myQuery.addPara(province, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(nationality)) {
			myQuery.addPara(nationality, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(collegeId)) {
			myQuery.addPara(collegeId, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}	
		
		if (StringUtils.isNotEmpty(idType)) {
			myQuery.addPara(idType, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(cultureMode)) {
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(studentChar)) {
			myQuery.addPara(studentChar, Types.VARCHAR);
		}
	
		if (StringUtils.isNotEmpty(checkornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}
		
		myQuery.setOrderby(" order by a.studentNo");
		myQuery.setQueryString(hqlStr);
		entitys = studentmodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			StudentWithAllInfo studentwithallinfo = (StudentWithAllInfo) entitys
					.get(i);
			if (!"".equals(studentwithallinfo.getClassId())
					&& studentwithallinfo.getClassId() != null) {
				List list_mng = classmodelDAO
						.find("select c.managerName from Classmodel a,Classmanager b,Managermodel c,Managermanagerrole d "
								+ "where a.classId='"
								+ studentwithallinfo.getClassId()
								+ "' and a.classId=b.id.classId "
								+ "and b.id.managerId=c.managerId and c.managerId=d.id.managerId and d.id.roleId='21'");
				if (list_mng.size() > 0) {
					String clsmanager = list_mng.get(0).toString();
					studentwithallinfo.setAssistant(clsmanager);

				}
				List list_cls = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b"
								+ " where a.classId='"
								+ studentwithallinfo.getClassId()
								+ "' and a.yxCollege.collegeId=b.collegeId ");
				if (list_cls.size() > 0) {
					Object[] classmodel = (Object[]) list_cls.get(0);
					studentwithallinfo.setClassId(classmodel[0].toString());
					studentwithallinfo.setCollege(classmodel[1].toString());
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(studentwithallinfo.getGender())
					&& studentwithallinfo.getGender() != null) {// 性别
				if (genderCode.equals(studentwithallinfo.getGender())) {
					studentwithallinfo.setGender(genderStr);
				} else {
					genderCode = studentwithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						studentwithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(studentwithallinfo.getFromProvince())
					&& studentwithallinfo.getFromProvince() != null) {// 生源地
				if (fromProvinceCode.equals(studentwithallinfo
						.getFromProvince())) {
					studentwithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = studentwithallinfo.getFromProvince();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 10 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getFromProvince()
									+ "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						fromProvinceStr = Cap;
						studentwithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}

			String nationalityCode = "";
			String nationalityStr = "";
			if (!"".equals(studentwithallinfo.getNationality())
					&& studentwithallinfo.getNationality() != null) {// 国籍
				if (nationalityCode.equals(studentwithallinfo.getNationality())) {
					studentwithallinfo.setNationality(nationalityStr);
				} else {
					nationalityCode = studentwithallinfo.getNationality();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 12 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getNationality() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationalityStr = Cap;
						studentwithallinfo.setNationality(nationalityStr);
					}
				}

			}
			String politybgCode = "";
			String politybgStr = "";
			if (!"".equals(studentwithallinfo.getPolityBg())
					&& studentwithallinfo.getPolityBg() != null) {// 政治面貌
				if (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					studentwithallinfo.setPolityBg(politybgStr);
				} else {
					politybgCode = studentwithallinfo.getPolityBg();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 4 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getPolityBg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						politybgStr = Cap;
						studentwithallinfo.setPolityBg(politybgStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(studentwithallinfo.getMajorin())
					&& studentwithallinfo.getMajorin() != null) {// 专业
				if (majorinCode.equals(studentwithallinfo.getMajorin())) {
					studentwithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = studentwithallinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						studentwithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(studentwithallinfo.getNation())
					&& studentwithallinfo.getNation() != null) {// 民族
				if (nationCode.equals(studentwithallinfo.getNation())) {
					studentwithallinfo.setNation(nationStr);
				} else {
					nationCode = studentwithallinfo.getNation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 2 "
									+ "and a.id.dictValue='"
									+ studentwithallinfo.getNation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationStr = Cap;
						studentwithallinfo.setNation(nationStr);
					}
				}

			}
			String deptCode = "";
			String deptStr = "";
			if (!"".equals(studentwithallinfo.getDepartment())) {// 所属院系
				if (deptCode.equals(studentwithallinfo.getDepartment())) {
					studentwithallinfo.setDepartment(deptStr);
				} else {
					deptCode = studentwithallinfo.getDepartment();
					List cap_list = studentmodelDAO
							.find("select a.deptName from Department a where a.deptCode='"
									+ studentwithallinfo.getDepartment() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						deptStr = Cap;
						studentwithallinfo.setDepartment(deptStr);
					}
				}

			}

			
//			HashMap Hash_idType = new HashMap();
//			List Temp_idType = studentmodelDAO
//					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
//							+ "from Dictionary a where a.id.dictNo= 29 ");
//			for (int i1 = 0; i < Temp_idType.size(); i1++) {
//				HashMap temp = (HashMap) Temp_idType.get(i);
//				Hash_idType.put(temp.get("dictValue"), temp.get("dictCaption"));
//			}
//			
//			HashMap Hash_cultureMode = new HashMap();
//			List Temp_cultureMode = studentmodelDAO
//					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
//							+ "from Dictionary a where a.id.dictNo= 26 ");
//			for (int i2 = 0; i < Temp_cultureMode.size(); i2++) {
//				HashMap temp = (HashMap) Temp_cultureMode.get(i);
//				Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
//			}
//			
//			HashMap Hash_studentChar = new HashMap();
//			List Temp_studentChar = studentmodelDAO
//					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
//							+ "from Dictionary a where a.id.dictNo= 27 ");
//			for (int i3 = 0; i < Temp_studentChar.size(); i3++) {
//				HashMap temp = (HashMap) Temp_studentChar.get(i);
//				Hash_studentChar.put(temp.get("dictValue"), temp.get("dictCaption"));
//			}			
//			
//			String idTypeCode = "";
//			String idTypeStr = "";
//			if (!"".equals(studentwithallinfo.getIdCard())) {// 证件类型
//				if (idTypeCode.equals(studentwithallinfo.getIdCard())) {
//					studentwithallinfo.setIdType(idTypeStr);
//				} else {
//					idTypeCode = studentwithallinfo.getIdCard();
//					if (Hash_idType.get(idTypeCode) != null) {
//						idTypeStr = Hash_idType.get(idTypeCode).toString();
//						studentwithallinfo.setIdType(idTypeStr);
//					}
//				}
//
//			}	
//			
//			String cultureModeCode = "";
//			String cultureModeStr = "";
//			if (!"".equals(studentwithallinfo.getCultureMode())) {// 证件类型
//				if (cultureModeCode.equals(studentwithallinfo.getCultureMode())) {
//					studentwithallinfo.setCultureMode(cultureModeStr);
//				} else {
//					cultureModeCode = studentwithallinfo.getCultureMode();
//					if (Hash_cultureMode.get(cultureModeCode) != null) {
//						cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
//						studentwithallinfo.setCultureMode(cultureModeStr);
//					}
//				}
//
//			}			
//			
//			String studentCharCode = "";
//			String studentCharStr = "";
//			if (!"".equals(studentwithallinfo.getStudentChar())) {// 证件类型
//				if (studentCharCode.equals(studentwithallinfo.getStudentChar())) {
//					studentwithallinfo.setStudentChar(studentCharStr);
//				} else {
//					studentCharCode = studentwithallinfo.getStudentChar();
//					if (Hash_studentChar.get(studentCharCode) != null) {
//						studentCharStr = Hash_studentChar.get(studentCharCode).toString();
//						studentwithallinfo.setStudentChar(studentCharStr);
//					}
//				}
//
//			}				
			
			if (!"".equals(studentwithallinfo.getStudentNo())) {// 淋浴卡
				List cap_list = studentmodelDAO
						.find("select a.bathcardNo from StuCardfeeInfo a where a.studentNo='"
								+ studentwithallinfo.getStudentNo() + "'");

				if (cap_list.size() > 0) {
					if (cap_list.get(0) != null) {
						String Cap = cap_list.get(0).toString();
						studentwithallinfo.setBathcardNo(Cap);
					}
				}
			}
		}
		
		

		return entitys;
	}

	public Integer findStudentCount(String[] args) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String nation = args[3];
		String province = args[4];
		String majorin = args[5];
		String nationality = args[6];
		String collegeId = args[7];
		String classId = args[8];
		String page = args[9];
		
		String idType = "";
		String cultureMode = "";
		String studentChar = "";
		String checkornot = "";
		String schoolornot = "";

		if(args.length>10){
			idType = args[10];
			cultureMode = args[11];
			studentChar = args[12];
			checkornot = args[13];
			schoolornot = args[14];
		}
		
		List entitys = null;

		Integer stuCount = new Integer("0");
		String hqlStr = "select count(distinct a.studentId) "
				+ "from Studentmodel a ";
		if (StringUtils.isNotEmpty(collegeId)
				|| StringUtils.isNotEmpty(classId)) {
			hqlStr += ",Classmodel b ";
		}

		hqlStr += "where (a.dormId='' or a.dormId is null) and a.majorin<>'623' " +
				"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
		if (StringUtils.isNotEmpty(collegeId)
				|| StringUtils.isNotEmpty(classId)) {
			hqlStr += " and a.yxClass.classId=b.classId  ";
		}
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and a.nation = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(province) ? " and a.fromProvince = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and a.majorin = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(nationality) ? " and a.nationality = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(collegeId) ? " and b.yxCollege.collegeId = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and b.classId = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(cultureMode) ? " and a.cultureMode = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(studentChar) ? " and a.studentChar = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(checkornot) ? " and a.checkornot = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(schoolornot) ? " and a.schoolornot = ?"
				: "");	
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(province)) {
			myQuery.addPara(province, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nationality)) {
			myQuery.addPara(nationality, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(collegeId)) {
			myQuery.addPara(collegeId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(cultureMode)) {
			myQuery.addPara(cultureMode, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentChar)) {
			myQuery.addPara(studentChar, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(checkornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(checkornot)), Types.INTEGER);
		}
		if (StringUtils.isNotEmpty(schoolornot)) {
			myQuery.addPara(new Integer(Integer.parseInt(schoolornot)), Types.INTEGER);
		}
		myQuery.setQueryString(hqlStr);
		entitys = studentmodelDAO.find(myQuery);
		if (entitys != null) {
			stuCount = (Integer) entitys.get(0);
		}
		return stuCount;

	}

	public Integer getStudentDistributionResult() {
		Integer stuCount = new Integer("0");
		List list = studentmodelDAO
				.find("select count(a.studentId) from Studentmodel a where a.yxClass.classId is not null");
		if (list.size() > 0) {
			stuCount = (Integer) list.get(0);
		}
		return stuCount;

	}
	
	public Integer getStudentDistributionResult(String schoolId) {
		Integer stuCount = new Integer("0");
		List list = studentmodelDAO
				.find("select count(a.studentId) from Studentmodel a " +
						"where a.yxClass.classId is not null " +
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								" and a.yxClass.yxCollege.yxSchool.schoolId='"+schoolId+"' ");
		if (list.size() > 0) {
			stuCount = (Integer) list.get(0);
		}
		return stuCount;

	}
	
	public Integer getStudentDistributionResult4yg(String perCode) {
		Integer stuCount = new Integer("0");
		List list = studentmodelDAO
				.find("select count(a.id) from YxGraduate a,TabSsManager b where b.stuNo='"+perCode+"' " +
						" and a.distriction=b.tabSsDept.id and a.dormitoryId is not null and a.dormitoryId<>'' and a.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		if (list.size() > 0) {
			stuCount = (Integer) list.get(0);
		}
		return stuCount;
	}
	public Integer getDormDistributionResult() {
		Integer dormCount = new Integer("0");
		List list = studentmodelDAO
				.find("select count(distinct a.dormId) from Studentmodel a where a.dormId<>'' and a.dormId is not null");
		if (list.size() > 0) {
			dormCount = (Integer) list.get(0);
		}
		return dormCount;
	}
	
	public Integer getDormDistributionResult(String schoolId) {
		Integer dormCount = new Integer("0");
		List list = studentmodelDAO
				.find("select count(distinct a.dormId) from Studentmodel a " +
						"where a.dormId<>'' and a.dormId is not null " +
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"and a.yxClass.yxCollege.yxSchool.schoolId='"+schoolId+"' ");
		if (list.size() > 0) {
			dormCount = (Integer) list.get(0);
		}
		return dormCount;
	}

	public void deleteStudentDormDistribution() {
		List list = studentmodelDAO.find("from Studentmodel a where a.enrollYear='"+DateUtil.getNow("yyyy")+"' ");
		for (int i = 0; i < list.size(); i++) {
			Studentmodel studentmodel = (Studentmodel) list.get(i);
			studentmodel.setYxClass(null);
			studentmodel.setDormId(null);
			studentmodelDAO.update(studentmodel);
		}
		// jdbcTemplate
		// .execute("update ykt_fm.yx_student a set
		// a.dorm_id=null,a.class_id=null where a.dorm_id<>'' and a.dorm_id is
		// not null");
	}
	
	public void deleteStudentDormDistribution(String schoolId) {
		List list = studentmodelDAO.find("from Studentmodel a " +
				"where a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
						"and a.yxClass.yxCollege.yxSchool.schoolId='"+schoolId+"' ");
		for (int i = 0; i < list.size(); i++) {
			Studentmodel studentmodel = (Studentmodel) list.get(i);
			if(schoolId!=null&&schoolId.equals("0001"))
			    studentmodel.setYxClass(null);
			studentmodel.setDormId(null);
			studentmodelDAO.update(studentmodel);
		}
		// jdbcTemplate
		// .execute("update ykt_fm.yx_student a set
		// a.dorm_id=null,a.class_id=null where a.dorm_id<>'' and a.dorm_id is
		// not null");
	}
	
	public void deleteStudentDormDistribution4gy(String stuNo) {
		// TODO Auto-generated method stub
		List list = yxGraduateDAO.find("select a " +
				"from YxGraduate a,Dormitorymodel b,TabSsManager c " +
				"where a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
				" and a.dormitoryId = b.dormitoryId" +
				" and c.stuNo='"+stuNo+"' and c.tabSsDept.id=b.curDormDept " +
						"and a.dormitoryId is not null and a.dormitoryId<>''");
		for (int i = 0; i < list.size(); i++) {
			YxGraduate graduate = (YxGraduate) list.get(i);
			graduate.setDormitoryId(null);
			yxGraduateDAO.update(graduate);
		}
	}
	public void deleteAbroadStuClassDistribution() {
		List list = studentmodelDAO
				.find("from Studentmodel a where a.nationality<>'CHN'");
		for (int i = 0; i < list.size(); i++) {
			Studentmodel studentmodel = (Studentmodel) list.get(i);
			studentmodel.setYxClass(null);
			studentmodel.setDormId(null);
			studentmodelDAO.update(studentmodel);
		}
		// jdbcTemplate
		// .execute("update ykt_fm.yx_student a set a.class_id=null where
		// a.nationality<>'CHN'");
	}

	public List getAllMajorinInfo() {
		List majorList = classmodelDAO
				.find("select distinct a.majorin from Studentmodel a ");
		String majorinStr = "'',";
		for (int i = 0; i < majorList.size(); i++) {
			majorinStr += "'" + majorList.get(i).toString() + "',";
		}
		majorinStr = majorinStr.substring(0, majorinStr.lastIndexOf(","));
		return studentmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinInfo(c.dictCaption,b.deptName,"
						+ "a.id.dictValue,a.dictCaption) from Dictionary a,Department b,"
						+ "Dictionary c where a.id.dictNo=11 and a.id.dictValue in ("
						+ majorinStr
						+ ") "
						+ "and a.dictAvail<>0 and a.dictParent=b.deptCode "
						+ "and a.dictParent1=c.id.dictValue and c.id.dictNo=14 "
						+ "and a.dictCaption not like '%武警班%' "
						+ "order by c.id.dictValue,b.deptCode,a.id.dictValue");
	}

	private String getAllMajorinInfoStr() {
		List majorinList = getAllMajorinInfo();
		String majorinStr = "'',";
		for (int i = 0; i < majorinList.size(); i++) {
			MajorinInfo majoininfo = (MajorinInfo) majorinList.get(i);
			majorinStr += "'" + majoininfo.getDaima() + "',";
		}
		majorinStr = majorinStr.substring(0, majorinStr.lastIndexOf(","));
		return majorinStr;
	}

	public List getCHNStudentCount() {
		String majorinStr = getAllMajorinInfoStr();
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinWithStuCount"
						+ "(a.majorin,count(a.studentId),0,0) "
						+ "from Studentmodel a "
						+ "where a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						// + "where a.enrollYear='2005' "
						+ "and a.majorin in ("
						+ majorinStr
						+ ") group by a.majorin ");
		List maleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinWithStuCount"
						+ "(a.majorin,0,count(a.studentId),0) "
						+ "from Studentmodel a "
						+ "where a.nationality='CHN' and a.gender='1' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						// + "where a.nationality='CHN' and a.gender='1' and
						// a.enrollYear='2005' "
						+ "and a.majorin in ("
						+ majorinStr
						+ ") "
						+ "group by a.majorin ");
		List femaleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinWithStuCount"
						+ "(a.majorin,0,0,count(a.studentId)) "
						+ "from Studentmodel a "
						+ "where a.nationality='CHN' and a.gender='2' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						// + "where a.nationality='CHN' and a.gender='2' and
						// a.enrollYear='2005' "
						+ "and a.majorin in ("
						+ majorinStr
						+ ") "
						+ "group by a.majorin ");
		int allMale = 0;
		int allFemale = 0;
		int allSum = 0;
		for (int i = 0; i < list.size(); i++) {
			MajorinWithStuCount majorinwithstucount = (MajorinWithStuCount) list
					.get(i);
			for (int j = 0; j < maleList.size(); j++) {
				MajorinWithStuCount male = (MajorinWithStuCount) maleList
						.get(j);
				String majorinmale = male.getMajorinCode();
				if (majorinmale.equals(majorinwithstucount.getMajorinCode())) {
					majorinwithstucount.setStuMaleCount(male.getStuMaleCount());
					maleList.remove(j);
					break;
				}
			}
			for (int k = 0; k < femaleList.size(); k++) {
				MajorinWithStuCount female = (MajorinWithStuCount) femaleList
						.get(k);
				String majorinfemale = female.getMajorinCode();
				if (majorinfemale.equals(majorinwithstucount.getMajorinCode())) {
					majorinwithstucount.setStuFemaleCount(female
							.getStuFemaleCount());
					femaleList.remove(k);
					break;
				}
			}
			allMale += majorinwithstucount.getStuMaleCount();
			allFemale += majorinwithstucount.getStuFemaleCount();
			allSum += majorinwithstucount.getStuCount();
			if (i == list.size() - 1) {
				MajorinWithStuCount addstu = new MajorinWithStuCount("--", 0,
						0, 0);
				addstu.setStuCount(allSum);
				addstu.setStuMaleCount(allMale);
				addstu.setStuFemaleCount(allFemale);
				list.add(i + 1, addstu);
				break;
			}
		}
		return list;

	}

	public List getAbroadStudentCount() {
		String majorinStr = getAllMajorinInfoStr();
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinWithStuCount"
						+ "(a.majorin,count(a.studentId),0,0) "
						+ "from Studentmodel a "
						+ "where a.nationality<>'CHN' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						// + "where a.nationality<>'CHN' and
						// a.enrollYear='2005'"
						+ "and a.majorin in("
						+ majorinStr
						+ ") "
						+ "group by a.majorin ");
		int allSum = 0;
		for (int i = 0; i < list.size(); i++) {
			MajorinWithStuCount majorinwithstucount = (MajorinWithStuCount) list
					.get(i);
			allSum += majorinwithstucount.getStuCount();
			if (i == list.size() - 1) {
				MajorinWithStuCount addstu = new MajorinWithStuCount("--", 0,
						0, 0);
				addstu.setStuCount(allSum);
				list.add(i + 1, addstu);
				break;
			}
		}
		return list;
	}

	public List getCollegeCHNStudentCount() {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinWithStuCount"
						+ "(b.collegeId,count(a.studentId),0,0) "
						+ "from Studentmodel a,DistributionTemp b "
						+ "where a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						// + "where a.enrollYear='2005' "
						+ "and a.studentId=b.studentId "
						+ "group by b.collegeId ");
		List maleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinWithStuCount"
						+ "(b.collegeId,0,count(a.studentId),0) "
						+ "from Studentmodel a ,DistributionTemp b "
						+ "where a.nationality='CHN' and a.gender='1' "
						+ "and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						// + "where a.nationality='CHN' and a.gender='1' "
						// + "and a.enrollYear='2005' "
						+ "and a.studentId=b.studentId "
						+ "group by b.collegeId ");
		List femaleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinWithStuCount"
						+ "(b.collegeId,0,0,count(a.studentId)) "
						+ "from Studentmodel a ,DistributionTemp b "
						+ "where a.nationality='CHN' and a.gender='2' "
						+ "and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						// + "where a.nationality='CHN' and a.gender='2' "
						// + "and a.enrollYear='2005' "
						+ "and a.studentId=b.studentId "
						+ "group by b.collegeId ");
		int allMale = 0;
		int allFemale = 0;
		int allSum = 0;
		for (int i = 0; i < list.size(); i++) {
			MajorinWithStuCount majorinwithstucount = (MajorinWithStuCount) list
					.get(i);
			for (int j = 0; j < maleList.size(); j++) {
				MajorinWithStuCount male = (MajorinWithStuCount) maleList
						.get(j);
				String majorinmale = male.getMajorinCode();
				if (majorinmale.equals(majorinwithstucount.getMajorinCode())) {
					majorinwithstucount.setStuMaleCount(male.getStuMaleCount());
					maleList.remove(j);
					break;
				}
			}
			for (int k = 0; k < femaleList.size(); k++) {
				MajorinWithStuCount female = (MajorinWithStuCount) femaleList
						.get(k);
				String majorinfemale = female.getMajorinCode();
				if (majorinfemale.equals(majorinwithstucount.getMajorinCode())) {
					majorinwithstucount.setStuFemaleCount(female
							.getStuFemaleCount());
					femaleList.remove(k);
					break;
				}
			}
			allMale += majorinwithstucount.getStuMaleCount();
			allFemale += majorinwithstucount.getStuFemaleCount();
			allSum += majorinwithstucount.getStuCount();
			if (i == list.size() - 1) {
				MajorinWithStuCount addstu = new MajorinWithStuCount(
						"allCount", 0, 0, 0);
				addstu.setStuCount(allSum);
				addstu.setStuMaleCount(allMale);
				addstu.setStuFemaleCount(allFemale);
				list.add(i + 1, addstu);
				break;
			}
		}
		return list;
	}

	public List getCollegeAbroadStudentCount() {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinWithStuCount"
						+ "(b.collegeId,count(a.studentId),0,0) "
						+ "from Studentmodel a ,DistributionTemp b "
						+ "where a.nationality<>'CHN' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						// + "where a.nationality<>'CHN' and a.enrollYear='2005'
						// "
						+ "and a.studentId=b.studentId "
						+ "group by b.collegeId ");
		int allSum = 0;
		for (int i = 0; i < list.size(); i++) {
			MajorinWithStuCount majorinwithstucount = (MajorinWithStuCount) list
					.get(i);
			allSum += majorinwithstucount.getStuCount();
			if (i == list.size() - 1) {
				MajorinWithStuCount addstu = new MajorinWithStuCount(
						"allCount", 0, 0, 0);
				addstu.setStuCount(allSum);
				list.add(i + 1, addstu);
				break;
			}
		}
		return list;
	}

	public List getCollegeDormitoryStatistic() {
		List list_all = dormitorymodelDAO
				.find("select new map(c.collegeId as collegeId,sum(a.accomodation) as accomodation, '10' as flag) "
						+ "from Dormitorymodel a,Classmodel b,Collegemodel c where a.classId=b.classId "
						+ "and b.yxCollege.collegeId=c.collegeId group by c.collegeId");
		List list_male = dormitorymodelDAO
				.find("select  new map(c.collegeId as collegeId,sum(a.accomodation) as accomodation, '11' as flag) "
						+ "from Dormitorymodel a,Classmodel b,Collegemodel c where a.classId=b.classId "
						+ "and b.yxCollege.collegeId=c.collegeId and a.gender='1' group by c.collegeId");
		List list_female = dormitorymodelDAO
				.find("select new map(c.collegeId as collegeId,sum(a.accomodation) as accomodation, '12' as flag) "
						+ "from Dormitorymodel a,Classmodel b,Collegemodel c where a.classId=b.classId "
						+ "and b.yxCollege.collegeId=c.collegeId and a.gender='2' group by c.collegeId");
		List maleList = classmodelDAO
		.find("select new Map"
				+ "(b.collegeId as collegeId,count(a.studentId) as accomodation,'13' as flag) "
				+ "from Studentmodel a ,DistributionTemp b "
				+ "where a.nationality='CHN' and a.gender='1' "
				+ "and a.enrollYear='"
				+ DateUtil.getNow("yyyy")
				+ "' "
				// + "where a.nationality='CHN' and a.gender='1' "
				// + "and a.enrollYear='2005' "
				+ "and a.studentId=b.studentId "
				+ "group by b.collegeId ");
		List femaleList = classmodelDAO
		.find("select new Map"
				+ "(b.collegeId as collegeId,count(a.studentId) as accomodation,'14' as flag) "
				+ "from Studentmodel a ,DistributionTemp b "
				+ "where a.nationality='CHN' and a.gender='2' "
				+ "and a.enrollYear='"
				+ DateUtil.getNow("yyyy")
				+ "' "
				// + "where a.nationality='CHN' and a.gender='2' "
				// + "and a.enrollYear='2005' "
				+ "and a.studentId=b.studentId "
				+ "group by b.collegeId ");		
		if (list_all.size() > 0) {
			if (list_male.size() > 0) {
				list_all.addAll(list_male);
			}
			if (list_female.size() > 0) {
				list_all.addAll(list_female);
			}
			if (maleList.size() > 0) {
				list_all.addAll(maleList);
			}
			if (femaleList.size() > 0) {
				list_all.addAll(femaleList);
			}			
		}
		return list_all;
	}

	public List getHisDistribution() {
		List list = classmodelDAO.find("select distinct new map"
				+ "(b.collegeId as collegeId,a.majorin as majorin) "
				+ "from Studentmodel a ,DistributionTemp b "
				+ "where a.enrollYear='" + DateUtil.getNow("yyyy") + "' "
				// + "where a.enrollYear='2005' "
				+ "and a.studentId=b.studentId "
				+ "group by a.majorin,b.collegeId ");
		return list;
	}

	public List getCollegeDormitoryAll() {
		List list = classmodelDAO
				.find("select sum(a.accomodation) as accomodation,b.yxCollege.collegeId from Dormitorymodel a,classmodel b where a.yxClass.classId=b.classId group by b.yxCollege.collegeId");
		return list;
	}
	
	public void addstu(List stuList){
		
		Studentmodel sm=new Studentmodel();
		Map stu=(Map)stuList.get(0);
        if(stu.get("studentNo")!=null)
            sm.setStudentNo((String)stu.get("studentNo"));
        else
       	 sm.setStudentNo("");
        if(stu.get("enterenceNo")!=null)
       	 sm.setEnterenceNo((String)stu.get("enterenceNo"));
        else
       	 sm.setEnterenceNo("");
        if(stu.get("examNo")!=null)
       	 sm.setExamNo((String)stu.get("examNo"));
        else
       	 sm.setExamNo(null);
        if(stu.get("idCard")!=null)
       	 sm.setIdCard((String)stu.get("idCard"));
        else
       	 sm.setIdCard(null);
        if(stu.get("birthday")!=null)
       	 sm.setBirthday((String)stu.get("birthday"));
        else
       	 sm.setBirthday(null);
        if(stu.get("homeTelephone")!=null)
       	 sm.setHomeTelephone((String)stu.get("homeTelephone"));
        else
       	 sm.setHomeTelephone(null);
        if(stu.get("nation")!=null)
       	 sm.setNation((String)stu.get("nation"));
        else
       	 sm.setNation(null);
        if(stu.get("midSchCode")!=null)
       	 sm.setMidSchCode((String)stu.get("midSchCode"));
        else
       	 sm.setMidSchCode(null);
        if(stu.get("midSchName")!=null)
       	 sm.setMidSchName((String)stu.get("midSchName"));
        else
       	 sm.setMidSchName(null);
        if(stu.get("polityBg")!=null)
       	 sm.setPolityBg((String)stu.get("polityBg"));
        else
       	 sm.setPolityBg(null);
        if(stu.get("department")!=null)
       	 sm.setDepartment((String)stu.get("department"));
        else
       	 sm.setDepartment(null);
        if(stu.get("specIntrst")!=null)
       	 sm.setSpecIntrst((String)stu.get("specIntrst"));
        else
       	 sm.setSpecIntrst(null);
        if(stu.get("studentType")!=null)
       	 sm.setStudentType((String)stu.get("studentType"));
        else
       	 sm.setStudentType(null);
        if(stu.get("curGrade")!=null)
       	 sm.setCurGrade((String)stu.get("curGrade"));
        else
       	 sm.setCurGrade(null);
        if(stu.get("enrollYear")!=null)
       	 sm.setEnrollYear((String)stu.get("enrollYear"));
        else
       	 sm.setEnrollYear("");
        if(stu.get("stuName")!=null)
       	 sm.setStuName((String)stu.get("stuName"));
        else
       	 sm.setStuName(null);
        if(stu.get("gender")!=null)
       	 sm.setGender((String)stu.get("gender"));
        else
       	 sm.setGender(null);
        if(stu.get("majorin")!=null)
       	 sm.setMajorin((String)stu.get("majorin"));
        else
       	 sm.setMajorin(null);
        if(stu.get("fromProvince")!=null)
       	 sm.setFromProvince((String)stu.get("fromProvince"));
        else
       	 sm.setFromProvince(null);
        if(stu.get("nationality")!=null)
       	 sm.setNationality((String)stu.get("nationality"));
        else
       	 sm.setNationality(null);
        if(stu.get("idType")!=null)
          	 sm.setIdType((String)stu.get("idType"));
        else
          	 sm.setIdType(null);
        if(stu.get("cultureMode")!=null)
         	 sm.setCultureMode((String)stu.get("cultureMode"));
        else
         	 sm.setCultureMode(null);
        if(stu.get("studentChar")!=null)
        	 sm.setStudentChar((String)stu.get("studentChar"));
        else
        	 sm.setStudentChar(null);
        
        if(stu.get("checkornot")!=null)
       	     sm.setCheckornot((Integer)stu.get("checkornot"));
        else
       	     sm.setCheckornot(null);
        
        if(stu.get("schoolornot")!=null)
          	 sm.setSchoolornot((Integer)stu.get("schoolornot"));
        else
          	 sm.setSchoolornot(null);
        
        if(stu.get("adminCollege")!=null)
       	 sm.setAdminCollege((String)stu.get("adminCollege"));
        else
       	 sm.setAdminCollege(null);
        
        
        studentmodelDAO.save(sm);
        
        /**********加入相关表*************/
        //报到信息表
        Stucheckininfo stucheckininfo=new Stucheckininfo();
        stucheckininfo.setStudentNo(sm.getStudentNo());
        stucheckininfo.setEnrollNo(sm.getEnterenceNo());
        stucheckininfo.setEnrollYear(sm.getEnrollYear());
        stucheckininfo.setIfCheckedin("0");
        stucheckininfo.setReason("03");
        stucheckininfo.setIfChecked("0");
        stucheckininfo.setIfReserve("0");
        stucheckininfo.setIfLeaveSchool("0");
        stucheckininfo.setIfGotMaterial("0");
        stucheckininfo.setIfGotEcard("0");
        stucheckininfo.setIfGotStucard("0");
        stucheckininfo.setIfSubmitted("0");
        
        stucheckininfoDAO.save(stucheckininfo);
        
        //档案信息表
        Stuarchivesinfo stuarchivesinfo=new Stuarchivesinfo();
        stuarchivesinfo.setStudentNo(sm.getStudentNo());
        stuarchivesinfo.setEnrollNo(sm.getEnterenceNo());
        stuarchivesinfo.setEnrollYear(sm.getEnrollYear());
        stuarchivesinfo.setHasArchives("0");
        stuarchivesinfo.setHasStuarchive("0");
        stuarchivesinfo.setHasLeagueFile("0");
        stuarchivesinfo.setHasRegform("0");
        stuarchivesinfo.setIfSubmitted("0");
        stuarchivesinfo.setArchiveSubmit("0");
        
        stuarchivesinfoDAO.save(stuarchivesinfo);
        
        //卡费缴纳表
        StuCardfeeInfo stuCardfeeInfo=new StuCardfeeInfo();
        stuCardfeeInfo.setStudentNo(sm.getStudentNo());
        stuCardfeeInfo.setEnrollYear(sm.getEnrollYear());
        stuCardfeeInfo.setEcardPayed("0");
        stuCardfeeInfo.setBathcardPayed("0");
        
        stucardfeeinfoDAO.save(stuCardfeeInfo);
        
        //体检表
        Stuhealthinfo stuhealthinfo=new Stuhealthinfo();
        stuhealthinfo.setStudentNo(sm.getStudentNo());
        stuhealthinfo.setEnrollNo(sm.getEnterenceNo());
        stuhealthinfo.setEnrollYear(sm.getEnrollYear());
        stuhealthinfo.setIfUnhealthy("0");
        stuhealthinfo.setIfDeleted("0");
        
        stuhealthinfoDAO.save(stuhealthinfo);
       
        
        /******************************/
        //保存用户
			Account account = new Account();
			Person person = new Person();
			person.setPersonCode(sm.getStudentNo());
			person.setPersonName(sm.getStuName());
			person.setPersonType("2");
			person.setSex(sm.getGender());				
			
			account.setName(sm.getStudentNo());
			account.setEnabled("0");
			account.setPerson(person);
			accountDAO.save(account);
			
			List roleList = new ArrayList();
			String roleid ="";
			//授权
			List list = stuAdddelhisDAO.find("select a.id from Role a where a.name='新生'");
	       if (list.size() > 0) {
		        roleid = list.get(0).toString();
	       }
			
			if(roleid!=null&&roleid.length()>0)
				roleList.add(roleid);						
			String[] roleArr =  new String[roleList.size()];
			roleList.toArray(roleArr);
			try{
			grantAccountRoles(account.getId(),roleArr);
			}catch(Exception e){
				e.printStackTrace();
			}
	}

//	自己的方法
	public List find(String query){
		List result=null;
		try{
			result=studentmodelDAO.find(query);
			//System.out.println("find ok");
		}catch(Exception e){
			e.printStackTrace();
			//System.out.println("find error");
		}
		//if(result==null)
			//System.out.println("findresult is null");
		return result;
	}
	
	public List find(MyQuery query){
		List result=null;
		try{
			result=studentmodelDAO.find(query);
			//System.out.println("find ok");
		}catch(Exception e){
			e.printStackTrace();
			//System.out.println("find error");
		}
		//if(result==null)
			//System.out.println("findresult is null");
		return result;
	}
	
public Studentmodel findbyStuId(String stuid){
    	
	    Studentmodel studentmodel = null;
	    try{
	    	studentmodel = studentmodelDAO.findbyStuId(stuid);
	         return studentmodel;
	    }catch(Exception e){
			e.printStackTrace();
			System.out.println("find by id error");
		}
		if(studentmodel==null)
			System.out.println("stuarriveinfo is null");
		return studentmodel;
}
	
    public void saveAddStu(StuAdddelhis stuAdddelhis){
		
		try{
			stuAdddelhisDAO.save(stuAdddelhis);
			//System.out.println("add ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("add error");
		}
		
	}
    
    public void deleteStudent(Studentmodel studentmodel) {
		studentmodelDAO.delete(studentmodel);
	}
    
    public void deleteStu(Studentmodel studentmodel) {
    	
		studentmodelDAO.delete(studentmodel);
		
		List list=new ArrayList();
		//报到信息表
		list=classmodelDAO.find("from Stucheckininfo ci where ci.studentNo='"+studentmodel.getStudentNo()+"'");
		if(list!=null&&list.size()>0){	
		  for(int i=0;i<list.size();i++){
		    Stucheckininfo stucheckininfo=new Stucheckininfo();
		    stucheckininfo=(Stucheckininfo)list.get(i);
		    stucheckininfoDAO.delete(stucheckininfo);
		  }
		}
		//档案信息表
		list=classmodelDAO.find("from Stuarchivesinfo ci where ci.studentNo='"+studentmodel.getStudentNo()+"'");
		if(list!=null&&list.size()>0){	
		  for(int i=0;i<list.size();i++){
			Stuarchivesinfo stuarchivesinfo=new Stuarchivesinfo();
			stuarchivesinfo=(Stuarchivesinfo)list.get(i);
			stuarchivesinfoDAO.delete(stuarchivesinfo);
		  }
		}
		//卡费缴纳信息表
		list=classmodelDAO.find("from StuCardfeeInfo ci where ci.studentNo='"+studentmodel.getStudentNo()+"'");
		if(list!=null&&list.size()>0){	
		  for(int i=0;i<list.size();i++){
			StuCardfeeInfo stuCardfeeInfo=new StuCardfeeInfo();
			stuCardfeeInfo=(StuCardfeeInfo)list.get(i);
			stucardfeeinfoDAO.delete(stuCardfeeInfo);
		  }
		}
		//体检表
		list=classmodelDAO.find("from Stuhealthinfo ci where ci.studentNo='"+studentmodel.getStudentNo()+"'");
		if(list!=null&&list.size()>0){
		  for(int i=0;i<list.size();i++){
			Stuhealthinfo stuhealthinfo=new Stuhealthinfo();
			stuhealthinfo=(Stuhealthinfo)list.get(i);
			stuhealthinfoDAO.delete(stuhealthinfo);
		  }
		}
		
        //删除用户
	     List accList=stuAdddelhisDAO.find("select new Map(a.id as id) from Account a where a.name ='" + studentmodel.getStudentNo()+ "'");
	     
	     String accId = "";
	     if(accList!=null&&accList.size()>0)
	    	 accId=(String)((Map)accList.get(0)).get("id");
	     
		 if (accId!=null&&accId.length()>0) {
			 accountDAO.delete(accountDAO.get(accId));
		 }
	}
    
    public void grantAccountRoles(String accountId, String[] currentRole) throws BusinessException {
		Account account = accountDAO.get(accountId);
		Set currentAccountRole = new HashSet();
		if(currentRole!=null) {
			for(int i=0;i<currentRole.length;i++){
				currentAccountRole.add((Role)roleDAO.get(currentRole[i]));
			}
		}
		account.setRoles(currentAccountRole);
		accountDAO.update(account);
	}
    

	public void addConvertDorm(List stuList) throws EnterenceNoNotExistException,
	FamilyAddressNotExistException, StuNameNotExistException,
	TotalScoreNotExistException {
//        <!-- 录取通知书号-->
//        <!-- 姓名-->
//        <!-- 性别-->
//        <!-- 生日-->
//        <!-- 政治面貌-->
//        <!-- 国籍-->
//        <!-- 生源地-->
//        <!-- 入学年份-->
//        <!-- 录取院系-->
//        <!-- 录取专业-->
//        <!-- 民族-->
//        <!-- 上海地区-->
//        <!-- 家庭地址-->
//        <!-- 身份证-->
//        <!-- 邮编-->
//        <!-- 电话-->
//        <!-- 高考科类-->
//        <!-- 学生性质-->
//        <!-- 高考总分-->
//        <!-- 学生类别-->
//        <!-- 培养层次-->	

		String enterenceNo = "", stuName = "";
		String gender = "",genderNo = "", birthday = "";
		String polityBg = "",polityBgNo = "", nationality = "", nationalityNo = "";
		String fromProvince = "",fromProvinceNo = "",enrollYear="";
		String department = "",departmentNo = "",majorin="",majorinNo="";
		String nation = "",nationNo = "",district="",districtNo="";
		String familyAddress = "",idCard="";
		String postCode = "",telephone="";
		String examType = "",examTypeNo = "",enrollType="",enrollTypeNo="";	
		String totalScore = "",studentType="",studentTypeNo="";
		String cultureMode = "",cultureModeNo = "";	

		List genders = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=1");
		List polityBgs = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=4");
		List nationalitys = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=12");
		List fromProvinces = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=10");
		List departments = dormitorymodelDAO
				.find("from Department a where 1=1");
		List majorins = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=11");	
		List nations = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=2");
		List districts = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=23");
		List examTypes = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=25");
		List enrollTypes = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=27");
		List studentTypes = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=15");
		List cultureModes = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=26");	
		
		for (int j = 0; j < stuList.size(); j++) {
			
			Dictionary dict = new Dictionary();		
			
			enterenceNo = ""; stuName = "";
			gender = "";genderNo = ""; birthday = "";
			polityBg = "";polityBgNo = ""; nationality = ""; nationalityNo = "";
			fromProvince = "";fromProvinceNo = "";enrollYear="";
			department = "";departmentNo = "";majorin="";majorinNo="";
			nation = "";nationNo = "";district="";districtNo="";
			familyAddress = "";idCard="";
			postCode = "";telephone="";
			examType = "";examTypeNo = "";enrollType="";enrollTypeNo="";	
			totalScore = "";studentType="";studentTypeNo="";
			cultureMode = "";cultureModeNo = "";			
			
			GzStuTemp student = new GzStuTemp();
			List oneStu = (List) stuList.get(j);
			
			enterenceNo = oneStu.get(0).toString();
			stuName = oneStu.get(1).toString();
			gender = oneStu.get(2).toString();	
			birthday = oneStu.get(3).toString();
			nation = oneStu.get(4).toString();
			polityBg = oneStu.get(5).toString();
			department = oneStu.get(6).toString();			
			majorin = oneStu.get(7).toString();
			nationality = oneStu.get(8).toString();
			fromProvince = oneStu.get(9).toString();
//			enrollYear = oneStu.get(7).toString();				


			district = oneStu.get(10).toString();	
			familyAddress = oneStu.get(11).toString();
			postCode = oneStu.get(12).toString();
			telephone = oneStu.get(13).toString();	
			idCard = oneStu.get(14).toString();

			examType = oneStu.get(15).toString();	
			totalScore = oneStu.get(16).toString();	
			enrollType = oneStu.get(17).toString();

			studentType = oneStu.get(18).toString();				
			cultureMode = oneStu.get(19).toString();	
			
			if ("".equals(enterenceNo)) {
				throw new EnterenceNoNotExistException("enterenceNo.notexist");
			}
			if ("".equals(stuName)) {
				throw new StuNameNotExistException("stuName.notexist");
			}
			if ("".equals(familyAddress)) {
				throw new FamilyAddressNotExistException("familyAddress.notexist");
			}
			if ("".equals(totalScore)) {
				throw new TotalScoreNotExistException("totalScore.notexist");
			}	
			
			//性别			
			for (int i = 0; i < genders.size(); i++) {
				dict = (Dictionary) genders.get(i);
				if (dict.getDictCaption().equals(gender.trim())) {
					genderNo = dict.getId().getDictValue();
					break;
				}
			}	
			//政治面貌
			for (int i = 0; i < polityBgs.size(); i++) {
				dict = (Dictionary) polityBgs.get(i);
				if (dict.getDictCaption().equals(polityBg.trim())) {
					polityBgNo = dict.getId().getDictValue();
					break;
				}
			}
			//国籍
			for (int i = 0; i < nationalitys.size(); i++) {
				dict = (Dictionary) nationalitys.get(i);
				if (dict.getDictCaption().equals(nationality.trim())) {
					nationalityNo = dict.getId().getDictValue();
					break;
				}
			}
			//生源地		
			for (int i = 0; i < fromProvinces.size(); i++) {
				dict = (Dictionary) fromProvinces.get(i);
				if (dict.getDictCaption().equals(fromProvince.trim())) {
					fromProvinceNo = dict.getId().getDictValue();
					break;
				}
			}	
			//院系
			Department dicts = new Department();
			for (int i = 0; i < departments.size(); i++) {
				dicts = (Department) departments.get(i);
				if (dicts.getDeptName().equals(department.trim())) {
					departmentNo = dicts.getDeptCode();
					break;
				}
			}
			//专业
			for (int i = 0; i < majorins.size(); i++) {
				dict = (Dictionary) majorins.get(i);
				if (dict.getDictCaption().equals(majorin.trim())) {
					majorinNo = dict.getId().getDictValue();
					break;
				}
			}
			//民族		
			for (int i = 0; i < nations.size(); i++) {
				dict = (Dictionary) nations.get(i);
				if (dict.getDictCaption().equals(nation.trim())) {
					nationNo = dict.getId().getDictValue();
					break;
				}
			}	
			//上海地区
			for (int i = 0; i < districts.size(); i++) {
				dict = (Dictionary) districts.get(i);
				if (dict.getDictCaption().equals(district.trim())) {
					districtNo = dict.getId().getDictValue();
					break;
				}
			}
			//高考科类
			for (int i = 0; i < examTypes.size(); i++) {
				dict = (Dictionary) examTypes.get(i);
				if (dict.getDictCaption().equals(examType.trim())) {
					examTypeNo = dict.getId().getDictValue();
					break;
				}
			}
			//学生性质		
			for (int i = 0; i < enrollTypes.size(); i++) {
				dict = (Dictionary) enrollTypes.get(i);
				if (dict.getDictCaption().equals(enrollType.trim())) {
					enrollTypeNo = dict.getId().getDictValue();
					break;
				}
			}	
			//学生类别
			for (int i = 0; i < studentTypes.size(); i++) {
				dict = (Dictionary) studentTypes.get(i);
				if (dict.getDictCaption().equals(studentType.trim())) {
					studentTypeNo = dict.getId().getDictValue();
					break;
				}
			}		
			//培养层次
			for (int i = 0; i < cultureModes.size(); i++) {
				dict = (Dictionary) cultureModes.get(i);
				if (dict.getDictCaption().equals(cultureMode.trim())) {
					cultureModeNo = dict.getId().getDictValue();
					break;
				}
			}				


			

			String hql = " from GzStuTemp a where a.enterenceNo='"+enterenceNo+"' ";
			List list = studentmodelDAO.find(hql);
			if(list!=null&&list.size()>0){
				
				student = (GzStuTemp)list.get(0);
				student.setEnterenceNo(enterenceNo);//不允许为空
				student.setStuName(stuName);//不允许为空
//				student.setGender(genderNo);//code
//				student.setBirthday(birthday);
//				student.setPolityBg(polityBgNo);//code
//				student.setNationality(nationalityNo);//code
//				student.setFromProvince(fromProvinceNo);//code
//				student.setEnrollYear(DateUtil.getNow("yyyy"));//今年入学新生
//				student.setDepartment(departmentNo);//code
//				student.setMajorin(majorinNo);//code
//				student.setNation(nationNo);//code
//				student.setDistrict(districtNo);//code
//				student.setFamilyAddress(familyAddress);
//				student.setIdCard(idCard);
//				student.setPostCode(postCode);
//				student.setTelephone(telephone);
//				student.setExamType(examTypeNo);//code
//				student.setEnrollType(enrollTypeNo);//code
//				student.setTotalScore(Double.valueOf(totalScore));//double型
//				student.setStudentType(studentType);
//				student.setCultureMode(cultureModeNo);//code
				
				
				student.setEnterenceNo(enterenceNo);//不允许为空
				student.setStuName(stuName);//不允许为空
				student.setGender(genderNo);//code
				student.setBirthday(birthday);
				student.setPolityBg(polityBgNo);//code
				student.setNationality(nationalityNo);//code
				student.setFromProvince(fromProvinceNo);//code
				student.setEnrollYear(DateUtil.getNow("yyyy"));//今年入学新生
				student.setDepartment(departmentNo);//code
				student.setMajorin(majorinNo);//code
				student.setNation(nationNo);//code
				student.setDistrict(districtNo);//code
				
				if (lengthCheck(familyAddress, 180)) {
					student.setFamilyAddress(familyAddress);
				}else{
					student.setFamilyAddress("");
				}
				if (lengthCheck(idCard, 20)) {
					student.setIdCard(idCard);
				}else{
					student.setIdCard("");
				}
				if (lengthCheck(postCode, 10)) {
					student.setPostCode(postCode);
				}else{
					student.setPostCode("");
				}
				if (lengthCheck(telephone, 30)) {
					student.setTelephone(telephone);
				}else{
					student.setTelephone("");
				}
				
				student.setExamType(examTypeNo);//code
				student.setEnrollType(enrollTypeNo);//code
				
				student.setTotalScore(Double.parseDouble(totalScore));//double型
				
				student.setStudentType(studentTypeNo);//code
				student.setCultureMode(cultureModeNo);//code				
				
				
				studentmodelDAO.updateGzStuTemp(student);
			}else{
				student.setEnterenceNo(enterenceNo);//不允许为空
				student.setStuName(stuName);//不允许为空
				student.setGender(genderNo);//code
				student.setBirthday(birthday);
				student.setPolityBg(polityBgNo);//code
				student.setNationality(nationalityNo);//code
				student.setFromProvince(fromProvinceNo);//code
				student.setEnrollYear(DateUtil.getNow("yyyy"));//今年入学新生
				student.setDepartment(departmentNo);//code
				student.setMajorin(majorinNo);//code
				student.setNation(nationNo);//code
				student.setDistrict(districtNo);//code
				
				if (lengthCheck(familyAddress, 180)) {
					student.setFamilyAddress(familyAddress);
				}else{
					student.setFamilyAddress("");
				}
				if (lengthCheck(idCard, 20)) {
					student.setIdCard(idCard);
				}else{
					student.setIdCard("");
				}
				if (lengthCheck(postCode, 10)) {
					student.setPostCode(postCode);
				}else{
					student.setPostCode("");
				}
				if (lengthCheck(telephone, 30)) {
					student.setTelephone(telephone);
				}else{
					student.setTelephone("");
				}
				
				student.setExamType(examTypeNo);//code
				student.setEnrollType(enrollTypeNo);//code
				
				student.setTotalScore(Double.parseDouble(totalScore));//double型
				
				student.setStudentType(studentTypeNo);//code
				student.setCultureMode(cultureModeNo);//code
				
				studentmodelDAO.saveGzStuTemp(student);
			}


			

		
		}
		
	}
	
	public void addConvertTempecard(List stuList) throws EnterenceNoNotExistException,
	FamilyAddressNotExistException, StuNameNotExistException,
	TotalScoreNotExistException {
//        <!-- 学号号-->
//        <!-- 临时一卡通卡号-->

		String studentNo = "", tempecardNo = "";
		
		for (int j = 0; j < stuList.size(); j++) {
			
			Dictionary dict = new Dictionary();		
			
			studentNo = ""; tempecardNo = "";		
			
			Studentmodel student = new Studentmodel();
			List oneStu = (List) stuList.get(j);
			
			studentNo = oneStu.get(0).toString();
			tempecardNo = oneStu.get(1).toString();				
			
			if ("".equals(studentNo)) {
				throw new EnterenceNoNotExistException("enterenceNo.notexist");
			}
			if ("".equals(tempecardNo)) {
				throw new StuNameNotExistException("stuName.notexist");
			}	

			String hql = " from Studentmodel a where a.studentNo='"+studentNo+"' ";
			List list = studentmodelDAO.find(hql);
			if(list!=null&&list.size()>0){
				
				student = (Studentmodel)list.get(0);
//				student.setStudentNo(studentNo);//不允许为空
//				student.setTempecardNo(Integer.parseInt(tempecardNo));//不允许为空
				
				if (lengthCheck(tempecardNo, 15)) {
					student.setTempecardNo(tempecardNo);
				}else{
					throw new StuNameNotExistException("stuName.notexist");
				}			
				studentmodelDAO.update(student);
				
			}
		
		}
		
	}
	
	public boolean isIntegerVal(String val) {
		for (int i=0;i<val.length();i++){
		char p = val.charAt(i);
		if (p<'0'||p>'9')
			return	false;
		}
		return	true;
	}
	
	public boolean lengthCheck(String checkColumn, int length) {
		boolean result = false;
		
		if (checkColumn == null || "null".equals(checkColumn)){
			checkColumn = "";
		}
		
		if (checkColumn.length() <= length){
			result = true;
		}else{
			result = false;
		}
		return result;
	}
/**
 * 根据前缀和开始号自动生成学号
 * @param request
 */	
	public void AutoMakeByStartNo(HttpServletRequest request) throws MakeStuNoFailException {	
		
		String stuNoPrefix = request.getParameter("stuNoPrefix");//前缀
		String startNo = request.getParameter("startNo");//起始号

		if(stuNoPrefix!=null&&startNo!=null&&!"".equals(stuNoPrefix)&&!"".equals(startNo)){
			String hql = "select a from GzStuTemp a,Classmodel b where a.classId=b.classId and a.enrollYear='"
				+DateUtil.getNow("yyyy")
				+"'  order by b.classNo asc,a.gender desc,a.examType asc,a.totalScore desc ";
			List list = studentmodelDAO.find(hql);
			
			if(list!=null&&list.size()>0){
				int startNoInt = Integer.parseInt(startNo);
				
				int sumlen = startNoInt + list.size();
				
				String sumlenv = String.valueOf(sumlen);
				
				if(startNo.length()<sumlenv.length()){
						throw new MakeStuNoFailException("student.makeStuNoFail");			
				}else {
					
					for(int i=0;i<list.size();i++){
						
						int lens = startNo.length()-String.valueOf(startNoInt+i).length();
						String zeroStrs = "";
						if(lens>1){//字符串不够补0				
							for(int j=0;j<lens;j++){
								zeroStrs = zeroStrs+"0";
							}
						}else if(lens==1){
							zeroStrs = "0";
						}
						
						String studentNo = stuNoPrefix+zeroStrs+String.valueOf(startNoInt+i);
						GzStuTemp g = (GzStuTemp)list.get(i);
						
						g.setStudentNo(studentNo);//自动生成学号
						
						studentmodelDAO.updateGzStuTemp(g);//更新学生信息
						
					}
					request.setAttribute("stuNoPrefix", stuNoPrefix);
					request.setAttribute("startNo", startNo);
				}
			}
		
		}
		
	}
	
	public void getStudent_hlxy(HttpServletRequest request){
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}
		String order = request.getParameter("horder");
		String odr = "asc";
		if (order != null && order.length() > 0 && order.equals("d"))
			odr = "desc";
		String orderby = request.getParameter("orderby");
		request.setAttribute("order", order);     
		 String sqlstring="";		

		 sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo," +
		 		"s.enrollYear as enrollYear,s.stuName as stuName," +
		 		"s.gender as gender,s.examType as examType," +
		 		"s.totalScore as totalScore,s.classId as classId," +
		 		"s.studentNo as studentNo) " +
		 		"from GzStuTemp s  " +
		 		"where 1=1 " +
//		 		"and c.yxCollege.yxSchool.schoolId='0002' " +
		 		"and s.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
	 			 			 			 
			MyQuery myQuery = new MyQuery();	
			
			if (orderby == null || orderby.length() == 0)
				myQuery.setOrderby(" order by s.studentNo ");
			else if (orderby != null && orderby.length() > 0
						&& orderby.equals("studentNo"))
				myQuery.setOrderby(" order by s.studentNo" + " " + odr);
			else if (orderby != null && orderby.length() > 0
						&& orderby.equals("stuName"))
				myQuery.setOrderby(" order by s.stuName" + " " + odr);
			else if (orderby != null && orderby.length() > 0
						&& orderby.equals("enrollNo"))
				myQuery.setOrderby(" order by s.enterenceNo" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("gender"))
				myQuery.setOrderby(" order by s.gender" + " " + odr);		
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("examType"))
				myQuery.setOrderby(" order by s.examType" + " " + odr);		
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("totalScore"))
				myQuery.setOrderby(" order by s.totalScore" + " " + odr);				
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("classNo"))
				myQuery.setOrderby(" order by s.classId" + " " + odr);	
		 			 
			myQuery.setQueryString(sqlstring);		 			 
			List stucheckininfoList=studentmodelDAO.find(myQuery);
			
			HashMap Hash_Class = new HashMap();
			List Temp_Class = studentmodelDAO
					.find("select new map(a.classId as classId, a.classNo as classNo) from Classmodel a ");
			for (int i = 0; i < Temp_Class.size(); i++) {
				HashMap temp = (HashMap) Temp_Class.get(i);
				Hash_Class.put(temp.get("classId"), temp.get("classNo"));
			}
		 
			List resultList=new ArrayList();		
			if(stucheckininfoList!=null&&stucheckininfoList.size()>0){
				for(int i=0;i<stucheckininfoList.size();i++){
					HashMap stuMap = (HashMap)stucheckininfoList.get(i);
					String classCode = "";
					String classStr = "";
					if (!"".equals((String)stuMap.get("classId"))) {// 班级
						if (classCode.equals((String)stuMap.get("classId"))) {
							stuMap.put("classId", classStr);
						} else {
							classCode = (String)stuMap.get("classId");
							if (Hash_Class.get(classCode) != null) {
								classStr = Hash_Class.get(classCode).toString();
								stuMap.put("classNo", classStr);
							}
						}

					}
					
				}
				if (orderby != null && orderby.length() > 0
						&& orderby.equals("classNo")){				
					 Comparator comp1 = new Comparator() { 
							public int compare(Object o1, Object o2){ 
							Map m1 = (Map)o1; 
							Map m2 = (Map)o2; 
							String dictCaption1 = (String)m1.get("classNo"); 
							String dictCaption2 = (String)m2.get("classNo");      				
	
							com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
							com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
							com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
			                //注意,返回值是比较的结果>0,=0,或者<0
						    return collator.compare(c1.getSourceString(),c2.getSourceString());				
							 } 
					} ;		
					 Comparator comp2 = new Comparator() { 
							public int compare(Object o1, Object o2){ 
							Map m1 = (Map)o1; 
							Map m2 = (Map)o2; 
							String dictCaption1 = (String)m1.get("classNo"); 
							String dictCaption2 = (String)m2.get("classNo");      				
	
							com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
							com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
							com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
			                //注意,返回值是比较的结果>0,=0,或者<0
						    return collator.compare(c2.getSourceString(),c1.getSourceString());				
							 } 
					} ;						
					if ("desc".equals(odr)) {
						Collections.sort(stucheckininfoList, comp1);	
					} else if ("asc".equals(odr)) {
						Collections.sort(stucheckininfoList, comp2);	
					}						 

				}				

	         //起始页设置
			 if(offset.equals("0"))
			     resultList=stucheckininfoList;
			 else if((Integer.parseInt(offset))<stucheckininfoList.size()
					 ||(Integer.parseInt(offset))==stucheckininfoList.size())
				 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
		 }	
		 
	     request.setAttribute("checkinlist",resultList);
	     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
		 
	}

	public List getStudentExport_hlxy(HttpServletRequest request){	
		
		String order = request.getParameter("horder");
		String odr = "asc";
		if (order != null && order.length() > 0 && order.equals("d"))
			odr = "desc";
		String orderby = request.getParameter("orderby");
//		request.setAttribute("order", order); 

		 String sqlstring="";
		 sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo," +
		 		"s.enrollYear as enrollYear,s.stuName as stuName," +
		 		"s.gender as gender,s.examType as examType," +
		 		"s.totalScore as totalScore,s.classId as classId," +
		 		"s.studentNo as studentNo,s.cultureMode as cultureMode," +
		 		"s.studentType as studentType,s.enrollType as enrollType," +
		 		"s.telephone as telephone,s.postCode as postCode," +
		 		"s.idCard as idCard,s.familyAddress as familyAddress," +
		 		"s.district as district,s.nation as nation," +
		 		"s.majorin as majorin,s.department as department," +
		 		"s.fromProvince as fromProvince,s.nationality as nationality," +
		 		"s.polityBg as polityBg,s.birthday as birthday) " +
		 		"from GzStuTemp s  " +
		 		"where 1=1 " +
//		 		"and c.yxCollege.yxSchool.schoolId='0002' " +
		 		"and s.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
		 
		MyQuery myQuery = new MyQuery();	
			
		if (orderby == null || orderby.length() == 0)
			myQuery.setOrderby(" order by s.studentNo ");
		else if (orderby != null && orderby.length() > 0
					&& orderby.equals("studentNo"))
			myQuery.setOrderby(" order by s.studentNo" + " " + odr);
		else if (orderby != null && orderby.length() > 0
					&& orderby.equals("stuName"))
			myQuery.setOrderby(" order by s.stuName" + " " + odr);
		else if (orderby != null && orderby.length() > 0
					&& orderby.equals("enrollNo"))
			myQuery.setOrderby(" order by s.enterenceNo" + " " + odr);
		else if (orderby != null && orderby.length() > 0
				&& orderby.equals("gender"))
			myQuery.setOrderby(" order by s.gender" + " " + odr);		
		else if (orderby != null && orderby.length() > 0
				&& orderby.equals("examType"))
			myQuery.setOrderby(" order by s.examType" + " " + odr);		
		else if (orderby != null && orderby.length() > 0
				&& orderby.equals("totalScore"))
			myQuery.setOrderby(" order by s.totalScore" + " " + odr);				
		else if (orderby != null && orderby.length() > 0
				&& orderby.equals("classNo"))
			myQuery.setOrderby(" order by s.classId" + " " + odr);	
		
//		 sqlstring=sqlstring+" order by c.classNo,s.totalScore desc";
			myQuery.setQueryString(sqlstring);		 			 
		 List stucheckininfoList=studentmodelDAO.find(myQuery);	
		 
			HashMap Hash_Class = new HashMap();
			List Temp_Class = studentmodelDAO
					.find("select new map(a.classId as classId, a.classNo as classNo) from Classmodel a ");
			for (int i = 0; i < Temp_Class.size(); i++) {
				HashMap temp = (HashMap) Temp_Class.get(i);
				Hash_Class.put(temp.get("classId"), temp.get("classNo"));
			}
			
			HashMap Hash_gender = new HashMap();
			List Temp_gender = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 1 ");
			for (int i = 0; i < Temp_gender.size(); i++) {
				HashMap temp = (HashMap) Temp_gender.get(i);
				Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
			}

			HashMap Hash_polityBg = new HashMap();
			List Temp_polityBg = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 4 ");
			for (int i = 0; i < Temp_polityBg.size(); i++) {
				HashMap temp = (HashMap) Temp_polityBg.get(i);
				Hash_polityBg.put(temp.get("dictValue"), temp.get("dictCaption"));
			}
			
			HashMap Hash_nationality = new HashMap();
			List Temp_nationality = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 12 ");
			for (int i = 0; i < Temp_nationality.size(); i++) {
				HashMap temp = (HashMap) Temp_nationality.get(i);
				Hash_nationality.put(temp.get("dictValue"), temp.get("dictCaption"));
			}
			
			HashMap Hash_fromProvince = new HashMap();
			List Temp_fromProvince = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 10 ");
			for (int i = 0; i < Temp_fromProvince.size(); i++) {
				HashMap temp = (HashMap) Temp_fromProvince.get(i);
				Hash_fromProvince.put(temp.get("dictValue"), temp.get("dictCaption"));
			}		
			
			HashMap Hash_Department = new HashMap();
			List Temp_Department = studentmodelDAO
					.find("select new map(a.deptCode as deptCode, a.deptName as deptName) from Department a ");
			for (int i = 0; i < Temp_Department.size(); i++) {
				HashMap temp = (HashMap) Temp_Department.get(i);
				Hash_Department.put(temp.get("deptCode"), temp.get("deptName"));
			}
			
			HashMap Hash_majorin = new HashMap();
			List Temp_majorin = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 11 ");
			for (int i = 0; i < Temp_majorin.size(); i++) {
				HashMap temp = (HashMap) Temp_majorin.get(i);
				Hash_majorin.put(temp.get("dictValue"), temp.get("dictCaption"));
			}
			
			HashMap Hash_nation = new HashMap();
			List Temp_nation = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 2 ");
			for (int i = 0; i < Temp_nation.size(); i++) {
				HashMap temp = (HashMap) Temp_nation.get(i);
				Hash_nation.put(temp.get("dictValue"), temp.get("dictCaption"));
			}
			
			HashMap Hash_district = new HashMap();
			List Temp_district = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 23 ");
			for (int i = 0; i < Temp_district.size(); i++) {
				HashMap temp = (HashMap) Temp_district.get(i);
				Hash_district.put(temp.get("dictValue"), temp.get("dictCaption"));
			}
			
			HashMap Hash_examType = new HashMap();
			List Temp_examType = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 25 ");
			for (int i = 0; i < Temp_examType.size(); i++) {
				HashMap temp = (HashMap) Temp_examType.get(i);
				Hash_examType.put(temp.get("dictValue"), temp.get("dictCaption"));
			}
			
			HashMap Hash_enrollType = new HashMap();
			List Temp_enrollType = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 27 ");
			for (int i = 0; i < Temp_enrollType.size(); i++) {
				HashMap temp = (HashMap) Temp_enrollType.get(i);
				Hash_enrollType.put(temp.get("dictValue"), temp.get("dictCaption"));
			}			
			
			HashMap Hash_studentType = new HashMap();
			List Temp_studentType = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 15 ");
			for (int i = 0; i < Temp_studentType.size(); i++) {
				HashMap temp = (HashMap) Temp_studentType.get(i);
				Hash_studentType.put(temp.get("dictValue"), temp.get("dictCaption"));
			}	

			HashMap Hash_cultureMode = new HashMap();
			List Temp_cultureMode = studentmodelDAO
					.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
							+ "from Dictionary a where a.id.dictNo= 26 ");
			for (int i = 0; i < Temp_cultureMode.size(); i++) {
				HashMap temp = (HashMap) Temp_cultureMode.get(i);
				Hash_cultureMode.put(temp.get("dictValue"), temp.get("dictCaption"));
			}		
				
		 if(stucheckininfoList!=null&&stucheckininfoList.size()>0){
			 for(int i=0;i<stucheckininfoList.size();i++){
				 HashMap stuMap = (HashMap)stucheckininfoList.get(i);
				 
					String classCode = "";
					String classStr = "";
					if (!"".equals((String)stuMap.get("classId"))) {// 班级
						if (classCode.equals((String)stuMap.get("classId"))) {
							stuMap.put("classId", classStr);
						} else {
							classCode = (String)stuMap.get("classId");
							if (Hash_Class.get(classCode) != null) {
								classStr = Hash_Class.get(classCode).toString();
								stuMap.put("classNo", classStr);
							}
						}

					}
				 
					String genderCode = "";
					String genderStr = "";
					if (!"".equals((String)stuMap.get("gender"))) {// 性别
						if (genderCode.equals((String)stuMap.get("gender"))) {
							stuMap.put("gender", genderStr);
						} else {
							genderCode = (String)stuMap.get("gender");
							if (Hash_gender.get(genderCode) != null) {
								genderStr = Hash_gender.get(genderCode).toString();
								stuMap.put("gender", genderStr);
							}
						}

					}
					
					String polityBgCode = "";
					String polityBgStr = "";
					if (!"".equals((String)stuMap.get("polityBg"))) {
						if (polityBgCode.equals((String)stuMap.get("polityBg"))) {
							stuMap.put("polityBg", polityBgStr);
						} else {
							polityBgCode = (String)stuMap.get("polityBg");
							if (Hash_polityBg.get(polityBgCode) != null) {
								polityBgStr = Hash_polityBg.get(polityBgCode).toString();
								stuMap.put("polityBg", polityBgStr);
							}
						}

					}
					
					String nationalityCode = "";
					String nationalityStr = "";
					if (!"".equals((String)stuMap.get("nationality"))) {
						if (nationalityCode.equals((String)stuMap.get("nationality"))) {
							stuMap.put("nationality", nationalityStr);
						} else {
							nationalityCode = (String)stuMap.get("nationality");
							if (Hash_nationality.get(nationalityCode) != null) {
								nationalityStr = Hash_nationality.get(nationalityCode).toString();
								stuMap.put("nationality", nationalityStr);
							}
						}

					}
					
					String fromProvinceCode = "";
					String fromProvinceStr = "";
					if (!"".equals((String)stuMap.get("fromProvince"))) {
						if (fromProvinceCode.equals((String)stuMap.get("fromProvince"))) {
							stuMap.put("fromProvince", fromProvinceStr);
						} else {
							fromProvinceCode = (String)stuMap.get("fromProvince");
							if (Hash_fromProvince.get(fromProvinceCode) != null) {
								fromProvinceStr = Hash_fromProvince.get(fromProvinceCode).toString();
								stuMap.put("fromProvince", fromProvinceStr);
							}
						}

					}	
					
					String departmentCode = "";
					String departmentStr = "";
					if (!"".equals((String)stuMap.get("department"))) {
						if (departmentCode.equals((String)stuMap.get("department"))) {
							stuMap.put("department", departmentStr);
						} else {
							departmentCode = (String)stuMap.get("department");
							if (Hash_Department.get(departmentCode) != null) {
								departmentStr = Hash_Department.get(departmentCode).toString();
								stuMap.put("department", departmentStr);
							}
						}

					}	
					
					String majorinCode = "";
					String majorinStr = "";
					if (!"".equals((String)stuMap.get("majorin"))) {
						if (majorinCode.equals((String)stuMap.get("majorin"))) {
							stuMap.put("majorin", majorinStr);
						} else {
							majorinCode = (String)stuMap.get("majorin");
							if (Hash_majorin.get(majorinCode) != null) {
								majorinStr = Hash_majorin.get(majorinCode).toString();
								stuMap.put("majorin", majorinStr);
							}
						}

					}
					
					String nationCode = "";
					String nationStr = "";
					if (!"".equals((String)stuMap.get("nation"))) {
						if (nationCode.equals((String)stuMap.get("nation"))) {
							stuMap.put("nation", majorinStr);
						} else {
							nationCode = (String)stuMap.get("nation");
							if (Hash_nation.get(nationCode) != null) {
								majorinStr = Hash_nation.get(nationCode).toString();
								stuMap.put("nation", majorinStr);
							}
						}

					}
					
					String districtCode = "";
					String districtStr = "";
					if (!"".equals((String)stuMap.get("district"))) {
						if (districtCode.equals((String)stuMap.get("district"))) {
							stuMap.put("district", districtStr);
						} else {
							districtCode = (String)stuMap.get("district");
							if (Hash_district.get(districtCode) != null) {
								districtStr = Hash_district.get(districtCode).toString();
								stuMap.put("district", districtStr);
							}
						}

					}	
					
					String examTypeCode = "";
					String examTypeStr = "";
					if (!"".equals((String)stuMap.get("examType"))) {
						if (examTypeCode.equals((String)stuMap.get("examType"))) {
							stuMap.put("examType", examTypeStr);
						} else {
							examTypeCode = (String)stuMap.get("examType");
							if (Hash_examType.get(examTypeCode) != null) {
								examTypeStr = Hash_examType.get(examTypeCode).toString();
								stuMap.put("examType", examTypeStr);
							}
						}

					}	
					
					String enrollTypeCode = "";
					String enrollTypeStr = "";
					if (!"".equals((String)stuMap.get("enrollType"))) {
						if (enrollTypeCode.equals((String)stuMap.get("enrollType"))) {
							stuMap.put("enrollType", enrollTypeStr);
						} else {
							enrollTypeCode = (String)stuMap.get("enrollType");
							if (Hash_enrollType.get(enrollTypeCode) != null) {
								enrollTypeStr = Hash_enrollType.get(enrollTypeCode).toString();
								stuMap.put("enrollType", enrollTypeStr);
							}
						}

					}	
					
					String studentTypeCode = "";
					String studentTypeStr = "";
					if (!"".equals((String)stuMap.get("studentType"))) {
						if (studentTypeCode.equals((String)stuMap.get("studentType"))) {
							stuMap.put("studentType", studentTypeStr);
						} else {
							studentTypeCode = (String)stuMap.get("studentType");
							if (Hash_studentType.get(studentTypeCode) != null) {
								studentTypeStr = Hash_studentType.get(studentTypeCode).toString();
								stuMap.put("studentType", studentTypeStr);
							}
						}

					}	
					
					String cultureModeCode = "";
					String cultureModeStr = "";
					if (!"".equals((String)stuMap.get("cultureMode"))) {
						if (cultureModeCode.equals((String)stuMap.get("cultureMode"))) {
							stuMap.put("cultureMode", cultureModeStr);
						} else {
							cultureModeCode = (String)stuMap.get("cultureMode");
							if (Hash_cultureMode.get(cultureModeCode) != null) {
								cultureModeStr = Hash_cultureMode.get(cultureModeCode).toString();
								stuMap.put("cultureMode", cultureModeStr);
							}
						}

					}					
			 }
				if (orderby != null && orderby.length() > 0
						&& orderby.equals("classNo")){				
					 Comparator comp1 = new Comparator() { 
							public int compare(Object o1, Object o2){ 
							Map m1 = (Map)o1; 
							Map m2 = (Map)o2; 
							String dictCaption1 = (String)m1.get("classNo"); 
							String dictCaption2 = (String)m2.get("classNo");      				
	
							com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
							com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
							com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
			                //注意,返回值是比较的结果>0,=0,或者<0
						    return collator.compare(c1.getSourceString(),c2.getSourceString());				
							 } 
					} ;		
					 Comparator comp2 = new Comparator() { 
							public int compare(Object o1, Object o2){ 
							Map m1 = (Map)o1; 
							Map m2 = (Map)o2; 
							String dictCaption1 = (String)m1.get("classNo"); 
							String dictCaption2 = (String)m2.get("classNo");      				
	
							com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
							com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
							com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
			                //注意,返回值是比较的结果>0,=0,或者<0
						    return collator.compare(c2.getSourceString(),c1.getSourceString());				
							 } 
					} ;						
					if ("desc".equals(odr)) {
						Collections.sort(stucheckininfoList, comp1);	
					} else if ("asc".equals(odr)) {
						Collections.sort(stucheckininfoList, comp2);	
					}						 

				}	
		 }

		 return stucheckininfoList;

		 
	}
	
	public List getmajorList(){
		List majorList=classmodelDAO.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
		
		Comparator comp1 = new Comparator() { 
				public int compare(Object o1, Object o2){ 
				Map m1 = (Map)o1; 
				Map m2 = (Map)o2; 
				String dictCaption1 = (String)m1.get("dictCaption"); 
				String dictCaption2 = (String)m2.get("dictCaption");      				

				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
                //注意,返回值是比较的结果>0,=0,或者<0
			    return collator.compare(c1.getSourceString(),c2.getSourceString());				
				 } 
		} ;				
			 
		Collections.sort(majorList, comp1);		
		
		return majorList;
	}
	
	public List getfromProvinceList(){
		List majorList=classmodelDAO.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=10 order by di.id.dictValue");
		Comparator comp1 = new Comparator() { 
			public int compare(Object o1, Object o2){ 
			Map m1 = (Map)o1; 
			Map m2 = (Map)o2; 
			String dictCaption1 = (String)m1.get("dictCaption"); 
			String dictCaption2 = (String)m2.get("dictCaption");      				

			com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
			com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
			com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
            //注意,返回值是比较的结果>0,=0,或者<0
		    return collator.compare(c1.getSourceString(),c2.getSourceString());				
			 } 
	    } ;				
		 
	    Collections.sort(majorList, comp1);
		return majorList;
	}	
	
	public List getcountryList(){
		List majorList=classmodelDAO.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
		Comparator comp1 = new Comparator() { 
			public int compare(Object o1, Object o2){ 
			Map m1 = (Map)o1; 
			Map m2 = (Map)o2; 
			String dictCaption1 = (String)m1.get("dictCaption"); 
			String dictCaption2 = (String)m2.get("dictCaption");      				

			com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
			com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
			com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
            //注意,返回值是比较的结果>0,=0,或者<0
		    return collator.compare(c1.getSourceString(),c2.getSourceString());				
			 } 
	    } ;				
		 
	    Collections.sort(majorList, comp1);
		return majorList;
	}
	
	public List getnationList(){
		List majorList=classmodelDAO.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=2 order by di.id.dictValue");
		Comparator comp1 = new Comparator() { 
			public int compare(Object o1, Object o2){ 
			Map m1 = (Map)o1; 
			Map m2 = (Map)o2; 
			String dictCaption1 = (String)m1.get("dictCaption"); 
			String dictCaption2 = (String)m2.get("dictCaption");      				

			com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
			com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
			com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
            //注意,返回值是比较的结果>0,=0,或者<0
		    return collator.compare(c1.getSourceString(),c2.getSourceString());				
			 } 
	    } ;				
		 
	    Collections.sort(majorList, comp1);
		return majorList;
	}
/**
 * 显示 班级导师信息
 */
	public void findAssistantList(HttpServletRequest request){
		
		String gh = (String)request.getSession().getAttribute("userName");		
		List list_Assistant = classmodelDAO
		.find("select a from Managermodel a,Classmanager b,Managermanagerrole c,Classmanager d,Managermodel e "
				+ " where a.managerId=b.id.managerId " +
						"and a.managerId=c.id.managerId " +
						"and c.id.roleId='22' "
				+ "and b.id.classId=d.id.classId and d.id.managerId=e.managerId and e.managerNo='"+ gh + "'");	
		
		request.setAttribute("list_Assistant", list_Assistant);
		
	}

}
