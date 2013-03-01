
package org.datacontract.schemas._2004._07.saff;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for User_OrganizationalUnit_Role_Relation complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="User_OrganizationalUnit_Role_Relation">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="UserId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="OrganizationalUnitRoleRelationId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="OrganizationalUnitId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="RoleId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="IsDefault" type="{http://www.w3.org/2001/XMLSchema}boolean" minOccurs="0"/>
 *         &lt;element name="OrderNum" type="{http://www.w3.org/2001/XMLSchema}int" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "User_OrganizationalUnit_Role_Relation", propOrder = {
    "userId",
    "organizationalUnitRoleRelationId",
    "organizationalUnitId",
    "roleId",
    "isDefault",
    "orderNum"
})
public class UserOrganizationalUnitRoleRelation {

    @XmlElement(name = "UserId")
    protected String userId;
    @XmlElement(name = "OrganizationalUnitRoleRelationId")
    protected String organizationalUnitRoleRelationId;
    @XmlElement(name = "OrganizationalUnitId")
    protected String organizationalUnitId;
    @XmlElement(name = "RoleId")
    protected String roleId;
    @XmlElementRef(name = "IsDefault", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<Boolean> isDefault;
    @XmlElementRef(name = "OrderNum", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<Integer> orderNum;

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

    /**
     * Gets the value of the organizationalUnitRoleRelationId property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getOrganizationalUnitRoleRelationId() {
        return organizationalUnitRoleRelationId;
    }

    /**
     * Sets the value of the organizationalUnitRoleRelationId property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setOrganizationalUnitRoleRelationId(String value) {
        this.organizationalUnitRoleRelationId = value;
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
     * Gets the value of the isDefault property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link Boolean }{@code >}
     *     
     */
    public JAXBElement<Boolean> getIsDefault() {
        return isDefault;
    }

    /**
     * Sets the value of the isDefault property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link Boolean }{@code >}
     *     
     */
    public void setIsDefault(JAXBElement<Boolean> value) {
        this.isDefault = ((JAXBElement<Boolean> ) value);
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

}
