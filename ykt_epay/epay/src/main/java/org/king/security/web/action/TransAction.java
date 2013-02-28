package org.king.security.web.action;

import java.util.Arrays;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.common.Configuration;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.DecoratorFactory;
import org.king.common.displaytag.decorator.StateDecorator;
import org.king.framework.web.action.BaseAction;
import org.king.security.service.TransService;
import org.king.utils.BccUtil;
import org.king.utils.Contants;
import org.king.utils.DateUtil;
import org.king.utils.PaginationUtil;

import antlr.StringUtils;

import com.kingstar.bcc.BccctlInit;
import com.kingstar.bcc.bccclt;

public class TransAction extends BaseAction{
	
	private TransService transService;
	
	
	public void setTransService(TransService transService) {
		this.transService = transService;
	}



	/**
	 * 获取电子支付交易流水
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward listEpayTransdtl(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        String starttime = (String) ((DynaActionForm) form).get("starttime");
        String endtime = (String) ((DynaActionForm) form).get("endtime");
        String custid = (String) ((DynaActionForm) form).get("custid");
        String stuempno = (String) ((DynaActionForm) form).get("stuempno");
        String status = (String) ((DynaActionForm) form).get("status");
        String revflag = (String) ((DynaActionForm) form).get("revflag");
        
        
        if(endtime==null || "".equals(endtime)){
        	endtime = DateUtil.getNow("yyyyMMdd");
 		    request.setAttribute("endtime", endtime);
        }
        
		if(starttime==null || "".equals(starttime)){
			starttime = DateUtil.getLastDays(endtime, 7, "yyyyMMdd");
        	request.setAttribute("starttime", starttime);
		}
		
		StateDecorator statusDecorator = DecoratorFactory.getStatusDecorator();
		StateDecorator revflagDecorator = DecoratorFactory.getRevflagDecorator();
		
        Object[] conditions = new Object[]{starttime,endtime,revflag,custid,stuempno,status};
        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        transService.getEayTransdtlList(page, conditions);
        request.setAttribute("listTransdtl", page);
        request.setAttribute("statusDecorator", statusDecorator);
        request.setAttribute("revflagDecorator", revflagDecorator);
        return mapping.findForward("listTransdtl");
    }
	
	public ActionForward reverseEpay (ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
		StateDecorator statusDecorator = DecoratorFactory.getStatusDecorator();
		StateDecorator revflagDecorator = DecoratorFactory.getRevflagDecorator();
		request.setAttribute("statusDecorator", statusDecorator);
        request.setAttribute("revflagDecorator", revflagDecorator);
		String refno = request.getParameter("refno"); //交易参考号
		String mac = request.getParameter("mac");//交易参考号MAC
		
		//掉后台处理
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		int mainfunction = Configuration.getIntProperty("mainfunction", 6000);
		int func = Configuration.getIntProperty("epay_transdtl_reverse", 846341);// 后台业务功能号
		bccclt bcc = null;
		try{
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(Configuration.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sphone3".getBytes(), refno.getBytes());
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(), mac.getBytes());
				
				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno, mainfunction, 10000, errcode, errmsg);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							//成功
							byte[] byteStr = new byte[300];
							Arrays.fill(byteStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess".getBytes(), byteStr, 81);
							String vsmess=BccUtil.getStringFromByte(byteStr);
							
							log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
							request.setAttribute("msg", "冲正成功！");
							return mapping.findForward("revok");	
							
						}else{
							//后台处理失败
							log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
							request.setAttribute("msg", "后台处理失败!");
							return mapping.findForward("revok");	
						}
					}else{
						//失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess".getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
							request.setAttribute("msg", vsmess);
							return mapping.findForward("revok");	
						}else{
							//后台处理失败
							log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
							request.setAttribute("msg", "后台处理失败!");
							return mapping.findForward("revok");	
						}
					}
				}else{
					//后台通讯暂时不可用，请稍后重试！
					log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
					request.setAttribute("msg", "后台通讯暂时不可用，请稍后重试!");
					return mapping.findForward("revok");	
				}
			}
			//系统出现异常，请稍后重试！
			log.error("cpack包构建失败!");
			request.setAttribute("msg", "系统出现异常，请稍后重试!");
			return mapping.findForward("revok");	
		}catch(Exception e){
			//系统出现异常，请稍后重试！
			log.error(e);
			request.setAttribute("msg", "系统出现异常，请稍后重试!");
			return mapping.findForward("revok");	
		}catch(UnsatisfiedLinkError e){
			//系统初始化异常，请稍后重试！
			log.error(e);
			request.setAttribute("msg", "系统出现异常，请稍后重试!");
			return mapping.findForward("revok");	
		}finally{
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
		
	}

}
