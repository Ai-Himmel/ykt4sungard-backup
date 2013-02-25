package com.sungard.smartcard.modules.system.dao.impl;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import com.sungard.modules.utils.StringHelper;
import com.sungard.smartcard.domain.Branch;
import com.sungard.smartcard.domain.Functionality;
import com.sungard.smartcard.modules.system.dao.BranchDao;

@Repository
public class BranchDaoImpl implements BranchDao {
	@Autowired
    private JdbcTemplate jdbcTemplate;
	/***/
	private static String QUERY_BRANCH = "select * from t_branch where 1=1";
	/**根据参数获取网点数*/
	private static String GET_BRANCHNUM = "select count(*) from t_branch where branchname=?";
	/**删除网点*/
	private static String DELETE_BRANCH = "update t_branch set useflag=?,lastsaved=? where branchno=?";
	/**更新网点*/
	private static String UPDATE_BRANCH = "update t_branch set areacode=?,branchname=?,branchtype=?,bankcode=?,bankaccno=?,bankaccname=?,contactman=?,tel=?,mobile=?,fax=?,addr=?,zipcode=?,lastsaved=? values(?,?,?,?,?,?,?,?,?,?,?,?,?) where branchno=?";
	/**添加网店信息*/
	private static String INSERT_NEWBRANCH = "insert into t_branch(areacode,branchname,branchtype,bankcode,bankaccno,bankaccname,contactman,tel,mobile,fax,addr,zipcode,status,opendate,closedate,useflag,lastsaved) values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	@Override
	public void addBranch(Branch b) {
		this.jdbcTemplate.update(INSERT_NEWBRANCH,b.getAreacode(),b.getBranchname(),b.getBranchtype(),b.getBankcode(),b.getBranchno(),b.getBankaccname(),b.getContactman(),b.getTel(),b.getMobile(),b.getFax(),b.getAddr(),b.getZipcode(),b.getStatus(),b.getOpendate(),b.getClosedate(),b.getUseflag(),b.getLastsaved());
	}

	@Override
	public void delBranch(Branch b) {
		jdbcTemplate.update(DELETE_BRANCH,b.getUseflag(),b.getLastsaved(),Long.valueOf(b.getBranchno()));
	}

	@Override
	public List<Branch> queryBranch(Branch b) {
		String areacode = b.getAreacode();
		String branchname = b.getBranchname();
		String branchtype = b.getBranchtype();
		String s = QUERY_BRANCH;
		if(StringHelper.isNotBlank(areacode)){
			s = QUERY_BRANCH+" and areacode='"+areacode+"'";
		}
		if(StringHelper.isNotBlank(branchtype)){
			s = QUERY_BRANCH+" and branchtype='"+branchtype+"'";
		}
		if(StringHelper.isNotBlank(branchname)){
			s = QUERY_BRANCH+" and branchname='"+branchname+"'";
		}
		List<Branch> branches = this.jdbcTemplate.query(
				s,
		        new RowMapper<Branch>() {
		            public Branch mapRow(ResultSet rs, int rowNum) throws SQLException {
		            	Branch f = new Branch();
		            	f.setBankaccno(rs.getString("bankaccno"));
		            	f.setBranchno(rs.getInt("branchno"));
		            	f.setBankaccname(rs.getString("bankaccname"));
		            	f.setAreacode(rs.getString("areacode"));
		            	f.setAddr(rs.getString("addr"));
		            	f.setBankcode(rs.getString("bankcode"));
		            	f.setBranchname(rs.getString("branchname"));
		            	f.setBranchtype(rs.getString("branchtype"));
		            	f.setClosedate(rs.getString("closedate"));
		            	f.setOpendate(rs.getString("opendate"));
		            	f.setContactman(rs.getString("contactman"));
		            	f.setFax(rs.getString("fax"));
		            	f.setMobile(rs.getString("mobile"));
		            	f.setStatus(rs.getString("status"));
		            	f.setTel(rs.getString("tel"));
		            	f.setUseflag(rs.getString("useflag"));
		            	f.setZipcode(rs.getString("zipcode"));
		                return f;
		            }
		       });
		return branches;
	}

	@Override
	public void updateBranch(Branch b) {
		this.jdbcTemplate.update(UPDATE_BRANCH,b.getAreacode(),b.getBranchname(),b.getBranchtype(),b.getBankcode(),b.getBranchno(),b.getBankaccname(),b.getContactman(),b.getTel(),b.getMobile(),b.getFax(),b.getAddr(),b.getZipcode(),b.getLastsaved(),Long.valueOf(b.getBranchno()));
	}

	@Override
	public int getBranchNumByParam(String branchname,Integer branchno) {
		if(branchno==null && branchname!=null){
			return jdbcTemplate.queryForInt(GET_BRANCHNUM,branchname);
		}else if(branchname!=null&&branchno!=null){
			return jdbcTemplate.queryForInt(GET_BRANCHNUM+" and branchno=?",branchname,Long.valueOf(branchno));
		}else{
			String s = GET_BRANCHNUM.replace("branchname", "branchno");
			return jdbcTemplate.queryForInt(s,Long.valueOf(branchno));
		}
	}


}
