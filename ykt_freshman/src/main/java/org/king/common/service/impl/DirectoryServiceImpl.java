/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    DirectoryServiceImpl.java
 * 创建日期： 2007-6-12 14:53:17
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-12 14:53:17     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.common.service.impl;

import java.util.List;

import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.DictionaryId;
import org.king.common.dao.AllDAO;
import org.king.common.service.IDirectoryService;

public class DirectoryServiceImpl implements IDirectoryService {

	private AllDAO allDAO;
	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}

	/* (non-Javadoc)
	 * @see org.king.common.service.IDirectoryService#getLocations()
	 */
	private List getDirections(int type){
		return allDAO.getHibernateTemplate().findByNamedParam("select new Map(d.dictCaption as name,d.id.dictValue as id) from Dictionary d where d.id.dictNo=:no order by d.dictSort asc",
				"no", new Integer(type));
	}
	private List getDirections(int type,String pId){
		return allDAO.getHibernateTemplate().findByNamedParam("select new Map(d.dictCaption as name,d.id.dictValue as id) from Dictionary d where d.id.dictNo=:no and d.dictParent=:pId order by d.dictSort asc",
				new String[]{"no","pId"}, new Object[]{new Integer(type),pId});
	}
	
	public List getAreas() {
		return this.getDirections(17);
	}

	/* (non-Javadoc)
	 * @see org.king.common.service.IDirectoryService#getAreas(java.lang.String)
	 */
	public List getLocations(String id) {
		return this.getDirections(20,id);
	}

	/* (non-Javadoc)
	 * @see org.king.common.service.IDirectoryService#getDormitory(java.lang.String)
	 */
	public List getDormitory(String id) {
		return this.getDirections(21,id);
	}

	public List getSexs() {
		return this.getDirections(1);
	}
	
	private String getDirectoryName(int no,String id) {
		
		DictionaryId dId = new DictionaryId();
		dId.setDictNo(new Integer(no));
		dId.setDictValue(id);
		Dictionary d = (Dictionary)allDAO.getHibernateTemplate().get(Dictionary.class,dId);
		if (d == null)return null;
		return d.getDictCaption();
		
	}

	public String getLocationName(String id) {
		// TODO Auto-generated method stub
		return getDirectoryName(20,id);
	}

	public String getAreaName(String id) {
		// TODO Auto-generated method stub
		return getDirectoryName(17,id);
	}

	public String getDormitoryName(String id) {
		// TODO Auto-generated method stub
		return getDirectoryName(21,id);
	}

	public String getSexName(String id) {
		// TODO Auto-generated method stub
		return getDirectoryName(1,id);
	}

	public List getLevels() {
		// TODO Auto-generated method stub
		return this.getDirections(22);
	}

	public List getDirections() {
		// TODO Auto-generated method stub
		return this.getDirections(24);
	}

	public String getLevelName(String id) {
		// TODO Auto-generated method stub
		return getDirectoryName(22,id);
	}

	public String getDirectionName(String id) {
		// TODO Auto-generated method stub
		return getDirectoryName(24,id);
	}

	

	public List getMajors(String id) {
		// TODO Auto-generated method stub
		return this.getDirections(11,id);
	}

	public List getGraduateMajors() {
		// TODO Auto-generated method stub
		return this.getDirections(28);
	}

	public List getGraduateDepartments() {
		// TODO Auto-generated method stub
		return allDAO.getHibernateTemplate().find("select new Map(d.deptCode as id,d.deptName as name) from Department d where d.gdisplay='1'");
		
		
	}

	public List getStudentTypes() {
		// TODO Auto-generated method stub
		//为研究生类型
		return allDAO.getHibernateTemplate().find("select new Map(d.dictCaption as name,d.id.dictValue as id) from Dictionary d " +
				" where d.id.dictNo=15 and d.id.dictValue in ('D','M') order by d.dictSort asc");
		//return this.getDirections(15);
	}

	public List getNations() {
		// TODO Auto-generated method stub
		return this.getDirections(2);
	}

	public List getNationalitys() {
		// TODO Auto-generated method stub
		return this.getDirections(12);
	}

}
