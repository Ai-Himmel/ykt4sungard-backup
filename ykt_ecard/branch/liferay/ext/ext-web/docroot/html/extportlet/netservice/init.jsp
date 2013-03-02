<%@ include file="/html/extcommon/init.jsp" %>
<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="org.apache.struts.validator.DynaValidatorForm" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.ResultPage" %>
<%@ page import="com.kingstargroup.ecard.util.EcardConstants" %>
<%@ page import="com.kingstargroup.ecard.util.PermissionUtil" %>
<%@ page import="com.kingstargroup.ecard.exceptions.FileSizeException" %>
<%@ page import="com.kingstargroup.ecard.exceptions.FileNameException" %>
<%@ page import="com.kingstargroup.ecard.util.DateFormatUtil" %>
<portlet:defineObjects />