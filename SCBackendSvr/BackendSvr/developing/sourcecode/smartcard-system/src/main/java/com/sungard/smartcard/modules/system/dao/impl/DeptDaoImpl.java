package com.sungard.smartcard.modules.system.dao.impl;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import com.sungard.smartcard.domain.Dept;
import com.sungard.smartcard.modules.system.dao.DeptDao;
/**
 * 部门数据库操作类实现
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-22
 */
@Repository
public class DeptDaoImpl implements DeptDao{

	@Autowired
    private JdbcTemplate jdbcTemplate;
	
	/**
	 * 查询
	 * */
	@Override
	public List<Dept> allDepts(Dept dept) {		
		List<Dept> deptlist=null;
		StringBuffer selectsql = new StringBuffer("select * from t_dept where 1=1 ");
		List args = new ArrayList();
		
		if(dept!=null){
			if(dept.getDeptcode().trim()!=null&&!"".equals(dept.getDeptcode().trim())){//部门code
				selectsql.append(" and deptcode=? ");
				args.add(dept.getDeptcode().trim());
			}
			if(dept.getDeptname().trim()!=null&&!"".equals(dept.getDeptname().trim())){//部门name
				selectsql.append(" and deptname like ? ");
				args.add("%"+dept.getDeptname().trim()+"%");
			}
			if(dept.getDeptename().trim()!=null&&!"".equals(dept.getDeptename().trim())){//部门英文name
				selectsql.append(" and deptename=? ");
				args.add("%"+dept.getDeptename().trim()+"%");
			}
			if(dept.getFdeptcode().trim()!=null&&!"".equals(dept.getFdeptcode().trim())){//上级部门CODE
				selectsql.append(" and fdeptcode=? ");
				args.add(dept.getFdeptcode().trim());
			}
		}
		selectsql.append("  order by deptcode  ");
		
		deptlist=this.jdbcTemplate.query(selectsql.toString(), (args!=null&&args.size()>0)?args.toArray():null,
				new BeanPropertyRowMapper(Dept.class));
		return deptlist;
	}

	
	/**
	 * 修改保存
	 * */
	@Override
	public int updateDept(Dept dept) {
		
		return this.jdbcTemplate.update("update t_dept set areacode=?,deptname=?,deptename=?,olddeptcode=?,deptfullname=?, lastsaved=? " +
				" where deptcode=? ",
				dept.getAreacode(),dept.getDeptname(),dept.getDeptename(),
				dept.getOlddeptcode(),dept.getDeptfullname(),dept.getLastsaved(),dept.getDeptcode());
	}
	/**
	 * 新增保存
	 * */
	@Override
	public int addDept(Dept dept) {	
		String addsql="insert into t_dept(deptcode ,areacode,deptname,deptename,deptfullname," +
					   "fdeptcode,deptlevel,depttype,olddeptcode,useflag," +
					   "lastsaved) values(?,?,?,?,?,?,?,?,?,?,?)";
//		return this.jdbcTemplate.update(addsql, dept.getDeptcode(),dept.getAreacode(),dept.getDeptname(),dept.getDeptename(),dept.getDeptfullname()
//				,dept.getFdeptcode(),dept.getDeptlevel(),dept.getDepttype(),dept.getOlddeptcode(),
//				dept.getUseflag(),dept.getUseflag(),dept.getLastsaved());
		
		return update(addsql,new Object[]{dept.getDeptcode(),dept.getAreacode(),dept.getDeptname(),dept.getDeptename(),dept.getDeptfullname()
				,dept.getFdeptcode(),dept.getDeptlevel(),dept.getDepttype(),dept.getOlddeptcode(),dept.getUseflag(),dept.getLastsaved()});
	}
	
	@Override
	public int update(String sql, Object[] args) {
		return jdbcTemplate.update(sql, args);
	}
	
	/**
	 * 查询
	 * */
	@Override
	public Dept getDept(String deptcode) {
		return this.jdbcTemplate.queryForObject("select * from t_dept where 1=1 and deptcode=? ", new BeanPropertyRowMapper(Dept.class), deptcode);
	}
	/**
	 * 根据fdeptcode获得最大的deptcode字符串值
	 * */
	@Override
	public int getDeptcode(String  fdeptcode){
		String sql =" select max(to_number(nvl(substr(deptcode,-3,3),0))) from  t_dept where fdeptcode=? ";		
		int deptcode=this.jdbcTemplate.queryForInt(sql,fdeptcode);	
		return deptcode;
	}
	
	/**
	 * 根据部门code查询，是否存在记录
	 */
	@Override
	public boolean isExitDept(String deptcode) {
		String sql="select count(*) from t_dept where 1=1 and deptcode = ?";
		int i=0;
		i= this.jdbcTemplate.queryForInt(sql, deptcode);
		
		if(i>0){
			return true;
		}	
		return false;
	}
	/**
	 * 根据部门名称查询，是否存在该名称记录
	 */
	@Override
	public boolean isExitDeptName(String deptcode, String deptname) {
		String sql="select count(*) from t_dept where 1=1 ";
		int i=0;
		if(deptcode!=null&&!"".equals(deptcode)){//修改时判断使用
			sql+=" and deptcode !=? and deptname = ?";
			i= this.jdbcTemplate.queryForInt(sql,deptcode, deptname);
		}else{//新增时判断使用
			sql+=" and deptname = ?";
			i= this.jdbcTemplate.queryForInt(sql, deptname);
		}	
		if(i>0){
			return true;
		}	
		return false;
	}

	
	/**
	 * 根据传入的deptcode 判断是根部门
	 * 是：true
	 * 否：false
	 * */
	@Override
	public boolean isFarDept(String deptcode){
		String sql="select count(*) from t_dept where 1=1  and fdeptcode is null and deptcode = ?";
		int i=0;
		i=this.jdbcTemplate.queryForInt(sql, deptcode);
		if(i>0){
			return true;
		}
		return false;
	}
	
	/**
	 * 根据传入的deptcode判断是否存在下级部门
	 * 删除的时候需要判断
	 * 存在：true
	 * 不存在：false
	 * */
	@Override
	public boolean isExistSonDept(String fdeptcode){
		String sql="select count(*) from t_dept where 1=1 and fdeptcode  = ?";
		int i=0;
		i=this.jdbcTemplate.queryForInt(sql, fdeptcode);
		if(i>0){
			return true;
		}
		return false;
	}

	/**
	 * 根据code删除
	 */
	@Override
	public int deleDept(String deptcode) {
		return this.jdbcTemplate.update("delete from t_dept where deptcode=? ", deptcode);
	}

}
