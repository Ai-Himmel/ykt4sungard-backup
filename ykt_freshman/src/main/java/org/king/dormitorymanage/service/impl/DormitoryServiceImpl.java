package org.king.dormitorymanage.service.impl;

import java.io.Serializable;
import java.sql.Types;
import java.text.RuleBasedCollator;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.DynaActionForm;
import org.king.classmanage.dao.ClassmodelDAO;
import org.king.classmanage.dao.CollegemodelDAO;
import org.king.classmanage.dao.DistributionTempDAO;
import org.king.classmanage.dao.ManagermodelDAO;
import org.king.classmanage.dao.StudentmodelDAO;
import org.king.classmanage.domain.ClassDorm;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.DistributionTemp;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.web.help.DormitoryBindInfo;
import org.king.classmanage.web.help.MajorinInfo;
import org.king.classmanage.web.help.StudentWithAllInfo;
import org.king.classmanage.web.help.StudentWithAllInfoDorm;
import org.king.dormitorymanage.dao.DormAlerthisDAO;
import org.king.dormitorymanage.dao.DormitorymodelDAO;
import org.king.dormitorymanage.domain.DormAlerthis;
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
import org.king.dormitorymanage.service.DormitoryService;
import org.king.dormitorymanage.util.ConvertXmlUtil;
import org.king.dormitorymanage.web.help.DormitoryHisWithAllInfo;
import org.king.dormitorymanage.web.help.DormitoryStatistic;
import org.king.dormitorymanage.web.help.DormitoryWithAllInfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.dao.YxGraduateDAO;
import org.king.yangong.dormitorymanage.domain.YxGraduate;
import org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount;
import org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo;
import org.springframework.jdbc.core.JdbcTemplate;

public class DormitoryServiceImpl implements DormitoryService {

	private DormitorymodelDAO dormitorymodelDAO;

	private ClassmodelDAO classmodelDAO;

	private StudentmodelDAO studentmodelDAO;

	private DormAlerthisDAO dormAlerthisDAO;

	private CollegemodelDAO collegemodelDAO;

	private ManagermodelDAO managermodelDAO;

	private JdbcTemplate jdbcTemplate;

	private DistributionTempDAO distributionTempDAO;

	private YxGraduateDAO yxGraduateDAO;

	private BaseDAO baseDAO;

	/**
	 * @param distributionTempDAO
	 *            The distributionTempDAO to set.
	 */
	public void setDistributionTempDAO(DistributionTempDAO distributionTempDAO) {
		this.distributionTempDAO = distributionTempDAO;
	}

	public void setYxGraduateDAO(YxGraduateDAO yxGraduateDAO) {
		this.yxGraduateDAO = yxGraduateDAO;

	}

	/**
	 * @param jdbcTemplate
	 *            The jdbcTemplate to set.
	 */
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	/**
	 * @param managermodelDAO
	 *            The managermodelDAO to set.
	 */
	public void setManagermodelDAO(ManagermodelDAO managermodelDAO) {
		this.managermodelDAO = managermodelDAO;
	}

	public void setDormAlerthisDAO(DormAlerthisDAO dormAlerthisDAO) {
		this.dormAlerthisDAO = dormAlerthisDAO;
	}

	public void setStudentmodelDAO(StudentmodelDAO studentmodelDAO) {
		this.studentmodelDAO = studentmodelDAO;
	}

	public void setDormitorymodelDAO(DormitorymodelDAO dormitorymodelDAO) {
		this.dormitorymodelDAO = dormitorymodelDAO;
	}

	public void setClassmodelDAO(ClassmodelDAO classmodelDAO) {
		this.classmodelDAO = classmodelDAO;
	}

