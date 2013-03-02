<%@ include file="/html/extportlet/ecard/hitinfo/init.jsp"%>
<%
    ResultPage curpage = (ResultPage) request.getAttribute("result");
    List list = curpage.getList();
    SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<!-- content table -->
<table width="100%" border="0" cellspacing="0" cellpadding="0">
    <c:if test="<%=PermissionUtil.hasHitinfoAdmin(request)%>">
        <tr>
            <td width="166" class="text_brown">

                <a class="txt_or"
                    href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardhitadmin" /></portlet:renderURL>">
                    <bean:message key="ecard.management" /> </a>
            </td>
        </tr>
    </c:if>
    <tr height="15px">
        <td>
            &nbsp;
        </td>
    </tr>
    <%
        int i = 0;
        Iterator it = list.iterator();
        while (it.hasNext()) {
            HitInfoResult hitInfo = (HitInfoResult) it.next();
            String infoType = hitInfo.getInfoType();
            String[] urlInfos = TypeMappingUtil.getPortletURLInfo(infoType);
    %>
    <tr height="20px">
        <td>
            <img src="/html/extthemes/classic/images/ecard/jiantou.jpg" width="8"
                height="8">
            <%
                if (infoType.equals(EcardConstants.INFORMATION_DOCUMENT_TYPE)) {
                        String[] attachIds = StringUtil.split(hitInfo
                                .getAttachments(), EcardConstants.DELIMITER);
            %>

            <a href="<%=urlInfos[1]%>?id=<%=attachIds[0]%>"
                class="blue_link_line"><%=hitInfo.getTitle()%>(<%=format.format((Date) hitInfo.getCreateDate())%>)</a>
            &nbsp;&nbsp;
            <%
                } else if (infoType.indexOf(EcardConstants.INFORMATION_FAQ_TYPE
                            + ".") == 0) {
            %>
            <a
                href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="<%=urlInfos[1]%>" /></portlet:renderURL>&subid=<%=infoType%>"
                class="blue_link_line"><%=hitInfo.getTitle()%>(<%=format.format((Date) hitInfo.getCreateDate())%>)</a>
            &nbsp;&nbsp;
            <%
                } else {
            %>
            <a
                href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="<%=urlInfos[1]%>" /></portlet:renderURL>&id=<%=hitInfo.getInfoId()%>"
                class="blue_link_line"><%=hitInfo.getTitle()%>(<%=format.format((Date) hitInfo.getCreateDate())%>)</a>
            &nbsp;&nbsp;
            <%
                }
            %>
        </td>
    </tr>
    <%
        i++;
        }
        for (int j = 10; j <= 10 - i; j--) {
    %>
    <tr height="20px">
        <td>
            &nbsp;
        </td>
    </tr>
    <%
        }
    %>

    <tr height="15px">
        <td>
            &nbsp;
        </td>
    </tr>
    <tr>
        <td align=right>
            <a class=text_brown
                href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardhitview" /></portlet:renderURL>">
                <bean:message key="ecard.more" />>></a>
        </td>
    </tr>
</table>
<!-- content table -->