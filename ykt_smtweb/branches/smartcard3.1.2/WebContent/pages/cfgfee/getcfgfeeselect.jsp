<%@ page contentType="text/html; charset=GBK"%>
<%@page import="com.kingstar.itemconfig.Configitem"%>
<%@page import="com.kingstargroup.fdykt.util.DateUtil"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<html>
    <head>
        <title>�շ���ѡ��</title>
        <meta http-equiv="Content-Type" content="text/html; charset=GBK" />
        <style type="text/css">
</style>
        <link href="pages/css/css.css" rel="stylesheet" type="text/css" />
    </head>

    <%
        String webserverip = KSConfiguration.getInstance().getProperty(
                "webserverip");
        String webserverport = KSConfiguration.getInstance().getProperty(
                "webserverport");
        String webserverapp = KSConfiguration.getInstance().getProperty(
                "webserverapp");
        String read_card_device_port = KSConfiguration.getInstance()
                .getProperty("read_card_device_port", "0");
    %>
    <script language="javascript">
    function checkcfgfee(gidval){
             document.selectform.gid.value=gidval;
             document.selectform.submit();
        }
    </script>
    <style type="text/css">
	.��ʽ5 {
	    font-family: "����";
	    color: #000000;
	    font-size: 18px;
	}
	
	.��ʽ13 {
	    font-family: "����";
	    color: #ffffff;
	    font-size: 18px;
	    padding-left: 60px;
	}
	   .��ʽ14 {
        font-family: "����";
        color:gray;
        font-size: 18px;
        padding-left: 60px;
    }
	</style>

    <body scroll="no">
        <div id="mid_top"></div>
        <div id="middle">
            <div id="Layer2">
                <div id="mid_center">
                    <ul>
                      <% Configitem cfgitemArr[] = (Configitem[])request.getAttribute("cfgitemArr");
                                        for(int i=0;i<cfgitemArr.length&&i<5;i++){
                                            Configitem cfgitem = cfgitemArr[i];
                                            String starttime = cfgitem.getStartTime();
                                            String endtime = cfgitem.getEndTime();
                                            String display = cfgitem.getDisplay();
                                            String gid = cfgitem.getGid();
                                            String shopid = cfgitem.getShopId();
                                            String name = cfgitem.getName();
                                            String now = DateUtil.getNow("yyyy-MM-dd");
                                            if("true".equals(display)){
                                                if(DateUtil.checkSpecialTimeSequence(starttime,now,"yyyy-MM-dd")<=0 && DateUtil.checkSpecialTimeSequence(endtime,now,"yyyy-MM-dd")>=0){
                                      %>
     
                                                    <li onmouseup="this.style.background='url(/smartcardweb/pages/images/sfan.gif)'" 
								                            onmousedown="this.style.background='url(/smartcardweb/pages/images/sfana.gif)'"
								                            style="cursor: hand; background: url(/smartcardweb/pages/images/sfan.gif)"
								                             onclick="javascript:checkcfgfee(<%=gid %>);"><br><br><font class="��ʽ13"><%=name%></font></li>
                                            <%
                                                }else{
                                            %>   
                                                   <li onmouseup="this.style.background='url(/smartcardweb/pages/images/sfan.gif)'" 
                                                            onmousedown="this.style.background='url(/smartcardweb/pages/images/sfana.gif)'"
                                                            style="cursor: hand; background: url(/smartcardweb/pages/images/sfan.gif)"
                                                            onclick="javascript:alert('������δ��ͨ');"><br><br><font class="��ʽ14"><%=name%></font></li>
                                                    <%
                                                }                                               
                                            }
                                        }
                                        
                                     %>

                    </ul>
                </div>
            </div>
            <div id="Layer11">
                <div id="mid_center">
                    <ul>
                      <% 
                          for(int i=0;i<cfgitemArr.length&&i<5;i++){
                              Configitem cfgitem = cfgitemArr[i];
                              String starttime = cfgitem.getStartTime();
                              String endtime = cfgitem.getEndTime();
                              String display = cfgitem.getDisplay();
                              String gid = cfgitem.getGid();
                              String shopid = cfgitem.getShopId();
                              String name = cfgitem.getName();
                              String now = DateUtil.getNow("yyyy-MM-dd");
                              if("true".equals(display)){
                                  if(DateUtil.checkSpecialTimeSequence(starttime,now,"yyyy-MM-dd")<=0 && DateUtil.checkSpecialTimeSequence(endtime,now,"yyyy-MM-dd")>=0){
                        %>

                                      <li><br><font class="��ʽ13">��ʼ��<%=starttime%></font><br><font class="��ʽ13">��ֹ��<%=endtime%></font></li>
                              <%
                                  }else{
                              %>   
                                     <li><br><font class="��ʽ13">��ʼ��<%=starttime%></font><br><font class="��ʽ13">��ֹ��<%=endtime%></font></li>
                                      <%
                                  }                                               
                              }
                          }
                          
                       %>

                    </ul>
                </div>
            </div>
            <div id="Layer3">
                <div id="mid_center">
                    <ul>

                       <%
                                for(int i=5;i<cfgitemArr.length;i++){
                                    Configitem cfgitem = cfgitemArr[i];
                                    String starttime = cfgitem.getStartTime();
                                    String endtime = cfgitem.getEndTime();
                                    String display = cfgitem.getDisplay();
                                    String gid = cfgitem.getGid();
                                    String shopid = cfgitem.getShopId();
                                    String name = cfgitem.getName();
                                    String now = DateUtil.getNow("yyyy-MM-dd");
                                    if("true".equals(display)){
                                        if(DateUtil.checkSpecialTimeSequence(starttime,now,"yyyy-MM-dd")<=0 && DateUtil.checkSpecialTimeSequence(endtime,now,"yyyy-MM-dd")>=0){
                              %>

                                            <li onmouseup="this.style.background='url(/smartcardweb/pages/images/sfan.gif)'" 
                                                    onmousedown="this.style.background='url(/smartcardweb/pages/images/sfana.gif)'"
                                                    style="cursor: hand; background: url(/smartcardweb/pages/images/sfan.gif)"
                                                      onclick="javascript:checkcfgfee(<%=gid %>);"><br><br><font class="��ʽ13"><%=name%></font></li>
                                    <%
                                        }else{
                                    %>   
                                           <li onmouseup="this.style.background='url(/smartcardweb/pages/images/sfan.gif)'" 
                                                    onmousedown="this.style.background='url(/smartcardweb/pages/images/sfana.gif)'"
                                                    style="cursor: hand; background: url(/smartcardweb/pages/images/sfan.gif)"
                                                       onclick="javascript:alert('������δ��ͨ');"><br><br><font class="��ʽ14"><%=name%></font></li>
                                            <%
                                        }                                               
                                    }
                                }
                                
                             %>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sfan.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/sfana.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/sfan.gif)"
                            onclick="javascript: window.location='/smartcardweb/index.do';"><br><br><font class="��ʽ13">�� &nbsp;&nbsp;&nbsp;&nbsp;��</font></li>

                    </ul>
                </div>
            </div>
             <div id="Layer12">
                <div id="mid_center">
                    <ul>
                      <% 
                          for(int i=5;i<cfgitemArr.length;i++){
                              Configitem cfgitem = cfgitemArr[i];
                              String starttime = cfgitem.getStartTime();
                              String endtime = cfgitem.getEndTime();
                              String display = cfgitem.getDisplay();
                              String gid = cfgitem.getGid();
                              String shopid = cfgitem.getShopId();
                              String name = cfgitem.getName();
                              String now = DateUtil.getNow("yyyy-MM-dd");
                              if("true".equals(display)){
                                  if(DateUtil.checkSpecialTimeSequence(starttime,now,"yyyy-MM-dd")<=0 && DateUtil.checkSpecialTimeSequence(endtime,now,"yyyy-MM-dd")>=0){
                        %>

                                      <li><br><font class="��ʽ13">��ʼ��<%=starttime%></font><br><font class="��ʽ13">��ֹ��<%=endtime%></font></li>
                              <%
                                  }else{
                              %>   
                                     <li><br><font class="��ʽ13">��ʼ��<%=starttime%></font><br><font class="��ʽ13">��ֹ��<%=endtime%></font></li>
                                      <%
                                  }                                               
                              }
                          }
                          
                       %>

                    </ul>
                </div>
            </div>
        </div>
        <div id="bottom"></div>
        <form action="/smartcardweb/cfgfeeputin.do" method="post"
            name="selectform">
            <input type="hidden" name="gid" />
        </form>
         <object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
					width="0" height="0"
			codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
    </body>
</html>
