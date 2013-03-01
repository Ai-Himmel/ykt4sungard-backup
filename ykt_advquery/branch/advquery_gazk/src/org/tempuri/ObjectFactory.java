
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;
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


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the org.tempuri package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _GetOrganizationalUnitsByIdsResponseGetOrganizationalUnitsByIdsResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitsByIdsResult");
    private final static QName _GetSelectedObjectIdsByTicketIDObjectType_QNAME = new QName("http://tempuri.org/", "objectType");
    private final static QName _GetUsersByIdNosResponseGetUsersByIdNosResult_QNAME = new QName("http://tempuri.org/", "GetUsersByIdNosResult");
    private final static QName _GetSelectedRolesByTicketIDResponseGetSelectedRolesByTicketIDResult_QNAME = new QName("http://tempuri.org/", "GetSelectedRolesByTicketIDResult");
    private final static QName _GetRolesByIdsIds_QNAME = new QName("http://tempuri.org/", "ids");
    private final static QName _GetOrganizationalUnitsByParentOrganizationalUnitResponseGetOrganizationalUnitsByParentOrganizationalUnitResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitsByParentOrganizationalUnitResult");
    private final static QName _GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponseGetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResult");
    private final static QName _GetChildOrganizationalUnitsNode_QNAME = new QName("http://tempuri.org/", "node");
    private final static QName _GetOrganizationalUnitsResponseGetOrganizationalUnitsResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitsResult");
    private final static QName _GetOrganizationalUnitRoleRelationResponseGetOrganizationalUnitRoleRelationResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitRoleRelationResult");
    private final static QName _GetSelectedObjectIdsByTicketIDResponseGetSelectedObjectIdsByTicketIDResult_QNAME = new QName("http://tempuri.org/", "GetSelectedObjectIdsByTicketIDResult");
    private final static QName _GetOrganizationalUnitRoleRelationsByIdsResponseGetOrganizationalUnitRoleRelationsByIdsResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitRoleRelationsByIdsResult");
    private final static QName _PrepareTicketIDOrganizationalUnitIds_QNAME = new QName("http://tempuri.org/", "organizationalUnitIds");
    private final static QName _PrepareTicketIDOrganizationalUnitRoleRelationGUIDs_QNAME = new QName("http://tempuri.org/", "OrganizationalUnitRoleRelationGUIDs");
    private final static QName _PrepareTicketIDPrivilegeGroupGUIDs_QNAME = new QName("http://tempuri.org/", "privilegeGroupGUIDs");
    private final static QName _PrepareTicketIDRoleIds_QNAME = new QName("http://tempuri.org/", "roleIds");
    private final static QName _PrepareTicketIDUserIds_QNAME = new QName("http://tempuri.org/", "userIds");
    private final static QName _GetSelectedUsersByTicketIDResponseGetSelectedUsersByTicketIDResult_QNAME = new QName("http://tempuri.org/", "GetSelectedUsersByTicketIDResult");
    private final static QName _GetUserResponseGetUserResult_QNAME = new QName("http://tempuri.org/", "GetUserResult");
    private final static QName _GetRolesByIdsResponseGetRolesByIdsResult_QNAME = new QName("http://tempuri.org/", "GetRolesByIdsResult");
    private final static QName _GetRolesResponseGetRolesResult_QNAME = new QName("http://tempuri.org/", "GetRolesResult");
    private final static QName _GetAncestorOrganizationalUnitsByIdResponseGetAncestorOrganizationalUnitsByIdResult_QNAME = new QName("http://tempuri.org/", "GetAncestorOrganizationalUnitsByIdResult");
    private final static QName _GetUsersByRoleResponseGetUsersByRoleResult_QNAME = new QName("http://tempuri.org/", "GetUsersByRoleResult");
    private final static QName _GetUsersByIdsResponseGetUsersByIdsResult_QNAME = new QName("http://tempuri.org/", "GetUsersByIdsResult");
    private final static QName _GetSelectedObjectNamesByTicketIDResponseGetSelectedObjectNamesByTicketIDResult_QNAME = new QName("http://tempuri.org/", "GetSelectedObjectNamesByTicketIDResult");
    private final static QName _GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponseGetSelectedOrganizationalUnitRoleRelationsByTicketIDResult_QNAME = new QName("http://tempuri.org/", "GetSelectedOrganizationalUnitRoleRelationsByTicketIDResult");
    private final static QName _GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponseGetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResult_QNAME = new QName("http://tempuri.org/", "GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResult");
    private final static QName _GetUsersByIdNosIdNos_QNAME = new QName("http://tempuri.org/", "idNos");
    private final static QName _GetSelectedOrganizationalUnitsByTicketIDResponseGetSelectedOrganizationalUnitsByTicketIDResult_QNAME = new QName("http://tempuri.org/", "GetSelectedOrganizationalUnitsByTicketIDResult");
    private final static QName _GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponseGetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult_QNAME = new QName("http://tempuri.org/", "GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult");
    private final static QName _GetUsersResponseGetUsersResult_QNAME = new QName("http://tempuri.org/", "GetUsersResult");
    private final static QName _GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponseGetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResult");
    private final static QName _GetOrganizationalUnitResponseGetOrganizationalUnitResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitResult");
    private final static QName _GetRoleResponseGetRoleResult_QNAME = new QName("http://tempuri.org/", "GetRoleResult");
    private final static QName _GetChildOrganizationalUnitsResponseGetChildOrganizationalUnitsResult_QNAME = new QName("http://tempuri.org/", "GetChildOrganizationalUnitsResult");
    private final static QName _GetDefaultOrganizationalUnitRoleByUserIdResponseGetDefaultOrganizationalUnitRoleByUserIdResult_QNAME = new QName("http://tempuri.org/", "GetDefaultOrganizationalUnitRoleByUserIdResult");
    private final static QName _GetUsersByOrganizationalUnitResponseGetUsersByOrganizationalUnitResult_QNAME = new QName("http://tempuri.org/", "GetUsersByOrganizationalUnitResult");
    private final static QName _GetUsersByOrganizationalUnitRoleRelationResponseGetUsersByOrganizationalUnitRoleRelationResult_QNAME = new QName("http://tempuri.org/", "GetUsersByOrganizationalUnitRoleRelationResult");
    private final static QName _GetOrganizationalUnitRolesByUserIdResponseGetOrganizationalUnitRolesByUserIdResult_QNAME = new QName("http://tempuri.org/", "GetOrganizationalUnitRolesByUserIdResult");
    private final static QName _GetDirectSupervisorOrganizationalUnitRoleRelationResponseGetDirectSupervisorOrganizationalUnitRoleRelationResult_QNAME = new QName("http://tempuri.org/", "GetDirectSupervisorOrganizationalUnitRoleRelationResult");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: org.tempuri
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitsByIdsResponse }
     * 
     */
    public GetOrganizationalUnitsByIdsResponse createGetOrganizationalUnitsByIdsResponse() {
        return new GetOrganizationalUnitsByIdsResponse();
    }

    /**
     * Create an instance of {@link GetSelectedObjectIdsByTicketID }
     * 
     */
    public GetSelectedObjectIdsByTicketID createGetSelectedObjectIdsByTicketID() {
        return new GetSelectedObjectIdsByTicketID();
    }

    /**
     * Create an instance of {@link GetUsersByIdNosResponse }
     * 
     */
    public GetUsersByIdNosResponse createGetUsersByIdNosResponse() {
        return new GetUsersByIdNosResponse();
    }

    /**
     * Create an instance of {@link GetRolesByIds }
     * 
     */
    public GetRolesByIds createGetRolesByIds() {
        return new GetRolesByIds();
    }

    /**
     * Create an instance of {@link GetSelectedRolesByTicketIDResponse }
     * 
     */
    public GetSelectedRolesByTicketIDResponse createGetSelectedRolesByTicketIDResponse() {
        return new GetSelectedRolesByTicketIDResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitsByParentOrganizationalUnitResponse }
     * 
     */
    public GetOrganizationalUnitsByParentOrganizationalUnitResponse createGetOrganizationalUnitsByParentOrganizationalUnitResponse() {
        return new GetOrganizationalUnitsByParentOrganizationalUnitResponse();
    }

    /**
     * Create an instance of {@link GetUsersByOrganizationalUnitRoleRelation }
     * 
     */
    public GetUsersByOrganizationalUnitRoleRelation createGetUsersByOrganizationalUnitRoleRelation() {
        return new GetUsersByOrganizationalUnitRoleRelation();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleId }
     * 
     */
    public GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleId createGetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleId() {
        return new GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleId();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponse }
     * 
     */
    public GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponse createGetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponse() {
        return new GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponse();
    }

    /**
     * Create an instance of {@link GetChildOrganizationalUnits }
     * 
     */
    public GetChildOrganizationalUnits createGetChildOrganizationalUnits() {
        return new GetChildOrganizationalUnits();
    }

    /**
     * Create an instance of {@link GetDirectSupervisorOrganizationalUnitRoleRelation }
     * 
     */
    public GetDirectSupervisorOrganizationalUnitRoleRelation createGetDirectSupervisorOrganizationalUnitRoleRelation() {
        return new GetDirectSupervisorOrganizationalUnitRoleRelation();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitsResponse }
     * 
     */
    public GetOrganizationalUnitsResponse createGetOrganizationalUnitsResponse() {
        return new GetOrganizationalUnitsResponse();
    }

    /**
     * Create an instance of {@link GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnit }
     * 
     */
    public GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnit createGetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnit() {
        return new GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnit();
    }

    /**
     * Create an instance of {@link GetUsersByOrganizationalUnit }
     * 
     */
    public GetUsersByOrganizationalUnit createGetUsersByOrganizationalUnit() {
        return new GetUsersByOrganizationalUnit();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRoleRelationResponse }
     * 
     */
    public GetOrganizationalUnitRoleRelationResponse createGetOrganizationalUnitRoleRelationResponse() {
        return new GetOrganizationalUnitRoleRelationResponse();
    }

    /**
     * Create an instance of {@link GetSelectedObjectIdsByTicketIDResponse }
     * 
     */
    public GetSelectedObjectIdsByTicketIDResponse createGetSelectedObjectIdsByTicketIDResponse() {
        return new GetSelectedObjectIdsByTicketIDResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnit }
     * 
     */
    public GetOrganizationalUnit createGetOrganizationalUnit() {
        return new GetOrganizationalUnit();
    }

    /**
     * Create an instance of {@link GetAncestorOrganizationalUnitsById }
     * 
     */
    public GetAncestorOrganizationalUnitsById createGetAncestorOrganizationalUnitsById() {
        return new GetAncestorOrganizationalUnitsById();
    }

    /**
     * Create an instance of {@link PrepareTicketID }
     * 
     */
    public PrepareTicketID createPrepareTicketID() {
        return new PrepareTicketID();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRoleRelationsByIdsResponse }
     * 
     */
    public GetOrganizationalUnitRoleRelationsByIdsResponse createGetOrganizationalUnitRoleRelationsByIdsResponse() {
        return new GetOrganizationalUnitRoleRelationsByIdsResponse();
    }

    /**
     * Create an instance of {@link GetSelectedUsersByTicketIDResponse }
     * 
     */
    public GetSelectedUsersByTicketIDResponse createGetSelectedUsersByTicketIDResponse() {
        return new GetSelectedUsersByTicketIDResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRoleRelation }
     * 
     */
    public GetOrganizationalUnitRoleRelation createGetOrganizationalUnitRoleRelation() {
        return new GetOrganizationalUnitRoleRelation();
    }

    /**
     * Create an instance of {@link GetUserResponse }
     * 
     */
    public GetUserResponse createGetUserResponse() {
        return new GetUserResponse();
    }

    /**
     * Create an instance of {@link GetRolesByIdsResponse }
     * 
     */
    public GetRolesByIdsResponse createGetRolesByIdsResponse() {
        return new GetRolesByIdsResponse();
    }

    /**
     * Create an instance of {@link GetRolesResponse }
     * 
     */
    public GetRolesResponse createGetRolesResponse() {
        return new GetRolesResponse();
    }

    /**
     * Create an instance of {@link GetAncestorOrganizationalUnitsByIdResponse }
     * 
     */
    public GetAncestorOrganizationalUnitsByIdResponse createGetAncestorOrganizationalUnitsByIdResponse() {
        return new GetAncestorOrganizationalUnitsByIdResponse();
    }

    /**
     * Create an instance of {@link GetDefaultOrganizationalUnitRoleByUserId }
     * 
     */
    public GetDefaultOrganizationalUnitRoleByUserId createGetDefaultOrganizationalUnitRoleByUserId() {
        return new GetDefaultOrganizationalUnitRoleByUserId();
    }

    /**
     * Create an instance of {@link GetUsersByRoleResponse }
     * 
     */
    public GetUsersByRoleResponse createGetUsersByRoleResponse() {
        return new GetUsersByRoleResponse();
    }

    /**
     * Create an instance of {@link GetUsersByIdsResponse }
     * 
     */
    public GetUsersByIdsResponse createGetUsersByIdsResponse() {
        return new GetUsersByIdsResponse();
    }

    /**
     * Create an instance of {@link PrepareTicketIDResponse }
     * 
     */
    public PrepareTicketIDResponse createPrepareTicketIDResponse() {
        return new PrepareTicketIDResponse();
    }

    /**
     * Create an instance of {@link GetSelectedObjectNamesByTicketIDResponse }
     * 
     */
    public GetSelectedObjectNamesByTicketIDResponse createGetSelectedObjectNamesByTicketIDResponse() {
        return new GetSelectedObjectNamesByTicketIDResponse();
    }

    /**
     * Create an instance of {@link IsUserInOrganizationalUnitRoleResponse }
     * 
     */
    public IsUserInOrganizationalUnitRoleResponse createIsUserInOrganizationalUnitRoleResponse() {
        return new IsUserInOrganizationalUnitRoleResponse();
    }

    /**
     * Create an instance of {@link GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponse }
     * 
     */
    public GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponse createGetSelectedOrganizationalUnitRoleRelationsByTicketIDResponse() {
        return new GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponse();
    }

    /**
     * Create an instance of {@link GetUsersByIds }
     * 
     */
    public GetUsersByIds createGetUsersByIds() {
        return new GetUsersByIds();
    }

    /**
     * Create an instance of {@link IsUserInRole }
     * 
     */
    public IsUserInRole createIsUserInRole() {
        return new IsUserInRole();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds }
     * 
     */
    public GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds createGetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds() {
        return new GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds();
    }

    /**
     * Create an instance of {@link GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponse }
     * 
     */
    public GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponse createGetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponse() {
        return new GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponse();
    }

    /**
     * Create an instance of {@link GetUsersByIdNos }
     * 
     */
    public GetUsersByIdNos createGetUsersByIdNos() {
        return new GetUsersByIdNos();
    }

    /**
     * Create an instance of {@link GetSelectedOrganizationalUnitsByTicketIDResponse }
     * 
     */
    public GetSelectedOrganizationalUnitsByTicketIDResponse createGetSelectedOrganizationalUnitsByTicketIDResponse() {
        return new GetSelectedOrganizationalUnitsByTicketIDResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitsByIds }
     * 
     */
    public GetOrganizationalUnitsByIds createGetOrganizationalUnitsByIds() {
        return new GetOrganizationalUnitsByIds();
    }

    /**
     * Create an instance of {@link GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponse }
     * 
     */
    public GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponse createGetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponse() {
        return new GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponse();
    }

    /**
     * Create an instance of {@link GetUsersResponse }
     * 
     */
    public GetUsersResponse createGetUsersResponse() {
        return new GetUsersResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRolesByUserId }
     * 
     */
    public GetOrganizationalUnitRolesByUserId createGetOrganizationalUnitRolesByUserId() {
        return new GetOrganizationalUnitRolesByUserId();
    }

    /**
     * Create an instance of {@link GetRole }
     * 
     */
    public GetRole createGetRole() {
        return new GetRole();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponse }
     * 
     */
    public GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponse createGetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponse() {
        return new GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnits }
     * 
     */
    public GetOrganizationalUnits createGetOrganizationalUnits() {
        return new GetOrganizationalUnits();
    }

    /**
     * Create an instance of {@link GetSelectedUsersByTicketID }
     * 
     */
    public GetSelectedUsersByTicketID createGetSelectedUsersByTicketID() {
        return new GetSelectedUsersByTicketID();
    }

    /**
     * Create an instance of {@link IsOrganizationalUnitInOrganizationalUnit }
     * 
     */
    public IsOrganizationalUnitInOrganizationalUnit createIsOrganizationalUnitInOrganizationalUnit() {
        return new IsOrganizationalUnitInOrganizationalUnit();
    }

    /**
     * Create an instance of {@link GetSelectedOrganizationalUnitsByTicketID }
     * 
     */
    public GetSelectedOrganizationalUnitsByTicketID createGetSelectedOrganizationalUnitsByTicketID() {
        return new GetSelectedOrganizationalUnitsByTicketID();
    }

    /**
     * Create an instance of {@link GetUsersByRole }
     * 
     */
    public GetUsersByRole createGetUsersByRole() {
        return new GetUsersByRole();
    }

    /**
     * Create an instance of {@link IsUserInRoleResponse }
     * 
     */
    public IsUserInRoleResponse createIsUserInRoleResponse() {
        return new IsUserInRoleResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitResponse }
     * 
     */
    public GetOrganizationalUnitResponse createGetOrganizationalUnitResponse() {
        return new GetOrganizationalUnitResponse();
    }

    /**
     * Create an instance of {@link GetRoleResponse }
     * 
     */
    public GetRoleResponse createGetRoleResponse() {
        return new GetRoleResponse();
    }

    /**
     * Create an instance of {@link GetChildOrganizationalUnitsResponse }
     * 
     */
    public GetChildOrganizationalUnitsResponse createGetChildOrganizationalUnitsResponse() {
        return new GetChildOrganizationalUnitsResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitsByParentOrganizationalUnit }
     * 
     */
    public GetOrganizationalUnitsByParentOrganizationalUnit createGetOrganizationalUnitsByParentOrganizationalUnit() {
        return new GetOrganizationalUnitsByParentOrganizationalUnit();
    }

    /**
     * Create an instance of {@link GetUser }
     * 
     */
    public GetUser createGetUser() {
        return new GetUser();
    }

    /**
     * Create an instance of {@link GetSelectedRolesByTicketID }
     * 
     */
    public GetSelectedRolesByTicketID createGetSelectedRolesByTicketID() {
        return new GetSelectedRolesByTicketID();
    }

    /**
     * Create an instance of {@link GetDefaultOrganizationalUnitRoleByUserIdResponse }
     * 
     */
    public GetDefaultOrganizationalUnitRoleByUserIdResponse createGetDefaultOrganizationalUnitRoleByUserIdResponse() {
        return new GetDefaultOrganizationalUnitRoleByUserIdResponse();
    }

    /**
     * Create an instance of {@link GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnit }
     * 
     */
    public GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnit createGetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnit() {
        return new GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnit();
    }

    /**
     * Create an instance of {@link IsOrganizationalUnitInOrganizationalUnitResponse }
     * 
     */
    public IsOrganizationalUnitInOrganizationalUnitResponse createIsOrganizationalUnitInOrganizationalUnitResponse() {
        return new IsOrganizationalUnitInOrganizationalUnitResponse();
    }

    /**
     * Create an instance of {@link GetSelectedOrganizationalUnitRoleRelationsByTicketID }
     * 
     */
    public GetSelectedOrganizationalUnitRoleRelationsByTicketID createGetSelectedOrganizationalUnitRoleRelationsByTicketID() {
        return new GetSelectedOrganizationalUnitRoleRelationsByTicketID();
    }

    /**
     * Create an instance of {@link GetUsersByOrganizationalUnitResponse }
     * 
     */
    public GetUsersByOrganizationalUnitResponse createGetUsersByOrganizationalUnitResponse() {
        return new GetUsersByOrganizationalUnitResponse();
    }

    /**
     * Create an instance of {@link GetUsersByOrganizationalUnitRoleRelationResponse }
     * 
     */
    public GetUsersByOrganizationalUnitRoleRelationResponse createGetUsersByOrganizationalUnitRoleRelationResponse() {
        return new GetUsersByOrganizationalUnitRoleRelationResponse();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRoleRelationsByIds }
     * 
     */
    public GetOrganizationalUnitRoleRelationsByIds createGetOrganizationalUnitRoleRelationsByIds() {
        return new GetOrganizationalUnitRoleRelationsByIds();
    }

    /**
     * Create an instance of {@link IsUserInOrganizationalUnitResponse }
     * 
     */
    public IsUserInOrganizationalUnitResponse createIsUserInOrganizationalUnitResponse() {
        return new IsUserInOrganizationalUnitResponse();
    }

    /**
     * Create an instance of {@link IsUserInOrganizationalUnitRole }
     * 
     */
    public IsUserInOrganizationalUnitRole createIsUserInOrganizationalUnitRole() {
        return new IsUserInOrganizationalUnitRole();
    }

    /**
     * Create an instance of {@link GetSelectedObjectNamesByTicketID }
     * 
     */
    public GetSelectedObjectNamesByTicketID createGetSelectedObjectNamesByTicketID() {
        return new GetSelectedObjectNamesByTicketID();
    }

    /**
     * Create an instance of {@link GetRoles }
     * 
     */
    public GetRoles createGetRoles() {
        return new GetRoles();
    }

    /**
     * Create an instance of {@link GetOrganizationalUnitRolesByUserIdResponse }
     * 
     */
    public GetOrganizationalUnitRolesByUserIdResponse createGetOrganizationalUnitRolesByUserIdResponse() {
        return new GetOrganizationalUnitRolesByUserIdResponse();
    }

    /**
     * Create an instance of {@link GetUsers }
     * 
     */
    public GetUsers createGetUsers() {
        return new GetUsers();
    }

    /**
     * Create an instance of {@link GetDirectSupervisorOrganizationalUnitRoleRelationResponse }
     * 
     */
    public GetDirectSupervisorOrganizationalUnitRoleRelationResponse createGetDirectSupervisorOrganizationalUnitRoleRelationResponse() {
        return new GetDirectSupervisorOrganizationalUnitRoleRelationResponse();
    }

    /**
     * Create an instance of {@link IsUserInOrganizationalUnit }
     * 
     */
    public IsUserInOrganizationalUnit createIsUserInOrganizationalUnit() {
        return new IsUserInOrganizationalUnit();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitsByIdsResult", scope = GetOrganizationalUnitsByIdsResponse.class)
    public JAXBElement<ArrayOfOrganizationalUnit> createGetOrganizationalUnitsByIdsResponseGetOrganizationalUnitsByIdsResult(ArrayOfOrganizationalUnit value) {
        return new JAXBElement<ArrayOfOrganizationalUnit>(_GetOrganizationalUnitsByIdsResponseGetOrganizationalUnitsByIdsResult_QNAME, ArrayOfOrganizationalUnit.class, GetOrganizationalUnitsByIdsResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "objectType", scope = GetSelectedObjectIdsByTicketID.class)
    public JAXBElement<String> createGetSelectedObjectIdsByTicketIDObjectType(String value) {
        return new JAXBElement<String>(_GetSelectedObjectIdsByTicketIDObjectType_QNAME, String.class, GetSelectedObjectIdsByTicketID.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfUser }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetUsersByIdNosResult", scope = GetUsersByIdNosResponse.class)
    public JAXBElement<ArrayOfUser> createGetUsersByIdNosResponseGetUsersByIdNosResult(ArrayOfUser value) {
        return new JAXBElement<ArrayOfUser>(_GetUsersByIdNosResponseGetUsersByIdNosResult_QNAME, ArrayOfUser.class, GetUsersByIdNosResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetSelectedRolesByTicketIDResult", scope = GetSelectedRolesByTicketIDResponse.class)
    public JAXBElement<ArrayOfguid> createGetSelectedRolesByTicketIDResponseGetSelectedRolesByTicketIDResult(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetSelectedRolesByTicketIDResponseGetSelectedRolesByTicketIDResult_QNAME, ArrayOfguid.class, GetSelectedRolesByTicketIDResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "ids", scope = GetRolesByIds.class)
    public JAXBElement<ArrayOfguid> createGetRolesByIdsIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetRolesByIdsIds_QNAME, ArrayOfguid.class, GetRolesByIds.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitsByParentOrganizationalUnitResult", scope = GetOrganizationalUnitsByParentOrganizationalUnitResponse.class)
    public JAXBElement<ArrayOfOrganizationalUnit> createGetOrganizationalUnitsByParentOrganizationalUnitResponseGetOrganizationalUnitsByParentOrganizationalUnitResult(ArrayOfOrganizationalUnit value) {
        return new JAXBElement<ArrayOfOrganizationalUnit>(_GetOrganizationalUnitsByParentOrganizationalUnitResponseGetOrganizationalUnitsByParentOrganizationalUnitResult_QNAME, ArrayOfOrganizationalUnit.class, GetOrganizationalUnitsByParentOrganizationalUnitResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OrganizationalUnitRoleRelation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResult", scope = GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponse.class)
    public JAXBElement<OrganizationalUnitRoleRelation> createGetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponseGetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResult(OrganizationalUnitRoleRelation value) {
        return new JAXBElement<OrganizationalUnitRoleRelation>(_GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponseGetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResult_QNAME, OrganizationalUnitRoleRelation.class, GetOrganizationalUnitRoleRelationByOrganizationalUnitIdAndRoleIdResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link RadTreeNodeData }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "node", scope = GetChildOrganizationalUnits.class)
    public JAXBElement<RadTreeNodeData> createGetChildOrganizationalUnitsNode(RadTreeNodeData value) {
        return new JAXBElement<RadTreeNodeData>(_GetChildOrganizationalUnitsNode_QNAME, RadTreeNodeData.class, GetChildOrganizationalUnits.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitsResult", scope = GetOrganizationalUnitsResponse.class)
    public JAXBElement<ArrayOfOrganizationalUnit> createGetOrganizationalUnitsResponseGetOrganizationalUnitsResult(ArrayOfOrganizationalUnit value) {
        return new JAXBElement<ArrayOfOrganizationalUnit>(_GetOrganizationalUnitsResponseGetOrganizationalUnitsResult_QNAME, ArrayOfOrganizationalUnit.class, GetOrganizationalUnitsResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OrganizationalUnitRoleRelation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitRoleRelationResult", scope = GetOrganizationalUnitRoleRelationResponse.class)
    public JAXBElement<OrganizationalUnitRoleRelation> createGetOrganizationalUnitRoleRelationResponseGetOrganizationalUnitRoleRelationResult(OrganizationalUnitRoleRelation value) {
        return new JAXBElement<OrganizationalUnitRoleRelation>(_GetOrganizationalUnitRoleRelationResponseGetOrganizationalUnitRoleRelationResult_QNAME, OrganizationalUnitRoleRelation.class, GetOrganizationalUnitRoleRelationResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetSelectedObjectIdsByTicketIDResult", scope = GetSelectedObjectIdsByTicketIDResponse.class)
    public JAXBElement<ArrayOfguid> createGetSelectedObjectIdsByTicketIDResponseGetSelectedObjectIdsByTicketIDResult(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetSelectedObjectIdsByTicketIDResponseGetSelectedObjectIdsByTicketIDResult_QNAME, ArrayOfguid.class, GetSelectedObjectIdsByTicketIDResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnitRoleRelation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitRoleRelationsByIdsResult", scope = GetOrganizationalUnitRoleRelationsByIdsResponse.class)
    public JAXBElement<ArrayOfOrganizationalUnitRoleRelation> createGetOrganizationalUnitRoleRelationsByIdsResponseGetOrganizationalUnitRoleRelationsByIdsResult(ArrayOfOrganizationalUnitRoleRelation value) {
        return new JAXBElement<ArrayOfOrganizationalUnitRoleRelation>(_GetOrganizationalUnitRoleRelationsByIdsResponseGetOrganizationalUnitRoleRelationsByIdsResult_QNAME, ArrayOfOrganizationalUnitRoleRelation.class, GetOrganizationalUnitRoleRelationsByIdsResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "organizationalUnitIds", scope = PrepareTicketID.class)
    public JAXBElement<ArrayOfguid> createPrepareTicketIDOrganizationalUnitIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_PrepareTicketIDOrganizationalUnitIds_QNAME, ArrayOfguid.class, PrepareTicketID.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "OrganizationalUnitRoleRelationGUIDs", scope = PrepareTicketID.class)
    public JAXBElement<ArrayOfguid> createPrepareTicketIDOrganizationalUnitRoleRelationGUIDs(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_PrepareTicketIDOrganizationalUnitRoleRelationGUIDs_QNAME, ArrayOfguid.class, PrepareTicketID.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "privilegeGroupGUIDs", scope = PrepareTicketID.class)
    public JAXBElement<ArrayOfguid> createPrepareTicketIDPrivilegeGroupGUIDs(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_PrepareTicketIDPrivilegeGroupGUIDs_QNAME, ArrayOfguid.class, PrepareTicketID.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "roleIds", scope = PrepareTicketID.class)
    public JAXBElement<ArrayOfguid> createPrepareTicketIDRoleIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_PrepareTicketIDRoleIds_QNAME, ArrayOfguid.class, PrepareTicketID.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "userIds", scope = PrepareTicketID.class)
    public JAXBElement<ArrayOfguid> createPrepareTicketIDUserIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_PrepareTicketIDUserIds_QNAME, ArrayOfguid.class, PrepareTicketID.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetSelectedUsersByTicketIDResult", scope = GetSelectedUsersByTicketIDResponse.class)
    public JAXBElement<ArrayOfguid> createGetSelectedUsersByTicketIDResponseGetSelectedUsersByTicketIDResult(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetSelectedUsersByTicketIDResponseGetSelectedUsersByTicketIDResult_QNAME, ArrayOfguid.class, GetSelectedUsersByTicketIDResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link User }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetUserResult", scope = GetUserResponse.class)
    public JAXBElement<User> createGetUserResponseGetUserResult(User value) {
        return new JAXBElement<User>(_GetUserResponseGetUserResult_QNAME, User.class, GetUserResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfRole }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetRolesByIdsResult", scope = GetRolesByIdsResponse.class)
    public JAXBElement<ArrayOfRole> createGetRolesByIdsResponseGetRolesByIdsResult(ArrayOfRole value) {
        return new JAXBElement<ArrayOfRole>(_GetRolesByIdsResponseGetRolesByIdsResult_QNAME, ArrayOfRole.class, GetRolesByIdsResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfRole }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetRolesResult", scope = GetRolesResponse.class)
    public JAXBElement<ArrayOfRole> createGetRolesResponseGetRolesResult(ArrayOfRole value) {
        return new JAXBElement<ArrayOfRole>(_GetRolesResponseGetRolesResult_QNAME, ArrayOfRole.class, GetRolesResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetAncestorOrganizationalUnitsByIdResult", scope = GetAncestorOrganizationalUnitsByIdResponse.class)
    public JAXBElement<ArrayOfOrganizationalUnit> createGetAncestorOrganizationalUnitsByIdResponseGetAncestorOrganizationalUnitsByIdResult(ArrayOfOrganizationalUnit value) {
        return new JAXBElement<ArrayOfOrganizationalUnit>(_GetAncestorOrganizationalUnitsByIdResponseGetAncestorOrganizationalUnitsByIdResult_QNAME, ArrayOfOrganizationalUnit.class, GetAncestorOrganizationalUnitsByIdResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfViewUserOrganizationalUnitRole }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetUsersByRoleResult", scope = GetUsersByRoleResponse.class)
    public JAXBElement<ArrayOfViewUserOrganizationalUnitRole> createGetUsersByRoleResponseGetUsersByRoleResult(ArrayOfViewUserOrganizationalUnitRole value) {
        return new JAXBElement<ArrayOfViewUserOrganizationalUnitRole>(_GetUsersByRoleResponseGetUsersByRoleResult_QNAME, ArrayOfViewUserOrganizationalUnitRole.class, GetUsersByRoleResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfUser }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetUsersByIdsResult", scope = GetUsersByIdsResponse.class)
    public JAXBElement<ArrayOfUser> createGetUsersByIdsResponseGetUsersByIdsResult(ArrayOfUser value) {
        return new JAXBElement<ArrayOfUser>(_GetUsersByIdsResponseGetUsersByIdsResult_QNAME, ArrayOfUser.class, GetUsersByIdsResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetSelectedObjectNamesByTicketIDResult", scope = GetSelectedObjectNamesByTicketIDResponse.class)
    public JAXBElement<String> createGetSelectedObjectNamesByTicketIDResponseGetSelectedObjectNamesByTicketIDResult(String value) {
        return new JAXBElement<String>(_GetSelectedObjectNamesByTicketIDResponseGetSelectedObjectNamesByTicketIDResult_QNAME, String.class, GetSelectedObjectNamesByTicketIDResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetSelectedOrganizationalUnitRoleRelationsByTicketIDResult", scope = GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponse.class)
    public JAXBElement<ArrayOfguid> createGetSelectedOrganizationalUnitRoleRelationsByTicketIDResponseGetSelectedOrganizationalUnitRoleRelationsByTicketIDResult(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponseGetSelectedOrganizationalUnitRoleRelationsByTicketIDResult_QNAME, ArrayOfguid.class, GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "ids", scope = GetUsersByIds.class)
    public JAXBElement<ArrayOfguid> createGetUsersByIdsIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetRolesByIdsIds_QNAME, ArrayOfguid.class, GetUsersByIds.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "organizationalUnitIds", scope = GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds.class)
    public JAXBElement<ArrayOfguid> createGetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsOrganizationalUnitIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_PrepareTicketIDOrganizationalUnitIds_QNAME, ArrayOfguid.class, GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "roleIds", scope = GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds.class)
    public JAXBElement<ArrayOfguid> createGetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsRoleIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_PrepareTicketIDRoleIds_QNAME, ArrayOfguid.class, GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OrganizationalUnitRoleRelation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResult", scope = GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponse.class)
    public JAXBElement<OrganizationalUnitRoleRelation> createGetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponseGetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResult(OrganizationalUnitRoleRelation value) {
        return new JAXBElement<OrganizationalUnitRoleRelation>(_GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponseGetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResult_QNAME, OrganizationalUnitRoleRelation.class, GetSupervisorOrganizationalUnitRoleRelationOfParentOrganizationalUnitResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfstring }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "idNos", scope = GetUsersByIdNos.class)
    public JAXBElement<ArrayOfstring> createGetUsersByIdNosIdNos(ArrayOfstring value) {
        return new JAXBElement<ArrayOfstring>(_GetUsersByIdNosIdNos_QNAME, ArrayOfstring.class, GetUsersByIdNos.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetSelectedOrganizationalUnitsByTicketIDResult", scope = GetSelectedOrganizationalUnitsByTicketIDResponse.class)
    public JAXBElement<ArrayOfguid> createGetSelectedOrganizationalUnitsByTicketIDResponseGetSelectedOrganizationalUnitsByTicketIDResult(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetSelectedOrganizationalUnitsByTicketIDResponseGetSelectedOrganizationalUnitsByTicketIDResult_QNAME, ArrayOfguid.class, GetSelectedOrganizationalUnitsByTicketIDResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "ids", scope = GetOrganizationalUnitsByIds.class)
    public JAXBElement<ArrayOfguid> createGetOrganizationalUnitsByIdsIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetRolesByIdsIds_QNAME, ArrayOfguid.class, GetOrganizationalUnitsByIds.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OrganizationalUnitRoleRelation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult", scope = GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponse.class)
    public JAXBElement<OrganizationalUnitRoleRelation> createGetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponseGetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult(OrganizationalUnitRoleRelation value) {
        return new JAXBElement<OrganizationalUnitRoleRelation>(_GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponseGetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult_QNAME, OrganizationalUnitRoleRelation.class, GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfUser }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetUsersResult", scope = GetUsersResponse.class)
    public JAXBElement<ArrayOfUser> createGetUsersResponseGetUsersResult(ArrayOfUser value) {
        return new JAXBElement<ArrayOfUser>(_GetUsersResponseGetUsersResult_QNAME, ArrayOfUser.class, GetUsersResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnitRoleRelation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResult", scope = GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponse.class)
    public JAXBElement<ArrayOfOrganizationalUnitRoleRelation> createGetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponseGetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResult(ArrayOfOrganizationalUnitRoleRelation value) {
        return new JAXBElement<ArrayOfOrganizationalUnitRoleRelation>(_GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponseGetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResult_QNAME, ArrayOfOrganizationalUnitRoleRelation.class, GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIdsResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OrganizationalUnit }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitResult", scope = GetOrganizationalUnitResponse.class)
    public JAXBElement<OrganizationalUnit> createGetOrganizationalUnitResponseGetOrganizationalUnitResult(OrganizationalUnit value) {
        return new JAXBElement<OrganizationalUnit>(_GetOrganizationalUnitResponseGetOrganizationalUnitResult_QNAME, OrganizationalUnit.class, GetOrganizationalUnitResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Role }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetRoleResult", scope = GetRoleResponse.class)
    public JAXBElement<Role> createGetRoleResponseGetRoleResult(Role value) {
        return new JAXBElement<Role>(_GetRoleResponseGetRoleResult_QNAME, Role.class, GetRoleResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfRadTreeNodeData }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetChildOrganizationalUnitsResult", scope = GetChildOrganizationalUnitsResponse.class)
    public JAXBElement<ArrayOfRadTreeNodeData> createGetChildOrganizationalUnitsResponseGetChildOrganizationalUnitsResult(ArrayOfRadTreeNodeData value) {
        return new JAXBElement<ArrayOfRadTreeNodeData>(_GetChildOrganizationalUnitsResponseGetChildOrganizationalUnitsResult_QNAME, ArrayOfRadTreeNodeData.class, GetChildOrganizationalUnitsResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ViewUserOrganizationalUnitRole }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetDefaultOrganizationalUnitRoleByUserIdResult", scope = GetDefaultOrganizationalUnitRoleByUserIdResponse.class)
    public JAXBElement<ViewUserOrganizationalUnitRole> createGetDefaultOrganizationalUnitRoleByUserIdResponseGetDefaultOrganizationalUnitRoleByUserIdResult(ViewUserOrganizationalUnitRole value) {
        return new JAXBElement<ViewUserOrganizationalUnitRole>(_GetDefaultOrganizationalUnitRoleByUserIdResponseGetDefaultOrganizationalUnitRoleByUserIdResult_QNAME, ViewUserOrganizationalUnitRole.class, GetDefaultOrganizationalUnitRoleByUserIdResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfViewUserOrganizationalUnitRole }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetUsersByOrganizationalUnitResult", scope = GetUsersByOrganizationalUnitResponse.class)
    public JAXBElement<ArrayOfViewUserOrganizationalUnitRole> createGetUsersByOrganizationalUnitResponseGetUsersByOrganizationalUnitResult(ArrayOfViewUserOrganizationalUnitRole value) {
        return new JAXBElement<ArrayOfViewUserOrganizationalUnitRole>(_GetUsersByOrganizationalUnitResponseGetUsersByOrganizationalUnitResult_QNAME, ArrayOfViewUserOrganizationalUnitRole.class, GetUsersByOrganizationalUnitResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfViewUserOrganizationalUnitRole }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetUsersByOrganizationalUnitRoleRelationResult", scope = GetUsersByOrganizationalUnitRoleRelationResponse.class)
    public JAXBElement<ArrayOfViewUserOrganizationalUnitRole> createGetUsersByOrganizationalUnitRoleRelationResponseGetUsersByOrganizationalUnitRoleRelationResult(ArrayOfViewUserOrganizationalUnitRole value) {
        return new JAXBElement<ArrayOfViewUserOrganizationalUnitRole>(_GetUsersByOrganizationalUnitRoleRelationResponseGetUsersByOrganizationalUnitRoleRelationResult_QNAME, ArrayOfViewUserOrganizationalUnitRole.class, GetUsersByOrganizationalUnitRoleRelationResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "ids", scope = GetOrganizationalUnitRoleRelationsByIds.class)
    public JAXBElement<ArrayOfguid> createGetOrganizationalUnitRoleRelationsByIdsIds(ArrayOfguid value) {
        return new JAXBElement<ArrayOfguid>(_GetRolesByIdsIds_QNAME, ArrayOfguid.class, GetOrganizationalUnitRoleRelationsByIds.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "objectType", scope = GetSelectedObjectNamesByTicketID.class)
    public JAXBElement<String> createGetSelectedObjectNamesByTicketIDObjectType(String value) {
        return new JAXBElement<String>(_GetSelectedObjectIdsByTicketIDObjectType_QNAME, String.class, GetSelectedObjectNamesByTicketID.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfViewUserOrganizationalUnitRole }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetOrganizationalUnitRolesByUserIdResult", scope = GetOrganizationalUnitRolesByUserIdResponse.class)
    public JAXBElement<ArrayOfViewUserOrganizationalUnitRole> createGetOrganizationalUnitRolesByUserIdResponseGetOrganizationalUnitRolesByUserIdResult(ArrayOfViewUserOrganizationalUnitRole value) {
        return new JAXBElement<ArrayOfViewUserOrganizationalUnitRole>(_GetOrganizationalUnitRolesByUserIdResponseGetOrganizationalUnitRolesByUserIdResult_QNAME, ArrayOfViewUserOrganizationalUnitRole.class, GetOrganizationalUnitRolesByUserIdResponse.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OrganizationalUnitRoleRelation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://tempuri.org/", name = "GetDirectSupervisorOrganizationalUnitRoleRelationResult", scope = GetDirectSupervisorOrganizationalUnitRoleRelationResponse.class)
    public JAXBElement<OrganizationalUnitRoleRelation> createGetDirectSupervisorOrganizationalUnitRoleRelationResponseGetDirectSupervisorOrganizationalUnitRoleRelationResult(OrganizationalUnitRoleRelation value) {
        return new JAXBElement<OrganizationalUnitRoleRelation>(_GetDirectSupervisorOrganizationalUnitRoleRelationResponseGetDirectSupervisorOrganizationalUnitRoleRelationResult_QNAME, OrganizationalUnitRoleRelation.class, GetDirectSupervisorOrganizationalUnitRoleRelationResponse.class, value);
    }

}
