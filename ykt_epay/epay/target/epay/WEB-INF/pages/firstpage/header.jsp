 <%@page pageEncoding="UTF-8"%>
 <%@ include file="../tiles/include.jsp"%>
 <%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
                    .getAttribute("STYLE")
                    : "default";
            String context = request.getScheme() + "://"
                    + request.getServerName() + ":" + request.getServerPort()
                    + request.getContextPath();
                    String stylePath = context + "/theme/style/" + style;
 %>
