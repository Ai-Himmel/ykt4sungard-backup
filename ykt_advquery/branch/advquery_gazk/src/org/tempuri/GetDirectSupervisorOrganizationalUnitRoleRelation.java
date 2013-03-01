
package org.tempuri;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
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
 *         &lt;element name="organizationalUnitId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="directSupervisorRoleId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="userId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
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
    "organizationalUnitId",
    "directSupervisorRoleId",
    "userId"
})
@XmlRootElement(name = "GetDirectSupervisorOrganizationalUnitRoleRelation")
public class GetDirectSupervisorOrganizationalUnitRoleRelation {

    protected String organizationalUnitId;
    protected String directSupervisorRoleId;
    protected String userId;

    /**
     * Gets the value of the organizationalUnitId property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getOrganizationalUnitId() {
        return organizationalUnitId;
    }

    /**
     * Sets the value of the organizationalUnitId property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setOrganizationalUnitId(String value) {
        this.organizationalUnitId = value;
    }

    /**
     * Gets the value of the directSupervisorRoleId property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getDirectSupervisorRoleId() {
        return directSupervisorRoleId;
    }

    /**
     * Sets the value of the directSupervisorRoleId property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setDirectSupervisorRoleId(String value) {
        this.directSupervisorRoleId = value;
    }

    /**
     * Gets the value of the userId property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getUserId() {
        return userId;
    }

    /**
     * Sets the value of the userId property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setUserId(String value) {
        this.userId = value;
    }

}