	/**
	 * @param collegemodelDAO
	 *            The collegemodelDAO to set.
	 */
	public void setCollegemodelDAO(CollegemodelDAO collegemodelDAO) {
		this.collegemodelDAO = collegemodelDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.dormitorymanage.service.DormitoryService#getDormByClass(java.lang.String)
	 */
	public List getDormByClass(String classId) {
		return classmodelDAO.find("from Dormitorymodel b where b.classId ='"
				+ classId + "'");
	}

	public Dormitorymodel[] getDormByDorm(String dormitory) {
		List dorm = new ArrayList();
		dorm = dormitorymodelDAO
				.find("from Dormitorymodel b where b.dormitory='" + dormitory
						+ "'");
		if (dorm.size() == 0) {
			return null;
		}
		Dormitorymodel[] dorms = new Dormitorymodel[dorm.size()];
		for (int i = 0; i < dorm.size(); i++) {
			dorms[i] = (Dormitorymodel) dorm.get(i);
		}
		return dorms;
	}

	public boolean deleteConnection(String classId) {
		// TODO Auto-generated method stub
		return false;
	}

	private void saveClassDistribution(String studentIds, String[] classIds) {
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

	
	/**
		* Method name: saveDormitoryDistribution<br>
		* Description: 分班分宿舍方法<br>
		* Return: void<br>
		* Args: @param StudentIds   需要分配的学生id，由逗号分隔
		* Args: @param classIds  可以用来分配的班级信息
		* Args: @throws DormitoryNotEnoughException 宿舍资源不足
		* Args: @throws StudentAlreadyInDormException 学生已经分配过宿舍了
		*/
	private void saveDormitoryDistribution(String StudentIds, String[] classIds)
			throws DormitoryNotEnoughException, StudentAlreadyInDormException {
		
		
		/*
		 * 班级分配规则：按性别、生源地、专业、政治面貌等均分。
		 * 宿舍分配原则：男女分开、生源地、专业都不同，党员均匀分布。
		 * 男女均分，同一生源地均分，党员均分，统一专业的打散均分，少数民族按族属性均分（同民族同班的不超过2个，而且要分到同一个宿舍），港澳台按区域属性均分，留学生按国家属性均分（更倾向于按专业，便于管理）。
		 * 自主招生300作为一个特殊的专业处理。
		 * 少数民族中维族和哈萨克族的学生需要特别考虑，不能和其他少数民族的学生放在一起。
		 * 一个班维族和哈族的学生不超过2个，而且需要放在同一个宿舍。
		 * 
		 * 2009年本科生分班、分宿舍规则调整：
		 * 在实际分配过程中，各专业选定了“书院”以后，外语小语种专业（朝鲜语、日语、德语、法语、俄语、翻译）
		 * 不要求平均分配到各宿舍、各班级中，
		 * 而是先要集中分到同一宿舍中；
		 * 并保证每一个专业的男、女生在同一班级，不同专业的在不同班级；然后再把其他学生按原有规则平均分配。
		 */

		// 建立班级容器
		if (null != classIds) {
			//查出每个书院的班级信息，用逗号分隔，分别存储于collegeArr数组中			
			List collegeList = collegemodelDAO.getAll();
			String[] collegeArr = new String[collegeList.size()];
			for (int c = 0; c < collegeList.size(); c++) {
				Collegemodel collegemodel = (Collegemodel) collegeList.get(c);
				List classList = classmodelDAO.find("from Classmodel a "
						+ "where a.yxCollege.collegeId='"
						+ collegemodel.getCollegeId() + "'");
				String classes = "";
				for (int d = 0; d < classList.size(); d++) {
					Classmodel classmodel = (Classmodel) classList.get(d);
					classes += classmodel.getClassId() + ",";
				}
				collegeArr[c] = classes;
			}
			
			/*
			 * 根据规则：小语种、少数民族新疆、 其他少数民族、汉族 学生都需要单独处理
			 * 所以这些人需要单独查询出来，以备单独处理之用
			 * 并且男女分开
			 */
			// -1 处理小语种 | 男
			List smalllanguageStudent_m = studentmodelDAO
					.find("from Studentmodel a where a.nationality='CHN' "
							+ "and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and (a.majorin='120' or a.majorin='121' or a.majorin='122' or a.majorin='123' or a.majorin='124' or a.majorin='128') "
							+ "and a.gender='1' and a.studentId in ("
							+ StudentIds + ") order by a.majorin");

			// -1 处理小语种 | 女

			List smalllanguageStudent_f = studentmodelDAO
					.find("from Studentmodel a where a.nationality='CHN' "
							+ "and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and (a.majorin='120' or a.majorin='121' or a.majorin='122' or a.majorin='123' or a.majorin='124' or a.majorin='128') "
							+ "and a.gender='2' and a.studentId in ("
							+ StudentIds + ") order by a.majorin");
			
			// -1.0 英语专业| 男
			List englishStudent_m = studentmodelDAO
			.find("from Studentmodel a where a.nationality='CHN' "
					+ "and a.enrollYear='"
					+ DateUtil.getNow("yyyy")
					+ "' "
					+ "and a.majorin='125' "
					+ "and a.gender='1' and a.studentId in ("
					+ StudentIds + ") order by a.majorin");
			
			//-1.0 英语专业|女
			List englishStudent_f = studentmodelDAO
			.find("from Studentmodel a where a.nationality='CHN' "
					+ "and a.enrollYear='"
					+ DateUtil.getNow("yyyy")
					+ "' "
					+ "and  a.majorin='125' "
					+ "and a.gender='2' and a.studentId in ("
					+ StudentIds + ") order by a.majorin");
			// -1.1 重庆医大 | 男  代码 100001
			List cqydStudent_m = studentmodelDAO.find("from Studentmodel a where a.nationality='CHN' " 
					+ "and a.enrollYear='"
					+ DateUtil.getNow("yyyy")
					+ "' "
					+"and a.majorin='100001' and a.gender='1' and a.studentId in ("
					+ StudentIds + ") order by a.majorin");
			// -1.1 重庆医大 | 女
			List cqydStudent_f = studentmodelDAO.find("from Studentmodel a where a.nationality='CHN' " 
					+ "and a.enrollYear='"
					+ DateUtil.getNow("yyyy")
					+ "' "
					+"and a.majorin='100001' and a.gender='2' and a.studentId in ("
					+ StudentIds + ") order by a.majorin");
			
			// -1.2 宿舍集中专业 | 男 
			//克卿学院 5大专业 中国语言文学类、物理、核技术、社会学类、心理学  要求班级相对分散，宿舍全部集中
			List kqgatherStudent_m = studentmodelDAO.find("from Studentmodel a where a.nationality='CHN' " 
					+ "and a.enrollYear='"
					+ DateUtil.getNow("yyyy")
					+ "' "
					+"and (a.majorin='344' or a.majorin='201' or a.majorin='11t' or a.majorin='34t' or a.majorin='191') "
					+"and a.gender='1' and a.studentId in ("
					+ StudentIds + ") order by a.majorin");
			// -1.2 宿舍集中专业 | 女
			List kqgatherStudent_f = studentmodelDAO.find("from Studentmodel a where a.nationality='CHN' " 
					+ "and a.enrollYear='"
					+ DateUtil.getNow("yyyy")
					+ "' "
					+"and (a.majorin='344' or a.majorin='201' or a.majorin='11t' or a.majorin='34t' or a.majorin='191') "
					+"and a.gender='2' and a.studentId in ("
					+ StudentIds + ") order by a.majorin");
			// -1.3数学专业学| 男
			List mathStudent_m = studentmodelDAO.find("from Studentmodel a where a.nationality='CHN' " 
					+ "and a.enrollYear='"
					+ DateUtil.getNow("yyyy")
					+ "' "
					+"and a.majorin='18t' "
					+"and a.gender='1' and a.studentId in ("
					+ StudentIds + ") order by a.majorin");
			// -1.3数学专业学| 女
			List mathStudent_f = studentmodelDAO.find("from Studentmodel a where a.nationality='CHN' " 
					+ "and a.enrollYear='"
					+ DateUtil.getNow("yyyy")
					+ "' "
					+"and a.majorin='18t' "
					+"and a.gender='2' and a.studentId in ("
					+ StudentIds + ") order by a.majorin");

			// 1 少数民族 新疆的 05 维吾尔族 |17 哈萨克族 -男
			List speminorityStudents_m = studentmodelDAO
					.find("from Studentmodel a where a.nationality='CHN' "
							+ "and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.majorin<>'120' and a.majorin<>'121' and a.majorin<>'122' and a.majorin<>'123' and a.majorin<>'124' and a.majorin<>'128' "
							+ "and a.majorin<>'125' and a.majorin<>'344' and a.majorin<>'201' and a.majorin<>'11t' and a.majorin<>'34t' and a.majorin<>'191' "
							+ "and a.majorin<>'18t' and a.majorin<>'100001' "
							+ "and a.fromProvince='65' and a.nation<>'01' "
							+ "and a.gender='1' and a.studentId in ("
							+ StudentIds + ") order by a.nation,a.majorin");

			// 1 少数民族 新疆的 05 维吾尔族 |17 哈萨克族 -女
			List speminorityStudents_f = studentmodelDAO
					.find("from Studentmodel a where a.nationality='CHN' "
							+ "and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.majorin<>'120' and a.majorin<>'121' and a.majorin<>'122' and a.majorin<>'123' and a.majorin<>'124' and a.majorin<>'128' "
							+ "and a.majorin<>'125' and a.majorin<>'344' and a.majorin<>'201' and a.majorin<>'11t' and a.majorin<>'34t' and a.majorin<>'191' "
							+ "and a.majorin<>'18t' and a.majorin<>'100001' "
							+ "and a.fromProvince='65' and a.nation<>'01' "
							+ "and a.gender='2' and a.studentId in ("
							+ StudentIds + ") order by a.nation,a.majorin");

			// 2 其他少数民族 -男
			List minorityStudents_m = studentmodelDAO
					.find("from Studentmodel a where a.nationality='CHN' "
							+ "and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.majorin<>'120' and a.majorin<>'121' and a.majorin<>'122' and a.majorin<>'123' and a.majorin<>'124' and a.majorin<>'128' "
							+ "and a.majorin<>'125' and a.majorin<>'344' and a.majorin<>'201' and a.majorin<>'11t' and a.majorin<>'34t' and a.majorin<>'191' "
							+ "and a.majorin<>'18t' and a.majorin<>'100001' "
							+ "and a.fromProvince<>'65' "
							+ "and a.nation<>'01' and a.gender='1' and a.studentId in ("
							+ StudentIds + ") " + "order by a.nation,a.majorin");

			// 2 其他少数民族 -女
			List minorityStudents_f = studentmodelDAO
					.find("from Studentmodel a where a.nationality='CHN' "
							+ "and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.majorin<>'120' and a.majorin<>'121' and a.majorin<>'122' and a.majorin<>'123' and a.majorin<>'124' and a.majorin<>'128' "
							+ "and a.majorin<>'125' and a.majorin<>'344' and a.majorin<>'201' and a.majorin<>'11t' and a.majorin<>'34t' and a.majorin<>'191' "
							+ "and a.majorin<>'18t' and a.majorin<>'100001' "
							+ "and a.fromProvince<>'65' "
							+ "and a.nation<>'01' and a.gender='2' and a.studentId in ("
							+ StudentIds + ") " + "order by a.nation,a.majorin");

			// 3 汉族 - 男
			List students_m = studentmodelDAO
					.find("from Studentmodel a where a.nationality='CHN' "
							+ "and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.majorin<>'120' and a.majorin<>'121' and a.majorin<>'122' and a.majorin<>'123' and a.majorin<>'124' and a.majorin<>'128' "
							+ "and a.majorin<>'125' and a.majorin<>'344' and a.majorin<>'201' and a.majorin<>'11t' and a.majorin<>'34t' and a.majorin<>'191' "
							+ "and a.majorin<>'18t' and a.majorin<>'100001' "
							+ "and (a.nation='01' or a.nation is null or a.nation='') and a.gender='1' and a.studentId in ("
							+ StudentIds + ") " + "order by a.nation,a.majorin");

			// 3 汉族 - 女
			List students_f = studentmodelDAO
					.find("from Studentmodel a where a.nationality='CHN' "
							+ "and a.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.majorin<>'120' and a.majorin<>'121' and a.majorin<>'122' and a.majorin<>'123' and a.majorin<>'124' and a.majorin<>'128' "
							+ "and a.majorin<>'125' and a.majorin<>'344' and a.majorin<>'201' and a.majorin<>'11t' and a.majorin<>'34t' and a.majorin<>'191' "
							+ "and a.majorin<>'18t' and a.majorin<>'100001' "
							+ "and (a.nation='01' or a.nation is null or a.nation='') and a.gender='2' and a.studentId in ("
							+ StudentIds + ")" + "order by a.nation,a.majorin");

			/*
			 * 首先需要为每个班级建立一个二维数组容器，用以存储分配到这个班级的学生id
			 * 数组的一个个第一个位置用来保存班级id
			 * 后面的位置用来保存学生的id
			 */
			
			// 根据宿舍情况，知道每个班的男女人数上限
			int[] accomodation_m = new int[classIds.length];
			int[] accomodation_f = new int[classIds.length];
			for (int a = 0; a < classIds.length; a++) {
				accomodation_m[a] = 0;
				accomodation_f[a] = 0;
			}
			// 查找出所有班级最大可容纳学生的床位数，作为二维数组的维数
			int max_m = 1;
			int max_f = 1;
			for (int d = 0; d < classIds.length; d++) {
				String cls = classIds[d];

				List accList_m = dormitorymodelDAO
						.find("select sum(a.accomodation) as accomodation from Dormitorymodel a "
								+ "where a.classId='"
								+ cls
								+ "' and a.gender='1' group by a.classId");
				List accList_f = dormitorymodelDAO
						.find("select sum(a.accomodation) as accomodation from Dormitorymodel a "
								+ "where a.classId='"
								+ cls
								+ "' and a.gender='2' group by a.classId");
				if (accList_m.size() > 0) {
					accomodation_m[d] = Integer.parseInt(accList_m.get(0)
							.toString());
				}
				if (accList_f.size() > 0) {
					accomodation_f[d] = Integer.parseInt(accList_f.get(0)
							.toString());
				}
				if (accomodation_m[d] > max_m) {
					max_m = accomodation_m[d];
				}
				if (accomodation_f[d] > max_f) {
					max_f = accomodation_f[d];
				}

			}
			
			//用最大的床位数建立二维数组容器
			// 男生
			String[][] classesArr_m = new String[classIds.length][max_m + 1];
			// 女生
			String[][] classesArr_f = new String[classIds.length][max_f + 1];
			//初始化一下各个位置为空
			for (int index = 0; index < classIds.length; index++) {
				classesArr_m[index][0] = classIds[index];
				for (int i = 1; i <= max_m; i++) {
					classesArr_m[index][i] = "";
				}
				classesArr_f[index][0] = classIds[index];
				for (int i = 1; i <= max_f; i++) {
					classesArr_f[index][i] = "";
				}
			}
			Studentmodel studentmodel_a = null;
			Studentmodel studentmodel_b = null;
			Studentmodel studentmodel_c = null;
			Studentmodel studentmodel_d = null;
			int cla_index = 0;
			int index = 1;

			// 所有小语种的学生id,分宿舍的时候有用
			String smalllanguageStudent_m_Str = "";
			String smalllanguageStudent_f_Str = "";

			for (int i = 0; i < smalllanguageStudent_m.size(); i++) {
				studentmodel_a = (Studentmodel) smalllanguageStudent_m.get(i);
				smalllanguageStudent_m_Str += studentmodel_a.getStudentId()
						+ ",";
			}

			for (int i = 0; i < smalllanguageStudent_f.size(); i++) {
				studentmodel_a = (Studentmodel) smalllanguageStudent_f.get(i);
				smalllanguageStudent_f_Str += studentmodel_a.getStudentId()
						+ ",";
			}
			//英语专业学生id 分宿舍时候有用
			String englishStudent_m_Str = "";
			String englishStudent_f_Str = "";

			for (int i = 0; i < englishStudent_m.size(); i++) {
				studentmodel_a = (Studentmodel) englishStudent_m.get(i);
				englishStudent_m_Str += studentmodel_a.getStudentId()
						+ ",";
			}

			for (int i = 0; i < englishStudent_f.size(); i++) {
				studentmodel_a = (Studentmodel) englishStudent_f.get(i);
				englishStudent_f_Str += studentmodel_a.getStudentId()
						+ ",";
			}
			//克卿 5大专业 宿舍集中专业所有学生id 分宿舍特殊处理有用
			String kqgatherStudent_m_Str = "";
			String kqgatherStudent_f_Str = "";
			for (int i = 0; i < kqgatherStudent_m.size(); i++) {
				studentmodel_a = (Studentmodel) kqgatherStudent_m.get(i);
				kqgatherStudent_m_Str += studentmodel_a.getStudentId()
						+ ",";
			}

			for (int i = 0; i < kqgatherStudent_f.size(); i++) {
				studentmodel_a = (Studentmodel) kqgatherStudent_f.get(i);
				kqgatherStudent_f_Str += studentmodel_a.getStudentId()
						+ ",";
			}
			
			//数学专业学生 班级分散 宿舍需要集中
			String mathStudent_m_Str = "";
			String mathStudent_f_Str = "";
			for (int i = 0; i < mathStudent_m.size(); i++) {
				studentmodel_a = (Studentmodel) mathStudent_m.get(i);
				mathStudent_m_Str += studentmodel_a.getStudentId()
						+ ",";
			}

			for (int i = 0; i < mathStudent_f.size(); i++) {
				studentmodel_a = (Studentmodel) mathStudent_f.get(i);
				mathStudent_f_Str += studentmodel_a.getStudentId()
						+ ",";
			}
			/*
			 * 按照既定的规则  依次分配各个需要特殊处理的人员
			 */
			
			
			// 1、分配小语种学生--男生
			int j = 0;
			cla_index = 0;// 上次分配的班级
			String majory_m = ""; //上次人员的专业，因为需要按专业分配到不同的班级，所以要记录上次的专业，如果发生了变化，那么就要分到不同的班级了
			while (j < smalllanguageStudent_m.size()) {
				for (int i = cla_index; i < classesArr_m.length; i++) {
					if (accomodation_m[i] >= 1) {
						//还有空位置
						studentmodel_a = (Studentmodel) smalllanguageStudent_m
								.get(j);
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_m[i].length; k++) {
							if ("".equals(classesArr_m[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if ("".equals(majory_m)) {
							// 第一个人，majory_m是空
							classesArr_m[i][index] = studentmodel_a
									.getStudentId();
							majory_m = studentmodel_a.getMajorin();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
							break;
						} else {
							// 前后相等，同一个专业
							if (majory_m.equals(studentmodel_a.getMajorin())) {
								classesArr_m[i][index] = studentmodel_a
										.getStudentId();
								majory_m = studentmodel_a.getMajorin();
								j++;
								accomodation_m[i] = accomodation_m[i] - 1;
								break;
							} else {
								// 前后不等，不同专业，到下一个班级
								cla_index++;
								majory_m = studentmodel_a.getMajorin();
								continue;
							}
						}
					} else {
						// 宿舍资源不够，没有空位置了,则分到下一个班，
						//继续循环，直到所有班级都循环完，如果还找不到空位置，则报宿舍资源不够的错误
						cla_index++;
						if (cla_index == classesArr_m.length) {
							throw new DormitoryNotEnoughException(
									"dormitory not enough!");
						} else {
							continue;
						}
					}

				}
			}
			// 1、分配小语种学生--女生
			j =0;
			cla_index = 0;// 上次分配的班级
			String majory_f = "";//上次人员的专业，因为需要按专业分配到不同的班级，所以要记录上次的专业，如果发生了变化，那么就要分到不同的班级了
			while (j < smalllanguageStudent_f.size()) {
				for (int i = cla_index; i < classesArr_f.length; i++) {
					if (accomodation_f[i] >= 1) {
						//还有空位置
						studentmodel_a = (Studentmodel) smalllanguageStudent_f
								.get(j);
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_f[i].length; k++) {
							if ("".equals(classesArr_f[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if ("".equals(majory_f)) {
							// 第一个人
							classesArr_f[i][index] = studentmodel_a
									.getStudentId();
							majory_f = studentmodel_a.getMajorin();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
							break;
						} else {
							// 前后相等，同一个专业
							if (majory_f.equals(studentmodel_a.getMajorin())) {
								classesArr_f[i][index] = studentmodel_a
										.getStudentId();
								majory_f = studentmodel_a.getMajorin();
								j++;
								accomodation_f[i] = accomodation_f[i] - 1;
								break;
							} else {
								// 前后不等，不同专业，到下一个班级
								cla_index++;
								majory_f = studentmodel_a.getMajorin();
								continue;
							}
						}
					} else {
						// 宿舍资源不够，没有空位置了,则分到下一个班，
						//继续循环，直到所有班级都循环完，如果还找不到空位置，则报宿舍资源不够的错误
						cla_index++;
						if (cla_index == classesArr_f.length) {
							throw new DormitoryNotEnoughException(
									"dormitory not enough!");
						} else {
							continue;
						}
					}

				}
			}
			//1.0、 2010年新需求  英语专业-- 男 --学生要均分到10个班级中，宿舍里要求集中
			j = 0;
			cla_index = 0;// 上次分配的班级
			while (j < englishStudent_m.size()) {
				for (int i = cla_index; i < classesArr_m.length; i++) {
					//还有空位置
					studentmodel_a = (Studentmodel) englishStudent_m
							.get(j);
					if(j+1<englishStudent_m.size()){
						studentmodel_b = (Studentmodel) englishStudent_m.get(j+1);
					}else{
						studentmodel_b = null;
					}
					if (accomodation_m[i] >= 2) {
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_m[i].length; k++) {
							if ("".equals(classesArr_m[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if(studentmodel_a!=null){
							classesArr_m[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						if(studentmodel_b!=null){
							classesArr_m[i][index+1] = studentmodel_b.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}						
						cla_index++;
						cla_index = cla_index%classesArr_m.length;
						break;
						
					}else if(accomodation_m[i] >= 1){
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_m[i].length; k++) {
							if ("".equals(classesArr_m[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if(studentmodel_a!=null&&accomodation_m[i]>0){
							classesArr_m[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						cla_index++;
						cla_index = cla_index%classesArr_m.length;
						break;						
					} else {
						// 宿舍资源不够，没有空位置了,则分到下一个班，
						//继续循环，直到所有班级都循环完，如果还找不到空位置，则报宿舍资源不够的错误
						cla_index++;
						if (cla_index == classesArr_m.length) {
							throw new DormitoryNotEnoughException(
									"dormitory not enough!");
						} else {
							continue;
						}
					}

				}
			}
			
			//1.0、 2010年新需求  英语专业-- 女 --学生要均分到10个班级中，宿舍里要求集中
			j = 0;
			cla_index = 0;// 上次分配的班级
			while (j < englishStudent_f.size()) {
				for (int i = cla_index; i < classesArr_f.length; i++) {
					//还有空位置
					studentmodel_a = (Studentmodel) englishStudent_f
							.get(j);
					if(j+1<englishStudent_f.size()){
						studentmodel_b = (Studentmodel) englishStudent_f.get(j+1);
					}else{
						studentmodel_b = null;
					}
					
					if (accomodation_f[i] >= 2) {						
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_f[i].length; k++) {
							if ("".equals(classesArr_f[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if(studentmodel_a!=null){
							classesArr_f[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						if(studentmodel_b!=null){
							classesArr_f[i][index+1] = studentmodel_b.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}						
						cla_index++;
						cla_index = cla_index%classesArr_f.length;
						break;
						
					}else if(accomodation_f[i] >= 1){
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_f[i].length; k++) {
							if ("".equals(classesArr_f[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if(studentmodel_a!=null&&accomodation_f[i]>0){
							classesArr_f[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}						
						cla_index++;
						cla_index = cla_index%classesArr_f.length;
						break;
						
					} else {
						// 宿舍资源不够，没有空位置了,则分到下一个班，
						//继续循环，直到所有班级都循环完，如果还找不到空位置，则报宿舍资源不够的错误
						cla_index++;
						if (cla_index == classesArr_f.length) {
							throw new DormitoryNotEnoughException(
									"dormitory not enough!");
						} else {
							continue;
						}
					}

				}
			}
			
			//1.1、2010年新需求 重庆医大该专业所有学生遍在其中一个班,和小语种处理一样

			j = 0;			
			if(cqydStudent_m!=null&&cqydStudent_m.size()>0){
				for (int i = 0; i < classesArr_m.length; i++) {
					//找到一个班级能容下所有人的，把学生全部放进去
					if(accomodation_m[i]>cqydStudent_m.size() && accomodation_f[i]>cqydStudent_f.size()){
						while (j < cqydStudent_m.size()) {
							studentmodel_a = (Studentmodel) cqydStudent_m.get(j);
							// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
							for (int k = 0; k < classesArr_m[i].length; k++) {
								if ("".equals(classesArr_m[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							
							classesArr_m[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						j=0;
						while(j<cqydStudent_f.size()){
							studentmodel_a = (Studentmodel) cqydStudent_f.get(j);
							// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
							for (int k = 0; k < classesArr_f[i].length; k++) {
								if ("".equals(classesArr_m[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							
							classesArr_f[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;						
						}
						break;						
					}
					
					if(i==classesArr_m.length-1){
						throw new DormitoryNotEnoughException("dormitory not enough!");
					} else {
						continue;
					}
				}
			}
			//----------------------------------重庆医大学生处理完毕-------------------------------------
			
			//1.2 2010年新需求 克卿书院 5个专业  ---男  学生需要宿舍相对集中
			j = 0;
			cla_index = 0;// 上次分配的班级
			while (j < kqgatherStudent_m.size()) {
				for (int i = cla_index; i < classesArr_m.length; i++) {
					//还有空位置
					studentmodel_a = (Studentmodel) kqgatherStudent_m
							.get(j);
					if(j+1<kqgatherStudent_m.size()){
						studentmodel_b = (Studentmodel) kqgatherStudent_m.get(j+1);
					}else{
						studentmodel_b = null;
					}
					if(j+2<kqgatherStudent_m.size()){
						studentmodel_c = (Studentmodel)kqgatherStudent_m.get(j+2);
					}else{
						studentmodel_c = null;
					}
					if(j+3<kqgatherStudent_m.size()){
						studentmodel_d = (Studentmodel) kqgatherStudent_m.get(j+3);
					}else{
						studentmodel_d = null;
					}
					if (accomodation_m[i] >= 4) {						
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_m[i].length; k++) {
							if ("".equals(classesArr_m[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if(studentmodel_a!=null){
							classesArr_m[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						if(studentmodel_b!=null){
							classesArr_m[i][index+1] = studentmodel_b.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						if(studentmodel_c!=null){
							classesArr_m[i][index+2] = studentmodel_c.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						if(studentmodel_d!=null){
							classesArr_m[i][index+3] = studentmodel_d.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						cla_index++;
						cla_index = cla_index%classesArr_m.length;
						break;
						
					}else if(accomodation_m[i] >= 1){
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_m[i].length; k++) {
							if ("".equals(classesArr_m[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if(studentmodel_a!=null&&accomodation_m[i]>0){
							classesArr_m[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						if(studentmodel_b!=null&&accomodation_m[i]>0){
							classesArr_m[i][index+1] = studentmodel_b.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						if(studentmodel_c!=null&&accomodation_m[i]>0){
							classesArr_m[i][index+2] = studentmodel_c.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						if(studentmodel_d!=null&&accomodation_m[i]>0){
							classesArr_m[i][index+3] = studentmodel_d.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						}
						cla_index++;
						cla_index = cla_index%classesArr_m.length;
						break;
						
					} else {
						// 宿舍资源不够，没有空位置了,则分到下一个班，
						//继续循环，直到所有班级都循环完，如果还找不到空位置，则报宿舍资源不够的错误
						cla_index++;
						if (cla_index == classesArr_m.length) {
							throw new DormitoryNotEnoughException(
									"dormitory not enough!");
						} else {
							continue;
						}
					}

				}
			}
			//1.2 2010年新需求 克卿书院 5个专业---女 --学生需要宿舍相对集中
			j = 0;
			cla_index = 0;// 上次分配的班级
			while (j < kqgatherStudent_f.size()) {
				for (int i = cla_index; i < classesArr_f.length; i++) {
					//还有空位置
					studentmodel_a = (Studentmodel) kqgatherStudent_f
							.get(j);
					if(j+1<kqgatherStudent_f.size()){
						studentmodel_b = (Studentmodel) kqgatherStudent_f.get(j+1);
					}else{
						studentmodel_b = null;
					}
					if(j+2<kqgatherStudent_f.size()){
						studentmodel_c = (Studentmodel) kqgatherStudent_f.get(j+2);
					}else{
						studentmodel_c = null;
					}
					if(j+3<kqgatherStudent_f.size()){
						studentmodel_d = (Studentmodel) kqgatherStudent_f.get(j+3);
					}else{
						studentmodel_d = null;
					}
					if (accomodation_f[i] >= 4) {						
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_f[i].length; k++) {
							if ("".equals(classesArr_f[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if(studentmodel_a!=null){
							classesArr_f[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						if(studentmodel_b!=null){
							classesArr_f[i][index+1] = studentmodel_b.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						if(studentmodel_c!=null){
							classesArr_f[i][index+2] = studentmodel_c.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						if(studentmodel_d!=null){
							classesArr_f[i][index+3] = studentmodel_d.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						cla_index++;
						cla_index = cla_index%classesArr_f.length;
						break;
						
					}else if(accomodation_f[i] >= 1){
						// 找到相应的空位置，（非空的就是已经分配人了，直到找到空的地方，记录索引）
						for (int k = 0; k < classesArr_f[i].length; k++) {
							if ("".equals(classesArr_f[i][k])) {
								index = k;
								break;
							} else {
								continue;
							}
						}
						if(studentmodel_a!=null&&accomodation_f[i]>0){
							classesArr_f[i][index] = studentmodel_a.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						if(studentmodel_b!=null&&accomodation_f[i]>0){
							classesArr_f[i][index+1] = studentmodel_b.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						if(studentmodel_c!=null&&accomodation_f[i]>0){
							classesArr_f[i][index+2] = studentmodel_c.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						if(studentmodel_d!=null&&accomodation_f[i]>0){
							classesArr_f[i][index+3] = studentmodel_d.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						}
						cla_index++;
						cla_index = cla_index%classesArr_f.length;
						break;
						
					} else {
						// 宿舍资源不够，没有空位置了,则分到下一个班，
						//继续循环，直到所有班级都循环完，如果还找不到空位置，则报宿舍资源不够的错误
						cla_index++;
						if (cla_index == classesArr_f.length) {
							throw new DormitoryNotEnoughException(
									"dormitory not enough!");
						} else {
							continue;
						}
					}

				}
			}
			
			//-1.3数学系男生的先分散分配进班级
			j = 0;
			while (j < mathStudent_m.size()) {
				cla_index = 0;
				for (int i = 0; i < classesArr_m.length; i++) {
					if (j < mathStudent_m.size()) {
						if (accomodation_m[i] >= 1) {
							studentmodel_a = (Studentmodel) mathStudent_m.get(j);
							for (int k = 0; k < classesArr_m[i].length; k++) {
								if ("".equals(classesArr_m[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_m[i][index] = studentmodel_a
									.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						} else {
							// 宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_m.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else {
						break;
					}
				}
			}

			// -1.3数学系女学生分配
			j = 0;
			while (j < mathStudent_f.size()) {
				cla_index = 0;
				for (int i = classesArr_f.length - 1; i >= 0; i--) {
					if (j < mathStudent_f.size()) {
						if (accomodation_f[i] >= 1) {
							studentmodel_a = (Studentmodel) mathStudent_f.get(j);
							for (int k = 0; k < classesArr_f[i].length; k++) {
								if ("".equals(classesArr_f[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_f[i][index] = studentmodel_a
									.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						} else {
							// 宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_f.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else {
						break;
					}
				}
			}

			// 新疆男学生分配
			j = 0;
			while (j < speminorityStudents_m.size()) {
				cla_index = 0;
				for (int i = 0; i < classesArr_m.length; i++) {
					if (j < speminorityStudents_m.size() - 1) {
						// 根据规则，新疆生要两两分配到一起，所以一次取两个学生
						if (accomodation_m[i] >= 2) {
							//有两个空位子
							studentmodel_a = (Studentmodel) speminorityStudents_m
									.get(j);
							studentmodel_b = (Studentmodel) speminorityStudents_m
									.get(j + 1);
							for (int k = 0; k < classesArr_m[i].length; k++) {
								if ("".equals(classesArr_m[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_m[i][index] = studentmodel_a
									.getStudentId();
							classesArr_m[i][index + 1] = studentmodel_b
									.getStudentId();
							j = j + 2;
							accomodation_m[i] = accomodation_m[i] - 2;
						} else {
							// 如果没有两个空位置，说明宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_m.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}

					} else if (j == speminorityStudents_m.size() - 1) {
						// 新疆生只有一个学生了(可能一个有落单的)
						if (accomodation_m[i] >= 1) {
							//有空位置
							studentmodel_a = (Studentmodel) speminorityStudents_m
									.get(j);
							for (int k = 0; k < classesArr_m[i].length; k++) {
								if ("".equals(classesArr_m[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_m[i][index] = studentmodel_a
									.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						} else {
							// 没有空位子了，说明这个班宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_m.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else {
						break;
					}
				}
			}
			// 新疆女学生分配
			j = 0;
			while (j < speminorityStudents_f.size()) {
				cla_index = 0;
				for (int i = classesArr_f.length - 1; i >= 0; i--) {
					if (j < speminorityStudents_f.size() - 1) {
						// 根据规则，新疆生要两两分配到一起，所以一次取两个学生
						if (accomodation_f[i] >= 2) {
							studentmodel_a = (Studentmodel) speminorityStudents_f
									.get(j);
							studentmodel_b = (Studentmodel) speminorityStudents_f
									.get(j + 1);
							for (int k = 0; k < classesArr_f[i].length; k++) {
								if ("".equals(classesArr_f[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_f[i][index] = studentmodel_a
									.getStudentId();
							classesArr_f[i][index + 1] = studentmodel_b
									.getStudentId();
							j = j + 2;
							accomodation_f[i] = accomodation_f[i] - 2;
						} else {
							// 如果没有两个空位置，说明宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_f.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else if (j == speminorityStudents_f.size() - 1) {
						// 新疆生只有一个学生了(可能一个有落单的)
						if (accomodation_f[i] >= 1) {
							studentmodel_a = (Studentmodel) speminorityStudents_f
									.get(j);
							for (int k = 0; k < classesArr_f[i].length; k++) {
								if ("".equals(classesArr_f[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_f[i][index] = studentmodel_a
									.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						} else {
							// 没有空位子了，说明这个班宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_f.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else {
						break;
					}
				}
			}

			// 其他少数民族男学生分配
			j = 0;
			while (j < minorityStudents_m.size()) {
				cla_index = 0;
				for (int i = classesArr_m.length - 1; i >= 0; i--) {
					if (j < minorityStudents_m.size() - 1) {
						// 根据规则，其他民族的心声要两两分配到一起，所以一次取两个学生
						if (accomodation_m[i] >= 2) {
							studentmodel_a = (Studentmodel) minorityStudents_m
									.get(j);
							studentmodel_b = (Studentmodel) minorityStudents_m
									.get(j + 1);
							for (int k = 0; k < classesArr_m[i].length; k++) {
								if ("".equals(classesArr_m[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_m[i][index] = studentmodel_a
									.getStudentId();
							classesArr_m[i][index + 1] = studentmodel_b
									.getStudentId();
							j = j + 2;
							accomodation_m[i] = accomodation_m[i] - 2;
						} else {
							// 没有空位子了，说明这个班宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_m.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else if (j == minorityStudents_m.size() - 1) {
						// 其他民族学生只有一个学生了(可能一个有落单的)
						if (accomodation_m[i] >= 1) {
							studentmodel_a = (Studentmodel) minorityStudents_m
									.get(j);
							for (int k = 0; k < classesArr_m[i].length; k++) {
								if ("".equals(classesArr_m[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_m[i][index] = studentmodel_a
									.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						} else {
							// 没有空位子了，说明这个班宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_m.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else {
						break;
					}
				}
			}
			// 其他少数民族女学生分配

			j = 0;
			while (j < minorityStudents_f.size()) {
				cla_index = 0;
				for (int i = 0; i < classesArr_f.length; i++) {
					if (j < minorityStudents_f.size() - 1) {
						// 取两个学生
						if (accomodation_f[i] >= 2) {
							studentmodel_a = (Studentmodel) minorityStudents_f
									.get(j);
							studentmodel_b = (Studentmodel) minorityStudents_f
									.get(j + 1);
							for (int k = 0; k < classesArr_f[i].length; k++) {
								if ("".equals(classesArr_f[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_f[i][index] = studentmodel_a
									.getStudentId();
							classesArr_f[i][index + 1] = studentmodel_b
									.getStudentId();
							j = j + 2;
							accomodation_f[i] = accomodation_f[i] - 2;
						} else {
							// 宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_f.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else if (j == minorityStudents_f.size() - 1) {
						// 只有一个学生
						if (accomodation_m[i] >= 1) {
							studentmodel_a = (Studentmodel) minorityStudents_f
									.get(j);
							for (int k = 0; k < classesArr_f[i].length; k++) {
								if ("".equals(classesArr_f[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_f[i][index] = studentmodel_a
									.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						} else {
							// 宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_f.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else {
						break;
					}
				}
			}
			

			// 汉族男学生分配
			j = 0;
			while (j < students_m.size()) {
				cla_index = 0;
				for (int i = 0; i < classesArr_m.length; i++) {
					if (j < students_m.size()) {
						if (accomodation_m[i] >= 1) {
							studentmodel_a = (Studentmodel) students_m.get(j);
							for (int k = 0; k < classesArr_m[i].length; k++) {
								if ("".equals(classesArr_m[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_m[i][index] = studentmodel_a
									.getStudentId();
							j++;
							accomodation_m[i] = accomodation_m[i] - 1;
						} else {
							// 宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_m.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else {
						break;
					}
				}
			}

			// 汉族女学生分配
			j = 0;
			while (j < students_f.size()) {
				cla_index = 0;
				for (int i = classesArr_f.length - 1; i >= 0; i--) {
					if (j < students_f.size()) {
						if (accomodation_f[i] >= 1) {
							studentmodel_a = (Studentmodel) students_f.get(j);
							for (int k = 0; k < classesArr_f[i].length; k++) {
								if ("".equals(classesArr_f[i][k])) {
									index = k;
									break;
								} else {
									continue;
								}
							}
							classesArr_f[i][index] = studentmodel_a
									.getStudentId();
							j++;
							accomodation_f[i] = accomodation_f[i] - 1;
						} else {
							// 宿舍资源不够,分到下一个班
							cla_index++;
							if (cla_index == classesArr_f.length) {
								throw new DormitoryNotEnoughException(
										"dormitory not enough!");
							} else {
								continue;
							}
						}
					} else {
						break;
					}
				}
			}

			// 保存分班结果
			String classId = "";
			// 男生数据更新到数据库中去
			for (int l = 0; l < classesArr_m.length; l++) {
				classId = classesArr_m[l][0];
				Classmodel classmodel = classmodelDAO.get(classId);
				for (int m = 1; m < classesArr_m[l].length; m++) {
					if (!"".equals(classesArr_m[l][m])) {
						Studentmodel studentmodel = studentmodelDAO
								.get(classesArr_m[l][m]);
						if (null != studentmodel) {
							studentmodel.setYxClass(classmodel);
							studentmodelDAO.update(studentmodel);
						}
					}
				}
			}
			// 女生数据更新到数据库中去
			for (int l = 0; l < classesArr_f.length; l++) {
				classId = classesArr_f[l][0];
				Classmodel classmodel = classmodelDAO.get(classId);
				for (int m = 1; m < classesArr_f[l].length; m++) {
					if (!"".equals(classesArr_f[l][m])) {
						Studentmodel studentmodel = studentmodelDAO
								.get(classesArr_f[l][m]);
						if (null != studentmodel) {
							studentmodel.setYxClass(classmodel);
							studentmodelDAO.update(studentmodel);
						}
					}
				}
			}
			
			/*
			 * 根据分班结果，把各自班级的学生 对应的分配到各个宿舍中
			 */
			// 开始分宿舍

			for (int i = 0; i < classIds.length; i++) {
				classId = classIds[i];
				// 根据班级取得此班级所有男宿舍资源
				List dorList_m = dormitorymodelDAO
						.find("from Dormitorymodel a where a.classId='"
								+ classId
								+ "' and a.gender='1' order by a.dormitoryId");
				// 根据班级取得此班级所有女宿舍资源
				List dorList_f = dormitorymodelDAO
						.find("from Dormitorymodel a where a.classId='"
								+ classId
								+ "' and a.gender='2' order by a.dormitoryId");
				//建两个宿舍二维数组容器，默认最大床位数为10个。
				//如果特殊情况，有大房间需要修改，否则不能正常分配
				String[][] dormitoryArr_m = new String[dorList_m.size()][10];
				String[][] dormitoryArr_f = new String[dorList_f.size()][10];
				//记录每个宿舍剩余的空床位
				//男宿舍
				int[] acc_now_m = new int[dorList_m.size()];
				//女宿舍
				int[] acc_now_f = new int[dorList_f.size()];
				for (int l = 0; l < dorList_m.size(); l++) {
					Dormitorymodel dormitorymodel = (Dormitorymodel) dorList_m
							.get(l);
					dormitoryArr_m[l][0] = dormitorymodel.getDormitoryId();//第一个位置放置宿舍id
					for (int m = 1; m < dormitoryArr_m[l].length; m++) {
						dormitoryArr_m[l][m] = "";
					}
				}
				for (int l = 0; l < dorList_f.size(); l++) {
					Dormitorymodel dormitorymodel = (Dormitorymodel) dorList_f
							.get(l);
					dormitoryArr_f[l][0] = dormitorymodel.getDormitoryId();//第一个位置放置宿舍id
					for (int m = 1; m < dormitoryArr_f[l].length; m++) {
						dormitoryArr_f[l][m] = "";
					}
				}
				// select int(b.ACCOMODATION)-count(a.student_id) from
				// ykt_fm.yx_dormitory b left join ykt_fm.yx_student a on
				// a.dorm_id=b.dormitory_id group by
				// b.dormitory_id,b.ACCOMODATION
				//男宿舍床位数
				List accoList_m = dormitorymodelDAO
						.find("select a.id.accomodation from AccomodationInfo a where a.id.classId='"
								+ classId
								+ "' and a.id.gender='1' order by a.id.dormitoryId");
				//女宿舍床位数
				List accoList_f = dormitorymodelDAO
						.find("select a.id.accomodation from AccomodationInfo a where a.id.classId='"
								+ classId
								+ "' and a.id.gender='2' order by a.id.dormitoryId");
				for (int k = 0; k < accoList_m.size(); k++) {
					acc_now_m[k] = Integer.parseInt(accoList_m.get(k)
							.toString());
				}
				for (int k = 0; k < accoList_f.size(); k++) {
					acc_now_f[k] = Integer.parseInt(accoList_f.get(k)
							.toString());
				}
				// 此班级男生先处理
				int s = 1;
				int flag = 0;//是否有小语种学生，要统一先分配到一个宿舍，而不是平均分配
				int dor_index = 0;//当前宿舍索引
				boolean english_first= true;
				index = 0;
				while ((s < classesArr_m[i].length)
						&& (!"".equals(classesArr_m[i][s]))) {
					dor_index = 0;//初始化索引
					//smalllanguageStudent_m_Str 保存着小语种学生的id字串
					//看看学生是否小语种学生
					if (smalllanguageStudent_m_Str.indexOf(classesArr_m[i][s]) > -1) {
						flag = 1;// 班级有小语种学生
						// 小语种班级
						for (j = 0; j < dormitoryArr_m.length; j++) {
							if ((1 == s) && (acc_now_m[j] >= 1)) {
								//班级容器中的第一个学生,并且宿舍有空位置 则把学生放进次宿舍
								dormitoryArr_m[j][1] = classesArr_m[i][s];
								s++;
								acc_now_m[j]--;
								break;
							} else if ((1 == s)) {
								// 第一个宿舍没有空位子，则到下一个宿舍去找位置，如果到最后都找不到位置，这报宿舍资源不足的错误
								dor_index++;
								if (dor_index == dormitoryArr_m.length) {
									throw new DormitoryNotEnoughException(
											"dormitory maybe not enough!");
								} else {
									continue;
								}
							} else {
								// 其他的学生是一个个往同一个宿舍里挨个往下分，达到集中到宿舍的要求
								if (acc_now_m[j] > 0) {
									for (int k = 0; k < dormitoryArr_m[j].length; k++) {
										if ("".equals(dormitoryArr_m[j][k])) {
											index = k;
											break;
										} else {
											continue;
										}
									}
									dormitoryArr_m[j][index] = classesArr_m[i][s];
									s++;
									acc_now_m[j]--;
									break;
								} else {
									//如果没有空位子了，并且是最后一个宿舍了，则报宿舍资源不足的错误
									dor_index++;
									if (dor_index == dormitoryArr_m.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								}
							}
						}

					}else if(englishStudent_m_Str.indexOf(classesArr_m[i][s]) > -1) {
						//英语专业，宿舍集中						
						flag = 2;
						int temp=s+1;
						while(temp<classesArr_m[i].length){
							if(englishStudent_m_Str.indexOf(classesArr_m[i][temp])>-1){
								temp++;
							}else{
								break;
							}
						}
						
						for (j = 0; j < dormitoryArr_m.length; j++) {
							if ("".equals(dormitoryArr_m[j][1])) {				
								for (int k = 0; k < dormitoryArr_m[j].length; k++) {
									if ("".equals(dormitoryArr_m[j][k])) {
										index = k;
										if(acc_now_m[j]>0&&s<=temp){
											english_first = false;//第一个可以处理
											dormitoryArr_m[j][index] = classesArr_m[i][s];
											s++;
											acc_now_m[j]--;
										}else{
											break;
										}
									} else {
										continue;
									}
								}
								
							}
							if(s>temp){
								//英语专业人员分配结束
								break;
							}
						}
						
						if(english_first==true){
							throw new DormitoryNotEnoughException("dormitory maybe not enough!");
						}					
					
						
					}else if(kqgatherStudent_m_Str.indexOf(classesArr_m[i][s]) > -1) {
						//五大示范专业学生，宿舍集中分配
						
						flag = 3;// 班级是示范班级
						// 小语种班级
						for (j = 0; j < dormitoryArr_m.length; j++) {
								// 按顺序 直接分到宿舍 达到集中的要求
								if (acc_now_m[j] > 0) {
									for (int k = 0; k < dormitoryArr_m[j].length; k++) {
										if ("".equals(dormitoryArr_m[j][k])) {
											index = k;
											break;
										} else {
											continue;
										}
									}
									dormitoryArr_m[j][index] = classesArr_m[i][s];
									s++;
									acc_now_m[j]--;
									break;
								} else {
									//如果没有空位子了，并且是最后一个宿舍了，则报宿舍资源不足的错误
									dor_index++;
									if (dor_index == dormitoryArr_m.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								}
						}						
						
					} else if(mathStudent_m_Str.indexOf(classesArr_m[i][s]) > -1) {
						//数学系的学生
						flag = 4;// 
						for (j = 0; j < dormitoryArr_m.length; j++) {
								// 按顺序 直接分到宿舍 达到集中的要求
								if (acc_now_m[j] > 0) {
									for (int k = 0; k < dormitoryArr_m[j].length; k++) {
										if ("".equals(dormitoryArr_m[j][k])) {
											index = k;
											break;
										} else {
											continue;
										}
									}
									dormitoryArr_m[j][index] = classesArr_m[i][s];
									s++;
									acc_now_m[j]--;
									break;
								} else {
									//如果没有空位子了，并且是最后一个宿舍了，则报宿舍资源不足的错误
									dor_index++;
									if (dor_index == dormitoryArr_m.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								}
						}
					}else {
						for (j = 0; j < dormitoryArr_m.length; j++) {
							//有小语种的班级，按照原来的分配方案走
							if (flag>0) {
								if ((flag>0) && (acc_now_m[j] >= 2)) {
									flag = -1;
									// 把新疆学生放到一个宿舍中先，根据规则，两两一起放到一个宿舍
									// 第一个宿舍有两个以上的空位子，放的下
									for (int k = 0; k < dormitoryArr_m[j].length; k++) {
										if ("".equals(dormitoryArr_m[j][k])) {
											index = k;
											break;
										} else {
											continue;
										}
									}
									dormitoryArr_m[j][index] = classesArr_m[i][s];
									s++;
									dormitoryArr_m[j][index+1] = classesArr_m[i][s];
									s++;
									acc_now_m[j] = acc_now_m[j] - 2;
								} else if (flag>0) {
									// 把新疆学生放到一个宿舍中先
									// 第一个宿舍放不下
									dor_index++;
									if (dor_index == dormitoryArr_m.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								} else {
									// 然后是一个个挨个往下分
									if (acc_now_m[j] > 0) {
										for (int k = 0; k < dormitoryArr_m[j].length; k++) {
											if ("".equals(dormitoryArr_m[j][k])) {
												index = k;
												break;
											} else {
												continue;
											}
										}
										dormitoryArr_m[j][index] = classesArr_m[i][s];
										s++;
										acc_now_m[j]--;
										if((s >= classesArr_m[i].length)
												|| ("".equals(classesArr_m[i][s]))){
											break;											
										}
									} else {
										//如果没有空位子了，并且是最后一个宿舍了，则报宿舍资源不足的错误
										dor_index++;
										if (dor_index == dormitoryArr_m.length) {
											throw new DormitoryNotEnoughException(
													"dormitory maybe not enough!");
										} else {
											continue;
										}
									}
								}
							} else {
								//没有小语种的班级
								if ((1 == s) && (acc_now_m[j] >= 2)) {
									// 把新疆学生放到一个宿舍中先
									// 第一个宿舍放的下，直接放到第一第二个
									dormitoryArr_m[j][1] = classesArr_m[i][s];
									s++;
									dormitoryArr_m[j][2] = classesArr_m[i][s];
									s++;
									acc_now_m[j] = acc_now_m[j] - 2;
								} else if ((1 == s)) {
									// 把新疆学生放到一个宿舍中先
									// 第一个宿舍放不下
									dor_index++;
									if (dor_index == dormitoryArr_m.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								} else {
									// 然后是一个个挨个往下分
									if (acc_now_m[j] > 0) {
										for (int k = 0; k < dormitoryArr_m[j].length; k++) {
											if ("".equals(dormitoryArr_m[j][k])) {
												index = k;
												break;
											} else {
												continue;
											}
										}
										dormitoryArr_m[j][index] = classesArr_m[i][s];
										s++;
										acc_now_m[j]--;
										if((s >= classesArr_m[i].length)
												|| ("".equals(classesArr_m[i][s]))){
											break;											
										}
									} else {
										dor_index++;
										if (dor_index == dormitoryArr_m.length) {
											throw new DormitoryNotEnoughException(
													"dormitory maybe not enough!");
										} else {
											continue;
										}
									}
								}
							}

						}
					}
				}
				// 女生
				s = 1;
				flag = 0;//是否有小语种学生，要统一先分配到一个宿舍，而不是平均分配
				dor_index = 0;//当前宿舍索引
				index = 0;//宿舍空位置索引
				english_first= true;
				while ((s < classesArr_f[i].length)
						&& (!"".equals(classesArr_f[i][s]))) {
					dor_index = 0;

					if (smalllanguageStudent_f_Str.indexOf(classesArr_f[i][s]) > -1) {
						flag = 1;// 有小语种
						// 小语种班级
						for (j = 0; j < dormitoryArr_f.length; j++) {
							if ((1 == s) && (acc_now_f[j] >= 1)) {
								dormitoryArr_f[j][1] = classesArr_f[i][s];
								s++;
								acc_now_f[j]--;
								break;
							} else if ((1 == s)) {
								// 第一个宿舍放不下
								dor_index++;
								if (dor_index == dormitoryArr_f.length) {
									throw new DormitoryNotEnoughException(
											"dormitory maybe not enough!");
								} else {
									continue;
								}
							} else {
								// 然后是一个个挨个往下分
								if (acc_now_f[j] > 0) {
									for (int k = 0; k < dormitoryArr_f[j].length; k++) {
										if ("".equals(dormitoryArr_f[j][k])) {
											index = k;
											break;
										} else {
											continue;
										}
									}
									dormitoryArr_f[j][index] = classesArr_f[i][s];
									s++;
									acc_now_f[j]--;
									break;
								} else {
									dor_index++;
									if (dor_index == dormitoryArr_f.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								}
							}
						}

					}else if(englishStudent_f_Str.indexOf(classesArr_f[i][s]) > -1) {
						//英语专业，宿舍集中						
						flag = 2;
						int temp=s+1;
						while(temp<classesArr_f[i].length){
							if(englishStudent_f_Str.indexOf(classesArr_f[i][temp])>-1){
								temp++;
							}else{
								break;
							}
						}
						
						for (j = 0; j < dormitoryArr_f.length; j++) {
							if ("".equals(dormitoryArr_f[j][1])) {				
								for (int k = 0; k < dormitoryArr_f[j].length; k++) {
									if ("".equals(dormitoryArr_f[j][k])) {
										index = k;
										if(acc_now_f[j]>0&&s<=temp){
											english_first = false;//第一个可以处理
											dormitoryArr_f[j][index] = classesArr_f[i][s];
											s++;
											acc_now_f[j]--;
										}else{
											break;
										}
									} else {
										continue;
									}
								}
								
							}
							if(s>temp){
								//英语专业人员分配结束
								break;
							}
						}
						
						if(english_first==true){
							throw new DormitoryNotEnoughException("dormitory maybe not enough!");
						}					
					
						
					}else if(kqgatherStudent_f_Str.indexOf(classesArr_f[i][s]) > -1) {
						//五大示范专业学生，宿舍集中分配
						
						flag = 3;// 班级是示范班级
						// 小语种班级
						for (j = 0; j < dormitoryArr_f.length; j++) {
								// 按顺序 直接分到宿舍 达到集中的要求
								if (acc_now_f[j] > 0) {
									for (int k = 0; k < dormitoryArr_f[j].length; k++) {
										if ("".equals(dormitoryArr_f[j][k])) {
											index = k;
											break;
										} else {
											continue;
										}
									}
									dormitoryArr_f[j][index] = classesArr_f[i][s];
									s++;
									acc_now_f[j]--;
									break;
								} else {
									//如果没有空位子了，并且是最后一个宿舍了，则报宿舍资源不足的错误
									dor_index++;
									if (dor_index == dormitoryArr_f.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								}
						}
						
						
					} else if(mathStudent_f_Str.indexOf(classesArr_f[i][s]) > -1) {
						//数学系的学生
						flag = 4;// 
						for (j = 0; j < dormitoryArr_f.length; j++) {
								// 按顺序 直接分到宿舍 达到集中的要求
								if (acc_now_f[j] > 0) {
									for (int k = 0; k < dormitoryArr_f[j].length; k++) {
										if ("".equals(dormitoryArr_f[j][k])) {
											index = k;
											break;
										} else {
											continue;
										}
									}
									dormitoryArr_f[j][index] = classesArr_f[i][s];
									s++;
									acc_now_f[j]--;
									break;
								} else {
									//如果没有空位子了，并且是最后一个宿舍了，则报宿舍资源不足的错误
									dor_index++;
									if (dor_index == dormitoryArr_f.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								}
						}
					} else {

						for (j = 0; j < dormitoryArr_f.length; j++) {
							if (flag>0) {
								if ((flag>0) && (acc_now_f[j] >= 2)) {
									flag = -1;
									// 把新疆学生放到一个宿舍中先，根据规则，两两一起放到一个宿舍
									// 第一个宿舍有两个以上的空位子，放的下
									for (int k = 0; k < dormitoryArr_f[j].length; k++) {
										if ("".equals(dormitoryArr_f[j][k])) {
											index = k;
											break;
										} else {
											continue;
										}
									}
									dormitoryArr_f[j][index] = classesArr_f[i][s];
									s++;
									dormitoryArr_f[j][index+1] = classesArr_f[i][s];
									s++;
									acc_now_f[j] = acc_now_f[j] - 2;
								} else if (flag>0) {
									// 把新疆学生放到一个宿舍中先
									// 第一个宿舍放不下
									dor_index++;
									if (dor_index == dormitoryArr_f.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								} else {
									// 然后是一个个挨个往下分
									if (acc_now_f[j] > 0) {
										for (int k = 0; k < dormitoryArr_f[j].length; k++) {
											if ("".equals(dormitoryArr_f[j][k])) {
												index = k;
												break;
											} else {
												continue;
											}
										}
										dormitoryArr_f[j][index] = classesArr_f[i][s];
										s++;
										acc_now_f[j]--;
										if((s >= classesArr_f[i].length)
												|| ("".equals(classesArr_f[i][s]))){
											break;											
										}
									} else {
										dor_index++;
										if (dor_index == dormitoryArr_f.length) {
											throw new DormitoryNotEnoughException(
													"dormitory maybe not enough!");
										} else {
											continue;
										}
									}
								}
							} else {
								if ((1 == s) && (acc_now_f[j] >= 2)) {
									// 把新疆学生放到一个宿舍中先
									// 第一个宿舍放的下
									dormitoryArr_f[j][1] = classesArr_f[i][s];
									s++;
									dormitoryArr_f[j][2] = classesArr_f[i][s];
									s++;
									acc_now_f[j] = acc_now_f[j] - 2;
								} else if ((1 == s)) {
									// 把新疆学生放到一个宿舍中先
									// 第一个宿舍放不下
									dor_index++;
									if (dor_index == dormitoryArr_f.length) {
										throw new DormitoryNotEnoughException(
												"dormitory maybe not enough!");
									} else {
										continue;
									}
								} else {
									// 然后是一个个挨个往下分
									if (acc_now_f[j] > 0) {
										for (int k = 0; k < dormitoryArr_f[j].length; k++) {
											if ("".equals(dormitoryArr_f[j][k])) {
												index = k;
												break;
											} else {
												continue;
											}
										}
										dormitoryArr_f[j][index] = classesArr_f[i][s];
										s++;
										acc_now_f[j]--;
										if((s >= classesArr_f[i].length)
												|| ("".equals(classesArr_f[i][s]))){
											break;											
										}
									} else {
										dor_index++;
										if (dor_index == dormitoryArr_f.length) {
											throw new DormitoryNotEnoughException(
													"dormitory maybe not enough!");
										} else {
											continue;
										}
									}
								}
							}

						}
					}
				}

				// 更新数据到数据库
				// 保存分班结果
				String dormitoryId = "";
				// 男生数据更新到数据库中去
				for (int l = 0; l < dormitoryArr_m.length; l++) {
					dormitoryId = dormitoryArr_m[l][0];
					for (int m = 1; m < dormitoryArr_m[l].length; m++) {
						if (!"".equals(dormitoryArr_m[l][m])) {
							Studentmodel studentmodel = studentmodelDAO
									.get(dormitoryArr_m[l][m]);
							if (null != studentmodel) {
								studentmodel.setDormId(dormitoryId);
								studentmodelDAO.update(studentmodel);
							}
						}

					}
				}
				// 女生数据更新到数据库中去
				for (int l = 0; l < dormitoryArr_f.length; l++) {
					dormitoryId = dormitoryArr_f[l][0];
					for (int m = 1; m < dormitoryArr_f[l].length; m++) {
						if (!"".equals(dormitoryArr_f[l][m])) {
							Studentmodel studentmodel = studentmodelDAO
									.get(dormitoryArr_f[l][m]);
							if (null != studentmodel) {
								studentmodel.setDormId(dormitoryId);
								studentmodelDAO.update(studentmodel);
							}
						}

					}
				}
			}
		}
	}

	public void saveCollegeDistribution(String[][] deleteX, List collegeList)
			throws StudentAlreadyInDormException {
		List noList = collegemodelDAO
				.find("from Studentmodel a where a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and a.majorin<>'623' and (a.dormId<>'' or a.dormId is not null)");
		if (noList.size() > 0) {
			throw new StudentAlreadyInDormException(
					"student already in dormitory");
		}
		// 清空表
		List collegeDistr = distributionTempDAO.getAll();
		for (int s = 0; s < collegeDistr.size(); s++) {
			DistributionTemp distributiontemp = (DistributionTemp) collegeDistr
					.get(s);
			distributionTempDAO.delete(distributiontemp);
		}
		// 专业
		List majorInList = studentmodelDAO
				.find("select new org.king.classmanage.web.help.MajorinInfo(c.dictCaption,b.deptName,a.id.dictValue,a.dictCaption) "
						+ "from Dictionary a,Department b,Dictionary c "
						+ "where a.id.dictNo=11 and a.dictAvail<>0 and a.dictParent=b.deptCode "
						+ "and a.dictParent1=c.id.dictValue and c.id.dictNo=14 "
						+ "and a.dictCaption not like '%武警班%' order by c.id.dictValue,a.id.dictValue");
		String majorinCode = "";
		String[] collegeArr = new String[collegeList.size()];
		int collegeCount = 0;
		for (int i = 0; i < majorInList.size(); i++) {
			collegeCount = 0;
			MajorinInfo majorininfo = (MajorinInfo) majorInList.get(i);
			majorinCode = majorininfo.getDaima();
			for (int j = 0; j < deleteX.length; j++) {
				collegeArr[j] = "";
				for (int k = 0; k < deleteX[j].length; k++) {
					if (majorinCode.equals(deleteX[j][k])) {
						Collegemodel collegemodel = (Collegemodel) collegeList
								.get(j);
						collegeArr[collegeCount] = collegemodel.getCollegeId();
						collegeCount++;
						break;
					}
				}
			}

			// 拿中国学生
			if (collegeCount > 0) {
				List stuList = studentmodelDAO
						.find("select a.studentId from Studentmodel a "
								+ "where a.majorin='" + majorinCode + "' "
								+ "and a.enrollYear='"
								+ DateUtil.getNow("yyyy") + "' "
								// "and a.enrollYear='2005'"
								+ " order by a.gender,a.fromProvince");
				int c = 0;
				String collegeId = "";
				String studentId = "";
				while (c < stuList.size()) {
					for (int t = 0; t < collegeCount; t++) {
						collegeId = collegeArr[t];
						if (c < stuList.size()) {
							studentId = stuList.get(c).toString();
							c++;
							DistributionTemp distributiontemp = new DistributionTemp();
							distributiontemp.setStudentId(studentId);
							distributiontemp.setCollegeId(collegeId);
							distributionTempDAO.save(distributiontemp);
						} else {
							break;
						}
					}
				}

			} else {
				continue;
			}

		}

	}

	public void saveLastDistribution() throws DormitoryNotEnoughException,
			StudentAlreadyInDormException {
		List noList = collegemodelDAO
				.find("from Studentmodel a where a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and a.majorin<>'623' and (a.dormId<>'' or a.dormId is not null)");
		if (noList.size() > 0) {
			throw new StudentAlreadyInDormException(
					"student already in dormitory");
		}
		List collegeList = collegemodelDAO.getAll();
		String studentIds = "";
		for (int i = 0; i < collegeList.size(); i++) {
			Collegemodel collegemodel = (Collegemodel) collegeList.get(i);
			System.out.println(collegemodel.getCollegeName());
			List CHNStudent = distributionTempDAO
					.find("select a.studentId from DistributionTemp a,Studentmodel b where a.collegeId='"
							+ collegemodel.getCollegeId()
							+ "' and a.studentId=b.studentId and b.nationality='CHN' and b.enrollYear='"
							+ DateUtil.getNow("yyyy") + "'");
			List AbroadStudent = distributionTempDAO
					.find("select a.studentId from DistributionTemp a,Studentmodel b where a.collegeId='"
							+ collegemodel.getCollegeId()
							+ "' and a.studentId=b.studentId and b.nationality<>'CHN' and b.enrollYear='"
							+ DateUtil.getNow("yyyy") + "'");
			List classList = classmodelDAO
					.find("select a.classId from Classmodel a where a.yxCollege.collegeId='"
							+ collegemodel.getCollegeId()
							+ "' and a.curYear='"
							+ DateUtil.getNow("yyyy") + "'");
			System.out.println(classList.size());
			if (classList.size() > 0) {
				String[] classIds = new String[classList.size()];
				classList.toArray(classIds);
				studentIds = "";
				if (CHNStudent.size() > 0) {
					int stuCount = CHNStudent.size();
					for (int j = 0; j < stuCount; j++) {
						if (j == stuCount - 1) {
							studentIds += "'" + CHNStudent.get(j).toString()
									+ "'";
						} else {
							studentIds += "'" + CHNStudent.get(j).toString()
									+ "',";
						}
					}
					// 分配
					try {
						saveDormitoryDistribution(studentIds, classIds);
					} catch (DormitoryNotEnoughException e) {
						e.printStackTrace();
						throw new DormitoryNotEnoughException(e.getMessage());
					} catch (StudentAlreadyInDormException e) {
						e.printStackTrace();
						throw new StudentAlreadyInDormException(e.getMessage());
					}

				}
				studentIds = "";
				if (AbroadStudent.size() > 0) {
					int stuCount = AbroadStudent.size();
					for (int j = 0; j < stuCount; j++) {
						if (j == stuCount - 1) {
							studentIds += "'" + AbroadStudent.get(j).toString()
									+ "'";
						} else {
							studentIds += "'" + AbroadStudent.get(j).toString()
									+ "',";
						}
					}
					// 分配

					saveClassDistribution(studentIds, classIds);
				}
			}

		}

		// 同步数据

		List unCommonList = dormitorymodelDAO
				.find("select new map(a.studentId as student_id,c.classId as class_id) "
						+ "from Studentmodel a,Dormitorymodel c where a.dormId=c.dormitoryId "
						+ "and a.yxClass.classId<>c.classId");
		String student_id = "";
		String class_id = "";
		for (int i = 0; i < unCommonList.size(); i++) {
			HashMap uncommonlist = (HashMap) unCommonList.get(i);
			student_id = uncommonlist.get("student_id").toString();
			class_id = uncommonlist.get("class_id").toString();
			Studentmodel studentmodel = studentmodelDAO.get(student_id);
			Classmodel classmodel = classmodelDAO.get(class_id);
			studentmodel.setYxClass(classmodel);
			studentmodelDAO.update(studentmodel);
		}

	}

	public List getDormitory(List param) {
		List dorm = new ArrayList();
		return dorm;
	}

	public void addDorm(Dormitorymodel dorm) {
		dormitorymodelDAO.save(dorm);
	}

	public List getAllDorm() {
		return dormitorymodelDAO.getAll();
	}

	public Dormitorymodel getDormByDormId(Serializable dormId) {
		return dormitorymodelDAO.get(dormId);
	}

	public void updateDormitory(Dormitorymodel dorm)
			throws AccomodationNotRightException {
		List list = studentmodelDAO
				.find("select count(a.studentId) from Studentmodel a where a.dormId='"
						+ dorm.getDormitoryId() + "'");
		int stuCount = 0;
		if (list.size() > 0) {
			stuCount = Integer.parseInt(list.get(0).toString());
		}
		if (dorm.getAccomodation() < stuCount) {
			throw new AccomodationNotRightException("accomodation Not Right");
		} else {
			dormitorymodelDAO.update(dorm);
		}

	}

	public boolean updateDormitory(String[] temp, String[] untemp)
			throws DormitoryHasStuException {
		List list = studentmodelDAO
				.find("select a.dormId from Studentmodel a "
						+ "where a.dormId<>'' and a.dormId is not null and a.enrollYear='"
						+ DateUtil.getNow("yyyy") + "'");
		String dromStr = "";
		for (int i = 0; i < list.size(); i++) {
			dromStr += list.get(i).toString() + ",";
		}

		String dormitoryId = "";
		String classId = "";
		List location_list = studentmodelDAO
				.find("from Dictionary a where a.id.dictNo= 6 ");
		List dormitory_list = studentmodelDAO
				.find("from Dictionary a where a.id.dictNo= 7 ");
		if (null != untemp) {
			for (int i = 0; i < untemp.length; i++) {
				if (i % 6 == 0) {
					// dormitoryId
					dormitoryId = untemp[i];
					if ("".equals(dormitoryId)) {
						i = i + 5;
						continue;
					}
					if (dromStr.indexOf(dormitoryId) != -1) {
						// 宿舍有学生
						Dormitorymodel dormm = dormitorymodelDAO
								.get(dormitoryId);

						if (!"".equals(dormm.getLocation())) {// 校区
							String location = "";
							String Cap = "";
							for (int k = 0; k < location_list.size(); k++) {
								Dictionary dictionary = (Dictionary) location_list
										.get(k);
								location = dictionary.getId().getDictValue();
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
								dormitory = dictionary.getId().getDictValue();
								if (dormitory.equals(dormm.getDormitory())) {
									Cap = dictionary.getDictCaption();
									break;
								}
							}
							dormm.setDormitory(Cap);
						}
						throw new DormitoryHasStuException(dormm.getLocation()
								+ dormm.getDormitory() + dormm.getRoomNumber());
					}
					Dormitorymodel dormitorymodel = dormitorymodelDAO
							.get(dormitoryId);
					dormitorymodel.setClassId(null);
					dormitorymodelDAO.update(dormitorymodel);
				}
			}

		}
		if (null != temp) {
			for (int i = 0; i < temp.length; i++) {
				if (i % 6 == 0) {
					// dormitoryId
					dormitoryId = temp[i];
					if ("".equals(dormitoryId)) {
						i = i + 5;
						continue;
					}
					i = i + 5;
					classId = temp[i];
					Dormitorymodel dormitorymodel = dormitorymodelDAO
							.get(dormitoryId);
					dormitorymodel.setClassId(classId);
					dormitorymodelDAO.update(dormitorymodel);
				}

			}
		}
		return true;

	}

	public void updateBatchDorm(String operator) {
		// batch update student classInfo 同步两张表的班级信息
		// jdbcTemplate
		// .update("update ykt_fm.yx_student a set a.class_id = "
		// + "(select b.class_id from ykt_fm.yx_dormitory b where
		// a.dorm_id=b.dormitory_id) "
		// + "where a.dorm_id in (select b.dormitory_id from ykt_fm.yx_dormitory
		// b "
		// + "where a.dorm_id=b.dormitory_id) ");
		List list = dormitorymodelDAO
				.find("select new map(a.studentId as studentId,a.yxClass.classId as oclassId,"
						+ "b.classId as nclassId,b.dormitoryId as dormitoryId) "
						+ "from Studentmodel a,Dormitorymodel b where a.dormId=b.dormitoryId "
						+ "and a.yxClass.classId<>b.classId and a.enrollYear='"
						+ DateUtil.getNow("yyyy") + "'");
		Iterator iter = list.iterator();
		while (iter.hasNext()) {
			HashMap stu_class = (HashMap) iter.next();
			String studentId = stu_class.get("studentId").toString();
			String oclassId = stu_class.get("oclassId").toString();
			String nclassId = stu_class.get("nclassId").toString();
			String dormitoryId = stu_class.get("dormitoryId").toString();
			Studentmodel studentmodel = studentmodelDAO.get(studentId);
			Classmodel classmodel = classmodelDAO.get(nclassId);
			studentmodel.setYxClass(classmodel);
			studentmodelDAO.update(studentmodel);

			DormAlerthis dormHis = new DormAlerthis();
			dormHis.setDormitoryIdO(dormitoryId);
			dormHis.setDormitoryIdN(dormitoryId);
			dormHis.setClassIdO(oclassId);
			dormHis.setClassIdN(nclassId);
			dormHis.setStudentId(studentId);
			dormHis.setOperatorTime(DateUtil.getNow());
			dormHis.setOperatorId(operator);
			dormAlerthisDAO.save(dormHis);
		}
	}

	public void deleteDorm(Dormitorymodel dorm) {
		dormitorymodelDAO.delete(dorm);
	}

	public void deleteDorm(String[] deleteX) throws DormitoryHasStuException {
		if (deleteX != null) {
			for (int i = 0; i < deleteX.length; i++) {
				Dormitorymodel dorm = dormitorymodelDAO.get(deleteX[i]);
				List list = studentmodelDAO
						.find("select count(a.studentId) from Studentmodel a where a.dormId='"
								+ dorm.getDormitoryId() + "'");
				int stuCount = 0;
				if (list.size() > 0) {
					stuCount = Integer.parseInt(list.get(0).toString());
				}
				if (stuCount > 0) {
					throw new DormitoryHasStuException(dorm.getRoomNumber());
				} else {
					dormitorymodelDAO.delete(dorm);
				}
			}
		}
	}

	public Dormitorymodel[] getDormByRoom(String roomNumber) {
		List dormList = new ArrayList();
		dormList = dormitorymodelDAO
				.find("from Dormitorymodel b where b.roomNumber='" + roomNumber
						+ "'");
		if (dormList.size() == 0) {
			return null;
		}
		Dormitorymodel[] dorms = new Dormitorymodel[dormList.size()];
		for (int i = 0; i < dormList.size(); i++) {
			dorms[i] = (Dormitorymodel) dormList.get(i);
		}
		return dorms;
	}

	public Dormitorymodel[] getOneDorm(String dorm, String room) {
		List dormList = new ArrayList();
		dormList = dormitorymodelDAO
				.find("from Dormitorymodel b where b.roomNumber='" + room
						+ "'and b.dormitory='" + dorm + "'");
		if (dormList.size() == 0) {
			return null;
		}
		Dormitorymodel[] dorms = new Dormitorymodel[dormList.size()];
		for (int i = 0; i < dormList.size(); i++) {
			dorms[i] = (Dormitorymodel) dormList.get(i);
		}
		return dorms;
	}

	public List findDormitorys(String[] args, String schoolId)
			throws BusinessException {
		String dormitory = args[0];
		String roomNumber = args[1];
		String collegeId = args[2];
		String classId = args[3];
		String managerId = args[4];
		String studentNo = args[5];
		String stuName = args[6];
		String gender = args[7];
		String majorin = args[8];
		String nation = args[9];
		String fromProvince = args[10];
		String location = args[11];
		String page = args[12];
		String area = args[13];
		String district = "";
		String enterenceNo = "";
		if (args.length > 14) {
			district = args[14];
		}
		if (args.length > 15) {
			enterenceNo = args[15];
		}

		List dormList = null;
		String hqlStr = "";
		if (schoolId != null && schoolId.equals("0001")) {
			hqlStr = "select distinct new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,a.area,a.location,"
					+ "a.dormitory,'',a.roomNumber,a.accomodation,d.classId,b.gender,b.fromProvince,c.collegeName,d.classNo,"
					+ "'',b.studentNo,b.stuName,b.majorin,b.nation,b.enterenceNo) "
					+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d ";
			if (StringUtils.isNotEmpty(managerId)) {
				hqlStr += ",Classmanager e,Managermodel f,Managermanagerrole ff ";
			}
			hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
					+ "and d.yxCollege.collegeId=c.collegeId "
					+ "and d.yxCollege.yxSchool.schoolId='"
					+ schoolId
					+ "' "
					+ "and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";
		} else if (schoolId != null && schoolId.equals("0002")) {
			hqlStr = "select distinct new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,a.area,a.location,"
					+ "a.dormitory,'',a.roomNumber,a.accomodation,d.classId,b.gender,b.fromProvince,c.collegeName,d.classNo,"
					+ "'',b.studentNo,b.stuName,b.majorin,g.district,b.enterenceNo) "
					+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d,GzStuTemp g ";
			if (StringUtils.isNotEmpty(managerId)) {
				hqlStr += ",Classmanager e,Managermodel f,Managermanagerrole ff ";
			}
			hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
					+ "and b.enterenceNo=g.enterenceNo "
					+ "and d.yxCollege.collegeId=c.collegeId "
					+ "and d.yxCollege.yxSchool.schoolId='"
					+ schoolId
					+ "' "
					+ "and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";
		}

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(managerId)) {
			hqlStr += "and d.classId=e.id.classId and e.id.managerId=f.managerId "
					+ "and f.managerId=ff.id.managerId and ff.id.roleId='21' ";
			hqlStr += (StringUtils.isNotEmpty(managerId) ? " and f.managerId=?"
					: "");
			if (StringUtils.isNotEmpty(managerId)) {
				myQuery.addPara(managerId, Types.VARCHAR);
			}
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
					: "");
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
					: "");
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(collegeId)) {
			hqlStr += (StringUtils.isNotEmpty(collegeId) ? " and c.collegeId=?"
					: "");
			myQuery.addPara(collegeId, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(classId)) {
			hqlStr += (StringUtils.isNotEmpty(classId) ? " and d.classId=?"
					: "");
			myQuery.addPara(classId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentNo)) {
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
					: "");
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(enterenceNo)) {
			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
					: "");
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?"
					: "");
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
			myQuery.addPara(nation, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(district)) {
			hqlStr += (StringUtils.isNotEmpty(district) ? " and g.district=?"
					: "");
			myQuery.addPara(district, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
					: "");
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?"
					: "");
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(area)) {
			hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");
			myQuery.addPara(area, Types.VARCHAR);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setQueryString(hqlStr.toString());
		myQuery.setPageSize(100);
		myQuery.setOffset(true);
		myQuery.setOrderby(" order by a.location,a.dormitory,a.roomNumber");
		dormList = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < dormList.size(); i++) {
			DormitoryWithAllInfo dormitorywithallinfo = (DormitoryWithAllInfo) dormList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(dormitorywithallinfo.getClassId())) {
				if (clsssIdCode.equals(dormitorywithallinfo.getClassId())) {
					dormitorywithallinfo.setManagerName(clsmanagerStr);
				} else {
					clsssIdCode = dormitorywithallinfo.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ dormitorywithallinfo.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						dormitorywithallinfo.setManagerName(clsmanagerStr);
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorywithallinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorywithallinfo.getGender())) {
					dormitorywithallinfo.setGender(genderStr);
				} else {
					genderCode = dormitorywithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						dormitorywithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(dormitorywithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(dormitorywithallinfo
						.getFromProvince())) {
					dormitorywithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = dormitorywithallinfo.getFromProvince();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 10 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getFromProvince()
									+ "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						fromProvinceStr = Cap;
						dormitorywithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(dormitorywithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(dormitorywithallinfo.getMajorin())) {
					dormitorywithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = dormitorywithallinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						dormitorywithallinfo.setMajorin(majorinStr);
					}
				}

			}
			if (schoolId != null && schoolId.equals("0001")) {
				String nationCode = "";
				String nationStr = "";
				if (!"".equals(dormitorywithallinfo.getNation())) {// 民族
					if (nationCode.equals(dormitorywithallinfo.getNation())) {
						dormitorywithallinfo.setNation(nationStr);
					} else {
						nationCode = dormitorywithallinfo.getNation();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 2 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getNation()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							nationStr = Cap;
							dormitorywithallinfo.setNation(nationStr);
						}
					}

				}
			} else if (schoolId != null && schoolId.equals("0002")) {
				String nationCode = "";
				String nationStr = "";
				if (!"".equals(dormitorywithallinfo.getNation())) {// 上海区县
					if (nationCode.equals(dormitorywithallinfo.getNation())) {
						dormitorywithallinfo.setNation(nationStr);
					} else {
						nationCode = dormitorywithallinfo.getNation();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 23 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getNation()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							nationStr = Cap;
							dormitorywithallinfo.setNation(nationStr);
						}
					}

				}
			}

			if (schoolId != null && schoolId.equals("0002")) {
				String areaCode = "";
				String areaStr = "";
				if (!"".equals(dormitorywithallinfo.getArea())) {// 大校区
					if (areaCode.equals(dormitorywithallinfo.getArea())) {
						dormitorywithallinfo.setArea(areaStr);
					} else {
						areaCode = dormitorywithallinfo.getArea();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getArea() + "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							areaStr = Cap;
							dormitorywithallinfo.setArea(areaStr);
						}
					}

				}
			}
			// --------------------------------------------------------------------
			if (schoolId != null && schoolId.equals("0001")) {
				String locationCode = "";
				String locationStr = "";
				if (!"".equals(dormitorywithallinfo.getLocation())) {// 校区
					if (locationCode.equals(dormitorywithallinfo.getLocation())) {
						dormitorywithallinfo.setLocation(locationStr);
					} else {
						locationCode = dormitorywithallinfo.getLocation();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getLocation()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							locationStr = Cap;
							dormitorywithallinfo.setLocation(locationStr);
						}
					}

				}
			} else if (schoolId != null && schoolId.equals("0002")) {
				String locationCode = "";
				String locationStr = "";
				if (!"".equals(dormitorywithallinfo.getLocation())) {// 校区
					if (locationCode.equals(dormitorywithallinfo.getLocation())) {
						dormitorywithallinfo.setLocation(locationStr);
					} else {
						locationCode = dormitorywithallinfo.getLocation();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getLocation()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							locationStr = Cap;
							dormitorywithallinfo.setLocation(locationStr);
						}
					}

				}
			}

			if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
				String dormitoryCode = "";
				String dormitoryStr = "";
				if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
					if (dormitoryCode.equals(dormitorywithallinfo
							.getDormitory())) {
						dormitorywithallinfo.setDormitory(dormitoryStr);
					} else {
						dormitoryCode = dormitorywithallinfo.getDormitory();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getDormitory()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							dormitoryStr = Cap;
							dormitorywithallinfo.setDormitory(dormitoryStr);
						}
					}

				}
			} else if (schoolId != null && schoolId.equals("0002")) {// 护理学院
				String dormitoryCode = "";
				String dormitoryStr = "";
				if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
					if (dormitoryCode.equals(dormitorywithallinfo
							.getDormitory())) {
						dormitorywithallinfo.setDormitory(dormitoryStr);
					} else {
						dormitoryCode = dormitorywithallinfo.getDormitory();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getDormitory()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							dormitoryStr = Cap;
							dormitorywithallinfo.setDormitory(dormitoryStr);
						}
					}

				}
			}

		}
		return dormList;
	}

	public List findDormitorysExport(String[] args, String schoolId)
			throws BusinessException {
		String dormitory = args[0];
		String roomNumber = args[1];
		String collegeId = args[2];
		String classId = args[3];
		String managerId = args[4];
		String studentNo = args[5];
		String stuName = args[6];
		String gender = args[7];
		String majorin = args[8];
		String nation = args[9];
		String fromProvince = args[10];
		String location = args[11];
		String page = args[12];
		String area = args[13];
		String district = "";
		String enterenceNo = "";
		if (args.length > 14) {
			district = args[14];
		}
		if (args.length > 15) {
			enterenceNo = args[15];
		}

		List dormList = null;
		String hqlStr = "";
		if (schoolId != null && schoolId.equals("0001")) {
			hqlStr = "select distinct new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,a.area,a.location,"
					+ "a.dormitory,'',a.roomNumber,a.accomodation,d.classId,b.gender,b.fromProvince,c.collegeName,d.classNo,"
					+ "'',b.studentNo,b.stuName,b.majorin,b.nation,b.enterenceNo) "
					+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d ";
			if (StringUtils.isNotEmpty(managerId)) {
				hqlStr += ",Classmanager e,Managermodel f,Managermanagerrole ff ";
			}
			hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
					+ "and d.yxCollege.collegeId=c.collegeId "
					+ "and d.yxCollege.yxSchool.schoolId='"
					+ schoolId
					+ "' "
					+ "and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";
		} else if (schoolId != null && schoolId.equals("0002")) {
			hqlStr = "select distinct new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,a.area,a.location,"
					+ "a.dormitory,'',a.roomNumber,a.accomodation,d.classId,b.gender,b.fromProvince,c.collegeName,d.classNo,"
					+ "'',b.studentNo,b.stuName,b.majorin,g.district,b.enterenceNo) "
					+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d,GzStuTemp g ";
			if (StringUtils.isNotEmpty(managerId)) {
				hqlStr += ",Classmanager e,Managermodel f,Managermanagerrole ff ";
			}
			hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
					+ "and b.enterenceNo=g.enterenceNo "
					+ "and d.yxCollege.collegeId=c.collegeId "
					+ "and d.yxCollege.yxSchool.schoolId='"
					+ schoolId
					+ "' "
					+ "and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";
		}

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(managerId)) {
			hqlStr += "and d.classId=e.id.classId and e.id.managerId=f.managerId "
					+ "and f.managerId=ff.id.managerId and ff.id.roleId='21' ";
			hqlStr += (StringUtils.isNotEmpty(managerId) ? " and f.managerId=?"
					: "");
			if (StringUtils.isNotEmpty(managerId)) {
				myQuery.addPara(managerId, Types.VARCHAR);
			}
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
					: "");
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
					: "");
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(collegeId)) {
			hqlStr += (StringUtils.isNotEmpty(collegeId) ? " and c.collegeId=?"
					: "");
			myQuery.addPara(collegeId, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(classId)) {
			hqlStr += (StringUtils.isNotEmpty(classId) ? " and d.classId=?"
					: "");
			myQuery.addPara(classId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentNo)) {
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
					: "");
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(enterenceNo)) {
			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
					: "");
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?"
					: "");
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
			myQuery.addPara(nation, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(district)) {
			hqlStr += (StringUtils.isNotEmpty(district) ? " and g.district=?"
					: "");
			myQuery.addPara(district, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
					: "");
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?"
					: "");
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(area)) {
			hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");
			myQuery.addPara(area, Types.VARCHAR);
		}

		myQuery.setPageStartNo(0);
		myQuery.setQueryString(hqlStr.toString());

		myQuery.setOrderby(" order by a.location,a.dormitory,a.roomNumber");
		dormList = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < dormList.size(); i++) {
			DormitoryWithAllInfo dormitorywithallinfo = (DormitoryWithAllInfo) dormList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(dormitorywithallinfo.getClassId())) {
				if (clsssIdCode.equals(dormitorywithallinfo.getClassId())) {
					dormitorywithallinfo.setManagerName(clsmanagerStr);
				} else {
					clsssIdCode = dormitorywithallinfo.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ dormitorywithallinfo.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						dormitorywithallinfo.setManagerName(clsmanagerStr);
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorywithallinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorywithallinfo.getGender())) {
					dormitorywithallinfo.setGender(genderStr);
				} else {
					genderCode = dormitorywithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						dormitorywithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(dormitorywithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(dormitorywithallinfo
						.getFromProvince())) {
					dormitorywithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = dormitorywithallinfo.getFromProvince();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 10 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getFromProvince()
									+ "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						fromProvinceStr = Cap;
						dormitorywithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(dormitorywithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(dormitorywithallinfo.getMajorin())) {
					dormitorywithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = dormitorywithallinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						dormitorywithallinfo.setMajorin(majorinStr);
					}
				}

			}
			if (schoolId != null && schoolId.equals("0001")) {
				String nationCode = "";
				String nationStr = "";
				if (!"".equals(dormitorywithallinfo.getNation())) {// 民族
					if (nationCode.equals(dormitorywithallinfo.getNation())) {
						dormitorywithallinfo.setNation(nationStr);
					} else {
						nationCode = dormitorywithallinfo.getNation();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 2 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getNation()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							nationStr = Cap;
							dormitorywithallinfo.setNation(nationStr);
						}
					}

				}
			} else if (schoolId != null && schoolId.equals("0002")) {
				String nationCode = "";
				String nationStr = "";
				if (!"".equals(dormitorywithallinfo.getNation())) {// 上海区县
					if (nationCode.equals(dormitorywithallinfo.getNation())) {
						dormitorywithallinfo.setNation(nationStr);
					} else {
						nationCode = dormitorywithallinfo.getNation();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 23 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getNation()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							nationStr = Cap;
							dormitorywithallinfo.setNation(nationStr);
						}
					}

				}
			}
			// --------------------------------------------------------------------------------
			if (schoolId != null && schoolId.equals("0002")) {// 护理学院
				String areaCode = "";
				String areaStr = "";
				if (!"".equals(dormitorywithallinfo.getArea())) {// 大校区
					if (areaCode.equals(dormitorywithallinfo.getArea())) {
						dormitorywithallinfo.setLocation(areaStr);
					} else {
						areaCode = dormitorywithallinfo.getArea();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getArea() + "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							areaStr = Cap;
							dormitorywithallinfo.setArea(areaStr);
						}
					}

				}
			}

			if (schoolId != null && schoolId.equals("0002")) {// 护理学院
				String locationCode = "";
				String locationStr = "";
				if (!"".equals(dormitorywithallinfo.getLocation())) {// 校区
					if (locationCode.equals(dormitorywithallinfo.getLocation())) {
						dormitorywithallinfo.setLocation(locationStr);
					} else {
						locationCode = dormitorywithallinfo.getLocation();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getLocation()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							locationStr = Cap;
							dormitorywithallinfo.setLocation(locationStr);
						}
					}

				}
			} else if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
				String locationCode = "";
				String locationStr = "";
				if (!"".equals(dormitorywithallinfo.getLocation())) {// 校区
					if (locationCode.equals(dormitorywithallinfo.getLocation())) {
						dormitorywithallinfo.setLocation(locationStr);
					} else {
						locationCode = dormitorywithallinfo.getLocation();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getLocation()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							locationStr = Cap;
							dormitorywithallinfo.setLocation(locationStr);
						}
					}

				}
			}

			if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
				String dormitoryCode = "";
				String dormitoryStr = "";
				if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
					if (dormitoryCode.equals(dormitorywithallinfo
							.getDormitory())) {
						dormitorywithallinfo.setDormitory(dormitoryStr);
					} else {
						dormitoryCode = dormitorywithallinfo.getDormitory();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getDormitory()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							dormitoryStr = Cap;
							dormitorywithallinfo.setDormitory(dormitoryStr);
						}
					}

				}
			} else if (schoolId != null && schoolId.equals("0002")) {// 护理学院
				String dormitoryCode = "";
				String dormitoryStr = "";
				if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
					if (dormitoryCode.equals(dormitorywithallinfo
							.getDormitory())) {
						dormitorywithallinfo.setDormitory(dormitoryStr);
					} else {
						dormitoryCode = dormitorywithallinfo.getDormitory();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
										+ "and a.id.dictValue='"
										+ dormitorywithallinfo.getDormitory()
										+ "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							dormitoryStr = Cap;
							dormitorywithallinfo.setDormitory(dormitoryStr);
						}
					}

				}
			}

		}
		return dormList;
	}

	public List findDormitorysExport4yg(String[] args, String schoolId)
			throws BusinessException {
		String dormitory = args[2];
		String unit = args[3];
		String roomNumber = args[4];
		String dormfee = args[5];
		String studentNo = args[6];
		String stuName = args[7];
		String gender = args[8];
		String location = args[1];
		String page = args[9];
		String area = args[0];
		String operator = args[10];
		List dormList = null;
		String hqlStr = "select new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,a.area,a.location,"
				+ "a.dormitory,a.unit,a.roomNumber,a.accomodation,a.classId,b.sex as gender,"
				+ "'','','','',b.graduateNo as studentNo,b.graduateName as stuName,b.speciality as majorin,b.nation,b.birthday) "
				+ "from Dormitorymodel a,YxGraduate b,TabSsManager c,Dictionary d ";
		hqlStr += " where a.dormitoryId=b.dormitoryId " + "and b.enrollYear='"
				+ DateUtil.getNow("yyyy") + "' "
				+ "and d.id.dictNo=21 and d.id.dictValue=a.dormitory "
				+ " and c.tabSsDept.id = b.distriction and c.stuNo = '"
				+ operator + "' ";

		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(unit) ? " and a.unit=?" : "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(dormfee) ? " and a.fee = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.graduateNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.graduateName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.sex=?" : "");

		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?" : "");

		hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(unit)) {
			myQuery.addPara(unit, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormfee)) {
			myQuery.addPara(new Double(dormfee), Types.DOUBLE);
		}
		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
		}

		myQuery.setPageStartNo(0);
		myQuery.setQueryString(hqlStr.toString());

		myQuery
				.setOrderby(" order by a.area,a.location,d.dictSort,a.unit,a.roomNumber");
		dormList = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < dormList.size(); i++) {
			DormitoryWithAllInfo dormitorywithallinfo = (DormitoryWithAllInfo) dormList
					.get(i);

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorywithallinfo.getBirthday())) {
				String birthday = dormitorywithallinfo.getBirthday();
				birthday = birthday.substring(0, 4) + "-"
						+ birthday.substring(4, 6) + "-"
						+ birthday.substring(6, 8);
				dormitorywithallinfo.setBirthday(birthday);
			}
			if (!"".equals(dormitorywithallinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorywithallinfo.getGender())) {
					dormitorywithallinfo.setGender(genderStr);
				} else {
					genderCode = dormitorywithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getGender() + "'");
					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						dormitorywithallinfo.setGender(genderStr);
					}
				}
			}
			// --------------------------------------------------------------------------------
			String areaCode = "";
			String areaStr = "";
			if (!"".equals(dormitorywithallinfo.getArea())) {// 大校区
				if (areaCode.equals(dormitorywithallinfo.getArea())) {
					dormitorywithallinfo.setLocation(areaStr);
				} else {
					areaCode = dormitorywithallinfo.getArea();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getArea() + "'");
					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						areaStr = Cap;
						dormitorywithallinfo.setArea(areaStr);
					}
				}

			}
			String locationCode = "";
			String locationStr = "";
			if (!"".equals(dormitorywithallinfo.getLocation())) {// 校区
				if (locationCode.equals(dormitorywithallinfo.getLocation())) {
					dormitorywithallinfo.setLocation(locationStr);
				} else {
					locationCode = dormitorywithallinfo.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						dormitorywithallinfo.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(dormitorywithallinfo.getDormitory())) {
					dormitorywithallinfo.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = dormitorywithallinfo.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						dormitorywithallinfo.setDormitory(dormitoryStr);
					}
				}

			}
			String unitCode = "";
			String unitStr = "";
			if (!"".equals(dormitorywithallinfo.getUnit())) {// 
				if (unitCode.equals(dormitorywithallinfo.getUnit())) {
					dormitorywithallinfo.setDormitory(unitStr);
				} else {
					unitCode = dormitorywithallinfo.getUnit();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 40 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getUnit() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						unitStr = Cap;
						dormitorywithallinfo.setUnit(unitStr);
					}
				}

			}
		}
		return dormList;
	}

	public List findDormitorys4yg(String[] args, String schoolId) {
		String dormitory = args[2];
		String unit = args[3];
		String roomNumber = args[4];
		String dormfee = args[5];
		String studentNo = args[6];
		String stuName = args[7];
		String gender = args[8];
		String location = args[1];
		String page = args[9];
		String area = args[0];
		String operator = args[10];
		List dormList = null;
		String hqlStr = "select new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,a.area,a.location,"
				+ "a.dormitory,a.unit,a.roomNumber,a.accomodation,a.classId,b.sex as gender,"
				+ "'','','','',b.graduateNo as studentNo,b.graduateName as stuName,b.speciality as majorin,b.nation,b.birthday) "
				+ "from Dormitorymodel a,YxGraduate b,TabSsManager c,Dictionary d ";
		hqlStr += " where a.dormitoryId=b.dormitoryId " + "and b.enrollYear='"
				+ DateUtil.getNow("yyyy") + "' "
				+ "and d.id.dictNo=21 and d.id.dictValue=a.dormitory "
				+ " and c.tabSsDept.id = b.distriction and c.stuNo = '"
				+ operator + "' ";

		// hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
		// : "");
		// hqlStr += (StringUtils.isNotEmpty(unit) ? " and a.unit=?" : "");
		// hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
		// : "");
		// hqlStr += (StringUtils.isNotEmpty(dormfee) ? " and a.fee = ?" : "");
		// hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.graduateNo
		// like ?"
		// : "");
		// hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.graduateName
		// like ?"
		// : "");
		// hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.sex=?" : "");
		//
		// hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?" :
		// "");
		//
		// hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");

		MyQuery myQuery = new MyQuery();

		if (dormitory != null && !dormitory.equals("")) {
			hqlStr += " and a.dormitory=?";
			myQuery.addPara(dormitory, Types.VARCHAR);
		}
		if (unit != null && !unit.equals("")) {
			hqlStr += " and a.unit=?";
			myQuery.addPara(unit, Types.VARCHAR);
		}
		if (roomNumber != null && !roomNumber.equals("")) {
			hqlStr += " and a.roomNumber=?";
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (dormfee != null && !dormfee.equals("")) {
			hqlStr += " and a.fee=?";
			myQuery.addPara(new Double(dormfee), Types.DOUBLE);
		}
		if (studentNo != null && !studentNo.equals("")) {
			hqlStr += " and b.graduateNo like ?";
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (stuName != null && !stuName.equals("")) {
			hqlStr += " and b.graduateName like ?";
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}
		if (gender != null && !gender.equals("")) {
			hqlStr += " and b.sex=?";
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (location != null && !location.equals("")) {
			hqlStr += " and a.location=?";
			myQuery.addPara(location, Types.VARCHAR);
		}
		if (area != null && !area.equals("")) {
			hqlStr += " and a.area=?";
			myQuery.addPara(area, Types.VARCHAR);
		}
		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setQueryString(hqlStr.toString());
		myQuery.setPageSize(100);
		myQuery.setOffset(true);
		myQuery.setQueryString(hqlStr.toString());

		myQuery
				.setOrderby(" order by a.area,a.location,d.dictSort,a.unit,a.roomNumber");
		dormList = dormitorymodelDAO.find(myQuery);
		System.out.println("dormList.size()=" + dormList.size());
		for (int i = 0; i < dormList.size(); i++) {
			DormitoryWithAllInfo dormitorywithallinfo = (DormitoryWithAllInfo) dormList
					.get(i);

			String genderCode = "";
			String genderStr = "";
			if (dormitorywithallinfo.getBirthday() != null
					&& !"".equals(dormitorywithallinfo.getBirthday())) {
				String birthday = dormitorywithallinfo.getBirthday();
				birthday = birthday.substring(0, 4) + "-"
						+ birthday.substring(4, 6) + "-"
						+ birthday.substring(6, 8);
				dormitorywithallinfo.setBirthday(birthday);
			} else {
				dormitorywithallinfo.setBirthday("");
			}
			if (!"".equals(dormitorywithallinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorywithallinfo.getGender())) {
					dormitorywithallinfo.setGender(genderStr);
				} else {
					genderCode = dormitorywithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getGender() + "'");
					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						dormitorywithallinfo.setGender(genderStr);
					}
				}
			}
			// --------------------------------------------------------------------------------
			String areaCode = "";
			String areaStr = "";
			if (!"".equals(dormitorywithallinfo.getArea())) {// 大校区
				if (areaCode.equals(dormitorywithallinfo.getArea())) {
					dormitorywithallinfo.setLocation(areaStr);
				} else {
					areaCode = dormitorywithallinfo.getArea();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getArea() + "'");
					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						areaStr = Cap;
						dormitorywithallinfo.setArea(areaStr);
					}
				}

			}
			String locationCode = "";
			String locationStr = "";
			if (!"".equals(dormitorywithallinfo.getLocation())) {// 校区
				if (locationCode.equals(dormitorywithallinfo.getLocation())) {
					dormitorywithallinfo.setLocation(locationStr);
				} else {
					locationCode = dormitorywithallinfo.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						dormitorywithallinfo.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(dormitorywithallinfo.getDormitory())) {
					dormitorywithallinfo.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = dormitorywithallinfo.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						dormitorywithallinfo.setDormitory(dormitoryStr);
					}
				}

			}
			String unitCode = "";
			String unitStr = "";
			if (!"".equals(dormitorywithallinfo.getUnit())) {// 
				if (unitCode.equals(dormitorywithallinfo.getUnit())) {
					dormitorywithallinfo.setDormitory(unitStr);
				} else {
					unitCode = dormitorywithallinfo.getUnit();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 40 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getUnit() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						unitStr = Cap;
						dormitorywithallinfo.setUnit(unitStr);
					}
				}

			}
		}
		return dormList;
	}

	public Integer getDormitoryCount4yg(String[] args, String schoolId) {
		String area = args[0];
		String location = args[1];
		String dormitory = args[2];
		String unit = args[3];
		String roomNumber = args[4];
		String dormfee = args[5];
		String studentNo = args[6];
		String stuName = args[7];
		String gender = args[8];
		String page = args[9];
		String operator = args[10];
		List dormList = null;
		Integer dormCount = new Integer("0");

		String hqlStr = "select distinct count(distinct b.graduateNo) "
				+ "from Dormitorymodel a,YxGraduate b,TabSsManager c ";

		hqlStr += " where a.dormitoryId=b.dormitoryId " + "and b.enrollYear='"
				+ DateUtil.getNow("yyyy") + "' "
				+ " and c.tabSsDept.id = b.distriction and c.stuNo = '"
				+ operator + "' ";

		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(unit) ? " and a.unit=?" : "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(dormfee) ? " and a.fee = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.graduateNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.graduateName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.sex=?" : "");

		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?" : "");

		hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(unit)) {
			myQuery.addPara(unit, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormfee)) {
			myQuery.addPara(new Double(dormfee), Types.DOUBLE);
		}
		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr.toString());
		dormList = dormitorymodelDAO.find(myQuery);

		if (dormList != null) {
			dormCount = (Integer) dormList.get(0);
		}
		return dormCount;
	}

	public Integer getDormitoryCount(String[] args, String schoolId) {
		String dormitory = args[0];
		String roomNumber = args[1];
		String collegeId = args[2];
		String classId = args[3];
		String managerId = args[4];
		String studentNo = args[5];
		String stuName = args[6];
		String gender = args[7];
		String majorin = args[8];
		String nation = args[9];
		String fromProvince = args[10];
		String location = args[11];
		String area = args[13];
		String district = "";
		String enterenceNo = "";
		if (args.length > 14) {
			district = args[14];
		}
		if (args.length > 15) {
			enterenceNo = args[15];
		}

		List dormList = null;
		Integer dormCount = new Integer("0");
		String hqlStr = "";
		if (schoolId != null && schoolId.equals("0001")) {
			hqlStr = "select distinct count(distinct b.studentNo) "
					+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d ";
			if (StringUtils.isNotEmpty(managerId)) {
				hqlStr += ",Classmanager e,Managermodel f,Managermanagerrole ff ";
			}
			hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
					+ "and d.yxCollege.collegeId=c.collegeId "
					+ "and d.yxCollege.yxSchool.schoolId='"
					+ schoolId
					+ "' "
					+ "and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";
		} else if (schoolId != null && schoolId.equals("0002")) {
			hqlStr = "select distinct count(distinct b.studentNo) "
					+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d,GzStuTemp g ";
			if (StringUtils.isNotEmpty(managerId)) {
				hqlStr += ",Classmanager e,Managermodel f,Managermanagerrole ff ";
			}
			hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
					+ "and b.enterenceNo=g.enterenceNo "
					+ "and d.yxCollege.collegeId=c.collegeId "
					+ "and d.yxCollege.yxSchool.schoolId='"
					+ schoolId
					+ "' "
					+ "and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";
		}

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(managerId)) {
			hqlStr += "and d.classId=e.id.classId and e.id.managerId=f.managerId "
					+ "and f.managerId=ff.id.managerId and ff.id.roleId='21' ";
			hqlStr += (StringUtils.isNotEmpty(managerId) ? " and f.managerId=?"
					: "");
			if (StringUtils.isNotEmpty(managerId)) {
				myQuery.addPara(managerId, Types.VARCHAR);
			}
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
					: "");
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
					: "");
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(collegeId)) {
			hqlStr += (StringUtils.isNotEmpty(collegeId) ? " and c.collegeId=?"
					: "");
			myQuery.addPara(collegeId, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(classId)) {
			hqlStr += (StringUtils.isNotEmpty(classId) ? " and d.classId=?"
					: "");
			myQuery.addPara(classId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(studentNo)) {
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
					: "");
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(enterenceNo)) {
			hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
					: "");
			myQuery.addPara("%" + enterenceNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
					: "");
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?"
					: "");
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
			myQuery.addPara(nation, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(district)) {
			hqlStr += (StringUtils.isNotEmpty(district) ? " and g.district=?"
					: "");
			myQuery.addPara(district, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
					: "");
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?"
					: "");
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(area)) {
			hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");
			myQuery.addPara(area, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr.toString());
		dormList = dormitorymodelDAO.find(myQuery);

		if (dormList != null) {
			dormCount = (Integer) dormList.get(0);
		}
		return dormCount;
	}

	public List findfdyDormitorys(String[] args, String classId) {
		String dormitory = args[0];
		String roomNumber = args[1];
		String studentNo = args[2];
		String stuName = args[3];
		String gender = args[4];
		String majorin = args[5];
		String nation = args[6];
		String fromProvince = args[7];
		String location = args[8];
		String page = args[9];
		String orderby = args[10];
		String sort = args[11];
		String enterenceNo = args[12];

		List dormList = null;
		String hqlStr = "select distinct new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,'',a.location,"
				+ "a.dormitory,'',a.roomNumber,a.accomodation,d.classId,b.gender,b.fromProvince,c.collegeName,d.classNo,"
				+ "'',b.studentNo,b.stuName,b.majorin,b.nation,b.enterenceNo) "
				+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d ";
		hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
				+ "and d.yxCollege.collegeId=c.collegeId "
				+ " and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";

		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and d.classId=?" : "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
		hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
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
		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setQueryString(hqlStr.toString());
		myQuery.setPageSize(100);
		myQuery.setOffset(true);
		// if("".equals(orderby)||"0".equals(sort)){
		myQuery.setOrderby(" order by a.location,a.dormitory,a.roomNumber");
		// }
		// if(!"".equals(orderby)){
		// if("location".equals(orderby)||"dormitory".equals(orderby)||"roomNumber".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by a."+orderby+ " asc");
		// }else{
		// myQuery.setOrderby(" order by a."+orderby+ " desc");
		// }
		//				
		// }
		// if("college".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by c.collegeName asc");
		// }else{
		// myQuery.setOrderby(" order by c.collegeName desc");
		// }
		// }
		// if("class".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by d.classNo asc");
		// }else{
		// myQuery.setOrderby(" order by d.classNo desc");
		// }
		// }
		// if("stuNo".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.studentNo asc");
		// }else{
		// myQuery.setOrderby(" order by b.studentNo desc");
		// }
		// }
		// if("gender".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.gender asc");
		// }else{
		// myQuery.setOrderby(" order by b.gender desc");
		// }
		// }
		// if("majorin".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.majorin asc");
		// }else{
		// myQuery.setOrderby(" order by b.majorin desc");
		// }
		// }
		// if("fromProvince".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.fromProvince asc");
		// }else{
		// myQuery.setOrderby(" order by b.fromProvince desc");
		// }
		// }
		// if("nation".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.nation asc");
		// }else{
		// myQuery.setOrderby(" order by b.nation desc");
		// }
		// }
		// }

		dormList = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < dormList.size(); i++) {
			DormitoryWithAllInfo dormitorywithallinfo = (DormitoryWithAllInfo) dormList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(dormitorywithallinfo.getClassId())) {
				if (clsssIdCode.equals(dormitorywithallinfo.getClassId())) {
					dormitorywithallinfo.setManagerName(clsmanagerStr);
				} else {
					clsssIdCode = dormitorywithallinfo.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ dormitorywithallinfo.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						dormitorywithallinfo.setManagerName(clsmanagerStr);
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorywithallinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorywithallinfo.getGender())) {
					dormitorywithallinfo.setGender(genderStr);
				} else {
					genderCode = dormitorywithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						dormitorywithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(dormitorywithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(dormitorywithallinfo
						.getFromProvince())) {
					dormitorywithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = dormitorywithallinfo.getFromProvince();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 10 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getFromProvince()
									+ "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						fromProvinceStr = Cap;
						dormitorywithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(dormitorywithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(dormitorywithallinfo.getMajorin())) {
					dormitorywithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = dormitorywithallinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						dormitorywithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(dormitorywithallinfo.getNation())) {// 民族
				if (nationCode.equals(dormitorywithallinfo.getNation())) {
					dormitorywithallinfo.setNation(nationStr);
				} else {
					nationCode = dormitorywithallinfo.getNation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 2 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getNation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationStr = Cap;
						dormitorywithallinfo.setNation(nationStr);
					}
				}

			}

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(dormitorywithallinfo.getLocation())) {// 校区
				if (locationCode.equals(dormitorywithallinfo.getLocation())) {
					dormitorywithallinfo.setLocation(locationStr);
				} else {
					locationCode = dormitorywithallinfo.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						dormitorywithallinfo.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(dormitorywithallinfo.getDormitory())) {
					dormitorywithallinfo.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = dormitorywithallinfo.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						dormitorywithallinfo.setDormitory(dormitoryStr);
					}
				}

			}

		}
		return dormList;
	}

	public List findfdyDormitorys_hlxy(String[] args, List classlist) {
		String dormitory = args[0];
		String roomNumber = args[1];
		String studentNo = args[2];
		String stuName = args[3];
		String gender = args[4];
		String majorin = args[5];
		String nation = args[6];
		String fromProvince = args[7];
		String location = args[8];
		String page = args[9];
		String orderby = args[10];
		String sort = args[11];
		String area = args[12];
		String classIds = args[13];
		String district = args[14];
		String enterenceNo = args[15];

		List dormList = null;
		String hqlStr = "select distinct new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,a.area,a.location,"
				+ "a.dormitory,'',a.roomNumber,a.distributeNum,d.classId,b.gender,b.fromProvince,c.collegeName,d.classNo,"
				+ "'',b.studentNo,b.stuName,b.majorin,g.district,b.enterenceNo) "
				+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d,GzStuTemp g ";
		hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
				+ " and b.enterenceNo=g.enterenceNo "
				+ "and d.yxCollege.collegeId=c.collegeId "
				+ " and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";

		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
		hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=? " : "");

		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and d.classId=? " : "");
		hqlStr += (StringUtils.isNotEmpty(district) ? " and g.district=? " : "");

		hqlStr += " and d.classId in(";
		if (classlist != null && classlist.size() > 0) {
			for (int i = 0; i < classlist.size(); i++) {
				HashMap hashmap = (HashMap) classlist.get(i);
				String classId = (String) hashmap.get("classId");
				hqlStr += "'" + classId + "',";
			}

		}
		hqlStr = hqlStr.substring(0, (hqlStr.length() - 1));
		hqlStr += ") ";

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
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
		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(district)) {
			myQuery.addPara(district, Types.VARCHAR);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setQueryString(hqlStr.toString());
		myQuery.setPageSize(100);
		myQuery.setOffset(true);
		// if("".equals(orderby)||"0".equals(sort)){
		myQuery
				.setOrderby(" order by a.area,a.location,a.dormitory,a.roomNumber ");
		// }
		// if(!"".equals(orderby)){
		// if("location".equals(orderby)||"dormitory".equals(orderby)||"roomNumber".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by a."+orderby+ " asc");
		// }else{
		// myQuery.setOrderby(" order by a."+orderby+ " desc");
		// }
		//				
		// }
		// if("college".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by c.collegeName asc");
		// }else{
		// myQuery.setOrderby(" order by c.collegeName desc");
		// }
		// }
		// if("class".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by d.classNo asc");
		// }else{
		// myQuery.setOrderby(" order by d.classNo desc");
		// }
		// }
		// if("stuNo".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.studentNo asc");
		// }else{
		// myQuery.setOrderby(" order by b.studentNo desc");
		// }
		// }
		// if("gender".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.gender asc");
		// }else{
		// myQuery.setOrderby(" order by b.gender desc");
		// }
		// }
		// if("majorin".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.majorin asc");
		// }else{
		// myQuery.setOrderby(" order by b.majorin desc");
		// }
		// }
		// if("fromProvince".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.fromProvince asc");
		// }else{
		// myQuery.setOrderby(" order by b.fromProvince desc");
		// }
		// }
		// if("nation".equals(orderby)){
		// if("1".equals(sort)){
		// myQuery.setOrderby(" order by b.nation asc");
		// }else{
		// myQuery.setOrderby(" order by b.nation desc");
		// }
		// }
		// }

		dormList = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < dormList.size(); i++) {
			DormitoryWithAllInfo dormitorywithallinfo = (DormitoryWithAllInfo) dormList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(dormitorywithallinfo.getClassId())) {
				if (clsssIdCode.equals(dormitorywithallinfo.getClassId())) {
					dormitorywithallinfo.setManagerName(clsmanagerStr);
				} else {
					clsssIdCode = dormitorywithallinfo.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ dormitorywithallinfo.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						dormitorywithallinfo.setManagerName(clsmanagerStr);
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorywithallinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorywithallinfo.getGender())) {
					dormitorywithallinfo.setGender(genderStr);
				} else {
					genderCode = dormitorywithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						dormitorywithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(dormitorywithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(dormitorywithallinfo
						.getFromProvince())) {
					dormitorywithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = dormitorywithallinfo.getFromProvince();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 10 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getFromProvince()
									+ "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						fromProvinceStr = Cap;
						dormitorywithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(dormitorywithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(dormitorywithallinfo.getMajorin())) {
					dormitorywithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = dormitorywithallinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						dormitorywithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(dormitorywithallinfo.getNation())) {// 上海区县
				if (nationCode.equals(dormitorywithallinfo.getNation())) {
					dormitorywithallinfo.setNation(nationStr);
				} else {
					nationCode = dormitorywithallinfo.getNation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 23 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getNation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationStr = Cap;
						dormitorywithallinfo.setNation(nationStr);
					}
				}

			}

			String areaCode = "";
			String areaStr = "";
			if (!"".equals(dormitorywithallinfo.getArea())) {// 大校区
				if (areaCode.equals(dormitorywithallinfo.getArea())) {
					dormitorywithallinfo.setArea(areaStr);
				} else {
					areaCode = dormitorywithallinfo.getArea();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getArea() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						areaStr = Cap;
						dormitorywithallinfo.setArea(areaStr);
					}
				}

			}

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(dormitorywithallinfo.getLocation())) {// 小校区
				if (locationCode.equals(dormitorywithallinfo.getLocation())) {
					dormitorywithallinfo.setLocation(locationStr);
				} else {
					locationCode = dormitorywithallinfo.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						dormitorywithallinfo.setLocation(locationStr);
					}
				}

			}

			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(dormitorywithallinfo.getDormitory())) {
					dormitorywithallinfo.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = dormitorywithallinfo.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						dormitorywithallinfo.setDormitory(dormitoryStr);
					}
				}

			}

		}
		return dormList;
	}

	public List findfdyDormitorysExport(String[] args, String classId) {
		String dormitory = args[0];
		String roomNumber = args[1];
		String studentNo = args[2];
		String stuName = args[3];
		String gender = args[4];
		String majorin = args[5];
		String nation = args[6];
		String fromProvince = args[7];
		String location = args[8];
		String enterenceNo = args[12];

		List dormList = null;
		String hqlStr = "select distinct new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,'',a.location,"
				+ "a.dormitory,'',a.roomNumber,a.accomodation,d.classId,b.gender,b.fromProvince,c.collegeName,d.classNo,"
				+ "'',b.studentNo,b.stuName,b.majorin,b.nation,b.enterenceNo) "
				+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d ";
		hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
				+ "and d.yxCollege.collegeId=c.collegeId "
				+ " and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";

		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and d.classId=?" : "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
		hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
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

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}
		myQuery.setPageStartNo(0);

		myQuery.setQueryString(hqlStr.toString());

		myQuery.setOrderby(" order by a.location,a.dormitory,a.roomNumber");
		dormList = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < dormList.size(); i++) {
			DormitoryWithAllInfo dormitorywithallinfo = (DormitoryWithAllInfo) dormList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(dormitorywithallinfo.getClassId())) {
				if (clsssIdCode.equals(dormitorywithallinfo.getClassId())) {
					dormitorywithallinfo.setManagerName(clsmanagerStr);
				} else {
					clsssIdCode = dormitorywithallinfo.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ dormitorywithallinfo.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						dormitorywithallinfo.setManagerName(clsmanagerStr);
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorywithallinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorywithallinfo.getGender())) {
					dormitorywithallinfo.setGender(genderStr);
				} else {
					genderCode = dormitorywithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						dormitorywithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(dormitorywithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(dormitorywithallinfo
						.getFromProvince())) {
					dormitorywithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = dormitorywithallinfo.getFromProvince();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 10 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getFromProvince()
									+ "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						fromProvinceStr = Cap;
						dormitorywithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(dormitorywithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(dormitorywithallinfo.getMajorin())) {
					dormitorywithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = dormitorywithallinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						dormitorywithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(dormitorywithallinfo.getNation())) {// 民族
				if (nationCode.equals(dormitorywithallinfo.getNation())) {
					dormitorywithallinfo.setNation(nationStr);
				} else {
					nationCode = dormitorywithallinfo.getNation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 2 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getNation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationStr = Cap;
						dormitorywithallinfo.setNation(nationStr);
					}
				}

			}

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(dormitorywithallinfo.getLocation())) {// 校区
				if (locationCode.equals(dormitorywithallinfo.getLocation())) {
					dormitorywithallinfo.setLocation(locationStr);
				} else {
					locationCode = dormitorywithallinfo.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						dormitorywithallinfo.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(dormitorywithallinfo.getDormitory())) {
					dormitorywithallinfo.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = dormitorywithallinfo.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						dormitorywithallinfo.setDormitory(dormitoryStr);
					}
				}

			}

		}
		return dormList;
	}

	public List findfdyDormitorysExport_hlxy(String[] args, List classlist) {
		String dormitory = args[0];
		String roomNumber = args[1];
		String studentNo = args[2];
		String stuName = args[3];
		String gender = args[4];
		String majorin = args[5];
		String nation = args[6];
		String fromProvince = args[7];
		String location = args[8];
		String area = args[12];
		String classIds = args[13];
		String district = args[14];
		String enterenceNo = args[14];

		List dormList = null;
		String hqlStr = "select distinct new org.king.dormitorymanage.web.help.DormitoryWithAllInfo(a.fee,a.area,a.location,"
				+ "a.dormitory,'',a.roomNumber,a.distributeNum,d.classId,b.gender,b.fromProvince,c.collegeName,d.classNo,"
				+ "'',b.studentNo,b.stuName,b.majorin,g.district,b.enterenceNo) "
				+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d,GzStuTemp g ";
		hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
				+ " and b.enterenceNo=g.enterenceNo "
				+ "and d.yxCollege.collegeId=c.collegeId "
				+ " and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";

		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
		hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=? " : "");

		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and d.classId=? " : "");
		hqlStr += (StringUtils.isNotEmpty(district) ? " and g.district=? " : "");

		hqlStr += " and d.classId in(";
		if (classlist != null && classlist.size() > 0) {
			for (int i = 0; i < classlist.size(); i++) {
				HashMap hashmap = (HashMap) classlist.get(i);
				String classId = (String) hashmap.get("classId");
				hqlStr += "'" + classId + "',";
			}

		}
		hqlStr = hqlStr.substring(0, (hqlStr.length() - 1));
		hqlStr += ") ";

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
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

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(district)) {
			myQuery.addPara(district, Types.VARCHAR);
		}

		myQuery.setPageStartNo(0);

		myQuery.setQueryString(hqlStr.toString());

		myQuery
				.setOrderby(" order by a.area,a.location,a.dormitory,a.roomNumber");
		dormList = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < dormList.size(); i++) {
			DormitoryWithAllInfo dormitorywithallinfo = (DormitoryWithAllInfo) dormList
					.get(i);
			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(dormitorywithallinfo.getClassId())) {
				if (clsssIdCode.equals(dormitorywithallinfo.getClassId())) {
					dormitorywithallinfo.setManagerName(clsmanagerStr);
				} else {
					clsssIdCode = dormitorywithallinfo.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ dormitorywithallinfo.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						dormitorywithallinfo.setManagerName(clsmanagerStr);
					}
				}
			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorywithallinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorywithallinfo.getGender())) {
					dormitorywithallinfo.setGender(genderStr);
				} else {
					genderCode = dormitorywithallinfo.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						dormitorywithallinfo.setGender(genderStr);
					}
				}

			}
			String fromProvinceCode = "";
			String fromProvinceStr = "";
			if (!"".equals(dormitorywithallinfo.getFromProvince())) {// 生源地
				if (fromProvinceCode.equals(dormitorywithallinfo
						.getFromProvince())) {
					dormitorywithallinfo.setFromProvince(fromProvinceStr);
				} else {
					fromProvinceCode = dormitorywithallinfo.getFromProvince();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 10 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getFromProvince()
									+ "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						fromProvinceStr = Cap;
						dormitorywithallinfo.setFromProvince(fromProvinceStr);
					}
				}

			}
			String majorinCode = "";
			String majorinStr = "";
			if (!"".equals(dormitorywithallinfo.getMajorin())) {// 专业
				if (majorinCode.equals(dormitorywithallinfo.getMajorin())) {
					dormitorywithallinfo.setMajorin(majorinStr);
				} else {
					majorinCode = dormitorywithallinfo.getMajorin();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 11 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getMajorin() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						majorinStr = Cap;
						dormitorywithallinfo.setMajorin(majorinStr);
					}
				}

			}
			String nationCode = "";
			String nationStr = "";
			if (!"".equals(dormitorywithallinfo.getNation())) {// 上海区县
				if (nationCode.equals(dormitorywithallinfo.getNation())) {
					dormitorywithallinfo.setNation(nationStr);
				} else {
					nationCode = dormitorywithallinfo.getNation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 23 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getNation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						nationStr = Cap;
						dormitorywithallinfo.setNation(nationStr);
					}
				}

			}

			String areaCode = "";
			String areaStr = "";
			if (!"".equals(dormitorywithallinfo.getArea())) {// 大校区
				if (areaCode.equals(dormitorywithallinfo.getArea())) {
					dormitorywithallinfo.setArea(areaStr);
				} else {
					areaCode = dormitorywithallinfo.getArea();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getArea() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						areaStr = Cap;
						dormitorywithallinfo.setArea(areaStr);
					}
				}

			}

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(dormitorywithallinfo.getLocation())) {// 小校区
				if (locationCode.equals(dormitorywithallinfo.getLocation())) {
					dormitorywithallinfo.setLocation(locationStr);
				} else {
					locationCode = dormitorywithallinfo.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						dormitorywithallinfo.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(dormitorywithallinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(dormitorywithallinfo.getDormitory())) {
					dormitorywithallinfo.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = dormitorywithallinfo.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
									+ "and a.id.dictValue='"
									+ dormitorywithallinfo.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						dormitorywithallinfo.setDormitory(dormitoryStr);
					}
				}

			}

		}
		return dormList;
	}

	public Integer getfdyDormitoryCount(String[] args, String classId) {
		String dormitory = args[0];
		String roomNumber = args[1];
		String studentNo = args[2];
		String stuName = args[3];
		String gender = args[4];
		String majorin = args[5];
		String nation = args[6];
		String fromProvince = args[7];
		String location = args[8];

		String enterenceNo = args[12];

		List dormList = null;
		Integer dormCount = new Integer("0");

		String hqlStr = "select distinct count(distinct b.studentNo) "
				+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d ";

		hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
				+ "and d.yxCollege.collegeId=c.collegeId "
				+ " and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";

		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and d.classId=?" : "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
		hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
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

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr.toString());
		dormList = dormitorymodelDAO.find(myQuery);

		if (dormList != null) {
			dormCount = (Integer) dormList.get(0);
		}
		return dormCount;
	}

	public Integer getfdyDormitoryCount_hlxy(String[] args, List classlist) {
		String dormitory = args[0];
		String roomNumber = args[1];
		String studentNo = args[2];
		String stuName = args[3];
		String gender = args[4];
		String majorin = args[5];
		String nation = args[6];
		String fromProvince = args[7];
		String location = args[8];
		String area = args[12];
		String classIds = args[13];
		String district = args[14];
		String enterenceNo = args[15];
		List dormList = null;
		Integer dormCount = new Integer("0");

		String hqlStr = "select distinct count(distinct b.studentNo) "
				+ "from Dormitorymodel a,Studentmodel b,Collegemodel c,Classmodel d,GzStuTemp g ";

		hqlStr += "where a.dormitoryId=b.dormId and b.yxClass.classId=d.classId "
				+ " and b.enterenceNo=g.enterenceNo "
				+ "and d.yxCollege.collegeId=c.collegeId "
				+ " and b.enrollYear='" + DateUtil.getNow("yyyy") + "' ";

		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(area) ? " and a.area=?" : "");
		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(enterenceNo) ? " and b.enterenceNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and b.gender=?" : "");
		hqlStr += (StringUtils.isNotEmpty(majorin) ? " and b.majorin=?" : "");
		hqlStr += (StringUtils.isNotEmpty(nation) ? " and b.nation=?" : "");
		hqlStr += (StringUtils.isNotEmpty(fromProvince) ? " and b.fromProvince=?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location=?" : "");

		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and d.classId=? " : "");
		hqlStr += (StringUtils.isNotEmpty(district) ? " and g.district=? " : "");

		hqlStr += "and d.classId in(";
		if (classlist != null && classlist.size() > 0) {
			for (int i = 0; i < classlist.size(); i++) {
				HashMap hashmap = (HashMap) classlist.get(i);
				String classId = (String) hashmap.get("classId");
				hqlStr += "'" + classId + "',";
			}

		}
		hqlStr = hqlStr.substring(0, (hqlStr.length() - 1));
		hqlStr += ") ";

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
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

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(majorin)) {
			myQuery.addPara(majorin, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(nation)) {
			myQuery.addPara(nation, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(fromProvince)) {
			myQuery.addPara(fromProvince, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(district)) {
			myQuery.addPara(district, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr.toString());
		dormList = dormitorymodelDAO.find(myQuery);

		if (dormList != null) {
			dormCount = (Integer) dormList.get(0);
		}
		return dormCount;
	}

	public List findDormInfo(String[] args) throws BusinessException {
		String location = args[0];
		String dormitory = args[1];
		String roomNumber = args[2];
		String gender = args[3];
		String page = args[4];
		List dorm = null;
		String hqlStr = "select new Map(a as dormitorymodel,b.dictCaption as location,"
				+ "c.dictCaption as dormitory,d.dictCaption as gender) from Dormitorymodel a,"
				+ "Dictionary b,Dictionary c,Dictionary d where a.location=b.id.dictValue "
				+ "and b.id.dictNo=6 and a.dormitory=c.id.dictValue and c.id.dictNo=7 "
				+ "and a.gender=d.id.dictValue and d.id.dictNo=1 ";
		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location= ?" : "");
		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender= ?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setOffset(true);
		myQuery.setQueryString(hqlStr);

		dorm = dormitorymodelDAO.find(myQuery);
		return dorm;

	}

	public Integer getDormInfoCount(String[] args) {
		String location = args[0];
		String dormitory = args[1];
		String roomNumber = args[2];
		String gender = args[3];
		List dormList = null;
		Integer dormCount = new Integer("0");
		String hqlStr = "select distinct count(*) from Dormitorymodel a,Dictionary b,"
				+ "Dictionary c,Dictionary d where a.location=b.id.dictValue "
				+ "and b.id.dictNo=6 and a.dormitory=c.id.dictValue and c.id.dictNo=7 "
				+ "and a.gender=d.id.dictValue and d.id.dictNo=1 ";
		hqlStr += (StringUtils.isNotEmpty(location) ? " and a.location= ?" : "");
		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and a.dormitory= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomNumber) ? " and a.roomNumber= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender= ?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomNumber)) {
			myQuery.addPara(roomNumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr);
		dormList = dormitorymodelDAO.find(myQuery);
		if (dormList != null) {
			dormCount = (Integer) dormList.get(0);
		}
		return dormCount;
	}

	public List findFreshmens(String[] args) throws BusinessException {
		List stuList = null;
		String stuNo = args[0];
		String stuName = args[1];
		String location = args[2];
		String dormitory = args[3];
		String gender = args[4];
		String roomNumber = args[5];
		String page = args[6];
		StringBuffer hqlStr = new StringBuffer();
		hqlStr
				.append("select new Map(a.studentId as stuId,a.studentNo as stuNo,c.dictCaption as location,d.dictCaption as dormitory,b.roomNumber as roomNumber,e.dictCaption as gender,"
						+ "a.stuName as stuName) from Studentmodel a,Dormitorymodel b,Dictionary c,Dictionary d,"
						+ "Dictionary e where a.dormId=b.dormitoryId and c.id.dictNo=6 and c.id.dictValue=b.location"
						+ " and d.id.dictNo=7 and d.id.dictValue=b.dormitory and e.id.dictValue=a.gender and e.id.dictNo=1 ");
		if (!"".equals(stuNo)) {
			hqlStr.append("and a.studentNo like '%").append(stuNo)
					.append("%' ");
		}
		if (!"".equals(location)) {
			hqlStr.append("and b.location='").append(location).append("' ");
		}
		if (!"".equals(dormitory)) {
			hqlStr.append("and b.dormitory='").append(dormitory).append("' ");
		}
		if (!"".equals(stuName)) {
			hqlStr.append("and a.stuName like '%").append(stuName)
					.append("%' ");
		}
		if (!"".equals(gender)) {
			hqlStr.append("and a.gender='").append(gender).append("' ");
		}
		if (!"".equals(roomNumber)) {
			hqlStr.append("and b.roomNumber='").append(roomNumber).append("' ");
		}

		MyQuery myQuery = new MyQuery();
		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setOffset(true);
		myQuery.setQueryString(hqlStr.toString());
		stuList = dormitorymodelDAO.find(myQuery);
		return stuList;
	}

	public Integer getFreshmenCount(String[] args) {
		List stuList = null;
		Integer stuCount = new Integer("0");
		String stuNo = args[0];
		String stuName = args[1];
		String location = args[2];
		String dormitory = args[3];
		String gender = args[4];
		String roomNumber = args[5];
		StringBuffer hqlStr = new StringBuffer();
		hqlStr
				.append("select count(*) "
						+ "from Studentmodel a,Dormitorymodel b,Dictionary c,Dictionary d,"
						+ "Dictionary e where a.dormId=b.dormitoryId and c.id.dictNo=6 and c.id.dictValue=b.location"
						+ " and d.id.dictNo=7 and d.id.dictValue=b.dormitory and e.id.dictValue=a.gender and e.id.dictNo=1 ");
		if (!"".equals(stuNo)) {
			hqlStr.append("and a.studentNo like '%").append(stuNo)
					.append("%' ");
		}
		if (!"".equals(location)) {
			hqlStr.append("and b.location='").append(location).append("' ");
		}
		if (!"".equals(dormitory)) {
			hqlStr.append("and b.dormitory='").append(dormitory).append("' ");
		}
		if (!"".equals(stuName)) {
			hqlStr.append("and a.stuName like '%").append(stuName)
					.append("%' ");
		}
		if (!"".equals(gender)) {
			hqlStr.append("and a.gender='").append(gender).append("' ");
		}
		if (!"".equals(roomNumber)) {
			hqlStr.append("and b.roomNumber='").append(roomNumber).append("' ");
		}

		MyQuery myQuery = new MyQuery();
		myQuery.setQueryString(hqlStr.toString());
		stuList = dormitorymodelDAO.find(myQuery);
		if (stuList != null) {
			stuCount = (Integer) stuList.get(0);
		}
		return stuCount;
	}

	public boolean updateAlert(String stuId, String dorm, String room,
			String location, String operator) {
		List ndormList = null, odormList = null;
		String ndormId, odormId;
		String nclassId, oclassId;
		ndormList = dormitorymodelDAO
				.find("select new Map(a.dormitoryId as dorId,a.classId as claId)from Dormitorymodel a where a.dormitory='"
						+ dorm
						+ "' and a.roomNumber='"
						+ room
						+ "'and a.location='" + location + "'");
		if (ndormList.size() != 0) {
			// 取出新的宿舍id和班级id
			ndormId = ((Map) ndormList.get(0)).get("dorId").toString();
			nclassId = ((Map) ndormList.get(0)).get("claId").toString();
			// 取出学生旧的宿舍id和班级id及学生学号
			odormList = studentmodelDAO
					.find("select new Map(b.studentId as stuId,b.dormId as odormId,b.yxClass as yxClass) from Studentmodel b where b.studentId='"
							+ stuId + "'");
			String studId = ((Map) (odormList.get(0))).get("stuId").toString();
			odormId = ((Map) (odormList.get(0))).get("odormId").toString();
			oclassId = ((Classmodel) ((Map) (odormList.get(0))).get("yxClass"))
					.getClassId();
			// 保存修改历史记录
			DormAlerthis dormHis = new DormAlerthis();
			dormHis.setDormitoryIdO(odormId);
			dormHis.setDormitoryIdN(ndormId);
			dormHis.setClassIdN(nclassId);
			dormHis.setClassIdO(oclassId);
			dormHis.setStudentId(studId);
			dormHis.setOperatorTime(DateUtil.getNow());
			dormHis.setOperatorId(operator);
			dormAlerthisDAO.save(dormHis);
			// 保存修改信息
			Dormitorymodel dormodel = new Dormitorymodel();
			dormodel = dormitorymodelDAO.get(odormId);
			dormodel.setAccomodation(dormodel.getAccomodation() - 1);
			dormitorymodelDAO.update(dormodel);
			dormodel = dormitorymodelDAO.get(ndormId);
			dormodel.setAccomodation(dormodel.getAccomodation() + 1);
			dormitorymodelDAO.update(dormodel);
			Studentmodel stumodel = new Studentmodel();
			stumodel = studentmodelDAO.get((Serializable) studId);
			stumodel.setDormId(ndormId);
			stumodel.setYxClass(classmodelDAO.get(nclassId));
			studentmodelDAO.update(stumodel);
			return true;
		}
		return false;
	}

	public void withdrawDis(String stuId, String operator)
			throws BusinessException {
		List odormList = null;
		String odormId;
		String oclassId;
		// 取出学生旧的宿舍id和班级id及学生学号
		odormList = studentmodelDAO
				.find("select new Map(b.studentId as stuId,b.dormId as odormId,b.yxClass as yxClass) from Studentmodel b where b.studentId='"
						+ stuId + "'");
		String studId = ((Map) (odormList.get(0))).get("stuId").toString();
		odormId = ((Map) (odormList.get(0))).get("odormId").toString();
		oclassId = ((Classmodel) ((Map) (odormList.get(0))).get("yxClass"))
				.getClassId();
		if (odormId != "") {
			// 保存修改历史记录
			DormAlerthis dormHis = new DormAlerthis();
			dormHis.setDormitoryIdO(odormId);
			dormHis.setDormitoryIdN(" ");
			dormHis.setClassIdN(oclassId);
			dormHis.setClassIdO(oclassId);
			dormHis.setStudentId(studId);
			dormHis.setOperatorId(operator);
			dormHis.setOperatorTime(DateUtil.getNow());
			dormAlerthisDAO.save(dormHis);
			// 保存修改信息
			Studentmodel stumodel = new Studentmodel();
			Dormitorymodel dormitorymodel = new Dormitorymodel();
			dormitorymodel = dormitorymodelDAO.get(odormId);
			dormitorymodel
					.setAccomodation(dormitorymodel.getAccomodation() - 1);
			stumodel = studentmodelDAO.get((Serializable) studId);
			stumodel.setDormId("");
			studentmodelDAO.update(stumodel);
			dormitorymodelDAO.update(dormitorymodel);
		}
	}

	public List searchAlertHis(String[] args, HttpServletRequest request,
			String schoolId) {

		String xhorgh = (String) request.getSession().getAttribute("userName");
		String getRole = request.getParameter("getrole");
		List his = null;
		String stuNo = args[0], roomNo = args[1], dormNo = args[2], startTime = args[3], endTime = args[4], location = args[5], page = args[6], orderby = args[7], odr = args[8];
		String area = args[9];
		String unit = "";
		if (args.length >= 11) {
			unit = args[10];
		}
		// Dormitorymodel dormitorymodel = null;

		StringBuffer hqlStr = new StringBuffer();
		MyQuery myQuery = new MyQuery();
		if (getRole != null && getRole.equals("3")) {
			// 研工
			// if (!"".equals(location) || !"".equals(location)
			// || !"".equals(location)) {
			// dormitorymodel = getDormitory(area, location,
			// dormNo,unit,roomNo);
			// }
			hqlStr
					.append("select distinct new org.king.dormitorymanage.web.help.DormitoryHisWithAllInfo("
							+ "st.graduateNo as studentNo,st.graduateName as stuName,re.dormitoryIdO,re.classIdO,'','','',"
							+ "re.dormitoryIdN,re.classIdN,'','','',re.operatorId as opId,"
							+ "re.operatorTime as changeTime,'','','','') from YxGraduate st,DormAlerthis re,"
							+ "Dormitorymodel dr,TabSsManager ma "
							+ "where re.studentId = st.id "
							+ "and ((re.dormitoryIdO=dr.dormitoryId and ma.tabSsDept.id=dr.curDormDept) "
							+ "or (re.dormitoryIdN=dr.dormitoryId and ma.tabSsDept.id=dr.curDormDept)) "
							+ "and ma.stuNo='" + xhorgh + "' ");
			// if (!"".equals(area) || !"".equals(area) || !"".equals(area)) {
			// if (dormitorymodel != null) {
			// hqlStr.append(" and (re.dormitoryIdO='").append(
			// dormitorymodel.getDormitoryId()).append(
			// "' or re.dormitoryIdN='").append(
			// dormitorymodel.getDormitoryId()).append("') ");
			// } else {
			// hqlStr.append("and 1<>1 ");
			// }
			// }
			if (!"".equals(area)) {
				hqlStr.append("and dr.area='").append(area).append("' ");
			}
			if (!"".equals(location)) {
				hqlStr.append("and dr.location='").append(location)
						.append("' ");
			}
			if (!"".equals(dormNo)) {
				hqlStr.append("and dr.dormitory='").append(dormNo).append("' ");
			}
			if (!"".equals(unit)) {
				hqlStr.append("and dr.unit like '%").append(unit).append("%' ");
			}
			if (!"".equals(roomNo)) {
				hqlStr.append("and dr.roomNumber='").append(roomNo)
						.append("' ");
			}

			if (!"".equals(stuNo)) {
				hqlStr.append("and re.studentId like '%").append(stuNo).append(
						"%' ");
			}
			if (!"".equals(startTime)) {
				startTime = startTime.replaceAll("-", "");
				startTime = startTime + "000000";
				hqlStr.append("and re.operatorTime >= '").append(startTime)
						.append("' ");
			}
			if (!"".equals(endTime)) {
				endTime = endTime.replaceAll("-", "");
				endTime = endTime + "235959";
				hqlStr.append("and re.operatorTime <= '").append(endTime)
						.append("' ");
			}

			// if (StringUtils.isNumeric(page)) {
			// myQuery.setPageStartNo(Integer.parseInt(page));
			// } else {
			// myQuery.setPageStartNo(0);
			// }

			myQuery.setPageSize(100);
			// myQuery.setOffset(true);

			if (orderby == null || orderby.length() == 0)
				myQuery.setOrderby(" order by re.operatorTime desc ");
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("studentNo"))
				myQuery.setOrderby(" order by st.graduateNo" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("stuName"))
				myQuery.setOrderby(" order by st.graduateName" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("operatetime"))
				myQuery.setOrderby(" order by re.operatorTime" + " " + odr);

		} else {
			// 护理和复旦
			// if (!"".equals(location) || !"".equals(location)
			// || !"".equals(location)) {
			// dormitorymodel = getDormitory(area, location, roomNo, dormNo);
			// }
			String hql = "select distinct new org.king.dormitorymanage.web.help.DormitoryHisWithAllInfo("
					+ "st.studentNo,st.stuName,re.dormitoryIdO,re.classIdO,'','','',"
					+ "re.dormitoryIdN,re.classIdN,'','','',re.operatorId as opId,"
					+ "re.operatorTime as changeTime,'','','','') from Studentmodel st,DormAlerthis re,"
					+ "Dormitorymodel dr,TabSsManager ma "
					+ "where re.studentId = st.studentId "
					+ "and ((re.dormitoryIdO=dr.dormitoryId "
					+ "and ma.tabSsDept.id=dr.curDormDept ) "
					+ "or (re.dormitoryIdN=dr.dormitoryId "
					+ "and ma.tabSsDept.id=dr.curDormDept )) ";

			if (schoolId != null && !"".equals(schoolId)
					&& schoolId.equals("0002")) {// 护理学院
				// -------------------------------------------------
				hql += "and st.majorin='623' ";
			} else if (schoolId != null && !"".equals(schoolId)
					&& schoolId.equals("0001")) {
				// -------------------------------------------------复旦学院
				hql += "and st.majorin<>'623' ";
			}
			hql += "and ma.stuNo='" + xhorgh + "' ";

			hqlStr.append(hql);

			// if (!"".equals(area) || !"".equals(area) || !"".equals(area)) {
			// if (dormitorymodel != null) {
			// hqlStr.append(" and (re.dormitoryIdO='").append(
			// dormitorymodel.getDormitoryId()).append(
			// "' or re.dormitoryIdN='").append(
			// dormitorymodel.getDormitoryId()).append("') ");
			// } else {
			// hqlStr.append("and 1<>1 ");
			// }
			//
			// }
			if (area != null && !"".equals(area)) {
				hqlStr.append("and dr.area='").append(area).append("' ");
			}
			if (location != null && !"".equals(location)) {
				hqlStr.append("and dr.location='").append(location)
						.append("' ");
			}
			if (dormNo != null && !"".equals(dormNo)) {
				hqlStr.append("and dr.dormitory='").append(dormNo).append("' ");
			}
			if (roomNo != null && !"".equals(roomNo)) {
				hqlStr.append("and dr.roomNumber='").append(roomNo)
						.append("' ");
			}

			if (stuNo != null && !"".equals(stuNo)) {
				hqlStr.append("and re.studentId='").append(stuNo).append("' ");
			}

			if (!"".equals(startTime)) {
				startTime = startTime.replaceAll("-", "");
				startTime = startTime + "000000";
				hqlStr.append("and re.operatorTime >= '").append(startTime)
						.append("' ");
			}
			if (!"".equals(endTime)) {
				endTime = endTime.replaceAll("-", "");
				endTime = endTime + "235959";
				hqlStr.append("and re.operatorTime <= '").append(endTime)
						.append("' ");

			}

			// if (StringUtils.isNumeric(page)) {
			// myQuery.setPageStartNo(Integer.parseInt(page));
			// } else {
			// myQuery.setPageStartNo(0);
			// }

			myQuery.setPageSize(100);
			// myQuery.setOffset(true);

			if (orderby == null || orderby.length() == 0)
				myQuery.setOrderby(" order by re.operatorTime desc ");
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("studentNo"))
				myQuery.setOrderby(" order by st.studentNo" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("stuName"))
				myQuery.setOrderby(" order by st.stuName" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("operatetime"))
				myQuery.setOrderby(" order by re.operatorTime" + " " + odr);
		}
		myQuery.setQueryString(hqlStr.toString());

		his = dormitorymodelDAO.find(myQuery);

		for (int i = 0; i < his.size(); i++) {
			DormitoryHisWithAllInfo dormitoryhiswithallinfo = (DormitoryHisWithAllInfo) his
					.get(i);
			String changeTime = dormitoryhiswithallinfo.getChangeTime();
			changeTime = changeTime.substring(0, changeTime.length() - 2);
			changeTime = changeTime.substring(0, 4) + "-"
					+ changeTime.substring(4, 6) + "-"
					+ changeTime.substring(6, 8) + " "
					+ changeTime.substring(8, 10) + ":"
					+ changeTime.substring(10, 12);
			dormitoryhiswithallinfo.setChangeTime(changeTime);
			List list_ass = managermodelDAO
					.find("select a from Person a " + " where a.id='"
							+ dormitoryhiswithallinfo.getOpId() + "'");
			if (list_ass.size() > 0) {
				Person person = (Person) list_ass.get(0);
				dormitoryhiswithallinfo.setOpId(person.getPersonName());
			} else {
				dormitoryhiswithallinfo.setOpId("");
			}
			if (((dormitoryhiswithallinfo.getOdormitoryId() != null))
					&& (!"".equals(dormitoryhiswithallinfo.getOdormitoryId()))) {
				List dormlist = null;
				dormlist = dormitorymodelDAO
						.find("from Dormitorymodel a where a.dormitoryId='"
								+ dormitoryhiswithallinfo.getOdormitoryId()
								+ "'");
				if (dormlist.size() > 0) {
					Dormitorymodel dorm = (Dormitorymodel) dormlist.get(0);
					dormitoryhiswithallinfo.setOlocation(dorm.getLocation());
					dormitoryhiswithallinfo.setOdorm(dorm.getDormitory());
					dormitoryhiswithallinfo.setOroom(dorm.getRoomNumber());
					dormitoryhiswithallinfo.setOunit(dorm.getUnit());
					dormitoryhiswithallinfo.setOarea(dorm.getArea());// 大校区

					if (!"".equals(dormitoryhiswithallinfo.getOarea())) {// 大校区
						// 复旦学院不需要大校区
						if (schoolId != null
								&& (schoolId.equals("0002") || schoolId
										.equals("0003"))) {// 护理学院 研工
							List capD_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17"
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOarea() + "'");
							// List cap_list = studentmodelDAO
							// .find("select a.dictCaption from Dictionary a
							// where a.id.dictNo= 20 "
							// + "and a.id.dictValue='"
							// + dormitoryhiswithallinfo
							// .getOlocation() + "'");

							if (capD_list.size() > 0) {
								String Cap = capD_list.get(0).toString();
								dormitoryhiswithallinfo.setOarea(Cap);
							}
							// if (cap_list.size() > 0) {
							// String Cap = cap_list.get(0).toString();
							// dormitoryhiswithallinfo.setOlocation(Cap);
							// }
						}
					}
					if (!"".equals(dormitoryhiswithallinfo.getOlocation())) {// 校区
						if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOlocation() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOlocation(Cap);
							}
						} else if (schoolId != null
								&& (schoolId.equals("0002") || schoolId
										.equals("0003"))) {// 护理学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOlocation() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOlocation(Cap);
							}
						}
					}

					if (!"".equals(dormitoryhiswithallinfo.getOdorm())) {// 楼号
						if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOdorm() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOdorm(Cap);
							}
						} else if (schoolId != null
								&& (schoolId.equals("0002") || schoolId
										.equals("0003"))) {// 护理学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOdorm() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOdorm(Cap);
							}
						}

					}
					if (!"".equals(dormitoryhiswithallinfo.getOunit())) {// 单元号
						if (schoolId != null && schoolId.equals("0003")) {// 研工
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 40 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOunit() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOunit(Cap);
							}
						}
					}
				}

			}

			if ((dormitoryhiswithallinfo.getNdormitoryId() != null)
					&& (!"".equals(dormitoryhiswithallinfo.getNdormitoryId()))) {
				List dormlist = null;
				dormlist = dormitorymodelDAO
						.find("from Dormitorymodel a where a.dormitoryId='"
								+ dormitoryhiswithallinfo.getNdormitoryId()
								+ "'");
				if (dormlist.size() > 0) {
					Dormitorymodel dorm = (Dormitorymodel) dormlist.get(0);
					dormitoryhiswithallinfo.setNlocation(dorm.getLocation());
					dormitoryhiswithallinfo.setNdorm(dorm.getDormitory());
					dormitoryhiswithallinfo.setNunit(dorm.getUnit());
					dormitoryhiswithallinfo.setNroom(dorm.getRoomNumber());
					dormitoryhiswithallinfo.setNarea(dorm.getArea());// 大校区

					if (!"".equals(dormitoryhiswithallinfo.getNarea())) {// 大校区
						if (schoolId != null
								&& (schoolId.equals("0002") || schoolId
										.equals("0003"))) {// 护理学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNarea() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNarea(Cap);
							}
						}
					}
					if (!"".equals(dormitoryhiswithallinfo.getNlocation())) {// 校区
						if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNlocation() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNlocation(Cap);
							}
						} else if (schoolId != null
								&& (schoolId.equals("0002") || schoolId
										.equals("0003"))) {// 护理学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNlocation() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNlocation(Cap);
							}
						}
					}

					if (!"".equals(dormitoryhiswithallinfo.getNdorm())) {// 楼号
						if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNdorm() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNdorm(Cap);
							}

						} else if (schoolId != null
								&& (schoolId.equals("0002") || schoolId
										.equals("0003"))) {// 护理学院
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNdorm() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNdorm(Cap);
							}
						}
					}
					if (!"".equals(dormitoryhiswithallinfo.getNunit())) {// 新单元号
						if (schoolId != null && schoolId.equals("0003")) {// 研工
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 40 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNunit() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNunit(Cap);
							}

						}
					}
				}

			}
			if (getRole == null || !getRole.equals("3")) { // 护理和复旦学院有，研工没有
				if ((dormitoryhiswithallinfo.getOclassNo() != null)
						&& (!"".equals(dormitoryhiswithallinfo.getOclassNo()))) {
					Classmodel classmodel = classmodelDAO
							.get(dormitoryhiswithallinfo.getOclassNo());
					if (classmodel != null) {
						dormitoryhiswithallinfo.setOclassNo(classmodel
								.getClassNo());
					}
				}
				if ((dormitoryhiswithallinfo.getNclassNo() != null)
						&& (!"".equals(dormitoryhiswithallinfo.getNclassNo()))) {
					Classmodel classmodel = classmodelDAO
							.get(dormitoryhiswithallinfo.getNclassNo());
					if (classmodel != null) {
						dormitoryhiswithallinfo.setNclassNo(classmodel
								.getClassNo());
					}
				}
			} // ///////////////
		}

		// 其它字段排序

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("stuName")) {
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getStuName();
					String collegeName2 = (String) m2.getStuName();

					java.text.RuleBasedCollator collator = (RuleBasedCollator) java.text.Collator
							.getInstance(java.util.Locale.CHINA);
					java.text.CollationKey c1 = collator
							.getCollationKey(collegeName1);
					java.text.CollationKey c2 = collator
							.getCollationKey(collegeName2);
					return c1.compareTo(c2);

				}
			};
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getStuName();
					String collegeName2 = (String) m2.getStuName();

					java.text.RuleBasedCollator collator = (RuleBasedCollator) java.text.Collator
							.getInstance(java.util.Locale.CHINA);
					java.text.CollationKey c1 = collator
							.getCollationKey(collegeName1);
					java.text.CollationKey c2 = collator
							.getCollationKey(collegeName2);
					return c2.compareTo(c1);

				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}

		if (orderby != null && orderby.length() > 0 && orderby.equals("areaO")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOarea();
					String collegeName2 = (String) m2.getOarea();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOarea();
					String collegeName2 = (String) m2.getOarea();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("locationO")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOlocation();
					String collegeName2 = (String) m2.getOlocation();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOlocation();
					String collegeName2 = (String) m2.getOlocation();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("dormitoryO")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOdorm();
					String collegeName2 = (String) m2.getOdorm();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOdorm();
					String collegeName2 = (String) m2.getOdorm();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}
		if (orderby != null && orderby.length() > 0 && orderby.equals("unitO")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOlocation();
					String collegeName2 = (String) m2.getOlocation();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOlocation();
					String collegeName2 = (String) m2.getOlocation();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("roomNumberO")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOroom();
					String collegeName2 = (String) m2.getOroom();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOroom();
					String collegeName2 = (String) m2.getOroom();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}
		if (getRole == null || !getRole.equals("3")) { // 护理和复旦学院有研工部没有
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("classO")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
						DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getOclassNo() != null)
							collegeName1 = (String) m1.getOclassNo();
						if (m2.getOclassNo() != null)
							collegeName2 = (String) m2.getOclassNo();

						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
						DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getOclassNo() != null)
							collegeName1 = (String) m1.getOclassNo();
						if (m2.getOclassNo() != null)
							collegeName2 = (String) m2.getOclassNo();

						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(his, comp1);
				else
					Collections.sort(his, comp2);

			}
		} // ////////////////////////
		if (orderby != null && orderby.length() > 0 && orderby.equals("areaN")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNarea();
					String collegeName2 = (String) m2.getNarea();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNarea();
					String collegeName2 = (String) m2.getNarea();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("locationN")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNlocation();
					String collegeName2 = (String) m2.getNlocation();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNlocation();
					String collegeName2 = (String) m2.getNlocation();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}

		if (orderby != null && orderby.length() > 0
				&& orderby.equals("dormitoryN")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNdorm();
					String collegeName2 = (String) m2.getNdorm();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNdorm();
					String collegeName2 = (String) m2.getNdorm();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}
		if (orderby != null && orderby.length() > 0 && orderby.equals("unitN")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNdorm();
					String collegeName2 = (String) m2.getNdorm();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNdorm();
					String collegeName2 = (String) m2.getNdorm();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("roomNumberN")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNroom();
					String collegeName2 = (String) m2.getNroom();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getNroom();
					String collegeName2 = (String) m2.getNroom();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}

		if (getRole == null || !getRole.equals("3")) { // 护理和复旦学院有 研工部没有
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("classN")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
						DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getNclassNo() != null)
							collegeName1 = (String) m1.getNclassNo();
						if (m2.getNclassNo() != null)
							collegeName2 = (String) m2.getNclassNo();

						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
						DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getNclassNo() != null)
							collegeName1 = (String) m1.getNclassNo();
						if (m2.getNclassNo() != null)
							collegeName2 = (String) m2.getNclassNo();

						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(his, comp1);
				else
					Collections.sort(his, comp2);

			}
		} // //////////////////////////////
		if (orderby != null && orderby.length() > 0
				&& orderby.equals("operator")) {
			Comparator comp1 = new Comparator() { // 升序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOpId();
					String collegeName2 = (String) m2.getOpId();

					return collegeName1.compareTo(collegeName2);
				}
			};
			Comparator comp2 = new Comparator() { // 降序比较器
				public int compare(Object o1, Object o2) {
					DormitoryHisWithAllInfo m1 = (DormitoryHisWithAllInfo) o1;
					DormitoryHisWithAllInfo m2 = (DormitoryHisWithAllInfo) o2;
					// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
					String collegeName1 = (String) m1.getOpId();
					String collegeName2 = (String) m2.getOpId();

					return collegeName2.compareTo(collegeName1);
				}
			};
			if (odr.equals("asc"))
				Collections.sort(his, comp1);
			else
				Collections.sort(his, comp2);

		}

		return his;
	}

	public List searchAlertHisExport(String[] args, HttpServletRequest request,
			String schoolId) {
		String getRole = request.getParameter("getrole");
		String xhorgh = (String) request.getSession().getAttribute("userName");
		List his = null;
		String stuNo = args[0], roomNo = args[1], dormNo = args[2], startTime = args[3], endTime = args[4], location = args[5];
		String area = args[9];
		String unit = "";
		if (args.length >= 11) {
			unit = args[10];
		}
		// Dormitorymodel dormitorymodel = null;
		// if (!"".equals(location) || !"".equals(location)
		// || !"".equals(location)) {
		// dormitorymodel = getDormitory(area, location, roomNo, dormNo);
		// }

		StringBuffer hqlStr = new StringBuffer();

		if (getRole == null || getRole.equals("2")) {
			String hql = "select distinct new org.king.dormitorymanage.web.help.DormitoryHisWithAllInfo("
					+ "st.studentNo,st.stuName,re.dormitoryIdO,re.classIdO,'','','',"
					+ "re.dormitoryIdN,re.classIdN,'','','',re.operatorId as opId,"
					+ "re.operatorTime as changeTime,'','','','') from Studentmodel st,DormAlerthis re,"
					+ "Dormitorymodel dr,TabSsManager ma "
					+ "where re.studentId = st.studentId "
					+ "and ((re.dormitoryIdO=dr.dormitoryId "
					+ "and ma.tabSsDept.id=dr.curDormDept ) "
					+ "or (re.dormitoryIdN=dr.dormitoryId "
					+ "and ma.tabSsDept.id=dr.curDormDept )) ";

			if (schoolId != null && !"".equals(schoolId)
					&& schoolId.equals("0002")) {// 护理学院
				// -------------------------------------------------
				hql += "and st.majorin='623' ";
			} else if (schoolId != null && !"".equals(schoolId)
					&& schoolId.equals("0001")) {
				// -------------------------------------------------复旦学院
				hql += "and st.majorin<>'623' ";
			}
			hql += "and ma.stuNo='" + xhorgh + "' ";

			hqlStr.append(hql);
			// if (!"".equals(area) || !"".equals(area) || !"".equals(area)) {
			// if (dormitorymodel != null) {
			// hqlStr.append(" and (re.dormitoryIdO='").append(
			// dormitorymodel.getDormitoryId()).append(
			// "' or re.dormitoryIdN='").append(
			// dormitorymodel.getDormitoryId()).append("') ");
			// } else {
			// hqlStr.append("and 1<>1 ");
			// }
			//
			// }
			if (area != null && !"".equals(area)) {
				hqlStr.append("and dr.area='").append(area).append("' ");
			}
			if (location != null && !"".equals(location)) {
				hqlStr.append("and dr.location='").append(location)
						.append("' ");
			}
			if (dormNo != null && !"".equals(dormNo)) {
				hqlStr.append("and dr.dormitory='").append(dormNo).append("' ");
			}
			if (roomNo != null && !"".equals(roomNo)) {
				hqlStr.append("and dr.roomNumber='").append(roomNo)
						.append("' ");
			}

			if (stuNo != null && !"".equals(stuNo)) {
				hqlStr.append("and re.studentId='").append(stuNo).append("' ");
			}
			if (!"".equals(startTime)) {
				startTime = startTime.replaceAll("-", "");
				startTime = startTime + "000000";
				hqlStr.append("and re.operatorTime >= '").append(startTime)
						.append("' ");
			}
			if (!"".equals(endTime)) {
				endTime = endTime.replaceAll("-", "");
				endTime = endTime + "235959";
				hqlStr.append("and re.operatorTime <= '").append(endTime)
						.append("' ");

			}
		} else {
			hqlStr
					.append("select distinct new org.king.dormitorymanage.web.help.DormitoryHisWithAllInfo("
							+ "st.graduateNo as studentNo,st.graduateName as stuName,re.dormitoryIdO,re.classIdO,'','','',"
							+ "re.dormitoryIdN,re.classIdN,'','','',re.operatorId as opId,"
							+ "re.operatorTime as changeTime,'','','','') from YxGraduate st,DormAlerthis re,"
							+ "Dormitorymodel dr,TabSsManager ma "
							+ "where re.studentId = st.id "
							+ "and ((re.dormitoryIdO=dr.dormitoryId and ma.tabSsDept.id=dr.curDormDept) "
							+ "or (re.dormitoryIdN=dr.dormitoryId and ma.tabSsDept.id=dr.curDormDept)) "
							+ "and ma.stuNo='" + xhorgh + "' ");

			// if (!"".equals(area) || !"".equals(area) || !"".equals(area)) {
			// if (dormitorymodel != null) {
			// hqlStr.append(" and (re.dormitoryIdO='").append(
			// dormitorymodel.getDormitoryId()).append(
			// "' or re.dormitoryIdN='").append(
			// dormitorymodel.getDormitoryId()).append("') ");
			// } else {
			// hqlStr.append("and 1<>1 ");
			// }
			//
			// }
			if (!"".equals(area)) {
				hqlStr.append("and dr.area='").append(area).append("' ");
			}
			if (!"".equals(location)) {
				hqlStr.append("and dr.location='").append(location)
						.append("' ");
			}
			if (!"".equals(dormNo)) {
				hqlStr.append("and dr.dormitory='").append(dormNo).append("' ");
			}
			if (!"".equals(unit)) {
				hqlStr.append("and dr.unit='").append(unit).append("' ");
			}
			if (!"".equals(roomNo)) {
				hqlStr.append("and dr.roomNumber='").append(roomNo)
						.append("' ");
			}
			if (!"".equals(stuNo)) {
				hqlStr.append("and re.studentId='").append(stuNo).append("' ");
			}
			if (!"".equals(startTime)) {
				startTime = startTime.replaceAll("-", "");
				startTime = startTime + "000000";
				hqlStr.append("and re.operatorTime >= '").append(startTime)
						.append("' ");
			}
			if (!"".equals(endTime)) {
				endTime = endTime.replaceAll("-", "");
				endTime = endTime + "235959";
				hqlStr.append("and re.operatorTime <= '").append(endTime)
						.append("' ");

			}
		}
		MyQuery myQuery = new MyQuery();
		myQuery.setPageStartNo(0);
		myQuery.setOrderby(" order by re.operatorTime desc ");
		myQuery.setQueryString(hqlStr.toString());
		his = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < his.size(); i++) {
			DormitoryHisWithAllInfo dormitoryhiswithallinfo = (DormitoryHisWithAllInfo) his
					.get(i);
			List list_ass = managermodelDAO
					.find("select a from Person a " + " where a.id='"
							+ dormitoryhiswithallinfo.getOpId() + "'");
			if (list_ass.size() > 0) {
				Person person = (Person) list_ass.get(0);
				dormitoryhiswithallinfo.setOpId(person.getPersonName());
			} else {
				dormitoryhiswithallinfo.setOpId("");
			}
			if (((dormitoryhiswithallinfo.getOdormitoryId() != null))
					&& (!"".equals(dormitoryhiswithallinfo.getOdormitoryId()))) {
				List dormlist = null;
				dormlist = dormitorymodelDAO
						.find("from Dormitorymodel a where a.dormitoryId='"
								+ dormitoryhiswithallinfo.getOdormitoryId()
								+ "'");
				if (dormlist.size() > 0) {
					Dormitorymodel dorm = (Dormitorymodel) dormlist.get(0);
					dormitoryhiswithallinfo.setOlocation(dorm.getLocation());
					dormitoryhiswithallinfo.setOdorm(dorm.getDormitory());
					dormitoryhiswithallinfo.setOroom(dorm.getRoomNumber());
					dormitoryhiswithallinfo.setOunit(dorm.getUnit());
					dormitoryhiswithallinfo.setOarea(dorm.getArea());

					if (schoolId != null
							&& (schoolId.equals("0002") || schoolId
									.equals("0003"))) {// 护理学院
						if (!"".equals(dormitoryhiswithallinfo.getOarea())) {// 大校区
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOarea() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOarea(Cap);
							}
						}
					}

					if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
						if (!"".equals(dormitoryhiswithallinfo.getOlocation())) {// 校区
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOlocation() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOlocation(Cap);
							}
						}
					} else if (schoolId != null
							&& (schoolId.equals("0002") || schoolId
									.equals("0003"))) {// 护理学院
						if (!"".equals(dormitoryhiswithallinfo.getOlocation())) {// 校区
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOlocation() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOlocation(Cap);
							}
						}
					}
					if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
						if (!"".equals(dormitoryhiswithallinfo.getOdorm())) {// 楼号
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOdorm() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOdorm(Cap);
							}
						}
					} else if (schoolId != null
							&& (schoolId.equals("0002") || schoolId
									.equals("0003"))) {// 护理学院
						if (!"".equals(dormitoryhiswithallinfo.getOdorm())) {// 楼号
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOdorm() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOdorm(Cap);
							}
						}
					}
					if (schoolId != null && schoolId.equals("0003")) {// 研工
						if (!"".equals(dormitoryhiswithallinfo.getOunit())) {// 单元号
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 40 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getOunit() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setOunit(Cap);
							}
						}
					}
				}

			}

			if ((dormitoryhiswithallinfo.getNdormitoryId() != null)
					&& (!"".equals(dormitoryhiswithallinfo.getNdormitoryId()))) {
				List dormlist = null;
				dormlist = dormitorymodelDAO
						.find("from Dormitorymodel a where a.dormitoryId='"
								+ dormitoryhiswithallinfo.getNdormitoryId()
								+ "'");
				if (dormlist.size() > 0) {
					Dormitorymodel dorm = (Dormitorymodel) dormlist.get(0);
					dormitoryhiswithallinfo.setNlocation(dorm.getLocation());
					dormitoryhiswithallinfo.setNdorm(dorm.getDormitory());
					dormitoryhiswithallinfo.setNroom(dorm.getRoomNumber());
					dormitoryhiswithallinfo.setNunit(dorm.getUnit());
					dormitoryhiswithallinfo.setNarea(dorm.getArea());

					if (schoolId != null
							&& (schoolId.equals("0002") || schoolId
									.equals("0003"))) {// 护理学院
						if (!"".equals(dormitoryhiswithallinfo.getNarea())) {// 校区
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNarea() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNarea(Cap);
							}
						}
					}

					if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
						if (!"".equals(dormitoryhiswithallinfo.getNlocation())) {// 校区
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNlocation() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNlocation(Cap);
							}
						}
					} else if (schoolId != null
							&& (schoolId.equals("0002") || schoolId
									.equals("0003"))) {// 护理学院
						if (!"".equals(dormitoryhiswithallinfo.getNlocation())) {// 校区
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNlocation() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNlocation(Cap);
							}
						}
					}

					if (schoolId != null && schoolId.equals("0001")) {// 复旦学院
						if (!"".equals(dormitoryhiswithallinfo.getNdorm())) {// 楼号
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNdorm() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNdorm(Cap);
							}
						}
					} else if (schoolId != null
							&& (schoolId.equals("0002") || schoolId
									.equals("0003"))) {// 护理学院
						if (!"".equals(dormitoryhiswithallinfo.getNdorm())) {// 楼号
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNdorm() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNdorm(Cap);
							}
						}
					}
					if (schoolId != null && schoolId.equals("0003")) {// 研工
						if (!"".equals(dormitoryhiswithallinfo.getNunit())) {// 单元号
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 40 "
											+ "and a.id.dictValue='"
											+ dormitoryhiswithallinfo
													.getNunit() + "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								dormitoryhiswithallinfo.setNunit(Cap);
							}
						}
					}
				}

			}
			if (getRole == null || !getRole.equals("3")) {
				if ((dormitoryhiswithallinfo.getOclassNo() != null)
						&& (!"".equals(dormitoryhiswithallinfo.getOclassNo()))) {
					Classmodel classmodel = classmodelDAO
							.get(dormitoryhiswithallinfo.getOclassNo());
					if (classmodel != null) {
						dormitoryhiswithallinfo.setOclassNo(classmodel
								.getClassNo());
					}
				}
				if ((dormitoryhiswithallinfo.getNclassNo() != null)
						&& (!"".equals(dormitoryhiswithallinfo.getNclassNo()))) {
					Classmodel classmodel = classmodelDAO
							.get(dormitoryhiswithallinfo.getNclassNo());
					if (classmodel != null) {
						dormitoryhiswithallinfo.setNclassNo(classmodel
								.getClassNo());
					}
				}
			}
		}
		return his;
	}

	public Integer getHisCount(String[] args) {
		Integer hisCount = new Integer("0");
		List his = null;
		String stuNo = args[0], roomNo = args[1], dormNo = args[2], startTime = args[3], endTime = args[4], location = args[5];
		String area = args[9];
		Dormitorymodel dormitorymodel = null;
		if (!"".equals(location) || !"".equals(location)
				|| !"".equals(location)) {
			dormitorymodel = getDormitory(area, location, roomNo, dormNo);
		}
		StringBuffer hqlStr = new StringBuffer();
		hqlStr
				.append("select distinct count(*) from Studentmodel st,DormAlerthis re "
						+ "where re.studentId = st.studentId ");
		if (!"".equals(area) || !"".equals(area) || !"".equals(area)) {
			if (dormitorymodel != null) {
				hqlStr.append(" and (re.dormitoryIdO='").append(
						dormitorymodel.getDormitoryId()).append(
						"' or re.dormitoryIdN='").append(
						dormitorymodel.getDormitoryId()).append("') ");
			} else {
				hqlStr.append("and 1<>1 ");
			}

		}
		if (!"".equals(stuNo)) {
			hqlStr.append("and re.studentId='").append(stuNo).append("' ");
		}

		if (!"".equals(startTime)) {
			startTime = startTime.replaceAll("-", "");
			hqlStr.append("and re.operatorTime > '").append(startTime).append(
					"' ");
		}
		if (!"".equals(endTime)) {
			endTime = endTime.replaceAll("-", "");
			hqlStr.append("and re.operatorTime < '").append(endTime).append(
					"' ");

		}
		MyQuery myQuery = new MyQuery();
		myQuery.setQueryString(hqlStr.toString());
		his = dormitorymodelDAO.find(myQuery);
		if (his != null) {
			hisCount = (Integer) his.get(0);
		}
		return hisCount;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.dormitorymanage.service.DormitoryService#getBindedDorm()
	 */
	public List getBindedDorm(HttpServletRequest request) {

		String xhorgh = (String) request.getSession().getAttribute("userName");

		// String hql = "select new
		// org.king.classmanage.web.help.DormitoryBindInfo("
		// +
		// "a.dormitoryId,a.location,'',a.dormitory,'',a.roomNumber,a.gender,a.accomodation,a.classId)
		// "
		// + "from Dormitorymodel a " +
		// "where a.classId<>'' and a.classId is not null ";
		String hql = "select new org.king.classmanage.web.help.DormitoryBindInfo("
				+ "a.dormitoryId,a.location,'',a.dormitory,'',a.roomNumber,a.gender,a.accomodation,a.classId,a.direction) "
				+ "from Dormitorymodel a,TabSsManager b "
				+ "where a.curDormDept=b.tabSsDept.id and b.stuNo='"
				+ xhorgh
				+ "' "
				+ "and a.classId<>'' and a.classId is not null and a.distributeNum>0 order by a.location,a.dormitory,a.roomNumber ";
		List entitys = dormitorymodelDAO.find(hql);

		HashMap Hash_location = new HashMap();
		List Temp_location = dormitorymodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 6 ");
		for (int i = 0; i < Temp_location.size(); i++) {
			HashMap temp = (HashMap) Temp_location.get(i);
			Hash_location.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_dormitory = new HashMap();
		List Temp_dormitory = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 7 ");
		for (int i = 0; i < Temp_dormitory.size(); i++) {
			HashMap temp = (HashMap) Temp_dormitory.get(i);
			Hash_dormitory.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_direction = new HashMap();
		List Temp_direction = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 24 ");
		for (int i = 0; i < Temp_direction.size(); i++) {
			HashMap temp = (HashMap) Temp_direction.get(i);
			Hash_direction.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		for (int i = 0; i < entitys.size(); i++) {
			DormitoryBindInfo dormitorybindinfo = (DormitoryBindInfo) entitys
					.get(i);
			String locationCode = "";
			String locationStr = "";
			if (!"".equals(dormitorybindinfo.getLocation())) {// 校区
				if (locationCode.equals(dormitorybindinfo.getLocation())) {
					dormitorybindinfo.setLocationStr(locationStr);
				} else {
					locationCode = dormitorybindinfo.getLocation();
					if (Hash_location.get(locationCode) != null) {
						locationStr = Hash_location.get(locationCode)
								.toString();
						dormitorybindinfo.setLocationStr(locationStr);
					} else {
						dormitorybindinfo.setLocationStr("");
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(dormitorybindinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(dormitorybindinfo.getDormitory())) {
					dormitorybindinfo.setDormitoryStr(dormitoryStr);
				} else {
					dormitoryCode = dormitorybindinfo.getDormitory();
					if (Hash_dormitory.get(dormitoryCode) != null) {
						dormitoryStr = Hash_dormitory.get(dormitoryCode)
								.toString();
						dormitorybindinfo.setDormitoryStr(dormitoryStr);
					} else {
						dormitorybindinfo.setDormitoryStr("");
					}
				}

			}

			String directionCode = "";
			String directionStr = "";
			if (!"".equals(dormitorybindinfo.getDirection())) {// 朝向
				if (directionCode.equals(dormitorybindinfo.getDirection())) {
					dormitorybindinfo.setDirection(directionStr);
				} else {
					directionCode = dormitorybindinfo.getDirection();
					if (Hash_direction.get(directionCode) != null) {
						directionStr = Hash_direction.get(directionCode)
								.toString();
						dormitorybindinfo.setDirection(directionStr);
					} else {
						dormitorybindinfo.setDirection("");
					}
				}

			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorybindinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorybindinfo.getGender())) {
					dormitorybindinfo.setGender(genderStr);
				} else {
					genderCode = dormitorybindinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						dormitorybindinfo.setGender(genderStr);
					} else {
						dormitorybindinfo.setGender("");
					}
				}

			}

		}
		return entitys;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.dormitorymanage.service.DormitoryService#getDormbyLocation(java.lang.String)
	 */
	public List getDormbyLocation(String location) {
		return dormitorymodelDAO
				.find("select distinct dormitory from Dormitorymodel a where a.location='"
						+ location + "'");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.dormitorymanage.service.DormitoryService#getDormmitoryList()
	 */
	public List getDormmitoryList() {
		return dormitorymodelDAO
				.find("select distinct dormitory,location from Dormitorymodel");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.dormitorymanage.service.DormitoryService#getDormNoClass()
	 */
	public List getDormNoClass(HttpServletRequest request) {

		String xhorgh = (String) request.getSession().getAttribute("userName");
		// String hql = "select new
		// org.king.classmanage.web.help.DormitoryBindInfo("
		// + "a.dormitoryId,a.location,''," +
		// "a.dormitory,'',a.roomNumber," +
		// "a.gender,a.accomodation,a.classId) "
		// + "from Dormitorymodel a " +
		// "where 1=1 " +
		// "and (a.classId='' or a.classId is null) ";
		// List entitys = dormitorymodelDAO.find(hql);

		String hql = "select new org.king.classmanage.web.help.DormitoryBindInfo("
				+ "a.dormitoryId,a.location,'',"
				+ "a.dormitory,'',a.roomNumber,"
				+ "a.gender,a.accomodation,a.classId,a.direction) "
				+ "from Dormitorymodel a,TabSsManager b  "
				+ "where a.curDormDept=b.tabSsDept.id and b.stuNo='"
				+ xhorgh
				+ "' "
				+ "and (a.classId='' or a.classId is null) and a.distributeNum>0 order by a.location,a.dormitory,a.roomNumber ";

		// String hql = "select new
		// org.king.classmanage.web.help.DormitoryBindInfo("
		// +
		// "a.dormitoryId,a.location,'',a.dormitory,'',a.roomNumber,a.gender,a.accomodation,a.classId)
		// "
		// + "from Dormitorymodel a where (a.classId='' or a.classId is null) ";
		List entitys = dormitorymodelDAO.find(hql);

		HashMap Hash_location = new HashMap();
		List Temp_location = dormitorymodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 6 ");
		for (int i = 0; i < Temp_location.size(); i++) {
			HashMap temp = (HashMap) Temp_location.get(i);
			Hash_location.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		HashMap Hash_dormitory = new HashMap();
		List Temp_dormitory = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 7 ");
		for (int i = 0; i < Temp_dormitory.size(); i++) {
			HashMap temp = (HashMap) Temp_dormitory.get(i);
			Hash_dormitory.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_direction = new HashMap();
		List Temp_direction = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 24 ");
		for (int i = 0; i < Temp_direction.size(); i++) {
			HashMap temp = (HashMap) Temp_direction.get(i);
			Hash_direction.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		for (int i = 0; i < entitys.size(); i++) {
			DormitoryBindInfo dormitorybindinfo = (DormitoryBindInfo) entitys
					.get(i);
			String locationCode = "";
			String locationStr = "";
			if (!"".equals(dormitorybindinfo.getLocation())) {// 校区
				if (locationCode.equals(dormitorybindinfo.getLocation())) {
					dormitorybindinfo.setLocationStr(locationStr);
				} else {
					locationCode = dormitorybindinfo.getLocation();
					if (Hash_location.get(locationCode) != null) {
						locationStr = Hash_location.get(locationCode)
								.toString();
						dormitorybindinfo.setLocationStr(locationStr);
					} else {
						dormitorybindinfo.setLocationStr("");
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(dormitorybindinfo.getDormitory())) {// 楼号
				if (dormitoryCode.equals(dormitorybindinfo.getDormitory())) {
					dormitorybindinfo.setDormitoryStr(dormitoryStr);
				} else {
					dormitoryCode = dormitorybindinfo.getDormitory();
					if (Hash_dormitory.get(dormitoryCode) != null) {
						dormitoryStr = Hash_dormitory.get(dormitoryCode)
								.toString();
						dormitorybindinfo.setDormitoryStr(dormitoryStr);
					} else {
						dormitorybindinfo.setDormitoryStr("");
					}
				}

			}

			String directionCode = "";
			String directionStr = "";
			if (!"".equals(dormitorybindinfo.getDirection())) {// 朝向
				if (directionCode.equals(dormitorybindinfo.getDirection())) {
					dormitorybindinfo.setDirection(directionStr);
				} else {
					directionCode = dormitorybindinfo.getDirection();
					if (Hash_direction.get(directionCode) != null) {
						directionStr = Hash_direction.get(directionCode)
								.toString();
						dormitorybindinfo.setDirection(directionStr);
					} else {
						dormitorybindinfo.setDirection("");
					}
				}

			}

			String genderCode = "";
			String genderStr = "";
			if (!"".equals(dormitorybindinfo.getGender())) {// 性别
				if (genderCode.equals(dormitorybindinfo.getGender())) {
					dormitorybindinfo.setGender(genderStr);
				} else {
					genderCode = dormitorybindinfo.getGender();
					if (Hash_gender.get(genderCode) != null) {
						genderStr = Hash_gender.get(genderCode).toString();
						dormitorybindinfo.setGender(genderStr);
					} else {
						dormitorybindinfo.setGender("");
					}
				}

			}

		}
		return entitys;

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.dormitorymanage.service.DormitoryService#getDormByDormNoBinded(java.lang.String)
	 */
	public List getDormByDormNoBinded(String dormitory) {
		return dormitorymodelDAO
				.find("from Dormitorymodel a where a.dormitory='" + dormitory
						+ "'" + " and a.classId=''");
	}

	// 未报到床位数
	public List getNotcheckinDormStat(HttpServletRequest request) {

		String xhorgh = (String) request.getSession().getAttribute("userName");
		List entitys = null;
		MyQuery myQuery = new MyQuery();
		List entitys1 = null;
		MyQuery myQuery1 = new MyQuery();

		int totalNumber = 0;
		int studentInCount = 0;
		int nonCount = 0;

		// 复旦学院
		// ---------------------------------------------------
		myQuery
				.setQueryString("select distinct new org.king.dormitorymanage.web.help.DormitoryStatistic("
						+ "a.id.location,a.id.dormitory,a.id.location,"
						+ "a.id.dormitory,a.id.accSum,b.id.incount,0,'','',0.0,0.0,0.0) "
						+ "from DormInfoView a,DormExactStuView b,Dormitorymodel c,TabSsManager d "
						+ " where a.id.dormitory=b.id.dormitory "
						+ "and a.id.location=b.id.location "
						+ "and c.curDormDept=d.tabSsDept.id "
						+ "and c.location=a.id.location "
						+ "and c.dormitory=a.id.dormitory "
						+ "and c.curDormDept=a.id.curdormdept "
						+ "and d.stuNo='"
						+ xhorgh
						+ "' order by a.id.location,a.id.dormitory ");
		entitys = dormitorymodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {

			DormitoryStatistic dormitorystatistic = (DormitoryStatistic) entitys
					.get(i);

			totalNumber = totalNumber + dormitorystatistic.getTotalNumber();
			studentInCount = studentInCount
					+ dormitorystatistic.getStudentInCount();
			nonCount = nonCount + dormitorystatistic.getNonCount();

			if (!"".equals(dormitorystatistic.getLocation())) {// 校区
				List cap_list = studentmodelDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
								+ "and a.id.dictValue='"
								+ dormitorystatistic.getLocation() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					dormitorystatistic.setLocation(Cap);
				}
			}
			if (!"".equals(dormitorystatistic.getDormitory())) {// 楼号
				List cap_list = studentmodelDAO
						.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
								+ "and a.id.dictValue='"
								+ dormitorystatistic.getDormitory() + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					dormitorystatistic.setDormitory(Cap);
				}
			}
		}

		myQuery1
				.setQueryString("select  new org.king.dormitorymanage.web.help.DormitoryStatistic('ALLLOC','ALLDORM','ALLLOC',"
						+ "'ALLDORM',sum(a.id.accSum),sum(b.id.incount),0,'','',0.0,0.0,0.0) "
						+ "from DormInfoView a,DormExactStuView b,Dormitorymodel c,TabSsManager d "
						+ "where a.id.dormitory=b.id.dormitory "
						+ "and a.id.location=b.id.location "
						+ "and c.curDormDept=d.tabSsDept.id "
						+ "and c.location=a.id.location "
						+ "and c.dormitory=a.id.dormitory "
						+ "and d.stuNo='"
						+ xhorgh + "' ");

		if (entitys != null && entitys.size() > 0) {
			entitys1 = dormitorymodelDAO.find(myQuery1);

			DormitoryStatistic dormitorystatisticSum = (DormitoryStatistic) entitys1
					.get(0);
			dormitorystatisticSum.setTotalNumber(totalNumber);
			dormitorystatisticSum.setStudentInCount(studentInCount);
			dormitorystatisticSum.setNonCount(nonCount);

			entitys.addAll(entitys1);
		}
		return entitys;
	}

	public List getDormStat(HttpServletRequest request) {

		String xhorgh = (String) request.getSession().getAttribute("userName");
		String getrole = request.getParameter("getrole");
		List entitys = null;
		MyQuery myQuery = new MyQuery();
		List entitys1 = null;
		MyQuery myQuery1 = new MyQuery();

		int totalNumber = 0;
		int studentInCount = 0;
		int nonCount = 0;

		if (getrole != null && getrole.equals("2")) {// 护理学院
			// ---------------------------------------------------
			myQuery
					.setQueryString("select distinct new org.king.dormitorymanage.web.help.DormitoryStatistic("
							+ "a.id.location,a.id.dormitory,a.id.location,"
							+ "a.id.dormitory,a.id.accSum,b.id.incount,(a.id.accSum-b.id.incount),a.id.area,a.id.area,0.0,0.0,0.0) "
							+ "from DormInfoViewHlxy a,DormStuViewHlxy b,Dormitorymodel c,TabSsManager d "
							+ " where a.id.dormitory=b.id.dormitory "
							+ "and a.id.location=b.id.location "
							+ "and a.id.area=b.id.area "
							+ "and c.curDormDept=d.tabSsDept.id "
							+ "and c.location=a.id.location "
							+ "and c.dormitory=a.id.dormitory "
							+ "and c.area=a.id.area "
							+ "and c.curDormDept=a.id.curdormdept "
							+ "and d.stuNo='"
							+ xhorgh
							+ "' order by a.id.area,a.id.location,a.id.dormitory ");

			entitys = dormitorymodelDAO.find(myQuery);
			if (entitys != null && entitys.size() > 0) {
				myQuery
						.setQueryString("select distinct new org.king.dormitorymanage.web.help.DormitoryStatistic("
								+ "a.id.location,a.id.dormitory,a.id.location,"
								+ "a.id.dormitory,a.id.accSum,b.id.incount,(a.id.accSum-b.id.incount),a.id.area,a.id.area,0.0,0.0,g.dictSort) "
								+ "from DormInfoViewHlxy a,DormStuViewHlxy b,Dormitorymodel c,TabSsManager d,"
								+ "Dictionary e,Dictionary f,Dictionary g "
								+ " where a.id.dormitory=b.id.dormitory "
								+ "and a.id.location=b.id.location "
								+ "and a.id.area=b.id.area "
								+ "and c.curDormDept=d.tabSsDept.id "
								+ "and c.location=a.id.location "
								+ "and c.dormitory=a.id.dormitory "
								+ "and c.area=a.id.area "
								+ "and c.curDormDept=a.id.curdormdept "
								+ "and d.stuNo='"
								+ xhorgh
								+ "' "
								+ "and c.area=e.id.dictValue and e.id.dictNo=17 "
								+ "and c.location=f.id.dictValue and f.id.dictNo=20 "
								+ "and c.dormitory=g.id.dictValue and g.id.dictNo=21 "
								+ "order by g.dictSort ");
				entitys = dormitorymodelDAO.find(myQuery);
			}

			for (int i = 0; i < entitys.size(); i++) {

				DormitoryStatistic dormitorystatistic = (DormitoryStatistic) entitys
						.get(i);

				totalNumber = totalNumber + dormitorystatistic.getTotalNumber();
				studentInCount = studentInCount
						+ dormitorystatistic.getStudentInCount();
				nonCount = nonCount + dormitorystatistic.getNonCount();

				if (!"".equals(dormitorystatistic.getArea())) {// 大校区
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
									+ "and a.id.dictValue='"
									+ dormitorystatistic.getArea() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitorystatistic.setArea(Cap);
					}
				}
				if (!"".equals(dormitorystatistic.getLocation())) {// 校区
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
									+ "and a.id.dictValue='"
									+ dormitorystatistic.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitorystatistic.setLocation(Cap);
					}
				}
				if (!"".equals(dormitorystatistic.getDormitory())) {// 楼号
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
									+ "and a.id.dictValue='"
									+ dormitorystatistic.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitorystatistic.setDormitory(Cap);
					}
				}
			}

			myQuery1
					.setQueryString("select  new org.king.dormitorymanage.web.help.DormitoryStatistic('ALLLOC','ALLDORM','ALLLOC',"
							+ "'ALLDORM',sum(a.id.accSum),sum(b.id.incount),sum(a.id.accSum-b.id.incount),'ALLAREA','ALLAREA',0.0,0.0,0.0) "
							+ "from DormInfoViewHlxy a,DormStuViewHlxy b,Dormitorymodel c,TabSsManager d "
							+ " where a.id.dormitory=b.id.dormitory "
							+ "and a.id.location=b.id.location "
							+ "and a.id.area=b.id.area "
							+ "and c.curDormDept=d.tabSsDept.id "
							+ "and c.location=a.id.location "
							+ "and c.dormitory=a.id.dormitory "
							+ "and c.area=a.id.area "
							+ "and d.stuNo='"
							+ xhorgh + "' ");
		} else if (getrole != null && getrole.equals("3")) {
			myQuery
					.setQueryString("select distinct new org.king.dormitorymanage.web.help.DormitoryStatistic("
							+ "a.id.location,a.id.dormitory,a.id.location,"
							+ "a.id.dormitory,a.id.accSum,b.id.incount,(a.id.accSum-b.id.incount),a.id.area,a.id.area,0.0,0.0,0.0) "
							+ "from DormInfoViewHlxy a,DormStuViewYg b,Dormitorymodel c,TabSsManager d "
							+ " where a.id.dormitory=b.id.dormitory "
							+ "and a.id.location=b.id.location "
							+ "and a.id.area=b.id.area "
							+ "and c.curDormDept=d.tabSsDept.id "
							+ "and c.location=a.id.location "
							+ "and c.dormitory=a.id.dormitory "
							+ "and c.area=a.id.area "
							+ "and c.curDormDept=a.id.curdormdept "
							+ "and c.curDormDept=b.id.curdormdept "
							+ "and d.stuNo='"
							+ xhorgh
							+ "' order by a.id.area,a.id.location,a.id.dormitory ");
			entitys = dormitorymodelDAO.find(myQuery);
			if (entitys != null && entitys.size() > 0) {
				myQuery
						.setQueryString("select distinct new org.king.dormitorymanage.web.help.DormitoryStatistic("
								+ "a.id.location,a.id.dormitory,a.id.location,"
								+ "a.id.dormitory,a.id.accSum,b.id.incount,(a.id.accSum-b.id.incount),a.id.area,a.id.area,0.0,f.dictSort,g.dictSort) "
								+ "from DormInfoViewHlxy a,DormStuViewYg b,Dormitorymodel c,TabSsManager d,"
								+ "Dictionary e,Dictionary f,Dictionary g "
								+ " where a.id.dormitory=b.id.dormitory "
								+ "and a.id.location=b.id.location "
								+ "and a.id.area=b.id.area "
								+ "and c.curDormDept=d.tabSsDept.id "
								+ "and c.location=a.id.location "
								+ "and c.dormitory=a.id.dormitory "
								+ "and c.area=a.id.area "
								+ "and c.curDormDept=a.id.curdormdept "
								+ "and c.curDormDept=b.id.curdormdept "
								+ "and d.stuNo='"
								+ xhorgh
								+ "' "
								+ "and c.area=e.id.dictValue and e.id.dictNo=17 "
								+ "and c.location=f.id.dictValue and f.id.dictNo=20 "
								+ "and c.dormitory=g.id.dictValue and g.id.dictNo=21 "
								+ "order by f.dictSort,g.dictSort ");
				entitys = dormitorymodelDAO.find(myQuery);
			}
			for (int i = 0; i < entitys.size(); i++) {

				DormitoryStatistic dormitorystatistic = (DormitoryStatistic) entitys
						.get(i);

				totalNumber = totalNumber + dormitorystatistic.getTotalNumber();
				studentInCount = studentInCount
						+ dormitorystatistic.getStudentInCount();
				nonCount = nonCount + dormitorystatistic.getNonCount();

				if (!"".equals(dormitorystatistic.getArea())) {// 大校区
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
									+ "and a.id.dictValue='"
									+ dormitorystatistic.getArea() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitorystatistic.setArea(Cap);
					}
				}
				if (!"".equals(dormitorystatistic.getLocation())) {// 校区
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
									+ "and a.id.dictValue='"
									+ dormitorystatistic.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitorystatistic.setLocation(Cap);
					}
				}
				if (!"".equals(dormitorystatistic.getDormitory())) {// 楼号
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
									+ "and a.id.dictValue='"
									+ dormitorystatistic.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitorystatistic.setDormitory(Cap);
					}
				}
			}

			myQuery1
					.setQueryString("select  new org.king.dormitorymanage.web.help.DormitoryStatistic('ALLLOC','ALLDORM','ALLLOC',"
							+ "'ALLDORM',sum(a.id.accSum),sum(b.id.incount),sum((a.id.accSum-b.id.incount)),'ALLAREA','ALLAREA',0.0,0.0,0.0) "
							+ "from DormInfoViewHlxy a,DormStuViewYg b,Dormitorymodel c,TabSsManager d "
							+ " where a.id.dormitory=b.id.dormitory "
							+ "and a.id.location=b.id.location "
							+ "and a.id.area=b.id.area "
							+ "and c.curDormDept=d.tabSsDept.id "
							+ "and c.location=a.id.location "
							+ "and c.dormitory=a.id.dormitory "
							+ "and c.area=a.id.area "
							+ "and d.stuNo='"
							+ xhorgh + "' ");
		} else {// 复旦学院
			// ---------------------------------------------------
			myQuery
					.setQueryString("select distinct new org.king.dormitorymanage.web.help.DormitoryStatistic("
							+ "a.id.location,a.id.dormitory,a.id.location,"
							+ "a.id.dormitory,a.id.accSum,b.id.incount,(a.id.accSum-b.id.incount),'','',0.0,0.0,0.0) "
							+ "from DormInfoView a,DormStuView b,Dormitorymodel c,TabSsManager d "
							+ " where a.id.dormitory=b.id.dormitory "
							+ "and a.id.location=b.id.location "
							+ "and c.curDormDept=d.tabSsDept.id "
							+ "and c.location=a.id.location "
							+ "and c.dormitory=a.id.dormitory "
							+ "and c.curDormDept=a.id.curdormdept "
							+ "and d.stuNo='"
							+ xhorgh
							+ "' order by a.id.location,a.id.dormitory ");
			entitys = dormitorymodelDAO.find(myQuery);
			for (int i = 0; i < entitys.size(); i++) {

				DormitoryStatistic dormitorystatistic = (DormitoryStatistic) entitys
						.get(i);

				totalNumber = totalNumber + dormitorystatistic.getTotalNumber();
				studentInCount = studentInCount
						+ dormitorystatistic.getStudentInCount();
				nonCount = nonCount + dormitorystatistic.getNonCount();

				if (!"".equals(dormitorystatistic.getLocation())) {// 校区
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
									+ "and a.id.dictValue='"
									+ dormitorystatistic.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitorystatistic.setLocation(Cap);
					}
				}
				if (!"".equals(dormitorystatistic.getDormitory())) {// 楼号
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
									+ "and a.id.dictValue='"
									+ dormitorystatistic.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitorystatistic.setDormitory(Cap);
					}
				}
			}

			myQuery1
					.setQueryString("select  new org.king.dormitorymanage.web.help.DormitoryStatistic('ALLLOC','ALLDORM','ALLLOC',"
							+ "'ALLDORM',sum(a.id.accSum),sum(b.id.incount),sum((a.id.accSum-b.id.incount)),'','',0.0,0.0,0.0) "
							+ "from DormInfoView a,DormStuView b,Dormitorymodel c,TabSsManager d "
							+ "where a.id.dormitory=b.id.dormitory "
							+ "and a.id.location=b.id.location "
							+ "and c.curDormDept=d.tabSsDept.id "
							+ "and c.location=a.id.location "
							+ "and c.dormitory=a.id.dormitory "
							+ "and d.stuNo='" + xhorgh + "' ");
		}
		if (entitys != null && entitys.size() > 0) {
			entitys1 = dormitorymodelDAO.find(myQuery1);

			DormitoryStatistic dormitorystatisticSum = (DormitoryStatistic) entitys1
					.get(0);
			dormitorystatisticSum.setTotalNumber(totalNumber);
			dormitorystatisticSum.setStudentInCount(studentInCount);
			dormitorystatisticSum.setNonCount(nonCount);

			entitys.addAll(entitys1);
		}
		return entitys;
	}

	public List getDormStat(String dorm, String location, String area,
			HttpServletRequest request) {
		List dormStat = null;
		List dormStat1 = null;
		MyQuery myQuery = new MyQuery();
		MyQuery myQuery1 = new MyQuery();
		String xhorgh = (String) request.getSession().getAttribute("userName");

		myQuery
				.setQueryString("select new Map(a.roomNumber as roomNumber,a.direction as direction,"
						+ "a.gender as gender,a.distributeNum as totalNum, "
						+ "count(b.studentId) as allotNum, (a.distributeNum-count(b.studentId)) as nonNum) "
						+ "from Dormitorymodel a,Studentmodel b,TabSsManager d "
						+ "where a.dormitoryId=b.dormId "
						+ "and a.curDormDept=d.tabSsDept.id "
						+ "and d.stuNo='"
						+ xhorgh
						+ "' and a.distributeNum>0 and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' and a.area='"
						+ area
						+ "' group by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum,a.direction,a.gender "
						+ "order by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum ");
		myQuery1
				.setQueryString("select new Map(a.roomNumber as roomNumber,a.direction as direction,"
						+ "a.gender as gender,a.distributeNum as totalNum, "
						+ "0 as allotNum, a.distributeNum as nonNum) from Dormitorymodel a,TabSsManager d "
						+ "where 1=1 "
						+ "and a.curDormDept=d.tabSsDept.id "
						+ "and d.stuNo='"
						+ xhorgh
						+ "' and a.distributeNum>0 "
						+ "and a.dormitoryId not in (select distinct b.dormId from Studentmodel b where b.dormId is not null and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "') and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' and a.area='"
						+ area
						+ "' group by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum,a.direction,a.gender "
						+ "order by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum ");
		// if (dormitorymodelDAO.find(myQuery).size() == 0) {
		// myQuery
		// .setQueryString("select new Map(a.roomNumber as
		// roomNumber,a.accomodation as totalNum, 0 as allotNum,a.accomodation
		// as nonNum) from Dormitorymodel a where a.dormitory='"
		// + dorm
		// + "' and a.location='"
		// + location
		// + "' group by a.location, a.dormitory, a.roomNumber,
		// a.accomodation");
		// }
		dormStat = dormitorymodelDAO.find(myQuery);
		dormStat1 = dormitorymodelDAO.find(myQuery1);
		if (dormStat != null) {
			dormStat1.addAll(dormStat);
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_direction = new HashMap();
		List Temp_direction = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 24 ");
		for (int i = 0; i < Temp_direction.size(); i++) {
			HashMap temp = (HashMap) Temp_direction.get(i);
			Hash_direction.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		if (dormStat1 != null && dormStat1.size() > 0) {
			for (int i = 0; i < dormStat1.size(); i++) {
				HashMap stuMap = (HashMap) dormStat1.get(i);

				String genderCode = "";
				String genderStr = "";
				if (!"".equals((String) stuMap.get("gender"))) {// 性别
					if (genderCode.equals((String) stuMap.get("gender"))) {
						stuMap.put("gender", genderStr);
					} else {
						genderCode = (String) stuMap.get("gender");
						if (Hash_gender.get(genderCode) != null) {
							genderStr = Hash_gender.get(genderCode).toString();
							stuMap.put("gender", genderStr);
						}
					}

				}

				String directionCode = "";
				String directionStr = "";
				if (!"".equals((String) stuMap.get("direction"))) {// 朝向
					if (directionCode.equals((String) stuMap.get("direction"))) {
						stuMap.put("direction", directionStr);
					} else {
						directionCode = (String) stuMap.get("direction");
						if (Hash_direction.get(directionCode) != null) {
							directionStr = Hash_direction.get(directionCode)
									.toString();
							stuMap.put("direction", directionStr);
						}
					}

				}
			}
		}

		return dormStat1;
	}

	public List getDormStatyg(String dorm, String location, String area,
			HttpServletRequest request) {
		List dormStat = null;
		List dormStat1 = null;
		MyQuery myQuery = new MyQuery();
		MyQuery myQuery1 = new MyQuery();
		String xhorgh = (String) request.getSession().getAttribute("userName");

		myQuery
				.setQueryString("select new Map(a.unit as unit,a.level as level ,a.roomNumber as roomNumber,a.gender as gender,a.direction as direction,"
						+ "a.distributeNum as totalNum, "
						+ "count(b.id) as allotNum, (a.distributeNum-count(b.id)) as nonNum) "
						+ "from Dormitorymodel a,YxGraduate b,TabSsManager d "
						+ "where a.dormitoryId=b.dormitoryId "
						+ "and a.curDormDept=d.tabSsDept.id "
						+ "and d.stuNo='"
						+ xhorgh
						+ "' and a.distributeNum>0 and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' and a.area='"
						+ area
						+ "' group by a.unit,a.roomNumber, a.distributeNum,a.level,a.gender,a.direction "
						+ "order by a.level,a.unit,a.roomNumber ");
		myQuery1
				.setQueryString("select new Map(a.unit as unit, a.level as level ,a.roomNumber as roomNumber,a.gender as gender,a.direction as direction,"
						+ "a.distributeNum as totalNum, "
						+ "0 as allotNum, a.distributeNum as nonNum) from Dormitorymodel a,TabSsManager d "
						+ "where 1=1 "
						+ "and a.curDormDept=d.tabSsDept.id "
						+ "and d.stuNo='"
						+ xhorgh
						+ "' and a.distributeNum>0 "
						+ "and a.dormitoryId not in (select distinct b.dormitoryId from YxGraduate b where b.dormitoryId is not null and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "') and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' and a.area='"
						+ area
						+ "' group by a.unit,a.roomNumber, a.distributeNum,a.level,a.gender,a.direction "
						+ "order by a.level,a.unit,a.roomNumber ");
		// if (dormitorymodelDAO.find(myQuery).size() == 0) {
		// myQuery
		// .setQueryString("select new Map(a.roomNumber as
		// roomNumber,a.accomodation as totalNum, 0 as allotNum,a.accomodation
		// as nonNum) from Dormitorymodel a where a.dormitory='"
		// + dorm
		// + "' and a.location='"
		// + location
		// + "' group by a.location, a.dormitory, a.roomNumber,
		// a.accomodation");
		// }
		dormStat = dormitorymodelDAO.find(myQuery);
		dormStat1 = dormitorymodelDAO.find(myQuery1);
		if (dormStat != null) {
			dormStat1.addAll(dormStat);
		}
		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_direction = new HashMap();
		List Temp_direction = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 24 ");
		for (int i = 0; i < Temp_direction.size(); i++) {
			HashMap temp = (HashMap) Temp_direction.get(i);
			Hash_direction.put(temp.get("dictValue"), temp.get("dictCaption"));
		}
		if (dormStat1 != null && dormStat1.size() > 0) {
			for (int i = 0; i < dormStat1.size(); i++) {
				HashMap stuMap = (HashMap) dormStat1.get(i);

				String genderCode = "";
				String genderStr = "";
				if (!"".equals((String) stuMap.get("gender"))) {// 性别
					if (genderCode.equals((String) stuMap.get("gender"))) {
						stuMap.put("gender", genderStr);
					} else {
						genderCode = (String) stuMap.get("gender");
						if (Hash_gender.get(genderCode) != null) {
							genderStr = Hash_gender.get(genderCode).toString();
							stuMap.put("gender", genderStr);
						}
					}

				}

				String directionCode = "";
				String directionStr = "";
				if (!"".equals((String) stuMap.get("direction"))) {// 朝向
					if (directionCode.equals((String) stuMap.get("direction"))) {
						stuMap.put("direction", directionStr);
					} else {
						directionCode = (String) stuMap.get("direction");
						if (Hash_direction.get(directionCode) != null) {
							directionStr = Hash_direction.get(directionCode)
									.toString();
							stuMap.put("direction", directionStr);
						}
					}

				}
			}
		}
		return dormStat1;
	}

	public Integer getDormStatCountyg(String dorm, String location,
			String area, HttpServletRequest request) {
		List dormStat = null;
		Integer hisCount = new Integer("0");
		MyQuery myQuery = new MyQuery();
		String xhorgh = (String) request.getSession().getAttribute("userName");

		myQuery
				.setQueryString("select count(*) from Dormitorymodel a,YxGraduate b,TabSsManager c  "
						+ "where a.dormitoryId=b.dormitoryId and a.curDormDept=c.tabSsDept.id "
						+ "and c.stuNo='"
						+ xhorgh
						+ "' and a.distributeNum>0 and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ " and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' and a.area='"
						+ area
						+ "' group by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum "
						+ "order by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum ");
		if (dormitorymodelDAO.find(myQuery).size() == 0) {
			myQuery
					.setQueryString("select count(*) from Dormitorymodel a,TabSsManager c  "
							+ "where a.curDormDept=c.tabSsDept.id  "
							+ "and c.stuNo='"
							+ xhorgh
							+ "' and a.distributeNum>0 "
							+ "and a.dormitory='"
							+ dorm
							+ "' and a.location='"
							+ location
							+ "' and a.area='"
							+ area
							+ "' group by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum "
							+ "order by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum ");
		}

		dormStat = dormitorymodelDAO.find(myQuery);
		if (dormStat != null && dormStat.size() > 0) {
			hisCount = (Integer) dormStat.get(0);
		}
		return hisCount;
	}

	public List getDormStat(String dorm, String location,
			HttpServletRequest request) {
		List dormStat = null;
		List dormStat1 = null;
		MyQuery myQuery = new MyQuery();
		MyQuery myQuery1 = new MyQuery();

		String xhorgh = (String) request.getSession().getAttribute("userName");

		myQuery
				.setQueryString("select new Map(a.roomNumber as roomNumber,a.direction as direction,"
						+ "a.gender as gender,a.accomodation as totalNum, "
						+ "count(b.studentId) as allotNum, (a.accomodation-count(b.studentId)) as nonNum) "
						+ "from Dormitorymodel a,Studentmodel b,TabSsManager d "
						+ "where a.dormitoryId=b.dormId "
						+ "and a.curDormDept=d.tabSsDept.id "
						+ "and d.stuNo='"
						+ xhorgh
						+ "' and a.distributeNum>0 and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' group by a.location, a.dormitory, a.roomNumber, a.accomodation,a.direction,a.gender "
						+ "order by a.location, a.dormitory, a.roomNumber, a.accomodation ");
		myQuery1
				.setQueryString("select new Map(a.roomNumber as roomNumber,a.direction as direction,"
						+ "a.gender as gender,a.accomodation as totalNum, "
						+ "0 as allotNum, a.accomodation as nonNum) from Dormitorymodel a,TabSsManager d "
						+ "where "
						+ " a.curDormDept=d.tabSsDept.id "
						+ "and d.stuNo='"
						+ xhorgh
						+ "' and a.distributeNum>0 "
						+ "and a.dormitoryId not in (select distinct b.dormId from Studentmodel b where b.dormId is not null and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "') and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' group by a.location, a.dormitory, a.roomNumber, a.accomodation,a.direction,a.gender "
						+ "order by a.location, a.dormitory, a.roomNumber, a.accomodation ");
		// if (dormitorymodelDAO.find(myQuery).size() == 0) {
		// myQuery
		// .setQueryString("select new Map(a.roomNumber as
		// roomNumber,a.accomodation as totalNum, 0 as allotNum,a.accomodation
		// as nonNum) from Dormitorymodel a where a.dormitory='"
		// + dorm
		// + "' and a.location='"
		// + location
		// + "' group by a.location, a.dormitory, a.roomNumber,
		// a.accomodation");
		// }
		dormStat = dormitorymodelDAO.find(myQuery);
		dormStat1 = dormitorymodelDAO.find(myQuery1);
		if (dormStat != null) {
			dormStat1.addAll(dormStat);
		}

		HashMap Hash_gender = new HashMap();
		List Temp_gender = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 1 ");
		for (int i = 0; i < Temp_gender.size(); i++) {
			HashMap temp = (HashMap) Temp_gender.get(i);
			Hash_gender.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		HashMap Hash_direction = new HashMap();
		List Temp_direction = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 24 ");
		for (int i = 0; i < Temp_direction.size(); i++) {
			HashMap temp = (HashMap) Temp_direction.get(i);
			Hash_direction.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		if (dormStat1 != null && dormStat1.size() > 0) {
			for (int i = 0; i < dormStat1.size(); i++) {
				HashMap stuMap = (HashMap) dormStat1.get(i);

				String genderCode = "";
				String genderStr = "";
				if (!"".equals((String) stuMap.get("gender"))) {// 性别
					if (genderCode.equals((String) stuMap.get("gender"))) {
						stuMap.put("gender", genderStr);
					} else {
						genderCode = (String) stuMap.get("gender");
						if (Hash_gender.get(genderCode) != null) {
							genderStr = Hash_gender.get(genderCode).toString();
							stuMap.put("gender", genderStr);
						}
					}

				}

				String directionCode = "";
				String directionStr = "";
				if (!"".equals((String) stuMap.get("direction"))) {// 朝向
					if (directionCode.equals((String) stuMap.get("direction"))) {
						stuMap.put("direction", directionStr);
					} else {
						directionCode = (String) stuMap.get("direction");
						if (Hash_direction.get(directionCode) != null) {
							directionStr = Hash_direction.get(directionCode)
									.toString();
							stuMap.put("direction", directionStr);
						}
					}

				}
			}
		}
		return dormStat1;
	}

	public List getNotCheckinDormStat(String dorm, String location,
			HttpServletRequest request) {
		List dormStat = null;
		List dormStat1 = null;
		MyQuery myQuery = new MyQuery();
		MyQuery myQuery1 = new MyQuery();

		String xhorgh = (String) request.getSession().getAttribute("userName");

		myQuery
				.setQueryString("select new Map(a.roomNumber as roomNumber,a.direction as direction,"
						+ "a.gender as gender,a.accomodation as totalNum, "
						+ "count(b.studentId) as allotNum) "
						+ "from Dormitorymodel a,Studentmodel b,Stucheckininfo checkin,TabSsManager d "
						+ "where checkin.studentNo=b.studentNo and checkin.ifCheckedin='0' and checkin.reason in ('00','02') "
						+ "and a.dormitoryId=b.dormId "
						+ "and a.curDormDept=d.tabSsDept.id "
						+ "and d.stuNo='"
						+ xhorgh
						+ "' and a.distributeNum>0 and b.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' group by a.location, a.dormitory, a.roomNumber, a.accomodation,a.direction,a.gender "
						+ "order by a.location, a.dormitory, a.roomNumber, a.accomodation ");
		dormStat = dormitorymodelDAO.find(myQuery);

		String roomNos = "";
		HashMap roomhash = new HashMap();
		if (dormStat != null && dormStat.size() > 0) {
			for (int i = 0; i < dormStat.size(); i++) {
				Map roomm = (Map) dormStat.get(i);
				roomNos = roomNos + "'" + (String) roomm.get("roomNumber")
						+ "'" + ",";
				roomhash.put(roomm.get("roomNumber"), roomm.get("allotNum"));
			}
		}
		if (roomNos.length() > 0)
			roomNos = roomNos.substring(0, roomNos.length() - 1);
		if (roomNos.length() > 0) {
			myQuery1
					.setQueryString("select new Map(a.roomNumber as roomNumber,a.direction as direction,"
							+ "a.gender as gender,a.accomodation as totalNum, "
							+ "count(b.studentId) as allotNum, (a.accomodation-count(b.studentId)) as nonNum) "
							+ "from Dormitorymodel a,Studentmodel b,TabSsManager d "
							+ "where a.dormitoryId=b.dormId "
							+ "and a.curDormDept=d.tabSsDept.id "
							+ "and d.stuNo='"
							+ xhorgh
							+ "' and a.distributeNum>0 and b.enrollYear='"
							+ DateUtil.getNow("yyyy")
							+ "' "
							+ "and a.dormitory='"
							+ dorm
							+ "' and a.location='"
							+ location
							+ "' and a.roomNumber in ("
							+ roomNos
							+ ") group by a.location, a.dormitory, a.roomNumber, a.accomodation,a.direction,a.gender "
							+ "order by a.location, a.dormitory, a.roomNumber, a.accomodation ");

			dormStat1 = dormitorymodelDAO.find(myQuery1);
		}
		if (dormStat1 != null) {
			for (int i = 0; i < dormStat1.size(); i++) {
				Map roomm = (Map) dormStat1.get(i);
				roomm.put("notcheckinNum", roomhash
						.get(roomm.get("roomNumber")));
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

		HashMap Hash_direction = new HashMap();
		List Temp_direction = studentmodelDAO
				.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 24 ");
		for (int i = 0; i < Temp_direction.size(); i++) {
			HashMap temp = (HashMap) Temp_direction.get(i);
			Hash_direction.put(temp.get("dictValue"), temp.get("dictCaption"));
		}

		if (dormStat1 != null && dormStat1.size() > 0) {
			for (int i = 0; i < dormStat1.size(); i++) {
				HashMap stuMap = (HashMap) dormStat1.get(i);

				String genderCode = "";
				String genderStr = "";
				if (!"".equals((String) stuMap.get("gender"))) {// 性别
					if (genderCode.equals((String) stuMap.get("gender"))) {
						stuMap.put("gender", genderStr);
					} else {
						genderCode = (String) stuMap.get("gender");
						if (Hash_gender.get(genderCode) != null) {
							genderStr = Hash_gender.get(genderCode).toString();
							stuMap.put("gender", genderStr);
						}
					}

				}

				String directionCode = "";
				String directionStr = "";
				if (!"".equals((String) stuMap.get("direction"))) {// 朝向
					if (directionCode.equals((String) stuMap.get("direction"))) {
						stuMap.put("direction", directionStr);
					} else {
						directionCode = (String) stuMap.get("direction");
						if (Hash_direction.get(directionCode) != null) {
							directionStr = Hash_direction.get(directionCode)
									.toString();
							stuMap.put("direction", directionStr);
						}
					}

				}
			}
		}
		return dormStat1;
	}

	public String getDormInfo(String dorm, String location, String area) {

		String dormInfo = "";
		MyQuery myQuery = new MyQuery();
		myQuery
				.setQueryString("select a.dictCaption from Dictionary a where a.id.dictNo= 17 and a.id.dictValue='"
						+ area + "'");
		List aa = dormitorymodelDAO.find(myQuery);
		myQuery
				.setQueryString("select a.dictCaption from Dictionary a where a.id.dictNo= 20 and a.id.dictValue='"
						+ location + "'");
		List ln = dormitorymodelDAO.find(myQuery);
		myQuery
				.setQueryString("select a.dictCaption from Dictionary a where a.id.dictNo= 21 and a.id.dictValue='"
						+ dorm + "'");
		List dm = dormitorymodelDAO.find(myQuery);

		if (aa != null && aa.size() > 0)
			dormInfo = dormInfo + (String) aa.get(0);
		if (ln != null && ln.size() > 0)
			dormInfo = dormInfo + " " + (String) ln.get(0);
		if (dm != null && dm.size() > 0)
			dormInfo = dormInfo + " " + (String) dm.get(0);
		return dormInfo;
	}

	public String getDormInfo(String dorm, String location) {

		String dormInfo = "";
		MyQuery myQuery = new MyQuery();
		myQuery
				.setQueryString("select a.dictCaption from Dictionary a where a.id.dictNo= 6 and a.id.dictValue='"
						+ location + "'");
		List ln = dormitorymodelDAO.find(myQuery);
		myQuery
				.setQueryString("select a.dictCaption from Dictionary a where a.id.dictNo= 7 and a.id.dictValue='"
						+ dorm + "'");
		List dm = dormitorymodelDAO.find(myQuery);

		if (ln != null && ln.size() > 0)
			dormInfo = (String) ln.get(0);
		if (dm != null && dm.size() > 0)
			dormInfo = dormInfo + " " + (String) dm.get(0);
		return dormInfo;
	}

	public Integer getDormStatCount(HttpServletRequest request) {

		String xhorgh = (String) request.getSession().getAttribute("userName");
		String getrole = request.getParameter("getrole");

		List dormStat = null;
		Integer hisCount = new Integer("0");
		MyQuery myQuery = new MyQuery();

		if (getrole != null && getrole.equals("2")) {// 护理学院
			// ------------------------------------------------------
			myQuery
					.setQueryString("select count(distinct a.id.area) from DormInfoViewHlxy a,Dormitorymodel b,TabSsManager c "
							+ "where b.curDormDept=c.tabSsDept.id "
							+ "and a.id.area=b.area "
							+ "and a.id.location=b.location "
							+ "and a.id.dormitory=b.dormitory "
							+ "and a.id.curdormdept=b.curDormDept "
							+ "and c.stuNo='" + xhorgh + "' ");
			dormStat = dormitorymodelDAO.find(myQuery);
			if (dormStat != null) {
				hisCount = (Integer) dormStat.get(0);
			}
		} else {// 复旦学院
			// -------------------------------------------------------
			myQuery
					.setQueryString("select count(distinct a.id.location) from DormInfoView a,Dormitorymodel b,TabSsManager c "
							+ "where b.curDormDept=c.tabSsDept.id "
							+ "and a.id.location=b.location "
							+ "and a.id.dormitory=b.dormitory "
							+ "and a.id.curdormdept=b.curDormDept "
							+ "and c.stuNo='" + xhorgh + "' ");
			dormStat = dormitorymodelDAO.find(myQuery);
			if (dormStat != null) {
				hisCount = (Integer) dormStat.get(0);
			}
		}

		return hisCount;
	}

	public Integer getDormStatCount(String dorm, String location, String area,
			HttpServletRequest request) {
		List dormStat = null;
		Integer hisCount = new Integer("0");
		MyQuery myQuery = new MyQuery();
		String xhorgh = (String) request.getSession().getAttribute("userName");

		myQuery
				.setQueryString("select count(*) from Dormitorymodel a,Studentmodel b,TabSsManager c  "
						+ "where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
						+ "and c.stuNo='"
						+ xhorgh
						+ "' "
						+ " and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' and a.area='"
						+ area
						+ "' group by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum "
						+ "order by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum ");
		if (dormitorymodelDAO.find(myQuery).size() == 0) {
			myQuery
					.setQueryString("select count(*) from Dormitorymodel a,TabSsManager c  "
							+ "where a.curDormDept=c.tabSsDept.id  "
							+ "and c.stuNo='"
							+ xhorgh
							+ "' "
							+ "and a.dormitory='"
							+ dorm
							+ "' and a.location='"
							+ location
							+ "' and a.area='"
							+ area
							+ "' group by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum "
							+ "order by a.area,a.location, a.dormitory, a.roomNumber, a.distributeNum ");
		}

		dormStat = dormitorymodelDAO.find(myQuery);
		if (dormStat != null && dormStat.size() > 0) {
			hisCount = (Integer) dormStat.get(0);
		}
		return hisCount;
	}

	public Integer getDormStatCount(String dorm, String location,
			HttpServletRequest request) {
		List dormStat = null;
		Integer hisCount = new Integer("0");
		MyQuery myQuery = new MyQuery();
		String xhorgh = (String) request.getSession().getAttribute("userName");
		myQuery
				.setQueryString("select count(*) from Dormitorymodel a,Studentmodel b,TabSsManager c  "
						+ "where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
						+ "and c.stuNo='"
						+ xhorgh
						+ "' "
						+ " and a.dormitory='"
						+ dorm
						+ "' and a.location='"
						+ location
						+ "' group by a.location, a.dormitory, a.roomNumber, a.accomodation");
		if (dormitorymodelDAO.find(myQuery).size() == 0) {
			myQuery
					.setQueryString("select count(*) from Dormitorymodel a,TabSsManager c "
							+ " where a.curDormDept=c.tabSsDept.id  "
							+ "and c.stuNo='"
							+ xhorgh
							+ "' "
							+ "and a.dormitory='"
							+ dorm
							+ "' and a.location='"
							+ location
							+ "' group by a.location, a.dormitory, a.roomNumber, a.accomodation");
		}

		dormStat = dormitorymodelDAO.find(myQuery);
		if (dormStat != null && dormStat.size() > 0) {
			hisCount = (Integer) dormStat.get(0);
		}
		return hisCount;
	}

	public List getAllDormUnique() {
		List dormNo = null;
		dormNo = dormitorymodelDAO
				.find("select new Map(a.dormitory as dormitory) from Dormitorymodel a group by a.dormitory");
		return dormNo;
	}

	public List getAllLocation() {
		List locationList;
		locationList = dormitorymodelDAO
				.find("select new Map(a.location as location) from Dormitorymodel a group by a.location");
		return locationList;
	}

	private int getStudentDistributionResult() {
		int stuCount = 0;
		List list = studentmodelDAO
				.find("select count(a.studentId) from Studentmodel a where a.dormId<>'' and a.dormId is not null");
		if (list.size() > 0) {
			stuCount = Integer.parseInt(list.get(0).toString());
		}
		return stuCount;

	}

	public void addConvertDorm(List dormList) throws LocationNotExistException,
			DormitoryNotExistException, GenderNotExistException,
			StudentAlreadyInDormException {
		// 判断是不是已经有学生分配宿舍了
		// 如果是则不能导
		if (getStudentDistributionResult() > 0) {
			throw new StudentAlreadyInDormException("student.alreadyindorm");
		}
		// 如果没有则开始导

		// 清空宿舍表
		List allDormList = dormitorymodelDAO.getAll();
		for (int k = 0; k < allDormList.size(); k++) {
			dormitorymodelDAO.delete((Dormitorymodel) allDormList.get(k));
		}
		// 宿舍调整清空历史表
		List dormAlertList = dormAlerthisDAO.getAll();
		for (int l = 0; l < dormAlertList.size(); l++) {
			dormAlerthisDAO.delete((DormAlerthis) dormAlertList.get(l));
		}

		Dictionary dict = new Dictionary();
		String location = "", locationNo = "";
		String dormitory = "", dormitoryNo = "";
		String gender = "", genderNo = "";
		String roomNumber = "";
		String accomodation = "0";
		String dormTelphone = "";
		String fee = "0";
		List locations = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=6");
		List dormitorys = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=7");
		List genders = dormitorymodelDAO
				.find("from Dictionary a where a.id.dictNo=1");
		for (int j = 0; j < dormList.size(); j++) {
			location = "";
			locationNo = "";
			dormitory = "";
			dormitoryNo = "";
			gender = "";
			genderNo = "";
			roomNumber = "";
			accomodation = "0";
			fee = "0";
			dormTelphone = "";
			Dormitorymodel dorm = new Dormitorymodel();
			List oneDorm = (List) dormList.get(j);
			location = oneDorm.get(0).toString();
			dormitory = oneDorm.get(1).toString();
			roomNumber = oneDorm.get(2).toString();
			gender = oneDorm.get(3).toString();
			if (roomNumber.indexOf(".") != -1) {
				roomNumber = roomNumber.substring(0, roomNumber.indexOf("."));
			}
			accomodation = oneDorm.get(4).toString();
			if (accomodation.indexOf(".") != -1) {
				accomodation = accomodation.substring(0, accomodation
						.indexOf("."));
			}
			fee = oneDorm.get(5).toString();
			for (int i = 0; i < locations.size(); i++) {
				dict = (Dictionary) locations.get(i);
				if (dict.getDictCaption().equals(location.trim())) {
					locationNo = dict.getId().getDictValue();
					break;
				}
			}
			dormTelphone = oneDorm.get(6).toString();
			if (dormTelphone.indexOf(".") != -1) {
				dormTelphone = dormTelphone.substring(0, dormTelphone
						.indexOf("."));
			}
			if ("".equals(locationNo)) {
				throw new LocationNotExistException("location.notexist");
			}
			for (int i = 0; i < dormitorys.size(); i++) {
				dict = (Dictionary) dormitorys.get(i);
				if (dict.getDictCaption().equals(dormitory.trim())
						&& dict.getDictParent().equals(locationNo)) {
					dormitoryNo = dict.getId().getDictValue();
					break;
				}
			}
			if ("".equals(dormitoryNo)) {
				throw new DormitoryNotExistException("dormitory.notexist");
			}
			for (int i = 0; i < genders.size(); i++) {
				dict = (Dictionary) genders.get(i);
				if (dict.getDictCaption().equals(gender.trim())) {
					genderNo = dict.getId().getDictValue();
					break;
				}
			}
			if ("".equals(genderNo)) {
				throw new GenderNotExistException("gender.notexist");
			}
			dorm.setLocation(locationNo);
			dorm.setDormitory(dormitoryNo);
			dorm.setRoomNumber(roomNumber);
			dorm.setGender(genderNo);
			dorm.setAccomodation(Integer.parseInt(accomodation));
			dorm.setFee(Double.parseDouble(fee));
			dorm.setTelphone(dormTelphone);
			dorm.setClassId("");
			dormitorymodelDAO.save(dorm);

		}

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.dormitorymanage.service.DormitoryService#getDormbylocdormandnum(java.lang.String,
	 *      java.lang.String, java.lang.String)
	 */
	public int getDormbylocdormandnum(String location, String dormitory,
			String roomNumber) {
		List list = dormitorymodelDAO
				.find("from Dormitorymodel a where a.location='" + location
						+ "' and a.dormitory='" + dormitory
						+ "' and a.roomNumber='" + roomNumber + "'");
		return list.size();
	}

	public boolean getCheckdup(String location, String dormitory,
			String roomNumber, String dormitoryId) {
		Dormitorymodel dormitorymodel = dormitorymodelDAO.get(dormitoryId);
		if (!location.equals(dormitorymodel.getLocation())
				|| !dormitory.equals(dormitorymodel.getDormitory())
				|| !roomNumber.equals(dormitorymodel.getRoomNumber())) {
			return true;
		} else {
			return false;
		}
	}

	public String getXmlMenuTree() {

		List classList = classmodelDAO.getAll();

		Map menuMap = new HashMap();
		// List menuList = null;

		String rootId = "-1";

		// 添加第一级子菜单
		menuMap.put(rootId, classList);

		// //为每个菜单添加他的子菜单
		// for(Iterator i=classList.iterator();i.hasNext();){
		// Classmodel classmodel = (Classmodel)i.next();
		// menuList = dormitorymodelDAO.find("from Dormitorymodel a where
		// a.classId = '"+classmodel.getClassId()+"'");
		// if(menuList.size()>0){
		// menuMap.put(classmodel.getClassId(),menuList);
		// }
		// }
		String xmlStr = ConvertXmlUtil.convertMenuListToXml(menuMap);

		return xmlStr;
	}

	public String getMajorinXmlMenuTree() {

		List majorinList = studentmodelDAO
				.find("from Dictionary a where a.id.dictNo=11");

		Map menuMap = new HashMap();
		String rootId = "-1";

		// 添加第一级子菜单
		menuMap.put(rootId, majorinList);

		String xmlStr = ConvertXmlUtil.convertMajorinListToXml(menuMap);

		return xmlStr;
	}

	/**
	 * 调整宿舍
	 * 
	 */

	public void updateDormitoryfm(String oldLocation, String oldDormitory,
			String oldRoom, String[] oldStudent, String newLocation,
			String newDormitory, String newRoom, String[] newStudent,
			String operator) {
		if (newStudent != null) {
			for (int i = 0; i < newStudent.length; i++) {
				String stuId = newStudent[i];

				updateAlert(stuId, newDormitory, newRoom, newLocation, operator);

			}
		}

	}

	public List findAdjustFreshmens(String[] args) throws BusinessException {
		List stuList = null;
		String stuNo = args[0];
		String stuName = args[1];
		String location = args[2];
		String dormitory = args[3];
		String gender = args[4];
		String roomNumber = args[5];
		String page = args[6];
		StringBuffer hqlStr = new StringBuffer();

		if ("".equals(location) && "".equals(dormitory)
				&& "".equals(roomNumber)) {
			hqlStr
					.append("select new Map(a.studentId as stuId,a.studentNo as stuNo,'','','',e.dictCaption as gender,"
							+ "a.stuName as stuName) from Studentmodel a, Dictionary e where e.id.dictValue=a.gender and e.id.dictNo=1 ");

			if (!"".equals(stuNo)) {
				hqlStr.append("and a.studentNo like '%").append(stuNo).append(
						"%' ");
			}

			if (!"".equals(stuName)) {
				hqlStr.append("and a.stuName like '%").append(stuName).append(
						"%' ");
			}
			if (!"".equals(gender)) {
				hqlStr.append("and a.gender='").append(gender).append("' ");
			}

		} else {
			hqlStr
					.append("select new Map(a.studentId as stuId,a.studentNo as stuNo,c.dictCaption as location,d.dictCaption as dormitory,b.roomNumber as roomNumber,e.dictCaption as gender,"
							+ "a.stuName as stuName) from Studentmodel a,Dormitorymodel b,Dictionary c,Dictionary d,"
							+ "Dictionary e where a.dormId=b.dormitoryId and c.id.dictNo=6 and c.id.dictValue=b.location"
							+ " and d.id.dictNo=7 and d.id.dictValue=b.dormitory and e.id.dictValue=a.gender and e.id.dictNo=1 ");

			if (!"".equals(stuNo)) {
				hqlStr.append("and a.studentNo like '%").append(stuNo).append(
						"%' ");
			}
			if (!"".equals(location)) {
				hqlStr.append("and b.location='").append(location).append("' ");
			}
			if (!"".equals(dormitory)) {
				hqlStr.append("and b.dormitory='").append(dormitory).append(
						"' ");
			}
			if (!"".equals(stuName)) {
				hqlStr.append("and a.stuName like '%").append(stuName).append(
						"%' ");
			}
			if (!"".equals(gender)) {
				hqlStr.append("and a.gender='").append(gender).append("' ");
			}
			if (!"".equals(roomNumber)) {
				hqlStr.append("and b.roomNumber='").append(roomNumber).append(
						"' ");
			}
		}
		MyQuery myQuery = new MyQuery();
		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setOffset(true);
		myQuery.setQueryString(hqlStr.toString());
		stuList = dormitorymodelDAO.find(myQuery);
		return stuList;
	}

	public List findAdjustPeoples(String[] args, String schoolId) {
		String studentNo = args[0];
		String stuName = args[1];
		String gender = args[2];
		String role = "";
		String operator = "";
		String hqlStr = "";
		if (args.length >= 4) {
			role = args[3];
		}
		if (args.length >= 5) {
			operator = args[4];
		}
		List entitys = null;
		if (role.equals("")) {

			if (schoolId != null && schoolId.equals("0001")) {

				hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfo"
						+ "('','','','','','', "
						+ "a.studentId,a.studentNo,a.enterenceNo,a.examNo,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
						+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
						+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
						+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot) "
						+ "from Studentmodel a ";
				hqlStr += "where a.nationality='CHN' " + "and a.enrollYear='"
						+ DateUtil.getNow("yyyy") + "' ";
				hqlStr += "and a.majorin<>'623' ";
			} else if (schoolId != null && schoolId.equals("0002")) {

				hqlStr = "select distinct new org.king.classmanage.web.help.StudentWithAllInfoDorm"
						+ "('','','','','','', "
						+ "a.studentId,a.studentNo,a.enterenceNo,a.examNo,a.tempecardNo,a.idCard,'',a.stuName, a.gender, "
						+ "a.birthday,a.homeTelephone, a.nation, a.nationality,a.fromProvince, "
						+ "a.midSchCode, a.midSchName,a.polityBg, a.majorin,a.department, a.specIntrst,"
						+ "a.studentType, a.enrollYear, a.curGrade,a.dormId,'',a.idType,a.cultureMode,a.studentChar,a.checkornot,a.schoolornot,b.district) "
						+ "from Studentmodel a,GzStuTemp b ";
				hqlStr += "where a.enterenceNo=b.enterenceNo and a.nationality='CHN' "
						+ "and a.enrollYear='" + DateUtil.getNow("yyyy") + "' ";
				hqlStr += "and a.majorin='623' ";
			}
			hqlStr += "and a.majorin<>'117' and a.majorin<>'135' "
					+ "and a.majorin<>'248' and a.majorin<>'276' "
					+ "and (a.dormId='' or a.dormId is null) ";
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.studentNo like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.stuName like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?"
					: "");

		} else {
			hqlStr = "select distinct new Map("
					+ "a.id as id,a.graduateNo as graduateNo,a.graduateName as graduateName, a.sex as sex, "
					+ "a.nation as nation) "
					+ "from YxGraduate a , TabSsManager c ";
			// yxgraduate0_.NATIONALITY='CHN' and
			hqlStr += "where a.enrollYear='" + DateUtil.getNow("yyyy") + "' "
					+ " and a.requestAvailable='1' and a.residentNeed='2' "
					+ " and (c.tabSsDept.id=a.distriction and c.stuNo='"
					+ operator + "') "
					+ "and a.speciality<>'117' and a.speciality<>'135' "
					+ "and a.speciality<>'248' and a.speciality<>'276' "
					+ "and (a.dormitoryId='' or a.dormitoryId is null) ";
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and a.graduateNo like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and a.graduateName like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.sex = ?" : "");
		}
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
		if (role.equals("")) {
			myQuery.setOrderby(" order by a.studentNo");
		} else {
			myQuery.setOrderby(" order by a.graduateNo");
		}
		myQuery.setQueryString(hqlStr);

		// myQuery.setOffset(true);
		entitys = studentmodelDAO.find(myQuery);
		if (role.equals("")) {
			for (int i = 0; i < entitys.size(); i++) {

				if (schoolId != null && schoolId.equals("0001")) {

					StudentWithAllInfo studentwithallinfo = null;
					studentwithallinfo = (StudentWithAllInfo) entitys.get(i);
					String genderCode = "";
					String genderStr = "";
					if (!"".equals(studentwithallinfo.getGender())) {// 性别
						if (genderCode.equals(studentwithallinfo.getGender())) {
							studentwithallinfo.setGender(genderStr);
						} else {
							genderCode = studentwithallinfo.getGender();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
											+ "and a.id.dictValue='"
											+ studentwithallinfo.getGender()
											+ "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								genderStr = Cap;
								studentwithallinfo.setGender(genderStr);
							}
						}

					}
					// String fromProvinceCode = "";
					// String fromProvinceStr = "";
					// if (!"".equals(studentwithallinfo.getFromProvince())) {//
					// 生源地
					// if (fromProvinceCode.equals(studentwithallinfo
					// .getFromProvince())) {
					// studentwithallinfo.setFromProvince(fromProvinceStr);
					// } else {
					// fromProvinceCode = studentwithallinfo.getFromProvince();
					// List cap_list = studentmodelDAO
					// .find("select a.dictCaption from Dictionary a where
					// a.id.dictNo=
					// 10 "
					// + "and a.id.dictValue='"
					// + studentwithallinfo.getFromProvince()
					// + "'");
					//
					// if (cap_list.size() > 0) {
					// String Cap = cap_list.get(0).toString();
					// fromProvinceStr = Cap;
					// studentwithallinfo.setFromProvince(fromProvinceStr);
					// }
					// }
					//
					// }
					//
					// String nationalityCode = "";
					// String nationalityStr = "";
					// if (!"".equals(studentwithallinfo.getNationality())) {//
					// 国籍
					// if
					// (nationalityCode.equals(studentwithallinfo.getNationality()))
					// {
					// studentwithallinfo.setNationality(nationalityStr);
					// } else {
					// nationalityCode = studentwithallinfo.getNationality();
					// List cap_list = studentmodelDAO
					// .find("select a.dictCaption from Dictionary a where
					// a.id.dictNo=
					// 12 "
					// + "and a.id.dictValue='"
					// + studentwithallinfo.getNationality() + "'");
					//
					// if (cap_list.size() > 0) {
					// String Cap = cap_list.get(0).toString();
					// nationalityStr = Cap;
					// studentwithallinfo.setNationality(nationalityStr);
					// }
					// }
					//
					// }
					// String politybgCode = "";
					// String politybgStr = "";
					// if (!"".equals(studentwithallinfo.getPolityBg())) {//
					// 政治面貌
					// if
					// (politybgCode.equals(studentwithallinfo.getPolityBg())) {
					// studentwithallinfo.setPolityBg(politybgStr);
					// } else {
					// politybgCode = studentwithallinfo.getPolityBg();
					// List cap_list = studentmodelDAO
					// .find("select a.dictCaption from Dictionary a where
					// a.id.dictNo=
					// 4 "
					// + "and a.id.dictValue='"
					// + studentwithallinfo.getPolityBg() + "'");
					//
					// if (cap_list.size() > 0) {
					// String Cap = cap_list.get(0).toString();
					// politybgStr = Cap;
					// studentwithallinfo.setPolityBg(politybgStr);
					// }
					// }
					//
					// }
					// String majorinCode = "";
					// String majorinStr = "";
					// if (!"".equals(studentwithallinfo.getMajorin())) {// 专业
					// if (majorinCode.equals(studentwithallinfo.getMajorin()))
					// {
					// studentwithallinfo.setMajorin(majorinStr);
					// } else {
					// majorinCode = studentwithallinfo.getMajorin();
					// List cap_list = studentmodelDAO
					// .find("select a.dictCaption from Dictionary a where
					// a.id.dictNo=
					// 11 "
					// + "and a.id.dictValue='"
					// + studentwithallinfo.getMajorin() + "'");
					//
					// if (cap_list.size() > 0) {
					// String Cap = cap_list.get(0).toString();
					// majorinStr = Cap;
					// studentwithallinfo.setMajorin(majorinStr);
					// }
					// }
					//
					// }
					String nationCode = "";
					String nationStr = "";
					if (!"".equals(studentwithallinfo.getNation())) {// 民族
						if (nationCode.equals(studentwithallinfo.getNation())) {
							studentwithallinfo.setNation(nationStr);
						} else {
							nationCode = studentwithallinfo.getNation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo=2 "
											+ "and a.id.dictValue='"
											+ studentwithallinfo.getNation()
											+ "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								nationStr = Cap;
								studentwithallinfo.setNation(nationStr);
							}
						}
					}
				} else if (schoolId != null && schoolId.equals("0002")) {
					StudentWithAllInfoDorm studentwithallinfo = null;
					studentwithallinfo = (StudentWithAllInfoDorm) entitys
							.get(i);
					String genderCode = "";
					String genderStr = "";
					if (!"".equals(studentwithallinfo.getGender())) {// 性别
						if (genderCode.equals(studentwithallinfo.getGender())) {
							studentwithallinfo.setGender(genderStr);
						} else {
							genderCode = studentwithallinfo.getGender();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
											+ "and a.id.dictValue='"
											+ studentwithallinfo.getGender()
											+ "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								genderStr = Cap;
								studentwithallinfo.setGender(genderStr);
							}
						}

					}

					String districtCode = "";
					String districtStr = "";
					if (!"".equals(studentwithallinfo.getDistrict())) {// 区县
						if (districtCode.equals(studentwithallinfo
								.getDistrict())) {
							studentwithallinfo.setDistrict(districtStr);
						} else {
							districtCode = studentwithallinfo.getDistrict();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 23 "
											+ "and a.id.dictValue='"
											+ studentwithallinfo.getDistrict()
											+ "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								districtStr = Cap;
								studentwithallinfo.setDistrict(districtStr);
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
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo=2 "
											+ "and a.id.dictValue='"
											+ studentwithallinfo.getNation()
											+ "'");

							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								nationStr = Cap;
								studentwithallinfo.setNation(nationStr);
							}
						}
					}
				}

			}
		} else {
			for (int i = 0; i < entitys.size(); i++) {
				Map mp = (Map) entitys.get(i);
				String genderCode = "";
				String genderStr = "";
				if (!"".equals(mp.get("sex"))) {// 性别
					if (genderCode.equals(mp.get("sex"))) {
						mp.put("sex", genderStr);
					} else {
						genderCode = (String) mp.get("sex");
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
										+ "and a.id.dictValue='"
										+ (String) mp.get("sex") + "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							genderStr = Cap;
							mp.put("sex", genderStr);
						}
					}

				}
				String nationCode = "";
				String nationStr = "";
				if (!"".equals(mp.get("nation"))) {// 民族
					if (nationCode.equals(mp.get("nation"))) {
						mp.put("nation", nationStr);
					} else {
						nationCode = (String) mp.get("nation");
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo=2 "
										+ "and a.id.dictValue='"
										+ (String) mp.get("nation") + "'");

						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							nationStr = Cap;
							mp.put("nation", nationStr);
						}
					}
				}

			}
		}
		return entitys;
	}

