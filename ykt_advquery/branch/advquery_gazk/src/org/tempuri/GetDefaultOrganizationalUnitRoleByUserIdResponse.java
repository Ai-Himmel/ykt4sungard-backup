
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.saff.ViewUserOrganizationalUnitRole;


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
 *         &lt;element name="GetDefaultOrganizationalUnitRoleByUserIdResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}View_User_OrganizationalUnit_Role" minOccurs="0"/>
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
    "getDefaultOrganizationalUnitRoleByUserIdResult"
})
@XmlRootElement(name = "GetDefaultOrganizationalUnitRoleByUserIdResponse")
public class GetDefaultOrganizationalUnitRoleByUserIdResponse {

    @XmlElementRef(name = "GetDefaultOrganizationalUnitRoleByUserIdResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ViewUserOrganizationalUnitRole> getDefaultOrganizationalUnitRoleByUserIdResult;

    /**
     * Gets the value of the getDefaultOrganizationalUnitRoleByUserIdResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ViewUserOrganizationalUnitRole }{@code >}
     *     
     */
    public JAXBElement<ViewUserOrganizationalUnitRole> getGetDefaultOrganizationalUnitRoleByUserIdResult() {
        return getDefaultOrganizationalUnitRoleByUserIdResult;
    }

    /**
     * Sets the value of the getDefaultOrganizationalUnitRoleByUserIdResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ViewUserOrganizationalUnitRole }{@code >}
     *     
     */
    public void setGetDefaultOrganizationalUnitRoleByUserIdResult(JAXBElement<ViewUserOrganizationalUnitRole> value) {
        this.getDefaultOrganizationalUnitRoleByUserIdResult = ((JAXBElement<ViewUserOrganizationalUnitRole> ) value);
    }

}
