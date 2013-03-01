
package org.datacontract.schemas._2004._07.saff;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOfUser_OrganizationalUnit_Role_Relation complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOfUser_OrganizationalUnit_Role_Relation">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="User_OrganizationalUnit_Role_Relation" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}User_OrganizationalUnit_Role_Relation" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOfUser_OrganizationalUnit_Role_Relation", propOrder = {
    "userOrganizationalUnitRoleRelation"
})
public class ArrayOfUserOrganizationalUnitRoleRelation {

    @XmlElement(name = "User_OrganizationalUnit_Role_Relation", required = true, nillable = true)
    protected List<UserOrganizationalUnitRoleRelation> userOrganizationalUnitRoleRelation;

    /**
     * Gets the value of the userOrganizationalUnitRoleRelation property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the userOrganizationalUnitRoleRelation property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getUserOrganizationalUnitRoleRelation().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link UserOrganizationalUnitRoleRelation }
     * 
     * 
     */
    public List<UserOrganizationalUnitRoleRelation> getUserOrganizationalUnitRoleRelation() {
        if (userOrganizationalUnitRoleRelation == null) {
            userOrganizationalUnitRoleRelation = new ArrayList<UserOrganizationalUnitRoleRelation>();
        }
        return this.userOrganizationalUnitRoleRelation;
    }

}