	public List findDormPeoples(String[] args, String schoolId,
			HttpServletRequest request) {

		String getrole = request.getParameter("getrole");

		List stuList = null;
		String location = args[0];
		String dormitory = args[1];
		String roomNumber = args[2];
		String area = "";
		if (args.length >= 4) {
			area = args[3]; // 表示大校区
		}
		String role = "";
		String unit = "";
		String operator = "";
		StringBuffer hqlStr = null;
		// StringBuffer whereStrBuf = null;
		if (args.length >= 5) {

			unit = args[4];
		}
		if (args.length >= 6) {
			role = args[5];
		}
		if (args.length >= 7) {
			operator = args[6];
		}
		if (!"".equals(location) && !"".equals(dormitory)
				&& !"".equals(roomNumber)) {
			if (role == null || role.equals("2") || role.equals("")) {
				hqlStr = new StringBuffer();
				if (getrole != null && getrole.equals("2")) {// 护理学院
					if (!"".equals(area)) {
						hqlStr
								.append("select new Map(a.studentId as stuId,a.studentNo as stuNo,a.stuName as stuName,"
										+ "b.dormitoryId as dormitoryId,e.dictCaption as gender,"
										+ "b.distributeNum as accomodation,d.dictCaption as district) "// 显示分配床位数
										+ "from Studentmodel a,GzStuTemp c,Dictionary d,Dormitorymodel b,Dictionary e "
										+ "where a.dormId=b.dormitoryId "
										+ "and a.enterenceNo=c.enterenceNo "
										+ "and d.id.dictValue=c.district and d.id.dictNo=23 "
										+ "and a.enrollYear='"
										+ DateUtil.getNow("yyyy")
										+ "' "
										+ "and a.yxClass.yxCollege.yxSchool.schoolId='"
										+ schoolId
										+ "' "
										+ "and e.id.dictValue=b.gender and e.id.dictNo=1 ");
					}
				} else {// 复旦学院
					hqlStr
							.append("select new Map(a.studentId as stuId,a.studentNo as stuNo,a.stuName as stuName,"
									+ "b.dormitoryId as dormitoryId,e.dictCaption as gender,b.accomodation as accomodation) "
									+ "from Studentmodel a,Dormitorymodel b,Dictionary e "
									+ "where a.dormId=b.dormitoryId "
									+ "and a.enrollYear='"
									+ DateUtil.getNow("yyyy")
									+ "' "
									+ "and a.yxClass.yxCollege.yxSchool.schoolId='"
									+ schoolId
									+ "' "
									+ "and e.id.dictValue=b.gender and e.id.dictNo=1 ");
				}

			} else {
				if (!"".equals(unit) && !"".equals(area)) {
					hqlStr = new StringBuffer(
							"select new Map(a.id as stuId,a.graduateNo as stuNo,a.graduateName as stuName,"
									+ " b.dormitoryId as dormitoryId,e.dictCaption as gender,b.distributeNum as accomodation)"
									+ " from YxGraduate a,Dormitorymodel b,TabSsManager c,Dictionary e  "
									+ "where a.dormitoryId=b.dormitoryId "
									+ "and a.distriction=c.tabSsDept.id and c.stuNo='"
									+ operator
									+ "' "
									+ " and a.enrollYear='"
									+ DateUtil.getNow("yyyy")
									+ "' and e.id.dictValue=b.gender and e.id.dictNo=1");
				}
			}
			MyQuery mq = new MyQuery();
			if (!"".equals(location)) {
				hqlStr.append(" and b.location = ?");
				mq.addPara(location, Types.VARCHAR);
			}
			if (!"".equals(dormitory)) {
				hqlStr.append(" and b.dormitory = ?");
				mq.addPara(dormitory, Types.VARCHAR);
			}
			if (!"".equals(roomNumber)) {
				hqlStr.append(" and b.roomNumber = ?");
				mq.addPara(roomNumber, Types.VARCHAR);
			}
			if (!"".equals(unit)) {
				hqlStr.append(" and b.unit = ?");
				mq.addPara(unit, Types.VARCHAR);
			}
			if (!"".equals(area)) {
				hqlStr.append(" and b.area = ?");
				mq.addPara(area, Types.VARCHAR);
			}
			// hqlStr.append(hqlStr);
			mq.setQueryString(hqlStr.toString());
			stuList = baseDAO.findEntity(mq);
		}
		return stuList;
	}

