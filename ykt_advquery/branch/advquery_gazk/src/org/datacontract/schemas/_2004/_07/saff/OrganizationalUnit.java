
package org.datacontract.schemas._2004._07.saff;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAnyElement;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlType;
import org.w3c.dom.Element;


/**
 * <p>Java class for OrganizationalUnit complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="OrganizationalUnit">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="Id" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="DomainId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="Name" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="ParentId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="NumOfUsers" type="{http://www.w3.org/2001/XMLSchema}int" minOccurs="0"/>
 *         &lt;element name="Description" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="OrderNum" type="{http://www.w3.org/2001/XMLSchema}int" minOccurs="0"/>
 *         &lt;element name="Path" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="ExtendProperty" minOccurs="0">
 *           &lt;complexType>
 *             &lt;complexContent>
 *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                 &lt;sequence>
 *                   &lt;any/>
 *                 &lt;/sequence>
 *               &lt;/restriction>
 *             &lt;/complexContent>
 *           &lt;/complexType>
 *         &lt;/element>
 *         &lt;element name="OrganizationalUnit_Role_Relation" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfOrganizationalUnit_Role_Relation" minOccurs="0"/>
 *         &lt;element name="User_OrganizationalUnit_Role_Relation" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfUser_OrganizationalUnit_Role_Relation" minOccurs="0"/>
 *         &lt;element name="ChildOrganizationalUnits" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfOrganizationalUnit" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "OrganizationalUnit", propOrder = {
    "id",
    "domainId",
    "name",
    "parentId",
    "numOfUsers",
    "description",
    "orderNum",
    "path",
    "extendProperty",
    "organizationalUnitRoleRelation",
    "userOrganizationalUnitRoleRelation",
    "childOrganizationalUnits"
})
public class OrganizationalUnit {

    @XmlElement(name = "Id")
    protected String id;
    @XmlElementRef(name = "DomainId", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> domainId;
    @XmlElementRef(name = "Name", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> name;
    @XmlElementRef(name = "ParentId", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> parentId;
    @XmlElementRef(name = "NumOfUsers", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<Integer> numOfUsers;
    @XmlElementRef(name = "Description", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> description;
    @XmlElementRef(name = "OrderNum", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<Integer> orderNum;
    @XmlElementRef(name = "Path", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> path;
    @XmlElementRef(name = "ExtendProperty", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<OrganizationalUnit.ExtendProperty> extendProperty;
    @XmlElementRef(name = "OrganizationalUnit_Role_Relation", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<ArrayOfOrganizationalUnitRoleRelation> organizationalUnitRoleRelation;
    @XmlElementRef(name = "User_OrganizationalUnit_Role_Relation", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<ArrayOfUserOrganizationalUnitRoleRelation> userOrganizationalUnitRoleRelation;
    @XmlElementRef(name = "ChildOrganizationalUnits", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<ArrayOfOrganizationalUnit> childOrganizationalUnits;

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
     * Gets the value of the parentId property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getParentId() {
        return parentId;
    }

    /**
     * Sets the value of the parentId property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setParentId(JAXBElement<String> value) {
        this.parentId = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the numOfUsers property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link Integer }{@code >}
     *     
     */
    public JAXBElement<Integer> getNumOfUsers() {
        return numOfUsers;
    }

    /**
     * Sets the value of the numOfUsers property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link Integer }{@code >}
     *     
     */
    public void setNumOfUsers(JAXBElement<Integer> value) {
        this.numOfUsers = ((JAXBElement<Integer> ) value);
    }

    /**
     * Gets the value of the description property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getDescription() {
        return description;
    }

    /**
     * Sets the value of the description property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setDescription(JAXBElement<String> value) {
        this.description = ((JAXBElement<String> ) value);
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
     * Gets the value of the path property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getPath() {
        return path;
    }

    /**
     * Sets the value of the path property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setPath(JAXBElement<String> value) {
        this.path = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the extendProperty property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link OrganizationalUnit.ExtendProperty }{@code >}
     *     
     */
    public JAXBElement<OrganizationalUnit.ExtendProperty> getExtendProperty() {
        return extendProperty;
    }

    /**
     * Sets the value of the extendProperty property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link OrganizationalUnit.ExtendProperty }{@code >}
     *     
     */
    public void setExtendProperty(JAXBElement<OrganizationalUnit.ExtendProperty> value) {
        this.extendProperty = ((JAXBElement<OrganizationalUnit.ExtendProperty> ) value);
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

    /**
     * Gets the value of the childOrganizationalUnits property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}
     *     
     */
    public JAXBElement<ArrayOfOrganizationalUnit> getChildOrganizationalUnits() {
        return childOrganizationalUnits;
    }

    /**
     * Sets the value of the childOrganizationalUnits property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}
     *     
     */
    public void setChildOrganizationalUnits(JAXBElement<ArrayOfOrganizationalUnit> value) {
        this.childOrganizationalUnits = ((JAXBElement<ArrayOfOrganizationalUnit> ) value);
    }


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
     *         &lt;any/>
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
        "any"
    })
    public static class ExtendProperty {

        @XmlAnyElement(lax = true)
        protected Object any;

        /**
         * Gets the value of the any property.
         * 
         * @return
         *     possible object is
         *     {@link Element }
         *     {@link Object }
         *     
         */
        public Object getAny() {
            return any;
        }

        /**
         * Sets the value of the any property.
         * 
         * @param value
         *     allowed object is
         *     {@link Element }
         *     {@link Object }
         *     
         */
        public void setAny(Object value) {
            this.any = value;
        }

    }

}
