
package com.kingstargroup.advquery.service;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.xml.bind.JAXBElement;
import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfguid;
import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfstring;
import org.datacontract.schemas._2004._07.saff.ArrayOfOrganizationalUnit;
import org.datacontract.schemas._2004._07.saff.ArrayOfOrganizationalUnitRoleRelation;
import org.datacontract.schemas._2004._07.saff.ArrayOfRole;
import org.datacontract.schemas._2004._07.saff.ArrayOfUser;
import org.datacontract.schemas._2004._07.saff.ArrayOfViewUserOrganizationalUnitRole;
import org.datacontract.schemas._2004._07.saff.OrganizationalUnit;
import org.datacontract.schemas._2004._07.saff.OrganizationalUnitRoleRelation;
import org.datacontract.schemas._2004._07.saff.Role;
import org.datacontract.schemas._2004._07.saff.User;
import org.datacontract.schemas._2004._07.saff.ViewUserOrganizationalUnitRole;
import org.datacontract.schemas._2004._07.telerik_web.ArrayOfRadTreeNodeData;
import org.datacontract.schemas._2004._07.telerik_web.RadTreeNodeData;

@WebService(name = "IOrganizationService", targetNamespace = "http://tempuri.org/")
@SOAPBinding(use = SOAPBinding.Use.LITERAL, parameterStyle = SOAPBinding.ParameterStyle.WRAPPED)
public interface IOrganizationService {


