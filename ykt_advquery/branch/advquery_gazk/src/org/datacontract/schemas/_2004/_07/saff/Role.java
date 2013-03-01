
package org.datacontract.schemas._2004._07.saff;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for Role complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="Role">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="Id" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="Name" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="DomainId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="OrderNum" type="{http://www.w3.org/2001/XMLSchema}int" minOccurs="0"/>
 *         &lt;element name="RoleType" type="{http://www.w3.org/2001/XMLSchema}int" minOccurs="0"/>
 *         &lt;element name="OrganizationalUnit_Role_Relation" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfOrganizationalUnit_Role_Relation" minOccurs="0"/>
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
@XmlType(name = "Role", propOrder = {
    "id",
    "name",
    "domainId",
    "orderNum",
    "roleType",
    "organizationalUnitRoleRelation",
    "userOrganizationalUnitRoleRelation"
})
public class Role {

    @XmlElement(name = "Id")
    protected String id;
    @XmlElementRef(name = "Name", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> name;
    @XmlElementRef(name = "DomainId", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> domainId;
    @XmlElementRef(name = "OrderNum", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<Integer> orderNum;
    @XmlElementRef(name = "RoleType", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<Integer> roleType;
    @XmlElementRef(name = "OrganizationalUnit_Role_Relation", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<ArrayOfOrganizationalUnitRoleRelation> organizationalUnitRoleRelation;
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
     * Gets the value of the name property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getName() {
        return name;
    }

    /**
     * Sets the value of the name property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setName(JAXBElement<String> value) {
        this.name = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the domainId property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getDomainId() {
        return domainId;
    }

    /**
     * Sets the value of the domainId property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setDomainId(JAXBElement<String> value) {
        this.domainId = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the orderNum property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link Integer }{@code >}
     *     
     */
    public JAXBElement<Integer> getOrderNum() {
        return orderNum;
    }

    /**
     * Sets the value of the orderNum property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link Integer }{@code >}
     *     
     */
    public void setOrderNum(JAXBElement<Integer> value) {
        this.orderNum = ((JAXBElement<Integer> ) value);
    }

    /**
     * Gets the value of the roleType property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link Integer }{@code >}
     *     
     */
    public JAXBElement<Integer> getRoleType() {
        return roleType;
    }

    /**
     * Sets the value of the roleType property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link Integer }{@code >}
     *     
     */
    public void setRoleType(JAXBElement<Integer> value) {
        this.roleType = ((JAXBElement<Integer> ) value);
    }

    /**
     * Gets the value of the organizationalUnitRoleRelation property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnitRoleRelation }{@code >}
     *     
     */
    public JAXBElement<ArrayOfOrganizationalUnitRoleRelation> getOrganizationalUnitRoleRelation() {
        return organizationalUnitRoleRelation;
    }

    /**
     * Sets the value of the organizationalUnitRoleRelation property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnitRoleRelation }{@code >}
     *     
     */
    public void setOrganizationalUnitRoleRelation(JAXBElement<ArrayOfOrganizationalUnitRoleRelation> value) {
        this.organizationalUnitRoleRelation = ((JAXBElement<ArrayOfOrganizationalUnitRoleRelation> ) value);
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