	public List findfdyDormPeoples_hlxy(String[] args, String schoolId,
			HttpServletRequest request) {

		String getrole = request.getParameter("getrole");
		String xhorgh = (String) request.getSession().getAttribute("userName");
		List stuList = null;
		String location = args[0];
		String dormitory = args[1];
		String roomNumber = args[2];
		String area = "";
		if (args.length >= 4) {
			area = args[3]; // 表示大校区
		}
		String role = "";
		String unit = "";
		// String operator = "";
		StringBuffer hqlStr = null;
		// StringBuffer whereStrBuf = null;
		if (args.length >= 5) {

			unit = args[4];
		}
		if (args.length >= 6) {
			role = args[5];
		}
		// if (args.length >= 7) {
		// operator = args[5];
		// }
		if (!"".equals(location) && !"".equals(dormitory)
				&& !"".equals(roomNumber)) {
			hqlStr = new StringBuffer();
			if (getrole != null && getrole.equals("2")) {// 护理学院
				if (!"".equals(area)) {
					hqlStr
							.append("select new Map(a.studentId as stuId,a.studentNo as stuNo,a.stuName as stuName,"
									+ "b.dormitoryId as dormitoryId,e.dictCaption as gender,"
									+ "b.distributeNum as accomodation,d.dictCaption as district) "// 显示分配床位数
									+ "from Studentmodel a,Classmanager f,Managermodel g,"
									+ "GzStuTemp c,Dictionary d,Dormitorymodel b,Dictionary e "
									+ "where a.dormId=b.dormitoryId "
									+ "and a.enterenceNo=c.enterenceNo "
									+ "and d.id.dictValue=c.district and d.id.dictNo=23 "
									+ "and a.yxClass.classId=f.id.classId "
									+ "and g.managerId=f.id.managerId "
									+ "and g.managerNo='"
									+ xhorgh
									+ "' "
									+ "and a.enrollYear='"
									+ DateUtil.getNow("yyyy")
									+ "' "
									+ "and a.yxClass.yxCollege.yxSchool.schoolId='"
									+ schoolId
									+ "' "
									+ "and e.id.dictValue=b.gender and e.id.dictNo=1 ");
				}
			}

			MyQuery mq = new MyQuery();
			if (!"".equals(location)) {
				hqlStr.append(" and b.location = ?");
				mq.addPara(location, Types.VARCHAR);
			}
			if (!"".equals(dormitory)) {
				hqlStr.append(" and b.dormitory = ?");
				mq.addPara(dormitory, Types.VARCHAR);
			}
			if (!"".equals(roomNumber)) {
				hqlStr.append(" and b.roomNumber = ?");
				mq.addPara(roomNumber, Types.VARCHAR);
			}
			if (!"".equals(area)) {
				hqlStr.append(" and b.area = ?");
				mq.addPara(area, Types.VARCHAR);
			}
			// hqlStr.append(hqlStr);
			mq.setQueryString(hqlStr.toString());
			stuList = baseDAO.findEntity(mq);
		}
		return stuList;
	}