    @WebMethod(operationName = "GetUsersByOrganizationalUnitRoleRelation", action = "http://tempuri.org/IOrganizationService/GetUsersByOrganizationalUnitRoleRelation")
    @WebResult(name = "GetUsersByOrganizationalUnitRoleRelationResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfViewUserOrganizationalUnitRole getUsersByOrganizationalUnitRoleRelation(
        @WebParam(name = "organizationalUnitRoleRelationId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitRoleRelationId,
        @WebParam(name = "isDefault", targetNamespace = "http://tempuri.org/")
        Boolean isDefault);

    @WebMethod(operationName = "IsUserInRole", action = "http://tempuri.org/IOrganizationService/IsUserInRole")
    @WebResult(name = "IsUserInRoleResult", targetNamespace = "http://tempuri.org/")
    public Boolean isUserInRole(
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId,
        @WebParam(name = "roleId", targetNamespace = "http://tempuri.org/")
        String roleId);

    @WebMethod(operationName = "GetUser", action = "http://tempuri.org/IOrganizationService/GetUser")
    @WebResult(name = "GetUserResult", targetNamespace = "http://tempuri.org/")
    public  User getUser(
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId);

    @WebMethod(operationName = "GetOrganizationalUnitsByIds", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnitsByIds")
    @WebResult(name = "GetOrganizationalUnitsByIdsResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfOrganizationalUnit getOrganizationalUnitsByIds(
        @WebParam(name = "ids", targetNamespace = "http://tempuri.org/")
         ArrayOfguid ids);

    @WebMethod(operationName = "GetOrganizationalUnitRoleRelation", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnitRoleRelation")
    @WebResult(name = "GetOrganizationalUnitRoleRelationResult", targetNamespace = "http://tempuri.org/")
    public  OrganizationalUnitRoleRelation getOrganizationalUnitRoleRelation(
        @WebParam(name = "organizationalUnitRoleId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitRoleId);

    @WebMethod(operationName = "GetOrganizationalUnitsByParentOrganizationalUnit", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnitsByParentOrganizationalUnit")
    @WebResult(name = "GetOrganizationalUnitsByParentOrganizationalUnitResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfOrganizationalUnit getOrganizationalUnitsByParentOrganizationalUnit(
        @WebParam(name = "parentOrganizationalUnitId", targetNamespace = "http://tempuri.org/")
        String parentOrganizationalUnitId,
        @WebParam(name = "recursive", targetNamespace = "http://tempuri.org/")
        Boolean recursive);

    @WebMethod(operationName = "GetSelectedUsersByTicketID", action = "http://tempuri.org/IOrganizationService/GetSelectedUsersByTicketID")
    @WebResult(name = "GetSelectedUsersByTicketIDResult", targetNamespace = "http://tempuri.org/")
    public ArrayOfguid getSelectedUsersByTicketID(
        @WebParam(name = "ticketID", targetNamespace = "http://tempuri.org/")
        String ticketID);

    @WebMethod(operationName = "GetUsersByIdNos", action = "http://tempuri.org/IOrganizationService/GetUsersByIdNos")
    @WebResult(name = "GetUsersByIdNosResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfUser getUsersByIdNos(
        @WebParam(name = "idNos", targetNamespace = "http://tempuri.org/")
         ArrayOfstring idNos);

    @WebMethod(operationName = "GetSelectedObjectIdsByTicketID", action = "http://tempuri.org/IOrganizationService/GetSelectedObjectIdsByTicketID")
    @WebResult(name = "GetSelectedObjectIdsByTicketIDResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfguid getSelectedObjectIdsByTicketID(
        @WebParam(name = "ticketID", targetNamespace = "http://tempuri.org/")
        String ticketID,
        @WebParam(name = "objectType", targetNamespace = "http://tempuri.org/")
         String objectType);

    @WebMethod(operationName = "PrepareTicketID", action = "http://tempuri.org/IOrganizationService/PrepareTicketID")
    @WebResult(name = "PrepareTicketIDResult", targetNamespace = "http://tempuri.org/")
    public String prepareTicketID(
        @WebParam(name = "userIds", targetNamespace = "http://tempuri.org/")
         ArrayOfguid userIds,
        @WebParam(name = "organizationalUnitIds", targetNamespace = "http://tempuri.org/")
         ArrayOfguid organizationalUnitIds,
        @WebParam(name = "roleIds", targetNamespace = "http://tempuri.org/")
         ArrayOfguid roleIds,
        @WebParam(name = "OrganizationalUnitRoleRelationGUIDs", targetNamespace = "http://tempuri.org/")
         ArrayOfguid OrganizationalUnitRoleRelationGUIDs,
        @WebParam(name = "privilegeGroupGUIDs", targetNamespace = "http://tempuri.org/")
         ArrayOfguid privilegeGroupGUIDs);

    @WebMethod(operationName = "GetRole", action = "http://tempuri.org/IOrganizationService/GetRole")
    @WebResult(name = "GetRoleResult", targetNamespace = "http://tempuri.org/")
    public  Role getRole(
        @WebParam(name = "roleId", targetNamespace = "http://tempuri.org/")
        String roleId);

    @WebMethod(operationName = "GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleId", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleId")
    @WebResult(name = "GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResult", targetNamespace = "http://tempuri.org/")
    public  OrganizationalUnitRoleRelation getOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleId(
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId,
        @WebParam(name = "roleId", targetNamespace = "http://tempuri.org/")
        String roleId);

    @WebMethod(operationName = "GetUsersByOrganizationalUnit", action = "http://tempuri.org/IOrganizationService/GetUsersByOrganizationalUnit")
    @WebResult(name = "GetUsersByOrganizationalUnitResult", targetNamespace = "http://tempuri.org/")
    public ArrayOfViewUserOrganizationalUnitRole getUsersByOrganizationalUnit(
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId,
        @WebParam(name = "recursive", targetNamespace = "http://tempuri.org/")
        Boolean recursive,
        @WebParam(name = "isDefault", targetNamespace = "http://tempuri.org/")
        Boolean isDefault);

    @WebMethod(operationName = "IsUserInOrganizationalUnit", action = "http://tempuri.org/IOrganizationService/IsUserInOrganizationalUnit")
    @WebResult(name = "IsUserInOrganizationalUnitResult", targetNamespace = "http://tempuri.org/")
    public Boolean isUserInOrganizationalUnit(
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId,
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId,
        @WebParam(name = "recursive", targetNamespace = "http://tempuri.org/")
        Boolean recursive);

    @WebMethod(operationName = "GetDirectSupervisorOrganizationalUnitRoleRelation", action = "http://tempuri.org/IOrganizationService/GetDirectSupervisorOrganizationalUnitRoleRelation")
    @WebResult(name = "GetDirectSupervisorOrganizationalUnitRoleRelationResult", targetNamespace = "http://tempuri.org/")
    public  OrganizationalUnitRoleRelation getDirectSupervisorOrganizationalUnitRoleRelation(
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId,
        @WebParam(name = "directSupervisorRoleId", targetNamespace = "http://tempuri.org/")
        String directSupervisorRoleId,
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId);

    @WebMethod(operationName = "GetOrganizationalUnits", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnits")
    @WebResult(name = "GetOrganizationalUnitsResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfOrganizationalUnit getOrganizationalUnits();

    @WebMethod(operationName = "GetSelectedRolesByTicketID", action = "http://tempuri.org/IOrganizationService/GetSelectedRolesByTicketID")
    @WebResult(name = "GetSelectedRolesByTicketIDResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfguid getSelectedRolesByTicketID(
        @WebParam(name = "ticketID", targetNamespace = "http://tempuri.org/")
        String ticketID);

    @WebMethod(operationName = "GetChildOrganizationalUnits", action = "http://tempuri.org/IOrganizationService/GetChildOrganizationalUnits")
    @WebResult(name = "GetChildOrganizationalUnitsResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfRadTreeNodeData getChildOrganizationalUnits(
        @WebParam(name = "node", targetNamespace = "http://tempuri.org/")
         RadTreeNodeData node);

    @WebMethod(operationName = "GetOrganizationalUnitRoleRelationsByIds", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnitRoleRelationsByIds")
    @WebResult(name = "GetOrganizationalUnitRoleRelationsByIdsResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfOrganizationalUnitRoleRelation getOrganizationalUnitRoleRelationsByIds(
        @WebParam(name = "ids", targetNamespace = "http://tempuri.org/")
         ArrayOfguid ids);

    @WebMethod(operationName = "GetSelectedObjectNamesByTicketID", action = "http://tempuri.org/IOrganizationService/GetSelectedObjectNamesByTicketID")
    @WebResult(name = "GetSelectedObjectNamesByTicketIDResult", targetNamespace = "http://tempuri.org/")
    public  String getSelectedObjectNamesByTicketID(
        @WebParam(name = "ticketID", targetNamespace = "http://tempuri.org/")
        String ticketID,
        @WebParam(name = "objectType", targetNamespace = "http://tempuri.org/")
         String objectType);

    @WebMethod(operationName = "GetOrganizationalUnitRolesByUserId", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnitRolesByUserId")
    @WebResult(name = "GetOrganizationalUnitRolesByUserIdResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfViewUserOrganizationalUnitRole getOrganizationalUnitRolesByUserId(
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId);

    @WebMethod(operationName = "IsOrganizationalUnitInOrganizationalUnit", action = "http://tempuri.org/IOrganizationService/IsOrganizationalUnitInOrganizationalUnit")
    @WebResult(name = "IsOrganizationalUnitInOrganizationalUnitResult", targetNamespace = "http://tempuri.org/")
    public Boolean isOrganizationalUnitInOrganizationalUnit(
        @WebParam(name = "offspringOrganizationalUnitId", targetNamespace = "http://tempuri.org/")
        String offspringOrganizationalUnitId,
        @WebParam(name = "ancestorOrganizationalUnitId", targetNamespace = "http://tempuri.org/")
        String ancestorOrganizationalUnitId,
        @WebParam(name = "recursive", targetNamespace = "http://tempuri.org/")
        Boolean recursive);

    @WebMethod(operationName = "IsUserInOrganizationalUnitRole", action = "http://tempuri.org/IOrganizationService/IsUserInOrganizationalUnitRole")
    @WebResult(name = "IsUserInOrganizationalUnitRoleResult", targetNamespace = "http://tempuri.org/")
    public Boolean isUserInOrganizationalUnitRole(
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId,
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId,
        @WebParam(name = "roleId", targetNamespace = "http://tempuri.org/")
        String roleId);

    @WebMethod(operationName = "GetUsersByIds", action = "http://tempuri.org/IOrganizationService/GetUsersByIds")
    @WebResult(name = "GetUsersByIdsResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfUser getUsersByIds(
        @WebParam(name = "ids", targetNamespace = "http://tempuri.org/")
         ArrayOfguid ids);

    @WebMethod(operationName = "GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds")
    @WebResult(name = "GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfOrganizationalUnitRoleRelation getOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds(
        @WebParam(name = "organizationalUnitIds", targetNamespace = "http://tempuri.org/")
         ArrayOfguid organizationalUnitIds,
        @WebParam(name = "roleIds", targetNamespace = "http://tempuri.org/")
         ArrayOfguid roleIds);

    @WebMethod(operationName = "GetSelectedOrganizationalUnitRoleRelationsByTicketID", action = "http://tempuri.org/IOrganizationService/GetSelectedOrganizationalUnitRoleRelationsByTicketID")
    @WebResult(name = "GetSelectedOrganizationalUnitRoleRelationsByTicketIDResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfguid getSelectedOrganizationalUnitRoleRelationsByTicketID(
        @WebParam(name = "ticketID", targetNamespace = "http://tempuri.org/")
        String ticketID);

    @WebMethod(operationName = "GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnit", action = "http://tempuri.org/IOrganizationService/GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnit")
    @WebResult(name = "GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResult", targetNamespace = "http://tempuri.org/")
    public  OrganizationalUnitRoleRelation getSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnit(
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId,
        @WebParam(name = "directSupervisorRoleId", targetNamespace = "http://tempuri.org/")
        String directSupervisorRoleId,
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId);

    @WebMethod(operationName = "GetUsers", action = "http://tempuri.org/IOrganizationService/GetUsers")
    @WebResult(name = "GetUsersResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfUser getUsers();

    @WebMethod(operationName = "GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnit", action = "http://tempuri.org/IOrganizationService/GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnit")
    @WebResult(name = "GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult", targetNamespace = "http://tempuri.org/")
    public  OrganizationalUnitRoleRelation getSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnit(
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId,
        @WebParam(name = "directSupervisorRoleId", targetNamespace = "http://tempuri.org/")
        String directSupervisorRoleId,
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId);

    @WebMethod(operationName = "GetUsersByRole", action = "http://tempuri.org/IOrganizationService/GetUsersByRole")
    @WebResult(name = "GetUsersByRoleResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfViewUserOrganizationalUnitRole getUsersByRole(
        @WebParam(name = "roleId", targetNamespace = "http://tempuri.org/")
        String roleId,
        @WebParam(name = "isDefault", targetNamespace = "http://tempuri.org/")
        Boolean isDefault);

    @WebMethod(operationName = "GetRolesByIds", action = "http://tempuri.org/IOrganizationService/GetRolesByIds")
    @WebResult(name = "GetRolesByIdsResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfRole getRolesByIds(
        @WebParam(name = "ids", targetNamespace = "http://tempuri.org/")
         ArrayOfguid ids);

    @WebMethod(operationName = "GetRoles", action = "http://tempuri.org/IOrganizationService/GetRoles")
    @WebResult(name = "GetRolesResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfRole getRoles();

    @WebMethod(operationName = "GetDefaultOrganizationalUnitRoleByUserId", action = "http://tempuri.org/IOrganizationService/GetDefaultOrganizationalUnitRoleByUserId")
    @WebResult(name = "GetDefaultOrganizationalUnitRoleByUserIdResult", targetNamespace = "http://tempuri.org/")
    public  ViewUserOrganizationalUnitRole getDefaultOrganizationalUnitRoleByUserId(
        @WebParam(name = "userId", targetNamespace = "http://tempuri.org/")
        String userId);

    @WebMethod(operationName = "GetSelectedOrganizationalUnitsByTicketID", action = "http://tempuri.org/IOrganizationService/GetSelectedOrganizationalUnitsByTicketID")
    @WebResult(name = "GetSelectedOrganizationalUnitsByTicketIDResult", targetNamespace = "http://tempuri.org/")
    public ArrayOfguid getSelectedOrganizationalUnitsByTicketID(
        @WebParam(name = "ticketID", targetNamespace = "http://tempuri.org/")
        String ticketID);

    @WebMethod(operationName = "GetAncestorOrganizationalUnitsById", action = "http://tempuri.org/IOrganizationService/GetAncestorOrganizationalUnitsById")
    @WebResult(name = "GetAncestorOrganizationalUnitsByIdResult", targetNamespace = "http://tempuri.org/")
    public  ArrayOfOrganizationalUnit getAncestorOrganizationalUnitsById(
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId);

    @WebMethod(operationName = "GetOrganizationalUnit", action = "http://tempuri.org/IOrganizationService/GetOrganizationalUnit")
    @WebResult(name = "GetOrganizationalUnitResult", targetNamespace = "http://tempuri.org/")
    public  OrganizationalUnit getOrganizationalUnit(
        @WebParam(name = "organizationalUnitId", targetNamespace = "http://tempuri.org/")
        String organizationalUnitId);

}
