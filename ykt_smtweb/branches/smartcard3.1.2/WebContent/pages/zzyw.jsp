<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.ConfigMenu" %>
<html>
    <head>
        <title>增值业务</title>
        <meta http-equiv="Content-Type" content="text/html; charset=GBK" />
        <style type="text/css">
		</style>
       <link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
    </head>

    <body scroll="no">
        <div id="mid_top"></div>
        <div id="middle">
            <div id="Layer2">
                <div id="mid_center1">
                    <ul>
                    <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/zysf.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/zysf2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/zysf.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_cfgfeebusiness")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/cfgfeebusiness.do';"></li>
                          <!-- card 2 card -->
                          <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/kkzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/kkzz2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/kkzz.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_card_card")) { out.print(" display:none; "); }%>"
                            onclick="javascript:window.location='/smartcardweb/cardcardbusiness.do';"></li>   
                         <!--通用水控转账 --> 
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/waterbusiness.do';"></li>
                             <!-- 凯路水控转账 --> 
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water_kl")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/waterbusinesskl.do';"></li>
                          <!-- 云交职水控-->
                          <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water_yjz")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/watershopchoosectlyjz.do';"></li>
                          <!-- 999水控 -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water_999")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/waterbusiness999.do';"></li>
                            <!-- 电控转账-->
                          <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/dk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/dka.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/dk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_elec")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/elecbusiness.do';"></li>                        
							<!-- 网费转账 -->
                           <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sjsw.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/sjsw2.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sjsw.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_net")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/netcomputebusiness.do';"></li> 
                    </ul>
                </div>
            </div>
            <div id="Layer3">
                <div id="mid_center2">
                    <ul>                        
                       <li>&nbsp;</li>
                        <li>&nbsp;</li>
                        <li>&nbsp;</li>                        
                        <%if(request.getSession().getAttribute("cutid")==null){ %>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/fhcd.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/index.jsp';"></li>
                       <%}else{%>
                          <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/reset.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/reseta.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/reset.gif)"
                            onclick="javascript: window.location='/smartcardweb/usrexit.do';"></li>
                       <%} %>

                    </ul>
                </div>
            </div>
        </div>
        <div id="bottom"></div>
         <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0"></object>
    </body>
</html>