	public void updateDormitoryPeople(String[] temp, String[] untemp,
			String operator, String role)
			throws AccomodationNotEnoughException, GenderNotMatchException,
			DormitoryHasnotbindedException {
		String studentId = "";
		String dromitoryId = "";
		boolean unchecked = true;
		String gender = "";
		String tempgender = "";
		if (null != temp) {
			for (int i = 0; i < temp.length; i++) {
				if (i % 5 == 0) {
					// dormitoryId
					studentId = temp[i];
					if ("".equals(studentId)) {
						i = i + 4;
						continue;
					}
					i = i + 2;
					tempgender = temp[i];
					i = i + 2;
					dromitoryId = temp[i];
					if (unchecked) {
						int stuCount = temp.length / 5;
						int max = stuCount;
						for (int s = 0; s < max; s++) {
							if ("".equals(temp[5 * s])) {
								stuCount--;
							}
						}
						Dormitorymodel dormitorymodel = dormitorymodelDAO
								.get(dromitoryId);
						if (role == null) {
							if (dormitorymodel.getAccomodation() < stuCount) {
								throw new AccomodationNotEnoughException();
							}
						} else {
							if (dormitorymodel.getDistributeNum() < stuCount) {
								throw new AccomodationNotEnoughException();
							}
						}
						if (role == null) {
							if (dormitorymodel.getClassId() == null
									|| "".equals(dormitorymodel.getClassId())) {
								throw new DormitoryHasnotbindedException();
							}
						}
						gender = "1".equals(dormitorymodel.getGender()) ? "男"
								: "女";
						unchecked = false;
					}
					if (!tempgender.equals(gender)) {
						throw new GenderNotMatchException();
					}
					if (role == null || !role.equals("3")) {
						Studentmodel studentmodel = studentmodelDAO
								.get(studentId);
						// 保存修改历史记录
						if (studentmodel.getDormId() == null
								|| "".equals(studentmodel.getDormId())) {
							Dormitorymodel dormitorymodel = dormitorymodelDAO
									.get(dromitoryId);
							DormAlerthis dormHis = new DormAlerthis();
							dormHis.setDormitoryIdO(null);
							dormHis.setDormitoryIdN(dromitoryId);
							dormHis.setClassIdN(dormitorymodel.getClassId());
							dormHis.setClassIdO(null);
							dormHis.setStudentId(studentmodel.getStudentId());
							dormHis.setOperatorTime(DateUtil.getNow());
							dormHis.setOperatorId(operator);
							dormAlerthisDAO.save(dormHis);
							// update 现在的记录
							if (role == null) {
								Classmodel classmodel = new Classmodel();
								String hql = "from Classmodel a where a.classId='"
										+ dormitorymodel.getClassId() + "' ";
								List list = classmodelDAO.find(hql);
								if (list != null && list.size() > 0) {
									classmodel = (Classmodel) list.get(0);
									studentmodel.setYxClass(new Classmodel());
									studentmodel.setYxClass(classmodel);
								}

							}
							studentmodel.setDormId(dromitoryId);
							studentmodelDAO.update(studentmodel);

						}
					} else {
						YxGraduate yg = (YxGraduate) baseDAO.getEntity(
								YxGraduate.class, studentId);
						if (yg.getDormitoryId() == null
								|| "".equals(yg.getDormitoryId())) {
							Dormitorymodel dormitorymodel = dormitorymodelDAO
									.get(dromitoryId);
							DormAlerthis dormHis = new DormAlerthis();
							dormHis.setDormitoryIdO(null);
							dormHis.setDormitoryIdN(dromitoryId);
							// dormHis.setClassIdN(dormitorymodel.getClassId());
							// dormHis.setClassIdO(null);
							dormHis.setStudentId(yg.getId());
							dormHis.setOperatorTime(DateUtil.getNow());
							dormHis.setOperatorId(operator);
							dormAlerthisDAO.save(dormHis);
							// update 现在的记录
							yg.setDormitoryId(dromitoryId);
							yg.setResidentNeed("1");
							yxGraduateDAO.update(yg);
						}
					}
				}
			}
		}
		if (null != untemp) {
			for (int i = 0; i < untemp.length; i++) {
				if (i % 5 == 0) {
					// dormitoryId
					studentId = untemp[i];
					if ("".equals(studentId)) {
						i = i + 4;
						continue;
					}
					if (role == null || !role.equals("3")) {
						Studentmodel studentmodel = studentmodelDAO
								.get(studentId);
						if (studentmodel.getDormId() != null) {
							// 保存修改历史记录
							DormAlerthis dormHis = new DormAlerthis();
							dormHis.setDormitoryIdO(studentmodel.getDormId());
							dormHis.setDormitoryIdN(null);
							dormHis.setClassIdN(null);
							dormHis.setClassIdO(studentmodel.getYxClass()
									.getClassId());
							dormHis.setStudentId(studentmodel.getStudentId());
							dormHis.setOperatorTime(DateUtil.getNow());
							dormHis.setOperatorId(operator);
							dormAlerthisDAO.save(dormHis);

							// if(role == null){
							// studentmodel.setYxClass(null);
							// }

							studentmodel.setDormId(null);
							studentmodelDAO.update(studentmodel);
						}
					} else {
						YxGraduate yg = (YxGraduate) baseDAO.getEntity(
								YxGraduate.class, studentId);
						if (yg.getDormitoryId() != null) {
							// 保存修改历史记录
							DormAlerthis dormHis = new DormAlerthis();
							dormHis.setDormitoryIdO(yg.getDormitoryId());
							dormHis.setDormitoryIdN(null);
							// dormHis.setClassIdN(null);
							// dormHis.setClassIdO(yg.getYxClass()
							// .getClassId());
							dormHis.setStudentId(yg.getId());
							dormHis.setOperatorTime(DateUtil.getNow());
							dormHis.setOperatorId(operator);
							dormAlerthisDAO.save(dormHis);
							yg.setDormitoryId(null);
							yg.setResidentNeed("2");
							yxGraduateDAO.update(yg);
						}
					}
				}
			}
		}
	}

