
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.saff.ArrayOfViewUserOrganizationalUnitRole;


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
 *         &lt;element name="GetUsersByOrganizationalUnitRoleRelationResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfView_User_OrganizationalUnit_Role" minOccurs="0"/>
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
    "getUsersByOrganizationalUnitRoleRelationResult"
})
@XmlRootElement(name = "GetUsersByOrganizationalUnitRoleRelationResponse")
public class GetUsersByOrganizationalUnitRoleRelationResponse {

    @XmlElementRef(name = "GetUsersByOrganizationalUnitRoleRelationResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfViewUserOrganizationalUnitRole> getUsersByOrganizationalUnitRoleRelationResult;

    /**
     * Gets the value of the getUsersByOrganizationalUnitRoleRelationResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfViewUserOrganizationalUnitRole }{@code >}
     *     
     */
    public JAXBElement<ArrayOfViewUserOrganizationalUnitRole> getGetUsersByOrganizationalUnitRoleRelationResult() {
        return getUsersByOrganizationalUnitRoleRelationResult;
    }

    /**
     * Sets the value of the getUsersByOrganizationalUnitRoleRelationResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfViewUserOrganizationalUnitRole }{@code >}
     *     
     */
    public void setGetUsersByOrganizationalUnitRoleRelationResult(JAXBElement<ArrayOfViewUserOrganizationalUnitRole> value) {
        this.getUsersByOrganizationalUnitRoleRelationResult = ((JAXBElement<ArrayOfViewUserOrganizationalUnitRole> ) value);
    }

}
