
package org.datacontract.schemas._2004._07.saff;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for OrganizationalUnit_Role_Relation complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="OrganizationalUnit_Role_Relation">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="Id" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="OrganizationalUnitId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="RoleId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="User_OrganizationalUnit_Role_Relation" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfUser_OrganizationalUnit_Role_Relation" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "OrganizationalUnit_Role_Relation", propOrder = {
    "id",
    "organizationalUnitId",
    "roleId",
    "userOrganizationalUnitRoleRelation"
})
public class OrganizationalUnitRoleRelation {

    @XmlElement(name = "Id")
    protected String id;
    @XmlElement(name = "OrganizationalUnitId")
    protected String organizationalUnitId;
    @XmlElement(name = "RoleId")
    protected String roleId;
    @XmlElementRef(name = "User_OrganizationalUnit_Role_Relation", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<ArrayOfUserOrganizationalUnitRoleRelation> userOrganizationalUnitRoleRelation;

    /**
     * Gets the value of the id property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getId() {
        return id;
    }

    /**
     * Sets the value of the id property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setId(String value) {
        this.id = value;
    }

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
     * Gets the value of the roleId property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getRoleId() {
        return roleId;
    }

    /**
     * Sets the value of the roleId property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setRoleId(String value) {
        this.roleId = value;
    }

    /**
     * Gets the value of the userOrganizationalUnitRoleRelation property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfUserOrganizationalUnitRoleRelation }{@code >}
     *     
     */
    public JAXBElement<ArrayOfUserOrganizationalUnitRoleRelation> getUserOrganizationalUnitRoleRelation() {
        return userOrganizationalUnitRoleRelation;
    }

    /**
     * Sets the value of the userOrganizationalUnitRoleRelation property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfUserOrganizationalUnitRoleRelation }{@code >}
     *     
     */
    public void setUserOrganizationalUnitRoleRelation(JAXBElement<ArrayOfUserOrganizationalUnitRoleRelation> value) {
        this.userOrganizationalUnitRoleRelation = ((JAXBElement<ArrayOfUserOrganizationalUnitRoleRelation> ) value);
    }

}
