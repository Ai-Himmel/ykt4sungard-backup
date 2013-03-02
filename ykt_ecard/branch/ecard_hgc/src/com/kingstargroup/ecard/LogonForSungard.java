package com.kingstargroup.ecard;
import com.sungard.cas.client.validation.ILogonHandler;
import org.jasig.cas.client.validation.Assertion;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.security.Principal;

/**
 * Created by IntelliJ IDEA.
 * User: Haiyu.Peng
 * Date: 2010-5-21
 * Time: 17:12:12
 * To change this template use File | Settings | File Templates.
 */
public class LogonForSungard implements ILogonHandler {

    public String _SsoUsername;
    public void onLogon(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, Assertion assertion) {
        Principal p=assertion.getPrincipal();
        _SsoUsername = p.getName();
        httpServletRequest.getSession().setAttribute("stuempno",p.getName());
    }
    public String getUsername(){
        return  _SsoUsername;
    }
}
