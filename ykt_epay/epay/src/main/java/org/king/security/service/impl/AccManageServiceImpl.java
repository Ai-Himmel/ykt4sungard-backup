package org.king.security.service.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.Constant;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.BaseDAO;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.framework.util.MyUtils;
import org.king.security.dao.TCardphytypeDAO;
import org.king.security.dao.TEpayRecordDAO;
import org.king.security.dao.TNetaccDAO;
import org.king.security.dao.TShopaccDAO;
import org.king.security.domain.TCardphytype;
import org.king.security.domain.TEpayRecord;
import org.king.security.domain.TNetacc;
import org.king.security.domain.TShopacc;
import org.king.security.service.AccManageService;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.orm.hibernate3.LocalSessionFactoryBean;


public class AccManageServiceImpl extends BaseService implements AccManageService{

	private static Log log = LogFactory.getLog(AccManageServiceImpl.class);

    private JdbcTemplate jdbcTemplate;

    private LocalSessionFactoryBean lsfb;
    
    private TNetaccDAO tNetaccDAO;
    
    private TEpayRecordDAO tEpayRecordDAO;
    
    private TShopaccDAO tShopaccDAO;
    
    private TCardphytypeDAO tCardphytypeDAO;
    
	public void settShopaccDAO(TShopaccDAO tShopaccDAO) {
		this.tShopaccDAO = tShopaccDAO;
	}


	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}


	public void setLsfb(LocalSessionFactoryBean lsfb) {
		this.lsfb = lsfb;
	}


	public void settNetaccDAO(TNetaccDAO tNetaccDAO) {
		this.tNetaccDAO = tNetaccDAO;
	}

	
	public void settEpayRecordDAO(TEpayRecordDAO tEpayRecordDAO) {
		this.tEpayRecordDAO = tEpayRecordDAO;
	}


	public void settCardphytypeDAO(TCardphytypeDAO tCardphytypeDAO) {
		this.tCardphytypeDAO = tCardphytypeDAO;
	}


	/*
	 * 检查老密码
	 * @param 账号
	 * @param 密码
	 * @param 密码类型
	 * @人员类型   1持卡人，2商户    required
	 * return false：与老密码相等,true:与来密码不相等
	 */
	public boolean checkoldpwd(String account, String oldpwd, String pwdtype,String acctype){
		boolean flag = false;
		if(Constant.ACCOUT_TYPE_CARD.equals(acctype)){
			TNetacc tNetacc= tNetaccDAO.get(account);
			if(pwdtype.equals(Constant.PWD_TYPE_ACC)){
				//卡密码
				flag = !MyUtils.toMD5(oldpwd).equals(tNetacc.getAccpwd());
			}else if(pwdtype.equals(Constant.PWD_TYPE_PAY)){
				//支付密码
				flag = !MyUtils.toMD5(oldpwd).equals(tNetacc.getPaypwd());
			}
		}else if(Constant.ACCOUT_TYPE_SHOP.equals(acctype)){
			TShopacc shop = tShopaccDAO.get(account);
			flag = !MyUtils.toDes(oldpwd).equals(shop.getAccpwd());
		}
		return flag;
	}
	//修改密码
	public boolean changepwd(String account, String pwd, String pwdtype,String acctype)
			throws BusinessException {
		if(Constant.ACCOUT_TYPE_CARD.equals(acctype)){
			TNetacc tNetacc= tNetaccDAO.get(account);
			if(pwdtype.equals(Constant.PWD_TYPE_ACC)){
				//卡密码
				tNetacc.setAccpwd(MyUtils.toMD5(pwd));
			}else if(pwdtype.equals(Constant.PWD_TYPE_PAY)){
				//支付密码
				tNetacc.setPaypwd(MyUtils.toMD5(pwd));
			}
			try{
				tNetaccDAO.save(tNetacc);
				return true;
			}catch(Exception e){
				e.printStackTrace();
				return false;
			}
		}else if(Constant.ACCOUT_TYPE_SHOP.equals(acctype)){
			TShopacc shop = tShopaccDAO.get(account);
			shop.setAccpwd(MyUtils.toDes(pwd));
			try{
				tShopaccDAO.save(shop);
				return true;
			}catch(Exception e){
				e.printStackTrace();
				return false;
			}
		}
		return false;
	}


	public boolean setStopPay(String flag, String accno) {
		try{
			TNetacc tNetacc = tNetaccDAO.get(accno);
			tNetacc.setStoppayflag(Long.valueOf(flag));
			tNetaccDAO.save(tNetacc);
			return true;
		}catch(Exception e){
			//e.printStackTrace();
			return false;
		}
	}
	public TNetacc getNetacc(String accno) {
			return tNetaccDAO.get(accno);
			
	}
	
	public void getPayRecordList(DBPaginatedList page,Object[] conditions){
		String hql = " from TEpayRecord a where a.tnetacc.accno = ?";
		if(conditions[1]!=null&&!"".equals(conditions[1])){
			hql+=" and a.epaydate>=?";
		}
		if(conditions[2]!=null&&!"".equals(conditions[2])){
			hql+=" and a.epaydate<=?";
		}
		QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());
        queryTranslate.addPara(conditions[0], Types.VARCHAR);
        if(conditions[1]!=null&&!"".equals(conditions[1]))
        	queryTranslate.addPara(conditions[1], Types.VARCHAR);
    	if(conditions[2]!=null&&!"".equals(conditions[2]))
    		queryTranslate.addPara(conditions[2], Types.VARCHAR);
		tEpayRecordDAO.findByPage(page, queryTranslate);
	}


	public void getNetaccList(DBPaginatedList page, Object[] conditions) {
		String hqlString = " from TNetacc t where 1=1";
		if(conditions[0]!=null&&!"".equals(conditions[0])&&!"-1".equals(conditions[0])){
			hqlString+=" and t.stoppayflag = ?";
		}
		if(conditions[1]!=null&&!"".equals(conditions[1])&&!"-1".equals(conditions[1])){
			hqlString+=" and t.status = ?";
		}
		QueryTranslate queryTranslate = new QueryTranslate();
		queryTranslate.setQueryString(hqlString);
		queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());
        if(conditions[0]!=null&&!"".equals(conditions[0])&&!"-1".equals(conditions[0]))
        	queryTranslate.addPara(conditions[0], Types.VARCHAR);
    	if(conditions[1]!=null&&!"".equals(conditions[1])&&!"-1".equals(conditions[1]))
    		queryTranslate.addPara(conditions[1], Types.VARCHAR);
    	
		tNetaccDAO.findByPage(page, queryTranslate);
		
	}
	
  public List getAvailCardPhytype(){
	return tCardphytypeDAO.getAvailCardPhytype();
	}

}
