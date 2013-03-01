
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.saff.ArrayOfOrganizationalUnitRoleRelation;


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
 *         &lt;element name="GetOrganizationalUnitRoleRelationsByIdsResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfOrganizationalUnit_Role_Relation" minOccurs="0"/>
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
    "getOrganizationalUnitRoleRelationsByIdsResult"
})
@XmlRootElement(name = "GetOrganizationalUnitRoleRelationsByIdsResponse")
public class GetOrganizationalUnitRoleRelationsByIdsResponse {

    @XmlElementRef(name = "GetOrganizationalUnitRoleRelationsByIdsResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfOrganizationalUnitRoleRelation> getOrganizationalUnitRoleRelationsByIdsResult;

    /**
     * Gets the value of the getOrganizationalUnitRoleRelationsByIdsResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnitRoleRelation }{@code >}
     *     
     */
    public JAXBElement<ArrayOfOrganizationalUnitRoleRelation> getGetOrganizationalUnitRoleRelationsByIdsResult() {
        return getOrganizationalUnitRoleRelationsByIdsResult;
    }

    /**
     * Sets the value of the getOrganizationalUnitRoleRelationsByIdsResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnitRoleRelation }{@code >}
     *     
     */
    public void setGetOrganizationalUnitRoleRelationsByIdsResult(JAXBElement<ArrayOfOrganizationalUnitRoleRelation> value) {
        this.getOrganizationalUnitRoleRelationsByIdsResult = ((JAXBElement<ArrayOfOrganizationalUnitRoleRelation> ) value);
    }

}
