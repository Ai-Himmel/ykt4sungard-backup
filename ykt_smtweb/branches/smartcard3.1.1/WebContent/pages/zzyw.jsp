<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page import="com.kingstargroup.fdykt.ConfigMenu" %>
<html>
    <head>
        <title>��ֵҵ��</title>
        <meta http-equiv="Content-Type" content="text/html; charset=GBK" />
        <style type="text/css">
        </style>
       <link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
            type="text/css" />
    </head>
        <%
        String hd_water_control=KSConfiguration.getInstance().getProperty("hd_water_control","1192"); 
        %>

    <script>
       function chooseshop(pama){
         document.all.moneyForm.tradecode.value=pama;
         moneyForm.submit();
       }
    </script>
    <body scroll="no">
        <form name="moneyForm" action="/smartcardweb/waterbusinessctlyjz.do"
            method="post">
            <input type="hidden" name="tradecode" value="0" />
        </form>
        <div id="mid_top"></div>
        <div id="middle">
            <div id="Layer2">
                <div id="mid_center1">
                    <ul>
                            <!-- �Զ���ר���շ� --> 
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/zysf.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/zysf2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/zysf.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_cfgfeebusiness")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/cfgfeebusiness.do';"></li>
                            <!-- ��·ˮ��ת�� --> 
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water_kl")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/waterbusinesskl.do';"></li>
                            <!-- �ƽ�ְˮ��-->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water_yjz")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/watershopchoosectlyjz.do';"></li>
                            <!-- ��൥��ˮ�� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water_hd")) { out.print(" display:none; "); }%>"
                            onclick="javascript: chooseshop('<%=hd_water_control%>');"></li>
                            <!-- 999ˮ�� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water_999")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/waterbusiness999.do';"></li>
                            <!-- ���ת��-->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/dk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/dka.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/dk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_elec")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/elecbusiness.do';"></li>   
                            <!-- �����󱾲����ת��-->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/dk_local.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/dka_local.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/dk_local.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_elec_local")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/elecbusiness.do?elecIndex=0';"></li>
                            <!-- �����������ת��-->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/dk_east.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/dka_east.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/dk_east.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_elec_east")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/elecbusiness.do?elecIndex=1';"></li>                     
                            <!-- ����ת�� -�ֹ������˺� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sjsw.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/sjsw2.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sjsw.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_net")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/netcomputebusiness.do';"></li> 
                            <!-- ����ת�� -���˺� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sjsw.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/sjsw2.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sjsw.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_net_bind")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/netcomputebusinessbind.do';"></li> 
                            <!-- ��ũ�ɶ�У������ת�� -�ֹ������˺� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/wfzz_chd.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/wfzza_chd.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/wfzz_chd.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_net_chd")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/netcomputebusiness.do?netIndex=0';"></li> 
                            <!-- ��ũ������У������ת�� -�ֹ������˺� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/wfzz_djy.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/wfzza_djy.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/wfzz_djy.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_net_djy")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/netcomputebusiness.do?netIndex=1';"></li> 
                            <!-- ��ũ�Ű�У������ת�� -�ֹ������˺� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/wfzz_yan.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/wfzza_yan.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/wfzz_yan.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_net_yan")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/netcomputebusiness.do?netIndex=2';"></li> 
                            <!-- ���ѶԽ�  ������ͨ�˺�(H3C) -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/swzhkt.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/swzhkt2.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/swzhkt.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_net_bind_openacc")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/netcomputebusinessbindopenacc.do';"></li>
                    </ul>
                </div>
            </div>
            <div id="Layer3">
                <div id="mid_center2">
                    <ul>                        
                            <!-- ����ת�� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/kkzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/kkzz2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/kkzz.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_card_card")) { out.print(" display:none; "); }%>"
                            onclick="javascript:window.location='/smartcardweb/cardcardbusiness.do';"></li>   
                             <!-- ����Ǯ�� -->
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/dzqb.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/dzqb2.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/dzqb.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_epay")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/epaybusiness.do';"></li>
                            <li>&nbsp;</li>
                            <li>&nbsp;</li>                        
                            <%if(request.getSession().getAttribute("cardphyid")==null){ %>
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
