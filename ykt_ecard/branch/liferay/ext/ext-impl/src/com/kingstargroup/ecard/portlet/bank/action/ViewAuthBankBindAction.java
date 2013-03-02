package com.kingstargroup.ecard.portlet.bank.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.exceptions.BccException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.portlet.bank.service.BankServiceUtil;
import com.kingstargroup.ecard.portlet.distribution.service.CustomerLocalServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ViewRuleAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-21  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ViewAuthBankBindAction extends PortletAction {
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		User user = null;
		user = PortalUtil.getUser(req);
//		long userid = user.getUserId();
		if(user!=null){
			String stuempno = user.getScreenName();
			TCustomer tcustomer = CustomerLocalServiceUtil.getCustomerByStuempno(stuempno);		
			if(tcustomer!=null){
				if(tcustomer.getStuempno()!=null&&!"".equals(tcustomer.getStuempno())){
					if(tcustomer.getIdno()!=null&&!"".equals(tcustomer.getIdno())){
						req.setAttribute("stuempno", stuempno);
						String bankacc="";
						try {
							bankacc= BankServiceUtil.getBankBindingAccount(tcustomer, tcustomer.getStuempno());
							if("".equals(bankacc)){
								//取得银行卡后同步
//								bankacc = BankServiceUtil.getLinkBankBindingAcc(tcustomer.getStuempno());
								if (!"".equals(bankacc.trim())){
//									BankServiceUtil.linkBindingOper(tcustomer.getStuempno(), bankacc, "S");
								}
							}
							
						} catch (BccBgInfoException e) {
							SessionErrors.add(req,e.getClass().getName(),e);
						}catch (BccException e) {
							SessionErrors.add(req,e.getClass().getName(),e);		
						}catch (Exception e) {			
							SessionErrors.add(req,e.getClass().getName(),e);		
						}					
						req.setAttribute("bankacc", bankacc);		
					}else{
						SessionErrors.add(req, EcardConstants.INFO_NOT_ENOUGH_IDCARD);
					}
					
				}else{
					SessionErrors.add(req, EcardConstants.INFO_NOT_ENOUGH_STUEMPNO);
				}
			}else{
				SessionErrors.add(req, EcardConstants.INFO_NOT_ENOUGH_CUSTOMER);
			}
		}else{
			SessionErrors.add(req, EcardConstants.INFO_NOT_ENOUGH_CUSTOMER);
		}		
		saveToken(req);
		return mapping.findForward("portlet.bankbind.edit");
	
	}
}
