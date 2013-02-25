package com.sungard.smartcard.modules.system.dao.impl;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import com.sungard.modules.utils.StringHelper;
import com.sungard.smartcard.domain.Functionality;
import com.sungard.smartcard.domain.Opersite;
import com.sungard.smartcard.domain.Site;
import com.sungard.smartcard.modules.system.dao.SiteDao;
import com.sungard.smartcard.modules.system.service.impl.SiteServiceImpl;

@Repository
public class SiteDaoImpl implements SiteDao {
	private static final Logger logger = LoggerFactory.getLogger(SiteDaoImpl.class);
	@Autowired
    private JdbcTemplate jdbcTemplate;
	
	/**查询站点关联操作员数据*/
	private static String QUERY_OPERATORSITE = "select tor.opercode opercode,t.siteno siteno,t.ip ip,t.machinecode machinecode,t.sitename sitename from t_opersite to,t_operator tor,t_site t where t.siteno=to.siteno and to.opercode=tor.opercode";
	/**删除操作员站点关系数*/
	private static String DEL_OPERATORSITE = "delete from t_opersite where siteno=? and opercode=?";	
	/**查询操作员站点关系数*/
	private static String GET_OPERATORSITENUM = "select count(*) from t_opersite where siteno=? and opercode=?";
	/**新增操作员站点关联关系*/
	private static String INSERT_OPERATORSITE = "insert into t_opersite values(?,?,?)";
	/**新增站点sql*/
	private static String INSERT_SITE = "insert into t_site (sitename,ip,machinecode,lastsaved,remark) values (?,?,?,?,?)";
	/**查询站点列表信息*/
	private static String QUERY_SITES = "select * from t_site where 1=1";
	/**删除站点*/
	private static String DELETE_SITE = "delete from t_site where siteno=?";
	/**根据参数获取站点数sql*/
	private static String GET_SITE_NUM = "select count(*) from t_site where 1=1";
	/**update语句*/
	private static String UPDATE_SITES = "update t_site set sitename=?,ip=?,machinecode=?,lastsaved=?,remark=? where siteno=?";
	/**根据siteno查找关联操作员*/
	private static String GET_RELATE_OPERATORNUM = "select count(ts.siteno) from t_site ts,t_operator to where ts.siteno=? and ts.siteno=to.siteno";
	

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	@Override
	public void addSite(Site site) {
		logger.debug("新增站点sql："+INSERT_SITE);
		//logger.debug("参数---"+"站点名称："+site.getSitename()+"---站点ip："+site.getIp()+"----机器码："+site.getMachinecode()+"---最后修改时间："+site.getLastsaved()+"-----备注："+site.getRemark());
		jdbcTemplate.update(
				INSERT_SITE,site.getSitename(),site.getIp(),site.getMachinecode(),site.getLastsaved(),site.getRemark());
	}

	@Override
	public void delSite(Site site) {
		logger.debug("删除站点sql："+DELETE_SITE);
		this.jdbcTemplate.update(
				DELETE_SITE,Long.valueOf(site.getSiteno()));
	}

	@Override
	public List<Site> querySite(Site site) {
		String qss = QUERY_SITES;
		String sitename = site.getSitename();
		String ip = site.getIp();
		Pattern p = Pattern.compile("\\s");
		Matcher m = p.matcher(sitename);
		sitename = m.replaceAll("");
		m = p.matcher(ip);
		ip = m.replaceAll("");
		if(site.getSiteno()!=0){
			qss = qss+" and siteno="+site.getSiteno();
		}
		if(sitename!=null && !"".equals(sitename)){
			qss = qss+" and sitename like '%"+sitename+"%'";
		}
		if(ip!=null && !"".equals(ip)){
			qss = qss+" and ip like '%"+ip+"%'";
		}
		logger.debug("查询站点sql："+qss);
		List<Site> sites = this.jdbcTemplate.query(
				qss,
		        new RowMapper<Site>() {
		            public Site mapRow(ResultSet rs, int rowNum) throws SQLException {
		            	Site f = new Site();
		            	f.setSiteno(rs.getInt("siteno"));
		            	f.setSitename(rs.getString("sitename"));
		            	f.setIp(rs.getString("ip"));
		            	f.setMachinecode(rs.getString("machinecode"));
		            	f.setRemark(rs.getString("remark"));
		                return f;
		            }
		       });
		return sites;
	}

	@Override
	public void updateSite(Site site) {
		logger.debug("更新站点sql："+UPDATE_SITES);
		jdbcTemplate.update(
				UPDATE_SITES,site.getSitename(),site.getIp(),site.getMachinecode(),site.getLastsaved(),site.getRemark(),Long.valueOf(site.getSiteno()));
	}

	@Override
	public int getExistSiteNum(String... parm) {
		String qss = GET_SITE_NUM;
		int s = 0;
		if(parm[0]!=null && !"".equals(parm[0])){
			s= jdbcTemplate.queryForInt(qss+" and sitename=?",parm[0]);
		}
		if(parm[1]!=null && !"".equals(parm[1])){
			s= jdbcTemplate.queryForInt(qss+" and ip=?",parm[1]);
		}
		return s;
	}

	@Override
	public int hasRelatedOperator(Site site) {
		return jdbcTemplate.queryForInt(GET_RELATE_OPERATORNUM,site.getSiteno());
	}

	@Override
	public int getExistSiteNumForUpdate(int siteno, String... parm) {
		String qss = GET_SITE_NUM;
		int s = 0;
		if(parm[0]!=null && !"".equals(parm[0])){
			s= jdbcTemplate.queryForInt(qss+" and sitename=? and siteno<>?",parm[0],siteno);
		}
		if(parm[1]!=null && !"".equals(parm[1])){
			s= jdbcTemplate.queryForInt(qss+" and ip=? and siteno<>?",parm[1],siteno);
		}
		return s;
	}

	@Override
	public void addOSite(Opersite os) {
		this.jdbcTemplate.update(INSERT_OPERATORSITE,os.getOpercode(),Long.valueOf(os.getSiteno()),os.getLastsaved());
	}

	@Override
	public void delOSite(Opersite os) {
		this.jdbcTemplate.update(DEL_OPERATORSITE,Long.valueOf(os.getSiteno()),os.getOpercode());
	}

	@Override
	public List<Site> queryOSite(Opersite os) {
		String qss = QUERY_OPERATORSITE;
		String opercode = os.getOpercode();
		Pattern p = Pattern.compile("\\s");
		Matcher m = p.matcher(opercode);
		opercode = m.replaceAll("");
		if(os.getSiteno()!=0){
			qss = qss+" and t.siteno="+os.getSiteno();
		}
		if(StringHelper.isBlank(opercode)){
			qss = qss+" and tor.opercode like '%"+opercode+"%'";
		}
		List<Site> sites = this.jdbcTemplate.query(
				qss,
		        new RowMapper<Site>() {
		            public Site mapRow(ResultSet rs, int rowNum) throws SQLException {
		            	Site f = new Site();
		            	f.setSiteno(rs.getInt("siteno"));
		            	f.setSitename(rs.getString("sitename"));
		            	f.setIp(rs.getString("ip"));
		            	f.setMachinecode(rs.getString("machinecode"));
		            	f.setRemark(rs.getString("opercode"));
		                return f;
		            }
		       });
		return sites;
	}

	@Override
	public void updateOSite(Opersite os) {
		//无需球
	}

	@Override
	public int hasOperatorSiteNum(Opersite os) {
		return this.jdbcTemplate.queryForInt(GET_OPERATORSITENUM,Long.valueOf(os.getSiteno()),os.getOpercode());
	}

}
