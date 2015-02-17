#!/bin/sh
# 
# File:   diffTest.sh
# Author: laurent
#
# Created on 2015-02-17, 09:40:31
#

diff mine his
if[ $? -ne 0 ]
then
    echo "The directory was modified"
