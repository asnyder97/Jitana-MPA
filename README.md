# Jitana-MPA  (Malicious Path Analyzer)
### **Summer Research Project at University of Lincoln-Nebraska to expand functionality of [Jitana](https://github.com/ytsutano/jitana/tree/master). Mentored and collobrated wih [Mohannad Alhanahnah](https://github.com/mhammad2).  Faculty sponser [Prof. Qiben Yan](http://cse.unl.edu/~qyan/)**

#### Setup

Initally ran and tested on [Orcale VirtualBox](https://www.virtualbox.org/) running Ubuntu 16.04 LTS.
IDE:  [Eclipse Neon](http://www.eclipse.org/neon/)
Language: C++

#### Implementation

**Step One**
Download [Jitana](https://github.com/ytsutano/jitana/tree/master)
  Instructions in Jitana Readme file.
  
**Step Two**
Create cc mysql database and use [schema](https://github.com/asnyder97/Jitana-MPA/blob/master/db/schema) to create necassary tables.
  Special note:  this schema and use of IC3 is thanks [SEALANT](https://softarch.usc.edu/sealant/).

[Mysql Insatallation](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-16-04) on Ubuntu 16.04, if not already installed.

**Step Three**
Installing [Mysql++](https://tangentsoft.com/mysqlpp/home)

sudo apt-get install mysql-server mysql-client
sudo apt-get install libmysqlclient-dev libmysql++-dev libmysqlcppconn-dev

Inlcude in libraries

'''python
/usr/include/mysql++
/usr/include/mysql
'''

Add Linkers

'''-lmysqlpp -lmysqlclient'''


