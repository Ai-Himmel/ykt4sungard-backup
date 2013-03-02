package org.king.yangong.dormitorymanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.classmanage.domain.ClassDorm;
import org.king.classmanage.domain.Schoolmanager;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.dao.YxGraduateDAO;
import org.king.yangong.dormitorymanage.domain.YxGraduate;

/**
 * Data access object (DAO) for domain model class yxGraduate.
 * 
 * @see org.king.yangong.dormitorymanage.dao.yxGraduate
 * @author MyEclipse - Hibernate Tools
 */
public class YxGraduateDAOHibernate implements YxGraduateDAO {

	private static final Log log = LogFactory
			.getLog(YxGraduateDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding yxGraduate instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding yxGraduate instance by query");
		return baseDAO.findEntity(query);
	}

	public YxGraduate get(Serializable id) {
		log.debug("getting yxGraduate instance by id");
		return (YxGraduate) baseDAO.getEntity(YxGraduate.class, id);
	}

	public List getAll() {
		log.debug("getting yxGraduate all");
		String allHql = "from yxGraduate";
		return baseDAO.findEntity(allHql);
	}

	public void save(YxGraduate transientInstance) {
		log.debug("saving yxGraduate instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(YxGraduate transientInstance) {
		log.debug("updating yxGraduate instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(YxGraduate persistentInstance) {
		log.debug("deleting yxGraduate instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public void deleteClassDorm(ClassDorm classdorm) {
		log.debug("deleting ClassDorm instance");
//		List list = baseDAO.findEntity("from ClassDorm where dormId='"
//				+ classdorm.getDormId() + "' and curYear='"+DateUtil.getNow("yyyy")+"'");
//		for (int i = 0; i < list.size(); i++) {
//			ClassDorm delcd = (ClassDorm) list.get(i);
//			baseDAO.removeEntity(delcd);
//		}
		baseDAO.removeEntity(classdorm);
	}
	
	public void saveClassDorm(ClassDorm classdorm){
		log.debug("saving ClassDorm instance");
		baseDAO.saveEntity(classdorm);		
	}
	
	public void updateClassDorm(ClassDorm classdorm){
		log.debug("saving ClassDorm instance");
		baseDAO.updateEntity(classdorm);		
	}

	public List getStudentTypeList() {
		String allHql = "from Dictionary where id.dictNo=15 and id.dictValue='D' or id.dictValue='M'";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getStyleList() {
		String allHql = "from Dictionary where id.dictNo=16";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getCollegeList() {
		String allHql = "from Department where deptLevel =0 and isAvailability='1'";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getCollegeListFromGraduateTable() {
		String allHql = "select distinct a from Department a,YxGraduate b where a.deptCode=b.curCollege";
		List list = baseDAO.findEntity(allHql);
		return list;
	}
	public List getMajorListFromGraduateTable() {
		String allHql = "select distinct new Map(a.id.dictValue as majorCode,a.dictCaption as majorName," +
				"b.curCollege as collegeCode) from Dictionary a,YxGraduate b where a.id.dictValue=b.speciality and a.id.dictNo=28";
		List list = baseDAO.findEntity(allHql);
		return list;
	}
	public List getDormitoryList(String stuemp_no) {
		String allHql = "select a from Dormitorymodel a,TabSsManager b where a.curDormDept=b.tabSsDept.id and b.stuNo='"
				+ stuemp_no + "' ";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getSpecialityList() {
		String allHql = "from Dictionary where id.dictNo=28";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getTypeList() {
		String allHql = "from GraduateType where ifdeleted = '1' ";
		List list = baseDAO.findEntity(allHql);
		return list;
	}
	
	public List getTabssdeptList(String stuemp_no) {
		String allHql = "select b.tabSsDept from TabSsManager b where b.stuNo='"+stuemp_no+"'";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getDistrictionList() {
		String allHql = "from Dictionary where id.dictNo=20";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getRequestavailableList() {
		String allHql = "from Dictionary where id.dictNo=19";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getSexList() {
		String allHql = "from Dictionary where id.dictNo=1 order by id.dictValue";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getSectionList() {
		String allHql = "from Dictionary where id.dictNo=17 order by dictSort";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getBuildingList() {
		String allHql = "from Dictionary where id.dictNo=21 order by dictSort";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getLayerList() {
		String allHql = "from Dictionary where id.dictNo=22";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

	public List getCellList() {
		String allHql = "from Dictionary where id.dictNo=23";
		List list = baseDAO.findEntity(allHql);
		return list;
	}

}