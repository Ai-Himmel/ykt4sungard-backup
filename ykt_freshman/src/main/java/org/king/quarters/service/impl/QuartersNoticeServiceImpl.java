/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    QuartersNoticeServiceImpl.java
 * 创建日期： 2007-6-14 10:19:35
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-14 10:19:35     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.service.impl;

import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.common.dao.AllDAO;
import org.king.quarters.domain.TabSsDept;
import org.king.quarters.service.IQuartersNoticeService;
import org.king.quarters.service.IQuartersService;
import org.king.quarters.service.NoticeInfo;
import org.king.utils.DateUtil;
import org.springframework.orm.hibernate3.HibernateCallback;

public class QuartersNoticeServiceImpl implements IQuartersNoticeService {
	private AllDAO allDAO;
	private IQuartersService quartersService;

	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}

	public void setQuartersService(IQuartersService quartersService) {
		this.quartersService = quartersService;
	}

	/*
	 * 0:没有权限
	 * 1:护理学院
	 * 2:复旦学院
	 * 3:研究生
	 */
	public int getDataRight(String uId){
		TabSsDept dept = quartersService.getManageDept(uId);
		if (dept == null) return 0;
		 dept.getRight();
		 return 3;
	}
	public List getNoticeDataSource(String uId, List stuIds) {
		int right = this.getDataRight(uId);;
		if (right == 0) return null;
		List l = null;
		if (right == 3){
			 l = this.generateJiaoKuanNoticeFromGraduate(stuIds);
		}
		
		return l;
	}
	
	//从研究生处获取数据
	private List generateJiaoKuanNoticeFromGraduate(List stuIds){
		if (stuIds == null || stuIds.isEmpty()) return null;
		String curYear=DateUtil.getNow("yyyy");
		int icurYear=Integer.parseInt(curYear);
		StringBuffer sb = 
			new StringBuffer("select  new org.king.quarters.service.NoticeInfo(g.id,g.graduateNo," +
						"g.graduateName,d3.dictCaption,d.unit,d.roomNumber,d.fee," +
						" g.lengthofschool,d5.deptName,d4.dictCaption,d2.dictCaption,d1.dictCaption,g.enrollYear) " +
						" from YxGraduate g,Dormitorymodel d,Dictionary d1," +
						"Dictionary d2,Dictionary d3,Dictionary d4,Department d5  " +
						" where g.id in (:stuIds) " +
						" and g.dormitoryId = d.dormitoryId  " +
						" and  (d.area=d1.id.dictValue and d1.id.dictNo=17) " +
						" and (d.location=d2.id.dictValue and d2.id.dictNo=20) " +
						" and (d.dormitory=d3.id.dictValue and d3.id.dictNo=21) " +
						" and (g.curCollege=d5.deptCode)" +
						" and (g.speciality=d4.id.dictValue and d4.id.dictNo=28) " +
						" order by d.area,d.location,d.dormitory,d.unit,d.roomNumber");
		List li=allDAO.getHibernateTemplate().findByNamedParam(sb.toString(),"stuIds",stuIds);
		if(li!=null&&li.size()>0){
			for(int i=0;i<li.size();i++){
				NoticeInfo ni=(NoticeInfo)li.get(i);
				String dormitory=ni.getDormitory();
				int pos=dormitory.indexOf("号楼");
				if(pos!=-1)
					dormitory=dormitory.substring(0,pos);
				ni.setDormitory(dormitory);
				String endyear=ni.getEndyear();
				if(ni.getGrade()!=null){
					int grade=(ni.getGrade()).intValue();
					int ey=icurYear+grade;
					endyear=String.valueOf(ey);
				}
				ni.setEndyear(endyear);
			}
		}
		return li;
	}

	public int searchStudents(List res,String uId,NoticeInfo con,int pageNo,int pageSize){
		// TODO Auto-generated method stub
		int code = getDataRight(uId);
		if (code == 0 ) return 0;
		TabSsDept dept = quartersService.getManageDept(uId);
		//
		if (code == 3){
			return searchGraduateStudents(res,dept.getId(),con,pageNo,pageSize);
		}
		return 0;
	}
	/*
	 * id;
	stuNo;
	name;
	dormitory;
	unit;
	roomNuber;
	fee;
	noticeDate;
	yearLimit;
	grade;
	college;
	majors ;
	location;
	area;
	 */
	private int searchGraduateStudents(List res,final String deptId,final NoticeInfo con,final int pageNo,final int  pageSize){
		if (res == null) return 0;
		if (deptId == null) return 0;
		Object[] os = (Object[])allDAO.getHibernateTemplate().execute(new HibernateCallback(){
			public Object doInHibernate(Session session) throws HibernateException, SQLException {
				StringBuffer sb = new StringBuffer(" " +
						" from YxGraduate g,Dormitorymodel d,Dictionary d1," +
						"Dictionary d2,Dictionary d3,Dictionary d4,Department d5  " +
						" where d.curDormDept =:deptId " +
						" and g.dormitoryId = d.dormitoryId  " +
						" and  (d.area=d1.id.dictValue and d1.id.dictNo=17) " +
						" and (d.location=d2.id.dictValue and d2.id.dictNo=20) " +
						" and (d.dormitory=d3.id.dictValue and d3.id.dictNo=21) " +
						" and (g.curCollege=d5.deptCode)" +
						" and (g.speciality=d4.id.dictValue and d4.id.dictNo=28) " +
						" and g.enrollYear =:enrollYear");
				Date now = new Date();
				SimpleDateFormat sdf = new SimpleDateFormat("yyyy");
				Map params= new HashMap();
				params.put("enrollYear", sdf.format(now));
				if (con != null){
					if (StringUtils.isNotEmpty(con.getArea())){
						sb.append(" and d.area=:area");
						params.put("area",con.getArea());
					}
					if (StringUtils.isNotEmpty(con.getLocation())){
						sb.append(" and d.location=:location");
						params.put("location",con.getLocation());
					}
					if (StringUtils.isNotEmpty(con.getDormitory())){
						sb.append(" and d.dormitory=:dormitory");
						params.put("dormitory",con.getDormitory());
					}
					if (StringUtils.isNotEmpty(con.getUnit())){
						sb.append(" and d.unit=:unit");
						params.put("unit",con.getUnit());
					}
					if (StringUtils.isNotEmpty(con.getRoomNumber())){
						sb.append(" and d.roomNuber=:roomNuber");
						params.put("roomNuber",con.getRoomNumber());
					}
					
					if (StringUtils.isNotEmpty(con.getCollege())){
						sb.append(" and g.curCollege=:college");
						params.put("college",con.getCollege());
					}
					if (StringUtils.isNotEmpty(con.getMajors())){
						sb.append(" and g.speciality=:majors");
						params.put("majors",con.getMajors());
					}
					
					if (StringUtils.isNotEmpty(con.getName())){
						sb.append(" and g.graduateName=:name");
						params.put("name",con.getName());
					}if (StringUtils.isNotEmpty(con.getStuNo())){
						sb.append(" and g.graduateNo=:stuNo");
						params.put("stuNo",con.getStuNo());
					}
					
					
				}
				Query query = session.createQuery("select  new org.king.quarters.service.NoticeInfo(g.id,g.graduateNo," +
						"g.graduateName,d3.dictCaption,d.unit,d.roomNumber,d.fee," +
						" g.lengthofschool,d5.deptName,d4.dictCaption,d2.dictCaption,d1.dictCaption,g.enrollYear) "+sb.toString()+
						" order by d.area asc,d.location,d.dormitory,d.unit,d.roomNumber ");
				query.setParameter("deptId",deptId);
				Iterator it = params.entrySet().iterator();
				while (it.hasNext()){
					Map.Entry e = (Map.Entry)it.next();
					query.setParameter((String)e.getKey(),e.getValue());
				}
				query.setMaxResults(pageSize);
				query.setFirstResult((pageNo-1)*pageSize);
				List res = query.list();
				//
				query = session.createQuery(" select distinct count(*) "+sb.toString());
				query.setParameter("deptId",deptId);
			    it = params.entrySet().iterator();
				while (it.hasNext()){
					Map.Entry e = (Map.Entry)it.next();
					query.setParameter((String)e.getKey(),e.getValue());
				}
				Number count = (Number)query.uniqueResult();
				return new Object[]{res,count};
			}
			
		});
		res.addAll((List)os[0]);
		return ((Number)os[1]).intValue();
	}

	
	
}
