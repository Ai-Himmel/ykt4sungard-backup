package org.king.check.service.impl;

import java.io.Serializable;
import java.util.Calendar;
import java.util.Iterator;
import java.util.List;
import java.util.Map;


import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.config.CommonConfig;
import org.king.check.dao.DepartmentDAO;
import org.king.check.dao.VacationDao;
import org.king.check.domain.Department;
import org.king.check.domain.Vacation;
import org.king.check.service.VacationService;
import org.springframework.jdbc.core.JdbcTemplate;

public class VacationServiceImpl implements VacationService{
	 private static final Log log = LogFactory.getLog(VacationServiceImpl.class);
	
	private VacationDao vacationDao;
	
	private JdbcTemplate jdbcTemplate;
	
    private DepartmentDAO departmentDAO;
	
	
	public void setDepartmentDAO(DepartmentDAO departmentDAO) {
		this.departmentDAO = departmentDAO;
	}
	
    public void setVacationDao(VacationDao vacationDao) {
		this.vacationDao = vacationDao;
	}
    
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	public void save(Vacation vacation)throws Exception
    {
		vacationDao.save(vacation);
    }
	public List getAll()
	{
		return vacationDao.getAll();
	}
	
	public void delete(Vacation vacation)throws Exception
	{
		vacationDao.delete(vacation);
	}
	
	public Vacation get(Serializable id)throws Exception
	{
		return vacationDao.get(id);
	}
	/*
	 *  (non-Javadoc)
	 * @see org.king.check.service.VacationService#isGlobeVacation()
	 * 判断是否为公共休息日
	 */
	public boolean isGlobeVacation(Calendar cal)throws Exception
	{
		Calendar calendar= cal;//Calendar.getInstance();
		String nowDay=Integer.toString(calendar.get(Calendar.MONTH)+1)+Integer.toString(calendar.get(Calendar.DAY_OF_MONTH));
		/*String hql="from Vacation vacation where vacation.isglobe='"+CommonConfig.isGlobe+"'";
		log.debug("globe nowDay:"+nowDay);
		List allVacations=vacationDao.find(hql);
		if(!allVacations.isEmpty()){
			Iterator ite=allVacations.iterator();
			while(ite.hasNext())
			{
				Vacation vacation=(Vacation)ite.next();
				if((new Integer(vacation.getEnddate())).intValue()>=Integer.parseInt(nowDay)&&(new Integer(vacation.getStartdate())).intValue()<=Integer.parseInt(nowDay))
				{
					log.debug(nowDay+"is golbe vacation");
					return true;
				}
			}
		}*/
		int DAY_OF_WEEK=calendar.get(Calendar.DAY_OF_WEEK);
		log.debug("DAY_OF_WEEK:"+DAY_OF_WEEK);
		if(DAY_OF_WEEK==Calendar.SUNDAY||DAY_OF_WEEK==Calendar.SATURDAY)//判断是否为周末
		{
			log.debug(nowDay+"is vacation");
			return true;
		}
		return false;
	}
	public List searchByFilter(Map filter)throws Exception
	{
		String sql=" select va.ID as vid,va.VACTIONALNAME as vname ,va.STARTDATE as startdate," +
				" va.ENDDATE as enddate ,depart.DEPT_NAME as dname" +
				" from YKT_CK.VACATION va,YKT_CK.DEPARTMENT depart where va.DEPARTID=depart.DEPT_ID ";
		sql+=StringUtils.isNotEmpty((String)filter.get("vacationName"))?" and va.VACTIONALNAME like '%"+(String)filter.get("vacationName")+"%' ":"";
		sql+=" group by depart.DEPT_NAME, va.VACTIONALNAME,va.STARTDATE,va.ENDDATE,va.ID ";
		sql+=" order by va.STARTDATE asc ";
		
		List resList=jdbcTemplate.queryForList(sql);
		if(!resList.isEmpty())
		{
			Iterator Ite=resList.iterator();
			while(Ite.hasNext())
			{
				Map temp=(Map)Ite.next();
				String startdate=(String)temp.get("startdate");
				String modify=startdate.substring(0,2)+"月"+startdate.substring(2)+"日";//修改成容易辩识的
				temp.put("startdate",modify);
				
				String enddate=(String)temp.get("enddate");
				modify=enddate.substring(0,2)+"月"+enddate.substring(2)+"日";
				temp.put("enddate",modify);
			}
			
		}
		return resList;
	}
	public void update(Vacation vacation)
	{
		vacationDao.update(vacation);
	}
	/*
	 *  (non-Javadoc)
	 * @see org.king.check.service.VacationService#isDepartVacation(java.lang.String)
	 * 判断是否为部门的休息日
	 */
	public boolean isDepartVacation(String departId,Calendar cal)throws Exception
	{
		Calendar calendar= cal;//Calendar.getInstance();
		String nowDay=Integer.toString(calendar.get(Calendar.MONTH)+1)+Integer.toString(calendar.get(Calendar.DAY_OF_MONTH));		
		Department department=departmentDAO.get(departId);
		log.debug("nowDay:"+nowDay);
		while(department!=null)
		{
			String hql="from Vacation vacation where vacation.departid='"+department.getId()+"'";
			List allVacations=vacationDao.find(hql);
		    //判断部门休息日
		    if(!allVacations.isEmpty()){
			    Iterator ite=allVacations.iterator();
			    while(ite.hasNext())
			   {
				   Vacation vacation=(Vacation)ite.next();
				   if((new Integer(vacation.getEnddate())).intValue()>=Integer.parseInt(nowDay)&&(new Integer(vacation.getStartdate())).intValue()<=Integer.parseInt(nowDay))
				   {
					   log.debug(nowDay+"is depart vacation");
					   return true;
				   }
			   }
		     }
		    department=department.getParent();
		}
		return false;
	}
	public List getVacationsByDeptId(String departId)throws Exception
	{
		List vacationList;
		String hql="from Vacation vacation where vacation.departid='"+departId+"'";
		vacationList=vacationDao.find(hql);
		return vacationList;
	}
	public List getGlobeVacation()throws Exception
	{
		List vacationList;
		String hql="from Vacation vacation where vacation.isglobe='"+CommonConfig.isGlobe+"'";
		vacationList=vacationDao.find(hql);
		return vacationList;
	}
}
