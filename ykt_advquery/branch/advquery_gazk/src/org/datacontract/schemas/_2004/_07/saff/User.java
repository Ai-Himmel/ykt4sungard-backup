
package org.datacontract.schemas._2004._07.saff;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAnyElement;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlType;
import javax.xml.datatype.XMLGregorianCalendar;
import org.w3c.dom.Element;


/**
 * <p>Java class for User complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="User">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="Id" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="Name" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="GenderID" type="{http://www.w3.org/2001/XMLSchema}int" minOccurs="0"/>
 *         &lt;element name="Photo" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="CreateDate" type="{http://www.w3.org/2001/XMLSchema}dateTime" minOccurs="0"/>
 *         &lt;element name="LastModifyDate" type="{http://www.w3.org/2001/XMLSchema}dateTime" minOccurs="0"/>
 *         &lt;element name="Status" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="DefaultOrderNum" type="{http://www.w3.org/2001/XMLSchema}int" minOccurs="0"/>
 *         &lt;element name="IDNo" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="IDNo2" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="DomainAccount" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="Email1" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="Email2" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="Email3" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="Mobile1" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="Mobile2" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="WordTel1" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="WordTel2" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="Office" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="HomeTel1" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="HomeTel2" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="HomeAddress" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="UserType" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
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
@XmlType(name = "User", propOrder = {
    "id",
    "name",
    "genderID",
    "photo",
    "createDate",
    "lastModifyDate",
    "status",
    "defaultOrderNum",
    "idNo",
    "idNo2",
    "domainAccount",
    "email1",
    "email2",
    "email3",
    "mobile1",
    "mobile2",
    "wordTel1",
    "wordTel2",
    "office",
    "homeTel1",
    "homeTel2",
    "homeAddress",
    "userType",
    "extendProperty",
    "userOrganizationalUnitRoleRelation"
})
public class User {

    @XmlElement(name = "Id")
    protected String id;
    @XmlElementRef(name = "Name", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> name;
    @XmlElement(name = "GenderID")
    protected Integer genderID;
    @XmlElementRef(name = "Photo", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> photo;
    @XmlElement(name = "CreateDate")
    protected XMLGregorianCalendar createDate;
    @XmlElement(name = "LastModifyDate")
    protected XMLGregorianCalendar lastModifyDate;
    @XmlElementRef(name = "Status", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> status;
    @XmlElementRef(name = "DefaultOrderNum", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<Integer> defaultOrderNum;
    @XmlElementRef(name = "IDNo", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> idNo;
    @XmlElementRef(name = "IDNo2", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> idNo2;
    @XmlElementRef(name = "DomainAccount", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> domainAccount;
    @XmlElementRef(name = "Email1", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> email1;
    @XmlElementRef(name = "Email2", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> email2;
    @XmlElementRef(name = "Email3", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> email3;
    @XmlElementRef(name = "Mobile1", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> mobile1;
    @XmlElementRef(name = "Mobile2", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> mobile2;
    @XmlElementRef(name = "WordTel1", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> wordTel1;
    @XmlElementRef(name = "WordTel2", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> wordTel2;
    @XmlElementRef(name = "Office", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> office;
    @XmlElementRef(name = "HomeTel1", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> homeTel1;
    @XmlElementRef(name = "HomeTel2", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> homeTel2;
    @XmlElementRef(name = "HomeAddress", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> homeAddress;
    @XmlElementRef(name = "UserType", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<String> userType;
    @XmlElementRef(name = "ExtendProperty", namespace = "http://schemas.datacontract.org/2004/07/SAFF.Organization", type = JAXBElement.class)
    protected JAXBElement<User.ExtendProperty> extendProperty;
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
     * Gets the value of the genderID property.
     * 
     * @return
     *     possible object is
     *     {@link Integer }
     *     
     */
    public Integer getGenderID() {
        return genderID;
    }

    /**
     * Sets the value of the genderID property.
     * 
     * @param value
     *     allowed object is
     *     {@link Integer }
     *     
     */
    public void setGenderID(Integer value) {
        this.genderID = value;
    }

    /**
     * Gets the value of the photo property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getPhoto() {
        return photo;
    }

    /**
     * Sets the value of the photo property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setPhoto(JAXBElement<String> value) {
        this.photo = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the createDate property.
     * 
     * @return
     *     possible object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public XMLGregorianCalendar getCreateDate() {
        return createDate;
    }

    /**
     * Sets the value of the createDate property.
     * 
     * @param value
     *     allowed object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public void setCreateDate(XMLGregorianCalendar value) {
        this.createDate = value;
    }

    /**
     * Gets the value of the lastModifyDate property.
     * 
     * @return
     *     possible object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public XMLGregorianCalendar getLastModifyDate() {
        return lastModifyDate;
    }

    /**
     * Sets the value of the lastModifyDate property.
     * 
     * @param value
     *     allowed object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public void setLastModifyDate(XMLGregorianCalendar value) {
        this.lastModifyDate = value;
    }

    /**
     * Gets the value of the status property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getStatus() {
        return status;
    }

    /**
     * Sets the value of the status property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setStatus(JAXBElement<String> value) {
        this.status = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the defaultOrderNum property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link Integer }{@code >}
     *     
     */
    public JAXBElement<Integer> getDefaultOrderNum() {
        return defaultOrderNum;
    }

    /**
     * Sets the value of the defaultOrderNum property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link Integer }{@code >}
     *     
     */
    public void setDefaultOrderNum(JAXBElement<Integer> value) {
        this.defaultOrderNum = ((JAXBElement<Integer> ) value);
    }

    /**
     * Gets the value of the idNo property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getIDNo() {
        return idNo;
    }

    /**
     * Sets the value of the idNo property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setIDNo(JAXBElement<String> value) {
        this.idNo = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the idNo2 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getIDNo2() {
        return idNo2;
    }

    /**
     * Sets the value of the idNo2 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setIDNo2(JAXBElement<String> value) {
        this.idNo2 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the domainAccount property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getDomainAccount() {
        return domainAccount;
    }

    /**
     * Sets the value of the domainAccount property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setDomainAccount(JAXBElement<String> value) {
        this.domainAccount = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the email1 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getEmail1() {
        return email1;
    }

    /**
     * Sets the value of the email1 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setEmail1(JAXBElement<String> value) {
        this.email1 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the email2 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getEmail2() {
        return email2;
    }

    /**
     * Sets the value of the email2 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setEmail2(JAXBElement<String> value) {
        this.email2 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the email3 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getEmail3() {
        return email3;
    }

    /**
     * Sets the value of the email3 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setEmail3(JAXBElement<String> value) {
        this.email3 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the mobile1 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getMobile1() {
        return mobile1;
    }

    /**
     * Sets the value of the mobile1 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setMobile1(JAXBElement<String> value) {
        this.mobile1 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the mobile2 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getMobile2() {
        return mobile2;
    }

    /**
     * Sets the value of the mobile2 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setMobile2(JAXBElement<String> value) {
        this.mobile2 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the wordTel1 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getWordTel1() {
        return wordTel1;
    }

    /**
     * Sets the value of the wordTel1 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setWordTel1(JAXBElement<String> value) {
        this.wordTel1 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the wordTel2 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getWordTel2() {
        return wordTel2;
    }

    /**
     * Sets the value of the wordTel2 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setWordTel2(JAXBElement<String> value) {
        this.wordTel2 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the office property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getOffice() {
        return office;
    }

    /**
     * Sets the value of the office property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setOffice(JAXBElement<String> value) {
        this.office = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the homeTel1 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getHomeTel1() {
        return homeTel1;
    }

    /**
     * Sets the value of the homeTel1 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setHomeTel1(JAXBElement<String> value) {
        this.homeTel1 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the homeTel2 property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getHomeTel2() {
        return homeTel2;
    }

    /**
     * Sets the value of the homeTel2 property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setHomeTel2(JAXBElement<String> value) {
        this.homeTel2 = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the homeAddress property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getHomeAddress() {
        return homeAddress;
    }

    /**
     * Sets the value of the homeAddress property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setHomeAddress(JAXBElement<String> value) {
        this.homeAddress = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the userType property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getUserType() {
        return userType;
    }

    /**
     * Sets the value of the userType property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setUserType(JAXBElement<String> value) {
        this.userType = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the extendProperty property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link User.ExtendProperty }{@code >}
     *     
     */
    public JAXBElement<User.ExtendProperty> getExtendProperty() {
        return extendProperty;
    }

    /**
     * Sets the value of the extendProperty property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link User.ExtendProperty }{@code >}
     *     
     */
    public void setExtendProperty(JAXBElement<User.ExtendProperty> value) {
        this.extendProperty = ((JAXBElement<User.ExtendProperty> ) value);
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
