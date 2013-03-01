package com.kingstargroup.advquery.hibernate.dao;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.fee.TTifRegisterPayLog;
import com.kingstargroup.advquery.register.dto.Register;
import com.kingstargroup.advquery.register.hibernate.TTifRegistration;
import com.kingstargroup.advquery.register.hibernate.TTifRegistrationId;

public class RegisterDAO extends BasicDAO {

	private static RegisterDAO _instance;

	public static RegisterDAO getInstance() {
		if (_instance == null) {
			return new RegisterDAO();
		}
		return _instance;
	}

	// public

	public List getResisterInfo(String regId, String custId) {

		try {
			Session s = getSession();
			String sql = " select new Map(r.id.custId as custId, r.id.regId as regId ,r.comments as  comments ) from TTifRegistration r"
					+ " where  r.id.regId=:regId and r.id.custId =:custId";
			Query q = s.createQuery(sql);
			q.setLong("regId", Long.parseLong(regId));
			q.setLong("custId", Long.parseLong(custId));

			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return new ArrayList();
		}
	}

	public boolean updateResisterInfo(String regId, String custId,
			String comments) {
		try {
			Session s = getSession();
			String sql = " from  TTifRegistration r  where  r.id.regId=:regId and r.id.custId =:custId";
			Query q = s.createQuery(sql);
			q.setLong("regId", Long.parseLong(regId));
			q.setLong("custId", Long.parseLong(custId));
			List list = q.list();
			TTifRegistration reg = (TTifRegistration) list.get(0);
			reg.setComments(comments);
			s.saveOrUpdate(reg);
			s.flush();
			return true;
		} catch (HibernateException he) {
			_log.error(he);
			return false;
		}

	}

	public boolean updateReserverByStuempNo(String stuempNo, String optDate,
			String optTime, String comments) throws HibernateException {
		Session s = getSession();
		try {
			String sql = " from TTifRegisterPayLog  g  where g.id.stuempNo=:stuempNo  and  g.id.operateDate=:optDate "
					+ " and g.id.operateTime=:optTime";
			Query q = s.createQuery(sql);
			q.setString("stuempNo", stuempNo);
			q.setString("optDate", optDate);
			q.setString("optTime", optTime);
			List list = q.list();
			TTifRegisterPayLog pl = (TTifRegisterPayLog) list.get(0);
			pl.setComments(comments);
			s.saveOrUpdate(pl);
			s.flush();
			return true;
		} catch (HibernateException he) {
			_log.error(he);
			return false;
		}
	}

