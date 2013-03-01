
package com.kingstargroup.advquery.service;

import javax.jws.WebService;
import org.datacontract.schemas._2004._07.saff.User;
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

import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfguid;
import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfstring;

@WebService(serviceName = "OrganizationService", targetNamespace = "http://tempuri.org/", endpointInterface = "pl.tomeks.client.IOrganizationService")
public class OrganizationServiceImpl
    implements IOrganizationService
{


    public  ArrayOfViewUserOrganizationalUnitRole getUsersByOrganizationalUnitRoleRelation(String organizationalUnitRoleRelationId, Boolean isDefault) {
        throw new UnsupportedOperationException();
    }

    public Boolean isUserInRole(String userId, String roleId) {
        throw new UnsupportedOperationException();
    }

    public  User getUser(String userId) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfOrganizationalUnit getOrganizationalUnitsByIds( ArrayOfguid ids) {
        throw new UnsupportedOperationException();
    }

    public  OrganizationalUnitRoleRelation getOrganizationalUnitRoleRelation(String organizationalUnitRoleId) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfOrganizationalUnit getOrganizationalUnitsByParentOrganizationalUnit(String parentOrganizationalUnitId, Boolean recursive) {
        throw new UnsupportedOperationException();
    }

    public ArrayOfguid getSelectedUsersByTicketID(String ticketID) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfUser getUsersByIdNos( ArrayOfstring idNos) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfguid getSelectedObjectIdsByTicketID(String ticketID,  String objectType) {
        throw new UnsupportedOperationException();
    }

    public String prepareTicketID( ArrayOfguid userIds,  ArrayOfguid organizationalUnitIds,  ArrayOfguid roleIds,  ArrayOfguid OrganizationalUnitRoleRelationGUIDs,  ArrayOfguid privilegeGroupGUIDs) {
        throw new UnsupportedOperationException();
    }

    public  Role getRole(String roleId) {
        throw new UnsupportedOperationException();
    }

    public  OrganizationalUnitRoleRelation getOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleId(String organizationalUnitId, String roleId) {
        throw new UnsupportedOperationException();
    }

    public ArrayOfViewUserOrganizationalUnitRole getUsersByOrganizationalUnit(String organizationalUnitId, Boolean recursive, Boolean isDefault) {
        throw new UnsupportedOperationException();
    }

    public Boolean isUserInOrganizationalUnit(String userId, String organizationalUnitId, Boolean recursive) {
        throw new UnsupportedOperationException();
    }

    public  OrganizationalUnitRoleRelation getDirectSupervisorOrganizationalUnitRoleRelation(String organizationalUnitId, String directSupervisorRoleId, String userId) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfOrganizationalUnit getOrganizationalUnits() {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfguid getSelectedRolesByTicketID(String ticketID) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfRadTreeNodeData getChildOrganizationalUnits( RadTreeNodeData node) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfOrganizationalUnitRoleRelation getOrganizationalUnitRoleRelationsByIds( ArrayOfguid ids) {
        throw new UnsupportedOperationException();
    }

    public  String getSelectedObjectNamesByTicketID(String ticketID,  String objectType) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfViewUserOrganizationalUnitRole getOrganizationalUnitRolesByUserId(String userId) {
        throw new UnsupportedOperationException();
    }

    public Boolean isOrganizationalUnitInOrganizationalUnit(String offspringOrganizationalUnitId, String ancestorOrganizationalUnitId, Boolean recursive) {
        throw new UnsupportedOperationException();
    }

    public Boolean isUserInOrganizationalUnitRole(String userId, String organizationalUnitId, String roleId) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfUser getUsersByIds( ArrayOfguid ids) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfOrganizationalUnitRoleRelation getOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds( ArrayOfguid organizationalUnitIds,  ArrayOfguid roleIds) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfguid getSelectedOrganizationalUnitRoleRelationsByTicketID(String ticketID) {
        throw new UnsupportedOperationException();
    }

    public  OrganizationalUnitRoleRelation getSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnit(String organizationalUnitId, String directSupervisorRoleId, String userId) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfUser getUsers() {
        throw new UnsupportedOperationException();
    }

    public  OrganizationalUnitRoleRelation getSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnit(String organizationalUnitId, String directSupervisorRoleId, String userId) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfViewUserOrganizationalUnitRole getUsersByRole(String roleId, Boolean isDefault) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfRole getRolesByIds( ArrayOfguid ids) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfRole getRoles() {
        throw new UnsupportedOperationException();
    }

    public  ViewUserOrganizationalUnitRole getDefaultOrganizationalUnitRoleByUserId(String userId) {
        throw new UnsupportedOperationException();
    }

    public ArrayOfguid getSelectedOrganizationalUnitsByTicketID(String ticketID) {
        throw new UnsupportedOperationException();
    }

    public  ArrayOfOrganizationalUnit getAncestorOrganizationalUnitsById(String organizationalUnitId) {
        throw new UnsupportedOperationException();
    }

    public  OrganizationalUnit getOrganizationalUnit(String organizationalUnitId) {
        throw new UnsupportedOperationException();
    }

}