	public Dormitorymodel getDormitory(String area, String location,
			String dormitory, String roomNumber) {
		Dormitorymodel dormitorymodel = null;
		String sqlStr = "from Dormitorymodel a where 1=1 ";

		if (!"".equals(area)) {
			sqlStr += "and a.area='" + area + "' ";
		}
		if (!"".equals(location)) {
			sqlStr += "and a.location='" + location + "' ";
		}
		if (!"".equals(dormitory)) {
			sqlStr += "and a.dormitory='" + dormitory + "' ";
		}
		if (!"".equals(roomNumber)) {
			sqlStr += "and a.roomNumber='" + roomNumber + "' ";
		}
		List list = dormitorymodelDAO.find(sqlStr);
		if (list.size() > 0) {
			dormitorymodel = (Dormitorymodel) list.get(0);
		}
		return dormitorymodel;
	}

	// 需要修改,增加大校区
	public Dormitorymodel getDormitory(String area, String location,
			String dormitory, String roomNumber, String operator) {
		Dormitorymodel dormitorymodel = null;
		String sqlStr = "select a from Dormitorymodel a,TabSsManager c where c.tabSsDept.id = a.curDormDept and c.stuNo = '"
				+ operator + "' ";

		if (!"".equals(area)) {
			sqlStr += "and a.area='" + area + "' ";
		}
		if (!"".equals(location)) {
			sqlStr += "and a.location='" + location + "' ";
		}
		if (!"".equals(dormitory)) {
			sqlStr += "and a.dormitory='" + dormitory + "' ";
		}
		if (!"".equals(roomNumber)) {
			sqlStr += "and a.roomNumber='" + roomNumber + "' ";
		}
		List list = dormitorymodelDAO.find(sqlStr);
		if (list.size() > 0) {
			dormitorymodel = (Dormitorymodel) list.get(0);
		}
		return dormitorymodel;
	}

