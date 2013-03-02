
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.saff.OrganizationalUnitRoleRelation;


/**
 * <p>Java class for anonymous complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType>
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}OrganizationalUnit_Role_Relation" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "getSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult"
})
@XmlRootElement(name = "GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponse")
public class GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResponse {

    @XmlElementRef(name = "GetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<OrganizationalUnitRoleRelation> getSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult;

    /**
     * Gets the value of the getSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link OrganizationalUnitRoleRelation }{@code >}
     *     
     */
    public JAXBElement<OrganizationalUnitRoleRelation> getGetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult() {
        return getSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult;
    }

    /**
     * Sets the value of the getSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link OrganizationalUnitRoleRelation }{@code >}
     *     
     */
    public void setGetSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult(JAXBElement<OrganizationalUnitRoleRelation> value) {
        this.getSupervisorOrganizationalUnitRoleRelationOfCurrentOrganizationalUnitResult = ((JAXBElement<OrganizationalUnitRoleRelation> ) value);
    }

}