	// 查询学生备注信息
	public List getReserverByStuempNo(String stuempNo, String optDate,
			String optTime) throws HibernateException {

		Session s = getSession();
		try {
			StringBuffer sql = new StringBuffer(
					" select  r.stuemp_no stuempNo,cut.cut_name cutName ,r.register_info regInfo ,")
					.append(" r.operate_date optDate ,r.operate_time opeTime ,")
					.append(
							" r.comments comments from ykt_cur.t_tif_register_pay_log  r,ykt_cur.t_cif_customer cut")
					.append(
							" where r.stuemp_no = cut.stuemp_no and  r.stuemp_No='"
									+ stuempNo + "'").append(
							" and r.operate_date ='" + optDate + "'").append(
							" and r.operate_time ='" + optTime + "'");
			SQLQuery q = s.createSQLQuery(sql.toString());
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("regInfo", Hibernate.STRING);
			q.addScalar("optDate", Hibernate.STRING);
			q.addScalar("opeTime", Hibernate.STRING);
			q.addScalar("comments", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return new ArrayList();
		}

	}

	// 取得注册查询结果
	public List getRegisterQueryResult(Register reg) throws HibernateException {
		try {
			String begindate = reg.getBegindate();
			String enddate = reg.getEnddate();
			String classroom = reg.getClassroom();
			String dept = reg.getDept();
			String stuempNo = reg.getStuempNo();
			String name = reg.getName();
			String degree = reg.getDegree();
			String scode = reg.getScode();
			String feeType = reg.getFeeType();
			String term = reg.getTerm();
			String isCome = reg.getIsCome();

			SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
			if ("".equals(enddate)) {
				enddate = dateFormat.format(new Date());
			} else {
				enddate = DateUtil.reFormatTime(enddate);
			}

			Session s = getSession();

			StringBuffer sql = new StringBuffer(
					"select  reg.reg_id regId ,reg.cust_id  custId , reg.tx_date txDate ,cut.stuemp_no stuempNo ,cut.cut_name cutName, ")
					.append(" s.s_name  Sname, ctf.type_name typeName ,")
					.append(
							" dept.dept_name deptName ,cut.class_no classNo ,fee.fee_name  feeName")
					.append(
							" ,term.schoolterm_name  termName, reg.comments comments ")
					.append(" from ( ")
					.append(
							" select reg_id,  cust_id , min(tx_date) tx_date ,reg_flag,comments  from t_tif_registration ")
					.append(
							" group by reg_id, cust_id ,reg_flag,comments ) reg ")
					.append(
							" inner join ykt_cur.t_tif_register_schoolterm term on term.reg_id =reg.reg_id ");

			if (!"".equals(term)) {
				sql.append(" and term.reg_id in (" + term + ")");
			}
			if (!"".equals(begindate)) {
				sql.append(" and tx_date >='"
						+ DateUtil.reFormatTime(begindate)
						+ "' and tx_date <='" + enddate + "'");
			}
			sql
					.append(
							" inner join   ykt_cur.t_cif_customer cut on cut.cut_id = reg.cust_id ")
					.append(
							" left join ykt_cur.t_cif_dept dept  on dept.dept_code = cut.classdept_no ")
					.append(
							" left join ykt_cur.t_cif_speciality s on s.s_code = cut.s_code ")
					.append(
							" left join ykt_cur.t_cif_cuttypefee ctf on  ctf.cut_type =cut.cut_type")
					.append(
							" left join ykt_cur.t_pif_feetype fee  on fee.fee_type =cut.fee_type  ")

					.append(" where 1=1 and  cut.at_school=1 ");

			if (!"".equals(classroom)) {
				sql.append(" and cut.class_no ='" + classroom + "'");
			}
			if (!"".equals(dept)) {
				sql.append(" and  cut.classdept_no  ='" + dept + "'");
			}
			if (!"".equals(stuempNo)) {
				sql.append(" and  cut.stuemp_no ='" + stuempNo + "'");
			}
			if (!"".equals(name)) {
				sql.append(" and cut.cut_name ='" + name + "'");
			}
			if (!"".equals(degree)) {
				sql.append(" and cut.cut_type = '" + degree + "'");
			}
			if (!"".equals(scode)) {
				sql.append(" and cut.s_code = '" + scode + "'");
			}
			if (!"".equals(feeType)) {
				sql.append(" and cut.fee_type = '" + feeType + "'");
			}
			if (!"".equals(isCome)) {
				sql.append(" and reg.reg_flag =" + isCome);
			}
			sql.append("order by termName desc");
			SQLQuery q = s.createSQLQuery(sql.toString());
			q.addScalar("regId", Hibernate.INTEGER);
			q.addScalar("custId", Hibernate.INTEGER);
			q.addScalar("txDate", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("Sname", Hibernate.STRING);
			q.addScalar("typeName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("classNo", Hibernate.STRING);
			q.addScalar("feeName", Hibernate.STRING);
			q.addScalar("regId", Hibernate.STRING);
			q.addScalar("termName", Hibernate.STRING);
			q.addScalar("comments", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return new ArrayList();
		} catch (Exception he) {
			_log.error(he);
			return new ArrayList();
		}
	}
	
//	 取得注册查询结果
	public List getRegisterComeQueryResult(Register reg) throws HibernateException {
		try {
		/*	String begindate = reg.getBegindate();
			String enddate = reg.getEnddate();*/
			String classroom = reg.getClassroom();
			String dept = reg.getDept();
			String stuempNo = reg.getStuempNo();
			String name = reg.getName();
			String degree = reg.getDegree();
			String scode = reg.getScode();
			String feeType = reg.getFeeType();
			String term = reg.getTerm();
			String isCome = reg.getIsCome();

			/*SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
			if ("".equals(enddate)) {
				enddate = dateFormat.format(new Date());
			} else {
				enddate = DateUtil.reFormatTime(enddate);
			}*/

			Session s = getSession();

			StringBuffer sql = new StringBuffer("");
			sql.append(" select w.reg_id regId,w.cust_id custId,w.reg_flag regflag,w.stuemp_no stuempNo,w.cut_name cutName,w.dept_code deptCode,w.dept_name deptName ,")
			   .append(" w.s_code Scode ,w.s_name Sname,w.type_name typeName ,w.class_no classNo ,w.termname termName,w.register register,w.cut_type cutType ") 
			   .append(" from (select reg.* ,term.schoolterm_name  termName, ")
			   .append(" (case when  reg.reg_flag=1 and(p.register_flag=1 or p.register_flag=2 or p.register_flag=4) then 1 else 0 end ) register ")
			   .append("  from ( ")
			   .append(" select  reg_id,  cust_id ,reg_flag ,c.stuemp_no,c.cut_name,dept.dept_name,dept.dept_code ,ctf.type_name  , s.s_name ,c.class_no ,c.cut_type,c.s_code ")
			   .append(" from t_tif_registration r  ")
			   .append(" left join t_cif_customer c ")
			   .append(" on  r.cust_id = c.cut_id ")
			   .append(" left join ykt_cur.t_cif_dept dept  on dept.dept_code = c.classdept_no ")
			   .append(" left join ykt_cur.t_cif_cuttypefee ctf on  ctf.cut_type =c.cut_type ")
			   .append("  left join ykt_cur.t_cif_speciality s on s.s_code = c.s_code  ")
			   .append(" where 1=1 ")
			   .append("  ) reg ")
			   .append("  left join  t_tif_register_pay p ")
			   .append("  on p.stuemp_no = reg.stuemp_no ")
			   .append("  inner join ykt_cur.t_tif_register_schoolterm term on term.reg_id =reg.reg_id ")
			   .append("  ) w ") 
			   .append(" where 1=1 ");
			if (!"".equals(classroom)) {
				sql.append(" and w.class_No ='" + classroom + "'");
			}
			if (!"".equals(dept)) {
				sql.append(" and  w.dept_Code  ='" + dept + "'");
			}
			if (!"".equals(stuempNo)) {
				sql.append(" and  w.stuemp_No ='" + stuempNo + "'");
			}
			if (!"".equals(name)) {
				sql.append(" and w.cut_Name ='" + name + "'");
			}
			if (!"".equals(degree)) {
				sql.append(" and w.cut_Type = '" + degree + "'");
			}
			if (!"".equals(scode)) {
				sql.append(" and w.S_code = '" + scode + "'");
			}
			if (!"".equals(isCome)) {
				sql.append(" and w.register =" + isCome);
			}
			if(!"".equals("term")){
				sql.append(" and w.reg_id in (" + term + ")");
			}
			
			SQLQuery q = s.createSQLQuery(sql.toString());
			q.addScalar("regId", Hibernate.INTEGER);
			q.addScalar("custId", Hibernate.INTEGER);
			q.addScalar("regflag",Hibernate.INTEGER);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("deptCode",Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("Scode",Hibernate.STRING);
			q.addScalar("Sname", Hibernate.STRING);
			q.addScalar("typeName", Hibernate.STRING);
			q.addScalar("classNo", Hibernate.STRING);
			q.addScalar("termName",Hibernate.STRING);
			q.addScalar("register", Hibernate.STRING);
			q.addScalar("cutType",Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return new ArrayList();
		} catch (Exception he) {
			_log.error(he);
			return new ArrayList();
		}

	}

	// 得到注册报表
	public List getRegisterReport(Register reg) throws HibernateException {
		try {
			/*
			 * String begindate = reg.getBegindate(); String enddate =
			 * reg.getEnddate();
			 */
			String classroom = reg.getClassroom();
			String dept = reg.getDept();
			/*
			 * SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
			 * if ("".equals(enddate)) { enddate = dateFormat.format(new
			 * Date()); } else { enddate = DateUtil.reFormatTime(enddate); }
			 */
			String term = reg.getTerm();
			Session s = getSession();
			StringBuffer sql = new StringBuffer(
					"select  decode(grouping(tt.schoolterm_name),'1','汇总',tt.schoolterm_name) term,")
					.append(
							" decode(grouping(tt.dept_name),'1','学期汇总',tt.dept_name) deptname, ")
					.append(
							" decode(grouping(tt.class_no),'1','小计',tt.class_no) classname ")
 					.append(
							" ,sum(tt.classtotal) classtotal ,sum(tt.regtotal) regtotal from ( ")
					.append(
							" select   aa.schoolterm_name,aa.regtotal,aa.class_no,aa.classdept_no,aa.dept_name,aa.classtotal from ( ")
					.append(
							" select   reg.schoolterm_name, sum(regtotal) regtotal,cut.class_no ,cut.classdept_no,dept.dept_name , sum(classtotal) classtotal")
					.append(" from ( ")
					.append(
							"  select  term.schoolterm_name ,reg.cust_id , sum(reg.reg_flag) regtotal , count(reg.reg_flag) classtotal  from ykt_cur.t_tif_registration reg ")
					.append(
							"  inner join ykt_cur.t_tif_register_schoolterm term on term.reg_id =reg.reg_id  ");
			if (!"".equals(term)) {
				sql.append("  where  term.reg_id in (" + term + ")");
			}
			sql
			        
					.append(" group by  term.schoolterm_name, cust_id  ) reg ")
					.append(
							" inner  join  ykt_cur.t_cif_customer cut on cut.cut_id = reg.cust_id  ")
					.append(
							" left join ykt_cur.t_cif_dept dept  on dept.dept_code = cut.classdept_no ")
					.append(
							" group by  reg.schoolterm_name,cut.classdept_no,cut.class_no ,dept.dept_name )aa" )
					.append(" where 1=1 ");
					if (!"".equals(classroom)) {
	         			sql.append(" and aa.class_no='" + classroom + "'");
			         }
			        if (!"".equals(dept)) {
				      sql.append(" and aa.classdept_no='" + dept + "'");
			        }

			sql
					.append(" )tt ")
					.append(
							" group by  rollup(tt.schoolterm_name,tt.dept_name,tt.class_no) ");

			SQLQuery q = s.createSQLQuery(sql.toString());
			q.addScalar("term", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("classname", Hibernate.STRING);
			q.addScalar("classtotal", Hibernate.INTEGER);
			q.addScalar("regtotal", Hibernate.INTEGER);
			return q.list();

		} catch (HibernateException he) {
			_log.error(he);
			return new ArrayList();
		}
	}

	// 学生付费查询
	public List getFeeQueryResult(Register reg) throws HibernateException {
		try {
			String begindate = reg.getBegindate();
			String enddate = reg.getEnddate();
			String classroom = reg.getClassroom();
			String dept = reg.getDept();
			String stuempNo = reg.getStuempNo();
			String name = reg.getName();
			String degree = reg.getDegree();
			String scode = reg.getScode();
			String feeType = reg.getFeeType();
			String term = reg.getTerm();
			String feeState = reg.getFeeState();
			SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");

			if ("".equals(enddate)) {
				enddate = dateFormat.format(new Date());
			} else {
				enddate = DateUtil.reFormatTime(enddate);
			}

			Session s = getSession();

			StringBuffer sql = new StringBuffer(
					" select lg.reg_id  regId, term.schoolterm_name term, cut.stuemp_no stuempNo ,cut.cut_name  cutName ,")
					.append(
							" lg.operate_date optDate, i.register_info regInfo, dept.dept_name deptName, ")
					.append(
							" s.s_name  sName ,ctf.type_name typeName ,fee.fee_name feeName ,cut.class_no classNo ,lg.operate_time operateTime")

					.append(" from v_register_pay_log  lg")

					.append(
							"  left join ykt_cur.t_tif_register_info i on i.register_flag = lg.register_flag ")

					.append(
							" left join ykt_cur.t_tif_register_schoolterm term on term.reg_id = lg.reg_id ")

					.append(
							" inner join ykt_cur.t_cif_customer cut on cut.stuemp_no = lg.stuemp_no  ")
					.append(
							" left join ykt_cur.t_cif_dept dept  on dept.dept_code = cut.classdept_no ")
					.append(
							" left join ykt_cur.t_cif_speciality s on s.s_code = cut.s_code ")
					.append(
							" left join ykt_cur.t_cif_cuttypefee ctf on  ctf.cut_type =cut.cut_type ")
					.append(
							" left join ykt_cur.t_pif_feetype fee  on fee.fee_type =cut.fee_type  where 1=1 and   cut.at_school=1");
			if (!"".equals(begindate)) {
				sql.append("and  lg.operate_date >= '"
						+ DateUtil.reFormatTime(begindate)
						+ "' and  lg.operate_date <= '" + enddate + "'");
			}
			if (!"".equals(classroom)) {
				sql.append(" and  cut.class_no ='" + classroom + "'");
			}
			if (!"".equals(dept)) {
				sql.append(" and  cut.classdept_no  ='" + dept + "'");
			}
			if (!"".equals(stuempNo)) {
				sql.append(" and  cut.stuemp_no ='" + stuempNo + "'");
			}
			if (!"".equals(name)) {
				sql.append(" and cut.cut_name ='" + name + "'");
			}
			if (!"".equals(degree)) {
				sql.append(" and cut.cut_type = '" + degree + "'");
			}
			if (!"".equals(scode)) {
				sql.append(" and cut.s_code = '" + scode + "'");
			}
			if (!"".equals(feeType)) {
				sql.append(" and cut.fee_type = '" + feeType + "'");
			}
			if (!"".equals(term)) {
				sql.append(" and  term.reg_id in (" + term + ")");
			}
			if (!"".equals(feeState)) {
				sql.append(" and lg.register_flag ='" + feeState + "'");
			}
			sql.append(" order by  term.schoolterm_name desc ");

			SQLQuery q = s.createSQLQuery(sql.toString());
			q.addScalar("regId", Hibernate.INTEGER);
			q.addScalar("term", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("optDate", Hibernate.STRING);
			q.addScalar("regInfo", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("Sname", Hibernate.STRING);
			q.addScalar("typeName", Hibernate.STRING);
			q.addScalar("feeName", Hibernate.STRING);
			q.addScalar("classNo", Hibernate.STRING);
			q.addScalar("operateTime", Hibernate.STRING);
			return q.list();

		} catch (HibernateException he) {
			_log.error(he);
			return new ArrayList();
		} catch (Exception he) {
			_log.error(he);
			return new ArrayList();
		}
	}

	// 取得付费报表
	public List getFeeReport(Register reg) throws HibernateException {
		try {
			/*
			 * String begindate = reg.getBegindate(); String enddate =
			 * reg.getEnddate();
			 */
			String classroom = reg.getClassroom();
			String dept = reg.getDept();
			String term = reg.getTerm();
			Session s = getSession();
			/*
			 * SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
			 * if ("".equals(enddate)) { enddate = dateFormat.format(new
			 * Date()); } else { enddate = DateUtil.reFormatTime(enddate); }
			 */

			StringBuffer sql = new StringBuffer(

					" select   decode(grouping(term.schoolterm_name),'1','总计',term.schoolterm_name) as termName,")
					.append(
							" decode(grouping(dept.dept_Name),'1','学期汇总',dept.dept_Name)  as deptName, ")
					.append(
							" decode(grouping(cut.class_No),'1','小计',cut.class_No) as classNo,")
					.append("  count(i1.register_flag)  flag1 ,")
					.append(
							" count(i2.register_flag) flag2 ,count(i3.register_flag)  flag3, ")

					.append(
							" count(i4.register_flag) flag4 ,count(vpl.register_flag) classtotal")

					.append(" from  v_register_pay_log vpl ")

					.append(
							" left  join ykt_cur.t_tif_register_schoolterm term on term.reg_id = vpl.reg_id ")

					.append(
							" left  join ykt_cur.t_tif_register_info i1 on i1.register_flag = vpl.register_flag and i1.register_flag=1 ")
					.append(
							" left  join ykt_cur.t_tif_register_info i2 on i2.register_flag = vpl.register_flag and i2.register_flag=2 ")
					.append(
							" left  join ykt_cur.t_tif_register_info i3 on i3.register_flag = vpl.register_flag and i3.register_flag=3 ")
					.append(
							" left  join ykt_cur.t_tif_register_info i4 on i4.register_flag = vpl.register_flag and i4.register_flag=4 ")
					.append(
							" inner  join ykt_cur.t_cif_customer cut on cut.stuemp_no = vpl.stuemp_no ")
					.append(
							" left  join ykt_cur.t_cif_dept dept  on dept.dept_code = cut.classdept_no  where 1=1  ");

			if (!"".equals(classroom)) {
				sql.append(" and cut.class_no='" + classroom + "'");
			}
			if (!"".equals(dept)) {
				sql.append(" and cut.classdept_no='" + dept + "'");
			}
			if (!"".equals(term)) {
				sql.append(" and    term.reg_id in (" + term + ")");
			}
			sql
					.append("  group by rollup(term.schoolterm_name,dept.dept_Name,cut.class_no) ");
			SQLQuery q = s.createSQLQuery(sql.toString());

			q.addScalar("termName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("classNo", Hibernate.STRING);
			q.addScalar("flag1", Hibernate.INTEGER);
			q.addScalar("flag2", Hibernate.INTEGER);
			q.addScalar("flag3", Hibernate.INTEGER);
			q.addScalar("flag4", Hibernate.INTEGER);
			q.addScalar("classtotal", Hibernate.INTEGER);
			return q.list();

		} catch (HibernateException he) {
			_log.error(he);
			return new ArrayList();
		}
	}

	// 取得所有未报到的人员信息
	/*
	 * public List getNoRegisterStudent(String termName){ try { Session s =
	 * getSession(); Query q = s.getNamedQuery("getNoRegisterStudent");
	 * q.setString("termName",termName); return q.list(); } catch
	 * (HibernateException e) { _log.error(e); return null; } }
	 */

	// 导入未注册的学生
	public boolean ImpNoRegisterStudent(String termName) {
		Session s = getSession();
		Transaction tx = s.beginTransaction();
		try {
			/*StringBuffer sql = new StringBuffer(" select t1.cut_id,t1.cut_type,term.reg_id from (")
					.append(" (  select c1.cut_id  ,c1.cut_type, r.reg_id  from (")
					.append("	  (select   c.cut_id,  c.cut_type ")
					.append("		 from ykt_cur.t_cif_customer c  ")
					.append("	 where c.at_school  =1 and c.class_no    is not null  ")
					.append(" and c.cut_type in (select cuttype from t_tif_register_schoolterm ")
					.append(" where reg_id  in ("+termName+") group by cuttype) ")
					.append("	 )) c1  ")
					.append(" left join (select  g.cust_id,g.reg_id,g.reg_flag  ")
					.append(" from ykt_cur.t_tif_registration g where g.reg_id in ("+termName+")) r ")
					.append("  on c1.cut_id  =r.cust_id  ").append(
							"  where reg_id is null ").append("  )t1 ").append(
							"  left join t_tif_register_schoolterm term ")
					.append("  on term.cuttype = t1.cut_type  ");*/
			StringBuffer sql = new StringBuffer("");
			sql.append(" select t1.cut_id,t1.cut_type,term.reg_id from ")
			.append(" (  select c1.cut_id  ,c1.cut_type, r.reg_id  from ( ")
			.append(" (select   c.cut_id,  c.cut_type  ")
			.append(" from ykt_cur.t_cif_customer c  ")
			.append("   where c.at_school  =1 and c.class_no  is not null    and c.cut_state = 1  ")
			.append("   and c.cut_type in (select cuttype from t_tif_register_schoolterm ")
			.append("  where reg_id  in ("+termName+ ") group by cuttype) ")
			.append("  	 )) c1  ")
			.append("  left join (select  g.cust_id,g.reg_id,g.reg_flag   ")
			.append("  from ykt_cur.t_tif_registration g where g.reg_id in ("+termName+")) r ")
			.append("  on c1.cut_id  =r.cust_id  ")
			.append("  where reg_id is null ")
			.append(" )t1 ")
			.append("  left join t_tif_register_schoolterm term  ")
			.append(" on term.cuttype = t1.cut_type   ")
			.append(" where term.reg_id in ("+termName+")");
			
             System.out.print(sql.toString());
			SQLQuery q = s.createSQLQuery(sql.toString());
			q.addScalar("cut_id", Hibernate.STRING);
			q.addScalar("cut_type", Hibernate.STRING);
			q.addScalar("reg_id", Hibernate.STRING);
			List list = q.list();
			if (list != null && list.size() > 0) {
				for (int i = 0; i < list.size(); i++) {
					Object[] obj = (Object[]) list.get(i);
					long custId = Long.valueOf((String) obj[0]).longValue();
					long regId = Long.valueOf((String) obj[2]).longValue();
					TTifRegistrationId kId = new TTifRegistrationId(custId,
							regId);
					TTifRegistration reg = new TTifRegistration(kId);
					reg.setRegFlag(new Integer(0));
					s.save(reg);
				}
			}
			tx.commit();
			return true;
		} catch (HibernateException e) {
			_log.error(e);
			tx.rollback();
			return false;
		}
	}
}
