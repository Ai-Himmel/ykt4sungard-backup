#!/bin/bash
ip=$1
user=bank
password="bank"
ftp -in $ip <<!
user $user $password
binary
get $2 $3
!
