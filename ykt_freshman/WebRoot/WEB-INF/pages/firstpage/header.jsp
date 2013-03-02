<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
					String stylePath = context + "/pages/style/" + style;
%>
<table class="header" CELLPADDING="0" CELLSPACING="0">
    <TH>
        <td align="center" valign="top">
				<img src="<%=stylePath%>/images/logintop.gif" border="0">
			</td>
    </TH>
</table>
