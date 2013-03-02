/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    QueryServiceImpl.java
 * 创建日期： 2007-7-6 13:28:53
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-7-6 13:28:53     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.summary.service.impl;

import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.transform.Transformers;
import org.king.common.dao.AllDAO;
import org.king.summary.service.IQueryService;
import org.king.summary.web.action.QueryInfo;
import org.springframework.orm.hibernate3.HibernateCallback;

public class QueryServiceImpl implements IQueryService {

	private AllDAO allDAO;
	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}
	
	//学号、姓名、性别、民族、国籍 录取院系、录取专业、学生类别（选择）
	//校区（8个汉字）、楼号（10个汉字）（选择）、单元号（10个汉字）、宿舍号（6位数字）
	//生日
	public int queryGraduateInfos(final List res, final QueryInfo condition,
			final int pageNo, final int pageSize) {
		

		Number count = (Number)allDAO.getHibernateTemplate().execute(new HibernateCallback(){

			
			/*
			 * select distinct g.GRADUATE_NO as col_0_0_, g.GRADUATE_NAME as col_1_0_, d1.DICT_CAPTION as col_2_0_, d2.DICT_CAPTION as col_3_0_, d3.DICT_CAPTION as col_4_0_, d0.DEPT_NAME as col_5_0_, d4.DICT_CAPTION as col_6_0_, d5.DICT_CAPTION as col_7_0_, d6.DICT_CAPTION as col_8_0_, d7.DICT_CAPTION as col_9_0_, d8.DICT_CAPTION as col_10_0_, d.UNIT as col_11_0_, d.ROOM_NUMBER as col_12_0_, g.BIRTHDAY as col_13_0_ */
				public Object doInHibernate(Session session) throws HibernateException, SQLException {
					
  StringBuffer sb = new StringBuffer( " from YKT_FM.YX_GRADUATE g left join YKT_FM.YX_DORMITORY d on (g.DORMITORY_ID=d.DORMITORY_ID) left join "+
  " YKT_FM.YX_DEPARTMENT d0 on (g.CUR_COLLEGE=d0.DEPT_CODE) left join "+ 
  " YKT_FM.YX_DICTIONARY d1 on (d1.DICT_NO=1 and g.SEX=d1.DICT_VALUE) left join "+ 
   " YKT_FM.YX_DICTIONARY d2  on (d2.DICT_NO=2 and g.NATION=d2.DICT_VALUE) "+ 
   " left join YKT_FM.YX_DICTIONARY d3  on (d3.DICT_NO=12 and g.NATIONALITY=d3.DICT_VALUE) "+ 
   " left join  YKT_FM.YX_DICTIONARY d4 on (d4.DICT_NO=28 and g.SPECIALITY=d4.DICT_VALUE) "+
    " left join YKT_FM.YX_DICTIONARY d5  on(d5.DICT_NO=15 and g.STUDENT_TYPE=d5.DICT_VALUE) "+
	" left join YKT_FM.YX_DICTIONARY d6 on (d6.DICT_NO=17 and d.AREA=d6.DICT_VALUE ) "+ 
	" left join YKT_FM.YX_DICTIONARY d7  on (d7.DICT_NO=20 and d.LOCATION=d7.DICT_VALUE ) "+ 
	" left join YKT_FM.YX_DICTIONARY d8 on ( d8.DICT_NO=21 and d.DORMITORY=d8.DICT_VALUE ) where g.ENROLL_YEAR=:curYear  ");
					/*StringBuffer sb = new StringBuffer(
							" from YxGraduate g,Dormitorymodel d," +
							" Department d0, Dictionary d1, Dictionary d2,Dictionary d3,Dictionary d4,Dictionary d5," +
							" Dictionary d6, Dictionary d7,Dictionary d8 " +
							" where g.dormitoryId=d.dormitoryId  and g.curCollege= d0.deptCode " +
							" and d1.id.dictNo=1 and g.sex=d1.id.dictValue " +
							" and d2.id.dictNo=2 and g.nation=d2.id.dictValue " +
							" and (d3.id.dictNo=12 and g.nationality=d3.id.dictValue or g.nationality is null)" +
							" and d4.id.dictNo=28 and g.speciality=d4.id.dictValue " +
							" and d5.id.dictNo=15 and g.studentType=d5.id.dictValue " +
							" and d6.id.dictNo=17 and d.area=d6.id.dictValue " +
							" and d7.id.dictNo=20 and d.location=d7.id.dictValue " +
							" and d8.id.dictNo=21 and d.dormitory=d8.id.dictValue " );*/
  					Date now = new Date();
  					SimpleDateFormat sdf = new SimpleDateFormat("yyyy");
				    Map params = new HashMap();
				    params.put("curYear",sdf.format(now));
					if (condition != null) {
						if (condition.getStuNo() != null && !condition.getStuNo().trim().equals("")) {
							sb.append(" and g.graduate_no like :stuNo");
							params.put("stuNo","%"+condition.getStuNo().trim()+"%");
						}
						if (condition.getStuName() != null && !condition.getStuName().trim().equals("")) {
							sb.append(" and g.graduate_name like :stuName");
							params.put("stuName","%"+condition.getStuName().trim()+"%");
						}
						if (condition.getGuoJi() != null && !condition.getGuoJi().trim().equals("")) {
							sb.append(" and g.nationality =:guoJi");
							params.put("guoJi",condition.getStuNo().trim());
						}
						if (condition.getMinZu() != null && !condition.getMinZu().trim().equals("")) {
							sb.append(" and g.nation =:minZu");
							params.put("minZu",condition.getMinZu().trim());
						}
						if (condition.getSex() != null && !condition.getSex().trim().equals("")) {
							sb.append(" and g.sex =:sex");
							params.put("sex",condition.getSex().trim());
						}
						if (condition.getYuanXi() != null && !condition.getYuanXi().trim().equals("")) {
							sb.append(" and g.cur_college =:yunXi");
							params.put("yunXi",condition.getYuanXi().trim());
						}
						if (condition.getZhuanYe() != null && !condition.getZhuanYe().trim().equals("")) {
							sb.append(" and g.speciality =:zhuanYe");
							params.put("zhuanYe",condition.getZhuanYe().trim());
						}
						if (condition.getLeiBie() != null && !condition.getLeiBie().trim().equals("")) {
							sb.append(" and g.student_type =:leiBie");
							params.put("leiBie",condition.getLeiBie().trim());
						}
						if (condition.getArea() != null && !condition.getArea().trim().equals("")) {
							sb.append(" and d.area =:area");
							params.put("area",condition.getArea().trim());
						}
						if (condition.getLocation() != null && !condition.getLocation().trim().equals("")) {
							sb.append(" and d.location =:location");
							params.put("location",condition.getLocation().trim());
						}
						if (condition.getLouHao() != null && !condition.getLouHao().trim().equals("")) {
							sb.append(" and d.dormitory =:louHao");
							params.put("louHao",condition.getLouHao().trim());
						}
						if (condition.getUnit() != null && !condition.getUnit().trim().equals("")) {
							sb.append(" and d.unit like :unit");
							params.put("unit","%"+condition.getUnit().trim()+"%");
						}
						if (condition.getRoomNumber() != null && !condition.getRoomNumber().trim().equals("")) {
							sb.append(" and d.room_number =:louHao");
							params.put("louHao","%"+condition.getRoomNumber().trim()+"%");
						}	
				}
					/*Query query = session.createQuery("select distinct new Map(g.graduateNo as stuNo,g.graduateName as stuName," +
							" d1.dictCaption as sex,d2.dictCaption as minZu,d3.dictCaption as guoJi," +
							" d0.deptName as yuanXi," +
							" d4.dictCaption as zhuanYe,d5.dictCaption as leiBie,d6.dictCaption as area," +
							" d7.dictCaption as location,d8.dictCaption as louHao," +
							" d.unit as unit,d.roomNumber as roomNumber,g.birthday as birthday) " +sb.toString());*/
					Query query = session.createSQLQuery("select distinct g.GRADUATE_NO as stuNo, " +
							"g.GRADUATE_NAME as stuName, d1.DICT_CAPTION as sex," +
							" d2.DICT_CAPTION as minZu, " +
							"d3.DICT_CAPTION as guoJi," +
							" d0.DEPT_NAME as yuanXi, " +
							"d4.DICT_CAPTION as zhuanYe, " +
							"d5.DICT_CAPTION as leiBie, " +
							"d6.DICT_CAPTION as area," +
							" d7.DICT_CAPTION as location, d8.DICT_CAPTION as louHao, " +
							"d.UNIT as unit, d.ROOM_NUMBER as roomNumber," +
							" g.BIRTHDAY as birthday "+sb.toString()+" order by g.GRADUATE_NO ");
					query.setResultTransformer(Transformers.ALIAS_TO_ENTITY_MAP);
					Iterator it = params.entrySet().iterator();
					while (it.hasNext()){
						Map.Entry e = (Map.Entry)it.next();
						String key = (String)e.getKey();
						Object value = e.getValue();
						query.setParameter(key,value);
					}
					query.setMaxResults(pageSize);
					query.setFirstResult((pageNo-1)*pageSize);
					List temp = query.list();
					res.addAll(temp);
					//总数量
					 query = session.createSQLQuery("select distinct  count(*) " +sb.toString());
					 it = params.entrySet().iterator();
					while (it.hasNext()){
						Map.Entry e = (Map.Entry)it.next();
						String key = (String)e.getKey();
						Object value = e.getValue();
						query.setParameter(key,value);
					}
					
					Number count =  (Number)query.uniqueResult();
					
				return count;
			}});
		
		return count.intValue();
	}

}
