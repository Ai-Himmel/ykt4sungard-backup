<%@ include file="/html/common/init.jsp" %>
<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="org.apache.struts.validator.DynaValidatorForm" %>
<%@ page import="com.liferay.util.StringUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.information.EcardInformation" %>
<%@ page import="com.kingstargroup.ecard.hibernate.infotype.InfoType" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.ResultPage" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.InformationUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.InfoTypeUtil" %>
<%@ page import="com.kingstargroup.ecard.util.EcardConstants" %>
<%@ page import="com.kingstargroup.ecard.util.PermissionUtil" %>
<portlet:defineObjects />