<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
%>
<table class="header" CELLPADDING="0" CELLSPACING="0">
    <TH>
        <td class="hTop">&nbsp;</td>
    </TH>
</table>
