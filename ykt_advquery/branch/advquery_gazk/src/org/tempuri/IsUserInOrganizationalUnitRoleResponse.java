
package org.tempuri;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


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
 *         &lt;element name="IsUserInOrganizationalUnitRoleResult" type="{http://www.w3.org/2001/XMLSchema}boolean" minOccurs="0"/>
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
    "isUserInOrganizationalUnitRoleResult"
})
@XmlRootElement(name = "IsUserInOrganizationalUnitRoleResponse")
public class IsUserInOrganizationalUnitRoleResponse {

    @XmlElement(name = "IsUserInOrganizationalUnitRoleResult")
    protected Boolean isUserInOrganizationalUnitRoleResult;

    /**
     * Gets the value of the isUserInOrganizationalUnitRoleResult property.
     * 
     * @return
     *     possible object is
     *     {@link Boolean }
     *     
     */
    public Boolean isIsUserInOrganizationalUnitRoleResult() {
        return isUserInOrganizationalUnitRoleResult;
    }

    /**
     * Sets the value of the isUserInOrganizationalUnitRoleResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link Boolean }
     *     
     */
    public void setIsUserInOrganizationalUnitRoleResult(Boolean value) {
        this.isUserInOrganizationalUnitRoleResult = value;
    }

}