	public Dormitorymodel getDormitory(String area, String location,
			String dormitory, String unit, String roomNumber, String operator) {
		Dormitorymodel dormitorymodel = null;
		String sqlStr = "select distinct a from Dormitorymodel a,TabSsManager c where c.tabSsDept.id = a.curDormDept and c.stuNo = '"
				+ operator + "' ";

		MyQuery mq = new MyQuery();
		if (!"".equals(area)) {
			sqlStr += "and a.area='" + area + "' ";
		}
		if (!"".equals(location)) {
			sqlStr += "and a.location='" + location + "' ";
		}
		if (!"".equals(dormitory)) {
			sqlStr += "and a.dormitory='" + dormitory + "' ";
		}
		if (!"".equals(unit)) {
			sqlStr += "and a.unit=? ";
			mq.addPara(unit, Types.VARCHAR);
		}
		if (!"".equals(roomNumber)) {
			sqlStr += "and a.roomNumber='" + roomNumber + "' ";
		}
		mq.setQueryString(sqlStr);
		List list = dormitorymodelDAO.find(mq);
		if (list.size() > 0) {
			dormitorymodel = (Dormitorymodel) list.get(0);
		}
		return dormitorymodel;
	}

	// 需要修改,增加大校区
	public Dormitorymodel getDormitory(String location, String dormitory,
			String roomNumber) {
		Dormitorymodel dormitorymodel = null;
		String sqlStr = "from Dormitorymodel a where 1=1 ";

		if (!"".equals(location)) {
			sqlStr += "and a.location='" + location + "' ";
		}
		if (!"".equals(dormitory)) {
			sqlStr += "and a.dormitory='" + dormitory + "' ";
		}
		if (!"".equals(roomNumber)) {
			sqlStr += "and a.roomNumber='" + roomNumber + "' ";
		}
		List list = dormitorymodelDAO.find(sqlStr);
		if (list.size() > 0) {
			dormitorymodel = (Dormitorymodel) list.get(0);
		}
		return dormitorymodel;
	}

	public Dormitorymodel getfdyDormitory(String location, String dormitory,
			String roomNumber, String classId) {
		Dormitorymodel dormitorymodel = null;
		String sqlStr = "from Dormitorymodel a where 1=1 ";

		if (!"".equals(location)) {
			sqlStr += "and a.location='" + location + "' ";
		}
		if (!"".equals(dormitory)) {
			sqlStr += "and a.dormitory='" + dormitory + "' ";
		}
		if (!"".equals(roomNumber)) {
			sqlStr += "and a.roomNumber='" + roomNumber + "' ";
		}
		if (!"".equals(classId)) {
			sqlStr += "and a.classId='" + classId + "' ";
		}

		List list = dormitorymodelDAO.find(sqlStr);
		if (list.size() > 0) {
			dormitorymodel = (Dormitorymodel) list.get(0);
		}
		return dormitorymodel;
	}

	/**
	 * 护理学院辅导调换宿舍
	 */
	public List getfdyDormitory_hlxy(String area, String location,
			String dormitory, String roomNumber, List classlist) {
		Dormitorymodel dormitorymodel = null;
		String sqlStr = "select new Map(a.dormitoryId as dormitoryId) "
				+ "from Dormitorymodel a,ClassDorm b "
				+ "where 1=1 and a.dormitoryId=b.dormId ";

		if (!"".equals(area)) {
			sqlStr += "and a.area='" + area + "' ";
		}
		if (!"".equals(location)) {
			sqlStr += "and a.location='" + location + "' ";
		}
		if (!"".equals(dormitory)) {
			sqlStr += "and a.dormitory='" + dormitory + "' ";
		}
		if (!"".equals(roomNumber)) {
			sqlStr += "and a.roomNumber='" + roomNumber + "' ";
		}
		sqlStr += "and b.classId in(";
		if (classlist != null && classlist.size() > 0) {
			for (int i = 0; i < classlist.size(); i++) {
				HashMap hashmap = (HashMap) classlist.get(i);
				String classId = (String) hashmap.get("classId");
				sqlStr += "'" + classId + "',";
			}

		}
		sqlStr = sqlStr.substring(0, (sqlStr.length() - 1));
		sqlStr += ") ";

		List list = dormitorymodelDAO.find(sqlStr);
		return list;
		// if (list.size() > 0) {
		// dormitorymodel = (Dormitorymodel) list.get(0);
		// }
		// return dormitorymodel;
	}

	public void updateTwoDormitory(String[] tempA, String[] tempB,
			String operator, String role)
			throws AccomodationNotEnoughException, GenderNotMatchException {
		String studentId = "";
		String dromitoryId = "";
		boolean unchecked = true;
		String gender = "";
		String tempgender = "";
		if (null != tempA) {
			for (int i = 0; i < tempA.length; i++) {
				if (i % 5 == 0) {
					// dormitoryId
					studentId = tempA[i];
					if ("".equals(studentId)) {
						i = i + 4;
						continue;
					}
					i = i + 2;
					tempgender = tempA[i];
					i = i + 2;
					dromitoryId = tempA[i];
					if (unchecked) {
						int stuCount = tempA.length / 5;
						int max = stuCount;
						for (int s = 0; s < max; s++) {
							if ("".equals(tempA[5 * s])) {
								stuCount--;
							}
						}
						Dormitorymodel dormitorymodel = dormitorymodelDAO
								.get(dromitoryId);
						if (role == null) {
							if (dormitorymodel.getAccomodation() < stuCount) {
								throw new AccomodationNotEnoughException();
							}
						} else {
							if (dormitorymodel.getDistributeNum() < stuCount) {
								throw new AccomodationNotEnoughException();
							}
						}
						gender = "1".equals(dormitorymodel.getGender()) ? "男"
								: "女";
						unchecked = false;
					}
					if (!tempgender.equals(gender)) {
						throw new GenderNotMatchException();
					}
					if (role == null || !role.equals("3")) {
						Studentmodel studentmodel = studentmodelDAO
								.get(studentId);
						// 保存修改历史记录
						if (!dromitoryId.equals(studentmodel.getDormId())) {
							Dormitorymodel dormitorymodel = dormitorymodelDAO
									.get(dromitoryId);
							DormAlerthis dormHis = new DormAlerthis();
							dormHis.setDormitoryIdO(studentmodel.getDormId());
							dormHis.setDormitoryIdN(dromitoryId);
							dormHis.setClassIdO(studentmodel.getYxClass()
									.getClassId());
							dormHis.setClassIdN(dormitorymodel.getClassId());
							dormHis.setStudentId(studentmodel.getStudentId());
							dormHis.setOperatorTime(DateUtil.getNow());
							dormHis.setOperatorId(operator);
							dormAlerthisDAO.save(dormHis);
							// update 现在的记录
							if (role == null) {
								Classmodel classmodel = new Classmodel();
								classmodel.setClassId(dormitorymodel
										.getClassId());
								studentmodel.setYxClass(classmodel);
							}
							studentmodel.setDormId(dromitoryId);
							studentmodelDAO.update(studentmodel);
						}
					} else {
						YxGraduate yg = (YxGraduate) baseDAO.getEntity(
								YxGraduate.class, studentId);
						if (!dromitoryId.equals(yg.getDormitoryId())) {
							Dormitorymodel dormitorymodel = dormitorymodelDAO
									.get(dromitoryId);
							DormAlerthis dormHis = new DormAlerthis();
							dormHis.setDormitoryIdO(yg.getDormitoryId());
							dormHis.setDormitoryIdN(dromitoryId);
							// dormHis.setClassIdN(dormitorymodel.getClassId());
							// dormHis.setClassIdO(null);
							dormHis.setStudentId(yg.getId());
							dormHis.setOperatorTime(DateUtil.getNow());
							dormHis.setOperatorId(operator);
							dormAlerthisDAO.save(dormHis);
							// update 现在的记录
							yg.setDormitoryId(dromitoryId);
							yxGraduateDAO.update(yg);
						}
					}
				}
			}
		}
		studentId = "";
		dromitoryId = "";
		unchecked = true;
		gender = "";
		tempgender = "";
		if (null != tempB) {
			for (int i = 0; i < tempB.length; i++) {
				if (i % 5 == 0) {
					// dormitoryId
					studentId = tempB[i];
					if ("".equals(studentId)) {
						i = i + 4;
						continue;
					}
					i = i + 2;
					tempgender = tempB[i];
					i = i + 2;
					dromitoryId = tempB[i];
					if (unchecked) {
						int stuCount = tempB.length / 5;
						int max = stuCount;
						for (int s = 0; s < max; s++) {
							if ("".equals(tempB[5 * s])) {
								stuCount--;
							}
						}
						Dormitorymodel dormitorymodel = dormitorymodelDAO
								.get(dromitoryId);
						if (role == null) {
							if (dormitorymodel.getAccomodation() < stuCount) {
								throw new AccomodationNotEnoughException();
							}
						} else {
							if (dormitorymodel.getDistributeNum() < stuCount) {
								throw new AccomodationNotEnoughException();
							}
						}
						gender = "1".equals(dormitorymodel.getGender()) ? "男"
								: "女";
						unchecked = false;
					}
					if (!tempgender.equals(gender)) {
						throw new GenderNotMatchException();
					}
					if (role == null || !role.equals("3")) {
						Studentmodel studentmodel = studentmodelDAO
								.get(studentId);
						// 保存修改历史记录
						if (!dromitoryId.equals(studentmodel.getDormId())) {
							Dormitorymodel dormitorymodel = dormitorymodelDAO
									.get(dromitoryId);
							DormAlerthis dormHis = new DormAlerthis();
							dormHis.setDormitoryIdO(studentmodel.getDormId());
							dormHis.setDormitoryIdN(dromitoryId);
							dormHis.setClassIdO(studentmodel.getYxClass()
									.getClassId());
							dormHis.setClassIdN(dormitorymodel.getClassId());
							dormHis.setStudentId(studentmodel.getStudentId());
							dormHis.setOperatorTime(DateUtil.getNow());
							dormHis.setOperatorId(operator);
							dormAlerthisDAO.save(dormHis);
							// update 现在的记录
							if (role == null) {
								Classmodel classmodel = new Classmodel();
								classmodel.setClassId(dormitorymodel
										.getClassId());
								studentmodel.setYxClass(classmodel);
							}
							studentmodel.setDormId(dromitoryId);
							studentmodelDAO.update(studentmodel);
						}
					} else {
						YxGraduate yg = (YxGraduate) baseDAO.getEntity(
								YxGraduate.class, studentId);
						if (!dromitoryId.equals(yg.getDormitoryId())) {
							// Dormitorymodel dormitorymodel = dormitorymodelDAO
							// .get(dromitoryId);
							DormAlerthis dormHis = new DormAlerthis();
							dormHis.setDormitoryIdO(yg.getDormitoryId());
							dormHis.setDormitoryIdN(dromitoryId);
							// dormHis.setClassIdN(dormitorymodel.getClassId());
							// dormHis.setClassIdO(null);
							dormHis.setStudentId(yg.getId());
							dormHis.setOperatorTime(DateUtil.getNow());
							dormHis.setOperatorId(operator);
							dormAlerthisDAO.save(dormHis);
							// update 现在的记录
							yg.setDormitoryId(dromitoryId);
							yxGraduateDAO.update(yg);
						}
					}
				}
			}
		}

	}

