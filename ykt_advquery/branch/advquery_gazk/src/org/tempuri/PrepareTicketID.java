
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfguid;


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
 *         &lt;element name="userIds" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
 *         &lt;element name="organizationalUnitIds" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
 *         &lt;element name="roleIds" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
 *         &lt;element name="OrganizationalUnitRoleRelationGUIDs" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
 *         &lt;element name="privilegeGroupGUIDs" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
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
    "userIds",
    "organizationalUnitIds",
    "roleIds",
    "organizationalUnitRoleRelationGUIDs",
    "privilegeGroupGUIDs"
})
@XmlRootElement(name = "PrepareTicketID")
public class PrepareTicketID {

    @XmlElementRef(name = "userIds", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> userIds;
    @XmlElementRef(name = "organizationalUnitIds", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> organizationalUnitIds;
    @XmlElementRef(name = "roleIds", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> roleIds;
    @XmlElementRef(name = "OrganizationalUnitRoleRelationGUIDs", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> organizationalUnitRoleRelationGUIDs;
    @XmlElementRef(name = "privilegeGroupGUIDs", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> privilegeGroupGUIDs;

    /**
     * Gets the value of the userIds property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getUserIds() {
        return userIds;
    }

    /**
     * Sets the value of the userIds property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setUserIds(JAXBElement<ArrayOfguid> value) {
        this.userIds = ((JAXBElement<ArrayOfguid> ) value);
    }

    /**
     * Gets the value of the organizationalUnitIds property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getOrganizationalUnitIds() {
        return organizationalUnitIds;
    }

    /**
     * Sets the value of the organizationalUnitIds property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setOrganizationalUnitIds(JAXBElement<ArrayOfguid> value) {
        this.organizationalUnitIds = ((JAXBElement<ArrayOfguid> ) value);
    }

    /**
     * Gets the value of the roleIds property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getRoleIds() {
        return roleIds;
    }

    /**
     * Sets the value of the roleIds property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setRoleIds(JAXBElement<ArrayOfguid> value) {
        this.roleIds = ((JAXBElement<ArrayOfguid> ) value);
    }

    /**
     * Gets the value of the organizationalUnitRoleRelationGUIDs property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getOrganizationalUnitRoleRelationGUIDs() {
        return organizationalUnitRoleRelationGUIDs;
    }

    /**
     * Sets the value of the organizationalUnitRoleRelationGUIDs property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setOrganizationalUnitRoleRelationGUIDs(JAXBElement<ArrayOfguid> value) {
        this.organizationalUnitRoleRelationGUIDs = ((JAXBElement<ArrayOfguid> ) value);
    }

    /**
     * Gets the value of the privilegeGroupGUIDs property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getPrivilegeGroupGUIDs() {
        return privilegeGroupGUIDs;
    }

    /**
     * Sets the value of the privilegeGroupGUIDs property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setPrivilegeGroupGUIDs(JAXBElement<ArrayOfguid> value) {
        this.privilegeGroupGUIDs = ((JAXBElement<ArrayOfguid> ) value);
    }

}
