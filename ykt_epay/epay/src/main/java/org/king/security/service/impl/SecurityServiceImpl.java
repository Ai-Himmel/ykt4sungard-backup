package org.king.security.service.impl;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.framework.util.MyUtils;
import org.king.security.dao.TEpayActiveinfoDAO;
import org.king.security.dao.TNetaccDAO;
import org.king.security.dao.TOperatorDAO;
import org.king.security.dao.TShopaccDAO;
import org.king.security.domain.Menu;
import org.king.security.domain.TEpayActiveinfo;
import org.king.security.domain.TNetacc;
import org.king.security.domain.TOperator;
import org.king.security.domain.TShopacc;
import org.king.security.service.Acl;
import org.king.security.service.SecurityService;
import org.king.security.util.MenuComparator;
import org.king.security.util.MenuParser;
import org.king.utils.DateUtil;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.orm.hibernate3.LocalSessionFactoryBean;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;

/**
 * <p>
 * SecurityServiceImpl.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * <p/>
 * <p>
 * <a href="SecurityServiceImpl.java.html"><i>查看源代码</i></a>
 * </p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 */
/**
 * @author Xinxing.Cheng
 *
 */
public class SecurityServiceImpl extends BaseService implements SecurityService {

    private static Log log = LogFactory.getLog(SecurityServiceImpl.class);

    private Acl acl;

    private JdbcTemplate jdbcTemplate;

    private LocalSessionFactoryBean lsfb;
    
    private TNetaccDAO tNetaccDAO;
    
    private TEpayActiveinfoDAO tEpayActiveinfoDAO;
    
    private TShopaccDAO tShopaccDAO;
    
    private TOperatorDAO tOperatorDAO;
    
    public void setAcl(Acl acl) {
        this.acl = acl;
    }

    public void setLsfb(LocalSessionFactoryBean lsfb) {
        this.lsfb = lsfb;
    }
    

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void settNetaccDAO(TNetaccDAO tNetaccDAO) {
		this.tNetaccDAO = tNetaccDAO;
	}

	public void settEpayActiveinfoDAO(TEpayActiveinfoDAO tEpayActiveinfoDAO) {
		this.tEpayActiveinfoDAO = tEpayActiveinfoDAO;
	}
	
	public void settShopaccDAO(TShopaccDAO tShopaccDAO) {
		this.tShopaccDAO = tShopaccDAO;
	}
	
	public void settOperatorDAO(TOperatorDAO tOperatorDAO) {
		this.tOperatorDAO = tOperatorDAO;
	}

	public void initSecurity() throws BusinessException {
        log.info("*****************init security begin!****************");
        MenuParser.init();
        log.info("*****************init security success!***************");
    }


    public void addChildren(Menu parent, List<Menu> menus,String accountype) {
        if (parent.getChildren().size() > 0) {
            List<Menu> children = parent.getChildren();
            Collections.sort(children, new MenuComparator());
            for (int i = 0; i < children.size(); i++) {
                //todo 根据登陆用户判断权限
            	if(children.get(i).getCode().equals(accountype)){
            		menus.add(children.get(i));
            		addChildren(children.get(i), menus,accountype);
            	}
            }
        }
    }

    public List getAccountMenus(String accountype) throws BusinessException {
        List menus = new ArrayList();
        Menu systemMenu = MenuParser.getMenu();
        menus.add(systemMenu);
        addChildren(systemMenu, menus,accountype);
        return menus;
    }

	public boolean actiCheckActivate(String account, String activatecode)
			throws BusinessException {
		List l= tEpayActiveinfoDAO.find("from TEpayActiveinfo a where a.id.accno='"+account+"' and a.id.activecode='"+activatecode+"' and a.id.status='0'");
		return l.size()>0;
	}

	public boolean activate(String account, String accpwd, String paypwd,String activatecode,String ip)
			throws BusinessException {
		try{
			TNetacc netacc = tNetaccDAO.get(account);
			netacc.setAccpwd(MyUtils.toMD5(accpwd));
			netacc.setPaypwd(MyUtils.toMD5(paypwd));
			netacc.setStatus("1");
			tNetaccDAO.update(netacc);
			TEpayActiveinfo activeinfo = (TEpayActiveinfo)tEpayActiveinfoDAO.find("from TEpayActiveinfo a where a.id.accno='"+account+"' and a.id.activecode='"+activatecode+"' and a.id.status='0'").get(0);
			activeinfo.setStatus("1");
			activeinfo.setActivetime(DateUtil.getNow());
			activeinfo.setIp(ip);
			tEpayActiveinfoDAO.update(activeinfo);
			return true;
		}catch(Exception e){
			e.printStackTrace();
			return false;
		}
		
	}
	public List getacc(String xh,String pwd){
		try{
			return jdbcTemplate.queryForList("select tn.accno as accno,tn.status as status,tn.accname as accname " +
					"from ykt_cur.t_customer t,ykt_cur.t_card tc,ykt_cur.t_netacc tn "+
					"where t.custid=tc.custid and tc.custid = tn.custid and t.stuempno=? and tc.cardpwd = ?",new Object[]{xh,MyUtils.toDes(pwd)});
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}
		
	}

	public void updateTnetacc(TNetacc netacc) {
		tNetaccDAO.update(netacc);
	}

	public TNetacc getNetaccByAccno(String accno) {
		return tNetaccDAO.findNetaccByAccno(accno);
	}

	public TShopacc getShopaccByAccno(String accno) {
		return tShopaccDAO.findShopaccByAccno(accno);
	}

	public TOperator getOperBycode(String operCode) {
		return tOperatorDAO.findOperBycode(operCode);
	}
	

}