	public void initForm(HttpServletRequest request) {

		// // 楼列表
		// List dormitoryList = studentService.getDiction("7");
		// request.setAttribute("dormitoryList", dormitoryList);
		// // 楼区域列表
		// List locationList = studentService.getDiction("6");
		// request.setAttribute("locationList", locationList);
		String getrole = request.getParameter("getrole");
		String xhorgh = (String) request.getSession().getAttribute("userName");
		String hql = "";
		List list = new ArrayList();

		if (getrole != null && ("2".equals(getrole) || "3".equals(getrole))) {// 护理学院,研工部---------大校区,小校区

			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,c.dictSort) "
					+ "from Dormitorymodel a,TabSsManager b,Dictionary c "
					+ "where a.curDormDept=b.tabSsDept.id and b.stuNo='"
					+ xhorgh
					+ "' "
					+ " and a.area=c.id.dictValue and c.id.dictNo=17 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("areaList", list);
			request.setAttribute("sectionList", list);

			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,c.dictParent as dictParent,"
					+ "a.area as area,c.dictSort) "
					+ "from Dormitorymodel a,TabSsManager b,Dictionary c "
					+ "where a.curDormDept=b.tabSsDept.id and b.stuNo='"
					+ xhorgh
					+ "' "
					+ " and a.location=c.id.dictValue and c.id.dictNo=20 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList", list);
			request.setAttribute("districtionList", list);
			// 用于不需权限控制的情况 护理学院
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,c.dictSort) "
					+ "from Dormitorymodel a,TabSsDept b,Dictionary c "
					+ "where a.curDormDept=b.id and b.id='8a708026130a0e4501130a0f9a930003' "
					+ " and a.area=c.id.dictValue and c.id.dictNo=17 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("areaList1", list);

			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,c.dictParent as dictParent,"
					+ "a.area as area,c.dictSort) "
					+ "from Dormitorymodel a,TabSsDept b,Dictionary c "
					+ "where a.curDormDept=b.id and b.id='8a708026130a0e4501130a0f9a930003' "
					+ " and a.location=c.id.dictValue and c.id.dictNo=20 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList1", list);

		} else {
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,c.dictSort) "
					+ "from Dormitorymodel a,TabSsManager b,Dictionary c "
					+ "where a.curDormDept=b.tabSsDept.id and b.stuNo='"
					+ xhorgh
					+ "' "
					+ " and a.location=c.id.dictValue and c.id.dictNo=6 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList", list);

			// 用于不需权限控制的情况
			hql = "select distinct new Map(" + "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,c.dictSort) "
					+ "from Dictionary c " + "where 1=1 "
					+ " and  c.id.dictNo=6 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList1", list);
		}
		if (getrole != null && ("2".equals(getrole) || "3".equals(getrole))) {// 护理学院,研工部---------楼号
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,a.location as location,a.area as area,c.dictSort) "
					+ "from Dormitorymodel a,TabSsManager b,Dictionary c "
					+ "where a.curDormDept=b.tabSsDept.id and b.stuNo='"
					+ xhorgh
					+ "' "
					+ " and a.dormitory=c.id.dictValue and c.id.dictNo=21 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("dormitoryList", list);
			request.setAttribute("buildingList", list);
			// 用于不需权限控制的情况 护理学院
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,a.location as location,a.area as area,c.dictSort) "
					+ "from Dormitorymodel a,TabSsDept b,Dictionary c "
					+ "where a.curDormDept=b.id and b.id='8a708026130a0e4501130a0f9a930003' "
					+ " and a.dormitory=c.id.dictValue and c.id.dictNo=21 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("dormitoryList1", list);
			request.setAttribute("buildingList1", list);

		} else {
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,a.location as location,c.dictSort) "
					+ "from Dormitorymodel a,TabSsManager b,Dictionary c "
					+ "where a.curDormDept=b.tabSsDept.id and b.stuNo='"
					+ xhorgh
					+ "' "
					+ " and a.dormitory=c.id.dictValue and c.id.dictNo=7 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("dormitoryList", list);

			// 用于不需权限控制的情况
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,a.location as location,c.dictSort) "
					+ "from Dormitorymodel a,Dictionary c "
					+ "where 1=1 "
					+ " and a.dormitory=c.id.dictValue and c.id.dictNo=7 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("dormitoryList1", list);
		}

		hql = "select distinct new Map(" + "c.id.dictValue as dictValue,"
				+ "c.dictCaption as dictCaption,"
				+ "c.dictParent as dictParent) "
				+ "from Dormitorymodel a,TabSsManager b,Dictionary c "
				+ "where a.curDormDept=b.tabSsDept.id and b.stuNo='" + xhorgh
				+ "' " + " and a.direction=c.id.dictValue and c.id.dictNo=24 ";
		list = classmodelDAO.find(hql);
		request.setAttribute("directionList", list);

		// 上海区县
		List districtList = getDiction("23");
		request.setAttribute("districtList", districtList);

	}

	public void initForm_fdy(HttpServletRequest request) {

		String getrole = request.getParameter("getrole");
		String xhorgh = (String) request.getSession().getAttribute("userName");
		String hql = "";
		List list = new ArrayList();

		if (getrole != null && "2".equals(getrole)) {// 护理学院---------大校区,小校区

			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,c.dictSort) "
					+ "from Dormitorymodel a,Classmanager b,Dictionary c,ClassDorm d,Managermodel e "
					+ "where d.classId=b.id.classId "
					+ "and d.dormId=a.dormitoryId "
					+ "and b.id.managerId=e.managerId "
					+ "and e.managerNo='"
					+ xhorgh
					+ "' "
					+ " and a.area=c.id.dictValue and c.id.dictNo=17 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("areaList", list);

			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,c.dictParent as dictParent,a.area as area,c.dictSort) "
					+ "from Dormitorymodel a,Classmanager b,Dictionary c,ClassDorm d,Managermodel e "
					+ "where d.classId=b.id.classId "
					+ "and d.dormId=a.dormitoryId "
					+ "and b.id.managerId=e.managerId "
					+ "and e.managerNo='"
					+ xhorgh
					+ "' "
					+ " and a.location=c.id.dictValue and c.id.dictNo=20 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList", list);
		} else {
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,c.dictSort) "
					+ "from Dormitorymodel a,Classmanager b,Dictionary c,Managermodel e "
					+ "where 1=1 "
					+ "and a.classId=b.id.classId "
					+ "and b.id.managerId=e.managerId "
					+ "and e.managerNo='"
					+ xhorgh
					+ "' "
					+ " and a.location=c.id.dictValue and c.id.dictNo=6 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList", list);
		}
		if (getrole != null && ("2".equals(getrole) || "3".equals(getrole))) {// 护理学院---------楼号
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,a.area as area,a.location as location,c.dictSort) "
					+ "from Dormitorymodel a,Classmanager b,Dictionary c,ClassDorm d,Managermodel e "
					+ "where d.classId=b.id.classId "
					+ "and d.dormId=a.dormitoryId "
					+ "and b.id.managerId=e.managerId "
					+ "and e.managerNo='"
					+ xhorgh
					+ "' "
					+ " and a.dormitory=c.id.dictValue and c.id.dictNo=21 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("dormitoryList", list);
			// request.setAttribute("buildingList", list);
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent) "
					+ "from Dormitorymodel a,Classmanager b,Dictionary c,ClassDorm d,Managermodel e "
					+ "where d.classId=b.id.classId "
					+ "and d.dormId=a.dormitoryId "
					+ "and b.id.managerId=e.managerId " + "and e.managerNo='"
					+ xhorgh + "' "
					+ " and a.direction=c.id.dictValue and c.id.dictNo=24 ";
			list = classmodelDAO.find(hql);
			request.setAttribute("directionList", list);

			hql = "select distinct new Map(" + "a.classId as classId,"
					+ "a.classNo as classNo ) "
					+ "from Classmodel a,Classmanager b,Managermodel e "
					+ "where 1=1 " + "and a.classId=b.id.classId "
					+ "and b.id.managerId=e.managerId " + "and e.managerNo='"
					+ xhorgh + "' order by a.classId ";
			list = classmodelDAO.find(hql);
			request.setAttribute("classList", list);

		} else {
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent,a.location as location,c.dictSort) "
					+ "from Dormitorymodel a,Classmanager b,Dictionary c,Managermodel e "
					+ "where 1=1 "
					+ "and a.classId=b.id.classId "
					+ "and b.id.managerId=e.managerId "
					+ "and e.managerNo='"
					+ xhorgh
					+ "' "
					+ " and a.dormitory=c.id.dictValue and c.id.dictNo=7 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("dormitoryList", list);
			hql = "select distinct new Map("
					+ "c.id.dictValue as dictValue,"
					+ "c.dictCaption as dictCaption,"
					+ "c.dictParent as dictParent) "
					+ "from Dormitorymodel a,Classmanager b,Dictionary c,Managermodel e "
					+ "where 1=1 " + "and a.classId=b.id.classId "
					+ "and b.id.managerId=e.managerId " + "and e.managerNo='"
					+ xhorgh + "' "
					+ " and a.direction=c.id.dictValue and c.id.dictNo=24 ";
			list = classmodelDAO.find(hql);
			request.setAttribute("directionList", list);
		}
		// 上海区县
		List districtList = getDiction("23");
		request.setAttribute("districtList", districtList);
		// 证件类型
		List idTypeList = getDiction("29");
		request.setAttribute("idTypeList", idTypeList);
		// 培养层次
		List cultureModeList = getDiction("26");
		request.setAttribute("cultureModeList", cultureModeList);
		// 学生性质
		List studentCharList = getDiction("27");
		request.setAttribute("studentCharList", studentCharList);

	}

	public List getDiction(String dicId) {
		return studentmodelDAO.find("from Dictionary a where a.id.dictNo="
				+ dicId + " order by a.id.dictValue");
	}

	// --------------------------------------------------------------------------------------

	// 护理学院宿舍校区列表
	public List getAreaList(String curDept) {
		List li = new ArrayList();
		String sqlstring = "select distinct new Map(a.area as area,b.dictCaption as areaName) from Dormitorymodel a,Dictionary b where b.id.dictValue=a.area and b.id.dictNo=17 and a.curDormDept='"
				+ curDept + "'";

		li = dormitorymodelDAO.find(sqlstring);

		return li;
	}

	// 校区、区域对应数组
	public String[][] getALList(String curDept) {

		List li = new ArrayList();

		String[][] result;

		List areaList = getAreaList(curDept);
		String areaIds = "";

		if (areaList != null && areaList.size() > 0) {
			for (int i = 0; i < areaList.size(); i++) {
				Map aream = (Map) areaList.get(i);
				String area = (String) aream.get("area");
				areaIds = areaIds + "'" + area + "',";
			}
		}
		if (areaIds.length() > 0)
			areaIds = areaIds.substring(0, areaIds.length() - 1);

		String sqlstring = " select distinct new Map(a.location as location,b.dictCaption as locationName,a.area as area) "
				+ "from Dormitorymodel a,Dictionary b where b.id.dictValue=a.location and b.id.dictNo=20 and a.area in ("
				+ areaIds + ")";

		if (areaIds.length() > 0)
			li = dormitorymodelDAO.find(sqlstring);

		if (li != null && li.size() > 0) {
			result = new String[li.size()][3];
			for (int i = 0; i < li.size(); i++) {
				result[i][0] = (String) (((Map) li.get(i)).get("location"));
				result[i][1] = (String) (((Map) li.get(i)).get("locationName"));
				result[i][2] = (String) (((Map) li.get(i)).get("area"));
			}
			return result;
		} else
			return null;

	}

	// 护理学院宿舍区域列表
	public List getLocationList(String curDept) {
		List li = new ArrayList();
		String sqlstring = "select distinct new Map(a.location as location,b.dictCaption as locationName) from Dormitorymodel a,Dictionary b where b.id.dictValue=a.location and b.id.dictNo=20 and a.curDormDept='"
				+ curDept + "'";

		li = dormitorymodelDAO.find(sqlstring);

		return li;
	}

	// 区域\楼号对应数组
	public String[][] getLDList(String curDept) {

		List li = new ArrayList();

		String[][] result;

		List locationList = getLocationList(curDept);
		String locationIds = "";

		if (locationList != null && locationList.size() > 0) {
			for (int i = 0; i < locationList.size(); i++) {
				Map aream = (Map) locationList.get(i);
				String location = (String) aream.get("location");
				locationIds = locationIds + "'" + location + "',";
			}
		}
		if (locationIds.length() > 0)
			locationIds = locationIds.substring(0, locationIds.length() - 1);

		String sqlstring = " select distinct new Map(a.dormitory as dormitory,b.dictCaption as dormitoryName,a.location as location) "
				+ "from Dormitorymodel a,Dictionary b where b.id.dictValue=a.dormitory and b.id.dictNo=21 and a.location in ("
				+ locationIds + ")";

		if (locationIds.length() > 0)
			li = dormitorymodelDAO.find(sqlstring);

		if (li != null && li.size() > 0) {
			result = new String[li.size()][3];
			for (int i = 0; i < li.size(); i++) {
				result[i][0] = (String) (((Map) li.get(i)).get("dormitory"));
				result[i][1] = (String) (((Map) li.get(i)).get("dormitoryName"));
				result[i][2] = (String) (((Map) li.get(i)).get("location"));
			}
			return result;
		} else
			return null;

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.dormitorymanage.service.DormitoryService#getBindedDorm()
	 */
	public List getBindedDorm(String curDept) {// 护理学院当年已绑定班级的宿舍
		List entitys = dormitorymodelDAO
				.find("select new Map("
						+ "a.dormitoryId as dormitoryId,"
						+ "a.area as area,"
						+ "a.location as location,"
						+ "a.dormitory as dormitory,"
						+ "a.roomNumber as roomNumber,"
						+ "a.gender as gender,"
						+ "a.direction as direction,"
						+ "b.classId as classId,"
						+ "b.distributeNum as distributeNum) "
						+ "from Dormitorymodel a,ClassDorm b where b.dormId=a.dormitoryId and a.curDormDept='"
						+ curDept
						+ "' and b.curYear='"
						+ DateUtil.getNow("yyyy")
						+ "' order by a.area,a.location,a.dormitory,a.roomNumber ");

		if (entitys != null && entitys.size() > 0) {
			ChangeGenderValue(entitys);
			ChangeAreaValue(entitys);
			ChangeLocationValue(entitys);
			ChangeDormitoryValue(entitys);
			ChangeDirectionValue(entitys);
		}

		return entitys;
	}

	public List getUnBindedDorm(String curDept) {// 护理学院当年还可以绑定班级的宿舍
		List entitys = dormitorymodelDAO
				.find("select new Map("
						+ "a.dormitoryId as dormitoryId,a.area as area,a.location as location,a.dormitory as dormitory,a.roomNumber as roomNumber,a.gender as gender,a.direction as direction,a.emptyNum as emptyNum) "
						+ "from Dormitorymodel a where a.ifDistribute='1' and a.emptyNum>0 and a.curDormDept='"
						+ curDept
						+ "' order by a.area,a.location,a.dormitory,a.roomNumber ");

		if (entitys != null && entitys.size() > 0) {
			ChangeGenderValue(entitys);
			ChangeAreaValue(entitys);
			ChangeLocationValue(entitys);
			ChangeDormitoryValue(entitys);
			ChangeDirectionValue(entitys);
		}

		return entitys;
	}

	public boolean updateDormitory(String[] temp, String[] untemp,
			String curDept) throws DormitoryHasStuException {
		List list = studentmodelDAO
				.find("select a.dormId from Studentmodel a "
						+ "where a.yxClass.yxCollege.yxSchool.schoolId='0002' and a.yxClass.curYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and a.dormId<>'' and a.dormId is not null");
		String dromStr = "";
		for (int i = 0; i < list.size(); i++) {
			dromStr += list.get(i).toString() + ",";
		}
		String dormitoryId = "";
		String classId = "";
		List location_list = studentmodelDAO
				.find("from Dictionary a where a.id.dictNo= 6 ");
		List dormitory_list = studentmodelDAO
				.find("from Dictionary a where a.id.dictNo= 7 ");
		if (null != untemp) {
			for (int i = 0; i < untemp.length; i++) {
				if (i % 6 == 0) {
					// dormitoryId
					dormitoryId = untemp[i];
					if ("".equals(dormitoryId)) {
						i = i + 5;
						continue;
					}
					if (dromStr.indexOf(dormitoryId) != -1) {
						// 宿舍有学生
						Dormitorymodel dormm = dormitorymodelDAO
								.get(dormitoryId);

						if (!"".equals(dormm.getLocation())) {// 校区
							String location = "";
							String Cap = "";
							for (int k = 0; k < location_list.size(); k++) {
								Dictionary dictionary = (Dictionary) location_list
										.get(k);
								location = dictionary.getId().getDictValue();
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
								dormitory = dictionary.getId().getDictValue();
								if (dormitory.equals(dormm.getDormitory())) {
									Cap = dictionary.getDictCaption();
									break;
								}
							}
							dormm.setDormitory(Cap);
						}
						throw new DormitoryHasStuException(dormm.getLocation()
								+ dormm.getDormitory() + dormm.getRoomNumber());
					}
					// Dormitorymodel dormitorymodel = dormitorymodelDAO
					// .get(dormitoryId);
					// dormitorymodel.setClassId(null);
					// dormitorymodelDAO.update(dormitorymodel);

					List dormList = dormitorymodelDAO
							.find(" select a from Dormitorymodel a where a.dormitoryId='"
									+ untemp[i] + "' ");
					if (dormList != null && dormList.size() > 0) {
						Dormitorymodel dormitorymodel = (Dormitorymodel) dormList
								.get(0);
						int unbindNum = (Integer.valueOf(untemp[4])).intValue();
						dormitorymodel.setEmptyNum(unbindNum);
						dormitorymodelDAO.update(dormitorymodel);
					}

					List classdormList = dormitorymodelDAO
							.find(" select a from ClassDorm a where a.dormId='"
									+ untemp[i] + "' and a.classId='"
									+ untemp[i + 5] + "' ");
					if (classdormList != null && classdormList.size() > 0) {
						ClassDorm classDorm = (ClassDorm) classdormList.get(0);
						int disNum = ((Integer) classDorm.getDistributeNum())
								.intValue();
						int unbindNum = (Integer.valueOf(untemp[4])).intValue();
						if (disNum > unbindNum) {
							classDorm.setDistributeNum(new Integer(disNum
									- unbindNum));
							yxGraduateDAO.updateClassDorm(classDorm);
						} else
							yxGraduateDAO.deleteClassDorm(classDorm);// 删除该classdorm

					}
				}
			}

		}
		if (null != temp) {
			for (int i = 0; i < temp.length; i++) {
				if (i % 6 == 0) {
					// dormitoryId
					dormitoryId = temp[i];
					if ("".equals(dormitoryId)) {
						i = i + 5;
						continue;
					}

					classId = temp[i + 5];

					List classdormList = dormitorymodelDAO
							.find(" select a from ClassDorm a where a.dormId='"
									+ temp[i] + "' and a.classId='"
									+ temp[i + 5] + "' ");
					if (classdormList != null && classdormList.size() > 0) {
						ClassDorm classDorm = (ClassDorm) classdormList.get(0);
						int disNum = ((Integer) classDorm.getDistributeNum())
								.intValue();
						int bindNum = (Integer.valueOf(temp[i + 4])).intValue();
						classDorm
								.setDistributeNum(new Integer(disNum + bindNum));
						yxGraduateDAO.updateClassDorm(classDorm);

					} else {
						ClassDorm classDorm = new ClassDorm();
						classDorm.setClassId(temp[i + 5]);
						classDorm.setDormId(temp[i]);
						classDorm
								.setDistributeNum(Integer.valueOf(temp[i + 4]));
						classDorm.setCurYear(DateUtil.getNow("yyyy"));
						yxGraduateDAO.saveClassDorm(classDorm);// 添加该classdorm
					}
				}

			}
		}
		return true;

	}

	public void ChangeGenderValue(List list) {
		String[][] ar = { { "1", "男" }, { "2", "女" } };

		for (int j = 0; j < list.size(); j++) {
			Map n = (Map) list.get(j);
			if (n.get("gender") != null) {
				String mj = ((String) n.get("gender")).trim();
				for (int k = 0; k < ar.length; k++) {
					String mj1 = ar[k][0];
					if (mj.equals(mj1)) {
						n.put("genderName", ar[k][1]);
					}
				}
			} else
				n.put("genderName", "");
		}

	}

	public void ChangeAreaValue(List list) {
		List dictList = getAreaList();
		for (int j = 0; j < list.size(); j++) {
			Map n = (Map) list.get(j);
			if (n.get("area") != null) {
				String mj = ((String) n.get("area")).trim();
				for (int k = 0; k < dictList.size(); k++) {
					Map n1 = (Map) dictList.get(k);
					String mj1 = ((String) n1.get("dictValue")).trim();
					if (mj.equals(mj1)) {
						n.put("areaName", ((String) n1.get("dictCaption"))
								.trim());
					}
				}
			} else
				n.put("areaName", "");
		}

	}

	public void ChangeLocationValue(List list) {
		List dictList = getLocationList();
		for (int j = 0; j < list.size(); j++) {
			Map n = (Map) list.get(j);
			if (n.get("location") != null) {
				String mj = ((String) n.get("location")).trim();
				for (int k = 0; k < dictList.size(); k++) {
					Map n1 = (Map) dictList.get(k);
					String mj1 = ((String) n1.get("dictValue")).trim();
					if (mj.equals(mj1)) {
						n.put("locationName", ((String) n1.get("dictCaption"))
								.trim());
					}
				}
			} else
				n.put("locationName", "");
		}

	}

	public void ChangeDormitoryValue(List list) {
		List dictList = getDormitoryList();
		for (int j = 0; j < list.size(); j++) {
			Map n = (Map) list.get(j);
			if (n.get("dormitory") != null) {
				String mj = ((String) n.get("dormitory")).trim();
				for (int k = 0; k < dictList.size(); k++) {
					Map n1 = (Map) dictList.get(k);
					String mj1 = ((String) n1.get("dictValue")).trim();
					if (mj.equals(mj1)) {
						n.put("dormitoryName", ((String) n1.get("dictCaption"))
								.trim());
					}
				}
			} else
				n.put("dormitoryName", "");
		}

	}

	public void ChangeDirectionValue(List list) {
		List dictList = getDirectionList();
		for (int j = 0; j < list.size(); j++) {
			Map n = (Map) list.get(j);
			if (n.get("direction") != null && !n.get("direction").equals("")) {
				String mj = ((String) n.get("direction")).trim();
				for (int k = 0; k < dictList.size(); k++) {
					Map n1 = (Map) dictList.get(k);
					String mj1 = ((String) n1.get("dictValue")).trim();
					if (mj.equals(mj1)) {
						n.put("directionName", ((String) n1.get("dictCaption"))
								.trim());
					}
				}
			} else
				n.put("directionName", "");
		}

	}

	public List getAreaList() {
		List dictList = dormitorymodelDAO
				.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=17 order by di.id.dictValue");
		return dictList;
	}

	public List getLocationList() {
		List dictList = dormitorymodelDAO
				.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=20 order by di.id.dictValue");
		return dictList;
	}

	public List getDormitoryList() {
		List dictList = dormitorymodelDAO
				.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=21 order by di.id.dictValue");
		return dictList;
	}

	public List getDirectionList() {
		List dictList = dormitorymodelDAO
				.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=24 order by di.id.dictValue");
		return dictList;
	}

	public List find(String query) {
		List result = null;
		try {
			result = dormitorymodelDAO.find(query);
			// System.out.println("find ok");
		} catch (Exception e) {
			e.printStackTrace();
			// System.out.println("find error");
		}
		// if(result==null)
		// System.out.println("findresult is null");
		return result;
	}

	public void saveGzDormDistribution(String stuemp_no)
			throws DormitoryNotEnoughException, StudentAlreadyInDormException,
			Exception {
		List noList = studentmodelDAO
				.find("select a.dormId from Studentmodel a "
						+ "where a.yxClass.yxCollege.yxSchool.schoolId='0002' and a.yxClass.curYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and a.dormId<>'' and a.dormId is not null");
		if (noList != null && noList.size() > 0) {
			throw new StudentAlreadyInDormException(
					"student already in dormitory");
		}

		List managerdeptList = studentmodelDAO
				.find("select a.tabSsDept.id from TabSsManager a where a.stuNo='"
						+ stuemp_no + "' and a.inOffice=1 ");

		String curDept = "";

		if (managerdeptList != null && managerdeptList.size() > 0)
			curDept = (String) managerdeptList.get(0);

		List classList = studentmodelDAO
				.find("select distinct a.yxClass.classId from Studentmodel a,GzDormApply b "
						+ "where a.studentNo=b.studentNo "
						+ "and b.ifGiveDorm='1' and a.yxClass.yxCollege.yxSchool.schoolId='0002' "
						+ "and a.yxClass.curYear='"
						+ DateUtil.getNow("yyyy")
						+ "'");

		for (int i = 0; i < classList.size(); i++) {
			String curClass = classList.get(i).toString();

			List BoyStudent = studentmodelDAO
					.find("select a.studentId from Studentmodel a,GzDormApply b "
							+ "where a.studentNo=b.studentNo "
							+ "and b.ifGiveDorm='1' and a.yxClass.yxCollege.yxSchool.schoolId='0002' "
							+ "and a.yxClass.curYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and a.yxClass.classId='"
							+ curClass
							+ "' and a.gender='1'");

			List GirlStudent = studentmodelDAO
					.find("select a.studentId from Studentmodel a,GzDormApply b "
							+ "where a.studentNo=b.studentNo "
							+ "and b.ifGiveDorm='1' and a.yxClass.yxCollege.yxSchool.schoolId='0002' "
							+ "and a.yxClass.curYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and a.yxClass.classId='"
							+ curClass
							+ "' and a.gender='2'");

			List BoyDorm = studentmodelDAO
					.find("select new org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo("
							+ "a.dormitoryId,'','','','','','','','','',''"
							+ ",'','','',a.gender,'',b.distributeNum,'',b.classId) "
							+ "from Dormitorymodel a,ClassDorm b"
							+ " where a.dormitoryId=b.dormId and a.curDormDept='"
							+ curDept
							+ "' and b.curYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and a.gender='1' and b.classId='"
							+ curClass
							+ "'");

			List GirlDorm = studentmodelDAO
					.find("select new org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo("
							+ "a.dormitoryId,'','','','','','','','','',''"
							+ ",'','','',a.gender,'',b.distributeNum,'',b.classId) "
							+ "from Dormitorymodel a,ClassDorm b"
							+ " where a.dormitoryId=b.dormId and a.curDormDept='"
							+ curDept
							+ "' and b.curYear='"
							+ DateUtil.getNow("yyyy")
							+ "' and a.gender='2' and b.classId='"
							+ curClass
							+ "'");

			String boyIds = "";
			String girlIds = "";
			if (BoyStudent.size() > 0) {
				int boyCount = BoyStudent.size();
				for (int j = 0; j < boyCount; j++) {
					if (j == boyCount - 1) {
						boyIds += BoyStudent.get(j).toString();
					} else {
						boyIds += BoyStudent.get(j).toString() + ",";
					}
				}
				try {
					DistributionTest(boyIds, BoyDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}
			}
			if (GirlStudent.size() > 0) {
				int girlCount = GirlStudent.size();
				for (int j = 0; j < girlCount; j++) {
					if (j == girlCount - 1) {
						girlIds += GirlStudent.get(j).toString();
					} else {
						girlIds += GirlStudent.get(j).toString() + ",";
					}
				}
				try {
					DistributionTest(girlIds, GirlDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}

			}

			if (BoyStudent.size() > 0) {

				try {
					Distribution(boyIds, BoyDorm);
				} catch (DormitoryNotEnoughException e) {
					throw new DormitoryNotEnoughException(e.getMessage());
				} catch (Exception e) {
					throw new Exception(e.getMessage());
				}
			}

			if (GirlStudent.size() > 0) {
				try {
					Distribution(girlIds, GirlDorm);
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

		String[][] dormitoryArr = new String[dorms.size()][20];
		int[] distributeNum = new int[dorms.size()];
		String[] studentArr = StudentIds.split(",");
		int radom = 1;
		int total = 0;
		for (int l = 0; l < dorms.size(); l++) {
			YangongDormitoryBindInfo yangongDormitoryBindInfo = (YangongDormitoryBindInfo) dorms
					.get(l);
			dormitoryArr[l][0] = yangongDormitoryBindInfo.getDormitoryId();
			for (int m = 1; m < dormitoryArr[l].length; m++) {
				dormitoryArr[l][m] = "";
			}
			distributeNum[l] = yangongDormitoryBindInfo.getEmptyNum();
			total += yangongDormitoryBindInfo.getEmptyNum();
		}
		int i = 0;
		while (i < studentArr.length && total >= 0) {
			radom = (int) (Math.random() * dorms.size());
			if (radom < dorms.size() && distributeNum[radom] > 0) {
				for (int j = 1; j < dormitoryArr[radom].length; j++) {
					if ("".equals(dormitoryArr[radom][j])) {
						dormitoryArr[radom][j] = studentArr[i];
						distributeNum[radom]--;
						total--;
						i++;
						break;
					}
				}
			}
		}
		// int stu_index = 0;
		// for (int i = 0; i < dormitoryArr.length; i++) {
		// for (int j = 1; j <= distributeNum[i]; j++) {
		// if (stu_index >= studentArr.length) {
		// break;
		// }
		// dormitoryArr[i][j] = studentArr[stu_index];
		// stu_index++;
		// }
		// }
		if (total == 0 && i < studentArr.length - 1) {
			throw new DormitoryNotEnoughException("dormitory maybe not enough!");
		}

		// 更新数据到数据库
		// 保存分宿舍结果
		String dormitoryId = "";
		for (int l = 0; l < dormitoryArr.length; l++) {
			dormitoryId = dormitoryArr[l][0];
			for (int m = 1; m < dormitoryArr[l].length; m++) {
				if (!"".equals(dormitoryArr[l][m])) {
					Studentmodel student = studentmodelDAO
							.get(dormitoryArr[l][m]);
					if (null != student) {
						student.setDormId(dormitoryId);
						studentmodelDAO.update(student);
					}
				}

			}
		}

	}

	private void DistributionTest(String StudentIds, List dorms)
			throws DormitoryNotEnoughException, Exception {

		String[][] dormitoryArr = new String[dorms.size()][20];
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

	public List getGzClassStudentCount() {
		List list = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"
						+ "(a.yxClass.classId ,'',count(a.studentNo),0,0,0,0) "
						+ "from Studentmodel a ,GzDormApply b "
						+ "where a.studentNo=b.studentNo "
						+ "and b.ifGiveDorm='1' and a.yxClass.yxCollege.yxSchool.schoolId='0002' "
						+ " and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' " + "group by a.yxClass.classId ");
		List mmaleList = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"
						+ "(a.yxClass.classId ,'',0,count(a.studentNo),0,0,0) "
						+ "from Studentmodel a ,GzDormApply b "
						+ "where a.studentNo=b.studentNo "
						+ "and b.ifGiveDorm='1' and a.yxClass.yxCollege.yxSchool.schoolId='0002' "
						+ " and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and a.gender='1'" + "group by a.yxClass.classId ");
		List mfemaleList = yxGraduateDAO
				.find("select new org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"
						+ "(a.yxClass.classId ,'',0,0,count(a.studentNo),0,0) "
						+ "from Studentmodel a ,GzDormApply b "
						+ "where a.studentNo=b.studentNo "
						+ "and b.ifGiveDorm='1' and a.yxClass.yxCollege.yxSchool.schoolId='0002' "
						+ " and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and a.gender='2'" + "group by a.yxClass.classId ");

		int MMale = 0;
		int MFemale = 0;
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

			MMale += collegeWithStuCount.getYjsMaleCount();
			MFemale += collegeWithStuCount.getYjsFemaleCount();

			allSum += collegeWithStuCount.getStuCount();
			if (i == list.size() - 1) {
				CollegeWithStuCount addstu = new CollegeWithStuCount(
						"allCount", "all", 0, 0, 0, 0, 0);
				addstu.setStuCount(allSum);
				addstu.setYjsFemaleCount(MFemale);
				addstu.setYjsMaleCount(MMale);
				list.add(i + 1, addstu);
				break;
			}
		}
		return list;
	}

	public List getGzClassDormitoryStatistic(String stuemp_no) {

		List list_all = dormitorymodelDAO
				.find("select new map(tt.classId as collegeId,sum(tt.distributeNum) as accomodation, '10' as flag) "
						+ " from ClassDorm tt,Classmodel c where tt.classId=c.classId "
						+ "and tt.curYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and c.yxCollege.collegeId='0002' group by tt.classId");
		List list_mmale = dormitorymodelDAO
				.find("select new map(tt.classId as collegeId,sum(tt.distributeNum) as accomodation, '11' as flag) "
						+ " from ClassDorm tt,Classmodel c,Dormitorymodel d  "
						+ "where tt.classId=c.classId  and tt.dormId=d.dormitoryId and d.gender='1' "
						+ "and tt.curYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and c.yxCollege.collegeId='0002' group by tt.classId");
		List list_mfemale = dormitorymodelDAO
				.find("select new map(tt.classId as collegeId,sum(tt.distributeNum) as accomodation, '12' as flag) "
						+ " from ClassDorm tt,Classmodel c,Dormitorymodel d "
						+ "where tt.classId=c.classId and tt.dormId=d.dormitoryId and d.gender='2' "
						+ "and tt.curYear='"
						+ DateUtil.getNow("yyyy")
						+ "' and c.yxCollege.collegeId='0002' group by tt.classId");

		int MMale = 0;
		int MFemale = 0;
		int allSum = 0;
		for (int i = 0; i < list_mmale.size(); i++) {
			HashMap maptemp = (HashMap) list_mmale.get(i);
			MMale += Integer.parseInt(maptemp.get("accomodation").toString());
		}

		for (int i = 0; i < list_mfemale.size(); i++) {
			HashMap maptemp = (HashMap) list_mfemale.get(i);
			MFemale += Integer.parseInt(maptemp.get("accomodation").toString());
		}

		for (int i = 0; i < list_all.size(); i++) {
			HashMap maptemp = (HashMap) list_all.get(i);
			allSum += Integer.parseInt(maptemp.get("accomodation").toString());
		}
		HashMap map1 = new HashMap();
		map1.put("collegeId", "dormCount");
		map1.put("accomodation", String.valueOf(allSum));
		map1.put("flag", "10");
		HashMap map2 = new HashMap();
		map2.put("collegeId", "dormCount");
		map2.put("accomodation", String.valueOf(MMale));
		map2.put("flag", "11");
		HashMap map3 = new HashMap();
		map3.put("collegeId", "dormCount");
		map3.put("accomodation", String.valueOf(MFemale));
		map3.put("flag", "12");
		list_all.add(map1);
		list_all.add(map2);
		list_all.add(map3);

		if (list_all.size() > 0) {
			if (list_mmale.size() > 0) {
				list_all.addAll(list_mmale);
			}
			if (list_mfemale.size() > 0) {
				list_all.addAll(list_mfemale);
			}
		}

		return list_all;
	}

	public List getSingleDormInfo(String operator) {
		// TODO Auto-generated method stub
		List li = new ArrayList();
		StringBuffer sHqlBuff = new StringBuffer(
				" select new Map(c.dictCaption as area,d.dictCaption as location,"
						+ "e.dictCaption as dormitory,b.unit as unit,b.roomNumber as roomNumber,b.fee as fee,"
						+ "a.graduateNo as stuNo, a.graduateName as stuName,a.sex as sex)"
						+ " from YxGraduate a ,Dormitorymodel b,Dictionary c,Dictionary d,Dictionary e"
						+ " where a.dormitoryId = b.dormitoryId and a.graduateNo = ? "
						+ " and (c.id.dictValue = b.area and c.id.dictNo = 17)"
						+ " and (d.id.dictValue = b.location and d.id.dictNo = 20)"
						+ " and (e.id.dictValue = b.dormitory and e.id.dictNo = 21)"
						+ " and a.enrollYear = '" + DateUtil.getNow("yyyy")
						+ "'");
		MyQuery mq = new MyQuery();
		mq.addPara(operator, Types.VARCHAR);
		mq.setQueryString(sHqlBuff.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
}
