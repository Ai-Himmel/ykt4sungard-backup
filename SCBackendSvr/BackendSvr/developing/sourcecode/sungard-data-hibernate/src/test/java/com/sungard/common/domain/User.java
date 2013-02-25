package com.sungard.common.domain;

import static javax.persistence.GenerationType.IDENTITY;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

//import org.hibernate.annotations.GenericGenerator;

/**
 * User entity. @author MyEclipse Persistence Tools
 */
@Entity
@Table(name = "ACCT_USER")
public class User implements java.io.Serializable {

    // Fields

    private Long id;
    private String email;
    private String loginName;
    private String name;
    private String password;

    // private Set<AcctUserRole> acctUserRoles = new HashSet<AcctUserRole>(0);

    // Constructors

    /** default constructor */
    public User() {
    }

    /** minimal constructor */
    public User(String loginName) {
        this.loginName = loginName;
    }

    /** full constructor */
    public User(String email, String loginName, String name, String password
    // , Set<AcctUserRole> acctUserRoles
    ) {
        this.email = email;
        this.loginName = loginName;
        this.name = name;
        this.password = password;
        // this.acctUserRoles = acctUserRoles;
    }

    // Property accessors
    // @GenericGenerator(name = "generator", strategy = "uuid.hex")
    @Id
    // @GeneratedValue(generator = "generator")
    @GeneratedValue(strategy = IDENTITY)
    @Column(name = "ID", unique = true, nullable = false)
    public Long getId() {
        return this.id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    @Column(name = "EMAIL")
    public String getEmail() {
        return this.email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Column(name = "LOGIN_NAME", unique = true, nullable = false)
    public String getLoginName() {
        return this.loginName;
    }

    public void setLoginName(String loginName) {
        this.loginName = loginName;
    }

    @Column(name = "NAME")
    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Column(name = "PASSWORD")
    public String getPassword() {
        return this.password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    // @OneToMany(cascade = CascadeType.ALL, fetch = FetchType.LAZY, mappedBy =
    // "user")
    // public Set<AcctUserRole> getAcctUserRoles() {
    // return this.acctUserRoles;
    // }
    //
    // public void setAcctUserRoles(Set<AcctUserRole> acctUserRoles) {
    // this.acctUserRoles = acctUserRoles;
    // }

}