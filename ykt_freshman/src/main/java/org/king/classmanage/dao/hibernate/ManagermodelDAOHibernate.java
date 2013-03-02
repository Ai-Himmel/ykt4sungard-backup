package org.king.classmanage.dao.hibernate;

import java.io.Serializable;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Locale;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.classmanage.dao.ManagermodelDAO;
import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Managermanagerrole;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Schoolmanager;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.utils.DateUtil;
import org.springframework.orm.ObjectRetrievalFailureException;

import com.ibm.icu.text.CollationKey;
import com.ibm.icu.text.Collator;

/**
 * Data access object (DAO) for domain model class Managermodel.
 * 
 * @see org.king.classmanage.domain.Managermodel
 * @author MyEclipse - Hibernate Tools
 */
public class ManagermodelDAOHibernate implements ManagermodelDAO {

	private static final Log log = LogFactory
			.getLog(ManagermodelDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding Managermodel instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding Managermodel instance by query");
		return baseDAO.findEntity(query);
	}

	public Managermodel get(Serializable id) {
		try {
			return (Managermodel) baseDAO.getEntity(Managermodel.class, id);
		} catch (ObjectRetrievalFailureException e) {
			return null;
		}
	}

	public List getAll() {
		log.debug("getting Managermodel all");
		String allHql = "from Managermodel";
		return baseDAO.findEntity(allHql);
	}

	public void save(Managermodel transientInstance) {
		log.debug("saving Managermodel instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void saveDuties(Managermanagerrole transientInstance) {
		log.debug("saving Managermodel instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(Managermodel transientInstance) {
		log.debug("updating Managermodel instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(Managermodel persistentInstance) {
		log.debug("deleting Managermodel instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public void deleteManagermanagerRole(Managermanagerrole persistentInstance) {
		log.debug("deleting Managermodel instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public List findSpecial(String speciality, String id,String schoolId) {
		return findSpecial(speciality, id, false,schoolId);
	}

	public List findSpecial(String speciality, String id, boolean check,String schoolId) {
		log.debug("finding sepcial Managermodel instance");
		StringBuffer allHql = new StringBuffer();
		allHql
				.append("select distinct manager from Managermodel manager,Managermanagerrole managerrole ");
		if (check) {// 查询出没有分配的
			if ("school".equals(speciality)) {
				if ("GET_ALL".equals(id)) {
					allHql
							.append(" where manager.managerId=managerrole.id.managerId and manager.managerId not in "
									+ "(select school.id.managerId from Schoolmanager school) "
									+ "and managerrole.id.roleId='01' ");
				} else {
					allHql
							.append(",Schoolmanager school where manager.managerId=school.id.managerId and manager.managerId not in "
									+ "(select school.id.managerId from Schoolmanager school) "
									+ "and school.id.managerId=managerrole.id.managerId and managerrole.id.roleId='01' "
									+ "and school.id.schoolId='" + id + "'");
				}

			} else if ("college".equals(speciality)) {
				if ("GET_ALL".equals(id)) {
					allHql
							.append(" where manager.managerId=managerrole.id.managerId and manager.managerId not in "
									+ "(select school.id.managerId from Collegemanager school) "
									+ "and managerrole.id.roleId='11' and manager.schoolId='"+schoolId+"' ");
				} else {
					allHql
							.append(",Collegemanager college where manager.managerId=college.id.managerId and manager.managerId not in "
									+ "(select school.id.managerId from Collegemanager school) "
									+ "and college.id.managerId=managerrole.id.managerId and managerrole.id.roleId='11' "
									+ "and manager.schoolId='"+schoolId+"' "
									+ "and college.id.collegeId='" + id + "' ");
				}
			} else if ("class_ass".equals(speciality)) {
				if ("GET_ALL".equals(id)) {
					allHql
							.append(" where manager.managerId=managerrole.id.managerId and manager.managerId not in "
									+ "(select school.id.managerId from Classmanager school,Classmodel classmodel  " +
									"where school.id.classId=classmodel.classId and classmodel.curYear='"+DateUtil.getNow("yyyy")+"') "
									+ "and managerrole.id.roleId='21'  and manager.schoolId='"+schoolId+"' and manager.available='1' ");
				} else {
					allHql
							.append(",Classmanager classes where manager.managerId=classes.id.managerId and manager.managerId not in "
									+ "(select school.id.managerId from Classmanager school ) "
									+ "and classes.id.managerId=managerrole.id.managerId and managerrole.id.roleId='21' "
									+ "and manager.schoolId='"+schoolId+"' "
									+ "and manager.available='1' "									
									+ "and classes.id.classId='" + id + "'");
				}
			} else if ("class_tu".equals(speciality)) {
				if ("GET_ALL".equals(id)) {
					allHql
							.append(" where manager.managerId=managerrole.id.managerId and manager.managerId not in "
									+ "(select school.id.managerId from Classmanager school,Classmodel classmodel " +
									"where school.id.classId=classmodel.classId and classmodel.curYear='"+DateUtil.getNow("yyyy")+"') "
									+ "and managerrole.id.roleId='22' and manager.schoolId='"+schoolId+"' and manager.available='1' ");
				} else {
					allHql
							.append(",Classmanager classes where manager.managerId=classes.id.managerId and manager.managerId not in "
									+ "(select school.id.managerId from Classmanager school) "
									+ "and classes.id.managerId=managerrole.id.managerId and managerrole.id.roleId='22' "
									+ "and manager.schoolId='"+schoolId+"' "
									+ "and manager.available='1' "											
									+ "and classes.id.classId='" + id + "'");
				}
			}
		} else {// 查询出所有的
			if ("school".equals(speciality)) {
				if ("GET_ALL".equals(id)) {
					allHql
							.append(" where manager.managerId=managerrole.id.managerId "
									+ "and managerrole.id.roleId='01' ");
				} else {
					allHql
							.append(",Schoolmanager school where manager.managerId=school.id.managerId "
									+ "and school.id.managerId=managerrole.id.managerId and managerrole.id.roleId='01' "
									+ "and school.id.schoolId='" + id + "'");
				}

			} else if ("college".equals(speciality)) {
				if ("GET_ALL".equals(id)) {
					allHql
							.append(" where manager.managerId=managerrole.id.managerId "
									+ "and managerrole.id.roleId='11' and manager.schoolId='"+schoolId+"' ");
				} else {
					allHql
							.append(",Collegemanager college where manager.managerId=college.id.managerId "
									+ "and college.id.managerId=managerrole.id.managerId and managerrole.id.roleId='11' "
									+ "and manager.schoolId='"+schoolId+"' "
									+ "and college.id.collegeId='" + id + "'");
				}
			} else if ("class_ass".equals(speciality)) {
				if ("GET_ALL".equals(id)) {
					allHql
							.append(" where manager.managerId=managerrole.id.managerId "
									+ "and managerrole.id.roleId='21'  and manager.schoolId='"+schoolId+"' and manager.available='1'  ");
				} else {
					allHql
							.append(",Classmanager classes where manager.managerId=classes.id.managerId "
									+ "and classes.id.managerId=managerrole.id.managerId and managerrole.id.roleId='21' "
									+ "and manager.schoolId='"+schoolId+"' "									
									+ "and classes.id.classId='" + id + "' and manager.available='1' ");
				}
			} else if ("class_tu".equals(speciality)) {
				if ("GET_ALL".equals(id)) {
					allHql
							.append(" where manager.managerId=managerrole.id.managerId "
									+ "and managerrole.id.roleId='22'  and manager.schoolId='"+schoolId+"' and manager.available='1'  ");
				} else {
					allHql
							.append(",Classmanager classes where manager.managerId=classes.id.managerId "
									+ "and classes.id.managerId=managerrole.id.managerId and managerrole.id.roleId='22' "
									+ "and manager.schoolId='"+schoolId+"' "									
									+ "and classes.id.classId='" + id + "' and manager.available='1' ");
				}
			}
		}
		List list = baseDAO.findEntity(allHql.toString());

		Comparator comp1 = new Comparator() {
			public int compare(Object o1, Object o2) {
				Managermodel m1 = (Managermodel) o1;
				Managermodel m2 = (Managermodel) o2;
				Collator col = Collator.getInstance(Locale.CHINA);
				String managerName1 = (String) m1.getManagerName();
				String managerName2 = (String) m2.getManagerName();
				CollationKey c1 = col.getCollationKey(managerName1);
				CollationKey c2 = col.getCollationKey(managerName2);
				return c1.compareTo(c2);
			}
		};
		Collections.sort(list, comp1);
		return list;

	}

	public void saveSchoolManager(Schoolmanager schoolmanager) {
		log.debug("saving Schoolmanager instance");
		baseDAO.saveEntity(schoolmanager);
	}

	public void deleteSchoolManager(String schoolId) {
		log.debug("deleting Schoolmanager instance");
		List list = baseDAO
				.findEntity("select school from Schoolmanager school,Managermanagerrole managerrole "
						+ "where school.id.managerId=managerrole.id.managerId and school.id.schoolId='"
						+ schoolId + "' and managerrole.id.roleId='01' ");
		for (int i = 0; i < list.size(); i++) {
			Schoolmanager schoolmanager = (Schoolmanager) list.get(i);
			baseDAO.removeEntity(schoolmanager);
		}
	}

	public void deleteSchoolManager(Schoolmanager schoolmanager) {
		baseDAO.removeEntity(schoolmanager);
	}

	public void saveCollegeManager(Collegemanager collegemanager) {
		log.debug("saving Collegemanager instance");
		baseDAO.saveEntity(collegemanager);

	}

	public void deleteCollegeManager(String collegeId) {
		log.debug("deleting Collegemanager instance");
		List list = baseDAO
				.findEntity("select college from Collegemanager college,Managermanagerrole managerrole "
						+ "where college.id.managerId=managerrole.id.managerId and college.id.collegeId='"
						+ collegeId + "' and managerrole.id.roleId='11' ");
		for (int i = 0; i < list.size(); i++) {
			Collegemanager collegemanager = (Collegemanager) list.get(i);
			baseDAO.removeEntity(collegemanager);
		}
	}

	public void deleteCollegeManager(Collegemanager collegemanager) {
		baseDAO.removeEntity(collegemanager);
	}

	public void saveClassManager(Classmanager classmanager) {
		log.debug("saving Classmanager instance");
		baseDAO.saveEntity(classmanager);
	}

	public void deleteClassAssitant(String classId) {
		log.debug("deleting Classmanager instance");
		List list = baseDAO
				.findEntity("select classes from Classmanager classes,Managermanagerrole managerrole "
						+ "where classes.id.managerId=managerrole.id.managerId and classes.id.classId='"
						+ classId + "' and managerrole.id.roleId='21' ");
		for (int i = 0; i < list.size(); i++) {
			Classmanager classmanager = (Classmanager) list.get(i);
			baseDAO.removeEntity(classmanager);
		}

	}

	public void deleteClassmanager(Classmanager classmanager) {
		baseDAO.removeEntity(classmanager);
	}

	public void deleteClassTutor(String classId) {
		log.debug("deleting Classmanager instance");
		List list = baseDAO
				.findEntity("select classes from Classmanager classes,Managermanagerrole managerrole "
						+ "where classes.id.managerId=managerrole.id.managerId and classes.id.classId='"
						+ classId + "' and managerrole.id.roleId='22' ");
		for (int i = 0; i < list.size(); i++) {
			Classmanager classmanager = (Classmanager) list.get(i);
			baseDAO.removeEntity(classmanager);
		}

	}

}